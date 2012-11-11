.global ResetHandler

.global main
.global memset
.global atexit
.global exit
.global __libc_init_array
.global __libc_fini_array
.global MMUTable

.global __stack
.global __irq_stack
.global __supervisor_stack
.global __abort_stack

.set Abort_stack,	__abort_stack
.set SPV_stack,		__supervisor_stack
.set IRQ_stack,		__irq_stack
.set SYS_stack,		__stack

.set BSS_Start,		__bss_start__
.set BSS_End,		__bss_end__
.set TblBase,		MMUTable

.set PSS_L2CC_BASE_ADDR, 0xF8F02000
.set L2CCWay,		(PSS_L2CC_BASE_ADDR + 0x077C)	/*(PSS_L2CC_BASE_ADDR + PSS_L2CC_CACHE_INVLD_WAY_OFFSET)*/
.set L2CCSync,		(PSS_L2CC_BASE_ADDR + 0x0730)	/*(PSS_L2CC_BASE_ADDR + PSS_L2CC_CACHE_SYNC_OFFSET)*/
.set L2CCCrtl,		(PSS_L2CC_BASE_ADDR + 0x0100)	/*(PSS_L2CC_BASE_ADDR + PSS_L2CC_CNTRL_OFFSET)*/
.set L2CCAuxCrtl,	(PSS_L2CC_BASE_ADDR + 0x0104)	/*(PSS_L2CC_BASE_ADDR + XPSS_L2CC_AUX_CNTRL_OFFSET)*/
.set L2CCTAGLatReg,	(PSS_L2CC_BASE_ADDR + 0x0108)	/*(PSS_L2CC_BASE_ADDR + XPSS_L2CC_TAG_RAM_CNTRL_OFFSET)*/
.set L2CCDataLatReg,	(PSS_L2CC_BASE_ADDR + 0x010C)	/*(PSS_L2CC_BASE_ADDR + XPSS_L2CC_DATA_RAM_CNTRL_OFFSET)*/
.set L2CCIntClear,	(PSS_L2CC_BASE_ADDR + 0x0220)	/*(PSS_L2CC_BASE_ADDR + XPSS_L2CC_IAR_OFFSET)*/
.set L2CCIntRaw,	(PSS_L2CC_BASE_ADDR + 0x021C)	/*(PSS_L2CC_BASE_ADDR + XPSS_L2CC_ISR_OFFSET)*/


.set CRValMmuCac,		0b01000000000101			/* Enable IDC, and MMU */
.set L2CCAuxControl,	0x72360000					/* Enable all prefetching, Cache replacement policy, Parity enable, 
													   Event monitor bus enable and Way Size (64 KB) */
.set L2CCControl,		0x01						/* Enable L2CC */
.set L2CCTAGLatency,	0x0111						/* latency for TAG RAM */
.set L2CCDataLatency,	0x0121						/* latency for DATA RAM */
.set FPEXC_EN,			0x40000000					/* FPU enable bit, (1 << 30) */


ResetHandler:
	/* Setup caches */
	/* Set SCU enable bit - this enables cache coherency between the two cores */
	ldr	r7, =0xF8F00000
	ldr	r0, [r7]
	orr	r0, r0, #0x01
	str	r0, [r7]

	/* invalidate SCU */
	ldr	r7, =0xF8F0000C
	ldr	r6, =0xFFFF
	str	r6, [r7]

	/* Set SMP bit in ACTLR - enables cache coherency in the cores */
	/* http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0388e/CIHIHFCG.html */
	mrc	p15, 0, r0, c1, c0, 1	/* Read ACTLR */
	orr	r0, r0, #(0x01 << 6)	/* set SMP bit */
	orr	r0, r0, #(0x01)			/* set FW bit */
	mcr	p15, 0, r0, c1, c0, 1	/* Write ACTLR */

	/* invalidate caches and TLB */
	mov	r0, #0
	mcr	p15, 0, r0, c8, c7, 0x0		/* invalidate TLBs */
	mcr	p15, 0, r0, c7, c5, 0x0		/* invalidate icache */
	mcr	p15, 0, r0, c7, c5, 0x6		/* invalidate branch predictor array */
	bl	invalidate_dcache
	
	/* invalidate L2 cache */
	ldr	r0,=L2CCCrtl				/* Load L2CC base address base + control register */
	mov	r1, #0						/* force the disable bit */
	str	r1, [r0]					/* disable the L2 Caches */

	ldr	r0,=L2CCAuxCrtl				/* Load L2CC base address base + Aux control register */
	ldr	r1,[r0]						/* read the register */
	ldr	r2,=L2CCAuxControl			/* set the default bits */
	orr	r1,r1,r2
	str	r1, [r0]					/* store the Aux Control Register */

	ldr	r0,=L2CCTAGLatReg			/* Load L2CC base address base + TAG Latency address */
	ldr	r1,=L2CCTAGLatency			/* set the latencies for the TAG*/
	str	r1, [r0]					/* store the TAG Latency register Register */

	ldr	r0,=L2CCDataLatReg			/* Load L2CC base address base + Data Latency address */
	ldr	r1,=L2CCDataLatency			/* set the latencies for the Data*/
	str	r1, [r0]					/* store the Data Latency register Register */

	ldr	r0,=L2CCWay					/* Load L2CC base address base + way register */
	ldr	r2, =0xFFFF
	str	r2, [r0]					/* force invalidate */

	ldr	r0,=L2CCSync				/* need to poll 0x730, PSS_L2CC_CACHE_SYNC_OFFSET */
									/* Load L2CC base address base + sync register*/
	/* poll for completion */
