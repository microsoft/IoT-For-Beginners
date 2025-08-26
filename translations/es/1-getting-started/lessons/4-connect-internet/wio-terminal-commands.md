<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-26T15:02:20+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "es"
}
-->
# Controla tu luz nocturna a través de Internet - Wio Terminal

En esta parte de la lección, te suscribirás a los comandos enviados desde un broker MQTT a tu Wio Terminal.

## Suscribirse a comandos

El siguiente paso es suscribirse a los comandos enviados desde el broker MQTT y responder a ellos.

### Tarea

Suscríbete a los comandos.

1. Abre el proyecto de luz nocturna en VS Code.

1. Agrega el siguiente código al final del archivo `config.h` para definir el nombre del tema para los comandos:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    El `SERVER_COMMAND_TOPIC` es el tema al que el dispositivo se suscribirá para recibir comandos de LED.

1. Agrega la siguiente línea al final de la función `reconnectMQTTClient` para suscribirte al tema de comandos cuando el cliente MQTT se reconecte:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Agrega el siguiente código debajo de la función `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Esta función será el callback que el cliente MQTT llamará cuando reciba un mensaje del servidor.

    El mensaje se recibe como un array de enteros sin signo de 8 bits, por lo que necesita ser convertido a un array de caracteres para tratarlo como texto.

    El mensaje contiene un documento JSON, y se decodifica utilizando la biblioteca ArduinoJson. La propiedad `led_on` del documento JSON se lee, y dependiendo de su valor, el LED se enciende o se apaga.

1. Agrega el siguiente código a la función `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Este código establece el `clientCallback` como el callback que se llamará cuando se reciba un mensaje del broker MQTT.

    > 💁 El manejador `clientCallback` se llama para todos los temas suscritos. Si más adelante escribes código que escucha múltiples temas, puedes obtener el tema al que se envió el mensaje desde el parámetro `topic` que se pasa a la función callback.

1. Sube el código a tu Wio Terminal y utiliza el Monitor Serial para ver los niveles de luz que se envían al broker MQTT.

1. Ajusta los niveles de luz detectados por tu dispositivo físico o virtual. Verás mensajes siendo recibidos y comandos siendo enviados en el terminal. También verás el LED encendiéndose y apagándose dependiendo del nivel de luz.

> 💁 Puedes encontrar este código en la carpeta [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Has codificado exitosamente tu dispositivo para responder a comandos de un broker MQTT.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.