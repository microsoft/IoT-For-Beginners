<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-25T21:20:19+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "pt"
}
-->
# Publicar temperatura - Wio Terminal

Nesta parte da lição, irá publicar os valores de temperatura detetados pelo Wio Terminal através de MQTT, para que possam ser usados mais tarde no cálculo do GDD.

## Publicar a temperatura

Depois de ler a temperatura, esta pode ser publicada via MQTT para algum código 'servidor' que irá ler os valores e armazená-los, prontos para serem usados no cálculo do GDD. Os microcontroladores não obtêm a hora da Internet nem acompanham o tempo com um relógio em tempo real por padrão; o dispositivo precisa ser programado para isso, assumindo que possui o hardware necessário.

Para simplificar as coisas nesta lição, a hora não será enviada com os dados do sensor; em vez disso, pode ser adicionada pelo código do servidor mais tarde, quando este receber as mensagens.

### Tarefa

Programar o dispositivo para publicar os dados de temperatura.

1. Abra o projeto `temperature-sensor` do Wio Terminal.

1. Repita os passos que realizou na lição 4 para se conectar ao MQTT e enviar telemetria. Irá usar o mesmo broker público Mosquitto.

    Os passos para isso são:

    - Adicionar as bibliotecas Seeed WiFi e MQTT ao ficheiro `.ini`
    - Adicionar o ficheiro de configuração e o código para se conectar ao WiFi
    - Adicionar o código para se conectar ao broker MQTT
    - Adicionar o código para publicar telemetria

    > ⚠️ Consulte as [instruções para se conectar ao MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) e as [instruções para enviar telemetria](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) da lição 4, se necessário.

1. Certifique-se de que o `CLIENT_NAME` no ficheiro de cabeçalho `config.h` reflete este projeto:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Para a telemetria, em vez de enviar um valor de luz, envie o valor de temperatura lido do sensor DHT numa propriedade do documento JSON chamada `temperature`, alterando a função `loop` no `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. O valor da temperatura não precisa de ser lido com muita frequência - não mudará muito num curto espaço de tempo, por isso defina o `delay` na função `loop` para 10 minutos:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 A função `delay` recebe o tempo em milissegundos, por isso, para facilitar a leitura, o valor é passado como o resultado de um cálculo. 1.000ms num segundo, 60s num minuto, então 10 x (60s num minuto) x (1.000ms num segundo) dá um atraso de 10 minutos.

1. Carregue este código para o seu Wio Terminal e use o monitor serial para ver a temperatura a ser enviada para o broker MQTT.

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

> 💁 Pode encontrar este código na pasta [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Conseguiu publicar com sucesso a temperatura como telemetria a partir do seu dispositivo.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.