<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-24T21:30:14+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "ja"
}
-->
# 画像を撮影する - Raspberry Pi

このレッスンでは、Raspberry Piにカメラセンサーを追加し、画像を読み取る方法を学びます。

## ハードウェア

Raspberry Piにはカメラが必要です。

使用するカメラは[Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/)です。このカメラはRaspberry Pi専用に設計されており、Piの専用コネクタに接続します。

> 💁 このカメラは[Camera Serial Interface（モバイル業界プロセッサインターフェースアライアンスによるプロトコル）](https://wikipedia.org/wiki/Camera_Serial_Interface)を使用します。これは画像を送信するための専用プロトコルです。

## カメラを接続する

カメラはリボンケーブルを使ってRaspberry Piに接続できます。

### タスク - カメラを接続する

![Raspberry Pi Camera](../../../../../translated_images/ja/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Piの電源を切ります。

1. カメラに付属しているリボンケーブルをカメラに接続します。これを行うには、ホルダーの黒いプラスチッククリップを少し引っ張って外し、ケーブルをソケットに差し込みます。青い面がレンズから離れる方向、金属ピンのストリップがレンズに向かう方向にしてください。ケーブルが完全に挿入されたら、黒いプラスチッククリップを元の位置に戻します。

    クリップを開けてケーブルを挿入する方法を示すアニメーションは[Raspberry Pi Getting Started with the Camera module documentation](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2)で確認できます。

    ![リボンケーブルがカメラモジュールに挿入された状態](../../../../../translated_images/ja/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Grove Base HatをPiから取り外します。

1. Grove Base Hatのカメラスロットを通してリボンケーブルを通します。ケーブルの青い面が**A0**、**A1**などとラベル付けされたアナログポートの方向を向くようにしてください。

    ![Grove Base Hatを通過するリボンケーブル](../../../../../translated_images/ja/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. リボンケーブルをPiのカメラポートに挿入します。再び黒いプラスチッククリップを引き上げ、ケーブルを挿入してクリップを元に戻します。ケーブルの青い面がUSBとイーサネットポートの方向を向くようにしてください。

    ![Piのカメラソケットに接続されたリボンケーブル](../../../../../translated_images/ja/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Grove Base Hatを再装着します。

## カメラをプログラムする

Raspberry Piは[PiCamera](https://pypi.org/project/picamera/) Pythonライブラリを使用してカメラをプログラムできます。

### タスク - レガシーカメラモードを有効にする

残念ながら、Raspberry Pi OS Bullseyeのリリースに伴い、OSに付属していたカメラソフトウェアが変更され、デフォルトではPiCameraが動作しなくなりました。代替としてPiCamera2が開発されていますが、まだ使用可能な状態ではありません。

現在のところ、Piをレガシーカメラモードに設定することでPiCameraを動作させることができます。カメラソケットはデフォルトで無効になっていますが、レガシーカメラソフトウェアを有効にすると自動的にソケットも有効になります。

1. Piの電源を入れ、起動を待ちます。

1. VS Codeを起動します。Pi上で直接起動するか、Remote SSH拡張機能を使用して接続します。

1. ターミナルで以下のコマンドを実行します：

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    このコマンドはレガシーカメラソフトウェアを有効にする設定を切り替え、設定を反映させるためにPiを再起動します。

1. Piの再起動を待ち、再度VS Codeを起動します。

### タスク - カメラをプログラムする

デバイスをプログラムします。

1. ターミナルで`pi`ユーザーのホームディレクトリに`fruit-quality-detector`という新しいフォルダを作成します。このフォルダ内に`app.py`というファイルを作成します。

1. このフォルダをVS Codeで開きます。

1. カメラと対話するためにPiCamera Pythonライブラリを使用します。以下のコマンドでPipパッケージをインストールします：

    ```sh
    pip3 install picamera
    ```

1. `app.py`ファイルに以下のコードを追加します：

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    このコードは必要なライブラリをインポートし、`PiCamera`ライブラリを含みます。

1. 次に、カメラを初期化する以下のコードを追加します：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    このコードはPiCameraオブジェクトを作成し、解像度を640x480に設定します。より高い解像度（最大3280x2464）もサポートされていますが、画像分類器はもっと小さい画像（227x227）で動作するため、大きな画像をキャプチャして送信する必要はありません。

    `camera.rotation = 0`行は画像の回転を設定します。リボンケーブルはカメラの下部に接続されますが、分類したいアイテムに向けやすくするためにカメラを回転させた場合、この行を回転角度に応じて変更できます。

    ![飲料缶の上に吊り下げられたカメラ](../../../../../translated_images/ja/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    例えば、リボンケーブルをカメラの上部に吊り下げた場合、回転を180に設定します：

    ```python
    camera.rotation = 180
    ```

    カメラは起動に数秒かかるため、`time.sleep(2)`が必要です。

1. 次に、画像をバイナリデータとしてキャプチャする以下のコードを追加します：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    このコードはバイナリデータを保存するための`BytesIO`オブジェクトを作成します。カメラからJPEGファイルとして画像を読み取り、このオブジェクトに保存します。このオブジェクトにはデータの位置インジケータがあり、必要に応じてデータを末尾に書き込むことができます。そのため、`image.seek(0)`行で位置を先頭に戻し、後で全データを読み取れるようにします。

1. 次に、画像をファイルに保存する以下のコードを追加します：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    このコードは`image.jpg`という名前のファイルを開き、`BytesIO`オブジェクトからすべてのデータを読み取り、そのファイルに書き込みます。

    > 💁 画像を直接ファイルにキャプチャすることもできますが、`camera.capture`呼び出しにファイル名を渡す必要があります。このレッスンの後半で画像を画像分類器に送信するために`BytesIO`オブジェクトを使用しています。

1. カメラを何かに向け、このコードを実行します。

1. 画像がキャプチャされ、現在のフォルダに`image.jpg`として保存されます。このファイルはVS Codeのエクスプローラーで確認できます。ファイルを選択して画像を表示します。必要に応じて`camera.rotation = 0`行を更新し、再度撮影してください。

> 💁 このコードは[code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi)フォルダにあります。

😀 カメラプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は一切の責任を負いません。