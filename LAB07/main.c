//KENNETH ANDREE ALDANA CORADO
//18435
//SECCION
//LABORATORIO 07
//ELECTRONICA DIGITAL 02

//----------------------------------------------------------------------------------------------------------------
// LIBRERIAS
//----------------------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/interrupt.h"
#include "driverlib/interrupt.c"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/timer.h"
#include "driverlib/timer.c"
#include "driverlib/uart.h"
#include "driverlib/uart.c"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include <string.h>

#define XTAL 16000000

//----------------------------------------------------------------------------------------------------------------
// PROTOTIPOS DE FUNCIONES
//----------------------------------------------------------------------------------------------------------------
void UART_fun(void);
void TMR0_fun(void);

//----------------------------------------------------------------------------------------------------------------
// VARIABLES
//----------------------------------------------------------------------------------------------------------------
char color='a';
int LON = false;

int main(void){

    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ ) ;
    //Para el puerto F
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF ) ;
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
    //Configuracion del UART0
    SysCtlPeripheralEnable (SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)){}
    //Configurar el puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //Configuracion DEL TX y RX
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    IntMasterEnable();
    //Configuracion de pines y el BaudRate
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTDisable(UART0_BASE);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable (INT_UART0);
    UARTIntEnable (UART0_BASE, UART_INT_RX);
    UARTEnable (UART0_BASE);
    IntPrioritySet(INT_UART0, 0x0);
    IntRegister(INT_UART0, UART_fun);
    UARTFIFOEnable(UART0_BASE);
    UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX1_8,UART_FIFO_RX1_8);

    //Configuracion para el TMR0
    SysCtlPeripheralEnable (SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}
    SysCtlPeripheralReset (SYSCTL_PERIPH_TIMER0);
    SysCtlDelay (5);
    TimerDisable(TIMER0_BASE, TIMER_A|TIMER_B);
    TimerConfigure (TIMER0_BASE,TIMER_CFG_PERIODIC);
    TimerLoadSet (TIMER0_BASE, TIMER_A, 20000000 -1);
    TimerEnable (TIMER0_BASE, TIMER_A|TIMER_B);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, TMR0_fun);
    //Habilitar el INT ENABLE
    IntEnable(INT_TIMER0A);
    TimerEnable(TIMER0_BASE, TIMER_A);

    //Pin para el rojo
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE,GPIO_PIN_1) ;
    //Pin para el azul
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2) ;
    //Pin para el verde
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_3) ;

    while(1){}
}
void TMR0_fun(){
    TimerIntClear(TIMER0_BASE,  TIMER_TIMA_TIMEOUT);
        if (LON){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);
        }else{
            switch(color){
                            //Case para ver si es o,r,b "o" g el color.
                            case 'o':
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);
                                break;

                            case 'r':
                                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x02);
                                break;

                            case 'b':
                                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x04);
                                break;

                            case 'g':
                                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
                                break;
                                }
        }
        LON = !LON;
}

void UART_fun(){
    uint32_t ui32Status;
        //Revision de la bandera
        ui32Status = UARTIntStatus(UART0_BASE, true);
        //Limpieza de bandera
        UARTIntClear(UART0_BASE, ui32Status);
        while(UARTCharsAvail(UART0_BASE))
        {
            color=UARTCharGet(UART0_BASE);
            UARTCharPutNonBlocking(UART0_BASE,color);
        }
}
