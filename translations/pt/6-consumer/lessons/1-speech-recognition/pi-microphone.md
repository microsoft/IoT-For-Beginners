<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-25T22:49:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "pt"
}
-->
# Configurar o microfone e os altifalantes - Raspberry Pi

Nesta parte da lição, irá adicionar um microfone e altifalantes ao seu Raspberry Pi.

## Hardware

O Raspberry Pi necessita de um microfone.

O Pi não tem um microfone integrado, por isso será necessário adicionar um microfone externo. Existem várias formas de fazer isto:

* Microfone USB  
* Auscultadores USB  
* Altifalante com microfone integrado USB  
* Adaptador de áudio USB e microfone com ficha de 3,5mm  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)  

> 💁 Nem todos os microfones Bluetooth são suportados no Raspberry Pi, por isso, se tiver um microfone ou auscultadores Bluetooth, pode ter problemas ao emparelhar ou capturar áudio.

Os Raspberry Pis vêm com uma entrada de auscultadores de 3,5mm. Pode utilizá-la para ligar auscultadores, um headset ou um altifalante. Também pode adicionar altifalantes utilizando:

* Áudio HDMI através de um monitor ou TV  
* Altifalantes USB  
* Auscultadores USB  
* Altifalante com microfone integrado USB  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) com um altifalante ligado, quer à entrada de 3,5mm ou à porta JST  

## Ligar e configurar o microfone e os altifalantes

O microfone e os altifalantes precisam de ser ligados e configurados.

### Tarefa - ligar e configurar o microfone

1. Ligue o microfone utilizando o método apropriado. Por exemplo, ligue-o a uma das portas USB.

1. Se estiver a utilizar o ReSpeaker 2-Mics Pi HAT, pode remover o Grove base hat e encaixar o ReSpeaker hat no seu lugar.

    ![Um Raspberry Pi com um ReSpeaker hat](../../../../../translated_images/pt/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Irá precisar de um botão Grove mais tarde nesta lição, mas um está integrado neste hat, por isso o Grove base hat não é necessário.

    Depois de encaixar o hat, será necessário instalar alguns drivers. Consulte as [instruções de introdução da Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) para instruções de instalação dos drivers.

    > ⚠️ As instruções utilizam `git` para clonar um repositório. Se não tiver o `git` instalado no seu Pi, pode instalá-lo executando o seguinte comando:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Execute o seguinte comando no Terminal, quer no Pi ou ligado através do VS Code e uma sessão remota SSH, para ver informações sobre o microfone ligado:

    ```sh
    arecord -l
    ```

    Irá ver uma lista de microfones ligados. Será algo como o seguinte:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Assumindo que tem apenas um microfone, deverá ver apenas uma entrada. A configuração de microfones pode ser complicada no Linux, por isso é mais fácil utilizar apenas um microfone e desligar quaisquer outros.

    Anote o número da placa, pois irá precisar dele mais tarde. No exemplo acima, o número da placa é 1.

### Tarefa - ligar e configurar os altifalantes

1. Ligue os altifalantes utilizando o método apropriado.

1. Execute o seguinte comando no Terminal, quer no Pi ou ligado através do VS Code e uma sessão remota SSH, para ver informações sobre os altifalantes ligados:

    ```sh
    aplay -l
    ```

    Irá ver uma lista de altifalantes ligados. Será algo como o seguinte:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Irá sempre ver `card 0: Headphones`, pois esta é a entrada de auscultadores integrada. Se tiver adicionado altifalantes adicionais, como um altifalante USB, verá esta entrada listada também.

1. Se estiver a utilizar um altifalante adicional, e não um altifalante ou auscultadores ligados à entrada de auscultadores integrada, será necessário configurá-lo como padrão. Para isso, execute o seguinte comando:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Isto irá abrir um ficheiro de configuração no `nano`, um editor de texto baseado no terminal. Desça utilizando as teclas de seta no teclado até encontrar a seguinte linha:

    ```output
    defaults.pcm.card 0
    ```

    Altere o valor de `0` para o número da placa que deseja utilizar da lista que apareceu na chamada ao `aplay -l`. Por exemplo, no exemplo acima há uma segunda placa de som chamada `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, utilizando a placa 1. Para utilizar esta, eu atualizaria a linha para:

    ```output
    defaults.pcm.card 1
    ```

    Defina este valor para o número da placa apropriado. Pode navegar até ao número utilizando as teclas de seta no teclado, depois apagar e digitar o novo número como faria normalmente ao editar ficheiros de texto.

1. Guarde as alterações e feche o ficheiro pressionando `Ctrl+x`. Pressione `y` para guardar o ficheiro e depois `return` para selecionar o nome do ficheiro.

### Tarefa - testar o microfone e os altifalantes

1. Execute o seguinte comando para gravar 5 segundos de áudio através do microfone:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Enquanto este comando estiver a ser executado, faça algum ruído no microfone, como falar, cantar, fazer beatbox, tocar um instrumento ou o que preferir.

1. Após 5 segundos, a gravação irá parar. Execute o seguinte comando para reproduzir o áudio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Irá ouvir o áudio a ser reproduzido através dos altifalantes. Ajuste o volume de saída no altifalante conforme necessário.

1. Se precisar de ajustar o volume da entrada de microfone integrada ou ajustar o ganho do microfone, pode utilizar a ferramenta `alsamixer`. Pode ler mais sobre esta ferramenta na [página man do alsamixer no Linux](https://linux.die.net/man/1/alsamixer).

1. Se obtiver erros ao reproduzir o áudio, verifique a placa que definiu como `defaults.pcm.card` no ficheiro `alsa.conf`.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.