<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-26T15:00:59+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "es"
}
-->
# Controla tu luz nocturna a través de Internet - Hardware IoT Virtual y Raspberry Pi

El dispositivo IoT necesita ser programado para comunicarse con *test.mosquitto.org* utilizando MQTT, con el fin de enviar valores de telemetría basados en la lectura del sensor de luz y recibir comandos para controlar el LED.

En esta parte de la lección, conectarás tu Raspberry Pi o dispositivo IoT virtual a un broker MQTT.

## Instalar el paquete del cliente MQTT

Para comunicarte con el broker MQTT, necesitas instalar una biblioteca MQTT como paquete de pip, ya sea en tu Raspberry Pi o en tu entorno virtual si estás utilizando un dispositivo virtual.

### Tarea

Instala el paquete pip

1. Abre el proyecto de luz nocturna en VS Code.

1. Si estás utilizando un dispositivo IoT virtual, asegúrate de que la terminal esté ejecutando el entorno virtual. Si estás utilizando una Raspberry Pi, no estarás usando un entorno virtual.

1. Ejecuta el siguiente comando para instalar el paquete pip de MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Programa el dispositivo

El dispositivo está listo para ser programado.

### Tarea

Escribe el código del dispositivo.

1. Agrega la siguiente importación al inicio del archivo `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    La biblioteca `paho.mqtt.client` permite que tu aplicación se comunique mediante MQTT.

1. Agrega el siguiente código después de las definiciones del sensor de luz y el LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Reemplaza `<ID>` con un ID único que será utilizado como el nombre de este cliente del dispositivo y, más adelante, para los temas que este dispositivo publique y a los que se suscriba. El broker *test.mosquitto.org* es público y es utilizado por muchas personas, incluidos otros estudiantes que están trabajando en esta tarea. Tener un nombre único para el cliente MQTT y nombres únicos para los temas asegura que tu código no entre en conflicto con el de otros. También necesitarás este ID cuando crees el código del servidor más adelante en esta tarea.

    > 💁 Puedes usar un sitio web como [GUIDGen](https://www.guidgen.com) para generar un ID único.

    El `client_name` es un nombre único para este cliente MQTT en el broker.

1. Agrega el siguiente código debajo de este nuevo código para crear un objeto cliente MQTT y conectarte al broker MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Este código crea el objeto cliente, se conecta al broker MQTT público y comienza un bucle de procesamiento que se ejecuta en un hilo en segundo plano, escuchando mensajes en cualquier tema suscrito.

1. Ejecuta el código de la misma manera que ejecutaste el código de la parte anterior de la tarea. Si estás utilizando un dispositivo IoT virtual, asegúrate de que la aplicación CounterFit esté ejecutándose y que el sensor de luz y el LED hayan sido creados en los pines correctos.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Puedes encontrar este código en la carpeta [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) o en la carpeta [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Has conectado exitosamente tu dispositivo a un broker MQTT.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.