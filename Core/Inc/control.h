/*
 * control.h
 *
 *  Created on: Apr 4, 2023
 *      Author: Chris
 */

#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

void control_init();

void control_run();

void balance(uint8_t encPos, uint8_t threshLow, uint8_t threshHigh, int motor);

int check_balanced();

#endif /* INC_CONTROL_H_ */
