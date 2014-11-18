
#ifndef SMART_REG_H
#define SMART_REG_H

#define	__REG	*(volatile unsigned long *)
#define	__REG32	*(volatile unsigned long *)
#define	__REG16	*(volatile unsigned short *)
#define	__REG8	*(volatile unsigned char *)


/** @brief Base address of AINTC memory mapped registers                      */
#define SOC_AINTC_REGS                       (0x48200000)
#define INTC_SYSCONFIG (0x10)
#define INTC_SYSSTATUS (0x14)
#define INTC_THRESHOLD (0x68)
#define INTC_IRQ_PRIORITY (0x60)


#define INTC_MIR_CLEAR(n) (0x88 + ((n) * 0x20))
#define INTC_MIR_SET(n) (0x8c + ((n) * 0x20))

#define REG_IDX_SHIFT                  (0x05)
#define REG_BIT_MASK                   (0x1F)
#define NUM_INTERRUPTS                 (128u)

#define INTC_ILR(n)  (0x100 + ((n) * 0x04))


/* THRESHOLD */
#define INTC_THRESHOLD_PRIORITYTHRESHOLD    (0x000000FFu)
#define INTC_THRESHOLD_PRIORITYTHRESHOLD_SHIFT  (0x00000000u)


 
/* SYSSTATUS */
#define INTC_SYSSTATUS_RESETDONE    (0x00000001u)
#define INTC_SYSSTATUS_RESETDONE_SHIFT  (0x00000000u)

/* SYSCONFIG */
#define INTC_SYSCONFIG_SOFTRESET    (0x00000002u)
#define INTC_SYSCONFIG_SOFTRESET_SHIFT  (0x00000001u)
    


#define TIMER_INITIAL_COUNT	0x00000000u
#define TIMER_MATCH_COUNT	0x6590	/* 26MHZ clock 1 msec difference */
/** @brief Base addresses of DMTIMER memory mapped registers                  */
#define SOC_DMTIMER_2_REGS                   (0x48040000)
/*************************************************************************\
 * DMTimer2 Registers Definition
\*************************************************************************/

#define DMTIMER_TIDR   (0x0)
#define DMTIMER_TIOCP_CFG   (0x10)
#define DMTIMER_IRQ_EOI   (0x20)
#define DMTIMER_IRQSTATUS_RAW   (0x24)
#define DMTIMER_IRQSTATUS   (0x28)
#define DMTIMER_IRQENABLE_SET   (0x2C)
#define DMTIMER_IRQENABLE_CLR   (0x30)
#define DMTIMER_IRQWAKEEN   (0x34)
#define DMTIMER_TCLR   (0x38)
#define DMTIMER_TCRR   (0x3C)
#define DMTIMER_TLDR   (0x40)
#define DMTIMER_TTGR   (0x44)
#define DMTIMER_TWPS   (0x48)
#define DMTIMER_TMAR   (0x4C)
#define DMTIMER_TCAR(n)   (0x50 + (((n) - 1) * 8))
#define DMTIMER_TSICR   (0x54)

/* TSICR */
#define DMTIMER_TSICR_POSTED   (0x00000004u)
#define DMTIMER_TSICR_POSTED_SHIFT   (0x00000002u)
#define DMTIMER_TSICR_POSTED_ACTIVE   (0x1u)
#define DMTIMER_TSICR_POSTED_INACTIVE   (0x0u)

/* TWPS */
#define DMTIMER_TWPS_W_PEND_TCLR   (0x00000001u)
#define DMTIMER_TWPS_W_PEND_TCLR_SHIFT   (0x00000000u)
#define DMTIMER_TWPS_W_PEND_TCLR_NONE   (0x0u)
#define DMTIMER_TWPS_W_PEND_TCLR_PENDING   (0x1u)

#define DMTIMER_TWPS_W_PEND_TCRR   (0x00000002u)
#define DMTIMER_TWPS_W_PEND_TCRR_SHIFT   (0x00000001u)
#define DMTIMER_TWPS_W_PEND_TCRR_NONE   (0x0u)
#define DMTIMER_TWPS_W_PEND_TCRR_PENDING   (0x1u)

#define DMTIMER_TWPS_W_PEND_TLDR   (0x00000004u)
#define DMTIMER_TWPS_W_PEND_TLDR_SHIFT   (0x00000002u)
#define DMTIMER_TWPS_W_PEND_TLDR_NONE   (0x0u)
#define DMTIMER_TWPS_W_PEND_TLDR_PENDING   (0x1u)

