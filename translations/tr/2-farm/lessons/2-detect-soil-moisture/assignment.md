<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-28T03:57:00+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "tr"
}
-->
# Sensörünüzü Kalibre Edin

## Talimatlar

Bu derste, 0-1023 arasında değerler olarak ölçülen toprak nem sensörü okumalarını topladınız. Bu değerleri gerçek toprak nem ölçümlerine dönüştürmek için sensörünüzü kalibre etmeniz gerekiyor. Bunu, toprak örneklerinden okumalar alarak ve bu örneklerden gravimetrik toprak nem içeriğini hesaplayarak yapabilirsiniz.

Bu adımları, her seferinde farklı nem seviyelerine sahip toprakla, gerekli okumaları almak için birkaç kez tekrarlamanız gerekecek.

1. Toprak nem sensörünü kullanarak bir toprak nem okuması alın. Bu okumayı not edin.

1. Toprak örneğini alın ve tartın. Bu ağırlığı not edin.

1. Toprağı kurutun - 110°C (230°F) sıcaklıkta birkaç saat boyunca sıcak bir fırın en iyi yöntemdir. Bunu güneş ışığında veya sıcak, kuru bir yerde toprağın tamamen kuruyana kadar yapabilirsiniz. Toprak toz gibi ve gevşek olmalıdır.

    > 💁 En doğru sonuçlar için bir laboratuvarda toprağı 48-72 saat boyunca bir fırında kurutursunuz. Okulunuzda kurutma fırınları varsa, daha uzun süre kurutmak için bunları kullanıp kullanamayacağınızı kontrol edin. Ne kadar uzun süre kurutulursa, örnek o kadar kuru olur ve sonuçlar o kadar doğru olur.

1. Toprağı tekrar tartın.

    > 🔥 Eğer fırında kuruttuysanız, önce soğuduğundan emin olun!

Gravimetrik toprak nemi şu şekilde hesaplanır:

![Toprak nemi % = ıslak ağırlık eksi kuru ağırlık, bölü kuru ağırlık, çarpı 100](../../../../../translated_images/tr/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - ıslak toprağın ağırlığı  
* W - kuru toprağın ağırlığı  

Örneğin, ıslak ağırlığı 212g ve kuru ağırlığı 197g olan bir toprak örneğiniz olduğunu varsayalım.

![Doldurulmuş hesaplama](../../../../../translated_images/tr/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g  
* W = 197g  
* 212 - 197 = 15  
* 15 / 197 = 0.076  
* 0.076 * 100 = 7.6%  

Bu örnekte, toprağın gravimetrik toprak nemi %7.6'dır.

En az 3 örnek için okumalar aldıktan sonra, toprak nemi % ile toprak nem sensörü okumasını gösteren bir grafik çizin ve noktalar için en iyi uyum çizgisini ekleyin. Daha sonra, bir sensör okuması için gravimetrik toprak nem içeriğini hesaplamak için bu çizgiden değeri okuyabilirsiniz.

## Değerlendirme Ölçütleri

| Kriter | Mükemmel | Yeterli | Geliştirme Gerekiyor |
| -------- | --------- | -------- | ----------------- |
| Kalibrasyon verilerini toplama | En az 3 kalibrasyon örneği alın | En az 2 kalibrasyon örneği alın | En az 1 kalibrasyon örneği alın |
| Kalibre edilmiş bir okuma yapma | Kalibrasyon grafiğini başarıyla çiz ve sensörden bir okuma yaparak bunu gravimetrik toprak nem içeriğine dönüştür | Kalibrasyon grafiğini başarıyla çiz | Grafiği çizemedi |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.