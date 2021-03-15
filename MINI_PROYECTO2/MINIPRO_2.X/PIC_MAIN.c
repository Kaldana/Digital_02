/*
 * File:   PIC_MAIN.c
 * Author: Kenneth Aldana
 * Carnet: 18435
 * MINI PROYECTO 2
 *
 * Created on March 10
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "I2C.h"
#include "USART.h"
#include "ADXL345.h"

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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

char accelerometer_val[6];
char Read_val = 0;
int controlvar = 0;
int dato = 0;
//**********************************************************************************************
//Configuracion de puertos
//**********************************************************************************************
void Setup(void){
    
    //Configuración de puertos
    ANSEL = 0;
    TRISA = 0;
    PORTA = 0;
    ANSELH = 0;
    TRISB = 0;
    PORTB = 0;
    
    TRISD = 0;
    PORTD = 0;
    
    TRISE = 0;
    PORTE = 0;
    //Inicializo el USART a un BaudRate de 9600
    USART_Initialize(9600);
    //Inicializo el I2C en el maestro
    MAS_INIT(100000);
    //Inicializo el acelerometro
    ADXL345_Init();
}

//*********************************************************************************
//Interrupciones
//*********************************************************************************

void __interrupt() ISR(void){

    if (PIR1bits.RCIF == 1) {
        //Obtengo el valor del RCREG para que baje la bandera
        Read_val = RCREG;

        //Instrucciones para las luces piloto
        if (Read_val == 2) {
            PORTAbits.RA0 = 1;
            PORTB = 1;
        }
        if (Read_val == 3) {
            PORTAbits.RA0 = 0;
        }
        if (Read_val == 4) {
            PORTAbits.RA1 = 1;
        }
        if (Read_val == 5) {
            PORTAbits.RA1 = 0;
        }
    }
    //Interrupcion para que envie los 5 datos.
    if(PIR1bits.TXIF == 1){
        TXREG = accelerometer_val[dato];
        if (dato == 5){
            dato = 0;
        }
        else {
            dato++;
        }
    }
}

//*********************************************************************************
//Principal
//*********************************************************************************
void main(void) {
    //Llamo a las configuraciones de los puertos
    Setup(); 
    OSCCONbits.IRCF = 0b111;
    while (1) {
        //obtengo los datos de los ejes del acelerometro
        accelerometer_val[0]=ADXL345_Read(0x32);
        accelerometer_val[1]=ADXL345_Read(0x33);
        accelerometer_val[2]=ADXL345_Read(0x34);
        accelerometer_val[3]=ADXL345_Read(0x35);
        accelerometer_val[4]=ADXL345_Read(0x36);
        accelerometer_val[5]=ADXL345_Read(0x37);
        PORTB = accelerometer_val[2];
    }
}
//*********************************************************************************
//                              FIN DEL PROGRAMA
//*********************************************************************************
