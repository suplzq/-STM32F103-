#include "show.h"
#include "oled.h"
#include "system.h"
  /**************************************************************************
���ߣ�ī��˹�Ƽ�
�ҵ��Ա�С�꣺https://moebius.taobao.com/
**************************************************************************/

/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void oled_show(void)
{			
		if(red > green)  //�ж�RGB�ĸ�ֵ��� �������ɫ
		{
			if(red > blue)
			{
				OLED_ShowString(0,0,(u8*)"Color:red");
			}
			else
			{
				OLED_ShowString(0,0,(u8*)"Color:blue");
			}
		}
		else
		{
			if(green > blue)
			{
				OLED_ShowString(0,0,(u8*)"Color:green");
			}
			else
			{
				OLED_ShowString(0,0,(u8*)"Color:blue");
			}
		}		
OLED_ShowString(0,0,(u8*)"Color:blue");
		//=============ˢ��=======================//
		OLED_Refresh_Gram();	
}

