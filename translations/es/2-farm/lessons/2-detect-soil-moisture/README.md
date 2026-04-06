C, pronunciado como *I-cuadrado-C*, es un protocolo multi-controlador y multi-periférico, donde cualquier dispositivo conectado puede actuar como controlador o periférico comunicándose a través del bus I²C (el nombre para un sistema de comunicación que transfiere datos). Los datos se envían como paquetes dirigidos, y cada paquete contiene la dirección del dispositivo conectado al que está destinado.

> 💁 Este modelo solía denominarse maestro/esclavo, pero esta terminología está siendo eliminada debido a su asociación con la esclavitud. La [Open Source Hardware Association ha adoptado los términos controlador/periférico](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), aunque aún puedes encontrar referencias a la terminología anterior.

Los dispositivos tienen una dirección que se utiliza cuando se conectan al bus I²C, y generalmente está codificada en el dispositivo. Por ejemplo, cada tipo de sensor Grove de Seeed tiene la misma dirección, por lo que todos los sensores de luz tienen la misma dirección, todos los botones tienen la misma dirección, que es diferente de la dirección del sensor de luz. Algunos dispositivos permiten cambiar la dirección, modificando configuraciones de jumpers o soldando pines.

I²C tiene un bus compuesto por 2 cables principales, junto con 2 cables de alimentación:

| Cable | Nombre | Descripción |
| ---- | --------- | ----------- |
| SDA | Datos en serie | Este cable se utiliza para enviar datos entre dispositivos. |
| SCL | Reloj en serie | Este cable envía una señal de reloj a una velocidad establecida por el controlador. |
| VCC | Colector común de voltaje | La fuente de alimentación para los dispositivos. Este cable está conectado a los cables SDA y SCL para proporcionarles energía a través de una resistencia pull-up que apaga la señal cuando ningún dispositivo actúa como controlador. |
| GND | Tierra | Proporciona una tierra común para el circuito eléctrico. |

![Bus I2C con 3 dispositivos conectados a los cables SDA y SCL, compartiendo un cable de tierra común](../../../../../translated_images/es/i2c.83da845dde02256b.webp)

Para enviar datos, un dispositivo emitirá una condición de inicio para indicar que está listo para enviar datos. Luego se convertirá en el controlador. El controlador envía la dirección del dispositivo con el que desea comunicarse, junto con la indicación de si quiere leer o escribir datos. Después de que los datos han sido transmitidos, el controlador envía una condición de parada para indicar que ha terminado. Después de esto, otro dispositivo puede convertirse en el controlador y enviar o recibir datos.

2</sup>C tiene límites de velocidad, con 3 modos diferentes que funcionan a velocidades fijas. El más rápido es el modo de Alta Velocidad con una velocidad máxima de 3.4Mbps (megabits por segundo), aunque muy pocos dispositivos admiten esa velocidad. Por ejemplo, la Raspberry Pi está limitada al modo rápido a 400Kbps (kilobits por segundo). El modo estándar funciona a 100Kbps.

> 💁 Si estás utilizando una Raspberry Pi con un Grove Base hat como tu hardware IoT, podrás ver varios conectores I<sup>2</sup>C en la placa que puedes usar para comunicarte con sensores I<sup>2</sup>C. Los sensores analógicos Grove también utilizan I<sup>2</sup>C con un ADC para enviar valores analógicos como datos digitales, por lo que el sensor de luz que usaste simuló un pin analógico, con el valor enviado a través de I<sup>2</sup>C, ya que la Raspberry Pi solo admite pines digitales.

### Receptor-transmisor asíncrono universal (UART)

UART implica circuitos físicos que permiten que dos dispositivos se comuniquen. Cada dispositivo tiene 2 pines de comunicación: transmitir (Tx) y recibir (Rx), con el pin Tx del primer dispositivo conectado al pin Rx del segundo, y el pin Tx del segundo dispositivo conectado al pin Rx del primero. Esto permite que los datos se envíen en ambas direcciones.

