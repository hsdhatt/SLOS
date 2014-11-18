.text
.code 32
.global modifyControlCPSR


modifyControlCPSR:


     STMFD   r13!,{r3}
     MOV     r3,r13	
     ADD     r13,r13,#4      
     STMFD   r3!,{r1,lr}


     MRS     r1,CPSR
     BIC     r1,r1,#0xff 
     ORR     r1,r1,r0 
     MSR     CPSR_c,r1


     LDMFD   r3!,{r1,lr}
     LDMFD   r3,{r3}
     MOV     pc,lr
     .end
