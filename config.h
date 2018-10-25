#ifndef CONFIG_H
#define CONFIG_H

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr3.h"

#define APP_VERSION_STR "0.7"       //This firmware version

//#define PRODUCTION

#define SIZE_TxBuffer   64               //MC_command max string length
#define MC_RX_PKT_SZ    64               //Max receive packet length

#define DIS_REFRESH_MS	70          //delay between display updates
#define LED_BLINK_MS	900         //LED blink rate
#define SLED		IO_RA0_LAT
#define BUZZER_OFF	TMR3_StopTimer()
#define BUZZER_ON	TMR3_StartTimer()

#define SW_D_S		2
#define SW_D_L		6

#define MC_SS600	0
#define COOKED_MC
#define MOTOR_POLES	24.0
#define MOTOR_PAIRS	2.0

#endif //CONFIG_H