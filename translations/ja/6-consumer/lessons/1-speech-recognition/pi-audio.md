<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-25T00:17:38+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "ja"
}
-->
# オーディオの録音 - Raspberry Pi

このレッスンでは、Raspberry Piでオーディオを録音するコードを書きます。オーディオ録音はボタンで制御されます。

## ハードウェア

Raspberry Piには、オーディオ録音を制御するためのボタンが必要です。

使用するボタンはGroveボタンです。これは信号をオンまたはオフに切り替えるデジタルセンサーです。このボタンは、押されたときに高信号を送信し、押されていないときに低信号を送信するように設定できます。または、押されたときに低信号、押されていないときに高信号を送信するようにも設定できます。

もしReSpeaker 2-Mics Pi HATをマイクとして使用している場合、ボタンを接続する必要はありません。このHATにはすでにボタンが付いているため、次のセクションに進んでください。

### ボタンを接続する

ボタンはGroveベースハットに接続できます。

#### タスク - ボタンを接続する

![Groveボタン](../../../../../translated_images/ja/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Groveケーブルの片方の端をボタンモジュールのソケットに差し込みます。このケーブルは一方向にしか差し込めません。

1. Raspberry Piの電源をオフにした状態で、Groveケーブルのもう一方の端を、Piに接続されたGroveベースハットのデジタルソケット**D5**に接続します。このソケットは、GPIOピンの隣のソケット列の左から2番目にあります。

![D5ソケットに接続されたGroveボタン](../../../../../translated_images/ja/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## オーディオの録音

Pythonコードを使用してマイクからオーディオを録音できます。

### タスク - オーディオを録音する

1. Piの電源を入れ、起動を待ちます。

1. VS Codeを起動します。Pi上で直接起動するか、Remote SSH拡張機能を使用して接続します。

1. PyAudio Pipパッケージには、オーディオの録音と再生のための関数が含まれています。このパッケージは、いくつかのオーディオライブラリに依存しているため、まず以下のコマンドをターミナルで実行してこれらをインストールします。

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pipパッケージをインストールします。

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer`という新しいフォルダを作成し、このフォルダに`app.py`というファイルを追加します。

1. このファイルの先頭に以下のインポートを追加します。

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    これにより、`pyaudio`モジュール、WAVファイルを処理するための標準Pythonモジュール、および`grove.factory`モジュールがインポートされ、ボタンクラスを作成するための`Factory`が使用可能になります。

1. この下に、Groveボタンを作成するコードを追加します。

    ReSpeaker 2-Mics Pi HATを使用している場合は、以下のコードを使用します。

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    これにより、ReSpeaker 2-Mics Pi HATに接続されたボタン（ポート**D17**）が作成されます。このボタンは、押されたときに低信号を送信するように設定されています。

    ReSpeaker 2-Mics Pi HATを使用していない場合で、Groveベースハットに接続されたGroveボタンを使用している場合は、以下のコードを使用します。

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    これにより、ポート**D5**に接続されたボタンが作成されます。このボタンは、押されたときに高信号を送信するように設定されています。

1. この下に、オーディオを処理するためのPyAudioクラスのインスタンスを作成します。

    ```python
    audio = pyaudio.PyAudio()
    ```

1. マイクとスピーカーのハードウェアカード番号を宣言します。これは、このレッスンの前半で`arecord -l`と`aplay -l`を実行して確認した番号です。

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>`をマイクのカード番号に置き換えます。

    `<speaker card number>`をスピーカーのカード番号に置き換えます。この番号は`alsa.conf`ファイルで設定した番号と同じです。

1. この下に、オーディオ録音と再生に使用するサンプルレートを宣言します。使用しているハードウェアによって、この値を変更する必要がある場合があります。

    ```python
    rate = 48000 #48KHz
    ```

    後でこのコードを実行した際にサンプルレートエラーが発生した場合、この値を`44100`または`16000`に変更してください。値が高いほど、音質が向上します。

1. この下に、`capture_audio`という新しい関数を作成します。この関数は、マイクからオーディオを録音するために呼び出されます。

    ```python
    def capture_audio():
    ```

1. この関数内に、以下のコードを追加してオーディオを録音します。

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

    このコードは、PyAudioオブジェクトを使用してオーディオ入力ストリームを開きます。このストリームは、16KHzでマイクからオーディオを録音し、4096バイトのバッファサイズでキャプチャします。

    コードは、Groveボタンが押されている間ループし、4096バイトのバッファを毎回配列に読み込みます。

    > 💁 `open`メソッドに渡されるオプションの詳細については、[PyAudioのドキュメント](https://people.csail.mit.edu/hubert/pyaudio/docs/)を参照してください。

    ボタンが離されたら、ストリームは停止して閉じられます。

1. この関数の最後に以下を追加します。

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

    このコードはバイナリバッファを作成し、キャプチャしたすべてのオーディオを[WAVファイル](https://wikipedia.org/wiki/WAV)として書き込みます。これは、非圧縮オーディオをファイルに書き込む標準的な方法です。このバッファはその後返されます。

1. オーディオバッファを再生するための`play_audio`関数を以下に追加します。

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

    この関数は、出力用の別のオーディオストリームを開きます。このストリームは、入力ストリームと同じ設定を使用します。バッファはWAVファイルとして開かれ、4096バイトのチャンクで出力ストリームに書き込まれ、オーディオが再生されます。その後、ストリームは閉じられます。

1. `capture_audio`関数の下に以下のコードを追加して、ボタンが押されるまでループします。ボタンが押されると、オーディオが録音され、その後再生されます。

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. コードを実行します。ボタンを押してマイクに向かって話します。話し終えたらボタンを離すと、録音が再生されます。

    PyAudioインスタンスが作成される際に、ALSAエラーが発生する場合があります。これは、Pi上で存在しないオーディオデバイスの設定が原因です。これらのエラーは無視して構いません。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    以下のエラーが発生した場合：

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    `rate`を`44100`または`16000`に変更してください。

> 💁 このコードは[code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi)フォルダにあります。

😀 オーディオ録音プログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。