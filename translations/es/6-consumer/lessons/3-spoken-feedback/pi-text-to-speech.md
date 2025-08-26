<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-26T15:30:53+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "es"
}
-->
# Texto a voz - Raspberry Pi

En esta parte de la lección, escribirás código para convertir texto a voz utilizando el servicio de voz.

## Convertir texto a voz utilizando el servicio de voz

El texto puede enviarse al servicio de voz utilizando la API REST para obtener un archivo de audio que puede reproducirse en tu dispositivo IoT. Al solicitar la conversión a voz, debes proporcionar la voz que se utilizará, ya que se puede generar voz utilizando una variedad de voces diferentes.

Cada idioma admite una gama de voces distintas, y puedes realizar una solicitud REST al servicio de voz para obtener la lista de voces compatibles para cada idioma.

### Tarea - obtener una voz

1. Abre el proyecto `smart-timer` en VS Code.

1. Agrega el siguiente código encima de la función `say` para solicitar la lista de voces para un idioma:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Este código define una función llamada `get_voice` que utiliza el servicio de voz para obtener una lista de voces. Luego encuentra la primera voz que coincide con el idioma que se está utilizando.

    Esta función se llama para almacenar la primera voz, y el nombre de la voz se imprime en la consola. Esta voz puede solicitarse una vez y el valor puede usarse en cada llamada para convertir texto a voz.

    > 💁 Puedes obtener la lista completa de voces compatibles en la [documentación de soporte de idiomas y voces en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Si deseas usar una voz específica, puedes eliminar esta función y codificar directamente el nombre de la voz desde esta documentación. Por ejemplo:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Tarea - convertir texto a voz

1. Debajo de esto, define una constante para el formato de audio que se recuperará del servicio de voz. Cuando solicitas audio, puedes hacerlo en una variedad de formatos diferentes.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    El formato que puedes usar depende de tu hardware. Si obtienes errores de `Invalid sample rate` al reproducir el audio, cambia esto a otro valor. Puedes encontrar la lista de valores compatibles en la [documentación de la API REST de texto a voz en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Necesitarás usar audio en formato `riff`, y los valores que puedes probar son `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` y `riff-48khz-16bit-mono-pcm`.

1. Debajo de esto, declara una función llamada `get_speech` que convertirá el texto a voz utilizando la API REST del servicio de voz:

    ```python
    def get_speech(text):
    ```

1. En la función `get_speech`, define la URL a la que llamar y los encabezados que se deben pasar:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Esto configura los encabezados para usar un token de acceso generado, establece el contenido como SSML y define el formato de audio necesario.

1. Debajo de esto, define el SSML que se enviará a la API REST:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Este SSML establece el idioma y la voz a utilizar, junto con el texto a convertir.

1. Finalmente, agrega código en esta función para realizar la solicitud REST y devolver los datos de audio binarios:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Tarea - reproducir el audio

1. Debajo de la función `get_speech`, define una nueva función para reproducir el audio devuelto por la llamada a la API REST:

    ```python
    def play_speech(speech):
    ```

1. El `speech` pasado a esta función será el audio binario devuelto por la API REST. Usa el siguiente código para abrirlo como un archivo wave y pasarlo a PyAudio para reproducir el audio:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Este código utiliza un flujo de PyAudio, igual que al capturar audio. La diferencia aquí es que el flujo se configura como un flujo de salida, y los datos se leen del audio y se envían al flujo.

    En lugar de codificar directamente los detalles del flujo, como la tasa de muestreo, estos se leen de los datos de audio.

1. Reemplaza el contenido de la función `say` con lo siguiente:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Este código convierte el texto a voz como datos de audio binarios y reproduce el audio.

1. Ejecuta la aplicación y asegúrate de que la función de la aplicación también esté en ejecución. Configura algunos temporizadores y escucharás una respuesta hablada indicando que tu temporizador ha sido configurado, y luego otra respuesta hablada cuando el temporizador se complete.

    Si obtienes errores de `Invalid sample rate`, cambia el `playback_format` como se describió anteriormente.

> 💁 Puedes encontrar este código en la carpeta [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 ¡Tu programa de temporizador fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.