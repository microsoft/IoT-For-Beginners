<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-24T21:47:56+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ja"
}
-->
# IoT Edgeベースの画像分類器を使用して画像を分類する - 仮想IoTハードウェアとRaspberry Pi

このレッスンのこの部分では、IoT Edgeデバイス上で動作する画像分類器を使用します。

## IoT Edge分類器を使用する

IoTデバイスは、IoT Edge画像分類器を使用するようにリダイレクトできます。画像分類器のURLは `http://<IP address or name>/image` であり、`<IP address or name>` をIoT Edgeを実行しているコンピュータのIPアドレスまたはホスト名に置き換えます。

Custom VisionのPythonライブラリはクラウドホストモデルでのみ動作し、IoT Edgeでホストされているモデルでは動作しません。そのため、REST APIを使用して分類器を呼び出す必要があります。

### タスク - IoT Edge分類器を使用する

1. VS Codeで`fruit-quality-detector`プロジェクトを開きます（まだ開いていない場合）。仮想IoTデバイスを使用している場合は、仮想環境が有効になっていることを確認してください。

1. `app.py`ファイルを開き、`azure.cognitiveservices.vision.customvision.prediction`と`msrest.authentication`からのインポート文を削除します。

1. ファイルの先頭に以下のインポートを追加します：

    ```python
    import requests
    ```

1. 画像がファイルに保存された後のコード、`image_file.write(image.read())`からファイルの最後までのコードをすべて削除します。

1. ファイルの最後に以下のコードを追加します：

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    `<URL>` を分類器のURLに置き換えてください。

    このコードは分類器に対してREST POSTリクエストを行い、リクエストの本文として画像を送信します。結果はJSON形式で返され、それをデコードして確率を出力します。

1. カメラを果物に向けるか、適切な画像セットを使用するか、仮想IoTハードウェアを使用している場合はウェブカメラに果物が見える状態でコードを実行してください。コンソールに出力が表示されます：

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 このコードは [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) または [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) フォルダーで見つけることができます。

😀 あなたの果物品質分類プログラムは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。