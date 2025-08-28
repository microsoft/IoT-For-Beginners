<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-28T03:07:23+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "tr"
}
-->
# Konuşmadan Metne - Wio Terminal

Bu dersin bu bölümünde, yakalanan seslerdeki konuşmayı konuşma hizmetini kullanarak metne dönüştürmek için kod yazacaksınız.

## Sesi konuşma hizmetine gönderin

Ses, REST API kullanılarak konuşma hizmetine gönderilebilir. Konuşma hizmetini kullanmak için önce bir erişim belirteci (access token) talep etmeniz, ardından bu belirteci REST API'ye erişmek için kullanmanız gerekir. Bu erişim belirteçleri 10 dakika sonra süresi dolar, bu nedenle kodunuzun bunları düzenli olarak talep etmesi ve her zaman güncel olmasını sağlaması gerekir.

### Görev - bir erişim belirteci alın

1. `smart-timer` projesini henüz açmadıysanız açın.

1. WiFi'ye erişmek ve JSON'u işlemek için `platformio.ini` dosyasına aşağıdaki kütüphane bağımlılıklarını ekleyin:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` başlık dosyasına aşağıdaki kodu ekleyin:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` ve `<PASSWORD>` değerlerini WiFi bilgilerinizle değiştirin.

    `<API_KEY>` değerini konuşma hizmeti kaynağınızın API anahtarıyla değiştirin. `<LOCATION>` değerini konuşma hizmeti kaynağını oluştururken kullandığınız konumla değiştirin.

    `<LANGUAGE>` değerini konuşacağınız dilin yerel ayar adıyla değiştirin, örneğin İngilizce için `en-GB` veya Kantonca için `zn-HK`. Desteklenen dillerin ve yerel ayar adlarının bir listesini [Microsoft dokümanlarındaki Dil ve ses desteği dokümanında](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) bulabilirsiniz.

    `TOKEN_URL` sabiti, konum olmadan belirteç sağlayıcısının URL'sidir. Bu, tam URL'yi elde etmek için daha sonra konumla birleştirilecektir.

1. Custom Vision'a bağlanırken olduğu gibi, belirteç sağlayıcı hizmetine bağlanmak için bir HTTPS bağlantısı kullanmanız gerekecek. `config.h` dosyasının sonuna aşağıdaki kodu ekleyin:

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

    Bu, Custom Vision'a bağlanırken kullandığınız aynı sertifikadır.

1. `main.cpp` dosyasının üst kısmına WiFi başlık dosyası ve config başlık dosyası için bir include ekleyin:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `main.cpp` dosyasında `setup` fonksiyonunun üstüne WiFi'ye bağlanmak için kod ekleyin:

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

1. Bu fonksiyonu, seri bağlantı kurulduktan sonra `setup` fonksiyonundan çağırın:

    ```cpp
    connectWiFi();
    ```

1. `src` klasöründe `speech_to_text.h` adında yeni bir başlık dosyası oluşturun. Bu başlık dosyasına aşağıdaki kodu ekleyin:

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

    Bu, bir HTTP bağlantısı, yapılandırma ve `mic.h` başlık dosyası için gerekli başlık dosyalarını içerir ve daha sonra kullanılabilecek bir sınıf örneği tanımlamadan önce `SpeechToText` adlı bir sınıf tanımlar.

1. Bu sınıfın `private` bölümüne aşağıdaki 2 alanı ekleyin:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client`, HTTPS kullanan bir WiFi Client'tır ve erişim belirtecini almak için kullanılacaktır. Bu belirteç daha sonra `_access_token` içinde saklanacaktır.

1. `private` bölümüne aşağıdaki yöntemi ekleyin:

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

    Bu kod, konuşma kaynağının konumunu kullanarak belirteç sağlayıcı API'si için URL'yi oluşturur. Daha sonra bir `HTTPClient` oluşturur ve web isteğini yapmak için belirteç uç noktalarının sertifikasıyla yapılandırılmış WiFi istemcisini kullanır. API anahtarını çağrı için bir başlık olarak ayarlar. Daha sonra belirteci almak için bir POST isteği yapar ve herhangi bir hata alırsa yeniden dener. Son olarak erişim belirteci döndürülür.

1. `public` bölümüne, erişim belirteci almak için bir yöntem ekleyin. Bu, sonraki derslerde metni konuşmaya dönüştürmek için gerekli olacaktır.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` bölümüne, belirteç istemcisini ayarlayan bir `init` yöntemi ekleyin:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Bu, WiFi istemcisinde sertifikayı ayarlar ve ardından erişim belirtecini alır.

