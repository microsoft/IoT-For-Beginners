<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T00:52:28+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "ja"
}
-->
# GPSデータのデコード - 仮想IoTハードウェアとRaspberry Pi

このレッスンでは、Raspberry Piまたは仮想IoTデバイスでGPSセンサーから読み取ったNMEAメッセージをデコードし、緯度と経度を抽出します。

## GPSデータのデコード

シリアルポートから生のNMEAデータを読み取った後、オープンソースのNMEAライブラリを使用してデコードすることができます。

### タスク - GPSデータのデコード

デバイスをプログラムしてGPSデータをデコードします。

1. `gps-sensor`アプリプロジェクトを開いていない場合は開いてください。

1. `pynmea2` Pipパッケージをインストールします。このパッケージにはNMEAメッセージをデコードするためのコードが含まれています。

    ```sh
    pip3 install pynmea2
    ```

1. `app.py`ファイルのインポート部分に以下のコードを追加して、`pynmea2`モジュールをインポートします。

    ```python
    import pynmea2
    ```

1. `print_gps_data`関数の内容を以下のコードに置き換えてください。

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    このコードは、UARTシリアルポートから読み取った行を解析するために`pynmea2`ライブラリを使用します。

    メッセージの文型が`GGA`の場合、これは位置固定メッセージであり、処理されます。メッセージから緯度と経度の値を読み取り、NMEA形式`(d)ddmm.mmmm`から10進度に変換します。この変換は`dm_to_sd`関数によって行われます。

    次に、緯度の方向を確認し、緯度が南の場合は値を負の数に変換します。同様に、経度が西の場合も負の数に変換されます。

    最後に、座標と位置を取得するために使用された衛星の数をコンソールに出力します。

1. コードを実行します。仮想IoTデバイスを使用している場合は、CounterFitアプリが実行中であり、GPSデータが送信されていることを確認してください。

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 このコードは[code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device)フォルダー、または[code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi)フォルダーにあります。

😀 GPSセンサーのデータデコードプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。