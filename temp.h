

void     Temp_Struct_Init(void);
void     Temp_ADC_Init(void);

uint16_t Temp_Read_ADC(uint8_t channel);
uint16_t Temp_Read_ADC_Avg(uint8_t channel);
uint16_t Temp_Read_Avg(void);

uint16_t Temp_Get_Raw_Val(void);
uint16_t Temp_Get_Filtered_Val(void);

void     Temp_Init(void);