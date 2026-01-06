<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T03:03:27+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "br"
}
-->
# Configure seu microfone e alto-falantes - Wio Terminal

Nesta parte da lição, você adicionará alto-falantes ao seu Wio Terminal. O Wio Terminal já possui um microfone embutido, que pode ser usado para capturar fala.

## Hardware

O Wio Terminal já vem com um microfone embutido, que pode ser usado para capturar áudio para reconhecimento de fala.

![O microfone no Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.br.png)

Para adicionar um alto-falante, você pode usar o [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Esta é uma placa externa que contém 2 microfones MEMS, além de um conector para alto-falante e uma entrada para fones de ouvido.

![O ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.br.png)

Você precisará adicionar fones de ouvido, um alto-falante com conector de 3,5 mm ou um alto-falante com conexão JST, como o [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Para conectar o ReSpeaker 2-Mics Pi Hat, você precisará de cabos jumper de 40 pinos (também chamados de macho-macho).

> 💁 Se você estiver confortável com soldagem, pode usar o [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) para conectar o ReSpeaker.

Você também precisará de um cartão SD para baixar e reproduzir áudio. O Wio Terminal suporta apenas cartões SD de até 16GB, que precisam estar formatados como FAT32 ou exFAT.

### Tarefa - conectar o ReSpeaker Pi Hat

1. Com o Wio Terminal desligado, conecte o ReSpeaker 2-Mics Pi Hat ao Wio Terminal usando os cabos jumper e os soquetes GPIO na parte traseira do Wio Terminal:

    Os pinos precisam ser conectados desta forma:

    ![Um diagrama de pinos](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.br.png)

1. Posicione o ReSpeaker e o Wio Terminal com os soquetes GPIO voltados para cima e no lado esquerdo.

1. Comece pelo soquete no canto superior esquerdo do soquete GPIO no ReSpeaker. Conecte um cabo jumper do soquete superior esquerdo do ReSpeaker ao soquete superior esquerdo do Wio Terminal.

1. Repita isso até o final dos soquetes GPIO no lado esquerdo. Certifique-se de que os pinos estejam bem encaixados.

    ![Um ReSpeaker com os pinos do lado esquerdo conectados aos pinos do lado esquerdo do Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.br.png)

    ![Um ReSpeaker com os pinos do lado esquerdo conectados aos pinos do lado esquerdo do Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.br.png)

    > 💁 Se seus cabos jumper estiverem conectados em fitas, mantenha-os juntos - isso facilita garantir que todos os cabos estejam conectados na ordem correta.

1. Repita o processo usando os soquetes GPIO do lado direito no ReSpeaker e no Wio Terminal. Esses cabos precisam passar ao redor dos cabos que já estão conectados.

    ![Um ReSpeaker com os pinos do lado direito conectados aos pinos do lado direito do Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.br.png)

    ![Um ReSpeaker com os pinos do lado direito conectados aos pinos do lado direito do Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.br.png)

    > 💁 Se seus cabos jumper estiverem conectados em fitas, divida-os em duas fitas. Passe uma de cada lado dos cabos já existentes.

    > 💁 Você pode usar fita adesiva para manter os pinos em um bloco, ajudando a evitar que eles se soltem enquanto você os conecta.
    >
    > ![Os pinos fixados com fita adesiva](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.br.png)

1. Você precisará adicionar um alto-falante.

    * Se estiver usando um alto-falante com cabo JST, conecte-o à porta JST no ReSpeaker.

      ![Um alto-falante conectado ao ReSpeaker com um cabo JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.br.png)

    * Se estiver usando um alto-falante com conector de 3,5 mm ou fones de ouvido, insira-o na entrada de 3,5 mm.

      ![Um alto-falante conectado ao ReSpeaker via entrada de 3,5 mm](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.br.png)

### Tarefa - configurar o cartão SD

1. Conecte o cartão SD ao seu computador, usando um leitor externo se o computador não tiver um slot para cartão SD.

1. Formate o cartão SD usando a ferramenta apropriada no seu computador, certificando-se de usar o sistema de arquivos FAT32 ou exFAT.

1. Insira o cartão SD no slot do Wio Terminal, localizado no lado esquerdo, logo abaixo do botão de energia. Certifique-se de que o cartão esteja completamente inserido e faça um clique - você pode precisar de uma ferramenta fina ou outro cartão SD para ajudar a empurrá-lo completamente.

    ![Inserindo o cartão SD no slot abaixo do botão de energia](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.br.png)

    > 💁 Para ejetar o cartão SD, você precisa empurrá-lo levemente para dentro, e ele será ejetado. Você precisará de uma ferramenta fina, como uma chave de fenda de cabeça chata ou outro cartão SD, para fazer isso.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.