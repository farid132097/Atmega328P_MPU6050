

#define I2C_SCL_DDR  DDRB
#define I2C_SCL_PORT PORTB
#define I2C_SCL_PIN  PINB
#define I2C_SCL_bp   5

#define I2C_SDA_DDR  DDRB
#define I2C_SDA_PORT PORTB
#define I2C_SDA_PIN  PINB
#define I2C_SDA_bp   3

void     I2C_Half_Bit_Delay(void);
void     I2C_Bit_Delay(void);

void     I2C_SCL_Set_DD(uint8_t state);
void     I2C_SCL_Set_Output(uint8_t state);
uint8_t  I2C_SCL_Get_State(void);

void     I2C_SDA_Set_DD(uint8_t state);
void     I2C_SDA_Set_Output_LL(uint8_t state);
void     I2C_SDA_Set_Output(uint8_t state);
uint8_t  I2C_SDA_Get_State(void);

void     I2C_SCL_Reset_State(void);
void     I2C_SDA_Reset_State(void);
void     I2C_GPIO_Init(void);

void     I2C_Start(void);
void     I2C_Stop(void);
void     I2C_Data(uint8_t data);

