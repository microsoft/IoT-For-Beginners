<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-25T00:53:50+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "ja"
}
-->
# GPSデータを読み取る - Raspberry Pi

このレッスンでは、Raspberry PiにGPSセンサーを追加し、その値を読み取ります。

## ハードウェア

Raspberry PiにはGPSセンサーが必要です。

使用するセンサーは[Grove GPS Air530センサー](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)です。このセンサーは複数のGPSシステムに接続でき、迅速かつ正確な位置情報を取得できます。センサーは2つの部分で構成されており、センサーのコア電子部品と、薄いワイヤーで接続された外部アンテナがあります。このアンテナは衛星からの電波を受信します。

このセンサーはUARTセンサーであり、UARTを介してGPSデータを送信します。

## GPSセンサーを接続する

Grove GPSセンサーはRaspberry Piに接続できます。

### タスク - GPSセンサーを接続する

GPSセンサーを接続します。

![Grove GPSセンサー](../../../../../translated_images/ja/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Groveケーブルの片方の端をGPSセンサーのソケットに差し込みます。ケーブルは一方向にしか差し込めません。

1. Raspberry Piの電源を切った状態で、Groveケーブルのもう片方の端を、Piに取り付けられたGrove Base Hatの**UART**と記されたUARTソケットに接続します。このソケットはSDカードスロットに近い側の中央列にあり、USBポートやイーサネットソケットの反対側に位置しています。

    ![UARTソケットに接続されたGrove GPSセンサー](../../../../../translated_images/ja/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. GPSセンサーを配置し、接続されたアンテナが空を見渡せる位置に置きます。理想的には窓の近くや屋外に置くと良いです。アンテナに障害物がない方が信号を受信しやすくなります。

## GPSセンサーをプログラムする

Raspberry Piをプログラムして、接続されたGPSセンサーを使用できるようにします。

### タスク - GPSセンサーをプログラムする

デバイスをプログラムします。

1. Piの電源を入れ、起動を待ちます。

1. GPSセンサーには2つのLEDがあります。青いLEDはデータが送信されると点滅し、緑のLEDは衛星からデータを受信すると毎秒点滅します。Piの電源を入れた際に青いLEDが点滅していることを確認してください。数分後に緑のLEDが点滅します。点滅しない場合はアンテナの位置を調整する必要があるかもしれません。

1. VS Codeを起動します。Pi上で直接起動するか、Remote SSH拡張機能を使用して接続します。

    > ⚠️ 必要に応じて、[レッスン1でのVS Codeのセットアップと起動手順](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)を参照してください。

1. Bluetoothをサポートする新しいバージョンのRaspberry Piでは、Bluetoothに使用されるシリアルポートとGrove UARTポートに使用されるシリアルポートが競合します。この問題を解決するには、以下の手順を実行してください：

    1. VS Codeのターミナルから、以下のコマンドを使用して`nano`という組み込みのターミナルテキストエディタで`/boot/config.txt`ファイルを編集します：

        ```sh
        sudo nano /boot/config.txt
        ```

        > このファイルは`sudo`権限（管理者権限）で編集する必要があるため、VS Codeでは編集できません。VS Codeはこの権限で実行されません。

    1. カーソルキーを使用してファイルの末尾に移動し、以下のコードをコピーして末尾に貼り付けます：

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        通常のキーボードショートカットを使用して貼り付けます（Windows、Linux、Raspberry Pi OSでは`Ctrl+v`、macOSでは`Cmd+v`）。

    1. `Ctrl+x`を押してファイルを保存し、nanoを終了します。変更したバッファを保存するか尋ねられたら`y`を押し、`enter`を押して`/boot/config.txt`を上書きすることを確認します。

        > 間違えた場合は保存せずに終了し、これらの手順を繰り返してください。

    1. 以下のコマンドを使用して`/boot/cmdline.txt`ファイルをnanoで編集します：

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. このファイルにはスペースで区切られたキー/値ペアがいくつか含まれています。キー`console`に関連するキー/値ペアを削除してください。それらは以下のように見える可能性があります：

        ```output
        console=serial0,115200 console=tty1 
        ```

        カーソルキーを使用してこれらのエントリに移動し、通常の`del`または`backspace`キーを使用して削除します。

        例えば、元のファイルが以下のようになっている場合：

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        新しいバージョンは以下のようになります：

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. 上記の手順に従ってこのファイルを保存し、nanoを終了します。

    1. Piを再起動し、再起動後にVS Codeに再接続します。

1. ターミナルから、`pi`ユーザーのホームディレクトリに`gps-sensor`という新しいフォルダを作成します。このフォルダ内に`app.py`というファイルを作成します。

1. このフォルダをVS Codeで開きます。

1. GPSモジュールはUARTデータをシリアルポート経由で送信します。Pythonコードからシリアルポートと通信するために`pyserial` Pipパッケージをインストールします：

    ```sh
    pip3 install pyserial
    ```

1. 以下のコードを`app.py`ファイルに追加します：

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    このコードは`pyserial` Pipパッケージから`serial`モジュールをインポートします。その後、Grove Pi Base HatがUARTポートに使用するシリアルポートのアドレスである`/dev/ttyAMA0`に接続します。そして、このシリアル接続から既存のデータをクリアします。

    次に、`print_gps_data`という関数が定義され、渡された行をコンソールに出力します。

    その後、コードは永遠にループし、各ループでシリアルポートから可能な限り多くのテキスト行を読み取ります。そして、各行に対して`print_gps_data`関数を呼び出します。

    すべてのデータが読み取られた後、ループは1秒間スリープし、再度試行します。

1. このコードを実行します。GPSセンサーからの生の出力が以下のように表示されます：

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > コードを停止して再起動する際に以下のエラーが発生した場合、`try - except`ブロックをwhileループに追加してください。

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 このコードは[code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi)フォルダにあります。

😀 GPSセンサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。