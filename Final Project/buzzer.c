/*
 * buzzer.c
 *
 *  Created on: Jun 6, 2017
 *      Author: Andrea
 */
#include "msp.h"

void buzzerInit() {
    P2->DIR |= BIT5;
    P2->SEL1 &= ~BIT5;         /* configure P2.1 as simple I/O */
    P2->SEL0 &= ~BIT5;
    P2->OUT &= ~BIT5;
}


void buzzerOn(int ms, int freq) {
    P2->OUT |= BIT5;
    delayMs(ms, freq);
    P2->OUT &= ~BIT5;
}






