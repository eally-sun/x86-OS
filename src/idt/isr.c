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

//ISR
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
}

//IRQ
void irq_handler (registers_t  *regs)
{
 
	if (regs->int_no >= 40)
	{
		outb (0xa0 , 0x20);
	}
	outb (0x20 , 0x20);
	
	if (interrupt_handlers[regs->int_no] )
	{
                isr_t handler = interrupt_handlers[regs->int_no];
		handler (regs);
	}
}
//注册中断
void register_interrupt_handler (u8int n , isr_t  handler)
{
	interrupt_handlers[n] = handler ;
}
