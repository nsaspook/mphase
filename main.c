/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
	Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
	Device            :  PIC18F45K80
	Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

// XC8 bogus warnings from MCC code
#pragma warning disable 520
#pragma warning disable 1498 

#include "mcc_generated_files/mcc.h"
#include "app.h"
#include "config.h"

/*
 *	Main application MPHASE
 *	A simple command, response parser that generates the proper offset angle
 *	to program a direct drive servo motor system with a resolver for the
 *	drive angle rotation/speed feedback. Serial port 1 sends and receives data on the
 *	servo control port. Serial port 2 updates a 4*20 LCD display.
 *	Both serial ports are 9600 baud with no flow control.
 * 
 *	There are two control buttons for the operator interface LCD. The top button near the
 *	display is the 'OK' that should be pressed after the required action on the
 *	LCD display has been executed. The second smaller button near the bottom is
 *	the 'BOOT' button that allows the operator to bypass the wait for the
 *	servo controller auto boot sequence so the operator can program an already running
 *	motor control system. The 'BOOT' button can also reboot the MHPASE box by quickly pressing 
 *	the 'BOOT' button and then the 'OK' button in sequence.
 * 
 *	Normally the servo controller is powered off first for a resolver calibration.
 *	The MPHASE box serial cable with DB9 connector is attached to the servo DB9 serial port,
 *	power is supplied to the MPHASE box via the attached power brick and
 *	then 'RUN' power is switched on to the servo controller and motor.
 *	The MPHASE box display should display a series of prompts with audio beeps 
 *	if the serial connection is correct and the servo responds in the expected manner.
 */

typedef struct card {
	int Valid, Lenght, Offset, Array[16];
} card;

struct card Card={
	.Lenght=15,
	.Offset=1,
	.Valid=0,
};

int Buff_In = 0, i;

void main(void)
{
	// Initialize the device
	SYSTEM_Initialize();
	PIN_MANAGER_IOC();

	// If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
	// If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
	// Use the following macros to:

	// Enable high priority global interrupts
	INTERRUPT_GlobalInterruptHighEnable();

	// Enable low priority global interrupts.
	INTERRUPT_GlobalInterruptLowEnable();

	// Disable high priority global interrupts
	//INTERRUPT_GlobalInterruptHighDisable();

	// Disable low priority global interrupts.
	//INTERRUPT_GlobalInterruptLowDisable();

	// Enable the Peripheral Interrupts
	INTERRUPT_PeripheralInterruptEnable();

	// Disable the Peripheral Interrupts
	//INTERRUPT_PeripheralInterruptDisable();

	for (i = 0; i <= Card.Lenght; i++) {
		Card.Valid += (unsigned int) (Card.Array[i + Card.Offset * Card.Lenght] == Buff_In);
	}

	for (i = 0; i <= Card.Lenght; i++) {
		Card.Valid += (Card.Array[i + Card.Offset * Card.Lenght] == Buff_In) ? 1 : 0;
	}

	while (true) {
		APP_Tasks();
	}
}
/**
 End of File
 */