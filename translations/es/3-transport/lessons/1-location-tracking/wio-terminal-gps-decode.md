<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-26T15:50:30+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "es"
}
-->
# Decodificar datos GPS - Wio Terminal

En esta parte de la lección, decodificarás los mensajes NMEA leídos desde el sensor GPS por el Wio Terminal y extraerás la latitud y la longitud.

## Decodificar datos GPS

Una vez que se hayan leído los datos NMEA en bruto desde el puerto serie, se pueden decodificar utilizando una biblioteca NMEA de código abierto.

### Tarea - decodificar datos GPS

Programa el dispositivo para decodificar los datos GPS.

1. Abre el proyecto de la aplicación `gps-sensor` si aún no está abierto.

1. Agrega una dependencia de biblioteca para la biblioteca [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) en el archivo `platformio.ini` del proyecto. Esta biblioteca contiene el código necesario para decodificar datos NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. En `main.cpp`, agrega una directiva de inclusión para la biblioteca TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Debajo de la declaración de `Serial3`, declara un objeto TinyGPSPlus para procesar las sentencias NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Cambia el contenido de la función `printGPSData` al siguiente:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Este código lee el siguiente carácter desde el puerto serie UART en el decodificador NMEA `gps`. Después de cada carácter, verificará si el decodificador ha leído una sentencia válida y luego comprobará si ha leído una ubicación válida. Si la ubicación es válida, la enviará al monitor serie junto con el número de satélites que contribuyeron a esta solución.

1. Compila y sube el código al Wio Terminal.

1. Una vez subido, puedes monitorear los datos de ubicación GPS utilizando el monitor serie.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Puedes encontrar este código en la carpeta [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 ¡Tu programa del sensor GPS con decodificación de datos fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.