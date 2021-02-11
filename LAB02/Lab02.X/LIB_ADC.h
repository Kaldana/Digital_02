/* 
 * File: INT_PORTB.h
 * Author: KENNETH ALDANA
 * Comments:
 * Revision history: 8 DE FEBRERO DE 2021
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LIB_ADC_H
#define LIB_ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000

void ADConvert();
unsigned char adcvar;
unsigned char displayizq;
unsigned char displayder;
#endif	/* INT_PORTB_H */

