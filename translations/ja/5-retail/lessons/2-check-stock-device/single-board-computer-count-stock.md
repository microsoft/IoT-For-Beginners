<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-24T21:13:09+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "ja"
}
-->
# IoTデバイスで在庫をカウントする - 仮想IoTハードウェアとRaspberry Pi

予測結果とそのバウンディングボックスを組み合わせることで、画像内の在庫をカウントすることができます。

## バウンディングボックスを表示する

デバッグの一環として、バウンディングボックスをコンソールに出力するだけでなく、画像に描画することもできます。画像はキャプチャ時にディスクに保存されます。

### タスク - バウンディングボックスを出力する

1. VS Codeで`stock-counter`プロジェクトを開き、仮想IoTデバイスを使用している場合は仮想環境を有効化してください。

1. `for`ループ内の`print`文を以下のように変更して、バウンディングボックスをコンソールに出力してください：

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. カメラを棚の在庫に向けてアプリを実行してください。バウンディングボックスがコンソールに出力され、左、上、幅、高さの値が0-1の範囲で表示されます。

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### タスク - 画像にバウンディングボックスを描画する

1. Pipパッケージ[Pillow](https://pypi.org/project/Pillow/)を使用して画像に描画できます。以下のコマンドでインストールしてください：

    ```sh
    pip3 install pillow
    ```

    仮想IoTデバイスを使用している場合は、仮想環境を有効化した状態でこのコマンドを実行してください。

1. `app.py`ファイルの冒頭に以下のインポート文を追加してください：

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    これにより、画像編集に必要なコードがインポートされます。

1. `app.py`ファイルの末尾に以下のコードを追加してください：

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    このコードは、以前保存された画像を編集用に開きます。その後、予測結果をループしてバウンディングボックスを取得し、0-1の値を使用して右下の座標を計算します。これらの値は画像の寸法に基づいて画像座標に変換されます。例えば、幅600ピクセルの画像で左の値が0.5の場合、300に変換されます（0.5 x 600 = 300）。

    各バウンディングボックスは赤い線で画像に描画されます。最後に編集された画像が保存され、元の画像を上書きします。

1. カメラを棚の在庫に向けてアプリを実行してください。VS Codeのエクスプローラーで`image.jpg`ファイルが表示され、バウンディングボックスを確認できます。

    ![4つのトマトペースト缶にバウンディングボックスが描かれている](../../../../../translated_images/ja/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## 在庫をカウントする

上記の画像では、バウンディングボックスが少し重なっています。もしこの重なりが大きい場合、バウンディングボックスが同じオブジェクトを示している可能性があります。正確にオブジェクトをカウントするには、重なりが大きいボックスを無視する必要があります。

### タスク - 重なりを無視して在庫をカウントする

1. Pipパッケージ[Shapely](https://pypi.org/project/Shapely/)を使用して交差を計算できます。Raspberry Piを使用している場合は、まずライブラリ依存関係をインストールしてください：

    ```sh
    sudo apt install libgeos-dev
    ```

1. Shapely Pipパッケージをインストールしてください：

    ```sh
    pip3 install shapely
    ```

    仮想IoTデバイスを使用している場合は、仮想環境を有効化した状態でこのコマンドを実行してください。

1. `app.py`ファイルの冒頭に以下のインポート文を追加してください：

    ```python
    from shapely.geometry import Polygon
    ```

    これにより、重なりを計算するためのポリゴンを作成するコードがインポートされます。

1. バウンディングボックスを描画するコードの上に以下のコードを追加してください：

    ```python
    overlap_threshold = 0.20
    ```

    これにより、バウンディングボックスが同じオブジェクトと見なされる前の許容重なり率が定義されます。0.20は20%の重なりを意味します。

1. Shapelyを使用して重なりを計算するには、バウンディングボックスをShapelyポリゴンに変換する必要があります。以下の関数を追加してください：

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    この関数は予測結果のバウンディングボックスを使用してポリゴンを作成します。

1. 重なりを削除するロジックは、すべてのバウンディングボックスを比較し、予測結果のペアが許容重なり率を超える場合、1つの予測結果を削除することです。以下のコードはこれを実現します：

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    重なりはShapelyの`Polygon.intersection`メソッドを使用して計算され、重なり部分のポリゴンが返されます。このポリゴンの面積が計算されます。この重なり閾値は絶対値ではなく、最小のバウンディングボックスの割合として計算されます。重なりがこの割合を超える場合、予測結果は削除対象としてマークされます。

    削除対象としてマークされた予測結果は再度チェックする必要がないため、内側のループは次の予測結果をチェックするために終了します。リストを反復処理中に項目を削除することはできないため、重なりが閾値を超えるバウンディングボックスは`to_delete`リストに追加され、最後に削除されます。

    最後に在庫数がコンソールに出力されます。この情報は、在庫が少ない場合にIoTサービスに通知するために使用できます。このコードはバウンディングボックスを描画する前に実行されるため、生成された画像には重なりのない在庫予測が表示されます。

    > 💁 この方法は非常に単純で、重なりのあるペアの最初の1つを削除するだけです。実際のコードでは、複数のオブジェクト間の重なりを考慮したり、1つのバウンディングボックスが別のバウンディングボックスに含まれている場合を考慮するなど、より高度なロジックを追加する必要があります。

1. カメラを棚の在庫に向けてアプリを実行してください。出力には閾値を超える重なりのないバウンディングボックスの数が表示されます。`overlap_threshold`値を調整して、予測結果が無視される様子を確認してください。

> 💁 このコードは[code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi)または[code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device)フォルダーにあります。

😀 あなたの在庫カウンタープログラムは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があることをご承知おきください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳をお勧めします。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。