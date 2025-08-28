<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T03:32:49+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "tr"
}
-->
# Gece Lambanızı İnternet Üzerinden Kontrol Edin - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal cihazınızdan ışık seviyeleriyle ilgili telemetriyi MQTT brokerına göndereceksiniz.

## JSON Arduino Kütüphanelerini Yükleyin

MQTT üzerinden mesaj göndermenin popüler bir yolu JSON kullanmaktır. JSON belgelerini okumayı ve yazmayı kolaylaştıran bir Arduino kütüphanesi bulunmaktadır.

### Görev

Arduino JSON kütüphanesini yükleyin.

1. VS Code'da gece lambası projesini açın.

1. `platformio.ini` dosyasındaki `lib_deps` listesine şu ek satırı ekleyin:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Bu, bir Arduino JSON kütüphanesi olan [ArduinoJson](https://arduinojson.org)'u içe aktarır.

## Telemetri Yayınlayın

Bir sonraki adım, telemetri ile bir JSON belgesi oluşturmak ve bunu MQTT brokerına göndermektir.

### Görev - telemetri yayınlama

Telemetriyi MQTT brokerına yayınlayın.

1. MQTT brokerı için telemetri konu adını tanımlamak üzere `config.h` dosyasının sonuna şu kodu ekleyin:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC`, cihazın ışık seviyelerini yayınlayacağı konudur.

1. `main.cpp` dosyasını açın.

1. Dosyanın en üstüne şu `#include` yönergesini ekleyin:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` fonksiyonunun içine, `delay` satırından hemen önce şu kodu ekleyin:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Bu kod, ışık seviyesini okur ve ArduinoJson kullanarak bu seviyeyi içeren bir JSON belgesi oluşturur. Daha sonra bu belge bir dizeye dönüştürülür ve MQTT istemcisi tarafından telemetri MQTT konusunda yayınlanır.

1. Kodu Wio Terminal cihazınıza yükleyin ve ışık seviyelerinin MQTT brokerına gönderildiğini görmek için Seri Monitör'ü kullanın.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Bu kodu [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) klasöründe bulabilirsiniz.

😀 Cihazınızdan başarıyla telemetri gönderdiniz.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.