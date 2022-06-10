#define PIN_LDR A1 //El LDR esta conectado al pin analogico 1
#define PIN_RELE 8 //El relé esta conectado al pin 8
#define DEBUG 0 //Modo depuracion

int nivelLuz = 0;

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
}
void loop() {
  leerluz();
  if (nivelLuz >= 400){
    digitalWrite(PIN_RELE, LOW);  
  } else {
    digitalWrite(PIN_RELE, HIGH);  
  }
  delay(500);
}
