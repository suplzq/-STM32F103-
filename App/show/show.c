#include "show.h"
#include "oled.h"
#include "system.h"
  /**************************************************************************
作者：墨比斯科技
我的淘宝小店：https://moebius.taobao.com/
**************************************************************************/

/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{			
		if(red > green)  //判断RGB哪个值最大 并输出颜色
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
		//=============刷新=======================//
		OLED_Refresh_Gram();	
}

