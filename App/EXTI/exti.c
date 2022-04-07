#include "exti.h"
  /**************************************************************************
���ߣ�ī��˹�Ƽ�
�ҵ��Ա�С�꣺https://moebius.taobao.com/
**************************************************************************/

/**************************************************************************
�������ܣ��ⲿ�жϳ�ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/

void EXTI1_Init(void)
{
	Ex_NVIC_Config(GPIO_C,1,FTIR);		//�½��ش���
	MY_NVIC_Init(2,0,EXTI1_IRQn,1);	//��ռ2�������ȼ�1����2
}
void EXTI2_Init(void)
{
	Ex_NVIC_Config(GPIO_C,2,FTIR);		//�½��ش���
	MY_NVIC_Init(2,0,EXTI2_IRQn,1);	//��ռ2�������ȼ�1����2
}
void EXTI3_Init(void)
{
	Ex_NVIC_Config(GPIO_C,3,FTIR);		//�½��ش���
	MY_NVIC_Init(2,0,EXTI3_IRQn,1);	//��ռ2�������ȼ�1����2
}
void EXTI4_Init(void)
{
	Ex_NVIC_Config(GPIO_A,4,FTIR);		//�½��ش���
	MY_NVIC_Init(2,0,EXTI4_IRQn,1);	//��ռ2�������ȼ�1����2
}


/**************************************************************************
��翪��
**************************************************************************/
void Key_GPIOC_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2| GPIO_Pin_3|GPIO_Pin_10 | GPIO_Pin_11; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void Key_GPIOA_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}




