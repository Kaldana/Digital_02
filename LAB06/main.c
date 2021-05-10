//KENNETH ANDREE ALDANA CORADO
//18435
//SECCION
//LABORATORIO 06
//ELECTRONICA DIGITAL 02
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.c"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.c"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"


int main(void)
{
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ );
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF );

    //PARTE02:
    //Timers:GPTMCTL, GPTMCFG, GPTMTnMR, GPTMTnILR, GPTMIMR, GPTMRIS,GPTMICR
    //UART: RCGCUART, RCGCGPIO, GPIOPCTL, UARTIBRD, UARTFBRD, UARTLCRH
    //USB: RCGCUSB, RCGCGPIO, GPIOPCTL, USBGPCS
    //PWM: RCGC0, RCGC2, GPIOAFSEL, GPIOPCTL, PWM0CTL, PWM0GENA, PWM0GENB, PWM0LOAD, PWM0CMPA,PWM0CMPB, PWM0CTL,PWMENABLE
    //ADC: RCGCADC, RCGCGPIO, GPIODEN, GPIOAMSEL, ADCSSPRI

    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE,GPIO_PIN_1);
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_3);

    // PARTE03 :
    // SysCtlDelay, con parametro de duracion del delay en nanosegundos

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE , GPIO_PIN_4 );
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_STRENGTH_4MA , GPIO_PIN_TYPE_STD_WPU );

    while(1) {
        if ((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4) & 0x16)==0) {
            while ((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4) & 0x16)==0) { }

            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (20000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x0A);
            SysCtlDelay (20000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x02);
            SysCtlDelay (20000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            SysCtlDelay (5000000);

        }
    }

}
