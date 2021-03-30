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
int led16 = PF_1;

//LED PARA GANADORES
int led17 = PC_4;
int led18 = PC_5;

//***************************************************
//DECLARACION DE VARIABLES
//***************************************************
//Variables de control para el push de la TIVA
int J = PUSH2;
int J2 = PUSH1;
//Variables para evitar el rebote de los switch 
int antib1 = 0;
int antib2 = 0;
//Variables para llevar los puntos de ambos jugadores
int contador1=0;
int contador2=0;


//Subrutinas para llevar la programación de cada jugador, semaforo y el de victoria
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


}

void loop(){

semaforo();
jugador1();
jugador2();
win();

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
