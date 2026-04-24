# Medir la temperatura - Wio Terminal

En esta parte de la lección, agregarás un sensor de temperatura a tu Wio Terminal y leerás los valores de temperatura desde él.

## Hardware

El Wio Terminal necesita un sensor de temperatura.

El sensor que usarás es un [sensor de humedad y temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), que combina 2 sensores en un solo paquete. Este es bastante popular, con varios sensores disponibles comercialmente que combinan temperatura, humedad y, a veces, presión atmosférica. El componente del sensor de temperatura es un termistor de coeficiente de temperatura negativo (NTC), un termistor cuya resistencia disminuye a medida que aumenta la temperatura.

Este es un sensor digital, por lo que tiene un ADC integrado para crear una señal digital que contiene los datos de temperatura y humedad que el microcontrolador puede leer.

### Conectar el sensor de temperatura

El sensor de temperatura Grove se puede conectar al puerto digital del Wio Terminal.

#### Tarea - conectar el sensor de temperatura

Conecta el sensor de temperatura.

![Un sensor de temperatura Grove](../../../../../translated_images/es/grove-dht11.07f8eafceee17004.webp)

1. Inserta un extremo de un cable Grove en el conector del sensor de humedad y temperatura. Solo encajará de una manera.

1. Con el Wio Terminal desconectado de tu computadora u otra fuente de alimentación, conecta el otro extremo del cable Grove al conector Grove del lado derecho del Wio Terminal, mirando la pantalla. Este es el conector más alejado del botón de encendido.

![El sensor de temperatura Grove conectado al conector derecho](../../../../../translated_images/es/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programar el sensor de temperatura

Ahora se puede programar el Wio Terminal para usar el sensor de temperatura conectado.

### Tarea - programar el sensor de temperatura

Programa el dispositivo.

1. Crea un nuevo proyecto de Wio Terminal usando PlatformIO. Llama a este proyecto `temperature-sensor`. Agrega código en la función `setup` para configurar el puerto serial.

    > ⚠️ Puedes consultar [las instrucciones para crear un proyecto PlatformIO en el proyecto 1, lección 1 si es necesario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Agrega una dependencia de biblioteca para la biblioteca Seeed Grove Humidity and Temperature sensor al archivo `platformio.ini` del proyecto:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Puedes consultar [las instrucciones para agregar bibliotecas a un proyecto PlatformIO en el proyecto 1, lección 4 si es necesario](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Agrega las siguientes directivas `#include` al principio del archivo, debajo del existente `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Esto importa los archivos necesarios para interactuar con el sensor. El archivo de encabezado `DHT.h` contiene el código para el sensor en sí, y agregar el encabezado `SPI.h` asegura que el código necesario para comunicarse con el sensor se vincule cuando se compile la aplicación.

1. Antes de la función `setup`, declara el sensor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Esto declara una instancia de la clase `DHT` que gestiona el sensor de **H**umedad y **T**emperatura **D**igital. Este está conectado al puerto `D0`, el conector Grove del lado derecho del Wio Terminal. El segundo parámetro indica que el sensor que se está utilizando es el sensor *DHT11*; la biblioteca que estás usando admite otras variantes de este sensor.

1. En la función `setup`, agrega código para configurar la conexión serial:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Al final de la función `setup`, después del último `delay`, agrega una llamada para iniciar el sensor DHT:

    ```cpp
    dht.begin();
    ```

1. En la función `loop`, agrega código para llamar al sensor e imprimir la temperatura en el puerto serial:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Este código declara un arreglo vacío de 2 flotantes y lo pasa a la llamada a `readTempAndHumidity` en la instancia `DHT`. Esta llamada llena el arreglo con 2 valores: la humedad se coloca en el elemento 0 del arreglo (recuerda que en C++ los arreglos son basados en 0, por lo que el elemento 0 es el 'primero' en el arreglo), y la temperatura se coloca en el elemento 1.

    La temperatura se lee del elemento 1 del arreglo y se imprime en el puerto serial.

    > 🇺🇸 La temperatura se lee en Celsius. Para los estadounidenses, para convertir esto a Fahrenheit, divide el valor en Celsius leído entre 5, luego multiplícalo por 9 y luego suma 32. Por ejemplo, una lectura de temperatura de 20°C se convierte en ((20/5)*9) + 32 = 68°F.

1. Compila y sube el código al Wio Terminal.

    > ⚠️ Puedes consultar [las instrucciones para crear un proyecto PlatformIO en el proyecto 1, lección 1 si es necesario](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Una vez subido, puedes monitorear la temperatura usando el monitor serial:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Puedes encontrar este código en la carpeta [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 ¡Tu programa del sensor de temperatura fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.