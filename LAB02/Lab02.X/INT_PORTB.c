#include <xc.h>
#include "INT_PORTB.h"

void intPORTB(void) {
    //ENCENDER BITS PARA INTERUPCIONES DEL PUERTO B
    INTCON = 0b10000000;
    
    return;
}
