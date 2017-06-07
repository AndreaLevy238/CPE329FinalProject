//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "timing.h"
#include "lcd.h"
#include "buzzer.h"
#include "sensor.h"

void justRight(int freq);
int temperature;

void main(void)
{

    buzzerInit();
	SPI_init();
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    for (;;) {
        temperature  = getData();
        displayTooCold(CS_CTL0_DCORSEL_3, temperature);
    }
}

void justRight(int freq) {
    buzzerOn(BUZZER_PERIOD, freq);
    displayJustRight(freq);
}

