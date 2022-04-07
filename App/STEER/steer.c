#include "steer.h"

int temp=0;
int steerA=75,steerB=75,steerC=70,steerD=70,steerE=75;//25-125

void STEER_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����	

	RCC_APB2PeriphClockCmd(STEER_PORT_RCC,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=STEER_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������	
	GPIO_Init(STEER_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;  //ѡ����Ҫ���õ�IO��
//	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
//	GPIO_SetBits(STEER_PORT,STEER_PIN);   //��STEER�˿�����	
//	GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1);
}

void TIM7_Steer_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseStructure.TIM_Period = 2-1;  //50000hz �ж�
	TIM_TimeBaseStructure.TIM_Prescaler = 720-1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIM7,ENABLE);//ʹ��Ԥװ�ؼĴ���
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);          //������ж�λ ��ʹ���ж�
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM7,ENABLE); //ʹ�ܶ�ʱ�� �ȶ�
}

void TIM7_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
	 {
		 temp++;
		 if(temp>steerA) PCout(0)=0; //���ݶ��IO ��
		 if(temp>steerB) PCout(13)=0;
		 if(temp>steerC) PCout(14)=0;
		 if(temp>steerD) PCout(15)=0;
		 //if(temp>steerE) PAout(4)=0;
		 if(temp>999) 
		 {
			 PCout(0)=1;
			 PCout(13)=1;
			 PCout(14)=1;
			 PCout(15)=1;
			 //PAout(4)=1;
			 temp=0; 
		 }
	 } 		 
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update); 
}

void Steer_SET(int steer, int DutyCycle)
{
	switch (steer)
	{
		case 1: 
			if (steerA > DutyCycle)
			{
				do
				{
					steerA--;
					delay_ms(50);
				}while(steerA > DutyCycle);
			}
			else
			{
				do
				{
					steerA++;
					delay_ms(50);
				}while(steerA < DutyCycle);
			}
			break;
		case 2: 
			if (steerB > DutyCycle)
			{
				do
				{
					steerB--;
					delay_ms(50);
				}while(steerB > DutyCycle);
			}
			else
			{
				do
				{
					steerB++;
					delay_ms(50);
				}while(steerB < DutyCycle);
			}
			break;
		case 3: 
			if (steerC > DutyCycle)
			{
				do
				{
					steerC--;
					delay_ms(50);
				}while(steerC > DutyCycle);
			}
			else
			{
				do
				{
					steerC++;
					delay_ms(50);
				}while(steerC< DutyCycle);
			}
			break;
		case 4: 
			if (steerD > DutyCycle)
			{
				do
				{
					steerD--;
					delay_ms(50);
				}while(steerD > DutyCycle);
			}
			else
			{
				do
				{
					steerD++;
					delay_ms(50);
				}while(steerD < DutyCycle);
			}
		break;
			
		default: break;		
	}
}
	
