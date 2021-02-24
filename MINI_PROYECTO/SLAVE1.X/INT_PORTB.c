/*
 * File:   LIB_ADC.c
 * Author: Kenneth Aldana
 *
 * Created on February 11, 2021, 9:50 PM
 */

#include "INT_PORTB.h"

void INT_PORTB_CONFIG (){
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
}
