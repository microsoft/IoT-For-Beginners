<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T03:32:18+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "br"
}
-->
# Controle sua luz noturna pela Internet - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, você irá se inscrever para receber comandos enviados de um broker MQTT para seu Raspberry Pi ou dispositivo IoT virtual.

## Inscreva-se para receber comandos

O próximo passo é se inscrever para os comandos enviados pelo broker MQTT e responder a eles.

### Tarefa

Inscreva-se para receber comandos.

1. Abra o projeto da luz noturna no VS Code.

1. Se você estiver usando um dispositivo IoT virtual, certifique-se de que o terminal está executando o ambiente virtual. Se estiver usando um Raspberry Pi, você não estará utilizando um ambiente virtual.

1. Adicione o seguinte código após as definições de `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    O `server_command_topic` é o tópico MQTT ao qual o dispositivo irá se inscrever para receber comandos para o LED.

1. Adicione o seguinte código logo acima do loop principal, após a linha `mqtt_client.loop_start()`:

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

    Este código define uma função, `handle_command`, que lê uma mensagem como um documento JSON e procura pelo valor da propriedade `led_on`. Se estiver configurada como `True`, o LED será ligado; caso contrário, será desligado.

    O cliente MQTT se inscreve no tópico em que o servidor enviará mensagens e define a função `handle_command` para ser chamada quando uma mensagem for recebida.

    > 💁 O manipulador `on_message` é chamado para todos os tópicos inscritos. Se você escrever código posteriormente que escute múltiplos tópicos, poderá obter o tópico ao qual a mensagem foi enviada a partir do objeto `message` passado para a função manipuladora.

1. Execute o código da mesma forma que executou o código da parte anterior da tarefa. Se estiver usando um dispositivo IoT virtual, certifique-se de que o aplicativo CounterFit está em execução e que o sensor de luz e o LED foram criados nos pinos corretos.

1. Ajuste os níveis de luz detectados pelo seu dispositivo físico ou virtual. As mensagens recebidas e os comandos enviados serão exibidos no terminal. O LED também será ligado e desligado dependendo do nível de luz.

> 💁 Você pode encontrar este código na pasta [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) ou na pasta [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Você codificou com sucesso seu dispositivo para responder a comandos de um broker MQTT.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.