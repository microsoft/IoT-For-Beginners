<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-25T00:01:01+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "ja"
}
-->
# 言語を理解する

![このレッスンのスケッチノート概要](../../../../../translated_images/ja/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.jpg)

> スケッチノート作成者: [Nitya Narasimhan](https://github.com/nitya)。画像をクリックすると拡大表示されます。

## 講義前のクイズ

[講義前のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## はじめに

前回のレッスンでは、音声をテキストに変換しました。この機能をスマートタイマーをプログラムするために使用するには、コードが発言内容を理解する必要があります。例えば、ユーザーが「3分タイマーをセットして」といった固定フレーズを話すと仮定し、その表現を解析してタイマーの時間を取得することは可能ですが、これはあまりユーザーフレンドリーではありません。もしユーザーが「タイマーを3分にセットして」と言った場合、私たち人間はその意味を理解できますが、コードは固定フレーズを期待しているため理解できません。

ここで言語理解が役立ちます。AIモデルを使用してテキストを解釈し、必要な詳細を返すことで、「3分タイマーをセットして」や「タイマーを3分にセットして」の両方を理解し、3分間のタイマーが必要であることを認識できるようになります。

このレッスンでは、言語理解モデルの作成方法、トレーニング方法、コードでの使用方法を学びます。

このレッスンで学ぶ内容は以下の通りです：

* [言語理解](../../../../../6-consumer/lessons/2-language-understanding)
* [言語理解モデルの作成](../../../../../6-consumer/lessons/2-language-understanding)
* [インテントとエンティティ](../../../../../6-consumer/lessons/2-language-understanding)
* [言語理解モデルの使用](../../../../../6-consumer/lessons/2-language-understanding)

## 言語理解

人間は何十万年もの間、言語を使ってコミュニケーションを取ってきました。私たちは言葉、音、行動を使って意思を伝え、それらの意味や文脈を理解します。私たちは誠実さや皮肉を理解し、声のトーンによって同じ言葉が異なる意味を持つことを認識します。

✅ 最近の会話を思い出してみてください。文脈が必要なためにコンピュータが理解するのが難しい会話はどれくらいあったでしょうか？

言語理解、または自然言語理解（Natural Language Understanding）は、自然言語処理（NLP）と呼ばれる人工知能の分野の一部であり、読解力に焦点を当て、言葉や文章の詳細を理解しようとします。AlexaやSiriのような音声アシスタントを使用したことがあるなら、言語理解サービスを利用したことがあります。これらは、「Alexa、Taylor Swiftの最新アルバムを再生して」というリクエストを、娘がリビングでお気に入りの曲に合わせて踊るという結果に変換する裏方のAIサービスです。

> 💁 コンピュータは多くの進歩を遂げていますが、テキストを真に理解するにはまだ長い道のりがあります。コンピュータによる言語理解というとき、それは人間のコミュニケーションに匹敵するほど高度なものではなく、単にいくつかの言葉を取り出して重要な詳細を抽出することを意味します。

人間は、特に意識せずに言語を理解します。例えば、他の人に「Taylor Swiftの最新アルバムを再生して」と頼めば、その意味を直感的に理解します。しかし、コンピュータにとってはこれが難しいのです。コンピュータは、音声からテキストに変換された言葉を取り出し、以下の情報を解析する必要があります：

* 音楽を再生する必要がある
* 音楽はアーティストTaylor Swiftによるものである
* 特定の音楽は複数のトラックが順番に並んだアルバムである
* Taylor Swiftには多くのアルバムがあるため、年代順に並べて最新のものを選ぶ必要がある

✅ コーヒーを注文したり、家族に何かを取ってもらうよう頼んだりしたときの会話を思い出してみてください。その文をコンピュータが理解するために必要な情報を分解してみましょう。

言語理解モデルは、言語から特定の詳細を抽出するように訓練されたAIモデルです。これらは、カスタムビジョンモデルを少量の画像で訓練したのと同じように、転移学習を使用して特定のタスク向けに訓練されます。モデルを取得し、理解させたいテキストを使用して訓練することができます。

## 言語理解モデルの作成

![LUISのロゴ](../../../../../translated_images/ja/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.png)

言語理解モデルは、MicrosoftのCognitive Servicesの一部であるLUIS（Language Understanding Intelligent Service）を使用して作成できます。

### タスク - オーサリングリソースの作成

LUISを使用するには、オーサリングリソースを作成する必要があります。

1. 以下のコマンドを使用して、`smart-timer`リソースグループ内にオーサリングリソースを作成します：

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    `<location>`をリソースグループを作成した場所に置き換えてください。

    > ⚠️ LUISはすべてのリージョンで利用可能ではありません。以下のエラーが表示された場合：
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > 別のリージョンを選択してください。

    これにより、無料のLUISオーサリングリソースが作成されます。

### タスク - 言語理解アプリの作成

1. ブラウザでLUISポータル [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) を開き、Azureで使用しているのと同じアカウントでサインインします。

1. ダイアログの指示に従ってAzureサブスクリプションを選択し、先ほど作成した`smart-timer-luis-authoring`リソースを選択します。

1. *Conversation apps*リストから**New app**ボタンを選択して新しいアプリケーションを作成します。新しいアプリの名前を`smart-timer`とし、*Culture*を自分の言語に設定します。

    > 💁 予測リソースのフィールドがあります。予測専用のリソースを作成することもできますが、無料のオーサリングリソースでは月に1,000回の予測が可能であり、開発には十分ですので、このフィールドは空白のままで構いません。

1. アプリを作成すると表示されるガイドを読み、言語理解モデルを訓練するために必要な手順を理解してください。ガイドを読み終えたら閉じてください。

## インテントとエンティティ

言語理解は、*インテント*と*エンティティ*を中心に構築されています。インテントは言葉の意図を指し、例えば音楽を再生する、タイマーをセットする、食べ物を注文するなどです。エンティティはインテントが何を指しているかを表し、例えばアルバム、タイマーの長さ、食べ物の種類などです。モデルが解釈する各文には、少なくとも1つのインテントと、オプションで1つ以上のエンティティが含まれます。

いくつかの例を挙げます：

| 文                                                 | インテント       | エンティティ                                   |
| -------------------------------------------------- | ---------------- | --------------------------------------------- |
| "Play the latest album by Taylor Swift"            | *音楽を再生する* | *Taylor Swiftの最新アルバム*                  |
| "Set a 3 minute timer"                             | *タイマーをセットする* | *3分*                                         |
| "Cancel my timer"                                  | *タイマーをキャンセルする* | なし                                          |
| "Order 3 large pineapple pizzas and a caesar salad" | *食べ物を注文する* | *3つの大きなパイナップルピザ*, *シーザーサラダ* |

✅ 先ほど考えた文について、その文のインテントとエンティティを考えてみてください。

LUISを訓練するには、まずエンティティを設定します。これらは固定リストの用語として提供することも、テキストから学習させることもできます。例えば、メニューにある食べ物の固定リストを提供し、それぞれの単語のバリエーション（または同義語）を追加することができます。例えば、*egg plant*と*aubergine*を*aubergine*のバリエーションとして追加します。LUISには、数字や場所などの事前構築されたエンティティも用意されています。

タイマーを設定する場合、時間の単位（分や秒）用のエンティティと、分や秒の数値用のエンティティを1つずつ作成できます。各単位には、単数形と複数形のバリエーションをカバーするために、複数のバリエーションを追加します（例：minuteとminutes）。

エンティティを定義した後、インテントを作成します。これらは、提供する例文（発話）に基づいてモデルが学習します。例えば、*タイマーをセットする*インテントの場合、以下のような文を提供します：

* `set a 1 second timer`
* `set a timer for 1 minute and 12 seconds`
* `set a timer for 3 minutes`
* `set a 9 minute 30 second timer`

これらの文のどの部分がエンティティに対応するかをLUISに教えます：

![文「set a timer for 1 minute and 12 seconds」をエンティティに分解した図](../../../../../translated_images/ja/sentence-as-intent-entities.301401696f992259.webp)

文`set a timer for 1 minute and 12 seconds`のインテントは`set timer`です。また、2つのエンティティがそれぞれ2つの値を持っています：

|            | time | unit   |
| ---------- | ---: | ------ |
| 1 minute   | 1    | minute |
| 12 seconds | 12   | second |

良いモデルを訓練するには、同じことを頼むためのさまざまな表現をカバーする多様な例文が必要です。

> 💁 他のAIモデルと同様、訓練に使用するデータが多く、正確であるほど、モデルの性能は向上します。

✅ 同じことを頼むために使うさまざまな表現を考え、それを人間が理解できると期待する方法を考えてみてください。

### タスク - 言語理解モデルにエンティティを追加する

タイマーの場合、2つのエンティティを追加する必要があります。1つは時間の単位（分や秒）用、もう1つは分や秒の数値用です。

LUISポータルの使用方法については、[Microsoft DocsのLUISポータルでアプリを構築するクイックスタートガイド](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn)を参照してください。

1. LUISポータルから*Entities*タブを選択し、**Add prebuilt entity**ボタンを選択して*number*事前構築エンティティを追加します。

1. **Create**ボタンを使用して、時間単位用の新しいエンティティを作成します。このエンティティに`time unit`という名前を付け、タイプを*List*に設定します。*Normalized values*リストに`minute`と`second`の値を追加し、*synonyms*リストに単数形と複数形のバリエーションを追加します。各同義語を追加した後、`return`キーを押してリストに追加します。

    | 正規化された値 | 同義語            |
    | -------------- | ----------------- |
    | minute         | minute, minutes   |
    | second         | second, seconds   |

### タスク - 言語理解モデルにインテントを追加する

1. *Intents*タブから**Create**ボタンを選択して新しいインテントを作成します。このインテントに`set timer`という名前を付けます。

1. 例文には、分、秒、または分と秒を組み合わせたタイマーを設定するさまざまな方法を入力します。例として以下を挙げます：

    * `set a 1 second timer`
    * `set a 4 minute timer`
    * `set a four minute six second timer`
    * `set a 9 minute 30 second timer`
    * `set a timer for 1 minute and 12 seconds`
    * `set a timer for 3 minutes`
    * `set a timer for 3 minutes and 1 second`
    * `set a timer for three minutes and one second`
    * `set a timer for 1 minute and 1 second`
    * `set a timer for 30 seconds`
    * `set a timer for 1 second`

    数字を単語や数値で混在させて、モデルが両方を処理できるようにします。

1. 各例文を入力すると、LUISがエンティティを検出し始め、検出された部分を下線付きでラベル付けします。

    ![LUISが例文の数字と時間単位を下線付きで表示している図](../../../../../translated_images/ja/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.png)

### タスク - モデルの訓練とテスト

1. エンティティとインテントを設定したら、トップメニューの**Train**ボタンを使用してモデルを訓練します。このボタンを選択すると、数秒でモデルが訓練されます。訓練中はボタンがグレーアウトし、完了すると再び有効になります。

1. トップメニューの**Test**ボタンを選択して、言語理解モデルをテストします。`set a timer for 5 minutes and 4 seconds`のようなテキストを入力し、リターンキーを押します。入力したテキストがテキストボックスの下に表示され、その下に*top intent*（最も高い確率で検出されたインテント）が表示されます。これが`set timer`であるはずです。インテント名の後には、そのインテントが正しいと判断された確率が表示されます。

1. **Inspect**オプションを選択して、結果の詳細を確認します。最もスコアの高いインテントとその確率、検出されたエンティティのリストが表示されます。

1. テストが終了したら、*Test*ペインを閉じます。

### タスク - モデルの公開

このモデルをコードから使用するには、公開する必要があります。LUISから公開する際には、テスト用のステージング環境または本番環境に公開することができます。このレッスンでは、ステージング環境で十分です。

1. LUISポータルからトップメニューの**Publish**ボタンを選択します。

1. *Staging slot*が選択されていることを確認し、**Done**を選択します。アプリが公開されると通知が表示されます。

1. curlを使用してこれをテストできます。curlコマンドを構築するには、エンドポイント、アプリケーションID（App ID）、APIキーの3つの値が必要です。これらは、トップメニューから選択できる**MANAGE**タブで確認できます。

    1. *Settings*セクションからApp IDをコピーします。
1. *Azure Resources* セクションから *Authoring Resource* を選択し、*Primary Key* と *Endpoint URL* をコピーします。

1. コマンドプロンプトまたはターミナルで以下の curl コマンドを実行します:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    `<endpoint url>` を *Azure Resources* セクションから取得した Endpoint URL に置き換えます。

    `<app id>` を *Settings* セクションから取得した App ID に置き換えます。

    `<primary key>` を *Azure Resources* セクションから取得した Primary Key に置き換えます。

    `<sentence>` をテストしたい文に置き換えます。

1. このコールの出力は、クエリ、トップインテント、タイプごとに分類されたエンティティのリストを詳細に記載した JSON ドキュメントになります。

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    上記の JSON は `set a timer for 45 minutes and 12 seconds` というクエリから生成されました:

    * `set timer` が 97% の確率でトップインテントとして検出されました。
    * 2つの *number* エンティティが検出されました: `45` と `12`。
    * 2つの *time-unit* エンティティが検出されました: `minute` と `second`。

## 言語理解モデルを使用する

LUIS モデルを公開すると、コードから呼び出すことができます。以前のレッスンでは、IoT Hub を使用してクラウドサービスとの通信を処理し、テレメトリを送信したりコマンドを受信したりしました。この方法は非常に非同期的で、テレメトリを送信した後にコードが応答を待つことはなく、クラウドサービスがダウンしている場合でも気づかない可能性があります。

スマートタイマーの場合、すぐに応答が必要です。これにより、タイマーが設定されたことをユーザーに伝えたり、クラウドサービスが利用できないことを警告したりできます。そのため、IoT デバイスは IoT Hub に依存せず、直接 Web エンドポイントを呼び出します。

LUIS を IoT デバイスから直接呼び出す代わりに、HTTP トリガーを使用したサーバーレスコードを利用できます。これにより、関数アプリが REST リクエストを受信し、それに応答することが可能になります。この関数は、デバイスが呼び出せる REST エンドポイントになります。

> 💁 LUIS を IoT デバイスから直接呼び出すこともできますが、サーバーレスコードのようなものを使用する方が良いです。例えば、より良いモデルをトレーニングしたり、別の言語でモデルをトレーニングしたりする場合、呼び出す LUIS アプリを変更する際にクラウドコードを更新するだけで済みます。これにより、数千または数百万の IoT デバイスにコードを再デプロイする必要がなくなります。

### タスク - サーバーレス関数アプリを作成する

1. `smart-timer-trigger` という名前の Azure Functions アプリを作成し、これを VS Code で開きます。

1. VS Code のターミナル内で以下のコマンドを使用して、このアプリに `speech-trigger` という HTTP トリガーを追加します:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    これにより、`text-to-timer` という HTTP トリガーが作成されます。

1. 関数アプリを実行して HTTP トリガーをテストします。実行すると、出力にエンドポイントが表示されます:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    ブラウザで [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL を読み込んでテストします。

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### タスク - 言語理解モデルを使用する

1. LUIS の SDK は Pip パッケージを通じて利用可能です。`requirements.txt` ファイルに以下の行を追加して、このパッケージへの依存関係を追加します:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. VS Code のターミナルで仮想環境がアクティブになっていることを確認し、以下のコマンドを実行して Pip パッケージをインストールします:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 エラーが発生した場合は、以下のコマンドで pip をアップグレードする必要があるかもしれません:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. LUIS ポータルの **MANAGE** タブから取得した LUIS API Key、Endpoint URL、App ID の新しいエントリを `local.settings.json` ファイルに追加します:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    `<endpoint url>` を **MANAGE** タブの *Azure Resources* セクションから取得した Endpoint URL に置き換えます。この URL は `https://<location>.api.cognitive.microsoft.com/` になります。

    `<app id>` を **MANAGE** タブの *Settings* セクションから取得した App ID に置き換えます。

    `<primary key>` を **MANAGE** タブの *Azure Resources* セクションから取得した Primary Key に置き換えます。

1. `__init__.py` ファイルに以下のインポートを追加します:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    これにより、システムライブラリと LUIS と対話するためのライブラリがインポートされます。

1. `main` メソッドの内容を削除し、以下のコードを追加します:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    これにより、LUIS アプリ用に `local.settings.json` ファイルに追加した値が読み込まれ、API キーを使用して資格情報オブジェクトが作成され、LUIS アプリと対話するための LUIS クライアントオブジェクトが作成されます。

1. この HTTP トリガーは、理解するテキストを JSON として渡し、`text` というプロパティにテキストを含めます。以下のコードを追加して、HTTP リクエストの本文から値を抽出し、コンソールにログを記録します:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. LUIS に予測をリクエストするには、予測リクエストを送信します。これは、予測するテキストを含む JSON ドキュメントです。以下のコードでこれを作成します:

    ```python
    prediction_request = { 'query' : text }
    ```

1. このリクエストを LUIS に送信し、アプリが公開されたステージングスロットを使用します:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. 予測応答には、最高の予測スコアを持つトップインテントとエンティティが含まれます。トップインテントが `set timer` の場合、エンティティを読み取ってタイマーに必要な時間を取得できます:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number` エンティティは数値の配列になります。例えば、*"Set a four minute 17 second timer."* と言った場合、`number` 配列には 2 つの整数 - 4 と 17 が含まれます。

    `time unit` エンティティは文字列の配列の配列になります。例えば、*"Set a four minute 17 second timer."* と言った場合、`time unit` 配列には 2 つの配列が含まれ、それぞれに単一の値 - `['minute']` と `['second']` が含まれます。

    *"Set a four minute 17 second timer."* のエンティティの JSON バージョンは以下の通りです:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    このコードは、タイマーの合計時間を秒単位で定義するカウントも設定します。このカウントはエンティティの値で設定されます。

1. エンティティはリンクされていませんが、いくつかの仮定をすることができます。エンティティは話された順序で並んでいるため、配列内の位置を使用して、どの数値がどの時間単位に対応するかを判断できます。例えば:

    * *"Set a 30 second timer"* - これには 1 つの数値 `30` と 1 つの時間単位 `second` が含まれるため、単一の数値が単一の時間単位に対応します。
    * *"Set a 2 minute and 30 second timer"* - これには 2 つの数値 `2` と `30`、および 2 つの時間単位 `minute` と `second` が含まれるため、最初の数値が最初の時間単位 (2 分) に対応し、2 番目の数値が 2 番目の時間単位 (30 秒) に対応します。

    以下のコードは、数値エンティティのアイテム数を取得し、それを使用して各配列から最初のアイテム、次に 2 番目のアイテムを抽出します。このコードを `if` ブロック内に追加します。

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    *"Set a four minute 17 second timer."* の場合、このコードは 2 回ループし、以下の値を生成します:

    | ループ回数 | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. このループ内で、数値と時間単位を使用してタイマーの合計時間を計算し、分ごとに 60 秒を追加し、秒単位の数値を加算します。

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. エンティティのループ外で、タイマーの合計時間をログに記録します:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. 秒数を HTTP レスポンスとして関数から返す必要があります。`if` ブロックの最後に以下を追加します:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    このコードは、タイマーの合計秒数を含むペイロードを作成し、それを JSON 文字列に変換して、ステータスコード 200 (成功を意味する) とともに HTTP 結果として返します。

1. 最後に、インテントが認識されなかった場合を処理するために、エラーコードを返します。`if` ブロックの外側に以下を追加します:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 は *not found* を意味するステータスコードです。

1. 関数アプリを実行し、curl を使用してテストします。

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    `<text>` をリクエストのテキストに置き換えます。例えば `set a 2 minutes 27 second timer`。

    関数アプリから以下の出力が表示されます:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    curl のコールは以下を返します:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    タイマーの秒数は `"seconds"` 値に含まれています。

> 💁 このコードは [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) フォルダーにあります。

### タスク - 関数を IoT デバイスで利用可能にする

1. IoT デバイスが REST エンドポイントを呼び出すには、URL を知る必要があります。以前アクセスした際には `localhost` を使用しましたが、これはローカルマシン上の REST エンドポイントにアクセスするためのショートカットです。IoT デバイスがアクセスできるようにするには、クラウドに公開するか、ローカルで IP アドレスを取得する必要があります。

    > ⚠️ Wio Terminal を使用している場合、関数アプリをローカルで実行する方が簡単です。これは、ライブラリの依存関係により、以前のように関数アプリをデプロイできない可能性があるためです。関数アプリをローカルで実行し、コンピュータの IP アドレスを使用してアクセスしてください。クラウドにデプロイしたい場合は、後のレッスンでその方法について説明します。

    * 関数アプリを公開する - 関数アプリをクラウドに公開する手順は以前のレッスンで説明されています。公開後、URL は `https://<APP_NAME>.azurewebsites.net/api/text-to-timer` になります。`<APP_NAME>` は関数アプリの名前です。ローカル設定も公開してください。

      HTTP トリガーを使用する場合、デフォルトで関数アプリキーで保護されています。このキーを取得するには、以下のコマンドを実行します:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      `functionKeys` セクションの `default` エントリの値をコピーします。

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      このキーは URL にクエリパラメータとして追加する必要があります。最終的な URL は `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>` になります。`<APP_NAME>` は関数アプリの名前で、`<FUNCTION_KEY>` はデフォルトの関数キーです。

      > 💁 HTTP トリガーの認証レベルは `function.json` ファイルの `authlevel` 設定を使用して変更できます。この設定については、[Microsoft Docs の Azure Functions HTTP トリガー ドキュメントの構成セクション](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration) を参照してください。

    * 関数アプリをローカルで実行し、IP アドレスを使用してアクセスする - ローカルネットワーク上のコンピュータの IP アドレスを取得し、それを使用して URL を構築します。

      IP アドレスを見つける方法:

      * Windows 10 の場合、[IP アドレスを見つけるガイド](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn) を参照してください。
      * macOS の場合、[Mac で IP アドレスを見つける方法ガイド](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac) を参照してください。
      * Linux の場合、[Linux で IP アドレスを見つける方法ガイド](https://opensource.com/article/18/5/how-find-ip-address-linux) のプライベート IP アドレスを見つけるセクションを参照してください。

      IP アドレスを取得したら、関数にアクセスするための URL は `http://` になります。

:7071/api/text-to-timer`で、`<IP_ADDRESS>`はあなたのIPアドレスになります。例えば、`http://192.168.1.10:7071/api/text-to-timer`のように指定します。

      > 💁 ポート7071を使用するため、IPアドレスの後に`:7071`を付ける必要があります。

      > 💁 これは、IoTデバイスがコンピュータと同じネットワーク上にある場合のみ動作します。

1. curlを使用してエンドポイントにアクセスし、テストしてください。

---

## 🚀 チャレンジ

タイマーを設定するなど、同じ要求をする方法はたくさんあります。これらの異なる方法を考え、それらをLUISアプリの例として使用してください。これらをテストして、モデルがタイマーの要求に対してどれだけ柔軟に対応できるか確認してください。

## 講義後のクイズ

[講義後のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## レビューと自己学習

* LUISの機能についてさらに詳しく知りたい場合は、[Microsoft DocsのLanguage Understanding (LUIS) ドキュメントページ](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)を参照してください。
* 言語理解についてさらに詳しく知りたい場合は、[Wikipediaの自然言語理解ページ](https://wikipedia.org/wiki/Natural-language_understanding)を参照してください。
* HTTPトリガーについてさらに詳しく知りたい場合は、[Microsoft DocsのAzure Functions HTTPトリガードキュメント](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)を参照してください。

## 課題

[タイマーをキャンセルする](assignment.md)

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。