<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T22:38:18+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "pt"
}
-->
# Texto para fala - Wio Terminal

Nesta parte da lição, irá converter texto em fala para fornecer feedback falado.

## Texto para fala

O SDK dos serviços de fala que utilizou na última lição para converter fala em texto pode ser usado para converter texto de volta em fala.

## Obter uma lista de vozes

Ao solicitar fala, é necessário fornecer a voz a ser usada, pois a fala pode ser gerada utilizando uma variedade de vozes diferentes. Cada idioma suporta uma gama de vozes distintas, e pode obter a lista de vozes suportadas para cada idioma a partir do SDK dos serviços de fala. Aqui entram as limitações dos microcontroladores - a chamada para obter a lista de vozes suportadas pelos serviços de texto para fala é um documento JSON com mais de 77KB de tamanho, demasiado grande para ser processado pelo Wio Terminal. No momento da escrita, a lista completa contém 215 vozes, cada uma definida por um documento JSON como o seguinte:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Este JSON é para a voz **Aria**, que tem vários estilos de voz. Tudo o que é necessário ao converter texto em fala é o nome curto, `en-US-AriaNeural`.

Em vez de descarregar e decodificar esta lista inteira no seu microcontrolador, precisará escrever algum código sem servidor para recuperar a lista de vozes para o idioma que está a usar e chamar isto a partir do seu Wio Terminal. O seu código pode então escolher uma voz apropriada da lista, como a primeira que encontrar.

### Tarefa - criar uma função sem servidor para obter uma lista de vozes

1. Abra o seu projeto `smart-timer-trigger` no VS Code e abra o terminal, garantindo que o ambiente virtual está ativado. Caso contrário, encerre e recrie o terminal.

1. Abra o ficheiro `local.settings.json` e adicione configurações para a chave da API de fala e localização:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Substitua `<key>` pela chave da API do recurso de serviço de fala. Substitua `<location>` pela localização que utilizou ao criar o recurso de serviço de fala.

1. Adicione um novo trigger HTTP a esta aplicação chamado `get-voices` usando o seguinte comando dentro do terminal do VS Code na pasta raiz do projeto da aplicação de funções:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Isto criará um trigger HTTP chamado `get-voices`.

1. Substitua o conteúdo do ficheiro `__init__.py` na pasta `get-voices` pelo seguinte:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Este código faz uma solicitação HTTP ao endpoint para obter as vozes. Esta lista de vozes é um grande bloco de JSON com vozes para todos os idiomas, então as vozes para o idioma passado no corpo da solicitação são filtradas, e o nome curto é extraído e retornado como uma lista JSON. O nome curto é o valor necessário para converter texto em fala, então apenas este valor é retornado.

    > 💁 Pode alterar o filtro conforme necessário para selecionar apenas as vozes que deseja.

    Isto reduz o tamanho dos dados de 77KB (no momento da escrita) para um documento JSON muito menor. Por exemplo, para vozes dos EUA, isto é 408 bytes.

1. Execute a sua aplicação de funções localmente. Pode então chamá-la usando uma ferramenta como curl da mesma forma que testou o trigger HTTP `text-to-timer`. Certifique-se de passar o seu idioma como um corpo JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Substitua `<language>` pelo seu idioma, como `en-GB` ou `zh-CN`.