1. `main.cpp` dosyasında, include yönergelerine bu yeni başlık dosyasını ekleyin:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` fonksiyonunun sonunda, `mic.init` çağrısından sonra ancak `Ready` seri monitöre yazılmadan önce `SpeechToText` sınıfını başlatın:

    ```cpp
    speechToText.init();
    ```

### Görev - flash bellekteki sesi okuyun

1. Dersin önceki bir bölümünde, ses flash belleğe kaydedildi. Bu ses, Konuşma Hizmetleri REST API'sine gönderilmesi gerektiğinden, flash bellekten okunmalıdır. Bellek içi bir arabelleğe yüklenemez çünkü çok büyük olur. REST çağrıları yapan `HTTPClient` sınıfı, bir Arduino Stream kullanarak verileri akış olarak gönderebilir - bu sınıf, verileri küçük parçalara ayırarak yükleyebilir ve her bir parçayı sırayla isteğin bir parçası olarak gönderebilir. Bir akıştan her `read` çağrısı, bir sonraki veri bloğunu döndürür. Flash bellekten okuyabilen bir Arduino akışı oluşturulabilir. `src` klasöründe `flash_stream.h` adında yeni bir dosya oluşturun ve aşağıdaki kodu ekleyin:

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

    Bu, Arduino `Stream` sınıfından türeyen `FlashStream` sınıfını tanımlar. Bu soyut bir sınıftır - türetilen sınıflar, sınıfın örneklendirilebilmesi için birkaç yöntemi uygulamalıdır ve bu yöntemler bu sınıfta tanımlanmıştır.

    ✅ Arduino Akışları hakkında daha fazla bilgi için [Arduino Stream dokümantasyonunu](https://www.arduino.cc/reference/en/language/functions/communication/stream/) okuyun.

1. `private` bölümüne aşağıdaki alanları ekleyin:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Bu, flash bellekten okunan verileri depolamak için geçici bir arabellek, arabellekten okuma sırasında mevcut konumu, flash bellekten okuma için mevcut adresi ve flash bellek cihazını depolamak için alanlar tanımlar.

1. `private` bölümüne aşağıdaki yöntemi ekleyin:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Bu kod, mevcut adreste flash bellekten okur ve verileri bir arabelleğe depolar. Daha sonra adresi artırır, böylece bir sonraki çağrı bir sonraki bellek bloğunu okur. Arabellek, REST API'ye bir kerede gönderilecek en büyük parçaya göre boyutlandırılmıştır.

    > 💁 Flash belleği silmek, tahıl boyutunu kullanarak yapılmalıdır, ancak okuma için bu geçerli değildir.

1. Bu sınıfın `public` bölümüne bir kurucu ekleyin:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Bu kurucu, flash bellek bloğunun başlangıcından okumaya başlamak için tüm alanları ayarlar ve ilk veri bloğunu arabelleğe yükler.

1. `write` yöntemini uygulayın. Bu akış yalnızca veri okuyacaktır, bu nedenle hiçbir şey yapmaz ve 0 döndürür:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` yöntemini uygulayın. Bu, akışı ilerletmeden mevcut konumdaki verileri döndürür. Akıştan veri okunmadığı sürece `peek` birden fazla kez çağrıldığında her zaman aynı veriyi döndürür.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` fonksiyonunu uygulayın. Bu, akıştan kaç bayt okunabileceğini döndürür veya akış tamamlanmışsa -1 döndürür. Bu sınıf için, mevcut olan maksimum miktar HTTPClient'ın parça boyutundan fazla olmayacaktır. Bu akış HTTP istemcisinde kullanıldığında, istemci ne kadar veri mevcut olduğunu görmek için bu fonksiyonu çağırır ve ardından REST API'ye göndermek için o kadar veri ister. Her parçanın HTTP istemcisinin parça boyutundan fazla olmamasını istiyoruz, bu nedenle mevcut olan daha fazlaysa, parça boyutu döndürülür. Daha azsa, mevcut olan döndürülür. Tüm veriler akış olarak gönderildikten sonra -1 döndürülür.

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

1. `read` yöntemini uygulayın, bu yöntem arabellekten bir sonraki baytı döndürür ve konumu artırır. Konum arabellek boyutunu aşarsa, arabellek flash bellekten bir sonraki blokla doldurulur ve konum sıfırlanır.

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

1. `speech_to_text.h` başlık dosyasında, bu yeni başlık dosyası için bir include yönergesi ekleyin:

    ```cpp
    #include "flash_stream.h"
    ```

### Görev - konuşmayı metne dönüştürün

1. Konuşma, sesi REST API aracılığıyla Konuşma Hizmetine göndererek metne dönüştürülebilir. Bu REST API, belirteç sağlayıcıdan farklı bir sertifikaya sahiptir, bu nedenle `config.h` başlık dosyasına bu sertifikayı tanımlamak için aşağıdaki kodu ekleyin:

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

1. Bu dosyaya, konum olmadan konuşma URL'si için bir sabit ekleyin. Bu, daha sonra konum ve dil ile birleştirilerek tam URL elde edilecektir.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` başlık dosyasında, `SpeechToText` sınıfının `private` bölümünde, konuşma sertifikasıyla bir WiFi Client için bir alan tanımlayın:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` yönteminde, bu WiFi Client'ta sertifikayı ayarlayın:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` sınıfının `public` bölümüne, konuşmayı metne dönüştürmek için bir yöntem tanımlamak üzere aşağıdaki kodu ekleyin:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Bu yönteme, konuşma sertifikasıyla yapılandırılmış WiFi istemcisini kullanarak bir HTTP istemcisi oluşturmak ve konum ve dil ile ayarlanmış konuşma URL'sini kullanmak için aşağıdaki kodu ekleyin:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Bağlantı üzerinde bazı başlıklar ayarlanmalıdır:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Bu, yetkilendirme için erişim belirteci, ses formatı için örnekleme oranı ve istemcinin sonucu JSON olarak beklediğini belirten başlıkları ayarlar.

