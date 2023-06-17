#include "WatchdogTimer.h"
#include "WatchdogTimer_prv.h"

void WatchdogTimer_start(WatchdogTimer_Count count) {
    WDTCR_REG.WDP_pins = count;
    WDTCR_REG.WDTOE_WDE_pins = 0b01;
}

void WatchdogTimer_restart(WatchdogTimer_Count count) {
    WatchdogTimer_stop();
    WatchdogTimer_start(count);
}

void WatchdogTimer_stop(){
    WDTCR_REG.WDTOE_WDE_pins = 0b11;
    WDTCR_REG.WDTOE_WDE_pins = 0b00;
}
