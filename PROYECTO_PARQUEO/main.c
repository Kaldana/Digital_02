//KENNETH ANDREE ALDANA CORADO
//18435
//SECCION
//PROYECTO 4 - CONTROL DE PARQUEO
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
// Declaracion de variables
//----------------------------------------------------------------------------------------------------------------

// Variables para poder cambiar los nombres
uint32_t i = 0;
uint32_t j = 0;
uint32_t S1 = 0; // Variables para los Ses
uint32_t S2 = 0;
uint32_t S3 = 0;
uint32_t S4 = 0;
uint8_t Ses = 0;

//----------------------------------------------------------------------------------------------------------------
// Prototipos para las fnciones
//----------------------------------------------------------------------------------------------------------------
void delay(uint32_t msec);
void delay1ms(void);

//----------------------------------------------------------------------------------------------------------------
// Programacion general
//----------------------------------------------------------------------------------------------------------------
int main(void)
 {
    // Configuracion de osciador externo para 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ);
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Se configuran los puertos necesarios como entradas y salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;
    GPIOPinConfigure(GPIO_PD7_U2TX);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);
    //Habilito el UART 2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    //Pines del TX y RX del uart 2
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    //Habilitar el UART
    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTIntClear(UART2_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX | UART_INT_FE | UART_INT_PE | UART_INT_BE | UART_INT_OE | UART_INT_RI | UART_INT_CTS | UART_INT_DCD | UART_INT_DSR);

      //----------------------------------------------------------------------------------------------------------------
      // Bucle principal
      //----------------------------------------------------------------------------------------------------------------

    while (1)
    {
        //Lectura de todos los sensores
        S1 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4) && GPIO_PIN_4);
        S2 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5) && GPIO_PIN_5);
        S3 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) && GPIO_PIN_6);
        S4 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7) && GPIO_PIN_7);

        Ses = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7) >> 4;

        //Funcionamiento de los leds color rojo
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, ~Ses);
        //Funcionamiento de los leds color verde
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, Ses);

        //Envio de datos por el UART2
        UARTCharPut(UART2_BASE, S1);
        UARTCharPut(UART2_BASE, S2);
        UARTCharPut(UART2_BASE, S3);
        UARTCharPut(UART2_BASE, S4);
        delay(100);
    }

}

//----------------------------------------------------------------------------------------------------------------
// Delay
//----------------------------------------------------------------------------------------------------------------

void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        SysTickDisable();
        SysTickPeriodSet(16000);
        SysTickEnable();

        while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);
    }
}
