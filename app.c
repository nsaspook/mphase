
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

float get_pfb(char *);

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
	const char *headder, *bootb, *cmd, *buttonp, *blank,
	*c1, *r1,
	*c2, *r2,
	*c3, *r3,
	*s1, *s2, *s3,
	*w1, *w2, *w3,
	*angle, *diskmove,
	*dis, *msg2, *mpoles0, *mphase90, *opmode2,
	*en, *t35, *pfb,
	*msg0, *mnumber0, *save_parm,
	*error,
	*done;
};

static const struct CR_DATA CrData[] = {
	{
		.headder = "Microchip Tech MCHP ",
		.bootb = "Boot Button Pressed ",
		.cmd = "-->",
		.buttonp = "When done press OK  ",
		.done = "Resolver value SET  ",
		.blank = "                    ",
		.c1 = "booting...",
		.r1 = "booting...",
		.c2 = "HVER\r\n",
		.r2 = "Drive 70",
		.c3 = "MPOLES\r\n",
		.r3 = "24",
		.angle = ".",
		.diskmove = "Wait, moving",
		.error = "Reboot SPIN AMP\r\n",
		.s1 = "Press Clear Error on",
		.w1 = "Spin Motor SCREEN   ",
		.s2 = "Press FLIP UP on    ",
		.w2 = "MID LEVEL SCREEN    ",
		.s3 = "Power Cycle Spin AMP",
		.w3 = "with Scan Safety Key",
		.dis = "DIS\r\n",
		.msg2 = "MSG 2\r\n",
		.mpoles0 = "MPOLES 0\r\n",
		.mphase90 = "MPHASE 90\r\n",
		.opmode2 = "OPMODE 2\r\n",
		.en = "EN\r\n",
		.t35 = "T 35\r\n",
		.pfb = "PFB\r\n",
		.msg0 = "MSG 0\r\n",
		.mnumber0 = "MNUMBER 0\r\n",
		.save_parm = "XXXXX\r\n",
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
	static float mphase, offset;
	int16_t offset_whole;
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
			clear_MC_port();
			BUZZER_ON;
			appData.got_packet = false;
			if (strstr(appData.receive_packet, cr_text->cmd)) { // command prompt
				strcpy(appData.receive_packet, "");
			}
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
				sprintf(mc_response, "\eO\x01\x01%s\r\n", "                   ");
				display_ea_line(mc_response);
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
					MC_SendCommand(cr_text->c3, false);
					break;
				case MC_SETUP:
					BUZZER_OFF;
					sprintf(mc_response, "\eO\x01\x02%s", cr_text->s2);
					display_ea_line(mc_response);
					sprintf(mc_response, "\eO\x01\x03%s", cr_text->w2);
					display_ea_line(mc_response);
					while (!appData.sw1) {
						sprintf(mc_response, "\eO\x01\x04%s", cr_text->buttonp);
						display_ea_line(mc_response);
					}
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

					sprintf(mc_response, "\eO\x01\x02%s", cr_text->s1);
					display_ea_line(mc_response);
					sprintf(mc_response, "\eO\x01\x03%s", cr_text->w1);
					display_ea_line(mc_response);
					while (!appData.sw1) {
						sprintf(mc_response, "\eO\x01\x04%s", cr_text->buttonp);
						display_ea_line(mc_response);
					}
					BUZZER_ON;
					appData.sw1 = false;
					WaitMs(100);
					BUZZER_OFF;

					clear_MC_port();
					MC_SendCommand(cr_text->en, true);
					MC_SendCommand(cr_text->t35, true);
					sprintf(mc_response, "\eO\x01\x01%s", cr_text->blank);
					display_ea_line(mc_response);
					c_down = 15;
					while (c_down--) {
						sprintf(mc_response, "\eO\x01\x01%s %d ", cr_text->diskmove, c_down);
						display_ea_line(mc_response);
						WaitMs(1000); // wait while spin disk moves to motor locked position
					}
					clear_MC_port();
					MC_SendCommand(cr_text->pfb, true);
					WaitMs(300);

					/* find PFB command echo from controller */
					while (!MC_ReceivePacket(appData.receive_packet)) {
					}

					/* find PFB resolver data from controller */
					while (!MC_ReceivePacket(appData.receive_packet)) {
					}

					clear_MC_port();

					/* find and compute resolver data */
					if ((m_start = strstr(appData.receive_packet, cr_text->angle))) { // resolver angle data
						m_start[4] = ' '; // add another space for parser
						m_start[5] = '\000'; // short terminate string
						sprintf(mc_response, "\eO\x01\x01%s", &m_start[-8]);
						display_ea_line(mc_response);
						mphase = get_pfb(&m_start[-8]); // pass a few of the first digits
						offset = ((24.0 / 2.0) * mphase) / 360.0;
						offset_whole = (int16_t) offset; // get the whole part
						offset = (offset - (float) offset_whole)*360.0; // extract fractional part for angle offset
						WaitMs(3000);
					} else {
						mphase = 321;
						//RESET();
					}

					sprintf(mc_response, "\eO\x01\x02 pfb %f offset %f ", mphase, offset);
					display_ea_line(mc_response);
					WaitMs(6000);

					MC_SendCommand(cr_text->dis, true);

					sprintf(mc_response, "\eO\x01\x02%s", cr_text->s3);
					display_ea_line(mc_response);
					sprintf(mc_response, "\eO\x01\x03%s", cr_text->w3);
					display_ea_line(mc_response);
					while (!appData.sw1) {
						sprintf(mc_response, "\eO\x01\x04%s", cr_text->buttonp);
						display_ea_line(mc_response);
					}
					BUZZER_ON;
					appData.sw1 = false;
					WaitMs(100);
					BUZZER_OFF;

					clear_MC_port();
					sprintf(mc_response, "MPHASE %d\r\n", mphase);
					MC_SendCommand(mc_response, true);
					MC_SendCommand(cr_text->msg0, true);
					MC_SendCommand(cr_text->mnumber0, true);
					MC_SendCommand(cr_text->save_parm, true);
					BUZZER_ON;
					WaitMs(100);
					BUZZER_OFF;

					appData.state = APP_DONE;
					appData.mc = MC_DONE;
					break;
				case MC_DONE:
					sprintf(mc_response, "%s", cr_text->done);
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
				sprintf(mc_response, "\eO\x01\x04%s", cr_text->headder);
				display_ea_line(mc_response);
			}
			StartTimer(TMR_DIS, DIS_REFRESH_MS);
		}
		break;
	case APP_DONE:
		while (true) {
			sprintf(mc_response, " MPHASE %d \r\n", mphase);
			display_ea_line(mc_response);
			WaitMs(100);
			BUZZER_OFF;
			WaitMs(50);
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

float get_pfb(char * buf)
{
	float pfb;
	char *token, pfb_ascii[BT_RX_PKT_SZ + 2], s[2] = " ";

	strcpy(pfb_ascii, buf);
	token = strtok(pfb_ascii, s); // init number search
	token = strtok(NULL, s); // look for the second number

	if (token != NULL) {
		pfb = atof(token);
		return pfb;
	} else
		return(666.66);
}
