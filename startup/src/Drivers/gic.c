#include <Drivers/gic.h>
#include <Drivers/cpu.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	GIC_DIST_Registers* distributor;
	GIC_CPU_Registers* cpu;
	uint32_t numIrqs;
	InterruptHandler* handler;
} GIC;

static GIC gic;

static void GICDistributorInit(GIC* gic);
static void GICCPUInit(GIC* gic);

void GICInit()
{
	gic.distributor = (GIC_DIST_Registers*)0xF8F01000;
	gic.cpu = (GIC_CPU_Registers*)0xF8F00100;

	//initialize the distributor
	GICDistributorInit(&gic);

	//initialize the first CPU
	GICCPUInit(&gic);

	gic.handler = malloc(gic.numIrqs * sizeof(InterruptHandler));
	memset(gic.handler, 0, gic.numIrqs * sizeof(InterruptHandler));
}

void GICConnectInterrupt(uint32_t interruptId, InterruptHandler handler)
{
	if(interruptId > gic.numIrqs)
		return;

	gic.handler[interruptId] = handler;
}

static void GICDistributorInit(GIC* gic)
{
	//disable the distributor
	gic->distributor->CTRL = 0;

	uint16_t numIrqs = gic->distributor->TYPE & GIC_DIST_NUM_INT_MASK;
	gic->numIrqs = (numIrqs + 1) * 32;

	//configure all SPIs level triggered, active low
	for(uint16_t i = 32; i < numIrqs; i += 16)
		gic->distributor->INTERRUPT_CONFIG[i/16] = 0;

	//configure all SPIs to be sent to this CPU only
	uint32_t cpumask = 1 << CPUGetCoreNumber();
	cpumask |= cpumask << 8;
	cpumask |= cpumask << 16;

	for(uint16_t i = 32; i < numIrqs; i += 4)
		gic->distributor->INTERRUPT_CONFIG[i/4] = cpumask;

	//set lowest priority for all SPIs
	for(uint16_t i = 32; i < numIrqs; i += 4)
		gic->distributor->PRIORITY[i/4] = 0xA0A0A0A0;

	//disable all SPIs
	for(uint16_t i = 32; i < numIrqs; i += 32)
		gic->distributor->DISABLE[i/32] = 0xFFFFFFFF;

	//reenable the distributor
	gic->distributor->CTRL = 1;
}

static void GICCPUInit(GIC* gic)
{
	//disable all PPI interrupts, enable all SGI interrupts
	gic->distributor->DISABLE[0] = 0xFFFF0000;
	gic->distributor->ENABLE[0] = 0x0000FFFF;

	//set lowest priority for PPIs and SGIs
	for(uint16_t i = 0; i < 32; i += 4)
		gic->distributor->PRIORITY[i/4] = 0xA0A0A0A0;

	gic->cpu->PRIMASK = 0xF0;	//set priority mask for CPU interface
	gic->cpu->CTRL = 1;			//enable CPU interface, or with 8 if interrupts should be delivered as FIQ
}

void GICMaskInterrupt(uint32_t interruptId)
{
	uint32_t mask = 1 << (interruptId % 32);
	gic.distributor->DISABLE[interruptId/32] = mask;
}

void GICUnmaskInterrupt(uint32_t interruptId)
{
	uint32_t mask = 1 << (interruptId % 32);
	gic.distributor->ENABLE[interruptId/32] = mask;
}

void GICAcknowledgeInterrupt(uint32_t interruptId)
{
	gic.cpu->EOI = interruptId;
}

void GICSetInterruptType(uint32_t interruptId, int type)
{
	if(type != GIC_INTERRUPT_TYPE_LEVEL_HIGH && type != GIC_INTERRUPT_TYPE_EDGE_RISING)
		return;

	//SGIs and PPIs are not changeable
	if(interruptId < 32)
		return;

	bool wasEnabled = false;

	uint32_t enablemask = 1 << (interruptId % 32);
	uint32_t enableoffset = interruptId/32;
	uint32_t confoffset = interruptId/16;
	uint32_t confmask = 0x2 << ((interruptId % 16)*2);

	//disable interrupt if enabled
	if(gic.distributor->ENABLE[enableoffset] & enablemask)
	{
		gic.distributor->DISABLE[enableoffset] = enablemask;
		wasEnabled = true;
	}

	uint32_t config = gic.distributor->INTERRUPT_CONFIG[confoffset];
	
	if(type == GIC_INTERRUPT_TYPE_LEVEL_HIGH)
		config &= ~confmask;
	else if(type == GIC_INTERRUPT_TYPE_EDGE_RISING)
		config |= confmask;

	gic.distributor->INTERRUPT_CONFIG[confoffset] = config;

	//reenable interrupt
	if(wasEnabled)
		gic.distributor->ENABLE[enableoffset] = enablemask;
}

void GICSetInterruptAffinity(uint32_t interruptId, int mask)
{
	//TODO: implement me
}

struct cpu_state* GICHandleIRQ(struct cpu_state* state)
{
	//get and ack interrupt
	uint32_t intnum = gic.cpu->INTACK & 0x3FF;

	gic.distributor->CLEARPENDING[intnum/32] = (1 << (intnum % 32));

	if(intnum > gic.numIrqs)
		return state;

	if(gic.handler[intnum] != NULL)
		return gic.handler[intnum](state);
	else
		return state;
}
