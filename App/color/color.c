#include "color.h"

char AT[]="AT\r\n";
char AT_LIGHT[]="AT+LIGHT+ON\r\n";
char AT_LIGHT2[]="AT+LIGHT+OFF\r\n";
char AT_COLOR[]="AT+COLOR\r\n";
char RED[]=" RED\r\n";
char GREEN[]=" GREEN\r\n";
char BLUE[]=" BLUE\r\n";

int red, green, blue;

void Color_Init(void)
{
	int temp;
	do
	{
		USART2_Puts(AT);
		temp++;
		delay_ms(100);
	}while((USART_RX_BUF2[0]!=0x4F)&&(temp<5));
}

void USART1_Puts(char *str)
{
    while(*str)
    {
        USART_SendData(USART1,*str++);
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
    }
}

void USART2_Puts(char *str)
{
    while(*str)
    {
        USART_SendData(USART2,*str++);
        while(USART_GetFlagStatus(USART2,USART_FLAG_TC) != SET);
    }
			
}

void USART2_COLOR_DATA_SEND(void)   
{
	int len,t;
	if(USART_RX_STA2&0x8000)
		{		
			USART_ClearFlag(USART1,USART_FLAG_TC);
			len=USART_RX_STA2&0x3fff;//得到此次接收到的数据长度
			
			str_to_num(USART_RX_BUF2,10,&red,&green,&blue);
			
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF2[t]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);//等待发送结束
			}
			
			if(red > green)  //判断RGB哪个值最大 并输出颜色
			{
				if(red > blue)
				{
					USART1_Puts(RED);
				}
				else
				{
					USART1_Puts(BLUE);
				}
			}
			else
			{
				if(green > blue)
				{
					USART1_Puts(GREEN);
				}
				else
				{
					USART1_Puts(BLUE);
				}
			}
			

			USART_SendData(USART1,0x0D);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
			USART_SendData(USART1,0x0A);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
			
			USART_ClearFlag(USART1,USART_FLAG_TC);
			USART_RX_STA2=0;
		}
}

void str_to_num(u8 *str,int n,int *red,int *green,int *blue)
{
	if (str[n+1]!=0x20)
	{
		if(str[n+2]!=0x20)
		{
			*red = (str[n]-0x30)*100+(str[n+1]-0x30)*10+(str[n+2]-0x30);
			n+=6;
		}
		else
		{
			*red = (str[n]-0x30)*10+(str[n+1]-0x30);
			n+=5;
		}
	}
	else
	{
		*red = (str[n]-0x30);
		n+=4;
	}
	
	if (str[n+1]!=0x20)
	{
		if(str[n+2]!=0x20)
		{
			*green = (str[n]-0x30)*100+(str[n+1]-0x30)*10+(str[n+2]-0x30);
			n+=6;
		}
		else
		{
			*green  = (str[n]-0x30)*10+(str[n+1]-0x30);
			n+=5;
		}
	}
	else
	{
		*green  = (str[n]-0x30);
		n+=4;
	}
	
	if (str[n+1]!=0x20)
	{
		if(str[n+2]!=0x20)
		{
			*blue = (str[n]-0x30)*100+(str[n+1]-0x30)*10+(str[n+2]-0x30);
		}
		else
		{
			*blue  = (str[n]-0x30)*10+(str[n+1]-0x30);
		}
	}
	else
	{
		*blue  = (str[n]-0x30);
	}
}
