<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T04:08:30+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "br"
}
-->
# Conecte seu dispositivo IoT à nuvem - Wio Terminal

Nesta parte da lição, você conectará seu Wio Terminal ao seu IoT Hub para enviar telemetria e receber comandos.

## Conecte seu dispositivo ao IoT Hub

O próximo passo é conectar seu dispositivo ao IoT Hub.

### Tarefa - conectar ao IoT Hub

1. Abra o projeto `soil-moisture-sensor` no VS Code.

1. Abra o arquivo `platformio.ini`. Remova a dependência da biblioteca `knolleary/PubSubClient`. Esta biblioteca era usada para conectar ao broker MQTT público e não é necessária para conectar ao IoT Hub.

1. Adicione as seguintes dependências de biblioteca:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    A biblioteca `Seeed Arduino RTC` fornece código para interagir com um relógio de tempo real no Wio Terminal, usado para rastrear o tempo. As bibliotecas restantes permitem que seu dispositivo IoT se conecte ao IoT Hub.

1. Adicione o seguinte ao final do arquivo `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Isso define uma flag de compilador necessária ao compilar o código do Arduino IoT Hub.

1. Abra o arquivo de cabeçalho `config.h`. Remova todas as configurações de MQTT e adicione a seguinte constante para a string de conexão do dispositivo:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Substitua `<connection string>` pela string de conexão do seu dispositivo que você copiou anteriormente.

1. A conexão ao IoT Hub utiliza um token baseado em tempo. Isso significa que o dispositivo IoT precisa saber o horário atual. Diferentemente de sistemas operacionais como Windows, macOS ou Linux, microcontroladores não sincronizam automaticamente o horário atual pela Internet. Isso significa que você precisará adicionar código para obter o horário atual de um servidor [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Depois que o horário for obtido, ele pode ser armazenado em um relógio de tempo real no Wio Terminal, permitindo que o horário correto seja solicitado posteriormente, assumindo que o dispositivo não perca energia. Adicione um novo arquivo chamado `ntp.h` com o seguinte código:

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

    Os detalhes deste código estão fora do escopo desta lição. Ele define uma função chamada `initTime` que obtém o horário atual de um servidor NTP e o utiliza para configurar o relógio no Wio Terminal.

1. Abra o arquivo `main.cpp` e remova todo o código MQTT, incluindo o arquivo de cabeçalho `PubSubClient.h`, a declaração da variável `PubSubClient`, os métodos `reconnectMQTTClient` e `createMQTTClient`, e quaisquer chamadas para essas variáveis e métodos. Este arquivo deve conter apenas código para conectar ao WiFi, obter a umidade do solo e criar um documento JSON com esses dados.

1. Adicione as seguintes diretivas `#include` ao topo do arquivo `main.cpp` para incluir os arquivos de cabeçalho das bibliotecas do IoT Hub e para configurar o horário:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Adicione a seguinte chamada ao final da função `setup` para configurar o horário atual:

    ```cpp
    initTime();
    ```

1. Adicione a seguinte declaração de variável ao topo do arquivo, logo abaixo das diretivas de inclusão:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Isso declara um `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, um identificador para uma conexão com o IoT Hub.

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

    Isso declara uma função de callback que será chamada quando a conexão com o IoT Hub mudar de status, como conectar ou desconectar. O status é enviado para a porta serial.

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

    Este código inicializa o código da biblioteca do IoT Hub e, em seguida, cria uma conexão usando a string de conexão no arquivo de cabeçalho `config.h`. Esta conexão é baseada em MQTT. Se a conexão falhar, isso será enviado para a porta serial - se você vir isso na saída, verifique a string de conexão. Por fim, o callback de status da conexão é configurado.

1. Chame esta função na função `setup` abaixo da chamada para `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Assim como no cliente MQTT, este código é executado em uma única thread, então precisa de tempo para processar mensagens enviadas pelo hub e para o hub. Adicione o seguinte ao topo da função `loop` para fazer isso:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Compile e carregue este código. Você verá a conexão no monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Na saída, você pode ver o horário NTP sendo obtido, seguido pelo cliente do dispositivo conectando. Pode levar alguns segundos para conectar, então você pode ver a umidade do solo na saída enquanto o dispositivo está conectando.

    > 💁 Você pode converter o horário UNIX do NTP para uma versão mais legível usando um site como [unixtimestamp.com](https://www.unixtimestamp.com)

## Enviar telemetria

Agora que seu dispositivo está conectado, você pode enviar telemetria para o IoT Hub em vez do broker MQTT.

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

## Manipular comandos

Seu dispositivo precisa manipular um comando do código do servidor para controlar o relé. Isso é enviado como uma solicitação de método direto.

## Tarefa - manipular uma solicitação de método direto

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

    > 💁 Isso também poderia ser implementado em uma única solicitação de método direto, passando o estado desejado do relé em um payload que pode ser enviado com a solicitação de método e disponível no parâmetro `payload`.

1. Adicione o seguinte código ao final da função `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Solicitações de método direto precisam de uma resposta, e a resposta é composta por duas partes - uma resposta como texto e um código de retorno. Este código criará um resultado como o seguinte documento JSON:

    ```JSON
    {
        "Result": ""
    }
    ```

    Isso é então copiado no parâmetro `response`, e o tamanho desta resposta é configurado no parâmetro `response_size`. Este código então retorna `IOTHUB_CLIENT_OK` para mostrar que o método foi manipulado corretamente.

1. Configure o callback adicionando o seguinte ao final da função `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. A função `loop` chamará a função `IoTHubDeviceClient_LL_DoWork` para processar eventos enviados pelo IoT Hub. Isso é chamado apenas a cada 10 segundos devido ao `delay`, o que significa que métodos diretos são processados apenas a cada 10 segundos. Para tornar isso mais eficiente, o atraso de 10 segundos pode ser implementado como vários atrasos mais curtos, chamando `IoTHubDeviceClient_LL_DoWork` a cada vez. Para fazer isso, adicione o seguinte código acima da função `loop`:

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

    Este código fará um loop repetidamente, chamando `IoTHubDeviceClient_LL_DoWork` e atrasando por 100ms a cada vez. Ele fará isso tantas vezes quanto necessário para atrasar pelo tempo dado no parâmetro `delay_time`. Isso significa que o dispositivo está esperando no máximo 100ms para processar solicitações de método direto.

1. Na função `loop`, remova a chamada para `IoTHubDeviceClient_LL_DoWork` e substitua a chamada `delay(10000)` pelo seguinte para chamar esta nova função:

    ```cpp
    work_delay(10000);
    ```

> 💁 Você pode encontrar este código na pasta [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Seu programa de sensor de umidade do solo está conectado ao seu IoT Hub!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.