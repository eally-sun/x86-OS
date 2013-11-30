/*
 * =====================================================================================
 *
 *       Filename:  schedule.c
 *
 *    Description:  内核态线程调度
 *
 *        Version:  1.0
 *        Created:  2013年11月25日 18时59分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "schedule.h"
#include "heap.h"


struct task_struct  *running_proc_head = 0 ;
struct task_struct  *wait_proc_head = 0 ;
struct task_struct  *current = 0 ; 


int kern_stack_top ;
void schedule () 
{
	if (current)
	{
		change_task_to (current->next);
	}

}
void init_schedule ()
{
	//为当前执行流创建信息结构体，该结构体位于当前执行流的最低端
	current = (struct task_struct *)kmalloc (sizeof (struct task_struct));
	current->state = TASK_RUNNABLE ;
	current->pid = now_pid ++ ;
	current->stack = current ; 

	current->next = current ; 
	running_proc_head = current ;
}

void change_task_to (struct task_struct *next)
{
	if (current != next)
	{
		struct task_struct  *prev = current ;
		current = next ;
		switch_to (&(prev->context), &(current->context));
	}
}

void switch_to (struct context *prev , struct context *next)
{
	asm volatile ("mov %%esp , %0": "=r"(prev->esp));
	asm volatile ("mov %%ebp , %0": "=r"(prev->ebp));
	asm volatile ("mov %%ebx , %0": "=r"(prev->ebx));
	asm volatile ("mov %%esi , %0": "=r"(prev->esi));
	asm volatile ("mov %%edi , %0": "=r"(prev->edi));
	//asm volatile ("pusha");

	asm volatile ("mov %0, %%edi":: "r" (next->edi));
	asm volatile ("mov %0, %%esi":: "r" (next->esi));
	asm volatile ("mov %0, %%ebx":: "r" (next->ebx));
	asm volatile ("mov %0, %%esp":: "r" (next->esp));
	asm volatile ("mov %0, %%ebp":: "r" (next->ebp));
	//asm volatile ("popa");

}
