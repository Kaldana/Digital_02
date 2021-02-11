#include "INT_PORTB.h"

void PuertoB() {
    if (INTCONbits.RBIF){
        if (PORTBbits.RB0 == 1){
            cont++;
        }
        
        if (PORTBbits.RB1 == 1){
            cont--;
        }
        INTCONbits.RBIF = 0;
    }
}
