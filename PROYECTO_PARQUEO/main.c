//KENNETH ANDREE ALDANA CORADO
//18435
//SECCION
//PROYECTO 04
//ELECTRONICA DIGITAL 02

//----------------------------------------------------------------------------------------------------------------
// LIBRERIAS
//----------------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#define XTAL 16000000

//----------------------------------------------------------------------------------------------------------------
// VARIABLES
//----------------------------------------------------------------------------------------------------------------

uint32_t i = 0;
uint32_t j = 0;
uint32_t Parqueos = 0;
uint32_t Sensor1 = 0;
uint32_t Sensor2 = 0;
uint32_t Sensor3 = 0;
uint32_t Sensor4 = 0;
uint8_t Sensores = 0;

//----------------------------------------------------------------------------------------------------------------
// PROTOTIPOS DE FUNCIONES
//----------------------------------------------------------------------------------------------------------------
void delay(uint32_t msec);
void delay1ms(void);
void Display7(uint32_t numero);

//----------------------------------------------------------------------------------------------------------------
// PROGRAMACION GENERAL
//----------------------------------------------------------------------------------------------------------------
int main(void)
 {
    // Se setea oscilador externo de 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ);  //16MHz

    // Se setea oscilador externo de 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    // Se asigna reloj a los puerto
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);


    // Se configuran los puertos como entradas salidas

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;
    GPIOPinConfigure(GPIO_PD7_U2TX);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);


    //habilito el uart
    UARTIntClear(UART1_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX | UART_INT_FE | UART_INT_PE | UART_INT_BE | UART_INT_OE | UART_INT_RI | UART_INT_CTS | UART_INT_DCD | UART_INT_DSR);

    //Enable the peripheral UART Module 1/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1)){
    }

    //Enable the GPIO Port C/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);

    // Se habilitan las interrupciones Globales
    IntMasterEnable();

    // Make the UART pins be peripheral controlled.
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTDisable(UART1_BASE);
    //Sets the configuration of a UART.
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntEnable (INT_UART1);

    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    UARTEnable (UART1_BASE);

    //----------------------------------------------------------------------------------------------------------------
    // BUCLE PRINCIPAL
    //----------------------------------------------------------------------------------------------------------------

    while (1)
    {
        Sensor1 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4) && GPIO_PIN_4); // lee el pin y se compara para saber si esta
        Sensor2 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5) && GPIO_PIN_5); // encendido o apagado
        Sensor3 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) && GPIO_PIN_6);
        Sensor4 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7) && GPIO_PIN_7);

        Sensores = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7) >> 4; // lee el puerto y corre  4

        Parqueos = ((((4 - Sensor4) - Sensor3) - Sensor2) - Sensor1) ; // resta para saber la cantidad de parqueos
        Display7(Parqueos);

        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, ~Sensores); //leds verdes = 1
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, Sensores); // leds rojas = 0

    }

}

//----------------------------------------------------------------------------------------------------------------
// DELAY EN MILISEGUNDOS
//----------------------------------------------------------------------------------------------------------------
void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        delay1ms();
    }

}

//----------------------------------------------------------------------------------------------------------------
// DELAY DE 1 MILISEGUNDO
//----------------------------------------------------------------------------------------------------------------
void delay1ms(void)
{
    SysTickDisable();
    SysTickPeriodSet(16000);
    SysTickEnable();

    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);
}

