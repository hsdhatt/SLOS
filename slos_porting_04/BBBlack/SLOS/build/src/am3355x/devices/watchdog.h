
typedef unsigned int u32;
#define __arch_getl(a)                  (*(volatile unsigned int *)(a))
#define __arch_putl(v,a)                (*(volatile unsigned int *)(a) = (v))

/*      
 * TODO: The kernel offers some more advanced versions of barriers, it might
 * have some advantages to use them instead of the simple one here.
 */     
#define mb()            asm volatile("dsb sy" : : : "memory")
#define dmb()           __asm__ __volatile__ ("" : : : "memory")
#define __iormb()       dmb()
#define __iowmb()       dmb()

#define writel(v,c)     ({ u32 __v = v; __iowmb(); __arch_putl(__v,c); __v; })
        
#define readl(c)        ({ u32 __v = __arch_getl(c); __iormb(); __v; })

#define BIT(x)				(1 << x)
#define WDT_WWPS_PEND_WTGR      BIT(3)

/* Watchdog timer registers */
struct wd_timer {
        unsigned int resv1[4];
        unsigned int wdtwdsc;   /* offset 0x010 */
        unsigned int wdtwdst;   /* offset 0x014 */
        unsigned int wdtwisr;   /* offset 0x018 */
        unsigned int wdtwier;   /* offset 0x01C */
        unsigned int wdtwwer;   /* offset 0x020 */
        unsigned int wdtwclr;   /* offset 0x024 */
        unsigned int wdtwcrr;   /* offset 0x028 */
        unsigned int wdtwldr;   /* offset 0x02C */
        unsigned int wdtwtgr;   /* offset 0x030 */
        unsigned int wdtwwps;   /* offset 0x034 */
        unsigned int resv2[3];
        unsigned int wdtwdly;   /* offset 0x044 */
        unsigned int wdtwspr;   /* offset 0x048 */
        unsigned int resv3[1];
        unsigned int wdtwqeoi;  /* offset 0x050 */
        unsigned int wdtwqstar; /* offset 0x054 */
        unsigned int wdtwqsta;  /* offset 0x058 */
        unsigned int wdtwqens;  /* offset 0x05C */
        unsigned int wdtwqenc;  /* offset 0x060 */
        unsigned int resv4[39];
        unsigned int wdt_unfr;  /* offset 0x100 */
};

