#ifndef _UART_H_
#define _UART_H_

#include <stdbool.h>

#include <Drivers/uart_hw.h>

void UartInitialize(UART_Registers* uart, uint32_t baudrate);
void UartSetBaudrate(UART_Registers* uart, uint32_t baudrate);
void UartEnable(UART_Registers* uart);
void UartDisable(UART_Registers* uart);

static inline bool UartIsDataReceived(UART_Registers* uart)
{
	return !((uart->SR & UART_SR_RXEMPTY) == UART_SR_RXEMPTY);
}

static inline bool UartIsTransmitFifoFull(UART_Registers* uart)
{
	return (uart->SR & UART_SR_TXFULL) == UART_SR_TXFULL;
}

static inline void UartSendByte(UART_Registers* uart, uint8_t data)
{
	while(UartIsTransmitFifoFull(uart));
	uart->FIFO = data;
}

static inline uint8_t UartReceiveByte(UART_Registers* uart)
{
	while(!UartIsDataReceived(uart));
	return uart->FIFO;
}

#endif
