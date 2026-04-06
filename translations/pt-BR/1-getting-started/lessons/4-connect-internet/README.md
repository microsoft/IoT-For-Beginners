# Conecte seu dispositivo à Internet

![Uma visão geral ilustrada desta lição](../../../../../translated_images/pt-BR/lesson-4.7344e074ea68fa54.webp)

> Ilustração por [Nitya Narasimhan](https://github.com/nitya). Clique na imagem para uma versão maior.

Esta lição foi ensinada como parte da série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) do [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). A lição foi apresentada em 2 vídeos - uma aula de 1 hora e uma sessão de perguntas e respostas de 1 hora, explorando mais a fundo partes da lição e respondendo dúvidas.

[![Lição 4: Conecte seu dispositivo à Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lição 4: Conecte seu dispositivo à Internet - Sessão de perguntas e respostas](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Clique nas imagens acima para assistir aos vídeos

## Questionário pré-aula

[Questionário pré-aula](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introdução

O **I** em IoT significa **Internet** - a conectividade com a nuvem e os serviços que possibilitam muitos dos recursos dos dispositivos IoT, desde coletar medições dos sensores conectados ao dispositivo até enviar mensagens para controlar os atuadores. Dispositivos IoT geralmente se conectam a um único serviço de IoT na nuvem usando um protocolo de comunicação padrão, e esse serviço está conectado ao restante da sua aplicação IoT, desde serviços de IA para tomar decisões inteligentes com base nos dados até aplicativos web para controle ou relatórios.

> 🎓 Dados coletados de sensores e enviados para a nuvem são chamados de telemetria.

Dispositivos IoT podem receber mensagens da nuvem. Muitas vezes, essas mensagens contêm comandos - ou seja, instruções para realizar uma ação, seja internamente (como reiniciar ou atualizar o firmware) ou usando um atuador (como acender uma luz).

Esta lição apresenta alguns dos protocolos de comunicação que dispositivos IoT podem usar para se conectar à nuvem e os tipos de dados que podem enviar ou receber. Você também colocará a mão na massa, adicionando controle pela Internet à sua luz noturna, movendo a lógica de controle do LED para um código 'servidor' executado localmente.

Nesta lição, abordaremos:

* [Protocolos de comunicação](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetria](../../../../../1-getting-started/lessons/4-connect-internet)
* [Comandos](../../../../../1-getting-started/lessons/4-connect-internet)

## Protocolos de comunicação

Existem vários protocolos de comunicação populares usados por dispositivos IoT para se comunicar com a Internet. Os mais comuns são baseados em mensagens de publicação/assinatura via algum tipo de broker. Os dispositivos IoT se conectam ao broker, publicam telemetria e assinam comandos. Os serviços na nuvem também se conectam ao broker, assinam todas as mensagens de telemetria e publicam comandos, seja para dispositivos específicos ou para grupos de dispositivos.

![Dispositivos IoT se conectam a um broker, publicam telemetria e assinam comandos. Serviços na nuvem se conectam ao broker, assinam toda a telemetria e enviam comandos para dispositivos específicos.](../../../../../translated_images/pt-BR/pub-sub.7c7ed43fe9fd15d4.webp)

O MQTT é o protocolo de comunicação mais popular para dispositivos IoT e será abordado nesta lição. Outros protocolos incluem AMQP e HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) é um protocolo de mensagens leve e de padrão aberto que pode enviar mensagens entre dispositivos. Ele foi projetado em 1999 para monitorar oleodutos, antes de ser lançado como um padrão aberto 15 anos depois pela IBM.

O MQTT possui um único broker e vários clientes. Todos os clientes se conectam ao broker, e o broker roteia mensagens para os clientes relevantes. As mensagens são roteadas usando tópicos nomeados, em vez de serem enviadas diretamente para um cliente individual. Um cliente pode publicar em um tópico, e qualquer cliente que assinar esse tópico receberá a mensagem.

![Dispositivo IoT publicando telemetria no tópico /telemetry, e o serviço na nuvem assinando esse tópico](../../../../../translated_images/pt-BR/mqtt.cbf7f21d9adc3e17.webp)

✅ Faça uma pesquisa. Se você tiver muitos dispositivos IoT, como garantir que seu broker MQTT consiga lidar com todas as mensagens?

### Conecte seu dispositivo IoT ao MQTT

A primeira parte para adicionar controle pela Internet à sua luz noturna é conectá-la a um broker MQTT.

#### Tarefa

Conecte seu dispositivo a um broker MQTT.

Nesta parte da lição, você conectará sua luz noturna IoT à Internet para permitir que ela seja controlada remotamente. Mais adiante nesta lição, seu dispositivo IoT enviará uma mensagem de telemetria via MQTT para um broker MQTT público com o nível de luz, onde será captada por um código de servidor que você escreverá. Esse código verificará o nível de luz e enviará uma mensagem de comando de volta ao dispositivo, instruindo-o a ligar ou desligar o LED.

O caso de uso real para tal configuração poderia ser coletar dados de vários sensores de luz antes de decidir acender as luzes em um local com muitas luzes, como um estádio. Isso poderia evitar que as luzes fossem acesas se apenas um sensor estivesse coberto por nuvens ou um pássaro, mas os outros sensores detectassem luz suficiente.

✅ Que outras situações exigiriam a avaliação de dados de múltiplos sensores antes de enviar comandos?

Em vez de lidar com as complexidades de configurar um broker MQTT como parte desta tarefa, você pode usar um servidor de teste público que executa o [Eclipse Mosquitto](https://www.mosquitto.org), um broker MQTT de código aberto. Este broker de teste está disponível publicamente em [test.mosquitto.org](https://test.mosquitto.org) e não requer a criação de uma conta, tornando-o uma ótima ferramenta para testar clientes e servidores MQTT.

> 💁 Este broker de teste é público e não seguro. Qualquer pessoa pode ouvir o que você publica, então ele não deve ser usado com dados que precisam ser mantidos privados.

![Um fluxograma da tarefa mostrando os níveis de luz sendo lidos e verificados, e o LED sendo controlado](../../../../../translated_images/pt-BR/assignment-1-internet-flow.3256feab5f052fd2.webp)

Siga a etapa relevante abaixo para conectar seu dispositivo ao broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Computador de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-mqtt.md)

### Explorando mais a fundo o MQTT

Os tópicos podem ter uma hierarquia, e os clientes podem assinar diferentes níveis da hierarquia usando curingas. Por exemplo, você pode enviar mensagens de telemetria de temperatura para o tópico `/telemetry/temperature` e mensagens de umidade para o tópico `/telemetry/humidity`, e então, no seu aplicativo na nuvem, assinar o tópico `/telemetry/*` para receber tanto as mensagens de telemetria de temperatura quanto de umidade.

As mensagens podem ser enviadas com uma qualidade de serviço (QoS), que determina a garantia de que a mensagem será recebida.

* No máximo uma vez - a mensagem é enviada apenas uma vez e o cliente e o broker não tomam medidas adicionais para reconhecer a entrega (enviar e esquecer).
* Pelo menos uma vez - a mensagem é reenviada pelo remetente várias vezes até que o reconhecimento seja recebido (entrega reconhecida).
* Exatamente uma vez - o remetente e o receptor realizam um handshake de dois níveis para garantir que apenas uma cópia da mensagem seja recebida (entrega garantida).

✅ Que situações podem exigir uma mensagem de entrega garantida em vez de uma mensagem de enviar e esquecer?

Embora o nome seja Message Queueing (iniciais em MQTT), ele na verdade não suporta filas de mensagens. Isso significa que, se um cliente se desconectar e depois reconectar, ele não receberá mensagens enviadas durante a desconexão, exceto aquelas mensagens que ele já havia começado a processar usando o processo de QoS. As mensagens podem ter um sinalizador de retenção ativado. Se este sinalizador estiver ativado, o broker MQTT armazenará a última mensagem enviada em um tópico com este sinalizador e a enviará para qualquer cliente que posteriormente assinar o tópico. Dessa forma, os clientes sempre receberão a mensagem mais recente.

O MQTT também suporta uma função de keep alive que verifica se a conexão ainda está ativa durante longos intervalos entre mensagens.

> 🦟 [Mosquitto da Eclipse Foundation](https://mosquitto.org) oferece um broker MQTT gratuito que você pode executar para experimentar o MQTT, além de um broker MQTT público que você pode usar para testar seu código, hospedado em [test.mosquitto.org](https://test.mosquitto.org).

As conexões MQTT podem ser públicas e abertas, ou criptografadas e protegidas usando nomes de usuário e senhas, ou certificados.

> 💁 O MQTT se comunica sobre TCP/IP, o mesmo protocolo de rede subjacente ao HTTP, mas em uma porta diferente. Você também pode usar MQTT sobre websockets para se comunicar com aplicativos web executados em um navegador ou em situações onde firewalls ou outras regras de rede bloqueiam conexões MQTT padrão.

## Telemetria

A palavra telemetria é derivada de raízes gregas que significam medir remotamente. Telemetria é o ato de coletar dados de sensores e enviá-los para a nuvem.

> 💁 Um dos primeiros dispositivos de telemetria foi inventado na França em 1874 e enviava em tempo real dados meteorológicos e de profundidade de neve do Mont Blanc para Paris. Ele usava fios físicos, já que tecnologias sem fio não estavam disponíveis na época.

Vamos voltar ao exemplo do termostato inteligente da Lição 1.

![Um termostato conectado à Internet usando múltiplos sensores de ambiente](../../../../../translated_images/pt-BR/telemetry.21e5d8b97649d2eb.webp)

O termostato possui sensores de temperatura para coletar telemetria. Ele provavelmente teria um sensor de temperatura embutido e poderia se conectar a vários sensores de temperatura externos por meio de um protocolo sem fio, como [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Um exemplo dos dados de telemetria que ele enviaria poderia ser:

| Nome | Valor | Descrição |
| ---- | ----- | --------- |
| `thermostat_temperature` | 18°C | A temperatura medida pelo sensor de temperatura embutido no termostato |
| `livingroom_temperature` | 19°C | A temperatura medida por um sensor remoto que foi nomeado como `livingroom` para identificar o cômodo onde está localizado |
| `bedroom_temperature` | 21°C | A temperatura medida por um sensor remoto que foi nomeado como `bedroom` para identificar o cômodo onde está localizado |

O serviço na nuvem pode então usar esses dados de telemetria para tomar decisões sobre quais comandos enviar para controlar o aquecimento.

### Enviar telemetria do seu dispositivo IoT

A próxima etapa para adicionar controle pela Internet à sua luz noturna é enviar a telemetria do nível de luz para o broker MQTT em um tópico de telemetria.

#### Tarefa - enviar telemetria do seu dispositivo IoT

Envie a telemetria do nível de luz para o broker MQTT.

Os dados são enviados codificados como JSON - abreviação de JavaScript Object Notation, um padrão para codificar dados em texto usando pares chave/valor.

✅ Se você nunca ouviu falar de JSON antes, pode aprender mais sobre ele na [documentação do JSON.org](https://www.json.org/).

Siga a etapa relevante abaixo para enviar telemetria do seu dispositivo para o broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Computador de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-telemetry.md)

### Receber telemetria do broker MQTT

Não adianta enviar telemetria se não houver nada na outra ponta para ouvi-la. A telemetria do nível de luz precisa de algo que a escute para processar os dados. Esse código 'servidor' é o tipo de código que você implantará em um serviço na nuvem como parte de uma aplicação IoT maior, mas aqui você executará esse código localmente no seu computador (ou no seu Pi, se estiver programando diretamente nele). O código do servidor consiste em um aplicativo Python que escuta mensagens de telemetria via MQTT com níveis de luz. Mais adiante nesta lição, você fará com que ele responda com uma mensagem de comando com instruções para ligar ou desligar o LED.

✅ Faça uma pesquisa: O que acontece com as mensagens MQTT se não houver nenhum ouvinte?

#### Instale Python e VS Code

Se você não tiver Python e VS Code instalados localmente, precisará instalá-los para programar o servidor. Se estiver usando um dispositivo IoT virtual ou trabalhando no seu Raspberry Pi, pode pular esta etapa, pois já deve ter isso instalado e configurado.

##### Tarefa - instalar Python e VS Code

Instale Python e VS Code.

1. Instale o Python. Consulte a [página de downloads do Python](https://www.python.org/downloads/) para instruções sobre como instalar a versão mais recente do Python.

2. Instale o Visual Studio Code (VS Code). Este será o editor que você usará para escrever o código do dispositivo virtual em Python. Consulte a [documentação do VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) para instruções sobre como instalar o VS Code.
💁 Você está livre para usar qualquer IDE ou editor Python para essas lições, caso tenha uma ferramenta preferida, mas as lições fornecerão instruções baseadas no uso do VS Code.
1. Instale a extensão Pylance do VS Code. Esta é uma extensão para o VS Code que oferece suporte à linguagem Python. Consulte a [documentação da extensão Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para instruções sobre como instalar esta extensão no VS Code.

#### Configure um ambiente virtual Python

Uma das características mais poderosas do Python é a capacidade de instalar [pacotes pip](https://pypi.org) - pacotes de código escritos por outras pessoas e publicados na Internet. Você pode instalar um pacote pip no seu computador com um único comando e, em seguida, usar esse pacote no seu código. Você usará o pip para instalar um pacote que permite comunicação via MQTT.

Por padrão, quando você instala um pacote, ele fica disponível em todo o seu computador, o que pode levar a problemas com versões de pacotes - como uma aplicação depender de uma versão de um pacote que pode quebrar ao instalar uma nova versão para outra aplicação. Para contornar esse problema, você pode usar um [ambiente virtual Python](https://docs.python.org/3/library/venv.html), essencialmente uma cópia do Python em uma pasta dedicada, e quando você instala pacotes pip, eles são instalados apenas nessa pasta.

##### Tarefa - configurar um ambiente virtual Python

Configure um ambiente virtual Python e instale os pacotes pip para MQTT.

1. No seu terminal ou linha de comando, execute o seguinte em um local de sua escolha para criar e navegar até um novo diretório:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Agora execute o seguinte para criar um ambiente virtual na pasta `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Você precisa chamar explicitamente `python3` para criar o ambiente virtual, caso tenha o Python 2 instalado além do Python 3 (a versão mais recente). Se você tiver o Python 2 instalado, chamar `python` usará o Python 2 em vez do Python 3.

1. Ative o ambiente virtual:

    * No Windows:
        * Se você estiver usando o Prompt de Comando ou o Prompt de Comando através do Windows Terminal, execute:

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

    > 💁 Esses comandos devem ser executados no mesmo local onde você executou o comando para criar o ambiente virtual. Você nunca precisará navegar para dentro da pasta `.venv`; sempre deve executar o comando de ativação e quaisquer comandos para instalar pacotes ou executar código a partir da pasta onde estava ao criar o ambiente virtual.

1. Uma vez que o ambiente virtual tenha sido ativado, o comando padrão `python` executará a versão do Python usada para criar o ambiente virtual. Execute o seguinte para verificar a versão:

    ```sh
    python --version
    ```

    A saída será semelhante ao seguinte:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Sua versão do Python pode ser diferente - desde que seja a versão 3.6 ou superior, está tudo certo. Caso contrário, exclua esta pasta, instale uma versão mais recente do Python e tente novamente.

1. Execute os seguintes comandos para instalar o pacote pip para [Paho-MQTT](https://pypi.org/project/paho-mqtt/), uma biblioteca popular de MQTT.

    ```sh
    pip install paho-mqtt
    ```

    Este pacote pip será instalado apenas no ambiente virtual e não estará disponível fora dele.

#### Escreva o código do servidor

Agora o código do servidor pode ser escrito em Python.

##### Tarefa - escrever o código do servidor

Escreva o código do servidor.

1. No seu terminal ou linha de comando, execute o seguinte dentro do ambiente virtual para criar um arquivo Python chamado `app.py`:

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

1. Quando o VS Code for iniciado, ele ativará o ambiente virtual Python. Isso será indicado na barra de status inferior:

    ![VS Code mostrando o ambiente virtual selecionado](../../../../../translated_images/pt-BR/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Se o terminal do VS Code já estiver em execução quando o VS Code for iniciado, ele não terá o ambiente virtual ativado. A maneira mais fácil de resolver isso é encerrar o terminal usando o botão **Encerrar a instância ativa do terminal**:

    ![Botão para encerrar a instância ativa do terminal no VS Code](../../../../../translated_images/pt-BR/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Inicie um novo terminal no VS Code selecionando *Terminal -> Novo Terminal*, ou pressionando `` CTRL+` ``. O novo terminal carregará o ambiente virtual, com a chamada para ativá-lo aparecendo no terminal. O nome do ambiente virtual (`.venv`) também estará no prompt:

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

    Substitua `<ID>` na linha 6 pelo ID único que você usou ao criar o código do dispositivo.

    ⚠️ Este **deve** ser o mesmo ID que você usou no seu dispositivo, caso contrário o código do servidor não se inscreverá ou publicará no tópico correto.

    Este código cria um cliente MQTT com um nome único e se conecta ao broker *test.mosquitto.org*. Em seguida, inicia um loop de processamento que é executado em uma thread de segundo plano, ouvindo mensagens em quaisquer tópicos inscritos.

    O cliente então se inscreve para mensagens no tópico de telemetria e define uma função que é chamada quando uma mensagem é recebida. Quando uma mensagem de telemetria é recebida, a função `handle_telemetry` é chamada, imprimindo a mensagem recebida no console.

    Finalmente, um loop infinito mantém a aplicação em execução. O cliente MQTT está ouvindo mensagens em uma thread de segundo plano e funciona enquanto a aplicação principal estiver em execução.

1. No terminal do VS Code, execute o seguinte para rodar seu aplicativo Python:

    ```sh
    python app.py
    ```

    O aplicativo começará a ouvir mensagens do dispositivo IoT.

1. Certifique-se de que seu dispositivo está em execução e enviando mensagens de telemetria. Ajuste os níveis de luz detectados pelo seu dispositivo físico ou virtual. As mensagens recebidas serão impressas no terminal.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    O arquivo app.py no ambiente virtual nightlight precisa estar em execução para que o arquivo app.py no ambiente virtual nightlight-server receba as mensagens enviadas.

> 💁 Você pode encontrar este código na pasta [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Com que frequência a telemetria deve ser enviada?

Uma consideração importante sobre telemetria é com que frequência medir e enviar os dados. A resposta é - depende. Se você medir com frequência, pode responder mais rapidamente às mudanças nas medições, mas usará mais energia, mais largura de banda, gerará mais dados e precisará de mais recursos na nuvem para processá-los. Você precisa medir com frequência suficiente, mas não excessivamente.

Para um termostato, medir a cada poucos minutos provavelmente é mais do que suficiente, já que as temperaturas não mudam com tanta frequência. Se você medir apenas uma vez por dia, pode acabar aquecendo sua casa para temperaturas noturnas no meio de um dia ensolarado, enquanto se medir a cada segundo terá milhares de medições de temperatura desnecessariamente duplicadas, o que consumirá a velocidade e largura de banda da Internet dos usuários (um problema para pessoas com planos de largura de banda limitada), usará mais energia, o que pode ser um problema para dispositivos alimentados por bateria, como sensores remotos, e aumentará o custo dos recursos de computação na nuvem para processá-los e armazená-los.

Se você estiver monitorando dados de uma máquina em uma fábrica que, se falhar, pode causar danos catastróficos e milhões de dólares em perda de receita, medir várias vezes por segundo pode ser necessário. É melhor desperdiçar largura de banda do que perder telemetria que indica que uma máquina precisa ser parada e consertada antes de quebrar.

> 💁 Nessa situação, você pode considerar ter um dispositivo de borda para processar a telemetria primeiro e reduzir a dependência da Internet.

### Perda de conectividade

Conexões de Internet podem ser instáveis, com interrupções comuns. O que um dispositivo IoT deve fazer nessas circunstâncias - deve perder os dados ou armazená-los até que a conectividade seja restaurada? Novamente, a resposta é depende.

Para um termostato, os dados podem provavelmente ser descartados assim que uma nova medição de temperatura for feita. O sistema de aquecimento não se importa que há 20 minutos estava 20,5°C se a temperatura agora é 19°C; é a temperatura atual que determina se o aquecimento deve estar ligado ou desligado.

Para máquinas, você pode querer manter os dados, especialmente se forem usados para buscar tendências. Existem modelos de aprendizado de máquina que podem detectar anomalias em fluxos de dados analisando dados de um período definido de tempo (como a última hora) e identificando dados anômalos. Isso é frequentemente usado para manutenção preditiva, buscando indicações de que algo pode quebrar em breve para que você possa reparar ou substituir antes que isso aconteça. Você pode querer que cada bit de telemetria de uma máquina seja enviado para que possa ser processado para detecção de anomalias, então, uma vez que o dispositivo IoT possa se reconectar, ele enviará toda a telemetria gerada durante a interrupção da Internet.

Os designers de dispositivos IoT também devem considerar se o dispositivo IoT pode ser usado durante uma interrupção da Internet ou perda de sinal causada pela localização. Um termostato inteligente deve ser capaz de tomar algumas decisões limitadas para controlar o aquecimento se não puder enviar telemetria para a nuvem devido a uma interrupção.

[![Este Ferrari ficou inutilizado porque alguém tentou atualizá-lo em um local subterrâneo sem sinal de celular](../../../../../translated_images/pt-BR/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Para o MQTT lidar com uma perda de conectividade, o código do dispositivo e do servidor será responsável por garantir a entrega das mensagens, se necessário, por exemplo, exigindo que todas as mensagens enviadas sejam respondidas por mensagens adicionais em um tópico de resposta e, caso contrário, sejam enfileiradas manualmente para serem reproduzidas posteriormente.

## Comandos

Comandos são mensagens enviadas pela nuvem para um dispositivo, instruindo-o a fazer algo. Na maioria das vezes, isso envolve fornecer algum tipo de saída por meio de um atuador, mas pode ser uma instrução para o próprio dispositivo, como reiniciar ou coletar telemetria extra e retorná-la como resposta ao comando.

![Um termostato conectado à Internet recebendo um comando para ligar o aquecimento](../../../../../translated_images/pt-BR/commands.d6c06bbbb3a02cce.webp)

Um termostato pode receber um comando da nuvem para ligar o aquecimento. Com base nos dados de telemetria de todos os sensores, se o serviço na nuvem decidiu que o aquecimento deve estar ligado, ele envia o comando relevante.

### Enviar comandos para o broker MQTT

O próximo passo para nosso nightlight controlado pela Internet é que o código do servidor envie um comando de volta para o dispositivo IoT para controlar a luz com base nos níveis de luz que ele detecta.

1. Abra o código do servidor no VS Code.

1. Adicione a seguinte linha após a declaração do `client_telemetry_topic` para definir qual tópico enviar comandos:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Adicione o seguinte código ao final da função `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Isso envia uma mensagem JSON para o tópico de comando com o valor de `led_on` definido como verdadeiro ou falso, dependendo se a luz é menor que 300 ou não. Se a luz for menor que 300, verdadeiro é enviado para instruir o dispositivo a ligar o LED.

1. Execute o código como antes.

1. Ajuste os níveis de luz detectados pelo seu dispositivo físico ou virtual. As mensagens recebidas e os comandos enviados serão exibidos no terminal:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 A telemetria e os comandos estão sendo enviados em um único tópico cada. Isso significa que a telemetria de vários dispositivos aparecerá no mesmo tópico de telemetria, e os comandos para vários dispositivos aparecerão no mesmo tópico de comandos. Se você quiser enviar um comando para um dispositivo específico, pode usar vários tópicos, nomeados com um ID único do dispositivo, como `/commands/device1`, `/commands/device2`. Dessa forma, um dispositivo pode ouvir mensagens destinadas apenas para ele.

> 💁 Você pode encontrar este código na pasta [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Lidar com comandos no dispositivo IoT

Agora que os comandos estão sendo enviados pelo servidor, você pode adicionar código ao dispositivo IoT para lidar com eles e controlar o LED.

Siga o passo relevante abaixo para ouvir comandos do broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Computador de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-commands.md)

Uma vez que este código esteja escrito e em execução, experimente alterar os níveis de luz. Observe a saída do servidor e do dispositivo, e veja o LED enquanto você altera os níveis de luz.

### Perda de conectividade

O que um serviço na nuvem deve fazer se precisar enviar um comando para um dispositivo IoT que está offline? Novamente, a resposta é depende.

Se o último comando substitui um anterior, então os anteriores podem provavelmente ser ignorados. Se um serviço na nuvem enviar um comando para ligar o aquecimento e depois enviar um comando para desligá-lo, o comando de ligar pode ser ignorado e não reenviado.

Se os comandos precisarem ser processados em sequência, como mover um braço robótico para cima e depois fechar um agarrador, então eles precisam ser enviados na ordem correta assim que a conectividade for restaurada.

✅ Como o código do dispositivo ou do servidor poderia garantir que os comandos sejam sempre enviados e processados na ordem correta via MQTT, se necessário?

---

## 🚀 Desafio

O desafio nas últimas três lições foi listar o maior número possível de dispositivos IoT que você tem em casa, na escola ou no trabalho e decidir se eles são construídos em torno de microcontroladores ou computadores de placa única, ou até mesmo uma mistura de ambos, e pensar sobre quais sensores e atuadores eles estão usando.
Para esses dispositivos, pense nas mensagens que eles podem estar enviando ou recebendo. Que telemetria eles enviam? Que mensagens ou comandos eles podem receber? Você acha que eles são seguros?

## Questionário pós-aula

[Questionário pós-aula](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Revisão e Autoestudo

Leia mais sobre MQTT na [página da Wikipedia sobre MQTT](https://wikipedia.org/wiki/MQTT).

Experimente executar um broker MQTT você mesmo usando o [Mosquitto](https://www.mosquitto.org) e conecte-se a ele a partir do seu dispositivo IoT e do código do servidor.

> 💁 Dica - por padrão, o Mosquitto não permite conexões anônimas (ou seja, conectar sem um nome de usuário e senha) e não permite conexões de fora do computador onde está sendo executado.  
> Você pode corrigir isso com um [arquivo de configuração `mosquitto.conf`](https://www.mosquitto.org/man/mosquitto-conf-5.html) com o seguinte:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Tarefa

[Compare e contraste o MQTT com outros protocolos de comunicação](assignment.md)

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.