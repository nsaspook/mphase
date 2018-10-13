
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
#include "mcc_generated_files/eusart1.h"

APP_DATA appData = {
	.error_code = ERROR_NONE,
	.got_packet = false,
	.state = APP_INITIALIZE,
	.mc = MC_INITIALIZE,
	.update_packet = false,
	.sw1=false,
	.sw2=false,
	.sw3=false,
	.sw4=false,
	.sw1Changed=false,
	.sw2Changed=false,
	.sw3Changed=false,
	.sw4Changed=false,
};

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
			if (strstr(appData.receive_packet, "booting...")) { // power restart
				appData.mc = MC_BOOT;
				appData.got_packet = true;
			}
			if (strstr(appData.receive_packet, "Drive 70")) { // hardware version
				if (appData.mc == MC_BOOT) {
					appData.mc = MC_DRIVE;
				} else {
					appData.mc = MC_INITIALIZE;
				}
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
					display_ea_line("Reboot SPIN AMP\r\n");
					break;
				case MC_BOOT:
					clear_MC_port();
					MC_SendCommand("HVER\r\n", false);
					break;
				case MC_DRIVE:
					clear_MC_port();
					MC_SendCommand("MPHASE\r\n", false);
					break;
				default:
					break;
				}
			} else {
				display_ea_line("Microchip Tech MCHP\r\n");
			}
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
			BUZZER_OFF;
		}
		break;
	default:
		break;
	} //end switch(appData.state)
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

bool MC_GetResponse(char *data)
{
	uint16_t byteCount = 0;
	char newByte;

	StartTimer(TMR_RN_COMMS, 600); //Start 600ms timeout for routine

	while (byteCount < BT_RX_PKT_SZ) //Don't accept more than the buffer size
	{
		if (EUSART1_is_rx_ready()) //Check if new data byte from BT module and return if nothing new
		{
			IO_RA3_Toggle();
			newByte = EUSART1_Read(); //Read the data byte for processing
			*data++ = newByte; //Add it to the buffer
			byteCount++; //Keep track of the number of bytes received
			if (newByte == '\n') //Check if got linefeed
				return true; //If linefeed then return success
		}
		if (TimerDone(TMR_RN_COMMS)) //Check if timed out
			return false; //If timed out then return failure
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