#ifndef _PRIVATE_TIMER_H_
#define _PRIVATE_TIMER_H_

#include <Drivers/private_timer_hw.h>
#include <stdbool.h>

static inline void PrivateTimerStart(PrivateTimer_Registers* timer)
{
	timer->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;
}

static inline void PrivateTimerStop(PrivateTimer_Registers* timer)
{
	timer->CONTROL &= ~PRIVATE_TIMER_CONTROL_ENABLE_MASK;
}

static inline void PrivateTimerLoad(PrivateTimer_Registers* timer, uint32_t value)
{
	timer->COUNTER = value;
}

static inline uint32_t PrivateTimerGetCounterValue(PrivateTimer_Registers* timer)
{
	return timer->COUNTER;
}

static inline void PrivateTimerEnableAutoReload(PrivateTimer_Registers* timer, uint32_t reloadValue)
{
	timer->LOAD = reloadValue;
	timer->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;
}

static inline void PrivateTimerDisableAutoReload(PrivateTimer_Registers* timer)
{
	timer->CONTROL &= ~PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;
}

static inline void PrivateTimerEnableInterrupt(PrivateTimer_Registers* timer)
{
	timer->CONTROL |= PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK;
}

static inline void PrivateTimerDisableInterrupt(PrivateTimer_Registers* timer)
{
	timer->CONTROL &= ~PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK;
}

static inline void PrivateTimerSetPrescaler(PrivateTimer_Registers* timer, uint8_t prescaler)
{
	uint32_t ctrl = timer->CONTROL;
	ctrl &= ~PRIVATE_TIMER_CONTROL_PRESCALER_MASK;
	ctrl |= (prescaler << PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT);
	timer->CONTROL = ctrl;
}

static inline uint8_t PrivateTimerGetPrescaler(PrivateTimer_Registers* timer)
{
	return (timer->CONTROL & PRIVATE_TIMER_CONTROL_PRESCALER_MASK) >> PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT;
}

static inline bool PrivateTimerIsExpired(PrivateTimer_Registers* timer)
{
	return (timer->ISR & PRIVATE_TIMER_ISR_EVENT_FLAG_MASK) == PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;
}

static inline void PrivateTimerClearExpiration(PrivateTimer_Registers* timer)
{
	timer->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;
}

#endif
