# Temperatura de publicação - Virtual IoT Hardware e Raspberry Pi

Nesta parte da lição, você publicará os valores de temperatura detectados pelo Raspberry Pi ou Virtual IoT Device sobre MQTT para que possam ser usados posteriormente para calcular o GDD.

## Publica a temperatura

Uma vez que a temperatura tenha sido lida, ela pode ser publicada no MQTT para algum código 'servidor' que lerá os valores e os armazenará prontos para serem usados para um cálculo de GDD.

### Tarefa - publicar a temperatura

Programe o dispositivo para publicar os dados de temperatura.

1. Abra o projeto do aplicativo `temperature-sensor` se ainda não estiver aberto

1. Repita as etapas que você fez na lição 4 para se conectar ao MQTT e enviar a telemetria. Você estará usando o mesmo broker público do Mosquitto.

     Os passos para isso são:

     - Adicione o pacote pip MQTT
     - Adicione o código para se conectar ao broker MQTT
     - Adicione o código para publicar a telemetria

    > ⚠️ Consulte as [instruções para conectar-se ao MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) e as [instruções para enviar telemetry](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) da lição 4, se necessário.

1. Certifique-se de que o `client_name` reflita este nome de projeto:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Para a telemetria, em vez de enviar um valor de luz, envie o valor de temperatura lido do sensor DHT em uma propriedade no documento JSON chamada `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. O valor da temperatura não precisa ser lido com muita frequência - não mudará muito em um curto espaço de tempo, então defina o `time.sleep` para 10 minutos:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 A função `sleep` leva o tempo em segundos, então para facilitar a leitura o valor é passado como resultado de um cálculo. 60s em um minuto, então 10x (60s em um minuto) dá um atraso de 10 minutos.

1. Execute o código da mesma forma que você executou o código da parte anterior da atribuição. Se você estiver usando um dispositivo IoT virtual, verifique se o aplicativo CounterFit está em execução e se os sensores de umidade e temperatura foram criados nos pinos corretos.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Você pode encontrar esse código na pasta [code-publish-temperature/virtual-device](code-publish-temperature/virtual-device) ou na pasta [code-publish-temperature/pi](code-publish-temperature/pi).

😀 Você publicou com sucesso a temperatura como telemetria do seu dispositivo.
