<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T02:46:37+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "tr"
}
-->
# IoT Edge Tabanlı Görüntü Sınıflandırıcı Kullanarak Bir Görüntüyü Sınıflandırma - Wio Terminal

Bu dersin bu bölümünde, IoT Edge cihazında çalışan Görüntü Sınıflandırıcıyı kullanacaksınız.

## IoT Edge Sınıflandırıcıyı Kullanma

IoT cihazı, IoT Edge görüntü sınıflandırıcısını kullanacak şekilde yönlendirilebilir. Görüntü Sınıflandırıcının URL'si `http://<IP address or name>/image` şeklindedir. `<IP address or name>` kısmını, IoT Edge çalıştıran bilgisayarın IP adresi veya ana bilgisayar adıyla değiştirin.

### Görev - IoT Edge sınıflandırıcıyı kullanma

1. `fruit-quality-detector` uygulama projesini henüz açmadıysanız açın.

1. Görüntü sınıflandırıcı, HTTPS yerine HTTP kullanarak bir REST API olarak çalışır, bu nedenle çağrı yalnızca HTTP çağrılarıyla çalışan bir WiFi istemcisi kullanmalıdır. Bu, sertifikanın gerekli olmadığı anlamına gelir. `config.h` dosyasından `CERTIFICATE` kısmını silin.

1. `config.h` dosyasındaki tahmin URL'si yeni URL ile güncellenmelidir. Ayrıca, `PREDICTION_KEY` kısmını da silebilirsiniz çünkü bu gerekli değildir.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` kısmını sınıflandırıcınızın URL'siyle değiştirin.

1. `main.cpp` dosyasında, WiFi Client Secure için olan include direktifini standart HTTP sürümünü içe aktaracak şekilde değiştirin:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` bildiriminin HTTP sürümüne dönüştürülmesini sağlayın:

    ```cpp
    WiFiClient client;
    ```

1. WiFi istemcisinde sertifikayı ayarlayan satırı seçin. `connectWiFi` fonksiyonundan `client.setCACert(CERTIFICATE);` satırını kaldırın.

1. `classifyImage` fonksiyonunda, başlıkta tahmin anahtarını ayarlayan `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` satırını kaldırın.

1. Kodunuzu yükleyin ve çalıştırın. Kamerayı bir meyveye doğrultun ve C düğmesine basın. Seri monitörde çıktıyı göreceksiniz:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Bu kodu [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) klasöründe bulabilirsiniz.

😀 Meyve kalite sınıflandırıcı programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.