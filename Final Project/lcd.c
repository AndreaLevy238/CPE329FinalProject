/*
 *  Created on: Apr 13, 2017
 *      Author: Andrea Levy and Nyssa Backes
 *  with code from: www.MicroDigitalEd.com
 * Data and control pins share Port 5.
 * This program does not poll the status of the LCD.
 * It uses delay to wait out the time LCD controller is busy.
 * Timing is more relax than the HD44780 datasheet to accommodate the
 * variations among the LCD modules.
 * You may want to adjust the amount of delay for your LCD
 * controller.
 *
 * Tested with Keil 5.20 and MSP532 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */
#include "lcd.h"
#include "msp.h"

void LCD_init(int freq) {
    P5->DIR = 0xFF;     /* make P5 pins output for data and controls */
    delayMs(30, freq);                /* initialization sequence */
    LCD_nibble_write(0x30, 0, freq);
    delayMs(10, freq);
    LCD_nibble_write(0x30, 0, freq);
    delayMs(1, freq);
    LCD_nibble_write(0x30, 0, freq);
    delayMs(1, freq);
    LCD_nibble_write(0x20, 0, freq);  /* use 4-bit data mode */
    delayMs(1, freq);

    LCD_command(0x28, freq);      /* set 4-bit data, 2-line, 5x7 font */
    LCD_command(0x06, freq);      /* move cursor right after each char */
    LCD_command(0x01, freq);      /* clear screen, move cursor to home */
    LCD_command(0x0F, freq);      /* turn on display, cursor blinking */
}

/* With 4-bit mode, each command or data is sent twice with upper
 * nibble first then lower nibble.
 */
void LCD_nibble_write(unsigned char data, unsigned char control, int freq) {
    data &= 0xF0;           /* clear lower nibble for control */
    control &= 0x0F;        /* clear upper nibble for data */
    P5->OUT = data | control;       /* RS = 0, R/W = 0 */
    P5->OUT = data | control | EN;  /* pulse E */
    delayNs(37, freq);
    P5->OUT = data;                 /* clear E */
    P5->OUT = 0;
}

/*gives an 1-byte command to a 4bit LCD
 *parameter: command - the code of the command you want to give
 *parameter: freq - the (constant in timing.h) freq we are running the board at
 *assumption: command is a valid command to the LCD
 */
void LCD_command(unsigned char command, int freq) {
    LCD_nibble_write(command & 0xF0, 0, freq);    /* upper nibble first */
    LCD_nibble_write(command << 4, 0, freq);      /* then lower nibble */

    if (command < 4)
        delayMs(4, freq);         /* commands 1 and 2 need up to 1.64ms */
    else
        delayMs(1, freq);         /* all others 40 us */
}

/* writes data to the board at freq
 *parameter: data - character to write to board (using ASCII table)
 *parameter: freq - (constant in timing.h) frequency of the board
 **/
void LCD_data(unsigned char data, int freq) {
    LCD_nibble_write(data & 0xF0, RS, freq);    /* upper nibble first */
    LCD_nibble_write(data << 4, RS, freq);      /* then lower nibble  */

    delayMs(1, freq);
}

/* displays a msg of length n on the board
 * assumption: the msg fits on the LCD
 * */
void displayMessage(char* msg, int length, int freq) {
    int i;
    for (i = 0; i < length; i++) {
        LCD_data(msg[i], freq);
    }
}

void displayTooCold(int freq) {
   LCD_command(1, freq);                   //clear display
   delayMs(500, freq);                     //cursor at beginning of first line
   LCD_command(0x80, freq);
   displayMessage("Too cold!", 9, freq);
   LCD_command(0xC0, freq);                //starts new line
   displayMessage("Temp is NUM", 11, freq);
   delayMs(500, freq);
}

void displayTooHot(int freq) {
   LCD_command(1, freq);                   //clear display
   delayMs(500, freq);                     //cursor at beginning of first line
   LCD_command(0x80, freq);
   displayMessage("Too hot!", 8, freq);
   LCD_command(0xC0, freq);                //starts new line
   displayMessage("Temp is NUM", 11, freq);
   delayMs(500, freq);
}

void displayJustRight(int freq) {
   LCD_command(1, freq);                  //clear display
   delayMs(500, freq);                    //cursors at beginning of first line
   LCD_command(0x80, freq);
   displayMessage("Just right!", 11, freq);
   LCD_command(0xC0, freq);               //starts new line
   displayMessage("Enjoy! :)", 9, freq);
   delayMs(500, freq);
}
