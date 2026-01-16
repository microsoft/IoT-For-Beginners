<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-24T21:34:20+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "ja"
}
-->
# 画像をキャプチャする - 仮想IoTハードウェア

このレッスンでは、仮想IoTデバイスにカメラセンサーを追加し、画像を読み取る方法を学びます。

## ハードウェア

仮想IoTデバイスは、ファイルからの画像またはウェブカメラからの画像を送信するシミュレートされたカメラを使用します。

### CounterFitにカメラを追加する

仮想カメラを使用するには、CounterFitアプリにカメラを追加する必要があります。

#### タスク - CounterFitにカメラを追加する

CounterFitアプリにカメラを追加します。

1. `fruit-quality-detector`というフォルダーに`app.py`という単一のファイルを持つ新しいPythonアプリを作成し、Python仮想環境を設定して、CounterFitのpipパッケージを追加します。

    > ⚠️ 必要に応じて、[レッスン1でのCounterFit Pythonプロジェクトの作成と設定に関する手順](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)を参照してください。

1. 追加のPipパッケージをインストールして、Cameraセンサーと通信できるCounterFit shimをインストールします。このshimは、一部の[Picamera Pipパッケージ](https://pypi.org/project/picamera/)をシミュレートします。仮想環境が有効化されたターミナルからインストールしてください。

    ```sh
    pip install counterfit-shims-picamera
    ```

1. CounterFitウェブアプリが実行中であることを確認します。

1. カメラを作成します：

    1. *Sensors*ペインの*Create sensor*ボックスで、*Sensor type*ボックスをドロップダウンし、*Camera*を選択します。

    1. *Name*を`Picamera`に設定します。

    1. **Add**ボタンを選択してカメラを作成します。

    ![カメラ設定](../../../../../translated_images/ja/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    カメラが作成され、センサーリストに表示されます。

    ![作成されたカメラ](../../../../../translated_images/ja/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## カメラをプログラムする

仮想IoTデバイスは、仮想カメラを使用するようにプログラムできます。

### タスク - カメラをプログラムする

デバイスをプログラムします。

1. `fruit-quality-detector`アプリがVS Codeで開かれていることを確認します。

1. `app.py`ファイルを開きます。

1. CounterFitにアプリを接続するために、以下のコードを`app.py`の先頭に追加します：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 以下のコードを`app.py`ファイルに追加します：

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    このコードは、必要なライブラリをインポートし、counterfit_shims_picameraライブラリの`PiCamera`クラスを含みます。

1. カメラを初期化するために、以下のコードを追加します：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    このコードは、PiCameraオブジェクトを作成し、解像度を640x480に設定します。より高い解像度もサポートされていますが、画像分類器ははるかに小さい画像（227x227）で動作するため、大きな画像をキャプチャして送信する必要はありません。

    `camera.rotation = 0`行は、画像の回転を度単位で設定します。ウェブカメラやファイルからの画像を回転させる必要がある場合は、適切に設定してください。例えば、横向きのウェブカメラで撮影したバナナの画像を縦向きに変更したい場合は、`camera.rotation = 90`に設定します。

1. 画像をバイナリデータとしてキャプチャするために、以下のコードを追加します：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    このコードは、バイナリデータを格納するための`BytesIO`オブジェクトを作成します。画像はカメラからJPEGファイルとして読み取られ、このオブジェクトに格納されます。このオブジェクトには、データのどこにいるかを示す位置インジケーターがあり、必要に応じてデータを末尾に書き込むことができます。そのため、`image.seek(0)`行は、この位置を先頭に戻し、後で全データを読み取れるようにします。

1. 以下のコードを追加して、画像をファイルに保存します：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    このコードは、`image.jpg`という名前のファイルを開き、`BytesIO`オブジェクトからすべてのデータを読み取り、それをファイルに書き込みます。

    > 💁 画像を直接ファイルにキャプチャすることもできます。その場合は、`camera.capture`呼び出しにファイル名を渡します。このレッスンの後半で画像を画像分類器に送信するために、`BytesIO`オブジェクトを使用しています。

1. CounterFitでカメラがキャプチャする画像を設定します。*Source*を*File*に設定して画像ファイルをアップロードするか、*Source*を*WebCam*に設定してウェブカメラから画像をキャプチャします。画像を選択するかウェブカメラを選択した後、**Set**ボタンを必ず選択してください。

    ![CounterFitで画像ソースをファイルに設定し、ウェブカメラでバナナを持つ人を表示しているプレビュー](../../../../../translated_images/ja/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. 画像がキャプチャされ、現在のフォルダーに`image.jpg`として保存されます。このファイルはVS Codeのエクスプローラーに表示されます。ファイルを選択して画像を確認してください。回転が必要な場合は、`camera.rotation = 0`行を適切に更新し、再度撮影してください。

> 💁 このコードは[code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device)フォルダーにあります。

😀 カメラプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。