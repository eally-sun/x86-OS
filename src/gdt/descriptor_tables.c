/*
 * =====================================================================================
 *
 *       Filename:  descriptor_tables.c
 *
 *    Description:  段描述符表的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月14日 17时20分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "common.h"
#include "descriptor_tables.h"
#include "montior.h"
#include "printk.h"
#define   Segmet_Max  5  

/*
 *初始化 GDT
 * 
 */


static void gdt_set_gate (s32int , u32int , u32int , u8int ,u8int);

gdt_entry_t     gdt_entries[Segmet_Max];
gdt_ptr_t       gdt_ptr ;



void init_gdt () 
{
	gdt_ptr.limit = (sizeof (gdt_entry_t )*Segmet_Max) -1 ;  //初始化段描述符表的长度
	gdt_ptr.base = (u32int)&gdt_entries;      //计算段描述符表的首地址a

	gdt_set_gate (0, 0 , 0 , 0, 0) ; //处理器规定第一个描述符表是空描述符(哑描述符和 NULL 描述符),
                                      //这是寄存器和内存在初始化值会是0 ， 加上程序的设计，就会无意的用0来作为索引来选择描述符


	//采用平坦寻址方式，段长机制都0 ，段长都是0xFFFFFFF
	//代码段在全局描述符表的位置是1， 基址是0 ，限长是4G ， 在内存中，系统段，特权是0 , 具有执行，读，向上扩展的权利
	
	gdt_set_gate (1 , 0 , 0xfffff, 0x9A, 0xcf) ; //code segment ; (系统)
        gdt_set_gate (2 , 0 , 0xfffff,  0x92 ,0xcf) ; //data segment ; 具有读写和向上扩展的权利（系统）
	gdt_set_gate (3 , 0 , 0xffffffff, 0xFA , 0xcf) ; //用户代码段  （用户， p=1 , dpl= 3 , s=1 type =1010）
	gdt_set_gate (4 , 0 , 0xffffffff, 0xF2 , 0xcf) ; //用户数据段  (用户，p =1 , dpl = 3, s=1 ,type =0010)

	gdt_flush ((u32int)&gdt_ptr);

}


static void gdt_set_gate (s32int num, u32int base , u32int limit , u8int access , u8int gran )
{
	gdt_entries[num].base_low = (base & 0xFFFF);   //基地址低16位
	gdt_entries[num].limit_low = (limit & 0xFFFF); // 段线程的低16位
	gdt_entries[num].base_middle = (base >> 16)& 0xFF ;//通过右移裁取了基地址的中间8位
	gdt_entries[num].granularity = ((limit>>16) &0x0F); //得到21位段界限的的高4位 ，这部分段界限的长度包含在granularity的低4位。
	gdt_entries[num].access = access ;          
	gdt_entries[num].granularity |= gran & 0xF0;  //为了得到graularity里面的高四位里面，但是最后的或是为了保证前面在granularity里面设置的低4位                                                        值不被清空
	gdt_entries[num].base_high= (base>>24 & 0xff); //得到基地址的高8位
        
         /*
	  * 所谓的清空流水线就是，在进入保护模式之前，很多指令已经进入了流水线，cs中会残留实模式内容，由于32位编译，就对操作数和默认地址的大小解释 
	  * 不同，从而影响指令的执行结果。因此这个时候就必须清空流水线，重新让指令自然顺序的执行
	  */

	
}


