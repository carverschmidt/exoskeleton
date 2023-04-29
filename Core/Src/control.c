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
	/*
	uint32_t tib_an_l = 0; //left tib
	uint32_t vas_lat_l = 0; //left vas

	uint32_t tib_an_r = 0; //right tib
	uint32_t vas_lat_r = 0; //right vas
	*/

	uint8_t encPos[6]; //array for encoder positions
	//uint8_t encStartPos[] = {80, 0, 0, 0, 0, 0}; //array for encoder positions
	//uint8_t encStandPos[] = {80, 0, 0, 0, 0, 0}; //array for encoder positions
	int8_t enc_start_pos[] = {93, 116}; //array for encoder positions. MOTOR 1 IS RIGHT KNEE, MOTOR 2 IS RIGHT HIP
	int8_t enc_stand_pos[] = {111, 116}; //array for encoder positions.
	int8_t enc_final_pos[] = {6, 85}; //array for encoder positions
	int8_t pos_step[] = {0, 0};
	uint32_t emg[4];  //array for EMG values for DMA to store values in

	uint8_t msg[100]; //buffer for UART message
	uint8_t num_steps = 5;
	int msgSize;		//variable for UART message size in bytes

	HAL_ADC_Start_DMA(&hadc1, emg, 4); //start DMA to update EMG values

	//move motors to initial conditions

	while(!check_balanced()){
		for(int i = 0; i < 2; i ++){
				encPos[i] = enc_read_pos(i+1);
				balance(encPos[i], enc_start_pos[i]-3, enc_start_pos[i]+3, i + 1);
		}
	}


	/*
	while(!motor_balanced[0])
	{
		encPos[0] = enc_read_pos(1); //read 1st joint
		balance(encPos[0], encStartPos[0]-5, encStartPos[0]+5, 1);
		msgSize = sprintf((char *)msg, "Encoder start: %u\r\n", encPos[0]); //store message in msg buffer
		HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2
		HAL_Delay(10);
	}
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
	/*
	//right calves
	while(emg[0] < 2100)
	{
		HAL_ADC_Start_DMA(&hadc1, emg, 4); //get DMA to update EMG values
		msgSize = sprintf((char *)msg, "ADC: %u\r\n", emg[0]); //store message in msg buffer
		HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2
		HAL_Delay(100);
	}
	*/
	//calculate angle to move by given a number of steps
	for(int i = 0; i < 2; i ++){
		if(enc_stand_pos[i] != enc_start_pos[i])
		{
			pos_step[i] = (enc_stand_pos[i] - enc_start_pos[i])/num_steps;
		}else{
			pos_step[i]=0;
		}
	}

	//move to standing position in steps
	for(int steps = 1; steps <= num_steps; steps++)
	{
		do{
			for(int i = 0; i < 2; i ++){
				encPos[i] = enc_read_pos(i+1);
				balance(encPos[i], (enc_start_pos[i] + pos_step[i] * steps) - 2, (enc_start_pos[i] + pos_step[i] * steps) + 2, i + 1);

				//if all motors are balanced, break
				if(check_balanced())
				{
					break;
				}
			}
		}while(!check_balanced());
		HAL_Delay(10);
	}

	HAL_Delay(5000);
	//rotate motor to move


	/*
	//right quads
	while(emg[1] < 2100 && emg[2] < 2100)
	{
		HAL_ADC_Start_DMA(&hadc1, emg, 4); //get DMA to update EMG values
		msgSize = sprintf((char *)msg, "ADC: %u\r\n", emg[0]); //store message in msg buffer
		HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2
		HAL_Delay(100);
	}
	*/
	//calculate angle to move by given a number of steps
	for(int i = 0; i < 2; i ++){
		if(enc_stand_pos[i] != enc_start_pos[i])
		{
			pos_step[i] = (enc_final_pos[i] - enc_stand_pos[i])/num_steps;
		}else{
			pos_step[i]=0;
		}
	}

	//move to standing position in steps
	for(int steps = 1; steps <= num_steps; steps++)
	{
		do{
			for(int i = 0; i < 2; i ++){
				encPos[i] = enc_read_pos(i+1);
				balance(encPos[i], (enc_stand_pos[i] + pos_step[i] * steps) - 2, (enc_stand_pos[i] + pos_step[i] * steps) + 2, i + 1);

				//if all motors are balanced, break
				if(check_balanced())
				{
					break;
				}
			}
		}while(!check_balanced());
		HAL_Delay(10);
	}

	HAL_Delay(5000);

	while(1)//stability loop, goes forever
	{
		for(int i = 0; i < 2; i ++){
			encPos[i] = enc_read_pos(i+1);
			balance(encPos[i], enc_final_pos[i] - 2, enc_final_pos[i] + 2, i + 1);
		}
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
			setMotorVel(motor, 1, 7);//move forward slowly
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
	for(int i = 0; i < 2; i ++)
	{
		if(motor_balanced[i] == 0){
			return 0;
		}
	}
	//return 1 if all motors are balanced
	return 1;
}