#define DMTIMER_TWPS_W_PEND_TMAR   (0x00000010u)
#define DMTIMER_TWPS_W_PEND_TMAR_SHIFT   (0x00000004u)
#define DMTIMER_TWPS_W_PEND_TMAR_NONE   (0x0u)
#define DMTIMER_TWPS_W_PEND_TMAR_PENDING   (0x1u)
    
#define DMTIMER_TWPS_W_PEND_TTGR   (0x00000008u)
#define DMTIMER_TWPS_W_PEND_TTGR_SHIFT   (0x00000003u)
#define DMTIMER_TWPS_W_PEND_TTGR_NONE   (0x0u)
#define DMTIMER_TWPS_W_PEND_TTGR_PENDING   (0x1u)


/* Value used to check the write posted condition for TMAR register */
#define DMTIMER_WRITE_POST_TMAR              (DMTIMER_TWPS_W_PEND_TMAR)

/* Value used to check the write posted condition for TTGR register */
#define DMTIMER_WRITE_POST_TTGR              (DMTIMER_TWPS_W_PEND_TTGR)

/* Value used to check the write posted condition for TLDR register */
#define DMTIMER_WRITE_POST_TLDR              (DMTIMER_TWPS_W_PEND_TLDR)

/* Value used to check the write posted condition for TCRR register */
#define DMTIMER_WRITE_POST_TCRR              (DMTIMER_TWPS_W_PEND_TCRR)

/* Value used to check the write posted condition for TCLR register */
#define DMTIMER_WRITE_POST_TCLR              (DMTIMER_TWPS_W_PEND_TCLR)

/* TCLR */
#define DMTIMER_TCLR_AR   (0x00000002u)
#define DMTIMER_TCLR_AR_SHIFT   (0x00000001u)
#define DMTIMER_TCLR_AR_AUTO   (0x1u)
#define DMTIMER_TCLR_AR_ONESHOT   (0x0u)


#define DMTIMER_TCLR_CE   (0x00000040u)
#define DMTIMER_TCLR_CE_SHIFT   (0x00000006u)
#define DMTIMER_TCLR_CE_DISABLE   (0x0u)
#define DMTIMER_TCLR_CE_ENABLE   (0x1u)            

/* Value used to enable the timer in one-shot and compare mode */
#define DMTIMER_ONESHOT_CMP_ENABLE          (DMTIMER_TCLR_CE)

#define DMTIMER_IRQENABLE_SET_MAT_EN_FLAG   (0x00000001u)
#define DMTIMER_IRQENABLE_SET_OVF_EN_FLAG   (0x00000002u)
#define DMTIMER_IRQENABLE_SET_TCAR_EN_FLAG   (0x00000004u)



/* IRQSTATUS */
#define DMTIMER_IRQSTATUS_MAT_IT_FLAG   (0x00000001u)
#define DMTIMER_IRQSTATUS_MAT_IT_FLAG_SHIFT   (0x00000000u)
#define DMTIMER_IRQSTATUS_MAT_IT_FLAG_CLEAR   (0x1u)
#define DMTIMER_IRQSTATUS_MAT_IT_FLAG_NONE   (0x0u)
#define DMTIMER_IRQSTATUS_MAT_IT_FLAG_PENDING   (0x1u)

#define DMTIMER_IRQSTATUS_OVF_IT_FLAG   (0x00000002u)
#define DMTIMER_IRQSTATUS_OVF_IT_FLAG_SHIFT   (0x00000001u)
#define DMTIMER_IRQSTATUS_OVF_IT_FLAG_CLEAR   (0x1u)
#define DMTIMER_IRQSTATUS_OVF_IT_FLAG_NONE   (0x0u)
#define DMTIMER_IRQSTATUS_OVF_IT_FLAG_PENDING   (0x1u)

#define DMTIMER_IRQSTATUS_TCAR_IT_FLAG   (0x00000004u)
#define DMTIMER_IRQSTATUS_TCAR_IT_FLAG_SHIFT   (0x00000002u)
#define DMTIMER_IRQSTATUS_TCAR_IT_FLAG_CLEAR   (0x1u)
#define DMTIMER_IRQSTATUS_TCAR_IT_FLAG_NONE   (0x0u)
#define DMTIMER_IRQSTATUS_TCAR_IT_FLAG_PENDING   (0x1u)

