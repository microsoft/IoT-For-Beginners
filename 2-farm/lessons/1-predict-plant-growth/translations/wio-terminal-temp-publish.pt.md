# Temperatura de publicação - Terminal Wio

Nesta parte da lição, você publicará os valores de temperatura detectados pelo Terminal Wio sobre MQTT para que possam ser usados ​​posteriormente para calcular o GDD.

## Publica a temperatura

Uma vez que a temperatura tenha sido lida, ela pode ser publicada no MQTT para algum código 'servidor' que lerá os valores e os armazenará prontos para serem usados ​​para um cálculo de GDD. Os microcontroladores não leem a hora da Internet e rastreiam a hora com um relógio em tempo real pronto para uso, o dispositivo precisa ser programado para fazer isso, desde que tenha o hardware necessário.

Para simplificar as coisas para esta lição, a hora não será enviada com os dados do sensor, mas poderá ser adicionada pelo código do servidor posteriormente quando receber as mensagens.

### Tarefa

Programe o dispositivo para publicar os dados de temperatura.

1. Abra o projeto do Terminal Wio `temperature-sensor`

1. Repita as etapas que você fez na lição 4 para se conectar ao MQTT e enviar a telemetria. Você estará usando o mesmo broker público do Mosquitto.

    Os passos para isso são:

    - Adicione as bibliotecas Seeed WiFi e MQTT ao arquivo `.ini`
    - Adicione o arquivo de configuração e o código para se conectar ao WiFi
    - Adicione o código para se conectar ao broker MQTT
    - Adicione o código para publicar a telemetria

    > ⚠️ Consulte as [instruções para se conectar ao MQTT](../../../../../1-getting-started/lessons/4-connect-internet/translations/wio-terminal-mqtt.pt.md) e as [instruções para enviar telemetria](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) da lição 4, se necessário.

1. Certifique-se de que o `CLIENT_NAME` no arquivo de cabeçalho `config.h` reflita este projeto:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Para a telemetria, em vez de enviar um valor de luz, envie o valor de temperatura lido do sensor DHT em uma propriedade no documento JSON chamada `temperature` alterando a função `loop` em `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. O valor da temperatura não precisa ser lido com muita frequência - ele não mudará muito em um curto espaço de tempo, então defina o `delay` na função `loop` para 10 minutos:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 A função `delay` leva o tempo em milissegundos, então para facilitar a leitura o valor é passado como resultado de um cálculo. 1.000ms em um segundo, 60s em um minuto, então 10 x (60s em um minuto) x (1000ms em um segundo) dá um atraso de 10 minutos.

1. Faça o upload para o seu Terminal Wio e use o monitor serial para ver a temperatura sendo enviada para o corretor MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Você pode encontrar esse código na pasta [code-publish-temperature/wio-terminal](../code-publish-temperature/wio-terminal).

😀 Você publicou com sucesso a temperatura como telemetria do seu dispositivo.
