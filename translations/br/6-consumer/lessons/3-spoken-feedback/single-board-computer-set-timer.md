<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T02:59:29+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "br"
}
-->
# Configurar um cronômetro - Hardware Virtual de IoT e Raspberry Pi

Nesta parte da lição, você chamará seu código serverless para entender a fala e configurar um cronômetro no seu dispositivo IoT virtual ou Raspberry Pi com base nos resultados.

## Configurar um cronômetro

O texto que retorna da chamada de conversão de fala para texto precisa ser enviado ao seu código serverless para ser processado pelo LUIS, retornando o número de segundos para o cronômetro. Esse número de segundos pode ser usado para configurar um cronômetro.

Cronômetros podem ser configurados usando a classe `threading.Timer` do Python. Essa classe recebe um tempo de atraso e uma função, e após o tempo de atraso, a função é executada.

### Tarefa - enviar o texto para a função serverless

1. Abra o projeto `smart-timer` no VS Code e certifique-se de que o ambiente virtual está carregado no terminal, caso esteja usando um dispositivo IoT virtual.

1. Acima da função `process_text`, declare uma função chamada `get_timer_time` para chamar o endpoint REST que você criou:

    ```python
    def get_timer_time(text):
    ```

1. Adicione o seguinte código a essa função para definir a URL a ser chamada:

    ```python
    url = '<URL>'
    ```

    Substitua `<URL>` pela URL do seu endpoint REST que você construiu na última lição, seja no seu computador ou na nuvem.

1. Adicione o seguinte código para definir o texto como uma propriedade passada como JSON na chamada:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Abaixo disso, recupere os `seconds` do payload da resposta, retornando 0 se a chamada falhar:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Chamadas HTTP bem-sucedidas retornam um código de status na faixa de 200, e seu código serverless retorna 200 se o texto foi processado e reconhecido como a intenção de configurar o cronômetro.

### Tarefa - configurar um cronômetro em uma thread de segundo plano

1. Adicione a seguinte declaração de importação no topo do arquivo para importar a biblioteca threading do Python:

    ```python
    import threading
    ```

1. Acima da função `process_text`, adicione uma função para falar uma resposta. Por enquanto, isso apenas escreverá no console, mas mais tarde nesta lição, isso falará o texto.

    ```python
    def say(text):
        print(text)
    ```

1. Abaixo disso, adicione uma função que será chamada por um cronômetro para anunciar que o cronômetro foi concluído:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Essa função recebe o número de minutos e segundos do cronômetro e constrói uma frase para dizer que o cronômetro foi concluído. Ela verificará o número de minutos e segundos e incluirá cada unidade de tempo apenas se tiver um número. Por exemplo, se o número de minutos for 0, apenas os segundos serão incluídos na mensagem. Essa frase é então enviada para a função `say`.

1. Abaixo disso, adicione a seguinte função `create_timer` para criar um cronômetro:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Essa função recebe o número total de segundos para o cronômetro que será enviado no comando e converte isso em minutos e segundos. Em seguida, cria e inicia um objeto de cronômetro usando o número total de segundos, passando a função `announce_timer` e uma lista contendo os minutos e segundos. Quando o cronômetro expirar, ele chamará a função `announce_timer` e passará o conteúdo dessa lista como os parâmetros - então o primeiro item da lista será passado como o parâmetro `minutes` e o segundo item como o parâmetro `seconds`.

1. No final da função `create_timer`, adicione algum código para construir uma mensagem que será falada ao usuário para anunciar que o cronômetro está começando:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Novamente, isso inclui apenas a unidade de tempo que tem um valor. Essa frase é então enviada para a função `say`.

1. Adicione o seguinte ao final da função `process_text` para obter o tempo do cronômetro a partir do texto e, em seguida, criar o cronômetro:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    O cronômetro só é criado se o número de segundos for maior que 0.

1. Execute o aplicativo e certifique-se de que o aplicativo de função também está em execução. Configure alguns cronômetros e a saída mostrará o cronômetro sendo configurado e, em seguida, mostrará quando ele expirar:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Você pode encontrar este código na pasta [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) ou [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Seu programa de cronômetro foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.