<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T02:59:07+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "tr"
}
-->
# Bir Zamanlayıcı Ayarla - Wio Terminal

Bu dersin bu bölümünde, konuşmayı anlamak için sunucusuz kodunuzu çağıracak ve sonuçlara göre Wio Terminal üzerinde bir zamanlayıcı ayarlayacaksınız.

## Bir Zamanlayıcı Ayarla

Konuşmadan metne dönüşüm çağrısından gelen metin, LUIS tarafından işlenmek üzere sunucusuz kodunuza gönderilmelidir ve zamanlayıcı için saniye sayısı geri alınmalıdır. Bu saniye sayısı bir zamanlayıcı ayarlamak için kullanılabilir.

Mikrodenetleyiciler, Arduino'da birden fazla iş parçacığını doğal olarak desteklemez, bu nedenle Python veya diğer üst düzey dillerde bulabileceğiniz standart zamanlayıcı sınıfları yoktur. Bunun yerine, `loop` fonksiyonunda geçen zamanı ölçerek ve zaman dolduğunda fonksiyonları çağırarak çalışan zamanlayıcı kütüphanelerini kullanabilirsiniz.

### Görev - Metni Sunucusuz Fonksiyona Gönder

1. `smart-timer` projesini VS Code'da açın (eğer zaten açık değilse).

1. `config.h` başlık dosyasını açın ve fonksiyon uygulamanızın URL'sini ekleyin:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>`'yi, bir önceki dersin son adımında elde ettiğiniz, fonksiyon uygulamanızın URL'siyle değiştirin. Bu URL, yerel makinenizde çalışan fonksiyon uygulamasının IP adresine işaret etmelidir.

1. `src` klasöründe `language_understanding.h` adında yeni bir dosya oluşturun. Bu dosya, tanınan konuşmayı fonksiyon uygulamanıza göndermek ve LUIS kullanarak saniyelere dönüştürmek için bir sınıf tanımlamak amacıyla kullanılacaktır.

1. Bu dosyanın en üstüne aşağıdaki kodu ekleyin:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Bu, gerekli başlık dosyalarını içerir.

1. `LanguageUnderstanding` adında bir sınıf tanımlayın ve bu sınıfın bir örneğini bildirin:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Fonksiyon uygulamanızı çağırmak için bir WiFi istemcisi bildirmeniz gerekir. Sınıfın `private` bölümüne aşağıdaki kodu ekleyin:

    ```cpp
    WiFiClient _client;
    ```

1. Sınıfın `public` bölümünde, fonksiyon uygulamasını çağırmak için `GetTimerDuration` adında bir yöntem bildirin:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` yönteminde, fonksiyon uygulamasına gönderilecek JSON'u oluşturmak için aşağıdaki kodu ekleyin:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Bu, `GetTimerDuration` yöntemine geçirilen metni aşağıdaki JSON'a dönüştürür:

    ```json
    {
        "text" : "<text>"
    }
    ```

    Burada `<text>`, fonksiyona geçirilen metindir.

1. Bunun altına, fonksiyon uygulaması çağrısını yapmak için aşağıdaki kodu ekleyin:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Bu, JSON gövdesini göndererek ve yanıt kodunu alarak fonksiyon uygulamasına bir POST isteği yapar.

1. Bunun altına aşağıdaki kodu ekleyin:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Bu kod, yanıt kodunu kontrol eder. Eğer kod 200 (başarılı) ise, zamanlayıcı için saniye sayısı yanıt gövdesinden alınır. Aksi takdirde, seri monitöre bir hata gönderilir ve saniye sayısı 0 olarak ayarlanır.

1. Bu yöntemin sonuna aşağıdaki kodu ekleyerek HTTP bağlantısını kapatın ve saniye sayısını döndürün:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` dosyasında bu yeni başlığı dahil edin:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` fonksiyonunun sonunda, zamanlayıcı süresini almak için `GetTimerDuration` yöntemini çağırın:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Bu, `SpeechToText` sınıfından gelen metni zamanlayıcı için saniye sayısına dönüştürür.

### Görev - Bir Zamanlayıcı Ayarla

Saniye sayısı bir zamanlayıcı ayarlamak için kullanılabilir.

1. `platformio.ini` dosyasına bir zamanlayıcı ayarlamak için bir kütüphane eklemek üzere aşağıdaki bağımlılığı ekleyin:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Bu kütüphane için bir include direktifi ekleyin:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` fonksiyonunun üstüne aşağıdaki kodu ekleyin:

    ```cpp
    auto timer = timer_create_default();
    ```

    Bu kod, `timer` adında bir zamanlayıcı tanımlar.

1. Bunun altına aşağıdaki kodu ekleyin:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Bu `say` fonksiyonu, sonunda metni konuşmaya dönüştürecek, ancak şimdilik sadece geçirilen metni seri monitöre yazacaktır.

1. `say` fonksiyonunun altına aşağıdaki kodu ekleyin:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Bu, bir zamanlayıcı sona erdiğinde çağrılacak bir geri çağırma fonksiyonudur. Zamanlayıcı sona erdiğinde söylenecek bir mesaj alır. Zamanlayıcılar tekrar edebilir ve bu geri çağırmanın dönüş değeri ile kontrol edilebilir - bu, zamanlayıcının tekrar çalışmaması için `false` döndürür.

1. `processAudio` fonksiyonunun sonuna aşağıdaki kodu ekleyin:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Bu kod, toplam saniye sayısını kontrol eder ve eğer 0 ise, fonksiyon çağrısından döner, böylece zamanlayıcılar ayarlanmaz. Ardından toplam saniye sayısını dakika ve saniyeye dönüştürür.

1. Bu kodun altına, zamanlayıcı başlatıldığında söylenecek bir mesaj oluşturmak için aşağıdaki kodu ekleyin:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Bunun altına, zamanlayıcı sona erdiğinde söylenecek benzer bir mesaj oluşturmak için aşağıdaki kodu ekleyin:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Bundan sonra, zamanlayıcı başlatıldı mesajını söyleyin:

    ```cpp
    say(begin_message);
    ```

1. Bu fonksiyonun sonunda zamanlayıcıyı başlatın:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Bu, zamanlayıcıyı tetikler. Zamanlayıcı milisaniye cinsinden ayarlanır, bu nedenle toplam saniye sayısı milisaniyeye dönüştürmek için 1.000 ile çarpılır. `timerExpired` fonksiyonu geri çağırma olarak geçirilir ve `end_message` geri çağırmaya iletilmek üzere bir argüman olarak geçirilir. Bu geri çağırma yalnızca `void *` argümanlarını alır, bu nedenle dize uygun şekilde dönüştürülür.

1. Son olarak, zamanlayıcı *tik* atmalıdır ve bu `loop` fonksiyonunda yapılır. `loop` fonksiyonunun sonuna aşağıdaki kodu ekleyin:

    ```cpp
    timer.tick();
    ```

1. Bu kodu derleyin, Wio Terminal'inize yükleyin ve seri monitör üzerinden test edin. Seri monitörde `Ready` yazısını gördüğünüzde, C düğmesine (sol tarafta, güç anahtarına en yakın olan) basın ve konuşun. 4 saniyelik ses kaydedilecek, metne dönüştürülecek, ardından fonksiyon uygulamanıza gönderilecek ve bir zamanlayıcı ayarlanacaktır. Fonksiyon uygulamanızın yerel olarak çalıştığından emin olun.

    Zamanlayıcı başladığında ve sona erdiğinde göreceksiniz.

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
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Bu kodu [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) klasöründe bulabilirsiniz.

😀 Zamanlayıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.