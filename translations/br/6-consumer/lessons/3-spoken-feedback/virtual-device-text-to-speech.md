<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T02:55:20+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "br"
}
-->
# Texto para fala - Dispositivo IoT Virtual

Nesta parte da lição, você escreverá código para converter texto em fala usando o serviço de fala.

## Converter texto em fala

O SDK dos serviços de fala que você utilizou na última lição para converter fala em texto também pode ser usado para converter texto de volta em fala. Ao solicitar a fala, é necessário fornecer a voz a ser usada, já que a fala pode ser gerada utilizando uma variedade de vozes diferentes.

Cada idioma suporta uma gama de vozes diferentes, e você pode obter a lista de vozes suportadas para cada idioma a partir do SDK dos serviços de fala.

### Tarefa - converter texto em fala

1. Abra o projeto `smart-timer` no VS Code e certifique-se de que o ambiente virtual está carregado no terminal.

1. Importe o `SpeechSynthesizer` do pacote `azure.cognitiveservices.speech` adicionando-o aos imports existentes:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Acima da função `say`, crie uma configuração de fala para usar com o sintetizador de fala:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Isso utiliza a mesma chave de API, localização e idioma que foram usados pelo reconhecedor.

1. Abaixo disso, adicione o seguinte código para obter uma voz e configurá-la na configuração de fala:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Isso recupera uma lista de todas as vozes disponíveis e, em seguida, encontra a primeira voz que corresponde ao idioma que está sendo usado.

    > 💁 Você pode obter a lista completa de vozes suportadas na [documentação de suporte a idiomas e vozes no Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Se você quiser usar uma voz específica, pode remover essa função e definir a voz diretamente pelo nome da voz na documentação. Por exemplo:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Atualize o conteúdo da função `say` para gerar SSML para a resposta:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Abaixo disso, pare o reconhecimento de fala, fale o SSML e, em seguida, reinicie o reconhecimento:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    O reconhecimento é interrompido enquanto o texto é falado para evitar que o anúncio do início do temporizador seja detectado, enviado ao LUIS e possivelmente interpretado como uma solicitação para configurar um novo temporizador.

    > 💁 Você pode testar isso comentando as linhas para parar e reiniciar o reconhecimento. Configure um temporizador e talvez perceba que o anúncio configura um novo temporizador, o que causa um novo anúncio, levando a um novo temporizador, e assim por diante, indefinidamente!

1. Execute o aplicativo e certifique-se de que o aplicativo de função também está em execução. Configure alguns temporizadores e você ouvirá uma resposta falada dizendo que seu temporizador foi configurado, seguida de outra resposta falada quando o temporizador for concluído.

> 💁 Você pode encontrar este código na pasta [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Seu programa de temporizador foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.