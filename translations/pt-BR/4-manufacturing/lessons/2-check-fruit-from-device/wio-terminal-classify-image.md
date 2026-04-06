# Classificar uma imagem - Wio Terminal

Nesta parte da lição, você enviará a imagem capturada pela câmera para o serviço Custom Vision para classificá-la.

## Classificar uma imagem

O serviço Custom Vision possui uma API REST que pode ser chamada a partir do Wio Terminal para classificar imagens. Essa API REST é acessada por meio de uma conexão HTTPS - uma conexão HTTP segura.

Ao interagir com endpoints HTTPS, o código cliente precisa solicitar o certificado de chave pública do servidor que está sendo acessado e usá-lo para criptografar o tráfego enviado. Seu navegador faz isso automaticamente, mas microcontroladores não. Você precisará solicitar esse certificado manualmente e usá-lo para criar uma conexão segura com a API REST. Esses certificados não mudam, então, uma vez que você tenha um certificado, ele pode ser codificado diretamente no seu aplicativo.

Esses certificados contêm chaves públicas e não precisam ser mantidos em segredo. Você pode usá-los no seu código-fonte e compartilhá-los publicamente em lugares como o GitHub.

### Tarefa - configurar um cliente SSL

1. Abra o projeto do aplicativo `fruit-quality-detector`, caso ainda não esteja aberto.

1. Abra o arquivo de cabeçalho `config.h` e adicione o seguinte:

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    Este é o *certificado Microsoft Azure DigiCert Global Root G2* - um dos certificados usados por muitos serviços Azure globalmente.

    > 💁 Para verificar que este é o certificado correto, execute o seguinte comando no macOS ou Linux. Se você estiver usando Windows, pode executar este comando usando o [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > A saída listará o certificado DigiCert Global Root G2.

1. Abra `main.cpp` e adicione a seguinte diretiva de inclusão:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Abaixo das diretivas de inclusão, declare uma instância de `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Esta classe contém o código para se comunicar com endpoints web via HTTPS.

1. No método `connectWiFi`, configure o WiFiClientSecure para usar o certificado DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Tarefa - classificar uma imagem

1. Adicione a seguinte linha adicional à lista `lib_deps` no arquivo `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Isso importa [ArduinoJson](https://arduinojson.org), uma biblioteca JSON para Arduino, que será usada para decodificar a resposta JSON da API REST.

1. Em `config.h`, adicione constantes para a URL de previsão e a chave do serviço Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Substitua `<PREDICTION_URL>` pela URL de previsão do Custom Vision. Substitua `<PREDICTION_KEY>` pela chave de previsão.

1. Em `main.cpp`, adicione uma diretiva de inclusão para a biblioteca ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Adicione a seguinte função em `main.cpp`, acima da função `buttonPressed`.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    Este código começa declarando um `HTTPClient` - uma classe que contém métodos para interagir com APIs REST. Em seguida, conecta o cliente à URL de previsão usando a instância `WiFiClientSecure` configurada com a chave pública do Azure.

    Uma vez conectado, ele envia cabeçalhos - informações sobre a solicitação que será feita contra a API REST. O cabeçalho `Content-Type` indica que a chamada da API enviará dados binários brutos, e o cabeçalho `Prediction-Key` passa a chave de previsão do Custom Vision.

    Em seguida, uma solicitação POST é feita ao cliente HTTP, enviando um array de bytes. Este array conterá a imagem JPEG capturada pela câmera quando esta função for chamada.

    > 💁 Solicitações POST são usadas para enviar dados e obter uma resposta. Existem outros tipos de solicitações, como as solicitações GET, que recuperam dados. Solicitações GET são usadas pelo seu navegador para carregar páginas web.

    A solicitação POST retorna um código de status de resposta. Esses valores são bem definidos, sendo 200 o código para **OK** - a solicitação POST foi bem-sucedida.

    > 💁 Você pode ver todos os códigos de status de resposta na [página Lista de códigos de status HTTP na Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Se um código 200 for retornado, o resultado é lido do cliente HTTP. Esta é uma resposta em texto da API REST com os resultados da previsão como um documento JSON. O JSON tem o seguinte formato:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    A parte importante aqui é o array `predictions`. Ele contém as previsões, com uma entrada para cada tag contendo o nome da tag e a probabilidade. As probabilidades retornadas são números de ponto flutuante de 0 a 1, sendo 0 uma chance de 0% de corresponder à tag e 1 uma chance de 100%.

    > 💁 Classificadores de imagem retornarão as porcentagens para todas as tags que foram usadas. Cada tag terá uma probabilidade de que a imagem corresponda àquela tag.

    Este JSON é decodificado, e as probabilidades de cada tag são enviadas ao monitor serial.

1. Na função `buttonPressed`, substitua o código que salva no cartão SD por uma chamada para `classifyImage`, ou adicione-o após a imagem ser gravada, mas **antes** do buffer ser excluído:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Se você substituir o código que salva no cartão SD, pode limpar seu código removendo as funções `setupSDCard` e `saveToSDCard`.

1. Faça o upload e execute seu código. Aponte a câmera para alguma fruta e pressione o botão C. Você verá a saída no monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Você poderá ver a imagem que foi capturada e esses valores na aba **Predictions** no Custom Vision.

    ![Uma banana no Custom Vision prevista como madura com 56.8% e não madura com 43.1%](../../../../../translated_images/pt-BR/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Você pode encontrar este código na pasta [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Seu programa de classificação de qualidade de frutas foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.