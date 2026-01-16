<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-24T21:11:45+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ja"
}
-->
# IoTデバイスで在庫をカウントする - Wio Terminal

予測結果とそのバウンディングボックスを組み合わせることで、画像内の在庫をカウントすることができます。

## 在庫をカウントする

![各缶の周りにバウンディングボックスが描かれたトマトペーストの缶4つ](../../../../../translated_images/ja/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

上記の画像では、バウンディングボックスが少し重なっています。この重なりがもっと大きい場合、バウンディングボックスが同じオブジェクトを示している可能性があります。オブジェクトを正確にカウントするには、重なりが大きいボックスを無視する必要があります。

### タスク - 重なりを無視して在庫をカウントする

1. `stock-counter`プロジェクトを開いていない場合は、開いてください。

1. `processPredictions`関数の上に、以下のコードを追加してください：

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    これは、バウンディングボックスが同じオブジェクトと見なされる前に許容される重なりの割合を定義します。0.20は20%の重なりを定義します。

1. その下で、`processPredictions`関数の上に、2つの矩形間の重なりを計算するコードを追加してください：

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    このコードは、画像上のポイントを格納するための`Point`構造体を定義し、矩形を左上と右下の座標で定義するための`Rect`構造体を定義します。そして、左上と右下の座標から矩形の面積を計算する`area`関数を定義します。

    次に、2つの矩形の重なり面積を計算する`overlappingArea`関数を定義します。重なりがない場合は0を返します。

1. `overlappingArea`関数の下に、バウンディングボックスを`Rect`に変換する関数を宣言してください：

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    これは、オブジェクト検出器からの予測を受け取り、バウンディングボックスを抽出し、その値を使用して矩形を定義します。右側は左側に幅を加えて計算されます。下側は上側に高さを加えて計算されます。

1. 予測結果を互いに比較し、2つの予測結果が閾値以上の重なりを持つ場合、そのうちの1つを削除する必要があります。重なりの閾値は割合であるため、最小のバウンディングボックスのサイズに掛けて、画像全体の割合ではなくバウンディングボックスの割合を超えているかどうかを確認する必要があります。まず、`processPredictions`関数の内容を削除してください。

1. 空の`processPredictions`関数に以下を追加してください：

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    このコードは、重ならない予測結果を格納するベクターを宣言します。そして、すべての予測結果をループし、バウンディングボックスから`Rect`を作成します。

    次に、このコードは残りの予測結果をループします。現在の予測結果の次のものから開始します。これにより、予測結果が複数回比較されることを防ぎます。例えば、1と2が比較された後、2を1と比較する必要はなく、3、4などと比較するだけで済みます。

    各予測結果のペアについて、重なり面積が計算されます。これが最小のバウンディングボックスの面積に対して閾値割合を超える場合、予測結果は通過しないとマークされます。すべての重なりを比較した後、予測結果がチェックを通過した場合、それは`passed_predictions`コレクションに追加されます。

    > 💁 これは重なりを削除する非常に単純な方法であり、重なりペアの最初のものを削除するだけです。実際のコードでは、複数のオブジェクト間の重なりを考慮したり、1つのバウンディングボックスが別のバウンディングボックスに含まれている場合を考慮したりするなど、より多くのロジックを追加する必要があります。

1. その後、通過した予測結果の詳細をシリアルモニターに送信するコードを追加してください：

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    このコードは、通過した予測結果をループし、その詳細をシリアルモニターに出力します。

1. その下に、カウントされたアイテムの数をシリアルモニターに出力するコードを追加してください：

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    これにより、在庫レベルが低い場合にIoTサービスに通知を送ることができます。

1. コードをアップロードして実行してください。カメラを棚の上のオブジェクトに向け、Cボタンを押してください。`overlap_threshold`値を調整して、予測結果が無視される様子を確認してください。

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 このコードは[code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal)フォルダーにあります。

😀 あなたの在庫カウンタープログラムは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。