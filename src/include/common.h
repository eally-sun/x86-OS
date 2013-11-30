/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  读写端口的头文件函数
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 21时53分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef COMMON_H
#define COMMON_H


typedef unsigned int   u32int ;
typedef          int   s32int ;
typedef unsigned short u16int ;
typedef          short s16int ;
typedef unsigned char  u8int  ;
typedef          char  s8int  ;


void   outb (u16int , u8int value);
u8int  inb (u16int port );
u16int inw (u16int port);
void   osti () ; 
void   ccli () ; 
#endif 

