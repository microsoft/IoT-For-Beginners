<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-25T21:18:19+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "pt"
}
-->
# Publicar temperatura - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, irá publicar os valores de temperatura detetados pelo Raspberry Pi ou Dispositivo IoT Virtual via MQTT, para que possam ser utilizados posteriormente no cálculo do GDD.

## Publicar a temperatura

Depois de ler a temperatura, pode publicá-la via MQTT para algum código 'servidor' que irá ler os valores e armazená-los, prontos para serem usados no cálculo do GDD.

### Tarefa - publicar a temperatura

Programe o dispositivo para publicar os dados de temperatura.

1. Abra o projeto da aplicação `temperature-sensor` caso ainda não esteja aberto.

1. Repita os passos que realizou na lição 4 para se conectar ao MQTT e enviar telemetria. Irá utilizar o mesmo broker público Mosquitto.

    Os passos para isso são:

    - Adicionar o pacote pip do MQTT
    - Adicionar o código para se conectar ao broker MQTT
    - Adicionar o código para publicar telemetria

    > ⚠️ Consulte as [instruções para se conectar ao MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) e as [instruções para enviar telemetria](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) da lição 4, se necessário.

1. Certifique-se de que o `client_name` reflete o nome deste projeto:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Para a telemetria, em vez de enviar um valor de luz, envie o valor de temperatura lido do sensor DHT numa propriedade do documento JSON chamada `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. O valor da temperatura não precisa de ser lido com muita frequência - não irá mudar muito num curto espaço de tempo, por isso defina o `time.sleep` para 10 minutos:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 A função `sleep` recebe o tempo em segundos, por isso, para facilitar a leitura, o valor é passado como resultado de um cálculo. 60s num minuto, então 10 x (60s num minuto) dá um atraso de 10 minutos.

1. Execute o código da mesma forma que executou o código da parte anterior da tarefa. Se estiver a usar um dispositivo IoT virtual, certifique-se de que a aplicação CounterFit está a funcionar e que os sensores de humidade e temperatura foram criados nos pinos corretos.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Pode encontrar este código na pasta [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) ou na pasta [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Conseguiu publicar com sucesso a temperatura como telemetria a partir do seu dispositivo.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se uma tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.