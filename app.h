#ifndef APP_H
#define APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "timers.h"

#define ERROR_NONE              1
#define ERROR_INITIALIZATION    -2
#define ERROR_RN_FW             -3

enum BluetoothDecodeState {
	WaitForCR, WaitForLF
};

typedef enum {
	APP_INITIALIZE = 0, // Initialize application
	APP_INITIALIZATION_ERROR, // Initialization Error
	APP_CONNECT,
	APP_COMMUNICATE,
	APP_SLEEP // Sleep mode
} APP_STATE_T;

typedef enum {
	MC_INITIALIZE = 0, // Initialize application
	MC_INITIALIZATION_ERROR, // Initialization Error
	MC_BOOT,
	MC_DRIVE,
	MC_COMMUNICATE,
} MC_STATE_T;

typedef struct {
	APP_STATE_T state; //APP_Tasks state
	MC_STATE_T mc; // servo controller state
	char receive_packet[BT_RX_PKT_SZ]; //message buffers
	char transmit_packet[BT_TX_PKT_SZ];
	bool got_packet, //new packet flag
	update_packet;
	int8_t error_code;
	volatile bool sw1, sw2, sw3, sw4; //switch states
	uint8_t sw1Changed, sw2Changed, sw3Changed, sw4Changed; //switch state has changed
	uint32_t version_code; // firmware version
} APP_DATA;

void APP_Tasks(void);
bool MC_ReceivePacket(char *message);
bool MC_SendCommand(const char *, bool);
void clear_MC_port(void);

#endif //APP_H