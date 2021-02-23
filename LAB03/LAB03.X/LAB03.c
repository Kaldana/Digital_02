/*
 * File:   Lab03.c
 * Author: Kenneth Aldana
 * Carnet: 18435
 * LAB03
 *
 * Created on Feb. 11
 */

#include <xc.h>
#include "LIB_ADC.h"
#include "LCD.h"
#include <stdint.h>
#include "stdio.h"
#include "USART.h"

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//**********************************************************************************************
// Variables
// *********************************************************************************************

#define _XTAL_FREQ 8000000

//**********************************************************************************************
//Definir funciones
//**********************************************************************************************
void Setup(void);
void main(void);

//**********************************************************************************************
//Definir variables
//**********************************************************************************************

uint8_t adcvar = 0;
uint8_t adcvar1 = 0;
uint8_t receive = 0;
uint8_t Lcdvar [20];
uint8_t contador = 0;
float Vol1 = 0.0;
float Vol2 = 0.0;

//**********************************************************************************************
//Configuracion de puertos
//**********************************************************************************************
void Setup(void){
    
    ANSEL = 0b00000011;
    ANSELH = 0;
    
    TRISA = 0b00000011;
    PORTA = 0;
    
    //Declaro como entrada el RX
    TRISC = 0b0000000;
    PORTC = 0;
        
    TRISD = 0;
    PORTD = 0;
    
    TRISE = 0;
    PORTE = 0;
    
    ADC_CONFIG();
    ADCON0bits.CHS=0;
    
}

//*********************************************************************************
//Interrupciones
//*********************************************************************************
void __interrupt() ISR(void){
    
    if(RCIF==1){
        
        receive = RCREG;  
        if(receive == '+'){
            contador++;
        } 
        if(receive == '-'){
            contador--;
        } 
    }  
    
    if (ADCON0bits.GO == 0 & ADCON0bits.CHS == 0){
        adcvar = ADRESH;
        ADCON0bits.CHS = 1;
        __delay_us(25);
        ADCON0bits.GO_DONE = 1;
        PIR1bits.ADIF = 0;
    }

    if (ADCON0bits.GO == 0 & ADCON0bits.CHS == 1){
        adcvar1 = ADRESH;
        ADCON0bits.CHS = 0;
        __delay_us(25);
        ADCON0bits.GO_DONE = 1;
        PIR1bits.ADIF = 0;
    }
}

//*********************************************************************************
//Principal
//*********************************************************************************
void main(void) {
    Setup();
    LCD_Init();
    LCD_Clear();
    Set_BaudRate();
    Init_Trans();
    Init_Receive();
    
    __delay_us(25);
    ADCON0bits.GO_DONE = 1;
    
    while (1) {
        
        Vol1 = adcvar*(0.0196);
        Vol2 = adcvar1*(0.0196);
        USART_WriteStr("V1     V2   CONT \n");
        USART_Write(13);
        USART_Write(10);
        sprintf(Lcdvar, "%1.2f  %1.2f %3d", Vol1,Vol2,contador);
        
        USART_WriteStr(Lcdvar);
       
        USART_Write(13);
        USART_Write(10);
        
        LCD_Clear();
        LCD_Set_Cursor(1,1);
        LCD_Write_String("V1   V2       CONT");
        LCD_Set_Cursor(2,1);
        LCD_Write_String(Lcdvar);    
        
        __delay_ms(500);
    }
}
//*********************************************************************************
//                              FIN DEL PROGRAMA
//*********************************************************************************
