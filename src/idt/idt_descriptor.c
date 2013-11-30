/*
 * =====================================================================================
 *
 *       Filename:  idt_descriptor.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 18时47分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "string.h"
#include "idt_tables.h"
#include "isr.h"
#include "printk.h"

static void idt_set_gate (u8int , u32int , u16int , u8int);

idt_entry_t   idt_entries[256];
idt_ptr_t     idt_ptr ;

//isr_t   interrupt_handlers[256];

//8258芯片的控制
void init_con_idt () 
{
	outb(0x20 , 0x11); //ICW1  初始化，并且设置工作的方式是上升沿触发，间隔8秒，多级连片，写ICW4
	outb(0xA0 , 0x11);

	outb(0x21, 0x20);  //ICW2  设置中断类型号（IR0-IR7）
	outb(0xA1, 0x28);  //设置中断号（IR8-IR15）

	outb (0x21, 0x04); //ICW3  设置主从芯片的连接方式(主片的IR2与从片相连)
	outb (0xA1, 0x02); //设置与主片的IR2相连

	outb (0x21,0x01); //ICW4 设置工作方式与第一个有很大的不同自通采用8086微处理器
	outb (0xA1,0x01);

	outb(0x21, 0x0);  //OCW1 允许中断请求
	outb(0xA1, 0x0);



}
void init_idt_set_gate ()
{
	/*用于中断处理*/
	idt_set_gate( 0, (u32int)isr0 , 0x08, 0x8E);
	idt_set_gate( 1, (u32int)isr1 , 0x08, 0x8E);
	idt_set_gate( 2, (u32int)isr2 , 0x08, 0x8E);
	idt_set_gate( 3, (u32int)isr3 , 0x08, 0x8E);
	idt_set_gate( 4, (u32int)isr4 , 0x08, 0x8E);
	idt_set_gate( 5, (u32int)isr5 , 0x08, 0x8E);
	idt_set_gate( 6, (u32int)isr6 , 0x08, 0x8E);
	idt_set_gate( 7, (u32int)isr7 , 0x08, 0x8E);
	idt_set_gate( 8, (u32int)isr8 , 0x08, 0x8E);
	idt_set_gate( 9, (u32int)isr9 , 0x08, 0x8E);
	idt_set_gate(10, (u32int)isr10, 0x08, 0x8E);
	idt_set_gate(11, (u32int)isr11, 0x08, 0x8E);
	idt_set_gate(12, (u32int)isr12, 0x08, 0x8E);
	idt_set_gate(13, (u32int)isr13, 0x08, 0x8E);
	idt_set_gate(14, (u32int)isr14, 0x08, 0x8E);
	idt_set_gate(15, (u32int)isr15, 0x08, 0x8E);
	idt_set_gate(16, (u32int)isr16, 0x08, 0x8E);
	idt_set_gate(17, (u32int)isr17, 0x08, 0x8E);
	idt_set_gate(18, (u32int)isr18, 0x08, 0x8E);
	idt_set_gate(19, (u32int)isr19, 0x08, 0x8E);
	idt_set_gate(20, (u32int)isr20, 0x08, 0x8E);
	idt_set_gate(21, (u32int)isr21, 0x08, 0x8E);
	idt_set_gate(22, (u32int)isr22, 0x08, 0x8E);
	idt_set_gate(23, (u32int)isr23, 0x08, 0x8E);
	idt_set_gate(24, (u32int)isr24, 0x08, 0x8E);
	idt_set_gate(25, (u32int)isr25, 0x08, 0x8E);
	idt_set_gate(26, (u32int)isr26, 0x08, 0x8E);
	idt_set_gate(27, (u32int)isr27, 0x08, 0x8E);
	idt_set_gate(28, (u32int)isr28, 0x08, 0x8E);
	idt_set_gate(29, (u32int)isr29, 0x08, 0x8E);
	idt_set_gate(30, (u32int)isr30, 0x08, 0x8E);
	idt_set_gate(31, (u32int)isr31, 0x08, 0x8E);
        
	idt_set_gate (32, (u32int)irq0,   0x08, 0x8E);
	idt_set_gate (33, (u32int)irq1,   0x08, 0x8E);
	idt_set_gate (34, (u32int)irq2,   0x08, 0x8E);
	idt_set_gate (35, (u32int)irq3,   0x08, 0x8E);
	idt_set_gate (36, (u32int)irq4,   0x08, 0x8E);
	idt_set_gate (37, (u32int)irq5,   0x08, 0x8E);
	idt_set_gate (38, (u32int)irq6,   0x08, 0x8E);
	idt_set_gate (39, (u32int)irq7,   0x08, 0x8E);
	idt_set_gate (40, (u32int)irq8,   0x08, 0x8E);
	idt_set_gate (41, (u32int)irq9,   0x08, 0x8E);
	idt_set_gate (42, (u32int)irq10,  0x08, 0x8E);
	idt_set_gate (43, (u32int)irq11,  0x08, 0x8E);
	idt_set_gate (44, (u32int)irq12,  0x08, 0x8E);
	idt_set_gate (45, (u32int)irq13,  0x08, 0x8E);
	idt_set_gate (46, (u32int)irq14,  0x08, 0x8E);
	idt_set_gate (47, (u32int)irq15,  0x08, 0x8E);

	idt_set_gate(255, (u32int)isr255, 0x08, 0x8E);


}


/*8259芯片控制*/
void init_idt () 
{
	init_con_idt () ;

	idt_ptr.limit = sizeof (idt_entry_t)*256 -1 ;
	idt_ptr.base  = (u32int )&idt_entries ;
       
        printk ("idt:0x%x\n", idt_ptr.base);

	memset ((u8int*)&idt_entries , 0 , sizeof (idt_entry_t)*256);
	memset ((u8int*)&interrupt_handlers, 0 , sizeof (isr_t)*256);
        
	init_idt_set_gate () ;
	idt_flush((u32int)&idt_ptr);

}
static void idt_set_gate (u8int num , u32int base , u16int sel ,u8int flags)
{
	idt_entries[num].offset_1 = base & 0xFFFF ;
	idt_entries[num].offset_2 = (base >> 16) & 0xFFFF ;
	idt_entries[num].self = sel ; 
	idt_entries[num].flag = flags ;

        idt_flush((u32int)&idt_ptr);

}
