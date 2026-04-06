# Traduzir fala - Wio Terminal

Nesta parte da lição, você escreverá código para traduzir texto usando o serviço de tradução.

## Converter texto em fala usando o serviço de tradução

A API REST do serviço de fala não suporta traduções diretas. Em vez disso, você pode usar o serviço Translator para traduzir o texto gerado pelo serviço de fala para texto e o texto da resposta falada. Este serviço possui uma API REST que você pode usar para traduzir o texto, mas para facilitar o uso, ele será encapsulado em outro gatilho HTTP no seu aplicativo de funções.

### Tarefa - criar uma função serverless para traduzir texto

1. Abra seu projeto `smart-timer-trigger` no VS Code e abra o terminal, garantindo que o ambiente virtual esteja ativado. Caso contrário, encerre e recrie o terminal.

1. Abra o arquivo `local.settings.json` e adicione as configurações para a chave da API do Translator e a localização:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Substitua `<key>` pela chave da API do recurso do serviço de tradução. Substitua `<location>` pela localização usada ao criar o recurso do serviço de tradução.

1. Adicione um novo gatilho HTTP a este aplicativo chamado `translate-text` usando o seguinte comando no terminal do VS Code, na pasta raiz do projeto do aplicativo de funções:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Isso criará um gatilho HTTP chamado `translate-text`.

1. Substitua o conteúdo do arquivo `__init__.py` na pasta `translate-text` pelo seguinte:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Este código extrai o texto e os idiomas da solicitação HTTP. Em seguida, faz uma solicitação à API REST do Translator, passando os idiomas como parâmetros para a URL e o texto a ser traduzido como corpo. Por fim, a tradução é retornada.

1. Execute seu aplicativo de funções localmente. Você pode então chamá-lo usando uma ferramenta como curl da mesma forma que testou seu gatilho HTTP `text-to-timer`. Certifique-se de passar o texto a ser traduzido e os idiomas como um corpo JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Este exemplo traduz *Définir une minuterie de 30 secondes* do francês para o inglês dos EUA. Ele retornará *Set a 30-second timer*.

> 💁 Você pode encontrar este código na pasta [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Tarefa - usar a função de tradução para traduzir texto

1. Abra o projeto `smart-timer` no VS Code, caso ainda não esteja aberto.

1. Seu temporizador inteligente terá 2 idiomas configurados - o idioma do servidor usado para treinar o LUIS (o mesmo idioma também é usado para construir as mensagens para falar com o usuário) e o idioma falado pelo usuário. Atualize a constante `LANGUAGE` no arquivo de cabeçalho `config.h` para ser o idioma que será falado pelo usuário e adicione uma nova constante chamada `SERVER_LANGUAGE` para o idioma usado para treinar o LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Substitua `<user language>` pelo nome do local do idioma que você falará, por exemplo, `fr-FR` para francês ou `zn-HK` para cantonês.

    Substitua `<server language>` pelo nome do local do idioma usado para treinar o LUIS.

    Você pode encontrar uma lista dos idiomas suportados e seus nomes de local na [documentação de suporte de idioma e voz nos documentos da Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Se você não fala vários idiomas, pode usar um serviço como [Bing Translate](https://www.bing.com/translator) ou [Google Translate](https://translate.google.com) para traduzir do seu idioma preferido para um idioma de sua escolha. Esses serviços podem reproduzir áudio do texto traduzido.
    >
    > Por exemplo, se você treinar o LUIS em inglês, mas quiser usar francês como idioma do usuário, pode traduzir frases como "set a 2 minute and 27 second timer" do inglês para o francês usando o Bing Translate e, em seguida, usar o botão **Ouvir tradução** para falar a tradução no seu microfone.
    >
    > ![O botão ouvir tradução no Bing Translate](../../../../../translated_images/pt-BR/bing-translate.348aa796d6efe2a9.webp)

1. Adicione a chave da API do Translator e a localização abaixo de `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Substitua `<KEY>` pela chave da API do recurso do serviço de tradução. Substitua `<LOCATION>` pela localização usada ao criar o recurso do serviço de tradução.

1. Adicione a URL do gatilho do Translator abaixo de `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Substitua `<URL>` pela URL do gatilho HTTP `translate-text` no seu aplicativo de funções. Este será o mesmo valor de `TEXT_TO_TIMER_FUNCTION_URL`, exceto com um nome de função de `translate-text` em vez de `text-to-timer`.

1. Adicione um novo arquivo à pasta `src` chamado `text_translator.h`.

1. Este novo arquivo de cabeçalho `text_translator.h` conterá uma classe para traduzir texto. Adicione o seguinte a este arquivo para declarar esta classe:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Isso declara a classe `TextTranslator`, junto com uma instância desta classe. A classe possui um único campo para o cliente WiFi.

1. Na seção `public` desta classe, adicione um método para traduzir texto:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Este método recebe o idioma de origem e o idioma de destino. Ao lidar com fala, a fala será traduzida do idioma do usuário para o idioma do servidor LUIS, e ao fornecer respostas, será traduzida do idioma do servidor LUIS para o idioma do usuário.

1. Neste método, adicione código para construir um corpo JSON contendo o texto a ser traduzido e os idiomas:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Abaixo disso, adicione o seguinte código para enviar o corpo ao aplicativo de funções serverless:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Em seguida, adicione código para obter a resposta:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Por fim, adicione código para fechar a conexão e retornar o texto traduzido:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Tarefa - traduzir a fala reconhecida e as respostas

1. Abra o arquivo `main.cpp`.

1. Adicione uma diretiva de inclusão no topo do arquivo para o arquivo de cabeçalho da classe `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. O texto que é dito quando um temporizador é configurado ou expira precisa ser traduzido. Para fazer isso, adicione o seguinte como a primeira linha da função `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Isso traduzirá o texto para o idioma do usuário.

1. Na função `processAudio`, o texto é recuperado do áudio capturado com a chamada `String text = speechToText.convertSpeechToText();`. Após esta chamada, traduza o texto:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Isso traduzirá o texto do idioma do usuário para o idioma usado no servidor.

1. Compile este código, carregue-o no seu Wio Terminal e teste-o através do monitor serial. Assim que você vir `Ready` no monitor serial, pressione o botão C (o da esquerda, mais próximo ao interruptor de energia) e fale. Certifique-se de que seu aplicativo de funções esteja em execução e solicite um temporizador no idioma do usuário, seja falando esse idioma você mesmo ou usando um aplicativo de tradução.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Você pode encontrar este código na pasta [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Seu programa de temporizador multilíngue foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.