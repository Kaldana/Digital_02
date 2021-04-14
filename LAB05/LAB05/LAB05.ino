//UNIVERSIDAD DEL VALLE DE GUATEMALA
//KENNETH ANDREE ALDANA CORADO
//CARNE 18435
//LABORATORIO 05
//ALMACENAMIENTO SD
//ELECTRONICA DIGITAL 2
//LUIS RIVERA
//SECCION 20
//14 DE ABRIL DE 2021

/*
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 2 Feb 2014
 by Scott Fitzgerald
 
 This example code is in the public domain.
 */
 
#include <SPI.h>
#include <SD.h>

//variable para indicar que txt quieren
int NIMG;
//variable para llevar el control si se termina o no el menu
int END; 

File myFile;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  SPI.setModule(0);

  Serial.println(" ");
  Serial.println("Initializing SD card...");
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  Serial.println();
  Serial.println("PERSONAJES EN LA SD");
  Serial.println();

  //Abrir los archivos contenidos en la SD
  myFile = SD.open("/"); 

  //Funcion para ver el contenido de la SD
  printDirectory(myFile, 0); 
  
  Serial.println("");
  
  Serial.println("Selecciona que archivo quieres ver, ingresa el numero según la lista");
}

void loop(){

  //Bucle principal para que, una vez la variable de control no sea 4, siga funcionando.
  while (END != 4){
      //Lectura de la variable que ingresan, esto ocurre en los demas else if
      if (Serial.available() > 0) {
        NIMG = Serial.read();
    }
    
      if (NIMG == '1'){ //mostrar mario
         myFile = SD.open("mario.txt");
        if (myFile) {
          Serial.println();
          Serial.println(" MARIO ");
          Serial.println();
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("no se encontro su archivo.txt");
        }
        Serial.println("");
        Serial.println("Escribir 1, 2, 3 para otro personaje o 4 para salir");
      } 
       
      else if (NIMG == '2'){ //mostrar contra
          myFile = SD.open("contra.txt");
        if (myFile) {
          Serial.println();
          Serial.println(" CONTRA ");
          Serial.println();
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
        } else {
          // if the file didn't open, print an error:
          
          Serial.println("no se encontro su archivo.txt");
        }
        Serial.println("");
        Serial.println("Escribir 1, 2, 3 para otro personaje o 4 para salir");
      }
        
    else if (NIMG == '3'){ //mostrar yoshi
      myFile = SD.open("yoshi.txt");
        if (myFile) {
          Serial.println();
          Serial.println(" YOSHI ");
          Serial.println();
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("no se encontro su archivo.txt.txt");
        }
        Serial.println("");
        Serial.println("Escribir 1, 2, 3 para otro personaje o 4 para salir");
      }
   else if (NIMG == '4'){
      Serial.println("");
      Serial.println("Gracias por ver los personajes");
      END = 4;
    }
    else{}
    }
}    
        

void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
  Serial.println("");

}
