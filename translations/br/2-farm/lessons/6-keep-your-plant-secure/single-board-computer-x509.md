<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T04:03:47+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "br"
}
-->
# Use o certificado X.509 no código do seu dispositivo - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, você conectará seu dispositivo IoT virtual ou Raspberry Pi ao IoT Hub usando o certificado X.509.

## Conecte seu dispositivo ao IoT Hub

O próximo passo é conectar seu dispositivo ao IoT Hub usando os certificados X.509.

### Tarefa - conectar ao IoT Hub

1. Copie os arquivos de chave e certificado para a pasta que contém o código do seu dispositivo IoT. Se você estiver usando um Raspberry Pi através do VS Code Remote SSH e criou as chaves no seu PC ou Mac, pode arrastar e soltar os arquivos no explorador do VS Code para copiá-los.

1. Abra o arquivo `app.py`.

1. Para conectar usando um certificado X.509, você precisará do nome do host do IoT Hub e do certificado X.509. Comece criando uma variável contendo o nome do host, adicionando o seguinte código antes de criar o cliente do dispositivo:

    ```python
    host_name = "<host_name>"
    ```

    Substitua `<host_name>` pelo nome do host do seu IoT Hub. Você pode obter isso na seção `HostName` da `connection_string`. Será o nome do seu IoT Hub, terminando com `.azure-devices.net`.

1. Abaixo disso, declare uma variável com o ID do dispositivo:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Você precisará de uma instância da classe `X509` contendo os arquivos X.509. Adicione `X509` à lista de classes importadas do módulo `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Crie uma instância da classe `X509` usando seus arquivos de certificado e chave, adicionando este código abaixo da declaração de `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Isso criará a classe `X509` usando os arquivos `soil-moisture-sensor-x509-cert.pem` e `soil-moisture-sensor-x509-key.pem` criados anteriormente.

1. Substitua a linha de código que cria o `device_client` a partir de uma connection string pelo seguinte:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Isso conectará usando o certificado X.509 em vez de uma connection string.

1. Exclua a linha com a variável `connection_string`.

1. Execute seu código. Monitore as mensagens enviadas ao IoT Hub e envie solicitações de método direto como antes. Você verá o dispositivo conectando e enviando leituras de umidade do solo, além de receber solicitações de método direto.

> 💁 Você pode encontrar este código na pasta [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) ou [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 O programa do sensor de umidade do solo está conectado ao seu IoT Hub usando um certificado X.509!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.