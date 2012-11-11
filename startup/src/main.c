#include <stdlib.h>
#include <stdio.h>

#include <Drivers/io.h>
#include <Drivers/gpio.h>
#include <Drivers/uart.h>

#include <ps7_init.h>

int main(int argc, char* agrv[]) {
	//TODO: enable caches
	//Enable VFP/NEON
	//TODO: systick?

	ps7_init();

	//Switch pin 7 to output
	GPIO->DIRECTION_0 = GPIO->DIRECTION_0 | (1 << 7);

	//Set pin 7 to on
	GPIO->MASK_DATA_LSW_0 = ((~(1<<7)) << 16) | (1 << 7);


	UartInitialize(UART1, 115200);
	printf("Initialized\n");

	while(1)
	{
		uint8_t foo = UartReceiveByte(UART1);
		UartSendByte(UART1, foo);
	}

	//int* foo = malloc(0x20);
	return 0;
}
