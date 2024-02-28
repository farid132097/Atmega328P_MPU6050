

#include <avr/io.h>

/*PWM Parameters*/
#define ICR1_TOP_VAL         600
#define PWM_MAX_VAL          ICR1_TOP_VAL-1
#define OCR1_INIT_VAL        0

typedef struct {
  uint16_t TOPVALUE;
  uint16_t CURRENTVALUE;
}PWM_t;


typedef struct heater_t{
  uint8_t  STATUS;
  PWM_t    PWM;
}heater_t;

heater_t HEATER_type;
heater_t *HEATER;


void Iron_Heater_On(uint16_t val){
  if((HEATER->STATUS==0) && (val>0)){
    DDRB|=(1<<1);
    PORTB&=~(1<<1);
    if(val>PWM_MAX_VAL){val=PWM_MAX_VAL;}
    OCR1A=val;
    TCCR1A|=(1<<COM1A1);
	HEATER->PWM.CURRENTVALUE=val;
	HEATER->STATUS=1;
  }
}


void Iron_Heater_Off(void){
  if(HEATER->STATUS==1){
    TCCR1A&=~(1<<COM1A1);
	OCR1A=0;
	DDRB &=~(1<<1);
    PORTB&=~(1<<1);
	HEATER->PWM.CURRENTVALUE=0;
	HEATER->STATUS=0;
  }
}

uint16_t Iron_Get_PWM(void){
  return HEATER->PWM.CURRENTVALUE;
}


void PWM_Init(void){
  HEATER=&HEATER_type;
  DDRB|=(1<<1);
  PORTB&=~(1<<1);
  TCCR1A=(1<<COM1A1)|(1<<WGM11);
  TCCR1B=(1<<CS10)|(1<<WGM12)|(1<<WGM13);
  ICR1=ICR1_TOP_VAL;
  OCR1A=OCR1_INIT_VAL;
  TCCR1A&=~(1<<COM1A1);
  HEATER->PWM.TOPVALUE=ICR1_TOP_VAL;
  HEATER->PWM.CURRENTVALUE=OCR1_INIT_VAL;
  HEATER->STATUS=0;
  Iron_Heater_Off();
}