<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-26T14:20:25+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "es"
}
-->
# Clasificar una imagen usando un clasificador de imágenes basado en IoT Edge - Wio Terminal

En esta parte de la lección, utilizarás el clasificador de imágenes que se ejecuta en el dispositivo IoT Edge.

## Usar el clasificador de IoT Edge

El dispositivo IoT puede ser redirigido para usar el clasificador de imágenes de IoT Edge. La URL para el clasificador de imágenes es `http://<IP address or name>/image`, reemplazando `<IP address or name>` con la dirección IP o el nombre del host del equipo que ejecuta IoT Edge.

### Tarea - usar el clasificador de IoT Edge

1. Abre el proyecto de la aplicación `fruit-quality-detector` si no está ya abierto.

1. El clasificador de imágenes se ejecuta como una API REST utilizando HTTP, no HTTPS, por lo que la llamada necesita usar un cliente WiFi que funcione solo con llamadas HTTP. Esto significa que no se necesita el certificado. Elimina el `CERTIFICATE` del archivo `config.h`.

1. La URL de predicción en el archivo `config.h` debe actualizarse a la nueva URL. También puedes eliminar el `PREDICTION_KEY`, ya que no es necesario.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Sustituye `<URL>` por la URL de tu clasificador.

1. En `main.cpp`, cambia la directiva de inclusión para el WiFi Client Secure para importar la versión estándar de HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Cambia la declaración de `WiFiClient` para que sea la versión HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Selecciona la línea que establece el certificado en el cliente WiFi. Elimina la línea `client.setCACert(CERTIFICATE);` de la función `connectWiFi`.

1. En la función `classifyImage`, elimina la línea `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` que establece la clave de predicción en el encabezado.

1. Sube y ejecuta tu código. Apunta la cámara hacia alguna fruta y presiona el botón C. Verás la salida en el monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Puedes encontrar este código en la carpeta [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 ¡Tu programa de clasificación de calidad de frutas fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.