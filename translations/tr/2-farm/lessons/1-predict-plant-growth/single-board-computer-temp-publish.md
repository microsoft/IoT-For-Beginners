<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T04:13:17+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "tr"
}
-->
# Sıcaklık Yayınlama - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi veya Sanal IoT Cihazı tarafından algılanan sıcaklık değerlerini MQTT üzerinden yayınlayacaksınız, böylece bu değerler daha sonra GDD hesaplaması için kullanılabilir.

## Sıcaklığı Yayınlama

Sıcaklık okunduktan sonra, MQTT üzerinden bir 'sunucu' koduna yayınlanabilir. Bu kod, değerleri okuyacak ve GDD hesaplaması için kullanılmaya hazır bir şekilde saklayacaktır.

### Görev - Sıcaklığı yayınlama

Cihazı, sıcaklık verilerini yayınlayacak şekilde programlayın.

1. `temperature-sensor` uygulama projesini henüz açmadıysanız açın.

1. MQTT'ye bağlanmak ve telemetri göndermek için ders 4'te yaptığınız adımları tekrarlayın. Aynı genel Mosquitto broker'ını kullanacaksınız.

    Bu adımlar şunlardır:

    - MQTT pip paketini ekleyin
    - MQTT broker'ına bağlanmak için kodu ekleyin
    - Telemetri yayınlamak için kodu ekleyin

    > ⚠️ Gerekirse [MQTT'ye bağlanma talimatlarına](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) ve [telemetri gönderme talimatlarına](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) ders 4'ten başvurun.

1. `client_name`in bu projenin adını yansıttığından emin olun:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Telemetri için, bir ışık değeri göndermek yerine, DHT sensöründen okunan sıcaklık değerini JSON belgesinde `temperature` adlı bir özellik olarak gönderin:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Sıcaklık değeri çok sık okunmak zorunda değil - kısa bir süre içinde çok fazla değişmeyecektir, bu yüzden `time.sleep`i 10 dakikaya ayarlayın:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 `sleep` fonksiyonu zamanı saniye cinsinden alır, bu yüzden okunabilirliği artırmak için değer bir hesaplama sonucu olarak geçirilir. Bir dakikada 60 saniye olduğundan, 10 x (bir dakikadaki 60 saniye) 10 dakikalık bir gecikme sağlar.

1. Kodu, ödevin önceki bölümündeki kodu çalıştırdığınız şekilde çalıştırın. Eğer bir sanal IoT cihazı kullanıyorsanız, CounterFit uygulamasının çalıştığından ve nem ve sıcaklık sensörlerinin doğru pinlerde oluşturulduğundan emin olun.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Bu kodu [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) klasöründe veya [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) klasöründe bulabilirsiniz.

😀 Cihazınızdan sıcaklığı telemetri olarak başarıyla yayınladınız.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.