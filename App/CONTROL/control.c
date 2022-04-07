#include "control.h"

long int Target_A = 6, Target_B = 6, Target_C = 6, Target_D = 6;	//电机目标值
float Velocity_KP = 10, Velocity_KI = 10;		//速度控制PID参数
long int Motor_A, Motor_B, Motor_C, Motor_D;		//电机PWM变量
int Encoder_A, Encoder_B, Encoder_C, Encoder_D;		//编码器的脉冲计数
float Vx,Vy,Vz;
int send,i=0;

int move_number=0,move_distance=0,move_direction=0; //1前进 2后退 3左移 4右移 5逆旋转
int temp_X,temp_Y,temp_Z;
int STOP=0,Route;

int move_dis[99]={ 1, 0, 1, 2, 0, 3, 3, 1, 0, 1, 3, 4, 0, 1, 0, 1, 3, 5, 0, 3, 1, 0, 0};  //当前所需执行格数 左移右移都需要减一
int move_dir[99]={ 1, 0, 3, 1, 0, 3, 5, 1, 0, 2, 5, 1, 0, 4, 0, 2, 5, 1, 0, 5, 4, 0, 0};  //1前进 2后退 3左移 4右移 5逆旋转
int move_dix[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0};    //下一步方向和速度
int move_diy[99]={ 5, 0, 0, 5, 0, 0, 0, 5, 0,-5, 0, 5, 0, 0, 0,-5, 0, 5, 0, 0, 0, 0, 0};
int move_diz[99]={ 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0};
int stop[99]=    { 0,99, 0, 0,99, 0, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0, 0,99, 0, 0, 3, 0};  //每次出现1前进，加一个99回退补偿

//int move_dis[99]={ 1, 0, 1, 2, 0, 3, 3, 1, 0, 1, 3, 4, 0, 1, 0, 1, 3, 5, 0, 3, 1, 0, 0};  //当前所需执行格数 左移右移都需要减一
//int move_dir[99]={ 1, 0, 3, 1, 0, 3, 5, 1, 0, 2, 5, 1, 0, 4, 0, 2, 5, 1, 0, 5, 4, 0, 0};  //1前进 2后退 3左移 4右移 5逆旋转
//int move_dix[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0};    //下一步方向和速度
//int move_diy[99]={ 5, 0, 0, 5, 0, 0, 0, 5, 0,-5, 0, 5, 0, 0, 0,-5, 0, 5, 0, 0, 0, 0, 0};
//int move_diz[99]={ 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0};
//int stop[99]=    { 0,99, 0, 0,99, 0, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0, 0,99, 0, 0, 3, 0};  //每次出现1前进，加一个99回退补偿

int move_dis2[99]={ 1, 0, 1, 2, 0, 3, 3, 0, 1, 3, 4, 0, 1, 0, 1, 3, 0, 4, 0, 5, 1, 0, 3, 0, 0};  //当前所需执行格数
int move_dir2[99]={ 1, 0, 3, 1, 0, 3, 5, 0, 2, 5, 1, 0, 3, 0, 2, 5, 0, 1, 0, 3, 1, 0, 5, 0, 0};  //1前进 2后退 3左移 4右移 5逆旋转
int move_dix2[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0};    //下一步方向和速度
int move_diy2[99]={ 5, 0, 0, 5, 0, 0, 0, 0,-5, 0, 5, 0, 0, 0,-5, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0};
int move_diz2[99]={ 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0};
int stop2[99]=    { 0,99, 0, 0,99, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0,98, 0,99, 0, 0,99, 0, 4, 0};  //每次出现1前进，加一个99回退补偿

int move_dis3[99]={ 1, 0, 1, 2, 0, 3, 3, 0, 1, 3, 4, 0, 5, 0, 1, 3, 0, 4, 0, 9, 1, 0, 3, 0, 0};  //当前所需执行格数
int move_dir3[99]={ 1, 0, 3, 1, 0, 3, 5, 0, 2, 5, 1, 0, 3, 0, 2, 5, 0, 1, 0, 3, 1, 0, 5, 0, 0};  //1前进 2后退 3左移 4右移 5逆旋转
int move_dix3[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0};    //下一步方向和速度
int move_diy3[99]={ 5, 0, 0, 5, 0, 0, 0, 0,-5, 0, 5, 0, 0, 0,-5, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0};
int move_diz3[99]={ 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0};
int stop3[99]=    { 0,99, 0, 0,99, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0,98, 0,99, 0, 0,99, 0, 5, 0};  //每次出现1前进，加一个99回退补偿

#define a_PARAMETER          (0.311f)               
#define b_PARAMETER          (0.3075f)         
/**************************************************************************
函数功能：小车运动数学模型
入口参数：X Y Z 三轴速度或者位置
返回  值：无
**************************************************************************/
void Kinematic_Analysis(void)
{
	Target_A   = -Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
	Target_B   = +Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
	Target_C   = -Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
	Target_D   = +Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
}
/**************************************************************************
函数功能：小车读编码器+寻迹
入口参数：X Y Z 三轴速度或者位置
返回  值：无
**************************************************************************/
void TIM6_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
	 {
			 TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
					 
//			 i++;
//			 if(i>200)//1s发一次
//			 {
//				 i=0;
//				 send=1;
//			 }
//			 
			 	Encoder_A	=	-Read_Encoder(2);                                          //===读取编码器的值
				Encoder_B	=	Read_Encoder(3);                                          //===读取编码器的值
				Encoder_C	=	Read_Encoder(4);                                         //===读取编码器的值
				Encoder_D	=	-Read_Encoder(5);                                       //===读取编码器的值
			 
				temp_X=Vx;
				temp_Y=Vy;
				temp_Z=Vz;
				
				if(temp_Y>0)
				{
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0 ){Vx-=0.8;Vz+=1.5;}	//直行修正	
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) == 0 ){Vx+=0.8;Vz-=1.5;}
				}
				if(temp_X>0)
				{	
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vy-=0.5;}	//右行修正	
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==0))
					{Vy+=0.5;}
