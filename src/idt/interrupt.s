;
;中断处理
;
;
;
;定义中断处理函数的宏 
;没有错误代码的中断
%macro ISR_NOERRCODE 1 
 [GLOBAL isr%1] 
 isr%1:
     cli
     push byte 0  ;占位
     push byte %1
     jmp isr_common_stub
%endmacro

;用于有错误代码的中断
%macro ISR_ERROR 1 
[GLOBAL isr%1]
isr%1:
       cli 
   
       push %1
       jmp isr_common_stub
%endmacro

;irq处理
%macro IRQ    2
global irq%1
irq%1:
cli 
push 0 
push %2 
jmp irq_common_stub
%endmacro



;定义中断处理函数
ISR_NOERRCODE    0   
ISR_NOERRCODE    1
ISR_NOERRCODE    2
ISR_NOERRCODE    3
ISR_NOERRCODE    4
ISR_NOERRCODE    5
ISR_NOERRCODE    6
ISR_NOERRCODE    7
ISR_ERROR        8
ISR_NOERRCODE    9
ISR_ERROR        10
ISR_ERROR        11
ISR_ERROR        12
ISR_ERROR        13
ISR_ERROR        14
ISR_NOERRCODE    15
ISR_NOERRCODE    16
ISR_NOERRCODE    17
ISR_NOERRCODE    18
ISR_NOERRCODE    19

;intel 保留
ISR_NOERRCODE    20
ISR_NOERRCODE    21
ISR_NOERRCODE    22
ISR_NOERRCODE    23
ISR_NOERRCODE    24
ISR_NOERRCODE    25
ISR_NOERRCODE    26
ISR_NOERRCODE    27
ISR_NOERRCODE    28
ISR_NOERRCODE    29
ISR_NOERRCODE    30
ISR_NOERRCODE    31

IRQ      0    ,  32   ;系统计时器
IRQ      1    ,  33   ;键盘
IRQ      2    ,  34   ;与IRQ9相连
IRQ      3    ,  35   ;串口设备
IRQ      4    ,  36   ;串口设备
IRQ      5    ,  37   ;声卡
IRQ      6    ,  38   ;软驱传输控制用
IRQ      7    ,  39   ;打印机传输控制用
IRQ      8    ,  40   ;IRC时钟
IRQ      9    ,  41   ;与IRQ2相连
IRQ      10   ,  42   ;网卡
IRQ      11   ,  43   ;显卡
IRQ      12   ,  44   ;ps/2 鼠标
IRQ      13   ,  45   ;协处理器
IRQ      14   ,  46   ;IDE0 传输控制用
IRQ      15   ,  47   ;IDE1 传输控制用

;用户自定义
ISR_NOERRCODE    255 

[GLOBAL isr_common_stub]
[EXTERN  isr_handler]

isr_common_stub:
    pusha    ; 将通用寄存器压入栈 

    mov  ax , ds   
    push eax           ;保留数据段描述符

    mov ax  ,0x10      
    mov ds  ,ax  
    mov es  ,ax
    mov fs  ,ax 
    mov gs  ,ax
    mov ss  ,ax

    push esp
    call isr_handler 
    add  esp , 4 

    pop  eax 
    mov  ds  ,ax 
    mov  es  ,ax
    mov  fs  ,ax 
    mov  gs  ,ax
    mov  ss  ,ax

    popa
    add  esp , 8 
    sti 
    iret

[GLOBAL irq_common_stub]
[extern irq_handler]
irq_common_stub:
pusha 
mov   ax , ds
push  eax 

mov  ax , 0x10 
mov  ds , ax 
mov  es , ax
mov  gs , ax
mov  fs , ax 
mov  ss , ax 

push esp 
call irq_handler 
add  esp , 4

pop ebx 
mov ds , bx
mov es , bx
mov fs , bx
mov gs , bx 
mov ss , bx 

popa 
add esp , 8 
sti
iret


































































