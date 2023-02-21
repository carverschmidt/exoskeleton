/*
 * motorTimer.h
 *
 *  Created on: Feb 15, 2023
 *      Author: Chris
 */

#ifndef INC_MOTORTIMER_H_
#define INC_MOTORTIMER_H_

#include "stm32f4xx_hal.h"

#define COUNTARR 65535

#define M1PWMTIM TIM3
#define M1PWMCH CCR2

#define M2PWMTIM TIM4
#define M2PWMCH CCR1

#define M3PWMTIM TIM8
#define M3PWMCH CCR2

#define M4PWMTIM TIM2
#define M4PWMCH CCR3

#define M5PWMTIM TIM3
#define M5PWMCH CCR1

#define M6PWMTIM TIM2
#define M6PWMCH CCR2


void setMotorVel(int motor, _Bool dir, int speed);
int getMotorVel(int motor);



#endif /* INC_MOTORTIMER_H_ */
