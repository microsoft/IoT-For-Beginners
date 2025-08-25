<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T00:29:01+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ja"
}
-->
# 音声からテキストへ - Wio Terminal

このレッスンのこの部分では、音声サービスを使用してキャプチャした音声をテキストに変換するコードを書きます。

## 音声を音声サービスに送信する

音声はREST APIを使用して音声サービスに送信できます。音声サービスを使用するには、まずアクセストークンをリクエストし、そのトークンを使用してREST APIにアクセスする必要があります。これらのアクセストークンは10分後に期限切れになるため、コードは定期的にトークンをリクエストして、常に最新の状態を保つ必要があります。

### タスク - アクセストークンを取得する

1. `smart-timer`プロジェクトを開いていない場合は開きます。

1. WiFiにアクセスし、JSONを処理するために、以下のライブラリ依存関係を`platformio.ini`ファイルに追加します：

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. 以下のコードを`config.h`ヘッダーファイルに追加します：

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>`と`<PASSWORD>`をWiFiの関連する値に置き換えます。

    `<API_KEY>`を音声サービスリソースのAPIキーに置き換えます。`<LOCATION>`を音声サービスリソースを作成した際に使用した場所に置き換えます。

    `<LANGUAGE>`を話す言語のロケール名に置き換えます。例えば、英語の場合は`en-GB`、広東語の場合は`zn-HK`です。サポートされている言語とそのロケール名のリストは、[Microsoft Docsの言語と音声サポートのドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)で確認できます。

    `TOKEN_URL`定数は、ロケーションを含まないトークン発行者のURLです。これは後でロケーションと組み合わせて完全なURLを取得します。

1. Custom Visionに接続する場合と同様に、トークン発行サービスに接続するにはHTTPS接続を使用する必要があります。`config.h`の末尾に以下のコードを追加します：

    ```cpp
    const char *TOKEN_CERTIFICATE =
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

    これは、Custom Visionに接続する際に使用したのと同じ証明書です。

1. `main.cpp`ファイルの先頭にWiFiヘッダーファイルとconfigヘッダーファイルのインクルードを追加します：

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `main.cpp`の`setup`関数の上にWiFiに接続するコードを追加します：

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

1. シリアル接続が確立された後、`setup`関数からこの関数を呼び出します：

    ```cpp
    connectWiFi();
    ```

1. `src`フォルダに`speech_to_text.h`という新しいヘッダーファイルを作成します。このヘッダーファイルに以下のコードを追加します：

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    これには、HTTP接続、設定、`mic.h`ヘッダーファイルに必要なヘッダーファイルが含まれ、`SpeechToText`というクラスを定義し、後で使用できるそのクラスのインスタンスを宣言します。

1. このクラスの`private`セクションに以下の2つのフィールドを追加します：

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client`はHTTPSを使用するWiFiクライアントで、アクセストークンを取得するために使用されます。このトークンは`_access_token`に保存されます。

1. `private`セクションに以下のメソッドを追加します：

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    このコードは、音声リソースのロケーションを使用してトークン発行者APIのURLを構築します。その後、トークンエンドポイント証明書で設定されたWiFiクライアントを使用してWebリクエストを行うための`HTTPClient`を作成します。APIキーを呼び出しのヘッダーとして設定します。その後、証明書を取得するためにPOSTリクエストを行い、エラーが発生した場合は再試行します。最後にアクセストークンが返されます。

1. `public`セクションにアクセストークンを取得するメソッドを追加します。このメソッドは、後のレッスンでテキストを音声に変換する際に必要になります。

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public`セクションにトークンクライアントを設定する`init`メソッドを追加します：

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    これにより、WiFiクライアントに証明書が設定され、アクセストークンが取得されます。

