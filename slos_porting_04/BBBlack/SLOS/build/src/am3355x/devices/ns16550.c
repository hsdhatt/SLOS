#include "ns16550.h"	/* for NS_16550_t */

typedef unsigned char u8;
#define __arch_getb(a)                  (*(volatile unsigned char *)(a))
#define __arch_putb(v,a)                (*(volatile unsigned char *)(a) = (v))

#define mb()            asm volatile("dsb sy" : : : "memory")
#define dmb()           __asm__ __volatile__ ("" : : : "memory")
#define __iormb()       dmb()
#define __iowmb()       dmb()

#define writeb(v,c)     ({ u8  __v = v; __iowmb(); __arch_putb(__v,c); __v; })
#define readb(c)        ({ u8  __v = __arch_getb(c); __iormb(); __v; })

#define serial_out(x, y)        writeb(x, y)
#define serial_in(y)            readb(y)

#define CONFIG_SYS_NS16550_IER	0x00
#define UART_LCRVAL UART_LCR_8N1		/* 8 data, 1 stop, no parity */
#define UART_MCRVAL (UART_MCR_DTR | \
                     UART_MCR_RTS)  
#define UART_FCRVAL (UART_FCR_FIFO_EN | \
                     UART_FCR_RXSR |    \
                     UART_FCR_TXSR) 

void NS16550_init(NS16550_t com_port, int baud_divisor);


DECLARE_ESERIAL_FUNCTIONS(1);

struct serial_device eserial1_device =
        INIT_ESERIAL_STRUCTURE(1, "eserial0");

void NS16550_init(NS16550_t com_port, int baud_divisor)
{
       while (!(serial_in(&com_port->lsr) & UART_LSR_TEMT))
                ;

        serial_out(CONFIG_SYS_NS16550_IER, &com_port->ier);
	
	 serial_out(0x7, &com_port->mdr1);
	
	serial_out(UART_LCR_BKSE | UART_LCRVAL, &com_port->lcr);
        serial_out(0, &com_port->dll);
        serial_out(0, &com_port->dlm);
        serial_out(UART_LCRVAL, &com_port->lcr);
        serial_out(UART_MCRVAL, &com_port->mcr);
        serial_out(UART_FCRVAL, &com_port->fcr);
        serial_out(UART_LCR_BKSE | UART_LCRVAL, &com_port->lcr);
        serial_out(baud_divisor & 0xff, &com_port->dll);
        serial_out((baud_divisor >> 8) & 0xff, &com_port->dlm);
        serial_out(UART_LCRVAL, &com_port->lcr);

        serial_out(0, &com_port->mdr1);
}


void NS16550_reinit(NS16550_t com_port, int baud_divisor)
{
        serial_out(CONFIG_SYS_NS16550_IER, &com_port->ier);
        serial_out(UART_LCR_BKSE | UART_LCRVAL, &com_port->lcr);
        serial_out(0, &com_port->dll);
        serial_out(0, &com_port->dlm);
        serial_out(UART_LCRVAL, &com_port->lcr);
        serial_out(UART_MCRVAL, &com_port->mcr);
        serial_out(UART_FCRVAL, &com_port->fcr);
        serial_out(UART_LCR_BKSE, &com_port->lcr);
        serial_out(baud_divisor & 0xff, &com_port->dll);
        serial_out((baud_divisor >> 8) & 0xff, &com_port->dlm);
        serial_out(UART_LCRVAL, &com_port->lcr);
}

int NS16550_tstc(NS16550_t com_port)
{
        return (serial_in(&com_port->lsr) & UART_LSR_DR) != 0;
}

#define WATCHDOG_RESET	hw_watchdog_reset

extern void hw_watchdog_reset(void);

char NS16550_getc(NS16550_t com_port)
{
        while ((serial_in(&com_port->lsr) & UART_LSR_DR) == 0) {
                WATCHDOG_RESET();
        }
        return serial_in(&com_port->rbr);
}


void NS16550_putc(NS16550_t com_port, char c)
{
        while ((serial_in(&com_port->lsr) & UART_LSR_THRE) == 0)
                ;
        serial_out(c, &com_port->thr);

        /*
         * Call watchdog_reset() upon newline. This is done here in putc
         * since the environment code uses a single puts() to print the complete
         * environment upon "printenv". So we can't put this watchdog call
         * in puts().
         */
#if 1
        if (c == '\n')
                WATCHDOG_RESET();
#endif
}

