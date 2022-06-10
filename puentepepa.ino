/*+++++++++++++++++++++++++++++++++
+   PROYECTO PUENTE DE LA PEPA    +
+ Ultima modificación: 10/06/2022 +
*/+++++++++++++++++++++++++++++++++

#define PIN_LDR A1 //El LDR esta conectado al pin analogico 1
#define PIN_RELE 8 //El relé esta conectado al pin 8
#define DEBUG 0 //Modo depuracion
#define TRIGGER_US1 3 // El trigger del ultrasonidos 1 está conectado al pin 3
#define ECHO_US1 4 //El echo del ultrasonidos 1 está conectado al pin 4
#define TRIGGER_US2 5 //El trigger del ultrasonidos 2 está conectado al pin 5
#define ECHO_US2 6 //El trigger del ultrasonidos 2 está conectado al pin 6


void setup() {
  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_RELE, OUTPUT);
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
  
}

void leerultrasonidos2(){ //Lee si hay un coche bajo el ultrasonidos numero 2


}

void comenzarmedicion(int disp)//Comienza a contar el tiempo cuando hay un coche bajo uno de los dos sensores
  int milliscomienzo = millis(); //Guarda el tiempo en el que pasó el primer coche
  int millisfinal = 0; //Variable para almacenar el tiempo en el que pasa por el segundo coche.
  break(); //BREAK BECAUSE NO CODE
  
}

void calcularvelocidad(int millisinicio, int millis final){
  int millisempleados = 0;
  millisempleados = millisfinal - millisinicio; //Calcula cuantos milisegundos pasan desde que empezó hasta que termina
  

}

void loop() {
  leerluz();
  leerultrasonidos1();
  leerultrasonidos2();
  delay(50);
}
