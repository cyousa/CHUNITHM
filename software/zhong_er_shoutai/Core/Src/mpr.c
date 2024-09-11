#include "mpr.h"
#include "main.h"
void I2C_Write(I2C_TypeDef *I2CR,int devaddr,int regaddr,int data)
{
	uint8_t dat =data;
	HAL_I2C_Mem_Write(&hi2c1, devaddr<<1, regaddr, I2C_MEMADD_SIZE_8BIT,&dat, sizeof(dat), 100);
}


uint8_t I2C_Read(I2C_TypeDef *I2CR,int devaddr,int regaddr)
{
	uint8_t data = 0;
	HAL_I2C_Mem_Read( &hi2c1, devaddr<<1, regaddr, I2C_MEMADD_SIZE_8BIT, &data, sizeof(data),100);

	return data;
}
int MPR121_Init(I2C_TypeDef *I2CR,int devaddr)
{
	I2C_Write(I2CR,devaddr,0x80,0x63);
	I2C_Write(I2CR,devaddr,0x5E,0x00);
	uint8_t status = I2C_Read(I2CR,devaddr,0x5D);
	if(status != 0x24)
	{
		return(0);
	}
	  // Section A  // 该组控制过滤。 data is > baseline.
	I2C_Write(I2CR,devaddr,MHD_R, 0x01);
	I2C_Write(I2CR,devaddr,NHD_R, 0x01);
	I2C_Write(I2CR,devaddr,NCL_R, 0x00);
	I2C_Write(I2CR,devaddr,FDL_R, 0x00);

	    // Section B  // 该组控制过滤。data is < baseline.
	I2C_Write(I2CR,devaddr,MHD_F, 0x01);
	I2C_Write(I2CR,devaddr,NHD_F, 0x01);
	I2C_Write(I2CR,devaddr,NCL_F, 0xFF);
	I2C_Write(I2CR,devaddr,FDL_F, 0x00);

	    //基线过滤控制寄存器
	I2C_Write(I2CR,devaddr,0x33, 0x00);    //noise half delta touched
	I2C_Write(I2CR,devaddr,0x34, 0x00);    //noise counts touched
	I2C_Write(I2CR,devaddr,0x35, 0x00);    //filter delay touched

	I2C_Write(I2CR,devaddr,0x36, 0x0F);
	I2C_Write(I2CR,devaddr,0x37, 0x0F);
	I2C_Write(I2CR,devaddr,0x38, 0x00);
	I2C_Write(I2CR,devaddr,0x39, 0x00);
	I2C_Write(I2CR,devaddr,0x3A, 0x01);
	I2C_Write(I2CR,devaddr,0x3B, 0x01);
	I2C_Write(I2CR,devaddr,0x3C, 0xFF);
	I2C_Write(I2CR,devaddr,0x3D, 0xFF);
	I2C_Write(I2CR,devaddr,0x3E, 0x00);
	I2C_Write(I2CR,devaddr,0x3F, 0x00);
	I2C_Write(I2CR,devaddr,0x40, 0x00);

	    // Section C  // 该组为每个电极设置触摸和释放阈值
	I2C_Write(I2CR,devaddr,ELE0_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE0_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE1_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE1_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE2_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE2_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE3_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE3_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE4_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE4_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE5_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE5_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE6_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE6_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE7_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE7_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE8_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE8_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE9_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE9_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE10_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE10_R, REL_THRESH);
	I2C_Write(I2CR,devaddr,ELE11_T, TOU_THRESH);
	I2C_Write(I2CR,devaddr,ELE11_R, REL_THRESH);

	I2C_Write(I2CR,devaddr,0x59, 0x02);
	I2C_Write(I2CR,devaddr,0x5A, 0x01);
	I2C_Write(I2CR,devaddr,0x5B, 0x00);
	I2C_Write(I2CR,devaddr,0x5C, 0x3F);
	I2C_Write(I2CR,devaddr,0x5D, 0x00);

	    // 启用自动配置和自动重新配置
	I2C_Write(I2CR,devaddr,0x7B, 0x0B);
	I2C_Write(I2CR,devaddr,0x7D, 0xC8);
	I2C_Write(I2CR,devaddr,0x7E, 0x82);
	I2C_Write(I2CR,devaddr,0x7F, 0xB4);

	    //电极配置（重要）
	I2C_Write(I2CR,devaddr,0x5E, 0xBC);//1011,1100。启用基线跟踪，启用接近检测，启用所有12个电极
	return(1);
	}


