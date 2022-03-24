#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <UniversalTelegramBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

#define WIFI_SSID "Livebox6-188D" //SSID de la red Wifi
#define WIFI_PASSWORD "56YFnRDTCsP7" //Contraseña de la red Wifi
#define BOT_TOKEN "5084575645:AAFYehTTPSV049yUlBJO3RjXTUfhAY6LP8M" //Token del bot de Telegram
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED

WiFiClientSecure secured_client;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

int linea = 20;

void ConfigurarOLED(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
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
  secured_client.setTrustAnchors(&cert); //Establece los certificados de telegram como de confianza
  Enviardatos("Conectando a la red ", 1);
  Enviardatos(WIFI_SSID, 0);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Enviardatos(".", 0);
    delay(500);
  }
  Serial.print("\nConectado a la red Wifi. Direccion IP: ");
  Serial.println(WiFi.localIP());
  time_t now = time(nullptr); //Recupera la hora del servidor NTP
  Serial.println(now);
}

void Enviardatos(String dato, int modo){
  if (modo == 1){
    Serial.print(dato);
    display.setCursor(5, linea); 
    display.print(dato);
    display.display();
    linea = linea + 9;
  } else if (modo == 0){
    Serial.print(dato);
    display.print(dato);
    display.display();
  }


  }

void setup() {
  Serial.begin(115200);
  ConfigurarOLED();
  ConfigurarWifi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
