<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-26T15:30:12+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "es"
}
-->
# Configurar un temporizador - Wio Terminal

En esta parte de la lección, llamarás a tu código sin servidor para interpretar el habla y configurar un temporizador en tu Wio Terminal basado en los resultados.

## Configurar un temporizador

El texto que se obtiene de la llamada de conversión de voz a texto necesita ser enviado a tu código sin servidor para ser procesado por LUIS, devolviendo el número de segundos para el temporizador. Este número de segundos se puede usar para configurar un temporizador.

Los microcontroladores no tienen soporte nativo para múltiples hilos en Arduino, por lo que no existen clases estándar de temporizador como las que podrías encontrar al programar en Python u otros lenguajes de alto nivel. En su lugar, puedes usar bibliotecas de temporizador que funcionan midiendo el tiempo transcurrido en la función `loop` y llamando a funciones cuando el tiempo se agota.

### Tarea - enviar el texto a la función sin servidor

1. Abre el proyecto `smart-timer` en VS Code si aún no está abierto.

1. Abre el archivo de encabezado `config.h` y agrega la URL de tu aplicación de funciones:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Reemplaza `<URL>` con la URL de tu aplicación de funciones que obtuviste en el último paso de la lección anterior, apuntando a la dirección IP de tu máquina local que está ejecutando la aplicación de funciones.

1. Crea un nuevo archivo en la carpeta `src` llamado `language_understanding.h`. Este se usará para definir una clase que enviará el habla reconocida a tu aplicación de funciones para convertirla en segundos usando LUIS.

1. Agrega lo siguiente al inicio de este archivo:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Esto incluye algunos archivos de encabezado necesarios.

1. Define una clase llamada `LanguageUnderstanding` y declara una instancia de esta clase:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Para llamar a tu aplicación de funciones, necesitas declarar un cliente WiFi. Agrega lo siguiente a la sección `private` de la clase:

    ```cpp
    WiFiClient _client;
    ```

1. En la sección `public`, declara un método llamado `GetTimerDuration` para llamar a la aplicación de funciones:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. En el método `GetTimerDuration`, agrega el siguiente código para construir el JSON que se enviará a la aplicación de funciones:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Esto convierte el texto pasado al método `GetTimerDuration` en el siguiente JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    donde `<text>` es el texto pasado a la función.

1. Debajo de esto, agrega el siguiente código para realizar la llamada a la aplicación de funciones:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Esto realiza una solicitud POST a la aplicación de funciones, pasando el cuerpo JSON y obteniendo el código de respuesta.

1. Agrega el siguiente código debajo de esto:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Este código verifica el código de respuesta. Si es 200 (éxito), entonces el número de segundos para el temporizador se obtiene del cuerpo de la respuesta. De lo contrario, se envía un error al monitor serial y el número de segundos se establece en 0.

1. Agrega el siguiente código al final de este método para cerrar la conexión HTTP y devolver el número de segundos:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. En el archivo `main.cpp`, incluye este nuevo encabezado:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Al final de la función `processAudio`, llama al método `GetTimerDuration` para obtener la duración del temporizador:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Esto convierte el texto de la llamada a la clase `SpeechToText` en el número de segundos para el temporizador.

### Tarea - configurar un temporizador

El número de segundos se puede usar para configurar un temporizador.

1. Agrega la siguiente dependencia de biblioteca al archivo `platformio.ini` para agregar una biblioteca para configurar un temporizador:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Agrega una directiva de inclusión para esta biblioteca al archivo `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Sobre la función `processAudio`, agrega el siguiente código:

    ```cpp
    auto timer = timer_create_default();
    ```

    Este código declara un temporizador llamado `timer`.

1. Debajo de esto, agrega el siguiente código:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Esta función `say` eventualmente convertirá texto a voz, pero por ahora solo escribirá el texto pasado en el monitor serial.

1. Debajo de la función `say`, agrega el siguiente código:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Esta es una función de callback que se llamará cuando un temporizador expire. Se le pasa un mensaje para decir cuando el temporizador expire. Los temporizadores pueden repetirse, y esto se controla con el valor de retorno de este callback - este devuelve `false`, para indicar que el temporizador no debe ejecutarse nuevamente.

1. Agrega el siguiente código al final de la función `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Este código verifica el número total de segundos, y si es 0, retorna de la llamada a la función para que no se configuren temporizadores. Luego convierte el número total de segundos en minutos y segundos.

1. Debajo de este código, agrega lo siguiente para crear un mensaje que indique que el temporizador ha comenzado:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Debajo de esto, agrega un código similar para crear un mensaje que indique que el temporizador ha expirado:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Después de esto, di el mensaje de inicio del temporizador:

    ```cpp
    say(begin_message);
    ```

1. Al final de esta función, inicia el temporizador:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Esto activa el temporizador. El temporizador se configura usando milisegundos, por lo que el número total de segundos se multiplica por 1,000 para convertirlo a milisegundos. La función `timerExpired` se pasa como el callback, y el `end_message` se pasa como un argumento para pasar al callback. Este callback solo acepta argumentos `void *`, por lo que la cadena se convierte adecuadamente.

1. Finalmente, el temporizador necesita *tickear*, y esto se hace en la función `loop`. Agrega el siguiente código al final de la función `loop`:

    ```cpp
    timer.tick();
    ```

1. Compila este código, súbelo a tu Wio Terminal y pruébalo a través del monitor serial. Una vez que veas `Ready` en el monitor serial, presiona el botón C (el que está en el lado izquierdo, más cerca del interruptor de encendido) y habla. Se capturarán 4 segundos de audio, se convertirán a texto, luego se enviarán a tu aplicación de funciones y se configurará un temporizador. Asegúrate de que tu aplicación de funciones esté ejecutándose localmente.

    Verás cuándo comienza el temporizador y cuándo termina.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Puedes encontrar este código en la carpeta [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 ¡Tu programa de temporizador fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.