#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files/tmr1.h"

//Software timers - use these to refer to timers rather than
//integers.  Add more as needed.
//NOTE: 32767 ms max delay

enum APP_TIMERS {
    TMR_INTERNAL = 0, //Used in timers.c - do not remove or use elsewhere
    TMR_LEDS,
    TMR_MC_COMMS,
    TMR_DIS,
    TMR_BUZZ,
    TMR_SW1_DEBOUNCE,
    TMR_SW2_DEBOUNCE,
    TMR_SW3_DEBOUNCE,
    TMR_SW4_DEBOUNCE,
    TMR_MC_TX,
    TMR_BAT_CHECK,
    TMR_SPI,
    //
    //(Add timers here as needed)
    //
    TMR_COUNT //number of timers - always keep at end of enum!
};

inline void StartTimer(uint8_t timer, uint16_t count);
inline bool TimerDone(uint8_t timer);
void WaitMs(uint16_t numMilliseconds);
void _T1Interrupt(void);

#endif //TIMERS_H
