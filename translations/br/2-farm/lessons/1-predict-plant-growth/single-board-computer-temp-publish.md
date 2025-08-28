<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T04:13:07+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "br"
}
-->
# Publicar temperatura - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, você irá publicar os valores de temperatura detectados pelo Raspberry Pi ou Dispositivo IoT Virtual via MQTT, para que possam ser usados posteriormente no cálculo de GDD.

## Publicar a temperatura

Depois que a temperatura for lida, ela pode ser publicada via MQTT para algum código 'servidor' que irá ler os valores e armazená-los, prontos para serem usados no cálculo de GDD.

### Tarefa - publicar a temperatura

Programe o dispositivo para publicar os dados de temperatura.

1. Abra o projeto do aplicativo `temperature-sensor` se ele ainda não estiver aberto.

1. Repita os passos que você realizou na lição 4 para se conectar ao MQTT e enviar telemetria. Você usará o mesmo broker público do Mosquitto.

    Os passos para isso são:

    - Adicionar o pacote pip do MQTT
    - Adicionar o código para se conectar ao broker MQTT
    - Adicionar o código para publicar telemetria

    > ⚠️ Consulte as [instruções para se conectar ao MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) e as [instruções para enviar telemetria](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) da lição 4, se necessário.

1. Certifique-se de que o `client_name` reflete o nome deste projeto:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Para a telemetria, em vez de enviar um valor de luz, envie o valor de temperatura lido do sensor DHT em uma propriedade no documento JSON chamada `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. O valor da temperatura não precisa ser lido com muita frequência - ele não mudará muito em um curto período de tempo, então configure o `time.sleep` para 10 minutos:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 A função `sleep` recebe o tempo em segundos, então, para facilitar a leitura, o valor é passado como o resultado de um cálculo. São 60s em um minuto, então 10 x (60s em um minuto) resulta em um atraso de 10 minutos.

1. Execute o código da mesma forma que você executou o código da parte anterior da tarefa. Se você estiver usando um dispositivo IoT virtual, certifique-se de que o aplicativo CounterFit esteja em execução e que os sensores de umidade e temperatura tenham sido criados nos pinos corretos.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Você pode encontrar este código na pasta [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) ou na pasta [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Você publicou com sucesso a temperatura como telemetria do seu dispositivo.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.