.org 0
.text

.global ResetHandler
.global _vector_table

.global FIQInterrupt
.global IRQInterrupt
.global SWInterrupt
.global DataAbortInterrupt
.global PrefetchAbortInterrupt

.section .vectors
_vector_table:
	B	ResetHandler
	B	Undefined
	B	SVCHandler
	B	PrefetchAbortHandler
	B	DataAbortHandler
	NOP	/* Placeholder for address exception vector*/
	B	IRQHandler
	B	FIQHandler


IRQHandler:					/* IRQ vector handler */
	sub		lr, #4			/* adjust return address */

	push 	{r0 - r12, lr}	/* save non-banked registers */

	msr		cpsr_ctl, #0xD3	/* switch to supervisor mode */
	mrs		r1, spsr 		/* get banked supervisor registers */
	mov     r2, sp
	mov     r3, lr
	msr     cpsr_ctl, #0xD2	/* switch back to IRQ-mode */
	mrs     r0, spsr
	push    {r0 - r3}		/* push the supervisor registers and IRQ spsr */

	/* get usermode sp, lr */
	stmdb   sp, {sp, lr}^
	sub     sp, #8

	/* handle irq */
	mov     r0, sp
	bl      IRQInterrupt
	mov     sp, r0

	/* restore usermode sp and lr */
	ldmia   sp, {sp, lr}^
	add     sp, #8

	/* restore banked supervisor registers */
	pop     {r0 - r3}
	msr     spsr_all, r0
	msr     cpsr_ctl, #0xD3
	msr     spsr_all, r1
	mov     sp, r2
	mov     lr, r3
	msr     cpsr_all, #0xD2

	/* restore non-banked resgisters and return */
	pop     {r0 - r12, lr}
	movs    pc, lr


FIQHandler:					/* FIQ vector handler */
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */

	bl	FIQInterrupt			/* FIQ vector */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */
	subs	pc, lr, #4			/* adjust return */


Undefined:					/* Undefined handler */
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	//b	_prestart			

	movs	pc, lr


SVCHandler:					/* SWI handler */
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */

	tst	r0, #0x20			/* check the T bit */
	ldrneh	r0, [lr,#-2]			/* Thumb mode */
	bicne	r0, r0, #0xff00			/* Thumb mode */
	ldreq	r0, [lr,#-4]			/* ARM mode */
	biceq	r0, r0, #0xff000000		/* ARM mode */

	bl	SWInterrupt			/* SWInterrupt: call C function here */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	subs	pc, lr, #4			/* adjust return */


DataAbortHandler:				/* Data Abort handler */
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */

	bl	DataAbortInterrupt		/*DataAbortInterrupt :call C function here */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	subs	pc, lr, #4			/* adjust return */

PrefetchAbortHandler:				/* Prefetch Abort handler */
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */

	bl	PrefetchAbortInterrupt		/* PrefetchAbortInterrupt: call C function here */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	subs	pc, lr, #4			/* adjust return */

.end
