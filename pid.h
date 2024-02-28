

void     PID_Init(void);
void     PID_Update_Constants(uint16_t kp, uint16_t ki, uint16_t kd);
void     PID_Update_IError_Limit(long max_IError);
void     PID_Reset_IError(void);
void     PID_Calculate_Error(int set_point, int process_value);
void     PID_Execute_Routine(int set_point, int process_value);
uint16_t PID_Get_Kp(void);
uint16_t PID_Get_Ki(void);
uint16_t PID_Get_Kd(void);
int      PID_Get_Set_Point(void);
int      PID_Get_Process_Value(void);
long     PID_Get_Current_Error(void);
long     PID_Get_IError(void);
long     PID_Get_DError(void);
long     PID_Get_IError_Limit(void);
uint16_t PID_Get_Output(void);
