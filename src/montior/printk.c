/*
 * =====================================================================================
 *
 *       Filename:  printk.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月23日 13时01分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */


#include "printk.h"

int printk (va_list format,... )
{
	  va_list   args = (va_list)0;
	  va_start (args , format) ;
	  vsprintfa (format , args);
	  va_end (args );
	  
	  return 0 ;
}

int   vsprintfa (va_list format ,va_list  args)
{
        char  c ;
     	do 
	{
			if (*format != '%')
			{
			    c = *format ;
			    format ++ ;
			    monitor_put (c);
			    continue ;
		        }
			
			switch (*++format)
			{
			    case 'd':
			    monitor_write_dec (*((int*)args));
			    va_arg(args, int);
			    break;
		            case 'x':
			    monitor_write_hex (*((int*)args));
			    va_arg(args , int );
			    break;
			    default :
			    break;
			 }
			format++ ;
			
	         }while (*format!='\0');

	return 0 ;
}

