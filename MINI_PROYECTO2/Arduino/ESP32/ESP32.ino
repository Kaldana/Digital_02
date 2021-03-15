//File:   ESP.INO
//Author: Kenneth Aldana
//Carnet: 18435
//MINI PROYECTO 2
//
//Created on March 10


/************************** Configuration ***********************************/

#include "config.h"

/************************ Example Starts Here *******************************/

#define IO_LOOP_DELAY 10000
unsigned long lastUpdate;
//Declaro las variables utiles
char acce_data[6];

float x_data;
float y_data;
float z_data;

char *valor1;
char *valor2;

//Indico como se llaman mis feeds
AdafruitIO_Feed *LED2 = io.feed("LED1");
AdafruitIO_Feed *LED1 = io.feed("LED2");

AdafruitIO_Feed *EJEX = io.feed("EJEX");
AdafruitIO_Feed *EJEY = io.feed("EJEY");
AdafruitIO_Feed *EJEZ = io.feed("EJEZ");

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(9600);
  Serial2.begin(9600);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  } 
  //Tomo el dato actualizado
  LED1->get();
  LED2->get();
  //Realizo la rutina de encendido y apagado con las rutinas CLED1 y CLED2
  LED1->onMessage(CLED1);
  LED2->onMessage(CLED2);
  
}

void loop() {
  io.run();

  //for para poder obtener todos los datos del acelerometro
  for(int i = 0; i <= 5; i++){
    if(Serial.available()){
      acce_data[i] = Serial.read();
    }
  }

  //Operaciones necesarias para poder tomar la pareja de datos por eje del acelerometro
  x_data = (acce_data[1]|acce_data[0] << 8);
  y_data = (acce_data[3]|acce_data[2] << 8);
  z_data = (acce_data[5]|acce_data[4] << 8);

  x_data = x_data / 256;
  y_data = y_data / 256;
  z_data = z_data / 256;

  //condicionante principal para el envio de datos a Adafruit
  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {

    Serial.print("sending -> Eje X ");
    Serial.println(x_data);
    EJEX->save(x_data);
    
    Serial.print("sending -> Eje Y ");
    Serial.println(y_data);
    EJEY->save(y_data);

    Serial.print("sending -> Eje Z ");
    Serial.println(z_data);
    EJEZ->save(z_data);
    
    // update timer
    lastUpdate = millis();
  }
}

//Rutina para controlar el pulsador en Adafruit y control de luz piloto
void CLED1(AdafruitIO_Data *data){
  Serial.print("received <- ");
  valor1 =  data->value();
  Serial.println(valor1);
  if(*valor1 == '1')Serial.write(2); 
  else Serial.write(3); ;
  return;
}

//Rutina para controlar el pulsador de Adafruit y control de luz piloto
void CLED2(AdafruitIO_Data *data){
  Serial.print("received <- ");
  valor2 =  data->value(); 
  Serial.println(valor2);
  if(*valor2 == '1')Serial.write(4); 
  else Serial.write(5); ;
  return;
}
