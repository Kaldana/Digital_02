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
#include "inc/tm4c123gh6pm.h"
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



