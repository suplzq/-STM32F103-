#include "control.h"

long int Target_A = 6, Target_B = 6, Target_C = 6, Target_D = 6;	//���Ŀ��ֵ
float Velocity_KP = 10, Velocity_KI = 10;		//�ٶȿ���PID����
long int Motor_A, Motor_B, Motor_C, Motor_D;		//���PWM����
int Encoder_A, Encoder_B, Encoder_C, Encoder_D;		//���������������
float Vx,Vy,Vz;
int send,i=0;

int move_number=0,move_distance=0,move_direction=0; //1ǰ�� 2���� 3���� 4���� 5����ת
int temp_X,temp_Y,temp_Z;
int STOP=0,Route;

int move_dis[99]={ 1, 0, 1, 2, 0, 3, 3, 1, 0, 1, 3, 4, 0, 1, 0, 1, 3, 5, 0, 3, 1, 0, 0};  //��ǰ����ִ�и��� �������ƶ���Ҫ��һ
int move_dir[99]={ 1, 0, 3, 1, 0, 3, 5, 1, 0, 2, 5, 1, 0, 4, 0, 2, 5, 1, 0, 5, 4, 0, 0};  //1ǰ�� 2���� 3���� 4���� 5����ת
int move_dix[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0};    //��һ��������ٶ�
int move_diy[99]={ 5, 0, 0, 5, 0, 0, 0, 5, 0,-5, 0, 5, 0, 0, 0,-5, 0, 5, 0, 0, 0, 0, 0};
int move_diz[99]={ 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0};
int stop[99]=    { 0,99, 0, 0,99, 0, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0, 0,99, 0, 0, 3, 0};  //ÿ�γ���1ǰ������һ��99���˲���

//int move_dis[99]={ 1, 0, 1, 2, 0, 3, 3, 1, 0, 1, 3, 4, 0, 1, 0, 1, 3, 5, 0, 3, 1, 0, 0};  //��ǰ����ִ�и��� �������ƶ���Ҫ��һ
//int move_dir[99]={ 1, 0, 3, 1, 0, 3, 5, 1, 0, 2, 5, 1, 0, 4, 0, 2, 5, 1, 0, 5, 4, 0, 0};  //1ǰ�� 2���� 3���� 4���� 5����ת
//int move_dix[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0};    //��һ��������ٶ�
//int move_diy[99]={ 5, 0, 0, 5, 0, 0, 0, 5, 0,-5, 0, 5, 0, 0, 0,-5, 0, 5, 0, 0, 0, 0, 0};
//int move_diz[99]={ 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0};
//int stop[99]=    { 0,99, 0, 0,99, 0, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0, 0,99, 0, 0, 3, 0};  //ÿ�γ���1ǰ������һ��99���˲���

int move_dis2[99]={ 1, 0, 1, 2, 0, 3, 3, 0, 1, 3, 4, 0, 1, 0, 1, 3, 0, 4, 0, 5, 1, 0, 3, 0, 0};  //��ǰ����ִ�и���
int move_dir2[99]={ 1, 0, 3, 1, 0, 3, 5, 0, 2, 5, 1, 0, 3, 0, 2, 5, 0, 1, 0, 3, 1, 0, 5, 0, 0};  //1ǰ�� 2���� 3���� 4���� 5����ת
int move_dix2[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0};    //��һ��������ٶ�
int move_diy2[99]={ 5, 0, 0, 5, 0, 0, 0, 0,-5, 0, 5, 0, 0, 0,-5, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0};
int move_diz2[99]={ 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0};
int stop2[99]=    { 0,99, 0, 0,99, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0,98, 0,99, 0, 0,99, 0, 4, 0};  //ÿ�γ���1ǰ������һ��99���˲���

