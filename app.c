
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

APP_DATA appData= {
	.error_code=ERROR_NONE,
	.got_packet=false,
	.state=APP_INITIALIZE,
	.update_packet=false
};

static bool APP_Initialize(void)
{
	/****************************************************************************
	 * Initialize appData structure
	 ***************************************************************************/


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
		if (TimerDone(TMR_DIS)) {
			IO_RA2_Toggle();
			display_ea_line("Microchip Tech MCHP\r\n");
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
		}
		break;
	default:
		break;
	} //end switch(appData.state)
} //end APP_Tasks()
