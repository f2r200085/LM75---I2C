#ifndef __IIC_H__
#define __IIC_H__

/*Pin definition*/
#define SDA	7
#define SCL	0

/*Input Output setting*/
#define set_output_SDA	pinMode(SDA, OUTPUT)
#define set_input_SDA	pinMode(SDA, INPUT)
#define set_output_SCL	pinMode(SCL, OUTPUT)
#define set_input_SCL	pinMode(SCL, INPUT)

/*Set pull-up or pull-down*/
#define set_pull_down   pullUpDnControl(SDA, PUD_UP)

/*Writes the value HIGH or LOW (1 or 0)*/
#define SDA_H	digitalWrite(SDA, HIGH)
#define SDA_L	digitalWrite(SDA, LOW)
#define SCL_H	digitalWrite(SCL, HIGH)
#define SCL_L	digitalWrite(SCL, LOW)
#define SDA_R	digitalRead(SDA)

/*GPIO Speed Minimum:1*/
#define speed	3
#endif

#ifdef __IIC_C__
#define __IIC_EXTERN__
#else
#define __IIC_EXTERN__ extern
#endif

/*Raspberry Pi INIT.*/
__IIC_EXTERN__ void raspberry_gpio_init(void);

/*IIC Function*/
__IIC_EXTERN__ void IIC_Init(void);
__IIC_EXTERN__ void IIC_Start(void);
__IIC_EXTERN__ void IIC_Stop(void);
__IIC_EXTERN__ void IIC_ACK_Master(void);
__IIC_EXTERN__ void IIC_ACK_Slave(void);
__IIC_EXTERN__ void IIC_Write(unsigned char dat);
__IIC_EXTERN__ unsigned char IIC_Read(void);

