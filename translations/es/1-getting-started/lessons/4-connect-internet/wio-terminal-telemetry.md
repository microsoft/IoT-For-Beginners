<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-26T15:00:11+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "es"
}
-->
# Controla tu luz nocturna a través de Internet - Wio Terminal

En esta parte de la lección, enviarás telemetría con los niveles de luz desde tu Wio Terminal al broker MQTT.

## Instalar las bibliotecas JSON para Arduino

Una forma popular de enviar mensajes a través de MQTT es utilizando JSON. Existe una biblioteca de Arduino para JSON que facilita la lectura y escritura de documentos JSON.

### Tarea

Instala la biblioteca Arduino JSON.

1. Abre el proyecto de la luz nocturna en VS Code.

1. Agrega la siguiente línea adicional a la lista `lib_deps` en el archivo `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Esto importa [ArduinoJson](https://arduinojson.org), una biblioteca JSON para Arduino.

## Publicar telemetría

El siguiente paso es crear un documento JSON con la telemetría y enviarlo al broker MQTT.

### Tarea - publicar telemetría

Publica telemetría en el broker MQTT.

1. Agrega el siguiente código al final del archivo `config.h` para definir el nombre del tema de telemetría para el broker MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    El `CLIENT_TELEMETRY_TOPIC` es el tema al que el dispositivo publicará los niveles de luz.

1. Abre el archivo `main.cpp`.

1. Agrega la siguiente directiva `#include` al principio del archivo:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Agrega el siguiente código dentro de la función `loop`, justo antes del `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Este código lee el nivel de luz y crea un documento JSON utilizando ArduinoJson que contiene este nivel. Luego, se serializa a una cadena y se publica en el tema de telemetría MQTT mediante el cliente MQTT.

1. Sube el código a tu Wio Terminal y utiliza el Monitor Serial para ver los niveles de luz que se envían al broker MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Puedes encontrar este código en la carpeta [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Has enviado telemetría desde tu dispositivo con éxito.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.