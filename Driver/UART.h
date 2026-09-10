#ifndef UART_H
#define UART_H
#include "STM32_reg.h"
#define UART1_ADDRESS_BASE 0x40011000
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} UART_TypeDef;

#define UART_SR_TXE (1 << 7) // Transmit data register empty
#define UART_SR_TC (1 << 6)  // Transmission complete
#define UART_SR_RXNE (1 << 5) // Received data ready to be read
#define UART_CR1_UE (1 << 13) // USART enable
#define UART_CR1_TE (1 << 3) // Transmitter enable
#define UART_CR1_RE (1 << 2) // Receiver enable
#define UART1 ((UART_TypeDef *)UART1_ADDRESS_BASE)

void UART_SetBaudRate(UART_TypeDef *UARTx, uint32_t baudrate, uint32_t pclk);
void UART_Enable(UART_TypeDef *UARTx );
void UART_SendByte(UART_TypeDef *UARTx, uint32_t data);
void UART_SendString(UART_TypeDef *UARTx, const char *str);
void UART_SendNumber(UART_TypeDef *UARTx, int32_t num);

#endif // UART_H