<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-25T22:28:06+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "pt"
}
-->
# Traduzir discurso - Raspberry Pi

Nesta parte da lição, vais escrever código para traduzir texto utilizando o serviço de tradução.

## Converter texto em discurso utilizando o serviço de tradução

A API REST do serviço de discurso não suporta traduções diretas. Em vez disso, podes usar o serviço Translator para traduzir o texto gerado pelo serviço de conversão de discurso para texto e o texto da resposta falada. Este serviço tem uma API REST que podes usar para traduzir o texto.

### Tarefa - usar o recurso Translator para traduzir texto

1. O teu temporizador inteligente terá 2 idiomas definidos - o idioma do servidor que foi usado para treinar o LUIS (o mesmo idioma também é usado para construir as mensagens para falar com o utilizador) e o idioma falado pelo utilizador. Atualiza a variável `language` para ser o idioma que será falado pelo utilizador e adiciona uma nova variável chamada `server_language` para o idioma usado para treinar o LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Substitui `<user language>` pelo nome da localidade do idioma que vais falar, por exemplo, `fr-FR` para francês ou `zn-HK` para cantonês.

    Substitui `<server language>` pelo nome da localidade do idioma usado para treinar o LUIS.

    Podes encontrar uma lista dos idiomas suportados e os seus nomes de localidade na [documentação de suporte de idiomas e vozes nos Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Se não falas vários idiomas, podes usar um serviço como [Bing Translate](https://www.bing.com/translator) ou [Google Translate](https://translate.google.com) para traduzir do teu idioma preferido para um idioma à tua escolha. Estes serviços podem reproduzir áudio do texto traduzido.
    >
    > Por exemplo, se treinares o LUIS em inglês, mas quiseres usar francês como idioma do utilizador, podes traduzir frases como "set a 2 minute and 27 second timer" de inglês para francês usando o Bing Translate e, em seguida, usar o botão **Ouvir tradução** para falar a tradução no teu microfone.
    >
    > ![O botão ouvir tradução no Bing Translate](../../../../../translated_images/pt/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Adiciona a chave da API do Translator abaixo da `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Substitui `<key>` pela chave da API do recurso do serviço Translator.

1. Acima da função `say`, define uma função `translate_text` que irá traduzir texto do idioma do servidor para o idioma do utilizador:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Os idiomas de origem e destino são passados para esta função - a tua aplicação precisa de converter do idioma do utilizador para o idioma do servidor ao reconhecer discurso e do idioma do servidor para o idioma do utilizador ao fornecer feedback falado.

1. Dentro desta função, define o URL e os cabeçalhos para a chamada da API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    O URL desta API não é específico de localização; em vez disso, a localização é passada como um cabeçalho. A chave da API é usada diretamente, por isso, ao contrário do serviço de discurso, não é necessário obter um token de acesso da API emissora de tokens.

1. Abaixo disso, define os parâmetros e o corpo para a chamada:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    Os `params` definem os parâmetros a passar para a chamada da API, passando os idiomas de origem e destino. Esta chamada irá traduzir texto no idioma `from` para o idioma `to`.

    O `body` contém o texto a ser traduzido. Este é um array, pois vários blocos de texto podem ser traduzidos na mesma chamada.

1. Faz a chamada à API REST e obtém a resposta:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    A resposta que retorna é um array JSON, com um item que contém as traduções. Este item tem um array para as traduções de todos os itens passados no corpo.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Retorna a propriedade `text` da primeira tradução do primeiro item no array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Atualiza o loop `while True` para traduzir o texto da chamada para `convert_speech_to_text` do idioma do utilizador para o idioma do servidor:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Este código também imprime as versões original e traduzida do texto na consola.

1. Atualiza a função `say` para traduzir o texto a ser dito do idioma do servidor para o idioma do utilizador:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Este código também imprime as versões original e traduzida do texto na consola.

1. Executa o teu código. Certifica-te de que a tua aplicação de função está a funcionar e solicita um temporizador no idioma do utilizador, seja falando esse idioma tu mesmo ou usando uma aplicação de tradução.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Devido às diferentes formas de dizer algo em diferentes idiomas, podes obter traduções que são ligeiramente diferentes dos exemplos que deste ao LUIS. Se for o caso, adiciona mais exemplos ao LUIS, treina novamente e publica o modelo.

> 💁 Podes encontrar este código na pasta [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 O teu programa de temporizador multilingue foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.