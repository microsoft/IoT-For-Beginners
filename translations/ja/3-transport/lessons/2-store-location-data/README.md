<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-25T01:04:12+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "ja"
}
-->
# 店舗位置データ

![このレッスンの概要を示すスケッチノート](../../../../../translated_images/ja/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.jpg)

> スケッチノート作成者：[Nitya Narasimhan](https://github.com/nitya)。画像をクリックすると拡大表示されます。

## 講義前のクイズ

[講義前のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## はじめに

前回のレッスンでは、GPSセンサーを使用して位置データを取得する方法を学びました。このデータを使って食品を積んだトラックの位置やその移動経路を可視化するには、クラウド上のIoTサービスに送信し、どこかに保存する必要があります。

今回のレッスンでは、IoTデータを保存するさまざまな方法について学び、サーバーレスコードを使用してIoTサービスからデータを保存する方法を学びます。

このレッスンで学ぶ内容は以下の通りです：

* [構造化データと非構造化データ](../../../../../3-transport/lessons/2-store-location-data)
* [GPSデータをIoT Hubに送信する](../../../../../3-transport/lessons/2-store-location-data)
* [ホット、ウォーム、コールドパス](../../../../../3-transport/lessons/2-store-location-data)
* [サーバーレスコードでGPSイベントを処理する](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage Accounts](../../../../../3-transport/lessons/2-store-location-data)
* [サーバーレスコードをストレージに接続する](../../../../../3-transport/lessons/2-store-location-data)

## 構造化データと非構造化データ

コンピューターシステムはデータを扱いますが、このデータはさまざまな形状やサイズで存在します。単一の数値から大量のテキスト、動画や画像、そしてIoTデータまで多岐にわたります。データは通常、以下の2つのカテゴリに分類されます：*構造化データ*と*非構造化データ*。

* **構造化データ**は、明確で固定された構造を持つデータで、通常はテーブル形式で関係性を持つデータに対応します。例としては、名前、生年月日、住所などの個人情報があります。

* **非構造化データ**は、明確で固定された構造を持たないデータで、頻繁に構造が変化する可能性があります。例としては、文書やスプレッドシートなどがあります。

✅ 調査してみましょう：他にどのような構造化データや非構造化データの例が考えられるでしょうか？

> 💁 また、固定されたテーブル形式には収まらない構造化データである半構造化データも存在します。

IoTデータは通常、非構造化データと見なされます。

例えば、大規模な商業農場の車両群にIoTデバイスを追加するとします。車両の種類によって異なるデバイスを使用したい場合があります。例えば：

* トラクターのような農業車両には、GPSデータを使用して正しい畑で作業していることを確認したい
* 食品を倉庫に運ぶ配送トラックには、GPSデータに加えて速度や加速度データを使用して安全運転を確認し、運転者の識別や開始/停止データを使用して労働時間に関する法律遵守を確認したい
* 冷蔵トラックには、食品が輸送中に適切な温度を保つように温度データを使用したい

このデータは常に変化します。例えば、IoTデバイスがトラックの運転席にある場合、トレーラーが変更されると送信されるデータも変化する可能性があります。例えば、冷蔵トレーラーが使用される場合のみ温度データを送信するなどです。

✅ 他にどのようなIoTデータが収集される可能性があるでしょうか？トラックが運ぶ荷物の種類やメンテナンスデータについて考えてみてください。

このデータは車両ごとに異なりますが、すべて同じIoTサービスに送信されて処理されます。IoTサービスはこの非構造化データを処理し、検索や分析が可能な形で保存しながら、異なる構造のデータにも対応する必要があります。

### SQLとNoSQLストレージ

データベースはデータを保存し、クエリを実行するためのサービスです。データベースにはSQLとNoSQLの2種類があります。

#### SQLデータベース

最初のデータベースはリレーショナルデータベース管理システム（RDBMS）またはリレーショナルデータベースと呼ばれるものでした。これらは、データを追加、削除、更新、クエリするために使用される構造化クエリ言語（SQL）にちなんでSQLデータベースとも呼ばれます。このデータベースはスキーマと呼ばれる明確に定義されたデータテーブルのセットで構成されており、スプレッドシートに似ています。各テーブルには複数の名前付き列があります。データを挿入する際には、テーブルに行を追加し、各列に値を入力します。この構造は非常に固定されており、列を空にすることはできますが、新しい列を追加する場合はデータベースに変更を加え、既存の行に値を入力する必要があります。これらのデータベースはリレーショナルであり、1つのテーブルが別のテーブルと関係を持つことができます。

![ユーザーテーブルのIDが購入テーブルのユーザーID列に関連し、製品テーブルのIDが購入テーブルの製品IDに関連するリレーショナルデータベース](../../../../../translated_images/ja/sql-database.be160f12bfccefd3.webp)

例えば、ユーザーの個人情報をテーブルに保存する場合、ユーザーごとに内部的な一意のIDを持ち、このIDを使用してユーザーの名前や住所を含むテーブルの行を作成します。その後、ユーザーの購入履歴などの詳細を別のテーブルに保存したい場合、新しいテーブルにそのユーザーのIDを含む列を追加します。ユーザーを検索する際には、IDを使用して1つのテーブルから個人情報を取得し、別のテーブルから購入履歴を取得することができます。

SQLデータベースは構造化データを保存するのに理想的であり、データがスキーマに一致することを保証したい場合に適しています。

✅ SQLを使用したことがない場合は、[WikipediaのSQLページ](https://wikipedia.org/wiki/SQL)で調べてみてください。

よく知られているSQLデータベースには、Microsoft SQL Server、MySQL、PostgreSQLがあります。

✅ 調査してみましょう：これらのSQLデータベースとその機能について調べてみてください。

#### NoSQLデータベース

NoSQLデータベースは、SQLデータベースのような固定された構造を持たないため、NoSQLと呼ばれています。また、文書データベースとも呼ばれ、文書のような非構造化データを保存することができます。

> 💁 名前に反して、一部のNoSQLデータベースではSQLを使用してデータをクエリすることができます。

![NoSQLデータベース内のフォルダに格納された文書](../../../../../translated_images/ja/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.png)

NoSQLデータベースには事前定義されたスキーマがなく、データの保存方法に制限がありません。通常、JSON文書を使用して非構造化データを挿入します。これらの文書はコンピューター上のファイルのようにフォルダに整理することができます。各文書は他の文書と異なるフィールドを持つことができます。例えば、農場車両のIoTデータを保存する場合、加速度計や速度データのフィールドを持つものもあれば、トレーラー内の温度データのフィールドを持つものもあります。新しいトラックタイプを追加する場合、例えば内蔵スケールで運搬する荷物の重量を追跡する場合、IoTデバイスはこの新しいフィールドを追加し、データベースに変更を加えることなく保存することができます。

よく知られているNoSQLデータベースには、Azure CosmosDB、MongoDB、CouchDBがあります。

✅ 調査してみましょう：これらのNoSQLデータベースとその機能について調べてみてください。

このレッスンでは、IoTデータを保存するためにNoSQLストレージを使用します。

## GPSデータをIoT Hubに送信する

前回のレッスンでは、IoTデバイスに接続されたGPSセンサーからGPSデータを取得しました。このIoTデータをクラウドに保存するには、IoTサービスに送信する必要があります。今回も前回のプロジェクトで使用したAzure IoT Hubを使用します。

![IoTデバイスからIoT HubにGPSテレメトリを送信する](../../../../../translated_images/ja/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.png)

### タスク - GPSデータをIoT Hubに送信する

1. 無料プランを使用して新しいIoT Hubを作成します。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン4のIoT Hub作成手順](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud)を参照してください。

    新しいリソースグループを作成してください。リソースグループの名前を`gps-sensor`、新しいIoT Hubの名前を`gps-sensor`に基づいた一意の名前（例：`gps-sensor-<あなたの名前>`）にしてください。

    > 💁 前回のプロジェクトで使用したIoT Hubがまだある場合は、それを再利用できます。他のサービスを作成する際には、このIoT Hubの名前とリソースグループを使用してください。

1. IoT Hubに新しいデバイスを追加します。このデバイスの名前を`gps-sensor`とし、デバイスの接続文字列を取得してください。

1. デバイスコードを更新して、前のステップで取得したデバイス接続文字列を使用して新しいIoT HubにGPSデータを送信するようにしてください。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン4のデバイス接続手順](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service)を参照してください。

1. GPSデータを送信する際には、以下のJSON形式で送信してください：

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. 毎分GPSデータを送信して、1日のメッセージ割り当てを使い切らないようにしてください。

Wio Terminalを使用している場合は、必要なライブラリをすべて追加し、NTPサーバーを使用して時間を設定してください。また、コードはGPS位置を送信する前にシリアルポートからすべてのデータを読み取る必要があります。前回のレッスンの既存コードを使用してください。以下のコードを使用してJSON文書を構築してください：

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

仮想IoTデバイスを使用している場合は、仮想環境を使用して必要なライブラリをすべてインストールしてください。

Raspberry Piと仮想IoTデバイスの両方で、前回のレッスンの既存コードを使用して緯度と経度の値を取得し、以下のコードを使用して正しいJSON形式で送信してください：

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 このコードは[code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal)、[code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi)、または[code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device)フォルダにあります。

デバイスコードを実行し、`az iot hub monitor-events` CLIコマンドを使用してIoT Hubにメッセージが流れていることを確認してください。

## ホット、ウォーム、コールドパス

IoTデバイスからクラウドに流れるデータは、必ずしもリアルタイムで処理されるわけではありません。一部のデータはリアルタイムで処理する必要がありますが、他のデータは少し後で処理することができ、さらに別のデータはずっと後で処理することができます。データが異なるタイミングで処理されるサービスに流れることをホット、ウォーム、コールドパスと呼びます。

### ホットパス

ホットパスは、リアルタイムまたはほぼリアルタイムで処理する必要があるデータを指します。例えば、車両が倉庫に近づいていることや冷蔵トラックの温度が高すぎることを知らせるアラートにホットパスデータを使用します。

ホットパスデータを使用するには、クラウドサービスにイベントが届いたらすぐにコードが応答する必要があります。

### ウォームパス

ウォームパスは、受信後少し後で処理できるデータを指します。例えば、日次レポートや短期分析に使用します。前日のデータを使用して車両の走行距離を報告する場合などです。

ウォームパスデータは、クラウドサービスに受信された後、迅速にアクセスできるストレージに保存されます。

### コールドパス

コールドパスは、長期間保存され、必要に応じて処理される履歴データを指します。例えば、車両の年間走行距離レポートを取得したり、燃料コストを削減するための最適なルートを分析する場合に使用します。

コールドパスデータはデータウェアハウスに保存されます。データウェアハウスは、大量の変更されないデータを保存し、迅速かつ簡単にクエリを実行できるように設計されています。通常、クラウドアプリケーション内で定期的に実行されるジョブがあり、ウォームパスストレージからデータウェアハウスにデータを移動します。

✅ これまでのレッスンで収集したデータについて考えてみましょう。それはホット、ウォーム、コールドパスのどれに該当しますか？

## サーバーレスコードでGPSイベントを処理する

データがIoT Hubに流れ込んだら、イベントハブ互換エンドポイントに公開されたイベントをリッスンするサーバーレスコードを記述できます。これはウォームパスに該当します。このデータは保存され、次のレッスンで旅程の報告に使用されます。

![IoTデバイスからIoT HubにGPSテレメトリを送信し、イベントハブトリガーを介してAzure Functionsに送信する](../../../../../translated_images/ja/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.png)

### タスク - サーバーレスコードでGPSイベントを処理する

1. Azure Functions CLIを使用してAzure Functionsアプリを作成します。Pythonランタイムを使用し、`gps-trigger`というフォルダに作成してください。また、Functions Appプロジェクト名も`gps-trigger`としてください。仮想環境を作成して使用することを忘れないでください。
> ⚠️ 必要に応じて、[プロジェクト2、レッスン5のAzure Functionsプロジェクト作成手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application)を参照してください。
1. IoT HubのEvent Hub互換エンドポイントを使用するIoT Hubイベントトリガーを追加します。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン5のIoT Hubイベントトリガー作成手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger)を参照してください。

