/*
 * control.c
 *
 *  Created on: Apr 4, 2023
 *      Author: Chris
 */
/*
 * control.c
 *
 *  Created on: Apr 4, 2023
 *      Author: Chris
 */

#include <stdint.h>
#include "main.h"
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;
uint8_t motor_balanced[] = {0, 0, 0, 0, 0, 0};
void control_init()
{
}

//script for running two joints
void control_run()
{
	uint32_t tib_an_l = 0; //left tib
	uint32_t vas_lat_l = 0; //left vas

	uint32_t tib_an_r = 0; //right tib
	uint32_t vas_lat_r = 0; //right vas

	uint8_t encPos[6]; //array for encoder positions
	uint8_t encStartPos[] = {80, 0, 0, 0, 0, 0}; //array for encoder positions
	uint32_t emg[4];  //array for EMG values for DMA to store values in

	uint8_t msg[100]; //buffer for UART message
	int msgSize;		//variable for UART message size in bytes

	HAL_ADC_Start_DMA(&hadc1, emg, 4); //start DMA to update EMG values

	//move motors to initial conditions
	/*
	for(int i = 0; i < 6; i ++){
		encPos[i] = enc_read_pos(i);
		balance(encPos[i], encStartPos[i]-1, encStartPos[i]+1, i);

		//if all motors are balanced, break
		if(check_balanced())
		{
			break;
		}
	}
	*/

	while(!motor_balanced[0])
	{
		encPos[0] = enc_read_pos(1); //read 1st joint
		balance(encPos[0], encStartPos[0]-5, encStartPos[0]+5, 1);
		msgSize = sprintf((char *)msg, "Encoder start: %u\r\n", encPos[0]); //store message in msg buffer
		HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2
		HAL_Delay(10);
	}
	/*
	while(tib_an < 5325)//betwenn 1.5V to 5V
	{
		//take in EMG data for tib_an
		tib_an_l = *(emg) + *(emg + 1);
	}

	//Perform rotation on ankles and knees

	while((vas_lat < 5325) || (tib_an < 5325))
	{
		//take in EMG for both
		tib_an = *(emg) + *(emg + 1);
		vas_lat = *(emg + 2) + *(emg + 3);
	}
	*/

	while(emg[0] < 2100)
	{
		HAL_ADC_Start_DMA(&hadc1, emg, 4); //get DMA to update EMG values
		msgSize = sprintf((char *)msg, "ADC: %u\r\n", emg[0]); //store message in msg buffer
		HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2
		HAL_Delay(100);
	}


	while(1)//stability loop, goes forever
	{
		/*
		for(int i = 0; i < 6; i ++){
			encPos[i] = enc_read_pos(i);
			balance(encPos[i], 47, 53, i + 1);
		}
		*/
		encPos[0] = enc_read_pos(1); //read 1st joint
		balance(encPos[0], 25, 35, 1);
		msgSize = sprintf((char *)msg, "Encoder balancing: %u\r\n", encPos[0]); //store message in msg buffer
		HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2
		HAL_Delay(10);
	}
}

void balance(uint8_t encPos, uint8_t threshLow, uint8_t threshHigh, int motor)
{
	if(encPos > threshHigh)//smart reverse threshold works at 7%, will have to adjust
	{
		setMotorVel(motor, 1, 8);//move back slowly
		motor_balanced[motor - 1] = 0;
	}
	else
	{
		if(encPos < threshLow)
		{
			setMotorVel(motor, 1, 6.75);//move forward slowly
			motor_balanced[motor - 1] = 0;
		}
		else
		{
			setMotorVel(motor, 1, 7.5);//STOP MOTOR
			motor_balanced[motor - 1] = 1;
		}
	}
}

/*
 * Returns 0 if at least one motor is not done balancing
 */
int check_balanced(){
	for(int i = 0; i < 6; i ++)
	{
		if(motor_balanced[i] == 0){
			return 0;
		}
	}
	//return 1 if all motors are balanced
	return 1;
}



