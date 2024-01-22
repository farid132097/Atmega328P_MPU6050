#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "time.h"
#include "mpu6050.h"
#include "servo.h"
#include "debug.h"
#include "i2c.h"
#include "lpf.h"

int main(void){

  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  Timer_Init();
  debug_init();
  debug_tx_text_nl("Debug Started");
  
  MPU6050_Init();
  
  int32_t ang_x=0;
  int32_t ang_y=0;
  int32_t ang_z=0;
  int32_t temp=0;
  while(1){
	
	
	MPU6050_Read_Acc_Gyro();
	
	int32_t time=Timer_Get_Time();
	Timer_Start();
	
	if(MPU6050_Get_Error()==0){
	  
	  temp = MPU6050_Get_GyroX();
	  temp*= time;
	  temp/= 100000;
	  ang_x+=temp;
	  
	  temp = MPU6050_Get_GyroY();
	  temp*= time;
	  temp/= 100000;
	  ang_y+=temp;
	  
	  temp = MPU6050_Get_GyroZ();
	  temp*= time;
	  temp/= 100000;
	  ang_z+=temp;
	  
	  debug_tx_number_cm(MPU6050_Read_Pitch());
	  debug_tx_number_cm(MPU6050_Read_Roll());
	  debug_tx_number_cm(ang_x);
	  debug_tx_number_cm(ang_y);
	  //debug_tx_number_cm(ang_z);
	  debug_tx_nl();
	}else{
	  MPU6050_Restart();
	}
	
	_delay_ms(5);
	
	
	
  }
}