#define __IIC_C__

#include <wiringPi.h>
#include <stdio.h>
#include "IIC.h"

void raspberry_gpio_init(void){
	if(wiringPiSetup()!=0){
		printf("Init Fail!\n");
	}else{
		printf("Init Pass!\n");
	}
}

void IIC_Init(void){
	set_output_SDA;
	set_output_SCL;
	SDA_H;
	SCL_H;
	delayMicroseconds(speed);
}

void IIC_Start(void){
	set_output_SDA;
	set_output_SCL;
	SDA_L;delayMicroseconds(speed);
	SCL_H;delayMicroseconds(speed);
	SCL_L;delayMicroseconds(speed);
}

void IIC_Stop(void){
	set_output_SDA;
	set_output_SCL;
	SDA_L;delayMicroseconds(speed);
	SCL_L;delayMicroseconds(speed);
	SCL_H;delayMicroseconds(speed);
	SDA_H;delayMicroseconds(speed);
	
}

void IIC_ACK_Master(void){
	unsigned char i;
	i=0;
	set_input_SDA;
	set_pull_down;
	while(SDA_R){
		if(i==3){break;}
		printf("Host no get acknowledge bit! Error!\n");
		delayMicroseconds(speed);
		++i;
	}
	SCL_H;delayMicroseconds(speed);
	SCL_L;delayMicroseconds(speed);
}

void IIC_ACK_Slave(void){
	set_output_SDA;
	SDA_L;delayMicroseconds(speed);
	SCL_H;delayMicroseconds(speed);
	SCL_L;delayMicroseconds(speed);
}

void IIC_Write(unsigned char dat){
	set_output_SDA;
	set_output_SCL;
	delayMicroseconds(speed);
	for(int i=0;i<8;++i){
		if(dat&0x80){
			SDA_H;delayMicroseconds(speed);
		}else{
			SDA_L;delayMicroseconds(speed);
		}
		SCL_H;delayMicroseconds(speed);
		SCL_L;delayMicroseconds(speed);
		dat <<= 1;		
	}
	IIC_ACK_Master();
}

unsigned char IIC_Read(void){
	set_input_SDA;
	set_pull_down;
	set_output_SCL;
	delayMicroseconds(speed);
	unsigned char dat=0x00;
	for(int i=0;i<8;++i){
		dat<<=1;
		if(SDA_R){dat|=0x01;delayMicroseconds(speed);}
		else{dat&=0xFE;delayMicroseconds(speed);}
		SCL_H;delayMicroseconds(speed);
		SCL_L;delayMicroseconds(speed);
	}
	IIC_ACK_Slave();
	return dat;
}