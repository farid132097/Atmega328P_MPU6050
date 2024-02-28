



#include <avr/io.h>


#define  PID_MAX_IERROR          150
#define  PID_OUTPUT_SCALING_FACT 100

typedef struct PID_Input_t{
  uint16_t    KP;
  uint16_t    KI;
  uint16_t    KD;
  int         SETPOINT;
  int         PROCESSVALUE;
}PID_Input_t;

typedef struct PID_Error_t{
  long        CURRENTERROR;
  long        DERROR;
  long        IERROR;
  long        IERRORLIMIT;
  long        LASTERROR;
}PID_Error_t;

typedef struct PID_t{
  PID_Input_t INPUT;
  PID_Error_t ERROR;
  uint16_t    OUTPUT;
}PID_t;


PID_t PID_type;
PID_t *PID;

void PID_Init(void){
  PID=&PID_type;
  PID->INPUT.KP=0;
  PID->INPUT.KI=0;
  PID->INPUT.KD=0;
  PID->INPUT.SETPOINT=0;
  PID->INPUT.PROCESSVALUE=0;
  PID->ERROR.CURRENTERROR=0;
  PID->ERROR.DERROR=0;
  PID->ERROR.IERROR=0;
  PID->ERROR.IERRORLIMIT=PID_MAX_IERROR;
  PID->ERROR.LASTERROR=0;
  PID->OUTPUT=0;
}

void PID_Update_Constants(uint16_t kp, uint16_t ki, uint16_t kd){
  PID->INPUT.KP=kp;
  PID->INPUT.KI=ki;
  PID->INPUT.KD=kd;
}

void PID_Update_IError_Limit(long max_IError){
  PID->ERROR.IERRORLIMIT=max_IError;
}

void PID_Reset_IError(void){
  PID->ERROR.IERROR=0;
}

void PID_Calculate_Error(int set_point, int process_value){
  PID->INPUT.SETPOINT=set_point;
  PID->INPUT.PROCESSVALUE=process_value;
  PID->ERROR.CURRENTERROR=PID->INPUT.SETPOINT-PID->INPUT.PROCESSVALUE;
  PID->ERROR.DERROR=PID->ERROR.CURRENTERROR-PID->ERROR.LASTERROR;
  PID->ERROR.LASTERROR=PID->ERROR.CURRENTERROR;
  PID->ERROR.IERROR+=PID->ERROR.CURRENTERROR;
  if     (PID->ERROR.IERROR > PID->ERROR.IERRORLIMIT){
    PID->ERROR.IERROR = PID->ERROR.IERRORLIMIT;
  }
  else if(PID->ERROR.IERROR < -PID->ERROR.IERRORLIMIT){
    PID->ERROR.IERROR = -PID->ERROR.IERRORLIMIT;
  }
}


void PID_Execute_Routine(int set_point, int process_value){
  PID_Calculate_Error(set_point, process_value);
  long control_value=(PID->ERROR.CURRENTERROR*PID->INPUT.KP);
  control_value+=(PID->ERROR.IERROR*PID->INPUT.KI);
  control_value+=(PID->ERROR.DERROR*PID->INPUT.KD);
  control_value/=PID_OUTPUT_SCALING_FACT;
  if(control_value<0){control_value=0;}
  PID->OUTPUT=(uint16_t)control_value;
}

uint16_t PID_Get_Kp(void){
  return PID->INPUT.KP;
}

uint16_t PID_Get_Ki(void){
  return PID->INPUT.KI;
}

uint16_t PID_Get_Kd(void){
  return PID->INPUT.KD;
}

int PID_Get_Set_Point(void){
  return PID->INPUT.SETPOINT;
}

int PID_Get_Process_Value(void){
  return PID->INPUT.PROCESSVALUE;
}

long PID_Get_Current_Error(void){
  return PID->ERROR.CURRENTERROR;
}

long PID_Get_IError(void){
  return PID->ERROR.IERROR;
}

long PID_Get_DError(void){
  return PID->ERROR.DERROR;
}

long PID_Get_IError_Limit(void){
  return PID->ERROR.IERRORLIMIT;
}

uint16_t PID_Get_Output(void){
  return PID->OUTPUT;
}
