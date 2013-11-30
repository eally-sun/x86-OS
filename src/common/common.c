/*
 * =====================================================================================
 *
 *       Filename:  common.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 21时58分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "common.h"

/*
 * asm 是__asm__的别名，而volatile 是__volatile__的别名，是允许在你的代码中内嵌汇编代码 %0%1，代表使用寄存器的样板操作数，而到具体的寄存器的时候
 * 就使用%%cr0，是将port 放入到edx寄存器，而将value 放入到eax寄存器中
 */

/*
 *规则：   __asm__(汇编语句模板: 输出部分: 输入部分: 破坏描述部分)  
 *共四个部分：汇编语句模板，输出部分，输入部分，破坏描述部分，各部分使用“:”格开，汇编语句模板必不可少，
 *其他三部分可选，如果使用了后面的部分，而前面部分为空，也需要用“:”格开，相应部分内容为空。
 *
 * %1 ，%0 被称为是立即数
 * "a"   eax  (如果被占用，则先压入栈，在用，因此在这之前加入一个push eax)
 * "b"   ebx 
 * "d"   edi 
 * "N"   0-255之间的立即数
 *  intel 处理器，允许256个中断，中端的端口号在"0-255",所以这里要使用"N",表示输入的端口号在0-255之间
 *
 *  想要了解更多的信息，阅读《x86 从实模式到保护模式》，
 *  关于GCC 内联汇编可以阅读：
 *  http://wenku.baidu.com/view/fe454e3a87c24028915fc3c4.html
 * 
 */


/*
 * 写入端口 
 */
void outb (u16int port , u8int value)
{
	asm volatile ("outb %1 ,%0" ::"dN" (port ), "a"(value));
}

/*
 * 从端口读出
 */
u8int inb (u16int port )
{
        u8int  ret ;
	asm volatile ("inb  %1 , %0":"=a"(ret):"dN"(port));
	return ret ;
}

u16int inw (u16int port)
{
	u16int  ret ;
	asm volatile ("inw %1, %0":"=a"(ret):"dN" (port));
        return ret ;
	
}


