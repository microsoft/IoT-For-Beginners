# Leer datos de GPS - Raspberry Pi

En esta parte de la lección, agregarás un sensor GPS a tu Raspberry Pi y leerás valores de él.

## Hardware

La Raspberry Pi necesita un sensor GPS.

El sensor que usarás es un [sensor Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Este sensor puede conectarse a múltiples sistemas GPS para obtener una ubicación rápida y precisa. El sensor está compuesto por 2 partes: la electrónica principal del sensor y una antena externa conectada por un cable delgado para captar las ondas de radio de los satélites.

Este es un sensor UART, por lo que envía datos GPS a través de UART.

## Conectar el sensor GPS

El sensor Grove GPS puede conectarse a la Raspberry Pi.

### Tarea - conectar el sensor GPS

Conecta el sensor GPS.

![Un sensor Grove GPS](../../../../../translated_images/es/grove-gps-sensor.247943bf69b03f0d.webp)

1. Inserta un extremo de un cable Grove en el conector del sensor GPS. Solo encajará de una manera.

1. Con la Raspberry Pi apagada, conecta el otro extremo del cable Grove al conector UART marcado como **UART** en el Grove Base Hat conectado a la Pi. Este conector está en la fila del medio, en el lado más cercano a la ranura de la tarjeta SD, en el extremo opuesto a los puertos USB y el conector Ethernet.

    ![El sensor Grove GPS conectado al conector UART](../../../../../translated_images/es/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Coloca el sensor GPS de manera que la antena conectada tenga visibilidad al cielo, idealmente cerca de una ventana abierta o al aire libre. Es más fácil obtener una señal clara sin obstáculos para la antena.

## Programar el sensor GPS

La Raspberry Pi ahora puede ser programada para usar el sensor GPS conectado.

### Tarea - programar el sensor GPS

Programa el dispositivo.

1. Enciende la Pi y espera a que arranque.

1. El sensor GPS tiene 2 LEDs: un LED azul que parpadea cuando se transmiten datos y un LED verde que parpadea cada segundo cuando recibe datos de los satélites. Asegúrate de que el LED azul esté parpadeando cuando enciendas la Pi. Después de unos minutos, el LED verde comenzará a parpadear; si no lo hace, puede que necesites reposicionar la antena.

1. Abre VS Code, ya sea directamente en la Pi o conectándote mediante la extensión Remote SSH.

    > ⚠️ Puedes consultar [las instrucciones para configurar y abrir VS Code en la lección 1 si lo necesitas](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Con las versiones más recientes de la Raspberry Pi que admiten Bluetooth, existe un conflicto entre el puerto serial utilizado para Bluetooth y el utilizado por el puerto UART del Grove. Para solucionarlo, haz lo siguiente:

    1. Desde el terminal de VS Code, edita el archivo `/boot/config.txt` usando `nano`, un editor de texto integrado en el terminal, con el siguiente comando:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Este archivo no puede ser editado por VS Code ya que necesitas permisos elevados (`sudo`). VS Code no ejecuta esta función.

    1. Usa las teclas de dirección para navegar al final del archivo, luego copia el código a continuación y pégalo al final del archivo:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Puedes pegar usando los atajos de teclado normales de tu dispositivo (`Ctrl+v` en Windows, Linux o Raspberry Pi OS, `Cmd+v` en macOS).

    1. Guarda este archivo y sal de nano presionando `Ctrl+x`. Presiona `y` cuando se te pregunte si deseas guardar el buffer modificado, luego presiona `enter` para confirmar que deseas sobrescribir `/boot/config.txt`.

        > Si cometes un error, puedes salir sin guardar y repetir estos pasos.

    1. Edita el archivo `/boot/cmdline.txt` en nano con el siguiente comando:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Este archivo tiene varios pares clave/valor separados por espacios. Elimina cualquier par clave/valor para la clave `console`. Probablemente se verán algo así:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Puedes navegar a estas entradas usando las teclas de dirección y luego eliminarlas usando las teclas `del` o `backspace`.

        Por ejemplo, si tu archivo original se ve así:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        La nueva versión será:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Sigue los pasos anteriores para guardar este archivo y salir de nano.

    1. Reinicia tu Pi y luego vuelve a conectarte en VS Code una vez que la Pi haya reiniciado.

1. Desde el terminal, crea una nueva carpeta en el directorio de inicio del usuario `pi` llamada `gps-sensor`. Crea un archivo en esta carpeta llamado `app.py`.

1. Abre esta carpeta en VS Code.

1. El módulo GPS envía datos UART a través de un puerto serial. Instala el paquete Pip `pyserial` para comunicarte con el puerto serial desde tu código Python:

    ```sh
    pip3 install pyserial
    ```

1. Agrega el siguiente código a tu archivo `app.py`:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Este código importa el módulo `serial` del paquete Pip `pyserial`. Luego se conecta al puerto serial `/dev/ttyAMA0`, que es la dirección del puerto serial que utiliza el Grove Pi Base Hat para su puerto UART. Después, limpia cualquier dato existente de esta conexión serial.

    A continuación, se define una función llamada `print_gps_data` que imprime en la consola la línea que se le pasa.

    Luego, el código entra en un bucle infinito, leyendo tantas líneas de texto como pueda del puerto serial en cada iteración. Llama a la función `print_gps_data` para cada línea.

    Después de leer todos los datos, el bucle duerme durante 1 segundo y luego intenta nuevamente.

1. Ejecuta este código. Verás la salida en bruto del sensor GPS, algo como lo siguiente:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Si obtienes uno de los siguientes errores al detener y reiniciar tu código, agrega un bloque `try - except` a tu bucle while.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Puedes encontrar este código en la carpeta [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 ¡Tu programa del sensor GPS fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.