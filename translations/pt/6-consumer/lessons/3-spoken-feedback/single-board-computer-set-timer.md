<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T22:34:05+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "pt"
}
-->
# Definir um temporizador - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, irá chamar o seu código serverless para interpretar o discurso e definir um temporizador no seu dispositivo IoT virtual ou Raspberry Pi com base nos resultados.

## Definir um temporizador

O texto que é retornado da chamada de reconhecimento de fala precisa ser enviado para o seu código serverless para ser processado pelo LUIS, obtendo o número de segundos para o temporizador. Este número de segundos pode ser usado para definir um temporizador.

Os temporizadores podem ser definidos utilizando a classe `threading.Timer` do Python. Esta classe recebe um tempo de atraso e uma função, e após o tempo de atraso, a função é executada.

### Tarefa - enviar o texto para a função serverless

1. Abra o projeto `smart-timer` no VS Code e certifique-se de que o ambiente virtual está carregado no terminal, caso esteja a usar um dispositivo IoT virtual.

1. Acima da função `process_text`, declare uma função chamada `get_timer_time` para chamar o endpoint REST que criou:

    ```python
    def get_timer_time(text):
    ```

1. Adicione o seguinte código a esta função para definir o URL a ser chamado:

    ```python
    url = '<URL>'
    ```

    Substitua `<URL>` pelo URL do seu endpoint REST que criou na última lição, seja no seu computador ou na nuvem.

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

    Chamadas HTTP bem-sucedidas retornam um código de status na faixa dos 200, e o seu código serverless retorna 200 se o texto foi processado e reconhecido como a intenção de definir um temporizador.

### Tarefa - definir um temporizador numa thread em segundo plano

1. Adicione a seguinte instrução de importação no início do ficheiro para importar a biblioteca threading do Python:

    ```python
    import threading
    ```

1. Acima da função `process_text`, adicione uma função para falar uma resposta. Por agora, esta apenas escreverá no console, mas mais tarde nesta lição, esta função irá falar o texto.

    ```python
    def say(text):
        print(text)
    ```

1. Abaixo disso, adicione uma função que será chamada por um temporizador para anunciar que o temporizador terminou:

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

    Esta função recebe o número de minutos e segundos do temporizador e constrói uma frase para dizer que o temporizador terminou. Verifica o número de minutos e segundos e só inclui cada unidade de tempo se tiver um valor. Por exemplo, se o número de minutos for 0, apenas os segundos são incluídos na mensagem. Esta frase é então enviada para a função `say`.

1. Abaixo disso, adicione a seguinte função `create_timer` para criar um temporizador:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Esta função recebe o número total de segundos para o temporizador que será enviado no comando e converte este valor em minutos e segundos. Em seguida, cria e inicia um objeto de temporizador utilizando o número total de segundos, passando a função `announce_timer` e uma lista contendo os minutos e segundos. Quando o temporizador expira, ele chama a função `announce_timer` e passa o conteúdo desta lista como parâmetros - assim, o primeiro item da lista é passado como o parâmetro `minutes` e o segundo item como o parâmetro `seconds`.

1. No final da função `create_timer`, adicione algum código para construir uma mensagem a ser falada ao utilizador para anunciar que o temporizador está a iniciar:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Novamente, isto apenas inclui a unidade de tempo que tem um valor. Esta frase é então enviada para a função `say`.

1. Adicione o seguinte ao final da função `process_text` para obter o tempo do temporizador a partir do texto e, em seguida, criar o temporizador:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    O temporizador só é criado se o número de segundos for maior que 0.

1. Execute a aplicação e certifique-se de que a aplicação de função também está em execução. Defina alguns temporizadores e o output mostrará o temporizador a ser definido e, em seguida, mostrará quando ele expira:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Pode encontrar este código na pasta [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) ou [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 O seu programa de temporizador foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.