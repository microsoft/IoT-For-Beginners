<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T22:40:16+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "pt"
}
-->
# Texto para fala - Dispositivo Virtual IoT

Nesta parte da lição, vais escrever código para converter texto em fala utilizando o serviço de fala.

## Converter texto em fala

O SDK dos serviços de fala que utilizaste na última lição para converter fala em texto pode ser usado para converter texto de volta em fala. Ao solicitar a fala, precisas de fornecer a voz a ser utilizada, uma vez que a fala pode ser gerada usando uma variedade de vozes diferentes.

Cada idioma suporta uma gama de vozes diferentes, e podes obter a lista de vozes suportadas para cada idioma através do SDK dos serviços de fala.

### Tarefa - converter texto em fala

1. Abre o projeto `smart-timer` no VS Code e certifica-te de que o ambiente virtual está carregado no terminal.

1. Importa o `SpeechSynthesizer` do pacote `azure.cognitiveservices.speech` adicionando-o às importações existentes:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Acima da função `say`, cria uma configuração de fala para usar com o sintetizador de fala:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Isto utiliza a mesma chave de API, localização e idioma que foram usados pelo reconhecedor.

1. Abaixo disso, adiciona o seguinte código para obter uma voz e defini-la na configuração de fala:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Isto obtém uma lista de todas as vozes disponíveis e, em seguida, encontra a primeira voz que corresponde ao idioma que está a ser utilizado.

    > 💁 Podes obter a lista completa de vozes suportadas na [documentação de suporte de idiomas e vozes no Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Se quiseres usar uma voz específica, podes remover esta função e definir diretamente o nome da voz a partir desta documentação. Por exemplo:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Atualiza o conteúdo da função `say` para gerar SSML para a resposta:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Abaixo disso, para o reconhecimento de fala, fala o SSML e, em seguida, reinicia o reconhecimento:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    O reconhecimento é interrompido enquanto o texto é falado para evitar que o anúncio do início do temporizador seja detetado, enviado para o LUIS e possivelmente interpretado como um pedido para definir um novo temporizador.

    > 💁 Podes testar isto comentando as linhas para parar e reiniciar o reconhecimento. Define um temporizador e podes verificar que o anúncio define um novo temporizador, o que causa um novo anúncio, levando a um novo temporizador, e assim sucessivamente para sempre!

1. Executa a aplicação e certifica-te de que a aplicação de funções também está a funcionar. Define alguns temporizadores e vais ouvir uma resposta falada a dizer que o teu temporizador foi definido, seguida de outra resposta falada quando o temporizador terminar.

> 💁 Podes encontrar este código na pasta [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 O teu programa de temporizador foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.