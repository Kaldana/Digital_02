/* 
 * File: LCD.c  
 * Libreria para la LCD de 8 bits
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 */
#include "LCD.h"

void LCD_Init(void){
    RS=0;
    EN=0;
    LCD_Port(0x00);
    __delay_ms(20);
    LCD_Cmd(0x30);
    __delay_ms(5);
    LCD_Cmd(0x30);
    __delay_ms(11);
    LCD_Cmd(0x30);
    LCD_Cmd(0x38);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x01);
    LCD_Cmd(0x06);  
}

void LCD_Port(uint8_t a){
    PORTD = a;
}

void LCD_Write_Char(uint8_t a){
    RS = 1;             // => RS = 1
    LCD_Port(a);
    EN = 1;
    __delay_us(40);
    EN = 0;
    __delay_us(10);
}

void LCD_Cmd(uint8_t a){
    RS=0;
    LCD_Port(a);
    EN=1;
    __delay_ms(4);
    EN=0;
    __delay_ms(2);
}

void LCD_Clear(void){
    LCD_Cmd(0);
    LCD_Cmd(1);
}

void LCD_Set_Cursor(uint8_t x,uint8_t y){
	uint8_t a;
	if(x == 1)
	{
        a = 0x80 + y;
		LCD_Cmd(a);
	}
	else if(x == 2)
	{
		a = 0xC0 + y;
		LCD_Cmd(a);
	}
}

void LCD_Write_String(uint8_t *a){
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_Write_Char(a[i]);
}