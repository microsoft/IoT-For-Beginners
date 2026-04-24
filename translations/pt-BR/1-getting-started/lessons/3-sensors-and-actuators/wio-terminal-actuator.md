# Construa uma luz noturna - Wio Terminal

Nesta parte da lição, você adicionará um LED ao seu Wio Terminal e o usará para criar uma luz noturna.

## Hardware

A luz noturna agora precisa de um atuador.

O atuador é um **LED**, um [diodo emissor de luz](https://wikipedia.org/wiki/Diodo_emissor_de_luz) que emite luz quando a corrente passa por ele. Este é um atuador digital que possui 2 estados: ligado e desligado. Enviar um valor de 1 liga o LED, e 0 o desliga. Este é um atuador externo Grove e precisa ser conectado ao Wio Terminal.

A lógica da luz noturna em pseudocódigo é:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Conecte o LED

O Grove LED vem como um módulo com uma seleção de LEDs, permitindo que você escolha a cor.

#### Tarefa - conectar o LED

Conecte o LED.

![Um Grove LED](../../../../../translated_images/pt-BR/grove-led.6c853be93f473cf2.webp)

1. Escolha seu LED favorito e insira as pernas nos dois orifícios do módulo LED.

    LEDs são diodos emissores de luz, e diodos são dispositivos eletrônicos que só permitem a passagem de corrente em uma direção. Isso significa que o LED precisa ser conectado na orientação correta, caso contrário, ele não funcionará.

    Uma das pernas do LED é o pino positivo, e a outra é o pino negativo. O LED não é perfeitamente redondo e é ligeiramente mais plano de um lado. O lado ligeiramente mais plano é o pino negativo. Ao conectar o LED ao módulo, certifique-se de que o pino do lado arredondado está conectado ao soquete marcado com **+** na parte externa do módulo, e o lado mais plano está conectado ao soquete mais próximo do centro do módulo.

1. O módulo LED possui um botão giratório que permite controlar o brilho. Gire-o completamente para cima no início, girando-o no sentido anti-horário até o limite usando uma pequena chave de fenda Phillips.

1. Insira uma extremidade de um cabo Grove no soquete do módulo LED. Ele só entrará de uma maneira.

1. Com o Wio Terminal desconectado do seu computador ou de outra fonte de alimentação, conecte a outra extremidade do cabo Grove ao soquete Grove do lado direito do Wio Terminal, olhando para a tela. Este é o soquete mais distante do botão de energia.

    > 💁 O soquete Grove do lado direito pode ser usado com sensores e atuadores analógicos ou digitais. O soquete do lado esquerdo é apenas para sensores e atuadores digitais. O C será abordado em uma lição posterior.

![O Grove LED conectado ao soquete do lado direito](../../../../../translated_images/pt-BR/wio-led.265a1897e72d7f21.webp)

## Programe a luz noturna

A luz noturna agora pode ser programada usando o sensor de luz embutido e o Grove LED.

### Tarefa - programar a luz noturna

Programe a luz noturna.

1. Abra o projeto da luz noturna no VS Code que você criou na parte anterior desta tarefa.

1. Adicione a seguinte linha ao final da função `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Esta linha configura o pino usado para se comunicar com o LED através da porta Grove.

    O pino `D0` é o pino digital para o soquete Grove do lado direito. Este pino é configurado como `OUTPUT`, o que significa que ele se conecta a um atuador e os dados serão escritos no pino.

1. Adicione o seguinte código imediatamente antes do `delay` na função loop:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Este código verifica o valor de `light`. Se for menor que 300, ele envia um valor `HIGH` para o pino digital `D0`. Este `HIGH` é um valor de 1, ligando o LED. Se o valor da luz for maior ou igual a 300, um valor `LOW` de 0 é enviado para o pino, desligando o LED.

    > 💁 Ao enviar valores digitais para atuadores, um valor LOW é 0v, e um valor HIGH é a tensão máxima para o dispositivo. Para o Wio Terminal, a tensão HIGH é 3,3V.

1. Reconecte o Wio Terminal ao seu computador e carregue o novo código como fez anteriormente.

1. Conecte o Monitor Serial. Os valores de luz serão exibidos no terminal.

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

1. Cubra e descubra o sensor de luz. Observe como o LED acende se o nível de luz for 300 ou menos, e apaga quando o nível de luz for maior que 300.

![O LED conectado ao WIO acendendo e apagando conforme o nível de luz muda](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Você pode encontrar este código na pasta [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Seu programa de luz noturna foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.