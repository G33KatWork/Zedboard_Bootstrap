.globl  MMUTable
.section .mmu_tbl,"aS"

MMUTable:
	/* Each table entry occupies one 32-bit word and there are
	 * 4096 entries, so the entire table takes up 16KB.
	 * Each entry covers a 1MB section.
	 */

.set SECT, 0

.rept	0x0400			/* 0x00000000 - 0x3fffffff (DDR Cacheable) */
.word	SECT + 0x15de6		/* S=b1 TEX=b101 AP=b11, Domain=b1111, C=b0, B=b1 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0400			/* 0x40000000 - 0x7fffffff (FPGA slave0) */
.word	SECT + 0xc02		/* S=b0 TEX=b000 AP=b11, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0400			/* 0x80000000 - 0xbfffffff (FPGA slave1) */
.word	SECT + 0xc02		/* S=b0 TEX=b000 AP=b11, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0200			/* 0xc0000000 - 0xdfffffff (unassigned/reserved).
				 * Generates a translation fault if accessed */
.word	SECT + 0x0		/* S=b0 TEX=b000 AP=b00, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0020			/* 0xe0000000 - 0xe1ffffff (Memory mapped devices)
				 * UART/USB/IIC/SPI/CAN/GEM/GPIO/QSPI/SD/NAND */
.word	SECT + 0xc02		/* S=b0 TEX=b000 AP=b11, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0020			/* 0xe2000000 - 0xe3ffffff (NOR) */
.word	SECT + 0xc02		/* S=b0 TEX=b000 AP=b11, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0020			/* 0xe4000000 - 0xe5ffffff (SRAM) */
.word	SECT + 0xc0e		/* S=b0 TEX=b000 AP=b11, Domain=b0, C=b1, B=b1 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0120			/* 0xe6000000 - 0xf7ffffff (unassigned/reserved).
				 * Generates a translation fault if accessed */
.word	SECT + 0x0		/* S=b0 TEX=b000 AP=b00, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0010			/* 0xf8000000 - 0xf8ffffff (AMBA APB Peripherals) */
.word	SECT + 0xc02		/* S=b0 TEX=b010 AP=b11, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x0030			/* 0xf9000000 - 0xfbffffff (unassigned/reserved).
				 * Generates a translation fault if accessed */
.word	SECT + 0x0		/* S=b0 TEX=b000 AP=b00, Domain=b0, C=b0, B=b0 */
.set	SECT, SECT+0x100000
.endr

.rept	0x003f			/* 0xfc000000 - 0xffefffff (Linear QSPI - XIP) */
.word	SECT + 0xc0a		/* S=b0 TEX=b000 AP=b11, Domain=b0, C=b1, B=b1 */
.set	SECT, SECT+0x100000
.endr

				/* 256K OCM when mapped to high address space
				 * inner-cacheable */
.word	SECT + 0x4c0e		/* S=b0 TEX=b100 AP=b11, Domain=b0, C=b1, B=b1 */
.set	SECT, SECT+0x100000

.end
