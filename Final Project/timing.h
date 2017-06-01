/*
 * timing.h
 *
 *  Created on: Jun 1, 2017
 *      Author: Andrea
 */

#ifndef TIMING_H_
#define TIMING_H_

void delayMs(int n, int freq);
void delayNs(int n, int freq);
void setFreq(int freq);
float getMHz(int freq);

#endif /* TIMING_H_ */
