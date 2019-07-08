#ifndef CONFIG_H
#define CONFIG_H

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr3.h"

#define APP_VERSION_STR "1.1"		//This firmware version
#define PRODUCTION

#define SIZE_TxBuffer   64		//MC_command max string length
#define MC_RX_PKT_SZ    64		//Max receive packet length

#define DIS_REFRESH_MS	70		//delay between display updates
#define MC_COMMS_MS	1000		// timeout waiting for controller response
#define LED_BLINK_MS	900		//LED blink rate
#define SLED		IO_RA0_LAT
#define BUZZER_OFF	TMR3_StopTimer()
#define BUZZER_ON	TMR3_StartTimer()

/* switch 'changed' delays so we can sequence button pressed */
#define SW_D_S		2
#define SW_D_L		6

#define MC_SS600	0		// current controller model
#define COOKED_MC			// clean prompts from controller
#define MOTOR_POLES	24.0		// motor params
#define MOTOR_PAIRS	2.0

#define	BADNUM		666
#define	BADNUM2		999

#endif //CONFIG_H