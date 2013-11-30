/*
 * =====================================================================================
 *
 *       Filename:  printk.c
 *
 *    Description:  printf 函数的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月18日 11时16分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef PRINTK_H 
#define PRINTK_H

#include "montior.h"



typedef char*   va_list ;
#define _INTSIZEOF(n)   ((sizeof (n) + sizeof (int)-1 ) & ~(sizeof (int) -1 ))
#define va_start(ap,v)  (ap = (va_list)&v + _INTSIZEOF (v))
#define va_arg(ap,t)   (*(t*)((ap += _INTSIZEOF (t)) -_INTSIZEOF (t) ))
#define va_end(ap)     ( ap = (va_list)0 )


int vsprintfa (va_list , va_list);
int printk (va_list format ,...);


#endif

