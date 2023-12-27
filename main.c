#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include "i2c.h"
#include "lpf.h"

int main(void){

  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  I2C_Init();
  debug_init();
  debug_tx_text_nl("Debug Started");
  I2C_Set_Mode_Active();

  
  while(1){
	debug_tx_number_cm(I2C_Read_Acc_X());
	debug_tx_number_cm(I2C_Read_Acc_Y());
	debug_tx_number_cm(I2C_Read_Acc_Z());
	debug_tx_number_cm(I2C_Read_Gyro_X());
	debug_tx_number_cm(I2C_Read_Gyro_Y());
	debug_tx_number_nl(I2C_Read_Gyro_Z());
	//debug_tx_number_nl(I2C_Read_Temp());
	
	_delay_ms(2);
  }
}