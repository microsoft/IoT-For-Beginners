<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-26T15:49:33+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "es"
}
-->
# Decodificar datos GPS - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, decodificarás los mensajes NMEA leídos del sensor GPS por la Raspberry Pi o el Dispositivo IoT Virtual, y extraerás la latitud y la longitud.

## Decodificar datos GPS

Una vez que los datos NMEA en bruto se han leído desde el puerto serial, pueden ser decodificados utilizando una biblioteca NMEA de código abierto.

### Tarea - decodificar datos GPS

Programa el dispositivo para decodificar los datos GPS.

1. Abre el proyecto de la aplicación `gps-sensor` si aún no está abierto.

1. Instala el paquete Pip `pynmea2`. Este paquete contiene código para decodificar mensajes NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Agrega el siguiente código a las importaciones en el archivo `app.py` para importar el módulo `pynmea2`:

    ```python
    import pynmea2
    ```

1. Reemplaza el contenido de la función `print_gps_data` con lo siguiente:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Este código utilizará la biblioteca `pynmea2` para analizar la línea leída desde el puerto serial UART.

    Si el tipo de sentencia del mensaje es `GGA`, entonces este es un mensaje de fijación de posición y se procesa. Los valores de latitud y longitud se leen del mensaje y se convierten a grados decimales desde el formato NMEA `(d)ddmm.mmmm`. La función `dm_to_sd` realiza esta conversión.

    Luego se verifica la dirección de la latitud, y si la latitud es sur, el valor se convierte en un número negativo. Lo mismo ocurre con la longitud; si es oeste, se convierte en un número negativo.

    Finalmente, las coordenadas se imprimen en la consola, junto con el número de satélites utilizados para obtener la ubicación.

1. Ejecuta el código. Si estás utilizando un dispositivo IoT virtual, asegúrate de que la aplicación CounterFit esté ejecutándose y que los datos GPS se estén enviando.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Puedes encontrar este código en la carpeta [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), o en la carpeta [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 ¡Tu programa del sensor GPS con decodificación de datos fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.