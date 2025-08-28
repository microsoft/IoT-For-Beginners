<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T04:12:21+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "br"
}
-->
# Publicar temperatura - Wio Terminal

Nesta parte da lição, você irá publicar os valores de temperatura detectados pelo Wio Terminal via MQTT para que possam ser usados posteriormente no cálculo de GDD.

## Publicar a temperatura

Depois que a temperatura for lida, ela pode ser publicada via MQTT para algum código 'servidor' que irá ler os valores e armazená-los, prontos para serem usados no cálculo de GDD. Microcontroladores não leem o horário da Internet nem acompanham o tempo com um relógio em tempo real por padrão; o dispositivo precisa ser programado para isso, assumindo que possui o hardware necessário.

Para simplificar as coisas nesta lição, o horário não será enviado com os dados do sensor; em vez disso, ele pode ser adicionado pelo código do servidor mais tarde, quando as mensagens forem recebidas.

### Tarefa

Programe o dispositivo para publicar os dados de temperatura.

1. Abra o projeto `temperature-sensor` do Wio Terminal.

1. Repita os passos que você realizou na lição 4 para se conectar ao MQTT e enviar telemetria. Você usará o mesmo broker público do Mosquitto.

    Os passos para isso são:

    - Adicionar as bibliotecas Seeed WiFi e MQTT ao arquivo `.ini`
    - Adicionar o arquivo de configuração e o código para conectar ao WiFi
    - Adicionar o código para conectar ao broker MQTT
    - Adicionar o código para publicar telemetria

    > ⚠️ Consulte as [instruções para conectar ao MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) e as [instruções para enviar telemetria](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) da lição 4, se necessário.

1. Certifique-se de que o `CLIENT_NAME` no arquivo de cabeçalho `config.h` reflete este projeto:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Para a telemetria, em vez de enviar um valor de luz, envie o valor de temperatura lido do sensor DHT em uma propriedade no documento JSON chamada `temperature`, alterando a função `loop` no arquivo `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. O valor da temperatura não precisa ser lido com muita frequência - ele não mudará muito em um curto período de tempo, então configure o `delay` na função `loop` para 10 minutos:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 A função `delay` recebe o tempo em milissegundos, então, para facilitar a leitura, o valor é passado como o resultado de um cálculo. 1.000ms em um segundo, 60s em um minuto, então 10 x (60s em um minuto) x (1.000ms em um segundo) resulta em um atraso de 10 minutos.

1. Envie este código para o seu Wio Terminal e use o monitor serial para ver a temperatura sendo enviada ao broker MQTT.

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

> 💁 Você pode encontrar este código na pasta [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Você publicou com sucesso a temperatura como telemetria do seu dispositivo.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte oficial. Para informações críticas, recomenda-se a tradução profissional feita por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.