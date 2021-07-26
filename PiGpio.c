/*****************************************************************************
**
** blueberryMSX
** https://github.com/pokebyte/blueberryMSX
**
** An MSX Emulator for Raspberry Pi based on blueMSX
**
** Copyright (C) 2014 Akop Karapetyan
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>

#include <wiringPi.h>
#include <wiringShift.h>

#include "Led.h"


#define CLOCK 3
#define LATCH 4
#define DATA  25

#define CAPS  0x05
#define HANS  0x0A
#define IOLD  0x10
#define SLT1  0x20
#define SLT2  0x40
#define POWER 0x80
#define FDD0  0xFF
#define FDD1  0xFF

static int ledBitMap = 0;

static void gpioShiftLeds();

void gpioInit()
{
	wiringPiSetup();

	pinMode(CLOCK, OUTPUT) ;
	pinMode(LATCH, OUTPUT) ;
	pinMode(DATA,  OUTPUT) ;
	printf("Ligting up Power led");
	ledBitMap = POWER;
	gpioShiftLeds();
	getchar();
	printf("Ligting up Caps led");
	ledBitMap = CAPS;
	gpioShiftLeds();
	getchar();
	printf("Ligting up HAN led");
	ledBitMap = HANS;
	gpioShiftLeds();
	getchar();
	printf("Ligting up I/O led");
	ledBitMap = IOLD;
	gpioShiftLeds();
	getchar();
	printf("Ligting up Slot1 led");
	ledBitMap = SLT1;
	gpioShiftLeds();
	getchar();
	printf("Ligting up Slot2 led");
	ledBitMap = SLT2;
	gpioShiftLeds();
	getchar();
}

void gpioShutdown()
{
	ledBitMap = 0;
	gpioShiftLeds();
}

/*int ledGetSlt1(){
	ledBitMap = SLT1;
	gpioShiftLeds();
}*/

void gpioUpdateLeds()
{
	int oldBitMap = ledBitMap;

	if (ledGetFdd1()) {
		ledBitMap |= FDD0;
	} else {
		ledBitMap &= ~FDD0;
	}

	if (ledGetFdd2()) {
		ledBitMap |= FDD1;
	} else {
		ledBitMap &= ~FDD1;
	}

	if (oldBitMap != ledBitMap) {
		gpioShiftLeds();
	}
}

static void gpioShiftLeds()
{
	digitalWrite(LATCH, LOW);
	shiftOut(DATA, CLOCK, LSBFIRST, ledBitMap);
	digitalWrite(LATCH, HIGH);
}

