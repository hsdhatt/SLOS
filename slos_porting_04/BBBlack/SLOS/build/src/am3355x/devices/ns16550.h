
#define CONFIG_SYS_NS16550_REG_SIZE	(-4) /*./files/ti_am335x_common.h*/

#define UART_REG(x)                                                     \
        unsigned char x;                                                \
        unsigned char postpad_##x[-CONFIG_SYS_NS16550_REG_SIZE - 1];

struct serial_device {
        /* enough bytes to match alignment of following func pointer */
        char    name[16];
        int     (*start)(void);
        int     (*stop)(void);
        void    (*setbrg)(void);
        int     (*getc)(void);
        int     (*tstc)(void);
        void    (*putc)(const char c);
        void    (*puts)(const char *s);
};    

struct NS16550 {
        UART_REG(rbr);          /* 0 */
        UART_REG(ier);          /* 1 */
        UART_REG(fcr);          /* 2 */
        UART_REG(lcr);          /* 3 */
        UART_REG(mcr);          /* 4 */
        UART_REG(lsr);          /* 5 */
        UART_REG(msr);          /* 6 */
        UART_REG(spr);          /* 7 */
        UART_REG(mdr1);         /* 8 */
        UART_REG(reg9);         /* 9 */
        UART_REG(regA);         /* A */
        UART_REG(regB);         /* B */
        UART_REG(regC);         /* C */
        UART_REG(regD);         /* D */
        UART_REG(regE);         /* E */
        UART_REG(uasr);         /* F */
        UART_REG(scr);          /* 10*/
        UART_REG(ssr);          /* 11*/
};

#define thr rbr
#define iir fcr
#define dll rbr
#define dlm ier

typedef struct NS16550 *NS16550_t;


#define CONFIG_SYS_NS16550_COM1         0x44e09000

static NS16550_t serial_ports[1] = {
	(NS16550_t)CONFIG_SYS_NS16550_COM1,
};



/*
 * These are the definitions for the FIFO Control Register
 */
#define UART_FCR_FIFO_EN        0x01 /* Fifo enable */
#define UART_FCR_CLEAR_RCVR     0x02 /* Clear the RCVR FIFO */
#define UART_FCR_CLEAR_XMIT     0x04 /* Clear the XMIT FIFO */
#define UART_FCR_DMA_SELECT     0x08 /* For DMA applications */
#define UART_FCR_TRIGGER_MASK   0xC0 /* Mask for the FIFO trigger range */
#define UART_FCR_TRIGGER_1      0x00 /* Mask for trigger set at 1 */
#define UART_FCR_TRIGGER_4      0x40 /* Mask for trigger set at 4 */
#define UART_FCR_TRIGGER_8      0x80 /* Mask for trigger set at 8 */
#define UART_FCR_TRIGGER_14     0xC0 /* Mask for trigger set at 14 */

#define UART_FCR_RXSR           0x02 /* Receiver soft reset */
#define UART_FCR_TXSR           0x04 /* Transmitter soft reset */

/*
 * These are the definitions for the Modem Control Register
 */
#define UART_MCR_DTR    0x01            /* DTR   */
#define UART_MCR_RTS    0x02            /* RTS   */
#define UART_MCR_OUT1   0x04            /* Out 1 */
#define UART_MCR_OUT2   0x08            /* Out 2 */
#define UART_MCR_LOOP   0x10            /* Enable loopback test mode */
#define UART_MCR_AFE    0x20            /* Enable auto-RTS/CTS */

#define UART_MCR_DMA_EN 0x04
#define UART_MCR_TX_DFR 0x08

/*
 * These are the definitions for the Line Control Register
 *
 * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
 * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
 */
#define UART_LCR_WLS_MSK 0x03           /* character length select mask */
#define UART_LCR_WLS_5  0x00            /* 5 bit character length */
#define UART_LCR_WLS_6  0x01            /* 6 bit character length */
#define UART_LCR_WLS_7  0x02            /* 7 bit character length */
#define UART_LCR_WLS_8  0x03            /* 8 bit character length */
#define UART_LCR_STB    0x04            /* # stop Bits, off=1, on=1.5 or 2) */
#define UART_LCR_PEN    0x08            /* Parity eneble */
#define UART_LCR_EPS    0x10            /* Even Parity Select */
#define UART_LCR_STKP   0x20            /* Stick Parity */
#define UART_LCR_SBRK   0x40            /* Set Break */
#define UART_LCR_BKSE   0x80            /* Bank select enable */
#define UART_LCR_DLAB   0x80            /* Divisor latch access bit */

/*
 * These are the definitions for the Line Status Register
 */
#define UART_LSR_DR     0x01            /* Data ready */
#define UART_LSR_OE     0x02            /* Overrun */
#define UART_LSR_PE     0x04            /* Parity error */
#define UART_LSR_FE     0x08            /* Framing error */
#define UART_LSR_BI     0x10            /* Break */
#define UART_LSR_THRE   0x20            /* Xmit holding register empty */
#define UART_LSR_TEMT   0x40            /* Xmitter empty */
#define UART_LSR_ERR    0x80            /* Error */

#define UART_MSR_DCD    0x80            /* Data Carrier Detect */
#define UART_MSR_RI     0x40            /* Ring Indicator */
#define UART_MSR_DSR    0x20            /* Data Set Ready */
#define UART_MSR_CTS    0x10            /* Clear to Send */
#define UART_MSR_DDCD   0x08            /* Delta DCD */
#define UART_MSR_TERI   0x04            /* Trailing edge ring indicator */
#define UART_MSR_DDSR   0x02            /* Delta DSR */
#define UART_MSR_DCTS   0x01            /* Delta CTS */

