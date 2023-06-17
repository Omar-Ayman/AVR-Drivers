#ifndef _WATCHDOG_TIMER_PRV_H
#define _WATCHDOG_TIMER_PRV_H

#include "WatchdogTimer.h"

struct WDTCR_RegStruct {
    u8 WDP_pins : 3;
    u8 WDTOE_WDE_pins : 2;
};

#define WDTCR_REG (*((volatile struct WDTCR_RegStruct *)0x41))

#endif