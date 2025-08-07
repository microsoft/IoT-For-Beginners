# Conecte seu dispositivo IoT à nuvem - Terminal Wio

Nesta parte da lição, você conectará seu Terminal Wio ao Hub IoT para enviar telemetria e receber comandos.

## Conecte seu dispositivo ao Hub IoT

A próxima etapa é conectar seu dispositivo ao Hub IoT.

### Tarefa - conectar ao Hub IoT

1. Abra o projeto `soil-moisture-sensor` no VS Code

1. Abra o arquivo `platformio.ini`. Remova a dependência da biblioteca `knolleary/PubSubClient`. Isso foi usado para se conectar ao agente MQTT público e não é necessário para se conectar ao Hub IoT.

1. Adicione as seguintes dependências de biblioteca:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    A biblioteca `Seeed Arduino RTC` fornece código para interagir com um relógio em tempo real no Terminal Wio, usado para rastrear o tempo. As bibliotecas restantes permitem que seu dispositivo IoT se conecte ao Hub IoT.

1. Adicione o seguinte na parte inferior do arquivo `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Isso define um sinalizador do compilador que é necessário ao compilar o código do Arduino IoT Hub.

1. Abra o arquivo de cabeçalho `config.h`. Remova todas as configurações de MQTT e adicione a seguinte constante para a string de conexão do dispositivo:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Substitua `<string de conexão>` pela string de conexão do seu dispositivo que você copiou anteriormente.

1. A conexão com o Hub IoT usa um token baseado em tempo. Isso significa que o dispositivo IoT precisa saber a hora atual. Ao contrário de sistemas operacionais como Windows, macOS ou Linux, os microcontroladores não sincronizam automaticamente a hora atual pela Internet. Isso significa que você precisará adicionar código para obter a hora atual de um servidor [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Uma vez recuperada a hora, ela pode ser armazenada em um relógio de tempo real no Terminal Wio, permitindo que a hora correta seja solicitada posteriormente, desde que o dispositivo não perca energia. Adicione um novo arquivo chamado `ntp.h` com o seguinte código:

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

    Os detalhes desse código estão fora do escopo desta lição. Ele define uma função chamada `initTime` que obtém a hora atual de um servidor NTP e a usa para acertar o relógio no Terminal Wio.

1. Abra o arquivo `main.cpp` e remova todo o código MQTT, incluindo o arquivo de cabeçalho `PubSubClient.h`, a declaração da variável `PubSubClient`, os métodos `reconnectMQTTClient` e `createMQTTClient` e quaisquer chamadas para essas variáveis e métodos. Este arquivo deve conter apenas o código para se conectar ao WiFi, obter a umidade do solo e criar um documento JSON com ele.

1. Adicione as seguintes diretivas `#include` à parte superior do arquivo `main.cpp` para incluir arquivos de cabeçalho para as bibliotecas do Hub IoT e para definir a hora:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Adicione a seguinte chamada ao final da função `setup` para definir a hora atual:

    ```cpp
    initTime();
    ```

1. Adicione a seguinte declaração de variável ao topo do arquivo, logo abaixo das diretivas de inclusão:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Isso declara um `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, um identificador para uma conexão com o Hub IoT.

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

    Isso declara uma função de retorno de chamada que será chamada quando a conexão com o Hub IoT mudar de status, como conectar ou desconectar. O status é enviado para a porta serial.

1. Abaixo disso, adicione uma função para se conectar ao Hub IoT:

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

    Esse código inicializa o código da biblioteca do Hub IoT e, em seguida, cria uma conexão usando a cadeia de conexão no arquivo de cabeçalho `config.h`. Esta conexão é baseada em MQTT. Se a conexão falhar, isso é enviado para a porta serial - se você vir isso na saída, verifique a string de conexão. Finalmente, o retorno de chamada do status da conexão é configurado.

1. Chame esta função na função `setup` abaixo da chamada para `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Assim como no cliente MQTT, esse código é executado em um único encadeamento, portanto, precisa de tempo para processar as mensagens enviadas pelo hub e enviadas para o hub. Adicione o seguinte ao topo da função `loop` para fazer isso:

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

    Na saída, você pode ver a hora do NTP sendo buscada, seguida pela conexão do cliente do dispositivo. Pode levar alguns segundos para conectar, então você pode ver a umidade do solo na saída enquanto o dispositivo está se conectando.

     > 💁 Você pode converter a hora do UNIX para o NTP para uma versão mais legível usando um site como [unixtimestamp.com](https://www.unixtimestamp.com)

## Enviar telemetria

Agora que seu dispositivo está conectado, você pode enviar telemetria para o Hub IoT em vez do broker MQTT.

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

    Esse código cria uma mensagem do Hub IoT a partir de uma string passada como parâmetro, a envia para o Hub e, em seguida, limpa o objeto de mensagem.

1. Chame este código na função `loop`, logo após a linha onde a telemetria é enviada para a porta serial:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Manipular comandos

Seu dispositivo precisa lidar com um comando do código do servidor para controlar a retransmissão. Isso é enviado como uma solicitação de método direto.

## Tarefa - lidar com uma solicitação de método direto

1. Adicione o seguinte código antes da função `connectIOTHub`:

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

    Esse código define um método de retorno de chamada que a biblioteca do Hub IoT pode chamar quando recebe uma solicitação de método direto. O método solicitado é enviado no parâmetro `method_name`. Esta função imprime o método chamado para a porta serial, então liga ou desliga o relé dependendo do nome do método.

     > 💁 Isso também pode ser implementado em uma única solicitação direta de método, passando o estado desejado do relé em uma carga útil que pode ser passada com a solicitação do método e disponível a partir do parâmetro `payload`.

1. Adicione o seguinte código ao final da função `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    As solicitações de método direto precisam de uma resposta, e a resposta está em duas partes - uma resposta como texto e um código de retorno. Este código criará um resultado como o seguinte documento JSON:

    ```JSON
    {
        "Result": ""
    }
    ```

    Isso é então copiado para o parâmetro `response`, e o tamanho dessa resposta é definido no parâmetro `response_size`. Este código então retorna `IOTHUB_CLIENT_OK` para mostrar que o método foi tratado corretamente.

1. Conecte o retorno de chamada adicionando o seguinte ao final da função `connectIOTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. A função `loop` chamará a função `IOTHubDeviceClient_LL_DoWork` para processar eventos enviados pelo Hub IoT. Isso só é chamado a cada 10 segundos devido ao `delay`, significando que os métodos diretos são processados apenas a cada 10 segundos. Para tornar isso mais eficiente, o atraso de 10 segundos pode ser implementado como muitos atrasos menores, chamando `IOTHubDeviceClient_LL_DoWork` a cada vez. Para fazer isso, adicione o seguinte código acima da função `loop`:

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

    Esse código fará um loop repetidamente, chamando `IOTHubDeviceClient_LL_DoWork` e atrasando por 100ms cada vez. Ele fará isso quantas vezes forem necessárias para atrasar a quantidade de tempo fornecida no parâmetro `delay_time`. Isso significa que o dispositivo está aguardando no máximo 100 ms para processar solicitações de métodos diretos.

1. Na função `loop`, remova a chamada para `IOTHubDeviceClient_LL_DoWork` e substitua a chamada `delay(10000)` pelo seguinte para chamar esta nova função:

    ```cpp
    work_delay(10000);
    ```

> 💁 Você pode encontrar este código na pasta [code/wio-terminal](../code/wio-terminal).

😀 Seu programa de sensor de umidade do solo está conectado ao seu Hub IoT!
