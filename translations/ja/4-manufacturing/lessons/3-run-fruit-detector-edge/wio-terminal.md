<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-24T21:47:09+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ja"
}
-->
# IoT Edgeベースの画像分類器を使用して画像を分類する - Wio Terminal

このレッスンのこの部分では、IoT Edgeデバイス上で動作する画像分類器を使用します。

## IoT Edge分類器を使用する

IoTデバイスは、IoT Edge画像分類器を使用するようにリダイレクトできます。画像分類器のURLは `http://<IP address or name>/image` です。`<IP address or name>` を、IoT Edgeを実行しているコンピュータのIPアドレスまたはホスト名に置き換えてください。

### タスク - IoT Edge分類器を使用する

1. `fruit-quality-detector` アプリプロジェクトをまだ開いていない場合は開きます。

1. 画像分類器はHTTPを使用するREST APIとして動作しており、HTTPSではありません。そのため、HTTP呼び出しのみをサポートするWiFiクライアントを使用する必要があります。これにより、証明書は不要です。`config.h` ファイルから `CERTIFICATE` を削除してください。

1. `config.h` ファイル内の予測URLを新しいURLに更新する必要があります。また、`PREDICTION_KEY` は不要なので削除できます。

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` を分類器のURLに置き換えてください。

1. `main.cpp` 内で、WiFi Client Secureのインクルードディレクティブを標準のHTTPバージョンに変更します：

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` の宣言をHTTPバージョンに変更します：

    ```cpp
    WiFiClient client;
    ```

1. WiFiクライアントに証明書を設定する行を選択します。`connectWiFi` 関数内の `client.setCACert(CERTIFICATE);` 行を削除してください。

1. `classifyImage` 関数内で、ヘッダーに予測キーを設定する `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` 行を削除してください。

1. コードをアップロードして実行します。カメラを果物に向けてCボタンを押してください。シリアルモニターに出力が表示されます：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 このコードは [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) フォルダーにあります。

😀 果物の品質分類プログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。