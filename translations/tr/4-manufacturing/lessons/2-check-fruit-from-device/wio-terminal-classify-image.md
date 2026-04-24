# Bir Görüntüyü Sınıflandır - Wio Terminal

Bu dersin bu bölümünde, kamera tarafından yakalanan görüntüyü sınıflandırmak için Custom Vision servisine göndereceksiniz.

## Bir Görüntüyü Sınıflandır

Custom Vision servisi, Wio Terminal'den görüntüleri sınıflandırmak için çağırabileceğiniz bir REST API'ye sahiptir. Bu REST API, güvenli bir HTTP bağlantısı olan HTTPS üzerinden erişilir.

HTTPS uç noktalarıyla etkileşim kurarken, istemci kodunun erişilen sunucudan genel anahtar sertifikasını talep etmesi ve gönderdiği trafiği şifrelemek için bunu kullanması gerekir. Web tarayıcınız bunu otomatik olarak yapar, ancak mikrodenetleyiciler yapmaz. Bu sertifikayı manuel olarak talep etmeniz ve REST API'ye güvenli bir bağlantı oluşturmak için kullanmanız gerekecek. Bu sertifikalar değişmez, bu nedenle bir sertifikaya sahip olduğunuzda, uygulamanızda sabit kodlanabilir.

Bu sertifikalar genel anahtarlar içerir ve güvenli tutulmaları gerekmez. Bunları kaynak kodunuzda kullanabilir ve GitHub gibi yerlerde herkese açık olarak paylaşabilirsiniz.

### Görev - SSL istemcisi kurma

1. `fruit-quality-detector` uygulama projesini henüz açmadıysanız açın.

1. `config.h` başlık dosyasını açın ve aşağıdakileri ekleyin:

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

    Bu, *Microsoft Azure DigiCert Global Root G2 sertifikasıdır* - dünya genelinde birçok Azure hizmeti tarafından kullanılan sertifikalardan biridir.

    > 💁 Bu sertifikanın kullanılacak sertifika olduğunu görmek için macOS veya Linux'ta aşağıdaki komutu çalıştırın. Windows kullanıyorsanız, bu komutu [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) kullanarak çalıştırabilirsiniz:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Çıktı, DigiCert Global Root G2 sertifikasını listeleyecektir.

1. `main.cpp` dosyasını açın ve aşağıdaki include yönergesini ekleyin:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Include yönergelerinin altına, bir `WifiClientSecure` örneği tanımlayın:

    ```cpp
    WiFiClientSecure client;
    ```

    Bu sınıf, HTTPS üzerinden web uç noktalarıyla iletişim kurmak için kod içerir.

1. `connectWiFi` yönteminde, WiFiClientSecure'ü DigiCert Global Root G2 sertifikasını kullanacak şekilde ayarlayın:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Görev - Bir görüntüyü sınıflandırma

1. `platformio.ini` dosyasındaki `lib_deps` listesine ek bir satır olarak aşağıdakileri ekleyin:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Bu, [ArduinoJson](https://arduinojson.org) adlı bir Arduino JSON kütüphanesini içe aktarır ve REST API'den gelen JSON yanıtını çözmek için kullanılacaktır.

1. `config.h` dosyasında, Custom Vision servisinden tahmin URL'si ve Anahtarı için sabitler ekleyin:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` yerine Custom Vision'dan tahmin URL'sini yazın. `<PREDICTION_KEY>` yerine tahmin anahtarını yazın.

1. `main.cpp` dosyasında, ArduinoJson kütüphanesi için bir include yönergesi ekleyin:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `main.cpp` dosyasına, `buttonPressed` fonksiyonunun üstüne aşağıdaki fonksiyonu ekleyin:

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

    Bu kod, bir REST API ile etkileşim kurmak için yöntemler içeren bir `HTTPClient` tanımlayarak başlar. Daha sonra istemciyi, Azure genel anahtarıyla ayarlanmış olan `WiFiClientSecure` örneğini kullanarak tahmin URL'sine bağlar.

    Bağlandıktan sonra, REST API'ye yapılacak istekle ilgili bilgileri içeren başlıklar gönderir. `Content-Type` başlığı, API çağrısının ham ikili veri göndereceğini belirtir, `Prediction-Key` başlığı ise Custom Vision tahmin anahtarını iletir.

    Daha sonra, HTTP istemcisine bir POST isteği yapılır ve bir bayt dizisi yüklenir. Bu, bu fonksiyon çağrıldığında kameradan yakalanan JPEG görüntüsünü içerecektir.

    > 💁 POST istekleri, veri göndermek ve bir yanıt almak için kullanılır. GET istekleri gibi başka istek türleri de vardır; bunlar veri almak için kullanılır. Web tarayıcınız, web sayfalarını yüklemek için GET isteklerini kullanır.

    POST isteği bir yanıt durum kodu döndürür. Bunlar iyi tanımlanmış değerlerdir ve 200, **OK** anlamına gelir - POST isteği başarılı olmuştur.

    > 💁 Tüm yanıt durum kodlarını [Wikipedia'daki HTTP durum kodları listesi](https://wikipedia.org/wiki/List_of_HTTP_status_codes) sayfasında görebilirsiniz.

    Eğer 200 dönerse, sonuç HTTP istemcisinden okunur. Bu, tahmin sonuçlarını bir JSON belgesi olarak içeren REST API'den gelen bir metin yanıtıdır. JSON şu formatta olur:

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

    Burada önemli olan kısım `predictions` dizisidir. Bu, her bir etiket için etiket adını ve olasılığı içeren tahminleri içerir. Döndürülen olasılıklar, 0-1 arasında kayan noktalı sayılardır; 0, etiketle eşleşme olasılığının %0 olduğunu, 1 ise %100 olduğunu belirtir.

    > 💁 Görüntü sınıflandırıcılar, kullanılan tüm etiketler için yüzdeleri döndürür. Her etiket, görüntünün o etiketle eşleşme olasılığını gösteren bir olasılığa sahip olacaktır.

    Bu JSON çözülür ve her etiket için olasılıklar seri monitörüne gönderilir.

1. `buttonPressed` fonksiyonunda, SD karta kaydetme kodunu `classifyImage` fonksiyonunu çağıracak şekilde değiştirin veya görüntü yazıldıktan sonra, ancak **buffer silinmeden önce** ekleyin:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Eğer SD karta kaydetme kodunu değiştirirseniz, `setupSDCard` ve `saveToSDCard` fonksiyonlarını kaldırarak kodunuzu temizleyebilirsiniz.

1. Kodunuzu yükleyin ve çalıştırın. Kamerayı bir meyveye doğrultun ve C düğmesine basın. Seri monitörde çıktıyı göreceksiniz:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Çekilen görüntüyü ve bu değerleri Custom Vision'daki **Predictions** sekmesinde görebileceksiniz.

    ![Custom Vision'da bir muz, %56.8 olgun ve %43.1 olgunlaşmamış olarak tahmin edildi](../../../../../translated_images/tr/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Bu kodu [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) klasöründe bulabilirsiniz.

😀 Meyve kalite sınıflandırıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.