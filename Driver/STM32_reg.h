#ifndef STM32_REG_H
#define STM32_REG_H

#define PERIPHERAL_BASE 0x40000000UL
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000UL)
#define GPIOA_BASE (AHB1_BASE + 0x0000UL)
#define RCC_BASE (AHB1_BASE + 0x3800UL)
#define SYSTICK_BASE   0xE000E010UL
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef long unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef signed char       int8_t;
typedef signed short      int16_t;
typedef long signed int         int32_t;
typedef signed long long  int64_t;
typedef struct 
{
    volatile uint32_t MODER;   // GPIO port mode register
    volatile uint32_t OTYPER;  // GPIO port output type register
    volatile uint32_t OSPEEDR; // GPIO port output speed register
    volatile uint32_t PUPDR;   // GPIO port pull-up/pull-down register
    volatile uint32_t IDR;     // GPIO port input data register
    volatile uint32_t ODR;     // GPIO port output data register
    volatile uint32_t BSRR;    // GPIO port bit set/reset register
    volatile uint32_t LCKR;    // GPIO port configuration lock register
    volatile uint32_t AFR[2];  // GPIO alternate function registers
} GPIO_typedef;
typedef struct RCC
{
    volatile uint32_t CR;       // RCC clock control register
    volatile uint32_t PLLCFGR;  // RCC PLL configuration register
    volatile uint32_t CFGR;     // RCC clock configuration register
    volatile uint32_t CIR;      // RCC clock interrupt
    volatile uint32_t AHB1RSTR; // RCC AHB1 peripheral reset register
    volatile uint32_t AHB1ENR;  // RCC AHB1 peripheral clock enable register
    volatile uint32_t APB2ENR;  // RCC APB2 peripheral clock enable register
} RCC_typedef;
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_TypeDef;
#define GPIOA ((GPIO_typedef *) GPIOA_BASE)
#define RCC ((RCC_typedef *) RCC_BASE)
#define RCC_AHB1ENR_GPIOAEN   (1 << 0)
#define RCC_APB2ENR_UART1EN   (1 << 4)
#endif
