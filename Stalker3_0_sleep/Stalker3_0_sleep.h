
#ifndef __STALKER3_0_SLEEP_H__
#define __STALKER3_0_SLEEP_H__


#define WDTCLK_SRC_IRC_OSC          0
#define WDTCLK_SRC_WDT_OSC          1

#define WDEN              (0x1<<0)
#define WDRESET           (0x1<<1)
#define WDTOF             (0x1<<2)
#define WDINT             (0x1<<3)
#define WDPROTECT         (0x1<<4)
#define WDLOCKCLK         (0x1<<5)

#define WDT_FEED_VALUE		0x003FFFFF

#define WINDOW_MODE       0
#define PROTECT_MODE      0
#define WATCHDOG_RESET    1
#define WDLOCK_MODE       0
#define LOCKCLK_MODE      0

#define MODE_SLEEP        0
#define MODE_WORKING      1

class Stalker3_0_sleep{

private:

    int workMode;                 // working mode, sleep or working

private:

    void gotoSleep();               // goto sleep mode, untill wdt interrupt
    void wdtClkSetup();
    void wdtInit(long tc);          // init wdt

public:

    void init();

    void sleep(long ts);            // sleep for ts (s) 
    void wakeUp();                  // wake up from sleep
    void feed();                    // watch dog feed

};

#endif
