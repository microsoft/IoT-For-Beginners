<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-26T15:40:35+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "es"
}
-->
# Configura tu micrófono y altavoces - Raspberry Pi

En esta parte de la lección, agregarás un micrófono y altavoces a tu Raspberry Pi.

## Hardware

La Raspberry Pi necesita un micrófono.

La Pi no tiene un micrófono incorporado, por lo que necesitarás agregar un micrófono externo. Hay varias formas de hacerlo:

* Micrófono USB
* Auriculares USB
* Altavoz USB todo en uno
* Adaptador de audio USB y micrófono con conector de 3.5mm
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 No todos los micrófonos Bluetooth son compatibles con la Raspberry Pi, por lo que si tienes un micrófono o auriculares Bluetooth, podrías tener problemas para emparejarlos o capturar audio.

Las Raspberry Pi vienen con un conector de auriculares de 3.5mm. Puedes usarlo para conectar auriculares, un headset o un altavoz. También puedes agregar altavoces utilizando:

* Audio HDMI a través de un monitor o TV
* Altavoces USB
* Auriculares USB
* Altavoz USB todo en uno
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) con un altavoz conectado, ya sea al conector de 3.5mm o al puerto JST

## Conecta y configura el micrófono y los altavoces

El micrófono y los altavoces necesitan ser conectados y configurados.

### Tarea - conectar y configurar el micrófono

1. Conecta el micrófono utilizando el método adecuado. Por ejemplo, conéctalo a uno de los puertos USB.

1. Si estás utilizando el ReSpeaker 2-Mics Pi HAT, puedes quitar el Grove base hat y luego colocar el ReSpeaker hat en su lugar.

    ![Una Raspberry Pi con un ReSpeaker hat](../../../../../translated_images/es/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Necesitarás un botón Grove más adelante en esta lección, pero uno está integrado en este hat, por lo que el Grove base hat no es necesario.

    Una vez que el hat esté colocado, necesitarás instalar algunos controladores. Consulta las [instrucciones de inicio de Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) para obtener instrucciones sobre la instalación de los controladores.

    > ⚠️ Las instrucciones utilizan `git` para clonar un repositorio. Si no tienes `git` instalado en tu Pi, puedes instalarlo ejecutando el siguiente comando:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Ejecuta el siguiente comando en tu Terminal, ya sea en la Pi o conectado mediante VS Code y una sesión SSH remota, para ver información sobre el micrófono conectado:

    ```sh
    arecord -l
    ```

    Verás una lista de micrófonos conectados. Será algo como lo siguiente:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Suponiendo que solo tienes un micrófono, deberías ver solo una entrada. La configuración de micrófonos puede ser complicada en Linux, por lo que es más fácil usar solo un micrófono y desconectar cualquier otro.

    Anota el número de tarjeta, ya que lo necesitarás más adelante. En el ejemplo anterior, el número de tarjeta es 1.

### Tarea - conectar y configurar el altavoz

1. Conecta los altavoces utilizando el método adecuado.

1. Ejecuta el siguiente comando en tu Terminal, ya sea en la Pi o conectado mediante VS Code y una sesión SSH remota, para ver información sobre los altavoces conectados:

    ```sh
    aplay -l
    ```

    Verás una lista de altavoces conectados. Será algo como lo siguiente:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Siempre verás `card 0: Headphones`, ya que este es el conector de auriculares incorporado. Si has agregado altavoces adicionales, como un altavoz USB, también aparecerán en la lista.

1. Si estás utilizando un altavoz adicional y no un altavoz o auriculares conectados al conector de auriculares incorporado, necesitas configurarlo como predeterminado. Para hacerlo, ejecuta el siguiente comando:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Esto abrirá un archivo de configuración en `nano`, un editor de texto basado en terminal. Desplázate hacia abajo utilizando las teclas de flecha en tu teclado hasta que encuentres la siguiente línea:

    ```output
    defaults.pcm.card 0
    ```

    Cambia el valor de `0` al número de tarjeta de la tarjeta que deseas usar de la lista que obtuviste con la llamada a `aplay -l`. Por ejemplo, en el ejemplo anterior hay una segunda tarjeta de sonido llamada `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, utilizando la tarjeta 1. Para usar esta, actualizaría la línea a:

    ```output
    defaults.pcm.card 1
    ```

    Establece este valor al número de tarjeta correspondiente. Puedes navegar hasta el número utilizando las teclas de flecha en tu teclado, luego eliminar y escribir el nuevo número como lo harías normalmente al editar archivos de texto.

1. Guarda los cambios y cierra el archivo presionando `Ctrl+x`. Presiona `y` para guardar el archivo y luego `return` para seleccionar el nombre del archivo.

### Tarea - probar el micrófono y el altavoz

1. Ejecuta el siguiente comando para grabar 5 segundos de audio a través del micrófono:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Mientras este comando esté ejecutándose, haz ruido en el micrófono, como hablar, cantar, hacer beatboxing, tocar un instrumento o lo que prefieras.

1. Después de 5 segundos, la grabación se detendrá. Ejecuta el siguiente comando para reproducir el audio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Escucharás el audio reproducido a través de los altavoces. Ajusta el volumen de salida en tu altavoz según sea necesario.

1. Si necesitas ajustar el volumen del puerto de micrófono incorporado o ajustar la ganancia del micrófono, puedes usar la utilidad `alsamixer`. Puedes leer más sobre esta utilidad en la [página man de alsamixer de Linux](https://linux.die.net/man/1/alsamixer).

1. Si obtienes errores al reproducir el audio, verifica la tarjeta que configuraste como `defaults.pcm.card` en el archivo `alsa.conf`.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.