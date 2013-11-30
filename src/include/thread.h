/*
 * =====================================================================================
 *
 *       Filename:  thread.h
 *
 *    Description:  内核线程的实现
 *
 *        Version:  1.0
 *        Created:  2013年11月25日 16时37分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef THREAD_H
#define THREAD_H

#include "common.h"

#define STACK_SIZE 8196


typedef enum task_state
{
	TASK_UNINIT   = 0,//未初始化
	TASK_SLEEPING = 1,//睡眠中
	TASK_RUNNABLE = 2,//可运行
	TASK_ZOMBIE = 3 , //僵死状态
}Task_State;

//内核保存线程的上下文切换信息
typedef struct context
{
	u32int   esp;
	u32int   ebp;
	u32int   ebx;
	u32int   esi;
	u32int   edi;
        u32int   eflags; 

}context_t ;


struct task_struct 
{
	volatile              Task_State  state ; //进程当前的状态
	u32int                pid  ; //进程的表示符
        void                  *stack ; //进程的内核栈地址
        context_t             context ; //进程切换需要上下文信息
        struct task_struct    *next ; //链表指针  
};


extern   u32int      now_pid ;

u32int create_thread ( u32int  (*fn)(void *), void *arg) ;

void thread_exit ();


#endif
