;boot.s --内核开始的地方
;Grub 可以直接识别elf文件格式


;寻找文件中关于操作系统的信息，文件中要包括:magic , flags ,checksum , header_addr , load_addr, load_end_addr 等字段
MBOOT_PAGE_ALIGN    equ 1<<0       ;以页对齐 (操作系统需要boot loader具有的特性) 
MBOOT_MEM_INFO      equ 1<<1       ;内存的信息
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ;魔数（用来表识多重引导头）

;MAGIC : 用来表识多重引导头,并且这个值是不能改变的。
;注意，我们没有使用MBOOT_AOUT_KLUDGE,GRUB 不会使用我们定义符号表

MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO   ; 多重引导头的开始地址，在那里寻找magic值的物理地址, 这个字段用来同步os image 偏移和物                                                             ; 理地址之间的映射
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


[BITS 32]                       ; 以下的所有说明都是以32字节为主的

section .text

[GLOBAL mboot]                  ; Make 'mboot' accessible from C (制作一个mboot ,采取C中内联汇编)

;多启动头(NASM语法)
mboot:
  dd  MBOOT_HEADER_MAGIC        ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file
  dd  MBOOT_HEADER_FLAGS        ; How GRUB should load your file / settings
  dd  MBOOT_CHECKSUM            ; To ensure that the above values are correct
   
[GLOBAL start]                  ; Kernel entry point.

[EXTERN main]                   ; This is the entry point of our C code

start:
  push    ebx                   ;将0x8放入ebx , 其中0x8是boot loader即是grub 提供的多重引导信息结构(struct multiboot_info)32位物理地址

                                ; Execute the kernel:
  cli                           ; Disable interrupts.（关闭中断，进入内核模块）
  mov esp, stack
  mov ebp, 0
  push ebx
  call main                     ; call our main() function.
  jmp $                         ; Enter an infinite loop, to stop the processor
                                ; executing whatever rubbish is in the memory
                                ; after our kernel!
.end:

section .bss
	resb 32768
stack:
        times  1024 db 0        ;分配stack 


