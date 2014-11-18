#include "watchdog.h"
#define WDT_BASE        0x44E35000


void watchdog_disable(void)
{
        struct wd_timer *wdtimer = (struct wd_timer *)WDT_BASE;

        writel(0xAAAA, &wdtimer->wdtwspr);
        while (readl(&wdtimer->wdtwwps) != 0x0)
                ;
        writel(0x5555, &wdtimer->wdtwspr);
        while (readl(&wdtimer->wdtwwps) != 0x0)
                ;
}

void hw_watchdog_reset(void)
{
        unsigned int wdt_trgr_pattern = 0x1234;

    struct wd_timer *wdt = (struct wd_timer *)WDT_BASE;

        /* wait for posted write to complete */
        while ((readl(&wdt->wdtwwps)) & WDT_WWPS_PEND_WTGR)
                ;

        wdt_trgr_pattern = ~wdt_trgr_pattern;
        writel(wdt_trgr_pattern, &wdt->wdtwtgr);

        /* wait for posted write to complete */
        while ((readl(&wdt->wdtwwps) & WDT_WWPS_PEND_WTGR))
                ;
}

