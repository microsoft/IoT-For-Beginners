<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T03:04:38+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "br"
}
-->
# Fala para texto - Raspberry Pi

Nesta parte da lição, você escreverá um código para converter a fala capturada no áudio em texto usando o serviço de fala.

## Enviar o áudio para o serviço de fala

O áudio pode ser enviado para o serviço de fala usando a API REST. Para usar o serviço de fala, primeiro você precisa solicitar um token de acesso e, em seguida, usar esse token para acessar a API REST. Esses tokens de acesso expiram após 10 minutos, então seu código deve solicitá-los regularmente para garantir que estejam sempre atualizados.

### Tarefa - obter um token de acesso

1. Abra o projeto `smart-timer` no seu Raspberry Pi.

1. Remova a função `play_audio`. Ela não é mais necessária, já que você não quer que o temporizador inteligente repita o que você disse.

1. Adicione a seguinte importação no topo do arquivo `app.py`:

    ```python
    import requests
    ```

1. Adicione o seguinte código acima do loop `while True` para declarar algumas configurações para o serviço de fala:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Substitua `<key>` pela chave da API do recurso do serviço de fala. Substitua `<location>` pela localização que você usou ao criar o recurso do serviço de fala.

    Substitua `<language>` pelo nome do local para o idioma que você estará falando, por exemplo, `en-GB` para inglês ou `zn-HK` para cantonês. Você pode encontrar uma lista dos idiomas suportados e seus nomes de local na [documentação de suporte a idiomas e vozes nos docs da Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Abaixo disso, adicione a seguinte função para obter um token de acesso:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Isso chama um endpoint de emissão de token, passando a chave da API como um cabeçalho. Essa chamada retorna um token de acesso que pode ser usado para chamar os serviços de fala.

1. Abaixo disso, declare uma função para converter a fala capturada no áudio em texto usando a API REST:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Dentro dessa função, configure a URL da API REST e os cabeçalhos:

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

    Isso constrói uma URL usando a localização do recurso dos serviços de fala. Em seguida, preenche os cabeçalhos com o token de acesso da função `get_access_token`, bem como a taxa de amostragem usada para capturar o áudio. Por fim, define alguns parâmetros a serem passados com a URL contendo o idioma do áudio.

1. Abaixo disso, adicione o seguinte código para chamar a API REST e obter o texto de volta:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Isso chama a URL e decodifica o valor JSON que vem na resposta. O valor `RecognitionStatus` na resposta indica se a chamada conseguiu extrair a fala em texto com sucesso, e se for `Success`, o texto é retornado da função; caso contrário, uma string vazia é retornada.

1. Acima do loop `while True:`, defina uma função para processar o texto retornado pelo serviço de fala para texto. Por enquanto, essa função apenas imprimirá o texto no console.

    ```python
    def process_text(text):
        print(text)
    ```

1. Finalmente, substitua a chamada para `play_audio` no loop `while True` por uma chamada para a função `convert_speech_to_text`, passando o texto para a função `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Execute o código. Pressione o botão e fale no microfone. Solte o botão quando terminar, e o áudio será convertido em texto e impresso no console.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Experimente diferentes tipos de frases, junto com frases onde palavras soam iguais, mas têm significados diferentes. Por exemplo, se você estiver falando em inglês, diga "I want to buy two bananas and an apple too" e perceba como ele usará o "to", "two" e "too" corretos com base no contexto da palavra, e não apenas no som.

> 💁 Você pode encontrar este código na pasta [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Seu programa de fala para texto foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.