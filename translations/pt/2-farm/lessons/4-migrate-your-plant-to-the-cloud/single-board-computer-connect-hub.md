<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-25T21:46:28+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "pt"
}
-->
# Conecte o seu dispositivo IoT à nuvem - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, irá conectar o seu dispositivo IoT virtual ou Raspberry Pi ao IoT Hub, para enviar telemetria e receber comandos.

## Conectar o seu dispositivo ao IoT Hub

O próximo passo é conectar o seu dispositivo ao IoT Hub.

### Tarefa - conectar ao IoT Hub

1. Abra a pasta `soil-moisture-sensor` no VS Code. Certifique-se de que o ambiente virtual está a funcionar no terminal, caso esteja a usar um dispositivo IoT virtual.

1. Instale alguns pacotes adicionais do Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` é uma biblioteca para comunicar com o seu IoT Hub.

1. Adicione as seguintes importações ao topo do ficheiro `app.py`, abaixo das importações existentes:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Este código importa o SDK para comunicar com o seu IoT Hub.

1. Remova a linha `import paho.mqtt.client as mqtt`, pois esta biblioteca já não é necessária. Remova todo o código MQTT, incluindo os nomes dos tópicos, todo o código que utiliza `mqtt_client` e o `handle_command`. Mantenha o ciclo `while True:`, apenas elimine a linha `mqtt_client.publish` deste ciclo.

1. Adicione o seguinte código abaixo das declarações de importação:

    ```python
    connection_string = "<connection string>"
    ```

    Substitua `<connection string>` pela cadeia de conexão que obteve para o dispositivo anteriormente nesta lição.

    > 💁 Isto não é uma boa prática. As cadeias de conexão nunca devem ser armazenadas no código fonte, pois podem ser incluídas no controlo de versão e encontradas por qualquer pessoa. Estamos a fazer isto aqui por simplicidade. Idealmente, deveria usar algo como uma variável de ambiente e uma ferramenta como [`python-dotenv`](https://pypi.org/project/python-dotenv/). Aprenderá mais sobre isto numa lição futura.

1. Abaixo deste código, adicione o seguinte para criar um objeto cliente do dispositivo que pode comunicar com o IoT Hub e conectá-lo:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Execute este código. Verá o seu dispositivo conectar-se.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Enviar telemetria

Agora que o seu dispositivo está conectado, pode enviar telemetria para o IoT Hub em vez do broker MQTT.

### Tarefa - enviar telemetria

1. Adicione o seguinte código dentro do ciclo `while True`, logo antes do comando de pausa:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Este código cria uma `Message` do IoT Hub contendo a leitura da humidade do solo como uma string JSON e envia-a para o IoT Hub como uma mensagem de dispositivo para nuvem.

## Lidar com comandos

O seu dispositivo precisa de lidar com um comando do código do servidor para controlar o relé. Este é enviado como um pedido de método direto.

## Tarefa - lidar com um pedido de método direto

1. Adicione o seguinte código antes do ciclo `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Isto define um método, `handle_method_request`, que será chamado quando um método direto for invocado pelo IoT Hub. Cada método direto tem um nome, e este código espera um método chamado `relay_on` para ligar o relé e `relay_off` para desligar o relé.

    > 💁 Isto também poderia ser implementado num único pedido de método direto, passando o estado desejado do relé num payload que pode ser enviado com o pedido de método e disponível a partir do objeto `request`.

1. Os métodos diretos requerem uma resposta para informar o código que os invocou de que foram tratados. Adicione o seguinte código no final da função `handle_method_request` para criar uma resposta ao pedido:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Este código envia uma resposta ao pedido de método direto com um código de estado HTTP 200 e envia-a de volta para o IoT Hub.

1. Adicione o seguinte código abaixo da definição desta função:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Este código informa o cliente do IoT Hub para chamar a função `handle_method_request` quando um método direto for invocado.

> 💁 Pode encontrar este código na pasta [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) ou [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 O programa do seu sensor de humidade do solo está conectado ao seu IoT Hub!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.