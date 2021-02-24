/*
 * File:   LIB_ADC.c
 * Author: Kenneth Aldana
 *
 * Created on February 11, 2021, 9:50 PM
 */

#include "LIB_ADC.h"

void ADC_CONFIG() {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    ADCON0bits.ADCS = 0b10;
    ADCON0bits.GO = 0;
    ADCON0bits.ADON = 1;
    ADCON1 = 0b0000000;    
}