//					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
//					{Vz-=1;Vy+=1;}
//					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
//					{Vz+=1;Vy-=1;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vy-=1;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==0))
					{Vy+=1;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==0))
					{Vz+=5;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vz-=5;}
				}
				if(temp_X<0)
				{	
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vy-=0.5;}	//左行修正	
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vy+=0.5;}
//					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
//					{Vz+=5;Vy+=4;}
//					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==0))
//					{Vz-=5;Vy-=4;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vy-=1;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==0))
					{Vy+=1;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==0))
					{Vz+=5;}
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 0 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vz-=5;}
				}
				if(temp_Y<0)
				{
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) == 0 ){Vx+=2;Vz+=1.3;}	//倒行修正	
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0 ){Vx-=2;Vz-=1.3;}
				}
				
				Kinematic_Analysis(); //转速解算
				 
				Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         //===速度闭环控制计算电机A最终PWM
				Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         //===速度闭环控制计算电机B最终PWM
				Motor_C=Incremental_PI_C(Encoder_C,Target_C);                         //===速度闭环控制计算电机C最终PWM
				Motor_D=Incremental_PI_D(Encoder_D,Target_D);                         //===速度闭环控制计算电机C最终PWM
				
				Xianfu_Pwm(6900);                     //===PWM限幅
				Set_Pwm(Motor_A,Motor_B,Motor_C,Motor_D);     //===赋值给PWM寄存器  
				
				Vx=temp_X;//修正后回位
				Vy=temp_Y;
				Vz=temp_Z;
			}
}
/**************************************************************************
外部中断计步器
**************************************************************************/
int EXTI1_IRQHandler(void) 
{    
	static int a=0;
	
	if(STOP==0)
	{
		if(move_direction==1)
		{
			a++;
			if(a>=move_distance)
			{
				a=0;
				move_set();
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
	return 0;	
}

int EXTI2_IRQHandler(void) 
{    
	static int a=0;
	if(STOP==0)
	{
		if(move_direction==2)
		{
			a++;
			if(a>=move_distance)
			{
				a=0;
				move_set();
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
	return 0;	
}
int EXTI3_IRQHandler(void) 
{    
	static int a=0;
	
		if(move_direction==3)
		{
			a++;
			if(a>=move_distance)
			{
				a=0;
				move_set();
			}
		}
		else if(move_direction==5)
		{
			a++;
			if(a>=move_distance)
			{
				a=0;
				move_set();
			}
		}
	
	EXTI_ClearITPendingBit(EXTI_Line3);
	return 0;	
}
int EXTI4_IRQHandler(void)   //PA4
{    
	static int a=0;
	
		if(move_direction==4)
			{
				a++;
				if(a>=move_distance)
				{
					a=0;
					move_set();
				}
			}
		
	EXTI_ClearITPendingBit(EXTI_Line4);
	return 0;	
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_D (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d)
{
	if(motor_a<0)		INA2=1,			INA1=0;
	else				INA2=0,			INA1=1;
	PWMA=myabs(motor_a);

	if(motor_b<0)		INB2=1,			INB1=0;
	else				INB2=0,			INB1=1;
	PWMB=myabs(motor_b);

	if(motor_c>0)		INC2=1,			INC1=0;
	else				INC2=0,			INC1=1;
	PWMC=myabs(motor_c);

	if(motor_d>0)		IND2=1,			IND1=0;
	else				IND2=0,			IND1=1;
	PWMD=myabs(motor_d);
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：幅值
返回  值：无
**************************************************************************/
void Xianfu_Pwm(int amplitude)
{	
	if(Motor_A<-amplitude) Motor_A=-amplitude;	
	if(Motor_A>amplitude)  Motor_A=amplitude;	
	if(Motor_B<-amplitude) Motor_B=-amplitude;	
	if(Motor_B>amplitude)  Motor_B=amplitude;		
	if(Motor_C<-amplitude) Motor_C=-amplitude;	
	if(Motor_C>amplitude)  Motor_C=amplitude;		
	if(Motor_D<-amplitude) Motor_D=-amplitude;	
	if(Motor_D>amplitude)  Motor_D=amplitude;		
}
	
/**************************************************************************
函数功能：绝对值函数
入口参数：long int
返回  值：unsigned int
**************************************************************************/
u32 myabs(long int a)
{ 		   
	u32 temp;
		if(a<0)  temp=-a;  
	else temp=a;
	return temp;
}

void move_set(void)
{
	if(Route==1)
	{
		move_direction= move_dir[move_number];
		move_distance = move_dis[move_number];
						 Vx   = move_dix[move_number];
						 Vy   = move_diy[move_number];
						 Vz   = move_diz[move_number];
						 STOP =     stop[move_number];
		
		move_number++;
	}
	if(Route==2)
	{
		move_direction= move_dir2[move_number];
		move_distance = move_dis2[move_number];
						 Vx   = move_dix2[move_number];
						 Vy   = move_diy2[move_number];
						 Vz   = move_diz2[move_number];
						 STOP =     stop2[move_number];
		move_number++;
	}
	if(Route==3)
	{
		move_direction= move_dir3[move_number];
		move_distance = move_dis3[move_number];
						 Vx   = move_dix3[move_number];
						 Vy   = move_diy3[move_number];
						 Vz   = move_diz3[move_number];
						 STOP =     stop3[move_number];
		move_number++;
	}
}


