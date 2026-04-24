# Detectar proximidade - Wio Terminal

Nesta parte da lição, você adicionará um sensor de proximidade ao seu Wio Terminal e lerá a distância a partir dele.

## Hardware

O Wio Terminal precisa de um sensor de proximidade.

O sensor que você usará é um [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Este sensor utiliza um módulo de medição a laser para detectar distâncias. Ele possui um alcance de 10mm a 2000mm (1cm - 2m) e reporta valores dentro desse intervalo com bastante precisão, sendo que distâncias acima de 1000mm são reportadas como 8109mm.

O medidor de distância a laser está localizado na parte traseira do sensor, no lado oposto ao conector Grove.

Este é um socket I²C.

### Conectar o sensor time of flight

O sensor Grove time of flight pode ser conectado ao Wio Terminal.

#### Tarefa - conectar o sensor time of flight

Conecte o sensor time of flight.

![Um sensor Grove time of flight](../../../../../translated_images/pt-BR/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Insira uma extremidade de um cabo Grove no conector do sensor time of flight. Ele só encaixará de uma maneira.

1. Com o Wio Terminal desconectado do seu computador ou de outra fonte de energia, conecte a outra extremidade do cabo Grove ao conector Grove do lado esquerdo do Wio Terminal, olhando para a tela. Este é o conector mais próximo do botão de energia. Este é um socket combinado digital e I²C.

![O sensor Grove time of flight conectado ao conector esquerdo](../../../../../translated_images/pt-BR/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Agora você pode conectar o Wio Terminal ao seu computador.

## Programar o sensor time of flight

Agora o Wio Terminal pode ser programado para usar o sensor time of flight conectado.

### Tarefa - programar o sensor time of flight

1. Crie um novo projeto para o Wio Terminal usando o PlatformIO. Chame este projeto de `distance-sensor`. Adicione código na função `setup` para configurar a porta serial.

1. Adicione uma dependência de biblioteca para a biblioteca Seeed Grove time of flight distance sensor no arquivo `platformio.ini` do projeto:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. No arquivo `main.cpp`, adicione o seguinte abaixo das diretivas de inclusão existentes para declarar uma instância da classe `Seeed_vl53l0x` para interagir com o sensor time of flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Adicione o seguinte ao final da função `setup` para inicializar o sensor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Na função `loop`, leia um valor do sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Este código inicializa uma estrutura de dados para armazenar os dados lidos e, em seguida, passa essa estrutura para o método `PerformSingleRangingMeasurement`, onde será preenchida com a medição da distância.

1. Abaixo disso, escreva a medição da distância e, em seguida, adicione um atraso de 1 segundo:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Compile, carregue e execute este código. Você poderá ver as medições de distância no monitor serial. Posicione objetos próximos ao sensor e verá a medição da distância:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    O medidor de distância está na parte traseira do sensor, então certifique-se de usar o lado correto ao medir a distância.

    ![O medidor de distância na parte traseira do sensor time of flight apontando para uma banana](../../../../../translated_images/pt-BR/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Você pode encontrar este código na pasta [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Seu programa para o sensor de proximidade foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.