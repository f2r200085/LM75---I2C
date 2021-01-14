/*
 * Author: KK_Toomuch
 * Data: 2021/01/14
 * Features: The LM75A uses the on-chip band gap sensor to measure the device temperature with
 *           the resolution of 0.125 °C and stores the 11-bit 2's complement digital data.
 * Note: Currently, only temperatures above 0 C are supported, and negative temperatures are not supported.
 * Update: First version.
 */
#include <stdio.h>
#include <wiringPi.h>
#include "LM75.h"
#include "IIC.h"


int main (void) {

	/*Init*/
	raspberry_gpio_init();
	IIC_Init();

	/*Setting LM75*/
	Set_All_Pointer_Register(Conf_register, 80.0, 75.0);	//Configuration, Overtemperature, Hysteresis

	/*Get LM75 All Information*/
	Get_All_Information();


	return 0 ;
}