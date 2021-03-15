 /* 
 * File:  I2C.c
 * Author: Kenneth Aldana
 * Comments: Librería para comunicacion I2C
 *
 * 
 * SE ADAPTARON LAS LIBRERIAS DE ELECTROSOME
 *
 */ 

#include "I2C.h"

#define _XTAL_FREQ 8000000

void MAS_INIT(const unsigned long c){
    SSPCON = 0b00101000;            //SSP Module as Master
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*c))-1; //Setting Clock Speed
    SSPSTAT = 0;
    TRISC3 = 1;                   //Setting as input as given in datasheet
    TRISC4 = 1;                   //Setting as input as given in datasheet
}

void MAS_WAIT(){
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));    
}

void MAS_START(){
    MAS_WAIT();    
    SEN = 1;  
}

void MAS_RST(){
    MAS_WAIT();
    RSEN = 1;
}

void MAS_STOP(){
    MAS_WAIT();
    PEN = 1;
}

void MAS_WRITE(int d){
    MAS_WAIT();
    SSPBUF = d; 
}

int MAS_READ(int a){
    int temp;
    MAS_WAIT();
    RCEN = 1;
    MAS_WAIT();
    temp = SSPBUF;      //Read data from SSPBUF
    MAS_WAIT();
    ACKDT = (a)?0:1;    //Acknowledge bit
    ACKEN = 1;          //Acknowledge sequence
    return temp;
}