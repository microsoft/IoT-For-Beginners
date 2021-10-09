# Computador de placa única virtual

Em vez de comprar um dispositivo IoT, junto com sensores e atuadores, você pode usar seu computador para simular o hardware IoT. O [projeto CounterFit](https://github.com/CounterFit-IoT/CounterFit) permite que você execute um aplicativo localmente que simula hardware IoT, como sensores e atuadores, e acesse os sensores e atuadores a partir do código Python local que está escrito da mesma forma que o código que você escreveria em um Raspberry Pi usando um hardware físico.

## Configuração

Para usar o CounterFit, você precisará instalar alguns softwares gratuitos em seu computador.

### Tarefa

Instale o software necessário.

1. Instale o Python. Consulte a [página de downloads do Python](https://www.python.org/downloads/) para obter instruções sobre como instalar a versão mais recente do Python.

1. Instale o Visual Studio Code (VS Code). Este é o editor que você usará para escrever o código do seu dispositivo virtual em Python. Consulte a [documentação do VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) para obter instruções sobre como instalar o VS Code.

    > 💁 Você está livre para usar qualquer IDE ou editor de código Python para essas lições se tiver uma ferramenta preferida, mas as lições darão instruções baseadas no uso do VS Code.

1. Instale a extensão Pylance do VS Code. Esta é uma extensão para VS Code que fornece suporte à linguagem Python. Consulte a [documentação da extensão Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para obter instruções sobre como instalar esta extensão no VS Code.

As instruções para instalar e configurar o aplicativo CounterFit serão fornecidas no momento relevante nas instruções de atribuição, uma vez que é instalado por projeto.

## Hello world

É tradicional, ao começar com uma nova linguagem de programação ou tecnologia, criar um aplicativo 'Hello World' - um pequeno aplicativo que produz algo como o texto `"Hello World"` para mostrar que todas as ferramentas estão configuradas corretamente.

O aplicativo Hello World para o hardware IoT virtual garantirá que você tenha o Python e o Visual Studio Code instalados corretamente. Ele também se conectará ao CounterFit para os sensores e atuadores IoT virtuais. Ele não usará nenhum hardware, apenas se conectará para provar que tudo está funcionando.

Este aplicativo estará em uma pasta chamada `nightlight` e será reutilizado com código diferente em partes posteriores desta atribuição para construir o aplicativo nightlight.

### Configure um ambiente virtual Python

Um dos recursos poderosos do Python é a capacidade de instalar [pacotes pip](https://pypi.org) - são pacotes de código escritos por outras pessoas e publicados na Internet. Você pode instalar um pacote pip em seu computador com um comando e, em seguida, usar esse pacote em seu código. Você usará o pip para instalar um pacote para falar com o CounterFit.

Por padrão, quando você instala um pacote, ele está disponível em qualquer lugar do seu computador, e isso pode causar problemas com as versões do pacote - como um aplicativo dependendo de uma versão de um pacote que quebra quando você instala uma nova versão para um aplicativo diferente. Para contornar esse problema, você pode usar um [ambiente virtual Python](https://docs.python.org/3/library/venv.html), essencialmente uma cópia do Python em uma pasta dedicada, e ao instalar o pip pacotes são instalados apenas nessa pasta.

#### Tarefa - configurar um ambiente virtual Python

Configure um ambiente virtual Python e instale os pacotes pip para CounterFit.

1. Em seu terminal ou linha de comando, execute o seguinte em um local de sua escolha para criar e navegar para um novo diretório:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Agora execute o seguinte para criar um ambiente virtual na pasta `.venv`

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Você precisa chamar explicitamente `python3` para criar o ambiente virtual apenas no caso de ter o Python 2 instalado além do Python 3 (a versão mais recente). Se você tiver Python2 instalado, chamar `python` usará Python 2 em vez de Python 3

1. Ative o ambiente virtual:

    * No Windows, execute:

        ```cmd
        .venv \ Scripts \ activate.bat
        ```

    * No macOS ou Linux, execute:

        ```cmd
        source ./.venv/bin/activate
        ```

1. Uma vez que o ambiente virtual foi ativado, o comando padrão `python` irá executar a versão do Python que foi usada para criar o ambiente virtual. Execute o seguinte para obter a versão:

    ```sh
    python --version
    ```

    A saída deve conter o seguinte:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Sua versão do Python pode ser diferente - contanto que seja a versão 3.6 ou superior, você está bem. Caso contrário, exclua esta pasta, instale uma versão mais recente do Python e tente novamente.

1. Execute os seguintes comandos para instalar os pacotes pip para CounterFit. Esses pacotes incluem o aplicativo CounterFit principal, bem como shims para hardware Grove. Esses shims permitem que você escreva código como se estivesse programando usando sensores e atuadores físicos do ecossistema Grove, mas conectado a dispositivos IoT virtuais.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Esses pacotes pip só serão instalados no ambiente virtual e não estarão disponíveis fora dele.

### Escreva o código

Assim que o ambiente virtual Python estiver pronto, você pode escrever o código para o aplicativo 'Hello World'

#### Tarefa - escreva o código

Crie um aplicativo Python para imprimir `" Hello World "` no console.

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

    > 💁 Se o seu terminal retornar `command not found` no macOS, significa que o VS Code não foi adicionado ao seu PATH. Você pode adicionar o VS Code ao seu PATH seguindo as instruções na seção [Iniciando a partir da linha de comando da documentação do código do VS](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) e execute o comando depois. O VS Code é instalado em seu PATH por padrão no Windows e Linux.

1. Quando o VS Code for iniciado, ele ativará o ambiente virtual Python. O ambiente virtual selecionado aparecerá na barra de status inferior:

    ![VS Code mostrando o ambiente virtual selecionado](../../../../images/vscode-virtual-env.png)

1. Se o Terminal do VS Code já estiver em execução quando o VS Code for inicializado, ele não terá o ambiente virtual ativado nele. A coisa mais fácil a fazer é matar o terminal usando o botão **Kill the active terminal instance**:

    ![Botão Kill the active terminal instance do VS Code](../../../../images/vscode-kill-terminal.png)

    Você pode dizer se o terminal tem o ambiente virtual ativado, pois o nome do ambiente virtual será um prefixo no prompt do terminal. Por exemplo, pode ser:

    ```sh
    (.venv) ➜  nightlight
    ```

    Se você não tiver `.venv` como prefixo no prompt, o ambiente virtual não está ativo no terminal.

1. Inicie um novo Terminal do VS Code selecionando *Terminal -> Novo Terminal* ou pressionando `` CTRL+` ``. O novo terminal irá carregar o ambiente virtual, e a chamada para ativá-lo aparecerá no terminal. O prompt também terá o nome do ambiente virtual (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Abra o arquivo `app.py` no VS Code explorer e adicione o seguinte código:

    ```python
    print('Hello World!')
    ```

    A função `print` imprime no console tudo o que é passado para ela.

1. No terminal do VS Code, execute o seguinte para executar seu aplicativo Python:

    ```sh
    python app.py
    ```

    O seguinte estará na saída:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Seu programa 'Hello World' foi um sucesso!

### Conecte o 'hardware'

Como uma segunda etapa 'Hello World', você executará o aplicativo CounterFit e conectará seu código a ele. Isso é o equivalente virtual de conectar algum hardware IoT a um kit de desenvolvimento.

#### Tarefa - conecte o 'hardware'

1. A partir do terminal do VS Code, inicie o aplicativo CounterFit com o seguinte comando:

    ```sh
    counterfit
    ```

    O aplicativo começará a funcionar e abrir no seu navegador da web:

    ![O aplicativo Counter Fit em execução em um navegador](../../../../images/counterfit-first-run.png)

    Ele será marcado como *Desconectado*, com o LED no canto superior direito apagado.

1. Adicione o seguinte código ao topo de `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Este código importa a classe `CounterFitConnection` do módulo `counterfit_connection`, que vem do pacote pip `counterfit-connection` que você instalou anteriormente. Em seguida, ele inicializa uma conexão com o aplicativo CounterFit em execução em `127.0.0.1`, que é um endereço IP que você sempre pode usar para acessar seu computador local (muitas vezes referido como *localhost*), na porta 5000.

    > 💁 Se você tiver outros aplicativos em execução na porta 5000, pode alterar isso atualizando a porta no código e executando o CounterFit usando `CounterFit --port <port_number>`, substituindo `<port_number>` pela porta que deseja usar.

1. Você precisará iniciar um novo terminal do VS Code selecionando o botão **Create a new integrated terminal**. Isso ocorre porque o aplicativo CounterFit está sendo executado no terminal atual.

    ![Botão Create a new integrated terminal do VS Code](../../../../images/vscode-new-terminal.png)

1. Neste novo terminal, execute o arquivo `app.py` como antes. O status do CounterFit mudará para **Conectado** e o LED acenderá.

    ![CounterFit mostrando como conectado](../../../../images/counterfit-connected.png)

> 💁 Você pode encontrar este código na pasta [code/virtual-device](../code/virtual-device).

😀 Sua conexão com o hardware foi um sucesso!
