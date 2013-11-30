/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  堆的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月23日 18时09分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "heap.h"
#include "mm.h"
#include "printk.h"

u32int  heap_max = HEAP_START ;
header_t *heap_first =  0 ;

void *kmalloc (u32int len )
{
//	printk ("hello kmalloc \n");
	len +=sizeof (header_t);

	header_t *cur_header = heap_first ;
	header_t *prev_header = 0  ;
	//printk ("header_t%d\n", sizeof (header_t));

	while (cur_header)
	{
		if (cur_header->allocated == 0 && cur_header->length>=len){
			//将一个块分成两部分，一部分是我们需要的，节省内存
			split_chunk (cur_header, len);
			cur_header->allocated  = 1 ;
			return (void*)((u32int)cur_header +sizeof (header_t));
		}
		prev_header = cur_header ;
		cur_header = cur_header->next ;
	}
	/*如果没有找到比我们所需要的块要大的数据块，就要扩充堆的大小*/
	u32int chunk_start ;
	
	//扩充堆链
        if (prev_header)
	{
		chunk_start = (u32int)prev_header + prev_header->length;
	}
	//如果当前堆链是空的。
	else 
	{
		printk ("hello  yes \n");
		chunk_start = HEAP_START ;
		heap_first = (header_t*)chunk_start ;
	}
	printk ("chunk_start address 0x%x\n", chunk_start);
	alloc_chunk (chunk_start , len) ;

	cur_header = (header_t *)chunk_start ;
	cur_header->prev = prev_header ;
	cur_header->next = 0 ;
	cur_header->allocated = 1 ;
	cur_header->length =len ;
        if (prev_header){
	prev_header->next = cur_header ;
	}
	return (void*) (chunk_start + sizeof (header_t));
}

void kfree (void *p)
{
	header_t *header = (header_t *) ((u32int)p - sizeof (header_t));
	header->allocated = 0 ;

	glue_chunk (header);
}

void alloc_chunk (u32int start , u32int len)
{
	//没有空闲的页,就要重新映射
	while (start + len > heap_max)
	{
		u32int page = pmm_alloc_page () ;
		map (heap_max , page , PAGE_PRESENT |PAGE_WRITE);
		//printk ("")
		heap_max += 0x1000 ;
	}
}
void split_chunk (header_t *chunk , u32int len)
{
	if (chunk->length - len > sizeof (header_t))
	{
		header_t *newchunk = (header_t *) ((u32int)chunk + chunk->length);
		newchunk->prev = chunk ;
		newchunk->next = 0  ;
		newchunk->allocated = 0 ;
		newchunk->length = chunk->length - len ;
		chunk->next = newchunk ;
		chunk->length = len ;
	}
}
void glue_chunk (header_t *chunk)
{
	//向右合并
	if (chunk->next && chunk->next->allocated == 0)
	{
		chunk->length = chunk->length + chunk->next->length ;
		chunk->next->prev = chunk ;
		chunk->next = chunk->next->next ;

	}
	//向左合并
	
	if (chunk->prev && chunk->prev->allocated == 0)
	{
		chunk->prev->length = chunk->prev->length + chunk->length ;
		chunk->prev->next = chunk->next ;
		chunk->next->prev = chunk->prev ;
		chunk = chunk->prev ;
	}
	
	if (chunk->next == 0 )
	{
		free_chunk (chunk);

	}

}
void free_chunk (header_t *chunk )
{
	chunk->prev->next  = 0 ;
	if (chunk->prev == 0)
	{
		heap_first =  0 ;
	}
	while ((heap_max - 0x1000) >= (u32int)chunk)
	{
		heap_max -=0x1000 ;
	
	u32int page ;
	get_mapping (heap_max , &page) ;
	pmm_free_page (page);
	unmap (heap_max);
	}
}
