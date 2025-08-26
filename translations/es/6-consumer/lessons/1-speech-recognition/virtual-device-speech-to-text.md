<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-26T15:36:50+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "es"
}
-->
# Conversión de voz a texto - Dispositivo IoT virtual

En esta parte de la lección, escribirás código para convertir el habla capturada desde tu micrófono en texto utilizando el servicio de voz.

## Convertir voz a texto

En Windows, Linux y macOS, el SDK de Python para los servicios de voz puede usarse para escuchar tu micrófono y convertir cualquier habla detectada en texto. Escuchará de forma continua, detectando los niveles de audio y enviando el habla para su conversión a texto cuando el nivel de audio disminuya, como al final de un bloque de habla.

### Tarea - convertir voz a texto

1. Crea una nueva aplicación de Python en tu computadora en una carpeta llamada `smart-timer` con un único archivo llamado `app.py` y un entorno virtual de Python.

1. Instala el paquete Pip para los servicios de voz. Asegúrate de instalarlo desde una terminal con el entorno virtual activado.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Si obtienes el siguiente error:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Necesitarás actualizar Pip. Hazlo con el siguiente comando y luego intenta instalar el paquete nuevamente:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Agrega las siguientes importaciones al archivo `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Esto importa algunas clases utilizadas para reconocer voz.

1. Agrega el siguiente código para declarar algunas configuraciones:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Sustituye `<key>` con la clave API de tu servicio de voz. Sustituye `<location>` con la ubicación que usaste al crear el recurso del servicio de voz.

    Sustituye `<language>` con el nombre de la configuración regional del idioma en el que hablarás, por ejemplo, `en-GB` para inglés o `zn-HK` para cantonés. Puedes encontrar una lista de los idiomas admitidos y sus nombres de configuración regional en la [documentación de soporte de idiomas y voces en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Esta configuración se utiliza para crear un objeto `SpeechConfig` que configurará los servicios de voz.

1. Agrega el siguiente código para crear un reconocedor de voz:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. El reconocedor de voz se ejecuta en un hilo en segundo plano, escuchando el audio y convirtiendo cualquier habla en texto. Puedes obtener el texto utilizando una función de callback: una función que defines y pasas al reconocedor. Cada vez que se detecta habla, se llama al callback. Agrega el siguiente código para definir un callback y pásalo al reconocedor, además de definir una función para procesar el texto, escribiéndolo en la consola:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. El reconocedor solo comienza a escuchar cuando lo inicias explícitamente. Agrega el siguiente código para iniciar el reconocimiento. Esto se ejecuta en segundo plano, por lo que tu aplicación también necesitará un bucle infinito que duerma para mantener la aplicación en ejecución.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Ejecuta esta aplicación. Habla en tu micrófono y el audio convertido a texto se mostrará en la consola.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prueba diferentes tipos de oraciones, junto con oraciones donde las palabras suenen igual pero tengan significados diferentes. Por ejemplo, si estás hablando en inglés, di "I want to buy two bananas and an apple too" y observa cómo utiliza correctamente "to", "two" y "too" según el contexto de la palabra, no solo su sonido.

> 💁 Puedes encontrar este código en la carpeta [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 ¡Tu programa de conversión de voz a texto fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.