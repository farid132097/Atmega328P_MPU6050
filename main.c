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
  
  I2C_Init();
  debug_init();
  Servo_Init(50);
  debug_tx_text_nl("Debug Started");
  I2C_Set_Mode_Active();
  
  while(1){
    
    /*debug_tx_number_cm(I2C_Read_Pitch_Angle());
	debug_tx_number_cm(I2C_Read_Roll_Angle());
	
	debug_tx_nl();
	_delay_ms(2);*/
	
	Servo_Set_Angle(45);
	_delay_ms(2000);
	Servo_Set_Angle(90);
	_delay_ms(2000);
	Servo_Set_Angle(135);
	_delay_ms(2000);
	Servo_Set_Angle(180);
	_delay_ms(2000);
	
	
  }
}