/*
 * File:   Lab01.c
 * Author: Kenneth Aldana
 * Carnet: 18435
 * Laboratorio 02
 *
 * Created on January 31, 2021, 9:56 PM
 */


#include <xc.h>

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

#include <xc.h>

//**********************************************************************************************
// Variables
// *********************************************************************************************

#define _XTAL_FREQ 8000000

//**********************************************************************************************
//Definir funciones
//**********************************************************************************************
char cont = 0;

//**********************************************************************************************
//Configuracion de puertos
//**********************************************************************************************
void Setup(void){
    
    ANSEL = 0b00000001;
    ANSELH = 0;
    
    TRISA = 0b00000001;
    PORTA = 0;
    
    TRISB = 0b00000011;
    PORTB = 0;
    
    TRISC = 0;
    PORTC = 0;
    
    TRISD = 0;
    PORTD = 0;
    
    TRISE = 0;
    PORTE = 0;
    
    INTCON = 0b10001001;
    IOCB = 0b00000011;
    
}

//*********************************************************************************
//Interrupciones
//*********************************************************************************
void __interrupt() my_inte(void){
    PORTD = cont;
    
    if (INTCONbits.RBIF){
        if (PORTBbits.RB0 == 1){
            cont = cont+1;
            RBIF = 0;
            __delay_ms(100);
        }    
        else {
            RBIF = 0;
        }
        if (PORTBbits.RB1 == 1){
            cont = cont - 1;
            RBIF =0;
            __delay_ms(100);
        }
        else {
            RBIF = 0;
        }
    }
}


//*********************************************************************************
//Principal
//*********************************************************************************
void main(void) {
    Setup ();
    while(1){    
    }
}
//*********************************************************************************
//                              FIN DEL PROGRAMA
//*********************************************************************************