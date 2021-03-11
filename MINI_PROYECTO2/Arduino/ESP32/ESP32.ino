// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int count = 1;
int PIC_data = 0;

char ACCX[2];
char ACCY[2];
char ACCZ[2];


AdafruitIO_Feed *COORDENADAS_X = io.feed("COORDENADAS_X");
AdafruitIO_Feed *COORDENADAS_Y = io.feed("COORDENADAS_Y");
AdafruitIO_Feed *COORDENADAS_Z = io.feed("COORDENADAS_Z");

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(9600);
  Serial2.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    delay(500);
  }

}

void loop() {

  io.run();

  if(Serial.availableForWrite()){
    Serial.print("EJE X EN GRADOS");
    Serial.print(ACCX[1], DEC);
    Serial.println(ACCX[0], DEC);

    Serial.print("EJE Y EN GRADOS");
    Serial.print(ACCY[1], DEC);
    Serial.println(ACCY[0], DEC);

    Serial.print("EJE Z EN GRADOS");
    Serial.print(ACCZ[1], DEC);
    Serial.println(ACCZ[0], DEC);
  }

  count++;
  switch (count) {
  case 1:
    ACCX[0] = Serial.read();
    
    break;
  case 2:
    ACCX[1] = Serial.read();
    COORDENADAS_X->save(ACCX[1]);
    break;
  case 3:
    ACCY[0] = Serial.read();
    
    break;
  case 4:
    ACCY[1] = Serial.read();
    COORDENADAS_Y->save(ACCY[1]);
    break;
  case 5:
    ACCZ[0] = Serial.read();
    
    break;
  case 6:
    ACCZ[1] = Serial.read();
    COORDENADAS_Z->save(ACCZ[1]);
    count = 1;
    break;
  }
    
  delay(3000);
}
