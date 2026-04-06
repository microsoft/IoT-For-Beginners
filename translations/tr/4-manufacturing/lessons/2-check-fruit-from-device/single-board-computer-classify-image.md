# Bir Görüntüyü Sınıflandırma - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, kamera tarafından yakalanan görüntüyü sınıflandırmak için Custom Vision hizmetine göndereceksiniz.

## Görüntüleri Custom Vision'a Gönderme

Custom Vision hizmeti, görüntüleri sınıflandırmak için kullanabileceğiniz bir Python SDK'sına sahiptir.

### Görev - Görüntüleri Custom Vision'a Gönderme

1. VS Code'da `fruit-quality-detector` klasörünü açın. Eğer sanal bir IoT cihazı kullanıyorsanız, sanal ortamın terminalde çalıştığından emin olun.

1. Görüntüleri Custom Vision'a göndermek için gereken Python SDK'sı bir Pip paketi olarak mevcuttur. Aşağıdaki komutla yükleyin:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` dosyasının en üstüne aşağıdaki import ifadelerini ekleyin:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Bu, Custom Vision kütüphanelerinden bazı modülleri içeri alır; biri tahmin anahtarıyla kimlik doğrulama yapmak için, diğeri ise Custom Vision'ı çağırabilecek bir tahmin istemci sınıfı sağlamak için.

1. Dosyanın sonuna aşağıdaki kodu ekleyin:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` kısmını bu derste daha önce *Prediction URL* diyalog kutusundan kopyaladığınız URL ile değiştirin. `<prediction key>` kısmını ise aynı diyalog kutusundan kopyaladığınız tahmin anahtarı ile değiştirin.

1. *Prediction URL* diyalog kutusu tarafından sağlanan tahmin URL'si, doğrudan REST uç noktasını çağırırken kullanılmak üzere tasarlanmıştır. Python SDK, URL'nin farklı bölümlerini farklı yerlerde kullanır. Bu URL'yi gerekli parçalara ayırmak için aşağıdaki kodu ekleyin:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Bu kod, URL'yi bölerek `https://<location>.api.cognitive.microsoft.com` uç noktasını, proje kimliğini ve yayınlanmış iterasyonun adını çıkarır.

1. Tahmin işlemini gerçekleştirmek için bir tahminci nesnesi oluşturun:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials`, tahmin anahtarını sarar. Bunlar, uç noktayı işaret eden bir tahmin istemci nesnesi oluşturmak için kullanılır.

1. Görüntüyü Custom Vision'a aşağıdaki kodla gönderin:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Bu kod, görüntüyü başa sarar ve ardından tahmin istemcisine gönderir.

1. Son olarak, sonuçları aşağıdaki kodla gösterin:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Bu kod, döndürülen tüm tahminler arasında döngü yapar ve bunları terminalde gösterir. Döndürülen olasılıklar, 0-1 arasında kayan noktalı sayılardır; 0, etiketle eşleşme olasılığının %0 olduğunu, 1 ise %100 olduğunu ifade eder.

    > 💁 Görüntü sınıflandırıcılar, kullanılan tüm etiketler için yüzdeleri döndürecektir. Her etiket, görüntünün o etiketle eşleşme olasılığını gösterecektir.

1. Kodunuzu çalıştırın; kameranız meyvelere, uygun bir görüntü setine veya sanal IoT donanımı kullanıyorsanız webcam'de görünen meyvelere yönelmiş olsun. Konsolda çıktıyı göreceksiniz:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Alınan görüntüyü ve bu değerleri Custom Vision'daki **Predictions** sekmesinde görebileceksiniz.

    ![Custom Vision'da olgun bir muz %56.8 olgun ve %43.1 olgun değil olarak tahmin edildi](../../../../../translated_images/tr/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Bu kodu [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) veya [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Meyve kalite sınıflandırıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.