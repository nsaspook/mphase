
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "config.h"
#include "timers.h"
#include "pfb.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/tmr1.h"
#include "board/ea_display.h"
#include "mcc_generated_files/eusart1.h"

/*
 * application data structures, state machine variables
 */
APP_DATA appData = {
	.error_code = ERROR_NONE,
	.got_packet = false,
	.state = APP_INITIALIZE,
	.mc = MC_INITIALIZE,
	.sw1 = false,
	.sw2 = false,
	.sw3 = false,
	.sw4 = false,
	.sw1Changed = 0,
	.sw2Changed = 0,
	.sw3Changed = 0,
	.sw4Changed = 0,
};

extern const struct CR_DATA *cr_text;
extern const struct RS_DATA *rs_text;
const char build_date[] = __DATE__, build_time[] = __TIME__;

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
	static char mc_response[MC_RX_PKT_SZ + 2];
	int16_t offset;
	uint8_t c_down;
	static char *m_start;

	if (TimerDone(TMR_LEDS)) {
		SLED ^= 1;
		StartTimer(TMR_LEDS, LED_BLINK_MS);
	}

	switch (appData.state) {
		//Initial state
	case APP_INITIALIZE:
		if (APP_Initialize()) {
			appData.state = APP_CONNECT;
			display_ea_init(700);
			BUZZER_OFF;
			display_ea_ff(1);
			display_ea_cursor_off(1);
			display_ea_version(1000);
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
		} else {
			appData.state = APP_INITIALIZATION_ERROR;
		}
		break;
		//Initialization failed
	case APP_INITIALIZATION_ERROR:
		appData.error_code = ERROR_INITIALIZATION;
		BUZZER_ON;
		break;
	case APP_CONNECT:
		appData.state = APP_COMMUNICATE;
		if (MC_ReceivePacket(appData.receive_packet)) { // received data from controller
			clear_MC_port();
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
			if (strstr(appData.receive_packet, cr_text->r3)) { // motor poles
				if (appData.mc == MC_DRIVE) {
					appData.mc = MC_SETUP;
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
				sprintf(mc_response, cr_text->line1, cr_text->blank);
				display_ea_line(mc_response);
				sprintf(mc_response, cr_text->line1, appData.receive_packet);
				display_ea_line(mc_response);
				switch (appData.mc) {
					//Initial state
				case MC_INITIALIZE:
					sprintf(mc_response, cr_text->line2, cr_text->error);
					display_ea_line(mc_response);
					break;
				case MC_BOOT:
					clear_MC_port();
					MC_SendCommand(cr_text->c2, false);
					break;
				case MC_DRIVE:
					clear_MC_port();
					MC_SendCommand(cr_text->c3, false);
					break;
				case MC_SETUP:
					BUZZER_OFF;
					sprintf(mc_response, cr_text->line2, cr_text->s2);
					display_ea_line(mc_response);
					sprintf(mc_response, cr_text->line3, cr_text->w2);
					display_ea_line(mc_response);
					while (!appData.sw1) {
						sprintf(mc_response, cr_text->line4, cr_text->buttonp);
						display_ea_line(mc_response);
					}
					sprintf(mc_response, cr_text->line1, cr_text->blank);
					display_ea_line(mc_response);

					BUZZER_ON;
					appData.sw1 = false;
					WaitMs(100);
					BUZZER_OFF;

					clear_MC_port();
					MC_SendCommand(cr_text->dis, true);
					MC_SendCommand(cr_text->msg2, true);
					MC_SendCommand(cr_text->mpoles0, true);
					MC_SendCommand(cr_text->mphase90, true);
					MC_SendCommand(cr_text->opmode2, true);

					sprintf(mc_response, cr_text->line2, cr_text->s1);
					display_ea_line(mc_response);
					sprintf(mc_response, cr_text->line3, cr_text->w1);
					display_ea_line(mc_response);
					while (!appData.sw1) {
						sprintf(mc_response, cr_text->line4, cr_text->buttonp);
						display_ea_line(mc_response);
					}
					sprintf(mc_response, cr_text->line4, cr_text->blank);
					display_ea_line(mc_response);
					BUZZER_ON;
					appData.sw1 = false;
					WaitMs(100);
					BUZZER_OFF;

					clear_MC_port();
					MC_SendCommand(cr_text->en, true);
					MC_SendCommand(cr_text->t35, true);
					sprintf(mc_response, cr_text->line1, cr_text->blank);
					display_ea_line(mc_response);
					sprintf(mc_response, cr_text->line2, cr_text->blank);
					display_ea_line(mc_response);
					sprintf(mc_response, cr_text->line3, cr_text->blank);
					display_ea_line(mc_response);

					c_down = 15;
					while (c_down--) {
						sprintf(mc_response, cr_text->line_d, cr_text->diskmove, c_down);
						display_ea_line(mc_response);
						WaitMs(1000); // wait while spin disk moves to motor locked position
					}
					clear_MC_port();
					MC_SendCommand(cr_text->pfb, true);
					WaitMs(300);

					/* find PFB command echo from controller */
					StartTimer(TMR_MC_COMMS, MC_COMMS_MS);
					while (!MC_ReceivePacket(appData.receive_packet)) {
						if (TimerDone(TMR_MC_COMMS)) {
							appData.state = APP_INITIALIZATION_ERROR;
							break;
						}
					}

					/* find PFB resolver data from controller */
					StartTimer(TMR_MC_COMMS, MC_COMMS_MS);
					while (!MC_ReceivePacket(appData.receive_packet)) {
						if (TimerDone(TMR_MC_COMMS)) {
							appData.state = APP_INITIALIZATION_ERROR;
							break;
						}
					}

#ifdef	PRODUCTION
					if (appData.state == APP_INITIALIZATION_ERROR)
						break;
#endif

					clear_MC_port();
					sprintf(mc_response, cr_text->line1, cr_text->blank);
					display_ea_line(mc_response);
					sprintf(mc_response, cr_text->line1, appData.receive_packet);
					display_ea_line(mc_response);

					/* find and compute resolver data */
					if ((m_start = strstr(appData.receive_packet, cr_text->angle))) { // resolver angle data
						m_start[4] = ' '; // add another space for parser
						m_start[5] = '\000'; // short terminate string
						offset = get_pfb(&m_start[-8]); // pass a few of the first unused number digits
						if (offset == BADNUM) {
							sprintf(mc_response, cr_text->line2, cr_text->error);
							display_ea_line(mc_response);
							c_down = 15;
							while (c_down--) {
								sprintf(mc_response, cr_text->line_d, cr_text->c1, c_down);
								display_ea_line(mc_response);
								WaitMs(333);
							}
#ifdef	PRODUCTION
							RESET();
#endif
							appData.state = APP_INITIALIZATION_ERROR;
							break;
						}
					} else {
						offset = BADNUM2;
						sprintf(mc_response, cr_text->line2, cr_text->error);
						display_ea_line(mc_response);
						c_down = 15;
						while (c_down--) {
							sprintf(mc_response, cr_text->line_d, cr_text->c1, c_down);
							display_ea_line(mc_response);
							WaitMs(333);
						}
#ifdef	PRODUCTION
						RESET(); // something is wrong so restart mcu
#endif
						appData.state = APP_INITIALIZATION_ERROR;
						break;
					}

					sprintf(mc_response, cr_text->line2, cr_text->blank);
					display_ea_line(mc_response);
					sprintf(mc_response, rs_text->line_o, offset);
					display_ea_line(mc_response);
					WaitMs(6000);

					MC_SendCommand(cr_text->dis, true);

					sprintf(mc_response, cr_text->line2, cr_text->s3);
					display_ea_line(mc_response);
					sprintf(mc_response, cr_text->line3, cr_text->w3);
					display_ea_line(mc_response);
					while (!appData.sw1) {
						sprintf(mc_response, cr_text->line4, cr_text->buttonp);
						display_ea_line(mc_response);
					}
					sprintf(mc_response, cr_text->line1, cr_text->blank);
					display_ea_line(mc_response);
					BUZZER_ON;
					appData.sw1 = false;
					WaitMs(100);
					BUZZER_OFF;

					clear_MC_port();
					sprintf(mc_response, rs_text->line_ms, offset); // send data to controller
					MC_SendCommand(mc_response, true);
					MC_SendCommand(cr_text->msg0, true);
					MC_SendCommand(cr_text->opmode3, true);
					MC_SendCommand(cr_text->mnumber0, true);
					MC_SendCommand(cr_text->save_parm, true); // save updated offset angle to controller
					BUZZER_ON;
					WaitMs(100);
					BUZZER_OFF;

					appData.state = APP_DONE;
					appData.mc = MC_DONE;
					break;
				case MC_DONE:
					sprintf(mc_response, rs_text->line_s, cr_text->done);
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
				sprintf(mc_response, cr_text->line_h, cr_text->headder, APP_VERSION_STR);
				display_ea_line(mc_response);
				sprintf(mc_response, cr_text->line2, __DATE__);
				display_ea_line(mc_response);
				sprintf(mc_response, cr_text->line3, __TIME__);
				display_ea_line(mc_response);
				sprintf(mc_response, cr_text->line1, cr_text->pressb);
				display_ea_line(mc_response);
			}
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
		}
		break;
	case APP_DONE:
		while (true) {
			sprintf(mc_response, rs_text->line_b0);
			display_ea_line(mc_response);
			WaitMs(100);
			sprintf(mc_response, rs_text->line_b1);
			display_ea_line(mc_response);
			WaitMs(1000);
			sprintf(mc_response, rs_text->line_m, offset);
			display_ea_line(mc_response);
			WaitMs(100);
			BUZZER_OFF;
			WaitMs(1333);
			BUZZER_ON;
		};
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

// collect and buffer controller data

bool MC_ReceivePacket(char * Message)
{
	static enum McDecodeState btDecodeState = WaitForCR; //Static so maintains state on reentry, Byte read(s) from the UART buffer
	static uint16_t i = 0;

	if (EUSART1_is_rx_ready()) //Check if new data byte 
	{

		Message[i++] = EUSART1_Read();
		if (i == MC_RX_PKT_SZ) {
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

	for (i = 0; i < SIZE_TxBuffer; i++) {
		if (*data != '\0') //Keep loading bytes until end of string
			EUSART1_Write(*data++); //Load byte into the transmit buffer
		else
			break;
	}

	if (wait) {
		WaitMs(200);
	}
	return true;
}

