<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-24T21:31:33+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "ja"
}
-->
# 画像を分類する - 仮想IoTハードウェアとRaspberry Pi

このレッスンのこの部分では、カメラで撮影した画像をCustom Visionサービスに送信して分類します。

## Custom Visionに画像を送信する

Custom Visionサービスには、画像を分類するために使用できるPython SDKがあります。

### タスク - Custom Visionに画像を送信する

1. VS Codeで`fruit-quality-detector`フォルダーを開きます。仮想IoTデバイスを使用している場合は、ターミナルで仮想環境が実行されていることを確認してください。

1. Custom Visionに画像を送信するためのPython SDKはPipパッケージとして利用可能です。以下のコマンドでインストールしてください:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py`ファイルの先頭に以下のインポート文を追加します:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    これにより、Custom Visionライブラリからいくつかのモジュールがインポートされます。一つは予測キーで認証するためのモジュール、もう一つはCustom Visionを呼び出すための予測クライアントクラスを提供します。

1. ファイルの末尾に以下のコードを追加します:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>`には、このレッスンの前半で*Prediction URL*ダイアログからコピーしたURLを置き換えてください。`<prediction key>`には同じダイアログからコピーした予測キーを置き換えてください。

1. *Prediction URL*ダイアログから提供された予測URLは、RESTエンドポイントを直接呼び出す際に使用するよう設計されています。Python SDKでは、このURLの一部を異なる場所で使用します。以下のコードを追加して、このURLを必要な部分に分解します:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    これにより、URLが分割され、`https://<location>.api.cognitive.microsoft.com`というエンドポイント、プロジェクトID、および公開されたイテレーションの名前が抽出されます。

1. 以下のコードを使用して予測を実行するための予測オブジェクトを作成します:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials`は予測キーをラップします。これを使用して、エンドポイントを指す予測クライアントオブジェクトを作成します。

1. 以下のコードを使用して画像をCustom Visionに送信します:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    これにより、画像が最初に戻され、予測クライアントに送信されます。

1. 最後に、以下のコードを使用して結果を表示します:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    これにより、返されたすべての予測をループしてターミナルに表示します。返される確率は0から1の浮動小数点数で、0はタグに一致する確率が0%、1は100%を意味します。

    > 💁 画像分類器は使用されたすべてのタグの確率を返します。各タグには、その画像がタグに一致する確率が表示されます。

1. カメラを果物に向けるか、適切な画像セットを使用するか、仮想IoTハードウェアを使用している場合はウェブカメラに果物が見えるようにしてコードを実行してください。コンソールに出力が表示されます:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    撮影された画像と、**Predictions**タブでこれらの値をCustom Visionで確認できます。

    ![Custom Visionでバナナが予測され、熟している確率が56.8%、未熟な確率が43.1%と表示されている](../../../../../translated_images/ja/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 このコードは[code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi)または[code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device)フォルダーで確認できます。

😀 あなたの果物品質分類プログラムは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳をお勧めします。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。