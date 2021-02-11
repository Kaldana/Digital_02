/*
 * File:   Lab03.c
 * Author: Kenneth Aldana
 * Carnet: 18435
 * Pseudocódigo
 *
 * Created on January 31, 2021, 9:56 PM
 */


#include <xc.h>
#include <stdint.h>

//Aquí también incluyo mis librearías que utilizaré en el código

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
// incluir la librerias necesarias, en este caso seran las del ADC

//**********************************************************************************************
// Variables
// *********************************************************************************************

#define _XTAL_FREQ 8000000

//**********************************************************************************************
//Definir funciones
//**********************************************************************************************

//Aqui voy a declarer las variables que vaya a utilizar

//**********************************************************************************************
//Configuracion de puertos
//**********************************************************************************************
void Setup(void){
    
    ANSEL = 0b00000011;
    ANSELH = 0;
    
    TRISA = 0b00000011;
    PORTA = 0;
    
    //Declaro como entrada el RX
    TRISC = 0b0100000;
    PORTC = 0;
        
    TRISD = 0;
    PORTD = 0;
    
    
    INTCON = 0b11101000;
    IOCB = 0b00000011;
    //Aqui debo apagar el bit 4 que es la bandera de la comunicacion serial
    PIR1 = 0b00000000;
    //Aqui debo encender el bit 4 para encender el bit enable de la comunicacion serial
    PIE1 = 0b01000000;
    //Debo trabajar con el registro TXSTA para ver los bits que debo encender
}

//*********************************************************************************
//Interrupciones
//*********************************************************************************

//Aqui debo trabajar la interrupcion de la comunicacion serial, tomando en cuenta
//si la hare sincrona o asincrona
//Configurar interrupcion de transmision
//Configurar interrupcion de recepcion
//Configurar USART mode
//Configurar Transmission width
//Configurar Maestro esclavo
//Configurar la recepcion
//Configurar el baud rate
//Configurar el address detect

//*********************************************************************************
//Principal
//*********************************************************************************
void main(void) {
    //En este bloque debo trabajar con el tema de la comunicacion serial
}
//*********************************************************************************
//                              FIN DEL PROGRAMA
//*********************************************************************************
