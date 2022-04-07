#include "system.h"
int jkl=1;
int main()
{	

	SysTick_Init(72);//延时时钟初始

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//优先级分组1
		
	STEER_Init();//舵机
	TIM7_Steer_Init();//舵机20ms 180° 占空比5%——12.5%| PC0 PC13 PC14 PC15 |
	
	USART1_Init(9600);	//串口输出PA9|串口输入PA10 上位机
	USART2_Init(9600);  //串口输出PA2|串口输入PA3  颜色识别TCS230
	
	MiniBalance_PWM_Init(7199,0);	//=====电机驱动，设置PWM周期TIM8电机驱动| PB4 PB5 | PD2 PC12 | PB0 PB1 | PC5 PC4 |(正反转控制口AIN1 AIN2)
	Encoder_Init_TIM2();//编码器模式
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	Encoder_Init_TIM5();
	TIM6_5ms_Init();//读编码器

	EXTI1_Init();//PC1 光电开关计步
	EXTI2_Init();//PC2
	EXTI3_Init();//PC3
	EXTI4_Init();//PA4	
	Key_GPIOC_Config();//光电开关初始
	Key_GPIOA_Config();
	
//	OLED_Init();//=====OLED初始化
	delay_ms(3000);//
	TIM_Cmd(TIM7,DISABLE);
	
	Route=1;
	move_set();

	while(1)
	{	
//		static int time=0;
//			TIM_Cmd(TIM7,ENABLE); //使能定时器
//			Steer_SET(1, 60);
//			Steer_SET(1, 90);
//			Steer_SET(2, 75);
//			Steer_SET(3, 125);
//			Steer_SET(4, 75);
//			Steer_SET(4, 110);
			
//			Steer_SET(4, 75);

		if(STOP==1)
		{	
			Vy=5;
			delay_ms(800);
			Vy=0;
			
//			TIM_Cmd(TIM7,ENABLE); //使能定时器
		
//			Steer_SET(1, 90);
//			delay_ms(1000);
//			
//			Steer_SET(4, 75);
//			Steer_SET(2, 75);
//			Steer_SET(3, 125);
//			Steer_SET(1, 60);
//			delay_ms(2000);
//			Steer_SET(3, 75);
			

			move_set();
		}
		if(STOP==2)
		{	
			Vy=5;
			delay_ms(1000);
			Vy=0;
			delay_ms(1000);

			TIM_Cmd(TIM7,ENABLE); //使能定时器
		
			Steer_SET(2, 100);
			Steer_SET(2, 75);
			Steer_SET(2, 125);
			Steer_SET(2, 75);

//			TIM_Cmd(TIM7,DISABLE); 
			
//			move_number=0;
//			Route = 2;
			move_set();
		}
		if(STOP==3)
		{	
			Vx=5;
			delay_ms(1000);
			Vx=0;
			Vy=-5;
			delay_ms(1000);
			Vy=0;
			delay_ms(1000);
			
			move_number=0;
			Route = 2;
			move_set();
		}
		
		if(STOP==4)
		{	
			Vx=5;
			delay_ms(1000);
			Vx=0;
			Vy=-5;
			delay_ms(1000);
			Vy=0;
			delay_ms(1000);
			
			move_number=0;
			Route = 3;
			move_set();
		}
		
		if(STOP==5)
		{	
			Vx=5;
			delay_ms(1000);
			Vx=0;
			Vy=-5;
			delay_ms(1000);
			Vy=0;
			delay_ms(1000);
			
//			move_number=0;
//			Route = 3;
			move_set();
		}
		
		if(STOP==99)
		{	
			Vy=-5;
			delay_ms(200);
			move_set();
		}
		
		if(STOP==98)
		{	
			Vz=-5;
			delay_ms(250);
			move_set();
		}
		if(STOP==97)
		{	
			Vz=5;
			delay_ms(250);
			move_set();
		}
	}
}

