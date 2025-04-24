

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "time.h"

void Timer_Struct_Init(void){
  
}

void Timer_Config_Reg(void){
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1C = 0x00;
  TCNT1  = 0x00;
  TIMSK1 = 0x00;
  TIFR1  = 0x00;
  TCCR1B = (1<<CS10)|(1<<CS11);
  TCNT1  = 0;
}

void Timer_Init(void){
  Timer_Struct_Init();
  Timer_Config_Reg();
}

void Timer_Start(void){
  TCNT1  = 0;
}

uint32_t Timer_Get_Time(void){
  uint32_t temp=0;
  temp=TCNT1;
  temp*=533;  //multiplied by 5.33us*100
  temp/=100;
  return temp;
}
  