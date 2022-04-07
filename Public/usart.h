#ifndef __usart_H
#define __usart_H

#include "system.h" 
//#include "color.h"

#define USART_REC_LEN 200

extern u8  USART_RX_BUF1[USART_REC_LEN];
extern u8  USART_RX_BUF2[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA1,USART_RX_STA2; 

void USART1_Init(u32 bound);
void USART2_Init(u32 bound);


#endif


