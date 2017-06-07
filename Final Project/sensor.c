/*
 * sensor.c
 *
 *  Created on: Jun 6, 2017
 *      Author: Andrea
 */
#include "msp.h"
#include "sensor.h"
#include "timing.h"

void InitOneWire(void)
{
    //General GPIO Defines
    P2->DIR |= (VCC + GND);
    P2->OUT |= VCC;
    P2->OUT &= ~GND;
}

unsigned int ResetOneWire(int freq) {
    /* Steps to reset one wire bus
     * Pull bus low
     * hold condition for 480us
     * release bus
     * wait for 60us
     * read bus
     * if bus low then device present set / return var accordingly
     * wait for balance period (480-60)
     */
    int device_present;
    OneWire_LO(); //Drive bus low
    delayNs(480, freq); //hold for 480us
    P2->DIR &= ~DATA_IN_PIN; //release bus
    device_present = (P2->IN & DATA_IN_PIN) ? 1 : 0;
    delayNs(480, freq); //hold for 480us
    return device_present;
}
void OneWire_HI(void){
    P2->DIR |= DATA_IN_PIN; //set port as output
    P2->OUT |= DATA_IN_PIN; //set port high

}
void OneWire_LO(void) {
    P2->DIR |= DATA_IN_PIN; //set port as output
    P2->OUT &= ~DATA_IN_PIN; //set port low
}
void WriteZero(int freq) {
    /*Steps for master to transmit logical zero to slave device on bus
     * pull bus low
     * hold for 60us
     * release bus
     * wait for 1us for recovery
     */
    OneWire_LO();
    delayNs(60, freq);
    P2->DIR &= ~DATA_IN_PIN; //release bus
    delayNs(1, freq);
}
void WriteOne(int freq) {
   /* Steps for master to transmit logical one to slave device on bus
    * pull bus low
    * hold for 5usrelease bus
    * wait for 1us for recovery
    */
    OneWire_LO();
    delayNs(5, freq);
    P2->DIR &= ~DATA_IN_PIN; //release bus
    delayNs(56, freq); //sample time slot for slave
}
unsigned int ReadBit(int freq) {
    /*Steps for master to issue a read request to slave device on bus
     * pull bus low
     * hold for 5us
     * release bus
     * wait for 45us for recovery
     */
    unsigned int bit = 0;
    OneWire_LO();
    delayNs(5, freq);
    P2->DIR &= ~DATA_IN_PIN; //release bus
    delayNs(10, freq);
    if (P2->IN & DATA_IN_PIN) {
        bit = 1;
    }
    delayNs(46, freq);
    return bit;

}
void WriteOneWire (unsigned char data,int power, int freq) {
    unsigned int i;
    for (i=8; i > 0; i--) {
        if (data & 0x01) {
            WriteOne(freq);
        }
        else {
            WriteZero(freq);
        }
        data = data >> 1;
    }
    if (power == 1) {
        OneWire_HI();
        delayMs(10, freq);
    }
}
unsigned int ReadOneWire (int freq) {
    unsigned int i;
    unsigned int data = 0;
    P2->DIR &= ~DATA_IN_PIN; //set port in input mode
    for(i=16; i>0; i--) {
        data= data >> 1;
        if (ReadBit(freq)) {
            data |= 0x8000;
        }
    }
    return data;

}
int getData(int freq) {
    unsigned int temp;
    ResetOneWire(freq);
    WriteOneWire(SKIP_ROM, 0, freq);
    WriteOneWire(CONVERT_T, 1, freq);
    delayMs(750, freq);
    ResetOneWire(freq);
    WriteOneWire(SKIP_ROM, 0, freq);
    WriteOneWire(READ_SCRATCHPAD, 0, freq);
    temp = ReadOneWire(freq);
    return temp;
}
