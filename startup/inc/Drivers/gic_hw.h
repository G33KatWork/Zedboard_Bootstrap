#ifndef _GIC_HW_H_
#define _GIC_HW_H_

#include <stdint.h>
#include <Drivers/io.h>

//Interrupt sources:
//SGI: Software generated interrupt - 0-16
//PPI: Private peripheral interrupt
//5 PPI Sources:
//	Legacy nFIQ-Pin: ID 28
//	Private timer: ID 29
//	Watchdog timer: ID 30
//	Legacy nIRQ-Pin: ID 31
//	Global timter: ID 27
//SPI: Shared peripheral interrupt
//	Starting at ID 32

typedef struct
{
	__IO uint32_t CTRL;
	__IO uint32_t PRIMASK;
	__IO uint32_t BINPOINT;
	__IO uint32_t INTACK;
	__IO uint32_t EOI;
	__IO uint32_t RUNNINGPRI;
	__IO uint32_t HIGHPRI;
} GIC_CPU_Registers;

typedef struct
{
	__IO uint32_t CTRL;
	__IO uint32_t TYPE;
	__IO uint32_t IDENTIFICATION;
	__IO uint32_t RESERVED1[0x1D];
	__IO uint32_t SECURITY[3];		/* first element is banked */
	__IO uint32_t RESERVED2[0x1D];
	__IO uint32_t ENABLE[3];		/* first element is banked */
	__IO uint32_t RESERVED3[0x1D];
	__IO uint32_t DISABLE[3];		/* first element is banked */
	__IO uint32_t RESERVED4[0x1D];
	__IO uint32_t SETPENDING[3];	/* first element is banked */
	__IO uint32_t RESERVED5[0x1D];
	__IO uint32_t CLEARPENDING[3];	/* first element is banked */
	__IO uint32_t RESERVED6[0x1D];
	__IO uint32_t ACTIVE[3];		/* first element is banked */
	__IO uint32_t RESERVED7[0x3D];
	__IO uint32_t PRIORITY[24];		/* element 0-7 is banked */
	__IO uint32_t RESERVED8[0xC0];
	__IO uint32_t PROCESSOR_TARGET[24];	/* element 0-7 is banked and read-only */
	__IO uint32_t RESERVED9[0xE8];
	__IO uint32_t INTERRUPT_CONFIG[6];	/* element 0 is read-only, all banked */
} GIC_DIST_Registers;


/* TYPE Register values */
#define GIC_DIST_LSPI_MASK		0x0000F800 /**< Number of Lockable Shared Peripheral Interrupts*/
#define GIC_DIST_DOMAIN_MASK	0x00000400 /**< Number os Security domains*/
#define GIC_DIST_CPU_NUM_MASK	0x000000E0 /**< Number of CPU Interfaces */
#define GIC_DIST_NUM_INT_MASK	0x0000001F /**< Number of Interrupt IDs */

#endif
