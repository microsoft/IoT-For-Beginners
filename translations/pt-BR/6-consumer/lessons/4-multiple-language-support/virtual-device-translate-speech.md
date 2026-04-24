# Traduzir fala - Dispositivo IoT Virtual

Nesta parte da lição, você escreverá código para traduzir fala ao convertê-la em texto usando o serviço de fala, e depois traduzir o texto usando o serviço Translator antes de gerar uma resposta falada.

## Usar o serviço de fala para traduzir fala

O serviço de fala pode pegar uma fala e não apenas convertê-la em texto no mesmo idioma, mas também traduzir a saída para outros idiomas.

### Tarefa - usar o serviço de fala para traduzir fala

1. Abra o projeto `smart-timer` no VS Code e certifique-se de que o ambiente virtual está carregado no terminal.

1. Adicione as seguintes declarações de importação abaixo das importações existentes:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Isso importa classes usadas para traduzir fala e uma biblioteca `requests` que será usada para fazer uma chamada ao serviço Translator mais adiante nesta lição.

1. Seu cronômetro inteligente terá 2 idiomas configurados - o idioma do servidor que foi usado para treinar o LUIS (o mesmo idioma também é usado para construir as mensagens faladas para o usuário) e o idioma falado pelo usuário. Atualize a variável `language` para ser o idioma que será falado pelo usuário e adicione uma nova variável chamada `server_language` para o idioma usado para treinar o LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Substitua `<user language>` pelo nome do local do idioma que você falará, por exemplo, `fr-FR` para francês ou `zn-HK` para cantonês.

    Substitua `<server language>` pelo nome do local do idioma usado para treinar o LUIS.

    Você pode encontrar uma lista dos idiomas suportados e seus nomes de local na [documentação de suporte a idiomas e vozes nos documentos da Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Se você não fala vários idiomas, pode usar um serviço como [Bing Translate](https://www.bing.com/translator) ou [Google Translate](https://translate.google.com) para traduzir do seu idioma preferido para um idioma de sua escolha. Esses serviços podem então reproduzir o áudio do texto traduzido. Esteja ciente de que o reconhecedor de fala ignorará algumas saídas de áudio do seu dispositivo, então você pode precisar usar um dispositivo adicional para reproduzir o texto traduzido.
    >
    > Por exemplo, se você treinar o LUIS em inglês, mas quiser usar francês como idioma do usuário, pode traduzir frases como "set a 2 minute and 27 second timer" de inglês para francês usando o Bing Translate, e depois usar o botão **Ouvir tradução** para falar a tradução no seu microfone.
    >
    > ![O botão ouvir tradução no Bing Translate](../../../../../translated_images/pt-BR/bing-translate.348aa796d6efe2a9.webp)

1. Substitua as declarações `recognizer_config` e `recognizer` pelo seguinte:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Isso cria uma configuração de tradução para reconhecer fala no idioma do usuário e criar traduções no idioma do usuário e no idioma do servidor. Em seguida, usa essa configuração para criar um reconhecedor de tradução - um reconhecedor de fala que pode traduzir a saída do reconhecimento de fala para vários idiomas.

    > 💁 O idioma original precisa ser especificado em `target_languages`, caso contrário, você não obterá nenhuma tradução.

1. Atualize a função `recognized`, substituindo todo o conteúdo da função pelo seguinte:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Este código verifica se o evento reconhecido foi acionado porque a fala foi traduzida (este evento pode ser acionado em outros momentos, como quando a fala é reconhecida, mas não traduzida). Se a fala foi traduzida, encontra a tradução no dicionário `args.result.translations` que corresponde ao idioma do servidor.

    O dicionário `args.result.translations` é indexado pela parte do idioma da configuração de local, não pela configuração completa. Por exemplo, se você solicitar uma tradução para `fr-FR` para francês, o dicionário conterá uma entrada para `fr`, não para `fr-FR`.

    O texto traduzido é então enviado para o IoT Hub.

1. Execute este código para testar as traduções. Certifique-se de que seu aplicativo de função está em execução e solicite um cronômetro no idioma do usuário, seja falando nesse idioma você mesmo ou usando um aplicativo de tradução.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Traduzir texto usando o serviço Translator

O serviço de fala não suporta a tradução de texto de volta para fala, em vez disso, você pode usar o serviço Translator para traduzir o texto. Este serviço possui uma API REST que você pode usar para traduzir o texto.

### Tarefa - usar o recurso Translator para traduzir texto

1. Adicione a chave da API do Translator abaixo da `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Substitua `<key>` pela chave da API do recurso do serviço Translator.

1. Acima da função `say`, defina uma função `translate_text` que traduzirá texto do idioma do servidor para o idioma do usuário:

    ```python
    def translate_text(text):
    ```

1. Dentro dessa função, defina a URL e os cabeçalhos para a chamada da API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    A URL para esta API não é específica de localização, em vez disso, a localização é passada como um cabeçalho. A chave da API é usada diretamente, então, ao contrário do serviço de fala, não há necessidade de obter um token de acesso da API emissora de tokens.

1. Abaixo disso, defina os parâmetros e o corpo para a chamada:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    Os `params` definem os parâmetros a serem passados para a chamada da API, especificando os idiomas de origem e destino. Esta chamada traduzirá texto no idioma `from` para o idioma `to`.

    O `body` contém o texto a ser traduzido. Este é um array, pois vários blocos de texto podem ser traduzidos na mesma chamada.

1. Faça a chamada para a API REST e obtenha a resposta:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    A resposta que retorna é um array JSON, com um item que contém as traduções. Este item possui um array para traduções de todos os itens passados no corpo.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Retorne a propriedade `text` da primeira tradução do primeiro item no array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Atualize a função `say` para traduzir o texto a ser dito antes que o SSML seja gerado:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Este código também imprime as versões original e traduzida do texto no console.

1. Execute seu código. Certifique-se de que seu aplicativo de função está em execução e solicite um cronômetro no idioma do usuário, seja falando nesse idioma você mesmo ou usando um aplicativo de tradução.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Devido às diferentes formas de dizer algo em diferentes idiomas, você pode obter traduções que são ligeiramente diferentes dos exemplos que você forneceu ao LUIS. Se for o caso, adicione mais exemplos ao LUIS, re-treine e publique novamente o modelo.

> 💁 Você pode encontrar este código na pasta [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Seu programa de cronômetro multilíngue foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.