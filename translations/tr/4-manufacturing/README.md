<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T02:36:12+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "tr"
}
-->
# Üretim ve işleme - IoT kullanarak gıda işleme süreçlerini iyileştirme

Gıda bir merkezi hub'a veya işleme tesisine ulaştığında, her zaman doğrudan süpermarketlere gönderilmez. Çoğu zaman, gıda kaliteye göre ayrıştırma gibi bir dizi işleme adımından geçer. Bu, eskiden manuel bir süreçti - tarlada çalışanlar sadece olgun meyveleri toplar, ardından fabrikada meyveler bir taşıma bandında ilerler ve çalışanlar çürük veya bozulmuş meyveleri manuel olarak ayırırdı. Okul döneminde yaz işinde çilek toplama ve ayırma işi yapmış biri olarak, bunun eğlenceli bir iş olmadığını söyleyebilirim.

Daha modern sistemler, ayrıştırma için IoT'ye dayanır. [Weco](https://wecotek.com) gibi erken dönem cihazlar, optik sensörler kullanarak ürün kalitesini tespit eder ve örneğin yeşil domatesleri reddeder. Bu cihazlar, çiftlikteki hasat makinelerinde veya işleme tesislerinde kullanılabilir.

Yapay Zeka (AI) ve Makine Öğrenimi (ML) alanındaki ilerlemelerle birlikte, bu makineler daha gelişmiş hale gelebilir. ML modelleri, meyve ile taş, toprak veya böcek gibi yabancı nesneleri ayırt etmek için eğitilebilir. Bu modeller ayrıca sadece çürük meyveleri değil, hastalıkların erken tespiti veya diğer mahsul sorunlarını da belirlemek için eğitilebilir.

> 🎓 *ML modeli* terimi, bir veri seti üzerinde makine öğrenimi yazılımını eğitmenin çıktısını ifade eder. Örneğin, olgun ve olgunlaşmamış domatesleri ayırt etmek için bir ML modeli eğitebilir, ardından yeni görüntülerde domateslerin olgun olup olmadığını kontrol etmek için bu modeli kullanabilirsiniz.

Bu 4 derste, meyve kalitesini tespit etmek için görüntü tabanlı AI modellerini nasıl eğiteceğinizi, bunları bir IoT cihazında nasıl kullanacağınızı ve bunları bulut yerine IoT cihazında, yani uçta nasıl çalıştıracağınızı öğreneceksiniz.

> 💁 Bu derslerde bazı bulut kaynakları kullanılacaktır. Bu projedeki tüm dersleri tamamlamazsanız, [projenizi temizlediğinizden](../clean-up.md) emin olun.

## Konular

1. [Meyve kalitesi tespit edici eğitimi](./lessons/1-train-fruit-detector/README.md)
1. [IoT cihazından meyve kalitesini kontrol etme](./lessons/2-check-fruit-from-device/README.md)
1. [Meyve tespit ediciyi uçta çalıştırma](./lessons/3-run-fruit-detector-edge/README.md)
1. [Sensörden meyve kalitesi tespiti tetikleme](./lessons/4-trigger-fruit-detector/README.md)

## Katkıda Bulunanlar

Tüm dersler [Jen Fox](https://github.com/jenfoxbot) ve [Jim Bennett](https://GitHub.com/JimBobBennett) tarafından ♥️ ile yazılmıştır.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.