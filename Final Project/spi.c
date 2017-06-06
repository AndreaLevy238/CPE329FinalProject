/*
 * spi.c
 * SPI interfacing with 1 wire
 *  Created on: Jun 6, 2017
 *      Author: Andrea Levy and Nyssa Backes
 *  SPI Ports:
 *  1.5->UCB0CLK  (SPI CLK)
 *  1.7->UCB0SIMO (MOSI/SIMO)
 *
 *  Since this is a 1 port SPI, the CS is not needed.
 */
#include "msp.h"

void SPI_init(void){
    // Configure port bits for SPI
    P1SEL0 |= BIT7 + BIT5;     // Configure P1.6 and P1.5 for UCB0SIMO and UCB0CLK
    P1SEL1 &= ~(BIT7 + BIT5);  //

    // SPI Setup
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST;   // Put eUSCI state machine in reset

    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_SWRST | // Remain eUSCI state machine in reset
                      EUSCI_B_CTLW0_MST   | // Set as SPI master
                      EUSCI_B_CTLW0_SYNC  | // Set as synchronous mode
                      EUSCI_B_CTLW0_CKPL  | // Set clock polarity high
                      EUSCI_B_CTLW0_MSB;    // MSB first

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK; // SMCLK
    EUSCI_B0->BRW = 0x01;                    // divide by 16, clock = fBRCLK/(UCBRx)
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Initialize USCI state machine, SPI
    EUSCI_B0->IFG |= EUSCI_B_IFG_RXIFG;  // Clear TXIFG flag
}


/* Gets the data from the sensor, which is 12 bits
 */
int getTemperature(void) {
    int data;
    EUSCI_B0->TXBUF = 0;
    // USCI_A0 RX buffer ready?
    while (!(EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG));
    data = EUSCI_B0->RXBUF;
    data = data >> 4; //creates a whole number
    return data;
}

