<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-25T22:01:30+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "pt"
}
-->
# Controle a sua luz noturna pela Internet - Wio Terminal

Nesta parte da lição, irá subscrever-se a comandos enviados de um broker MQTT para o seu Wio Terminal.

## Subscrever-se a comandos

O próximo passo é subscrever-se aos comandos enviados pelo broker MQTT e responder a eles.

### Tarefa

Subscrever-se a comandos.

1. Abra o projeto da luz noturna no VS Code.

1. Adicione o seguinte código ao final do ficheiro `config.h` para definir o nome do tópico para os comandos:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    O `SERVER_COMMAND_TOPIC` é o tópico ao qual o dispositivo irá subscrever-se para receber comandos para o LED.

1. Adicione a seguinte linha ao final da função `reconnectMQTTClient` para subscrever-se ao tópico de comandos quando o cliente MQTT for reconectado:

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

    A mensagem é recebida como um array de inteiros não assinados de 8 bits, por isso precisa ser convertida para um array de caracteres para ser tratada como texto.

    A mensagem contém um documento JSON, que é decodificado usando a biblioteca ArduinoJson. A propriedade `led_on` do documento JSON é lida e, dependendo do valor, o LED é ligado ou desligado.

1. Adicione o seguinte código à função `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Este código define o `clientCallback` como o callback a ser chamado quando uma mensagem for recebida do broker MQTT.

    > 💁 O handler `clientCallback` é chamado para todos os tópicos subscritos. Se mais tarde escrever código que escute múltiplos tópicos, pode obter o tópico ao qual a mensagem foi enviada a partir do parâmetro `topic` passado para a função callback.

1. Carregue o código para o seu Wio Terminal e use o Monitor Serial para ver os níveis de luz sendo enviados para o broker MQTT.

1. Ajuste os níveis de luz detetados pelo seu dispositivo físico ou virtual. Verá mensagens sendo recebidas e comandos sendo enviados no terminal. Também verá o LED sendo ligado e desligado dependendo do nível de luz.

> 💁 Pode encontrar este código na pasta [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Conseguiu programar o seu dispositivo para responder a comandos de um broker MQTT.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se uma tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.