1. `main.cpp`にこの新しいヘッダーファイルをインクルードディレクティブに追加します：

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup`関数の最後に、`mic.init`呼び出しの後、シリアルモニターに`Ready`が書き込まれる前に`SpeechToText`クラスを初期化します：

    ```cpp
    speechToText.init();
    ```

### タスク - フラッシュメモリから音声を読み取る

1. このレッスンの以前の部分で、音声はフラッシュメモリに記録されました。この音声をSpeech Services REST APIに送信する必要があるため、フラッシュメモリから読み取る必要があります。音声をメモリ内バッファにロードすることはできません。サイズが大きすぎるためです。REST呼び出しを行う`HTTPClient`クラスは、Arduino Streamを使用してデータをストリームできます。Streamはデータを小さなチャンクでロードし、1回のリクエストで1つのチャンクを送信します。`read`を呼び出すたびに、次のデータブロックが返されます。Arduino Streamを作成してフラッシュメモリから読み取ることができます。`src`フォルダに`flash_stream.h`という新しいファイルを作成し、以下のコードを追加します：

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    これにより、Arduinoの`Stream`クラスから派生した`FlashStream`クラスが宣言されます。このクラスは抽象クラスであり、派生クラスはインスタンス化される前にいくつかのメソッドを実装する必要があります。これらのメソッドはこのクラスで定義されています。

    ✅ Arduino Streamsについて詳しくは、[Arduino Streamのドキュメント](https://www.arduino.cc/reference/en/language/functions/communication/stream/)をご覧ください。

1. `private`セクションに以下のフィールドを追加します：

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    これにより、フラッシュメモリから読み取ったデータを一時的に保存するバッファ、バッファから読み取る現在の位置、フラッシュメモリから読み取る現在のアドレス、およびフラッシュメモリデバイスが定義されます。

1. `private`セクションに以下のメソッドを追加します：

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    このコードは、現在のアドレスでフラッシュメモリから読み取り、データをバッファに保存します。その後、次回の呼び出しで次のメモリブロックを読み取るようにアドレスをインクリメントします。バッファのサイズは、HTTPClientが一度にREST APIに送信する最大チャンクに基づいています。

    > 💁 フラッシュメモリを消去するにはグレインサイズを使用する必要がありますが、読み取りはその限りではありません。

1. このクラスの`public`セクションにコンストラクタを追加します：

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    このコンストラクタは、フラッシュメモリブロックの先頭から読み取りを開始するようにすべてのフィールドを設定し、最初のデータチャンクをバッファにロードします。

1. `write`メソッドを実装します。このストリームはデータを読み取るだけなので、何もせずに0を返します：

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek`メソッドを実装します。これは現在の位置のデータを返し、ストリームを進めません。`peek`を複数回呼び出しても、ストリームからデータが読み取られない限り、常に同じデータが返されます。

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available`関数を実装します。これはストリームから読み取れるバイト数を返します。ストリームが完了した場合は-1を返します。このクラスでは、利用可能な最大値はHTTPClientのチャンクサイズを超えることはありません。このストリームがHTTPクライアントで使用されると、HTTPクライアントはこの関数を呼び出して利用可能なデータ量を確認し、その量のデータをREST APIに送信します。各チャンクがHTTPクライアントのチャンクサイズを超えないようにするため、利用可能なデータがそれ以上の場合はチャンクサイズを返します。それ以下の場合は利用可能なデータ量を返します。すべてのデータがストリームされた後は-1を返します。

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. `read`メソッドを実装して、バッファから次のバイトを返し、位置をインクリメントします。位置がバッファのサイズを超えた場合、フラッシュメモリから次のブロックをバッファに読み込み、位置をリセットします。

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. `speech_to_text.h`ヘッダーファイルに、この新しいヘッダーファイルのインクルードディレクティブを追加します：

    ```cpp
    #include "flash_stream.h"
    ```

### タスク - 音声をテキストに変換する

1. 音声はREST APIを介して音声サービスに送信することでテキストに変換できます。このREST APIはトークン発行者とは異なる証明書を持っているため、以下のコードを`config.h`ヘッダーファイルに追加してこの証明書を定義します：

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. このファイルにロケーションを含まない音声URLの定数を追加します。これは後でロケーションと言語と組み合わせて完全なURLを取得します。

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h`ヘッダーファイルの`SpeechToText`クラスの`private`セクションに、音声証明書を使用するWiFiクライアントのフィールドを定義します：

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init`メソッドで、このWiFiクライアントに証明書を設定します：

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText`クラスの`public`セクションに、音声をテキストに変換するメソッドを定義する以下のコードを追加します：

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. このメソッドに、音声証明書で設定されたWiFiクライアントを使用し、ロケーションと言語で設定された音声URLを使用してHTTPクライアントを作成する以下のコードを追加します：

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. 接続にいくつかのヘッダーを設定する必要があります：

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    これにより、アクセストークンを使用した認証、サンプルレートを使用した音声フォーマット、およびクライアントが結果をJSONとして期待していることが設定されます。

1. この後、REST API呼び出しを行う以下のコードを追加します：

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    これにより、`FlashStream`が作成され、REST APIにデータをストリームするために使用されます。

1. この下に以下のコードを追加します：

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    このコードはレスポンスコードを確認します。

    コードが200（成功の場合）の場合、結果が取得され、JSONからデコードされ、`DisplayText`プロパティが`text`変数に設定されます。これは音声のテキストバージョンが返されるプロパティです。

    レスポンスコードが401の場合、アクセストークンが期限切れになっています（これらのトークンは10分間のみ有効です）。新しいアクセストークンがリクエストされ、再度呼び出しが行われます。

    それ以外の場合、エラーがシリアルモニターに送信され、`text`は空白のままです。

1. このメソッドの最後に以下のコードを追加してHTTPクライアントを閉じ、テキストを返します：

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp`で、この新しい`convertSpeechToText`メソッドを`processAudio`関数内で呼び出し、シリアルモニターに音声をログ出力します：

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. このコードをビルドし、Wio Terminalにアップロードして、シリアルモニターでテストします。シリアルモニターに`Ready`と表示されたら、Cボタン（左側で電源スイッチに最も近いボタン）を押して話します。4秒間の音声がキャプチャされ、テキストに変換されます。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    ```

> 💁 このコードは[code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal)フォルダにあります。

😀 音声からテキストへのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。