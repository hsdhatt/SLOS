@ ****************************************************************************
@ * Simple Little Operating System - SLOS
@ ****************************************************************************

@ ****************************************************************************
@ *
@ * Module     : swi.s
@ * Project	: SLOS
@ * Version	: 0.09
@ * Originator	: Andrew N. Sloss
@ * History    :
@ * 
@ * 16th July 2003 Andrew N. Sloss
@ * - added header information
@ *
@ ****************************************************************************

	/* For LED debugging */
	.equ CM_PER_GPIO1_CLKCTRL, 0x44e000AC
	.equ GPIO1_OE, 0x4804C134
	.equ GPIO1_SETDATAOUT, 0x4804C194

     .text
     .code 32 
     .align 0
     .global coreSWIHandler
     .global coreCallSWI
     .extern eventsSWIHandler

@ ****************************************************************************
@ * kernel swi handler event
@ ****************************************************************************

@
@  void coreCallSWI(registerstr *r0)
@  User/Sys Mode

coreCallSWI:
     STMFD   r13!,{r0-r4,r12,lr}	@ save the corruptible registers	
     MOV     r4,r0			@ r0 contains the address of tmpreg	

     LDMIA   r4,{r0-r3}			/* 
					 * Prepare the arguments. r0 - typeofiocall, 
					 * Event)IODeviceInit  - r1 - 0, r2 - 0 , r3 - 0  
					 * Event_IODeviceOpen  - r1 - addr of UID, r2 - device major, r3 - minor
					 * Event_IODeviceWrite - r1 - addr of devicestr, r2 - UID, r3 - byte to write
					 * Event_IODeviceRead  - r1 - addr of devicestr, on return r1 - read byte , r2 - UID, r3 - 0 
					 */
						
     svc   5075 

     STMIA   r4,{r0-r3}			
     LDMFD   r13!,{r0-r4,r12,pc}	/* restore all the reg values */

@
@  void coreSWIHandler(void)
@	MODE=SVC

coreSWIHandler:
     STMFD   sp!,{r0-r12,lr}      /* storing all the registers on SVC stack. the lr points to STMIA instruction in coreCallSWI */ 

	
     ldr r0, =GPIO1_OE
     ldr r1, [r0]
     bic r1, r1, #(1<<23)
     str r1, [r0]
 
     ldr r0, =GPIO1_OE
     ldr r1, [r0]
     bic r1, r1, #(1<<24)
     str r1, [r0]

     LDR     r10,[lr,#-4]         /*the svc instruction word*/
     BIC     r10,r10,#0xff000000  
     MOV     r0,r10		/* r0 - 5075*/
     MOV     r1,sp		/* pointer to r0-r12, lr*/
     MRS     r2,SPSR        
     STMFD   sp!,{r2}
     BL      eventsSWIHandler    @ eventsSWIHandler(r0-swiNumber,r1-pointer to all registers),  on return, r0 is 0 and r0 on the stack is addr					  of led_device
     LDMFD   sp!,{r2}          
     MSR     SPSR_cxsf,r2     /* the spsr of svc wil be restored in cpsr of user mode on svc exit*/ 
     LDMFD   sp!,{r0-r12,pc}^ /* the lr of svc mode now points to stmia of corecallswi */
     .end
