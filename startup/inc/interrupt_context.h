#ifndef _INTERRUPT_CONTEXT_H_
#define _INTERRUPT_CONTEXT_H_

#include <inttypes.h>
#include <stdio.h>

struct cpu_state
{
    // r13 und r14 des Usermodes
    uint32_t usr_r13, usr_r14;
    // CPSR vor dem IRQ und SPSR des Supervisormodes
    uint32_t cpsr, svc_spsr;
    // r13 und r14 des Supervisormodes
    uint32_t svc_r13, svc_r14;
    // r0 bis r12 sowie r15
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
    uint32_t r8, r9, r10, r11, r12, r15;
} __attribute__((packed));

static inline void printState(struct cpu_state* state)
{
	printf(
		"usr_r13:\t0x%"PRIx32"\n"
		"usr_r14:\t0x%"PRIx32"\n"
		"cpsr:\t\t0x%"PRIx32"\n"
		"svc_spsr:\t0x%"PRIx32"\n"
		"svc_r13:\t0x%"PRIx32"\n"
		"svc_r14:\t0x%"PRIx32"\n"
		"r0:\t\t0x%"PRIx32"\n"
		"r1:\t\t0x%"PRIx32"\n"
		"r2:\t\t0x%"PRIx32"\n"
		"r3:\t\t0x%"PRIx32"\n"
		"r4:\t\t0x%"PRIx32"\n"
		"r5:\t\t0x%"PRIx32"\n"
		"r6:\t\t0x%"PRIx32"\n"
		"r7:\t\t0x%"PRIx32"\n"
		"r8:\t\t0x%"PRIx32"\n"
		"r9:\t\t0x%"PRIx32"\n"
		"r10:\t\t0x%"PRIx32"\n"
		"r11:\t\t0x%"PRIx32"\n"
		"r12:\t\t0x%"PRIx32"\n"
		"r15:\t\t0x%"PRIx32"\n",
		state->usr_r13, state->usr_r14,
		state->cpsr, state->svc_spsr,
		state->svc_r13, state->svc_r14,
		state->r0, state->r1, state->r2,
		state->r3, state->r4, state->r5,
		state->r6, state->r7, state->r8,
		state->r9, state->r10, state->r11,
		state->r12, state->r15
	);
}

#endif
