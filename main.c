#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include "i2c.h"

int main(void){

  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  I2C_Init();
  debug_init();
  debug_tx_text_nl("Debug Started");
  
  
  while(1){
    I2C_Read_Register(0x6B);
	//I2C_Send_Device_Address(0x64);
	_delay_ms(500);
  }
}