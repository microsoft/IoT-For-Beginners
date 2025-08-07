# Medir temperatura - Terminal Wio

Nesta parte da lição, você adicionará um sensor de temperatura ao seu Terminal Wio e lerá os valores de temperatura a partir dele.

## Hardware

O Terminal Wio precisa de um sensor de temperatura.

O sensor que você usará é um [sensor de umidade e temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), combinando 2 sensores em um pacote. Isso é bastante popular, com vários sensores comercialmente disponíveis combinando temperatura, umidade e, às vezes, pressão atmosférica. O componente do sensor de temperatura é um termistor de coeficiente de temperatura negativo (NTC), um termistor onde a resistência diminui à medida que a temperatura aumenta.

Este é um sensor digital, portanto, possui um ADC integrado para criar um sinal digital contendo os dados de temperatura e umidade que o microcontrolador pode ler.

### Conecte o sensor de temperatura

O sensor de temperatura Grove pode ser conectado à porta digital Wio Terminals.

#### Tarefa - conecte o sensor de temperatura

Conecte o sensor de temperatura.

![Um sensor de temperatura Grove](../../../../images/grove-dht11.png)

1. Insira uma extremidade de um cabo Grove no soquete do sensor de umidade e temperatura. Só vai dar uma volta.

1. Com o Terminal Wio desconectado do computador ou de outra fonte de alimentação, conecte a outra extremidade do cabo Grove ao soquete Grove do lado direito do Terminal Wio enquanto olha para a tela. Este é o soquete mais distante do botão liga/desliga.

![O sensor de temperatura Grove conectado ao soquete do lado direito](../../../../images/wio-temperature-sensor.png)

## Programar o sensor de temperatura

O Terminal Wio agora pode ser programado para usar o sensor de temperatura conectado.

### Tarefa: programar o sensor de temperatura

Programe o dispositivo.

1. Crie um novo projeto de Terminal Wio usando PlatformIO. Chame este projeto de `sensor de temperatura`. Adicione código na função `setup` para configurar a porta serial.

    > ⚠️ Você pode consultar [as instruções para criar um projeto PlatformIO no projeto 1, lição 1, se necessário](../../../1-getting-started/lessons/1-introduction-to-iot/translations/wio-terminal.pt.md#crie-um-projeto-platformio).

1. Adicione uma dependência de biblioteca para a biblioteca do sensor de umidade e temperatura Seeed Grove ao arquivo `platformio.ini` do projeto:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Você pode consultar [as instruções para adicionar bibliotecas a um projeto PlatformIO no projeto 1, lição 4, se necessário](../../../../1-getting-started/lessons/4-connect-internet/translactions/wio-terminal-mqtt.pt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Adicione as seguintes diretivas `#include` ao topo do arquivo, sob o `#include <Arduino.h>` existente:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Isso importa os arquivos necessários para interagir com o sensor. O arquivo de cabeçalho `DHT.h` contém o código para o próprio sensor, e adicionar o cabeçalho `SPI.h` garante que o código necessário para se comunicar com o sensor seja vinculado quando o aplicativo for compilado.

1. Antes da função `setup`, declare o sensor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Isso declara uma instância da classe `DHT` que gerencia o sensor de **D**igital umidade (**H**umidity) e **T** de temperatura. Este está conectado à porta `D0`, o soquete Grove do lado direito no Terminal Wio. O segundo parâmetro informa ao código que o sensor que está sendo usado é o sensor *DHT11* - a biblioteca que você está usando suporta outras variantes desse sensor.

1. Na função `setup`, adicione o código para configurar a conexão serial:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. No final da função `setup`, após o último `delay`, adicione uma chamada para iniciar o sensor DHT:

    ```cpp
    dht.begin();
    ```

1. Na função `loop`, adicione o código para chamar o sensor e imprimir a temperatura na porta serial:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Este código declara um array vazio de 2 floats e passa isso para a chamada para `readTempAndHumidity` na instância `DHT`. Esta chamada preenche o array com 2 valores - a umidade vai no 0º item no array (lembre-se em arrays C++ são baseados em 0, então o 0º item é o 'primeiro' item no array), e a temperatura vai para o 1º artigo.

     A temperatura é lida a partir do 1º item da matriz e impressa na porta serial.

    > 🇧🇷 A temperatura é lida em Celsius. Para os americanos, para converter isso em Fahrenheit, divida o valor Celsius lido por 5, multiplique por 9 e adicione 32. Por exemplo, uma leitura de temperatura de 20°C se torna ((20/5)*9) + 32 = 68 °F.

1. Construa e carregue o código para o Terminal Wio.

    > ⚠️ Você pode consultar [as instruções para criar um projeto PlatformIO no projeto 1, lição 1, se necessário](../../../../1-getting-started/lessons/1-introduction-to-iot/translations/wio-terminal.pt.md#write-the-hello-world-app).

1. Uma vez carregado, você pode monitorar a temperatura usando o monitor serial:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁Você pode encontrar esse código na pasta [code-temperature/wio-terminal](../code-temperature/wio-terminal).

😀 Seu programa de sensor de temperatura foi um sucesso!
