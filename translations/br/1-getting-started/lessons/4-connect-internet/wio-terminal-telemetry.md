<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T03:32:39+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "br"
}
-->
# Controle sua luz noturna pela Internet - Wio Terminal

Nesta parte da lição, você enviará telemetria com os níveis de luz do seu Wio Terminal para o broker MQTT.

## Instale as bibliotecas JSON para Arduino

Uma maneira popular de enviar mensagens via MQTT é usando JSON. Existe uma biblioteca Arduino para JSON que facilita a leitura e escrita de documentos JSON.

### Tarefa

Instale a biblioteca Arduino JSON.

1. Abra o projeto da luz noturna no VS Code.

1. Adicione a seguinte linha adicional à lista `lib_deps` no arquivo `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Isso importa [ArduinoJson](https://arduinojson.org), uma biblioteca JSON para Arduino.

## Publicar telemetria

O próximo passo é criar um documento JSON com a telemetria e enviá-lo para o broker MQTT.

### Tarefa - publicar telemetria

Publique telemetria no broker MQTT.

1. Adicione o seguinte código ao final do arquivo `config.h` para definir o nome do tópico de telemetria para o broker MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    O `CLIENT_TELEMETRY_TOPIC` é o tópico no qual o dispositivo publicará os níveis de luz.

1. Abra o arquivo `main.cpp`.

1. Adicione a seguinte diretiva `#include` ao topo do arquivo:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Adicione o seguinte código dentro da função `loop`, logo antes do `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Este código lê o nível de luz e cria um documento JSON usando ArduinoJson contendo este nível. Em seguida, ele é serializado para uma string e publicado no tópico de telemetria MQTT pelo cliente MQTT.

1. Faça o upload do código para o seu Wio Terminal e use o Monitor Serial para ver os níveis de luz sendo enviados para o broker MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Você pode encontrar este código na pasta [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Você enviou com sucesso a telemetria do seu dispositivo.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.