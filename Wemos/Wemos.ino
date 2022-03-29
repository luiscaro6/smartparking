/*+++++++++++++++++++++++++++++++++++++++++
+      PROYECTO PARKING INTELIGENTE       +
+      Ultima modificacion: 28/03/2022    +
++++++++++++++++++++++++++++++++++++++++++*/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define WIFI_SSID "POCO M3 Pro 5G de Luisito" //SSID de la red Wifi
#define WIFI_PASSWORD "lhxx5332" //Contraseña de la red Wifi
#define BOT_TOKEN "5175736759:AAFvgvtX_Q-UjpOJ4aX_HTE7oTRBZ0Lu2Dk" //Token del bot de Telegram
#define ID_LUIS "536826985" //Id de Luis en Telegram
#define ID_ADMIN "-1001635337717" //ID del canal de Admin
#define ANCHO_PANTALLA 128 // Ancho pantalla OLED
#define ALTO_PANTALLA 64 //* Alto pantalla OLED
#define DIRECCION_I2C 0x3C // Direccion 0x3C


WiFiClientSecure client;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(BOT_TOKEN, client);
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "hora.roa.es", 7200);


int linea = 20;
int estado = 0; //Numero de plazas ocupadas
int plaza1_estado = 0; //1 si ocupada, 0 si vacia
int plaza2_estado = 0; //1 si ocupada, 0 si vacia
int plaza3_estado = 0; //1 si ocupado, 0 si vacia

void Enviardatos(String dato, int modo){
  if(linea > 50){
    ConfigurarOLED();
    linea = 20;  
  }
  if (modo == 1){
    Serial.print("\r\n");
    Serial.print(dato);
    display.setCursor(5, linea); 
    display.print(dato);
    display.display();
  } else if (modo == 0){
    Serial.print(dato);
    display.print(dato);
    display.display();
  }
    linea = linea + 9;
}

void ConfigurarOLED(){
  display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_I2C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
  display.setCursor(32, 5);
  display.println("PREPARANDO");
  display.display();
  Enviardatos("OLED listo", 1);
}

void ConfigurarWifi(){
  configTime(0, 0, "pool.ntp.org");      //Establece la fuente horaria
  Enviardatos("Conectando a la red ", 1);
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    if (WiFi.status() == WL_CONNECT_FAILED) {
      ErrorConexion("Contrasena incorrecta");
    } else if (WiFi.status() == WL_NO_SSID_AVAIL) {
      ErrorConexion("Red no encontrada"); 
    }
  }
  Enviardatos("Conexion WiFi lista", 1);
  time_t now = time(nullptr); //Recupera la hora del servidor NTP
  timeClient.begin();
  timeClient.update();
}

void ErrorConexion(String motivo){
  display.clearDisplay();
  display.setCursor(10, 5);
  display.println("ERROR CONEXION WIFI");
  display.setCursor(0,20);
  display.print("SSID: ");
  display.println(WIFI_SSID);
  display.print("ERROR: ");
  display.println(motivo);
  if (WiFi.status() == WL_CONNECT_FAILED) {
    display.print("Contrasena: ");
    display.println(WIFI_PASSWORD);
  }
  display.display();
}

void ConectarTelegram(){
  client.setTrustAnchors(&cert); //Establece los certificados de telegram como de confianza
  bot.sendMessage(ID_ADMIN, "Hola, son las " + timeClient.getFormattedTime() + ". El parking se acaba de iniciar y está listo. A continuación se detalla el estado:", "");
  EnviarResumen();  
}

void ConectarPlaca() { //Esta función no tiene utilidad ahora mismo
  Enviardatos("Placa lista", 1);  
}

void ActualizarHora(){
  timeClient.update(); 
  display.setCursor(70, 5);
  display.setTextColor(WHITE, BLACK);
  display.print(timeClient.getFormattedTime());  
  display.display();
}

