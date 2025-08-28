<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T03:32:59+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "br"
}
-->
# Controle sua luz noturna pela Internet - Hardware IoT Virtual e Raspberry Pi

O dispositivo IoT precisa ser programado para se comunicar com o *test.mosquitto.org* usando MQTT, a fim de enviar valores de telemetria com a leitura do sensor de luz e receber comandos para controlar o LED.

Nesta parte da lição, você conectará seu Raspberry Pi ou dispositivo IoT virtual a um broker MQTT.

## Instale o pacote cliente MQTT

Para se comunicar com o broker MQTT, você precisa instalar uma biblioteca MQTT usando o pip, seja no seu Raspberry Pi ou no ambiente virtual, caso esteja utilizando um dispositivo virtual.

### Tarefa

Instale o pacote pip

1. Abra o projeto da luz noturna no VS Code.

1. Se estiver usando um dispositivo IoT virtual, certifique-se de que o terminal está executando o ambiente virtual. Se estiver usando um Raspberry Pi, você não precisará de um ambiente virtual.

1. Execute o seguinte comando para instalar o pacote MQTT via pip:

    ```sh
    pip3 install paho-mqtt
    ```

## Programe o dispositivo

O dispositivo está pronto para ser programado.

### Tarefa

Escreva o código do dispositivo.

1. Adicione a seguinte importação no topo do arquivo `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    A biblioteca `paho.mqtt.client` permite que seu aplicativo se comunique via MQTT.

1. Adicione o seguinte código após as definições do sensor de luz e do LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Substitua `<ID>` por um ID único que será usado como o nome deste cliente do dispositivo e, mais tarde, para os tópicos que este dispositivo publicará e assinará. O broker *test.mosquitto.org* é público e usado por muitas pessoas, incluindo outros estudantes que estão trabalhando nesta tarefa. Ter um nome de cliente MQTT e nomes de tópicos únicos garante que seu código não entre em conflito com o de outras pessoas. Você também precisará desse ID ao criar o código do servidor mais adiante nesta tarefa.

    > 💁 Você pode usar um site como [GUIDGen](https://www.guidgen.com) para gerar um ID único.

    O `client_name` é um nome exclusivo para este cliente MQTT no broker.

1. Adicione o seguinte código abaixo deste novo código para criar um objeto cliente MQTT e conectar-se ao broker MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Este código cria o objeto cliente, conecta-se ao broker MQTT público e inicia um loop de processamento que roda em uma thread em segundo plano, ouvindo mensagens em quaisquer tópicos assinados.

1. Execute o código da mesma forma que você executou o código da parte anterior da tarefa. Se estiver usando um dispositivo IoT virtual, certifique-se de que o aplicativo CounterFit está em execução e que o sensor de luz e o LED foram criados nos pinos corretos.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Você pode encontrar este código na pasta [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) ou na pasta [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Você conectou com sucesso seu dispositivo a um broker MQTT.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.