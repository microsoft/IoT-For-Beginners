# Traducir discurso - Raspberry Pi

En esta parte de la lección, escribirás código para traducir texto utilizando el servicio de traducción.

## Convertir texto a discurso usando el servicio de traducción

La API REST del servicio de voz no admite traducciones directas; en su lugar, puedes usar el servicio de Traducción para traducir el texto generado por el servicio de voz a texto, así como el texto de la respuesta hablada. Este servicio tiene una API REST que puedes usar para traducir el texto.

### Tarea - usar el recurso de traducción para traducir texto

1. Tu temporizador inteligente tendrá configurados 2 idiomas: el idioma del servidor que se utilizó para entrenar LUIS (el mismo idioma también se usa para construir los mensajes que se le hablarán al usuario) y el idioma hablado por el usuario. Actualiza la variable `language` para que sea el idioma que hablará el usuario, y agrega una nueva variable llamada `server_language` para el idioma utilizado para entrenar LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Sustituye `<user language>` por el nombre de la configuración regional del idioma que hablarás, por ejemplo, `fr-FR` para francés o `zn-HK` para cantonés.

    Sustituye `<server language>` por el nombre de la configuración regional del idioma utilizado para entrenar LUIS.

    Puedes encontrar una lista de los idiomas admitidos y sus nombres de configuración regional en la [documentación de soporte de idiomas y voces en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Si no hablas varios idiomas, puedes usar un servicio como [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) para traducir de tu idioma preferido a otro idioma de tu elección. Estos servicios también pueden reproducir audio del texto traducido.
    >
    > Por ejemplo, si entrenas LUIS en inglés pero deseas usar francés como idioma del usuario, puedes traducir frases como "set a 2 minute and 27 second timer" del inglés al francés usando Bing Translate, y luego usar el botón **Escuchar traducción** para hablar la traducción en tu micrófono.
    >
    > ![El botón de escuchar traducción en Bing Translate](../../../../../translated_images/es/bing-translate.348aa796d6efe2a9.webp)

1. Agrega la clave de la API del traductor debajo de `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Sustituye `<key>` por la clave de la API de tu recurso del servicio de traducción.

1. Encima de la función `say`, define una función `translate_text` que traduzca texto del idioma del servidor al idioma del usuario:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Los idiomas de origen y destino se pasan a esta función: tu aplicación necesita convertir del idioma del usuario al idioma del servidor al reconocer el habla, y del idioma del servidor al idioma del usuario al proporcionar retroalimentación hablada.

1. Dentro de esta función, define la URL y los encabezados para la llamada a la API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    La URL para esta API no es específica de la ubicación; en su lugar, la ubicación se pasa como un encabezado. La clave de la API se usa directamente, por lo que, a diferencia del servicio de voz, no es necesario obtener un token de acceso de la API emisora de tokens.

1. Debajo de esto, define los parámetros y el cuerpo para la llamada:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    Los `params` definen los parámetros que se pasarán a la llamada de la API, especificando los idiomas de origen y destino. Esta llamada traducirá el texto del idioma `from` al idioma `to`.

    El `body` contiene el texto a traducir. Es un arreglo, ya que se pueden traducir múltiples bloques de texto en la misma llamada.

1. Realiza la llamada a la API REST y obtén la respuesta:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    La respuesta que se recibe es un arreglo JSON, con un elemento que contiene las traducciones. Este elemento tiene un arreglo con las traducciones de todos los elementos pasados en el cuerpo.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Devuelve la propiedad `text` de la primera traducción del primer elemento en el arreglo:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Actualiza el bucle `while True` para traducir el texto de la llamada a `convert_speech_to_text` del idioma del usuario al idioma del servidor:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Este código también imprime las versiones original y traducida del texto en la consola.

1. Actualiza la función `say` para traducir el texto a decir del idioma del servidor al idioma del usuario:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Este código también imprime las versiones original y traducida del texto en la consola.

1. Ejecuta tu código. Asegúrate de que tu aplicación de funciones esté en ejecución y solicita un temporizador en el idioma del usuario, ya sea hablando ese idioma tú mismo o usando una aplicación de traducción.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Debido a las diferentes formas de decir algo en distintos idiomas, es posible que obtengas traducciones ligeramente diferentes a los ejemplos que diste a LUIS. Si este es el caso, agrega más ejemplos a LUIS, vuelve a entrenar y luego vuelve a publicar el modelo.

> 💁 Puedes encontrar este código en la carpeta [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 ¡Tu programa de temporizador multilingüe fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.