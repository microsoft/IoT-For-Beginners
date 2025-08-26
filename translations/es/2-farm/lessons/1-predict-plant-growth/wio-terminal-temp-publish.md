<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-26T14:30:28+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "es"
}
-->
# Publicar temperatura - Wio Terminal

En esta parte de la lección, publicarás los valores de temperatura detectados por el Wio Terminal a través de MQTT para que puedan ser utilizados posteriormente para calcular GDD.

## Publicar la temperatura

Una vez que se haya leído la temperatura, se puede publicar a través de MQTT a algún código 'servidor' que leerá los valores y los almacenará listos para ser utilizados en un cálculo de GDD. Los microcontroladores no leen la hora de Internet ni rastrean el tiempo con un reloj en tiempo real de forma predeterminada; el dispositivo necesita ser programado para hacerlo, suponiendo que tenga el hardware necesario.

Para simplificar las cosas en esta lección, el tiempo no se enviará junto con los datos del sensor; en su lugar, puede ser agregado por el código del servidor más tarde cuando reciba los mensajes.

### Tarea

Programa el dispositivo para publicar los datos de temperatura.

1. Abre el proyecto `temperature-sensor` de Wio Terminal.

1. Repite los pasos que realizaste en la lección 4 para conectarte a MQTT y enviar telemetría. Utilizarás el mismo broker público de Mosquitto.

    Los pasos para esto son:

    - Agregar las bibliotecas Seeed WiFi y MQTT al archivo `.ini`.
    - Agregar el archivo de configuración y el código para conectarse a WiFi.
    - Agregar el código para conectarse al broker MQTT.
    - Agregar el código para publicar telemetría.

    > ⚠️ Consulta las [instrucciones para conectarte a MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) y las [instrucciones para enviar telemetría](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) de la lección 4 si es necesario.

1. Asegúrate de que el `CLIENT_NAME` en el archivo de encabezado `config.h` refleje este proyecto:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Para la telemetría, en lugar de enviar un valor de luz, envía el valor de temperatura leído del sensor DHT en una propiedad del documento JSON llamada `temperature` cambiando la función `loop` en `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. El valor de la temperatura no necesita ser leído con mucha frecuencia, ya que no cambiará mucho en un corto período de tiempo. Por lo tanto, establece el `delay` en la función `loop` a 10 minutos:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 La función `delay` toma el tiempo en milisegundos, por lo que para hacerlo más fácil de leer, el valor se pasa como el resultado de un cálculo. 1,000ms en un segundo, 60s en un minuto, así que 10 x (60s en un minuto) x (1000ms en un segundo) da un retraso de 10 minutos.

1. Carga esto en tu Wio Terminal y utiliza el monitor serial para ver la temperatura siendo enviada al broker MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Puedes encontrar este código en la carpeta [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Has publicado exitosamente la temperatura como telemetría desde tu dispositivo.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.