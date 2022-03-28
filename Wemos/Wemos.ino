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
#include <ESP8266Ping.h>
#include <NTPClient.h>

#define WIFI_SSID "Livebox6-188D" //SSID de la red Wifi
#define WIFI_PASSWORD "56YFnRDTCsP7" //Contraseña de la red Wifi
#define BOT_TOKEN "5175736759:AAFvgvtX_Q-UjpOJ4aX_HTE7oTRBZ0Lu2Dk" //Token del bot de Telegram
#define ID_LUIS "536826985" //Id de Luis en Telegram
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
int estado = 0;
int plaza1_estado = 0;
int plaza2_estado = 0;
int plaza3_estado = 0;

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
}

void ConectarPlaca() { //Esta función no tiene utilidad ahora mismo
  Enviardatos("Placa lista", 1);  
}

void ActualizarHora(){
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());  
  display.setCursor(80, 5);
  display.setTextColor(WHITE);
  display.print(timeClient.getFormattedTime());
  display.setCursor(80, 5);
  display.setTextColor(WHITE, BLACK);
  display.print(timeClient.getFormattedTime());  
  display.display();
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
}

void loop() {
  ActualizarHora();
  delay(1000);
}
