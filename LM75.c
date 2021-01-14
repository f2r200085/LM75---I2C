#define __LM75_C__

#include "LM75.h"
#include "IIC.h"
#include <stdio.h>
#include <stdlib.h>


void write_1byte(unsigned char data1){
	IIC_Start();
	IIC_Write(I2C_ADDRESS|Write);
	IIC_Write(data1);
	IIC_Stop();
}

void write_2byte(unsigned char data1, unsigned char data2){
	IIC_Start();
	IIC_Write(I2C_ADDRESS|Write);
	IIC_Write(data1);
	IIC_Write(data2);
	IIC_Stop();
}

void write_3byte(unsigned char data1, unsigned char data2, unsigned char data3){
	IIC_Start();
	IIC_Write(I2C_ADDRESS|Write);
	IIC_Write(data1);
	IIC_Write(data2);
	IIC_Write(data3);
	IIC_Stop();
}

unsigned char *get_1byte(void){
	static unsigned char data[1];
	IIC_Start();
	IIC_Write(I2C_ADDRESS|Read);
	data[0]= IIC_Read();
	IIC_Stop();
	return data;
}

unsigned char *get_2byte(void){
	static unsigned char data[2];
	IIC_Start();
	IIC_Write(I2C_ADDRESS|Read);
	data[0] = IIC_Read();
	data[1] = IIC_Read();
	IIC_Stop();
	return data;
}

void Get_Temperature(void){
	unsigned char *t_data;
	write_1byte(Temp);
	t_data = malloc( 2 * sizeof(unsigned char) );
	t_data = get_2byte();
	printf("Temp = %03.3fC\n", (float)(((t_data[0] << 8) | t_data[1]) >> 5)*0.125 );
}

void Get_Configuration(void){
	unsigned char *t_data;
	write_1byte(Conf);
	t_data = malloc( 1 * sizeof(unsigned char) );
	t_data = get_1byte();
	printf("Conﬁguration = 0x%02X\n", t_data[0]);
}

void Get_Hysteresis(void){
	unsigned char *t_data;
	write_1byte(Thyst);
	t_data = malloc( 2 * sizeof(unsigned char) );
	t_data = get_2byte();
	printf("Hysteresis = %03.1fC\n", (float)(((t_data[0] << 8) | t_data[1]) >> 7)*0.5 );
}

void Get_Overtemperature_Shutdown_Threshold(void){
	unsigned char *t_data;
	write_1byte(Tos);
	t_data = malloc( 2 * sizeof(unsigned char) );
	t_data = get_2byte();
	printf("Overtemperature Shutdown Threshold = %03.1fC\n", (float)(((t_data[0] << 8) | t_data[1]) >> 7)*0.5 );
}

void Get_All_Information(void){
	Get_Temperature();
	Get_Configuration();
	Get_Overtemperature_Shutdown_Threshold();
	Get_Hysteresis();
}

void Set_Configuration(unsigned char data){
	data = data & 0x1F;		//B[7:5] reserved, reserved for manufacturer’s use; should be kept as zeroes for normal operation
	write_2byte(Conf, data);
}

void Set_Hysteresis(float f_input){
	unsigned char MSB, LSB;
	f_input = f_input/0.5;
	MSB = (((unsigned short)f_input & 0x1ff) >> 1);
	LSB = (((unsigned short)f_input & 0x001));
	write_3byte(Thyst, MSB, LSB);
}

void Set_Overtemperature_Shutdown_Threshold(float f_input){
	unsigned char MSB, LSB;
	f_input = f_input/0.5;
	MSB = (((unsigned short)f_input & 0x1ff) >> 1);
	LSB = (((unsigned short)f_input & 0x001));
	write_3byte(Tos, MSB, LSB);
}

void Set_All_Pointer_Register(unsigned char h_conf, float f_tos, float f_thyst){	//Configuration, Overtemperature,  Hysteresis
	Set_Configuration(h_conf);
	Set_Overtemperature_Shutdown_Threshold(f_tos);
	Set_Hysteresis(f_thyst);
}