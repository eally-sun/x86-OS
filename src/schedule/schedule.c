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

//运行的对列
struct task_struct  *running_proc_head = 0 ;
//处于等待的队列
struct task_struct  *wait_proc_head = 0 ;

//当前的进程
struct task_struct  *current = 0 ; 

int kern_stack_top ;

//内核线程的调度，结合时钟中断加以处理
void schedule () 
{
	if (current)
	{
		change_task_to (current->next);
	}

}
//初始化调度
//由于自己是一个算法渣，目前采取了最简单的实现就是一个循环链表
void init_schedule ()
{
	
	current = (struct task_struct *)kmalloc (sizeof (struct task_struct));
	current->state = TASK_RUNNABLE ;
	current->pid = now_pid ++ ;
	current->stack = current ; 
        //循环链表
	current->next = current ; 
	running_proc_head = current ;
}
//在任务切换前的准备工作
void change_task_to (struct task_struct *next)
{
	if (current != next)
	{
		struct task_struct  *prev = current ;
		current = next ;
		switch_to (&(prev->context), &(current->context));
	}
}

//线程切换
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
