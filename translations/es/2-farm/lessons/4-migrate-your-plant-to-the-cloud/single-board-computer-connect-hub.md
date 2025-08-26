<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-26T14:50:50+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "es"
}
-->
# Conecta tu dispositivo IoT a la nube - Hardware IoT virtual y Raspberry Pi

En esta parte de la lección, conectarás tu dispositivo IoT virtual o Raspberry Pi a tu IoT Hub para enviar telemetría y recibir comandos.

## Conecta tu dispositivo al IoT Hub

El siguiente paso es conectar tu dispositivo al IoT Hub.

### Tarea - conectar al IoT Hub

1. Abre la carpeta `soil-moisture-sensor` en VS Code. Asegúrate de que el entorno virtual esté ejecutándose en la terminal si estás utilizando un dispositivo IoT virtual.

1. Instala algunos paquetes adicionales de Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` es una biblioteca para comunicarse con tu IoT Hub.

1. Agrega las siguientes importaciones en la parte superior del archivo `app.py`, debajo de las importaciones existentes:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Este código importa el SDK para comunicarse con tu IoT Hub.

1. Elimina la línea `import paho.mqtt.client as mqtt`, ya que esta biblioteca ya no es necesaria. Elimina todo el código relacionado con MQTT, incluidos los nombres de los temas, todo el código que utiliza `mqtt_client` y la función `handle_command`. Conserva el bucle `while True:`, pero elimina la línea `mqtt_client.publish` de este bucle.

1. Agrega el siguiente código debajo de las declaraciones de importación:

    ```python
    connection_string = "<connection string>"
    ```

    Sustituye `<connection string>` por la cadena de conexión que recuperaste para el dispositivo anteriormente en esta lección.

    > 💁 Esto no es una buena práctica. Las cadenas de conexión nunca deben almacenarse en el código fuente, ya que pueden ser registradas en el control de código fuente y encontradas por cualquiera. Estamos haciendo esto aquí por simplicidad. Idealmente, deberías usar algo como una variable de entorno y una herramienta como [`python-dotenv`](https://pypi.org/project/python-dotenv/). Aprenderás más sobre esto en una lección futura.

1. Debajo de este código, agrega lo siguiente para crear un objeto cliente del dispositivo que pueda comunicarse con el IoT Hub y conectarlo:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Ejecuta este código. Verás que tu dispositivo se conecta.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Enviar telemetría

Ahora que tu dispositivo está conectado, puedes enviar telemetría al IoT Hub en lugar del broker MQTT.

### Tarea - enviar telemetría

1. Agrega el siguiente código dentro del bucle `while True`, justo antes de la pausa:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Este código crea un `Message` de IoT Hub que contiene la lectura de humedad del suelo como una cadena JSON, y luego lo envía al IoT Hub como un mensaje de dispositivo a nube.

## Manejar comandos

Tu dispositivo necesita manejar un comando del código del servidor para controlar el relé. Esto se envía como una solicitud de método directo.

## Tarea - manejar una solicitud de método directo

1. Agrega el siguiente código antes del bucle `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Esto define un método, `handle_method_request`, que será llamado cuando el IoT Hub invoque un método directo. Cada método directo tiene un nombre, y este código espera un método llamado `relay_on` para encender el relé, y `relay_off` para apagarlo.

    > 💁 Esto también podría implementarse en una única solicitud de método directo, pasando el estado deseado del relé en un payload que puede ser enviado con la solicitud del método y estar disponible desde el objeto `request`.

1. Los métodos directos requieren una respuesta para informar al código que los invocó que han sido manejados. Agrega el siguiente código al final de la función `handle_method_request` para crear una respuesta a la solicitud:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Este código envía una respuesta a la solicitud de método directo con un código de estado HTTP 200, y la envía de vuelta al IoT Hub.

1. Agrega el siguiente código debajo de esta definición de función:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Este código indica al cliente del IoT Hub que llame a la función `handle_method_request` cuando se invoque un método directo.

> 💁 Puedes encontrar este código en la carpeta [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) o [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 ¡Tu programa del sensor de humedad del suelo está conectado a tu IoT Hub!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.