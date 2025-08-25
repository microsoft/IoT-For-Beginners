<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-25T21:54:11+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "pt"
}
-->
# Controle a sua luz noturna pela Internet - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, irá subscrever comandos enviados de um broker MQTT para o seu Raspberry Pi ou dispositivo IoT virtual.

## Subscrever comandos

O próximo passo é subscrever os comandos enviados pelo broker MQTT e responder a eles.

### Tarefa

Subscrever comandos.

1. Abra o projeto da luz noturna no VS Code.

1. Se estiver a usar um dispositivo IoT virtual, certifique-se de que o terminal está a executar o ambiente virtual. Se estiver a usar um Raspberry Pi, não estará a usar um ambiente virtual.

1. Adicione o seguinte código após as definições de `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    O `server_command_topic` é o tópico MQTT ao qual o dispositivo irá subscrever para receber comandos para o LED.

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

    Este código define uma função, `handle_command`, que lê uma mensagem como um documento JSON e procura o valor da propriedade `led_on`. Se estiver definido como `True`, o LED será ligado; caso contrário, será desligado.

    O cliente MQTT subscreve o tópico no qual o servidor enviará mensagens e define a função `handle_command` para ser chamada quando uma mensagem for recebida.

    > 💁 O handler `on_message` é chamado para todos os tópicos subscritos. Se mais tarde escrever código que escute múltiplos tópicos, pode obter o tópico ao qual a mensagem foi enviada a partir do objeto `message` passado para a função handler.

1. Execute o código da mesma forma que executou o código da parte anterior da tarefa. Se estiver a usar um dispositivo IoT virtual, certifique-se de que a aplicação CounterFit está a funcionar e que o sensor de luz e o LED foram criados nos pinos corretos.

1. Ajuste os níveis de luz detetados pelo seu dispositivo físico ou virtual. As mensagens recebidas e os comandos enviados serão escritos no terminal. O LED também será ligado e desligado dependendo do nível de luz.

> 💁 Pode encontrar este código na pasta [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) ou na pasta [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Conseguiu programar o seu dispositivo para responder a comandos de um broker MQTT com sucesso.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.