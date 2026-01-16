<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T03:49:36+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "tr"
}
-->
# Nesne algılayıcınızı IoT cihazınızdan çağırın - Wio Terminal

Nesne algılayıcınız yayınlandıktan sonra, IoT cihazınızdan kullanılabilir.

## Görüntü sınıflandırıcı projesini kopyalayın

Stok algılayıcınızın büyük bir kısmı, önceki bir derste oluşturduğunuz görüntü sınıflandırıcı ile aynıdır.

### Görev - görüntü sınıflandırıcı projesini kopyalayın

1. ArduCam'i Wio Terminal'inize bağlayın, [üretim projesinin 2. dersindeki adımları](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) takip ederek.

    Kamerayı sabit bir pozisyonda tutmak isteyebilirsiniz, örneğin kabloyu bir kutunun veya tenekenin üzerine asarak ya da kamerayı çift taraflı bantla bir kutuya sabitleyerek.

1. PlatformIO kullanarak yepyeni bir Wio Terminal projesi oluşturun. Bu projeye `stock-counter` adını verin.

1. Kameradan görüntü yakalamak için [üretim projesinin 2. dersindeki adımları](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) tekrarlayın.

1. Görüntü sınıflandırıcıyı çağırmak için [üretim projesinin 2. dersindeki adımları](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) tekrarlayın. Bu kodun büyük bir kısmı nesneleri algılamak için yeniden kullanılacaktır.

## Kodunuzu sınıflandırıcıdan görüntü algılayıcıya dönüştürün

Görüntüleri sınıflandırmak için kullandığınız kod, nesneleri algılamak için kullanılan koda oldukça benzerdir. Ana fark, Custom Vision'dan aldığınız çağrılan URL ve çağrının sonuçlarıdır.

### Görev - kodu sınıflandırıcıdan görüntü algılayıcıya dönüştürün

1. `main.cpp` dosyasının üst kısmına aşağıdaki include direktifini ekleyin:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` fonksiyonunun adını `detectStock` olarak değiştirin, hem fonksiyonun adını hem de `buttonPressed` fonksiyonundaki çağrıyı.

1. `detectStock` fonksiyonunun üstünde, düşük olasılığa sahip algılamaları filtrelemek için bir eşik değeri tanımlayın:

    ```cpp
    const float threshold = 0.3f;
    ```

    Görüntü sınıflandırıcı yalnızca her etiket için bir sonuç döndürürken, nesne algılayıcı birden fazla sonuç döndürecektir. Bu nedenle, düşük olasılığa sahip olanlar filtrelenmelidir.

1. `detectStock` fonksiyonunun üstünde, tahminleri işlemek için bir fonksiyon tanımlayın:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Bu, bir tahmin listesini alır ve seri monitöre yazdırır.

1. `detectStock` fonksiyonunda, tahminler arasında döngü yapan `for` döngüsünün içeriğini aşağıdakiyle değiştirin:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Bu, tahminler arasında döngü yapar ve olasılığı eşik değeriyle karşılaştırır. Eşik değerinden yüksek olasılığa sahip tüm tahminler bir `list` içine eklenir ve `processPredictions` fonksiyonuna iletilir.

1. Kodunuzu yükleyin ve çalıştırın. Kamerayı bir raftaki nesnelere doğrultun ve C düğmesine basın. Seri monitörde çıktıyı göreceksiniz:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Görüntüleriniz için uygun bir değer belirlemek amacıyla `threshold` değerini ayarlamanız gerekebilir.

    Çekilen görüntüyü ve bu değerleri Custom Vision'daki **Predictions** sekmesinde görebileceksiniz.

    ![Bir rafta 4 kutu domates salçası ve 35.8%, 33.5%, 25.7% ve 16.6% algılama tahminleri](../../../../../translated_images/tr/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Bu kodu [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) klasöründe bulabilirsiniz.

😀 Stok sayacı programınız başarıyla tamamlandı!

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Orijinal belgenin kendi dilindeki hali, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.