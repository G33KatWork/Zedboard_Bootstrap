#ifndef _GIC_H_
#define _GIC_H_

#include <Drivers/gic_hw.h>
#include <interrupt_context.h>

#define GIC_INTERRUPT_TYPE_LEVEL_HIGH	0x1
#define GIC_INTERRUPT_TYPE_EDGE_RISING	0x2

typedef struct cpu_state*(*InterruptHandler)(struct cpu_state*);

void GICInit(void);

void GICConnectInterrupt(uint32_t interruptId, InterruptHandler handler);

void GICMaskInterrupt(uint32_t interruptId);
void GICUnmaskInterrupt(uint32_t interruptId);
void GICAcknowledgeInterrupt(uint32_t interruptId);

//edge, level, etc.
void GICSetInterruptType(uint32_t interruptId, int type);
void GICSetInterruptAffinity(uint32_t interruptId, int mask);

//TODO: struct with registers as parameter
struct cpu_state* GICHandleIRQ(struct cpu_state* state);

#endif