Sync:	ldr	r1, [r0]
	cmp	r1, #0
	bne	Sync

	ldr	r0,=L2CCIntRaw				/* clear pending interrupts */
	ldr	r1,[r0]
	ldr	r0,=L2CCIntClear
	str	r1,[r0]

	/* disable MMU */
	mrc	p15, 0, r0, c1, c0, 0		/* read CP15 register 1 */
	bic	r0, r0, #0x1				/* clear bit 0 */
	mcr	p15, 0, r0, c1, c0, 0		/* write value back */


	/* Setup stacks for interrupt modes */
	/* Usermode is not set up here */
	mrs	r0, cpsr			/* get the current PSR */
	mvn	r1, #0x1f			/* set up the irq stack pointer */
	and	r2, r1, r0
	orr	r2, r2, #0x12		/* IRQ mode */
	msr	cpsr, r2
	ldr	r13,=IRQ_stack		/* IRQ stack pointer */

	mrs	r0, cpsr			/* get the current PSR */
	mvn	r1, #0x1f			/* set up the supervisor stack pointer */
	and	r2, r1, r0
	orr	r2, r2, #0x13		/* supervisor mode */
	msr	cpsr, r2
	ldr	r13,=SPV_stack		/* Supervisor stack pointer */

	mrs	r0, cpsr			/* get the current PSR */
	mvn	r1, #0x1f			/* set up the Abort  stack pointer */
	and	r2, r1, r0
	orr	r2, r2, #0x17		/* Abort mode */
	msr	cpsr, r2
	ldr	r13,=Abort_stack	/* Abort stack pointer */

	mrs	r0, cpsr			/* get the current PSR */
	mvn	r1, #0x1f			/* set up the system stack pointer */
	and	r2, r1, r0
	orr	r2, r2, #0x1F		/* SYS mode */
	msr	cpsr, r2
	ldr	r13,=SYS_stack		/* SYS stack pointer */


	/* Enable caches and MMU */
	/* load translation table base */
	ldr	r0, =TblBase
	orr	r0, r0, #0x5B
	mcr	p15, 0, r0, cr2, cr0, 0

	/* load MMU domains -- all ones=manager */
	mvn	r0, #0
	mcr	p15, 0, r0, cr3, cr0, 0

	/* Enable MMU, icache and dcache */
	ldr	r0, =CRValMmuCac	/* Enable IDC, and MMU */
	mcr	p15,0,r0,cr1,cr0,0	/* Enable cache and MMU */
	dsb						/* dsb	allow the MMU to start up */
	isb						/* isb	flush prefetch buffer */

	/* Enable L2 cache */
	ldr	r0,=L2CCCrtl		/* Load L2CC base address base + control register */
	ldr	r1,[r0]				/* read the register */
	mov	r2, #L2CCControl	/* set the enable bit */
	orr	r1,r1,r2
	str	r1, [r0]			/* enable the L2 Caches */

	/* Allow access to FPU from user mode */
	mov	r0, r0
	mrc	p15, 0, r1, c1, c0, 2		/* read cp access control register (CPACR) into r1 */
	orr	r1, r1, #(0xf << 20)		/* enable full access for p10 & p11 */
	mcr	p15, 0, r1, c1, c0, 2		/* write back into CPACR */

	/* enable VFP and NEON */
	fmrx	r1, FPEXC		/* read the exception register */
	orr	r1,r1, #FPEXC_EN	/* set VFP enable bit, leave the others in orig state */
	fmxr	FPEXC, r1		/* write back the exception register */

	mrc	p15, 0, r0, cr1, cr0, 0		/* flow prediction enable */
	orr	r0, r0, #(0x01 << 11)		/* #0x8000 */
	mcr	p15, 0, r0, cr1, cr0, 0

	mrc	p15, 0, r0, c1, c0, 1		/* read Auxiliary Control Register */
	orr	r0, r0, #(0x1 << 2)			/* enable Dside prefetch */
	mcr	p15, 0, r0, c1, c0, 1		/* write Auxiliary Control Register */


	/* Zero the memory in the .bss section.  */
	movs a2, #0				/* Second arg: fill value */
	mov	fp, a2				/* Null frame pointer */
	
	ldr	a1, =BSS_Start		/* First arg: start of memory block */
	ldr	a3, =BSS_End	
	subs	a3, a3, a1		/* Third arg: length of block */

	bl memset

	/* call custom init functions */
	ldr	r3, .Lhwinit
	cmp	r3, #0
	beq	.noHwinit
	mov lr, pc
	mov pc, r3

