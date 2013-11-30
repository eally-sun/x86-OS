/*
 * =====================================================================================
 *
 *       Filename:  montior.h
 *
 *    Description:  从屏幕上显示字符和数字
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 22时21分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */


#ifndef  MONTIOR_H
#define  MONTIOR_H

#include "common.h"


void monitor_put (char c );
void monitor_clear ();
void monitor_write (char *c);
void move_cursor () ;
void scroll () ;
void monitor_write_dec (u32int n);
void monitor_write_hex (u32int n);


#endif 

