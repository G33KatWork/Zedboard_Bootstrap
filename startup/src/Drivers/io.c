#include <Drivers/io.h>

uint8_t io_in8(uint32_t Addr)
{
	SYNCHRONIZE_IO;
	return *(volatile uint8_t*)Addr;
}

uint16_t io_in16(uint32_t Addr)
{
	SYNCHRONIZE_IO;
	return *(volatile uint16_t*)Addr;
}

uint32_t io_in32(uint32_t Addr)
{
	SYNCHRONIZE_IO;
	return *(volatile uint32_t*)Addr;
}

void io_out8(uint32_t Addr, uint8_t Value)
{
	*(volatile uint8_t*) Addr = Value;
	SYNCHRONIZE_IO;
}

void io_out16(uint32_t Addr, uint16_t Value)
{
	*(volatile uint16_t*) Addr = Value;
	SYNCHRONIZE_IO;
}

void io_out32(uint32_t Addr, uint32_t Value)
{
	*(volatile uint32_t*) Addr = Value;
	SYNCHRONIZE_IO;
}