//掩码
uint8_t maskcode[8] =  {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

//HID对应键值
uint8_t keycodeA[8] = {F,F,D,D,S,S,A,A};
uint8_t keycodeB[8] = {K,K,J,J,H,H,G,G};
uint8_t keycodeC[8] = {C,C,X,X,Z,Z,L,L};
uint8_t keycodeD[8] = {M,M,N,N,B,B,V,V};
uint8_t ir_keycode[6]={Q,W,E,R,T,Y};
	//各个传感器的状态
uint8_t touchA_status = 0;
uint8_t touchB_status = 0;
uint8_t touchC_status = 0;
uint8_t touchD_status = 0;
void Read_key_value()
{
  /* USER CODE BEGIN vMPR121Task */
  /* Infinite loop */

		//考虑是否需要延时
		touchA_status = I2C_Read(I2C1,0X5A,0x00);

		touchB_status = I2C_Read(I2C1,0X5B,0x00);

		touchC_status = I2C_Read(I2C1,0X5D,0x00);

		touchD_status = I2C_Read(I2C1,0X5C,0x00);

  /* USER CODE END vMPR121Task */
} 
//发送的按键
extern uint8_t ws_peach[48];
extern volatile uint8_t refresh_flag;
uint8_t key_buffer[40] = {0};
void Key_Map()
{
			  for(uint8_t i = 0 ; i < 8 ; i++)
	  		{
					
					if(touchA_status & maskcode[i])
					{
							key_buffer[i+2]=keycodeA[i];

							ws_peach[36+(i/2)*3]=0xFF;//set rgb
							ws_peach[37+(i/2)*3]=0X87;
							ws_peach[38+(i/2)*3]=0XFC;
							
					}
					else
					{
						key_buffer[i+2]=0;
						
						if((i%2==0))
						{
							ws_peach[36+(i/2)*3]=0x98;
							ws_peach[37+(i/2)*3]=0xFF;
							ws_peach[38+(i/2)*3]=0xE4;
						}
						
					}
					
	  		}
				
				for(uint8_t i = 0 ; i < 8 ; i++)
	  		{
					if(touchB_status & maskcode[i])
					{
							key_buffer[i+10]=keycodeB[i];
						
							ws_peach[24+(i/2)*3]=0xFF;//set rgb
							ws_peach[25+(i/2)*3]=0X87;
							ws_peach[26+(i/2)*3]=0XFC;
					}
					else
					{
							key_buffer[i+10]=0;
						
						if(i%2==0)
						{
							ws_peach[24+(i/2)*3]=0x98;
							ws_peach[25+(i/2)*3]=0xFF;
							ws_peach[26+(i/2)*3]=0xE4;
						}
					}
	  		}
				for(uint8_t i = 0 ; i < 8 ; i++)
	  		{

					if(touchC_status & maskcode[i])
					{
							key_buffer[i+18]=keycodeC[i];
						
							ws_peach[12+(i/2)*3]=0xFF;//set rgb
							ws_peach[13+(i/2)*3]=0X87;
							ws_peach[14+(i/2)*3]=0XFC;
					}
					else
					{
							key_buffer[i+18]=0;
						if(i%2==0)
						{
							ws_peach[12+(i/2)*3]=0x98;
							ws_peach[13+(i/2)*3]=0xFF;
							ws_peach[14+(i/2)*3]=0xE4;
						}
					}
	  		}
				for(uint8_t i = 0 ; i < 8 ; i++)
	  		{

					if(touchD_status & maskcode[i])
					{
							key_buffer[i+26] =keycodeD[i];
						
							ws_peach[0+(i/2)*3]=0xFF;//set rgb
							ws_peach[1+(i/2)*3]=0X87;
							ws_peach[2+(i/2)*3]=0XFC;
					}
					else
					{
							key_buffer[i+26]=0;
							if(i%2==0)
						{
							ws_peach[0+(i/2)*3]=0x98;
							ws_peach[1+(i/2)*3]=0xFF;
							ws_peach[2+(i/2)*3]=0xE4;
						}
					}
	  		}
				for(uint8_t i = 0 ; i < 6 ; i++)
	  		{
					key_buffer[i+34] = adc_value[i] > 2500 ? ir_keycode[i] : 0 ;
										if(touchA_status & maskcode[i])
					{
							key_buffer[i+2]=keycodeA[i];
					}
					else
					{
							key_buffer[i+2]=0;
					}
	  		}
		refresh_flag=1;
}