.noHwinit:
	ldr	r3, .Lswinit
	cmp	r3, #0
	beq	.noSwinit
	mov lr, pc
	mov pc, r3
.noSwinit:

	/* do atexit and init stuff */
	ldr	r0, .Lfini
	bl	atexit
	bl	__libc_init_array

	movs r0, #0				/* 0 arguments */
	movs r1, #0 			/* no argv */

	/* call main */
	bl main
	bl exit

.hang:
	b .hang

.Lfini:
	.word	__libc_fini_array

.Lhwinit:	
	.word	hardware_init_hook
.Lswinit:
	.word	software_init_hook

	/* make the init functions weak */
	/* if they are not defined elsewhere, they are initialized with 0 */
	.weak hardware_init_hook
	.weak software_init_hook

/*
 *************************************************************************
 *
 * invalidate_dcache - invalidate the entire d-cache by set/way
 *
 * Note: for Cortex-A9, there is no cp instruction for invalidating
 * the whole D-cache. Need to invalidate each line.
 *
 *************************************************************************
 */
invalidate_dcache:
	mrc	p15, 1, r0, c0, c0, 1		/* read CLIDR */
	ands	r3, r0, #0x7000000
	mov	r3, r3, lsr #23				/* cache level value (naturally aligned) */
	beq	finished
	mov	r10, #0						/* start with level 0 */
loop1:
	add	r2, r10, r10, lsr #1		/* work out 3xcachelevel */
	mov	r1, r0, lsr r2				/* bottom 3 bits are the Cache type for this level */
	and	r1, r1, #7					/* get those 3 bits alone */
	cmp	r1, #2
	blt	skip						/* no cache or only instruction cache at this level */
	mcr	p15, 2, r10, c0, c0, 0		/* write the Cache Size selection register */
	isb								/* isb to sync the change to the CacheSizeID reg */
	mrc	p15, 1, r1, c0, c0, 0		/* reads current Cache Size ID register */
	and	r2, r1, #7					/* extract the line length field */
	add	r2, r2, #4					/* add 4 for the line length offset (log2 16 bytes) */
	ldr	r4, =0x3ff
	ands	r4, r4, r1, lsr #3		/* r4 is the max number on the way size (right aligned) */
	clz	r5, r4						/* r5 is the bit position of the way size increment */
	ldr	r7, =0x7fff
	ands	r7, r7, r1, lsr #13		/* r7 is the max number of the index size (right aligned) */
loop2:
	mov	r9, r4						/* r9 working copy of the max way size (right aligned) */
loop3:
	orr	r11, r10, r9, lsl r5		/* factor in the way number and cache number into r11 */
	orr	r11, r11, r7, lsl r2		/* factor in the index number */
	mcr	p15, 0, r11, c7, c14, 2		/* clean & invalidate by set/way */
	subs	r9, r9, #1				/* decrement the way number */
	bge	loop3
	subs	r7, r7, #1				/* decrement the index */
	bge	loop2
skip:
	add	r10, r10, #2				/* increment the cache number */
	cmp	r3, r10
	bgt	loop1

finished:
	mov	r10, #0						/* swith back to cache level 0 */
	mcr	p15, 2, r10, c0, c0, 0		/* select current cache level in cssr */
	dsb
	isb

	bx	lr

.end
