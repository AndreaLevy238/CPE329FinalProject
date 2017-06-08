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
int16_t getTemperature(int16_t data);
int16_t temperature;

void main(void)
{
    temperature = 0;
    setFreq(CS_CTL0_DCORSEL_4);
    buzzerInit();
	InitOneWire();
	LCD_init(CS_CTL0_DCORSEL_4);
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    temperature = getData(CS_CTL0_DCORSEL_4);
    displayTooCold(CS_CTL0_DCORSEL_4, temperature);

}

void justRight(int freq) {
    buzzerOn(BUZZER_PERIOD, freq);
    displayJustRight(freq);
}

int16_t getTemperature(int16_t data) {
    if (data < 0) {
        data = -data;
    }
}

