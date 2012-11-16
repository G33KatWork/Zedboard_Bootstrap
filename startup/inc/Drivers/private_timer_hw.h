#ifndef _PRIVATE_TIMER_HW_H_
#define _PRIVATE_TIMER_HW_H_

#include <stdint.h>
#include <Drivers/io.h>

typedef struct
{
	__IO uint32_t LOAD;
	__IO uint32_t COUNTER;
	__IO uint32_t CONTROL;
	__IO uint32_t ISR;
} PrivateTimer_Registers;


/* Values for control register */
#define PRIVATE_TIMER_CONTROL_PRESCALER_MASK	0x0000FF00
#define PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT	8
#define PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK	0x00000004
#define PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK	0x00000002
#define PRIVATE_TIMER_CONTROL_ENABLE_MASK		0x00000001

/* Values for ISR register */
#define PRIVATE_TIMER_ISR_EVENT_FLAG_MASK		0x00000001


#define PRIVATE_TIMER_BASE			0xF8F00600
#define PRIVATE_TIMER				((PrivateTimer_Registers*)PRIVATE_TIMER_BASE)

#endif
