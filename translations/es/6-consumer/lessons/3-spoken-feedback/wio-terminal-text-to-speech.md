<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-26T15:32:01+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "es"
}
-->
# Texto a voz - Wio Terminal

En esta parte de la lección, convertirás texto a voz para proporcionar retroalimentación hablada.

## Texto a voz

El SDK de servicios de voz que utilizaste en la lección anterior para convertir voz a texto también puede usarse para convertir texto a voz.

## Obtener una lista de voces

Al solicitar voz, necesitas proporcionar la voz que se usará, ya que se puede generar utilizando una variedad de voces diferentes. Cada idioma admite un rango de voces distintas, y puedes obtener la lista de voces compatibles para cada idioma desde el SDK de servicios de voz. Aquí es donde entran en juego las limitaciones de los microcontroladores: la llamada para obtener la lista de voces compatibles con los servicios de texto a voz es un documento JSON de más de 77 KB, demasiado grande para ser procesado por el Wio Terminal. Al momento de escribir esto, la lista completa contiene 215 voces, cada una definida por un documento JSON como el siguiente:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Este JSON corresponde a la voz **Aria**, que tiene múltiples estilos de voz. Todo lo que se necesita al convertir texto a voz es el nombre corto, `en-US-AriaNeural`.

En lugar de descargar y decodificar esta lista completa en tu microcontrolador, necesitarás escribir algo de código sin servidor para recuperar la lista de voces para el idioma que estás utilizando y llamarlo desde tu Wio Terminal. Tu código puede entonces elegir una voz adecuada de la lista, como la primera que encuentre.

### Tarea - crear una función sin servidor para obtener una lista de voces

1. Abre tu proyecto `smart-timer-trigger` en VS Code y abre el terminal asegurándote de que el entorno virtual esté activado. Si no, cierra y vuelve a crear el terminal.

1. Abre el archivo `local.settings.json` y agrega configuraciones para la clave de la API de voz y la ubicación:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Sustituye `<key>` por la clave de la API de tu recurso de servicio de voz. Sustituye `<location>` por la ubicación que usaste al crear el recurso de servicio de voz.

1. Agrega un nuevo disparador HTTP a esta aplicación llamado `get-voices` utilizando el siguiente comando desde el terminal de VS Code en la carpeta raíz del proyecto de la aplicación de funciones:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Esto creará un disparador HTTP llamado `get-voices`.

1. Sustituye el contenido del archivo `__init__.py` en la carpeta `get-voices` con lo siguiente:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Este código realiza una solicitud HTTP al endpoint para obtener las voces. Esta lista de voces es un gran bloque de JSON con voces para todos los idiomas, por lo que se filtran las voces para el idioma pasado en el cuerpo de la solicitud, luego se extrae el nombre corto y se devuelve como una lista JSON. El nombre corto es el valor necesario para convertir texto a voz, por lo que solo se devuelve este valor.

    > 💁 Puedes cambiar el filtro según sea necesario para seleccionar solo las voces que desees.

    Esto reduce el tamaño de los datos de 77 KB (al momento de escribir esto) a un documento JSON mucho más pequeño. Por ejemplo, para voces en inglés de EE. UU., esto es 408 bytes.

1. Ejecuta tu aplicación de funciones localmente. Luego puedes llamarla usando una herramienta como curl de la misma manera que probaste tu disparador HTTP `text-to-timer`. Asegúrate de pasar tu idioma como un cuerpo JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Sustituye `<language>` por tu idioma, como `en-GB` o `zh-CN`.

