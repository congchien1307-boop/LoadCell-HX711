#define HX711_DT_PIN 0
#define HX711_DP_SCK_PIN 1

void GPIOA_HX711_Init(void);
void GPIOA_HX711_SCK_LOW(void);
void GPIOA_HX711_SCK_HIGH(void);
int8_t GPIOA_HX711_DT_Read(void);
void GPIO_UART_Init(void);
