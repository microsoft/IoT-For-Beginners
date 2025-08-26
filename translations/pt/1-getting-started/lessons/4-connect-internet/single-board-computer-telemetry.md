<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-25T21:54:38+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "pt"
}
-->
# Controle a sua luz noturna pela Internet - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, irá enviar telemetria com níveis de luz a partir do seu Raspberry Pi ou dispositivo IoT virtual para um broker MQTT.

## Publicar telemetria

O próximo passo é criar um documento JSON com telemetria e enviá-lo para o broker MQTT.

### Tarefa

Publique telemetria no broker MQTT.

1. Abra o projeto da luz noturna no VS Code.

1. Se estiver a usar um dispositivo IoT virtual, certifique-se de que o terminal está a executar o ambiente virtual. Se estiver a usar um Raspberry Pi, não estará a usar um ambiente virtual.

1. Adicione a seguinte importação ao topo do ficheiro `app.py`:

    ```python
    import json
    ```

    A biblioteca `json` é usada para codificar a telemetria como um documento JSON.

1. Adicione o seguinte após a declaração de `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    O `client_telemetry_topic` é o tópico MQTT onde o dispositivo irá publicar os níveis de luz.

1. Substitua o conteúdo do ciclo `while True:` no final do ficheiro pelo seguinte:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Este código empacota o nível de luz num documento JSON e publica-o no broker MQTT. Em seguida, faz uma pausa para reduzir a frequência com que as mensagens são enviadas.

1. Execute o código da mesma forma que executou o código na parte anterior da tarefa. Se estiver a usar um dispositivo IoT virtual, certifique-se de que a aplicação CounterFit está a funcionar e que o sensor de luz e o LED foram criados nos pinos corretos.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Pode encontrar este código na pasta [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) ou na pasta [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Conseguiu enviar telemetria a partir do seu dispositivo com sucesso.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se uma tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.