

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "time.h"

void Time_Struct_Init(void){
  
}

void Time_Config_Reg(void){
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1C = 0x00;
  TCNT1  = 0x00;
  TIMSK1 = 0x00;
  TIFR1  = 0x00;
  