#include "UART.h"

void Nextion_sendendcmd(void)
{
    UART_SendByte(UART1, 0xFF);
    UART_SendByte(UART1, 0xFF);
    UART_SendByte(UART1, 0xFF);
}

void Nextion_sendcmd(const char *cmd)
{
    UART_SendString(UART1, cmd);
    Nextion_sendendcmd();
}

void Nextion_settext(const char *obj, const char *text)
{
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "%s.txt=\"%s\"", obj, text);
    Nextion_sendcmd(cmd);
}

void Nextion_setvalue(const char *obj, int32_t value)
{
    UART_SendString(UART1, obj);
    UART_SendString(UART1, ".val=");
    UART_SendNumber(UART1, value);
    Nextion_sendendcmd();
}
void Nextion_sendweight(const char *obj, float weight)
{
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "%s.txt=\"%.2f\"", obj, weight);
    Nextion_sendcmd(cmd);
}