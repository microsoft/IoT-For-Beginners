# Captura una imagen - Raspberry Pi

En esta parte de la lección, agregarás un sensor de cámara a tu Raspberry Pi y leerás imágenes desde él.

## Hardware

La Raspberry Pi necesita una cámara.

La cámara que usarás es un [Módulo de Cámara Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/). Esta cámara está diseñada para funcionar con la Raspberry Pi y se conecta a través de un conector dedicado en la Pi.

> 💁 Esta cámara utiliza la [Interfaz Serial de Cámara, un protocolo de la Alianza de Procesadores de la Industria Móvil](https://wikipedia.org/wiki/Camera_Serial_Interface), conocido como MIPI-CSI. Este es un protocolo dedicado para enviar imágenes.

## Conecta la cámara

La cámara se puede conectar a la Raspberry Pi utilizando un cable plano.

### Tarea - conectar la cámara

![Una cámara Raspberry Pi](../../../../../translated_images/es/pi-camera-module.4278753c31bd6e75.webp)

1. Apaga la Raspberry Pi.

1. Conecta el cable plano que viene con la cámara a la cámara. Para hacerlo, tira suavemente del clip de plástico negro en el soporte para que salga un poco, luego desliza el cable en el conector, con el lado azul mirando hacia afuera del lente y las tiras de pines metálicos mirando hacia el lente. Una vez que esté completamente insertado, empuja el clip de plástico negro de nuevo en su lugar.

    Puedes encontrar una animación que muestra cómo abrir el clip e insertar el cable en la [documentación de Raspberry Pi para comenzar con el módulo de cámara](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![El cable plano insertado en el módulo de cámara](../../../../../translated_images/es/pi-camera-ribbon-cable.0bf82acd251611c2.webp)

1. Retira el Grove Base Hat de la Raspberry Pi.

1. Pasa el cable plano a través de la ranura para cámara en el Grove Base Hat. Asegúrate de que el lado azul del cable mire hacia los puertos analógicos etiquetados como **A0**, **A1**, etc.

    ![El cable plano pasando a través del Grove Base Hat](../../../../../translated_images/es/grove-base-hat-ribbon-cable.501fed202fcf73b1.webp)

1. Inserta el cable plano en el puerto de cámara de la Raspberry Pi. Una vez más, tira del clip de plástico negro hacia arriba, inserta el cable y luego empuja el clip hacia abajo. El lado azul del cable debe mirar hacia los puertos USB y Ethernet.

    ![El cable plano conectado al puerto de cámara en la Raspberry Pi](../../../../../translated_images/es/pi-camera-socket-ribbon-cable.a18309920b118009.webp)

1. Vuelve a colocar el Grove Base Hat.

## Programa la cámara

Ahora se puede programar la Raspberry Pi para usar la cámara utilizando la biblioteca de Python [PiCamera](https://pypi.org/project/picamera/).

### Tarea - habilitar el modo de cámara heredado

Desafortunadamente, con el lanzamiento de Raspberry Pi OS Bullseye, el software de cámara incluido en el sistema operativo cambió, lo que significa que, por defecto, PiCamera ya no funciona. Hay un reemplazo en desarrollo, llamado PiCamera2, pero aún no está listo para ser utilizado.

Por ahora, puedes configurar tu Raspberry Pi en modo de cámara heredado para permitir que PiCamera funcione. El puerto de la cámara también está deshabilitado por defecto, pero al activar el software de cámara heredado, el puerto se habilita automáticamente.

1. Enciende la Raspberry Pi y espera a que inicie.

1. Abre VS Code, ya sea directamente en la Raspberry Pi o conectándote a través de la extensión Remote SSH.

1. Ejecuta los siguientes comandos desde tu terminal:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Esto activará una configuración para habilitar el software de cámara heredado y luego reiniciará la Raspberry Pi para que la configuración surta efecto.

1. Espera a que la Raspberry Pi se reinicie y luego vuelve a abrir VS Code.

### Tarea - programa la cámara

Programa el dispositivo.

1. Desde el terminal, crea una nueva carpeta en el directorio de inicio del usuario `pi` llamada `fruit-quality-detector`. Crea un archivo en esta carpeta llamado `app.py`.

1. Abre esta carpeta en VS Code.

1. Para interactuar con la cámara, puedes usar la biblioteca de Python PiCamera. Instala el paquete Pip para esto con el siguiente comando:

    ```sh
    pip3 install picamera
    ```

1. Agrega el siguiente código a tu archivo `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Este código importa algunas bibliotecas necesarias, incluida la biblioteca `PiCamera`.

1. Agrega el siguiente código debajo de esto para inicializar la cámara:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Este código crea un objeto PiCamera y establece la resolución en 640x480. Aunque se admiten resoluciones más altas (hasta 3280x2464), el clasificador de imágenes funciona con imágenes mucho más pequeñas (227x227), por lo que no es necesario capturar y enviar imágenes más grandes.

    La línea `camera.rotation = 0` establece la rotación de la imagen. El cable plano entra por la parte inferior de la cámara, pero si tu cámara está girada para apuntar más fácilmente al objeto que deseas clasificar, puedes cambiar esta línea al número de grados de rotación.

    ![La cámara colgando sobre una lata de bebida](../../../../../translated_images/es/pi-camera-upside-down.5376961ba3145988.webp)

    Por ejemplo, si suspendes el cable plano sobre algo para que esté en la parte superior de la cámara, entonces establece la rotación en 180:

    ```python
    camera.rotation = 180
    ```

    La cámara tarda unos segundos en encenderse, de ahí la línea `time.sleep(2)`.

1. Agrega el siguiente código debajo de esto para capturar la imagen como datos binarios:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Este código crea un objeto `BytesIO` para almacenar datos binarios. La imagen se lee desde la cámara como un archivo JPEG y se almacena en este objeto. Este objeto tiene un indicador de posición para saber dónde está en los datos, de modo que se puedan escribir más datos al final si es necesario, por lo que la línea `image.seek(0)` mueve esta posición al inicio para que todos los datos puedan leerse más tarde.

1. Debajo de esto, agrega lo siguiente para guardar la imagen en un archivo:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Este código abre un archivo llamado `image.jpg` para escritura, luego lee todos los datos del objeto `BytesIO` y los escribe en el archivo.

    > 💁 Puedes capturar la imagen directamente en un archivo en lugar de un objeto `BytesIO` pasando el nombre del archivo a la llamada `camera.capture`. La razón para usar el objeto `BytesIO` es que más adelante en esta lección podrás enviar la imagen a tu clasificador de imágenes.

1. Apunta la cámara a algo y ejecuta este código.

1. Se capturará una imagen y se guardará como `image.jpg` en la carpeta actual. Verás este archivo en el explorador de VS Code. Selecciona el archivo para ver la imagen. Si necesita rotación, actualiza la línea `camera.rotation = 0` según sea necesario y toma otra foto.

> 💁 Puedes encontrar este código en la carpeta [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 ¡Tu programa de cámara fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.