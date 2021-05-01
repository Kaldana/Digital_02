//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
   Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
   Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
   Con ayuda de: José Guerra
   IE3027: Electrónica Digital 2 - 2019
*/
//***************************************************************************************************************************************
// Librerias necesarias para el funcionamiento
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include <SPI.h>
#include <SD.h>
#include <stdlib.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "sonidos.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

//***************************************************************************************************************************************
// Definimos palabras especificas para pines, facilitando la programacion
//***************************************************************************************************************************************
#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
//#define UP    PC_6
#define DOWN  PC_7
#define LEFT  PD_6
#define RIGHT PD_7

//***************************************************************************************************************************************
// Definicion de variables
//***************************************************************************************************************************************
const int START = PUSH1;
const int UP = PUSH2;
int jugar;
int buttonState = 0;
int J2State = 0;
int J1State = 0;
int RIGHTState = 0;
int LEFTState = 0;
int lastx = 0;
int lastx2 = 0;
int lasty = 0;
int lasty2 = 0;
int actx = 0;
int actx2 = 0;
int acty = 0;
int acty2 = 0;
uint8_t xfood = 0;
uint8_t xfood2 = 0;
uint8_t yfood = 0;
uint8_t yfood2 = 0;
int movimiento = 0;
int movimiento2 = 0;
int comida = 0;
int puntaje = 0;
int puntaje2 = 0;
int newfoodx =0;
int newfoodx2 =0;
int newfoody =0;
int newfoody2 =0;
int Num = 0;
int Num2 = 0;
File file;
unsigned char *Blok;
const int Gled = GREEN_LED;
//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset);
void Menu(void);
void Entorno(void);
void food(void);
void punteo(void);
void start_screen(void);
void setupsd(void);
//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");

  LCD_Init();
  LCD_Clear(0x00);
  setupsd();
  Blok = opensd();
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(Gled, OUTPUT);
  //LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);

  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);

}

//***************************************************************************************************************************************
// Función para mostrar el menu
//***************************************************************************************************************************************

void Menu(void) {
  //Ciclo principal para que se verifique constantemente cuando se presiona el boton y se mueva el snake
  while (jugar == 0) {
    //Coloco el fondo a la LCD
    FillRect(0, 0, 320, 240, 0xACD1);
    //Declaro la primer fila de texto
    String menu1 = "Snake Classic Game";
    //Imprimo la fila detexto creada arriba
    LCD_Print(menu1, 20, 100, 2, 0x0000, 0xACD1);
    //Declaro la segunda fila de texto
    String menu2 = "PUSH START TO PLAY";
    //Imprimo la segunda fila de texto creada arriba
    LCD_Print(menu2, 20, 140, 2, 0x0000, 0xACD1);

    //Ciclo para que el snake recorra de izquierda a derecha la pantalla y borre la primer fila de texto
    for (int x = 0; x < 320 - 32; x++) {
      delay(15);
      //variable para definir el cambio de frame
      int anim2 = (x / 35) % 2;
      //Funcion para imprimir el snake segun las condiciones de las variables
      LCD_Sprite(x, 100, 32, 24, snakeinicio, 4, anim2, 0, 0);
      //Se imprime una linea detras del snake para borrar rastro
      V_line( x , 100, 24, 0xACD1);
      //Se verifica si se presiono el boton de START para empezar el juego
      buttonState = digitalRead(START);
      if (buttonState == 0) {
        delay (5);
        jugar = 1;
        break;
      }
    }
  }
}

//***************************************************************************************************************************************
// Función para jugar
//***************************************************************************************************************************************