> 💁 Puedes encontrar este código en la carpeta [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tarea - recuperar la voz desde tu Wio Terminal

1. Abre el proyecto `smart-timer` en VS Code si aún no está abierto.

1. Abre el archivo de encabezado `config.h` y agrega la URL de tu aplicación de funciones:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Sustituye `<URL>` por la URL del disparador HTTP `get-voices` en tu aplicación de funciones. Esto será igual al valor de `TEXT_TO_TIMER_FUNCTION_URL`, excepto que el nombre de la función será `get-voices` en lugar de `text-to-timer`.

1. Crea un nuevo archivo en la carpeta `src` llamado `text_to_speech.h`. Este se usará para definir una clase que convierta de texto a voz.

1. Agrega las siguientes directivas de inclusión en la parte superior del nuevo archivo `text_to_speech.h`:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Agrega el siguiente código debajo para declarar la clase `TextToSpeech`, junto con una instancia que pueda usarse en el resto de la aplicación:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Para llamar a tu aplicación de funciones, necesitas declarar un cliente WiFi. Agrega lo siguiente a la sección `private` de la clase:

    ```cpp
    WiFiClient _client;
    ```

1. En la sección `private`, agrega un campo para la voz seleccionada:

    ```cpp
    String _voice;
    ```

1. En la sección `public`, agrega una función `init` que obtendrá la primera voz:

    ```cpp
    void init()
    {
    }
    ```

1. Para obtener las voces, se necesita enviar un documento JSON a la aplicación de funciones con el idioma. Agrega el siguiente código a la función `init` para crear este documento JSON:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Luego, crea un `HTTPClient` y úsalo para llamar a la aplicación de funciones para obtener las voces, enviando el documento JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Debajo de esto, agrega código para verificar el código de respuesta, y si es 200 (éxito), extrae la lista de voces, recuperando la primera de la lista:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Después de esto, finaliza la conexión del cliente HTTP:

    ```cpp
    httpClient.end();
    ```

1. Abre el archivo `main.cpp` y agrega la siguiente directiva de inclusión en la parte superior para incluir este nuevo archivo de encabezado:

    ```cpp
    #include "text_to_speech.h"
    ```

1. En la función `setup`, debajo de la llamada a `speechToText.init();`, agrega lo siguiente para inicializar la clase `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Compila este código, súbelo a tu Wio Terminal y pruébalo a través del monitor serial. Asegúrate de que tu aplicación de funciones esté en ejecución.

    Verás la lista de voces disponibles devuelta por la aplicación de funciones, junto con la voz seleccionada.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Convertir texto a voz

Una vez que tengas una voz para usar, esta puede usarse para convertir texto a voz. Las mismas limitaciones de memoria con las voces también se aplican al convertir texto a voz, por lo que necesitarás escribir el audio en una tarjeta SD para que pueda reproducirse a través del ReSpeaker.

> 💁 En lecciones anteriores de este proyecto usaste memoria flash para almacenar el audio capturado desde el micrófono. Esta lección utiliza una tarjeta SD ya que es más fácil reproducir audio desde ella utilizando las bibliotecas de audio de Seeed.

También hay otra limitación a considerar: los datos de audio disponibles desde el servicio de voz y los formatos que admite el Wio Terminal. A diferencia de las computadoras completas, las bibliotecas de audio para microcontroladores pueden ser muy limitadas en los formatos de audio que admiten. Por ejemplo, la biblioteca Seeed Arduino Audio que puede reproducir sonido a través del ReSpeaker solo admite audio con una frecuencia de muestreo de 44.1 kHz. Los servicios de voz de Azure pueden proporcionar audio en varios formatos, pero ninguno de ellos utiliza esta frecuencia de muestreo; solo proporcionan 8 kHz, 16 kHz, 24 kHz y 48 kHz. Esto significa que el audio necesita ser remuestreado a 44.1 kHz, algo que requeriría más recursos de los que tiene el Wio Terminal, especialmente memoria.

Cuando se necesita manipular datos como este, a menudo es mejor usar código sin servidor, especialmente si los datos se obtienen a través de una llamada web. El Wio Terminal puede llamar a una función sin servidor, pasarle el texto a convertir, y la función sin servidor puede tanto llamar al servicio de voz para convertir texto a voz como remuestrear el audio a la frecuencia de muestreo requerida. Luego puede devolver el audio en el formato que el Wio Terminal necesita para almacenarlo en la tarjeta SD y reproducirlo a través del ReSpeaker.

### Tarea - crear una función sin servidor para convertir texto a voz

1. Abre tu proyecto `smart-timer-trigger` en VS Code y abre el terminal asegurándote de que el entorno virtual esté activado. Si no, cierra y vuelve a crear el terminal.

1. Agrega un nuevo disparador HTTP a esta aplicación llamado `text-to-speech` utilizando el siguiente comando desde el terminal de VS Code en la carpeta raíz del proyecto de la aplicación de funciones:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Esto creará un disparador HTTP llamado `text-to-speech`.

1. El paquete Pip [librosa](https://librosa.org) tiene funciones para remuestrear audio, así que agrégalo al archivo `requirements.txt`:

    ```sh
    librosa
    ```

    Una vez agregado, instala los paquetes Pip utilizando el siguiente comando desde el terminal de VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Si estás utilizando Linux, incluido Raspberry Pi OS, es posible que necesites instalar `libsndfile` con el siguiente comando:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Para convertir texto a voz, no puedes usar directamente la clave de la API de voz; en su lugar, necesitas solicitar un token de acceso, utilizando la clave de la API para autenticar la solicitud del token de acceso. Abre el archivo `__init__.py` de la carpeta `text-to-speech` y reemplaza todo el código con lo siguiente:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Esto define constantes para la ubicación y la clave de voz que se leerán desde la configuración. Luego define la función `get_access_token` que recuperará un token de acceso para el servicio de voz.

1. Debajo de este código, agrega lo siguiente:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Esto define el disparador HTTP que convierte el texto a voz. Extrae el texto a convertir, el idioma y la voz del cuerpo JSON enviado en la solicitud, construye un SSML para solicitar la voz, luego llama a la API REST correspondiente autenticándose con el token de acceso. Esta llamada a la API REST devuelve el audio codificado como un archivo WAV mono de 16 bits y 48 kHz, definido por el valor de `playback_format`, que se envía en la llamada a la API REST.

    Luego, este audio es remuestreado por `librosa` de una frecuencia de muestreo de 48 kHz a una frecuencia de muestreo de 44.1 kHz, y este audio se guarda en un búfer binario que luego se devuelve.

1. Ejecuta tu aplicación de funciones localmente o despliega en la nube. Luego puedes llamarla usando una herramienta como curl de la misma manera que probaste tu disparador HTTP `text-to-timer`. Asegúrate de pasar el idioma, la voz y el texto como cuerpo JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Sustituye `<language>` por tu idioma, como `en-GB` o `zh-CN`. Sustituye `<voice>` por la voz que deseas usar. Sustituye `<text>` por el texto que deseas convertir a voz. Puedes guardar la salida en un archivo y reproducirlo con cualquier reproductor de audio que pueda reproducir archivos WAV.

    Por ejemplo, para convertir "Hello" a voz usando inglés de EE. UU. con la voz Jenny Neural, con la aplicación de funciones ejecutándose localmente, puedes usar el siguiente comando curl:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Esto guardará el audio en `hello.wav` en el directorio actual.

> 💁 Puedes encontrar este código en la carpeta [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tarea - recuperar el audio desde tu Wio Terminal

1. Abre el proyecto `smart-timer` en VS Code si aún no está abierto.

1. Abre el archivo de encabezado `config.h` y agrega la URL de tu aplicación de funciones:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Sustituye `<URL>` por la URL del disparador HTTP `text-to-speech` en tu aplicación de funciones. Esto será igual al valor de `TEXT_TO_TIMER_FUNCTION_URL`, excepto que el nombre de la función será `text-to-speech` en lugar de `text-to-timer`.

1. Abre el archivo de encabezado `text_to_speech.h` y agrega el siguiente método a la sección `public` de la clase `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. En el método `convertTextToSpeech`, agrega el siguiente código para crear el JSON que se enviará a la aplicación de funciones:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Esto escribe el idioma, la voz y el texto en el documento JSON, luego lo serializa a una cadena.

1. Debajo de esto, agrega el siguiente código para llamar a la aplicación de funciones:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Esto crea un `HTTPClient`, luego realiza una solicitud POST utilizando el documento JSON al disparador HTTP de texto a voz.

1. Si la llamada funciona, los datos binarios crudos devueltos por la llamada a la aplicación de funciones pueden transmitirse a un archivo en la tarjeta SD. Agrega el siguiente código para hacer esto:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Este código verifica la respuesta, y si es 200 (éxito), los datos binarios se transmiten a un archivo en la raíz de la tarjeta SD llamado `SPEECH.WAV`.

1. Al final de este método, cierra la conexión HTTP:

    ```cpp
    httpClient.end();
    ```

1. Ahora se puede convertir el texto a audio. En el archivo `main.cpp`, agrega la siguiente línea al final de la función `say` para convertir el texto a decir en audio:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Tarea - reproducir audio desde tu Wio Terminal

**Próximamente**

## Implementar tu aplicación de funciones en la nube

La razón para ejecutar la aplicación de funciones localmente es porque el paquete Pip `librosa` en Linux tiene una dependencia de una biblioteca que no está instalada por defecto y necesitará ser instalada antes de que la aplicación de funciones pueda ejecutarse. Las aplicaciones de funciones son sin servidor: no hay servidores que puedas gestionar tú mismo, por lo que no hay forma de instalar esta biblioteca de antemano.

La manera de hacerlo es implementar tu aplicación de funciones utilizando un contenedor Docker. Este contenedor es desplegado por la nube cada vez que necesita iniciar una nueva instancia de tu aplicación de funciones (como cuando la demanda supera los recursos disponibles, o si la aplicación de funciones no se ha utilizado durante un tiempo y se ha cerrado).

Puedes encontrar las instrucciones para configurar una aplicación de funciones e implementarla mediante Docker en la [documentación de Microsoft Docs sobre cómo crear una función en Linux usando un contenedor personalizado](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Una vez que esto se haya implementado, puedes adaptar tu código de Wio Terminal para acceder a esta función:

1. Agrega el certificado de Azure Functions a `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIFWjCCBEKgAwIBAgIQDxSWXyAgaZlP1ceseIlB4jANBgkqhkiG9w0BAQsFADBa\r\n"
        "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n"
        "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\r\n"
        "MDcyMTIzMDAwMFoXDTI0MTAwODA3MDAwMFowTzELMAkGA1UEBhMCVVMxHjAcBgNV\r\n"
        "BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEgMB4GA1UEAxMXTWljcm9zb2Z0IFJT\r\n"
        "QSBUTFMgQ0EgMDEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCqYnfP\r\n"
        "mmOyBoTzkDb0mfMUUavqlQo7Rgb9EUEf/lsGWMk4bgj8T0RIzTqk970eouKVuL5R\r\n"
        "IMW/snBjXXgMQ8ApzWRJCZbar879BV8rKpHoAW4uGJssnNABf2n17j9TiFy6BWy+\r\n"
        "IhVnFILyLNK+W2M3zK9gheiWa2uACKhuvgCca5Vw/OQYErEdG7LBEzFnMzTmJcli\r\n"
        "W1iCdXby/vI/OxbfqkKD4zJtm45DJvC9Dh+hpzqvLMiK5uo/+aXSJY+SqhoIEpz+\r\n"
        "rErHw+uAlKuHFtEjSeeku8eR3+Z5ND9BSqc6JtLqb0bjOHPm5dSRrgt4nnil75bj\r\n"
        "c9j3lWXpBb9PXP9Sp/nPCK+nTQmZwHGjUnqlO9ebAVQD47ZisFonnDAmjrZNVqEX\r\n"
        "F3p7laEHrFMxttYuD81BdOzxAbL9Rb/8MeFGQjE2Qx65qgVfhH+RsYuuD9dUw/3w\r\n"
        "ZAhq05yO6nk07AM9c+AbNtRoEcdZcLCHfMDcbkXKNs5DJncCqXAN6LhXVERCw/us\r\n"
        "G2MmCMLSIx9/kwt8bwhUmitOXc6fpT7SmFvRAtvxg84wUkg4Y/Gx++0j0z6StSeN\r\n"
        "0EJz150jaHG6WV4HUqaWTb98Tm90IgXAU4AW2GBOlzFPiU5IY9jt+eXC2Q6yC/Zp\r\n"
        "TL1LAcnL3Qa/OgLrHN0wiw1KFGD51WRPQ0Sh7QIDAQABo4IBJTCCASEwHQYDVR0O\r\n"
        "BBYEFLV2DDARzseSQk1Mx1wsyKkM6AtkMB8GA1UdIwQYMBaAFOWdWTCCR1jMrPoI\r\n"
        "VDaGezq1BE3wMA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYI\r\n"
        "KwYBBQUHAwIwEgYDVR0TAQH/BAgwBgEB/wIBADA0BggrBgEFBQcBAQQoMCYwJAYI\r\n"
        "KwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTA6BgNVHR8EMzAxMC+g\r\n"
        "LaArhilodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vT21uaXJvb3QyMDI1LmNybDAq\r\n"
        "BgNVHSAEIzAhMAgGBmeBDAECATAIBgZngQwBAgIwCwYJKwYBBAGCNyoBMA0GCSqG\r\n"
        "SIb3DQEBCwUAA4IBAQCfK76SZ1vae4qt6P+dTQUO7bYNFUHR5hXcA2D59CJWnEj5\r\n"
        "na7aKzyowKvQupW4yMH9fGNxtsh6iJswRqOOfZYC4/giBO/gNsBvwr8uDW7t1nYo\r\n"
        "DYGHPpvnpxCM2mYfQFHq576/TmeYu1RZY29C4w8xYBlkAA8mDJfRhMCmehk7cN5F\r\n"
        "JtyWRj2cZj/hOoI45TYDBChXpOlLZKIYiG1giY16vhCRi6zmPzEwv+tk156N6cGS\r\n"
        "Vm44jTQ/rs1sa0JSYjzUaYngoFdZC4OfxnIkQvUIA4TOFmPzNPEFdjcZsgbeEz4T\r\n"
        "cGHTBPK4R28F44qIMCtHRV55VMX53ev6P3hRddJb\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Cambia todas las inclusiones de `<WiFiClient.h>` a `<WiFiClientSecure.h>`.

1. Cambia todos los campos `WiFiClient` a `WiFiClientSecure`.

1. En cada clase que tenga un campo `WiFiClientSecure`, agrega un constructor y establece el certificado en ese constructor:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.