<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-28T04:11:43+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "tr"
}
-->
# IoT ile Bitki Büyümesini Tahmin Et

![Bu dersin genel bir sketchnote'u](../../../../../translated_images/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.tr.jpg)

> Sketchnote [Nitya Narasimhan](https://github.com/nitya) tarafından hazırlanmıştır. Daha büyük bir versiyon için görsele tıklayın.

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Giriş

Bitkilerin büyümesi için belirli şeylere ihtiyaç vardır - su, karbondioksit, besinler, ışık ve ısı. Bu derste, hava sıcaklığını ölçerek bitkilerin büyüme ve olgunlaşma oranlarını nasıl hesaplayacağınızı öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Dijital tarım](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Tarımda sıcaklık neden önemlidir?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Ortam sıcaklığını ölçme](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Büyüme dereceleri (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Sıcaklık sensörü verilerini kullanarak GDD hesaplama](../../../../../2-farm/lessons/1-predict-plant-growth)

## Dijital Tarım

Dijital Tarım, tarımda veri toplama, depolama ve analiz etme yöntemlerini dönüştürmektedir. Şu anda Dünya Ekonomik Forumu tarafından 'Dördüncü Sanayi Devrimi' olarak adlandırılan bir dönemdeyiz ve dijital tarımın yükselişi 'Dördüncü Tarım Devrimi' veya 'Tarım 4.0' olarak adlandırılmaktadır.

> 🎓 Dijital Tarım terimi, 'tarım değer zinciri'ni de içerir, yani çiftlikten sofraya kadar olan tüm süreci kapsar. Bu, gıda taşınırken ve işlenirken ürün kalitesinin izlenmesini, depo ve e-ticaret sistemlerini, hatta traktör kiralama uygulamalarını bile içerir!

Bu değişiklikler, çiftçilerin verimi artırmasına, daha az gübre ve pestisit kullanmasına ve suyu daha verimli kullanmasına olanak tanır. Sensörler ve diğer cihazlar, öncelikle daha zengin ülkelerde kullanılsa da, fiyatlarının düşmesiyle birlikte gelişmekte olan ülkelerde de daha erişilebilir hale gelmektedir.

Dijital tarımın sağladığı bazı teknikler şunlardır:

* Sıcaklık ölçümü - Sıcaklık ölçümü, çiftçilerin bitki büyümesini ve olgunlaşmasını tahmin etmesine olanak tanır.
* Otomatik sulama - Toprak nemini ölçerek ve toprak çok kuru olduğunda sulama sistemlerini açarak zamanlı sulama yerine daha verimli bir yöntem sunar. Zamanlı sulama, sıcak ve kuru bir dönemde bitkilerin yeterince sulanmamasına veya yağmur sırasında fazla sulanmasına neden olabilir. Çiftçiler, yalnızca toprağın ihtiyaç duyduğu zaman sulama yaparak su kullanımını optimize edebilir.
* Zararlı kontrolü - Çiftçiler, otomatik robotlar veya dronlar üzerindeki kameraları kullanarak zararlıları kontrol edebilir ve yalnızca ihtiyaç duyulan yerlere pestisit uygulayarak pestisit kullanımını ve yerel su kaynaklarına pestisit akışını azaltabilir.

✅ Araştırma yapın. Tarım verimini artırmak için kullanılan diğer teknikler nelerdir?

> 🎓 'Hassas Tarım' terimi, tarlaları veya tarlaların belirli bölümlerini gözlemleme, ölçme ve bunlara yanıt verme sürecini tanımlar. Bu, su, besin ve zararlı seviyelerini ölçmeyi ve yalnızca bir tarlanın küçük bir bölümünü sulamak gibi doğru yanıtlar vermeyi içerir.

## Tarımda Sıcaklık Neden Önemlidir?

Bitkiler hakkında öğrenirken, çoğu öğrenci su, ışık, karbondioksit ve besinlerin gerekliliğini öğrenir. Ancak bitkilerin büyümesi için sıcaklığa da ihtiyaç vardır - bu nedenle bitkiler sıcaklık arttıkça ilkbaharda çiçek açar, kar çiçekleri veya nergisler kısa bir sıcak dönem nedeniyle erken filizlenebilir ve seralar bitkilerin büyümesini hızlandırmada oldukça etkilidir.

> 🎓 Seralar ve sıcak evler benzer bir işlev görür, ancak önemli bir farkla. Sıcak evler yapay olarak ısıtılır ve çiftçilerin sıcaklıkları daha hassas bir şekilde kontrol etmelerine olanak tanır, seralar ise güneşe bağlıdır ve genellikle yalnızca ısıyı dışarı atmak için pencereler veya diğer açıklıklarla kontrol edilir.

Bitkilerin büyümesi için günlük ortalama sıcaklıklara dayalı bir taban veya minimum sıcaklık, optimum sıcaklık ve maksimum sıcaklık vardır.

* Taban sıcaklık - Bir bitkinin büyümesi için gereken minimum günlük ortalama sıcaklıktır.
* Optimum sıcaklık - En fazla büyüme için en iyi günlük ortalama sıcaklıktır.
* Maksimum sıcaklık - Bir bitkinin dayanabileceği maksimum sıcaklıktır. Bu sıcaklığın üzerinde bitki, suyu korumak ve hayatta kalmak için büyümesini durdurur.

> 💁 Bunlar, günlük ve gece sıcaklıklarının ortalaması alınarak elde edilen ortalama sıcaklıklardır. Bitkilerin daha verimli fotosentez yapabilmesi ve geceleri enerji tasarrufu yapabilmesi için gündüz ve gece farklı sıcaklıklara ihtiyaçları vardır.

Her bitki türünün taban, optimum ve maksimum sıcaklık değerleri farklıdır. Bu nedenle bazı bitkiler sıcak ülkelerde, bazıları ise soğuk ülkelerde daha iyi yetişir.

✅ Araştırma yapın. Bahçenizde, okulunuzda veya yerel parkınızda bulunan herhangi bir bitki için taban sıcaklığını bulabilir misiniz?

![Büyüme oranının sıcaklık arttıkça arttığını, ardından sıcaklık çok yükseldiğinde düştüğünü gösteren bir grafik](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca83.tr.png)

Yukarıdaki grafik, büyüme oranı ile sıcaklık arasındaki ilişkiyi gösteren bir örnek grafiktir. Taban sıcaklığa kadar büyüme olmaz. Büyüme oranı, optimum sıcaklığa kadar artar, ardından bu zirveye ulaştıktan sonra düşer. 

Bu grafiğin şekli, bitki türüne göre değişir. Bazılarında optimum sıcaklığın üzerinde daha keskin düşüşler olurken, bazılarında tabandan optima kadar daha yavaş artışlar görülür.

> 💁 Bir çiftçinin en iyi büyümeyi elde edebilmesi için, yetiştirdiği bitkiler için bu üç sıcaklık değerini ve grafiğin şeklini bilmesi gerekir.

Eğer bir çiftçi sıcaklığı kontrol edebiliyorsa, örneğin ticari bir sıcak evde, bitkileri için en uygun sıcaklığı ayarlayabilir. Örneğin, domates yetiştiren bir ticari sıcak evde sıcaklık, gündüz 25°C ve gece 20°C civarında ayarlanır.

> 🍅 Bu sıcaklıklar, yapay ışıklar, gübreler ve kontrollü CO
Bu kod, CSV dosyasını açar ve sonuna yeni bir satır ekler. Satır, insan tarafından okunabilir bir formatta biçimlendirilmiş mevcut tarih ve saat ile IoT cihazından alınan sıcaklığı içerir. Veriler, [ISO 8601 formatında](https://wikipedia.org/wiki/ISO_8601) zaman dilimiyle birlikte, ancak mikro saniyeler olmadan saklanır.

1. IoT cihazınızın veri gönderdiğinden emin olarak bu kodu daha önceki gibi çalıştırın. Aynı klasörde `temperature.csv` adlı bir CSV dosyası oluşturulacaktır. Dosyayı görüntülediğinizde tarih/saat ve sıcaklık ölçümlerini göreceksiniz:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Veri toplamak için bu kodu bir süre çalıştırın. İdeal olarak, GDD hesaplamaları için yeterli veri toplamak adına bunu bir gün boyunca çalıştırmalısınız.

    
> 💁 Sanal IoT Cihazı kullanıyorsanız, rastgele kutucuğunu işaretleyin ve sıcaklık değeri her döndüğünde aynı sıcaklığı almamak için bir aralık belirleyin.
    ![Rastgele kutucuğunu işaretleyin ve bir aralık belirleyin](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.tr.png) 

    > 💁 Bunu bir gün boyunca çalıştırmak istiyorsanız, sunucu kodunuzun çalıştığı bilgisayarın uyku moduna geçmeyeceğinden emin olmalısınız. Bunun için güç ayarlarınızı değiştirebilir veya [bu sistemi aktif tutan Python scripti](https://github.com/jaqsparow/keep-system-active) gibi bir şey çalıştırabilirsiniz.
    
> 💁 Bu kodu [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server) klasöründe bulabilirsiniz.

### Görev - Saklanan verileri kullanarak GDD hesaplama

Sunucu sıcaklık verilerini topladıktan sonra, bir bitki için GDD hesaplanabilir.

Bunu manuel olarak yapmak için adımlar:

1. Bitki için temel sıcaklığı bulun. Örneğin, çilekler için temel sıcaklık 10°C'dir.

1. `temperature.csv` dosyasından günün en yüksek ve en düşük sıcaklıklarını bulun.

1. Daha önce verilen GDD hesaplamasını kullanarak GDD'yi hesaplayın.

Örneğin, günün en yüksek sıcaklığı 25°C ve en düşük sıcaklığı 12°C ise:

![GDD = 25 + 12 bölü 2, ardından sonuçtan 10 çıkarılarak 8.5 elde edilir](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.tr.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Bu nedenle çilekler **8.5** GDD almıştır. Çileklerin meyve vermesi için yaklaşık 250 GDD'ye ihtiyacı vardır, yani biraz daha zaman var.

---

## 🚀 Meydan Okuma

Bitkilerin büyümesi için sadece sıcaklık yeterli değildir. Başka hangi şeylere ihtiyaç vardır?

Bunlar için, bunları ölçebilecek sensörler var mı? Bu seviyeleri kontrol etmek için aktüatörler ne durumda? Bitki büyümesini optimize etmek için bir veya daha fazla IoT cihazını nasıl bir araya getirirsiniz?

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## İnceleme ve Kendi Kendine Çalışma

* [Dijital Tarım Wikipedia sayfasında](https://wikipedia.org/wiki/Digital_agriculture) dijital tarım hakkında daha fazla okuyun. Ayrıca [Hassas Tarım Wikipedia sayfasında](https://wikipedia.org/wiki/Precision_agriculture) hassas tarım hakkında daha fazla bilgi edinin.
* Tam büyüme derecesi günleri hesaplaması burada verilen basitleştirilmiş olandan daha karmaşıktır. Daha karmaşık denklem ve temel sıcaklığın altındaki sıcaklıklarla nasıl başa çıkılacağı hakkında daha fazla bilgi için [Büyüme Derecesi Günü Wikipedia sayfasını](https://wikipedia.org/wiki/Growing_degree-day) okuyun.
* Gelecekte yiyecek kıt olabilir, eğer hala aynı tarım yöntemlerini kullanmaya devam edersek. Bu konuda [Geleceğin Yüksek Teknoloji Çiftlikleri YouTube videosunda](https://www.youtube.com/watch?v=KIEOuKD9KX8) yüksek teknoloji tarım teknikleri hakkında daha fazla bilgi edinin.

## Ödev

[Jupyter Notebook kullanarak GDD verilerini görselleştirin](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.