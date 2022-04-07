#ifndef _MOTOR_H
#define _MOTOR_H

#include "system.h"

#define PWMA   TIM8->CCR4 //д��ռ�ձȼĴ���
#define PWMB   TIM8->CCR3 
#define PWMC   TIM8->CCR2
#define PWMD   TIM8->CCR1  

#define Set_MotorPWMA(x)	TIM_SetCompare3(TIM8, x);
#define INB1   PBout(4)  
#define INB2   PBout(5)  

#define Set_MotorPWMB(x)	TIM_SetCompare4(TIM8, x);
#define INA2   PDout(2)  
#define INA1   PCout(12) 

#define Set_MotorPWMC(x)	TIM_SetCompare1(TIM8, x);
#define IND1   PBout(0)  
#define IND2   PBout(1) 

#define Set_MotorPWMD(x)	TIM_SetCompare2(TIM8, x);
#define INC2   PCout(5)  
#define INC1   PCout(4)  

#define EN     PAin(12)  

void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
#endif
