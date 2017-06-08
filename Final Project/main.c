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
    while(1) {
        temperature = getData(CS_CTL0_DCORSEL_4);
        temperature = getTemperature(temperature);
        if(temperature > 71) {
            displayTooHot(CS_CTL0_DCORSEL_4, temperature);
        }
        else if (temperature < 44) {
            displayTooCold(CS_CTL0_DCORSEL_4, temperature);
        }
        else {
           justRight(CS_CTL0_DCORSEL_4);
        }

    }

}

void justRight(int freq) {
    buzzerOn(BUZZER_PERIOD, freq);
    displayJustRight(freq);
}

int16_t getTemperature(int16_t data) {
    int temp = (int) data;
    temp = temp >> 4;
    data = (int16_t) temp;
    return data;
}

