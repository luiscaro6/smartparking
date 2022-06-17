# PROYECTO SMARTPARKING + PUENTE DE LA PEPA

Este proyecto fue realizado durante el curso 2021/2022 por los alumnos de Computación y Robótica de 3º de E.S.O. del I.E.S. Alventus, Trebujena (Cádiz).

Está compuesto por dos proyectos, **SmartParking** y el **Puente de la Pepa.** 

## SmartParking
Este proyecto era el que más código iba a necesitar en un principio, y por ello creamos el repositorio con ese nombre. Consiste en un aparcamiento para el cual **no necesitas ningún tipo de ticket, sino que funciona a través del teléfono** en su totalidad, gracias a la app de mensajería instantánea *Telegram*. En dicha app podemos encontrar un bot dedicado a este proyecto (pdte. link) y junto a la maqueta en madera tendríamos un aparcamiento totalmente independiente e inteligente.

Por el tiempo, no pudo ser completado, pero el código de Telegram se encontraba prácticamente acabado, quedando únicamente pendiente la programación de la placa Arduino UNO que se encargaba de expulsar los coches así como del movimiento de las cintas.

### Materiales
* Placa Wemos D1 (Wifi)
* Placa Arduino UNO
* Arduino UNO Shield
* 1 servomotor continuo
* 4 servomotores
* Madera
* Materiales reciclados
* Cables DUPONT
* OLED 128x64 I2C


### Funcionamiento
El código comienza conectándose a una red WiFi y estableciendo conexión a los servidores de *Telegram*. Una vez ahí, chequea los mensajes y una vez que recibe uno comienza a interpretarlo. En caso de ser una solicitud nueva de aparcamiento, elige en qué plaza lo va a aparcar y almacena la fecha y la hora en la que ha entrado. Después, envía un mensaje de confirmación al chat de *Telegram* del cliente y la otra placa comienza su función.


### Pendiente
Queda pendiente la completa integración de la placa **Arduino UNO** para el control de los motores para así hacer el aparcamiento funcional de manera mecánica, y no solo lógica. Además, no se llegó a completar el sistema de aparcamiento en su totalidad, por ejemplo el procedimiento de salir del aparcamiento queda pendiente.

### Fotos
(prox)

## Puente de la Pepa

Este proyecto estaba dedicado al *Puente de la Constitución de 1812* localizado en Cádiz. Se trata de un puente atirantado de más de 
3 kilómetros de longitud. y 187 metros de altura. Este fue el proyecto presentado en la tercera edición del certamen de Robótica libre Gaditana (*Robycad’22*) celebrada en la Escuela de Ingeniería Superior de la Universidad de Cádiz el pasado **6 de mayo de 2022.**

El proyecto está compuesto de la maqueta a escala del puente, hecha con tablones y listones de madera, que se encuentran apoyados sobre un tablero de madera. En uno de los extremos se encuentra la placa con su cableado, y el sensor LDR. Justo enfrente podemos encontrar el LCD 16X2 junto al conversor I2C. En el otro extremo encontramos una maqueta de *El Corte Inglés* Bahía de Cádiz.

**El proyecto actualmente se encuentra finalizado.**

### Materiales
* Placa Arduino UNO
* Arduino UNO Shield
* Relé
* LDR (Resistencia dependiente de la luz)
* Dos sensores de ultrasonidos HC-SR04
* Cables DUPONT
* LCD 16X2
* Conversor a I2C para LCD
* Madera
* Cartón
* Corcho

### Funcionamiento

El código lo podemos dividir en dos partes. La primera de ellas es la de las **farolas** controladas por el **LDR**. Un LDR es una resistencia dependiente de la luz, que proporciona a la placa Arduino la capacidad de poder medir **el nivel de luz del ambiente**. El programa se encarga de que cuando el nivel de luz baje del umbral establecido, accione el relé para poder encender las farolas.

La segunda parte del código se trata de un sensor de velocidad. Cuando uno de los dos **sensores de ultrasonidos** detecta que hay un objeto debajo de él, comienza a contar el tiempo que pasa hasta que llega al otro. Una vez que tenemos ambos datos, la placa se encarga de calcular a cuántos kilómetros por hora iba el móvil. Dicha velocidad la muestra a través del LCD.


### Pendiente
**El proyecto se encuentra finalizado, aunque siempre podemos mejorar o ampliar algo :)**

### Fotos
![alt text]([https://raw.githubusercontent.com/luiscaro6/smartparking/blob/main/PUENTE DE LA PEPA/img/Cartel.jpeg](https://github.com/luiscaro6/smartparking/blob/5f6f088c16de591290b4665383ade60551231422/PUENTE%20DE%20LA%20PEPA/img/Cartel.jpeg))(prox)

