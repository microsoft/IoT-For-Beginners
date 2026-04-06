# Construir uma luz de presença - Raspberry Pi

Nesta parte da lição, vais adicionar um LED ao teu Raspberry Pi e utilizá-lo para criar uma luz de presença.

## Hardware

A luz de presença agora precisa de um atuador.

O atuador é um **LED**, um [díodo emissor de luz](https://wikipedia.org/wiki/Diodo_emissor_de_luz) que emite luz quando a corrente passa por ele. Este é um atuador digital que tem dois estados: ligado e desligado. Enviar um valor de 1 liga o LED, e 0 desliga-o. O LED é um atuador externo Grove e precisa de ser ligado ao Grove Base hat no Raspberry Pi.

A lógica da luz de presença em pseudo-código é:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Ligar o LED

O LED Grove vem como um módulo com uma seleção de LEDs, permitindo-te escolher a cor.

#### Tarefa - ligar o LED

Liga o LED.

![Um LED Grove](../../../../../translated_images/pt-PT/grove-led.6c853be93f473cf2.webp)

1. Escolhe o teu LED favorito e insere as pernas nos dois orifícios do módulo LED.

    Os LEDs são díodos emissores de luz, e os díodos são dispositivos eletrónicos que só permitem a passagem de corrente num sentido. Isto significa que o LED precisa de ser ligado na orientação correta, caso contrário não funcionará.

    Uma das pernas do LED é o pino positivo, e a outra é o pino negativo. O LED não é perfeitamente redondo e é ligeiramente mais achatado de um lado. O lado ligeiramente mais achatado é o pino negativo. Quando ligares o LED ao módulo, certifica-te de que o pino do lado arredondado está ligado à tomada marcada com **+** na parte externa do módulo, e o lado achatado está ligado à tomada mais próxima do centro do módulo.

1. O módulo LED tem um botão rotativo que permite controlar o brilho. Gira-o completamente para cima no início, rodando-o no sentido anti-horário até ao limite, utilizando uma pequena chave de fendas Phillips.

1. Insere uma extremidade de um cabo Grove na tomada do módulo LED. Ele só encaixará de uma forma.

1. Com o Raspberry Pi desligado, liga a outra extremidade do cabo Grove à tomada digital marcada como **D5** no Grove Base hat ligado ao Pi. Esta tomada é a segunda a contar da esquerda, na fila de tomadas ao lado dos pinos GPIO.

![O LED Grove ligado à tomada D5](../../../../../translated_images/pt-PT/pi-led.97f1d474981dc35d.webp)

## Programar a luz de presença

A luz de presença pode agora ser programada utilizando o sensor de luz Grove e o LED Grove.

### Tarefa - programar a luz de presença

Programa a luz de presença.

1. Liga o Pi e espera que ele inicie.

1. Abre o projeto da luz de presença no VS Code que criaste na parte anterior desta tarefa, seja diretamente no Pi ou conectado usando a extensão Remote SSH.

1. Adiciona o seguinte código ao ficheiro `app.py` para importar uma biblioteca necessária. Isto deve ser adicionado no topo, abaixo das outras linhas `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    A instrução `from grove.grove_led import GroveLed` importa o `GroveLed` das bibliotecas Python Grove. Esta biblioteca contém código para interagir com um LED Grove.

1. Adiciona o seguinte código após a declaração `light_sensor` para criar uma instância da classe que gere o LED:

    ```python
    led = GroveLed(5)
    ```

    A linha `led = GroveLed(5)` cria uma instância da classe `GroveLed` conectada ao pino **D5** - o pino digital Grove ao qual o LED está ligado.

    > 💁 Todas as tomadas têm números de pinos únicos. Os pinos 0, 2, 4 e 6 são pinos analógicos, enquanto os pinos 5, 16, 18, 22, 24 e 26 são pinos digitais.

1. Adiciona uma verificação dentro do `while` loop, antes do `time.sleep`, para verificar os níveis de luz e ligar ou desligar o LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Este código verifica o valor de `light`. Se for inferior a 300, chama o método `on` da classe `GroveLed`, que envia um valor digital de 1 para o LED, ligando-o. Se o valor de luz for maior ou igual a 300, chama o método `off`, enviando um valor digital de 0 para o LED, desligando-o.

    > 💁 Este código deve estar indentado ao mesmo nível que a linha `print('Light level:', light)` para estar dentro do loop while!

    > 💁 Ao enviar valores digitais para atuadores, um valor de 0 corresponde a 0V, e um valor de 1 corresponde à voltagem máxima do dispositivo. Para o Raspberry Pi com sensores e atuadores Grove, a voltagem de 1 é 3.3V.

1. No Terminal do VS Code, executa o seguinte comando para correr a tua aplicação Python:

    ```sh
    python3 app.py
    ```

    Os valores de luz serão exibidos na consola.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Cobre e descobre o sensor de luz. Observa como o LED acende se o nível de luz for 300 ou menos, e apaga-se quando o nível de luz for superior a 300.

    > 💁 Se o LED não acender, certifica-te de que está ligado na orientação correta e que o botão rotativo está ajustado para o máximo.

![O LED ligado ao Pi a acender e apagar conforme o nível de luz muda](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Podes encontrar este código na pasta [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 O teu programa de luz de presença foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.