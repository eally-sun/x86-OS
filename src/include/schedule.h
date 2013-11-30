/*
 * =====================================================================================
 *
 *       Filename:  schedule.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月25日 21时58分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */


#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "common.h"
#include "thread.h"

//可调度进程链表
extern struct task_struct *running_proc_head ;

//等待进程链表
extern struct task_struct *wait_proc_head ;

//当前运行的任务
extern struct task_struct *current ;



//任务调度
void schedule () ;

//初始化任务调度
void init_schedule ();

//任务切换准备
void change_task_to (struct task_struct *next);

//任务切换
void switch_to (struct context *prev , struct context *next);



#endif
