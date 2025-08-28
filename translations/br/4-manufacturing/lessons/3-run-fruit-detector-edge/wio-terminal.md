<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T02:46:28+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "br"
}
-->
# Classifique uma imagem usando um classificador de imagens baseado em IoT Edge - Wio Terminal

Nesta parte da lição, você usará o Classificador de Imagens executando no dispositivo IoT Edge.

## Use o classificador IoT Edge

O dispositivo IoT pode ser redirecionado para usar o classificador de imagens do IoT Edge. A URL para o Classificador de Imagens é `http://<IP address or name>/image`, substituindo `<IP address or name>` pelo endereço IP ou nome do host do computador que está executando o IoT Edge.

### Tarefa - usar o classificador IoT Edge

1. Abra o projeto do aplicativo `fruit-quality-detector` caso ele ainda não esteja aberto.

1. O classificador de imagens está sendo executado como uma API REST usando HTTP, não HTTPS, então a chamada precisa usar um cliente WiFi que funcione apenas com chamadas HTTP. Isso significa que o certificado não é necessário. Exclua o `CERTIFICATE` do arquivo `config.h`.

1. A URL de previsão no arquivo `config.h` precisa ser atualizada para a nova URL. Você também pode excluir o `PREDICTION_KEY`, pois ele não é necessário.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Substitua `<URL>` pela URL do seu classificador.

1. No arquivo `main.cpp`, altere a diretiva de inclusão do WiFi Client Secure para importar a versão padrão HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Altere a declaração de `WiFiClient` para ser a versão HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Localize a linha que define o certificado no cliente WiFi. Remova a linha `client.setCACert(CERTIFICATE);` da função `connectWiFi`.

1. Na função `classifyImage`, remova a linha `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` que define a chave de previsão no cabeçalho.

1. Faça o upload e execute seu código. Aponte a câmera para alguma fruta e pressione o botão C. Você verá a saída no monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Você pode encontrar este código na pasta [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Seu programa de classificação de qualidade de frutas foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.