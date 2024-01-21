#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "mpu6050.h"
#include "servo.h"
#include "debug.h"
#include "i2c.h"
#include "lpf.h"

int main(void){

  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  
  debug_init();
  debug_tx_text_nl("Debug Started");
  
  MPU6050_Init();
  
  
  while(1){
	
	MPU6050_Read_Acc_Gyro();
	
	if(MPU6050_Get_Error()==0){
	  //debug_tx_number_cm(MPU6050_Read_Pitch());
	  //debug_tx_number_cm(MPU6050_Read_Roll());
	  debug_tx_number_cm(MPU6050_Get_GyroX());
	  debug_tx_number_cm(MPU6050_Get_GyroY());
	  debug_tx_number_cm(MPU6050_Get_GyroZ());
	  debug_tx_nl();
	}else{
	  MPU6050_Restart();
	}
	
	_delay_ms(5);
	
	
	
  }
}