int move_dis3[99]={ 1, 0, 1, 2, 0, 3, 3, 0, 1, 3, 4, 0, 5, 0, 1, 3, 0, 4, 0, 9, 1, 0, 3, 0, 0};  //��ǰ����ִ�и���
int move_dir3[99]={ 1, 0, 3, 1, 0, 3, 5, 0, 2, 5, 1, 0, 3, 0, 2, 5, 0, 1, 0, 3, 1, 0, 5, 0, 0};  //1ǰ�� 2���� 3���� 4���� 5����ת
int move_dix3[99]={ 0, 0,-5, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0, 0,-5, 0, 0, 0, 0, 0};    //��һ��������ٶ�
int move_diy3[99]={ 5, 0, 0, 5, 0, 0, 0, 0,-5, 0, 5, 0, 0, 0,-5, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0};
int move_diz3[99]={ 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0};
int stop3[99]=    { 0,99, 0, 0,99, 0, 0, 1, 0, 0, 0,99, 0, 2, 0, 0,98, 0,99, 0, 0,99, 0, 5, 0};  //ÿ�γ���1ǰ������һ��99���˲���

#define a_PARAMETER          (0.311f)               
#define b_PARAMETER          (0.3075f)         
/**************************************************************************
�������ܣ�С���˶���ѧģ��
��ڲ�����X Y Z �����ٶȻ���λ��
����  ֵ����
**************************************************************************/
void Kinematic_Analysis(void)
{
	Target_A   = -Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
	Target_B   = +Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
	Target_C   = -Vx+Vy-Vz*(a_PARAMETER+b_PARAMETER);
	Target_D   = +Vx+Vy+Vz*(a_PARAMETER+b_PARAMETER);
}
/**************************************************************************
�������ܣ�С����������+Ѱ��
��ڲ�����X Y Z �����ٶȻ���λ��
����  ֵ����
**************************************************************************/
void TIM6_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
	 {
			 TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
					 
//			 i++;
//			 if(i>200)//1s��һ��
//			 {
//				 i=0;
//				 send=1;
//			 }
//			 
			 	Encoder_A	=	-Read_Encoder(2);                                          //===��ȡ��������ֵ
				Encoder_B	=	Read_Encoder(3);                                          //===��ȡ��������ֵ
				Encoder_C	=	Read_Encoder(4);                                         //===��ȡ��������ֵ
				Encoder_D	=	-Read_Encoder(5);                                       //===��ȡ��������ֵ
			 
				temp_X=Vx;
				temp_Y=Vy;
				temp_Z=Vz;
				
				if(temp_Y>0)
				{
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0 ){Vx-=0.8;Vz+=1.5;}	//ֱ������	
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) == 0 ){Vx+=0.8;Vz-=1.5;}
				}
				if(temp_X>0)
				{	
					if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1 )&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0)&&(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==1))
					{Vy-=0.5;}	//��������	
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
					{Vy-=0.5;}	//��������	
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
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) == 0 ){Vx+=2;Vz+=1.3;}	//��������	
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0 ){Vx-=2;Vz-=1.3;}
				}
				
				Kinematic_Analysis(); //ת�ٽ���
				 
				Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         //===�ٶȱջ����Ƽ�����A����PWM
				Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         //===�ٶȱջ����Ƽ�����B����PWM
				Motor_C=Incremental_PI_C(Encoder_C,Target_C);                         //===�ٶȱջ����Ƽ�����C����PWM
				Motor_D=Incremental_PI_D(Encoder_D,Target_D);                         //===�ٶȱջ����Ƽ�����C����PWM
				
				Xianfu_Pwm(6900);                     //===PWM�޷�
				Set_Pwm(Motor_A,Motor_B,Motor_C,Motor_D);     //===��ֵ��PWM�Ĵ���  
				
				Vx=temp_X;//�������λ
				Vy=temp_Y;
				Vz=temp_Z;
			}
}
/**************************************************************************
�ⲿ�жϼƲ���
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
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_D (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)	Pwm=7200;
	 if(Pwm<-7200)	Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
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
�������ܣ�����PWM��ֵ 
��ڲ�������ֵ
����  ֵ����
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
�������ܣ�����ֵ����
��ڲ�����long int
����  ֵ��unsigned int
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


