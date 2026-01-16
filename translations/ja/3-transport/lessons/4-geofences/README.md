<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-25T00:39:46+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "ja"
}
-->
# ジオフェンス

![このレッスンの概要を示すスケッチノート](../../../../../translated_images/ja/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> スケッチノート作成者：[Nitya Narasimhan](https://github.com/nitya)。画像をクリックすると拡大表示されます。

このビデオでは、ジオフェンスの概要とAzure Mapsでの使用方法について説明します。このレッスンで扱うトピックは以下の通りです：

[![Microsoft Developer IoTショーのAzure Mapsでのジオフェンシング](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 上の画像をクリックしてビデオを視聴してください

## レクチャー前のクイズ

[レクチャー前のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## はじめに

過去3回のレッスンでは、IoTを使用して農場から加工拠点へ向かうトラックの位置を特定しました。GPSデータを収集し、クラウドに送信して保存し、地図上で可視化しました。次のステップとして、トラックが加工拠点に到着する直前にアラートを受け取ることで、荷降ろしに必要なクルーがフォークリフトやその他の設備を準備できるようにします。これにより迅速な荷降ろしが可能となり、トラックやドライバーの待機時間を削減できます。

このレッスンでは、ジオフェンスについて学びます。ジオフェンスは、加工拠点から2km以内の範囲など、特定の地理的領域を定義するものです。GPS座標がジオフェンス内か外かをテストする方法を学び、GPSセンサーが特定のエリアに到着したか離れたかを確認できるようになります。

このレッスンで学ぶ内容は以下の通りです：

* [ジオフェンスとは何か](../../../../../3-transport/lessons/4-geofences)
* [ジオフェンスの定義](../../../../../3-transport/lessons/4-geofences)
* [ジオフェンスに対するポイントのテスト](../../../../../3-transport/lessons/4-geofences)
* [サーバーレスコードでのジオフェンスの使用](../../../../../3-transport/lessons/4-geofences)

> 🗑 このプロジェクトの最後のレッスンです。このレッスンと課題を完了した後は、クラウドサービスをクリーンアップすることを忘れないでください。課題を完了するためにサービスが必要なので、まず課題を完了してください。
>
> 必要に応じて、[プロジェクトのクリーンアップガイド](../../../clean-up.md)を参照してください。

## ジオフェンスとは何か

ジオフェンスは、現実世界の地理的領域に対する仮想的な境界線です。ジオフェンスは、建物周辺100mの円のように点と半径で定義される円形や、学校区域、市境界、大学やオフィスキャンパスのようなポリゴンで構成されることがあります。

![Microsoftの会社ストア周辺の円形ジオフェンスと、Microsoft西キャンパス周辺のポリゴンジオフェンスの例](../../../../../translated_images/ja/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 すでにジオフェンスを知らずに使用しているかもしれません。iOSのリマインダーアプリやGoogle Keepで位置情報に基づいてリマインダーを設定したことがある場合、それはジオフェンスを使用しています。これらのアプリは指定された位置情報に基づいてジオフェンスを設定し、スマートフォンがジオフェンス内に入ると通知を送ります。

ジオフェンスを使用して車両がジオフェンス内か外かを知る理由は多岐にわたります：

* 荷降ろしの準備 - 車両が現場に到着した通知を受け取ることで、クルーが荷降ろしの準備を整え、車両の待機時間を短縮できます。これにより、ドライバーは1日により多くの配送を行うことが可能になります。
* 税務コンプライアンス - ニュージーランドなどの国では、ディーゼル車両の重量に基づいて公共道路での走行距離に応じた道路税を課しています。ジオフェンスを使用することで、農場や伐採地などの私有道路ではなく公共道路での走行距離を追跡できます。
* 盗難の監視 - 車両が農場内に留まるべきである場合、ジオフェンスを離れると盗難の可能性があります。
* 場所のコンプライアンス - 作業現場、農場、工場の一部は特定の車両に立ち入り禁止区域である場合があります。例えば、人工肥料や農薬を運ぶ車両を有機農産物を栽培している畑から遠ざける必要がある場合などです。ジオフェンスに侵入すると、車両がコンプライアンス外となり、ドライバーに通知されます。

✅ ジオフェンスの他の用途を考えてみてください。

前回のレッスンでGPSデータを可視化するために使用したAzure Mapsでは、ジオフェンスを定義し、ポイントがジオフェンス内か外かをテストすることができます。

## ジオフェンスの定義

ジオフェンスは、前回のレッスンで地図に追加したポイントと同じくGeoJSONを使用して定義されます。この場合、`Point`値の`FeatureCollection`ではなく、`Polygon`を含む`FeatureCollection`になります。

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

ポリゴンの各ポイントは配列内の経度と緯度のペアとして定義され、これらのポイントは`coordinates`として設定された配列内に含まれます。前回のレッスンでの`Point`では、`coordinates`は緯度と経度の2つの値を含む配列でしたが、`Polygon`の場合は経度と緯度の2つの値を含む配列の配列になります。

> 💁 GeoJSONではポイントに`緯度, 経度`ではなく`経度, 緯度`を使用することを忘れないでください。

ポリゴンの座標配列は、ポリゴンのポイント数より1つ多いエントリを常に持ち、最後のエントリは最初のエントリと同じでポリゴンを閉じます。例えば、長方形の場合は5つのポイントになります。

![座標を持つ長方形](../../../../../translated_images/ja/polygon-points.302193da381cb415.webp)

上の画像では、長方形があります。ポリゴン座標は左上の47,-122から始まり、右に移動して47,-121、下に移動して46,-121、左に移動して46,-122、そして開始点の47,-122に戻ります。これにより、ポリゴンには5つのポイント（左上、右上、右下、左下、そして左上で閉じる）が含まれます。

✅ 自宅や学校周辺にGeoJSONポリゴンを作成してみてください。[GeoJSON.io](https://geojson.io/)のようなツールを使用すると便利です。

### タスク - ジオフェンスの定義

Azure Mapsでジオフェンスを使用するには、まずAzure Mapsアカウントにアップロードする必要があります。アップロード後、ジオフェンスをテストするために使用する一意のIDを取得できます。Azure Mapsにジオフェンスをアップロードするには、マップのWeb APIを使用します。[curl](https://curl.se)というツールを使用してAzure Maps Web APIを呼び出すことができます。

> 🎓 CurlはWebエンドポイントに対してリクエストを行うためのコマンドラインツールです

1. Linux、macOS、またはWindows 10の最近のバージョンを使用している場合、curlはすでにインストールされている可能性があります。ターミナルまたはコマンドラインで以下を実行して確認してください：

    ```sh
    curl --version
    ```

    curlのバージョン情報が表示されない場合は、[curlダウンロードページ](https://curl.se/download.html)からインストールする必要があります。

    > 💁 Postmanに慣れている場合は、代わりにそれを使用することもできます。

1. ポリゴンを含むGeoJSONファイルを作成します。GPSセンサーを使用してこれをテストするため、現在の位置周辺にポリゴンを作成してください。上記のGeoJSON例を手動で編集するか、[GeoJSON.io](https://geojson.io/)のようなツールを使用して作成できます。

    GeoJSONには`FeatureCollection`が含まれている必要があり、その中に`geometry`が`Polygon`タイプの`Feature`が含まれます。

    また、`geometry`要素と同じレベルに`properties`要素を追加し、その中に`geometryId`を含める必要があります：

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    [GeoJSON.io](https://geojson.io/)を使用する場合、ダウンロードしたJSONファイルを編集するか、アプリ内のJSONエディタでこの項目を空の`properties`要素に手動で追加する必要があります。

    この`geometryId`はこのファイル内で一意である必要があります。同じGeoJSONファイル内で複数の`Feature`として複数のジオフェンスをアップロードできますが、それぞれ異なる`geometryId`を持つ必要があります。異なるファイルから異なる時間にアップロードされた場合、ポリゴンは同じ`geometryId`を持つことができます。

1. このファイルを`geofence.json`として保存し、ターミナルまたはコンソールで保存場所に移動します。

1. 以下のcurlコマンドを実行してGeoFenceを作成します：

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    URL内の`<subscription_key>`をAzure MapsアカウントのAPIキーに置き換えてください。

    このURLは`https://atlas.microsoft.com/mapData/upload` APIを介してマップデータをアップロードするために使用されます。この呼び出しには、使用するAzure Maps APIを指定する`api-version`パラメータが含まれています。これは、APIが時間とともに変更されても後方互換性を維持するためです。アップロードされるデータ形式は`geojson`に設定されています。

    このPOSTリクエストはアップロードAPIを実行し、`location`というヘッダーを含むレスポンスヘッダーのリストを返します：

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Webエンドポイントを呼び出す際、`?`の後に`key=value`形式でキーと値のペアを追加し、`&`でキーと値のペアを区切ることでパラメータを呼び出しに渡すことができます。

1. Azure Mapsはこれをすぐに処理しないため、アップロードリクエストが完了したかどうかを確認する必要があります。`location`ヘッダーで指定されたURLを使用してステータスを確認します。`location` URLの末尾に`&subscription-key=<subscription_key>`を追加し、`<subscription_key>`をAzure MapsアカウントのAPIキーに置き換えてください。以下のコマンドを実行します：

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    `<location>`を`location`ヘッダーの値に置き換え、`<subscription_key>`をAzure MapsアカウントのAPIキーに置き換えてください。

1. レスポンス内の`status`の値を確認します。`Succeeded`でない場合は、1分待って再試行してください。

1. ステータスが`Succeeded`として返されたら、レスポンス内の`resourceLocation`を確認します。これにはGeoJSONオブジェクトの一意のID（UDID）に関する詳細が含まれています。UDIDは`metadata/`の後の値で、`api-version`を含まない部分です。例えば、`resourceLocation`が以下の場合：

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    UDIDは`7c3776eb-da87-4c52-ae83-caadf980323a`となります。

    このUDIDをコピーしておきます。ジオフェンスをテストする際に必要になります。

## ジオフェンスに対するポイントのテスト

ポリゴンがAzure Mapsにアップロードされたら、ポイントがジオフェンス内か外かをテストできます。これを行うには、ジオフェンスのUDIDとテストするポイントの緯度と経度を渡してWeb APIリクエストを行います。

このリクエストを行う際、`searchBuffer`という値を渡すこともできます。これは結果を返す際の精度を指定します。その理由は、GPSが完全に正確ではなく、場合によっては数メートル以上の誤差が生じることがあるためです。デフォルトの検索バッファは50mですが、0mから500mまでの値を設定できます。

API呼び出しから返される結果の一部には、ジオフェンスの境界線に最も近いポイントまでの`distance`が含まれます。この値は、ポイントがジオフェンス外の場合は正の値、ジオフェンス内の場合は負の値となります。この距離が検索バッファより小さい場合、実際の距離がメートル単位で返されます。それ以外の場合、値は999または-999となります。999はポイントが検索バッファを超えてジオフェンス外にあることを意味し、-999はポイントが検索バッファを超えてジオフェンス内にあることを意味します。

![ジオフェンスとその周囲50mの検索バッファ](../../../../../translated_images/ja/search-buffer-and-distance.e6a79af3898183c7.webp)

上の画像では、ジオフェンスには50mの検索バッファがあります。

* ジオフェンスの中心にあるポイントは検索バッファ内に十分収まっており、距離は**-999**です。
* 検索バッファを大きく超えたポイントは距離が**999**です。
* ジオフェンス内で検索バッファ内にあるポイントは、ジオフェンスから6m離れており、距離は**6m**です。
* ジオフェンス外で検索バッファ内にあるポイントは、ジオフェンスから39m離れており、距離は**39m**です。

ジオフェンスの境界線までの距離を知ることは重要であり、車両の位置に基づいて意思決定を行う際には、他の情報（他のGPS測定値、速度、道路データなど）と組み合わせて使用する必要があります。

例えば、車両がジオフェンスの隣を走る道路を走行していることを示すGPS測定値があるとします。単一のGPS値が不正確で、車両がジオフェンス内にあると示されても、車両がアクセスできない場合は無視することができます。

![Microsoftキャンパスを通過する520号線沿いの車両のGPSトレイル。道路沿いのGPS測定値の中に、ジオフェンス内にある1つの不正確な測定値が含まれている](../../../../../translated_images/ja/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.png)
上記の画像では、Microsoftキャンパスの一部にジオフェンスが設定されています。赤い線は520号線を走るトラックを示しており、GPSの読み取り値を示す円が描かれています。ほとんどの読み取り値は正確で520号線上にありますが、1つの不正確な読み取り値がジオフェンス内にあります。この読み取り値が正しいはずがありません。トラックが突然520号線からキャンパス内に入り、再び520号線に戻るような道路は存在しません。このジオフェンスをチェックするコードは、ジオフェンステストの結果を処理する前に、以前の読み取り値を考慮する必要があります。

✅ GPS読み取り値が正しいと判断するために、どのような追加データが必要ですか？

### タスク - ジオフェンスに対してポイントをテストする

1. Web APIクエリのURLを構築することから始めます。フォーマットは以下の通りです：

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    `<subscription_key>`をAzure MapsアカウントのAPIキーに置き換えます。

    `<UDID>`を前のタスクで取得したジオフェンスのUDIDに置き換えます。

    `<lat>`と`<lon>`をテストしたい緯度と経度に置き換えます。

    このURLは、GeoJSONを使用して定義されたジオフェンスをクエリするために`https://atlas.microsoft.com/spatial/geofence/json` APIを使用します。APIバージョン`1.0`をターゲットにしています。`deviceId`パラメータは必須で、緯度と経度が取得されたデバイスの名前を指定する必要があります。

    デフォルトの検索バッファは50mで、`searchBuffer=<distance>`という追加パラメータを渡すことで変更できます。`<distance>`には0から500メートルの検索バッファ距離を設定します。

1. curlを使用してこのURLにGETリクエストを送信します：

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 `BadRequest`のレスポンスコードと以下のエラーが返された場合：
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > GeoJSONに`geometryId`を含む`properties`セクションが欠けています。GeoJSONを修正し、上記の手順を繰り返して再アップロードし、新しいUDIDを取得する必要があります。

1. レスポンスには、GeoJSONを使用して作成されたジオフェンス内の各ポリゴンに対応する`geometries`のリストが含まれます。各ジオメトリには、`distance`、`nearestLat`、`nearestLon`という3つの重要なフィールドがあります。

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat`と`nearestLon`は、テスト対象の位置に最も近いジオフェンスの境界上のポイントの緯度と経度です。

    * `distance`は、テスト対象の位置からジオフェンスの境界上の最も近いポイントまでの距離です。負の値はジオフェンス内、正の値は外側を意味します。この値は50（デフォルトの検索バッファ）未満、または999になります。

1. ジオフェンス内外の位置でこれを複数回繰り返します。

## サーバーレスコードからジオフェンスを使用する

これで、Functionsアプリに新しいトリガーを追加して、IoT Hub GPSイベントデータをジオフェンスに対してテストできるようになります。

### コンシューマーグループ

以前のレッスンで学んだように、IoT Hubはハブに受信されたが処理されていないイベントを再生することができます。しかし、複数のトリガーが接続された場合、どのトリガーがどのイベントを処理したかをIoT Hubは認識できません。

その解決策として、複数の独立した接続を定義してイベントを読み取り、それぞれが未読メッセージの再生を管理することができます。これらは*コンシューマーグループ*と呼ばれます。エンドポイントに接続する際に、接続したいコンシューマーグループを指定できます。アプリケーションの各コンポーネントは異なるコンシューマーグループに接続します。

![1つのIoT Hubが3つのコンシューマーグループを使用して同じメッセージを3つの異なるFunctionsアプリに配信する](../../../../../translated_images/ja/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

理論的には、各コンシューマーグループに最大5つのアプリケーションが接続でき、メッセージが到着するとすべてのアプリケーションがメッセージを受信します。ただし、メッセージの重複処理を避け、再起動時にすべてのキューに入ったメッセージが正しく処理されるようにするため、各コンシューマーグループには1つのアプリケーションのみがアクセスするのがベストプラクティスです。例えば、Functionsアプリをローカルで起動し、クラウドでも実行している場合、両方がメッセージを処理し、ストレージアカウントに重複したBlobが保存される可能性があります。

以前のレッスンで作成したIoT Hubトリガーの`function.json`ファイルを確認すると、イベントハブトリガーバインディングセクションにコンシューマーグループが記載されています：

```json
"consumerGroup": "$Default"
```

IoT Hubを作成すると、デフォルトで`$Default`コンシューマーグループが作成されます。追加のトリガーを追加したい場合は、新しいコンシューマーグループを使用してこれを行うことができます。

> 💁 このレッスンでは、GPSデータを保存するために使用したものとは異なる関数を使用してジオフェンスをテストします。これは、コンシューマーグループを使用する方法を示し、コードを分離して読みやすく理解しやすくするためです。実際のアプリケーションでは、これを設計する方法はさまざまです。1つの関数にまとめる、ストレージアカウントのトリガーを使用してジオフェンスをチェックする関数を実行する、または複数の関数を使用するなどです。正しい方法はなく、アプリケーション全体やニーズに依存します。

### タスク - 新しいコンシューマーグループを作成する

1. 以下のコマンドを実行して、IoT Hubに`geofence`という新しいコンシューマーグループを作成します：

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    `<hub_name>`を使用したIoT Hubの名前に置き換えます。

1. IoT Hubのすべてのコンシューマーグループを確認したい場合は、以下のコマンドを実行します：

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    `<hub_name>`を使用したIoT Hubの名前に置き換えます。これにより、すべてのコンシューマーグループが一覧表示されます。

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 前のレッスンでIoT Hubイベントモニターを実行した際、`$Default`コンシューマーグループに接続しました。このため、イベントモニターとイベントトリガーを同時に実行することはできません。両方を実行したい場合は、すべてのFunctionsアプリに他のコンシューマーグループを使用し、イベントモニターには`$Default`を保持します。

### タスク - 新しいIoT Hubトリガーを作成する

1. 前のレッスンで作成した`gps-trigger`関数アプリに新しいIoT Hubイベントトリガーを追加します。この関数を`geofence-trigger`と呼びます。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン5のIoT Hubイベントトリガー作成手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger)を参照してください。

1. `function.json`ファイルでIoT Hub接続文字列を構成します。`local.settings.json`はFunctionsアプリ内のすべてのトリガー間で共有されます。

1. `function.json`ファイルの`consumerGroup`値を新しい`geofence`コンシューマーグループに更新します：

    ```json
    "consumerGroup": "geofence"
    ```

1. このトリガーでAzure Mapsアカウントのサブスクリプションキーを使用する必要があるため、`local.settings.json`ファイルに`MAPS_KEY`という新しいエントリを追加します。

1. Functionsアプリを実行して、メッセージを接続して処理していることを確認します。前のレッスンの`iot-hub-trigger`も実行され、Blobをストレージにアップロードします。

    > BlobストレージにGPS読み取り値が重複しないようにするには、クラウドで実行中のFunctionsアプリを停止できます。これを行うには、以下のコマンドを使用します：
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > `<functions_app_name>`を使用したFunctionsアプリの名前に置き換えます。
    >
    > 後で以下のコマンドを使用して再起動できます：
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > `<functions_app_name>`を使用したFunctionsアプリの名前に置き換えます。

### タスク - トリガーからジオフェンスをテストする

このレッスンの前半で、curlを使用してジオフェンスをクエリし、ポイントが内側か外側かを確認しました。同様のWebリクエストをトリガー内から行うことができます。

1. ジオフェンスをクエリするには、そのUDIDが必要です。`local.settings.json`ファイルに`GEOFENCE_UDID`という新しいエントリを追加して、この値を設定します。

1. 新しい`geofence-trigger`トリガーの`__init__.py`ファイルを開きます。

1. ファイルの先頭に以下のインポートを追加します：

    ```python
    import json
    import os
    import requests
    ```

    `requests`パッケージを使用してWeb API呼び出しを行います。Azure MapsにはPython SDKがないため、Pythonコードから使用するにはWeb API呼び出しを行う必要があります。

1. `main`メソッドの冒頭に以下の2行を追加してMapsサブスクリプションキーを取得します：

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. `for event in events`ループ内で、以下を追加して各イベントから緯度と経度を取得します：

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    このコードは、イベントボディのJSONを辞書に変換し、`gps`フィールドから`lat`と`lon`を抽出します。

1. `requests`を使用する際、curlのように長いURLを構築する代わりに、URL部分だけを使用し、パラメータを辞書として渡すことができます。以下のコードを追加して呼び出すURLを定義し、パラメータを設定します：

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    `params`辞書内の項目は、curlを使用してWeb APIを呼び出した際のキーと値のペアに一致します。

1. 以下のコードを追加してWeb APIを呼び出します：

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    これにより、パラメータを使用してURLを呼び出し、レスポンスオブジェクトを取得します。

1. この下に以下のコードを追加します：

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    このコードは1つのジオメトリを想定し、その単一のジオメトリから距離を抽出します。その後、距離に基づいて異なるメッセージをログに記録します。

1. このコードを実行します。GPS座標がジオフェンス内か外か、50m以内の場合は距離がログ出力に表示されます。このコードを異なるジオフェンスで試し、GPSセンサーの位置に基づいて変化を確認してください（例えば、モバイルWiFiに接続されたセンサーや仮想IoTデバイスの異なる座標を使用）。

1. 準備が整ったら、このコードをクラウドのFunctionsアプリにデプロイします。新しいアプリケーション設定をデプロイするのを忘れないでください。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン5のアプリケーション設定アップロード手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings)を参照してください。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン5のFunctionsアプリデプロイ手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud)を参照してください。

> 💁 このコードは[code/functions](../../../../../3-transport/lessons/4-geofences/code/functions)フォルダーにあります。

---

## 🚀 チャレンジ

このレッスンでは、単一のポリゴンを含むGeoJSONファイルを使用して1つのジオフェンスを追加しました。`properties`セクション内の`geometryId`値が異なる限り、複数のポリゴンを同時にアップロードすることができます。

複数のポリゴンを含むGeoJSONファイルをアップロードし、GPS座標が最も近いポリゴンまたは内側にあるポリゴンを見つけるようにコードを調整してみてください。

## 講義後のクイズ

[講義後のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## 復習と自己学習

* [Wikipediaのジオフェンスページ](https://en.wikipedia.org/wiki/Geo-fence)でジオフェンスとその使用例についてさらに学びましょう。
* [Microsoft Azure Maps Spatial - Get Geofence ドキュメント](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn)でAzure MapsジオフェンスAPIについてさらに学びましょう。
* [Microsoft DocsのAzure Event Hubsの機能と用語 - イベントコンシューマードキュメント](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers)でコンシューマーグループについてさらに学びましょう。

## 課題

[Twilioを使用して通知を送信する](assignment.md)

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された文書が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の利用に起因する誤解や誤認について、当方は一切の責任を負いません。