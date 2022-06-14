#include <NewPing.h>
/*+++++++++++++++++++++++++++++++++
+   PROYECTO PUENTE DE LA PEPA    +
+ Ultima modificación: 10/06/2022 +
++++++++++++++++++++++++++++++++++*/

#define PIN_LDR A1 //El LDR esta conectado al pin analogico 1
#define PIN_RELE 8 //El relé esta conectado al pin 8
#define DEBUG 1 //Modo depuracion
#define TRIGGER_US1 9 // El trigger del ultrasonidos 1 está conectado al pin 7
#define ECHO_US1 6 //El echo del ultrasonidos 1 está conectado al pin 6
#define TRIGGER_US2 5 //El trigger del ultrasonidos 2 está conectado al pin 5
#define ECHO_US2 10 //El echo del ultrasonidos 2 está conectado al pin 4

NewPing ultra1(TRIGGER_US1, ECHO_US1, 15);
NewPing ultra2(TRIGGER_US2, ECHO_US2, 15);

int nivelLuz = 0;
int distanciaUS1 = 0;
int distanciaUS2 = 0;

void setup() {
  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_RELE, OUTPUT);
  pinMode(TRIGGER_US1, OUTPUT);
  pinMode(TRIGGER_US2, OUTPUT);
  pinMode(ECHO_US1, INPUT);
  pinMode(ECHO_US2, INPUT);
  Serial.begin(9600);
}

void leerluz(){ 
  int medicion = analogRead(PIN_LDR); //Almacena el nivel de luz en una variable temporal
  nivelLuz = medicion;
  if (DEBUG == 1){
    Serial.println(nivelLuz);   //Envia los datos por el puerto serie si el modo de depuración esta activado.
  }
  if (medicion >= 400){
    digitalWrite(PIN_RELE, LOW);  
  } else {
    digitalWrite(PIN_RELE, HIGH);  
  }
}

void leerultrasonidos1(){ //Lee si hay un coche bajo el ultrasonidos numero 1
  distanciaUS1 = ultra1.ping_cm();
  if (DEBUG == 1){
    Serial.print(distanciaUS1); // obtener el valor en cm (0 = fuera de rango)
    Serial.println(" cm. SENSOR 1");  
  }
  if (distanciaUS1 < 10){
    Serial.println("Coche bajo sensor 1. Comienza medicion.");
    comenzarmedicion(1);  
  }
}

void leerultrasonidos2(){ //Lee si hay un coche bajo el ultrasonidos numero 2
  distanciaUS2 = ultra2.ping_cm();
  if (DEBUG == 1){
    Serial.print(distanciaUS2); // obtener el valor en cm (0 = fuera de rango)
    Serial.println(" cm. SENSOR 2");  
  }
  if (distanciaUS2 < 10){
    Serial.println("Coche bajo sensor 2. Comienza medicion.");
    comenzarmedicion(2);  
  }
}

void comenzarmedicion(int disp){//Comienza a contar el tiempo cuando hay un coche bajo uno de los dos sensores
  int milliscomienzo = millis(); //Guarda el tiempo en el que pasó el primer coche
  int millisfinal = 0; //Variable para almacenar el tiempo en el que pasa por el segundo coche.
  if (disp == 1){
    while (distanciaUS2 > 8 && distanciaUS2 > 2){
      distanciaUS2 = ultra2.ping_cm();
      if (DEBUG == 1){
        Serial.print(distanciaUS2); // obtener el valor en cm (0 = fuera de rango)
        Serial.println(" cm. SENSOR 2");  
      }
    }  
    millisfinal = millis();
  }
  if (disp == 2){
    while (distanciaUS1 > 8 && distanciaUS1 > 2){
      distanciaUS1 = ultra1.ping_cm();
      if (DEBUG == 1){
        Serial.print(distanciaUS1); // obtener el valor en cm (0 = fuera de rango)
        Serial.println(" cm. SENSOR 1");  
      }
    }  
    millisfinal = millis();
    calcularvelocidad(milliscomienzo, millisfinal);
  }  
}

void calcularvelocidad(int millisinicio, int millisfinal){
  int millisempleados = 0;
  Serial.println(millisfinal);
  Serial.println(millisinicio);
  millisempleados = millisfinal - millisinicio; //Calcula cuantos milisegundos pasan desde que empezó hasta que termina
  Serial.println("Milisegundos empleados: ");
  Serial.println(millisempleados);
  float velocidad = 0;
  velocidad = 40000 / millisempleados;
  int velocidadkmh = velocidad * 3.6;
  Serial.println("VELOCIDAD EN KM/H: ");
  Serial.println(velocidadenkm);

}

void loop() {
  leerluz();
  leerultrasonidos1();
  leerultrasonidos2();
  delay(500);
}
