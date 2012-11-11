#include <stdio.h>

void FIQInterrupt(void)
{
	printf("FIQInterrupt\n");
	while(1);
}

void IRQInterrupt(void)
{
	printf("IRQInterrupt\n");
	while(1);
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
