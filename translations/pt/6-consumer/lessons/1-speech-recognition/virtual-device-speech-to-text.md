<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T22:45:04+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "pt"
}
-->
# Conversão de fala para texto - Dispositivo IoT virtual

Nesta parte da lição, vais escrever código para converter fala captada pelo teu microfone em texto, utilizando o serviço de fala.

## Converter fala em texto

No Windows, Linux e macOS, o SDK Python dos serviços de fala pode ser usado para ouvir o teu microfone e converter qualquer fala detetada em texto. Ele escuta continuamente, detetando os níveis de áudio e enviando a fala para conversão em texto quando o nível de áudio diminui, como no final de um bloco de fala.

### Tarefa - converter fala em texto

1. Cria uma nova aplicação Python no teu computador numa pasta chamada `smart-timer` com um único ficheiro chamado `app.py` e um ambiente virtual Python.

1. Instala o pacote Pip para os serviços de fala. Certifica-te de que estás a instalar isto a partir de um terminal com o ambiente virtual ativado.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Se receberes o seguinte erro:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Terás de atualizar o Pip. Faz isso com o seguinte comando e tenta instalar o pacote novamente:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Adiciona as seguintes importações ao ficheiro `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Isto importa algumas classes usadas para reconhecer fala.

1. Adiciona o seguinte código para declarar algumas configurações:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Substitui `<key>` pela chave API do teu serviço de fala. Substitui `<location>` pela localização que usaste ao criar o recurso do serviço de fala.

    Substitui `<language>` pelo nome do local para o idioma em que vais falar, por exemplo, `en-GB` para inglês ou `zn-HK` para cantonês. Podes encontrar uma lista dos idiomas suportados e os respetivos nomes de local na [documentação de suporte a idiomas e vozes nos documentos da Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Esta configuração é então usada para criar um objeto `SpeechConfig` que será utilizado para configurar os serviços de fala.

1. Adiciona o seguinte código para criar um reconhecedor de fala:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. O reconhecedor de fala funciona numa thread em segundo plano, ouvindo o áudio e convertendo qualquer fala em texto. Podes obter o texto utilizando uma função de callback - uma função que defines e passas ao reconhecedor. Sempre que uma fala é detetada, o callback é chamado. Adiciona o seguinte código para definir um callback e passá-lo ao reconhecedor, bem como definir uma função para processar o texto, escrevendo-o na consola:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. O reconhecedor só começa a ouvir quando o inicias explicitamente. Adiciona o seguinte código para iniciar o reconhecimento. Isto funciona em segundo plano, por isso a tua aplicação também precisará de um loop infinito que dorme para manter a aplicação em execução.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Executa esta aplicação. Fala no teu microfone e o áudio convertido em texto será exibido na consola.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Experimenta diferentes tipos de frases, juntamente com frases onde as palavras soam iguais, mas têm significados diferentes. Por exemplo, se estiveres a falar em inglês, diz "I want to buy two bananas and an apple too" e repara como ele usa corretamente "to", "two" e "too" com base no contexto da palavra, e não apenas no som.

> 💁 Podes encontrar este código na pasta [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 O teu programa de conversão de fala para texto foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, tenha em atenção que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.