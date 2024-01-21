

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "mpu6050.h"
#include "time.h"
#include "lpf.h"
#include "i2c.h"


#define  LPF_EN 50

typedef struct mpu6050_t{
  int   AccX;
  int   AccY;
  int   AccZ;
  int   GyroX;
  int   GyroY;
  int   GyroZ;
  int   GyroXCal;
  int   GyroYCal;
  int   GyroZCal;
  int   Pitch;
  int   Roll;
  int   Yaw;
  int   Temp;
  int   Error;
}mpu6050_t;

mpu6050_t MPU6050;

void MPU6050_Struct_Init(void){
  MPU6050.AccX=0;
  MPU6050.AccY=0;
  MPU6050.AccZ=0;
  MPU6050.GyroX=0;
  MPU6050.GyroY=0;
  MPU6050.GyroZ=0;
  MPU6050.GyroXCal=0;
  MPU6050.GyroYCal=0;
  MPU6050.GyroZCal=0;
  MPU6050.Pitch=0;
  MPU6050.Roll=0;
  MPU6050.Yaw=0;
  MPU6050.Temp=0;
  MPU6050.Error=0;
}

int MPU6050_Get_AccX(void){
  return MPU6050.AccX;
}

int MPU6050_Get_AccY(void){
  return MPU6050.AccY;
}

int MPU6050_Get_AccZ(void){
  return MPU6050.AccZ;
}

int MPU6050_Get_GyroX(void){
  return MPU6050.GyroX;
}

int MPU6050_Get_GyroY(void){
  return MPU6050.GyroY;
}

int MPU6050_Get_GyroZ(void){
  return MPU6050.GyroZ;
}

int MPU6050_Get_GyroXCal(void){
  return MPU6050.GyroXCal;
}

int MPU6050_Get_GyroYCal(void){
  return MPU6050.GyroYCal;
}

int MPU6050_Get_GyroZCal(void){
  return MPU6050.GyroZCal;
}

int MPU6050_Get_Pitch(void){
  return MPU6050.Pitch;
}

int MPU6050_Get_Roll(void){
  return MPU6050.Roll;
}

int MPU6050_Get_Yaw(void){
  return MPU6050.Yaw;
}

int MPU6050_Get_Temp(void){
  return MPU6050.Temp;
}

int MPU6050_Get_Error(void){
  return MPU6050.Error;
}

void MPU6050_Error_Clear(void){
  MPU6050.Error=0x00;
}

uint8_t MPU6050_Get_Mode(void){
  return I2C_Read_Register(0x6B);
}

void MPU6050_Set_Mode_Sleep(void){
  if( (MPU6050_Get_Mode() & 0x40) == 0){
    I2C_Write_Register(0x6B, 0x40);
  }
}

void MPU6050_Set_Mode_Active(void){
  if( (MPU6050_Get_Mode() & 0x40) == 0x40){
    I2C_Write_Register(0x6B, 0x00);
  }
}

int MPU6050_Read_AccX(void){
  int data=0, error1=0, error2=0;
  data = I2C_Read_Register(0x3B);
  error1 = I2C_Get_Error();
  data <<= 8;
  data |= I2C_Read_Register(0x3C);
  error2 = I2C_Get_Error();
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(0, data);
  #endif
  if( (error1!=0) || (error2!=0) ){
    data=0;
	MPU6050.Error=0x01;
  }
  MPU6050.AccX=data;
  return data;
}

int MPU6050_Read_AccY(void){
  int data=0, error1=0, error2=0;
  data = I2C_Read_Register(0x3D);
  error1 = I2C_Get_Error();
  data <<= 8;
  data |= I2C_Read_Register(0x3E);
  error2 = I2C_Get_Error();
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(1, data);
  #endif
  if( (error1!=0) || (error2!=0) ){
    data=0;
	MPU6050.Error=0x02;
  }
  MPU6050.AccY=data;
  return data;
}

int MPU6050_Read_AccZ(void){
  int data=0, error1=0, error2=0;
  data = I2C_Read_Register(0x3F);
  error1 = I2C_Get_Error();
  data <<= 8;
  data |= I2C_Read_Register(0x40);
  error2 = I2C_Get_Error();
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(2, data);
  #endif
  if( (error1!=0) || (error2!=0) ){
    data=0;
	MPU6050.Error=0x03;
  }
  MPU6050.AccZ=data;
  return data;
}

int MPU6050_Read_GyroX(void){
  int data=0, error1=0, error2=0;
  data = I2C_Read_Register(0x43);
  error1 = I2C_Get_Error();
  data <<= 8;
  data |= I2C_Read_Register(0x44);
  error2 = I2C_Get_Error();
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(3, data);
  #endif
  data-=MPU6050.GyroXCal;
  if( (error1!=0) || (error2!=0) ){
    data=0;
	MPU6050.Error=0x11;
  }
  // 131 LSB/Degree/Second
  data/=131;
  MPU6050.GyroX=data;
  return data;
}

