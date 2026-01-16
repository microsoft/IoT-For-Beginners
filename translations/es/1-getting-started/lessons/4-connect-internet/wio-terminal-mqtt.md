<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-26T15:01:46+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "es"
}
-->
# Controla tu luz nocturna a través de Internet - Wio Terminal

El dispositivo IoT necesita ser programado para comunicarse con *test.mosquitto.org* utilizando MQTT, enviar valores de telemetría con la lectura del sensor de luz y recibir comandos para controlar el LED.

En esta parte de la lección, conectarás tu Wio Terminal a un broker MQTT.

## Instalar las bibliotecas de WiFi y MQTT para Arduino

Para comunicarte con el broker MQTT, necesitas instalar algunas bibliotecas de Arduino para usar el chip WiFi en el Wio Terminal y comunicarte con MQTT. Al desarrollar para dispositivos Arduino, puedes usar una amplia gama de bibliotecas que contienen código de código abierto e implementan una gran variedad de funcionalidades. Seeed publica bibliotecas para el Wio Terminal que le permiten comunicarse a través de WiFi. Otros desarrolladores han publicado bibliotecas para comunicarse con brokers MQTT, y usarás estas con tu dispositivo.

Estas bibliotecas se proporcionan como código fuente que puede ser importado automáticamente en PlatformIO y compilado para tu dispositivo. De esta manera, las bibliotecas de Arduino funcionarán en cualquier dispositivo que soporte el marco de Arduino, siempre que el dispositivo tenga el hardware específico necesario para esa biblioteca. Algunas bibliotecas, como las bibliotecas WiFi de Seeed, son específicas para ciertos hardware.

Las bibliotecas pueden instalarse globalmente y compilarse si es necesario, o dentro de un proyecto específico. Para esta tarea, las bibliotecas se instalarán en el proyecto.

✅ Puedes aprender más sobre la gestión de bibliotecas y cómo encontrar e instalar bibliotecas en la [documentación de bibliotecas de PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Tarea - instalar las bibliotecas de WiFi y MQTT para Arduino

Instala las bibliotecas de Arduino.

1. Abre el proyecto de luz nocturna en VS Code.

1. Agrega lo siguiente al final del archivo `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Esto importa las bibliotecas WiFi de Seeed. La sintaxis `@ <número>` se refiere a una versión específica de la biblioteca.

    > 💁 Puedes eliminar el `@ <número>` para usar siempre la última versión de las bibliotecas, pero no hay garantías de que las versiones posteriores funcionen con el código a continuación. El código aquí ha sido probado con esta versión de las bibliotecas.

    Esto es todo lo que necesitas hacer para agregar las bibliotecas. La próxima vez que PlatformIO compile el proyecto, descargará el código fuente de estas bibliotecas y lo compilará en tu proyecto.

1. Agrega lo siguiente a los `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Esto importa [PubSubClient](https://github.com/knolleary/pubsubclient), un cliente MQTT para Arduino.

## Conectar a WiFi

El Wio Terminal ahora puede conectarse a WiFi.

### Tarea - conectar a WiFi

Conecta el Wio Terminal a WiFi.

1. Crea un nuevo archivo en la carpeta `src` llamado `config.h`. Puedes hacerlo seleccionando la carpeta `src`, o el archivo `main.cpp` dentro, y seleccionando el botón **Nuevo archivo** desde el explorador. Este botón solo aparece cuando tu cursor está sobre el explorador.

    ![El botón de nuevo archivo](../../../../../translated_images/es/vscode-new-file-button.182702340fe6723c.webp)

1. Agrega el siguiente código a este archivo para definir constantes con tus credenciales de WiFi:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Reemplaza `<SSID>` con el SSID de tu WiFi. Reemplaza `<PASSWORD>` con tu contraseña de WiFi.

1. Abre el archivo `main.cpp`.

1. Agrega las siguientes directivas `#include` al inicio del archivo:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Esto incluye los archivos de encabezado de las bibliotecas que agregaste anteriormente, así como el archivo de encabezado de configuración. Estos archivos de encabezado son necesarios para indicarle a PlatformIO que traiga el código de las bibliotecas. Sin incluir explícitamente estos archivos de encabezado, parte del código no se compilará y obtendrás errores de compilación.

1. Agrega el siguiente código encima de la función `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Este código realiza un bucle mientras el dispositivo no está conectado a WiFi e intenta conectarse utilizando el SSID y la contraseña del archivo de encabezado de configuración.

1. Agrega una llamada a esta función al final de la función `setup`, después de que se hayan configurado los pines.

    ```cpp
    connectWiFi();
    ```

1. Sube este código a tu dispositivo para verificar que la conexión WiFi está funcionando. Deberías ver esto en el monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Conectar a MQTT

Una vez que el Wio Terminal esté conectado a WiFi, puede conectarse al broker MQTT.

### Tarea - conectar a MQTT

Conéctate al broker MQTT.

1. Agrega el siguiente código al final del archivo `config.h` para definir los detalles de conexión al broker MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Reemplaza `<ID>` con un ID único que se usará como el nombre del cliente de este dispositivo y más adelante para los temas que este dispositivo publique y suscriba. El broker *test.mosquitto.org* es público y es utilizado por muchas personas, incluidos otros estudiantes que están trabajando en esta tarea. Tener un nombre único para el cliente MQTT y los temas asegura que tu código no entre en conflicto con el de otros. También necesitarás este ID cuando crees el código del servidor más adelante en esta tarea.

    > 💁 Puedes usar un sitio web como [GUIDGen](https://www.guidgen.com) para generar un ID único.

    El `BROKER` es la URL del broker MQTT.

    El `CLIENT_NAME` es un nombre único para este cliente MQTT en el broker.

1. Abre el archivo `main.cpp` y agrega el siguiente código debajo de la función `connectWiFi` y encima de la función `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Este código crea un cliente WiFi utilizando las bibliotecas WiFi del Wio Terminal y lo usa para crear un cliente MQTT.

1. Debajo de este código, agrega lo siguiente:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Esta función prueba la conexión al broker MQTT y se reconecta si no está conectado. Realiza un bucle todo el tiempo que no está conectado e intenta conectarse utilizando el nombre único del cliente definido en el archivo de encabezado de configuración.

    Si la conexión falla, vuelve a intentarlo después de 5 segundos.

1. Agrega el siguiente código debajo de la función `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Este código configura el broker MQTT para el cliente, así como la función de callback cuando se recibe un mensaje. Luego intenta conectarse al broker.

1. Llama a la función `createMQTTClient` en la función `setup` después de que se haya conectado a WiFi.

1. Reemplaza toda la función `loop` con lo siguiente:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Este código comienza reconectándose al broker MQTT. Estas conexiones pueden romperse fácilmente, por lo que vale la pena verificar regularmente y reconectar si es necesario. Luego llama al método `loop` en el cliente MQTT para procesar cualquier mensaje que esté llegando en el tema suscrito. Esta aplicación es de un solo hilo, por lo que los mensajes no pueden recibirse en un hilo de fondo; por lo tanto, se necesita tiempo en el hilo principal para procesar cualquier mensaje que esté esperando en la conexión de red.

    Finalmente, un retraso de 2 segundos asegura que los niveles de luz no se envíen con demasiada frecuencia y reduce el consumo de energía del dispositivo.

1. Sube el código a tu Wio Terminal y usa el Monitor Serial para ver el dispositivo conectándose a WiFi y MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Puedes encontrar este código en la carpeta [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Has conectado exitosamente tu dispositivo a un broker MQTT.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.