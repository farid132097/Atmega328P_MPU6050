#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

int main(void){

  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  I2C_GPIO_Init();
  
  while(1){
    I2C_Start();
	I2C_Data(0x63);
	I2C_Stop();
	_delay_ms(500);
  }
}