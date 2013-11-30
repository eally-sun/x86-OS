/*
 * =====================================================================================
 *
 *       Filename:  mm.c
 *
 *    Description:  内存管理的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月21日 17时35分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "mm.h"
#include "montior.h"
#include "multiboot.h"
#include "printk.h"
/*
 *建立在栈基础上的内存管理
 *先把空闲的地址全部入栈，然后当在需要的时候，从栈中弹出。
 *
 */


u32int pmm_stack_loc =  PMM_STACK_ADDR ;  //栈指针
u32int pmm_stack_max =  PMM_STACK_ADDR ;  //内存申请的界限

u32int pmm_location ;

//开启分页,开启分页的时候=1
char mm_paging_active = 0 ;



void init_pmm (struct multiboot_t *mboot_ptr)
{


	printk ("mem_lower: 0x%x\n",mboot_ptr->mem_lower *1024 );
	printk ("mem_upper: 0x%x\n",mboot_ptr->mem_upper * 1024);
        
	mmap_entry_t  *mmap ;
	printk ("mmap_addr = 0x%x , mmap_length=0x%x\n\n",(unsigned)mboot_ptr->mmap_addr , (unsigned)mboot_ptr->mmap_length );
        
	/*
	 *探测物理布局
	 *
	 */
	for (mmap = (mmap_entry_t *)mboot_ptr->mmap_addr ; (u32int)mmap < mboot_ptr->mmap_addr + mboot_ptr->mmap_length; 
			mmap = (mmap_entry_t *)((u32int)mmap + mmap->size + sizeof (mmap->size)))
        {
		printk ("base_addr : 0x%x%x  length: 0x%x%x     type: 0x%x   size: 0x%x\n\n", mmap->base_addr_high,
					mmap->base_addr_low , mmap->length_high, mmap->length_low, mmap->type , mmap->size);
	
	}
        
	u32int  i = mboot_ptr->mmap_addr ;

	while (i < mboot_ptr->mmap_addr + mboot_ptr->mmap_length)
	{
		mmap_entry_t   *map_entry = (mmap_entry_t *)i ;
                /*
		 * 在1MB 之下只有一个一段可以使用的内存
		 */
		if (map_entry->type == 1 && map_entry->base_addr_low < 0x0100000)           {
			pmm_location = (map_entry->base_addr_low + 0x1000) & PAGE_MASK ;
			return ;
                 }
		i += map_entry->size + sizeof (u32int);


	}
	monitor_write ("not find the 1MB under memory\n");

}
void init_page_pmm (multiboot_t  *mboot_ptr)
{
	u32int  i = mboot_ptr->mmap_addr ;
	while (i < mboot_ptr->mmap_addr + mboot_ptr->mmap_length)
	{
	          mmap_entry_t  *map_entry = (mmap_entry_t *)i ;
		  //管理1MB之上的内存
		  if (map_entry->type == 1 && map_entry->base_addr_low >= 0x100000)
		  {
			  u32int  j = map_entry->base_addr_low ;
			  while (j < map_entry->base_addr_low + map_entry->length_low)
			  {
				  //这里实现比较简单，是直接跳过1MB , 因为1MB 里面的数据内容比较复杂，数据的一点操作，就会给很大的灾难.
				  if ( j == 0x100000)
				  {
					  j += 0x100000 ; //0x100000 = 1MB 
				  }
				  pmm_free_page (j) ;
				  j += 0x1000 ;
			  }
		  }
		  i += map_entry->size + sizeof (u32int);
	}
}
u32int pmm_alloc_page () 
{
	if (mm_paging_active)
	{
		if (pmm_stack_loc == PMM_STACK_ADDR)
		{
		   monitor_write ("Error : out of memory\n");	

		}
		//出栈
		pmm_stack_loc -=sizeof (u32int);
		u32int *stack = (u32int*)pmm_stack_loc ;
		return *stack ;

	}
	else 
	{
		return pmm_location += 0x1000;
	}
}
void pmm_free_page (u32int  p ) 
{
	
	if (p  <  pmm_location)
	      return ;
        //进栈
	//空闲的页面已经分配完了，需要映射一页内存来存储索引
	if (pmm_stack_max <= pmm_stack_loc)
	{
		map (pmm_stack_max , p , PAGE_PRESENT | PAGE_WRITE);
		pmm_stack_max += 4096 ;
	}
	else 
	{
		u32int *stack = (u32int*)pmm_stack_loc ;
		*stack = p ;
		pmm_stack_loc += sizeof (u32int); 

	}
	
}
