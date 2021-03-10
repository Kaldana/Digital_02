/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void Set_BaudRate(void);
void Init_Trans(void);
void Init_Receive(void);
void USART_Write(uint8_t a);
void USART_WriteStr(char *a);
uint8_t USART_Read(void);

#endif	/* USART_H */

