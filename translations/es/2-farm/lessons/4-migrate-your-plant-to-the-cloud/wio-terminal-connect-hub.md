<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-26T14:52:01+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "es"
}
-->
# Conecta tu dispositivo IoT a la nube - Wio Terminal

En esta parte de la lección, conectarás tu Wio Terminal a tu IoT Hub para enviar telemetría y recibir comandos.

## Conecta tu dispositivo a IoT Hub

El siguiente paso es conectar tu dispositivo a IoT Hub.

### Tarea - conectar a IoT Hub

1. Abre el proyecto `soil-moisture-sensor` en VS Code.

1. Abre el archivo `platformio.ini`. Elimina la dependencia de la biblioteca `knolleary/PubSubClient`. Esta se utilizaba para conectarse al broker MQTT público y no es necesaria para conectarse a IoT Hub.

1. Agrega las siguientes dependencias de biblioteca:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    La biblioteca `Seeed Arduino RTC` proporciona código para interactuar con un reloj en tiempo real en el Wio Terminal, utilizado para rastrear el tiempo. Las bibliotecas restantes permiten que tu dispositivo IoT se conecte a IoT Hub.

1. Agrega lo siguiente al final del archivo `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Esto establece una bandera del compilador que es necesaria al compilar el código de Arduino IoT Hub.

1. Abre el archivo de encabezado `config.h`. Elimina todas las configuraciones de MQTT y agrega la siguiente constante para la cadena de conexión del dispositivo:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Reemplaza `<connection string>` con la cadena de conexión de tu dispositivo que copiaste anteriormente.

1. La conexión a IoT Hub utiliza un token basado en tiempo. Esto significa que el dispositivo IoT necesita conocer la hora actual. A diferencia de sistemas operativos como Windows, macOS o Linux, los microcontroladores no sincronizan automáticamente la hora actual a través de Internet. Esto significa que deberás agregar código para obtener la hora actual de un servidor [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Una vez que se haya obtenido la hora, se puede almacenar en un reloj en tiempo real en el Wio Terminal, permitiendo solicitar la hora correcta en una fecha posterior, suponiendo que el dispositivo no pierda energía. Agrega un nuevo archivo llamado `ntp.h` con el siguiente código:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Los detalles de este código están fuera del alcance de esta lección. Define una función llamada `initTime` que obtiene la hora actual de un servidor NTP y la utiliza para configurar el reloj en el Wio Terminal.

1. Abre el archivo `main.cpp` y elimina todo el código de MQTT, incluyendo el archivo de encabezado `PubSubClient.h`, la declaración de la variable `PubSubClient`, los métodos `reconnectMQTTClient` y `createMQTTClient`, y cualquier llamada a estas variables y métodos. Este archivo solo debe contener código para conectarse a WiFi, obtener la humedad del suelo y crear un documento JSON con esta información.

1. Agrega las siguientes directivas `#include` al inicio del archivo `main.cpp` para incluir archivos de encabezado de las bibliotecas de IoT Hub y para configurar la hora:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Agrega la siguiente llamada al final de la función `setup` para configurar la hora actual:

    ```cpp
    initTime();
    ```

1. Agrega la siguiente declaración de variable al inicio del archivo, justo debajo de las directivas de inclusión:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Esto declara un `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, un identificador para una conexión a IoT Hub.

1. Debajo de esto, agrega el siguiente código:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Esto declara una función de callback que será llamada cuando la conexión a IoT Hub cambie de estado, como conectarse o desconectarse. El estado se envía al puerto serial.

1. Debajo de esto, agrega una función para conectarse a IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Este código inicializa el código de la biblioteca de IoT Hub y luego crea una conexión utilizando la cadena de conexión en el archivo de encabezado `config.h`. Esta conexión se basa en MQTT. Si la conexión falla, esto se envía al puerto serial; si ves esto en la salida, verifica la cadena de conexión. Finalmente, se configura el callback de estado de conexión.

1. Llama a esta función en la función `setup` debajo de la llamada a `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Al igual que con el cliente MQTT, este código se ejecuta en un solo hilo, por lo que necesita tiempo para procesar los mensajes enviados por el hub y enviados al hub. Agrega lo siguiente al inicio de la función `loop` para hacer esto:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Compila y sube este código. Verás la conexión en el monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    En la salida puedes ver que se obtiene la hora NTP, seguido de la conexión del cliente del dispositivo. Puede tardar unos segundos en conectarse, por lo que puedes ver la humedad del suelo en la salida mientras el dispositivo se conecta.

    > 💁 Puedes convertir el tiempo UNIX del NTP a una versión más legible utilizando un sitio web como [unixtimestamp.com](https://www.unixtimestamp.com)

## Enviar telemetría

Ahora que tu dispositivo está conectado, puedes enviar telemetría a IoT Hub en lugar del broker MQTT.

### Tarea - enviar telemetría

1. Agrega la siguiente función encima de la función `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Este código crea un mensaje de IoT Hub a partir de una cadena pasada como parámetro, lo envía al hub y luego limpia el objeto del mensaje.

1. Llama a este código en la función `loop`, justo después de la línea donde la telemetría se envía al puerto serial:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Manejar comandos

Tu dispositivo necesita manejar un comando del código del servidor para controlar el relé. Esto se envía como una solicitud de método directo.

## Tarea - manejar una solicitud de método directo

1. Agrega el siguiente código antes de la función `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Este código define un método de callback que la biblioteca de IoT Hub puede llamar cuando recibe una solicitud de método directo. El método solicitado se envía en el parámetro `method_name`. Esta función imprime el método llamado en el puerto serial y luego enciende o apaga el relé dependiendo del nombre del método.

    > 💁 Esto también podría implementarse en un único método directo, pasando el estado deseado del relé en un payload que puede ser pasado con la solicitud de método y disponible desde el parámetro `payload`.

1. Agrega el siguiente código al final de la función `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Las solicitudes de método directo necesitan una respuesta, y la respuesta tiene dos partes: una respuesta como texto y un código de retorno. Este código creará un resultado como el siguiente documento JSON:

    ```JSON
    {
        "Result": ""
    }
    ```

    Esto luego se copia en el parámetro `response`, y el tamaño de esta respuesta se establece en el parámetro `response_size`. Este código luego devuelve `IOTHUB_CLIENT_OK` para mostrar que el método fue manejado correctamente.

1. Conecta el callback agregando lo siguiente al final de la función `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. La función `loop` llamará a la función `IoTHubDeviceClient_LL_DoWork` para procesar eventos enviados por IoT Hub. Esto solo se llama cada 10 segundos debido al `delay`, lo que significa que los métodos directos solo se procesan cada 10 segundos. Para hacerlo más eficiente, el retraso de 10 segundos puede implementarse como muchos retrasos más cortos, llamando a `IoTHubDeviceClient_LL_DoWork` cada vez. Para hacer esto, agrega el siguiente código encima de la función `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Este código repetirá el bucle, llamando a `IoTHubDeviceClient_LL_DoWork` y retrasando 100ms cada vez. Hará esto tantas veces como sea necesario para retrasar la cantidad de tiempo dada en el parámetro `delay_time`. Esto significa que el dispositivo está esperando como máximo 100ms para procesar solicitudes de método directo.

1. En la función `loop`, elimina la llamada a `IoTHubDeviceClient_LL_DoWork` y reemplaza la llamada `delay(10000)` con lo siguiente para llamar a esta nueva función:

    ```cpp
    work_delay(10000);
    ```

> 💁 Puedes encontrar este código en la carpeta [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 ¡Tu programa de sensor de humedad del suelo está conectado a tu IoT Hub!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.