#ifndef _control_h
#define _control_h

#include "system.h"

extern int send;
extern float Vx,Vy,Vz;
extern int STOP;
extern int move_number;
extern int Route;
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
int Incremental_PI_C (int Encoder,int Target);
int Incremental_PI_D (int Encoder,int Target);
void Xianfu_Pwm(int amplitude);
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d);
void Kinematic_Analysis(void);
void TIM6_IRQHandler(void);
u32 myabs(long int a);
void move_set(void);

#endif
