# Medir a temperatura - Raspberry Pi

Nesta parte da lição, você adicionará um sensor de temperatura ao seu Raspberry Pi.

## Hardware

O sensor que você usará é um [sensor de umidade e temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), combinando 2 sensores em um pacote. Isso é bastante popular, com vários sensores comercialmente disponíveis combinando temperatura, umidade e, às vezes, pressão atmosférica. O componente do sensor de temperatura é um termistor de coeficiente de temperatura negativo (NTC), um termistor onde a resistência diminui à medida que a temperatura aumenta.

This is a digital sensor, so has an onboard ADC to create a digital signal containing the temperature and humidity data that the microcontroller can read.

### Conecte o sensor de temperatura

O sensor de temperatura Grove pode ser conectado ao Raspberry Pi.

#### Tarefa

Conecte o sensor de temperatura

![Um sensor de temperatura groove](../../../../images/grove-dht11.png)

1. Insira uma extremidade de um cabo Grove no soquete do sensor de umidade e temperatura. Só vai dar uma volta.

1. Com o Raspberry Pi desligado, conecte a outra extremidade do cabo Grove ao soquete digital marcado como **D5** no chapéu Grove Base conectado ao Pi. Este soquete é o segundo da esquerda, na fileira de soquetes ao lado dos pinos GPIO.

![O sensor de temperatura Grove conectado ao soquete A0](../../../../images/pi-temperature-sensor.png)

## Programe o sensor de temperatura

O dispositivo agora pode ser programado para usar o sensor de temperatura conectado.

### Tarefa

Programe o dispositivo.

1. Ligue o Pi e espere que ele inicialize

1. Inicie o VS Code, diretamente no Pi ou conecte-se através da extensão SSH remota.

    > ⚠️ Você pode consultar [as instruções para configurar e iniciar o VS Code na lição 1, se necessário](../../../../1-getting-started/lessons/1-introduction-to-iot/translations/pi.pt.md).

1. A partir do terminal, crie uma nova pasta no diretório inicial dos usuários `pi` chamada `temperature-sensor`. Crie um arquivo nesta pasta chamado `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Abra esta pasta no VS Code

1. Para usar o sensor de temperatura e umidade, um pacote Pip adicional precisa ser instalado. No Terminal no VS Code, execute o seguinte comando para instalar este pacote Pip no Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Adicione o seguinte código ao arquivo `app.py` para importar as bibliotecas necessárias:

    ```python
    import time
    from seeed_dht import DHT
    ```

    A instrução `from seeed_dht import DHT` importa a classe de sensor `DHT` para interagir com um sensor de temperatura Grove do módulo `seeed_dht`.

1. Adicione o seguinte código após o código acima para criar uma instância da classe que gerencia o sensor de temperatura:

    ```python
    sensor = DHT("11", 5)
    ```

    Isso declara uma instância da classe `DHT` que gerencia o sensor de **D**igital **H**umidade e **T** de temperatura. O primeiro parâmetro informa ao código que o sensor que está sendo usado é o sensor *DHT11* - a biblioteca que você está usando suporta outras variantes desse sensor. O segundo parâmetro informa ao código que o sensor está conectado à porta digital `D5` no chapéu base Grove.

    > ✅ Lembre-se, todos os soquetes têm números de pinos exclusivos. Os pinos 0, 2, 4 e 6 são pinos analógicos, pinos 5, 16, 18, 22, 24 e 26 são pinos digitais.

1. Adicione um loop infinito após o código acima para pesquisar o valor do sensor de temperatura e imprimi-lo no console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

   A chamada para `sensor.read()` retorna uma tupla de umidade e temperatura. Você só precisa do valor da temperatura, então a umidade é ignorada. O valor da temperatura é então impresso no console.

1. Adicione um pequeno descanso de dez segundos no final do 'loop', pois os níveis de temperatura não precisam ser verificados continuamente. Uma suspensão reduz o consumo de energia do dispositivo.

    ```python
    time.sleep(10)
    ```

1. No Terminal do VS Code, execute o seguinte para executar seu aplicativo Python:

    ```sh
    python3 app.py
    ```

    Você deve ver os valores de temperatura sendo emitidos para o console. Use algo para aquecer o sensor, como pressionar o polegar sobre ele ou usar um ventilador para ver os valores mudarem:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Você pode encontrar esse código na pasta [code-temperature/pi](../code-temperature/pi).

😀 Seu programa de sensor de temperatura foi um sucesso!
