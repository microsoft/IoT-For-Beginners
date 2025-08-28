<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T03:02:59+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "br"
}
-->
# Fala para texto - Dispositivo IoT Virtual

Nesta parte da lição, você escreverá um código para converter fala capturada do seu microfone em texto usando o serviço de fala.

## Converter fala em texto

No Windows, Linux e macOS, o SDK Python dos serviços de fala pode ser usado para ouvir o microfone e converter qualquer fala detectada em texto. Ele escuta continuamente, detectando os níveis de áudio e enviando a fala para conversão em texto quando o nível de áudio cai, como no final de um bloco de fala.

### Tarefa - converter fala em texto

1. Crie um novo aplicativo Python no seu computador em uma pasta chamada `smart-timer` com um único arquivo chamado `app.py` e um ambiente virtual Python.

1. Instale o pacote Pip para os serviços de fala. Certifique-se de instalar isso a partir de um terminal com o ambiente virtual ativado.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Se você receber o seguinte erro:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Será necessário atualizar o Pip. Faça isso com o seguinte comando e tente instalar o pacote novamente:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Adicione os seguintes imports ao arquivo `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Isso importa algumas classes usadas para reconhecer fala.

1. Adicione o seguinte código para declarar algumas configurações:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Substitua `<key>` pela chave de API do seu serviço de fala. Substitua `<location>` pela localização que você usou ao criar o recurso do serviço de fala.

    Substitua `<language>` pelo nome do local para o idioma que você estará falando, por exemplo, `en-GB` para inglês ou `zn-HK` para cantonês. Você pode encontrar uma lista dos idiomas suportados e seus nomes de local na [documentação de suporte a idiomas e vozes nos docs da Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Essa configuração é então usada para criar um objeto `SpeechConfig` que será usado para configurar os serviços de fala.

1. Adicione o seguinte código para criar um reconhecedor de fala:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. O reconhecedor de fala é executado em uma thread em segundo plano, ouvindo o áudio e convertendo qualquer fala nele em texto. Você pode obter o texto usando uma função de callback - uma função que você define e passa para o reconhecedor. Toda vez que uma fala é detectada, o callback é chamado. Adicione o seguinte código para definir um callback e passar esse callback para o reconhecedor, além de definir uma função para processar o texto, escrevendo-o no console:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. O reconhecedor só começa a escutar quando você explicitamente o inicia. Adicione o seguinte código para iniciar o reconhecimento. Isso é executado em segundo plano, então seu aplicativo também precisará de um loop infinito que dorme para manter o aplicativo em execução.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Execute este aplicativo. Fale no seu microfone e o áudio convertido em texto será exibido no console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Experimente diferentes tipos de frases, junto com frases onde palavras soam iguais, mas têm significados diferentes. Por exemplo, se você estiver falando em inglês, diga "I want to buy two bananas and an apple too" e perceba como ele usará o "to", "two" e "too" corretos com base no contexto da palavra, não apenas no som.

> 💁 Você pode encontrar este código na pasta [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Seu programa de fala para texto foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.