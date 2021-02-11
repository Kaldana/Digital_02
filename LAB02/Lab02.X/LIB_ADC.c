#include "LIB_ADC.h"

void ADConvert(){
    if (ADCON0bits.GO == 0){
        adcvar = ADRESH;
        displayizq = (ADRESH & 0xF0)>> 4;
        displayder = (ADRESH & 0x0F);
        __delay_us(25);
        ADCON0bits.GO_DONE = 1;
        PIR1bits.ADIF = 0;      
    }
}
