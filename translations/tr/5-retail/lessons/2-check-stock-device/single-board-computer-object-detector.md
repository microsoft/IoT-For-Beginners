<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-28T03:51:31+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "tr"
}
-->
# Nesne Algılayıcınızı IoT Cihazınızdan Çalıştırın - Sanal IoT Donanımı ve Raspberry Pi

Nesne algılayıcınız yayınlandıktan sonra, IoT cihazınızdan kullanılabilir.

## Görüntü sınıflandırıcı projesini kopyalayın

Stok algılayıcınızın büyük bir kısmı, önceki bir derste oluşturduğunuz görüntü sınıflandırıcı ile aynıdır.

### Görev - görüntü sınıflandırıcı projesini kopyalayın

1. Eğer sanal bir IoT cihazı kullanıyorsanız bilgisayarınızda, ya da Raspberry Pi üzerinde `stock-counter` adında bir klasör oluşturun. Sanal bir IoT cihazı kullanıyorsanız, bir sanal ortam kurduğunuzdan emin olun.

1. Kamera donanımını kurun.

    * Eğer bir Raspberry Pi kullanıyorsanız, PiCamera'yı takmanız gerekecek. Ayrıca, kamerayı sabit bir konuma yerleştirmek isteyebilirsiniz; örneğin, kabloyu bir kutunun ya da tenekenin üzerine asarak veya kamerayı çift taraflı bantla bir kutuya sabitleyerek.
    * Eğer sanal bir IoT cihazı kullanıyorsanız, CounterFit ve CounterFit PyCamera shim'i yüklemeniz gerekecek. Eğer sabit görüntüler kullanacaksanız, nesne algılayıcınızın daha önce görmediği bazı görüntüler yakalayın. Eğer web kameranızı kullanacaksanız, algılayacağınız stokları görebilecek şekilde konumlandırdığınızdan emin olun.

1. Kameradan görüntü yakalamak için [üretim projesinin 2. dersi](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)'ndeki adımları tekrarlayın.

1. Görüntü sınıflandırıcıyı çağırmak için [üretim projesinin 2. dersi](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)'ndeki adımları tekrarlayın. Bu kodun büyük bir kısmı nesne algılamak için yeniden kullanılacaktır.

## Kodunuzu bir sınıflandırıcıdan görüntü algılayıcıya dönüştürün

Görüntüleri sınıflandırmak için kullandığınız kod, nesneleri algılamak için kullanılan koda oldukça benzerdir. Ana fark, Custom Vision SDK'da çağrılan yöntem ve çağrının sonuçlarıdır.

### Görev - kodu bir sınıflandırıcıdan görüntü algılayıcıya dönüştürün

1. Görüntüyü sınıflandıran ve tahminleri işleyen üç satırlık kodu silin:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Bu üç satırı kaldırın.

1. Görüntüdeki nesneleri algılamak için aşağıdaki kodu ekleyin:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Bu kod, nesne algılayıcıyı çalıştırmak için tahmin edicinin `detect_image` yöntemini çağırır. Daha sonra, belirli bir eşik değerinin üzerindeki tüm tahminleri toplar ve bunları konsola yazdırır.

    Görüntü sınıflandırıcı yalnızca her etiket için bir sonuç döndürürken, nesne algılayıcı birden fazla sonuç döndürebilir. Bu nedenle, düşük olasılıklı tahminlerin filtrelenmesi gerekir.

1. Bu kodu çalıştırın; bir görüntü yakalayacak, nesne algılayıcıya gönderecek ve algılanan nesneleri yazdıracaktır. Eğer sanal bir IoT cihazı kullanıyorsanız, CounterFit'te uygun bir görüntü ayarlandığından veya web kameranızın seçili olduğundan emin olun. Eğer bir Raspberry Pi kullanıyorsanız, kameranızın bir raftaki nesnelere yöneldiğinden emin olun.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Görüntüleriniz için uygun bir değer belirlemek amacıyla `threshold` ayarını değiştirmeniz gerekebilir.

    Çekilen görüntüyü ve bu değerleri Custom Vision'daki **Predictions** sekmesinde görebileceksiniz.

    ![Bir rafta 4 kutu domates salçası ve 35.8%, 33.5%, 25.7% ve 16.6% algılama oranlarıyla tahminler](../../../../../translated_images/tr/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Bu kodu [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) veya [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Stok sayıcı programınız başarıyla tamamlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.