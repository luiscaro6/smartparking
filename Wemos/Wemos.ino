/*+++++++++++++++++++++++++++++++++++++++++
+      PROYECTO PARKING INTELIGENTE       +
+      Ultima modificacion: 01/04/2022    +
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
bool plaza1_estado = 0; //1 si ocupada, 0 si vacia
String plaza1_id = "0";
String plaza1_hora = "00:00:00";
bool plaza2_estado = 0; //1 si ocupada, 0 si vacia
String plaza2_id = "0";
String plaza2_hora = "00:00:00";
bool plaza3_estado = 0; //1 si ocupado, 0 si vacia
String plaza3_id = "0";
String plaza3_hora = "00:00:00";

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

void ConfigurarOLED(){ //Prepara el display OLED, lo inicializa y vacía la pantalla
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

void ConfigurarWifi(){ //Se conecta a la red Wifi establecida, espera a su conexion e inicia el cliente NTP
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

void ErrorConexion(String motivo){ // Se usa para mostrar en el display el error por el que no se puede conectar a la red Wifi
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

void ConectarPlaca() { //Esta función no tiene utilidad ahora mismo
  Enviardatos("Placa lista", 1);  
}

void ActualizarHora(){ //Se usa para mostrar la hora actual en la parte superior de la pantalla y actualizar el cliente NTP
  timeClient.update();
  String Horaentera = timeClient.getFormattedTime();
  int separardospuntos = Horaentera.indexOf(":");
  String Hora = Horaentera.substring(0, separardospuntos);
  String Minutos = Horaentera.substring(5, separardospuntos);    
  String Segundos = Horaentera.substring(10, separardospuntos); 
  String hhmm = Hora + Minutos;
  display.setCursor(70, 5);
  display.setTextColor(WHITE, BLACK);
  display.print(hhmm);  
  display.display();
}

void ActualizarPantalla(){ // Se usa para mostrar en la pantalla de inicio el estado de las plazas y el estado del parking
  estado = plaza1_estado + plaza2_estado + plaza3_estado;
  int plazas = 3;
  int plazas_libres = plazas - estado;
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
  display.setCursor(10, 60);
  display.setTextColor(WHITE, BLACK);
  display.print("PLAZAS LIBRES: " + plazas_libres);
  display.display();
}

void CambioCoche(int plaza, int accion, int ID_chat){
  if (plaza == 1){
    if (accion == 1){
      plaza1_estado = 1;
      String Admin = "Un coche acaba de ocupar la plaza 1. Su ID es: ");
      Admin += ID_chat;
      bot.sendMessage(ID_ADMIN, Admin, "");
      ActualizarPantalla();
    }
    if (accion == 0){
      plaza1_estado = 0;
      bot.sendMessage(ID_ADMIN, "La plaza 1 se acaba de liberar", "");
      ActualizarPantalla();
    }    
  }
  if (plaza == 2){
    if (accion == 1){
      plaza2_estado = 1;
      String Admin = "Un coche acaba de ocupar la plaza 2. Su ID es: ");
      Admin += ID_chat;
      bot.sendMessage(ID_ADMIN, Admin, "");
      ActualizarPantalla();
    }
    if (accion == 0){
      plaza2_estado = 0;
      bot.sendMessage(ID_ADMIN, "La plaza 2 se acaba de liberar", "");
      ActualizarPantalla();
    }    
  }
  if (plaza == 3){
    if (accion == 1){
      plaza3_estado = 1;
      String Admin = "Un coche acaba de ocupar la plaza 3. Su ID es: ");
      Admin += ID_chat;
      bot.sendMessage(ID_ADMIN, Admin, "");
      ActualizarPantalla();
    }
    if (accion == 0){
      plaza3_estado = 0;
      bot.sendMessage(ID_ADMIN, "La plaza 3 se acaba de liberar", "");
      ActualizarPantalla();
    }    
  }    
}

void EnviarResumen(){ //Esta función se utiliza para enviar un mensaje con el estado del parking y sus plazas al canal de admin
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
    if (estado == 3) {
      estado_texto = "completo";
    } else {
      estado_texto = "libre";
    }
  bot.sendMessage(ID_ADMIN, "El parking actualmente se encuentra " + estado_texto + ". \n La plaza 1 está " + plaza1_texto + ". \n La plaza 2 está " + plaza2_texto + ". \n La plaza 3 está " + plaza3_texto + ".", "");
}

void RecibirMensajes(int numMensajesNuevos) { //Esta función se encarga de la recepción de mensajes y su interpretación
  for (int i=0; i<numMensajesNuevos; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    Serial.println("Mensaje " + text + " recibido de " + from_name + " con ID " + chat_id);
    if (text == "/start"){
      String Bienvenida = "Hola " + from_name + ".\n";
      Bienvenida += "Te damos la bienvenida al sistema de parking inteligente.\n";
      Bienvenida += "A continuación te detallamos los comandos que puedes utilizar aquí\n\n";
      Bienvenida += "/help : Ayuda de comandos\n";
      Bienvenida += "/aparcar : Comenzar un aparcamiento\n";
      Bienvenida += "/info : Consultar si puedes aparcar\n";
      Bienvenida += "/salir : Terminar tu aparcamiento\n";
      Bienvenida += "/info_parking : Ver el estado de tu sesión de aparcamiento actual\n"; 
      bot.sendMessage(chat_id, Bienvenida, "");      
    }
    if (text == "/help"){
      String Ayuda = "A continuación te detallamos los comandos que puedes utilizar aquí\n\n";
      Ayuda += "/help : Ayuda de comandos\n";
      Ayuda += "/aparcar : Comenzar un aparcamiento\n";
      Ayuda += "/info : Consultar si puedes aparcar o no\n";
      Ayuda += "/salir : Terminar tu aparcamiento\n";
      Ayuda += "/info_parking : Ver el estado de tu sesión de aparcamiento actual";  
      bot.sendMessage(chat_id, Ayuda, "");      
    }
    if (text == "/aparcar"){
      String keyboardJson = "[[{ \"text\" : \"Continuar\", \"callback_data\" : \"Iniciaraparcar\" }],[{ \"text\" : \"Cancelar\", \"callback_data\" : \"Cancelaraparcar\" }]]";
      String Aparcar = "Vas a iniciar una sesión de aparcamiento.\n";
      Aparcar += "¿Estás seguro?\n";
      Aparcar += "Si pulsas en 'Continuar' se abrirá la barrera para que dejes tu coche y en unos segundos te llegará la información\n";  
      bot.sendMessageWithInlineKeyboard(chat_id, Aparcar, "", keyboardJson);      
    }
    if (text == "Cancelaraparcar"){
      bot.sendMessage(chat_id, "Cancelado", "");
    }
    if (text == "Iniciaraparcar"){
      int Error = 0;
      if (plaza1_id == chat_id){
        Error += 1;
      }
      if (plaza2_id == chat_id){
        Error += 1;
      }
      if (plaza3_id == chat_id){
        Error += 1;
      }            
      if (Error > 0){
          String Error = "Actualmente tiene otra sesion de aparcamiento iniciada. \n";
          Error += "Consulta su estado con /info_parking";
          bot.sendMessage(chat_id, Error, "");
      }else if (plaza1_estado == 0){
        plaza1_id = chat_id;
        CambioCoche(1, 1, chat_id);
        String Aparcamiento = "Se ha iniciado tu aparcamiento correctamente en la plaza 1.\n";
        Aparcamiento += "Actualmente son las ";
        Aparcamiento += timeClient.getFormattedTime();
        Aparcamiento += "\n¡Gracias!";
        bot.sendMessage(chat_id, Aparcamiento, "");          
      } else if (plaza2_estado == 0){
        plaza2_id = chat_id;
        CambioCoche(2, 1, chat_id);
        String Aparcamiento = "Se ha iniciado tu aparcamiento correctamente en la plaza 2.\n";
        Aparcamiento += "Actualmente son las ";
        Aparcamiento += timeClient.getFormattedTime();
        Aparcamiento += "\n¡Gracias!";
        bot.sendMessage(chat_id, Aparcamiento, "");          
      } else if (plaza3_estado == 0){
        plaza3_id = chat_id;
        CambioCoche(3, 1, chat_id);
        String Aparcamiento = "Se ha iniciado tu aparcamiento correctamente en la plaza 3.\n";
        Aparcamiento += "Actualmente son las ";
        Aparcamiento += timeClient.getFormattedTime();
        Aparcamiento += "\n¡Gracias!";
        bot.sendMessage(chat_id, Aparcamiento, "");
      } else {
        bot.sendMessage(chat_id, "Lo sentimos, pero nuestro parking está completo actualmente", "");  
      }
      
    }    
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\r\n");
  ConfigurarOLED();
  ConfigurarWifi();
  client.setTrustAnchors(&cert); //Establece los certificados de telegram como de confianza
  EnviarResumen();  
  ConectarPlaca();
  delay(500);
  display.clearDisplay();
  display.display();
  ActualizarPantalla();
}

void loop() {
  ActualizarHora();
  int numMensajesNuevos = bot.getUpdates(bot.last_message_received + 1);
  while(numMensajesNuevos) {
    Serial.println("Nuevo mensaje");
    RecibirMensajes(numMensajesNuevos);
    numMensajesNuevos = bot.getUpdates(bot.last_message_received + 1);
  }
  delay(1000);
}