1. `local.settings.json`ファイルにEvent Hub互換エンドポイント接続文字列を設定し、そのエントリのキーを`function.json`ファイルで使用します。

1. Azuriteアプリをローカルストレージエミュレーターとして使用します。

1. 関数アプリを実行して、GPSデバイスからイベントを受信していることを確認します。IoTデバイスも実行中でGPSデータを送信していることを確認してください。

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storageアカウント

![Azure Storageのロゴ](../../../../../translated_images/ja/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.png)

Azure Storageアカウントは、さまざまな方法でデータを保存できる汎用ストレージサービスです。データをBlob、キュー、テーブル、またはファイルとして保存でき、同時にすべてを利用することが可能です。

### Blobストレージ

*Blob*という言葉は「バイナリ大規模オブジェクト」を意味しますが、現在では非構造化データ全般を指す用語として使われています。Blobストレージには、IoTデータを含むJSONドキュメントから画像や動画ファイルまで、あらゆるデータを保存できます。Blobストレージには*コンテナー*という概念があり、これはリレーショナルデータベースのテーブルに似た名前付きバケットです。これらのコンテナーには1つ以上のフォルダーを作成してBlobを保存でき、各フォルダーにはさらに他のフォルダーを含めることができます。これは、コンピュータのハードディスク上でファイルが保存される方法に似ています。

