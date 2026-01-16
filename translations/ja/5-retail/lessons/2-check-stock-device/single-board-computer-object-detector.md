<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-24T21:07:09+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "ja"
}
-->
# IoTデバイスからオブジェクト検出器を呼び出す - 仮想IoTハードウェアとRaspberry Pi

オブジェクト検出器を公開したら、IoTデバイスから使用できるようになります。

## 画像分類プロジェクトをコピーする

在庫検出器の大部分は、以前のレッスンで作成した画像分類器と同じです。

### タスク - 画像分類プロジェクトをコピーする

1. `stock-counter`というフォルダーを作成します。仮想IoTデバイスを使用している場合はコンピューター上に、Raspberry Piを使用している場合はRaspberry Pi上に作成してください。仮想IoTデバイスを使用している場合は、仮想環境を設定することを忘れないでください。

1. カメラハードウェアをセットアップします。

    * Raspberry Piを使用している場合は、PiCameraを取り付ける必要があります。また、カメラを固定位置に設置することを検討してください。例えば、ケーブルを箱や缶の上に吊るしたり、両面テープで箱に固定したりする方法があります。
    * 仮想IoTデバイスを使用している場合は、CounterFitとCounterFit PyCamera shimをインストールする必要があります。静止画像を使用する場合は、オブジェクト検出器がまだ見たことのない画像をいくつかキャプチャしてください。ウェブカメラを使用する場合は、検出する在庫が見える位置にカメラを配置してください。

1. [製造プロジェクトのレッスン2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)の手順を再現して、カメラから画像をキャプチャします。

1. [製造プロジェクトのレッスン2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)の手順を再現して、画像分類器を呼び出します。このコードの大部分はオブジェクトを検出するために再利用されます。

## 分類器のコードをオブジェクト検出器に変更する

画像を分類するために使用したコードは、オブジェクトを検出するコードと非常に似ています。主な違いは、Custom Vision SDKで呼び出されるメソッドと、その呼び出し結果です。

### タスク - 分類器のコードをオブジェクト検出器に変更する

1. 画像を分類し、予測を処理する3行のコードを削除します：

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    この3行を削除してください。

1. 画像内のオブジェクトを検出するための以下のコードを追加します：

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    このコードは、予測器の`detect_image`メソッドを呼び出してオブジェクト検出器を実行します。その後、しきい値を超える確率を持つすべての予測を収集し、それらをコンソールに出力します。

    画像分類器がタグごとに1つの結果しか返さないのに対し、オブジェクト検出器は複数の結果を返すため、確率が低いものはフィルタリングする必要があります。

1. このコードを実行すると、画像をキャプチャし、オブジェクト検出器に送信し、検出されたオブジェクトを出力します。仮想IoTデバイスを使用している場合は、CounterFitで適切な画像を設定するか、ウェブカメラが選択されていることを確認してください。Raspberry Piを使用している場合は、カメラが棚の上のオブジェクトを指していることを確認してください。

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 画像に適した`threshold`値を調整する必要があるかもしれません。

    撮影された画像とこれらの値をCustom Visionの**Predictions**タブで確認できます。

    ![棚の上に置かれた4つのトマトペースト缶と、それぞれの検出確率（35.8%、33.5%、25.7%、16.6%）](../../../../../translated_images/ja/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 このコードは[code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi)または[code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device)フォルダーで見つけることができます。

😀 在庫カウンタープログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は責任を負いません。