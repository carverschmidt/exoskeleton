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
/*
void control_init()
{

}

void control_run(uint32_t *emg, uint8_t *encPos)
{
	uint32_t tib_an = 0;
	uint32_t vas_lat = 0;
	uint8_t encPos[6]; //array for encoder positions
	uint32_t emg[4];  //array for EMG values for DMA to store values in


	balance(*encPos, tbd, tbd, 1);
	balance(*(encPos+1), tbd, tbd, 2);
	balance(*(encPos+2), tbd, tbd, 3);
	balance(*(encPos+3), tbd, tbd, 4);
	balance(*(encPos+4), tbd, tbd, 5);
	balance(*(encPos+5), tbd, tbd, 6);
	//move motors to initial conditions


	while(tib_an < 5325)//betwenn 1.5V to 5V
	{
		//take in EMG data for tib_an
		tib_an = *(emg) + *(emg + 1);
	}

	//Perform rotation on ankles and knees

	while((vas_lat < 5325) || (tib_an < 5325))
	{
		//take in EMG for both
		tib_an = *(emg) + *(emg + 1);
		vas_lat = *(emg + 2) + *(emg + 3);
	}

	//Perform rotation on hips, ankles, knees

	while(1)//stability loop, goes forever
	{
		for(int i = 0; i < 6; i ++){
			encPos[i] = enc_read_pos(i);
			balance(encPos[i], tbd, tbd, i);
		}
	}
}

void balance(uint8_t encPos, uint8_t threshHi, uint8_t threshLow, int motor)
{
	if(((*encPos) > threshHi))//smart reverse threshold works at 7%, will have to adjust
	{
		setMotorVelocity(motor, 1, 6.75  );//move back slowly
	}
	else
	{
		if(((*encPos) < threshLow))
		{
			setMotorVelocity(motor, 1, 7.75);//move forward slowly
		}
		else
		{
			setMotorVelocity(motor, 1, 7.5);//STOP MOTOR
		}
	}
}

*/


