/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#ifndef RS
#define RS RE0
#endif 

#ifndef EN
#define EN RE1
#endif 

#ifndef D0
#define D0 RD0 
#endif 
#ifndef D1
#define D1 RD1 
#endif 
#ifndef D2
#define D2 RD2 
#endif 
#ifndef D3
#define D3 RD3 
#endif 
#ifndef D4
#define D4 RD4 
#endif 
#ifndef D5
#define D5 RD5 
#endif 
#ifndef D6
#define D6 RD6 
#endif 
#ifndef D7
#define D7 RD7 
#endif 


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void LCD_Init(void);
void LCD_Write_Char(unsigned char a);
void LCD_Cmd(uint8_t a);
void LCD_Port(uint8_t a);
void LCD_Clear(void);
void LCD_Set_Cursor(uint8_t x,uint8_t y);
void LCD_Write_String(uint8_t *a);

#endif	/* XC_HEADER_TEMPLATE_H */