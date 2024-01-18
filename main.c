#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "servo.h"
#include "debug.h"
#include "i2c.h"
#include "lpf.h"

int main(void){

  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  MPU6050_Init();
  debug_init();
  Servo_Init(50);
  debug_tx_text_nl("Debug Started");
  
  
  while(1){
	
    /*debug_tx_number_cm(I2C_Read_Acc_X());
	debug_tx_number_cm(I2C_Read_Acc_Y());
	debug_tx_number_cm(I2C_Read_Acc_Z());
	
    debug_tx_number_cm(I2C_Read_Pitch_Angle());
	debug_tx_number_cm(I2C_Read_Roll_Angle());
	
	debug_tx_number_cm(I2C_Get_Error());
	debug_tx_number_cm(I2C_Get_ErrorAccu());*/
	
	debug_tx_number_cm(I2C_Read_Register(0x6B));
	debug_tx_number_cm(MPU6050_Read_Roll_Angle_Safely());
	
	debug_tx_nl();
	_delay_ms(100);
	
	/*Servo_Set_Angle(45);
	_delay_ms(2000);
	Servo_Set_Angle(90);
	_delay_ms(2000);
	Servo_Set_Angle(135);
	_delay_ms(2000);
	Servo_Set_Angle(180);
	_delay_ms(2000);*/
	
	
  }
}