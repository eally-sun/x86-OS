/*
 * =====================================================================================
 *
 *       Filename:  thread.c
 *
 *    Description:  内核线程的实现
 *
 *        Version:  1.0
 *        Created:  2013年11月25日 16时43分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "thread.h"
#include "heap.h"
#include "isr.h"
#include "string.h"
#include "schedule.h"
#include "printk.h"




u32int now_pid = 0 ;



u32int  create_thread (u32int (*fn) (void *), void *arg)
{
	

	struct task_struct *new_task = (struct task_struct *)kmalloc (STACK_SIZE);
	if (new_task == (u8int*)0 )
	{
	      printk ("new_task is null\n");
	      return -1 ;
	}

	memset (new_task , 0 , sizeof (struct task_struct));
	new_task->state = TASK_RUNNABLE ;
	new_task->stack = current ;
	new_task->pid = now_pid ++ ;

         u32int *stack = (u32int*) ((u32int)new_task + STACK_SIZE);

	//模拟函数调用的过程

	*(--stack) = (u32int)arg ; //参数
	*(--stack) = (u32int)&thread_exit;//返回值
	*(--stack) = (u32int)fn ; //函数
	//*(--stack) = 0 ; //push ebp  (占位)

	new_task->context.esp = (u32int)new_task + STACK_SIZE - sizeof (u32int)*4 ;

	new_task->context.eflags = 0x200 ;//打开中断0010, 0000, 0000
	new_task->next = running_proc_head ;
	
        
        struct task_struct *tail = running_proc_head ;
	while (tail->next != running_proc_head)
	{
		tail = tail->next ;
	}
        tail->next = new_task;

	return new_task->pid ;

}

void thread_exit ()
{
	register u32int val asm ("eax");
	printk ("thread  exited with value %d\n", val);
	while (1);
}