/*
 * These are the definitions for the Interrupt Identification Register
 */
#define UART_IIR_NO_INT 0x01    /* No interrupts pending */
#define UART_IIR_ID     0x06    /* Mask for the interrupt ID */

#define UART_IIR_MSI    0x00    /* Modem status interrupt */
#define UART_IIR_THRI   0x02    /* Transmitter holding register empty */
#define UART_IIR_RDI    0x04    /* Receiver data interrupt */
#define UART_IIR_RLSI   0x06    /* Receiver line status interrupt */

/*
 * These are the definitions for the Interrupt Enable Register
 */
#define UART_IER_MSI    0x08    /* Enable Modem status interrupt */
#define UART_IER_RLSI   0x04    /* Enable receiver line status interrupt */
#define UART_IER_THRI   0x02    /* Enable Transmitter holding register int. */
#define UART_IER_RDI    0x01    /* Enable receiver data interrupt */

/* useful defaults for LCR */
#define UART_LCR_8N1    0x03


/*
 * Divide positive or negative dividend by positive divisor and round
 * to closest integer. Result is undefined for negative divisors and
 * for negative dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor)(                  \
{                                                       \
        typeof(x) __x = x;                              \
        typeof(divisor) __d = divisor;                  \
        (((typeof(x))-1) > 0 ||                         \
         ((typeof(divisor))-1) > 0 || (__x) > 0) ?      \
                (((__x) + ((__d) / 2)) / (__d)) :       \
                (((__x) - ((__d) / 2)) / (__d));        \
}                                                       \
)

#define PORT    serial_ports[port-1]


#define CONFIG_SYS_NS16550_CLK		48000000 /*ti_am335x_common.h*/
#define CONFIG_BAUDRATE			115200

static int calc_divisor (NS16550_t port)
{
	const unsigned int mode_x_div = 16;

//	return DIV_ROUND_CLOSEST(CONFIG_SYS_NS16550_CLK,
						//mode_x_div * gd->baudrate);
	return DIV_ROUND_CLOSEST(CONFIG_SYS_NS16550_CLK,
						mode_x_div * CONFIG_BAUDRATE);
}

extern void NS16550_reinit(NS16550_t com_port, int baud_divisor);
void
_serial_setbrg (const int port)
{
        int clock_divisor;

        clock_divisor = calc_divisor(PORT);
        NS16550_reinit(PORT, clock_divisor);
}

extern void NS16550_putc(NS16550_t com_port, char c);
void
_serial_putc(const char c,const int port)
{
        if (c == '\n')
                NS16550_putc(PORT, '\r');

        NS16550_putc(PORT, c);
}

void
_serial_putc_raw(const char c,const int port)
{
        NS16550_putc(PORT, c);
}

void
_serial_puts (const char *s,const int port)
{
        while (*s) {
                _serial_putc(*s++,port);
        }
}

extern char NS16550_getc(NS16550_t com_port);
int
_serial_getc(const int port)
{
        return NS16550_getc(PORT);
}

extern int NS16550_tstc(NS16550_t com_port);
int
_serial_tstc(const int port)
{
        return NS16550_tstc(PORT);
}

static inline void
serial_putc_dev(unsigned int dev_index,const char c)
{
        _serial_putc(c,dev_index);
}

static inline void
serial_putc_raw_dev(unsigned int dev_index,const char c)
{
        _serial_putc_raw(c,dev_index);
}

static inline void
serial_puts_dev(unsigned int dev_index,const char *s)
{
        _serial_puts(s,dev_index);
}

static inline int
serial_getc_dev(unsigned int dev_index)
{
        return _serial_getc(dev_index);
}

static inline int
serial_tstc_dev(unsigned int dev_index)
{
        return _serial_tstc(dev_index);
}

static inline void
serial_setbrg_dev(unsigned int dev_index)
{
        _serial_setbrg(dev_index);
}



#define DECLARE_ESERIAL_FUNCTIONS(port) \
	static int  eserial##port##_init(void) \
	{ \
		int clock_divisor; \
		clock_divisor = calc_divisor(serial_ports[port-1]); \
		NS16550_init(serial_ports[port-1], clock_divisor); \
		return 0 ; \
	} \
	static void eserial##port##_setbrg(void) \
	{ \
		serial_setbrg_dev(port); \
	} \
	static int  eserial##port##_getc(void) \
	{ \
		return serial_getc_dev(port); \
	} \
	static int  eserial##port##_tstc(void) \
	{ \
		return serial_tstc_dev(port); \
	} \
	static void eserial##port##_putc(const char c) \
	{ \
		serial_putc_dev(port, c); \
	} \
	static void eserial##port##_puts(const char *s) \
	{ \
		serial_puts_dev(port, s); \
	}

/* Serial device descriptor */
#define INIT_ESERIAL_STRUCTURE(port, __name) {	\
	.name	= __name,			\
	.start	= eserial##port##_init,		\
	.setbrg	= eserial##port##_setbrg,	\
	.getc	= eserial##port##_getc,		\
	.tstc	= eserial##port##_tstc,		\
	.putc	= eserial##port##_putc,		\
	.puts	= eserial##port##_puts,		\
}

