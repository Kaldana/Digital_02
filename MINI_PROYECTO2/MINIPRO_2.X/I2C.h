/* 
 * File:  I2C.h
 * Author: Kenneth Aldana
 * Comments: Librer�a para comunicacion USART
 * Revision history: 
 */
/* 
 * SE ADAPTARON LAS LIBRERIAS DE KHALED MADGY
 * Enlace: https://deepbluembedded.com/
  */ 

#ifndef I2C_H
#define I2C_H
#include <xc.h>
#include <stdint.h>
#include <stdio.h>

void MAS_INIT(const unsigned long c);
void MAS_WAIT(void);
void MAS_START(void);
void MAS_RST(void);
void MAS_STOP(void);
void MAS_WRITE(int d);
int MAS_READ(int a);

#endif /* I2C_H */

