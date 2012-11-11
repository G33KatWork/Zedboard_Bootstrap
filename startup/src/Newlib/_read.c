#include <Drivers/uart.h>

int _read(int fd, char* buf, int nbytes)
{
	(void)fd;

	int i;
	for(i = 0; i < nbytes; i++)
	{
		*(buf+i) = UartReceiveByte(UART1);

		if(*(buf+i) == '\n' || *(buf+i) == '\r')
			break;
	}

	return i+1;
}