int MPU6050_Read_GyroY(void){
  int data=0, error1=0, error2=0;
  data = I2C_Read_Register(0x45);
  error1 = I2C_Get_Error();
  data <<= 8;
  data |= I2C_Read_Register(0x46);
  error2 = I2C_Get_Error();
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(4, data);
  #endif
  data-=MPU6050.GyroYCal;
  if( (error1!=0) || (error2!=0) ){
    data=0;
	MPU6050.Error=0x12;
  }
  // 131 LSB/Degree/Second
  data/=131;
  MPU6050.GyroY=data;
  return data;
}

int MPU6050_Read_GyroZ(void){
  int data=0, error1=0, error2=0;
  data = I2C_Read_Register(0x47);
  error1 = I2C_Get_Error();
  data <<= 8;
  data |= I2C_Read_Register(0x48);
  error2 = I2C_Get_Error();
  #ifdef LPF_EN
    data = LPF_Get_Filtered_Value(5, data);
  #endif
  data-=MPU6050.GyroZCal;
  if( (error1!=0) || (error2!=0) ){
    data=0;
	MPU6050.Error=0x13;
  }
  // 131 LSB/Degree/Second
  data/=131;
  MPU6050.GyroZ=data;
  return (int16_t)data;
}

int MPU6050_Read_Temp(void){
  int data=0, error1=0, error2=0;
  data = I2C_Read_Register(0x41);
  error1 = I2C_Get_Error();
  data <<= 8;
  data |= I2C_Read_Register(0x42);
  error2 = I2C_Get_Error();
  data /=340;
  data +=36;
  if( (error1!=0) || (error2!=0) ){
    data=0;
	MPU6050.Error=0x21;
  }
  MPU6050.Temp=data;
  return data;
}

void MPU6050_Read_Acc(void){
  if(MPU6050.Error==0){
    MPU6050_Read_AccX();
  }
  if(MPU6050.Error==0){
    MPU6050_Read_AccY();
  }
  if(MPU6050.Error==0){
    MPU6050_Read_AccZ();
  }
}

void MPU6050_Read_Gyro(void){
  if(MPU6050.Error==0){
    MPU6050_Read_GyroX();
  }
  if(MPU6050.Error==0){
    MPU6050_Read_GyroY();
  }
  if(MPU6050.Error==0){
    MPU6050_Read_GyroZ();
  }
}

void MPU6050_Read_Acc_Gyro(void){
  MPU6050_Read_Acc();
  MPU6050_Read_Gyro();
}

int MPU6050_Read_Pitch(void){
  if(MPU6050.Error==0){
    float ax=MPU6050_Get_AccX();
    float az=MPU6050_Get_AccZ();
    float divx=ax/az;
    float pitch = atan(divx);
    pitch*=10.0;
    pitch*=57.3;
	MPU6050.Pitch=(int)pitch;
	return MPU6050.Pitch;
  }else{
    MPU6050.Pitch=0;
    return 0;
  }
}

int MPU6050_Read_Roll(void){
  if(MPU6050.Error==0){
    float ay=MPU6050_Get_AccY();
    float az=MPU6050_Get_AccZ();
    float divy=ay/az;
    float roll = atan(divy);
    roll*=10.0;
    roll*=57.3;
	MPU6050.Roll=(int)roll;
    return MPU6050.Roll;
  }else{
    MPU6050.Roll=0;
    return 0;
  }
}

void MPU6050_Init(void){
  I2C_Init();
  _delay_ms(10);
  MPU6050_Struct_Init();
  MPU6050_Set_Mode_Active();
  #ifdef LPF_EN
	LPF_Init();
	LPF_Set_Alpha(0,LPF_EN);
	LPF_Set_Alpha(1,LPF_EN);
	LPF_Set_Alpha(2,LPF_EN);
	LPF_Set_Alpha(3,LPF_EN);
	LPF_Set_Alpha(4,LPF_EN);
	LPF_Set_Alpha(5,LPF_EN);
  #endif
  _delay_ms(100);
  for(uint8_t i=0;i<32;i++){
    MPU6050_Read_Acc_Gyro();
  }
  MPU6050.GyroXCal=MPU6050_Get_GyroX();
  MPU6050.GyroYCal=MPU6050_Get_GyroY();
  MPU6050.GyroZCal=MPU6050_Get_GyroZ();
  
}

void MPU6050_Restart(void){
  I2C_Error_Clear_All();
  uint8_t temp=MPU6050_Get_Error();
  MPU6050_Error_Clear();
  _delay_ms(2);
  I2C_Stop();
  _delay_ms(2);
  MPU6050_Set_Mode_Active();
  _delay_ms(2);
  MPU6050_Read_Acc_Gyro();
  if(MPU6050_Get_Mode()!=0){
    MPU6050.Error=temp;
  }
}
