/*
 * =====================================================================================
 *
 *       Filename:  multiboot.h
 *
 *    Description:  Multiboot 结构的定义
 *
 *        Version:  1.0
 *        Created:  2013年07月24日 20时08分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef INCLUDE_MULTIBOOT_H_
#define INCLUDE_MULTIBOOT_H_

/*multiboot 规范的背景*/

#include "common.h"

#define MULTIBOOT_FLAG_MEM     0x001
#define MULTIBOOT_FLAG_DEVICE  0x002
#define MULTIBOOT_FLAG_CMDLINE 0x004
#define MULTIBOOT_FLAG_MODS    0x008
#define MULTIBOOT_FLAG_AOUT    0x010
#define MULTIBOOT_FLAG_ELF     0x020
#define MULTIBOOT_FLAG_MMAP    0x040
#define MULTIBOOT_FLAG_CONFIG  0x080
#define MULTIBOOT_FLAG_LOADER  0x100
#define MULTIBOOT_FLAG_APM     0x200
#define MULTIBOOT_FLAG_VBE     0x400
/*
 *
 * grub向你的内核传递的信息：
 *（1）cs指向基地址为0x00000000, 线上是4G-1的代码描述符
 * (2) ds, ss , es , fs gs 指向基地址为0x00000000,线长为4G-1的数据段描述符
 * (3) A20地址线已经打开
 * (4) 页机制被禁止
 * (5) 中断被禁止
 * (6) EAX = 0x2badb002
 * (7) 系统信息和启动信息块的线性地址保存在EBX中 (相当与一个指针）
 * (8) CR0的第0位已经被设置了
 * (9) EFlags的第17位和第9位都要被清理
 * (10)esp 操作系统的镜像必须要创建属于自己的栈
 * (11)gdtr，可以不用加载，知道当你建立了属于自己的gdt表之后，就可以加载
 * (12) idtr 当你自己建立后，就可以设置
 * 在调用main 函数之前先将ebx的值压入堆栈，就可以用C语言来访问结构体中的相关信息了
 */

typedef struct multiboot_t {
	u32int flags ;   //版本的信息
	/*
	 *从bios可以知道内存的大小
         *
	 * mem_lower 指出了物理地址的低地址，mem_upper指出了物理地址的高地址
	 * mem_lower的首地址从0开始，而高地址内存的首地址是从1M开始。
	 * 低端内存的的最小值是640k ,高端地址的最大值可能性最大值减1M.
	 */
	u32int mem_lower; 
	u32int mem_upper;
	u32int boot_device;  //引导程序从那个bios磁盘设备载入的OS映像
	u32int cmdline;  //内核命令行
	u32int mods_count; //boot 模块列表
	u32int mods_addr;
       /**
	*elf格式额的内核映像的section头表，表项的大小,一共有几项作为名字索引的字符串表
	*他们对应于可执行可连接格式的program头中的shdr_*项，所有的section都会被载入，elf section头的物理地址域指向所有的section在内存中的位置
	*/

	
	u32int num;
	u32int size;
	u32int addr;
	u32int shndx;
	/*
        * 以下两项指出保存由BIOS提供的内存分布的缓冲区的地址和长度
	* mmap_addr是缓冲区的地址，mmap_length是缓冲区的总大小
   	* 缓冲区由一个或者多个下面的大小/结构对 mmap_entry_t（size实际上是用来跳过下一个对的）组成
        */
	u32int mmap_length;
	u32int mmap_addr;


	u32int drives_length;
	u32int drives_addr;
	u32int config_table;
	u32int boot_loader_name;
	u32int apm_table;
	u32int vbe_control_info;
	u32int vbe_mode_info;
	u32int vbe_mode;
	u32int vbe_interface_seg;
	u32int vbe_interface_off;
	u32int vbe_interface_len;
}__attribute__((packed))multiboot_t;


typedef struct mmap_entry_t 
{
	u32int  size ; //留意size是不含size自身变量的大小
        u32int  base_addr_low ; 
	u32int  base_addr_high ; //主要是为了64位的扩展 
	u32int  length_low ;
	u32int  length_high ;  //主要是对64位的扩展
	u32int  type ;
}__attribute__((packed))mmap_entry_t; 



#endif 	// INCLUDE_MULTIBOOT_H_
