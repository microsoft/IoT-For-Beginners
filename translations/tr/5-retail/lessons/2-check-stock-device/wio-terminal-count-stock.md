<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T03:50:48+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "tr"
}
-->
# IoT Cihazınızla Stok Sayımı - Wio Terminal

Tahminler ve bunlara ait sınırlayıcı kutuların kombinasyonu, bir görüntüdeki stokları saymak için kullanılabilir.

## Stok Sayımı

![Her bir kutunun etrafında sınırlayıcı kutular olan 4 domates salçası kutusu](../../../../../translated_images/tr/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

Yukarıdaki görüntüde, sınırlayıcı kutuların küçük bir örtüşmesi var. Eğer bu örtüşme çok daha büyük olsaydı, sınırlayıcı kutular aynı nesneyi gösterebilirdi. Nesneleri doğru bir şekilde saymak için, önemli ölçüde örtüşen kutuları görmezden gelmeniz gerekir.

### Görev - Örtüşmeyi göz ardı ederek stok sayımı

1. `stock-counter` projenizi henüz açmadıysanız açın.

1. `processPredictions` fonksiyonunun üstüne aşağıdaki kodu ekleyin:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Bu, sınırlayıcı kutuların aynı nesne olarak kabul edilmeden önce izin verilen örtüşme yüzdesini tanımlar. 0.20, %20'lik bir örtüşmeyi ifade eder.

1. Bunun altına ve `processPredictions` fonksiyonunun üstüne, iki dikdörtgen arasındaki örtüşmeyi hesaplamak için aşağıdaki kodu ekleyin:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Bu kod, görüntüdeki noktaları saklamak için bir `Point` yapısı ve bir dikdörtgeni sol üst ve sağ alt koordinatlarla tanımlamak için bir `Rect` yapısı tanımlar. Daha sonra, bir dikdörtgenin alanını sol üst ve sağ alt koordinatlarından hesaplayan bir `area` fonksiyonu tanımlar.

    Ardından, iki dikdörtgenin örtüşen alanını hesaplayan bir `overlappingArea` fonksiyonu tanımlar. Eğer örtüşme yoksa, 0 döner.

1. `overlappingArea` fonksiyonunun altına, bir sınırlayıcı kutuyu `Rect`e dönüştürmek için bir fonksiyon tanımlayın:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Bu, nesne algılayıcıdan bir tahmin alır, sınırlayıcı kutuyu çıkarır ve sınırlayıcı kutudaki değerleri kullanarak bir dikdörtgen tanımlar. Sağ taraf, sol taraf artı genişlikten hesaplanır. Alt taraf ise üst taraf artı yükseklikten hesaplanır.

1. Tahminlerin birbirleriyle karşılaştırılması gerekir ve eğer iki tahmin, eşik değerinden daha fazla örtüşüyorsa, bunlardan biri silinmelidir. Örtüşme eşiği bir yüzdedir, bu yüzden en küçük sınırlayıcı kutunun boyutuyla çarpılması gerekir. Böylece örtüşmenin, sınırlayıcı kutunun belirli bir yüzdesini aşıp aşmadığı kontrol edilir, tüm görüntünün yüzdesini değil. `processPredictions` fonksiyonunun içeriğini silerek başlayın.

1. Boş `processPredictions` fonksiyonuna aşağıdakileri ekleyin:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Bu kod, örtüşmeyen tahminleri saklamak için bir vektör tanımlar. Daha sonra tüm tahminler arasında döngü yapar ve sınırlayıcı kutudan bir `Rect` oluşturur.

    Ardından, kalan tahminler arasında döngü yapar ve mevcut tahminden sonrakilerle başlar. Bu, tahminlerin birden fazla kez karşılaştırılmasını önler - bir kez 1 ve 2 karşılaştırıldıktan sonra, 2'nin 1 ile tekrar karşılaştırılmasına gerek yoktur, yalnızca 3, 4, vb. ile karşılaştırılır.

    Her tahmin çifti için örtüşen alan hesaplanır. Bu, en küçük sınırlayıcı kutunun alanıyla karşılaştırılır - eğer örtüşme, en küçük sınırlayıcı kutunun eşik yüzdesini aşarsa, tahmin geçerli olarak işaretlenmez. Tüm örtüşmeler karşılaştırıldıktan sonra, tahmin kontrolleri geçerse `passed_predictions` koleksiyonuna eklenir.

    > 💁 Bu, örtüşmeleri kaldırmanın oldukça basit bir yoludur, sadece örtüşen çiftteki ilkini kaldırır. Üretim kodu için, birden fazla nesne arasındaki örtüşmeleri dikkate almak veya bir sınırlayıcı kutunun başka bir kutunun içinde olup olmadığını kontrol etmek gibi daha fazla mantık eklemek isteyebilirsiniz.

1. Bundan sonra, geçen tahminlerin detaylarını seri monitöre göndermek için aşağıdaki kodu ekleyin:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Bu kod, geçen tahminler arasında döngü yapar ve detaylarını seri monitöre yazdırır.

1. Bunun altına, sayılan öğelerin sayısını seri monitöre yazdırmak için kod ekleyin:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Bu, stok seviyelerinin düşük olduğunu bildirmek için bir IoT hizmetine gönderilebilir.

1. Kodunuzu yükleyin ve çalıştırın. Kamerayı bir raftaki nesnelere doğrultun ve C düğmesine basın. Tahminlerin göz ardı edildiğini görmek için `overlap_threshold` değerini ayarlamayı deneyin.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Bu kodu [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) klasöründe bulabilirsiniz.

😀 Stok sayacı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.