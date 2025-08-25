<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-25T21:47:15+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "pt"
}
-->
# Conecte o seu dispositivo IoT à nuvem - Wio Terminal

Nesta parte da lição, irá conectar o seu Wio Terminal ao IoT Hub para enviar telemetria e receber comandos.

## Conectar o dispositivo ao IoT Hub

O próximo passo é conectar o seu dispositivo ao IoT Hub.

### Tarefa - conectar ao IoT Hub

1. Abra o projeto `soil-moisture-sensor` no VS Code.

1. Abra o ficheiro `platformio.ini`. Remova a dependência da biblioteca `knolleary/PubSubClient`. Esta era usada para conectar ao broker MQTT público e não é necessária para conectar ao IoT Hub.

1. Adicione as seguintes dependências de biblioteca:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    A biblioteca `Seeed Arduino RTC` fornece código para interagir com um relógio em tempo real no Wio Terminal, usado para acompanhar o tempo. As restantes bibliotecas permitem que o seu dispositivo IoT se conecte ao IoT Hub.

1. Adicione o seguinte ao final do ficheiro `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Isto define uma flag do compilador necessária ao compilar o código do Arduino IoT Hub.

1. Abra o ficheiro de cabeçalho `config.h`. Remova todas as configurações de MQTT e adicione a seguinte constante para a string de conexão do dispositivo:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Substitua `<connection string>` pela string de conexão do seu dispositivo que copiou anteriormente.

1. A conexão ao IoT Hub utiliza um token baseado no tempo. Isto significa que o dispositivo IoT precisa de saber a hora atual. Diferentemente de sistemas operativos como Windows, macOS ou Linux, os microcontroladores não sincronizam automaticamente a hora atual pela Internet. Por isso, será necessário adicionar código para obter a hora atual de um servidor [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Depois de obter a hora, esta pode ser armazenada num relógio em tempo real no Wio Terminal, permitindo que a hora correta seja solicitada posteriormente, assumindo que o dispositivo não perde energia. Adicione um novo ficheiro chamado `ntp.h` com o seguinte código:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Os detalhes deste código estão fora do âmbito desta lição. Ele define uma função chamada `initTime` que obtém a hora atual de um servidor NTP e usa-a para configurar o relógio no Wio Terminal.

1. Abra o ficheiro `main.cpp` e remova todo o código MQTT, incluindo o ficheiro de cabeçalho `PubSubClient.h`, a declaração da variável `PubSubClient`, os métodos `reconnectMQTTClient` e `createMQTTClient`, e quaisquer chamadas a estas variáveis e métodos. Este ficheiro deve conter apenas código para conectar ao WiFi, obter a humidade do solo e criar um documento JSON com esta informação.

1. Adicione as seguintes diretivas `#include` ao topo do ficheiro `main.cpp` para incluir os ficheiros de cabeçalho das bibliotecas do IoT Hub e para configurar a hora:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Adicione a seguinte chamada ao final da função `setup` para configurar a hora atual:

    ```cpp
    initTime();
    ```

1. Adicione a seguinte declaração de variável ao topo do ficheiro, logo abaixo das diretivas de inclusão:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Isto declara um `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, um identificador para uma conexão ao IoT Hub.

1. Abaixo disso, adicione o seguinte código:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Isto declara uma função de callback que será chamada quando a conexão ao IoT Hub mudar de estado, como conectar ou desconectar. O estado é enviado para a porta serial.

1. Abaixo disso, adicione uma função para conectar ao IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Este código inicializa o código da biblioteca do IoT Hub e cria uma conexão usando a string de conexão no ficheiro de cabeçalho `config.h`. Esta conexão é baseada em MQTT. Se a conexão falhar, isso será enviado para a porta serial - se vir isto na saída, verifique a string de conexão. Finalmente, o callback de estado da conexão é configurado.

1. Chame esta função na função `setup` abaixo da chamada para `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Tal como com o cliente MQTT, este código funciona numa única thread, por isso precisa de tempo para processar mensagens enviadas pelo hub e para o hub. Adicione o seguinte ao topo da função `loop` para fazer isto:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Compile e carregue este código. Verá a conexão no monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Na saída, pode ver a hora NTP a ser obtida, seguida pela conexão do cliente do dispositivo. Pode demorar alguns segundos para conectar, por isso pode ver a humidade do solo na saída enquanto o dispositivo está a conectar.

    > 💁 Pode converter o tempo UNIX do NTP para uma versão mais legível usando um site como [unixtimestamp.com](https://www.unixtimestamp.com)

## Enviar telemetria

Agora que o seu dispositivo está conectado, pode enviar telemetria para o IoT Hub em vez do broker MQTT.

### Tarefa - enviar telemetria

1. Adicione a seguinte função acima da função `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Este código cria uma mensagem do IoT Hub a partir de uma string passada como parâmetro, envia-a para o hub e, em seguida, limpa o objeto da mensagem.

1. Chame este código na função `loop`, logo após a linha onde a telemetria é enviada para a porta serial:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Processar comandos

O seu dispositivo precisa de processar um comando do código do servidor para controlar o relé. Este é enviado como uma solicitação de método direto.

### Tarefa - processar uma solicitação de método direto

1. Adicione o seguinte código antes da função `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Este código define uma função de callback que a biblioteca do IoT Hub pode chamar quando recebe uma solicitação de método direto. O método solicitado é enviado no parâmetro `method_name`. Esta função imprime o método chamado na porta serial e, em seguida, liga ou desliga o relé dependendo do nome do método.

    > 💁 Isto também poderia ser implementado num único pedido de método direto, passando o estado desejado do relé num payload que pode ser enviado com o pedido de método e disponível no parâmetro `payload`.

1. Adicione o seguinte código ao final da função `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    As solicitações de método direto precisam de uma resposta, e a resposta é composta por duas partes - uma resposta em texto e um código de retorno. Este código criará um resultado como o seguinte documento JSON:

    ```JSON
    {
        "Result": ""
    }
    ```

    Este é então copiado para o parâmetro `response`, e o tamanho desta resposta é definido no parâmetro `response_size`. Este código retorna `IOTHUB_CLIENT_OK` para indicar que o método foi processado corretamente.

1. Configure o callback adicionando o seguinte ao final da função `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. A função `loop` chamará a função `IoTHubDeviceClient_LL_DoWork` para processar eventos enviados pelo IoT Hub. Isto é chamado apenas a cada 10 segundos devido ao `delay`, o que significa que os métodos diretos são processados apenas a cada 10 segundos. Para tornar isto mais eficiente, o atraso de 10 segundos pode ser implementado como vários atrasos mais curtos, chamando `IoTHubDeviceClient_LL_DoWork` cada vez. Para fazer isto, adicione o seguinte código acima da função `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Este código irá fazer um loop repetidamente, chamando `IoTHubDeviceClient_LL_DoWork` e atrasando por 100ms cada vez. Fará isto tantas vezes quanto necessário para atrasar pelo tempo dado no parâmetro `delay_time`. Isto significa que o dispositivo está a esperar no máximo 100ms para processar solicitações de método direto.

1. Na função `loop`, remova a chamada para `IoTHubDeviceClient_LL_DoWork` e substitua a chamada `delay(10000)` pelo seguinte para chamar esta nova função:

    ```cpp
    work_delay(10000);
    ```

> 💁 Pode encontrar este código na pasta [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 O programa do sensor de humidade do solo está conectado ao seu IoT Hub!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.