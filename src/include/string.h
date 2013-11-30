/*
 * =====================================================================================
 *
 *       Filename:  string.h
 *
 *    Description:  字符串处理函数
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 19时20分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef  STRING_H
#define  STRINT_H
#include "common.h"

void memcpy (u8int *dest ,const u8int *src , u32int len );

void memset (u8int *dest , const u8int val , u32int len );

int strcmp(const char *str1, const char *str2);

char *strcpy(char *dest, const char *src);

char *strcat(char *dest, const char *src);

int strlen(const char *src);



#endif 
