<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-28T03:48:45+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "tr"
}
-->
# IoT Cihazından Stok Kontrolü

![Bu dersin genel görünümünü gösteren bir skeç notu](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.tr.jpg)

> Skeç notu: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Giriş

Önceki derste, perakendede nesne tespitinin farklı kullanım alanlarını öğrendiniz. Ayrıca, stokları tanımlamak için bir nesne dedektörünü nasıl eğiteceğinizi de öğrendiniz. Bu derste, IoT cihazınızdan nesne dedektörünüzü kullanarak stok saymayı öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Stok sayımı](../../../../../5-retail/lessons/2-check-stock-device)
* [IoT cihazınızdan nesne dedektörünüzü çağırma](../../../../../5-retail/lessons/2-check-stock-device)
* [Sınır kutuları](../../../../../5-retail/lessons/2-check-stock-device)
* [Modeli yeniden eğitme](../../../../../5-retail/lessons/2-check-stock-device)
* [Stok sayma](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Bu proje içindeki son derstir, bu yüzden bu dersi ve ödevi tamamladıktan sonra bulut hizmetlerinizi temizlemeyi unutmayın. Ödevi tamamlamak için bu hizmetlere ihtiyacınız olacak, bu yüzden önce ödevi tamamladığınızdan emin olun.
>
> Gerekirse [projenizi temizleme rehberine](../../../clean-up.md) başvurabilirsiniz.

## Stok Sayımı

Nesne dedektörleri, stok kontrolü için kullanılabilir; stok sayımı yapmak veya stokların olması gereken yerde olup olmadığını kontrol etmek için. Kameralı IoT cihazları, mağaza genelinde stokları izlemek için konuşlandırılabilir. Bu, özellikle az sayıda yüksek değerli ürünlerin bulunduğu alanlar gibi, ürünlerin yeniden stoklanmasının önemli olduğu sıcak noktalardan başlayabilir.

Örneğin, bir kamera 8 kutu domates salçası alabilecek bir rafı izliyorsa ve bir nesne dedektörü yalnızca 7 kutu tespit ediyorsa, bir kutu eksiktir ve yeniden stoklanması gerekir.

![Bir rafta 7 kutu domates salçası, üst sırada 4, alt sırada 3](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.tr.png)

Yukarıdaki görselde, bir nesne dedektörü 8 kutu alabilecek bir rafta 7 kutu domates salçası tespit etmiştir. IoT cihazı yalnızca yeniden stoklama ihtiyacını bildirmekle kalmaz, aynı zamanda eksik ürünün yerini de belirtebilir. Bu, rafları yeniden stoklamak için robotlar kullanıyorsanız önemli bir veridir.

> 💁 Mağazaya ve ürünün popülerliğine bağlı olarak, yalnızca 1 kutu eksikse yeniden stoklama yapılmayabilir. Ürünlerinize, müşterilerinize ve diğer kriterlere göre ne zaman yeniden stoklama yapılacağını belirleyen bir algoritma oluşturmanız gerekir.

✅ Nesne tespiti ve robotları başka hangi senaryolarda birleştirebilirsiniz?

Bazen raflarda yanlış stok bulunabilir. Bu, yeniden stoklama sırasında yapılan bir insan hatası veya müşterilerin satın alma kararlarını değiştirip ürünü ilk buldukları yere geri koymaları nedeniyle olabilir. Bu durum, konserve ürünler gibi bozulmayan ürünler için bir rahatsızlık yaratır. Ancak, dondurulmuş veya soğutulmuş ürünler gibi bozulabilir ürünler için, ürünün ne kadar süreyle dondurucudan çıkarıldığını belirlemek imkansız olabileceğinden, ürün artık satılamaz hale gelebilir.

Nesne tespiti, beklenmeyen ürünleri tespit etmek için kullanılabilir ve bu ürünlerin tespit edildiği anda bir insanı veya robotu uyararak ürünü geri yerine koymasını sağlayabilir.

![Domates salçası rafında yanlış yerleştirilmiş bir bebek mısır konservesi](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.tr.png)

Yukarıdaki görselde, bir bebek mısır konservesi domates salçası rafına yerleştirilmiştir. Nesne dedektörü bunu tespit etmiş ve IoT cihazı bir insanı veya robotu uyararak konservesi doğru yerine koymasını sağlamıştır.

## IoT Cihazınızdan Nesne Dedektörünüzü Çağırma

Son derste eğittiğiniz nesne dedektörü, IoT cihazınızdan çağrılabilir.

### Görev - Nesne Dedektörünüzün Bir Sürümünü Yayınlayın

Sürümler, Custom Vision portalından yayınlanır.

1. [CustomVision.ai](https://customvision.ai) adresinden Custom Vision portalını başlatın ve henüz açık değilse oturum açın. Ardından `stock-detector` projenizi açın.

1. Üstteki seçeneklerden **Performance** sekmesini seçin.

1. Yan taraftaki *Iterations* listesinden en son sürümü seçin.

1. Sürüm için **Publish** düğmesini seçin.

    ![Yayınla düğmesi](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.tr.png)

1. *Publish Model* iletişim kutusunda, *Prediction resource* alanını önceki derste oluşturduğunuz `stock-detector-prediction` kaynağına ayarlayın. Adı `Iteration2` olarak bırakın ve **Publish** düğmesini seçin.

1. Yayınlandıktan sonra **Prediction URL** düğmesini seçin. Bu, tahmin API'sinin ayrıntılarını gösterecektir ve modeli IoT cihazınızdan çağırmak için bu bilgilere ihtiyacınız olacak. Alt bölüm *If you have an image file* olarak etiketlenmiştir ve ihtiyacınız olan ayrıntılar buradadır. Şu şekilde bir URL'nin bir kopyasını alın:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Burada `<location>`, özel görüş kaynağınızı oluştururken kullandığınız konum olacaktır ve `<id>` harfler ve rakamlardan oluşan uzun bir kimliktir.

    Ayrıca *Prediction-Key* değerinin bir kopyasını alın. Bu, modeli çağırırken geçirmeniz gereken güvenli bir anahtardır. Yalnızca bu anahtarı geçen uygulamalar modeli kullanabilir, diğer tüm uygulamalar reddedilir.

    ![Tahmin API'si iletişim kutusu, URL ve anahtarı gösteriyor](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.tr.png)

✅ Yeni bir sürüm yayınlandığında, farklı bir adı olacaktır. IoT cihazının kullandığı sürümü nasıl değiştireceğinizi düşünüyorsunuz?

### Görev - IoT Cihazınızdan Nesne Dedektörünüzü Çağırın

IoT cihazınızdan nesne dedektörünü kullanmak için aşağıdaki ilgili rehberi takip edin:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal cihaz](single-board-computer-object-detector.md)

## Sınır Kutuları

Nesne dedektörünü kullandığınızda, yalnızca tespit edilen nesneleri etiketleri ve olasılıklarıyla birlikte değil, aynı zamanda nesnelerin sınır kutularını da alırsınız. Bu kutular, nesne dedektörünün belirli bir olasılıkla nesneyi tespit ettiği alanı tanımlar.

> 💁 Bir sınır kutusu, tespit edilen nesneyi içeren alanı tanımlayan bir kutudur, nesne için sınırı belirler.

Custom Vision'daki **Predictions** sekmesindeki bir tahminin sonuçları, tahmin için gönderilen görüntüde çizilmiş sınır kutularına sahiptir.

![Bir rafta 4 kutu domates salçası, tahminler 35.8%, 33.5%, 25.7% ve 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.tr.png)

Yukarıdaki görselde, 4 kutu domates salçası tespit edilmiştir. Sonuçlarda, görüntüde tespit edilen her nesne için bir kırmızı kare yerleştirilmiştir ve bu, görüntü için sınır kutusunu belirtir.

✅ Custom Vision'daki tahminleri açın ve sınır kutularını inceleyin.

Sınır kutuları 4 değerle tanımlanır - üst, sol, yükseklik ve genişlik. Bu değerler 0-1 arasında bir ölçekle ifade edilir ve görüntünün boyutuna göre bir yüzde olarak pozisyonları temsil eder. Başlangıç noktası (0,0 pozisyonu) görüntünün sol üst köşesidir, bu nedenle üst değer yukarıdan olan mesafeyi, sınır kutusunun altı ise üst artı yükseklik değerini ifade eder.

![Bir domates salçası kutusunun etrafında bir sınır kutusu](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.tr.png)

Yukarıdaki görsel 600 piksel genişliğinde ve 800 piksel yüksekliğindedir. Sınır kutusu 320 piksel aşağıdan başlar, bu da 0.4 üst koordinatını verir (800 x 0.4 = 320). Soldan, sınır kutusu 240 piksel ileride başlar, bu da 0.4 sol koordinatını verir (600 x 0.4 = 240). Sınır kutusunun yüksekliği 240 piksel, bu da 0.3 yükseklik değerini verir (800 x 0.3 = 240). Sınır kutusunun genişliği 120 piksel, bu da 0.2 genişlik değerini verir (600 x 0.2 = 120).

| Koordinat | Değer |
| ---------- | ----: |
| Üst        | 0.4   |
| Sol        | 0.4   |
| Yükseklik  | 0.3   |
| Genişlik   | 0.2   |

0-1 arasındaki yüzde değerlerini kullanmak, görüntü ne kadar ölçeklenirse ölçeklensin, sınır kutusunun 0.4 oranında ileride ve aşağıda başlamasını ve 0.3 yükseklik ve 0.2 genişlikte olmasını sağlar.

Sınır kutularını olasılıklarla birleştirerek bir tespitin ne kadar doğru olduğunu değerlendirebilirsiniz. Örneğin, bir nesne dedektörü üst üste binen birden fazla nesne tespit edebilir, örneğin bir kutunun içinde başka bir kutu tespit edebilir. Kodunuz sınır kutularını inceleyebilir, bunun imkansız olduğunu anlayabilir ve diğer nesnelerle önemli ölçüde örtüşen nesneleri görmezden gelebilir.

![Bir domates salçası kutusunu kapsayan iki sınır kutusu](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.tr.png)

Yukarıdaki örnekte, bir sınır kutusu %78.3 olasılıkla bir domates salçası kutusu tespit ettiğini belirtmiştir. İkinci bir sınır kutusu biraz daha küçüktür ve ilk sınır kutusunun içinde %64.3 olasılıkla bir tespit yapmıştır. Kodunuz sınır kutularını kontrol edebilir, tamamen örtüştüklerini görebilir ve daha düşük olasılığı görmezden gelebilir çünkü bir kutunun başka bir kutunun içinde olması mümkün değildir.

✅ Bir nesnenin başka bir nesnenin içinde tespit edilmesinin geçerli olduğu bir durumu düşünebilir misiniz?

## Modeli Yeniden Eğitme

Görüntü sınıflandırıcıda olduğu gibi, IoT cihazınızdan alınan verilerle modelinizi yeniden eğitebilirsiniz. Bu gerçek dünya verilerini kullanmak, modelinizin IoT cihazınızdan kullanıldığında iyi çalışmasını sağlar.

Görüntü sınıflandırıcıdan farklı olarak, yalnızca bir görüntüyü etiketleyemezsiniz. Bunun yerine, model tarafından tespit edilen her sınır kutusunu gözden geçirmeniz gerekir. Eğer kutu yanlış bir şeyin etrafındaysa silinmesi, yanlış bir konumdaysa düzeltilmesi gerekir.

### Görev - Modeli Yeniden Eğitme

1. IoT cihazınızdan bir dizi görüntü yakaladığınızdan emin olun.

1. **Predictions** sekmesinden bir görüntü seçin. Tespit edilen nesnelerin sınır kutularını gösteren kırmızı kutular göreceksiniz.

1. Her sınır kutusunu gözden geçirin. Önce kutuyu seçin ve bir açılır pencere etiketi gösterecektir. Gerekirse sınır kutusunun boyutunu ayarlamak için köşelerdeki tutamaçları kullanın. Etiket yanlışsa, **X** düğmesiyle kaldırın ve doğru etiketi ekleyin. Sınır kutusu bir nesne içermiyorsa, çöp kutusu düğmesiyle silin.

1. Düzenleyiciyi kapattığınızda, görüntü **Predictions** sekmesinden **Training Images** sekmesine taşınacaktır. Tüm tahminler için bu işlemi tekrarlayın.

1. **Train** düğmesini kullanarak modelinizi yeniden eğitin. Eğitim tamamlandıktan sonra sürümü yayınlayın ve IoT cihazınızı yeni sürümün URL'sini kullanacak şekilde güncelleyin.

1. Kodunuzu yeniden dağıtın ve IoT cihazınızı test edin.

## Stok Sayma

Tespit edilen nesnelerin sayısı ve sınır kutularının bir kombinasyonunu kullanarak, bir raftaki stokları sayabilirsiniz.

### Görev - Stok Sayma

IoT cihazınızdan nesne dedektöründen alınan sonuçları kullanarak stok saymak için aşağıdaki ilgili rehberi takip edin:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal cihaz](single-board-computer-count-stock.md)

---

## 🚀 Zorluk

Yanlış stokları tespit edebilir misiniz? Modelinizi birden fazla nesne üzerinde eğitin, ardından uygulamanızı yanlış stok tespit edildiğinde sizi uyarması için güncelleyin.

Belki bunu bir adım ileri götürerek aynı rafta yan yana duran stokları tespit edin ve sınır kutularına limitler tanımlayarak bir şeyin yanlış yere konulup konulmadığını görün.

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Gözden Geçirme ve Kendi Kendine Çalışma

* Microsoft Docs'taki [Edge'de stok tükenme tespiti desen rehberinden](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn) uçtan uca bir stok tespit sistemi nasıl tasarlanacağını öğrenin.
* IoT ve bulut hizmetlerini birleştirerek uçtan uca perakende çözümleri oluşturmanın diğer yollarını öğrenmek için bu [Perakende çözümünün perde arkası - Hands On! YouTube videosunu](https://www.youtube.com/watch?v=m3Pc300x2Mw) izleyin.

## Ödev

[Nesne dedektörünüzü uçta kullanın](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.