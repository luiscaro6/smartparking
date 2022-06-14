
/*+++++++++++++++++++++++++++++++++
+   PROYECTO PUENTE DE LA PEPA    +
+ Ultima modificación: 14/06/2022 +
++++++++++++++++++++++++++++++++++*/

#include <NewPing.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define PIN_LDR A1 //El LDR esta conectado al pin analogico 1
#define PIN_RELE 8 //El relé esta conectado al pin 8
#define DEBUG 0 //Modo depuracion
#define TRIGGER_US1 9 // El trigger del ultrasonidos 1 está conectado al pin 7
#define ECHO_US1 6 //El echo del ultrasonidos 1 está conectado al pin 6
#define TRIGGER_US2 5 //El trigger del ultrasonidos 2 está conectado al pin 5
#define ECHO_US2 10 //El echo del ultrasonidos 2 está conectado al pin 4

NewPing ultra1(TRIGGER_US1, ECHO_US1, 15); //Crea clase ultra1 con los parámetros del ultrasonidos 1
NewPing ultra2(TRIGGER_US2, ECHO_US2, 15); //Crea clase ultra2 con los parámetros del ultrasonidos 2
LiquidCrystal_I2C lcd(0x27,16,2); //Crea clase lcd con los parámetros y dirección I2C de la pantalla LCD

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
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("PUENTE DE LA"); 
  lcd.setCursor(6, 1);
  lcd.print("PEPA");
}

void leerluz(){ 
  int medicion = analogRead(PIN_LDR); //Almacena el nivel de luz en una variable temporal
  nivelLuz = medicion;
  if (DEBUG == 1){
    Serial.println(nivelLuz);   //Envia los datos por el puerto serie si el modo de depuración esta activado.
  }
  if (medicion >= 400){
    digitalWrite(PIN_RELE, LOW);  //Enciende las farolas si se necesita
  } else {
    digitalWrite(PIN_RELE, HIGH);  //Apaga las farolas si se necesita
  }
}

void leerultrasonidos1(){ //Lee si hay un coche bajo el ultrasonidos numero 1
  distanciaUS1 = ultra1.ping_cm();
  if (DEBUG == 1){
    Serial.print(distanciaUS1); // obtener el valor en cm (0 = fuera de rango)
    Serial.println(" cm. SENSOR 1");  
  }
  if (distanciaUS1 < 9){
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
  if (distanciaUS2 < 9){
    Serial.println("Coche bajo sensor 2. Comienza medicion.");
    comenzarmedicion(2);  
  }
}

void comenzarmedicion(int disp){//Comienza a contar el tiempo cuando hay un coche bajo uno de los dos sensores
  int milliscomienzo = millis(); //Guarda el tiempo en el que pasó el primer coche
  int millisfinal = 0; //Variable para almacenar el tiempo en el que pasa por el segundo coche.
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("MIDIENDO");
  lcd.setCursor(2,1);
  lcd.print("VELOCIDAD...");
  if (disp == 1){
    while (distanciaUS2 > 8 && distanciaUS2 > 2){ //Espera hasta que haya un objeto bajo el otro sensor, obviando los dos primeros cm para evitar errores de medición.
      distanciaUS2 = ultra2.ping_cm(); 
      if (DEBUG == 1){
        Serial.print(distanciaUS2); // obtener el valor en cm (0 = fuera de rango)
        Serial.println(" cm. SENSOR 2");  
      }
    }  
    millisfinal = millis(); //Guarda el tiempo en el que ha llegado a su destino
    calcularvelocidad(milliscomienzo, millisfinal); 
  }
  if (disp == 2){
    while (distanciaUS1 > 8 && distanciaUS1 > 2){ //Espera hasta que haya un objeto bajo el otro sensor, obviando los dos primeros cm para evitar errores de medición.
      distanciaUS1 = ultra1.ping_cm();
      if (DEBUG == 1){
        Serial.print(distanciaUS1); // obtener el valor en cm (0 = fuera de rango)
        Serial.println(" cm. SENSOR 1");  
      }
    }  
    millisfinal = millis(); //Guarda el tiempo en el que ha llegado a su destino
    calcularvelocidad(milliscomienzo, millisfinal);
  }  
}

void calcularvelocidad(int millisinicio, int millisfinal){ //Función que se encarga de calcular el tiempo empleado en recorrer el camino y pasarlo a km/h
  lcd.clear();
  lcd.print("VELOCIDAD ACTUAL");
  int millisempleados = 0;
  if(DEBUG == 1){
    Serial.print("Ha salido a: ");
    Serial.println(millisinicio);
    Serial.print("Ha llegado a: ");
    Serial.println(millisfinal);
  }
  millisempleados = millisfinal - millisinicio; //Calcula cuantos milisegundos pasan desde que empezó hasta que termina
  Serial.print("El móvil acaba de terminar el radar de tramo. ");
  float velocidad = 0;
  velocidad = 40000 / millisempleados;
  int velocidadkmh = velocidad * 3.6;
  Serial.print("VELOCIDAD EN KM/H: ");
  Serial.println(velocidadkmh);
  Serial.println("---------------------------------------------------");
  lcd.setCursor(5, 1);
  lcd.print(velocidadkmh);
  lcd.setCursor(8, 1);
  lcd.print(" km/h");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("PUENTE DE LA"); 
  lcd.setCursor(6, 1);
  lcd.print("PEPA");
}


void loop() {
  leerluz();
  leerultrasonidos1();
  leerultrasonidos2();
  delay(50);
}