void Entorno(void) {
  //Se verifica si ya se presiono start para comezar el juego
  if (jugar == 1) {
    //Se crea el fondo para la LCD
    FillRect(0, 0, 320, 240, 0x0000);
    //Se crea el cuerpo de la primer snake
    FillRect(7, 23, 8, 8, 0x97C0);
    //Se crea el cuerpo del segundo snake
    FillRect(164, 23, 8, 8, 0x97C0);
    //Los siguientes dos for se utilizaron para poder crear los muros del juego, tanto los del marco como la linea divisora.
    for (int x = 0; x < 319; x++) {
      LCD_Bitmap(x, 16, 7, 7, muro);
      LCD_Bitmap(x, 233, 7, 7, muro);
      x += 7;
    }
    for (int y = 16; y < 319; y++) {
      LCD_Bitmap(0, y, 7, 7, muro);
      LCD_Bitmap(313, y, 7, 7, muro);
      LCD_Bitmap(157, y, 7, 7, muro);
      y += 7;
    }    
  }
  //estas variables son importantes porque son las que definen la posicion inicial de los snake
  lastx = 7;
  lasty = 23;
  lastx2 = 164;
  lasty2 = 23;
  //estas variables permiten generar la comida de forma aleatoria en el mapa
  xfood =(random(8,150)); 
  yfood =(random(16,220));
  xfood2 =(random(200,300)); 
  yfood2 =(random(16,220));
  //estas funciones crean la comida de los dos jugadores, una color LILA y otro AZUL
  FillRect(xfood,yfood, 8, 8, 0x81EE);
  FillRect(xfood2,yfood2, 8, 8, 0x001F);
};

//***************************************************************************************************************************************
// Función para la comida
//***************************************************************************************************************************************

void food(void) {
  //Comprobaciones si el snake esta dentro de los pixeles de la comida en x para contar que ya se la comio
  if (xfood > lastx-4 || xfood < lastx+4){
    //creacion de una nueva coordenada en x para la comida
    xfood = (random(8,150));
    //bandera que me permite conocer si ya paso por la comida y asi generar una nueva
    newfoodx = 1;
  }
  
  //Comprobaciones si el snake esta dentro de los pixeles de la comida en y para contar que ya se la comio
  if (yfood > lasty-4 || yfood < lasty+4){
  //creacion de una nueva coordenada en y para la comida
    yfood = (random(16,220));
    //bandera que me permite conocer si ya paso por la comida y asi generar una nueva
    newfoody = 1;
  }

  //Revisar las dos banderas si en realidad se comio la comida, y si afirmativo generar una nueva comida.
  if (newfoodx == 1 || newfoody == 1){
    FillRect(xfood,yfood,8,8,0x81EE);  
    puntaje += 1;
    newfoodx = 0;
    newfoody = 0;
  }

  //Misma logica que el bloque anterior, este es para el jugador 2
  if (xfood2 > lastx2-4 || xfood2 < lastx2+4){
    xfood2 = (random(160,300));
    newfoodx2 = 1;
  }
  if (yfood2 > lasty2-4 || yfood2 < lasty2+4){
    yfood2 = (random(16,220));
    newfoody2 = 1;
  }
  if (newfoodx2 == 1 || newfoody2 == 1){
    FillRect(xfood2,yfood2,8,8,0x001F);  
    puntaje2 += 1;
    newfoodx2 = 0;
    newfoody2 = 0;
  }
  
};

//***************************************************************************************************************************************
// Función para la musica
//***************************************************************************************************************************************

void start_screen(void){
  musica(melody1, durations1, songLength1);
  delay(100);  
};

//***************************************************************************************************************************************
// Función para el puntaje
//***************************************************************************************************************************************

void punteo(void) {
  //Crear variable de texto para indicar el punteo del jugador 1
  String textopunteo = "J1:";
  //Impresion de la variable que indica que es el punteo del jugador 1
  LCD_Print(textopunteo, 38, 0, 2, 0x0000, 0xACD1);    
  //Impresion del puntaje del jugador 1
  LCD_Print(String(puntaje), 98, 0, 2, 0x0000, 0xACD1);
  //Crear variable de texto para indicar el punteo del jugador 2
  String textopunteo2 = "J2:";
  //Impresion de la variable que indica que es el punteo del jugador 2
  LCD_Print(textopunteo2, 200, 0, 2, 0x0000, 0xACD1);    
  //Impresion del puntaje del jugador 2
  LCD_Print(String(puntaje2), 250, 0, 2, 0x0000, 0xACD1);  
};

