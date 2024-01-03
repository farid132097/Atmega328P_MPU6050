#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
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
    float ax=I2C_Read_Acc_X();
	float ay=I2C_Read_Acc_Y();
	float az=I2C_Read_Acc_Z();
	float divx=ax/az;
	float divy=ay/az;
	float divz=ay/ax;
	
    float ThetaX = atan(divx);
    ThetaX*=100.0;
    ThetaX*=57.3;
	float ThetaY = atan(divy);
    ThetaY*=100.0;
    ThetaY*=57.3;
	float ThetaZ = atan2(ay,ax);
	ThetaZ*=100.0;
    ThetaZ*=57.3;
	
    debug_tx_number_cm(ThetaX);
	debug_tx_number_cm(ThetaY);
	//debug_tx_number_cm(ThetaZ);
	//debug_tx_number_cm(I2C_Read_Acc_Z());
	/*debug_tx_number_cm(I2C_Read_Acc_X());
	debug_tx_number_cm(I2C_Read_Acc_Y());
	debug_tx_number_cm(I2C_Read_Acc_Z());*/
	//debug_tx_number_cm(I2C_Read_Gyro_X());
	//debug_tx_number_cm(I2C_Read_Gyro_Y());
	//debug_tx_number_cm(I2C_Read_Gyro_Z());
	//debug_tx_number_cm(I2C_Read_Temp());
	
	debug_tx_nl();
	_delay_ms(2);
  }
}