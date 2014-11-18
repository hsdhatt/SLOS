@ //
@ // ********************************************************
@ // @ * Simple Little Operating System - SLOS
@ // @ *******************************************************

@ ****************************************************************************
@ *
@ * Module     : start.s
@ * Project	: SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ * History    :
@ * 
@ * 16th July 2003 Andrew N. Sloss
@ * - added header information
@ *
@ ****************************************************************************

@ *******************************************************
@ * SLOS 2002 
@ *******************************************************
	/* for led debugging */
	.equ CM_PER_GPIO1_CLKCTRL, 0x44e000AC
	.equ GPIO1_OE, 0x4804C134
	.equ GPIO1_SETDATAOUT, 0x4804C194

@ *******************************************************
@ * IMPORT 
@ *******************************************************

@************************ Internal Definitions ******************************
@
@
@ to set the mode bits in CPSR for different modes
@
        .set  MODE_USR, 0x10
        .set  MODE_FIQ, 0x11
        .set  MODE_IRQ, 0x12
        .set  MODE_SVC, 0x13
        .set  MODE_ABT, 0x17
        .set  MODE_UND, 0x1B
        .set  MODE_SYS, 0x1F
        .equ  I_F_BIT, 0xC0

	.text
	.code 32
	.align 0
	.section INTERRUPT_VECTOR, "x"
	.global _asm_entry

_asm_entry:

@
@ Change to SVC mode 
@
	MSR   cpsr_c, #MODE_SVC|I_F_BIT       @ change to SVC mode

	LDR     r1,vectoraddr			@ save exception base address in VBAR
	MCR     p15, #0, r1, c12, c0, #0
	DSB

#_mainCRTStartup:
 
 @ ----------------------------------------------------
 @ table offset  
 @ 00 - Reset
 @ 04 - Undefined instructions
 @ 08 - SWI instructions
 @ 0C - prefetch abort
 @ 10 - Data abort
 @ 14 - Reserved
 @ 18 - IRQ interrupts
 @ 1C - FIQ interrupts
 @ ----------------------------------------------------


	.align 5	/* vector base address should be aligned to 16 byte boundary */
vectors:
     LDR     pc,vectorReset
     LDR     pc,vectorUndefined
     LDR     pc,vectorSWI
     LDR     pc,vectorPrefetchAbort
     LDR     pc,vectorDataAbort
     LDR     pc,vectorReserved
     LDR     pc,vectorIRQ
     LDR     pc,vectorFIQ


@ -- Useful address to the PCB tables ------------------ 

ptrPCBTable:
     .word   PCB_Table

@ -- Kernel Jump table ------------------------------ 

vectorReset:
     .word     coreInitialize
vectorUndefined:     
     .word     coreUndefinedHandler
vectorSWI:           
     .word     coreSWIHandler
vectorPrefetchAbort: 
     .word     corePrefetchAbortHandler
vectorDataAbort:
     .word     coreDataAbortHandler
vectorReserved:      
     .word     coreReservedHandler
vectorIRQ:           
     .word     coreIRQHandler
vectorFIQ:           
     .word     coreFIQHandler
vectoraddr:           
     .word     vectors

     .end
