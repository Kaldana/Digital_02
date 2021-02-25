#include "LIB_MASTERSPI.h"

void SPI_MASTER(void) {
    
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC0 = 0;
    PORTCbits.RC0 = 0;
    
    TRISCbits.TRISC1 = 0;
    PORTCbits.RC1 = 1;
    
    TRISCbits.TRISC2 = 0;
    PORTCbits.RC2 = 1;
    
    SSPCON  = 0b00100000;
    SSPSTAT = 0;
    
    
}
    