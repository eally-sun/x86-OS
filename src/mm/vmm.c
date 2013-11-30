/*
 * =====================================================================================
 *
 *       Filename:  vmm.c
 *
 *    Description:  虚拟内存管理
 *
 *        Version:  1.0
 *        Created:  2013年10月22日 16时25分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "mm.h"
#include "string.h"
#include "montior.h"
#include "printk.h"

//内核的页目录
u32int *page_directory = (u32int*)PAGE_DIR_VIRTUAL_ADDR ;
//内核页表
u32int *page_tables = (u32int*)PAGE_TABLE_VIRTUAL_ADDR ;

page_directory_t   *current_directory ;


void init_vmm () 
{
	int        i  ; 
	u32int     cr0 ;
        
	//注册页错误处理函数
	register_interrupt_handler (14 , &page_fault);
       
	page_directory_t  *pd = (page_directory_t *)pmm_alloc_page () ;
	memset ((void*)pd, 0 , 0x1000) ;  //为页目录分配大小 ,1024 *4K = 4096  ，将32位全部置0 ，
        /*页目录的第一项用来映射第一个4MB ，我们的内核代码放置在4MB 一下,因此我们要保证当前的物理地址=虚拟地址，这样的好处就是内核代码不用做任何变         化可以在分页机制下正常共了*/

	pd[0] = pmm_alloc_page () |PAGE_PRESENT |PAGE_WRITE ;  //设置低12位
        
//	printk("pd's address : 0x%x\n", pd);
        //printk ("pd[0] address: 0x%x\n",&pd[0] )
	u32int *pt = (u32int ) (pd[0] & PAGE_MASK) ; 
//	printk ("pt's address : 0x%x\n", pt);
        
	/*相当与左移12位*/
	for (i = 0 ; i < 1024 ; i++){
		pt[i] = i* 0x1000 | PAGE_PRESENT |PAGE_WRITE ;
	}
        
        //FFBFF000拆开就是1111, 1111, 10是1022 ,11 1111, 1111 是1023
	pd [1022] = pmm_alloc_page ()  |PAGE_PRESENT |PAGE_WRITE ;
	pt = (u32int *) (pd[1022] & PAGE_MASK);
	memset ((void*)pt , 0 , 0x1000) ; 
	//printk ("pd 1022 's address : 0x%x\n", &pd[1022]);

	pt[1023] = (u32int)pd |PAGE_PRESENT |PAGE_WRITE ;
	pd[1023] = (u32int)pd |PAGE_PRESENT |PAGE_WRITE ;
	printk ("pd 1023 0x%x\n", pd[1023]);

	switch_page_directory (pd) ;
	asm volatile ("mov %%cr0 , %0" :"=r" (cr0)) ;
	cr0 |= 0x80000000 ;
	asm volatile ("mov %0 , %%cr0" ::"r" (cr0));
        
	u32int  pt_idx = PAGE_DIR_IDX ((PMM_STACK_ADDR >>12));
        page_directory[pt_idx] = pmm_alloc_page () |PAGE_PRESENT |PAGE_WRITE ;
	
        memset ((void*)page_tables[pt_idx *1024] , 0 , 0x1000);

	mm_paging_active = 1 ;
}
void switch_page_directory (page_directory_t  *pd)
{
	current_directory = pd ;
	/*
	 * cr3 控制寄存器，存放当前任务页目录的物理地址。页目录给出所有页表的地址，每个页表给出所包含物理页的地址。
	 * 页部件将专门将线性地址到物理地址，将32位线性地址截成3部分，高10位是页目录，中间的10位是页表，剩下的12位是页内偏移。 
	 * 根据段部件取出他的高10位*4 （每个页目录4个字节）,作为要访问的页目录。在根据处理器所提供的物理地址+偏移地址，就找到页表的物理地址.
	 *
	 */
	asm volatile ("mov %0 , %%cr3"::"r" (pd));


}
void map (u32int va , u32int pa , u32int flags)
{
	u32int virtual_page = va / 0x1000;
	u32int pt_idx = PAGE_DIR_IDX (virtual_page);

	if (page_directory[pt_idx] == 0 )
	{
		page_directory[pt_idx] = pmm_alloc_page()|PAGE_PRESENT|PAGE_WRITE;
		memset ((void*) page_tables[pt_idx *1024] , 0 , 0x1000);

	}

	page_tables[virtual_page] = (pa & PAGE_MASK) |flags ;


}
void unmap (u32int va)
{
	u32int virtual_page = va /0x1000 ;
	page_tables[virtual_page] = 0 ;
	asm volatile ("invlpg (%0)"::"a"(va));



}
int  get_mapping (u32int va , u32int *pa)
{
	u32int  virtual_page = va /0x1000 ;
	u32int  pt_idx = PAGE_DIR_IDX (virtual_page);

	if (page_directory[pt_idx] == 0)
	{
		return 0 ;
        }

	if (page_tables[virtual_page] != 0 && pa)
	{
		*pa = page_tables[virtual_page] &PAGE_MASK ;
		 return 1 ; 
	}
	return -1 ;
}
void page_fault (registers_t  *regs)
{
	u32int cr2 ;
	asm volatile ("mov %%cr2 , %0" :"=r" (cr2));

	printk ("page fault at : 0x%x   virtual faulting address: 0x%x error code  0x%x\n", regs->eip , cr2 , regs->error_code);
	/*
	monitor_write ("page fault at :") ;
	monitor_write_hex ("regs->eip");
	monitor_write ("\n");
	monitor_write ("faulting address :");
	monitor_write_hex (cr2);
	monitor_write ("page_fault:");
	monitor_write_hex (regs->err_code);
	monitor_write ("\n");*/

	for (;;);
	
}
