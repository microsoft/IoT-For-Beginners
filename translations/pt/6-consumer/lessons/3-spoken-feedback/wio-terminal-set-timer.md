<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T22:36:20+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "pt"
}
-->
# Definir um temporizador - Wio Terminal

Nesta parte da lição, irá chamar o seu código serverless para interpretar a fala e definir um temporizador no seu Wio Terminal com base nos resultados.

## Definir um temporizador

O texto que retorna da chamada de conversão de fala para texto precisa ser enviado para o seu código serverless para ser processado pelo LUIS, que devolverá o número de segundos para o temporizador. Este número de segundos pode ser usado para definir um temporizador.

Microcontroladores não têm suporte nativo para múltiplas threads no Arduino, por isso não existem classes padrão de temporizador como as que pode encontrar ao programar em Python ou outras linguagens de alto nível. Em vez disso, pode usar bibliotecas de temporizador que funcionam medindo o tempo decorrido na função `loop` e chamando funções quando o tempo termina.

### Tarefa - enviar o texto para a função serverless

1. Abra o projeto `smart-timer` no VS Code, caso ainda não esteja aberto.

1. Abra o ficheiro de cabeçalho `config.h` e adicione o URL para a sua aplicação de função:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Substitua `<URL>` pelo URL da sua aplicação de função que obteve no último passo da última lição, apontando para o endereço IP da sua máquina local que está a executar a aplicação de função.

1. Crie um novo ficheiro na pasta `src` chamado `language_understanding.h`. Este será usado para definir uma classe que enviará a fala reconhecida para a sua aplicação de função para ser convertida em segundos usando o LUIS.

1. Adicione o seguinte ao topo deste ficheiro:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Isto inclui alguns ficheiros de cabeçalho necessários.

1. Defina uma classe chamada `LanguageUnderstanding` e declare uma instância desta classe:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Para chamar a sua aplicação de funções, precisa de declarar um cliente WiFi. Adicione o seguinte à secção `private` da classe:

    ```cpp
    WiFiClient _client;
    ```

1. Na secção `public`, declare um método chamado `GetTimerDuration` para chamar a aplicação de funções:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. No método `GetTimerDuration`, adicione o seguinte código para construir o JSON a ser enviado para a aplicação de funções:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Isto converte o texto passado para o método `GetTimerDuration` no seguinte JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    onde `<text>` é o texto passado para a função.

1. Abaixo disto, adicione o seguinte código para fazer a chamada à aplicação de funções:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Isto faz uma requisição POST para a aplicação de funções, passando o corpo JSON e obtendo o código de resposta.

1. Adicione o seguinte código abaixo disto:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Este código verifica o código de resposta. Se for 200 (sucesso), o número de segundos para o temporizador é recuperado do corpo da resposta. Caso contrário, um erro é enviado para o monitor serial e o número de segundos é definido como 0.

1. Adicione o seguinte código ao final deste método para fechar a conexão HTTP e retornar o número de segundos:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. No ficheiro `main.cpp`, inclua este novo cabeçalho:

    ```cpp
    #include "speech_to_text.h"
    ```

1. No final da função `processAudio`, chame o método `GetTimerDuration` para obter a duração do temporizador:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Isto converte o texto da chamada para a classe `SpeechToText` no número de segundos para o temporizador.

### Tarefa - definir um temporizador

O número de segundos pode ser usado para definir um temporizador.

1. Adicione a seguinte dependência de biblioteca ao ficheiro `platformio.ini` para adicionar uma biblioteca para definir um temporizador:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Adicione uma diretiva de inclusão para esta biblioteca no ficheiro `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Acima da função `processAudio`, adicione o seguinte código:

    ```cpp
    auto timer = timer_create_default();
    ```

    Este código declara um temporizador chamado `timer`.

1. Abaixo disto, adicione o seguinte código:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Esta função `say` eventualmente converterá texto em fala, mas por agora apenas escreverá o texto passado no monitor serial.

1. Abaixo da função `say`, adicione o seguinte código:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Esta é uma função de callback que será chamada quando um temporizador expirar. É passada uma mensagem para ser dita quando o temporizador expirar. Os temporizadores podem repetir, e isto pode ser controlado pelo valor de retorno deste callback - este retorna `false`, para indicar que o temporizador não deve ser executado novamente.

1. Adicione o seguinte código ao final da função `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Este código verifica o número total de segundos e, se for 0, retorna da chamada da função para que nenhum temporizador seja definido. Em seguida, converte o número total de segundos em minutos e segundos.

1. Abaixo deste código, adicione o seguinte para criar uma mensagem a ser dita quando o temporizador for iniciado:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Abaixo disto, adicione um código semelhante para criar uma mensagem a ser dita quando o temporizador expirar:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Depois disto, diga a mensagem de início do temporizador:

    ```cpp
    say(begin_message);
    ```

1. No final desta função, inicie o temporizador:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Isto ativa o temporizador. O temporizador é definido usando milissegundos, então o número total de segundos é multiplicado por 1.000 para converter em milissegundos. A função `timerExpired` é passada como o callback, e a `end_message` é passada como um argumento para o callback. Este callback apenas aceita argumentos `void *`, então a string é convertida apropriadamente.

1. Finalmente, o temporizador precisa de "ticar", e isto é feito na função `loop`. Adicione o seguinte código ao final da função `loop`:

    ```cpp
    timer.tick();
    ```

1. Compile este código, carregue-o no seu Wio Terminal e teste-o através do monitor serial. Assim que vir `Ready` no monitor serial, pressione o botão C (o que está do lado esquerdo, mais próximo do interruptor de energia) e fale. Serão capturados 4 segundos de áudio, convertidos em texto, enviados para a sua aplicação de função e um temporizador será definido. Certifique-se de que a sua aplicação de função está a ser executada localmente.

    Verá quando o temporizador começa e quando termina.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Pode encontrar este código na pasta [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 O seu programa de temporizador foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.