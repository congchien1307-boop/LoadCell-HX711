#include "STM32_reg.h"
#include "GPIO.h"
// set up HX711 pins 
void GPIOA_HX711_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
    // Set GPIOA pin 0 as output
    GPIOA->MODER |= ~(0x3 << (HX711_DP_SCK_PIN * 2));
    // Set GPIOA pin 1 as input
    GPIOA->MODER &= ~(0x3 << (HX711_DT_PIN * 2));
    GPIOA->MODER |= (0x1 << (HX711_DT_PIN * 2));
    GPIOA->OTYPER |= ~(0x1 << HX711_DP_SCK_PIN); // Set GPIOA pin 1 as push-pull
    GPIOA->OSPEEDR |= (0x3 << (HX711_DP_SCK_PIN * 2)); // High speed
    GPIOA->PUPDR &= ~(0x3 << (HX711_DT_PIN * 2)); // No pull-up, no pull-down
} 
void GPIOA_HX711_SCK_LOW(void)
{ 
    GPIOA->BSRR |= (1 << HX711_DP_SCK_PIN); // Set GPIOA pin 1 LOW
}
void GPIOA_HX711_SCK_HIGH(void)
{ 
    GPIOA->BSRR |= (1 << (HX711_DP_SCK_PIN + 16)); // Set GPIOA pin 1 HIGH
}
int8_t GPIOA_HX711_DT_Read(void)
{
return (GPIOA->IDR & (1 << HX711_DT_PIN)) ? 1 : 0; // Read GPIOA pin 0, DT_pin
}
void GPIO_UART_Init(void){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;      // Enable GPIOA clock, PA2 is TX, PA3 is RX
    GPIOA->MODER &= ~((3 << 2*2) | (3 << 2*3)); // Clear mode bits for PA2 and PA3
    GPIOA->MODER |= ((2<< 2*2) | (2 << 2*3)); // Set PA3 to alternate function mode
    GPIOA->OSPEEDR |= ((2 << 2*2) | (2 << 2*3)); // Set PA2 and PA3 to high speed
    GPIOA->AFR[0] &= ~((0xF << 4*2) | (0xF << 4*3)); // Clear alternate function for PA2 and PA3
    GPIOA->AFR[0] |= (7 << 4*2) | (7 << 4*3); // Set alternate function to AF7 (USART2) for PA2 and PA3
}

    