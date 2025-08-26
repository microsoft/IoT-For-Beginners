<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T22:50:55+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "pt"
}
-->
# Conversão de fala para texto - Raspberry Pi

Nesta parte da lição, vais escrever código para converter a fala captada no áudio em texto, utilizando o serviço de fala.

## Enviar o áudio para o serviço de fala

O áudio pode ser enviado para o serviço de fala utilizando a API REST. Para usar o serviço de fala, primeiro precisas de solicitar um token de acesso e, em seguida, usar esse token para aceder à API REST. Estes tokens de acesso expiram após 10 minutos, por isso o teu código deve solicitá-los regularmente para garantir que estão sempre atualizados.

### Tarefa - obter um token de acesso

1. Abre o projeto `smart-timer` no teu Raspberry Pi.

1. Remove a função `play_audio`. Esta já não é necessária, pois não queres que o temporizador inteligente repita o que disseste.

1. Adiciona a seguinte importação no início do ficheiro `app.py`:

    ```python
    import requests
    ```

1. Adiciona o seguinte código acima do ciclo `while True` para declarar algumas definições para o serviço de fala:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Substitui `<key>` pela chave da API do teu recurso do serviço de fala. Substitui `<location>` pela localização que utilizaste ao criar o recurso do serviço de fala.

    Substitui `<language>` pelo nome do local para o idioma em que vais falar, por exemplo, `en-GB` para inglês ou `zn-HK` para cantonês. Podes encontrar uma lista dos idiomas suportados e os respetivos nomes de local na [documentação de suporte a idiomas e vozes nos Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Abaixo disto, adiciona a seguinte função para obter um token de acesso:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Esta função chama um endpoint de emissão de tokens, passando a chave da API como um cabeçalho. Esta chamada retorna um token de acesso que pode ser usado para chamar os serviços de fala.

1. A seguir, declara uma função para converter a fala captada no áudio em texto utilizando a API REST:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Dentro desta função, configura o URL da API REST e os cabeçalhos:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Isto constrói um URL utilizando a localização do recurso dos serviços de fala. Em seguida, preenche os cabeçalhos com o token de acesso da função `get_access_token`, bem como a taxa de amostragem usada para capturar o áudio. Por fim, define alguns parâmetros a serem passados com o URL, contendo o idioma do áudio.

1. Abaixo disto, adiciona o seguinte código para chamar a API REST e obter o texto de volta:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Esta chamada utiliza o URL e decodifica o valor JSON que vem na resposta. O valor `RecognitionStatus` na resposta indica se a chamada conseguiu extrair com sucesso a fala em texto e, se for `Success`, o texto é retornado pela função; caso contrário, é retornada uma string vazia.

1. Acima do ciclo `while True:`, define uma função para processar o texto retornado pelo serviço de conversão de fala para texto. Esta função, por agora, apenas imprimirá o texto no terminal.

    ```python
    def process_text(text):
        print(text)
    ```

1. Por fim, substitui a chamada para `play_audio` no ciclo `while True` por uma chamada para a função `convert_speech_to_text`, passando o texto para a função `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Executa o código. Pressiona o botão e fala para o microfone. Solta o botão quando terminares, e o áudio será convertido em texto e impresso no terminal.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Experimenta diferentes tipos de frases, incluindo frases onde as palavras têm o mesmo som, mas significados diferentes. Por exemplo, se estiveres a falar em inglês, diz "I want to buy two bananas and an apple too" e repara como ele utiliza corretamente "to", "two" e "too" com base no contexto da palavra, e não apenas no som.

> 💁 Podes encontrar este código na pasta [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 O teu programa de conversão de fala para texto foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.