#ifndef _WATCHDOG_TIMER_H
#define _WATCHDOG_TIMER_H

#include <VL/Types.h>

typedef ENUM_PACKED WatchdogTimer_Count {
    WatchdogTimer_16k   = 0b000,
    WatchdogTimer_32k   = 0b001,
    WatchdogTimer_64k   = 0b010,
    WatchdogTimer_128k  = 0b011,
    WatchdogTimer_256k  = 0b100,
    WatchdogTimer_512k  = 0b101,
    WatchdogTimer_1024k = 0b110,
    WatchdogTimer_2048k = 0b111,
} WatchdogTimer_Count;

void WatchdogTimer_start(WatchdogTimer_Count count);

void WatchdogTimer_restart(WatchdogTimer_Count count);

void WatchdogTimer_stop();

#endif