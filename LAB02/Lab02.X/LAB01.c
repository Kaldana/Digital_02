/*
 * File:   Lab02.c
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
//Definir variables
//**********************************************************************************************
unsigned char cont = 0;
unsigned char advar = 0;
unsigned char display[16]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67,0x77,0x7C,0x39,0x7E,0xF9,0x71};
unsigned char dispvar = 0;
unsigned char pre_var = 0;
unsigned char displayder = 0;
unsigned char displayizq = 0;
//**********************************************************************************************
//Configuracion de puertos
//**********************************************************************************************
void Setup(void){
    //DECLARAR PUERTO A0 COMO ANALOGICO
    ANSEL = 0b00000001;
    ANSELH = 0;
    
    //DECLARAR PUERTO A0 COMO ENTRADA
    TRISA = 0b00000001;
    PORTA = 0;
    
    //DECLARAR PUERTO B0 Y B1 COMO ENTRADAS
    TRISB = 0b00000011;
    PORTB = 0;
    
    //DECLARAR COMO SALIDAS Y LIMPIAR EL PUERTO C, D Y E
    TRISC = 0;
    PORTC = 0;
    
    TRISD = 0;
    PORTD = 0;
    
    TRISE = 0;
    PORTE = 0;
    
    //ENCENDER BITS PARA INTERUPCIONES DEL PUERTO B Y TMR0
    INTCON = 0b11101000;
    //DECLARAR QUE EN B0 Y B1 SE ACTIVARA LA INTERRUPCION
    IOCB = 0b00000011;
    
    //DECLARAR BITS DE LOS REGISTROS PIR1, PIE1, ADCON0 Y ADCON1 PARA LA CONVERSION ADC Y
    //EL BIT NECESARIO PARA EL TMR0
    PIR1 = 0b00000000;
    PIE1 = 0b01000000;
    ADCON1  = 0;
    ADCON0  = 0b10000001;
    //CONFIGURAR EL PRESCALER PARA LA INTERRUPCION DEL TMR0
    OPTION_REG = 0b0000101;
    
}

//*********************************************************************************
//Interrupciones
//*********************************************************************************
void __interrupt() my_inte(void){
    //INTERRUPCION DEL PUERTO B, PARA AUMENTAR O DECREMENTAR EL CONTADOR
    if (INTCONbits.RBIF){
        if (PORTBbits.RB0 == 1){
            cont++;
        }
        
        if (PORTBbits.RB1 == 1){
            cont--;
        }
        INTCONbits.RBIF = 0;
    }
    //INTERRUPCION DEL ADC Y HACIENDO EL LAS OPERACIONES PARA PODER MOSTRAR LOS 
    //VALORES EN EL DISPLAY
    if (ADCON0bits.GO == 0){
        advar = ADRESH;
        displayizq = (ADRESH & 0xF0)>> 4;
        displayder = (ADRESH & 0x0F);
        __delay_us(25);
        ADCON0bits.GO_DONE = 1;
        PIR1bits.ADIF = 0;      
    }
    //INTERRUPCION DEL TMR0 PARA MULTIPLEXAR
    if (INTCONbits.T0IF){

        if (PORTEbits.RE0){
            PORTEbits.RE0 = 0;
            PORTC = display[displayder];
            PORTEbits.RE1 = 1;
            __delay_ms(8);
        }
        if (PORTEbits.RE1){
            PORTEbits.RE1 = 0;
            PORTC = display[displayizq];
            PORTEbits.RE0 = 1;
            __delay_ms(8);
        }
        INTCONbits.T0IF = 0;
    }
}


//*********************************************************************************
//Principal
//*********************************************************************************
void main(void) {
    Setup ();
    PORTEbits.RE1 = 1; 
    __delay_us(25);
    //ENCENDER EL BIT DEL GO_DONE PARA EL ADC
    ADCON0bits.GO_nDONE = 1;
    TMR0 = 150;
    while(1){
        //MOSTRAR EL VALOR DEL CONTADOR EN EL PUERTO D
        PORTD = cont;
        //CONFIGURACION DE LA ALARMA VISUAL
        if (advar <= cont){
            PORTEbits.RE2 = 0;
        }
        else{
            PORTEbits.RE2 = 1;
        }
    }
}
//*********************************************************************************
//                              FIN DEL PROGRAMA
//*********************************************************************************