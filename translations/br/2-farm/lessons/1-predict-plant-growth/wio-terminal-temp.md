<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-28T04:14:15+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "br"
}
-->
# Medir temperatura - Wio Terminal

Nesta parte da lição, você adicionará um sensor de temperatura ao seu Wio Terminal e lerá os valores de temperatura dele.

## Hardware

O Wio Terminal precisa de um sensor de temperatura.

O sensor que você usará é um [sensor de umidade e temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), que combina 2 sensores em um único dispositivo. Este sensor é bastante popular, com vários modelos disponíveis comercialmente que combinam temperatura, umidade e, às vezes, pressão atmosférica. O componente do sensor de temperatura é um termistor de coeficiente de temperatura negativo (NTC), um termistor cuja resistência diminui à medida que a temperatura aumenta.

Este é um sensor digital, portanto, possui um conversor ADC integrado para criar um sinal digital contendo os dados de temperatura e umidade que o microcontrolador pode ler.

### Conectar o sensor de temperatura

O sensor de temperatura Grove pode ser conectado à porta digital do Wio Terminal.

#### Tarefa - conectar o sensor de temperatura

Conecte o sensor de temperatura.

![Um sensor de temperatura Grove](../../../../../translated_images/br/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Insira uma extremidade de um cabo Grove no conector do sensor de umidade e temperatura. Ele só se encaixará de uma maneira.

1. Com o Wio Terminal desconectado do seu computador ou de outra fonte de energia, conecte a outra extremidade do cabo Grove ao conector Grove do lado direito do Wio Terminal, olhando para a tela. Este é o conector mais distante do botão de energia.

![O sensor de temperatura Grove conectado ao conector do lado direito](../../../../../translated_images/br/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programar o sensor de temperatura

Agora o Wio Terminal pode ser programado para usar o sensor de temperatura conectado.

### Tarefa - programar o sensor de temperatura

Programe o dispositivo.

1. Crie um novo projeto para o Wio Terminal usando o PlatformIO. Chame este projeto de `temperature-sensor`. Adicione código na função `setup` para configurar a porta serial.

    > ⚠️ Você pode consultar [as instruções para criar um projeto PlatformIO no projeto 1, lição 1, se necessário](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Adicione uma dependência de biblioteca para a biblioteca Seeed Grove Humidity and Temperature sensor no arquivo `platformio.ini` do projeto:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Você pode consultar [as instruções para adicionar bibliotecas a um projeto PlatformIO no projeto 1, lição 4, se necessário](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Adicione as seguintes diretivas `#include` ao topo do arquivo, abaixo do `#include <Arduino.h>` existente:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Isso importa os arquivos necessários para interagir com o sensor. O arquivo de cabeçalho `DHT.h` contém o código para o próprio sensor, e adicionar o cabeçalho `SPI.h` garante que o código necessário para se comunicar com o sensor seja vinculado quando o aplicativo for compilado.

1. Antes da função `setup`, declare o sensor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Isso declara uma instância da classe `DHT` que gerencia o sensor de **U**midade e **T**emperatura **D**igital. Ele está conectado à porta `D0`, o conector Grove do lado direito do Wio Terminal. O segundo parâmetro informa ao código que o sensor usado é o *DHT11* - a biblioteca que você está usando suporta outras variantes deste sensor.

1. Na função `setup`, adicione código para configurar a conexão serial:

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

1. Na função `loop`, adicione código para chamar o sensor e imprimir a temperatura na porta serial:

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

    Este código declara um array vazio de 2 floats e o passa para a chamada `readTempAndHumidity` na instância `DHT`. Esta chamada preenche o array com 2 valores - a umidade vai para o item 0 do array (lembre-se de que em C++ os arrays são baseados em 0, então o item 0 é o 'primeiro' item do array), e a temperatura vai para o item 1.

    A temperatura é lida do item 1 do array e impressa na porta serial.

    > 🇺🇸 A temperatura é lida em Celsius. Para os americanos, para converter isso para Fahrenheit, divida o valor em Celsius por 5, depois multiplique por 9 e, em seguida, adicione 32. Por exemplo, uma leitura de temperatura de 20°C se torna ((20/5)*9) + 32 = 68°F.

1. Compile e envie o código para o Wio Terminal.

    > ⚠️ Você pode consultar [as instruções para criar um projeto PlatformIO no projeto 1, lição 1, se necessário](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Depois de enviado, você pode monitorar a temperatura usando o monitor serial:

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

> 💁 Você pode encontrar este código na pasta [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Seu programa do sensor de temperatura foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.