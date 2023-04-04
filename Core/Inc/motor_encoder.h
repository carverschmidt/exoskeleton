/*
 * motor_encoder.h
 *
 *  Created on: Mar 7, 2023
 *      Author: Chris
 */


#ifndef INC_MOTOR_ENCODER_H_
#define INC_MOTOR_ENCODER_H_



#define MCP_IODIR	0x00		/* init/reset:  all ones */
#define MCP_IPOL	0x01
#define MCP_GPINTEN	0x02
#define MCP_DEFVAL	0x03
#define MCP_INTCON	0x04
#define MCP_IOCON	0x05
#define MCP_GPPU	0x06
#define MCP_INTF	0x07
#define MCP_INTCAP	0x08
#define MCP_GPIO	0x09
#define MCP_OLAT	0x0a

#define ENC1ADD 0x20 //addresses for I2C encoder devices
#define ENC2ADD 0x21
#define ENC3ADD 0x22
#define ENC4ADD 0x23
#define ENC5ADD 0x24
#define ENC6ADD 0x25

//void motor_enc_set_up(void);

//uint8_t motor_enc_read(void);
uint8_t MCP23008_Write8(uint8_t reg, uint8_t val);
uint8_t MCP23008_Read8(uint8_t reg, uint8_t *val);
uint8_t MCP23008_ReadRegs(void);

#endif /* INC_MOTOR_ENCODER_H_ */
