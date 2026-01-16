<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-25T22:40:48+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "pt"
}
-->
# Capturar áudio - Raspberry Pi

Nesta parte da lição, vais escrever código para capturar áudio no teu Raspberry Pi. A captura de áudio será controlada por um botão.

## Hardware

O Raspberry Pi precisa de um botão para controlar a captura de áudio.

O botão que vais usar é um botão Grove. Este é um sensor digital que liga ou desliga um sinal. Estes botões podem ser configurados para enviar um sinal alto quando o botão é pressionado, e baixo quando não é, ou baixo quando pressionado e alto quando não é.

Se estiveres a usar um ReSpeaker 2-Mics Pi HAT como microfone, não é necessário conectar um botão, pois este HAT já tem um botão integrado. Podes passar para a próxima secção.

### Conectar o botão

O botão pode ser conectado ao Grove Base Hat.

#### Tarefa - conectar o botão

![Um botão Grove](../../../../../translated_images/pt/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Insere uma extremidade de um cabo Grove na entrada do módulo do botão. Só encaixará de uma forma.

1. Com o Raspberry Pi desligado, conecta a outra extremidade do cabo Grove à entrada digital marcada como **D5** no Grove Base Hat conectado ao Pi. Esta entrada é a segunda da esquerda, na fila de entradas ao lado dos pinos GPIO.

![O botão Grove conectado à entrada D5](../../../../../translated_images/pt/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Capturar áudio

Podes capturar áudio do microfone usando código em Python.

### Tarefa - capturar áudio

1. Liga o Pi e espera que ele inicie.

1. Abre o VS Code, diretamente no Pi ou conecta-te através da extensão Remote SSH.

1. O pacote PyAudio Pip tem funções para gravar e reproduzir áudio. Este pacote depende de algumas bibliotecas de áudio que precisam de ser instaladas primeiro. Executa os seguintes comandos no terminal para instalá-las:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Instala o pacote PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Cria uma nova pasta chamada `smart-timer` e adiciona um ficheiro chamado `app.py` a esta pasta.

1. Adiciona as seguintes importações ao topo deste ficheiro:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Isto importa o módulo `pyaudio`, alguns módulos padrão do Python para lidar com ficheiros WAV, e o módulo `grove.factory` para importar uma `Factory` que cria uma classe de botão.

1. Abaixo disso, adiciona código para criar um botão Grove.

    Se estiveres a usar o ReSpeaker 2-Mics Pi HAT, usa o seguinte código:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Isto cria um botão na porta **D17**, a porta à qual o botão no ReSpeaker 2-Mics Pi HAT está conectado. Este botão está configurado para enviar um sinal baixo quando pressionado.

    Se não estiveres a usar o ReSpeaker 2-Mics Pi HAT e estiveres a usar um botão Grove conectado ao Base Hat, usa este código:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Isto cria um botão na porta **D5**, configurado para enviar um sinal alto quando pressionado.

1. Abaixo disso, cria uma instância da classe PyAudio para lidar com áudio:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Declara o número da placa de hardware para o microfone e altifalante. Este será o número da placa que encontraste ao executar `arecord -l` e `aplay -l` anteriormente nesta lição.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Substitui `<microphone card number>` pelo número da placa do teu microfone.

    Substitui `<speaker card number>` pelo número da placa do teu altifalante, o mesmo número que configuraste no ficheiro `alsa.conf`.

1. Abaixo disso, declara a taxa de amostragem a usar para a captura e reprodução de áudio. Poderás precisar de alterar isto dependendo do hardware que estás a usar.

    ```python
    rate = 48000 #48KHz
    ```

    Se obtiveres erros de taxa de amostragem ao executar este código mais tarde, altera este valor para `44100` ou `16000`. Quanto maior o valor, melhor a qualidade do som.

1. Abaixo disso, cria uma nova função chamada `capture_audio`. Esta será chamada para capturar áudio do microfone:

    ```python
    def capture_audio():
    ```

1. Dentro desta função, adiciona o seguinte para capturar o áudio:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    Este código abre um fluxo de entrada de áudio usando o objeto PyAudio. Este fluxo capturará áudio do microfone a 16KHz, capturando-o em buffers de 4096 bytes.

    O código então entra num loop enquanto o botão Grove está pressionado, lendo estes buffers de 4096 bytes para um array a cada vez.

    > 💁 Podes ler mais sobre as opções passadas ao método `open` na [documentação do PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Quando o botão é solto, o fluxo é parado e fechado.

1. Adiciona o seguinte ao final desta função:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    Este código cria um buffer binário e escreve todo o áudio capturado nele como um [ficheiro WAV](https://wikipedia.org/wiki/WAV). Este é um formato padrão para escrever áudio não comprimido num ficheiro. Este buffer é então retornado.

1. Adiciona a seguinte função `play_audio` para reproduzir o buffer de áudio:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    Esta função abre outro fluxo de áudio, desta vez para saída - para reproduzir o áudio. Usa as mesmas configurações do fluxo de entrada. O buffer é então aberto como um ficheiro WAV e escrito no fluxo de saída em blocos de 4096 bytes, reproduzindo o áudio. O fluxo é então fechado.

1. Adiciona o seguinte código abaixo da função `capture_audio` para entrar num loop até que o botão seja pressionado. Quando o botão é pressionado, o áudio é capturado e depois reproduzido.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Executa o código. Pressiona o botão e fala no microfone. Solta o botão quando terminares e ouvirás a gravação.

    Poderás ver alguns erros ALSA quando a instância PyAudio é criada. Isto deve-se à configuração no Pi para dispositivos de áudio que não tens. Podes ignorar estes erros.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Se obtiveres o seguinte erro:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    então altera o `rate` para 44100 ou 16000.

> 💁 Podes encontrar este código na pasta [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 O teu programa de gravação de áudio foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.