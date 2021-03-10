 /* 
 * File:  I2C.c
 * Author: Kenneth Aldana
 * Comments: Librería para comunicacion I2C
 *
 * 
 * SE ADAPTARON LAS LIBRERIAS DE KHALED MAGDY
 * Enlace: https://deepbluembedded.com
 */ 

#include <xc.h>
#include "I2C.h"

//Codigo para la configuracion del I2C del maestro

void CONFIG_I2CMAS()
{
  SSPCON  = 0x28;
  SSPCON2 = 0x00;
  SSPSTAT = 0x00;
  SSPADD = ((_XTAL_FREQ/4)/BaudRate) - 1;
  SCL_D = 1;
  SDA_D = 1; 
}
//Se inicia el proceso del maestro luego que termine la espera

void MAS_INIT()
{
    WAIT();
    SEN = 1;
}

//Se inicializa la comunicacion 
void I2C_INIT(char d)
{
    WAIT();
    SEN = 1;
    MAS_WRITE(d);
}

void R_INIT()
{
    WAIT();
    RSEN = 1;
}

//Aqui se da una espera hasta que se hayan enviado los datos
void WAIT()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void STOP()
{
    WAIT();
    PEN = 1;
}

//Se envia los datos ACK
void ACK_I2C(void)
{
	ACKDT = 0;			
    ACKEN = 1;			
    while(ACKEN);
}
//Se envia los datos NACK
void NACK_I2C(void)
{
	ACKDT = 1;			
	ACKEN = 1;			
    while(ACKEN);
}

//Se envia los datos por medio del buffer
unsigned char MAS_WRITE(unsigned char data)
{
    WAIT();
    SSPBUF = data;
    while(!SSPIF);  // Wait Until Completion
	SSPIF = 0;
    return ACKSTAT;
}

//Lecutra al momento de recibir los datos 
unsigned char MAS_READBYTE(void)
{
    WAIT();
    RCEN = 1;		  // Enable & Start Reception
	while(!SSPIF);	  // Wait Until Completion
	SSPIF = 0;		  // Clear The Interrupt Flag Bit
    WAIT();
    return SSPBUF;	  // Return The Received Byte
}

unsigned char MAS_READ(unsigned char an)
{   WAIT();
    //---[ Receive & Return A Byte & Send ACK or NACK ]---
    unsigned char data;
    RCEN = 1;              
    while(!BF);      
    data = SSPBUF;           
    if(an==0)
        ACK_I2C();            
    else
        NACK_I2C();     
    while(!SSPIF);                 
    SSPIF=0;   
    return data;
}
