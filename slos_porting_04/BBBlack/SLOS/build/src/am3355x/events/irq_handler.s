@  ____________________________________________________________________
@ 
@  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
@  All rights reserved.
@  ____________________________________________________________________
@ 
@  NON-COMMERCIAL USE License
@  
@  Redistribution and use in source and binary forms, with or without 
@  modification, are permitted provided that the following conditions 
@  are met: 
@  
@  1. For NON-COMMERCIAL USE only.
@ 
@  2. Redistributions of source code must retain the above copyright 
@     notice, this list of conditions and the following disclaimer. 
@ 
@  3. Redistributions in binary form must reproduce the above 
@     copyright notice, this list of conditions and the following 
@     disclaimer in the documentation and/or other materials provided 
@     with the distribution. 
@ 
@  4. All advertising materials mentioning features or use of this 
@     software must display the following acknowledgement:
@ 
@     This product includes software developed by Andrew N. Sloss,
@     Chris Wright and Dominic Symes. 
@ 
@   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
@   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
@   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
@   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
@   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
@   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
@   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES@ LOSS OF USE, DATA, 
@   OR PROFITS@ OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
@   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
@   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
@   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
@   OF SUCH DAMAGE. 
@ 
@  If you have questions about this license or would like a different
@  license please email :
@ 
@ 	andrew@sloss.net
@ 
@ 
@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ****************************************************************************
@ *
@ * Module      : handler.s
@ * Description : handles the irq events
@ * OS          : SLOS
@ * Platform    : LDS2000
@ * History     :
@ *
@ * 21 December 2001 Andrew N. Sloss
@ * - started working on the handlers
@ *   
@ ****************************************************************************
       .equ SOC_AINTC_REGS, 0x48200000
       .equ INTC_SIR_IRQ, 0x40
       .equ INTC_ADDR_CONTROL, 0x48
       .equ INTC_IRQ_PRIORITY, 0x60
       .equ MASK_ACTIVE_IRQ,0x0000007f
       .equ NEWIRQGEN,  0x00000001
       .equ ADDR_SIR_IRQ, SOC_AINTC_REGS + INTC_SIR_IRQ
       .equ ADDR_CONTROL, SOC_AINTC_REGS + INTC_ADDR_CONTROL
       .equ ADDR_IRQ_PRIORITY, SOC_AINTC_REGS + INTC_IRQ_PRIORITY

@ ****************************************************************************
@ * EXPORT
@ ****************************************************************************

     .text 
     .code 32
     .global eventsIRQHandler

@ ****************************************************************************
@ * IMPORT
@ ****************************************************************************

	.extern eventTickService
	.extern eventButtonService
	.extern kernelScheduler

	/* for LED Debugging */
	.equ GPIO1_OE, 0x4804C134
	.equ GPIO1_SETDATAOUT, 0x4804C194


@ ****************************************************************************
@ * ROUTINES
@ ****************************************************************************

@ -- address of the IRQ controller for LDS2000. 

     
@ -- events_irq_handler -------------------------------------------------------
@ ;
@ Description  : handles the IRQ interrupt and determines the source and then
@                vectors to the correct interrupt rountine.
@ ;

eventsIRQHandler:

     SUB     r14, r14, #4		/* LR correction */
     STMFD   r13!, {r0-r3, r12, r14}    @ save context
	
     LDR     r1, =ADDR_SIR_IRQ
     LDR     r2, [r1]			@ get the active IRQ
     AND     r2, r2, #MASK_ACTIVE_IRQ	@ r2 contains the IRQ number. for timer it should be 0x44
     

     CMP     r2, #0x44			@ the DMTimer2 Interrupt
     BEQ     eventTickVeneer       
     
     MOV     r0, #NEWIRQGEN
     LDR     r1, =ADDR_CONTROL      
     STR     r0, [r1]                     @ acknowledge the INTC that you have read the interrupt number
     DSB
     LDMFD r13!, {r0-r3, r12, pc}^	@restore the context and return

eventTickVeneer:

     BL      eventTickService		@ The DMTimer2 ISR

     MOV     r0, #NEWIRQGEN
     LDR     r1, =ADDR_CONTROL      
     STR     r0, [r1]                     @ acknowledge the INTC that you have read the interrupt number
     DSB
     B       kernelScheduler
     LDMFD r13!, {r0-r3, r12, pc}^	@ dummy restore the context and return
     .end

