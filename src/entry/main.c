/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 19时03分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
 
#include "multiboot.h"
#include "montior.h"
#include "descriptor_tables.h"
#include "idt_tables.h"
#include "isr.h"
#include "timer.h"
#include "printk.h"
#include "mm.h"
#include "heap.h"
#include "schedule.h"
#include "thread.h"


/*定义一个全局变量*/
int flag = 0 ;

/*定义一个线程*/
int thread (void *args)
{
	while (1)
	{
		if (flag == 1)
		{
			monitor_write ("B");
			asm volatile ("sti"); //这是重点，因为在线程切换后，中断关闭，这一步是将中断打开
			flag = 0 ;  //释放锁
		}
	}
	return 0 ;
}

int main(struct multiboot_t *mboot_ptr)
{
	init_gdt () ; //初始化gdt
	init_idt() ; //初始化idt

	monitor_clear () ;
	printk ("hello,world\n");
//	monitor_write ("hello, world");
//	monitor_write ("\n");
 //       asm volatile ("int $0x3");
	init_timer (200);  //初始化中断
	asm volatile ("sti"); //打开中断
	init_pmm (mboot_ptr);  
	//init_page_pmm (mboot_ptr) ;
	init_vmm () ;
	init_page_pmm (mboot_ptr);
	//u32int *ptr = (u32int*)0xA0000000;
	//u32int  do_page_fault = *ptr ;

        printk ("from heap malloc :\n");
 	int a = kmalloc (8);
 	int b = kmalloc (8);
	//kfree (a);
	//kfree (b);
	//int c = kmalloc (16);
	printk ("a = 0x%x\n" , a);
	printk ("b = 0x%x\n",  b);
	

	printk ("from heap free\n");
	kfree (a) ;
	kfree (b) ;
        
   
	init_schedule ();
	asm volatile ("sti");
	create_thread (thread ,(char*)0);

	while (1)
	{
		if (flag == 0 )
		{
			monitor_write ("A");
			asm volatile ("sti");
			flag = 1;
		}
	}
   
	//kfree (c) ;


//	monitor_write ("OK");

	


	return 0;
}

