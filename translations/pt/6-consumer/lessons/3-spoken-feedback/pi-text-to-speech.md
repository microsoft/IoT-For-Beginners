<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T22:37:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "pt"
}
-->
# Texto para fala - Raspberry Pi

Nesta parte da lição, vais escrever código para converter texto em fala utilizando o serviço de fala.

## Converter texto em fala utilizando o serviço de fala

O texto pode ser enviado ao serviço de fala através da API REST para obter a fala como um ficheiro de áudio que pode ser reproduzido no teu dispositivo IoT. Ao solicitar a fala, precisas de indicar a voz a ser utilizada, uma vez que a fala pode ser gerada com uma variedade de vozes diferentes.

Cada idioma suporta uma gama de vozes distintas, e podes fazer uma solicitação REST ao serviço de fala para obter a lista de vozes suportadas para cada idioma.

### Tarefa - obter uma voz

1. Abre o projeto `smart-timer` no VS Code.

1. Adiciona o seguinte código acima da função `say` para solicitar a lista de vozes para um idioma:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Este código define uma função chamada `get_voice` que utiliza o serviço de fala para obter uma lista de vozes. Em seguida, encontra a primeira voz que corresponde ao idioma que está a ser utilizado.

    Esta função é chamada para armazenar a primeira voz, e o nome da voz é impresso na consola. Esta voz pode ser solicitada uma vez e o valor utilizado em cada chamada para converter texto em fala.

    > 💁 Podes obter a lista completa de vozes suportadas na [documentação de suporte de idiomas e vozes no Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Se quiseres utilizar uma voz específica, podes remover esta função e definir diretamente o nome da voz a partir desta documentação. Por exemplo:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Tarefa - converter texto em fala

1. Abaixo disto, define uma constante para o formato de áudio a ser obtido dos serviços de fala. Quando solicitas áudio, podes fazê-lo em vários formatos diferentes.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    O formato que podes utilizar depende do teu hardware. Se obtiveres erros de `Invalid sample rate` ao reproduzir o áudio, altera isto para outro valor. Podes encontrar a lista de valores suportados na [documentação da API REST de texto para fala no Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Vais precisar de utilizar áudio no formato `riff`, e os valores a experimentar são `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` e `riff-48khz-16bit-mono-pcm`.

1. Abaixo disto, declara uma função chamada `get_speech` que irá converter o texto em fala utilizando a API REST do serviço de fala:

    ```python
    def get_speech(text):
    ```

1. Na função `get_speech`, define o URL a ser chamado e os cabeçalhos a serem enviados:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Isto define os cabeçalhos para utilizar um token de acesso gerado, define o conteúdo como SSML e especifica o formato de áudio necessário.

1. Abaixo disto, define o SSML a ser enviado à API REST:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Este SSML define o idioma e a voz a ser utilizada, juntamente com o texto a ser convertido.

1. Finalmente, adiciona código nesta função para fazer a solicitação REST e retornar os dados binários de áudio:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Tarefa - reproduzir o áudio

1. Abaixo da função `get_speech`, define uma nova função para reproduzir o áudio retornado pela chamada à API REST:

    ```python
    def play_speech(speech):
    ```

1. O `speech` passado para esta função será os dados binários de áudio retornados pela API REST. Utiliza o seguinte código para abrir isto como um ficheiro wave e passá-lo para o PyAudio para reproduzir o áudio:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Este código utiliza um stream do PyAudio, tal como na captura de áudio. A diferença aqui é que o stream é configurado como um stream de saída, e os dados são lidos a partir dos dados de áudio e enviados para o stream.

    Em vez de definir diretamente os detalhes do stream, como a taxa de amostragem, estes são lidos a partir dos dados de áudio.

1. Substitui o conteúdo da função `say` pelo seguinte:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Este código converte o texto em fala como dados binários de áudio e reproduz o áudio.

1. Executa a aplicação e certifica-te de que a aplicação de função também está a ser executada. Define alguns temporizadores e vais ouvir uma resposta falada a dizer que o teu temporizador foi definido, e outra resposta falada quando o temporizador terminar.

    Se obtiveres erros de `Invalid sample rate`, altera o `playback_format` conforme descrito acima.

> 💁 Podes encontrar este código na pasta [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 O teu programa de temporizador foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.