<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-26T15:08:37+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "es"
}
-->
# Agregar un sensor - Wio Terminal

En esta parte de la lección, usarás el sensor de luz en tu Wio Terminal.

## Hardware

El sensor para esta lección es un **sensor de luz** que utiliza un [fotodiodo](https://wikipedia.org/wiki/Photodiode) para convertir la luz en una señal eléctrica. Este es un sensor analógico que envía un valor entero de 0 a 1,023 indicando una cantidad relativa de luz que no se corresponde con ninguna unidad estándar de medida como [lux](https://wikipedia.org/wiki/Lux).

El sensor de luz está integrado en el Wio Terminal y es visible a través de la ventana de plástico transparente en la parte trasera.

![El sensor de luz en la parte trasera del Wio Terminal](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.es.png)

## Programar el sensor de luz

Ahora se puede programar el dispositivo para usar el sensor de luz integrado.

### Tarea

Programa el dispositivo.

1. Abre el proyecto de luz nocturna en VS Code que creaste en la parte anterior de esta tarea.

1. Agrega la siguiente línea al final de la función `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Esta línea configura los pines utilizados para comunicarse con el hardware del sensor.

    El pin `WIO_LIGHT` es el número del pin GPIO conectado al sensor de luz integrado. Este pin se configura como `INPUT`, lo que significa que se conecta a un sensor y se leerán datos desde el pin.

1. Elimina el contenido de la función `loop`.

1. Agrega el siguiente código a la función `loop`, que ahora está vacía.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Este código lee un valor analógico del pin `WIO_LIGHT`. Esto lee un valor de 0-1,023 del sensor de luz integrado. Este valor luego se envía al puerto serial para que puedas leerlo en el Monitor Serial cuando este código esté en ejecución. `Serial.print` escribe el texto sin un salto de línea al final, por lo que cada línea comenzará con `Light value:` y terminará con el valor real de luz.

1. Agrega un pequeño retraso de un segundo (1,000ms) al final del `loop`, ya que no es necesario verificar los niveles de luz de manera continua. Un retraso reduce el consumo de energía del dispositivo.

    ```cpp
    delay(1000);
    ```

1. Reconecta el Wio Terminal a tu computadora y sube el nuevo código como lo hiciste antes.

1. Conecta el Monitor Serial. Los valores de luz se mostrarán en el terminal. Cubre y descubre el sensor de luz en la parte trasera del Wio Terminal, y los valores cambiarán.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Puedes encontrar este código en la carpeta [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 ¡Agregar un sensor a tu programa de luz nocturna fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.