このレッスンでは、IoTデータを保存するためにBlobストレージを使用します。

✅ 調査してみましょう: [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)について読んでみてください。

### テーブルストレージ

テーブルストレージは、半構造化データを保存するためのものです。テーブルストレージは実際にはNoSQLデータベースであり、事前に定義されたテーブルセットを必要としませんが、1つ以上のテーブルにデータを保存し、各行を一意のキーで定義するように設計されています。

✅ 調査してみましょう: [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)について読んでみてください。

### キューストレージ

キューストレージは、最大64KBのメッセージをキューに保存するためのものです。メッセージをキューの後ろに追加し、前から読み取ることができます。キューはストレージスペースがある限りメッセージを無期限に保存するため、長期間メッセージを保存し、必要に応じて読み取ることができます。たとえば、GPSデータを処理する月次ジョブを実行したい場合、1か月間毎日キューに追加し、月末にすべてのメッセージを処理することができます。

✅ 調査してみましょう: [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)について読んでみてください。

### ファイルストレージ

ファイルストレージはクラウド上のファイル保存であり、業界標準のプロトコルを使用してアプリやデバイスが接続できます。ファイルストレージにファイルを書き込み、それをPCやMac上でドライブとしてマウントすることができます。

✅ 調査してみましょう: [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)について読んでみてください。

