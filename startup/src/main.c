#include <stdlib.h>
#include <stdio.h>

#include <Drivers/io.h>
#include <Drivers/gpio.h>
#include <Drivers/uart.h>
#include <Drivers/private_timer.h>
#include <Drivers/cpu.h>
#include <Drivers/gic.h>

#include <ps7_init.h>

struct cpu_state* TimerHandler(struct cpu_state* state)
{
	printf("Tick\n");
	PrivateTimerClearExpiration(PRIVATE_TIMER);
	GICAcknowledgeInterrupt(29);
	return state;
}

int main(int argc, char* agrv[]) {
	//initialize DDR and MMIO
	ps7_init();

	//Switch pin 7 to output
	GPIO->DIRECTION_0 = GPIO->DIRECTION_0 | (1 << 7);

	//Set pin 7 to on
	GPIO->MASK_DATA_LSW_0 = ((~(1<<7)) << 16) | (1 << 7);

	//disable stdout buffering
	setvbuf(stdout, 0, _IONBF, 0);

	UartInitialize(UART1, 115200);
	printf("Initialized\n");

	unsigned int id = CPUGetCoreNumber();
	printf("Running on CPU %X\n", id);

	GICInit();
	printf("GIC Initialized\n");

	GICUnmaskInterrupt(29);
	GICConnectInterrupt(29, TimerHandler);

	PrivateTimerStop(PRIVATE_TIMER);
	PrivateTimerSetPrescaler(PRIVATE_TIMER, 255);
	PrivateTimerLoad(PRIVATE_TIMER, 1302083);
	PrivateTimerEnableAutoReload(PRIVATE_TIMER, 1302083);
	PrivateTimerEnableInterrupt(PRIVATE_TIMER);
	PrivateTimerClearExpiration(PRIVATE_TIMER);
	PrivateTimerStart(PRIVATE_TIMER);

	//enable interrupts
	CPUEnableInterrupts();
	//CPUEnableFastInterrupts();

	//uint32_t foo = 0;

	while(1)
	{
		/*if(PrivateTimerIsExpired(PRIVATE_TIMER))
		{
			foo++;
			PrivateTimerClearExpiration(PRIVATE_TIMER);
		}

		if(foo % 10000 == 0)
			printf("A");*/
			
		//uint8_t foo = UartReceiveByte(UART1);
		//UartSendByte(UART1, foo);
	}

	//int* foo = malloc(0x20);
	return 0;
}
