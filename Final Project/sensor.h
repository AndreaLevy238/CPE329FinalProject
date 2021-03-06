/*
 * sensor.h
 * adapted from http://karve.in/?p=1408
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#define DATA_IN_PIN          BIT4
#define VCC                  BIT3
#define GND                  BIT5

#define SKIP_ROM             0xCC
#define WRITE_SCRATCHPAD     0x4E
#define READ_SCRATCHPAD      0xBE
#define CONVERT_T            0x44

void InitOneWire(void);
unsigned int ResetOneWire(int freq);
void OneWire_HI(void);
void OneWire_LO(void);
void WriteZero(int freq);
void WriteOne(int freq);
unsigned int ReadBit(int freq);
void WriteOneWire (unsigned char data,int power, int freq);
int16_t ReadOneWire (int freq);
int16_t getData(int freq);



#endif /* SENSOR_H_ */