## サーバーレスコードをストレージに接続する

関数アプリは、IoT HubからのメッセージをBlobストレージに保存するためにBlobストレージに接続する必要があります。これには2つの方法があります：

* 関数コード内でBlobストレージに接続し、Python SDKを使用してデータをBlobとして書き込む
* 出力関数バインディングを使用して、関数の戻り値をBlobストレージにバインドし、自動的にBlobを保存する

このレッスンでは、Python SDKを使用してBlobストレージとやり取りする方法を学びます。

![IoTデバイスからIoT HubにGPSテレメトリを送信し、イベントハブトリガーを介してAzure Functionsに渡し、Blobストレージに保存する](../../../../../translated_images/ja/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

データは以下の形式のJSON Blobとして保存されます：

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### タスク - サーバーレスコードをストレージに接続する

1. Azure Storageアカウントを作成します。名前は`gps<あなたの名前>`のようにします。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン5のストレージアカウント作成手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)を参照してください。

    前のプロジェクトでストレージアカウントを作成している場合、それを再利用することができます。

    > 💁 このストレージアカウントは、このレッスンの後半でAzure Functionsアプリをデプロイする際にも使用できます。

1. 次のコマンドを実行して、ストレージアカウントの接続文字列を取得します：

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    `<storage_name>`を、前のステップで作成したストレージアカウントの名前に置き換えてください。

