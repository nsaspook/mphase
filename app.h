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

typedef enum {
    APP_INITIALIZE = 0, // Initialize application
    APP_INITIALIZATION_ERROR, // Initialization Error
    APP_BLUETOOTH_ADVERTISE, // Advertise the bluetooth connection, not connected
    APP_BLUETOOTH_PAIRED, // Bluetooth module is paired to server, we idle
    APP_SLEEP // Sleep mode
} APP_STATE_T;

typedef struct {
    APP_STATE_T state; //APP_Tasks state
    char receive_packet[BT_RX_PKT_SZ]; //message buffers
    char transmit_packet[BT_TX_PKT_SZ];
    bool got_packet, //new packet flag
    update_packet,
    sendSwitches, //new switch states ready to send
    ADCcalFlag, //ADC is calibrated if true
    led1, led2, led3, led4, led5, led6, //LED states
    oled1, oled2, oled3, oled4;
    int8_t error_code;
    volatile bool sw1, sw2, sw3, sw4, //switch states
    sw1Changed, sw2Changed, sw3Changed, sw4Changed, //switch state has changed
    RTCCalarm, //RTCC alarm has tripped
    accumReady, //ADC accumulator is done
    ADCinUse, //ADC or accumulator register is currently in use
    timer1Flag, //Timer1 has tripped
    CNint, //CN interrupt has tripped (flag to exit sleep)
    sleepFlag; //sleep mode triggered
    uint16_t potValue, potValueOld, potValueLastTX, version_code; //potentiometer values - current, previous, and last transmitted, firmware version
} APP_DATA;

void APP_Tasks(void);
bool APP_Initialize(void);

#endif //APP_H