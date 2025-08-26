<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-26T14:29:04+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "es"
}
-->
# Publicar temperatura - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, publicarás los valores de temperatura detectados por el Raspberry Pi o el Dispositivo IoT Virtual a través de MQTT para que puedan ser utilizados posteriormente en el cálculo de GDD.

## Publicar la temperatura

Una vez que se haya leído la temperatura, se puede publicar a través de MQTT a algún código 'servidor' que leerá los valores y los almacenará listos para ser utilizados en un cálculo de GDD.

### Tarea - publicar la temperatura

Programa el dispositivo para publicar los datos de temperatura.

1. Abre el proyecto de la aplicación `temperature-sensor` si aún no está abierto.

1. Repite los pasos que realizaste en la lección 4 para conectarte a MQTT y enviar telemetría. Utilizarás el mismo broker público de Mosquitto.

    Los pasos para esto son:

    - Agregar el paquete pip de MQTT.
    - Agregar el código para conectarte al broker MQTT.
    - Agregar el código para publicar telemetría.

    > ⚠️ Consulta las [instrucciones para conectarte a MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) y las [instrucciones para enviar telemetría](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) de la lección 4 si es necesario.

1. Asegúrate de que el `client_name` refleje el nombre de este proyecto:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Para la telemetría, en lugar de enviar un valor de luz, envía el valor de temperatura leído del sensor DHT en una propiedad del documento JSON llamada `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. No es necesario leer el valor de temperatura con mucha frecuencia, ya que no cambiará mucho en un corto período de tiempo. Por lo tanto, establece el `time.sleep` en 10 minutos:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 La función `sleep` toma el tiempo en segundos, por lo que para hacerlo más fácil de leer, el valor se pasa como el resultado de un cálculo. 60 segundos en un minuto, así que 10 x (60 segundos en un minuto) da un retraso de 10 minutos.

1. Ejecuta el código de la misma manera que ejecutaste el código de la parte anterior de la tarea. Si estás utilizando un dispositivo IoT virtual, asegúrate de que la aplicación CounterFit esté ejecutándose y que los sensores de humedad y temperatura hayan sido creados en los pines correctos.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Puedes encontrar este código en la carpeta [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) o en la carpeta [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Has publicado exitosamente la temperatura como telemetría desde tu dispositivo.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.