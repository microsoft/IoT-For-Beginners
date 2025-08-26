<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T22:47:55+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "pt"
}
-->
# Fala para texto - Wio Terminal

Nesta parte da lição, vais escrever código para converter fala captada no áudio em texto utilizando o serviço de fala.

## Enviar o áudio para o serviço de fala

O áudio pode ser enviado para o serviço de fala utilizando a API REST. Para usar o serviço de fala, primeiro precisas de solicitar um token de acesso e, em seguida, usar esse token para aceder à API REST. Estes tokens de acesso expiram após 10 minutos, por isso o teu código deve solicitá-los regularmente para garantir que estão sempre atualizados.

### Tarefa - obter um token de acesso

1. Abre o projeto `smart-timer` caso ainda não esteja aberto.

1. Adiciona as seguintes dependências de biblioteca ao ficheiro `platformio.ini` para aceder ao WiFi e manipular JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Adiciona o seguinte código ao ficheiro de cabeçalho `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Substitui `<SSID>` e `<PASSWORD>` pelos valores relevantes para o teu WiFi.

    Substitui `<API_KEY>` pela chave de API do recurso do serviço de fala. Substitui `<LOCATION>` pela localização que utilizaste ao criar o recurso do serviço de fala.

    Substitui `<LANGUAGE>` pelo nome do local para o idioma em que vais falar, por exemplo, `en-GB` para inglês ou `zn-HK` para cantonês. Podes encontrar uma lista dos idiomas suportados e os seus nomes de local na [documentação de suporte de idiomas e vozes nos Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    A constante `TOKEN_URL` é o URL do emissor de tokens sem a localização. Este será combinado com a localização mais tarde para obter o URL completo.

1. Tal como na conexão ao Custom Vision, vais precisar de usar uma conexão HTTPS para ligar ao serviço emissor de tokens. No final do ficheiro `config.h`, adiciona o seguinte código:

    ```cpp
    const char *TOKEN_CERTIFICATE =
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

    Este é o mesmo certificado que utilizaste ao conectar ao Custom Vision.

1. Adiciona um include para o ficheiro de cabeçalho do WiFi e o ficheiro de cabeçalho de configuração no topo do ficheiro `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Adiciona código para conectar ao WiFi em `main.cpp` acima da função `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

1. Chama esta função a partir da função `setup` após a conexão serial ter sido estabelecida:

    ```cpp
    connectWiFi();
    ```

1. Cria um novo ficheiro de cabeçalho na pasta `src` chamado `speech_to_text.h`. Neste ficheiro de cabeçalho, adiciona o seguinte código:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    Isto inclui alguns ficheiros de cabeçalho necessários para uma conexão HTTP, configuração e o ficheiro de cabeçalho `mic.h`, e define uma classe chamada `SpeechToText`, antes de declarar uma instância dessa classe que pode ser usada mais tarde.

1. Adiciona os seguintes 2 campos à secção `private` desta classe:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    O `_token_client` é um cliente WiFi que usa HTTPS e será usado para obter o token de acesso. Este token será então armazenado em `_access_token`.

1. Adiciona o seguinte método à secção `private`:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    Este código constrói o URL para a API do emissor de tokens usando a localização do recurso de fala. Em seguida, cria um `HTTPClient` para fazer a solicitação web, configurando-o para usar o cliente WiFi configurado com o certificado dos endpoints de token. Define a chave de API como um cabeçalho para a chamada. Faz uma solicitação POST para obter o certificado, tentando novamente se ocorrerem erros. Finalmente, o token de acesso é retornado.

1. Na secção `public`, adiciona um método para obter o token de acesso. Este será necessário em lições posteriores para converter texto em fala.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Na secção `public`, adiciona um método `init` que configura o cliente de token:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Isto define o certificado no cliente WiFi e, em seguida, obtém o token de acesso.

1. Em `main.cpp`, adiciona este novo ficheiro de cabeçalho às diretivas de inclusão:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicializa a classe `SpeechToText` no final da função `setup`, após a chamada `mic.init`, mas antes de `Ready` ser escrito no monitor serial:

    ```cpp
    speechToText.init();
    ```

### Tarefa - ler áudio da memória flash

