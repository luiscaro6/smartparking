++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                PROGRAMA PLACA MASTER - WIFI                  +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                    LIBRERIAS USADAS

<Wire.h> -> Usado por el protocolo I2C para comunicarse con el OLED
<Adafruit_GFX.h> -> Se usa por la pantalla OLED para generar imágenes y gráficos.
<Adafruit_SSD1306.h> -> Usado por la pantalla OLED. Genera las funciones display y comunica con el OLED.
<UniversalTelegramBot.h> -> Se usa para el bot de telegram (pendiente)
<ESP8266WiFi.h> -> Incluye las dependencias necesarias para que la placa se conecte a Internet.
<WiFiClient.h>-> Es necesario para que la placa se conecte a una red Wifi. Genera las funciones Wifi.
<WiFiClientSecure.h> -> Necesario para poder utilizar certificados SSL
<ArduinoJSON.h> -> Se usa para generar JSON para la API de Telegram.


                    CONSTANTES
WIFI_SSID -> Incluye el nombre de la red Wifi
WIFI_PASSWORD -> Incluye la contraseña de la red Wifi proporcionada
BOT_TOKEN -> Especifica el token del Bot de Telegram a usar
ANCHO_PANTALLA -> Especifica el ancho de la pantalla OLED. Por defecto: 128
ALTO_PANTALLA -> Especifica el alto de la pantalla OLED. Por defecto: 64
DIRECCION_PANTALLA -> Especifica la direccion I2C de la pantalla OLED. Por defecto: 0x3C


                      CLASES
cert -> Incluye los certificados de Telegram
bot -> Incluye el token del bot y especifica qué certificado utilizar (cert)
display -> Especifica el tipo de controlador del OLED (Adafruit SSD1306), sus medidas y el pin de reset (-1)


                     VARIABLES
Nombre -> tipo -> Descripción -> Valor inicial
linea -> int -> Especifica la línea en la que tiene que escribir el OLED -> 20
