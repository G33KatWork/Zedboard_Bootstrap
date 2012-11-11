#ifndef _IO_H_
#define _IO_H_

#include <stdint.h>
#include <pseudo_asm.h>

/* IO definitions for registers */
#ifdef __cplusplus
  #define   __I     volatile
#else
  #define   __I     volatile const
#endif
#define     __O     volatile
#define     __IO    volatile

#define SYNCHRONIZE_IO	dmb()
#define INST_SYNC		isb()
#define DATA_SYNC		dsb()

uint8_t  io_in8(uint32_t Addr);
uint16_t io_in16(uint32_t Addr);
uint32_t io_in32(uint32_t Addr);

void io_out8(uint32_t Addr, uint8_t Value);
void io_out16(uint32_t Addr, uint16_t Value);
void io_out32(uint32_t Addr, uint32_t Value);

#endif