//******************************************************************************************************************************************
//Funciones SD
//*******************************************************************************************************************************************
//Setup SPI SD
void setupsd(void){
  SPI.setModule(0);

  Serial.println(" ");
  Serial.println("Initializing SD card...");
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
}

unsigned char* opensd(){
  file = SD.open("olak.txt"); //abrir archivos
 
  Serial.println("a");
  Serial.println("a");
  char data[file.size()];
  file.read(data, file.size());
  file.close();

  unsigned char* temp_data = (unsigned char*)malloc(7*7*2*sizeof(unsigned char));
//cargar a ram
  const char s1[2] = ",";

  temp_data[0] = strtoul(strtok(data,s1), NULL, 16);
//rtok separa y toul vuelve string
  for (int i = 1; i<(7*7*2); i++){
    temp_data[i] = strtoul(strtok(NULL,s1), NULL,16);
  }
  
  return temp_data;

}


//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {
  //Llamo a las funcioens de musica, menu y entorno.
  start_screen();
  Menu();
  Entorno();
  //Ciclo principal para que siempre se ejecute
  while(1){
    //Llamo a la funcion de punteo y comida
    food();                
    punteo();
    //Verifico si alguno de los botones de los jugadores fue presionado
    J1State = digitalRead(UP);
    J2State = digitalRead(START);

    //Si se presiono, la variable movimiento indica a que lado se movera el snake, esta aumenta cuando se presiona el boton.
    //En esta seccion no se dejo el antirebote porque si nos conviene que el jugador pueda dejar presionado y este cambie, por la logica, no es necesario
    //colocar delay.
    if (J1State == 0) {
      movimiento += 1;
      if (movimiento == 5) {
        //Si ya termino los 4 posibles movimientos posibles (abajo, izquierda, arriba, derecha), empieza con el movimiento principal permitido(abajo).
        movimiento = 1;
      }
    }
    //Misma logica que el bloque anterior pero para el jugador 2
    if (J2State == 0) {
      movimiento2 += 1;
      if (movimiento2 == 5) {
        movimiento2 = 1;
      }
    }

    //cuando la variable movimiento o movimiento2 estan en cero, es porque el juego esta comenzando, por ello automaticamente la serpiente empieza a moverse a la izquierda
    if (movimiento == 0) {
      //este ciclo for se hizo solo para que la serpiente recorriera unicamente 7 pixeles, esto porque se necesitaba que revisara constantemente si se presionaba el boton
      for (int x = lastx; x < lastx + 7 ; x++) {
        delay(15);
        //Funcion para que el snake se mueva
        FillRect(x, 23, 8, 8, 0x97C0);
        //Funcion para eliminar el rastro del snake
        V_line( x, 23, 8, 0x0000);
        //Guardo la posicion en x actual del snake, que para el siguiente movimiento sera la posicion pasada.
        actx = x;
        //Guardo la posicion en y anterior, en esta caso como solo se movio en x, y no vario desde que se creo al inicio el snake.
        lasty = 23; 
      }
      //Esto se genero para que al momento de utilizar de nuevo lastx, el for no se conviertiese en infinito, aqui entra la logica del actual para este bloque, es el pasado para el siguiente.
      lastx = actx;
      
    }
    //Misma logica que el bloque de movimiento = 0 pero para moverse a la izquierda  
    if (movimiento == 1) {
      for (int y = lasty; y < lasty +7; y++) {
        delay(15);
        FillRect(lastx, y, 8, 8, 0x97C0);
        H_line(lastx,y, 8, 0x0000);
        acty = y;
      }
      lasty = acty;
    }
    //Misma logica que el bloque de movimiento = 0  pero para moverse para arriba
    if (movimiento == 2) {
      
      for (int x = lastx; x > lastx -7; x--) {
        delay(15);
        FillRect(x, lasty, 8, 8, 0x97C0);
        V_line(x+9,lasty, 8, 0x0000);
        actx = x;
      }
      lastx = actx;
    }
    
    //Misma logica que el bloque de movimiento = 0  pero para moverse para la derecha
    if (movimiento == 3) {
      
      for (int y = lasty; y > lasty -7; y--) {
        delay(15);
        FillRect(lastx, y, 8, 8, 0x97C0);
        H_line(lastx,y+9, 8, 0x0000);
        acty = y;
      }
      lasty = acty;
    }

    //Misma logica que el bloque de movimiento == 0 para abajo, la diferencia es que este toma en cuental a posicion anterior, movimiento = 0, no.
    if (movimiento == 4) {
      for (int x = lastx; x < lastx +7 ; x++) {
        delay(15);
        FillRect(x, lasty, 8, 8, 0x97C0);
        V_line(x, lasty, 8, 0x0000);
        actx = x;
      }
      lastx = actx;
    }


  //Misma logica que el bloque completo anterior pero para el jugador 2
  if (movimiento2 == 0) {
      for (int x = lastx2; x < lastx2 + 7 ; x++) {
        delay(15);
        FillRect(x, 23, 8, 8, 0x97C0);
        V_line( x, 23, 8, 0x0000);
        actx2 = x;
        lasty2 = 23; 
      }
      lastx2 = actx2;
      
    }
  
    if (movimiento2 == 1) {
      
      for (int y = lasty2; y < lasty2 +7; y++) {
        delay(15);
        FillRect(lastx2, y, 8, 8, 0x97C0);
        H_line(lastx2,y, 8, 0x0000);
        acty2 = y;
      }
      lasty2 = acty2;
    }
    
    if (movimiento2 == 2) {
      
      for (int x = lastx2; x > lastx2 -7; x--) {
        delay(15);
        FillRect(x, lasty2, 8, 8, 0x97C0);
        V_line(x+9,lasty2, 8, 0x0000);
        actx2 = x;
      }
      lastx2 = actx2;
    }
    if (movimiento2 == 3) {
      
      for (int y = lasty2; y > lasty2 -7; y--) {
        delay(15);
        FillRect(lastx2, y, 8, 8, 0x97C0);
        H_line(lastx2,y+9, 8, 0x0000);
        acty2 = y;
      }
      lasty2 = acty2;
    }
    if (movimiento2 == 4) {
      for (int x = lastx2; x < lastx2 +7 ; x++) {
        delay(15);
        FillRect(x, lasty2, 8, 8, 0x97C0);
        V_line(x, lasty2, 8, 0x0000);
        actx2 = x;
      }
      lastx2 = actx2;
    }
  }
    
}

//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER)
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40 | 0x80 | 0x20 | 0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
  //  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c) {
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
    }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y + h, w, c);
  V_line(x  , y  , h, c);
  V_line(x + w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y + i, w, c);
  }
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background)
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;

  if (fontSize == 1) {
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if (fontSize == 2) {
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }

  char charInput ;
  int cLength = text.length();
  Serial.println(cLength, DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength + 1];
  text.toCharArray(char_array, cLength + 1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1) {
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2) {
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + width;
  y2 = y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k + 1]);
      //LCD_DATA(bitmap[k]);
      k = k + 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 =   x + width;
  y2 =    y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  int k = 0;
  int ancho = ((width * columns));
  if (flip) {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width - 1 - offset) * 2;
      k = k + width * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k - 2;
      }
    }
  } else {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width + 1 + offset) * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k + 2;
      }
    }


  }
  digitalWrite(LCD_CS, HIGH);
}
