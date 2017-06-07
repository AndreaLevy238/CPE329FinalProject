/*
 * timing.c
 *
 *  Created on: Jun 1, 2017
 *      Author: Andrea
 */

#include "timing.h"
#include "msp.h"

/* gets the number of megahertz of the system
 * parameters: freq: system constant for frequency
 */
float getMHz(int freq) {
    switch (freq) {
    case CS_CTL0_DCORSEL_0:
        return 1.5;
    case CS_CTL0_DCORSEL_1:
        return 3;
    case CS_CTL0_DCORSEL_2:
        return 6;
    case CS_CTL0_DCORSEL_3:
        return 12;
    case CS_CTL0_DCORSEL_4:
        return 24;
    case CS_CTL0_DCORSEL_5:
        return 48;
    default:
        return -1;
    }
}

/*creates a delay of n milliseconds at freq (constants)*/
void delayMs(int n, int freq) {
    int i, j, count;
    count = (int) 100 * getMHz(freq);
    for (j = 0; j < n; j++)
        for (i = count; i > 0; i--);      /* Delay 1 ms*/
}

/* creates a delay of n microseconds
 * assumption: freq = 24 MHz
 * */
void delayNs(int n, int freq) {
    while (n > 1) {
        n--;
    }
}

/* sets the frequency of the system
 * parameters: freq : frequency using constants
 */
void setFreq(int freq){
    CS->KEY = CS_KEY_VAL; /* unlock CS registers */
    CS->CTL0 = 0; // clear register CTL0
    CS->CTL0 = freq;
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3; // select clock sources
    CS->KEY = 0; // lock the CS registers
}


