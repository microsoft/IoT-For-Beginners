<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-25T21:52:32+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "pt"
}
-->
# Utilize o certificado X.509 no código do seu dispositivo - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, irá conectar o seu dispositivo IoT virtual ou Raspberry Pi ao IoT Hub utilizando o certificado X.509.

## Conectar o seu dispositivo ao IoT Hub

O próximo passo é conectar o seu dispositivo ao IoT Hub utilizando os certificados X.509.

### Tarefa - conectar ao IoT Hub

1. Copie os ficheiros de chave e certificado para a pasta que contém o código do seu dispositivo IoT. Se estiver a usar um Raspberry Pi através do VS Code Remote SSH e criou as chaves no seu PC ou Mac, pode arrastar e largar os ficheiros no explorador do VS Code para os copiar.

1. Abra o ficheiro `app.py`.

1. Para conectar utilizando um certificado X.509, precisará do nome do host do IoT Hub e do certificado X.509. Comece por criar uma variável que contenha o nome do host, adicionando o seguinte código antes de criar o cliente do dispositivo:

    ```python
    host_name = "<host_name>"
    ```

    Substitua `<host_name>` pelo nome do host do seu IoT Hub. Pode encontrar esta informação na secção `HostName` da `connection_string`. Será o nome do seu IoT Hub, terminando com `.azure-devices.net`.

1. Abaixo disso, declare uma variável com o ID do dispositivo:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Precisará de uma instância da classe `X509` que contenha os ficheiros X.509. Adicione `X509` à lista de classes importadas do módulo `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Crie uma instância da classe `X509` utilizando os seus ficheiros de certificado e chave, adicionando este código abaixo da declaração de `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Isto criará a classe `X509` utilizando os ficheiros `soil-moisture-sensor-x509-cert.pem` e `soil-moisture-sensor-x509-key.pem` criados anteriormente.

1. Substitua a linha de código que cria o `device_client` a partir de uma connection string pela seguinte:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Isto conectará utilizando o certificado X.509 em vez de uma connection string.

1. Apague a linha com a variável `connection_string`.

1. Execute o seu código. Monitorize as mensagens enviadas ao IoT Hub e envie pedidos de método direto como antes. Verá o dispositivo conectar-se e enviar leituras de humidade do solo, bem como receber pedidos de método direto.

> 💁 Pode encontrar este código na pasta [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) ou [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 O programa do seu sensor de humidade do solo está conectado ao seu IoT Hub utilizando um certificado X.509!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.