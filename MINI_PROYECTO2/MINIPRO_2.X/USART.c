/*
 * File:   USART.c
 * Author: kenne
 *
 * Created on February 14, 2021, 10:21 AM
 */

#include "USART.h"
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000

void Set_BaudRate(void){
    SPBRG = 12;
}

void Init_Trans(void){
    TXSTAbits.TXEN = 1;
    PIR1bits.TXIF = 0;
    PIE1bits.TXIE = 0;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7  = 1;
}

void Init_Receive(void){
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;
}

void USART_Write(uint8_t a){
    while(!TRMT);
    TXREG=a;
}

void USART_WriteStr(char *a){
    uint8_t i;
    for(i=0;a[i]!='\0';i++){
        USART_Write(a[i]);
    }
}

uint8_t USART_Read(){
  while(!RCIF);
  return RCREG;
} 
