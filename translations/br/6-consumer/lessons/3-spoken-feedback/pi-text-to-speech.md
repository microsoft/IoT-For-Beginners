<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T02:58:16+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "br"
}
-->
# Texto para fala - Raspberry Pi

Nesta parte da lição, você escreverá código para converter texto em fala usando o serviço de fala.

## Converter texto em fala usando o serviço de fala

O texto pode ser enviado ao serviço de fala usando a API REST para obter a fala como um arquivo de áudio que pode ser reproduzido no seu dispositivo IoT. Ao solicitar a fala, você precisa fornecer a voz a ser usada, pois a fala pode ser gerada usando uma variedade de vozes diferentes.

Cada idioma suporta uma gama de vozes diferentes, e você pode fazer uma solicitação REST ao serviço de fala para obter a lista de vozes suportadas para cada idioma.

### Tarefa - obter uma voz

1. Abra o projeto `smart-timer` no VS Code.

1. Adicione o seguinte código acima da função `say` para solicitar a lista de vozes para um idioma:

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

    Este código define uma função chamada `get_voice` que usa o serviço de fala para obter uma lista de vozes. Em seguida, encontra a primeira voz que corresponde ao idioma que está sendo usado.

    Esta função é chamada para armazenar a primeira voz, e o nome da voz é impresso no console. Essa voz pode ser solicitada uma vez e o valor usado para cada chamada para converter texto em fala.

    > 💁 Você pode obter a lista completa de vozes suportadas na [documentação de suporte de idiomas e vozes no Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Se você quiser usar uma voz específica, pode remover esta função e definir a voz diretamente com o nome da voz da documentação. Por exemplo:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Tarefa - converter texto em fala

1. Abaixo disso, defina uma constante para o formato de áudio a ser recuperado dos serviços de fala. Ao solicitar áudio, você pode fazê-lo em uma variedade de formatos diferentes.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    O formato que você pode usar depende do seu hardware. Se você receber erros de `Invalid sample rate` ao reproduzir o áudio, altere isso para outro valor. Você pode encontrar a lista de valores suportados na [documentação da API REST de texto para fala no Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Você precisará usar áudio no formato `riff`, e os valores para tentar são `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` e `riff-48khz-16bit-mono-pcm`.

1. Abaixo disso, declare uma função chamada `get_speech` que converterá o texto em fala usando a API REST do serviço de fala:

    ```python
    def get_speech(text):
    ```

1. Na função `get_speech`, defina a URL a ser chamada e os cabeçalhos a serem passados:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Isso define os cabeçalhos para usar um token de acesso gerado, define o conteúdo como SSML e especifica o formato de áudio necessário.

1. Abaixo disso, defina o SSML a ser enviado para a API REST:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Este SSML define o idioma e a voz a serem usados, juntamente com o texto a ser convertido.

1. Por fim, adicione código nesta função para fazer a solicitação REST e retornar os dados binários de áudio:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Tarefa - reproduzir o áudio

1. Abaixo da função `get_speech`, defina uma nova função para reproduzir o áudio retornado pela chamada da API REST:

    ```python
    def play_speech(speech):
    ```

1. O `speech` passado para esta função será os dados binários de áudio retornados pela API REST. Use o seguinte código para abrir isso como um arquivo wave e passá-lo para o PyAudio para reproduzir o áudio:

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

    Este código usa um stream do PyAudio, o mesmo que capturar áudio. A diferença aqui é que o stream é configurado como um stream de saída, e os dados são lidos dos dados de áudio e enviados para o stream.

    Em vez de definir os detalhes do stream, como a taxa de amostragem, eles são lidos dos dados de áudio.

1. Substitua o conteúdo da função `say` pelo seguinte:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Este código converte o texto em fala como dados binários de áudio e reproduz o áudio.

1. Execute o aplicativo e certifique-se de que o aplicativo de função também esteja em execução. Configure alguns temporizadores e você ouvirá uma resposta falada dizendo que seu temporizador foi configurado, e outra resposta falada quando o temporizador for concluído.

    Se você receber erros de `Invalid sample rate`, altere o `playback_format` conforme descrito acima.

> 💁 Você pode encontrar este código na pasta [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Seu programa de temporizador foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte oficial. Para informações críticas, recomenda-se a tradução profissional feita por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.