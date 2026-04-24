# Construa uma luz noturna - Raspberry Pi

Nesta parte da lição, você adicionará um LED ao seu Raspberry Pi e o usará para criar uma luz noturna.

## Hardware

A luz noturna agora precisa de um atuador.

O atuador é um **LED**, um [diodo emissor de luz](https://wikipedia.org/wiki/Light-emitting_diode) que emite luz quando a corrente elétrica passa por ele. Este é um atuador digital que possui dois estados: ligado e desligado. Enviar um valor de 1 liga o LED, e 0 o desliga. O LED é um atuador externo Grove e precisa ser conectado ao Grove Base Hat no Raspberry Pi.

A lógica da luz noturna em pseudocódigo é:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Conecte o LED

O LED Grove vem como um módulo com uma seleção de LEDs, permitindo que você escolha a cor.

#### Tarefa - conectar o LED

Conecte o LED.

![Um LED Grove](../../../../../translated_images/pt-BR/grove-led.6c853be93f473cf2.webp)

1. Escolha seu LED favorito e insira as pernas nos dois orifícios do módulo LED.

    LEDs são diodos emissores de luz, e diodos são dispositivos eletrônicos que só permitem a passagem de corrente em uma direção. Isso significa que o LED precisa ser conectado na orientação correta, caso contrário, ele não funcionará.

    Uma das pernas do LED é o pino positivo, e a outra é o pino negativo. O LED não é perfeitamente redondo e é ligeiramente mais plano de um lado. O lado ligeiramente mais plano é o pino negativo. Ao conectar o LED ao módulo, certifique-se de que o pino do lado arredondado esteja conectado ao soquete marcado com **+** na parte externa do módulo, e o lado mais plano esteja conectado ao soquete mais próximo do centro do módulo.

1. O módulo LED possui um botão giratório que permite controlar o brilho. Gire-o completamente para começar, girando no sentido anti-horário até o limite usando uma pequena chave de fenda Phillips.

1. Insira uma extremidade de um cabo Grove no soquete do módulo LED. Ele só encaixará de uma maneira.

1. Com o Raspberry Pi desligado, conecte a outra extremidade do cabo Grove ao soquete digital marcado como **D5** no Grove Base Hat conectado ao Pi. Este soquete é o segundo da esquerda, na fileira de soquetes ao lado dos pinos GPIO.

![O LED Grove conectado ao soquete D5](../../../../../translated_images/pt-BR/pi-led.97f1d474981dc35d.webp)

## Programe a luz noturna

A luz noturna agora pode ser programada usando o sensor de luz Grove e o LED Grove.

### Tarefa - programar a luz noturna

Programe a luz noturna.

1. Ligue o Raspberry Pi e aguarde a inicialização.

1. Abra o projeto da luz noturna no VS Code que você criou na parte anterior desta tarefa, seja executando diretamente no Pi ou conectado usando a extensão Remote SSH.

1. Adicione o seguinte código ao arquivo `app.py` para importar uma biblioteca necessária. Isso deve ser adicionado no topo, abaixo das outras linhas de `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    A instrução `from grove.grove_led import GroveLed` importa o `GroveLed` das bibliotecas Python do Grove. Esta biblioteca contém o código para interagir com um LED Grove.

1. Adicione o seguinte código após a declaração de `light_sensor` para criar uma instância da classe que gerencia o LED:

    ```python
    led = GroveLed(5)
    ```

    A linha `led = GroveLed(5)` cria uma instância da classe `GroveLed` conectando ao pino **D5** - o pino digital Grove ao qual o LED está conectado.

    > 💁 Todos os soquetes possuem números de pinos únicos. Os pinos 0, 2, 4 e 6 são pinos analógicos, enquanto os pinos 5, 16, 18, 22, 24 e 26 são pinos digitais.

1. Adicione uma verificação dentro do loop `while`, antes do `time.sleep`, para verificar os níveis de luz e ligar ou desligar o LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Este código verifica o valor de `light`. Se for menor que 300, ele chama o método `on` da classe `GroveLed`, que envia um valor digital de 1 para o LED, ligando-o. Se o valor de luz for maior ou igual a 300, ele chama o método `off`, enviando um valor digital de 0 para o LED, desligando-o.

    > 💁 Este código deve estar indentado no mesmo nível da linha `print('Light level:', light)` para estar dentro do loop while!

    > 💁 Ao enviar valores digitais para atuadores, um valor 0 corresponde a 0V, e um valor 1 corresponde à voltagem máxima do dispositivo. Para o Raspberry Pi com sensores e atuadores Grove, a voltagem de 1 é 3,3V.

1. No Terminal do VS Code, execute o seguinte comando para rodar seu aplicativo Python:

    ```sh
    python3 app.py
    ```

    Os valores de luz serão exibidos no console.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Cubra e descubra o sensor de luz. Observe como o LED acende se o nível de luz for 300 ou menos, e apaga quando o nível de luz for maior que 300.

    > 💁 Se o LED não acender, certifique-se de que ele está conectado na orientação correta e que o botão giratório está ajustado para o máximo.

![O LED conectado ao Pi acendendo e apagando conforme o nível de luz muda](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Você pode encontrar este código na pasta [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Seu programa de luz noturna foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.