
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "config.h"
#include "timers.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/tmr1.h"
#include "board/ea_display.h"
#include "mcc_generated_files/eusart1.h"

APP_DATA appData = {
	.error_code = ERROR_NONE,
	.got_packet = false,
	.state = APP_INITIALIZE,
	.mc = MC_INITIALIZE,
	.update_packet = false,
	.sw1 = false,
	.sw2 = false,
	.sw3 = false,
	.sw4 = false,
	.sw1Changed = 0,
	.sw2Changed = 0,
	.sw3Changed = 0,
	.sw4Changed = 0,
};

struct CR_DATA {
	const char *headder, *bootb,
	*c1, *r1,
	*c2, *r2,
	*c3, *r3,
	*s1, *s2, *s3,
	*error;
};

static const struct CR_DATA CrData[] = {
	{
		.headder = "Microchip Tech MCHP ",
		.bootb = "Boot Button Pressed ",
		.c1 = "booting...",
		.r1 = "booting...",
		.c2 = "HVER\r\n",
		.r2 = "Drive 70",
		.error = "Reboot SPIN AMP\r\n",
		.s1 = "Clear Error         ",
		.s2 = "FLIP UP             ",
		.s3 = "Power Cycle Spin AMP",
	},
	{
		.headder = "Microchip Tech MCHP ",
		.bootb = "Boot Button Pressed ",
		.c1 = "booting",
		.error = "Reboot SPIN AMP\r\n",
	}
};

static const struct CR_DATA *cr_text = &CrData[MC_SS600];

static bool APP_Initialize(void)
{
	TMR1_StartTimer();
	TMR0_StartTimer();

	SLED = 1; // init completed
	return true;
}

// dump serial buffer and clean possible lockup flags

void clear_MC_port(void)
{
	while (EUSART1_is_rx_ready()) { //While buffer contains old data
		EUSART1_Read(); //Keep reading until empty
		if (!EUSART1_is_rx_ready()) {
			WaitMs(1);
		}
	}
	//Clear any UART error bits
	if (1 == RCSTA1bits.OERR) {
		// EUSART1 error - restart
		RCSTA1bits.CREN = 0;
		RCSTA1bits.CREN = 1;
	}
}

//Primary application state machine

void APP_Tasks(void)
{
	static char mc_response[BT_RX_PKT_SZ + 2];

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
			BUZZER_OFF;
			display_ea_ff(1);
			display_ea_version(1000);
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
		} else {
			appData.state = APP_INITIALIZATION_ERROR;
		}
		break;
		//Initialization failed
	case APP_INITIALIZATION_ERROR:
		BUZZER_ON;
		break;
	case APP_CONNECT:
		appData.state = APP_COMMUNICATE;
		if (MC_ReceivePacket(appData.receive_packet)) { // received data from controller
			BUZZER_ON;
			appData.got_packet = false;
			if (strstr(appData.receive_packet, cr_text->r1)) { // power restart
				appData.mc = MC_BOOT;
				appData.got_packet = true;
			}
			if (strstr(appData.receive_packet, cr_text->r2)) { // hardware version
				if (appData.mc == MC_BOOT) {
					appData.mc = MC_DRIVE;
				} else {
					appData.mc = MC_INITIALIZE;
				}
				appData.got_packet = true;
			}
			if (appData.mc == MC_SETUP) {
				appData.got_packet = true;
			}
		}
		break;
	case APP_COMMUNICATE:
		appData.state = APP_CONNECT;
		if (TimerDone(TMR_DIS)) {
			IO_RA2_Toggle();
			if (appData.got_packet) {
				sprintf(mc_response, "\eO\x01\x01%s\r\n", appData.receive_packet);
				display_ea_line(mc_response);
				switch (appData.mc) {
					//Initial state
				case MC_INITIALIZE:
					sprintf(mc_response, "\eO\x01\x02%s", cr_text->error);
					display_ea_line(mc_response);
					break;
				case MC_BOOT:
					clear_MC_port();
					MC_SendCommand(cr_text->c2, false);
					break;
				case MC_DRIVE:
					clear_MC_port();
					MC_SendCommand("MPHASE\r\n", false);
					appData.mc = MC_SETUP;
					break;
				case MC_SETUP:
					sprintf(mc_response, "\eO\x01\x02%s", cr_text->error);
					display_ea_line(mc_response);
					break;
				default:
					break;
				}
				appData.got_packet = false;
			} else {
				if (appData.sw1) {
					BUZZER_ON;
					appData.sw1 = false;
					WaitMs(100);
				}
				sprintf(mc_response, "\eO\x01\x03%s", cr_text->headder);
				display_ea_line(mc_response);
			}
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
		}
		break;
	default:
		break;
	} //end switch(appData.state)

	// start programming sequence without MC 'booting'
	if (appData.sw2) {
		BUZZER_ON;
		appData.sw2 = false;
		appData.mc = MC_BOOT;
		appData.got_packet = true;
		display_ea_ff(1);
		sprintf(appData.receive_packet, cr_text->bootb);
		WaitMs(25);
	}
	BUZZER_OFF;
} //end APP_Tasks()

bool MC_ReceivePacket(char * Message)
{
	static enum BluetoothDecodeState btDecodeState = WaitForCR; //Static so maintains state on reentry   //Byte read from the UART buffer
	static uint16_t i = 0;

	if (EUSART1_is_rx_ready()) //Check if new data byte 
	{

		Message[i++] = EUSART1_Read();
		if (i == BT_RX_PKT_SZ) {
			i = 0;
		}


		switch (btDecodeState) {
		case WaitForCR:
			if (Message[i - 1] == '\r') { //See if this is the 'ENTER' key
				btDecodeState = WaitForLF; //Is CR so wait for LF
			}
			break;

		case WaitForLF:
			btDecodeState = WaitForCR; //Will be looking for a new packet next
			if (Message[i - 1] == '\n') //See if this is the LF 'CTRL-J' key
			{
				Message[i] = 0; //Got a complete message!
				i = 0;
				IO_RA3_Toggle();
				return true;
			}
			break;

		default: //Invalid state so start looking for a new start of frame
			btDecodeState = WaitForCR;
		}
	}
	return false;
}

bool MC_SendCommand(const char *data, bool wait)
{
	uint16_t i;
	//Only transmit a message if TX timer expired, or wait flag is set to false
	//We limit transmission frequency to avoid overwhelming the link
	if (TimerDone(TMR_MC_TX) || wait == false) {
		for (i = 0; i < SIZE_TxBuffer; i++) {
			if (*data != '\0') //Keep loading bytes until end of string
				EUSART1_Write(*data++); //Load byte into the transmit buffer
			else
				break;
		}
		StartTimer(TMR_MC_TX, BT_TX_MS); //Restart transmit timer
		return true;
	}
	return false;
}