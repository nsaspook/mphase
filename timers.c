#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "timers.h"
#include "app.h"

extern APP_DATA appData;

static volatile uint16_t tickCount[TMR_COUNT] = {0};

//**********************************************************************************************************************
// Start one of the software timers

inline void StartTimer(uint8_t timer, uint16_t count)
{
	tickCount[timer] = count << 1; //Interrupt is every 500us but StartTimer() takes multiple of 1ms so multiply by 2
}

//**********************************************************************************************************************
// Check if one of the software software timers has timed out

inline bool TimerDone(uint8_t timer)
{
	if (tickCount[timer] == 0) { //Check if counted down to zero
		return true; //then return true
	}
	return false; //else return false
}

//**********************************************************************************************************************
// Simple delay for n milliseconds (blocking)

void WaitMs(uint16_t numMilliseconds)
{
	StartTimer(TMR_INTERNAL, numMilliseconds); //Start software timer and wait for it to count down
	while (!TimerDone(TMR_INTERNAL)) {
		//		Idle();
	} //Enter idle mode to reduce power while waiting
} //(timer interrupt will wake part from idle)

//**********************************************************************************************************************
// Timer 1 interrupt routine - software timers

void _T1Interrupt(void)
{
	uint8_t i;

	//Decrement each software timer
	for (i = 0; i < TMR_COUNT; i++) {
		if (tickCount[i] != 0) {
			tickCount[i]--;
		}
	}
	IO_RA1_Toggle();
}

