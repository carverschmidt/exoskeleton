/*
 * motorTimer.c
 *
 *  Created on: Feb 15, 2023
 *      Author: Chris
 */
#include "motorTimer.h"
#include "main.h"

/*
 * Function to select and set the motor's velocity
 * Motor 1: Right Ankle <---we can change these
 * Motor 2: Right Knee
 * Motor 3: Right Hip
 * Motor 4: Left Ankle
 * Motor 5: Left Knee
 * Motor 6: Left Hip
 *
 * Param:
 * uint8_t motor: selected motor
 * uint8_t dir: Boolean, 0 for forwards, 1 for backwards
 * uint8_t speed: percentage of total speed to run, 0-100
 *
 * Return:
 * none
 *
 *
 */
void setMotorVel(int motor, _Bool dir, float speed)
{
	float arr = COUNTARR;
	int vel = (float)speed/100 * arr;

	switch(motor){
		case 1:
			M1PWMTIM->M1PWMCH = vel;
			HAL_GPIO_WritePin(M1DIR_GPIO_Port, M1DIR_Pin, dir);
			break;
		case 2:
			M2PWMTIM->M2PWMCH = vel;
			HAL_GPIO_WritePin(M2DIR_GPIO_Port, M2DIR_Pin, dir);
			break;
		case 3:
			M3PWMTIM->M3PWMCH = vel;
			HAL_GPIO_WritePin(M3DIR_GPIO_Port, M3DIR_Pin, dir);
			break;
		case 4:
			M4PWMTIM->M4PWMCH = vel;
			HAL_GPIO_WritePin(M4DIR_GPIO_Port, M4DIR_Pin, dir);
			break;
		case 5:
			M5PWMTIM->M5PWMCH = vel;
			//HAL_GPIO_WritePin(M5DIR_GPIO_Port, M5DIR_Pin, 1);
			break;
		case 6:
			M6PWMTIM->M6PWMCH = vel;
			//HAL_GPIO_WritePin(M6DIR_GPIO_Port, M6DIR_Pin, 1);
			break;
	}
}

/*
 * Function to get the motor's set velocity
 *
 * Param:
 * uint8_t motor: selected motor
 * uint8_t dir: Boolean, 0 for forwards, 1 for backwards
 * uint8_t speed: percentage of total speed to run
 *
 * Return:
 * uint8_t vel
 *
 */
int getMotorVel(int motor)
{
	return 1;
}