1. Numa parte anterior desta lição, o áudio foi gravado na memória flash. Este áudio precisará de ser enviado para a API REST do Speech Services, por isso precisa de ser lido da memória flash. Não pode ser carregado num buffer em memória, pois seria demasiado grande. A classe `HTTPClient` que faz chamadas REST pode transmitir dados usando um Arduino Stream - uma classe que pode carregar dados em pequenos blocos, enviando os blocos um de cada vez como parte da solicitação. Sempre que chamas `read` num stream, ele retorna o próximo bloco de dados. Um stream Arduino pode ser criado para ler da memória flash. Cria um novo ficheiro chamado `flash_stream.h` na pasta `src` e adiciona o seguinte código:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    Isto declara a classe `FlashStream`, derivada da classe `Stream` do Arduino. Esta é uma classe abstrata - classes derivadas têm de implementar alguns métodos antes que a classe possa ser instanciada, e esses métodos são definidos nesta classe.

    ✅ Lê mais sobre Streams do Arduino na [documentação de Streams do Arduino](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Adiciona os seguintes campos à secção `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Isto define um buffer temporário para armazenar dados lidos da memória flash, juntamente com campos para armazenar a posição atual ao ler do buffer, o endereço atual para ler da memória flash e o dispositivo de memória flash.

1. Na secção `private`, adiciona o seguinte método:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Este código lê da memória flash no endereço atual e armazena os dados num buffer. Em seguida, incrementa o endereço, para que a próxima chamada leia o próximo bloco de memória. O buffer é dimensionado com base no maior bloco que o `HTTPClient` enviará para a API REST de uma só vez.

    > 💁 Apagar memória flash tem de ser feito usando o tamanho do grão, ler, por outro lado, não.

1. Na secção `public` desta classe, adiciona um construtor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Este construtor configura todos os campos para começar a ler do início do bloco de memória flash e carrega o primeiro bloco de dados no buffer.

1. Implementa o método `write`. Este stream apenas lerá dados, por isso pode não fazer nada e retornar 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementa o método `peek`. Este retorna os dados na posição atual sem mover o stream. Chamar `peek` várias vezes sempre retornará os mesmos dados enquanto nenhum dado for lido do stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementa a função `available`. Esta retorna quantos bytes podem ser lidos do stream ou -1 se o stream estiver completo. Para esta classe, o máximo disponível será no máximo o tamanho do bloco do HTTPClient. Quando este stream é usado no cliente HTTP, ele chama esta função para ver quantos dados estão disponíveis e, em seguida, solicita essa quantidade de dados para enviar para a API REST. Não queremos que cada bloco seja maior do que o tamanho do bloco do cliente HTTP, por isso, se mais do que isso estiver disponível, o tamanho do bloco é retornado. Se menos, então o que está disponível é retornado. Uma vez que todos os dados tenham sido transmitidos, -1 é retornado.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. Implementa o método `read` para retornar o próximo byte do buffer, incrementando a posição. Se a posição exceder o tamanho do buffer, ele preenche o buffer com o próximo bloco da memória flash e redefine a posição.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. No ficheiro de cabeçalho `speech_to_text.h`, adiciona uma diretiva de inclusão para este novo ficheiro de cabeçalho:

    ```cpp
    #include "flash_stream.h"
    ```

### Tarefa - converter a fala em texto

1. A fala pode ser convertida em texto enviando o áudio para o Serviço de Fala através de uma API REST. Esta API REST tem um certificado diferente do emissor de tokens, por isso adiciona o seguinte código ao ficheiro de cabeçalho `config.h` para definir este certificado:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Adiciona uma constante a este ficheiro para o URL de fala sem a localização. Este será combinado com a localização e o idioma mais tarde para obter o URL completo.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. No ficheiro de cabeçalho `speech_to_text.h`, na secção `private` da classe `SpeechToText`, define um campo para um cliente WiFi usando o certificado de fala:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. No método `init`, define o certificado neste cliente WiFi:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Adiciona o seguinte código à secção `public` da classe `SpeechToText` para definir um método para converter fala em texto:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Adiciona o seguinte código a este método para criar um cliente HTTP usando o cliente WiFi configurado com o certificado de fala e usando o URL de fala definido com a localização e o idioma:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Alguns cabeçalhos precisam de ser definidos na conexão:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Isto define cabeçalhos para a autorização usando o token de acesso, o formato de áudio usando a taxa de amostragem e define que o cliente espera o resultado como JSON.

1. Após isto, adiciona o seguinte código para fazer a chamada à API REST:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Isto cria um `FlashStream` e usa-o para transmitir dados para a API REST.

1. Abaixo disto, adiciona o seguinte código:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Este código verifica o código de resposta.

    Se for 200, o código para sucesso, então o resultado é recuperado, decodificado de JSON, e a propriedade `DisplayText` é definida na variável `text`. Esta é a propriedade onde a versão em texto da fala é retornada.

    Se o código de resposta for 401, então o token de acesso expirou (estes tokens só duram 10 minutos). Um novo token de acesso é solicitado e a chamada é feita novamente.

    Caso contrário, um erro é enviado ao monitor serial e o `text` é deixado em branco.

1. Adiciona o seguinte código ao final deste método para fechar o cliente HTTP e retornar o texto:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Em `main.cpp`, chama este novo método `convertSpeechToText` na função `processAudio`, depois regista a fala no monitor serial:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Compila este código, carrega-o no teu Wio Terminal e testa-o através do monitor serial. Assim que vires `Ready` no monitor serial, pressiona o botão C (o que está do lado esquerdo, mais próximo do interruptor de energia) e fala. Serão capturados 4 segundos de áudio, que serão convertidos em texto.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    ```

> 💁 Podes encontrar este código na pasta [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 O teu programa de fala para texto foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.