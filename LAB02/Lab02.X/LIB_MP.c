#include "LIB_MP.h"

void MP7SEG(){
    if (INTCONbits.T0IF){

        if (PORTEbits.RE0){
            PORTEbits.RE0 = 0;
            PORTC = display[displayder];
            PORTEbits.RE1 = 1;
            __delay_ms(8);
        }
        if (PORTEbits.RE1){
            PORTEbits.RE1 = 0;
            PORTC = display[displayizq];
            PORTEbits.RE0 = 1;
            __delay_ms(8);
        }
        INTCONbits.T0IF = 0;
    }
}
