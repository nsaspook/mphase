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
#define ERROR_FW             -3

enum McDecodeState {
	WaitForCR, WaitForLF
};

typedef enum {
	APP_INITIALIZE = 0, // Initialize application
	APP_INITIALIZATION_ERROR, // Initialization Error
	APP_CONNECT,
	APP_COMMUNICATE,
	APP_SLEEP, // Sleep mode
	APP_DONE,
} APP_STATE_T;

typedef enum {
	MC_INITIALIZE = 0, // Initialize application
	MC_INITIALIZATION_ERROR, // Initialization Error
	MC_BOOT,
	MC_DRIVE,
	MC_COMMUNICATE,
	MC_SETUP,
	MC_CMD,
	MC_WAIT,
	MC_DONE,
} MC_STATE_T;

typedef struct {
	APP_STATE_T state; //APP_Tasks state
	MC_STATE_T mc; // servo controller state
	char receive_packet[MC_RX_PKT_SZ]; //message buffers
	bool got_packet; //new packet flag
	int8_t error_code;
	volatile bool sw1, sw2, sw3, sw4; //switch states
	uint8_t sw1Changed, sw2Changed, sw3Changed, sw4Changed; //switch state has changed
} APP_DATA;

struct CR_DATA {
	const char *headder, *bootb, *buttonp, *blank,
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
	*done,
	*line1,
	*line2,
	*line3,
	*line4,
	*line_d,
	*line_h;
};

struct RS_DATA {
	const char *line_m,
	*line_o,
	*line_s;
};

void APP_Tasks(void);
bool MC_ReceivePacket(char *message);
bool MC_SendCommand(const char *, bool);
void clear_MC_port(void);

#endif //APP_H