/* 
 * File:  USART.h
 * Author: KENNETH ALDANA
 * Comments: Librería para comunicacion USART
 * Revision history: 
 */
/* 
 * SE ADAPTARON LAS LIBRERIAS DE KHALED MADGY
 * Enlace: https://deepbluembedded.com/interfacing-i2c-lcd-16x2-tutorial-with-pic-microcontrollers-mplab-xc8/
  */ 

#ifndef I2C_H
#define I2C_H

#define _XTAL_FREQ             4000000

#define BaudRate               100000
#define SCL_D                  TRISC3
#define SDA_D                  TRISC4

void CONFIG_I2CMAS();
void WAIT();
void MAS_INIT();
void I2C_INIT(char d);
void R_INIT();
void STOP();
void ACK_I2C();
void NACK_I2C();
unsigned char MAS_WRITE(unsigned char data);
unsigned char MAS_READBYTE();
unsigned char MAS_READ(unsigned char);

#endif /* I2C_H */

