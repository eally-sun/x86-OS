/*
 * =====================================================================================
 *
 *       Filename:  montior.c
 *
 *    Description:  屏幕操作函数的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月08日 22时24分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "montior.h"
#define   SIZE  32

u16int      cursor_y  = 0 ;
u16int      cursor_x  = 0 ;
u16int     *video_memory  =  (u16int*)0xB8000;


/*
 * 光标在屏幕上的显示的位置，保存在显卡内部的两个光标寄存器中，每个寄存器是8位，合起来就是一个16位的数值。
 * 根据VGA文本模式是25行，80个字符。光标寄存器是可读可写的，你可以通过写入的数值来设定光标的位置。
 * 索引寄存器的端口号是0x3d4,可以向其中写入一个值，用来指定内部某个寄存器。
 */



/*重置光标的位置 ，
 * 思路：通过索引寄存器的端口号来指定寄存器0x0e和 0x0f ，提供光标位置的低8位和高8位
 * 然后通过数据段口（0x3d5）将数据写入
 *
 */
void move_cursor () 
{
	u16int cursorLocation = cursor_y * 80 + cursor_x ;
	outb (0x3D4 , 14 );  //通过索引端口，指定光标寄存器寄存器
	outb (0x3d5 , cursorLocation >> 8);  //通过数据段口来写入 （高8位）
	outb (0x3D4, 15) ;           //指定光标寄存器 
	outb (0x3D5 , cursorLocation ); //通过数据端口来写入 （低8位）


}

/*
 *滚动屏幕的内容（当光标的位置越界）
 */
void scroll () 
{
	u8int  attributeByte = ( 0 << 4 ) |(15 & 0x0F); //设置背景色为黑，前景色为白 
	u16int blank = 0x20  | (attributeByte << 8);     //空格的颜色用背景色填补

	if (cursor_y >= 25)
	{
		int   i ;
		for ( i = 0*80 ; i < 24*80 ; i++)
		{
			video_memory[i] = video_memory[i+80] ;  //把整个屏幕看成是一维数组，所用到的就是用下一行替换这一行。
		}
		//把最后一行用背景色来替换,重新填补上80个空白字符。
	        for ( i = 24*80 ; i < 25*80 ; i++)
		{
			video_memory[i] = blank ;
		}
		cursor_y = 24 ;

	}
}

void monitor_put (char c )
{
	u8int    backcolour = 0  ;//背景色
	u8int    forecolour = 15 ; //前景色
        
	//高4位是背景色，低4位是前景色
	u8int    attributeByte = (backcolour << 4  ) | (forecolour  & 0x0F);
	
	//attributeByte的高8位是字体的颜色 ，就是我们在显示屏上的颜色
	u16int   attribute = attributeByte << 8 ;

	u16int   *location ;

	//处理退格
	if ( c == 0x08  && cursor_x )
	{
                cursor_x-- ;
	}
	//处理tab,一个tab等于8个空格的长度
	else if  ( c== 0x09 )
	{
	 
                cursor_x = (cursor_x + 8) &~( 8 - 1 );  //保证一个tab可以移动8个空格
	}
	else if  (c == '\r') 
	{
		cursor_x = 0 ;
	}
	else if ( c== '\n' )
	{
		cursor_x = 0 ;
		cursor_y ++ ;
	}

	//处理能够打印的字符
	else if (c >= ' ')
	{
		location = video_memory + (cursor_y *80 + cursor_x);
		*location = c | attribute ; // 字符和字颜色属性
                cursor_x ++ ;
	}
	if (cursor_x >= 80)
	{
		cursor_x = 0 ;
		cursor_y ++ ;
	}
	//如果cursor_y >=25那么就要执行滚动
	scroll () ;
	move_cursor () ;
	

}

void monitor_clear () 
{
	u8int attributeByte = ( 0  <<4 ) | (15  & 0x0F);
	u16int blank = 0x20  | (attributeByte <<8) ;

	int  i ; 

	for  ( i = 0 ; i< 25*80 ; i++)
	{
		video_memory[i] = blank ;
	}

	cursor_x  = 0 ;
	cursor_y  = 0 ;
	move_cursor () ;
}

void monitor_write (char * c)
{
	int  i =  0 ;
	while (c[i])
	{
		monitor_put (c[i++]);
	}
}
void monitor_write_hex (u32int  n)
{
        int    temp ;
	int    flag  = 1;

    //    monitor_write ("0x");
	int   i ;
	
	for ( i = 28 ; i>=0 ; i-=4)
	{
                 temp = (n >> i) & 0xF ;

		 //第一次的0 是不用输出来的
		
	//	 flag = 0 ;
		 if (temp >=0xA)
		 {
			 monitor_put (temp-0xA +'a' );
		 }
		 else 
		 {
			 monitor_put (temp+'0');
		 }
	}


	


}
void monitor_write_dec(u32int n)
{
	if (n == 0) {
			monitor_write("0");
			return;
		}

	u32int acc = n;
	char c[32];
	int i = 0;
	while (acc > 0) {
			c[i] = '0' + acc % 10;
			acc /= 10;
			i++;
		}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;

	int j = 0;
	while(i >= 0) {
		      c2[i--] = c[j++];
		}

	monitor_write(c2);
}





