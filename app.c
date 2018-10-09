
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "config.h"
#include "timers.h"
#include "mcc_generated_files/tmr1.h"
#include "board/ea_display.h"

APP_DATA appData;

bool APP_Initialize(void)
{
	/****************************************************************************
	 * Initialize appData structure
	 ***************************************************************************/
	appData.error_code = ERROR_NONE;
	appData.got_packet = false;

	appData.state = APP_INITIALIZE;
	appData.sw1 = false;
	appData.sw2 = false;
	appData.sw3 = false;
	appData.sw4 = false;
	appData.led1 = 0;
	appData.led2 = 0;
	appData.led3 = 0;
	appData.led4 = 0;
	appData.led5 = 0;
	appData.led6 = 0;
	appData.update_packet = true;
	appData.sw1Changed = false;
	appData.sw2Changed = false;
	appData.sw3Changed = false;
	appData.sw4Changed = false;
	appData.timer1Flag = false;

	/****************************************************************************
	 * Peripherals Init
	 ***************************************************************************/
	TMR1_StartTimer();

	SLED = 1; // init completed
	return true;
}

//Primary application state machine

void APP_Tasks(void)
{
	IO_RA3_Toggle();
	if (TimerDone(TMR_LEDS)) {
		SLED ^= 1;
		StartTimer(TMR_LEDS, LED_BLINK_MS);
	}
	
	switch (appData.state) {
		//Initial state
	case APP_INITIALIZE:
		if (APP_Initialize()) {
			appData.state = APP_CONNECT;
			display_ea_init(500);
			display_ea_ff(1);
			display_ea_version(1000);
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
		} else {
			appData.state = APP_INITIALIZATION_ERROR;
		}
		break;
		//Initialization failed
	case APP_INITIALIZATION_ERROR:
		break;
	case APP_CONNECT:
		appData.state = APP_COMMUNICATE;
		break;
	case APP_COMMUNICATE:
		appData.state = APP_CONNECT;
		break;
	default:
		break;
	} //end switch(appData.state)
} //end APP_Tasks()
