<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T02:58:47+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "br"
}
-->
# Configurar um cronômetro - Wio Terminal

Nesta parte da lição, você chamará seu código serverless para interpretar o discurso e configurar um cronômetro no seu Wio Terminal com base nos resultados.

## Configurar um cronômetro

O texto retornado da chamada de reconhecimento de fala precisa ser enviado para o seu código serverless para ser processado pelo LUIS, que retornará o número de segundos para o cronômetro. Esse número de segundos pode ser usado para configurar o cronômetro.

Microcontroladores não possuem suporte nativo para múltiplas threads no Arduino, então não há classes padrão de cronômetro como você encontraria ao programar em Python ou outras linguagens de alto nível. Em vez disso, você pode usar bibliotecas de cronômetro que funcionam medindo o tempo decorrido na função `loop` e chamando funções quando o tempo termina.

### Tarefa - enviar o texto para a função serverless

1. Abra o projeto `smart-timer` no VS Code, caso ainda não esteja aberto.

1. Abra o arquivo de cabeçalho `config.h` e adicione a URL para o seu aplicativo de função:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Substitua `<URL>` pela URL do seu aplicativo de função que você obteve na última etapa da lição anterior, apontando para o endereço IP da sua máquina local que está executando o aplicativo de função.

1. Crie um novo arquivo na pasta `src` chamado `language_understanding.h`. Este arquivo será usado para definir uma classe que enviará o discurso reconhecido para o seu aplicativo de função, convertendo-o em segundos usando o LUIS.

1. Adicione o seguinte ao início deste arquivo:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Isso inclui alguns arquivos de cabeçalho necessários.

1. Defina uma classe chamada `LanguageUnderstanding` e declare uma instância dessa classe:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Para chamar seu aplicativo de função, você precisa declarar um cliente WiFi. Adicione o seguinte à seção `private` da classe:

    ```cpp
    WiFiClient _client;
    ```

1. Na seção `public`, declare um método chamado `GetTimerDuration` para chamar o aplicativo de função:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. No método `GetTimerDuration`, adicione o seguinte código para construir o JSON a ser enviado ao aplicativo de função:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Isso converte o texto passado para o método `GetTimerDuration` no seguinte JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    onde `<text>` é o texto passado para a função.

1. Abaixo disso, adicione o seguinte código para fazer a chamada ao aplicativo de função:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Isso faz uma solicitação POST ao aplicativo de função, passando o corpo JSON e obtendo o código de resposta.

1. Adicione o seguinte código abaixo disso:

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

    Este código verifica o código de resposta. Se for 200 (sucesso), o número de segundos para o cronômetro é recuperado do corpo da resposta. Caso contrário, um erro é enviado ao monitor serial e o número de segundos é definido como 0.

1. Adicione o seguinte código ao final deste método para fechar a conexão HTTP e retornar o número de segundos:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. No arquivo `main.cpp`, inclua este novo cabeçalho:

    ```cpp
    #include "speech_to_text.h"
    ```

1. No final da função `processAudio`, chame o método `GetTimerDuration` para obter a duração do cronômetro:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Isso converte o texto da chamada para a classe `SpeechToText` no número de segundos para o cronômetro.

### Tarefa - configurar um cronômetro

O número de segundos pode ser usado para configurar um cronômetro.

1. Adicione a seguinte dependência de biblioteca ao arquivo `platformio.ini` para adicionar uma biblioteca para configurar um cronômetro:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Adicione uma diretiva de inclusão para esta biblioteca no arquivo `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Acima da função `processAudio`, adicione o seguinte código:

    ```cpp
    auto timer = timer_create_default();
    ```

    Este código declara um cronômetro chamado `timer`.

1. Abaixo disso, adicione o seguinte código:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Esta função `say` eventualmente converterá texto em fala, mas por enquanto apenas escreverá o texto passado no monitor serial.

1. Abaixo da função `say`, adicione o seguinte código:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Esta é uma função de callback que será chamada quando um cronômetro expirar. Ela recebe uma mensagem para ser dita quando o cronômetro expirar. Cronômetros podem se repetir, e isso pode ser controlado pelo valor de retorno deste callback - aqui retorna `false`, indicando que o cronômetro não deve ser executado novamente.

1. Adicione o seguinte código ao final da função `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Este código verifica o número total de segundos e, se for 0, retorna da chamada da função para que nenhum cronômetro seja configurado. Ele então converte o número total de segundos em minutos e segundos.

1. Abaixo deste código, adicione o seguinte para criar uma mensagem a ser dita quando o cronômetro for iniciado:

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

1. Abaixo disso, adicione um código semelhante para criar uma mensagem a ser dita quando o cronômetro expirar:

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

1. Após isso, diga a mensagem de início do cronômetro:

    ```cpp
    say(begin_message);
    ```

1. No final desta função, inicie o cronômetro:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Isso aciona o cronômetro. O cronômetro é configurado usando milissegundos, então o número total de segundos é multiplicado por 1.000 para converter em milissegundos. A função `timerExpired` é passada como callback, e a `end_message` é passada como argumento para o callback. Este callback aceita apenas argumentos `void *`, então a string é convertida adequadamente.

1. Finalmente, o cronômetro precisa "contar", e isso é feito na função `loop`. Adicione o seguinte código ao final da função `loop`:

    ```cpp
    timer.tick();
    ```

1. Compile este código, carregue-o no seu Wio Terminal e teste-o através do monitor serial. Assim que você vir `Ready` no monitor serial, pressione o botão C (o da esquerda, mais próximo do interruptor de energia) e fale. 4 segundos de áudio serão capturados, convertidos em texto, enviados para o seu aplicativo de função e um cronômetro será configurado. Certifique-se de que seu aplicativo de função esteja sendo executado localmente.

    Você verá quando o cronômetro começar e quando ele terminar.

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

> 💁 Você pode encontrar este código na pasta [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Seu programa de cronômetro foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.