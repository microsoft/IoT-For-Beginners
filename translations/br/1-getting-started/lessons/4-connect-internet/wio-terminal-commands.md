<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T03:30:51+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "br"
}
-->
# Controle sua luz noturna pela Internet - Wio Terminal

Nesta parte da lição, você irá se inscrever para receber comandos enviados de um broker MQTT para o seu Wio Terminal.

## Inscrever-se para comandos

O próximo passo é se inscrever para os comandos enviados pelo broker MQTT e responder a eles.

### Tarefa

Inscreva-se para receber comandos.

1. Abra o projeto da luz noturna no VS Code.

1. Adicione o seguinte código ao final do arquivo `config.h` para definir o nome do tópico para os comandos:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    O `SERVER_COMMAND_TOPIC` é o tópico ao qual o dispositivo se inscreverá para receber comandos para o LED.

1. Adicione a seguinte linha ao final da função `reconnectMQTTClient` para se inscrever no tópico de comandos quando o cliente MQTT for reconectado:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Adicione o seguinte código abaixo da função `reconnectMQTTClient`.

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

    Esta função será o callback que o cliente MQTT chamará quando receber uma mensagem do servidor.

    A mensagem é recebida como um array de inteiros não assinados de 8 bits, então precisa ser convertida para um array de caracteres para ser tratada como texto.

    A mensagem contém um documento JSON, que é decodificado usando a biblioteca ArduinoJson. A propriedade `led_on` do documento JSON é lida e, dependendo do valor, o LED é ligado ou desligado.

1. Adicione o seguinte código à função `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Este código define o `clientCallback` como o callback a ser chamado quando uma mensagem for recebida do broker MQTT.

    > 💁 O handler `clientCallback` é chamado para todos os tópicos aos quais você está inscrito. Se você escrever código posteriormente para ouvir múltiplos tópicos, poderá obter o tópico ao qual a mensagem foi enviada a partir do parâmetro `topic` passado para a função callback.

1. Envie o código para o seu Wio Terminal e use o Monitor Serial para ver os níveis de luz sendo enviados para o broker MQTT.

1. Ajuste os níveis de luz detectados pelo seu dispositivo físico ou virtual. Você verá mensagens sendo recebidas e comandos sendo enviados no terminal. Também verá o LED sendo ligado e desligado dependendo do nível de luz.

> 💁 Você pode encontrar este código na pasta [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Você codificou com sucesso o seu dispositivo para responder a comandos de um broker MQTT.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.