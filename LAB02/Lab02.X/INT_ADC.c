#include <xc.h>
#include "LIB_7SEG.h"

unsigned char advar = 0;
unsigned char displayizq = 0;
unsigned char displayder = 0;
#define _XTAL_FREQ 8000000

void intADC(void) {
    if (ADCON0bits.GO == 0){
        advar = ADRESH;
        displayizq = (ADRESH & 0xF0)>> 4;
        displayder = (ADRESH & 0x0F);
        __delay_us(25);
        ADCON0bits.GO_DONE = 1;
        PIR1bits.ADIF = 0;      
    }
    return;
}
