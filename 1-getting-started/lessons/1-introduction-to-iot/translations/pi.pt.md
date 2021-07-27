# Raspberry Pi

O [Raspberry Pi](https://raspberrypi.org) é um computador de placa única. Você pode adicionar sensores e atuadores usando uma ampla variedade de dispositivos e ecossistemas, e para essas lições, usando um ecossistema de hardware chamado [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Você codificará seu Pi e acessará os sensores Grove usando Python.

![Um Raspberry Pi 4](../../../../images/raspberry-pi-4.jpg)

## Configuração

Se você estiver usando um Raspberry Pi como seu hardware IoT, você tem duas opções - você pode trabalhar em todas essas lições e codificar diretamente no Pi ou pode se conectar remotamente a um Pi 'headless' e codificar de seu computador.

Antes de começar, você também precisa conectar o Grove Base Hat ao seu Pi.

### Tarefa - configuração

Instale o Grove Base Hat no seu Pi e configure o Pi

1. Conecte o Grove Base Hat ao seu Pi. O soquete no Grove Base Hat se encaixa em todos os pinos de GPIO no Pi, deslizando para baixo sobre os pinos para que se assente firmemente na base. Ele fica sobre o Pi, cobrindo-o.

    ![Ajustando o Grove Hat](../../../../images/pi-grove-hat-fitting.gif)

1. Decida como você deseja programar seu Pi e vá para a seção relevante abaixo:

    * [Trabalhe diretamente no seu Pi](#trabalhe-diretamente-no-seu-pi)
    * [Acesso remoto para codificar o Pi](#acesso-remoto-para-codificar-o-pi)

### Trabalhe diretamente no seu Pi

Se você quiser trabalhar diretamente no seu Pi, pode usar a versão desktop do Raspberry Pi OS e instalar todas as ferramentas de que precisa.

#### Tarefa - trabalhe diretamente no seu Pi

Configure seu Pi para desenvolvimento.

1. Siga as instruções no [guia de configuração do Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) para configurar seu Pi, conecte-o a um teclado/mouse/monitor, conecte-o à sua rede WiFi ou ethernet e atualize o software. O sistema operacional que você deseja instalar é o **Raspberry Pi OS (32 bits)**, ele é marcado como o sistema operacional recomendado ao usar o Raspberry Pi Imager para criar a imagem do seu cartão SD.

Para programar o Pi usando os sensores e atuadores Grove, você precisará instalar um editor para permitir que você escreva o código do dispositivo e várias bibliotecas e ferramentas que interagem com o hardware Grove.

1. Assim que seu Pi for reiniciado, inicie o Terminal clicando no ícone **Terminal** na barra de menu superior ou escolha *Menu -> Acessórios -> Terminal*

1. Execute o seguinte comando para garantir que o sistema operacional e o software instalado estejam atualizados:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Execute o seguinte comando para instalar todas as bibliotecas necessárias para o hardware Grove:

    ```sh
    curl -sL https://github.com/Seeed-Studio/grove.py/raw/master/install.sh | sudo bash -s -
    ```

    Um dos recursos poderosos do Python é a capacidade de instalar [pacotes pip](https://pypi.org) - são pacotes de código escritos por outras pessoas e publicados na Internet. Você pode instalar um pacote pip em seu computador com um comando e, em seguida, usar esse pacote em seu código. Este script de instalação do Grove instalará os pacotes pip que você usará para trabalhar com o hardware Grove a partir do Python.

1. Reinicialize o Pi usando o menu ou executando o seguinte comando no Terminal:

    ```sh
    sudo reboot
    ```

1. Após a reinicialização do Pi, reinicie o Terminal e execute o seguinte comando para instalar o [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - este é o editor que você usará para escrever o código do seu dispositivo em Python.

    ```sh
    sudo apt install code
    ```

    Depois de instalado, o VS Code estará disponível no menu superior.

    > 💁 Você está livre para usar qualquer IDE de Python ou editor para essas lições se tiver uma ferramenta preferida, mas as lições darão instruções baseadas no uso do VS Code.

1. Instale o Pylance. Esta é uma extensão para VS Code que fornece suporte à linguagem Python. Consulte a [documentação da extensão Pylance](https://marketplace.visualstudio.com/items?itemName=ms-python.vscode-pylance&WT.mc_id=academic-17441-jabenn) para obter instruções sobre como instalar esta extensão no VS Code.

### Acesso remoto para codificar o Pi

Em vez de codificar diretamente no Pi, ele pode rodar 'headless', quando não está conectado a um teclado/mouse/monitor, e assim configurar e codificar nele a partir do seu computador, usando o Visual Studio Code.

#### Configure o Pi OS

Para codificar remotamente, o Pi OS precisa ser instalado em um cartão SD.

##### Tarefa - configurar o Pi OS

Configure o Pi OS headless.

1. Baixe o **Raspberry Pi Imager** da [página do software Raspberry Pi OS](https://www.raspberrypi.org/software/) e instale-o

1. Insira um cartão SD em seu computador, usando um adaptador, se necessário

1. Inicie o Raspberry Pi Imager

1. No Raspberry Pi Imager, selecione o botão **CHOOSE OS** e, em seguida, selecione *Raspberry Pi OS (Other)*, seguido por *Raspberry Pi OS Lite (32 bits)*

    ![O Raspberry Pi Imager com o Raspberry Pi OS Lite selecionado](../../../../images/raspberry-pi-imager.png)

    > 💁 Raspberry Pi OS Lite é uma versão do Raspberry Pi OS que não possui a UI para desktop ou ferramentas baseadas em UI. Eles não são necessários para um Pi headless e tornam a instalação menor e o tempo de inicialização mais rápido.

1. Selecione o botão **CHOOSE STORAGE** e, em seguida, selecione seu cartão SD

1. Inicie as **Advanced Options** pressionando `Ctrl+Shift+X`. Essas opções permitem alguma pré-configuração do sistema operacional do Raspberry Pi antes que sua imagem seja criada no cartão SD.

    1. Marque a caixa de seleção **Enable SSH** e defina uma senha para o usuário `pi`. Esta é a senha que você usará para fazer login no Pi mais tarde.

    1. Se você está planejando se conectar ao Pi por WiFi, marque a caixa de seleção **Configure WiFi** e insira o SSID e a senha do seu WiFi, bem como selecione o país do seu WiFi. Você não precisa fazer isso se for usar um cabo Ethernet. Certifique-se de que a rede à qual você se conecta é a mesma em que seu computador está.

    1. Marque a caixa de seleção **Set locale settings** e defina seu país e fuso horário

    1. Selecione o botão **SAVE**

1. Selecione o botão **WRITE** para gravar o sistema operacional no cartão SD. Se estiver usando o macOS, será solicitado que você insira sua senha, pois a ferramenta subjacente que grava imagens de disco precisa de acesso privilegiado.

O sistema operacional será gravado no cartão SD e, uma vez concluído, o cartão será ejetado pelo sistema operacional e você será notificado. Remova o cartão SD do seu computador, insira-o no Pi e ligue o Pi.

#### Conecte-se ao Pi

A próxima etapa é acessar remotamente o Pi. Você pode fazer isso usando `ssh`, que está disponível no macOS, Linux e versões recentes do Windows.

##### Tarefa - conectar ao Pi

Acesse remotamente o Pi.

1. Inicie um Terminal ou Prompt de Comando e digite o seguinte comando para se conectar ao Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Se você estiver no Windows usando uma versão mais antiga que não possui o `ssh` instalado, você pode usar o OpenSSH. Você pode encontrar as instruções de instalação na [documentação de instalação do OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Isso deve se conectar ao seu Pi e pedir a senha.

    Ser capaz de encontrar computadores em sua rede usando `<hostname>.local` é uma adição bastante recente ao Linux e Windows. Se você estiver usando Linux ou Windows e receber algum erro sobre o nome do host não ser encontrado, será necessário instalar software adicional para habilitar o ZeroConf networking (também conhecido pela Apple como Bonjour):

    1. Se você estiver usando Linux, instale o Avahi usando o seguinte comando:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Se você estiver usando o Windows, a maneira mais fácil de ativar o ZeroConf é instalar [Bonjour Print Services para Windows](http://support.apple.com/kb/DL999). Você também pode instalar o [iTunes para Windows](https://www.apple.com/itunes/download/) para obter uma versão mais recente do utilitário (que não está disponível standalone).

    > 💁 Se você não conseguir se conectar usando `raspberrypi.local`, poderá usar o endereço IP do seu Pi. Consulte a [documentação do endereço IP do Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) para obter instruções sobre várias maneiras de obter o endereço IP.

1. Digite a senha que você definiu nas opções avançadas do Raspberry Pi Imager

#### Configure o software no Pi

Assim que estiver conectado ao Pi, você precisa garantir que o sistema operacional esteja atualizado e instalar várias bibliotecas e ferramentas que interagem com o hardware Grove.

##### Tarefa - configurar software no Pi

Configure o software Pi instalado e instale as bibliotecas Grove.

1. Na sessão `ssh`, execute o seguinte comando para atualizar e reinicie o Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    O Pi será atualizado e reiniciado. A sessão `ssh` terminará quando o Pi for reiniciado, então deixe-o por cerca de 30 segundos e reconecte.

1. A partir da sessão `ssh` reconectada, execute o seguinte comando para instalar todas as bibliotecas necessárias para o hardware Grove:

    ```sh
    curl -sL https://github.com/Seeed-Studio/grove.py/raw/master/install.sh | sudo bash -s -
    ```

    Um dos recursos poderosos do Python é a capacidade de instalar [pacotes pip](https://pypi.org) - são pacotes de código escritos por outras pessoas e publicados na Internet. Você pode instalar um pacote pip em seu computador com um comando e, em seguida, usar esse pacote em seu código. Este script de instalação do Grove instalará os pacotes pip que você usará para trabalhar com o hardware Grove a partir do Python.

1. Reinicialize o Pi executando o seguinte comando:

    ```sh
    sudo reboot
    ```

    A sessão `ssh` terminará quando o Pi for reiniciado. Não há necessidade de reconectar.

#### Configure o VS Code para acesso remoto

Depois que o Pi estiver configurado, você pode se conectar a ele usando o Visual Studio Code (VS Code) a partir do seu computador - este é um editor de texto para desenvolvedores gratuito que você usará para escrever o código do seu dispositivo em Python.

##### Tarefa - configurar o VS Code para acesso remoto

Instale o software necessário e conecte-se remotamente ao seu Pi.

1. Instale o VS Code em seu computador seguindo a [documentação do VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

1. Siga as instruções em [VS Code Remote Development using SSH documentation](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) para instalar os componentes necessários

1. Seguindo as mesmas instruções, conecte o VS Code ao Pi

1. Depois de conectado, siga as instruções em [gerenciando extensões](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) para instalar a [extensão Pylance](https://marketplace.visualstudio.com/items?itemName=ms-python.vscode-pylance&WT.mc_id=academic-17441-jabenn) remotamente no Pi

## Hello World

É tradicional, ao começar com uma nova linguagem de programação ou tecnologia, criar um aplicativo 'Hello World' - um pequeno aplicativo que produz algo como o texto `"Hello World"` para mostrar que todas as ferramentas estão configuradas corretamente.

O aplicativo Hello World para o Pi garantirá que você tenha o Python e o Visual Studio Code instalados corretamente.

Este aplicativo estará em uma pasta chamada `nightlight` e será reutilizado com código diferente em partes posteriores desta tarefa para construir o aplicativo nightlight.

### Tarefa - hello world

Crie o aplicativo Hello World.

1. Inicie o VS Code, diretamente no Pi ou em seu computador e conectado ao Pi usando a extensão Remote SSH

1. Inicie o Terminal do VS Code selecionando *Terminal -> Novo Terminal* ou pressionando `` CTRL+` ``. Ele será aberto no diretório inicial dos usuários `pi`.

1. Execute os seguintes comandos para criar um diretório para o seu código e crie um arquivo Python chamado `app.py` dentro desse diretório:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Abra esta pasta no VS Code selecionando *File -> Open...* e selecionando a pasta *nightlight* e, em seguida, selecione **OK**

    ![A caixa de diálogo de abertura do VS Code mostrando a pasta nightlight](../../../../images/vscode-open-nightlight-remote.png)

1. Abra o arquivo `app.py` no VS Code explorer e adicione o seguinte código:

    ```python
    print('Hello World!')
    ```

    A função `print` imprime tudo o que é passado para ela no console.

1. No Terminal do VS Code, execute o seguinte para executar seu aplicativo Python:

    ```sh
    python3 app.py
    ```

    > 💁 Você precisa chamar explicitamente `python3` para executar este código apenas no caso de ter o Python 2 instalado além do Python 3 (a versão mais recente). Se você tiver Python2 instalado, chamar `python` usará Python 2 em vez de Python 3

    A seguinte saída aparecerá no terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Você pode encontrar este código na pasta [code/pi](code/pi).

😀 Seu programa 'Hello World' foi um sucesso!