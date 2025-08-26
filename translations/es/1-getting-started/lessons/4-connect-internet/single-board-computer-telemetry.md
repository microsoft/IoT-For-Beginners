<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-26T14:56:54+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "es"
}
-->
# Controla tu luz nocturna a través de Internet - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, enviarás telemetría con niveles de luz desde tu Raspberry Pi o dispositivo IoT virtual a un broker MQTT.

## Publicar telemetría

El siguiente paso es crear un documento JSON con telemetría y enviarlo al broker MQTT.

### Tarea

Publica telemetría en el broker MQTT.

1. Abre el proyecto de luz nocturna en VS Code.

1. Si estás utilizando un dispositivo IoT virtual, asegúrate de que el terminal esté ejecutando el entorno virtual. Si estás utilizando una Raspberry Pi, no estarás usando un entorno virtual.

1. Agrega la siguiente importación al inicio del archivo `app.py`:

    ```python
    import json
    ```

    La biblioteca `json` se utiliza para codificar la telemetría como un documento JSON.

1. Agrega lo siguiente después de la declaración de `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    El `client_telemetry_topic` es el tema MQTT al que el dispositivo publicará los niveles de luz.

1. Reemplaza el contenido del bucle `while True:` al final del archivo con lo siguiente:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Este código empaqueta el nivel de luz en un documento JSON y lo publica en el broker MQTT. Luego, se detiene por un momento para reducir la frecuencia con la que se envían los mensajes.

1. Ejecuta el código de la misma manera que ejecutaste el código de la parte anterior de la tarea. Si estás utilizando un dispositivo IoT virtual, asegúrate de que la aplicación CounterFit esté ejecutándose y que el sensor de luz y el LED hayan sido creados en los pines correctos.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Puedes encontrar este código en la carpeta [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) o en la carpeta [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Has enviado telemetría desde tu dispositivo con éxito.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.