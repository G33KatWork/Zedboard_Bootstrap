#include <Drivers/uart.h>

int _write(int fd, char* buf, int nbytes)
{
	(void)fd;

	for(int i = 0; i < nbytes; i++)
	{
		if(*(buf+i) == '\n')
			UartSendByte(UART1, '\r');

		UartSendByte(UART1, *(buf+i));
	}

	return nbytes;
}
