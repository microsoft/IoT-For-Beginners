<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-28T02:47:20+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "tr"
}
-->
# IoT Cihazından Meyve Kalitesini Kontrol Etme

![Bu dersin genel bir sketchnote'u](../../../../../translated_images/tr/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Giriş

Son derste, görüntü sınıflandırıcıları ve bunları iyi ve kötü meyveleri tespit etmek için nasıl eğitebileceğinizi öğrendiniz. Bu görüntü sınıflandırıcıyı bir IoT uygulamasında kullanmak için, bir tür kamera kullanarak bir görüntü yakalayabilmeli ve bu görüntüyü sınıflandırılması için buluta gönderebilmelisiniz.

Bu derste, kamera sensörlerini ve bunları bir IoT cihazıyla görüntü yakalamak için nasıl kullanacağınızı öğreneceksiniz. Ayrıca IoT cihazınızdan görüntü sınıflandırıcıyı nasıl çağıracağınızı da öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Kamera sensörleri](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Bir IoT cihazı kullanarak görüntü yakalama](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Görüntü sınıflandırıcınızı yayınlama](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [IoT cihazınızdan görüntüleri sınıflandırma](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Modeli geliştirme](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kamera Sensörleri

Kamera sensörleri, adından da anlaşılacağı gibi, IoT cihazınıza bağlayabileceğiniz kameralardır. Bu kameralar sabit görüntüler çekebilir veya akışlı video kaydedebilir. Bazıları ham görüntü verisi dönerken, diğerleri görüntü verisini JPEG veya PNG gibi bir görüntü dosyasına sıkıştırır. Genellikle IoT cihazlarıyla çalışan kameralar, alışık olduğunuz kameralardan çok daha küçük ve düşük çözünürlüklüdür, ancak üst düzey telefonlarla yarışabilecek yüksek çözünürlüklü kameralar da bulabilirsiniz. Değiştirilebilir lensler, çoklu kamera kurulumları, kızılötesi termal kameralar veya UV kameralar gibi birçok seçenek mevcuttur.

![Bir sahneden gelen ışık bir lensin içinden geçer ve bir CMOS sensör üzerinde odaklanır](../../../../../translated_images/tr/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Çoğu kamera sensörü, her pikselin bir fotodiyot olduğu görüntü sensörlerini kullanır. Bir lens, görüntüyü görüntü sensörüne odaklar ve binlerce veya milyonlarca fotodiyot, her birine düşen ışığı algılar ve bunu piksel verisi olarak kaydeder.

> 💁 Lensler görüntüleri ters çevirir, kamera sensörü daha sonra görüntüyü doğru şekilde çevirir. Gözlerinizde de aynı durum geçerlidir - gördüğünüz şey gözünüzün arkasında ters algılanır ve beyniniz bunu düzeltir.

> 🎓 Görüntü sensörü, Aktif Piksel Sensörü (APS) olarak bilinir ve en popüler APS türü, tamamlayıcı metal oksit yarı iletken sensör veya CMOS'tur. Kamera sensörleri için kullanılan CMOS sensörü terimini duymuş olabilirsiniz.

Kamera sensörleri dijital sensörlerdir ve genellikle iletişimi sağlayan bir kütüphanenin yardımıyla görüntü verilerini dijital olarak gönderir. Kameralar, büyük miktarda veri göndermelerine olanak tanıyan SPI gibi protokoller kullanarak bağlanır - görüntüler, bir sıcaklık sensörü gibi bir sensörden gelen tek bir sayıdan çok daha büyüktür.

✅ IoT cihazlarında görüntü boyutuyla ilgili sınırlamalar nelerdir? Özellikle mikrodenetleyici donanımındaki kısıtlamaları düşünün.

## Bir IoT Cihazı Kullanarak Görüntü Yakalama

IoT cihazınızı kullanarak sınıflandırılacak bir görüntü yakalayabilirsiniz.

### Görev - Bir IoT Cihazı Kullanarak Görüntü Yakalama

IoT cihazınızı kullanarak bir görüntü yakalamak için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-camera.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-camera.md)

## Görüntü Sınıflandırıcınızı Yayınlama

Son derste görüntü sınıflandırıcınızı eğittiniz. IoT cihazınızdan kullanabilmek için modeli yayınlamanız gerekir.

### Model İterasyonları

Modeliniz son derste eğitilirken, **Performans** sekmesinde yan tarafta iterasyonların gösterildiğini fark etmiş olabilirsiniz. Modeli ilk eğittiğinizde, eğitim sırasında *İterasyon 1* görmüş olacaksınız. Tahmin görüntülerini kullanarak modeli geliştirdiğinizde, eğitim sırasında *İterasyon 2* görmüş olacaksınız.

Modeli her eğittiğinizde yeni bir iterasyon elde edersiniz. Bu, farklı veri setleriyle eğitilmiş modelinizin farklı sürümlerini takip etmenin bir yoludur. **Hızlı Test** yaptığınızda, birden fazla iterasyon arasındaki sonuçları karşılaştırmak için kullanabileceğiniz bir açılır menü vardır.

Bir iterasyondan memnun olduğunuzda, bunu harici uygulamalar tarafından kullanılabilir hale getirmek için yayınlayabilirsiniz. Bu şekilde cihazlarınız tarafından kullanılan bir yayınlanmış sürümünüz olabilir, ardından yeni bir sürüm üzerinde birden fazla iterasyon boyunca çalışabilir ve memnun olduğunuzda bunu yayınlayabilirsiniz.

### Görev - Bir İterasyonu Yayınlama

İterasyonlar Custom Vision portalından yayınlanır.

1. [CustomVision.ai](https://customvision.ai) adresinden Custom Vision portalını başlatın ve henüz açık değilse oturum açın. Ardından `fruit-quality-detector` projenizi açın.

1. Üstteki seçeneklerden **Performans** sekmesini seçin.

1. Yan taraftaki *İterasyonlar* listesinden en son iterasyonu seçin.

1. İterasyon için **Yayınla** düğmesini seçin.

    ![Yayınla düğmesi](../../../../../translated_images/tr/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. *Modeli Yayınla* iletişim kutusunda, *Tahmin kaynağı* olarak önceki derste oluşturduğunuz `fruit-quality-detector-prediction` kaynağını seçin. Adı `Iteration2` olarak bırakın ve **Yayınla** düğmesini seçin.

1. Yayınlandıktan sonra, **Tahmin URL'si** düğmesini seçin. Bu, tahmin API'sinin ayrıntılarını gösterecek ve modeli IoT cihazınızdan çağırmak için bunlara ihtiyacınız olacak. Alt bölüm *Bir görüntü dosyanız varsa* olarak etiketlenmiştir ve istediğiniz ayrıntılar bunlardır. Şu şekilde bir URL'nin bir kopyasını alın:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Burada `<location>`, özel görüş kaynağınızı oluştururken kullandığınız konum olacak ve `<id>` harfler ve rakamlardan oluşan uzun bir kimlik olacaktır.

    Ayrıca *Tahmin Anahtarı* değerinin bir kopyasını alın. Bu, modeli çağırırken geçirmeniz gereken güvenli bir anahtardır. Sadece bu anahtarı geçen uygulamaların modeli kullanmasına izin verilir, diğer tüm uygulamalar reddedilir.

    ![Tahmin API'si iletişim kutusu, URL ve anahtarı gösteriyor](../../../../../translated_images/tr/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Yeni bir iterasyon yayınlandığında, farklı bir adı olacaktır. IoT cihazının kullandığı iterasyonu nasıl değiştirebileceğinizi düşünün.

## IoT Cihazınızdan Görüntüleri Sınıflandırma

Artık bu bağlantı ayrıntılarını kullanarak IoT cihazınızdan görüntü sınıflandırıcıyı çağırabilirsiniz.

### Görev - IoT Cihazınızdan Görüntüleri Sınıflandırma

IoT cihazınızı kullanarak görüntüleri sınıflandırmak için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer-classify-image.md)

## Modeli Geliştirme

IoT cihazınıza bağlı kamerayı kullanırken elde ettiğiniz sonuçların beklediğinizle eşleşmediğini fark edebilirsiniz. Tahminler, bilgisayarınızdan yüklenen görüntüleri kullanmaya kıyasla her zaman o kadar doğru olmayabilir. Bunun nedeni, modelin tahminlerde kullanılan verilerden farklı verilerle eğitilmiş olmasıdır.

Bir görüntü sınıflandırıcıdan en iyi sonuçları almak için, modeli tahminlerde kullanılan görüntülere mümkün olduğunca benzeyen görüntülerle eğitmek istersiniz. Örneğin, eğitmek için telefon kameranızı kullandıysanız, görüntü kalitesi, keskinlik ve renk, bir IoT cihazına bağlı bir kameradan farklı olacaktır.

![2 muz resmi, biri IoT cihazından düşük çözünürlüklü ve kötü aydınlatmalı, diğeri telefondan yüksek çözünürlüklü ve iyi aydınlatmalı](../../../../../translated_images/tr/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Yukarıdaki görüntüde, soldaki muz resmi bir Raspberry Pi Kamerası kullanılarak çekildi, sağdaki ise aynı muzun aynı konumda bir iPhone kullanılarak çekildi. Kalite açısından belirgin bir fark var - iPhone resmi daha keskin, daha parlak renkler ve daha fazla kontrast içeriyor.

✅ IoT cihazınızın yakaladığı görüntülerin yanlış tahminlere neden olmasına başka neler sebep olabilir? IoT cihazının kullanılabileceği ortamı düşünün, görüntünün yakalanmasını etkileyebilecek faktörler nelerdir?

Modeli geliştirmek için, IoT cihazından yakalanan görüntüleri kullanarak yeniden eğitebilirsiniz.

### Görev - Modeli Geliştirme

1. IoT cihazınızı kullanarak hem olgun hem de olgunlaşmamış meyvelerin birden fazla görüntüsünü sınıflandırın.

1. Custom Vision portalında, *Tahminler* sekmesindeki görüntüleri kullanarak modeli yeniden eğitin.

    > ⚠️ [Görüntü sınıflandırıcınızı yeniden eğitme talimatlarına 1. derste ihtiyaç duyarsanız buradan ulaşabilirsiniz](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Görüntüleriniz, eğitmek için kullanılan orijinal görüntülerden çok farklı görünüyorsa, *Eğitim Görüntüleri* sekmesindeki tüm orijinal görüntüleri seçip **Sil** düğmesini seçerek silebilirsiniz. Bir görüntüyü seçmek için, imlecinizi üzerine getirin ve bir işaret görünecektir, bu işareti seçerek görüntüyü seçebilir veya seçimden kaldırabilirsiniz.

1. Modelin yeni bir iterasyonunu eğitin ve yukarıdaki adımları kullanarak yayınlayın.

1. Kodunuzdaki uç nokta URL'sini güncelleyin ve uygulamayı yeniden çalıştırın.

1. Tahmin sonuçlarından memnun kalana kadar bu adımları tekrarlayın.

---

## 🚀 Zorluk

Görüntü çözünürlüğü veya aydınlatma tahmini ne kadar etkiler?

Cihaz kodunuzdaki görüntülerin çözünürlüğünü değiştirin ve bunun görüntü kalitesine bir fark yaratıp yaratmadığını görün. Ayrıca aydınlatmayı değiştirmeyi deneyin.

Çiftliklere veya fabrikalara satılacak bir üretim cihazı oluşturacak olsaydınız, her zaman tutarlı sonuçlar vermesini nasıl sağlardınız?

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Gözden Geçirme ve Kendi Kendine Çalışma

Custom Vision modelinizi portalı kullanarak eğittiniz. Bu, görüntülerin mevcut olmasına dayanır - ve gerçek dünyada cihazınızdaki kameranın yakaladığı görüntülerle eşleşen eğitim verilerini elde edemeyebilirsiniz. Bunu, IoT cihazınızdan yakalanan görüntüleri kullanarak bir modeli eğitmek için eğitim API'sini doğrudan cihazınızdan kullanarak aşabilirsiniz.

* [Custom Vision SDK hızlı başlangıcında](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python) eğitim API'si hakkında bilgi edinin.

## Ödev

[Sınıflandırma sonuçlarına yanıt verin](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.