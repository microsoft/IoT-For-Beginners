# Traducir voz - Dispositivo IoT Virtual

En esta parte de la lección, escribirás código para traducir voz al convertirla en texto utilizando el servicio de voz, luego traducirás el texto usando el servicio de Traducción antes de generar una respuesta hablada.

## Usar el servicio de voz para traducir voz

El servicio de voz puede tomar voz y no solo convertirla en texto en el mismo idioma, sino también traducir el resultado a otros idiomas.

### Tarea - usar el servicio de voz para traducir voz

1. Abre el proyecto `smart-timer` en VS Code y asegúrate de que el entorno virtual esté cargado en la terminal.

1. Agrega las siguientes declaraciones de importación debajo de las importaciones existentes:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Esto importa las clases utilizadas para traducir voz y una biblioteca `requests` que se usará para realizar una llamada al servicio de Traducción más adelante en esta lección.

1. Tu temporizador inteligente tendrá 2 idiomas configurados: el idioma del servidor que se utilizó para entrenar LUIS (el mismo idioma también se utiliza para construir los mensajes que se le hablarán al usuario) y el idioma hablado por el usuario. Actualiza la variable `language` para que sea el idioma que hablará el usuario y agrega una nueva variable llamada `server_language` para el idioma utilizado para entrenar LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Reemplaza `<user language>` con el nombre de la configuración regional del idioma que hablarás, por ejemplo, `fr-FR` para francés o `zn-HK` para cantonés.

    Reemplaza `<server language>` con el nombre de la configuración regional del idioma utilizado para entrenar LUIS.

    Puedes encontrar una lista de los idiomas compatibles y sus nombres de configuración regional en la [documentación de soporte de idiomas y voces en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Si no hablas varios idiomas, puedes usar un servicio como [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) para traducir de tu idioma preferido a un idioma de tu elección. Estos servicios pueden reproducir audio del texto traducido. Ten en cuenta que el reconocedor de voz ignorará parte del audio de salida de tu dispositivo, por lo que es posible que necesites usar un dispositivo adicional para reproducir el texto traducido.
    >
    > Por ejemplo, si entrenas LUIS en inglés pero deseas usar francés como idioma del usuario, puedes traducir frases como "set a 2 minute and 27 second timer" del inglés al francés usando Bing Translate, luego usar el botón **Escuchar traducción** para hablar la traducción en tu micrófono.
    >
    > ![El botón escuchar traducción en Bing Translate](../../../../../translated_images/es/bing-translate.348aa796d6efe2a9.webp)

1. Reemplaza las declaraciones `recognizer_config` y `recognizer` con lo siguiente:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Esto crea una configuración de traducción para reconocer voz en el idioma del usuario y generar traducciones en el idioma del usuario y del servidor. Luego utiliza esta configuración para crear un reconocedor de traducción: un reconocedor de voz que puede traducir el resultado del reconocimiento de voz a múltiples idiomas.

    > 💁 El idioma original debe especificarse en `target_languages`, de lo contrario no obtendrás ninguna traducción.

1. Actualiza la función `recognized`, reemplazando todo el contenido de la función con lo siguiente:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Este código verifica si el evento reconocido se activó porque la voz fue traducida (este evento puede activarse en otros momentos, como cuando la voz es reconocida pero no traducida). Si la voz fue traducida, encuentra la traducción en el diccionario `args.result.translations` que coincide con el idioma del servidor.

    El diccionario `args.result.translations` está indexado por la parte del idioma de la configuración regional, no por toda la configuración. Por ejemplo, si solicitas una traducción a `fr-FR` para francés, el diccionario contendrá una entrada para `fr`, no para `fr-FR`.

    Luego, el texto traducido se envía al IoT Hub.

1. Ejecuta este código para probar las traducciones. Asegúrate de que tu aplicación de funciones esté en ejecución y solicita un temporizador en el idioma del usuario, ya sea hablando ese idioma tú mismo o utilizando una aplicación de traducción.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Traducir texto usando el servicio de traducción

El servicio de voz no admite la traducción de texto de vuelta a voz, en su lugar puedes usar el servicio de Traducción para traducir el texto. Este servicio tiene una API REST que puedes usar para traducir el texto.

### Tarea - usar el recurso de traducción para traducir texto

1. Agrega la clave de la API de traducción debajo de `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Reemplaza `<key>` con la clave de API para tu recurso de servicio de traducción.

1. Encima de la función `say`, define una función `translate_text` que traducirá texto del idioma del servidor al idioma del usuario:

    ```python
    def translate_text(text):
    ```

1. Dentro de esta función, define la URL y los encabezados para la llamada a la API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    La URL para esta API no es específica de la ubicación, en su lugar la ubicación se pasa como un encabezado. La clave de API se utiliza directamente, por lo que, a diferencia del servicio de voz, no es necesario obtener un token de acceso de la API emisora de tokens.

1. Debajo de esto, define los parámetros y el cuerpo para la llamada:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    Los `params` definen los parámetros para pasar a la llamada de la API, pasando los idiomas de origen y destino. Esta llamada traducirá texto en el idioma `from` al idioma `to`.

    El `body` contiene el texto a traducir. Esto es un arreglo, ya que se pueden traducir múltiples bloques de texto en la misma llamada.

1. Realiza la llamada a la API REST y obtén la respuesta:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    La respuesta que regresa es un arreglo JSON, con un elemento que contiene las traducciones. Este elemento tiene un arreglo para las traducciones de todos los elementos pasados en el cuerpo.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Devuelve la propiedad `text` de la primera traducción del primer elemento en el arreglo:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Actualiza la función `say` para traducir el texto antes de que se genere el SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Este código también imprime las versiones original y traducida del texto en la consola.

1. Ejecuta tu código. Asegúrate de que tu aplicación de funciones esté en ejecución y solicita un temporizador en el idioma del usuario, ya sea hablando ese idioma tú mismo o utilizando una aplicación de traducción.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Debido a las diferentes formas de decir algo en diferentes idiomas, es posible que obtengas traducciones que sean ligeramente diferentes a los ejemplos que diste a LUIS. Si este es el caso, agrega más ejemplos a LUIS, vuelve a entrenar y luego vuelve a publicar el modelo.

> 💁 Puedes encontrar este código en la carpeta [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 ¡Tu programa de temporizador multilingüe fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.