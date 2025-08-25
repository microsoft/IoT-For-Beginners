<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-24T22:28:05+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "ja"
}
-->
# 手動リレー制御を追加する

## 手順

サーバーレスコードは、HTTPリクエストを含むさまざまな方法でトリガーされます。HTTPトリガーを使用してリレー制御に手動オーバーライドを追加することで、ウェブリクエストを通じてリレーをオンまたはオフにすることができます。

この課題では、学んだ内容を活用してデバイスにコマンドを送信し、リレーをオンとオフにするための2つのHTTPトリガーをFunctions Appに追加する必要があります。

いくつかのヒント:

* 以下のコマンドを使用して、既存のFunctions AppにHTTPトリガーを追加できます:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    `<trigger name>`をHTTPトリガーの名前に置き換えてください。`relay_on`や`relay_off`のような名前を使用すると良いでしょう。

* HTTPトリガーにはアクセス制御を設定できます。デフォルトでは、URLと一緒に関数固有のAPIキーを渡す必要があります。この課題では、この制限を解除して誰でも関数を実行できるようにします。そのためには、HTTPトリガーの`function.json`ファイル内の`authLevel`設定を以下のように更新してください:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 このアクセス制御について詳しくは、[Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys)をご覧ください。

* HTTPトリガーはデフォルトでGETおよびPOSTリクエストをサポートしています。つまり、ウェブブラウザを使用して呼び出すことができます。ウェブブラウザはGETリクエストを行います。

    Functions Appをローカルで実行すると、トリガーのURLが表示されます:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    URLをブラウザに貼り付けて`return`キーを押すか、ターミナルウィンドウのリンクを`Ctrl+クリック`（macOSでは`Cmd+クリック`）してデフォルトのブラウザで開いてください。これによりトリガーが実行されます。

    > 💁 URLには`/api`が含まれていることに注意してください - HTTPトリガーはデフォルトで`api`サブドメインにあります。

* Functions Appをデプロイすると、HTTPトリガーのURLは以下のようになります:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    `<functions app name>`はFunctions Appの名前、`<trigger name>`はトリガーの名前です。

## 評価基準

| 基準 | 優秀 | 適切 | 改善が必要 |
| -------- | --------- | -------- | ----------------- |
| HTTPトリガーの作成 | リレーをオンとオフにするための適切な名前を持つ2つのトリガーを作成した | 適切な名前を持つ1つのトリガーを作成した | トリガーを作成できなかった |
| HTTPトリガーからリレーを制御する | 両方のトリガーをIoT Hubに接続し、リレーを適切に制御できた | 1つのトリガーをIoT Hubに接続し、リレーを適切に制御できた | トリガーをIoT Hubに接続できなかった |

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。