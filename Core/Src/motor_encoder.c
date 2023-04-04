/*
 * motor_encoder.c
 *
 *  Created on: Mar 7, 2023
 *      Author: Chris
 */


#include "main.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

const uint8_t encoderMap_87654321[256] = {
  0xFF,0x48,0x58,0x57,0x68,0xFF,0x67,0x64,0x78,0x79,0xFF,0xFF,0x77,0xFF,0x74,0x4D,
  0x08,0xFF,0x09,0xFF,0xFF,0xFF,0xFF,0x63,0x07,0x06,0xFF,0xFF,0x04,0x05,0x5D,0x62,
  0x18,0x49,0xFF,0x56,0x19,0x1A,0xFF,0xFF,0xFF,0x4A,0xFF,0x4B,0xFF,0xFF,0x73,0x4C,
  0x17,0xFF,0x16,0xFF,0xFF,0xFF,0xFF,0xFF,0x14,0xFF,0x15,0xFF,0x6D,0x6E,0x72,0x61,
  0x28,0xFF,0x59,0xFF,0xFF,0xFF,0x66,0x65,0x29,0x7A,0x2A,0xFF,0xFF,0xFF,0xFF,0x4E,
  0xFF,0xFF,0x5A,0xFF,0xFF,0xFF,0x5B,0xFF,0xFF,0x7B,0xFF,0xFF,0x03,0xFF,0x5C,0x4F,
  0x27,0xFF,0xFF,0xFF,0x26,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0x24,0x23,0xFF,0xFF,0x25,0xFF,0xFF,0xFF,0x7D,0x7C,0x7E,0xFF,0x02,0x6F,0x71,0x70,
  0x38,0x47,0xFF,0x54,0x69,0xFF,0xFF,0x3D,0xFF,0xFF,0xFF,0x53,0x76,0xFF,0x75,0x52,
  0x39,0x46,0x0A,0xFF,0x3A,0x3B,0xFF,0x3C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x5E,0x51,
  0xFF,0xFF,0xFF,0x55,0x6A,0xFF,0xFF,0x3E,0xFF,0xFF,0xFF,0xFF,0x6B,0xFF,0xFF,0x3F,
  0xFF,0xFF,0x0B,0xFF,0xFF,0xFF,0xFF,0xFF,0x13,0xFF,0xFF,0xFF,0x6C,0xFF,0x5F,0x60,
  0x37,0x44,0xFF,0x2D,0xFF,0x43,0xFF,0x42,0x36,0xFF,0x2B,0x2C,0xFF,0xFF,0xFF,0x41,
  0xFF,0x45,0xFF,0x2E,0xFF,0xFF,0xFF,0x2F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x50,
  0x34,0x1D,0x33,0x32,0xFF,0x1C,0xFF,0x31,0x35,0x1E,0xFF,0x1F,0xFF,0xFF,0xFF,0x40,
  0x0D,0x22,0x0C,0x21,0x0E,0x0F,0xFF,0x30,0x12,0x11,0x7F,0x20,0x01,0x10,0x00,0xFF };

/*
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

void motor_enc_set_up(void)
//read message from i2c device
uint8_t motor_enc_read(void)
{
	HAL_I2C_Master_Receive(&hi2c1, ENC1ADD, (uint8_t *)i2cMsg, 1, 10);
}
&*/

uint8_t MCP23008_ReadRegs(void)
{
	uint8_t buf;
	uint8_t msg[100]; //buffer for UART message
	int msgSize;		//variable for UART message size in bytes

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_IODIR, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "IODIR: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_IPOL, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "IPOL: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_GPINTEN, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "GPINTEN: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_DEFVAL, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "DEFVAL: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_INTCON, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "INTCON: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_GPPU, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "GPPU: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_INTF, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "INTF: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_INTCAP, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "INTCAP: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_GPIO, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "GPIO: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2

	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), MCP_OLAT, 1, &buf, 1, 10) != HAL_OK)
		return 1;
	msgSize = sprintf((char *)msg, "OLAT: %u\r\n", buf); //store message in msg buffer
	HAL_UART_Transmit(&huart2, msg, msgSize, 10); //Send UART message to UART2
	return 0;
}
/* Function to write to MCP23008 register
 * Param: reg: register of MCP23008 to write to
 * 		  val: value to write to register
 * Return: 0 if write successful
 * 		   1 if write fails
 */
uint8_t MCP23008_Write8(uint8_t reg, uint8_t val)
{
	if(HAL_I2C_Mem_Write(&hi2c1, (ENC1ADD << 1), reg, 1, &val, 1, 10) != HAL_OK)
		return 1;
	return 0;
}

/*
 * Function to read from MCP23008 register
 * Param: reg: register of MCP23008 to read from
 * 		  val: value to store register value in
 * Return: 0 if write successful
 * 		   1 if write fails
 */
uint8_t MCP23008_Read8(uint8_t reg, uint8_t * val)
{
	if(HAL_I2C_Mem_Read(&hi2c1, (ENC1ADD << 1), reg, 1, val, 1, 10) != HAL_OK)
		return 1;
	return 0;
}
