#ifndef CONFIG_H
#define CONFIG_H

#include "mcc_generated_files/pin_manager.h"

//Buffer sizes
#define SIZE_RxBuffer   64               //UART RX software buffer size in bytes
#define SIZE_TxBuffer   64               //UART TX software buffer size in bytes
#define SIZE_SPI_Buffer 64

#define BT_RX_PKT_SZ    64               //Max receive packet length
#define BT_TX_PKT_SZ    64               //Max transmit packet length

#define DEBOUNCE_MS         75          //debounce time for switches 1 - 4
#define ADC_REFRESH_MS      10          //delay between ADC reads
#define POT_TX_MS           50         //delay between transmitting new pot values
#define LED_BLINK_MS        900         //LED blink rate for advertise mode
#define BT_TX_MS            10         //minimum time between consecutive BTLE message transmissions
#define SLED        IO_RA0_LAT

#endif //CONFIG_H