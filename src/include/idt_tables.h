/*
 * =====================================================================================
 *
 *       Filename:  idt_tables.h
 *
 *    Description:   中断描述符表
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 17时29分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef  IDT_TABLES_H
#define  IDT_TABLES_H

#include "common.h"

struct idt_entry_struct 
{
	u16int   offset_1 ;  //中断处理过程在目标代码段内的偏移的低16位
	u16int   self  ;     //代码段描述符选择子
	u8int    always0 ;   //必须是0（unused）
	u8int    flag  ;     //其中包含 (P， DPL ， )
	u16int   offset_2 ; //中断处理过程在目标代码段内的偏移的高16位
}__attribute__ ((packed));

typedef struct idt_entry_struct  idt_entry_t ;

/*
 * idtr
 */

struct idt_ptr_struct 
{
	u16int   limit ;//定义中断描述符表的界限
	u32int   base  ; //这个地址描述的是在idt_entry_t array 中第一个元素的地址
}__attribute__ ((packed));
typedef struct idt_ptr_struct    idt_ptr_t ;


/*
 * 其中的flag由一下的几部分组成
 *----+---+--+--+---+---+---+----+
 *|p  |  DPL |s | GateType       |
 *-------------------------------
 *offset : (48--63) and (0 ---16)
 * p = 0 ,没有使用的中断 （47）
 * dpl (45, 46) 中断的特权级别
 * s  (44) s= 0 , 是中断门
 * Gatetype : (40--43)  0x5  :任务门(80386 32-bit)
 *                      0x6  :中断门(80286 16-bit)
 *                      0x7  :陷阱门(80286 16-bit)
 *                      0xE  :中断门(80386 32-bit)
 *                      0xF  :陷阱门(80386 32-bit)
 * 0: (32-39)全部都是0 
 * selector :(16-31) 
 */

/*中断*/
void isr0(); 		// 0 #DE 除 0 异常 
void isr1(); 		// 1 #DB 调试异常 
void isr2(); 		// 2 NMI 
void isr3(); 		// 3 BP 断点异常 
void isr4(); 		// 4 #OF 溢出 
void isr5(); 		// 5 #BR 对数组的引用超出边界 
void isr6(); 		// 6 #UD 无效或未定义的操作码 
void isr7(); 		// 7 #NM 设备不可用(无数学协处理器) 
void isr8(); 		// 8 #DF 双重故障(有错误代码) 
void isr9(); 		// 9 协处理器跨段操作 
void isr10(); 		// 10 #TS 无效TSS(有错误代码) 
void isr11(); 		// 11 #NP 段不存在(有错误代码) 
void isr12(); 		// 12 #SS 栈错误(有错误代码) 
void isr13(); 		// 13 #GP 常规保护(有错误代码) 
void isr14(); 		// 14 #PF 页故障(有错误代码) 
void isr15(); 		// 15 CPU 保留 
void isr16(); 		// 16 #MF 浮点处理单元错误 
void isr17(); 		// 17 #AC 对齐检查 
void isr18(); 		// 18 #MC 机器检查 
void isr19(); 		// 19 #XM SIMD(单指令多数据)浮点异常

/*intel 保留*/
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();
void irq0 () ;
void irq1();
void irq2 () ;
void irq3 () ;
void irq4 () ;
void irq5 () ;
void irq6 () ;
void irq7 () ;
void irq8 () ;
void irq9 () ;
void irq10 () ;
void irq11 () ;
void irq12 () ;
void irq13 () ;
void irq14 () ;
void irq15 () ;


/*32-255  用户自定义中断*/
void isr255() ;

void init_idt () ;
void idt_flush (u32int) ;


#endif

