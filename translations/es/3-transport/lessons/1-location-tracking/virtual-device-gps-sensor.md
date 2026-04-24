# Leer datos GPS - Hardware IoT Virtual

En esta parte de la lección, agregarás un sensor GPS a tu dispositivo IoT virtual y leerás valores de él.

## Hardware Virtual

El dispositivo IoT virtual usará un sensor GPS simulado que es accesible a través de UART mediante un puerto serial.

Un sensor GPS físico tendrá una antena para captar ondas de radio de los satélites GPS y convertir las señales GPS en datos GPS. La versión virtual simula esto permitiéndote establecer una latitud y longitud, enviar sentencias NMEA en bruto o cargar un archivo GPX con múltiples ubicaciones que se pueden devolver secuencialmente.

> 🎓 Las sentencias NMEA se cubrirán más adelante en esta lección.

### Agregar el sensor a CounterFit

Para usar un sensor GPS virtual, necesitas agregar uno a la aplicación CounterFit.

#### Tarea - agregar el sensor a CounterFit

Agrega el sensor GPS a la aplicación CounterFit.

1. Crea una nueva aplicación en Python en tu computadora dentro de una carpeta llamada `gps-sensor` con un único archivo llamado `app.py` y un entorno virtual de Python, y agrega los paquetes pip de CounterFit.

    > ⚠️ Puedes consultar [las instrucciones para crear y configurar un proyecto Python de CounterFit en la lección 1 si lo necesitas](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instala un paquete adicional de Pip para instalar un shim de CounterFit que pueda comunicarse con sensores basados en UART a través de una conexión serial. Asegúrate de instalarlo desde un terminal con el entorno virtual activado.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Asegúrate de que la aplicación web de CounterFit esté en ejecución.

1. Crea un sensor GPS:

    1. En el cuadro *Create sensor* en el panel *Sensors*, despliega el cuadro *Sensor type* y selecciona *UART GPS*.

    1. Deja el *Port* configurado como */dev/ttyAMA0*.

    1. Selecciona el botón **Add** para crear el sensor GPS en el puerto `/dev/ttyAMA0`.

    ![Configuración del sensor GPS](../../../../../translated_images/es/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    El sensor GPS será creado y aparecerá en la lista de sensores.

    ![Sensor GPS creado](../../../../../translated_images/es/counterfit-gps-sensor.3fbb15af0a536756.webp)

## Programar el sensor GPS

El dispositivo IoT virtual ahora puede ser programado para usar el sensor GPS virtual.

### Tarea - programar el sensor GPS

Programa la aplicación del sensor GPS.

1. Asegúrate de que la aplicación `gps-sensor` esté abierta en VS Code.

1. Abre el archivo `app.py`.

1. Agrega el siguiente código al inicio de `app.py` para conectar la aplicación a CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Agrega el siguiente código debajo de este para importar algunas bibliotecas necesarias, incluida la biblioteca para el puerto serial de CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Este código importa el módulo `serial` del paquete Pip `counterfit_shims_serial`. Luego se conecta al puerto serial `/dev/ttyAMA0`, que es la dirección del puerto serial que el sensor GPS virtual utiliza para su puerto UART.

1. Agrega el siguiente código debajo de este para leer desde el puerto serial e imprimir los valores en la consola:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Se define una función llamada `print_gps_data` que imprime en la consola la línea que se le pasa.

    Luego, el código entra en un bucle infinito, leyendo tantas líneas de texto como pueda desde el puerto serial en cada iteración. Llama a la función `print_gps_data` para cada línea.

    Después de leer todos los datos, el bucle duerme durante 1 segundo y luego lo intenta de nuevo.

1. Ejecuta este código, asegurándote de usar un terminal diferente al que está ejecutando la aplicación CounterFit, para que la aplicación CounterFit siga funcionando.

1. Desde la aplicación CounterFit, cambia el valor del sensor GPS. Puedes hacerlo de una de estas maneras:

    * Configura la **Source** como `Lat/Lon` y establece una latitud, longitud y número de satélites utilizados para obtener la posición GPS. Este valor se enviará solo una vez, así que marca la casilla **Repeat** para que los datos se repitan cada segundo.

      ![El sensor GPS con lat lon seleccionado](../../../../../translated_images/es/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Configura la **Source** como `NMEA` y agrega algunas sentencias NMEA en el cuadro de texto. Todos estos valores se enviarán, con un retraso de 1 segundo antes de que se pueda leer cada nueva sentencia GGA (posición fija).

      ![El sensor GPS con sentencias NMEA configuradas](../../../../../translated_images/es/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Puedes usar una herramienta como [nmeagen.org](https://www.nmeagen.org) para generar estas sentencias dibujando en un mapa. Estos valores se enviarán solo una vez, así que marca la casilla **Repeat** para que los datos se repitan un segundo después de que se hayan enviado todos.

    * Configura la **Source** como archivo GPX y carga un archivo GPX con ubicaciones de ruta. Puedes descargar archivos GPX de varios sitios populares de mapas y senderismo, como [AllTrails](https://www.alltrails.com/). Estos archivos contienen múltiples ubicaciones GPS como un recorrido, y el sensor GPS devolverá cada nueva ubicación en intervalos de 1 segundo.

      ![El sensor GPS con un archivo GPX configurado](../../../../../translated_images/es/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Estos valores se enviarán solo una vez, así que marca la casilla **Repeat** para que los datos se repitan un segundo después de que se hayan enviado todos.

    Una vez que hayas configurado los ajustes del GPS, selecciona el botón **Set** para confirmar estos valores en el sensor.

1. Verás la salida en bruto del sensor GPS, algo como lo siguiente:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Puedes encontrar este código en la carpeta [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 ¡Tu programa del sensor GPS fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.