/*
 * =====================================================================================
 *
 *       Filename:  descriptor_tables.h
 *
 *    Description:  GDT的定义
 *
 *        Version:  1.0
 *        Created:  2013年10月14日 16时31分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * ==================================================================================
 */



#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H



#include "common.h"

/*
 *GDT :全局描述符表，一个段描述符表占8个字节，64位。
 */

/*
 *      --------------------------
 *      P   DPL DT   TYPE (0--3)
 *
 *      --------------------------
 *      G   D    0  A   segment length 
 *      其中； 
 *      P :段是否存在内存中，p=0 ,表示不在内存中，p=1 在内存中
 *      DPL ：特权级别 
 *      DT：描述类型
 *      type :描述符类型 segment type - code segment /data segment 
 *      G :段界限粒度 ，G= 0  1byte , G= 1  lKbyte
 *      D :D= 0 , 16位地址， D=1 32 位地址
 *      0 : 一直是0 
 *      A ：能否被系统已经访问
 *
 *
 */



struct gdt_entry_struct
{
	u16int   limit_low;   //段限长的低15位  (0~ 15)
	u16int   base_low ;   //段基址的低15位  (0~15)
	u8int    base_middle ;  //基址的中间8位(16~24)
	u8int    access ; //段的描述， 其中包括（段是否在内存中，特权，类型 以及段的可读可写）
        u8int    granularity; // 其中包括(粒度， 32位/16位，0，是否被系统已经访问，段界限  )
	u8int    base_high ; //基地址的高8位地址 （24~32）
}__attribute__ ((packed));

//__attribute__ ((packed))告诉GCC 取消编译器过程中的优化对齐
//packed : 这个属性可以使得变量或者结构体成员使用最小的对齐方式
//详细：http://blog.csdn.net/ithomer/article/details/6566739

typedef struct gdt_entry_struct  gdt_entry_t ;


/*
 *
 * 段描述结构体表的定义
 */
struct gdt_ptr_struct 
{
	u16int limit ;  //段描述符的大小-第一个gdt_first_struct后的大小（偏移）
	u32int base ;  //段基址  (第一个gdt_first_struct 的地址)
} __attribute__ ((packed));

typedef struct gdt_ptr_struct   gdt_ptr_t ;
void init_gdt() ;
void gdt_flush (u32int) ;








#endif
