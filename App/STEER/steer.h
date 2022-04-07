#ifndef _steer_h
#define _steer_h

#include "system.h"

extern int steerA,steerB,steerC,steerD,steerE;
/*  STEER时钟端口、引脚定义 */
#define STEER_PORT 			GPIOC   
#define STEER_PIN 			(GPIO_Pin_0|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define STEER_PORT_RCC		RCC_APB2Periph_GPIOC

void STEER_Init(void);
void TIM7_Steer_Init(void);
void Steer_SET(int steer, int DutyCycle);

#endif