/* IRQENABLE_CLR */
#define DMTIMER_IRQENABLE_CLR_MAT_EN_FLAG   (0x00000001u)
#define DMTIMER_IRQENABLE_CLR_MAT_EN_FLAG_SHIFT   (0x00000000u)
#define DMTIMER_IRQENABLE_CLR_MAT_EN_FLAG_DISABLE   (0x1u)
#define DMTIMER_IRQENABLE_CLR_MAT_EN_FLAG_DISABLED   (0x0u)
#define DMTIMER_IRQENABLE_CLR_MAT_EN_FLAG_ENABLED   (0x1u)

#define DMTIMER_IRQENABLE_CLR_OVF_EN_FLAG   (0x00000002u)
#define DMTIMER_IRQENABLE_CLR_OVF_EN_FLAG_SHIFT   (0x00000001u)
#define DMTIMER_IRQENABLE_CLR_OVF_EN_FLAG_DISABLE   (0x1u)
#define DMTIMER_IRQENABLE_CLR_OVF_EN_FLAG_DISABLED   (0x0u)
#define DMTIMER_IRQENABLE_CLR_OVF_EN_FLAG_ENABLED   (0x1u)

#define DMTIMER_IRQENABLE_CLR_TCAR_EN_FLAG   (0x00000004u)
#define DMTIMER_IRQENABLE_CLR_TCAR_EN_FLAG_SHIFT   (0x00000002u)
#define DMTIMER_IRQENABLE_CLR_TCAR_EN_FLAG_DISABLE   (0x1u)
#define DMTIMER_IRQENABLE_CLR_TCAR_EN_FLAG_DISABLED   (0x0u)
#define DMTIMER_IRQENABLE_CLR_TCAR_EN_FLAG_ENABLED   (0x1u)
                                            

/* Value used for capture event of DMTimer */
#define DMTIMER_INT_TCAR_EN_FLAG             (DMTIMER_IRQENABLE_SET_TCAR_EN_FLAG)
    
/* Value used for overflow event of DMTimer */
#define DMTIMER_INT_OVF_EN_FLAG              (DMTIMER_IRQENABLE_SET_OVF_EN_FLAG)
    
/* Value used for Match event of DMTimer */
#define DMTIMER_INT_MAT_EN_FLAG              (DMTIMER_IRQENABLE_SET_MAT_EN_FLAG)

#define DMTIMER_TCLR_ST   (0x00000001u)
#define DMTIMER_TCLR_ST_SHIFT   (0x00000000u)
#define DMTIMER_TCLR_ST_START   (0x1u)
#define DMTIMER_TCLR_ST_STOP   (0x0u)



#define BOOT_SWI 0xa3fe0024
#define BOOT_IRQ 0xa3fe0034
#define	TICKS_PER_SECOND 32768
#define	RCNR	 __REG(0x40900000)


//Interrupt Control Registers
//#define	INTERRUPT_CONTROL_BASE 0x40D00000
#define		INTER_BASE 0x40D00000
#define	ICIP		0x00
#define	ICMR		0x04
#define	ICLR		0x08
#define	ICFP		0x0C
#define	ICPR		0x10
#define	ICCR		0x14

#define	CLOCK_MANAGER_BASE 0x41300000

#define	CCCR		0x00
#define	CKEN		0x04
#define	OSCC		0x08
//#define	OSCR		0x40A00010

//OS Timer base
#define TIMER_BASE 0x40A00000

#define OSMR0		0x00
#define OSMR1		0x04
#define OSMR2		0x08
#define OSMR3		0x0C
#define OSCR		0x10
#define OSSR		0x14
#define OIER		0x1C

//GPIO registers
#define	GPIO_BASE	0x40E00000

#define	GPLR0		0x00
#define	GPLR1		0x04
#define	GPLR2		0x08
#define	GPDR0		0x0C
#define	GPDR1		0x10
#define	GPDR2		0x14
#define	GPSR0		0x18
#define	GPSR1		0x1C
#define	GPSR2		0x20
#define	GPCR0		0x24
#define	GPCR1		0x28
#define	GPCR2		0x2C
#define	GRER0		0x30
#define	GRER1		0x34
#define	GRER2		0x38
#define	GFER0		0x3C
#define	GFER1		0x40
#define	GFER2		0x44
#define	GDER0		0x48
#define	GDER1		0x4C
#define	GDER2		0x50
#define	GAFR0_L	0x54
#define	GAFR0_U	0x58
#define	GAFR1_L	0x5C
#define	GAFR1_U	0x60
#define	GAFR2_L	0x64
#define	GAFR2_U	0x68

//Memory Control Registers
#define	MEM_CTL_BASE      0x48000000

