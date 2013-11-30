/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  时钟控制函数
 *
 *        Version:  1.0
 *        Created:  2013年10月17日 15时45分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "timer.h"
#include "isr.h"
#include "montior.h"
#include "schedule.h"

u32int tick = 0  ;
void  timer_callback (registers_t  *regs)
{
	schedule ();
	tick ++ ;
//	monitor_write ("Tick \n");
/*//	monitor_write_dec (tick);
	monitor_write ("\n");
	*/
	
}
void init_timer (u32int frequency)
{
	//monitor_write ("hello");
	register_interrupt_handler (IRQ0 , timer_callback) ;

	u32int divisor = 1193180 / frequency;
	outb (0x43, 0x36);
	u8int l = (u8int) (divisor & 0xff);
	u8int h = (u8int) ((divisor >> 8) &  0xff);

	outb (0x40 , l); 
	outb (0x40 , h);
}
