#include "STM32_reg.h"
#define HX711_DT_PIN 0
#define HX711_DP_SCK_PIN 1
// set up HX711 pins 
void HX711_Init(void)
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
void HX711_SCK_LOW(void)
{ 
    GPIOA->BSRR |= (1 << HX711_DP_SCK_PIN); // Set GPIOA pin 1 LOW
}
void HX711_SCK_HIGH(void)
{ 
    GPIOA->BSRR |= (1 << (HX711_DP_SCK_PIN + 16)); // Set GPIOA pin 1 HIGH
}
void HX711_DT_Read(void)
{
return (GPIOA->IDR & (1 << HX711_DT_PIN)) ? 1 : 0; // Read GPIOA pin 0, DT_pin
}

    