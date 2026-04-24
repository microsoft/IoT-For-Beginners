# Medir la humedad del suelo - Wio Terminal

En esta parte de la lección, agregarás un sensor capacitivo de humedad del suelo a tu Wio Terminal y leerás valores de él.

## Hardware

El Wio Terminal necesita un sensor capacitivo de humedad del suelo.

El sensor que usarás es un [Sensor Capacitivo de Humedad del Suelo](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), que mide la humedad del suelo detectando la capacitancia del mismo, una propiedad que cambia a medida que varía la humedad del suelo. A medida que aumenta la humedad del suelo, el voltaje disminuye.

Este es un sensor analógico, por lo que se conecta a los pines analógicos del Wio Terminal, utilizando un ADC integrado para generar un valor de 0 a 1,023.

### Conecta el sensor de humedad del suelo

El sensor de humedad del suelo Grove puede conectarse al puerto analógico/digital configurable del Wio Terminal.

#### Tarea - conectar el sensor de humedad del suelo

Conecta el sensor de humedad del suelo.

![Un sensor Grove de humedad del suelo](../../../../../translated_images/es/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Inserta un extremo de un cable Grove en el conector del sensor de humedad del suelo. Solo encajará de una manera.

1. Con el Wio Terminal desconectado de tu computadora u otra fuente de alimentación, conecta el otro extremo del cable Grove al conector Grove del lado derecho del Wio Terminal, mirando la pantalla. Este es el conector más alejado del botón de encendido.

![El sensor Grove de humedad del suelo conectado al conector derecho](../../../../../translated_images/es/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Inserta el sensor de humedad del suelo en la tierra. Tiene una 'línea de posición máxima' - una línea blanca a través del sensor. Inserta el sensor hasta esta línea, pero no más allá.

![El sensor Grove de humedad del suelo en la tierra](../../../../../translated_images/es/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Ahora puedes conectar el Wio Terminal a tu computadora.

## Programa el sensor de humedad del suelo

El Wio Terminal ahora puede ser programado para usar el sensor de humedad del suelo conectado.

### Tarea - programar el sensor de humedad del suelo

Programa el dispositivo.

1. Crea un nuevo proyecto de Wio Terminal usando PlatformIO. Llama a este proyecto `soil-moisture-sensor`. Agrega código en la función `setup` para configurar el puerto serial.

    > ⚠️ Puedes consultar [las instrucciones para crear un proyecto PlatformIO en el proyecto 1, lección 1 si es necesario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. No existe una biblioteca para este sensor, en su lugar puedes leer desde el pin analógico usando la función [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) incorporada de Arduino. Comienza configurando el pin analógico como entrada para que se puedan leer valores de él, agregando lo siguiente a la función `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Esto configura el pin `A0`, el pin combinado analógico/digital, como un pin de entrada desde el cual se puede leer voltaje.

1. Agrega lo siguiente a la función `loop` para leer el voltaje de este pin:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Debajo de este código, agrega el siguiente código para imprimir el valor en el puerto serial:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Finalmente, agrega un retraso al final de 10 segundos:

    ```cpp
    delay(10000);
    ```

1. Compila y sube el código al Wio Terminal.

    > ⚠️ Puedes consultar [las instrucciones para crear un proyecto PlatformIO en el proyecto 1, lección 1 si es necesario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Una vez subido, puedes monitorear la humedad del suelo usando el monitor serial. Agrega un poco de agua a la tierra o retira el sensor de la tierra y observa cómo cambia el valor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    En el ejemplo de salida anterior, puedes ver cómo el voltaje disminuye a medida que se agrega agua.

> 💁 Puedes encontrar este código en la carpeta [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 ¡Tu programa para el sensor de humedad del suelo fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.