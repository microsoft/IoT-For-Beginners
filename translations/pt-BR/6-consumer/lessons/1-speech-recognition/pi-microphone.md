# Configure seu microfone e alto-falantes - Raspberry Pi

Nesta parte da lição, você adicionará um microfone e alto-falantes ao seu Raspberry Pi.

## Hardware

O Raspberry Pi precisa de um microfone.

O Pi não possui um microfone embutido, então você precisará adicionar um microfone externo. Existem várias maneiras de fazer isso:

* Microfone USB  
* Headset USB  
* Speakerphone USB tudo-em-um  
* Adaptador de áudio USB e microfone com conector de 3,5mm  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)  

> 💁 Microfones Bluetooth nem sempre são compatíveis com o Raspberry Pi, então, se você tiver um microfone ou headset Bluetooth, pode enfrentar problemas ao emparelhar ou capturar áudio.

Os Raspberry Pis possuem um conector de fone de ouvido de 3,5mm. Você pode usá-lo para conectar fones de ouvido, um headset ou um alto-falante. Também é possível adicionar alto-falantes usando:

* Áudio HDMI através de um monitor ou TV  
* Alto-falantes USB  
* Headset USB  
* Speakerphone USB tudo-em-um  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) com um alto-falante conectado, seja ao conector de 3,5mm ou à porta JST  

## Conectar e configurar o microfone e os alto-falantes

O microfone e os alto-falantes precisam ser conectados e configurados.

### Tarefa - conectar e configurar o microfone

1. Conecte o microfone usando o método apropriado. Por exemplo, conecte-o a uma das portas USB.

1. Se você estiver usando o ReSpeaker 2-Mics Pi HAT, pode remover o Grove base hat e encaixar o ReSpeaker hat no lugar.

    ![Um Raspberry Pi com um ReSpeaker hat](../../../../../translated_images/pt-BR/pi-respeaker-hat.f00fabe7dd039a93.webp)

    Você precisará de um botão Grove mais tarde nesta lição, mas um já está embutido neste hat, então o Grove base hat não é necessário.

    Depois de encaixar o hat, será necessário instalar alguns drivers. Consulte as [instruções de introdução da Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) para obter instruções sobre a instalação dos drivers.

    > ⚠️ As instruções utilizam `git` para clonar um repositório. Se você não tiver o `git` instalado no seu Pi, pode instalá-lo executando o seguinte comando:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Execute o seguinte comando no Terminal, seja no Pi ou conectado via VS Code e uma sessão SSH remota, para ver informações sobre o microfone conectado:

    ```sh
    arecord -l
    ```

    Você verá uma lista de microfones conectados. Será algo como o seguinte:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Assumindo que você tenha apenas um microfone, deverá ver apenas uma entrada. A configuração de microfones pode ser complicada no Linux, então é mais fácil usar apenas um microfone e desconectar quaisquer outros.

    Anote o número da placa, pois você precisará dele mais tarde. No exemplo acima, o número da placa é 1.

### Tarefa - conectar e configurar o alto-falante

1. Conecte os alto-falantes usando o método apropriado.

1. Execute o seguinte comando no Terminal, seja no Pi ou conectado via VS Code e uma sessão SSH remota, para ver informações sobre os alto-falantes conectados:

    ```sh
    aplay -l
    ```

    Você verá uma lista de alto-falantes conectados. Será algo como o seguinte:

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

    Você sempre verá `card 0: Headphones`, pois este é o conector de fone de ouvido embutido. Se você adicionou alto-falantes adicionais, como um alto-falante USB, verá isso listado também.

1. Se você estiver usando um alto-falante adicional, e não um alto-falante ou fones de ouvido conectados ao conector de fone de ouvido embutido, será necessário configurá-lo como padrão. Para fazer isso, execute o seguinte comando:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Isso abrirá um arquivo de configuração no `nano`, um editor de texto baseado em terminal. Role para baixo usando as teclas de seta do teclado até encontrar a seguinte linha:

    ```output
    defaults.pcm.card 0
    ```

    Altere o valor de `0` para o número da placa que você deseja usar da lista retornada pela chamada ao `aplay -l`. Por exemplo, no exemplo acima há uma segunda placa de som chamada `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, usando a placa 1. Para usar esta, eu atualizaria a linha para:

    ```output
    defaults.pcm.card 1
    ```

    Defina este valor para o número da placa apropriado. Você pode navegar até o número usando as teclas de seta do teclado, depois excluir e digitar o novo número normalmente ao editar arquivos de texto.

1. Salve as alterações e feche o arquivo pressionando `Ctrl+x`. Pressione `y` para salvar o arquivo e, em seguida, `return` para selecionar o nome do arquivo.

### Tarefa - testar o microfone e o alto-falante

1. Execute o seguinte comando para gravar 5 segundos de áudio através do microfone:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Enquanto este comando estiver sendo executado, faça algum ruído no microfone, como falar, cantar, fazer beatbox, tocar um instrumento ou o que preferir.

1. Após 5 segundos, a gravação será interrompida. Execute o seguinte comando para reproduzir o áudio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Você ouvirá o áudio sendo reproduzido pelos alto-falantes. Ajuste o volume de saída no alto-falante conforme necessário.

1. Se precisar ajustar o volume da porta de microfone embutida ou o ganho do microfone, você pode usar o utilitário `alsamixer`. Você pode ler mais sobre este utilitário na [página de manual do alsamixer no Linux](https://linux.die.net/man/1/alsamixer).

1. Se você encontrar erros ao reproduzir o áudio, verifique a placa que configurou como `defaults.pcm.card` no arquivo `alsa.conf`.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.