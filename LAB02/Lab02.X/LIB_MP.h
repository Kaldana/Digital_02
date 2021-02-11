/* 
 * File: INT_PORTB.h
 * Author: KENNETH ALDANA
 * Comments:
 * Revision history: 8 DE FEBRERO DE 2021
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LIB_MP_H
#define LIB_MP_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000

void MP7SEG();
unsigned char display[16]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67,0x77,0x7c,0x39,0b1011110,0xf9,0x71};
unsigned char displayizq;
unsigned char displayder;
#endif	/* INT_PORTB_H */

