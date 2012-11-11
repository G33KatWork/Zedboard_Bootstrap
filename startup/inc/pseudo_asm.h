#ifndef _PSEUDO_ASM_H_
#define _PSEUDO_ASM_H_

/* necessary for pre-processor */
#define stringify(s)	tostring(s)
#define tostring(s)	#s

/* pseudo assembler instructions */
#define mfcpsr()	({unsigned int rval; \
			  __asm__ __volatile__(\
			    "mrs	%0, cpsr\n"\
			    : "=r" (rval)\
			  );\
			  rval;\
			 })

#define mtcpsr(v)	__asm__ __volatile__(\
			  "msr	cpsr,%0\n"\
			  : : "r" (v)\
			)

#define cpsiei()	__asm__ __volatile__("cpsie	i\n")
#define cpsidi()	__asm__ __volatile__("cpsid	i\n")

#define cpsief()	__asm__ __volatile__("cpsie	f\n")
#define cpsidf()	__asm__ __volatile__("cpsid	f\n")



#define mtgpr(rn, v)	__asm__ __volatile__(\
			  "mov r" stringify(rn) ", %0 \n"\
			  : : "r" (v)\
			)

#define mfgpr(rn)	({unsigned int rval; \
			  __asm__ __volatile__(\
			    "mov %0,r" stringify(rn) "\n"\
			    : "=r" (rval)\
			  );\
			  rval;\
			 })

/* memory synchronization operations */

/* Instruction Synchronization Barrier */
#define isb() __asm__ __volatile__ ("isb" : : : "memory")

/* Data Synchronization Barrier */
#define dsb() __asm__ __volatile__ ("dsb" : : : "memory")

/* Data Memory Barrier */
#define dmb() __asm__ __volatile__ ("dmb" : : : "memory")


/* Memory Operations */
#define ldr(adr)	({unsigned long rval; \
			  __asm__ __volatile__(\
			    "ldr	%0,[%1]"\
			    : "=r" (rval) : "r" (adr)\
			  );\
			  rval;\
			 })

#define ldrb(adr)	({unsigned char rval; \
			  __asm__ __volatile__(\
			    "ldrb	%0,[%1]"\
			    : "=r" (rval) : "r" (adr)\
			  );\
			  rval;\
			 })

#define str(adr, val)	__asm__ __volatile__(\
			  "str	%0,[%1]\n"\
			  : : "r" (val), "r" (adr)\
			)

#define strb(adr, val)	__asm__ __volatile__(\
			  "strb	%0,[%1]\n"\
			  : : "r" (val), "r" (adr)\
			)

/* Count leading zeroes (clz) */
#define clz(arg)	({unsigned char rval; \
			  __asm__ __volatile__(\
			    "clz	%0,%1"\
			    : "=r" (rval) : "r" (arg)\
			  );\
			  rval;\
			 })

/* CP15 operations */
#define mtcp(rn, v)	__asm__ __volatile__(\
			 "mcr " rn "\n"\
			 : : "r" (v)\
			);

#define mfcp(rn)	({unsigned int rval; \
			 __asm__ __volatile__(\
			   "mrc " rn "\n"\
			   : "=r" (rval)\
			 );\
			 rval;\
			 })

#endif
