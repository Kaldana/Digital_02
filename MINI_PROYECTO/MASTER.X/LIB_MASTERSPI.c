#include "LIB_MASTERSPI.h"

void SPI_MASTER(void) {
    
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC5 = 0;
    SSPCON  = 0b00100000;
    SSPSTAT = 0;
}
    