

#include <avr/io.h>
#include <util/delay.h>
#include "servo.h"

void Servo_Init(uint32_t frequency){
  uint32_t temp=F_CPU;
  temp/=8;
  temp/=frequency;
  DDRB  |= (1<<1);
  ICR1   = (uint16_t)temp-1;
  OCR1A  = 1500;
  TCCR1A = (1<<WGM11)|(1<<COM1A1);
  TCCR1B = (1<<CS11)|(1<<WGM12)|(1<<WGM13);
  Servo_Set_Angle(0);
  _delay_ms(100);
}

void Servo_Set_Angle(uint16_t angle){
  uint32_t temp0 = angle;
  uint32_t temp1 = 150000;
  temp1 += (temp0*833);
  temp1 /= 100;
  OCR1A = (uint16_t)temp1;
}