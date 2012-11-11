# .global ResetHandler

# .global main

# .global __stack
# .global __irq_stack
# .global __supervisor_stack
# .global __abort_stack

# .set Abort_stack,	__abort_stack
# .set SPV_stack,		__supervisor_stack
# .set IRQ_stack,		__irq_stack
# .set SYS_stack,		__stack

# ResetHandler:
# 	mrs	r0, cpsr			/* get the current PSR */
# 	mvn	r1, #0x1f			/* set up the irq stack pointer */
# 	and	r2, r1, r0
# 	orr	r2, r2, #0x12		/* IRQ mode */
# 	msr	cpsr, r2
# 	ldr	r13,=IRQ_stack		/* IRQ stack pointer */

# 	mrs	r0, cpsr			/* get the current PSR */
# 	mvn	r1, #0x1f			/* set up the supervisor stack pointer */
# 	and	r2, r1, r0
# 	orr	r2, r2, #0x13		/* supervisor mode */
# 	msr	cpsr, r2
# 	ldr	r13,=SPV_stack		/* Supervisor stack pointer */

# 	mrs	r0, cpsr			/* get the current PSR */
# 	mvn	r1, #0x1f			/* set up the Abort  stack pointer */
# 	and	r2, r1, r0
# 	orr	r2, r2, #0x17		/* Abort mode */
# 	msr	cpsr, r2
# 	ldr	r13,=Abort_stack	/* Abort stack pointer */

# 	mrs	r0, cpsr			/* get the current PSR */
# 	mvn	r1, #0x1f			/* set up the system stack pointer */
# 	and	r2, r1, r0
# 	orr	r2, r2, #0x1F		/* SYS mode */
# 	msr	cpsr, r2
# 	ldr	r13,=SYS_stack		/* SYS stack pointer */

# 	#TODO: call ctors

# 	bl main

# 	#TODO: call dtors

# .hang:
# 	b .hang

# .end
