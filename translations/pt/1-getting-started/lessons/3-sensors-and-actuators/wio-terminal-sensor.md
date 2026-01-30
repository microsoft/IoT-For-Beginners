<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-25T22:09:14+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "pt"
}
-->
# Adicionar um sensor - Wio Terminal

Nesta parte da lição, vais utilizar o sensor de luz do teu Wio Terminal.

## Hardware

O sensor para esta lição é um **sensor de luz** que utiliza um [fotodíodo](https://wikipedia.org/wiki/Photodiode) para converter luz em um sinal elétrico. Este é um sensor analógico que envia um valor inteiro de 0 a 1.023, indicando uma quantidade relativa de luz que não corresponde a nenhuma unidade de medida padrão, como [lux](https://wikipedia.org/wiki/Lux).

O sensor de luz está integrado no Wio Terminal e é visível através da janela de plástico transparente na parte de trás.

![O sensor de luz na parte de trás do Wio Terminal](../../../../../translated_images/pt-PT/wio-light-sensor.b1f529f3c95f5165.webp)

## Programar o sensor de luz

O dispositivo pode agora ser programado para utilizar o sensor de luz integrado.

### Tarefa

Programa o dispositivo.

1. Abre o projeto da luz noturna no VS Code que criaste na parte anterior deste exercício.

1. Adiciona a seguinte linha ao final da função `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Esta linha configura os pinos utilizados para comunicar com o hardware do sensor.

    O pino `WIO_LIGHT` é o número do pino GPIO conectado ao sensor de luz integrado. Este pino é configurado como `INPUT`, o que significa que está ligado a um sensor e os dados serão lidos a partir do pino.

1. Apaga o conteúdo da função `loop`.

1. Adiciona o seguinte código à função `loop`, que agora está vazia.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Este código lê um valor analógico do pino `WIO_LIGHT`. Ele lê um valor de 0 a 1.023 do sensor de luz integrado. Este valor é então enviado para a porta serial para que possas lê-lo no Monitor Serial enquanto este código estiver a ser executado. `Serial.print` escreve o texto sem uma nova linha no final, então cada linha começará com `Light value:` e terminará com o valor real da luz.

1. Adiciona um pequeno atraso de um segundo (1.000ms) no final do `loop`, já que os níveis de luz não precisam de ser verificados continuamente. Um atraso reduz o consumo de energia do dispositivo.

    ```cpp
    delay(1000);
    ```

1. Reconecta o Wio Terminal ao teu computador e faz o upload do novo código como fizeste anteriormente.

1. Conecta o Monitor Serial. Os valores de luz serão exibidos no terminal. Cobre e descobre o sensor de luz na parte de trás do Wio Terminal, e os valores irão mudar.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Podes encontrar este código na pasta [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Adicionar um sensor ao teu programa de luz noturna foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.