1. Bunun ardından, REST API çağrısını yapmak için aşağıdaki kodu ekleyin:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Bu, bir `FlashStream` oluşturur ve REST API'ye veri akışı yapmak için kullanır.

1. Bunun altına aşağıdaki kodu ekleyin:

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

    Bu kod, yanıt kodunu kontrol eder.

    Eğer 200 ise, yani başarı kodu, sonuç alınır, JSON'dan çözülür ve `DisplayText` özelliği `text` değişkenine ayarlanır. Bu özellik, konuşmanın metin sürümünün döndürüldüğü özelliktir.

    Eğer yanıt kodu 401 ise, erişim belirteci süresi dolmuş demektir (bu belirteçler yalnızca 10 dakika geçerlidir). Yeni bir erişim belirteci talep edilir ve çağrı tekrar yapılır.

    Aksi takdirde, seri monitöre bir hata gönderilir ve `text` boş bırakılır.

1. Bu yöntemin sonuna, HTTP istemcisini kapatmak ve metni döndürmek için aşağıdaki kodu ekleyin:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp` dosyasında, bu yeni `convertSpeechToText` yöntemini `processAudio` fonksiyonunda çağırın ve ardından konuşmayı seri monitöre yazdırın:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Bu kodu derleyin, Wio Terminal cihazınıza yükleyin ve seri monitör üzerinden test edin. Seri monitörde `Ready` yazısını gördüğünüzde, C düğmesine (sol tarafta, güç anahtarına en yakın olan) basın ve konuşun. 4 saniyelik ses kaydedilecek ve ardından metne dönüştürülecektir.

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

> 💁 Bu kodu [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) klasöründe bulabilirsiniz.

😀 Konuşmadan metne programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.