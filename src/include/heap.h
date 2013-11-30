/*
 * =====================================================================================
 *
 *       Filename:  heap.h
 *
 *    Description:  堆的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月23日 17时32分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef HEAP_H 
#define HEAP_H

#include "common.h"

#define HEAP_START   0xD0000000  //堆的开始位置
#define HEAP_END     0xFF000000  //堆的结束位置(栈的开始位置)








/*
 * 一个块能使用的x - sizeof (header_t)
 */
typedef struct header
{
	struct header *prev , *next ;
	u32int   allocated :1 ;  //是否已经被分配，如果分配了就是1，没有分配是0
	u32int   length  :31; 
}header_t ;

/*
 * 寻找适合当前我们所有分配的合适值
 * 如果没有发现可用的块:
 * (1)扩大堆 
 * (2)如果当前还没记录可用的数据块信息,就创建一个新的数据块
 * (3)调整最后一个头的长度大小
 *
 * 在把块分成两部分的时候，首先要考虑如果按这中方法进行了，所剩下的数据块是否能满足我们的条件。
 */

void init_heap () ;
void *kmalloc (u32int  len ) ;
void  kfree (void *p);
void alloc_chunk (u32int start , u32int len);
void split_chunk (header_t *chunk , u32int len);
void glue_chunk (header_t *chunk);
void free_chunk(header_t *chunk);







#endif
