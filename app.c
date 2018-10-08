
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "config.h"
#include "timers.h"
#include "mcc_generated_files/tmr1.h"

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
	switch (appData.state) {
		//Initial state
	case APP_INITIALIZE:
		if (APP_Initialize()) {
			appData.state = APP_BLUETOOTH_ADVERTISE;
		} else {
			appData.state = APP_INITIALIZATION_ERROR;
		}
		break;
		//Initialization failed
	case APP_INITIALIZATION_ERROR:
		break;
		//We're not connected to a device - advertise mode
	case APP_BLUETOOTH_ADVERTISE:
		appData.state = APP_BLUETOOTH_PAIRED;
		break;
		//We are connected to a BTLE device
	case APP_BLUETOOTH_PAIRED:
		appData.state = APP_BLUETOOTH_ADVERTISE;
		break;
	default:
		break;
	} //end switch(appData.state)
} //end APP_Tasks()
