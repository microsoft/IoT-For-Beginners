<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-26T15:41:54+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "es"
}
-->
# De voz a texto - Raspberry Pi

En esta parte de la lección, escribirás código para convertir el habla del audio capturado en texto utilizando el servicio de voz.

## Envía el audio al servicio de voz

El audio puede enviarse al servicio de voz utilizando la API REST. Para usar el servicio de voz, primero necesitas solicitar un token de acceso y luego usar ese token para acceder a la API REST. Estos tokens de acceso expiran después de 10 minutos, por lo que tu código debe solicitarlos regularmente para asegurarse de que siempre estén actualizados.

### Tarea - obtener un token de acceso

1. Abre el proyecto `smart-timer` en tu Raspberry Pi.

1. Elimina la función `play_audio`. Ya no es necesaria, ya que no quieres que el temporizador inteligente repita lo que dijiste.

1. Agrega la siguiente importación al inicio del archivo `app.py`:

    ```python
    import requests
    ```

1. Añade el siguiente código encima del bucle `while True` para declarar algunas configuraciones para el servicio de voz:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Sustituye `<key>` con la clave API de tu recurso del servicio de voz. Sustituye `<location>` con la ubicación que usaste al crear el recurso del servicio de voz.

    Sustituye `<language>` con el nombre de la configuración regional del idioma en el que hablarás, por ejemplo, `en-GB` para inglés o `zn-HK` para cantonés. Puedes encontrar una lista de los idiomas admitidos y sus nombres de configuración regional en la [documentación de soporte de idiomas y voces en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Debajo de esto, agrega la siguiente función para obtener un token de acceso:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Esto llama a un endpoint de emisión de tokens, pasando la clave API como un encabezado. Esta llamada devuelve un token de acceso que puede usarse para llamar a los servicios de voz.

1. Debajo de esto, declara una función para convertir el habla del audio capturado en texto utilizando la API REST:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Dentro de esta función, configura la URL de la API REST y los encabezados:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Esto construye una URL utilizando la ubicación del recurso del servicio de voz. Luego, llena los encabezados con el token de acceso de la función `get_access_token`, así como la frecuencia de muestreo utilizada para capturar el audio. Finalmente, define algunos parámetros que se pasarán con la URL, incluyendo el idioma del audio.

1. Debajo de esto, agrega el siguiente código para llamar a la API REST y obtener el texto:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Esto llama a la URL y decodifica el valor JSON que viene en la respuesta. El valor `RecognitionStatus` en la respuesta indica si la llamada pudo extraer con éxito el habla en texto, y si este es `Success`, entonces el texto se devuelve desde la función; de lo contrario, se devuelve una cadena vacía.

1. Encima del bucle `while True:`, define una función para procesar el texto devuelto por el servicio de voz a texto. Por ahora, esta función solo imprimirá el texto en la consola.

    ```python
    def process_text(text):
        print(text)
    ```

1. Finalmente, reemplaza la llamada a `play_audio` en el bucle `while True` con una llamada a la función `convert_speech_to_text`, pasando el texto a la función `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Ejecuta el código. Presiona el botón y habla al micrófono. Suelta el botón cuando termines, y el audio se convertirá en texto y se imprimirá en la consola.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prueba diferentes tipos de oraciones, junto con oraciones donde las palabras suenen igual pero tengan significados diferentes. Por ejemplo, si estás hablando en inglés, di "I want to buy two bananas and an apple too" y observa cómo utiliza correctamente "to", "two" y "too" según el contexto de la palabra, no solo por su sonido.

> 💁 Puedes encontrar este código en la carpeta [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 ¡Tu programa de voz a texto fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.