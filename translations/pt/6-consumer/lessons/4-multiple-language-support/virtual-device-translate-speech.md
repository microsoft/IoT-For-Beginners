<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-25T22:28:59+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "pt"
}
-->
# Traduzir fala - Dispositivo Virtual IoT

Nesta parte da lição, vais escrever código para traduzir fala ao convertê-la em texto usando o serviço de fala, e depois traduzir o texto usando o serviço Translator antes de gerar uma resposta falada.

## Usar o serviço de fala para traduzir fala

O serviço de fala pode captar fala e não só convertê-la em texto na mesma língua, mas também traduzir o resultado para outras línguas.

### Tarefa - usar o serviço de fala para traduzir fala

1. Abre o projeto `smart-timer` no VS Code e certifica-te de que o ambiente virtual está carregado no terminal.

1. Adiciona as seguintes instruções de importação abaixo das importações existentes:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Isto importa classes usadas para traduzir fala e uma biblioteca `requests` que será usada para fazer uma chamada ao serviço Translator mais tarde nesta lição.

1. O teu temporizador inteligente terá 2 línguas definidas - a língua do servidor que foi usada para treinar o LUIS (a mesma língua também é usada para construir as mensagens para falar com o utilizador) e a língua falada pelo utilizador. Atualiza a variável `language` para ser a língua que será falada pelo utilizador e adiciona uma nova variável chamada `server_language` para a língua usada para treinar o LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Substitui `<user language>` pelo nome do locale da língua que vais falar, por exemplo, `fr-FR` para Francês ou `zn-HK` para Cantonês.

    Substitui `<server language>` pelo nome do locale da língua usada para treinar o LUIS.

    Podes encontrar uma lista das línguas suportadas e os seus nomes de locale na [documentação de suporte de línguas e vozes nos Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Se não falas várias línguas, podes usar um serviço como [Bing Translate](https://www.bing.com/translator) ou [Google Translate](https://translate.google.com) para traduzir da tua língua preferida para uma língua à tua escolha. Estes serviços podem reproduzir áudio do texto traduzido. Tem em atenção que o reconhecedor de fala ignorará algum áudio reproduzido pelo teu dispositivo, por isso podes precisar de usar um dispositivo adicional para reproduzir o texto traduzido.
    >
    > Por exemplo, se treinares o LUIS em Inglês, mas quiseres usar Francês como a língua do utilizador, podes traduzir frases como "set a 2 minute and 27 second timer" de Inglês para Francês usando o Bing Translate, e depois usar o botão **Listen translation** para falar a tradução no teu microfone.
    >
    > ![O botão de ouvir tradução no Bing Translate](../../../../../translated_images/pt/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Substitui as declarações `recognizer_config` e `recognizer` pelo seguinte:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Isto cria uma configuração de tradução para reconhecer fala na língua do utilizador e criar traduções na língua do utilizador e na língua do servidor. Depois usa esta configuração para criar um reconhecedor de tradução - um reconhecedor de fala que pode traduzir o resultado do reconhecimento de fala para várias línguas.

    > 💁 A língua original precisa de ser especificada em `target_languages`, caso contrário não obterás nenhuma tradução.

1. Atualiza a função `recognized`, substituindo todo o conteúdo da função pelo seguinte:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Este código verifica se o evento reconhecido foi acionado porque a fala foi traduzida (este evento pode ser acionado em outros momentos, como quando a fala é reconhecida mas não traduzida). Se a fala foi traduzida, encontra a tradução no dicionário `args.result.translations` que corresponde à língua do servidor.

    O dicionário `args.result.translations` é indexado pela parte da língua da configuração do locale, não pela configuração completa. Por exemplo, se pedires uma tradução para `fr-FR` para Francês, o dicionário conterá uma entrada para `fr`, não para `fr-FR`.

    O texto traduzido é então enviado para o IoT Hub.

1. Executa este código para testar as traduções. Certifica-te de que a tua aplicação de função está a correr e pede um temporizador na língua do utilizador, seja falando essa língua tu mesmo ou usando uma aplicação de tradução.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Traduzir texto usando o serviço Translator

O serviço de fala não suporta tradução de texto de volta para fala, em vez disso podes usar o serviço Translator para traduzir o texto. Este serviço tem uma API REST que podes usar para traduzir o texto.

### Tarefa - usar o recurso Translator para traduzir texto

1. Adiciona a chave da API do Translator abaixo da `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Substitui `<key>` pela chave da API para o recurso do serviço Translator.

1. Acima da função `say`, define uma função `translate_text` que irá traduzir texto da língua do servidor para a língua do utilizador:

    ```python
    def translate_text(text):
    ```

1. Dentro desta função, define o URL e os cabeçalhos para a chamada da API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    O URL para esta API não é específico da localização, em vez disso, a localização é passada como um cabeçalho. A chave da API é usada diretamente, por isso, ao contrário do serviço de fala, não há necessidade de obter um token de acesso da API emissora de tokens.

1. Abaixo disto, define os parâmetros e o corpo para a chamada:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    Os `params` definem os parâmetros a passar para a chamada da API, passando as línguas de origem e destino. Esta chamada irá traduzir texto na língua `from` para a língua `to`.

    O `body` contém o texto a traduzir. Isto é um array, pois múltiplos blocos de texto podem ser traduzidos na mesma chamada.

1. Faz a chamada à API REST e obtém a resposta:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    A resposta que retorna é um array JSON, com um item que contém as traduções. Este item tem um array para traduções de todos os itens passados no corpo.

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

1. Retorna a propriedade `text` da primeira tradução do primeiro item no array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Atualiza a função `say` para traduzir o texto a ser dito antes de o SSML ser gerado:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Este código também imprime as versões original e traduzida do texto na consola.

1. Executa o teu código. Certifica-te de que a tua aplicação de função está a correr e pede um temporizador na língua do utilizador, seja falando essa língua tu mesmo ou usando uma aplicação de tradução.

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

    > 💁 Devido às diferentes formas de dizer algo em diferentes línguas, podes obter traduções que são ligeiramente diferentes dos exemplos que deste ao LUIS. Se for o caso, adiciona mais exemplos ao LUIS, treina novamente e publica o modelo.

> 💁 Podes encontrar este código na pasta [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 O teu programa de temporizador multilingue foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.