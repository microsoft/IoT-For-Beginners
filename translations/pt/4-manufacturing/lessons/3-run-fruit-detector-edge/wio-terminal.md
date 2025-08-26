<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-25T21:08:56+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "pt"
}
-->
# Classificar uma imagem usando um classificador de imagens baseado em IoT Edge - Wio Terminal

Nesta parte da lição, irá utilizar o Classificador de Imagens que está a correr no dispositivo IoT Edge.

## Utilizar o classificador IoT Edge

O dispositivo IoT pode ser redirecionado para usar o classificador de imagens IoT Edge. O URL para o Classificador de Imagens é `http://<IP address or name>/image`, substituindo `<IP address or name>` pelo endereço IP ou nome do host do computador que está a executar o IoT Edge.

### Tarefa - utilizar o classificador IoT Edge

1. Abra o projeto da aplicação `fruit-quality-detector` caso ainda não esteja aberto.

1. O classificador de imagens está a correr como uma API REST usando HTTP, não HTTPS, por isso a chamada precisa de usar um cliente WiFi que funcione apenas com chamadas HTTP. Isto significa que o certificado não é necessário. Elimine o `CERTIFICATE` do ficheiro `config.h`.

1. O URL de previsão no ficheiro `config.h` precisa de ser atualizado para o novo URL. Também pode eliminar o `PREDICTION_KEY`, pois este não é necessário.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Substitua `<URL>` pelo URL do seu classificador.

1. No ficheiro `main.cpp`, altere a diretiva de inclusão do WiFi Client Secure para importar a versão padrão HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Altere a declaração de `WiFiClient` para ser a versão HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Selecione a linha que define o certificado no cliente WiFi. Remova a linha `client.setCACert(CERTIFICATE);` da função `connectWiFi`.

1. Na função `classifyImage`, remova a linha `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` que define a chave de previsão no cabeçalho.

1. Carregue e execute o seu código. Aponte a câmara para alguma fruta e pressione o botão C. Verá o resultado no monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Pode encontrar este código na pasta [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 O seu programa de classificação de qualidade de frutas foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.