# Construa uma luz noturna - Hardware IoT Virtual

Nesta parte da lição, você adicionará um LED ao seu dispositivo IoT virtual e o usará para criar uma luz noturna.

## Hardware Virtual

A luz noturna precisa de um atuador, criado no aplicativo CounterFit.

O atuador é um **LED**. Em um dispositivo IoT físico, seria um [diodo emissor de luz](https://wikipedia.org/wiki/Light-emitting_diode) que emite luz quando a corrente passa por ele. Este é um atuador digital que possui 2 estados: ligado e desligado. Enviar um valor de 1 liga o LED, e 0 o desliga.

A lógica da luz noturna em pseudocódigo é:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Adicionar o atuador ao CounterFit

Para usar um LED virtual, você precisa adicioná-lo ao aplicativo CounterFit.

#### Tarefa - adicionar o atuador ao CounterFit

Adicione o LED ao aplicativo CounterFit.

1. Certifique-se de que o aplicativo web CounterFit está em execução a partir da parte anterior desta tarefa. Caso contrário, inicie-o e re-adicione o sensor de luz.

1. Crie um LED:

    1. Na caixa *Create actuator* no painel *Actuator*, abra o menu suspenso *Actuator type* e selecione *LED*.

    1. Defina o *Pin* como *5*.

    1. Selecione o botão **Add** para criar o LED no pino 5.

    ![As configurações do LED](../../../../../translated_images/pt-BR/counterfit-create-led.ba9db1c9b8c622a6.webp)

    O LED será criado e aparecerá na lista de atuadores.

    ![O LED criado](../../../../../translated_images/pt-BR/counterfit-led.c0ab02de6d256ad8.webp)

    Depois que o LED for criado, você pode alterar a cor usando o seletor *Color*. Selecione o botão **Set** para alterar a cor após escolhê-la.

### Programar a luz noturna

Agora, a luz noturna pode ser programada usando o sensor de luz e o LED do CounterFit.

#### Tarefa - programar a luz noturna

Programe a luz noturna.

1. Abra o projeto da luz noturna no VS Code que você criou na parte anterior desta tarefa. Finalize e recrie o terminal para garantir que ele esteja sendo executado no ambiente virtual, se necessário.

1. Abra o arquivo `app.py`.

1. Adicione o seguinte código ao arquivo `app.py` para importar uma biblioteca necessária. Isso deve ser adicionado no topo, abaixo das outras linhas de `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    A instrução `from counterfit_shims_grove.grove_led import GroveLed` importa o `GroveLed` das bibliotecas Python shim do CounterFit Grove. Esta biblioteca contém o código para interagir com um LED criado no aplicativo CounterFit.

1. Adicione o seguinte código após a declaração de `light_sensor` para criar uma instância da classe que gerencia o LED:

    ```python
    led = GroveLed(5)
    ```

    A linha `led = GroveLed(5)` cria uma instância da classe `GroveLed` conectando-se ao pino **5** - o pino do CounterFit Grove ao qual o LED está conectado.

1. Adicione uma verificação dentro do loop `while`, antes do `time.sleep`, para verificar os níveis de luz e ligar ou desligar o LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Este código verifica o valor de `light`. Se for menor que 300, ele chama o método `on` da classe `GroveLed`, que envia um valor digital de 1 para o LED, ligando-o. Se o valor de luz for maior ou igual a 300, ele chama o método `off`, enviando um valor digital de 0 para o LED, desligando-o.

    > 💁 Este código deve estar indentado no mesmo nível da linha `print('Light level:', light)` para estar dentro do loop while!

1. No Terminal do VS Code, execute o seguinte comando para rodar seu aplicativo Python:

    ```sh
    python3 app.py
    ```

    Os valores de luz serão exibidos no console.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Altere as configurações de *Value* ou *Random* para variar o nível de luz acima e abaixo de 300. O LED ligará e desligará.

![O LED no aplicativo CounterFit ligando e desligando conforme o nível de luz muda](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Você pode encontrar este código na pasta [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Seu programa de luz noturna foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.