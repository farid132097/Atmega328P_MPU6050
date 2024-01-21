

void     MPU6050_Struct_Init(void);

int      MPU6050_Get_AccX(void);
int      MPU6050_Get_AccY(void);
int      MPU6050_Get_AccZ(void);
int      MPU6050_Get_GyroX(void);
int      MPU6050_Get_GyroY(void);
int      MPU6050_Get_GyroZ(void);
int      MPU6050_Get_GyroXCal(void);
int      MPU6050_Get_GyroYCal(void);
int      MPU6050_Get_GyroZCal(void);
int      MPU6050_Get_Pitch(void);
int      MPU6050_Get_Roll(void);
int      MPU6050_Get_Yaw(void);
int      MPU6050_Get_Temp(void);
int      MPU6050_Get_Error(void);
uint8_t  MPU6050_Get_Mode(void);

void     MPU6050_Error_Clear(void);

void     MPU6050_Set_Mode_Sleep(void);
void     MPU6050_Set_Mode_Active(void);

int      MPU6050_Read_AccX(void);
int      MPU6050_Read_AccY(void);
int      MPU6050_Read_AccZ(void);
int      MPU6050_Read_GyroX(void);
int      MPU6050_Read_GyroY(void);
int      MPU6050_Read_GyroZ(void);
int      MPU6050_Read_Temp(void);

void     MPU6050_Read_Acc(void);
void     MPU6050_Read_Gyro(void);
void     MPU6050_Read_Acc_Gyro(void);

int      MPU6050_Read_Pitch(void);
int      MPU6050_Read_Roll(void);

void     MPU6050_Init(void);
void     MPU6050_Restart(void);