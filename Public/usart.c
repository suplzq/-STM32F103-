#include "usart.h"		 


/*******************************************************************************
* �� �� ��         : USART1_Init
* ��������		   : USART1��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/
u8 USART_RX_BUF1[USART_REC_LEN],USART_RX_BUF2[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA1=0,USART_RX_STA2=0; 

void USART1_Init(u32 bound)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //�������PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ��ʼ����������IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //��������PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* ��ʼ��GPIO */
	

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����	
}

void USART2_Init(u32 bound)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	
//	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE); 				//USART2������ӳ��
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//TX			   //�������PA2
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ��ʼ����������IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//RX			 //��������PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* ��ʼ��GPIO */

		/*  ����GPIO��ģʽ��IO�� */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;//TX			   //�������PD5
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
//	GPIO_Init(GPIOD,&GPIO_InitStructure);  /* ��ʼ����������IO */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;//RX			 //��������PD6
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
//	GPIO_Init(GPIOD,&GPIO_InitStructure); /* ��ʼ��GPIO */

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����	
}

/*******************************************************************************
* �� �� ��         : USART1_IRQHandler
* ��������		   : USART1�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/ 
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//����жϱ�־λ
		
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		if((USART_RX_STA1&0x8000)==0)//����δ���
		{
			if(USART_RX_STA1&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART_RX_STA1=0;//���մ���,���¿�ʼ
				else USART_RX_STA1|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART_RX_STA1|=0x4000;
				else
			 { 
					USART_RX_BUF1[USART_RX_STA1&0X3FFF]=Res ;
					USART_RX_STA1++;
				  if(USART_RX_STA1>(USART_REC_LEN-1))USART_RX_STA1=0;//�������ݴ���,���¿�ʼ����	  
			 }		 
			}
		}  
	} 
	
} 	

void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);	//����жϱ�־λ
		
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		if((USART_RX_STA2&0x8000)==0)//����δ���
		{
			if(USART_RX_STA2&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART_RX_STA2=0;//���մ���,���¿�ʼ
				else 
				{
					USART_RX_STA2|=0x8000;
					USART_RX_BUF2[USART_RX_STA2&0X3FFF]=0x20;//  �����������һ���ÿո�
				}	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART_RX_STA2|=0x4000;
				else
				{
					USART_RX_BUF2[USART_RX_STA2&0X3FFF]=Res;
					USART_RX_STA2++;
					if(USART_RX_STA2>(USART_REC_LEN-1))USART_RX_STA2=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}  
	} 
	
	
} 	


 



