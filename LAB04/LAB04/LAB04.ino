//PINES PARA EL SEMAFORO
int LRED = RED_LED;
int LGREEN = GREEN_LED;
int LBLUE = BLUE_LED;

// PINES PARA LOS JUGADORES, 1-8 JUGADOR 1, 9-16 JUGADOR 2
int led1 = PB_5;
int led2 = PB_0;
int led3 = PB_1;
int led4 = PE_4;
int led5 = PE_5;
int led6 = PB_4;
int led7 = PA_5;
int led8 = PA_6;
int led9 = PD_0;
int led10 = PD_1;
int led11 = PD_2;
int led12 = PD_3;
int led13 = PE_1;
int led14 = PE_2;
int led15 = PE_3;
int led16 = PD_7;

//LED PARA GANADORES
int led17 = PC_4;
int led18 = PC_5;

//*******************************************************************************
//DECLARACION DE VARIABLES
//*******************************************************************************
//Variables de control para el push de la TIVA
int J = PUSH2;
int J2 = PUSH1;
//Variables para evitar el rebote de los switch 
int antib1 = 0;
int antib2 = 0;
//Variables para llevar los puntos de ambos jugadores
int contador1=0;
int contador2=0;

//*********************************************************************************
//PROTOTIPOS DE FUNCIONES
//*********************************************************************************
void jugador1(void);
void jugador2(void);
void semaforo(void);
void win(void);

void setup() {
//Configuracion general de los pines
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
pinMode(led6, OUTPUT);
pinMode(led7, OUTPUT);
pinMode(led8, OUTPUT);
pinMode(led9,  OUTPUT);
pinMode(led10, OUTPUT);
pinMode(led11, OUTPUT);
pinMode(led12, OUTPUT);
pinMode(led13, OUTPUT);
pinMode(led14, OUTPUT);
pinMode(led15, OUTPUT);
pinMode(led16, OUTPUT);

pinMode(led17, OUTPUT);
pinMode(led18, OUTPUT);


pinMode(LRED, OUTPUT);
pinMode(LGREEN, OUTPUT);
pinMode(LBLUE, OUTPUT);

pinMode(J, INPUT_PULLUP);
pinMode(J2, INPUT_PULLUP);  

semaforo();
}

void loop(){
jugador1();
jugador2();
win();
}

void semaforo(void){
  //Enciendo el LED rojo
  digitalWrite(LRED, HIGH);
  digitalWrite(LGREEN, LOW);
  delay(1000);
  //Enciendo el LED amarillo
  digitalWrite(LRED, HIGH);
  digitalWrite(LGREEN, HIGH);
  delay(1000);
  //Enciendo el LED verde
  digitalWrite(LRED, LOW);
  digitalWrite(LGREEN, HIGH);
  delay(1000);
  return;
}

void win(void){
if (contador1>8){
  digitalWrite(led17, HIGH);
  digitalWrite(led8, LOW);  
  loop();
}

if (contador2>8){
  digitalWrite(led18, HIGH);
  digitalWrite(led16, LOW);
  loop();
}

}

void jugador1(void){
if (digitalRead(J) == LOW){ //Comprobar si el pulsador se presiono
  antib1 = 1;//actualizar el estado para evitar el antirrebote
}

if (digitalRead(J) == HIGH && antib1 == 1){
  antib1 = 0; //actualiza variable para que vuelva a funcionar el antirrebote
  delay(100);
  contador1++; //aumenta el puntaje del jugador 1
}

//Por la forma en que tome los pines, se tomara un switch case para encender segun la necesidad
switch (contador1)
  {
    
      case 0:
      //Encendidos para 0 punto
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
    
    case 1:
      //Encendidos para 1 punto
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 2:
      //Encendidos para 2 puntos
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 3:
      //Encendidos para 3 puntos
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 4:
      //Encendidos para 4 puntos
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 5:
      //Encendidos para 5 puntos
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
      
     case 6:
      //Encendidos para 6 puntos
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break; 
       
      case 7:
      //Encendidos para 7 puntos
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, HIGH);
      digitalWrite(led8, LOW);
      break; 
      
      case 8:
      //Encendidos para 8 puntos
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, HIGH);
      break;
  }
}

//Para el jugador 2 se aplico la misma logica que para el jugador 1
void jugador2(void){
if (digitalRead(J2) == LOW){
  antib2 = 1;
}
if (digitalRead(J2) == HIGH && antib2 == 1){
  antib2 = 0;
  delay(100);
  contador2++;
}

  switch (contador2){
    case 0:
      //Encendidos para 0 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
      
    case 1:
      //Encendidos para 1 punto
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 2:
      //Encendidos para 2 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 3:
      //Encendidos para 3 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 4:
      //Encendidos para 4 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 5:
      //Encendidos para 5 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, HIGH);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
      
     case 6:
      //Encendidos para 6 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, HIGH);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break; 
       
      case 7:
      //Encendidos para 7 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, HIGH);
      digitalWrite(led16, LOW);
      break; 
      
      case 8:
      //Encendidos para 8 puntos
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, HIGH);
      break; 
  }
}
