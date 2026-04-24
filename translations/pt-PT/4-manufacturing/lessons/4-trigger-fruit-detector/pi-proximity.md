# Detetar proximidade - Raspberry Pi

Nesta parte da lição, vais adicionar um sensor de proximidade ao teu Raspberry Pi e ler a distância a partir dele.

## Hardware

O Raspberry Pi necessita de um sensor de proximidade.

O sensor que vais utilizar é um [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Este sensor utiliza um módulo de medição a laser para detetar distâncias. Tem um alcance de 10mm a 2000mm (1cm - 2m) e reporta valores dentro desse intervalo com bastante precisão, sendo que distâncias acima de 1000mm são reportadas como 8109mm.

O medidor de distância a laser está na parte de trás do sensor, no lado oposto ao conector Grove.

Este é um sensor I²C.

### Ligar o sensor Time of Flight

O sensor Grove Time of Flight pode ser ligado ao Raspberry Pi.

#### Tarefa - ligar o sensor Time of Flight

Liga o sensor Time of Flight.

![Um sensor Grove Time of Flight](../../../../../translated_images/pt-PT/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Insere uma extremidade de um cabo Grove na entrada do sensor Time of Flight. O cabo só encaixa de uma forma.

1. Com o Raspberry Pi desligado, liga a outra extremidade do cabo Grove a uma das entradas I²C marcadas como **I²C** no Grove Base Hat ligado ao Pi. Estas entradas estão na fila inferior, na extremidade oposta aos pinos GPIO e ao lado da entrada para o cabo da câmara.

![O sensor Grove Time of Flight ligado à entrada I²C](../../../../../translated_images/pt-PT/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programar o sensor Time of Flight

Agora o Raspberry Pi pode ser programado para utilizar o sensor Time of Flight ligado.

### Tarefa - programar o sensor Time of Flight

Programa o dispositivo.

1. Liga o Raspberry Pi e espera que ele inicie.

1. Abre o código `fruit-quality-detector` no VS Code, diretamente no Pi ou através da extensão Remote SSH.

1. Instala o pacote Pip `rpi-vl53l0x`, um pacote Python que interage com o sensor de distância VL53L0X Time of Flight. Instala-o com o seguinte comando pip:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Cria um novo ficheiro neste projeto chamado `distance-sensor.py`.

    > 💁 Uma forma simples de simular múltiplos dispositivos IoT é criar cada um num ficheiro Python diferente e executá-los ao mesmo tempo.

1. Adiciona o seguinte código a este ficheiro:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Este código importa a biblioteca Grove I²C bus e uma biblioteca para o hardware principal do sensor incorporado no sensor Grove Time of Flight.

1. Abaixo disso, adiciona o seguinte código para aceder ao sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Este código declara um sensor de distância utilizando o Grove I²C bus e, em seguida, inicia o sensor.

1. Por fim, adiciona um loop infinito para ler as distâncias:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Este código espera que um valor esteja pronto para ser lido do sensor e, em seguida, imprime-o na consola.

1. Executa este código.

    > 💁 Não te esqueças de que este ficheiro se chama `distance-sensor.py`! Certifica-te de que o executas com Python, e não com `app.py`.

1. Vais ver as medições de distância aparecerem na consola. Coloca objetos perto do sensor e verás a medição da distância:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    O medidor de distância está na parte de trás do sensor, por isso certifica-te de que utilizas o lado correto ao medir a distância.

    ![O medidor de distância na parte de trás do sensor Time of Flight apontado para uma banana](../../../../../translated_images/pt-PT/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Podes encontrar este código na pasta [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 O teu programa para o sensor de proximidade foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, tenha em atenção que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.