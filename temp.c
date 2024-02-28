#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"
#include "lpf.h"

#define  TEMP_AVG_SMPL   4
#define  TEMP_AVG_RSHIFT 2

typedef struct temp_t{
  uint16_t Raw;
  uint16_t Filtered;
}temp_t;

temp_t Temperature;

void Temp_Struct_Init(void){
  Temperature.Raw=0;
  Temperature.Filtered=0;
}

void Temp_ADC_Init(void){
  ADMUX  = (1<<REFS0)|(1<<REFS1);
  ADCSRA = (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
  ADCSRA|= (1<<ADEN) |(1<<ADSC);
}



uint16_t Temp_Read_ADC(uint8_t channel){
  uint8_t temp=ADMUX;
  temp &= 0xF0;
  temp |= channel;
  ADMUX = temp;
  ADCSRA|=(1<<ADSC);
  while((ADCSRA & (1<<ADIF))==0);
  return ADCW;
}

uint16_t Temp_Read_ADC_Avg(uint8_t channel){
  Temp_Read_ADC(channel);
  uint16_t sum=0;
  for(uint8_t i=0;i<TEMP_AVG_SMPL;i++){
    sum+=Temp_Read_ADC(channel);
  }
  sum>>=TEMP_AVG_RSHIFT;
  return sum;
}

uint16_t Temp_Read_Avg(void){
  Iron_Heater_Off();
  _delay_us(50);
  uint16_t temp_mv=Temp_Read_ADC_Avg(0);
  Temperature.Raw=temp_mv;
  temp_mv=LPF_Get_Filtered_Value(0,temp_mv);
  Temperature.Filtered=temp_mv;
  return temp_mv;
}

uint16_t Temp_Get_Raw_Val(void){
  return Temperature.Raw;
}

uint16_t Temp_Get_Filtered_Val(void){
  return Temperature.Filtered;
}


void Temp_Init(void){
  Temp_Struct_Init();
  Temp_ADC_Init();
}