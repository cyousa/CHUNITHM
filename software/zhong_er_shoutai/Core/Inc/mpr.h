#ifndef __MPR_H
#define __MPR_H
#include "stm32g4xx_hal.h"
#include "i2c.h"
	// MPR121 寄存器定义
	#define    MHD_R    0x2B
	#define    NHD_R    0x2C
	#define    NCL_R    0x2D
	#define    FDL_R    0x2E

	#define    MHD_F    0x2F
	#define    NHD_F    0x30
	#define    NCL_F    0x31
	#define    FDL_F    0x32

	#define    ELE0_T      0x41
	#define    ELE0_R      0x42
	#define    ELE1_T      0x43
	#define    ELE1_R      0x44
	#define    ELE2_T      0x45
	#define    ELE2_R      0x46
	#define    ELE3_T      0x47
	#define    ELE3_R      0x48
	#define    ELE4_T      0x49
	#define    ELE4_R      0x4A
	#define    ELE5_T      0x4B
	#define    ELE5_R      0x4C
	#define    ELE6_T      0x4D
	#define    ELE6_R      0x4E
	#define    ELE7_T      0x4F
	#define    ELE7_R      0x50
	#define    ELE8_T      0x51
	#define    ELE8_R      0x52
	#define    ELE9_T      0x53
	#define    ELE9_R      0x54
	#define    ELE10_T     0x55
	#define    ELE10_R     0x56
	#define    ELE11_T     0x57
	#define    ELE11_R     0x58

	#define    FIL_CFG     0x5D
	#define    ELE_CFG     0x5E
	#define    GPIO_CTRL0  0x73
	#define    GPIO_CTRL1  0x74
	#define    GPIO_DATA   0x75
	#define    GPIO_DIR    0x76
	#define    GPIO_EN     0x77
	#define    GPIO_SET    0x78
	#define    GPIO_CLEAR  0x79
	#define    GPIO_TOGGLE 0x7A
	#define    ATO_CFG0    0x7B
	#define    ATO_CFGU    0x7D
	#define    ATO_CFGL    0x7E
	#define    ATO_CFGT    0x7F

	// 全局常数（实测“3/2”参数适用3mm有机玻璃板）
	#define    TOU_THRESH    15       //触摸阈值 0x0F     10//15//30//10//3
	#define    REL_THRESH    8	    //释放阈值 0x0A         08//08//25//08//2
	
	#define   A    0x04
	#define   S    0x16
	#define   D    0x07
	#define   F    0x09
	#define   G    0x0A
	#define   H    0x0B
	#define   J    0x0D
	#define   K    0x0E
	
	#define   L    0x0F
	#define   Z    0x1D
	#define   X    0x1B
	#define   C    0x06
	#define   V    0x19
	#define   B    0x05
	#define   N    0x11
	#define   M    0x10
	
	#define   Q    0x14
	#define   W    0x1A
	#define   E    0x08
	
	#define   R    0x15
	#define   T    0x17
	#define   Y    0x1C

	
	extern uint8_t key_buffer[40];
	
void I2C_Write(I2C_TypeDef *I2CR,int devaddr,int regaddr,int data);
uint8_t I2C_Read(I2C_TypeDef *I2CR,int devaddr,int regaddr);
int MPR121_Init(I2C_TypeDef *I2CR,int devaddr);
void Read_key_value();
void Key_Map();
#endif