/*
 *  ____________________________________________________________________
 * 
 *  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
 *  All rights reserved.
 *  ____________________________________________________________________
 * 
 *  NON-COMMERCIAL USE License
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met: 
 *  
 *  1. For NON-COMMERCIAL USE only.
 * 
 *  2. Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *  3. Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 * 
 *  4. All advertising materials mentioning features or use of this 
 *     software must display the following acknowledgement:
 * 
 *     This product includes software developed by Andrew N. Sloss,
 *     Chris Wright and Dominic Symes. 
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
 *   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
 *   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
 *   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 *   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 *   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *   OF SUCH DAMAGE. 
 * 
 *  If you have questions about this license or would like a different
 *  license please email :
 * 
 * 	andrew@sloss.net
 * 
 * 
 */
 
/*****************************************************************************
 * Simple Little Operating System - SLOS
 *****************************************************************************/

/*****************************************************************************
 *
 * Module      : tick_service.c
 * Description : Header File
 * Platform    : LDS2000
 * History     : 
 *
 * 2000-03-25 Andrew N. Sloss
 * - implemented a tick service
 *
 *****************************************************************************/


/*****************************************************************************
 * IMPORT
 *****************************************************************************/
#include "soc_AM335x.h"
#include "hw_cm_dpll.h"
#include "hw_cm_per.h"
#include "../headers/macros.h"
#include "../headers/reg.h"
#include "../../headers/api_types.h"

/*****************************************************************************
 * MACRO'S
 *****************************************************************************/

/* none ... */
 
/*****************************************************************************
 * GLOBAL
 *****************************************************************************/

UINT countdown;

/*****************************************************************************
 * EXTERN's
 *****************************************************************************/

/* none... */

/*****************************************************************************
 * GLOBALS
 *****************************************************************************/

/* none... */

/*****************************************************************************
 * ROUTINES
 *****************************************************************************/

/* -- eventTickInit -----------------------------------------------------------
 *                                                            
 * Description  : Initialises the counter timer in milliseconds
 *
 * Parameters   : UINT msec - sets periodic timer in milliseconds
 * Return       : none...
 * Notes        : none...
 *                                                                             
 */
#define __REG32 *(volatile unsigned long *)

#define HWREG(x)                                                              \
        (*((volatile unsigned int *)(x)))

#define DMTimerWaitForWrite(reg, baseAdd)   \
            if(__REG32(baseAdd + DMTIMER_TSICR) & DMTIMER_TSICR_POSTED)\
            while((reg & DMTimerWritePostedStatusGet(baseAdd)));
 
int toggle = 0; /* toggle led4 on every interrupt */

void DMTimer2ClkConfig(void)
{
    /* Select the clock source for the Timer2 instance. */
    __REG32(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER2_CLK) &=
          ~(CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL);

    __REG32(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER2_CLK) |=
          CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL_CLK_M_OSC;

    while((__REG32(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER2_CLK) &
           CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL) !=
           CM_DPLL_CLKSEL_TIMER2_CLK_CLKSEL_CLK_M_OSC);

    __REG32(SOC_CM_PER_REGS + CM_PER_TIMER2_CLKCTRL) |=
                             CM_PER_TIMER2_CLKCTRL_MODULEMODE_ENABLE;

    while((__REG32(SOC_CM_PER_REGS + CM_PER_TIMER2_CLKCTRL) &
    CM_PER_TIMER2_CLKCTRL_MODULEMODE) != CM_PER_TIMER2_CLKCTRL_MODULEMODE_ENABLE);

    while((__REG32(SOC_CM_PER_REGS + CM_PER_TIMER2_CLKCTRL) &
       CM_PER_TIMER2_CLKCTRL_IDLEST) != CM_PER_TIMER2_CLKCTRL_IDLEST_FUNC);

    while(!(__REG32(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) &
            CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));

    while(!(__REG32(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) &
            CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));

    while(!(__REG32(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
           (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK |
            CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));

    while(!(__REG32(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) &
           (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK |
            CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK)));
}

unsigned int DMTimerWritePostedStatusGet(unsigned int baseAdd)
{
    /* Return the status of TWPS register */
    return (__REG32(baseAdd + DMTIMER_TWPS));
}



void eventTickInit (UINT msec)
{
	/* enable the dmtimer2 interrupt in the system*/
	int intrNum = 68;

	DMTimer2ClkConfig();

	    /* Reset the ARM interrupt controller */
	__REG32(SOC_AINTC_REGS + INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;

	   /* Wait for the reset to complete */
	while((__REG32(SOC_AINTC_REGS + INTC_SYSSTATUS)
          & INTC_SYSSTATUS_RESETDONE) != INTC_SYSSTATUS_RESETDONE);


        /* Enable any interrupt generation by setting priority threshold */
        __REG32(SOC_AINTC_REGS + INTC_THRESHOLD) =
                                     INTC_THRESHOLD_PRIORITYTHRESHOLD;



	/* Set the priority */
	__REG32(SOC_AINTC_REGS + INTC_ILR(intrNum))
			= 0x0;

	__asm__("dsb");

	/* Disable the system interrupt in the corresponding MIR_CLEAR register */
	__REG32(SOC_AINTC_REGS + INTC_MIR_CLEAR(intrNum >> REG_IDX_SHIFT))
                                   = (0x01 << (intrNum & REG_BIT_MASK));



	/* Wait for previous write to complete */
	DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR, SOC_DMTIMER_2_REGS);

	/* Set the counter value */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_TCRR) = TIMER_INITIAL_COUNT;

	/* Wait for previous write to complete */
	DMTimerWaitForWrite(DMTIMER_WRITE_POST_TMAR, SOC_DMTIMER_2_REGS);

	/* Write the compare value to TMAR */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = TIMER_MATCH_COUNT * msec ;

	/* DMTimerModeConfigure */
	/* Wait for previous write to complete */
	DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, SOC_DMTIMER_2_REGS);

	/* Clear the AR and CE field of TCLR */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) &= ~(DMTIMER_TCLR_AR | DMTIMER_TCLR_CE);

	/* Wait for previous write to complete */
	DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, SOC_DMTIMER_2_REGS);

	/* Set the timer mode in TCLR register */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (DMTIMER_ONESHOT_CMP_ENABLE & (DMTIMER_TCLR_AR | 
                                                   DMTIMER_TCLR_CE));

	/* Enable the DMTimer interrupts represented by intFlags */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_SET) = (DMTIMER_INT_MAT_EN_FLAG &
                                           (DMTIMER_IRQENABLE_SET_TCAR_EN_FLAG |
                                            DMTIMER_IRQENABLE_SET_OVF_EN_FLAG |
                                            DMTIMER_IRQENABLE_SET_MAT_EN_FLAG));

}

