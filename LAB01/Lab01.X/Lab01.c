/*
 * File:   Lab01.c
 * Author: Kenneth Aldana
 * Carnet: 18435
 * Laboratorio 01
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
// Aqui asigno variables a mi semaforo para que sea mas facil de trabajar con los pines
// *********************************************************************************************

#define ROJO PORTEbits.RE0
#define AMARILLO PORTEbits.RE1
#define VERDE PORTEbits.RE2
#define _XTAL_FREQ 8000000

//**********************************************************************************************
//Definir funciones
//**********************************************************************************************
void Setup(void);
void Semaforo (void);
char cont = 1;
int juego = 0;
char cont2 = 1;
//**********************************************************************************************
//Configuracion de puertos
//**********************************************************************************************
void Setup(void){
    
    ANSEL = 0;
    ANSELH = 0;
    
    TRISA = 0b00000111;
    PORTA = 0;
    
    TRISB = 0;
    PORTB = 0;
    
    TRISC = 0;
    PORTC = 0;
    
    TRISD = 0;
    PORTD = 0;
    
    TRISE = 0;
    PORTE = 0;
    
}

//**************************************************************************************
// Semaforo
//**************************************************************************************

void Semaforo (void){
    //Vuelvo a limpiar los puertos si se quiere jugar otra partida
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    
    // Empieza secuencia del semaforo
    ROJO = 1;
    __delay_ms(500);
    ROJO = 0;
    
    AMARILLO = 1;
    __delay_ms(500);
    AMARILLO = 0;
    
    VERDE = 1;
    __delay_ms(500);
    VERDE = 0;
    
    //Reasigno los valores a las variables por si se empieza otro juego
    juego = 1;
    cont = 1;
    cont2 = 1;
    
}

//*********************************************************************************
//Principal
//*********************************************************************************
void main(void) {
    Setup();
    while(1){
        if (PORTAbits.RA2 == 0) {
            __delay_ms(50);
            
        }
        if (PORTAbits.RA2 == 1) {
            Semaforo();
            while (juego == 1){
                __delay_ms(50);
                if (PORTAbits.RA0 == 1){
                    //delay para evitar que se producta mas de una lactura por vez que se presiona el swich
                    __delay_ms(150);
                    //muestro el valor de cont en el puerto C
                    PORTC = cont;
                    //proceso para aumentar el contador por bits segun la condicion que tenga
                    if (cont == 1){
                        cont = cont*2;
                    }
                    else if (cont == 0){
                        //Enciende el led del jugador 1 que indica que gano y reinicia el juego
                        PORTBbits.RB0 = 1;
                        cont = 1;
                        juego = 0;
                    }
                    else{
                        cont = cont*2;
                    }
                }
                if (PORTAbits.RA1 == 1){
                    __delay_ms(150);
                    PORTD = cont2;
                    if (cont2 == 1){
                        cont2 = cont2*2;
                    }
                    else if (cont2 == 0){
                        PORTBbits.RB1 = 1;
                        cont2 = 1;
                        juego = 0;
                    }
                    else{
                        cont2 = cont2*2;
                    }
                }
            }
        }
    }
}
//*********************************************************************************
//                              FIN DEL PROGRAMA
//*********************************************************************************