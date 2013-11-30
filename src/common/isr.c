/*
 * =====================================================================================
 *
 *       Filename:  isr.c
 *
 *    Description:  中断处理函数
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 20时47分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "montior.h"
#include "isr.h"



void isr_handler (registers_t  *regs)
{
	if (regs->int_no >= 32)
	{
		monitor_write ("unable interrupt\n");
		return ;

	}
        if (interrupt_handlers[regs->int_no])
	{
		isr_t   handler = interrupt_handlers[regs->int_no];
		handler (regs);
	}
       /* 
	monitor_write ("received interrupt");
	monitor_write_dec (regs->int_no);
	monitor_write("\n");*/
}
void irq_handler (registers_t  *regs)
{
 
	if (regs->int_no >= 40)
	{
		outb (0xa0 , 0x20);
	}
	outb (0x20 , 0x20);
	
	//monitor_write_dec (regs.int_no);
	//monitor_write("\n");
	//regs.int_no = regs.int_no + 32 ;
	if (interrupt_handlers[regs->int_no] )
	{
          //      monitor_write ("go\n");
		isr_t handler = interrupt_handlers[regs->int_no];
		handler (regs);
	}
}
void register_interrupt_handler (u8int n , isr_t handler)
{
//	monitor_write ("yes\n");
//	monitor_write_dec (n);
//	monitor_write("\n");
	interrupt_handlers[n] = handler ;
}
