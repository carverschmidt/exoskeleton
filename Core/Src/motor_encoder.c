/*
 * motor_encoder.c
 *
 *  Created on: Mar 7, 2023
 *      Author: Chris
 */

#include "motor_encoder.h"
#include "main.h"

I2C_HandleTypeDef hi2c1;

void motor_enc_set_up(void)
{
	//start up sequence of MCP23008
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0xFF, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0xFF, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
	HAL_I2C_Master_Transmit(&hi2c1, ENC1ADD, (uint8_t)0x00, 1, 10); //i2c messages
}

//read message from i2c device
uint8_t motor_enc_read(void)
{
	HAL_I2C_Master_Receive(&hi2c1, ENC1ADD, (uint8_t *)i2cMsg, 1, 10);
}
