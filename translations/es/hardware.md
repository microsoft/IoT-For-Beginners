# Hardware

La **T** en IoT significa **Things** (Cosas) y se refiere a los dispositivos que interactúan con el mundo que nos rodea. Cada proyecto se basa en hardware real disponible para estudiantes y aficionados. Tenemos dos opciones de hardware IoT para usar, dependiendo de las preferencias personales, el conocimiento o las preferencias del lenguaje de programación, los objetivos de aprendizaje y la disponibilidad. También hemos proporcionado una versión de 'hardware virtual' para aquellos que no tienen acceso a hardware o que desean aprender más antes de comprometerse con una compra.

> 💁 No necesitas comprar ningún hardware IoT para completar las tareas. Puedes hacer todo utilizando hardware IoT virtual.

Las opciones de hardware físico son Arduino o Raspberry Pi. Cada plataforma tiene sus propias ventajas y desventajas, y todas se explican en una de las lecciones iniciales. Si aún no has decidido qué plataforma de hardware usar, puedes revisar [la lección dos del primer proyecto](./1-getting-started/lessons/2-deeper-dive/README.md) para decidir cuál te interesa más aprender.

El hardware específico fue elegido para reducir la complejidad de las lecciones y tareas. Aunque otros dispositivos pueden funcionar, no podemos garantizar que todas las tareas sean compatibles con tu dispositivo sin hardware adicional. Por ejemplo, muchos dispositivos Arduino no tienen WiFi, que es necesario para conectarse a la nube; el terminal Wio fue elegido porque tiene WiFi integrado.

También necesitarás algunos elementos no técnicos, como tierra o una planta en maceta, y frutas o verduras.

## Compra los kits

![El logo de Seeed Studios](../../translated_images/es/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios ha tenido la amabilidad de poner todo el hardware disponible en kits fáciles de comprar:

### Arduino - Wio Terminal

**[IoT para principiantes con Seeed y Microsoft - Kit de inicio Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![El kit de hardware Wio Terminal](../../translated_images/es/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT para principiantes con Seeed y Microsoft - Kit de inicio Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![El kit de hardware Raspberry Pi Terminal](../../translated_images/es/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Todo el código para dispositivos Arduino está en C++. Para completar todas las tareas, necesitarás lo siguiente:

### Hardware de Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opcional* - Cable USB-C o adaptador de USB-A a USB-C. El terminal Wio tiene un puerto USB-C y viene con un cable USB-C a USB-A. Si tu PC o Mac solo tiene puertos USB-C, necesitarás un cable USB-C o un adaptador de USB-A a USB-C.

### Sensores y actuadores específicos de Arduino

Estos son específicos para usar el dispositivo Arduino Wio Terminal y no son relevantes para usar el Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Cables jumper para protoboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Auriculares u otro altavoz con conector de 3.5mm, o un altavoz JST como:
  * [Altavoz mono cerrado - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Tarjeta microSD de 16GB o menos, junto con un conector para usar la tarjeta SD con tu computadora si no tienes uno integrado. **NOTA** - El terminal Wio solo admite tarjetas SD de hasta 16GB, no admite capacidades mayores.

## Raspberry Pi

Todo el código para dispositivos Raspberry Pi está en Python. Para completar todas las tareas, necesitarás lo siguiente:

### Hardware de Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Las versiones desde la Pi 2B en adelante deberían funcionar con las tareas de estas lecciones. Si planeas ejecutar VS Code directamente en la Pi, entonces se necesita una Pi 4 con 2GB o más de RAM. Si vas a acceder a la Pi de forma remota, cualquier Pi 2B o superior funcionará.
* Tarjeta microSD (puedes conseguir kits de Raspberry Pi que incluyen una tarjeta microSD), junto con un conector para usar la tarjeta SD con tu computadora si no tienes uno integrado.
* Fuente de alimentación USB (puedes conseguir kits de Raspberry Pi 4 que incluyen una fuente de alimentación). Si estás usando una Raspberry Pi 4, necesitas una fuente de alimentación USB-C; los dispositivos anteriores necesitan una fuente de alimentación micro-USB.

### Sensores y actuadores específicos de Raspberry Pi

Estos son específicos para usar la Raspberry Pi y no son relevantes para usar el dispositivo Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Módulo de cámara Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Micrófono y altavoz:

  Usa uno de los siguientes (o equivalente):
  * Cualquier micrófono USB con cualquier altavoz USB, o altavoz con cable de conector de 3.5mm, o salida de audio HDMI si tu Raspberry Pi está conectada a un monitor o TV con altavoces.
  * Cualquier auricular USB con micrófono incorporado.
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) con:
    * Auriculares u otro altavoz con conector de 3.5mm, o un altavoz JST como:
    * [Altavoz mono cerrado - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [Altavoz USB para conferencias](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Sensor de luz Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Botón Grove](https://www.seeedstudio.com/Grove-Button.html)

## Sensores y actuadores

La mayoría de los sensores y actuadores necesarios se utilizan tanto en las rutas de aprendizaje de Arduino como de Raspberry Pi:

* [LED Grove](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Sensor de humedad y temperatura Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Sensor de humedad del suelo capacitivo Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Relé Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Sensor de distancia Time of Flight Grove](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Hardware opcional

Las lecciones sobre riego automatizado funcionan utilizando un relé. Como opción, puedes conectar este relé a una bomba de agua alimentada por USB utilizando el hardware que se detalla a continuación.

* [Bomba de agua de 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminal USB](https://www.adafruit.com/product/3628)
* Tubos de silicona
* Cables rojo y negro
* Destornillador plano pequeño

## Hardware virtual

La ruta de hardware virtual proporcionará simuladores para los sensores y actuadores, implementados en Python. Dependiendo de la disponibilidad de tu hardware, puedes ejecutar esto en tu dispositivo de desarrollo normal, como una Mac, PC, o ejecutarlo en una Raspberry Pi y simular solo el hardware que no tengas. Por ejemplo, si tienes la cámara Raspberry Pi pero no los sensores Grove, podrás ejecutar el código del dispositivo virtual en tu Pi y simular los sensores Grove, pero usar una cámara física.

El hardware virtual utilizará el [proyecto CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Para completar estas lecciones, necesitarás tener una cámara web, micrófono y salida de audio como altavoces o auriculares. Estos pueden ser integrados o externos, y deben estar configurados para funcionar con tu sistema operativo y disponibles para su uso en todas las aplicaciones.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.