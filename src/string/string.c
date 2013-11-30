/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  字符串处理函数
 *
 *        Version:  1.0
 *        Created:  2013年10月16日 08时48分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */



#include "string.h"

inline void memcpy(u8int *dest, const u8int *src, u32int len)
{
	for (; len != 0; len--) {
			*dest++ = *src++;
		}
}

inline void memset(u8int *dest, u8int val, u32int len)
{
	for ( ; len != 0; len--) {
			*dest++ = val;
		}
}

inline int strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && (*str1++ == *str2++))
	      ;

	if (*str1 == '\0' && *str2 == '\0') {
		      return 0;
		}

	if (*str1 == '\0') {
		      return -1;
		}
	
	return 1;
}

inline char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while (*src) {
		      *dest++ = *src++;
		}

	*dest = '\0';
	
	return tmp;
}

inline char *strcat(char *dest, const char *src)
{
	char *cp = dest;

	while (*cp) {
		      cp++;
		}

	while ((*cp++ = *src++))
	      ;

	return dest;
}

inline int strlen(const char *src)
{
	const char *eos = src;

        while(*eos++)
	      ;
	        
	return (eos - src - 1);
}