1. `local.settings.json`ファイルにストレージアカウント接続文字列の新しいエントリを追加し、前のステップで取得した値を使用します。名前は`STORAGE_CONNECTION_STRING`とします。

1. `requirements.txt`ファイルに次の内容を追加して、AzureストレージのPipパッケージをインストールします：

    ```sh
    azure-storage-blob
    ```

    仮想環境でこのファイルからパッケージをインストールします。

    > エラーが発生した場合は、次のコマンドで仮想環境内のPipバージョンを最新にアップグレードしてから再試行してください：
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `iot-hub-trigger`の`__init__.py`ファイルに次のインポート文を追加します：

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    `json`システムモジュールはJSONの読み書きに使用され、`os`システムモジュールは接続文字列の読み取りに使用されます。`uuid`システムモジュールはGPS読み取りの一意のIDを生成するために使用されます。

    `azure.storage.blob`パッケージは、Blobストレージを操作するためのPython SDKを含みます。

1. `main`メソッドの前に次のヘルパー関数を追加します：

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    PythonのBlob SDKには、存在しない場合にコンテナーを作成するヘルパーメソッドがありません。このコードは、`local.settings.json`ファイル（またはクラウドにデプロイされた後はアプリケーション設定）から接続文字列を読み込み、これを使用してBlobストレージアカウントとやり取りするための`BlobServiceClient`クラスを作成します。その後、Blobストレージアカウントのすべてのコンテナーをループして指定された名前のコンテナーを探し、見つかった場合はそのコンテナーとやり取りするための`ContainerClient`クラスを返します。見つからない場合は、新しいコンテナーを作成し、そのクライアントを返します。

    新しいコンテナーが作成されると、コンテナー内のBlobをクエリするための公開アクセスが許可されます。これは次のレッスンでGPSデータを地図上に可視化するために使用されます。

1. 土壌水分センサーとは異なり、このコードではすべてのイベントを保存したいので、`main`関数内の`for event in events:`ループの`logging`ステートメントの下に次のコードを追加します：

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    このコードは、イベントメタデータからデバイスIDを取得し、それを使用してBlob名を作成します。Blobはフォルダーに保存でき、デバイスIDはフォルダー名として使用されるため、各デバイスのGPSイベントは1つのフォルダーにまとめられます。Blob名はこのフォルダーとドキュメント名で構成され、スラッシュで区切られます（LinuxやmacOSのパスに似ています。Windowsも同様ですが、Windowsではバックスラッシュを使用します）。ドキュメント名はPythonの`uuid`モジュールを使用して生成された一意のIDで、ファイルタイプは`json`です。

    たとえば、デバイスIDが`gps-sensor`の場合、Blob名は`gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`のようになります。

1. この下に次のコードを追加します：

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    このコードは、`get_or_create_container`ヘルパークラスを使用してコンテナクライアントを取得し、Blob名を使用してBlobクライアントオブジェクトを取得します。これらのBlobクライアントは既存のBlobを参照することも、新しいBlobを参照することもできます。

