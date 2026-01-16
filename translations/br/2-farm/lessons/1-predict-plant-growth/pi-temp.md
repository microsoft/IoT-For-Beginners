<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-28T04:09:25+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "br"
}
-->
# Medir temperatura - Raspberry Pi

Nesta parte da lição, você adicionará um sensor de temperatura ao seu Raspberry Pi.

## Hardware

O sensor que você usará é um [sensor de umidade e temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), que combina 2 sensores em um único pacote. Este sensor é bastante popular, com vários sensores disponíveis comercialmente que combinam temperatura, umidade e, às vezes, pressão atmosférica. O componente de temperatura é um termistor de coeficiente de temperatura negativo (NTC), um termistor cuja resistência diminui à medida que a temperatura aumenta.

Este é um sensor digital, então ele possui um conversor ADC integrado para criar um sinal digital contendo os dados de temperatura e umidade que o microcontrolador pode ler.

### Conectar o sensor de temperatura

O sensor de temperatura Grove pode ser conectado ao Raspberry Pi.

#### Tarefa

Conecte o sensor de temperatura

![Um sensor de temperatura Grove](../../../../../translated_images/br/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Insira uma extremidade do cabo Grove no conector do sensor de umidade e temperatura. Ele só encaixará de uma maneira.

1. Com o Raspberry Pi desligado, conecte a outra extremidade do cabo Grove ao conector digital marcado como **D5** no Grove Base Hat conectado ao Pi. Este conector é o segundo da esquerda, na fileira de conectores ao lado dos pinos GPIO.

![O sensor de temperatura Grove conectado ao conector A0](../../../../../translated_images/br/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Programar o sensor de temperatura

Agora o dispositivo pode ser programado para usar o sensor de temperatura conectado.

### Tarefa

Programe o dispositivo.

1. Ligue o Raspberry Pi e aguarde o boot.

1. Abra o VS Code, diretamente no Pi ou conecte-se via a extensão Remote SSH.

    > ⚠️ Você pode consultar [as instruções para configurar e abrir o VS Code na lição 1, se necessário](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. No terminal, crie uma nova pasta no diretório home do usuário `pi` chamada `temperature-sensor`. Crie um arquivo nesta pasta chamado `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Abra esta pasta no VS Code.

1. Para usar o sensor de temperatura e umidade, é necessário instalar um pacote adicional do Pip. No terminal do VS Code, execute o seguinte comando para instalar este pacote no Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Adicione o seguinte código ao arquivo `app.py` para importar as bibliotecas necessárias:

    ```python
    import time
    from seeed_dht import DHT
    ```

    A instrução `from seeed_dht import DHT` importa a classe `DHT` para interagir com um sensor de temperatura Grove do módulo `seeed_dht`.

1. Adicione o seguinte código após o código acima para criar uma instância da classe que gerencia o sensor de temperatura:

    ```python
    sensor = DHT("11", 5)
    ```

    Isso declara uma instância da classe `DHT` que gerencia o sensor de **U**midade e **T**emperatura **D**igital. O primeiro parâmetro informa ao código que o sensor utilizado é o *DHT11* - a biblioteca que você está usando suporta outras variantes deste sensor. O segundo parâmetro informa ao código que o sensor está conectado ao conector digital `D5` no Grove Base Hat.

    > ✅ Lembre-se, todos os conectores possuem números de pinos únicos. Os pinos 0, 2, 4 e 6 são pinos analógicos, enquanto os pinos 5, 16, 18, 22, 24 e 26 são pinos digitais.

1. Adicione um loop infinito após o código acima para consultar o valor do sensor de temperatura e imprimi-lo no console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    A chamada para `sensor.read()` retorna uma tupla com umidade e temperatura. Você só precisa do valor de temperatura, então a umidade é ignorada. O valor da temperatura é então impresso no console.

1. Adicione uma pausa de dez segundos no final do `loop`, já que os níveis de temperatura não precisam ser verificados continuamente. Uma pausa reduz o consumo de energia do dispositivo.

    ```python
    time.sleep(10)
    ```

1. No terminal do VS Code, execute o seguinte comando para rodar seu aplicativo Python:

    ```sh
    python3 app.py
    ```

    Você deverá ver os valores de temperatura sendo exibidos no console. Use algo para aquecer o sensor, como pressionar seu dedo sobre ele ou usar um ventilador, para ver os valores mudarem:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Você pode encontrar este código na pasta [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Seu programa do sensor de temperatura foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.