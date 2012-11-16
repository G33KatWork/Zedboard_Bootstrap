#ifndef _CPU_H_
#define _CPU_H_

static inline unsigned int CPUGetCoreNumber()
{
	unsigned int id;
	asm volatile("mrc p15, 0, %0, c0, c0, 5" : "=r" (id));
	return id & 0x3;
}

static inline void CPUEnableInterrupts()
{
	__asm__ __volatile__ ("mrs r0,cpsr;"
							"bic r0,#0x80;"
							"msr cpsr_ctl,r0" ::: "r0");
}

static inline void CPUDisableInterrupts()
{
	__asm__ __volatile__ ("mrs r0,cpsr;"
							"orr r0,r0,#0x80;"
							"msr cpsr_ctl,r0" ::: "r0");
}

static inline void CPUEnableFastInterrupts()
{
	__asm__ __volatile__ ("mrs r0,cpsr;"
							"bic r0,#0x40;"
							"msr cpsr_ctl,r0" ::: "r0");
}

static inline void CPUDisableFastInterrupts()
{
	__asm__ __volatile__ ("mrs r0,cpsr;"
							"orr r0,r0,#0x40;"
							"msr cpsr_ctl,r0" ::: "r0");
}

#endif
