#include <stdio.h>
#include <interrupt_context.h>
#include <Drivers/gic.h>

void FIQInterrupt(void)
{
	printf("FIQInterrupt\n");
	while(1);
}

struct cpu_state* IRQInterrupt(struct cpu_state* state)
{
	// printf("IRQInterrupt\n");
	// printState(state);

	return GICHandleIRQ(state);
}

void SWInterrupt(void)
{
	printf("SWInterrupt\n");
	while(1);
}

void DataAbortInterrupt(void)
{
	printf("DataAbortInterrupt\n");
	while(1);
}

void PrefetchAbortInterrupt(void)
{	
	printf("PrefetchAbortInterrupt\n");
	while(1);
}
