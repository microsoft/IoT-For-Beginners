<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-26T15:20:39+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "es"
}
-->
# Traducir discurso - Wio Terminal

En esta parte de la lección, escribirás código para traducir texto utilizando el servicio de traducción.

## Convertir texto a discurso utilizando el servicio de traducción

La API REST del servicio de discurso no admite traducciones directas. En su lugar, puedes usar el servicio de Traducción para traducir el texto generado por el servicio de discurso a texto y el texto de la respuesta hablada. Este servicio tiene una API REST que puedes usar para traducir el texto, pero para facilitar su uso, se envolverá en otro disparador HTTP en tu aplicación de funciones.

### Tarea - crear una función sin servidor para traducir texto

1. Abre tu proyecto `smart-timer-trigger` en VS Code y abre la terminal asegurándote de que el entorno virtual esté activado. Si no lo está, cierra y vuelve a crear la terminal.

1. Abre el archivo `local.settings.json` y agrega configuraciones para la clave de API del traductor y la ubicación:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Sustituye `<key>` con la clave de API de tu recurso del servicio de traducción. Sustituye `<location>` con la ubicación que usaste al crear el recurso del servicio de traducción.

1. Agrega un nuevo disparador HTTP a esta aplicación llamado `translate-text` utilizando el siguiente comando desde la terminal de VS Code en la carpeta raíz del proyecto de la aplicación de funciones:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Esto creará un disparador HTTP llamado `translate-text`.

1. Sustituye el contenido del archivo `__init__.py` en la carpeta `translate-text` con lo siguiente:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Este código extrae el texto y los idiomas de la solicitud HTTP. Luego realiza una solicitud a la API REST del traductor, pasando los idiomas como parámetros para la URL y el texto a traducir como el cuerpo. Finalmente, se devuelve la traducción.

1. Ejecuta tu aplicación de funciones localmente. Luego puedes llamarla utilizando una herramienta como curl de la misma manera que probaste tu disparador HTTP `text-to-timer`. Asegúrate de pasar el texto a traducir y los idiomas como un cuerpo JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Este ejemplo traduce *Définir une minuterie de 30 secondes* de francés a inglés estadounidense. Devolverá *Set a 30-second timer*.

> 💁 Puedes encontrar este código en la carpeta [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Tarea - usar la función de traducción para traducir texto

1. Abre el proyecto `smart-timer` en VS Code si aún no está abierto.

1. Tu temporizador inteligente tendrá configurados 2 idiomas: el idioma del servidor que se utilizó para entrenar LUIS (el mismo idioma también se utiliza para construir los mensajes que se le hablarán al usuario) y el idioma hablado por el usuario. Actualiza la constante `LANGUAGE` en el archivo de encabezado `config.h` para que sea el idioma que hablará el usuario, y agrega una nueva constante llamada `SERVER_LANGUAGE` para el idioma utilizado para entrenar LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Sustituye `<user language>` con el nombre de la configuración regional del idioma que hablarás, por ejemplo, `fr-FR` para francés o `zn-HK` para cantonés.

    Sustituye `<server language>` con el nombre de la configuración regional del idioma utilizado para entrenar LUIS.

    Puedes encontrar una lista de los idiomas admitidos y sus nombres de configuración regional en la [documentación de soporte de idiomas y voces en Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Si no hablas varios idiomas, puedes usar un servicio como [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) para traducir de tu idioma preferido a un idioma de tu elección. Estos servicios pueden reproducir audio del texto traducido.
    >
    > Por ejemplo, si entrenas LUIS en inglés pero deseas usar francés como idioma del usuario, puedes traducir frases como "set a 2 minute and 27 second timer" de inglés a francés utilizando Bing Translate, luego usar el botón **Escuchar traducción** para hablar la traducción en tu micrófono.
    >
    > ![El botón escuchar traducción en Bing Translate](../../../../../translated_images/es/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Agrega la clave de API del traductor y la ubicación debajo de `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Sustituye `<KEY>` con la clave de API de tu recurso del servicio de traducción. Sustituye `<LOCATION>` con la ubicación que usaste al crear el recurso del servicio de traducción.

1. Agrega la URL del disparador del traductor debajo de `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Sustituye `<URL>` con la URL del disparador HTTP `translate-text` en tu aplicación de funciones. Esto será igual al valor de `TEXT_TO_TIMER_FUNCTION_URL`, excepto que el nombre de la función será `translate-text` en lugar de `text-to-timer`.

1. Agrega un nuevo archivo a la carpeta `src` llamado `text_translator.h`.

1. Este nuevo archivo de encabezado `text_translator.h` contendrá una clase para traducir texto. Agrega lo siguiente a este archivo para declarar esta clase:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Esto declara la clase `TextTranslator`, junto con una instancia de esta clase. La clase tiene un único campo para el cliente WiFi.

1. En la sección `public` de esta clase, agrega un método para traducir texto:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Este método toma el idioma del que se traducirá y el idioma al que se traducirá. Al manejar el discurso, el discurso se traducirá del idioma del usuario al idioma del servidor LUIS, y al dar respuestas se traducirá del idioma del servidor LUIS al idioma del usuario.

1. En este método, agrega código para construir un cuerpo JSON que contenga el texto a traducir y los idiomas:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Debajo de esto, agrega el siguiente código para enviar el cuerpo a la aplicación de funciones sin servidor:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. A continuación, agrega código para obtener la respuesta:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Finalmente, agrega código para cerrar la conexión y devolver el texto traducido:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Tarea - traducir el discurso reconocido y las respuestas

1. Abre el archivo `main.cpp`.

1. Agrega una directiva de inclusión en la parte superior del archivo para el archivo de encabezado de la clase `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. El texto que se dice cuando se establece o expira un temporizador necesita ser traducido. Para hacer esto, agrega lo siguiente como la primera línea de la función `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Esto traducirá el texto al idioma del usuario.

1. En la función `processAudio`, el texto se recupera del audio capturado con la llamada `String text = speechToText.convertSpeechToText();`. Después de esta llamada, traduce el texto:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Esto traducirá el texto del idioma del usuario al idioma utilizado en el servidor.

1. Compila este código, súbelo a tu Wio Terminal y pruébalo a través del monitor serial. Una vez que veas `Ready` en el monitor serial, presiona el botón C (el que está en el lado izquierdo, más cerca del interruptor de encendido) y habla. Asegúrate de que tu aplicación de funciones esté ejecutándose y solicita un temporizador en el idioma del usuario, ya sea hablando ese idioma tú mismo o utilizando una aplicación de traducción.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Puedes encontrar este código en la carpeta [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 ¡Tu programa de temporizador multilingüe fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.