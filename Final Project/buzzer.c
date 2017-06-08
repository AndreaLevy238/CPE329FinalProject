/*
 * buzzer.c
 *
 *  Created on: Jun 6, 2017
 *      Author: Andrea
 */
#include "msp.h"

void buzzerInit() {
    P2->DIR |= BIT6;
    P2->SEL1 &= ~BIT6;         /* configure P2.1 as simple I/O */
    P2->SEL0 &= ~BIT6;
    P2->OUT &= ~BIT6;
}


void buzzerOn(int ms, int freq) {
    P2->OUT |= BIT6;
    delayMs(ms, freq);
    P2->OUT &= ~BIT6;
}






