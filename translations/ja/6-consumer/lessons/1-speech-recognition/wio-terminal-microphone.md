<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-25T00:32:29+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "ja"
}
-->
# マイクとスピーカーの設定 - Wio Terminal

このレッスンでは、Wio Terminalにスピーカーを追加します。Wio Terminalにはすでに内蔵マイクが搭載されており、これを使って音声を録音することができます。

## ハードウェア

Wio Terminalにはすでに内蔵マイクが搭載されており、音声認識のための音声を録音することができます。

![Wio Terminalのマイク](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.ja.png)

スピーカーを追加するには、[ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)を使用できます。この外部ボードには2つのMEMSマイク、スピーカーコネクタ、ヘッドフォンジャックが含まれています。

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.ja.png)

スピーカーを追加するには、ヘッドフォン、3.5mmジャック付きスピーカー、または[JST接続のMono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)のようなスピーカーが必要です。

ReSpeaker 2-Mics Pi Hatを接続するには、40ピンのジャンパーケーブル（ピン-ピン、またはオス-オスとも呼ばれる）が必要です。

> 💁 はんだ付けに慣れている場合は、[40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html)を使用してReSpeakerを接続することができます。

また、音声のダウンロードと再生に使用するSDカードが必要です。Wio Terminalは最大16GBまでのSDカードをサポートしており、これらはFAT32またはexFAT形式でフォーマットする必要があります。

### タスク - ReSpeaker Pi Hatを接続する

1. Wio Terminalの電源を切った状態で、ジャンパーケーブルとWio Terminalの背面にあるGPIOソケットを使用してReSpeaker 2-Mics Pi Hatを接続します。

    ピンは以下のように接続する必要があります：

    ![ピンの配線図](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.ja.png)

1. GPIOソケットが上向きで左側にある状態で、ReSpeakerとWio Terminalを配置します。

1. ReSpeakerのGPIOソケットの左上から始めます。ReSpeakerの左上ソケットからWio Terminalの左上ソケットにジャンパーケーブルを接続します。

1. 左側のGPIOソケットを下まで順番に接続します。ピンがしっかりと差し込まれていることを確認してください。

    ![左側のピンを接続したReSpeakerとWio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.ja.png)

    ![左側のピンを接続したReSpeakerとWio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.ja.png)

    > 💁 ジャンパーケーブルがリボン状になっている場合は、まとめておくとすべてのケーブルを順番に接続しやすくなります。

1. ReSpeakerとWio Terminalの右側のGPIOソケットを使って同じ手順を繰り返します。これらのケーブルはすでに接続されているケーブルの周りを通す必要があります。

    ![右側のピンを接続したReSpeakerとWio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.ja.png)

    ![右側のピンを接続したReSpeakerとWio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.ja.png)

    > 💁 ジャンパーケーブルがリボン状になっている場合は、2つのリボンに分けて、既存のケーブルの両側に通します。

    > 💁 ピンをブロック状に固定するために粘着テープを使用すると、接続中にピンが抜けるのを防ぐことができます。
    >
    > ![テープで固定されたピン](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.ja.png)

1. スピーカーを追加する必要があります。

    * JSTケーブル付きスピーカーを使用する場合は、ReSpeakerのJSTポートに接続します。

      ![JSTケーブルでReSpeakerに接続されたスピーカー](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.ja.png)

    * 3.5mmジャック付きスピーカーまたはヘッドフォンを使用する場合は、3.5mmジャックソケットに差し込みます。

      ![3.5mmジャックソケットでReSpeakerに接続されたスピーカー](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.ja.png)

### タスク - SDカードのセットアップ

1. SDカードをコンピュータに接続します。SDカードスロットがない場合は外部リーダーを使用してください。

1. コンピュータの適切なツールを使用してSDカードをフォーマットし、FAT32またはexFATファイルシステムを使用することを確認してください。

1. Wio Terminalの左側、電源ボタンのすぐ下にあるSDカードスロットにSDカードを挿入します。カードが完全に挿入され、クリック音がするまで押し込んでください。薄い工具や別のSDカードを使用して完全に押し込む必要がある場合があります。

    ![電源スイッチの下にあるSDカードスロットにSDカードを挿入する様子](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.ja.png)

    > 💁 SDカードを取り出すには、少し押し込むとカードが取り出されます。これを行うには、平らなドライバーや別のSDカードなどの薄い工具が必要です。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。