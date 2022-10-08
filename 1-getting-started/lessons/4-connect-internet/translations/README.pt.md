# Conecte seu dispositivo à Internet

![Uma visão geral do sketchnote desta lição](../../../sketchnotes/lesson-4.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Clique na imagem para uma versão maior.

Esta lição foi ministrada como parte da [série Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) do [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT .mc_id=academic-17441-jabenn). A aula foi ministrada em 2 vídeos - uma aula de 1 hora e uma hora de expediente de 1 hora, mergulhando mais profundamente em partes da aula e respondendo a perguntas.

[![Lição 4: Conecte seu dispositivo à Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lição 4: Conecte seu dispositivo à Internet - Horário comercial](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q )

> 🎥 Clique nas imagens acima para assistir aos vídeos

## Teste pré-aula

[Teste pré-aula](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introdução

O **I** em IoT significa **Internet** - a conectividade em nuvem e os serviços que permitem muitos dos recursos dos dispositivos IoT, desde a coleta de medições dos sensores conectados ao dispositivo até o envio de mensagens para controlar os atuadores . Os dispositivos de IoT normalmente se conectam a um único serviço de IoT em nuvem usando um protocolo de comunicação padrão, e esse serviço é conectado ao restante de seu aplicativo de IoT, desde serviços de IA para tomar decisões inteligentes sobre seus dados até aplicativos da Web para controle ou geração de relatórios.

> 🎓 Os dados coletados de sensores e enviados para a nuvem são chamados de telemetria.

Os dispositivos IoT podem receber mensagens da nuvem. Muitas vezes, as mensagens contêm comandos - ou seja, instruções para executar uma ação internamente (como reinicializar ou atualizar o firmware) ou usando um atuador (como acender uma luz).

Esta lição apresenta alguns dos protocolos de comunicação que os dispositivos IoT podem usar para se conectar à nuvem e os tipos de dados que eles podem enviar ou receber. Você também terá experiência com ambos, adicionando controle de internet à sua luz noturna, movendo a lógica de controle de LED para o código 'servidor' executado localmente.

Nesta lição abordaremos:

* [Protocolos de comunicação](#protocolos-de-comunicação)
* [Message Queueing Telemetry Transport (MQTT)](#message-queueing-telemetry-transport-mqtt)
* [Telemetria](#telemetria)
* [Commands](#commands)

## Protocolos de comunicação

Existem vários protocolos de comunicação populares usados por dispositivos IoT para se comunicar com a Internet. Os mais populares são baseados em mensagens de publicação/assinatura por meio de algum tipo de corretor. Os dispositivos IoT se conectam ao broker e publicam telemetria e assinam comandos. Os serviços de nuvem também se conectam ao broker e assinam todas as mensagens de telemetria e publicam comandos para dispositivos específicos ou para grupos de dispositivos.

![Os dispositivos IoT se conectam a um broker e publicam telemetria e assinam comandos. Os serviços em nuvem se conectam ao broker e assinam toda a telemetria e enviam comandos para dispositivos específicos.](../../../../images/pub-sub.png)

O MQTT é o protocolo de comunicação mais popular para dispositivos IoT e é abordado nesta lição. Outros protocolos incluem AMQP e HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) é um protocolo de mensagens padrão aberto e leve que pode enviar mensagens entre dispositivos. Ele foi projetado em 1999 para monitorar oleodutos, antes de ser lançado como um padrão aberto 15 anos depois pela IBM.

O MQTT possui um único broker e vários clientes. Todos os clientes se conectam ao broker e o broker roteia mensagens para os clientes relevantes. As mensagens são roteadas usando tópicos nomeados, em vez de serem enviadas diretamente para um cliente individual. Um cliente pode publicar em um tópico e qualquer cliente que se inscrever nesse tópico receberá a mensagem.

![telemetria de publicação de dispositivo IoT no tópico /telemetry e o serviço de nuvem assinando esse tópico](../../../../images/mqtt.png)

✅ Pesquise. Se você tiver muitos dispositivos IoT, como garantir que seu agente MQTT possa lidar com todas as mensagens?

### Conecte seu dispositivo IoT ao MQTT

A primeira parte de adicionar o controle da Internet ao seu nightlight é conectá-lo a um broker MQTT.

#### Tarefa

Conecte seu dispositivo a um broker MQTT.

Nesta parte da lição, você conectará sua luz noturna IoT à Internet para permitir que ela seja controlada remotamente. Mais adiante nesta lição, seu dispositivo IoT enviará uma mensagem de telemetria por MQTT para um broker MQTT público com o nível leve, onde será captado por algum código de servidor que você escreverá. Este código verificará o nível de luz e enviará uma mensagem de comando de volta ao dispositivo, informando-o para ligar ou desligar o LED.

O caso de uso do mundo real para essa configuração pode ser coletar dados de vários sensores de luz antes de decidir acender as luzes, em um local com muitas luzes, como um estádio. Isso poderia impedir que as luzes fossem acesas se apenas um sensor estivesse coberto por nuvens ou um pássaro, mas os outros sensores detectassem luz suficiente.

✅ Que outras situações exigiriam que os dados de vários sensores fossem avaliados antes de enviar comandos?

Em vez de lidar com as complexidades de configurar um corretor MQTT como parte desta tarefa, você pode usar um servidor de teste público que executa o [Eclipse Mosquitto](https://www.mosquitto.org), um corretor MQTT de código aberto. Este corretor de teste está disponível publicamente em [test.mosquitto.org](https://test.mosquitto.org) e não requer que uma conta seja configurada, tornando-se uma ótima ferramenta para testar clientes e servidores MQTT.

> 💁 Este corretor de teste é público e não seguro. Qualquer pessoa pode estar ouvindo o que você publica, portanto, não deve ser usado com nenhum dado que precise ser mantido privado

![Um fluxograma da atribuição mostrando os níveis de luz sendo lidos e verificados, e o LED começa a ser controlado](../../../../images/assignment-1-internet-flow.png)

Siga a etapa relevante abaixo para conectar seu dispositivo ao broker MQTT:

* [Arduino - Terminal Wio](wio-terminal-mqtt.md)
* [Computador de placa única - dispositivo Raspberry Pi/Virtual IoT](computador de placa única-mqtt.md)

### Um mergulho mais profundo no MQTT

Os tópicos podem ter uma hierarquia e os clientes podem se inscrever em diferentes níveis da hierarquia usando curingas. Por exemplo, você pode enviar mensagens de telemetria de temperatura para o tópico `/telemetry/temperature` e mensagens de umidade para o tópico `/telemetry/humidity`. mensagens de telemetria de temperatura e umidade.

As mensagens podem ser enviadas com uma qualidade de serviço (QoS), que determina a garantia do recebimento da mensagem.

* No máximo uma vez - a mensagem é enviada apenas uma vez e o cliente e o corretor não realizam etapas adicionais para confirmar a entrega (disparar e esquecer).
* Pelo menos uma vez - a mensagem é repetida pelo remetente várias vezes até que a confirmação seja recebida (entrega confirmada).
* Exatamente uma vez - o remetente e o destinatário realizam um handshake de dois níveis para garantir que apenas uma cópia da mensagem seja recebida (entrega garantida).

✅ Que situações podem exigir uma mensagem de entrega garantida sobre uma mensagem de incêndio e esquecimento?

Embora o nome seja Enfileiramento de Mensagens (iniciais em MQTT), na verdade ele não oferece suporte a filas de mensagens. Isso significa que se um cliente se desconectar e depois se reconectar, ele não receberá mensagens enviadas durante a desconexão, exceto aquelas mensagens que ele já havia começado a processar usando o processo de QoS. As mensagens podem ter um sinalizador retido definido nelas. Se isso for definido, o broker MQTT armazenará a última mensagem enviada em um tópico com esse sinalizador e a enviará para qualquer cliente que assinar o tópico posteriormente. Dessa forma, os clientes sempre receberão a mensagem mais recente.

O MQTT também suporta uma função keep alive que verifica se a conexão ainda está ativa durante longos intervalos entre as mensagens.

> 🦟 [Mosquitto da Eclipse Foundation](https://mosquitto.org) tem um corretor MQTT gratuito que você pode executar para experimentar o MQTT, juntamente com um corretor MQTT público que você pode usar para testar seu código, hospedado em [test.mosquitto.org](https://test.mosquitto.org).

As conexões MQTT podem ser públicas e abertas ou criptografadas e protegidas usando nomes de usuário e senhas ou certificados.

> 💁 O MQTT se comunica por TCP/IP, o mesmo protocolo de rede subjacente do HTTP, mas em uma porta diferente. Você também pode usar o MQTT em websockets para se comunicar com aplicativos da Web executados em um navegador ou em situações em que firewalls ou outras regras de rede bloqueiam conexões MQTT padrão.

## Telemetria

A palavra telemetria é derivada das raízes gregas que significam medir remotamente. A telemetria é o ato de coletar dados de sensores e enviá-los para a nuvem.

> 💁 Um dos primeiros dispositivos de telemetria foi inventado na França em 1874 e enviava o clima em tempo real e as profundidades da neve do Mont Blanc a Paris. Ele usava fios físicos, pois as tecnologias sem fio não estavam disponíveis na época.

Vamos relembrar o exemplo do termostato inteligente da Lição 1.

![Um termostato conectado à Internet usando vários sensores de ambiente](../../../../images/telemetry.png)

O termostato possui sensores de temperatura para coletar telemetria. Ele provavelmente teria um sensor de temperatura embutido e poderia se conectar a vários sensores de temperatura externos por meio de um protocolo sem fio, como [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Um exemplo dos dados de telemetria que enviaria poderia ser:

| Name | Value | Description |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | A temperatura medida pelo sensor de temperatura embutido do termostato |
| `livingroom_temperature` | 19°C | A temperatura medida por um sensor de temperatura remoto que foi chamado de "sala de estar" para identificar a sala em que está |
| `bedroom_temperature` | 21°C | A temperatura medida por um sensor de temperatura remoto que foi chamado de "quarto" para identificar a sala em que está |

O serviço de nuvem pode então usar esses dados de telemetria para tomar decisões sobre quais comandos enviar para controlar o aquecimento.

### Envie telemetria do seu dispositivo IoT

A próxima parte da adição de controle de Internet à sua luz noturna é enviar a telemetria de nível de luz para o agente MQTT em um tópico de telemetria.

#### Tarefa - enviar telemetria do seu dispositivo IoT

Envie telemetria de nível leve para o broker MQTT.

Os dados são enviados codificados como JSON - abreviação de JavaScript Object Notation, um padrão para codificar dados em texto usando pares de chave/valor.

✅ Se você ainda não encontrou o JSON, saiba mais sobre ele na [documentação do JSON.org](https://www.json.org/).

Siga a etapa relevante abaixo para enviar a telemetria do seu dispositivo para o agente MQTT:

* [Arduino - Terminal Wio](wio-terminal-telemetry.md)
* [Computador de placa única - dispositivo Raspberry Pi/Virtual IoT](single-board-computer-telemetry.md)

### Receber telemetria do broker MQTT

Não adianta enviar telemetria se não houver nada do outro lado para ouvi-la. A telemetria de nível de luz precisa de algo que a escute para processar os dados. Esse código 'servidor' é o tipo de código que você implantará em um serviço de nuvem como parte de um aplicativo IoT maior, mas aqui você executará esse código localmente no seu computador (ou no seu Pi, se estiver codificando diretamente lá ). O código do servidor consiste em um aplicativo Python que escuta mensagens de telemetria em MQTT com níveis leves. Mais adiante nesta lição, você fará com que ele responda com uma mensagem de comando com instruções para ligar ou desligar o LED.

✅ Faça alguma pesquisa: O que acontece com as mensagens MQTT se não houver um ouvinte?

#### Instale o Python e o VS Code

Se você não tiver o Python e o VS Code instalados localmente, precisará instalá-los para codificar o servidor. Se você estiver usando um dispositivo IoT virtual ou estiver trabalhando em seu Raspberry Pi, pule esta etapa, pois já deve tê-lo instalado e configurado.

##### Tarefa - instale o Python e o VS Code

Instale o Python e o VS Code.

1. Instale o Python. Consulte a [página de downloads do Python](https://www.python.org/downloads/) para obter instruções sobre como instalar a versão mais recente do Python.

1. Instale o Visual Studio Code (VS Code). Este é o editor que você usará para escrever o código do seu dispositivo virtual em Python. Consulte a [documentação do VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) para obter instruções sobre como instalar o VS Code.

    > 💁 Você pode usar qualquer IDE ou editor Python para essas lições se tiver uma ferramenta preferida, mas as lições fornecerão instruções baseadas no uso do VS Code.

1. Instale a extensão VS Code Pylance. Esta é uma extensão para o VS Code que fornece suporte à linguagem Python. Consulte a [documentação da extensão Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para obter instruções sobre como instalar essa extensão no VS Code.

#### Configurar um ambiente virtual Python

Um dos recursos poderosos do Python é a capacidade de instalar [pacotes pip](https://pypi.org) - são pacotes de código escritos por outras pessoas e publicados na Internet. Você pode instalar um pacote pip em seu computador com um comando e usar esse pacote em seu código. Você usará o pip para instalar um pacote para se comunicar pelo MQTT.

Por padrão, quando você instala um pacote, ele fica disponível em todos os lugares do seu computador, e isso pode levar a problemas com as versões do pacote - como um aplicativo dependendo de uma versão de um pacote que quebra quando você instala uma nova versão para um aplicativo diferente. Para contornar esse problema, você pode usar um [ambiente virtual Python](https://docs.python.org/3/library/venv.html), essencialmente uma cópia do Python em uma pasta dedicada, e quando você instala o pip pacotes eles são instalados apenas para essa pasta.

##### Tarefa - configurar um ambiente virtual Python

Configure um ambiente virtual Python e instale os pacotes pip MQTT.

1. Em seu terminal ou linha de comando, execute o seguinte em um local de sua escolha para criar e navegar para um novo diretório:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Agora execute o seguinte para criar um ambiente virtual na pasta `.venv`

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Você precisa chamar explicitamente `python3` para criar o ambiente virtual caso você tenha o Python 2 instalado além do Python 3 (a versão mais recente). Se você tiver o Python2 instalado, chamar `python` usará o Python 2 em vez do Python 3

1. Ative o ambiente virtual:

    * No Windows:
        * Se você estiver usando o Prompt de Comando ou o Prompt de Comando pelo Terminal do Windows, execute:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Se você estiver usando o PowerShell, execute:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * No macOS ou Linux, execute:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Esses comandos devem ser executados no mesmo local em que você executou o comando para criar o ambiente virtual. Você nunca precisará navegar na pasta `.venv`, você deve sempre executar o comando activate e quaisquer comandos para instalar pacotes ou executar o código da pasta em que você estava quando criou o ambiente virtual.

1. Assim que o ambiente virtual for ativado, o comando padrão `python` executará a versão do Python que foi usada para criar o ambiente virtual. Execute o seguinte para obter a versão:

    ```sh
    python --version
    ```

    A saída será semelhante à seguinte:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Sua versão do Python pode ser diferente - contanto que seja a versão 3.6 ou superior, você é bom. Caso contrário, exclua esta pasta, instale uma versão mais recente do Python e tente novamente.

1. Execute os comandos a seguir para instalar o pacote pip para [Paho-MQTT](https://pypi.org/project/paho-mqtt/), uma biblioteca MQTT popular.

    ```sh
    pip install paho-mqtt
    ```

    Este pacote pip será instalado apenas no ambiente virtual e não estará disponível fora dele.

#### Escreva o código do servidor

O código do servidor agora pode ser escrito em Python.

##### Tarefa - escreva o código do servidor

Escreva o código do servidor.

1. Em seu terminal ou linha de comando, execute o seguinte dentro do ambiente virtual para criar um arquivo Python chamado `app.py`:

     * No Windows, execute:

        ```cmd
        type nul > app.py
        ```

    * No macOS ou Linux, execute:

        ```cmd
        touch app.py
        ```

1. Abra a pasta atual no VS Code:

    ```sh
    code .
    ```

1. Quando o VS Code for iniciado, ele ativará o ambiente virtual do Python. Isso será relatado na barra de status inferior:

     ![VS Code mostrando o ambiente virtual selecionado](../../../images/vscode-virtual-env.png)

1. Se o VS Code Terminal já estiver em execução quando o VS Code for inicializado, ele não terá o ambiente virtual ativado nele. A coisa mais fácil de fazer é matar o terminal usando o botão **Kill the active terminal instance**:

     ![VS Code Kill the active terminal instance button](../../../images/vscode-kill-terminal.png)

1. Inicie um novo Terminal VS Code selecionando *Terminal -> New Terminal, ou pressionando `` CTRL+` ``. O novo terminal carregará o ambiente virtual, com a chamada para ativá-lo aparecendo no terminal. O nome do ambiente virtual (`.venv`) também estará no prompt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Abra o arquivo `app.py` no explorador do VS Code e adicione o seguinte código:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Substitua `<ID>` na linha 6 pelo ID exclusivo que você usou ao criar o código do seu dispositivo.

    ⚠️ Este **deve** ser o mesmo ID que você usou em seu dispositivo, ou o código do servidor não será inscrito ou publicado no tópico correto.

    Esse código cria um cliente MQTT com um nome exclusivo e se conecta ao broker *test.mosquitto.org*. Em seguida, ele inicia um loop de processamento que é executado em um thread em segundo plano, ouvindo mensagens em qualquer tópico inscrito.

     O cliente então assina mensagens no tópico de telemetria e define uma função que é chamada quando uma mensagem é recebida. Quando uma mensagem de telemetria é recebida, a função `handle_telemetry` é chamada, imprimindo a mensagem recebida no console.

     Finalmente, um loop infinito mantém o aplicativo em execução. O cliente MQTT está ouvindo mensagens em um encadeamento em segundo plano e é executado o tempo todo em que o aplicativo principal está em execução.

1. No terminal do VS Code, execute o seguinte para executar seu aplicativo Python:

    ```sh
    python app.py
    ```

    O aplicativo começará a ouvir as mensagens do dispositivo IoT.

1. Certifique-se de que seu dispositivo esteja funcionando e enviando mensagens de telemetria. Ajuste os níveis de luz detectados pelo seu dispositivo físico ou virtual. As mensagens recebidas serão impressas no terminal.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    O arquivo app.py no ambiente virtual nightlight deve estar em execução para que o arquivo app.py no ambiente virtual nightlight-server receba as mensagens que estão sendo enviadas.

> 💁 Você pode encontrar este código na pasta [code-server/server](../code-server/server).

### Com que frequência a telemetria deve ser enviada?

Uma consideração importante com a telemetria é com que frequência medir e enviar os dados? A resposta é - depende. Se você mede com frequência, pode responder mais rapidamente às mudanças nas medições, mas usa mais energia, mais largura de banda, gera mais dados e precisa de mais recursos de nuvem para processar. Você precisa medir com frequência suficiente, mas não com muita frequência.

Para um termostato, medir a cada poucos minutos provavelmente é mais do que suficiente, pois as temperaturas não mudam com tanta frequência. Se você medir apenas uma vez por dia, poderá acabar aquecendo sua casa para temperaturas noturnas no meio de um dia ensolarado, enquanto se medir a cada segundo, terá milhares de medições de temperatura duplicadas desnecessariamente que consumirão a velocidade da Internet dos usuários e largura de banda (um problema para pessoas com planos de largura de banda limitados), usar mais energia, o que pode ser um problema para dispositivos alimentados por bateria, como sensores remotos, e aumentar o custo dos recursos de computação em nuvem dos provedores que os processam e armazenam.

Se você estiver monitorando dados em torno de uma máquina em uma fábrica que, se falhar, pode causar danos catastróficos e milhões de dólares em receita perdida, pode ser necessário medir várias vezes por segundo. É melhor desperdiçar largura de banda do que perder a telemetria que indica que uma máquina precisa ser parada e consertada antes de quebrar.

> 💁 Nessa situação, você pode considerar ter um dispositivo de borda para processar a telemetria primeiro para reduzir a dependência da Internet.

### Perda de conectividade

As conexões com a Internet podem não ser confiáveis, com interrupções comuns. O que um dispositivo IoT deve fazer nessas circunstâncias - ele deve perder os dados ou deve armazená-los até que a conectividade seja restaurada? Novamente, a resposta é depende.

Para um termostato, os dados provavelmente podem ser perdidos assim que uma nova medição de temperatura for feita. O sistema de aquecimento não se importa que 20 minutos atrás era 20,5°C se a temperatura agora é 19°C, é a temperatura agora que determina se o aquecimento deve ser ligado ou desligado.

Para máquinas, você pode querer manter os dados, especialmente se for usado para procurar tendências. Existem modelos de aprendizado de máquina que podem detectar anomalias em fluxos de dados examinando dados de um período de tempo definido (como a última hora) e identificando dados anômalos. Isso geralmente é usado para manutenção preditiva, procurando indicações de que algo pode quebrar em breve para que você possa repará-lo ou substituí-lo antes que isso aconteça. Você pode querer que cada bit de telemetria de uma máquina seja enviado para que possa ser processado para detecção de anomalias, portanto, assim que o dispositivo IoT puder se reconectar, ele enviará toda a telemetria gerada durante a interrupção da Internet.

Os designers de dispositivos IoT também devem considerar se o dispositivo IoT pode ser usado durante uma interrupção na Internet ou perda de sinal causada pela localização. Um termostato inteligente deve ser capaz de tomar algumas decisões limitadas para controlar o aquecimento se não puder enviar telemetria para a nuvem devido a uma interrupção.

[![Este ferrari foi emparedado porque alguém tentou atualizá-lo no subsolo, onde não há recepção de celular](../../../../images/bricked-car.png)](https://twitter.com/internetofshit/status/1315736960082808832)

Para que o MQTT lide com uma perda de conectividade, o código do dispositivo e do servidor precisará ser responsável por garantir a entrega da mensagem, se necessário, por exemplo, exigindo que todas as mensagens enviadas sejam respondidas por mensagens adicionais em um tópico de resposta e, se não eles são enfileirados manualmente para serem reproduzidos posteriormente.

## Commands

Comandos são mensagens enviadas pela nuvem para um dispositivo, instruindo-o a fazer algo. Na maioria das vezes, isso envolve fornecer algum tipo de saída por meio de um atuador, mas pode ser uma instrução para o próprio dispositivo, como reinicializar ou reunir telemetria extra e devolvê-la como resposta ao comando.

![Um termostato conectado à Internet recebendo um comando para ligar o aquecimento](../../../images/commands.png)

Um termostato poderia receber um comando da nuvem para ligar o aquecimento. Com base nos dados de telemetria de todos os sensores, se o serviço de nuvem decidiu que o aquecimento deve estar ligado, ele envia o comando relevante.

### Envie comandos para o broker MQTT

O próximo passo para nossa luz noturna controlada pela Internet é que o código do servidor envie um comando de volta ao dispositivo IoT para controlar a luz com base nos níveis de luz detectados.

1. Abra o código do servidor no VS Code

1. Adicione a seguinte linha após a declaração do `client_telemetry_topic` para definir para qual tópico enviar comandos:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Adicione o seguinte código ao final da função `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Isso envia uma mensagem JSON para o tópico de comando com o valor de `led_on` definido como verdadeiro ou falso, dependendo se a luz for menor que 300 ou não. Se a luz for menor que 300, true é enviado para instruir o dispositivo a ligar o LED.

1. Execute o código como antes

1. Ajuste os níveis de luz detectados pelo seu dispositivo físico ou virtual. As mensagens recebidas e os comandos enviados serão gravados no terminal:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 A telemetria e os comandos estão sendo enviados em um único tópico cada. Isso significa que a telemetria de vários dispositivos aparecerá no mesmo tópico de telemetria e os comandos para vários dispositivos aparecerão no mesmo tópico de comandos. Se você quiser enviar um comando para um dispositivo específico, poderá usar vários tópicos, nomeados com um ID de dispositivo exclusivo, como `/commands/device1`, `/commands/device2`. Dessa forma, um dispositivo pode ouvir mensagens destinadas apenas a esse dispositivo.

> 💁 Você pode encontrar este código na pasta [code-commands/server](code-commands/server).

### Manipular comandos no dispositivo IoT

Agora que os comandos estão sendo enviados do servidor, você pode adicionar código ao dispositivo IoT para lidar com eles e controlar o LED.

Siga a etapa relevante abaixo para ouvir os comandos do broker MQTT:

* [Arduino - Terminal Wio](wio-terminal-commands.md)
* [Computador de placa única - dispositivo Raspberry Pi/Virtual IoT](single-board-computer-commands.md)

Depois que esse código estiver escrito e em execução, experimente alterar os níveis de luz. Observe a saída do servidor e do dispositivo e observe o LED conforme você altera os níveis de luz.

### Perda de conectividade

O que um serviço de nuvem deve fazer se precisar enviar um comando para um dispositivo IoT que está offline? Novamente, a resposta é depende.

Se o comando mais recente substituir um anterior, os anteriores provavelmente poderão ser ignorados. Se um serviço de nuvem envia um comando para ligar o aquecimento e, em seguida, envia um comando para desligá-lo, o comando de ligar pode ser ignorado e não reenviado.

Se os comandos precisarem ser processados em sequência, como mover um braço do robô para cima e fechar um grabber, eles precisam ser enviados em ordem assim que a conectividade for restaurada.

✅ Como o código do dispositivo ou do servidor pode garantir que os comandos sejam sempre enviados e manipulados em ordem no MQTT, se necessário?

---

## 🚀 Desafio

O desafio nas últimas três lições foi listar o maior número possível de dispositivos IoT que estão em sua casa, escola ou local de trabalho e decidir se eles são construídos em torno de microcontroladores ou computadores de placa única, ou mesmo uma mistura de ambos, e pensar sobre quais sensores e atuadores eles estão usando.

Para esses dispositivos, pense em quais mensagens eles podem estar enviando ou recebendo. Que telemetria eles enviam? Que mensagens ou comandos eles podem receber? Você acha que eles são seguros?

## Questionário pós-aula

[Quiz pós-aula](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Revisão e autoestudo

Leia mais sobre MQTT na [página MQTT Wikipedia](https://wikipedia.org/wiki/MQTT).

Tente executar você mesmo um broker MQTT usando [Mosquitto](https://www.mosquitto.org) e conecte-se a ele a partir de seu dispositivo IoT e código do servidor.

> 💁 Dica - por padrão, o Mosquitto não permite conexões anônimas (ou seja, conexão sem nome de usuário e senha), e não permite conexões de fora do computador em que está sendo executado.
> Você pode corrigir isso com um [arquivo de configuração `mosquitto.conf`](https://www.mosquitto.org/man/mosquitto-conf-5.html) com o seguinte:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Tarefa

[Compare e contraste o MQTT com outros protocolos de comunicação](assignment.pt.md)
