
#include "Stalker3_0_sleep.h"
#include "mbed.h"

extern "C"{
void WDT_IRQHandler(void)
{
    for(int i=0; i<10; i++)
    {
        led2 = 1;
        wait(0.1);
        led2 = 0;
        wait(0.1);
    }
    LPC_WWDT->MOD &= ~WDTOF;		/* clear the time-out flag and interrupt flag */
    LPC_WWDT->MOD &= ~WDINT;		/* clear the time-out flag and interrupt flag */
		WDTInit();
}


void Stalker3_0_sleep::gotoSleep()               // goto sleep mode, untill wdt interrupt
{
    LPC_PMU->PCON          |= 0x01;                                     /* ?????????           */
    LPC_SYSCON->PDSLEEPCFG |= (1UL << 3);                               /* ??BOD???????        */
    SCB->SCR &= ~(1UL << 2);                                            /* ??????                 */

}

void Stalker3_0_sleep::wdtClkSetup()
{
  /* Freq = 0.5Mhz, div_sel is 0x1F, divided by 64. WDT_OSC should be 7.8125khz */
  LPC_SYSCON->WDTOSCCTRL = (0x1<<5)|0x1F;
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    /* Let WDT clock run */

  /* Enables clock for WDT */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<15);
  LPC_WWDT->CLKSEL = clksrc;        /* Select clock source */

}

void Stalker3_0_sleep::wdtInit(long tc)          // init wdt
{
    uint32_t regVal;

    LPC_WWDT->TC = 0x3fffff;
#if 0
  regVal = WDEN | WDRESET;
  LPC_WWDT->MOD = regVal;
#else
  regVal = WDEN;
  LPC_WWDT->MOD = regVal;
#endif

  LPC_WWDT->FEED = 0xAA;		/* Feeding sequence */
  LPC_WWDT->FEED = 0x55;    

  NVIC_EnableIRQ(WDT_IRQn);
  NVIC_SetPriority(WDT_IRQn, 2);
  return;

}

void Stalker3_0_sleep::init()
{

}

void Stalker3_0_sleep::sleep(long ts)            // sleep for ts (s) 
{

}

void Stalker3_0_sleep::wakeUp()                  // wake up from sleep
{

}

void Stalker3_0_sleep::feed()                    // watch dog feed
{
  LPC_WWDT->FEED = 0xAA;		/* Feeding sequence */
  LPC_WWDT->FEED = 0x55;
  return;

}
