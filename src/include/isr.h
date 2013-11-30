/*
 * =====================================================================================
 *
 *       Filename:  isr.h
 *
 *    Description:  中断服务
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 20时41分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef ISR_H
#define ISR_H

#include "common.h"

#define IRQ0  32 
#define IRQ1  33 
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47




typedef struct registers 
{
	u32int    ds  ; //数据段选择子
	u32int    edi , esi , ebp , esp , ebx , edx, ecx, eax ; //pusha 
	u32int    int_no , error_code ;//中断号， 错误号码
	u32int    eip , cs , eflags , useresp , ss ;
}registers_t ;


typedef void  (*isr_t)  (registers_t *);

isr_t    interrupt_handlers[256];
extern void isr_handler (registers_t  *regs);
extern void irq_handler (registers_t  *regs);
extern void  register_interrupt_handler (u8int  n ,isr_t  handler);
#endif 




