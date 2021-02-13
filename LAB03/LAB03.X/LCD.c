/* 
 * File: LCD.c  
 * Libreria para la LCD de 8 bits
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 */
#include "LCD.h"

void Lcd_Init(void){
    TRISE = 0;
    TRISD = 0;
    __delay_ms(5);
    
}

void Lcd_Cmd(uint8_t cmd){
	RS = 0;
    RW = 0;
    Lcd_Dato(cmd);
    EN = 1;
    __delay_ms(10);
    EN = 0;
    __delay_ms(1);
}

void Lcd_Set_Cursor(uint8_t a, uint8_t b) {
	uint8_t c;
	if(a == 1) 	{
        c = 0x80;
		Lcd_Cmd(c);
	}
	else if(a == 2)	{
		c = 0xC0 ;
		Lcd_Cmd(c);
	}
}

void Lcd_data(uint8_t data){
   RS = 1;
   RW = 0;
   Lcd_Dato(data);             //Data transfer
   EN = 1;
   __delay_ms(12);
   EN = 0;
   __delay_ms(2);
}

void Lcd_Dato (uint8_t dato){
    if (dato & 1){D0 = 1;} else {D0 = 0;}
    if (dato & 2){D1 = 1;} else {D1 = 0;}
    if (dato & 4){D2 = 1;} else {D2 = 0;}
    if (dato & 8){D3 = 1;} else {D3 = 0;}
    if (dato & 16){D4 = 1;} else {D4 = 0;}
    if (dato & 32){D5 = 1;} else {D5 = 0;}
    if (dato & 64){D6 = 1;} else {D6 = 0;}
    if (dato & 128){D7 = 1;} else {D7 = 0;}
    }

void Lcd_Data_String(uint8_t *a){
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Data(a[i]);
}

void Clear(void){
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}