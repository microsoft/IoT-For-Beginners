<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-24T21:14:19+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "ja"
}
-->
# IoTデバイス（Wio Terminal）からオブジェクト検出器を呼び出す

オブジェクト検出器が公開されたら、IoTデバイスから使用できるようになります。

## 画像分類プロジェクトをコピーする

ストック検出器の大部分は、以前のレッスンで作成した画像分類器と同じです。

### タスク - 画像分類プロジェクトをコピーする

1. [製造プロジェクトのレッスン2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera)の手順に従って、ArduCamをWio Terminalに接続します。

    また、カメラを固定する方法を検討してください。例えば、ケーブルを箱や缶の上に吊るしたり、両面テープでカメラを箱に固定したりする方法があります。

1. PlatformIOを使用して新しいWio Terminalプロジェクトを作成します。このプロジェクトを`stock-counter`と名付けます。

1. [製造プロジェクトのレッスン2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)の手順を再現して、カメラから画像をキャプチャします。

1. [製造プロジェクトのレッスン2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)の手順を再現して、画像分類器を呼び出します。このコードの大部分は、オブジェクトを検出するために再利用されます。

## コードを分類器から画像検出器に変更する

画像を分類するために使用したコードは、オブジェクトを検出するコードと非常に似ています。主な違いは、Custom Visionから取得した呼び出し先のURLと、その呼び出し結果です。

### タスク - コードを分類器から画像検出器に変更する

1. `main.cpp`ファイルの先頭に次のインクルードディレクティブを追加します：

    ```cpp
    #include <vector>
    ```

1. `classifyImage`関数の名前を`detectStock`に変更します。関数名と`buttonPressed`関数内での呼び出しの両方を変更してください。

1. `detectStock`関数の上に、低い確率の検出を除外するためのしきい値を宣言します：

    ```cpp
    const float threshold = 0.3f;
    ```

    画像分類器はタグごとに1つの結果しか返しませんが、オブジェクト検出器は複数の結果を返します。そのため、確率が低いものを除外する必要があります。

1. `detectStock`関数の上に、予測を処理する関数を宣言します：

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    これは予測のリストを受け取り、それをシリアルモニターに出力します。

1. `detectStock`関数内で、予測をループする`for`ループの内容を次のコードに置き換えます：

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    これは予測をループし、確率をしきい値と比較します。しきい値を超える確率を持つすべての予測が`list`に追加され、`processPredictions`関数に渡されます。

1. コードをアップロードして実行します。カメラを棚の上のオブジェクトに向け、Cボタンを押してください。シリアルモニターに出力が表示されます：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 画像に適した値にするために、`threshold`を調整する必要があるかもしれません。

    撮影された画像とこれらの値は、Custom Visionの**Predictions**タブで確認できます。

    ![棚の上にある4つのトマトペースト缶と、それぞれの検出確率（35.8%、33.5%、25.7%、16.6%）](../../../../../translated_images/ja/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 このコードは[code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal)フォルダーで確認できます。

😀 ストックカウンタープログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。