1. この後に次のコードを追加します：

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    これは、Blobストレージに書き込まれるBlobの本文を構築します。JSONドキュメントで、デバイスID、IoT Hubに送信されたテレメトリの時間、およびテレメトリからのGPS座標が含まれます。

    > 💁 メッセージが送信された時間を取得するために、現在の時間ではなくメッセージのキューイング時間を使用することが重要です。関数アプリが実行されていない場合、メッセージがハブ上でしばらく待機している可能性があります。

1. このコードの下に次のコードを追加します：

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    このコードは、Blobが書き込まれる直前にその詳細をログに記録し、新しいBlobの内容としてBlob本文をアップロードします。

1. 関数アプリを実行します。すべてのGPSイベントに対してBlobが書き込まれるのが出力に表示されます：

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 IoT Hubイベントモニターを同時に実行していないことを確認してください。

> 💁 このコードは[code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions)フォルダーにあります。

### タスク - アップロードされたBlobを確認する

1. 作成されたBlobを表示するには、[Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn)（ストレージアカウントを表示および管理するための無料ツール）を使用するか、CLIを使用します。

    1. CLIを使用するには、まずアカウントキーが必要です。次のコマンドを実行してこのキーを取得します：

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        `<storage_name>`をストレージアカウントの名前に置き換えてください。

        `key1`の値をコピーします。

    1. 次のコマンドを実行して、コンテナー内のBlobを一覧表示します：

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        `<storage_name>`をストレージアカウントの名前に、`<key1>`を前のステップでコピーした`key1`の値に置き換えてください。

        これにより、コンテナー内のすべてのBlobが一覧表示されます：

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. 次のコマンドを使用してBlobの1つをダウンロードします：

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        `<storage_name>`をストレージアカウントの名前に、`<key1>`を前のステップでコピーした`key1`の値に置き換えてください。

        `<blob_name>`を、前のステップの出力の`Name`列にある完全な名前（フォルダー名を含む）に置き換えます。`<file_name>`をローカルファイルの名前に置き換えてBlobを保存します。

    ダウンロードが完了したら、VS CodeでJSONファイルを開き、GPS位置情報の詳細を含むBlobを確認できます：

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### タスク - 関数アプリをクラウドにデプロイする

関数アプリが動作していることを確認したら、クラウドにデプロイします。

1. 新しいAzure Functionsアプリを作成し、先ほど作成したストレージアカウントを使用します。名前は`gps-sensor-`にランダムな単語や名前を追加したものにします。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン5のFunctionsアプリ作成手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)を参照してください。

1. `IOT_HUB_CONNECTION_STRING`と`STORAGE_CONNECTION_STRING`の値をアプリケーション設定にアップロードします。

    > ⚠️ 必要に応じて、[プロジェクト2、レッスン5のアプリケーション設定アップロード手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings)を参照してください。

1. ローカルのFunctionsアプリをクラウドにデプロイします。
> ⚠️ 必要に応じて、[プロジェクト2、レッスン5の関数アプリをデプロイする手順](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud)を参照してください。
## 🚀 チャレンジ

GPSデータは完全に正確ではなく、特にトンネルや高層ビルの周辺では、検出される位置が数メートル以上ずれることがあります。

衛星ナビゲーションがこれをどのように克服できるか考えてみましょう。あなたのカーナビには、位置をより正確に予測するためにどのようなデータがあるでしょうか？

## 講義後のクイズ

[講義後のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## 復習と自己学習

* Wikipediaの[データモデルのページ](https://wikipedia.org/wiki/Data_model)で構造化データについて読む
* Wikipediaの[半構造化データのページ](https://wikipedia.org/wiki/Semi-structured_data)で半構造化データについて読む
* Wikipediaの[非構造化データのページ](https://wikipedia.org/wiki/Unstructured_data)で非構造化データについて読む
* Azure Storageと異なるストレージタイプについて、[Azure Storageのドキュメント](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)でさらに学ぶ

## 課題

[関数バインディングを調査する](assignment.md)

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があります。元の言語で記載された文書が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。