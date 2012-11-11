#include <Drivers/uart.h>

//for frequencies
#include <ps7_init.h>

void UartInitialize(UART_Registers* uart, uint32_t baudrate)
{
	UartSetBaudrate(uart, baudrate);

	uint32_t modeRegister = uart->MR;
	modeRegister &= ~(UART_MR_CHARLEN_MASK |
					 UART_MR_STOPMODE_MASK |
					 UART_MR_PARITY_MASK);
	modeRegister |= (UART_MR_CHARLEN_8_BIT |
					UART_MR_STOPMODE_1_BIT |
					UART_MR_PARITY_NONE);
	uart->MR = modeRegister;

	//set tx fifo trigger level to 8
	uart->TXWM = 8;

	//disable all interrupts
	uart->IDR = UART_IXR_MASK;
}

void UartSetBaudrate(UART_Registers* uart, uint32_t baudrate)
{
	uint32_t uartInputClock = UART_FREQ;
	//uint32_t uartMaxErrorRate = 3;

	uint32_t uartBGGR = 0;
	uint32_t uartResultingBaudrate = 0;
	uint32_t uartBaudError = 0;

	uint32_t uartBestError = 0xFFFFFFFF;
	uint32_t uartBestBGGR = 0;
	uint32_t uartBestDivider = 0;

	//check if input clock is divided by 8
	if(uart->MR & UART_MR_CLKSEL)
		uartInputClock /= 8;

	for(uint8_t uartBaudrateDivider = 3; uartBaudrateDivider < 255; uartBaudrateDivider++)
	{
		uartBGGR = uartInputClock / (baudrate * (uartBaudrateDivider + 1));
		uartResultingBaudrate = uartInputClock / (uartBGGR * (uartBaudrateDivider + 1));

		if(baudrate > uartResultingBaudrate)
			uartBaudError = baudrate - uartResultingBaudrate;
		else
			uartBaudError = uartResultingBaudrate - baudrate;

		if(uartBestError > uartBaudError)
		{
			uartBestBGGR = uartBGGR;
			uartBestDivider = uartBaudrateDivider;
			uartBestError = uartBaudError;
		}
	}

	//TODO: check if error is too big and bail

	//disable uart
	UartDisable(uart);

	uart->BAUDGEN = uartBestBGGR;
	uart->BAUDDIV = uartBestDivider;

	//reenable uart
	UartEnable(uart);
}

void UartEnable(UART_Registers* uart)
{
	uint32_t tmp = uart->CR;
	tmp &= ~UART_CR_EN_DIS_MASK;
	tmp |= (UART_CR_TX_EN | UART_CR_RX_EN);
	uart->CR = tmp;
}

void UartDisable(UART_Registers* uart)
{
	uint32_t tmp = uart->CR;
	tmp &= ~UART_CR_EN_DIS_MASK;
	tmp |= (UART_CR_TX_DIS | UART_CR_RX_DIS);
	uart->CR = tmp;
}
