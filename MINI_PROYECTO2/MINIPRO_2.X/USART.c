 /* 
 * File:  I2C.c
 * Author: Kenneth Aldana
 * Comments: Librería para USART
 *
 * 
 * SE ADAPTARON LAS LIBRERIAS DE ELECTROSOME
 *
 */ 

#include <xc.h>
#include <stdint.h>
#include "USART.h"
#define _XTAL_FREQ 8000000

void USART_Initialize(const long int baudrate){
    long int x;
    
    //Select 8bit transmission 
    TXSTAbits.TX9 = 0;
    //Enable Transmit
    TXSTAbits.TXEN = 1;
    //Async mode select
    TXSTAbits.SYNC = 0;
    //Operate in Low Speed
    TXSTAbits.BRGH = 0;
    BAUDCTLbits.BRG16 = 0;

    //Enable Serial Port
    RCSTAbits.SPEN = 1;
    //Enable continuous receive
    RCSTAbits.CREN = 1;

    x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);   //SPBRG for Low Baud Rate 
    SPBRG = x;
    
    //Enable global interrupt
    INTCONbits.GIE = 1;
    //Enable Peripheral interrupt
    INTCONbits.PEIE = 1;

    //Enable receive interrupt
    PIE1bits.RCIE = 1;
    //Enable transmitive interrupt
    PIE1bits.TXIE = 1;
}