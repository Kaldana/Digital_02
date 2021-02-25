/*
 * File:   Slave0_main.c
 * Author: Kenneth Aldana
 * Carnet: 18435
 * Mini Proyecto
 *
 * Created on Feb. 19 
 */

#include <xc.h>
#include <stdint.h>
#include "stdio.h"
#include "LIB_ADC.h"
#include "LIB_SPI.h"
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

//**********************************************************************************************
//Definir variables
//**********************************************************************************************

uint8_t temp_val = 0;
uint8_t lectura = 0;

//**********************************************************************************************
//Configuracion de puertos
//**********************************************************************************************
void Setup(void){
    
    ANSEL = 0b00000001;
    ANSELH = 0;
    
    TRISA = 0b00000001;
    PORTA = 0;
    
//    TRISC = 0b0000000;
//    PORTC = 0;
        
    TRISD = 0;
    PORTD = 0;
    
    TRISE = 0;
    PORTE = 0;
    
    TRISB = 0;
    PORTB = 0;
    ADC_CONFIG();
    CONFIG_SPI();
}

//*********************************************************************************
//Interrupciones
//*********************************************************************************
void __interrupt() ISR(void){
    if (ADCON0bits.GO == 0){
        temp_val = ADRESH;
        __delay_us(25);
        ADCON0bits.GO_DONE = 1;
        PIR1bits.ADIF = 0;      
    }
    if(PIR1bits.SSPIF){
        if(SSPSTATbits.BF == 0){
            lectura = SSPBUF;
        }
        SSPBUF = temp_val;
        PIR1bits.SSPIF = 0;
    }
}

//*********************************************************************************
//Principal
//*********************************************************************************
void main(void) {
    Setup();
    __delay_us(25);
    ADCON0bits.GO_DONE = 1;
    while (1) {
        PORTB = temp_val;
        if(temp_val < 13){
            PORTD = 4;
        }
        if((temp_val <= 18) && (temp_val >= 13)){
            PORTD = 2;
        }
        if(temp_val > 18){
            PORTD = 1;
        }
    }
}
//*********************************************************************************
//                              FIN DEL PROGRAMA
//*********************************************************************************