void ActualizarPantalla(){
  estado = plaza1_estado + plaza2_estado + plaza3_estado;
  if (estado == 3){
    display.setCursor(10, 5);
    display.setTextColor(WHITE, BLACK);
    display.print("COMPLETO");  
  }
  if (estado < 3){
    display.setCursor(10, 5);
    display.setTextColor(WHITE, BLACK);
    display.print("  LIBRE  ");  
  }
  if (plaza1_estado == 1){
    display.setCursor(10, 20);
    display.setTextColor(WHITE, BLACK);
    display.print("PLAZA 1: OCUPADA");  
  } else {
    display.setCursor(10, 20);
    display.setTextColor(WHITE, BLACK);    
    display.print("PLAZA 1: LIBRE");      
  }
  if (plaza2_estado == 1){
    display.setCursor(10, 30);
    display.setTextColor(WHITE, BLACK);    
    display.print("PLAZA 2: OCUPADA");  
  } else {
    display.setCursor(10, 30);
    display.setTextColor(WHITE, BLACK);    
    display.print("PLAZA 2: LIBRE");      
  }
  if (plaza3_estado == 1){
    display.setCursor(10, 40);
    display.setTextColor(WHITE, BLACK);    
    display.print("PLAZA 3: OCUPADA");  
  } else {
    display.setCursor(10, 40);
    display.setTextColor(WHITE, BLACK);    
    display.print("PLAZA 3: LIBRE");      
  }
  display.display();
}

void CambioCoche(int plaza, int accion){
  if (plaza = 1){
    if (accion = 1){
      plaza1_estado = 1;
      bot.sendMessage(ID_ADMIN, "Un coche acaba de ocupar la plaza 1", "");
      ActualizarPantalla();
    }
    if (accion = 0){
      plaza1_estado = 0;
      bot.sendMessage(ID_ADMIN, "La plaza 1 se acaba de liberar", "");
      ActualizarPantalla();
    }    
  }
  if (plaza = 2){
    if (accion = 1){
      plaza2_estado = 1;
      bot.sendMessage(ID_ADMIN, "Un coche acaba de ocupar la plaza 2", "");
      ActualizarPantalla();
    }
    if (accion = 0){
      plaza2_estado = 0;
      bot.sendMessage(ID_ADMIN, "La plaza 2 se acaba de liberar", "");
      ActualizarPantalla();
    }    
  }
  if (plaza = 3){
    if (accion = 1){
      plaza3_estado = 1;
      bot.sendMessage(ID_ADMIN, "Un coche acaba de ocupar la plaza 3", "");
      ActualizarPantalla();
    }
    if (accion = 0){
      plaza3_estado = 0;
      bot.sendMessage(ID_ADMIN, "La plaza 3 se acaba de liberar", "");
      ActualizarPantalla();
    }    
  }    
}

void EnviarResumen(){
    String plaza1_texto = "";
    String plaza2_texto = "";
    String plaza3_texto = "";
    String estado_texto = "";

    if (plaza1_estado == 1) {
      plaza1_texto = "ocupada";
    } else {
      plaza1_texto = "libre";
    }
    if (plaza2_estado == 1) {
      plaza2_texto = "ocupada";
    } else {
      plaza2_texto = "libre";
    }
    if (plaza3_estado == 1) {
      plaza3_texto = "ocupada";
    } else {
      plaza3_texto = "libre";
    }
    if (estado == 1) {
      estado_texto = "completo";
    } else {
      estado_texto = "libre";
    }
  bot.sendMessage(ID_ADMIN, "El parking actualmente se encuentra " + estado_texto + ". \n La plaza 1 está " + plaza1_texto + ". \n La plaza 2 está " + plaza2_texto + ". \n La plaza 3 está " + plaza3_texto + ".", "");
}

void RecibirMensajes(int numNewMessages) {
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    Serial.println(text);
    if (text = "hola"){
      bot.sendMessage(bot.messages[i].chat_id, "Recibido", ""); 
    }
    String from_name = bot.messages[i].from_name;

  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\r\n");
  ConfigurarOLED();
  ConfigurarWifi();
  ConectarTelegram();
  ConectarPlaca();
  delay(500);
  display.clearDisplay();
  display.display();
  ActualizarPantalla();
}

void loop() {
  ActualizarHora();
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages) {
    Serial.println("got response");
    RecibirMensajes(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
  delay(1000);
}