#define	MDCNFG	0x00
#define	MDREFR	0x04
#define	MSC0		0x08
#define	MSC1		0x0C
#define	MSC2		0x10
#define	MECR		0x14
#define	SXCNFG	0x1C
#define	MCMEM0	0x28
#define	MCMEM1	0x2C
#define	MCATT0	0x30
#define	MCATT1	0x34
#define	MCIO0		0x38
#define	MCIO1		0x3C
#define	MDMRS		0x40

// Power management
#define	RCSR		0x40F00030
#define	RCSR_SLEEP	0x00000004
#define	PSPR		0x40F00008
#define	PSSR		0x40F00004
//#define	PSSR_PH	0x00000010
//#define	PSSR_RDH	0x00000020
//#define	PSSR_STATUS_MASK  0x00000007

//FFUART Registers
#define	FFUART_BASE       0x40100000

#define	FFRBR		0x00
#define	FFTHR		0x00
#define	FFIER		0x04
#define	FFIIR		0x08
#define	FFFCR		0x08
#define	FFLCR		0x0C
#define	FFMCR		0x10
#define	FFLSR		0x14
#define	FFMSR		0x18
#define	FFSPR		0x1C
#define	FFISR		0x20
#define	FFDLL		0x00
#define	FFDLH		0x04

// Status bits.
#define	STATUS_BUSY			0x00800080
#define	STATUS_ERR_FILTER		0x007E007E
#define	STATUS_LOCK_DETECT		0x00020002
#define	STATUS_VOLT_RANG_ERR		0x00080008
#define	STATUS_CMD_SEQ_ERR		0x00300030
#define	STATUS_PGM_ERR			0x00100010
#define	STATUS_LOCK_ERR			0x00100010
#define	STATUS_ERASE_ERR		0x00200020
#define	STATUS_UNLOCK_ERR		0x00200020
#define	STATUS_LOCK_ERR_FILTER	0x00380038


/** @brief Base addresses of UART memory mapped registers                     */
#define SOC_UART_0_REGS                      (0x44E09000)

/* Values for enabling/disabling the interrupts of UART. */
    
#define UART_INT_CTS                        (UART_IER_CTS_IT)
#define UART_INT_RTS                        (UART_IER_RTS_IT)
#define UART_INT_XOFF                       (UART_IER_XOFF_IT)
#define UART_INT_SLEEPMODE                  (UART_IER_SLEEP_MODE_IT)
#define UART_INT_MODEM_STAT                 (UART_IER_MODEM_STS_IT)
#define UART_INT_LINE_STAT                  (UART_IER_LINE_STS_IT)
#define UART_INT_THR                        (UART_IER_THR_IT)
#define UART_INT_RHR_CTI                    (UART_IER_RHR_IT)

/* IER - UART Register */
#define UART_IER_CTS_IT   (0x00000080u)
#define UART_IER_CTS_IT_SHIFT   (0x00000007u)
#define UART_IER_CTS_IT_DISABLE   (0x0u)
#define UART_IER_CTS_IT_ENABLE   (0x1u)

#define UART_IER_RTS_IT   (0x00000040u)
#define UART_IER_RTS_IT_SHIFT   (0x00000006u)
#define UART_IER_RTS_IT_DISABLE   (0x0u)
#define UART_IER_RTS_IT_ENABLE   (0x1u)

#define UART_IER_XOFF_IT   (0x00000020u)
#define UART_IER_XOFF_IT_SHIFT   (0x00000005u)
#define UART_IER_XOFF_IT_DISABLE   (0x0u)
#define UART_IER_XOFF_IT_ENABLE   (0x1u)

#define UART_IER_SLEEP_MODE_IT   (0x00000010u)
#define UART_IER_SLEEP_MODE_IT_SHIFT   (0x00000004u)
#define UART_IER_SLEEP_MODE_IT_DISABLE   (0x0u)
#define UART_IER_SLEEP_MODE_IT_ENABLE   (0x1u)

#define UART_IER_MODEM_STS_IT   (0x00000008u)
#define UART_IER_MODEM_STS_IT_SHIFT   (0x00000003u)
#define UART_IER_MODEM_STS_IT_DISABLE   (0x0u)
#define UART_IER_MODEM_STS_IT_ENABLE   (0x1u)

#define UART_IER_LINE_STS_IT   (0x00000004u)
#define UART_IER_LINE_STS_IT_SHIFT   (0x00000002u)
#define UART_IER_LINE_STS_IT_DISABLE   (0x0u)
#define UART_IER_LINE_STS_IT_ENABLE   (0x1u)

