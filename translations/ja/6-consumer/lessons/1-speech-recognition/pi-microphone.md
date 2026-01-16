<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-25T00:31:03+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "ja"
}
-->
# マイクとスピーカーの設定 - Raspberry Pi

このレッスンでは、Raspberry Piにマイクとスピーカーを追加します。

## ハードウェア

Raspberry Piにはマイクが必要です。

Piには内蔵マイクがないため、外付けマイクを追加する必要があります。以下の方法で接続できます：

* USBマイク
* USBヘッドセット
* USB一体型スピーカーフォン
* USBオーディオアダプターと3.5mmジャック付きマイク
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 BluetoothマイクはすべてのRaspberry Piでサポートされているわけではありません。そのため、Bluetoothマイクやヘッドセットを使用する場合、ペアリングや音声の取得に問題が発生する可能性があります。

Raspberry Piには3.5mmヘッドフォンジャックが付属しています。これを使用してヘッドフォン、ヘッドセット、またはスピーカーを接続できます。また、以下の方法でスピーカーを追加することもできます：

* HDMIオーディオ（モニターやテレビを通じて）
* USBスピーカー
* USBヘッドセット
* USB一体型スピーカーフォン
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)にスピーカーを接続（3.5mmジャックまたはJSTポートを使用）

## マイクとスピーカーの接続と設定

マイクとスピーカーを接続し、設定する必要があります。

### タスク - マイクの接続と設定

1. 適切な方法でマイクを接続します。例えば、USBポートの1つを使用して接続します。

1. ReSpeaker 2-Mics Pi HATを使用する場合、Groveベースハットを取り外し、代わりにReSpeakerハットを取り付けます。

    ![ReSpeakerハットを装着したRaspberry Pi](../../../../../translated_images/ja/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    このレッスンの後半でGroveボタンが必要になりますが、このハットにはボタンが内蔵されているため、Groveベースハットは不要です。

    ハットを取り付けたら、ドライバーをインストールする必要があります。ドライバーのインストール手順については、[Seeedのスタートガイド](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started)を参照してください。

    > ⚠️ 手順では`git`を使用してリポジトリをクローンします。Piに`git`がインストールされていない場合は、以下のコマンドを実行してインストールできます：
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Pi上のターミナル、またはVS Codeを使用したリモートSSHセッションで以下のコマンドを実行し、接続されているマイクの情報を確認します：

    ```sh
    arecord -l
    ```

    接続されているマイクのリストが表示されます。以下のような出力が得られるでしょう：

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    マイクが1つしか接続されていない場合、エントリは1つだけ表示されます。Linuxでのマイクの設定は複雑な場合があるため、1つのマイクのみを使用し、他のマイクは取り外すのが最も簡単です。

    カード番号をメモしておいてください。この番号は後で必要になります。上記の出力ではカード番号は1です。

### タスク - スピーカーの接続と設定

1. 適切な方法でスピーカーを接続します。

1. Pi上のターミナル、またはVS Codeを使用したリモートSSHセッションで以下のコマンドを実行し、接続されているスピーカーの情報を確認します：

    ```sh
    aplay -l
    ```

    接続されているスピーカーのリストが表示されます。以下のような出力が得られるでしょう：

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

    `card 0: Headphones`は常に表示されます。これは内蔵ヘッドフォンジャックです。USBスピーカーなどの追加スピーカーを接続している場合、それもリストに表示されます。

1. 内蔵ヘッドフォンジャックに接続されたスピーカーやヘッドフォンではなく、追加スピーカーを使用する場合は、それをデフォルトとして設定する必要があります。以下のコマンドを実行してください：

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    このコマンドを実行すると、`nano`というターミナルベースのテキストエディタで設定ファイルが開きます。キーボードの矢印キーを使用して以下の行を探します：

    ```output
    defaults.pcm.card 0
    ```

    値を`0`から、`aplay -l`コマンドの出力で確認した使用したいカード番号に変更します。例えば、上記の出力では、`card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`という2番目のサウンドカードがあり、カード番号は1です。このカードを使用するには、以下のように行を更新します：

    ```output
    defaults.pcm.card 1
    ```

    適切なカード番号に設定してください。矢印キーを使用して番号の位置に移動し、通常のテキスト編集のように削除して新しい番号を入力します。

1. `Ctrl+x`を押して変更を保存し、ファイルを閉じます。`y`を押してファイルを保存し、`return`を押してファイル名を選択します。

### タスク - マイクとスピーカーのテスト

1. 以下のコマンドを実行して、マイクを使用して5秒間音声を録音します：

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    このコマンドが実行されている間、マイクに向かって音を出してください。話す、歌う、ビートボックスする、楽器を演奏するなど、自由に行ってください。

1. 5秒後、録音が停止します。以下のコマンドを実行して音声を再生します：

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    スピーカーを通じて音声が再生されます。必要に応じてスピーカーの出力音量を調整してください。

1. 内蔵マイクポートの音量を調整したり、マイクのゲインを調整する必要がある場合は、`alsamixer`ユーティリティを使用できます。このユーティリティについては、[Linux alsamixer manページ](https://linux.die.net/man/1/alsamixer)で詳しく読むことができます。

1. 音声の再生時にエラーが発生した場合、`alsa.conf`ファイルで設定した`defaults.pcm.card`のカード番号を確認してください。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤った解釈について、当方は責任を負いません。