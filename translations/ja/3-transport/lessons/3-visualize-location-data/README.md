<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-25T00:57:43+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "ja"
}
-->
# 位置データの可視化

![このレッスンの概要を示すスケッチノート](../../../../../translated_images/ja/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> スケッチノート作成者：[Nitya Narasimhan](https://github.com/nitya)。画像をクリックすると拡大表示されます。

このビデオでは、Azure MapsとIoTの概要を説明します。このレッスンで取り上げるサービスです。

[![Azure Maps - Microsoft Azureのエンタープライズ位置情報プラットフォーム](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 上の画像をクリックしてビデオを視聴してください

## 講義前のクイズ

[講義前のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## はじめに

前回のレッスンでは、センサーからGPSデータを取得し、サーバーレスコードを使用してクラウドのストレージコンテナに保存する方法を学びました。今回は、そのポイントをAzureマップ上で可視化する方法を学びます。ウェブページ上でマップを作成し、GeoJSONデータ形式について学び、それを使用してキャプチャしたGPSポイントをマップ上にプロットする方法を学びます。

このレッスンでは以下を取り上げます：

* [データ可視化とは](../../../../../3-transport/lessons/3-visualize-location-data)
* [マップサービス](../../../../../3-transport/lessons/3-visualize-location-data)
* [Azure Mapsリソースの作成](../../../../../3-transport/lessons/3-visualize-location-data)
* [ウェブページにマップを表示する](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON形式](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSONを使用してGPSデータをマップにプロットする](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 このレッスンでは少量のHTMLとJavaScriptを使用します。HTMLとJavaScriptを使用したウェブ開発について詳しく学びたい場合は、[Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners)をチェックしてください。

## データ可視化とは

データ可視化とは、その名の通り、データを人間が理解しやすい形で視覚化することです。通常はチャートやグラフと関連付けられますが、データを図式的に表現することで、人間がデータをよりよく理解し、意思決定を助ける方法全般を指します。

簡単な例を挙げると、農場プロジェクトでは土壌の湿度データをキャプチャしました。2021年6月1日に毎時キャプチャされた土壌湿度データの表は以下のようになります：

| 日付             | 測定値 |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

人間にとって、このデータを理解するのは難しいです。数字の壁でしかありません。このデータを視覚化する最初のステップとして、折れ線グラフにプロットすることができます：

![上記データの折れ線グラフ](../../../../../translated_images/ja/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

さらに、土壌湿度が450に達した時点で自動給水システムが作動したことを示す線を追加することで、グラフを改善できます：

![土壌湿度の折れ線グラフと450のライン](../../../../../translated_images/ja/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

このグラフは、土壌湿度レベルだけでなく、給水システムが作動したポイントも迅速に示しています。

チャートはデータを視覚化する唯一のツールではありません。天気を追跡するIoTデバイスは、ウェブアプリやモバイルアプリを使用して、曇りの日には雲のシンボル、雨の日には雨雲のシンボルなど、天気の状況を視覚化することができます。データを視覚化する方法は非常に多く、真面目なものから楽しいものまで様々です。

✅ データが視覚化されている方法について考えてみてください。どの方法が最も明確で、最も迅速に意思決定を可能にしましたか？

最良の視覚化は、人間が迅速に意思決定できるようにするものです。例えば、産業機械のすべての読み取り値を示すゲージの壁は処理が難しいですが、何か問題が発生したときに赤いライトが点滅することで、人間は迅速に意思決定を行うことができます。時には、最良の視覚化は点滅するライトかもしれません！

GPSデータを扱う場合、最も明確な視覚化方法はデータを地図上にプロットすることです。例えば、配送トラックを示す地図は、処理工場の作業員がトラックが到着する時間を確認するのに役立ちます。この地図が現在のトラックの位置だけでなく、トラックの内容物の情報も示している場合、工場の作業員は計画を立てることができます。例えば、冷蔵トラックが近くにあることがわかれば、冷蔵庫のスペースを準備することができます。

## マップサービス

地図を扱うことは興味深い課題であり、Bing Maps、Leaflet、Open Street Maps、Google Mapsなど、多くの選択肢があります。このレッスンでは、[Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn)について学び、GPSデータを表示する方法を学びます。

![Azure Mapsのロゴ](../../../../../translated_images/ja/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Mapsは「最新の地図データを使用して、ウェブおよびモバイルアプリケーションに地理的コンテキストを提供する地理空間サービスとSDKのコレクション」です。開発者は、美しいインタラクティブな地図を作成するためのツールを提供され、推奨される交通ルート、交通事故情報、屋内ナビゲーション、検索機能、標高情報、天気サービスなどを提供することができます。

✅ [マッピングコードサンプル](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)を試してみてください

地図は空白のキャンバス、タイル、衛星画像、道路が重ねられた衛星画像、さまざまな種類のグレースケール地図、標高を示す陰影付き地図、夜間表示地図、高コントラスト地図として表示できます。[Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn)と統合することで、地図にリアルタイムの更新を追加することができます。地図がピンチ、ドラッグ、クリックなどのイベントに反応するようにするためのさまざまなコントロールを有効にすることで、地図の動作と外観を制御できます。地図の外観を制御するために、バブル、線、ポリゴン、ヒートマップなどのレイヤーを追加することができます。どのスタイルの地図を実装するかは、選択するSDKによります。

Azure Maps APIには、[REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest)、[Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn)、またはモバイルアプリを構築する場合は[Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android)を利用してアクセスできます。

このレッスンでは、Web SDKを使用して地図を描画し、センサーのGPS位置の経路を表示します。

## Azure Mapsリソースの作成

最初のステップはAzure Mapsアカウントを作成することです。

### タスク - Azure Mapsリソースを作成する

1. ターミナルまたはコマンドプロンプトから以下のコマンドを実行して、`gps-sensor`リソースグループにAzure Mapsリソースを作成します：

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    これにより、`gps-sensor`という名前のAzure Mapsリソースが作成されます。使用されるティアは`S1`で、有料ティアですが、無料で利用できるコール数が十分にあります。

    > 💁 Azure Mapsの使用コストについては、[Azure Maps料金ページ](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn)を確認してください。

1. マップリソースのAPIキーが必要です。以下のコマンドを使用してこのキーを取得してください：

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    `PrimaryKey`の値をコピーしてください。

## ウェブページにマップを表示する

次のステップは、ウェブページにマップを表示することです。小規模なウェブアプリでは、1つの`html`ファイルを使用しますが、実際のプロダクション環境やチーム環境では、ウェブアプリにはもっと多くの要素が含まれる可能性があります。

### タスク - ウェブページにマップを表示する

1. ローカルコンピュータの任意のフォルダに`index.html`という名前のファイルを作成します。マップを保持するHTMLマークアップを追加してください：

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    マップは`myMap`という`div`内にロードされます。いくつかのスタイルを使用してページの幅と高さを占めるようにします。

    > 🎓 `div`はウェブページのセクションで、名前を付けたりスタイルを適用したりできます。

1. 開始`<head>`タグの下に、マップ表示を制御する外部スタイルシートと、その動作を管理するWeb SDKの外部スクリプトを追加してください：

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    このスタイルシートにはマップの外観設定が含まれており、スクリプトファイルにはマップをロードするコードが含まれています。このコードを追加することは、C++のヘッダーファイルを含めたり、Pythonモジュールをインポートしたりするのと似ています。

1. そのスクリプトの下に、マップを起動するスクリプトブロックを追加してください。

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    `<subscription_key>`をAzure MapsアカウントのAPIキーに置き換えてください。

    `index.html`ページをウェブブラウザで開くと、シアトル地域にフォーカスしたマップが表示されるはずです。

    ![アメリカ合衆国ワシントン州の都市シアトルを示す地図](../../../../../translated_images/ja/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ ズームや中心座標のパラメータを変更してマップ表示を試してみてください。データの緯度と経度に対応する異なる座標を追加してマップを再中心化することができます。

> 💁 ローカルでウェブアプリを操作するより良い方法は、[http-server](https://www.npmjs.com/package/http-server)をインストールすることです。[node.js](https://nodejs.org/)と[npm](https://www.npmjs.com/)をインストールする必要があります。これらのツールをインストールした後、`index.html`ファイルの場所に移動して`http-server`と入力してください。ウェブアプリはローカルウェブサーバー[http://127.0.0.1:8080/](http://127.0.0.1:8080/)で開きます。

## GeoJSON形式

ウェブアプリがマップを表示するようになったら、ストレージアカウントからGPSデータを抽出し、マップ上にマーカーのレイヤーとして表示する必要があります。その前に、Azure Mapsで必要な[GeoJSON](https://wikipedia.org/wiki/GeoJSON)形式について見てみましょう。

[GeoJSON](https://geojson.org/)は、地理的データを扱うために設計された特別なフォーマットを持つオープンスタンダードのJSON仕様です。[geojson.io](https://geojson.io)を使用してサンプルデータをテストすることで学ぶことができ、GeoJSONファイルをデバッグするための便利なツールでもあります。

サンプルGeoJSONデータは以下のようになります：

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

特に注目すべきは、データが`FeatureCollection`内の`Feature`としてネストされている方法です。その中に`geometry`があり、`coordinates`が緯度と経度を示しています。

✅ GeoJSONを構築する際には、オブジェクト内の`latitude`と`longitude`の順序に注意してください。順序が正しくないとポイントが正しい場所に表示されません！GeoJSONではポイントのデータを`lon,lat`の順序で期待しており、`lat,lon`ではありません。

`Geometry`には異なるタイプがあり、単一のポイントやポリゴンなどがあります。この例では、2つの座標（経度と緯度）が指定されたポイントです。
✅ Azure Mapsは標準的なGeoJSONをサポートしており、円やその他のジオメトリを描画する機能を含む[拡張機能](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn)も提供しています。

## GeoJSONを使用してGPSデータを地図上にプロットする

前のレッスンで構築したストレージからデータを利用する準備が整いました。復習すると、このデータはBlobストレージ内の複数のファイルとして保存されています。そのため、ファイルを取得して解析し、Azure Mapsがデータを使用できるようにする必要があります。

### タスク - ストレージをウェブページからアクセス可能に設定する

ストレージにデータを取得するためのリクエストを送信すると、ブラウザのコンソールにエラーが表示されるかもしれません。これは、外部のウェブアプリがデータを読み取れるようにするために、このストレージで[CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS)の権限を設定する必要があるためです。

> 🎓 CORSは「クロスオリジンリソース共有」を意味し、通常はセキュリティ上の理由からAzureで明示的に設定する必要があります。これにより、予期しないサイトがデータにアクセスするのを防ぐことができます。

1. 以下のコマンドを実行してCORSを有効にします：

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    `<storage_name>`をストレージアカウントの名前に置き換えてください。`<key1>`をストレージアカウントのアカウントキーに置き換えてください。

    このコマンドは、任意のウェブサイト（ワイルドカード`*`は任意を意味します）がストレージアカウントからデータを取得するための*GET*リクエストを送信できるようにします。`--services b`は、この設定をBlobにのみ適用することを意味します。

### タスク - ストレージからGPSデータを読み込む

1. `init`関数の内容全体を以下のコードに置き換えてください：

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    `<storage_name>`をストレージアカウントの名前に置き換えてください。`<subscription_key>`をAzure MapsアカウントのAPIキーに置き換えてください。

    ここではいくつかの処理が行われています。まず、コードはストレージアカウント名を使用して構築されたURLエンドポイントを介してBlobコンテナからGPSデータを取得します。このURLは`gps-data`からデータを取得し、リソースタイプがコンテナであることを示す`restype=container`を含み、すべてのBlobに関する情報をリストします。このリストはBlob自体を返すのではなく、Blobデータを読み込むために使用できるURLを返します。

    > 💁 このURLをブラウザに入力すると、コンテナ内のすべてのBlobの詳細を確認できます。各項目には`Url`プロパティがあり、ブラウザでBlobの内容を確認するために使用できます。

    このコードは次に各Blobを読み込み、次に作成する`loadJSON`関数を呼び出します。その後、地図コントロールを作成し、`ready`イベントにコードを追加します。このイベントは地図がウェブページに表示されたときに呼び出されます。

    `ready`イベントはAzure Mapsのデータソースを作成します。これは後でGeoJSONデータで埋められるコンテナです。このデータソースは次にバブルレイヤーを作成するために使用されます。バブルレイヤーは、GeoJSON内の各ポイントを中心とした地図上の円のセットです。

1. `init`関数の下に、`loadJSON`関数をスクリプトブロックに追加してください：

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    この関数は、フェッチルーチンによって呼び出され、JSONデータを解析して、経度と緯度の座標としてGeoJSONとして読み取れるように変換します。
    解析後、データはGeoJSONの`Feature`として設定されます。地図が初期化され、データがプロットしている経路の周りに小さなバブルが表示されます：

1. HTMLページをブラウザで読み込んでください。地図が読み込まれ、ストレージからすべてのGPSデータが読み込まれ、地図上にプロットされます。

    ![シアトル近郊のセントエドワード州立公園の地図。公園の端を囲む経路に沿って円が表示されている](../../../../../translated_images/ja/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 このコードは[code](../../../../../3-transport/lessons/3-visualize-location-data/code)フォルダーにあります。

---

## 🚀 チャレンジ

地図上に静的なデータをマーカーとして表示するのは便利ですが、このウェブアプリを拡張してアニメーションを追加し、タイムスタンプ付きのJSONファイルを使用してマーカーの経路を時間経過とともに表示できるようにしてみてください。[いくつかのサンプル](https://azuremapscodesamples.azurewebsites.net/)で地図内でのアニメーションの使用方法を確認できます。

## 講義後のクイズ

[講義後のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## 復習と自己学習

Azure MapsはIoTデバイスを扱う際に特に役立ちます。

* [Microsoft DocsのAzure Mapsドキュメント](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn)でその用途について調査してください。
* [Microsoft LearnのAzure Mapsを使用した最初のルート検索アプリを作成する自己学習モジュール](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn)で地図作成とウェイポイントの知識を深めてください。

## 課題

[アプリをデプロイする](assignment.md)

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確さが含まれる可能性があることをご承知おきください。元の言語で記載された原文が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の利用に起因する誤解や誤認について、当社は一切の責任を負いません。