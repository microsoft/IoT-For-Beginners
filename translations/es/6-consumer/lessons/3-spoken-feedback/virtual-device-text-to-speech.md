<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-26T15:33:01+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "es"
}
-->
# Texto a voz - Dispositivo IoT virtual

En esta parte de la lección, escribirás código para convertir texto a voz utilizando el servicio de voz.

## Convertir texto a voz

El SDK de servicios de voz que utilizaste en la última lección para convertir voz a texto también puede ser usado para convertir texto a voz. Al solicitar la conversión a voz, necesitas proporcionar la voz que se utilizará, ya que la voz puede generarse utilizando una variedad de opciones diferentes.

Cada idioma admite una gama de voces distintas, y puedes obtener la lista de voces compatibles para cada idioma desde el SDK de servicios de voz.

### Tarea - convertir texto a voz

1. Abre el proyecto `smart-timer` en VS Code y asegúrate de que el entorno virtual esté cargado en la terminal.

1. Importa el `SpeechSynthesizer` del paquete `azure.cognitiveservices.speech` añadiéndolo a las importaciones existentes:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Encima de la función `say`, crea una configuración de voz para usar con el sintetizador de voz:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Esto utiliza la misma clave de API, ubicación e idioma que se usaron con el reconocedor.

1. Debajo de esto, agrega el siguiente código para obtener una voz y configurarla en la configuración de voz:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Esto recupera una lista de todas las voces disponibles y luego encuentra la primera voz que coincide con el idioma que se está utilizando.

    > 💁 Puedes obtener la lista completa de voces compatibles en la [documentación de soporte de idiomas y voces en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Si deseas usar una voz específica, puedes eliminar esta función y codificar directamente el nombre de la voz desde esta documentación. Por ejemplo:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Actualiza el contenido de la función `say` para generar SSML para la respuesta:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Debajo de esto, detén el reconocimiento de voz, reproduce el SSML, y luego reinicia el reconocimiento:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    El reconocimiento se detiene mientras se reproduce el texto para evitar que el anuncio de inicio del temporizador sea detectado, enviado a LUIS y posiblemente interpretado como una solicitud para configurar un nuevo temporizador.

    > 💁 Puedes probar esto comentando las líneas para detener y reiniciar el reconocimiento. Configura un temporizador y es posible que el anuncio configure un nuevo temporizador, lo que provoca un nuevo anuncio, que a su vez configura otro temporizador, y así sucesivamente indefinidamente.

1. Ejecuta la aplicación y asegúrate de que la función de la aplicación también esté en ejecución. Configura algunos temporizadores y escucharás una respuesta hablada indicando que tu temporizador ha sido configurado, y luego otra respuesta hablada cuando el temporizador se complete.

> 💁 Puedes encontrar este código en la carpeta [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 ¡Tu programa de temporizador fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.