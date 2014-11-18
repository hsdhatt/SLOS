@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ****************************************************************************
@ *
@ * Module     : init.s
@ * OS         : SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ *
@ * 14 July 2003 Andrew N. Sloss
@ * - separated the pcbSetUp routine
@ *
@ ****************************************************************************

     .text
     .code 32
     .align 0
     .global coreInitialize
     .extern C_Entry
     .extern C_EntryTask2
     .extern C_EntryTask3
     .extern PCB_PtrTask2
     .extern PCB_PtrTask3
     .extern PCB_CurrentTask
     .extern pcbSetUp
     .extern coreCallSWI

	/* for led debugging */
	.equ GPIO1_SETDATAOUT, 0x4804C194
	.equ CM_PER_GPIO1_CLKCTRL, 0x44e000AC
        .equ GPIO1_OE, 0x4804C134


     .equ IRQ32md, 0x12
     .equ SVC32md, 0x13
     .equ SYS32md, 0x1f
     .equ NoInt,   0xc0

SVC_STACK_START:
	.word	0x80080000	/* SDRAM_BEGIN + 512K. SVC_STACK_SIZE = 128K */
SYS_STACK_START:
	.word	0x80040000	/* SDRAM_BEGIN + 128K. SYS_STACK_SIZE = 512K */
IRQ_STACK_START:
	.word	0x80009000	/* SDRAM_BEGIN + 36K  IRQ_STACK_SIZE = don't know. maybe 28K??*/
TASK2_STACK_START:
	.word	0x80010000	/* SDRAM_BEGIN + 36K  IRQ_STACK_SIZE = don't know. maybe 28K??*/
TASK3_STACK_START:
	.word	0x80090000	/* SDRAM_BEGIN + 36K  IRQ_STACK_SIZE = don't know. maybe 28K??*/

coreInitialize:
/*     BL	     bringUpInitFIQRegisters*/


/*
@ ------------------------------------------------
@ Setup stacks for SVC,IRQ,SYS&USER 
@ Mode = SVC 
@ ------------------------------------------------
*/

     ldr sp, SVC_STACK_START
     MSR CPSR_c,#NoInt|SYS32md
     ldr sp, SYS_STACK_START
     MSR CPSR_c,#NoInt|IRQ32md
     ldr sp, IRQ_STACK_START
     MSR CPSR_c,#NoInt|SVC32md /* back in SVC mode */


/*
@ ------------------------------------------------
@ Setup Task Process Control Block (PCB).
@ Mode = SVC
@ ------------------------------------------------
*/

     LDR     r0,=C_EntryTask2    
     LDR     r1,=PCB_PtrTask2
     LDR     r2, =TASK2_STACK_START	/* task 2 stack base is 0x80010000 */
     BL      pcbSetUp

     LDR     r0,=C_EntryTask3     
     LDR     r1,=PCB_PtrTask3
     LDR     r2, =TASK3_STACK_START	/* task 3 stack base is 0x80020000 */
     BL      pcbSetUp

@ -- set the current ID to TASK1 ...........
     LDR     r0, =PCB_CurrentTask
     MOV     r1, #0
     STR     r1,[r0]              

/* set clock for GPIO1, TRM 8.1.12.1.29 */
        ldr r0, =CM_PER_GPIO1_CLKCTRL
        ldr r1, =0x40002
        str r1, [r0] 

        /* set pin 21 for output, led USR0, TRM 25.3.4.3 */
        ldr r0, =GPIO1_OE
        ldr r1, [r0]
        bic r1, r1, #(1<<21)
        str r1, [r0]

        /* set pin 21 for output, led USR0, TRM 25.3.4.3 */
        ldr r0, =GPIO1_OE
        ldr r1, [r0]
        bic r1, r1, #(1<<22)
        str r1, [r0]

        /* set pin 21 for output, led USR0, TRM 25.3.4.3 */
        ldr r0, =GPIO1_OE
        ldr r1, [r0]
        bic r1, r1, #(1<<23)
        str r1, [r0]

        /* logical 1 turns on the led, TRM 25.3.4.2.2.2 */
     BLX   C_Entry         
              SUB   pc, pc, #0x08                   @ looping   
     .end
