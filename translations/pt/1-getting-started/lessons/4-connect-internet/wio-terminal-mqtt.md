<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-25T22:00:09+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "pt"
}
-->
# Controle a sua luz noturna pela Internet - Wio Terminal

O dispositivo IoT precisa ser programado para comunicar-se com *test.mosquitto.org* usando MQTT, enviando valores de telemetria com a leitura do sensor de luz e recebendo comandos para controlar o LED.

Nesta parte da lição, irá conectar o seu Wio Terminal a um broker MQTT.

## Instalar as bibliotecas WiFi e MQTT para Arduino

Para comunicar-se com o broker MQTT, é necessário instalar algumas bibliotecas Arduino para utilizar o chip WiFi do Wio Terminal e comunicar-se com MQTT. Ao desenvolver para dispositivos Arduino, pode usar uma ampla gama de bibliotecas que contêm código de código aberto e implementam uma enorme variedade de funcionalidades. A Seeed publica bibliotecas para o Wio Terminal que permitem a comunicação via WiFi. Outros desenvolvedores publicaram bibliotecas para comunicação com brokers MQTT, e irá utilizar estas com o seu dispositivo.

Estas bibliotecas são fornecidas como código-fonte que pode ser importado automaticamente para o PlatformIO e compilado para o seu dispositivo. Desta forma, as bibliotecas Arduino funcionarão em qualquer dispositivo que suporte o framework Arduino, desde que o dispositivo tenha o hardware específico necessário para essa biblioteca. Algumas bibliotecas, como as bibliotecas WiFi da Seeed, são específicas para determinados hardwares.

As bibliotecas podem ser instaladas globalmente e compiladas, se necessário, ou em um projeto específico. Para esta tarefa, as bibliotecas serão instaladas no projeto.

✅ Pode aprender mais sobre gestão de bibliotecas e como encontrar e instalar bibliotecas na [documentação de bibliotecas do PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Tarefa - instalar as bibliotecas WiFi e MQTT para Arduino

Instale as bibliotecas Arduino.

1. Abra o projeto da luz noturna no VS Code.

1. Adicione o seguinte ao final do ficheiro `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Isto importa as bibliotecas WiFi da Seeed. A sintaxe `@ <number>` refere-se a uma versão específica da biblioteca.

    > 💁 Pode remover o `@ <number>` para sempre usar a versão mais recente das bibliotecas, mas não há garantias de que as versões posteriores funcionarão com o código abaixo. O código aqui foi testado com esta versão das bibliotecas.

    Isto é tudo o que precisa fazer para adicionar as bibliotecas. Na próxima vez que o PlatformIO construir o projeto, ele irá descarregar o código-fonte destas bibliotecas e compilá-lo no seu projeto.

1. Adicione o seguinte ao `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Isto importa [PubSubClient](https://github.com/knolleary/pubsubclient), um cliente MQTT para Arduino.

## Conectar ao WiFi

O Wio Terminal agora pode ser conectado ao WiFi.

### Tarefa - conectar ao WiFi

Conecte o Wio Terminal ao WiFi.

1. Crie um novo ficheiro na pasta `src` chamado `config.h`. Pode fazer isso selecionando a pasta `src` ou o ficheiro `main.cpp` dentro dela e clicando no botão **Novo ficheiro** no explorador. Este botão só aparece quando o cursor está sobre o explorador.

    ![O botão novo ficheiro](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.pt.png)

1. Adicione o seguinte código a este ficheiro para definir constantes para as credenciais do WiFi:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Substitua `<SSID>` pelo SSID do seu WiFi. Substitua `<PASSWORD>` pela sua palavra-passe do WiFi.

1. Abra o ficheiro `main.cpp`.

1. Adicione as seguintes diretivas `#include` ao topo do ficheiro:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Isto inclui ficheiros de cabeçalho para as bibliotecas que adicionou anteriormente, bem como o ficheiro de cabeçalho de configuração. Estes ficheiros de cabeçalho são necessários para informar o PlatformIO a trazer o código das bibliotecas. Sem incluir explicitamente estes ficheiros de cabeçalho, algum código não será compilado e irá obter erros de compilação.

1. Adicione o seguinte código acima da função `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Este código faz um loop enquanto o dispositivo não está conectado ao WiFi e tenta conectar-se usando o SSID e a palavra-passe do ficheiro de cabeçalho de configuração.

1. Adicione uma chamada a esta função no final da função `setup`, após os pinos terem sido configurados.

    ```cpp
    connectWiFi();
    ```

1. Carregue este código no seu dispositivo para verificar se a conexão WiFi está a funcionar. Deve ver isto no monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Conectar ao MQTT

Depois de o Wio Terminal estar conectado ao WiFi, pode conectar-se ao broker MQTT.

### Tarefa - conectar ao MQTT

Conecte-se ao broker MQTT.

1. Adicione o seguinte código ao final do ficheiro `config.h` para definir os detalhes de conexão para o broker MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Substitua `<ID>` por um ID único que será usado como o nome deste cliente do dispositivo e, mais tarde, para os tópicos que este dispositivo publica e subscreve. O broker *test.mosquitto.org* é público e usado por muitas pessoas, incluindo outros estudantes que estão a realizar esta tarefa. Ter um nome único para o cliente MQTT e nomes de tópicos garante que o seu código não entre em conflito com o de outras pessoas. Também irá precisar deste ID ao criar o código do servidor mais tarde nesta tarefa.

    > 💁 Pode usar um site como [GUIDGen](https://www.guidgen.com) para gerar um ID único.

    O `BROKER` é o URL do broker MQTT.

    O `CLIENT_NAME` é um nome único para este cliente MQTT no broker.

1. Abra o ficheiro `main.cpp` e adicione o seguinte código abaixo da função `connectWiFi` e acima da função `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Este código cria um cliente WiFi usando as bibliotecas WiFi do Wio Terminal e utiliza-o para criar um cliente MQTT.

1. Abaixo deste código, adicione o seguinte:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Esta função testa a conexão ao broker MQTT e reconecta-se caso não esteja conectado. Faz um loop enquanto não está conectado e tenta conectar-se usando o nome único do cliente definido no ficheiro de cabeçalho de configuração.

    Se a conexão falhar, tenta novamente após 5 segundos.

1. Adicione o seguinte código abaixo da função `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Este código define o broker MQTT para o cliente, bem como configura o callback para quando uma mensagem for recebida. Em seguida, tenta conectar-se ao broker.

1. Chame a função `createMQTTClient` na função `setup` após o WiFi estar conectado.

1. Substitua toda a função `loop` pelo seguinte:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Este código começa por reconectar-se ao broker MQTT. Estas conexões podem ser facilmente interrompidas, por isso vale a pena verificar regularmente e reconectar-se, se necessário. Em seguida, chama o método `loop` no cliente MQTT para processar quaisquer mensagens que estejam a chegar no tópico subscrito. Esta aplicação é single-threaded, então as mensagens não podem ser recebidas numa thread em segundo plano; portanto, é necessário alocar tempo na thread principal para processar quaisquer mensagens que estejam a aguardar na conexão de rede.

    Finalmente, um atraso de 2 segundos garante que os níveis de luz não sejam enviados com muita frequência e reduz o consumo de energia do dispositivo.

1. Carregue o código no seu Wio Terminal e use o Monitor Serial para ver o dispositivo conectar-se ao WiFi e ao MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Pode encontrar este código na pasta [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Conseguiu conectar o seu dispositivo a um broker MQTT com sucesso.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, tenha em atenção que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.