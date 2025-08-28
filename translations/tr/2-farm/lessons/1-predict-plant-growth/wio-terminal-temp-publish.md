<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T04:12:33+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "tr"
}
-->
# Sıcaklık Yayınlama - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal tarafından algılanan sıcaklık değerlerini MQTT üzerinden yayınlayarak, daha sonra GDD hesaplaması için kullanılabilir hale getireceksiniz.

## Sıcaklığı Yayınlama

Sıcaklık okunduktan sonra, MQTT üzerinden bir 'sunucu' koduna yayınlanabilir. Bu kod, değerleri okuyacak ve GDD hesaplaması için hazır bir şekilde saklayacaktır. Mikrodenetleyiciler, kutudan çıktığı haliyle internetten zaman okuyamaz ve gerçek zamanlı bir saatle zamanı takip edemez; cihazın gerekli donanıma sahip olduğu varsayılarak bu şekilde programlanması gerekir.

Bu dersi basitleştirmek için, sensör verileriyle birlikte zaman gönderilmeyecek. Bunun yerine, mesajlar alındığında zaman bilgisi sunucu kodu tarafından eklenebilir.

### Görev

Cihazı sıcaklık verilerini yayınlayacak şekilde programlayın.

1. `temperature-sensor` Wio Terminal projesini açın.

1. MQTT'ye bağlanmak ve telemetri göndermek için ders 4'te yaptığınız adımları tekrarlayın. Aynı genel Mosquitto broker'ını kullanacaksınız.

    Bu adımlar şunlardır:

    - `.ini` dosyasına Seeed WiFi ve MQTT kütüphanelerini ekleyin.
    - WiFi'ye bağlanmak için yapılandırma dosyasını ve kodu ekleyin.
    - MQTT broker'ına bağlanmak için kodu ekleyin.
    - Telemetri yayınlamak için kodu ekleyin.

    > ⚠️ Gerekirse [MQTT'ye bağlanma talimatlarına](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) ve [telemetri gönderme talimatlarına](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) ders 4'ten başvurun.

1. `config.h` başlık dosyasındaki `CLIENT_NAME`'in bu projeyi yansıttığından emin olun:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Telemetri için, bir ışık değeri göndermek yerine, DHT sensöründen okunan sıcaklık değerini JSON belgesindeki `temperature` adlı bir özelliğe gönderin. Bunun için `main.cpp` dosyasındaki `loop` fonksiyonunu değiştirin:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Sıcaklık değeri çok sık okunmasına gerek yoktur - kısa bir süre içinde çok fazla değişmeyecektir. Bu nedenle, `loop` fonksiyonundaki `delay` değerini 10 dakikaya ayarlayın:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` fonksiyonu zamanı milisaniye cinsinden alır, bu yüzden okunabilirliği artırmak için değer bir hesaplama sonucu olarak geçirilir. Bir saniyede 1.000ms, bir dakikada 60s olduğundan, 10 x (bir dakikadaki 60s) x (bir saniyedeki 1000ms) 10 dakikalık bir gecikme sağlar.

1. Bunu Wio Terminal'inize yükleyin ve sıcaklığın MQTT broker'ına gönderildiğini görmek için seri monitörü kullanın.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Bu kodu [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) klasöründe bulabilirsiniz.

😀 Cihazınızdan sıcaklığı telemetri olarak başarıyla yayınladınız.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.