> 💁 Pode encontrar este código na pasta [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tarefa - recuperar a voz do seu Wio Terminal

1. Abra o projeto `smart-timer` no VS Code, caso ainda não esteja aberto.

1. Abra o ficheiro de cabeçalho `config.h` e adicione o URL para a sua aplicação de funções:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Substitua `<URL>` pelo URL do trigger HTTP `get-voices` na sua aplicação de funções. Este será o mesmo valor de `TEXT_TO_TIMER_FUNCTION_URL`, exceto com um nome de função `get-voices` em vez de `text-to-timer`.

1. Crie um novo ficheiro na pasta `src` chamado `text_to_speech.h`. Este será usado para definir uma classe para converter de texto para fala.

1. Adicione as seguintes diretivas de inclusão ao topo do novo ficheiro `text_to_speech.h`:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Adicione o seguinte código abaixo para declarar a classe `TextToSpeech`, juntamente com uma instância que pode ser usada no resto da aplicação:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Para chamar a sua aplicação de funções, precisa declarar um cliente WiFi. Adicione o seguinte à seção `private` da classe:

    ```cpp
    WiFiClient _client;
    ```

1. Na seção `private`, adicione um campo para a voz selecionada:

    ```cpp
    String _voice;
    ```

1. Na seção `public`, adicione uma função `init` que irá obter a primeira voz:

    ```cpp
    void init()
    {
    }
    ```

1. Para obter as vozes, um documento JSON precisa ser enviado à aplicação de funções com o idioma. Adicione o seguinte código à função `init` para criar este documento JSON:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Em seguida, crie um `HTTPClient` e use-o para chamar a aplicação de funções para obter as vozes, enviando o documento JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Abaixo disso, adicione código para verificar o código de resposta e, se for 200 (sucesso), então extraia a lista de vozes, recuperando a primeira da lista:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Após isso, encerre a conexão do cliente HTTP:

    ```cpp
    httpClient.end();
    ```

1. Abra o ficheiro `main.cpp` e adicione a seguinte diretiva de inclusão no topo para incluir este novo ficheiro de cabeçalho:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Na função `setup`, abaixo da chamada para `speechToText.init();`, adicione o seguinte para inicializar a classe `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Compile este código, carregue-o no seu Wio Terminal e teste-o através do monitor serial. Certifique-se de que a sua aplicação de funções está em execução.

    Verá a lista de vozes disponíveis retornada pela aplicação de funções, juntamente com a voz selecionada.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Converter texto em fala

Depois de ter uma voz para usar, ela pode ser usada para converter texto em fala. As mesmas limitações de memória com vozes também se aplicam ao converter texto em fala, então precisará gravar a fala num cartão SD pronto para ser reproduzido através do ReSpeaker.

> 💁 Em lições anteriores deste projeto, utilizou memória flash para armazenar fala capturada do microfone. Esta lição utiliza um cartão SD, pois é mais fácil reproduzir áudio a partir dele usando as bibliotecas de áudio da Seeed.

Há também outra limitação a considerar, os dados de áudio disponíveis do serviço de fala e os formatos que o Wio Terminal suporta. Ao contrário de computadores completos, as bibliotecas de áudio para microcontroladores podem ser muito limitadas nos formatos de áudio que suportam. Por exemplo, a biblioteca Seeed Arduino Audio que pode reproduzir som através do ReSpeaker só suporta áudio com uma taxa de amostragem de 44.1KHz. Os serviços de fala da Azure podem fornecer áudio em vários formatos, mas nenhum deles utiliza esta taxa de amostragem, fornecendo apenas 8KHz, 16KHz, 24KHz e 48KHz. Isto significa que o áudio precisa ser reamostrado para 44.1KHz, algo que exigiria mais recursos do que o Wio Terminal possui, especialmente memória.

Quando é necessário manipular dados como este, é frequentemente melhor usar código sem servidor, especialmente se os dados forem obtidos através de uma chamada web. O Wio Terminal pode chamar uma função sem servidor, passando o texto a ser convertido, e a função sem servidor pode tanto chamar o serviço de fala para converter texto em fala, como também reamostrar o áudio para a taxa de amostragem necessária. Pode então retornar o áudio no formato que o Wio Terminal precisa para ser armazenado no cartão SD e reproduzido através do ReSpeaker.

### Tarefa - criar uma função sem servidor para converter texto em fala

1. Abra o seu projeto `smart-timer-trigger` no VS Code e abra o terminal, garantindo que o ambiente virtual está ativado. Caso contrário, encerre e recrie o terminal.

1. Adicione um novo trigger HTTP a esta aplicação chamado `text-to-speech` usando o seguinte comando dentro do terminal do VS Code na pasta raiz do projeto da aplicação de funções:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Isto criará um trigger HTTP chamado `text-to-speech`.

1. O pacote Pip [librosa](https://librosa.org) tem funções para reamostrar áudio, então adicione-o ao ficheiro `requirements.txt`:

    ```sh
    librosa
    ```

    Depois de adicionar isto, instale os pacotes Pip usando o seguinte comando no terminal do VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Se estiver a usar Linux, incluindo Raspberry Pi OS, pode precisar instalar `libsndfile` com o seguinte comando:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Para converter texto em fala, não pode usar diretamente a chave da API de fala, em vez disso, precisa solicitar um token de acesso, usando a chave da API para autenticar a solicitação do token de acesso. Abra o ficheiro `__init__.py` da pasta `text-to-speech` e substitua todo o código nele pelo seguinte:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Isto define constantes para a localização e chave de fala que serão lidas das configurações. Em seguida, define a função `get_access_token` que irá recuperar um token de acesso para o serviço de fala.

1. Abaixo deste código, adicione o seguinte:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Isto define o trigger HTTP que converte o texto em fala. Extrai o texto a ser convertido, o idioma e a voz do corpo JSON enviado na solicitação, constrói algum SSML para solicitar a fala, e então chama a API REST relevante autenticando usando o token de acesso. Esta chamada à API REST retorna o áudio codificado como um ficheiro WAV mono de 16 bits e 48KHz, definido pelo valor de `playback_format`, que é enviado na chamada à API REST.

    Isto é então reamostrado por `librosa` de uma taxa de amostragem de 48KHz para uma taxa de amostragem de 44.1KHz, e este áudio é guardado num buffer binário que é então retornado.

1. Execute a sua aplicação de funções localmente ou implemente-a na nuvem. Pode então chamá-la usando uma ferramenta como curl da mesma forma que testou o trigger HTTP `text-to-timer`. Certifique-se de passar o idioma, voz e texto como corpo JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Substitua `<language>` pelo seu idioma, como `en-GB` ou `zh-CN`. Substitua `<voice>` pela voz que deseja usar. Substitua `<text>` pelo texto que deseja converter em fala. Pode guardar o resultado num ficheiro e reproduzi-lo com qualquer leitor de áudio que suporte ficheiros WAV.

    Por exemplo, para converter "Hello" em fala usando inglês dos EUA com a voz Jenny Neural, com a aplicação de funções a ser executada localmente, pode usar o seguinte comando curl:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Isto irá guardar o áudio em `hello.wav` no diretório atual.

> 💁 Pode encontrar este código na pasta [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tarefa - recuperar a fala do seu Wio Terminal

1. Abra o projeto `smart-timer` no VS Code, caso ainda não esteja aberto.

1. Abra o ficheiro de cabeçalho `config.h` e adicione o URL para a sua aplicação de funções:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Substitua `<URL>` pelo URL do trigger HTTP `text-to-speech` na sua aplicação de funções. Este será o mesmo valor de `TEXT_TO_TIMER_FUNCTION_URL`, exceto com um nome de função `text-to-speech` em vez de `text-to-timer`.

1. Abra o ficheiro de cabeçalho `text_to_speech.h` e adicione o seguinte método à seção `public` da classe `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Ao método `convertTextToSpeech`, adicione o seguinte código para criar o JSON a ser enviado à aplicação de funções:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Isto escreve o idioma, voz e texto no documento JSON e, em seguida, serializa-o para uma string.

1. Abaixo disso, adicione o seguinte código para chamar a aplicação de funções:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Isto cria um `HTTPClient` e faz uma solicitação POST usando o documento JSON ao trigger HTTP de texto para fala.

1. Se a chamada funcionar, os dados binários brutos retornados pela chamada à aplicação de funções podem ser transmitidos para um ficheiro no cartão SD. Adicione o seguinte código para fazer isso:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Este código verifica a resposta e, se for 200 (sucesso), os dados binários são transmitidos para um ficheiro na raiz do cartão SD chamado `SPEECH.WAV`.

1. No final deste método, feche a conexão HTTP:

    ```cpp
    httpClient.end();
    ```

1. O texto a ser falado pode agora ser convertido em áudio. No ficheiro `main.cpp`, adicione a seguinte linha ao final da função `say` para converter o texto a ser dito em áudio:
### Tarefa - reproduzir áudio no seu Wio Terminal

**Em breve**

## Implantar a sua aplicação de funções na nuvem

O motivo para executar a aplicação de funções localmente é que o pacote `librosa` do Pip no Linux tem uma dependência de uma biblioteca que não está instalada por padrão e precisará ser instalada antes que a aplicação de funções possa ser executada. Aplicações de funções são sem servidor - não há servidores que você possa gerenciar diretamente, então não há como instalar essa biblioteca antecipadamente.

A maneira de resolver isso é implantar a sua aplicação de funções usando um contêiner Docker. Este contêiner é implantado pela nuvem sempre que é necessário iniciar uma nova instância da sua aplicação de funções (como quando a demanda excede os recursos disponíveis ou se a aplicação de funções não foi usada por um tempo e foi encerrada).

Você pode encontrar as instruções para configurar uma aplicação de funções e implantá-la via Docker na [documentação sobre criar uma função no Linux usando uma imagem personalizada no Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Depois de implantada, você pode adaptar o código do seu Wio Terminal para acessar essa função:

1. Adicione o certificado do Azure Functions ao `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Altere todas as inclusões de `<WiFiClient.h>` para `<WiFiClientSecure.h>`.

1. Substitua todos os campos `WiFiClient` por `WiFiClientSecure`.

1. Em cada classe que tenha um campo `WiFiClientSecure`, adicione um construtor e configure o certificado nesse construtor:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.