* El dispositivo 1 transmite datos desde su pin Tx, que son recibidos por el dispositivo 2 en su pin Rx.
* El dispositivo 1 recibe datos en su pin Rx que son transmitidos por el dispositivo 2 desde su pin Tx.

![UART con el pin Tx de un chip conectado al pin Rx de otro, y viceversa](../../../../../translated_images/es/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Los datos se envían un bit a la vez, y esto se conoce como comunicación *serial*. La mayoría de los sistemas operativos y microcontroladores tienen *puertos seriales*, es decir, conexiones que pueden enviar y recibir datos seriales disponibles para tu código.

Los dispositivos UART tienen una [tasa de baudios](https://wikipedia.org/wiki/Symbol_rate) (también conocida como tasa de símbolos), que es la velocidad a la que los datos se enviarán y recibirán en bits por segundo. Una tasa de baudios común es 9,600, lo que significa que se envían 9,600 bits (0s y 1s) de datos cada segundo.

UART utiliza bits de inicio y parada: envía un bit de inicio para indicar que está a punto de enviar un byte (8 bits) de datos, y luego un bit de parada después de enviar los 8 bits.

La velocidad de UART depende del hardware, pero incluso las implementaciones más rápidas no superan los 6.5 Mbps (megabits por segundo, o millones de bits, 0 o 1, enviados por segundo).

Puedes usar UART sobre pines GPIO: puedes configurar un pin como Tx y otro como Rx, y luego conectarlos a otro dispositivo.

> 💁 Si estás utilizando una Raspberry Pi con un Grove Base hat como tu hardware IoT, podrás ver un conector UART en la placa que puedes usar para comunicarte con sensores que utilizan el protocolo UART.

### Interfaz Periférica Serial (SPI)

SPI está diseñado para comunicarse a corta distancia, como en un microcontrolador para interactuar con un dispositivo de almacenamiento como memoria flash. Se basa en un modelo de controlador/periférico con un único controlador (generalmente el procesador del dispositivo IoT) interactuando con múltiples periféricos. El controlador controla todo seleccionando un periférico y enviando o solicitando datos.

> 💁 Al igual que I<sup>2</sup>C, los términos controlador y periférico son cambios recientes, por lo que es posible que veas los términos más antiguos aún en uso.

Los controladores SPI utilizan 3 cables, junto con 1 cable adicional por periférico. Los periféricos utilizan 4 cables. Estos cables son:

| Cable | Nombre | Descripción |
| ---- | --------- | ----------- |
| COPI | Salida del controlador, entrada del periférico | Este cable es para enviar datos del controlador al periférico. |
| CIPO | Entrada del controlador, salida del periférico | Este cable es para enviar datos del periférico al controlador. |
| SCLK | Reloj serial | Este cable envía una señal de reloj a una velocidad establecida por el controlador. |
| CS   | Selección de chip | El controlador tiene múltiples cables, uno por periférico, y cada cable se conecta al cable CS en el periférico correspondiente. |

![SPI con un controlador y dos periféricos](../../../../../translated_images/es/spi.297431d6f98b386b.webp)

El cable CS se utiliza para activar un periférico a la vez, comunicándose a través de los cables COPI y CIPO. Cuando el controlador necesita cambiar de periférico, desactiva el cable CS conectado al periférico actualmente activo, y luego activa el cable conectado al periférico con el que desea comunicarse a continuación.

SPI es *full-duplex*, lo que significa que el controlador puede enviar y recibir datos al mismo tiempo desde el mismo periférico utilizando los cables COPI y CIPO. SPI utiliza una señal de reloj en el cable SCLK para mantener los dispositivos sincronizados, por lo que, a diferencia de enviar directamente a través de UART, no necesita bits de inicio y parada.

No hay límites de velocidad definidos para SPI, con implementaciones que a menudo pueden transmitir múltiples megabytes de datos por segundo.

Los kits de desarrollo IoT suelen admitir SPI en algunos de los pines GPIO. Por ejemplo, en una Raspberry Pi puedes usar los pines GPIO 19, 21, 23, 24 y 26 para SPI.

### Inalámbrico

Algunos sensores pueden comunicarse a través de protocolos inalámbricos estándar, como Bluetooth (principalmente Bluetooth Low Energy, o BLE), LoRaWAN (un protocolo de red de bajo consumo de **Lo**ng **Ra**nge), o WiFi. Estos permiten sensores remotos que no están físicamente conectados a un dispositivo IoT.

Un ejemplo de esto son los sensores comerciales de humedad del suelo. Estos medirán la humedad del suelo en un campo y luego enviarán los datos a través de LoRaWAN a un dispositivo concentrador, que procesará los datos o los enviará a través de Internet. Esto permite que el sensor esté lejos del dispositivo IoT que gestiona los datos, reduciendo el consumo de energía y la necesidad de grandes redes WiFi o cables largos.

BLE es popular para sensores avanzados como rastreadores de actividad física que funcionan en la muñeca. Estos combinan múltiples sensores y envían los datos del sensor a un dispositivo IoT en forma de tu teléfono a través de BLE.

✅ ¿Tienes algún sensor Bluetooth contigo, en tu casa o en tu escuela? Estos podrían incluir sensores de temperatura, sensores de ocupación, rastreadores de dispositivos y dispositivos de fitness.

Una forma popular para que los dispositivos comerciales se conecten es Zigbee. Zigbee utiliza WiFi para formar redes de malla entre dispositivos, donde cada dispositivo se conecta a tantos dispositivos cercanos como sea posible, formando una gran cantidad de conexiones como una telaraña. Cuando un dispositivo quiere enviar un mensaje a Internet, puede enviarlo a los dispositivos más cercanos, que luego lo reenvían a otros dispositivos cercanos y así sucesivamente, hasta que llega a un coordinador y puede enviarse a Internet.

> 🐝 El nombre Zigbee hace referencia al baile de meneo de las abejas melíferas después de regresar a la colmena.

## Medir los niveles de humedad en el suelo

Puedes medir el nivel de humedad en el suelo utilizando un sensor de humedad del suelo, un dispositivo IoT y una planta de interior o un parche de suelo cercano.

### Tarea - medir la humedad del suelo

Sigue la guía correspondiente para medir la humedad del suelo utilizando tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Computadora de placa única - Raspberry Pi](pi-soil-moisture.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-soil-moisture.md)

## Calibración de sensores

Los sensores dependen de medir propiedades eléctricas como la resistencia o la capacitancia.

> 🎓 La resistencia, medida en ohmios (Ω), es cuánta oposición hay a la corriente eléctrica que viaja a través de algo. Cuando se aplica un voltaje a un material, la cantidad de corriente que pasa a través de él depende de la resistencia del material. Puedes leer más en la [página de resistencia eléctrica en Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 La capacitancia, medida en faradios (F), es la capacidad de un componente o circuito para recolectar y almacenar energía eléctrica. Puedes leer más sobre capacitancia en la [página de capacitancia en Wikipedia](https://wikipedia.org/wiki/Capacitance).

Estas mediciones no siempre son útiles: imagina un sensor de temperatura que te diera una medición de 22.5KΩ. En cambio, el valor medido necesita convertirse en una unidad útil mediante la calibración, es decir, igualar los valores medidos con la cantidad medida para permitir que las nuevas mediciones se conviertan a la unidad correcta.

Algunos sensores vienen pre-calibrados. Por ejemplo, el sensor de temperatura que usaste en la última lección ya estaba calibrado para que pudiera devolver una medición de temperatura en °C. En la fábrica, el primer sensor creado se expondría a una gama de temperaturas conocidas y se mediría la resistencia. Esto luego se usaría para construir un cálculo que pueda convertir del valor medido en Ω (la unidad de resistencia) a °C.

> 💁 La fórmula para calcular la resistencia a partir de la temperatura se llama la [ecuación de Steinhart–Hart](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Calibración del sensor de humedad del suelo

La humedad del suelo se mide utilizando contenido de agua gravimétrico o volumétrico.

* Gravimétrico es el peso del agua en una unidad de peso de suelo medido, como el número de kilogramos de agua por kilogramo de suelo seco.
* Volumétrico es el volumen de agua en una unidad de volumen de suelo medido, como el número de metros cúbicos de agua por metros cúbicos de suelo seco.

> 🇺🇸 Para los estadounidenses, debido a la consistencia de las unidades, estos pueden medirse en libras en lugar de kilogramos o pies cúbicos en lugar de metros cúbicos.

Los sensores de humedad del suelo miden resistencia eléctrica o capacitancia: esto no solo varía según la humedad del suelo, sino también según el tipo de suelo, ya que los componentes en el suelo pueden cambiar sus características eléctricas. Idealmente, los sensores deben calibrarse, es decir, tomar lecturas del sensor y compararlas con mediciones obtenidas utilizando un enfoque más científico. Por ejemplo, un laboratorio puede calcular la humedad gravimétrica del suelo utilizando muestras de un campo específico tomadas unas pocas veces al año, y estos números se utilizan para calibrar el sensor, igualando la lectura del sensor con la humedad gravimétrica del suelo.

![Un gráfico de voltaje vs contenido de humedad del suelo](../../../../../translated_images/es/soil-moisture-to-voltage.df86d80cda158700.webp)

El gráfico anterior muestra cómo calibrar un sensor. El voltaje se captura para una muestra de suelo que luego se mide en un laboratorio comparando el peso húmedo con el peso seco (midiendo el peso húmedo, luego secándolo en un horno y midiendo el peso seco). Una vez que se han tomado algunas lecturas, esto puede graficarse y ajustarse una línea a los puntos. Esta línea luego puede usarse para convertir las lecturas del sensor de humedad del suelo tomadas por un dispositivo IoT en mediciones reales de humedad del suelo.

💁 Para los sensores de humedad del suelo resistivos, el voltaje aumenta a medida que aumenta la humedad del suelo. Para los sensores de humedad del suelo capacitivos, el voltaje disminuye a medida que aumenta la humedad del suelo, por lo que los gráficos para estos se inclinarían hacia abajo, no hacia arriba.

![Un valor de humedad del suelo interpolado desde el gráfico](../../../../../translated_images/es/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

El gráfico anterior muestra una lectura de voltaje de un sensor de humedad del suelo, y al seguir esa lectura hasta la línea en el gráfico, se puede calcular la humedad real del suelo.

Este enfoque significa que el agricultor solo necesita obtener algunas mediciones de laboratorio para un campo, luego puede usar dispositivos IoT para medir la humedad del suelo, acelerando drásticamente el tiempo para tomar mediciones.

---

## 🚀 Desafío

Los sensores de humedad del suelo resistivos y capacitivos tienen varias diferencias. ¿Cuáles son estas diferencias y cuál tipo (si alguno) es el mejor para que un agricultor lo use? ¿Cambia esta respuesta entre países en desarrollo y desarrollados?

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Revisión y autoestudio

Investiga sobre el hardware y los protocolos utilizados por sensores y actuadores:

* [Página de Wikipedia sobre GPIO](https://wikipedia.org/wiki/General-purpose_input/output)
* [Página de Wikipedia sobre UART](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [Página de Wikipedia sobre SPI](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [Página de Wikipedia sobre I<sup>2</sup>C](https://wikipedia.org/wiki/I²C)
* [Página de Wikipedia sobre Zigbee](https://wikipedia.org/wiki/Zigbee)

## Asignación

[Calibra tu sensor](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.