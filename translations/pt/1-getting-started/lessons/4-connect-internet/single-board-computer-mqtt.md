<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-25T21:59:35+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "pt"
}
-->
# Controle a sua luz de presença pela Internet - Hardware IoT Virtual e Raspberry Pi

O dispositivo IoT precisa ser programado para comunicar-se com *test.mosquitto.org* usando MQTT, a fim de enviar valores de telemetria com a leitura do sensor de luz e receber comandos para controlar o LED.

Nesta parte da lição, irá ligar o seu Raspberry Pi ou dispositivo IoT virtual a um broker MQTT.

## Instalar o pacote cliente MQTT

Para comunicar-se com o broker MQTT, é necessário instalar uma biblioteca MQTT através do pacote pip, seja no seu Pi ou no ambiente virtual, caso esteja a usar um dispositivo virtual.

### Tarefa

Instale o pacote pip

1. Abra o projeto da luz de presença no VS Code.

1. Se estiver a usar um dispositivo IoT virtual, certifique-se de que o terminal está a executar o ambiente virtual. Se estiver a usar um Raspberry Pi, não estará a usar um ambiente virtual.

1. Execute o seguinte comando para instalar o pacote pip MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Programar o dispositivo

O dispositivo está pronto para ser programado.

### Tarefa

Escreva o código do dispositivo.

1. Adicione a seguinte importação no início do ficheiro `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    A biblioteca `paho.mqtt.client` permite que a sua aplicação comunique via MQTT.

1. Adicione o seguinte código após as definições do sensor de luz e do LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Substitua `<ID>` por um ID único que será usado como o nome deste cliente do dispositivo e, mais tarde, para os tópicos que este dispositivo publica e subscreve. O broker *test.mosquitto.org* é público e usado por muitas pessoas, incluindo outros estudantes a trabalhar nesta tarefa. Ter um nome de cliente MQTT único e nomes de tópicos únicos garante que o seu código não entre em conflito com o de outras pessoas. Também precisará deste ID ao criar o código do servidor mais tarde nesta tarefa.

    > 💁 Pode usar um site como [GUIDGen](https://www.guidgen.com) para gerar um ID único.

    O `client_name` é um nome único para este cliente MQTT no broker.

1. Adicione o seguinte código abaixo deste novo código para criar um objeto cliente MQTT e conectá-lo ao broker MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Este código cria o objeto cliente, conecta-se ao broker MQTT público e inicia um loop de processamento que é executado numa thread em segundo plano, ouvindo mensagens em quaisquer tópicos subscritos.

1. Execute o código da mesma forma que executou o código da parte anterior da tarefa. Se estiver a usar um dispositivo IoT virtual, certifique-se de que a aplicação CounterFit está em execução e que o sensor de luz e o LED foram criados nos pinos corretos.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Pode encontrar este código na pasta [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) ou na pasta [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Conseguiu ligar o seu dispositivo a um broker MQTT com sucesso.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.