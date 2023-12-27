
#include <avr/io.h>
#include <util/delay.h>
#include "lpf.h"
#include "i2c.h"

#define  LPF_EN 10

typedef struct i2c_t{
  uint8_t  WriteAddr;
  uint8_t  ReadAddr;
}i2c_t;

i2c_t I2C;

void I2C_Struct_Init(void){
  I2C.WriteAddr=0x00;
  I2C.ReadAddr=0x00;
}

void I2C_Half_Bit_Delay(void){
  _delay_us(20);
}

void I2C_Bit_Delay(void){
  _delay_us(40);
}

void I2C_Guard_Delay(void){
  _delay_us(2);
}

void I2C_SCL_Set_DD(uint8_t state){
  if(state==1){
    I2C_SCL_DDR |=  (1<<I2C_SCL_bp);
  }else{
    I2C_SCL_DDR &=~ (1<<I2C_SCL_bp);
  }
}

void I2C_SCL_Set_Output_LL(uint8_t state){
  if(state==1){
    I2C_SCL_PORT |=  (1<<I2C_SCL_bp);
  }else{
    I2C_SCL_PORT &=~ (1<<I2C_SCL_bp);
  }
}

void I2C_SCL_Set_Output(uint8_t state){
  if(state==1){
    I2C_SCL_Set_Output_LL(1);
	I2C_SCL_Set_DD(0);
  }else{
    I2C_SCL_Set_Output_LL(0);
	I2C_SCL_Set_DD(1);
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

void I2C_Data_Send(uint8_t data){
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
	I2C_Guard_Delay();
	data<<=1;
  }
}

uint8_t I2C_Data_Receive(void){
  uint8_t data=0;
  I2C_SDA_Set_Output(1);
  for(uint8_t i=0;i<8;i++){
    data<<=1;
	I2C_Half_Bit_Delay();
	I2C_SCL_Set_Output(1);
	if(I2C_SDA_Get_State()){
	  data|=0x01;
	}
	I2C_Half_Bit_Delay();
	I2C_SCL_Set_Output(0);
  }
  I2C_Half_Bit_Delay();
  I2C_SCL_Set_Output(1);
  return data;
}

void I2C_Set_Ack(void){
  I2C_SDA_Set_Output(0);
  I2C_Half_Bit_Delay();
  I2C_SCL_Set_Output(1);
  I2C_Half_Bit_Delay();
  I2C_SCL_Set_Output(0);
}

void I2C_Set_Nack(void){
  I2C_SDA_Set_Output(1);
  I2C_Half_Bit_Delay();
  I2C_SCL_Set_Output(1);
  I2C_Half_Bit_Delay();
  I2C_SCL_Set_Output(0);
}

uint8_t I2C_Get_Ack(void){
  uint8_t ack=0;
  I2C_SDA_Set_Output(1);
  I2C_Half_Bit_Delay();
  I2C_SCL_Set_Output(1);
  ack=I2C_SDA_Get_State();
  I2C_Half_Bit_Delay();
  I2C_SCL_Set_Output(0);
  I2C_Guard_Delay();
  if(ack==0){
    return 1;
  }else{
    return 0;
  }
}

uint8_t I2C_Send_Device_Address(uint8_t address){
  uint8_t ack=0;
  I2C_Start();
  I2C_Data_Send(address);
  ack = I2C_Get_Ack();
  I2C_Stop();
  return ack;
}

uint8_t I2C_Get_Device_Address(void){
  uint8_t sts=0;
  for(uint8_t i=0;i<255;i++){
	sts = I2C_Send_Device_Address(i);
	if(sts==1){
	  sts=i;
	  break;
	}
  }
  return sts;
}

uint8_t I2C_Read_Register(uint8_t reg){
  uint8_t sts=0,data=0;
  I2C_Start();
  I2C_Data_Send(I2C.WriteAddr);
  sts |= I2C_Get_Ack()<<0;
  I2C_Data_Send(reg);
  sts |= I2C_Get_Ack()<<1;
  I2C_Stop();
  I2C_Start();
  I2C_Data_Send(I2C.ReadAddr);
  sts |= I2C_Get_Ack()<<2;
  data = I2C_Data_Receive();
  sts |= I2C_Get_Ack()<<3;
  I2C_Stop();
  if(sts == 0x07){
    sts = data;
  }else{
    sts = 0xFF;
  }
  return sts;
}

void I2C_Write_Register(uint8_t reg, uint8_t val){
  uint8_t sts=0,data=0;
  I2C_Start();
  I2C_Data_Send(I2C.WriteAddr);
  sts |= I2C_Get_Ack()<<0;
  I2C_Data_Send(reg);
  sts |= I2C_Get_Ack()<<1;

  I2C_Data_Send(val);
  sts |= I2C_Get_Ack()<<2;
  I2C_Stop();
  if(sts == 0x07){
    sts = data;
  }else{
    sts = 0xFF;
  }
}
 
void I2C_Init(void){
  I2C_Struct_Init();
  I2C_GPIO_Init();
  I2C.WriteAddr = I2C_Get_Device_Address();
  I2C.ReadAddr = I2C.WriteAddr+1;
  #ifdef LPF_EN
	LPF_Init();
	LPF_Set_Alpha(0,LPF_EN);
	LPF_Set_Alpha(1,LPF_EN);
	LPF_Set_Alpha(2,LPF_EN);
	LPF_Set_Alpha(3,LPF_EN);
	LPF_Set_Alpha(4,LPF_EN);
	LPF_Set_Alpha(5,LPF_EN);
  #endif
}

void I2C_Set_Mode_Sleep(void){
  I2C_Write_Register(0x6B, 0x40);
}

void I2C_Set_Mode_Active(void){
  I2C_Write_Register(0x6B, 0x00);
}

int16_t I2C_Read_Acc_X(void){
  int16_t data = 0;
  data = I2C_Read_Register(0x3B);
  data <<= 8;
  data |= I2C_Read_Register(0x3C);
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(0, data);
  #endif
  return (int16_t)data;
}

int16_t I2C_Read_Acc_Y(void){
  int16_t data = 0;
  data = I2C_Read_Register(0x3D);
  data <<= 8;
  data |= I2C_Read_Register(0x3E);
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(1, data);
  #endif
  return (int16_t)data;
}

int16_t I2C_Read_Acc_Z(void){
  int16_t data = 0;
  data = I2C_Read_Register(0x3F);
  data <<= 8;
  data |= I2C_Read_Register(0x40);
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(2, data);
  #endif
  return (int16_t)data;
}

int16_t I2C_Read_Gyro_X(void){
  int16_t data = 0;
  data = I2C_Read_Register(0x43);
  data <<= 8;
  data |= I2C_Read_Register(0x44);
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(3, data);
  #endif
  return (int16_t)data;
}

int16_t I2C_Read_Gyro_Y(void){
  int16_t data = 0;
  data = I2C_Read_Register(0x45);
  data <<= 8;
  data |= I2C_Read_Register(0x46);
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(4, data);
  #endif
  return (int16_t)data;
}

int16_t I2C_Read_Gyro_Z(void){
  int16_t data = 0;
  data = I2C_Read_Register(0x47);
  data <<= 8;
  data |= I2C_Read_Register(0x48);
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(5, data);
  #endif
  return (int16_t)data;
}

int16_t I2C_Read_Temp(void){
  int16_t data = 0;
  data = I2C_Read_Register(0x41);
  data <<= 8;
  data |= I2C_Read_Register(0x42);
  data /=340;
  data +=36;
  return data;
}

