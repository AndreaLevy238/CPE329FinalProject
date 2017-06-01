/*
 * lcd.h
 *
 *  Created on: Jun 1, 2017
 *      Author: Andrea
 */

#ifndef LCD_H_
#define LCD_H_

#define RS 1     /* P5.0 mask */
#define RW 2     /* P5.1 mask */
#define EN 4     /* P5.2 mask */

void LCD_nibble_write(unsigned char data, unsigned char control, int freq);
void LCD_command(unsigned char command, int freq);
void LCD_data(unsigned char data, int freq);
void LCD_init(int freq);
void displayMessage(char *msg, int length, int freq);
void displayTooCold(int freq);
void displayTooHot(int freq);
void displayJustRight(int freq);

#endif /* LCD_H_ */
