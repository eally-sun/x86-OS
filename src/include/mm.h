/*
 * =====================================================================================
 *
 *       Filename:  mm.h
 *
 *    Description:  内存管理
 *
 *        Version:  1.0
 *        Created:  2013年10月21日 17时18分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef MM_H
#define MM_H

#include "common.h"
#include "multiboot.h"
#include "isr.h"




#define PAGE_PRESENT   0x1    //是否在内存中
#define PAGE_WRITE     0x2    //页可读可写 
#define PAGE_USER      0x4    //和高速缓存有关系,允许特权级别0,1访问，只能读
#define PAGE_MASK      0xFFFFF000  //页表的20位基地址的处理

#define PAGE_DIR_VIRTUAL_ADDR     0xffbff000  //虚拟页目录地址
#define PAGE_TABLE_VIRTUAL_ADDR   0xffc00000  //虚拟页表地址
#define PMM_STACK_ADDR 0xff000000

/*是在页目录和页表中的索引，对于页目录是直接除1024 ，是因为每个的页表的索引是从高向低排列，在开机的时候，基本上都已经建立了页目录和也表的对应关系*/
#define PAGE_DIR_IDX(x)   ((u32int)x/1024)
//页表中对应的物理页会不端的变化，映射关系也会改变，所以就要在这里面不断的寻找空闲页表
#define PAGE_TABLE_IDX(x) ((u32int)x%1024)

/*
 *页目录是一个数组，并且数组的元素是无符号数,页目录的高20位是页表的物理基地址，剩下的低12位是与权限有关系，其中包括的字段有
 *P , PW , US , PWT , PCD , A , D , PAT , G AVL .
 *页表是的高20位是页物理地址 ， 剩下的低12位与页目录相同.
 *
 */
typedef u32int  page_directory_t  ; 
extern char     mm_paging_active  ; 






void init_pmm (struct multiboot_t  *mboot_ptr);
void init_page_pmm (multiboot_t  *mbbot_ptr);
u32int pmm_alloc_page () ;
void   pmm_free_page (u32int p) ;
void   switch_page_directory (page_directory_t *pd);
void   map (u32int va , u32int pa , u32int flags);
void   unmap (u32int va);
int    get_mapping (u32int va , u32int *pa);
void   init_vmm () ;
void   page_fault (registers_t  *regs) ;




#endif

