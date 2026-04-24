# Capturar audio - Raspberry Pi

En esta parte de la lección, escribirás código para capturar audio en tu Raspberry Pi. La captura de audio será controlada por un botón.

## Hardware

La Raspberry Pi necesita un botón para controlar la captura de audio.

El botón que usarás es un botón Grove. Este es un sensor digital que activa o desactiva una señal. Estos botones pueden configurarse para enviar una señal alta cuando se presionan y baja cuando no, o baja cuando se presionan y alta cuando no.

Si estás utilizando un ReSpeaker 2-Mics Pi HAT como micrófono, no es necesario conectar un botón, ya que este HAT ya tiene uno incorporado. Salta a la siguiente sección.

### Conectar el botón

El botón puede conectarse al Grove Base Hat.

#### Tarea - conectar el botón

![Un botón Grove](../../../../../translated_images/es/grove-button.a70cfbb809a85636.webp)

1. Inserta un extremo de un cable Grove en el conector del módulo del botón. Solo encajará de una manera.

1. Con la Raspberry Pi apagada, conecta el otro extremo del cable Grove al conector digital marcado como **D5** en el Grove Base Hat conectado a la Pi. Este conector es el segundo desde la izquierda, en la fila de conectores junto a los pines GPIO.

![El botón Grove conectado al conector D5](../../../../../translated_images/es/pi-button.c7a1a4f55943341c.webp)

## Capturar audio

Puedes capturar audio desde el micrófono utilizando código en Python.

### Tarea - capturar audio

1. Enciende la Raspberry Pi y espera a que arranque.

1. Abre VS Code, ya sea directamente en la Pi o conectándote mediante la extensión Remote SSH.

1. El paquete PyAudio de Pip tiene funciones para grabar y reproducir audio. Este paquete depende de algunas bibliotecas de audio que deben instalarse primero. Ejecuta los siguientes comandos en el terminal para instalarlas:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Instala el paquete PyAudio de Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Crea una nueva carpeta llamada `smart-timer` y añade un archivo llamado `app.py` a esta carpeta.

1. Añade las siguientes importaciones al inicio de este archivo:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Esto importa el módulo `pyaudio`, algunos módulos estándar de Python para manejar archivos WAV, y el módulo `grove.factory` para importar una `Factory` que crea una clase de botón.

1. Debajo de esto, añade código para crear un botón Grove.

    Si estás utilizando el ReSpeaker 2-Mics Pi HAT, usa el siguiente código:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Esto crea un botón en el puerto **D17**, el puerto al que está conectado el botón en el ReSpeaker 2-Mics Pi HAT. Este botón está configurado para enviar una señal baja cuando se presiona.

    Si no estás utilizando el ReSpeaker 2-Mics Pi HAT y estás usando un botón Grove conectado al Base Hat, usa este código:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Esto crea un botón en el puerto **D5**, configurado para enviar una señal alta cuando se presiona.

1. Debajo de esto, crea una instancia de la clase PyAudio para manejar el audio:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Declara el número de tarjeta de hardware para el micrófono y el altavoz. Este será el número de la tarjeta que encontraste ejecutando `arecord -l` y `aplay -l` anteriormente en esta lección.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Reemplaza `<microphone card number>` con el número de la tarjeta de tu micrófono.

    Reemplaza `<speaker card number>` con el número de la tarjeta de tu altavoz, el mismo número que configuraste en el archivo `alsa.conf`.

1. Debajo de esto, declara la tasa de muestreo que se usará para la captura y reproducción de audio. Es posible que necesites cambiar esto dependiendo del hardware que estés utilizando.

    ```python
    rate = 48000 #48KHz
    ```

    Si obtienes errores de tasa de muestreo al ejecutar este código más adelante, cambia este valor a `44100` o `16000`. Cuanto mayor sea el valor, mejor será la calidad del sonido.

1. Debajo de esto, crea una nueva función llamada `capture_audio`. Esta será llamada para capturar audio desde el micrófono:

    ```python
    def capture_audio():
    ```

1. Dentro de esta función, añade lo siguiente para capturar el audio:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    Este código abre un flujo de entrada de audio utilizando el objeto PyAudio. Este flujo capturará audio desde el micrófono a 16KHz, capturándolo en búferes de 4096 bytes de tamaño.

    El código luego entra en un bucle mientras el botón Grove está presionado, leyendo estos búferes de 4096 bytes en un array cada vez.

    > 💁 Puedes leer más sobre las opciones que se pasan al método `open` en la [documentación de PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Una vez que se suelta el botón, el flujo se detiene y se cierra.

1. Añade lo siguiente al final de esta función:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    Este código crea un búfer binario y escribe todo el audio capturado en él como un [archivo WAV](https://wikipedia.org/wiki/WAV). Este es un formato estándar para escribir audio sin comprimir en un archivo. Este búfer luego se devuelve.

1. Añade la siguiente función `play_audio` para reproducir el búfer de audio:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    Esta función abre otro flujo de audio, esta vez para salida, para reproducir el audio. Utiliza la misma configuración que el flujo de entrada. El búfer se abre como un archivo WAV y se escribe en el flujo de salida en fragmentos de 4096 bytes, reproduciendo el audio. Luego, el flujo se cierra.

1. Añade el siguiente código debajo de la función `capture_audio` para entrar en un bucle hasta que se presione el botón. Una vez que se presione el botón, se capturará el audio y luego se reproducirá.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Ejecuta el código. Presiona el botón y habla en el micrófono. Suelta el botón cuando termines y escucharás la grabación.

    Es posible que obtengas algunos errores de ALSA cuando se crea la instancia de PyAudio. Esto se debe a la configuración en la Pi para dispositivos de audio que no tienes. Puedes ignorar estos errores.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Si obtienes el siguiente error:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    entonces cambia el `rate` a 44100 o 16000.

> 💁 Puedes encontrar este código en la carpeta [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 ¡Tu programa de grabación de audio fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.