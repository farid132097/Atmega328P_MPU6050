
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

void I2C_Half_Bit_Delay(void){
  _delay_us(250);
}

void I2C_Bit_Delay(void){
  _delay_us(500);
}

void I2C_SCL_Set_DD(uint8_t state){
  if(state==1){
    I2C_SCL_DDR |=  (1<<I2C_SCL_bp);
  }else{
    I2C_SCL_DDR &=~ (1<<I2C_SCL_bp);
  }
}

void I2C_SCL_Set_Output(uint8_t state){
  if(state==1){
    I2C_SCL_PORT |=  (1<<I2C_SCL_bp);
  }else{
    I2C_SCL_PORT &=~ (1<<I2C_SCL_bp);
  }
}

uint8_t I2C_SCL_Get_State(void){
  if(I2C_SCL_PIN & (1<<I2C_SCL_bp)){
    return 1;
  }else{
    return 0;
  }
}

void I2C_SDA_Set_DD(uint8_t state){
  if(state==1){
    I2C_SDA_DDR |=  (1<<I2C_SDA_bp);
  }else{
    I2C_SDA_DDR &=~ (1<<I2C_SDA_bp);
  }
}

void I2C_SDA_Set_Output_LL(uint8_t state){
  if(state==1){
    I2C_SDA_PORT |=  (1<<I2C_SDA_bp);
  }else{
    I2C_SDA_PORT &=~ (1<<I2C_SDA_bp);
  }
}

void I2C_SDA_Set_Output(uint8_t state){
  if(state==1){
    I2C_SDA_Set_Output_LL(1);
	I2C_SDA_Set_DD(0);
  }else{
    I2C_SDA_Set_Output_LL(0);
	I2C_SDA_Set_DD(1);
  }
}

uint8_t I2C_SDA_Get_State(void){
  if(I2C_SDA_PIN & (1<<I2C_SDA_bp)){
    return 1;
  }else{
    return 0;
  }
}

void I2C_SCL_Reset_State(void){
  I2C_SCL_Set_DD(0);
  I2C_SCL_Set_Output(0);
}

void I2C_SDA_Reset_State(void){
  I2C_SDA_Set_DD(0);
  I2C_SDA_Set_Output(0);
}

void I2C_GPIO_Init(void){
  I2C_SCL_Set_DD(1);
  I2C_SDA_Set_DD(0);
  I2C_SCL_Set_Output(1);
  I2C_SDA_Set_Output(1);
}

void I2C_Start(void){
  I2C_SCL_Set_Output(1);
  I2C_SDA_Set_Output(1);
  I2C_Half_Bit_Delay();
  
  I2C_SDA_Set_Output(0);
  I2C_Half_Bit_Delay();
  
  I2C_SCL_Set_Output(0);
  I2C_Half_Bit_Delay();
}

void I2C_Stop(void){
  I2C_SCL_Set_Output(0);
  I2C_SDA_Set_Output(0);
  I2C_Half_Bit_Delay();
  
  I2C_SCL_Set_Output(1);
  I2C_Half_Bit_Delay();
  
  I2C_SDA_Set_Output(1);
  I2C_Half_Bit_Delay();
}

void I2C_Data(uint8_t data){
  for(uint8_t i=0;i<8;i++){
    if( data & 0x80){
	  I2C_SDA_Set_Output(1);
	}else{
	  I2C_SDA_Set_Output(0);
	}
	I2C_Half_Bit_Delay();
	I2C_SCL_Set_Output(1);
	I2C_Half_Bit_Delay();
	I2C_SCL_Set_Output(0);
	data<<=1;
  }
}
  