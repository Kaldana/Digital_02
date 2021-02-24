/*//////////////////////////////////////////////////////////////////////////////
 * File:   LIB_SPI.c
 * Author: Kenneth Aldana 18435
 *
 */

#include "LIB_SPI.h"

void CONFIG_SPI(){
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC5 = 0;
    TRISAbits.TRISA5 = 1;
    SSPCON  = 0b00100100;
    SSPSTAT = 0;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
}
    