/* -- eventTickService --------------------------------------------------------
 *
 * Description : interrupt service routine for timer0 interrupt.
 *
 * Parameters  : none...
 * Return      : none...
 * Notes       : 
 * 
 * timer interrupt everytime the counter reaches 0. To reset
 * the timer TDATA0 has to have a new initialization value.
 * Finally the last act is to unmask the timer interrupt on 
 * the Samsung KS3250C100.
 *
 */ 

typedef unsigned int uint32_t;
static inline void setbits_le32(const void* addr, uint32_t pattern)
{
        uint32_t register_value = *(volatile uint32_t *) addr;
        register_value = register_value | pattern;
        *(volatile uint32_t *)addr = register_value;
}
static inline void clrbits_le32(const void* addr, uint32_t pattern)
{
        uint32_t register_value = *(volatile uint32_t *) addr;
        register_value = register_value & ~pattern;
        *(volatile uint32_t *)addr = register_value;
}
 

void eventTickService(void) 
{
	/* Disable the DMTimer interrupts */
	/* Disable the DMTimer interrupts represented by intFlags */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_CLR) = (DMTIMER_INT_MAT_EN_FLAG &
                                           (DMTIMER_IRQENABLE_CLR_TCAR_EN_FLAG |
                                            DMTIMER_IRQENABLE_CLR_OVF_EN_FLAG |
                                            DMTIMER_IRQENABLE_CLR_MAT_EN_FLAG));

	/* Clear the status of the interrupt flags */
	/* Clear the interrupt status from IRQSTATUS register */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) = (DMTIMER_INT_MAT_EN_FLAG &
                                         (DMTIMER_IRQSTATUS_TCAR_IT_FLAG |
                                          DMTIMER_IRQSTATUS_OVF_IT_FLAG |
                                          DMTIMER_IRQSTATUS_MAT_IT_FLAG));


	/* Load the counter with the initial count value */

	/* Wait for previous write to complete */
	DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR, SOC_DMTIMER_2_REGS);

	/* Set the counter value */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_TCRR) = TIMER_INITIAL_COUNT;

	/* Enable the DMTimer interrupts represented by intFlags */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_SET) = (DMTIMER_INT_MAT_EN_FLAG & 
                                            DMTIMER_IRQENABLE_SET_MAT_EN_FLAG);
	
	if (toggle == 0){
	        setbits_le32((uint32_t *)(0x4804c000 + 0x13c), (0x1 << 24)); /* switch of led 4*/
		toggle = 1;
	}
	else{
	        clrbits_le32((uint32_t *)(0x4804c000 + 0x13c), (0x1 << 24)); /* switch of led 4*/
		toggle = 0;
	}	

} 

/* -- eventTickStart ----------------------------------------------------------
 *
 * Description  : switches on the periodic tick event
 *
 * Parameters   : none...
 * Return       : none...
 * Notes        : none...
 *
 */  
 
void eventTickStart(void)
{	
	
	DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, SOC_DMTIMER_2_REGS);
            
	/* Start the timer */
	__REG32(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= DMTIMER_TCLR_ST;


}

