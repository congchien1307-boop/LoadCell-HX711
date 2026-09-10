#include "STM32_reg.h"
#include "UART.h"
// set the baud rate for the UART peripheral
void UART_SetBaudRate(UART_TypeDef *UARTx, uint32_t baudrate, uint32_t pclk){
    uint32_t uartdiv = (pclk + (baudrate/2)) / baudrate; // Calculate UARTDIV
    UARTx->BRR = uartdiv; // Set the baud rate register
}
// enable the UART peripheral, transmitter, and receiver
void UART_Enable(UART_TypeDef *UARTx ){
    RCC->APB2ENR |= RCC_APB2ENR_UART1EN; // Enable USART1 clock
    GPIOA_UART_Init(); // Initialize GPIO pins for UART
    UARTx->CR1 |= UART_CR1_TE; // Enable transmitter
    UARTx->CR1 |= UART_CR1_RE; // Enable receiver
    UARTx->CR1 |= UART_CR1_UE; // Enable USART
}
// send a single byte of data over UART
void UART_SendByte(UART_TypeDef *UARTx, uint32_t data){
    while (!(UARTx->SR & UART_SR_TXE)); // Wait until transmit data register is empty
    UARTx->DR = data; // Write data to the data register
}
void UART_SendString(UART_TypeDef *UARTx, const char *str){
    while (*str){
        UART_SendByte(UARTx, (uint8_t)(*str)); // Send each character in the string
        str++;
    }
}
void UART_SendNumber(UART_TypeDef *UARTx, int32_t num){
    char buffer[12]; // Buffer to hold the string representation of the number
    int i = 0;
    if (num < 0){
        UART_SendByte(UARTx, '-'); // Send negative sign for negative numbers
        num = -num; // Make the number positive
    }
    if (num == 0){
        UART_SendByte(UARTx, '0'); // Send '0' if the number is zero
        return;
    }
    while (num > 0){
        buffer[i++] = (num % 10) + '0'; // Convert each digit to character
        num /= 10; // Remove the last digit
    }
    for (int j = i - 1; j >= 0; j--){
        UART_SendByte(UARTx, buffer[j]); // Send the digits in reverse order
    }
}
