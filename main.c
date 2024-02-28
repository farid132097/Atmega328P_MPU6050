

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "timebase.h"
#include "debug.h"
#include "temp.h"
#include "lpf.h"
#include "pwm.h"
#include "pid.h"



int main(void){
  
  debug_init();
  PWM_Init();
  PID_Init();
  Temp_Init();
  //Timebase_Init(50);
  
  PID_Update_Constants(800,0,0);
  
  LPF_Init();
  LPF_Set_Alpha(0,30);
  LPF_Set_Alpha(1,30);
  LPF_Set_Alpha(2,50);
  
  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  DDRD |= (1<<1);
  PORTD&=~(1<<1);
  
  DDRD &=~(1<<0);
  PORTD|= (1<<0);
  
  int Target= 750, Actual_Target=0;
  int Count = 20;
  
  DDRD &=~(1<<4);
  PORTD|= (1<<4);
  
  
  DDRB &=~(1<<0);
  PORTB|= (1<<0);
  
  while(1){
	
	Temp_Read_Avg();
	PID_Execute_Routine(Actual_Target,Temp_Get_Raw_Val());
	Iron_Heater_On(PID_Get_Output());
	_delay_ms(5);
	uint32_t curr  = Temp_Read_ADC_Avg(1);
	uint32_t curr1 = curr;
	curr1*=1100;  //ref*1000
	curr1*=1000;  //Rs in mOhms
	curr1/=1024;  //adc resolution
	curr1/=50;    //Rs in mOhms
	curr1/=10;    //I=mA/10
	curr1 = LPF_Get_Filtered_Value(1,curr1);
	
	debug_tx_number_cm(Target);
	debug_tx_number_cm(Actual_Target);
	debug_tx_number_cm(Temp_Get_Filtered_Val());
	//debug_tx_number_cm(curr);
	debug_tx_number_cm(curr1);
	//debug_tx_number_cm(PID_Get_Output());
	debug_tx_number_nl(Iron_Get_PWM());
	_delay_ms(50);
	
	
	if(Count>0){
	  Count--;
	}
	
	if(Count==0){
	  Actual_Target=Target;
	}
	
	if((PIND & (1<<4))==0){
	  Target++;
	  if(Target>800){
	    Target=800;
	  }
	  Count = 20;
	  _delay_ms(20);
	}else if((PINB & (1<<0))==0){
	  Target--;
	  if(Target<0){
	    Target=0;
	  }
	  Count = 20;
	  _delay_ms(20);
	}
	
  }
}