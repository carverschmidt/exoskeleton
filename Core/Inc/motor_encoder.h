/*
 * motor_encoder.h
 *
 *  Created on: Mar 7, 2023
 *      Author: Chris
 */


#ifndef INC_MOTOR_ENCODER_H_
#define INC_MOTOR_ENCODER_H_

#define ENC1ADD 0x20 //one we are testing
#define ENC2ADD 0x21 //knee joint
#define ENC3ADD 0x22
#define ENC4ADD 0x23
#define ENC5ADD 0x24
#define ENC6ADD 0x25

//void motor_enc_set_up(void);

//uint8_t motor_enc_read(void);
uint8_t enc_read_pos(uint8_t enc_num);


#endif /* INC_MOTOR_ENCODER_H_ */
