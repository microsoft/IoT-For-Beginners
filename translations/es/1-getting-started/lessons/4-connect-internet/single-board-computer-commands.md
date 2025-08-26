<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-26T14:56:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "es"
}
-->
# Controla tu luz nocturna a través de Internet - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, te suscribirás a los comandos enviados desde un broker MQTT a tu Raspberry Pi o dispositivo IoT virtual.

## Suscribirse a comandos

El siguiente paso es suscribirse a los comandos enviados desde el broker MQTT y responder a ellos.

### Tarea

Suscríbete a los comandos.

1. Abre el proyecto de la luz nocturna en VS Code.

1. Si estás utilizando un dispositivo IoT virtual, asegúrate de que la terminal esté ejecutando el entorno virtual. Si estás utilizando una Raspberry Pi, no estarás usando un entorno virtual.

1. Agrega el siguiente código después de las definiciones de `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    El `server_command_topic` es el tema MQTT al que el dispositivo se suscribirá para recibir comandos para el LED.

1. Agrega el siguiente código justo encima del bucle principal, después de la línea `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Este código define una función, `handle_command`, que lee un mensaje como un documento JSON y busca el valor de la propiedad `led_on`. Si está configurado en `True`, el LED se enciende; de lo contrario, se apaga.

    El cliente MQTT se suscribe al tema en el que el servidor enviará mensajes y establece la función `handle_command` para que se llame cuando se reciba un mensaje.

    > 💁 El controlador `on_message` se llama para todos los temas a los que se está suscrito. Si más adelante escribes código que escuche múltiples temas, puedes obtener el tema al que se envió el mensaje desde el objeto `message` que se pasa a la función del controlador.

1. Ejecuta el código de la misma manera que ejecutaste el código de la parte anterior de la tarea. Si estás utilizando un dispositivo IoT virtual, asegúrate de que la aplicación CounterFit esté en ejecución y que el sensor de luz y el LED se hayan creado en los pines correctos.

1. Ajusta los niveles de luz detectados por tu dispositivo físico o virtual. Los mensajes recibidos y los comandos enviados se escribirán en la terminal. El LED también se encenderá y apagará dependiendo del nivel de luz.

> 💁 Puedes encontrar este código en la carpeta [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) o en la carpeta [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Has codificado con éxito tu dispositivo para responder a los comandos de un broker MQTT.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.