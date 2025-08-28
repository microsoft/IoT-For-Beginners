<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T04:07:45+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "br"
}
-->
# Conecte seu dispositivo IoT à nuvem - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, você conectará seu dispositivo IoT virtual ou Raspberry Pi ao IoT Hub, para enviar telemetria e receber comandos.

## Conecte seu dispositivo ao IoT Hub

O próximo passo é conectar seu dispositivo ao IoT Hub.

### Tarefa - conectar ao IoT Hub

1. Abra a pasta `soil-moisture-sensor` no VS Code. Certifique-se de que o ambiente virtual está em execução no terminal, caso esteja utilizando um dispositivo IoT virtual.

1. Instale alguns pacotes adicionais do Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` é uma biblioteca para se comunicar com seu IoT Hub.

1. Adicione as seguintes importações no topo do arquivo `app.py`, abaixo das importações existentes:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Este código importa o SDK para se comunicar com seu IoT Hub.

1. Remova a linha `import paho.mqtt.client as mqtt`, pois esta biblioteca não será mais necessária. Remova todo o código relacionado ao MQTT, incluindo os nomes dos tópicos, todo o código que utiliza `mqtt_client` e o `handle_command`. Mantenha o loop `while True:`, apenas exclua a linha `mqtt_client.publish` deste loop.

1. Adicione o seguinte código abaixo das declarações de importação:

    ```python
    connection_string = "<connection string>"
    ```

    Substitua `<connection string>` pela string de conexão que você recuperou para o dispositivo anteriormente nesta lição.

    > 💁 Isso não é uma prática recomendada. Strings de conexão nunca devem ser armazenadas no código-fonte, pois podem ser verificadas no controle de versão e encontradas por qualquer pessoa. Estamos fazendo isso aqui por simplicidade. Idealmente, você deveria usar algo como uma variável de ambiente e uma ferramenta como [`python-dotenv`](https://pypi.org/project/python-dotenv/). Você aprenderá mais sobre isso em uma lição futura.

1. Abaixo deste código, adicione o seguinte para criar um objeto cliente de dispositivo que possa se comunicar com o IoT Hub e conectá-lo:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Execute este código. Você verá seu dispositivo se conectar.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Enviar telemetria

Agora que seu dispositivo está conectado, você pode enviar telemetria para o IoT Hub em vez do broker MQTT.

### Tarefa - enviar telemetria

1. Adicione o seguinte código dentro do loop `while True`, logo antes do comando de pausa (`sleep`):

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Este código cria uma `Message` do IoT Hub contendo a leitura de umidade do solo como uma string JSON e a envia para o IoT Hub como uma mensagem de dispositivo para nuvem.

## Manipular comandos

Seu dispositivo precisa manipular um comando do código do servidor para controlar o relé. Isso é enviado como uma solicitação de método direto.

## Tarefa - manipular uma solicitação de método direto

1. Adicione o seguinte código antes do loop `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Isso define um método, `handle_method_request`, que será chamado quando um método direto for chamado pelo IoT Hub. Cada método direto tem um nome, e este código espera um método chamado `relay_on` para ligar o relé e `relay_off` para desligá-lo.

    > 💁 Isso também poderia ser implementado em uma única solicitação de método direto, passando o estado desejado do relé em um payload que pode ser enviado com a solicitação de método e acessado a partir do objeto `request`.

1. Métodos diretos requerem uma resposta para informar ao código que os chamou que foram tratados. Adicione o seguinte código ao final da função `handle_method_request` para criar uma resposta à solicitação:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Este código envia uma resposta à solicitação de método direto com um código de status HTTP 200 e a envia de volta ao IoT Hub.

1. Adicione o seguinte código abaixo da definição desta função:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Este código informa ao cliente do IoT Hub para chamar a função `handle_method_request` quando um método direto for chamado.

> 💁 Você pode encontrar este código na pasta [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) ou [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Seu programa de sensor de umidade do solo está conectado ao seu IoT Hub!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.