#define UART_IER_THR_IT   (0x00000002u)
#define UART_IER_THR_IT_SHIFT   (0x00000001u)
#define UART_IER_THR_IT_DISABLE   (0x0u)
#define UART_IER_THR_IT_ENABLE   (0x1u)

#define UART_IER_RHR_IT   (0x00000001u)
#define UART_IER_RHR_IT_SHIFT   (0x00000000u)
#define UART_IER_RHR_IT_DISABLE   (0x0u)
#define UART_IER_RHR_IT_ENABLE   (0x1u)

/* Values to be used while switching between register configuration modes. */
    
#define UART_REG_CONFIG_MODE_A              (0x0080)
#define UART_REG_CONFIG_MODE_B              (0x00BF)
#define UART_REG_OPERATIONAL_MODE           (0x007F)
                
/*************************************************************************\
 * Registers Definition
\*************************************************************************/

#define UART_DLL   (0x0)
#define UART_RHR   (0x0)
#define UART_THR   (0x0)
#define UART_DLH   (0x4)
#define UART_IER   (0x4)
#define UART_EFR   (0x8)
#define UART_FCR   (0x8)
#define UART_IIR   (0x8)
#define UART_LCR   (0xC)
#define UART_MCR   (0x10)
#define UART_XON1_ADDR1   (0x10)
#define UART_LSR   (0x14)
#define UART_XON2_ADDR2   (0x14)
#define UART_MSR   (0x18)
#define UART_TCR   (0x18) 
#define UART_XOFF1 (0x18) 
#define UART_SPR   (0x1C)
#define UART_TLR   (0x1C)
#define UART_XOFF2 (0x1C)
#define UART_MDR1   (0x20)
#define UART_MDR2   (0x24)
#define UART_SFLSR   (0x28)
#define UART_TXFLL   (0x28)
#define UART_RESUME   (0x2C)
#define UART_TXFLH   (0x2C)
#define UART_RXFLL   (0x30)
#define UART_SFREGL   (0x30)
#define UART_RXFLH   (0x34)
#define UART_SFREGH   (0x34)
#define UART_BLR   (0x38)
#define UART_UASR   (0x38)
#define UART_ACREG   (0x3C)
#define UART_SCR   (0x40)
/*************************************************************************\
 * Registers Definition
\*************************************************************************/

#define UART_DLL   (0x0)
#define UART_RHR   (0x0)
#define UART_THR   (0x0)
#define UART_DLH   (0x4)
#define UART_IER   (0x4)
#define UART_EFR   (0x8)
#define UART_FCR   (0x8)
#define UART_IIR   (0x8)
#define UART_LCR   (0xC)
#define UART_MCR   (0x10)
#define UART_XON1_ADDR1   (0x10)
#define UART_LSR   (0x14)
#define UART_XON2_ADDR2   (0x14)
#define UART_MSR   (0x18)
#define UART_TCR   (0x18) 
#define UART_XOFF1 (0x18) 
#define UART_SPR   (0x1C)
#define UART_TLR   (0x1C)
#define UART_XOFF2 (0x1C)
#define UART_MDR1   (0x20)
#define UART_MDR2   (0x24)
#define UART_SFLSR   (0x28)
#define UART_TXFLL   (0x28)
#define UART_RESUME   (0x2C)
#define UART_TXFLH   (0x2C)
#define UART_RXFLL   (0x30)
#define UART_SFREGL   (0x30)
#define UART_RXFLH   (0x34)
#define UART_SFREGH   (0x34)
#define UART_BLR   (0x38)
#define UART_UASR   (0x38)
#define UART_ACREG   (0x3C)
#define UART_SCR   (0x40)
#define UART_SSR   (0x44)
#define UART_EBLR   (0x48)
#define UART_MVR   (0x50)
#define UART_SYSC   (0x54)
#define UART_SYSS   (0x58)
#define UART_WER   (0x5C)
#define UART_CFPS   (0x60)
#define UART_RXFIFO_LVL   (0x64)
#define UART_TXFIFO_LVL   (0x68)
#define UART_IER2   (0x6C)
#define UART_ISR2   (0x70)
#define UART_FREQ_SEL   (0x74)
#define UART_MDR3   (0x80)
#define UART_TX_DMA_THRESHOLD   (0x84)

/* EFR */
#define UART_EFR_ENHANCED_EN   (0x00000010u)
#define UART_EFR_ENHANCED_EN_SHIFT   (0x00000004u)
#define UART_EFR_ENHANCED_EN_DISABLE   (0x0u)
#define UART_EFR_ENHANCED_EN_ENABLE   (0x1u)
    


#endif
