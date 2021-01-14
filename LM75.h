#ifndef __LM75_H__
#define __LM75_H__

/*LM75 Address  fix: '1001' + A2 A1 A0 + 'Write/ Read'*/
#define A2  1
#define A1  1
#define A0  1
#define I2C_ADDRESS (0x90 | (A2 << 3) | (A1 << 2) | (A0 << 1))

/*LM75 Read/ Wirte bit*/
#define Read    0x01
#define Write   0x00

/*Pointer Register*/
#define Temp	0x00
#define Conf	0x01
#define Thyst	0x02
#define Tos		0x03

/*Configuration register*/
#define  OS_F_QUE_queue_0       0 << 2      // (default value)
#define  OS_F_QUE_queue_2       1 << 2
#define  OS_F_QUE_queue_4       2 << 2
#define  OS_F_QUE_queue_6       3 << 2

#define  OS_POL_active_LOW      0 << 1      // (default value)
#define  OS_POL_active_HIGH     1 << 1

#define OS_COMP_INT_comparator  0 << 1      // (default value)
#define OS_COMP_INT_interrupt   1 << 1

#define SHUTDOWN_normal         0           // (default value)
#define SHUTDOWN_shutdown       1

#define Conf_register           (OS_F_QUE_queue_0 | OS_POL_active_LOW | OS_COMP_INT_comparator | SHUTDOWN_normal)

#endif

#ifdef __LM75_C__
#define __LM75_EXTERN__
#else
#define __LM75_EXTERN__ extern
#endif


/*IIC Applictiion*/
__LM75_EXTERN__ void write_1byte(unsigned char data1);
__LM75_EXTERN__ void write_2byte(unsigned char data1, unsigned char data2);
__LM75_EXTERN__ void write_3byte(unsigned char data1, unsigned char data2, unsigned char data3);
__LM75_EXTERN__ unsigned char *get_1byte(void);
__LM75_EXTERN__ unsigned char *get_2byte(void);

/*Get LM75 register information*/
__LM75_EXTERN__ void Get_Temperature(void);
__LM75_EXTERN__ void Get_Hysteresis(void);
__LM75_EXTERN__ void Get_Configuration(void);
__LM75_EXTERN__ void Get_Overtemperature_Shutdown_Threshold(void);
__LM75_EXTERN__ void Get_All_Information(void);

/*set LM75 register*/
__LM75_EXTERN__ void Set_Configuration(unsigned char data);
__LM75_EXTERN__ void Set_Hysteresis(float f_input);
__LM75_EXTERN__ void Set_Overtemperature_Shutdown_Threshold(float f_input);
__LM75_EXTERN__ void Set_All_Pointer_Register(unsigned char h_conf, float f_tos, float f_thyst);