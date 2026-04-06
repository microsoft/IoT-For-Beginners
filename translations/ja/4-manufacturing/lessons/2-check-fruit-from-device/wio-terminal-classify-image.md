# 画像を分類する - Wio Terminal

このレッスンのこの部分では、カメラで撮影した画像をCustom Visionサービスに送信し、分類を行います。

## 画像を分類する

Custom Visionサービスには、画像を分類するためにWio Terminalから呼び出せるREST APIがあります。このREST APIはHTTPS接続（安全なHTTP接続）を介してアクセスされます。

HTTPSエンドポイントとやり取りする際、クライアントコードはアクセスするサーバーから公開鍵証明書を要求し、それを使用して送信するトラフィックを暗号化する必要があります。ウェブブラウザはこれを自動的に行いますが、マイクロコントローラーはそうではありません。この証明書を手動で取得し、それを使用してREST APIへの安全な接続を作成する必要があります。これらの証明書は変更されないため、一度取得すればアプリケーションにハードコードすることが可能です。

これらの証明書には公開鍵が含まれており、秘密にする必要はありません。ソースコード内で使用したり、GitHubのような公共の場所で共有することができます。

### タスク - SSLクライアントを設定する

1. `fruit-quality-detector`アプリプロジェクトを開いていない場合は開きます。

1. `config.h`ヘッダーファイルを開き、以下を追加します：

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    これは*Microsoft Azure DigiCert Global Root G2証明書*です。これは多くのAzureサービスでグローバルに使用されている証明書の1つです。

    > 💁 この証明書を使用することを確認するには、macOSまたはLinuxで以下のコマンドを実行します。Windowsを使用している場合は、[Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn)を使用してこのコマンドを実行できます：
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > 出力にはDigiCert Global Root G2証明書がリストされます。

1. `main.cpp`を開き、以下のインクルードディレクティブを追加します：

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. インクルードディレクティブの下に、`WifiClientSecure`のインスタンスを宣言します：

    ```cpp
    WiFiClientSecure client;
    ```

    このクラスには、HTTPSを介してウェブエンドポイントと通信するコードが含まれています。

1. `connectWiFi`メソッド内で、WiFiClientSecureをDigiCert Global Root G2証明書を使用するよう設定します：

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### タスク - 画像を分類する

1. `platformio.ini`ファイルの`lib_deps`リストに以下を追加します：

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    これは[ArduinoJson](https://arduinojson.org)というArduino JSONライブラリをインポートし、REST APIからのJSONレスポンスをデコードするために使用されます。

1. `config.h`に、Custom Visionサービスの予測URLとキーの定数を追加します：

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>`をCustom Visionの予測URLに置き換えます。`<PREDICTION_KEY>`を予測キーに置き換えます。

1. `main.cpp`にArduinoJsonライブラリのインクルードディレクティブを追加します：

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp`の`buttonPressed`関数の上に以下の関数を追加します：

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    このコードは、まず`HTTPClient`を宣言します。このクラスにはREST APIとやり取りするためのメソッドが含まれています。その後、Azure公開鍵を設定した`WiFiClientSecure`インスタンスを使用して予測URLに接続します。

    接続後、ヘッダーを送信します。これは、REST APIに対して行われるリクエストに関する情報を提供します。`Content-Type`ヘッダーは、API呼び出しが生のバイナリデータを送信することを示し、`Prediction-Key`ヘッダーはCustom Visionの予測キーを渡します。

    次に、HTTPクライアントにPOSTリクエストを行い、バイト配列をアップロードします。これは、この関数が呼び出されたときにカメラで撮影されたJPEG画像を含みます。

    > 💁 POSTリクエストはデータを送信し、レスポンスを取得するためのものです。他にもGETリクエストのようなリクエストタイプがあり、データを取得します。GETリクエストはウェブブラウザがウェブページを読み込む際に使用されます。

    POSTリクエストはレスポンスステータスコードを返します。これらは明確に定義された値で、200は**OK**を意味し、POSTリクエストが成功したことを示します。

    > 💁 レスポンスステータスコードの一覧は[WikipediaのHTTPステータスコードのページ](https://wikipedia.org/wiki/List_of_HTTP_status_codes)で確認できます。

    200が返された場合、REST APIからの予測結果がJSONドキュメントとしてHTTPクライアントから読み取られます。このJSONは以下の形式です：

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    重要な部分は`predictions`配列です。これには予測が含まれており、各タグに対してタグ名と確率が含まれています。返される確率は0から1までの浮動小数点数で、0はタグに一致する可能性が0%、1はタグに一致する可能性が100%を意味します。

    > 💁 画像分類器は使用されたすべてのタグのパーセンテージを返します。各タグにはそのタグに画像が一致する確率が含まれます。

    このJSONはデコードされ、各タグの確率がシリアルモニターに送信されます。

1. `buttonPressed`関数内で、SDカードに保存するコードを`classifyImage`の呼び出しに置き換えるか、画像を書き込んだ後、**バッファを削除する前**に追加します：

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 SDカードに保存するコードを置き換える場合は、`setupSDCard`と`saveToSDCard`関数を削除してコードを整理できます。

1. コードをアップロードして実行します。カメラを果物に向けてCボタンを押します。シリアルモニターに出力が表示されます：

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    撮影された画像とこれらの値をCustom Visionの**Predictions**タブで確認できます。

    ![Custom Visionで予測されたバナナ。熟している確率56.8%、未熟な確率43.1%](../../../../../translated_images/ja/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 このコードは[code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal)フォルダーにあります。

😀 果物の品質分類プログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解について、当社は責任を負いません。