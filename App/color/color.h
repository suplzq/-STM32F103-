#ifndef _color_H
#define _color_H

#include "system.h"
#include "usart.h"
#include "SysTick.h"

extern char AT[];
extern char AT_LIGHT[];
extern char AT_LIGHT2[];
extern char AT_COLOR[];
extern int red, green, blue;
extern char RED[];
extern char GREEN[];
extern char BLUE[];

void Color_Init(void);
void USART1_Puts(char *str); //����һ����̶��ַ���
void USART2_Puts(char *str); //���ڶ�����̶��ַ���
void USART2_COLOR_DATA_SEND(void); //����ɫоƬ���ص���Ϣ���͵�PC
void str_to_num(u8 *str,int n,int *red,int *green,int *blue);  //��ȡRGB����ֵ����RGB����



#endif
