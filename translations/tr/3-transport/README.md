<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-28T03:11:54+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "tr"
}
-->
# Çiftlikten fabrikaya taşımacılık - IoT kullanarak gıda teslimatlarını takip etme

Birçok çiftçi, yetiştirdikleri ürünleri satmak için tarım yapar - ya yetiştirdiklerinin tamamını satan ticari çiftçilerdir ya da ihtiyaçlarını karşılamak için fazla ürünlerini satan geçimlik çiftçilerdir. Bir şekilde, gıdanın çiftlikten tüketiciye ulaşması gerekir ve bu genellikle çiftliklerden, merkezlere veya işleme tesislerine, ardından mağazalara yapılan toplu taşımacılığa dayanır. Örneğin, bir domates çiftçisi domatesleri hasat eder, kutulara yerleştirir, kutuları bir kamyona yükler ve ardından bir işleme tesisine teslim eder. Domatesler burada ayrıştırılır ve ardından işlenmiş gıda, perakende satış veya restoranlarda tüketim şeklinde tüketicilere ulaştırılır.

IoT, bu tedarik zincirine, taşınan gıdaları takip ederek yardımcı olabilir - sürücülerin doğru yerlere gidip gitmediğini kontrol ederek, araçların konumlarını izleyerek ve araçlar varış noktasına ulaştığında uyarılar alarak, gıdaların mümkün olan en kısa sürede boşaltılıp işlenmeye hazır hale gelmesini sağlayabilir.

> 🎓 *Tedarik zinciri*, bir şeyin üretilmesi ve teslim edilmesi için yapılan faaliyetlerin sırasıdır. Örneğin, domates tarımında bu zincir; tohum, toprak, gübre ve su teminini, domates yetiştirmeyi, domatesleri bir merkeze teslim etmeyi, bunları bir süpermarketin yerel merkezine taşımayı, bireysel süpermarkete taşımayı, sergilenmeyi, ardından bir tüketiciye satılmayı ve eve götürülüp yenmeyi kapsar. Her adım, zincirin halkaları gibidir.

> 🎓 Tedarik zincirinin taşımacılık kısmına *lojistik* denir.

Bu 4 derste, bir (sanal) kamyona yüklenen gıdaları izleyerek ve kamyonun varış noktasına hareketini takip ederek, IoT'yi tedarik zincirini iyileştirmek için nasıl uygulayacağınızı öğreneceksiniz. GPS takibi, GPS verilerini nasıl depolayıp görselleştireceğinizi ve bir kamyon varış noktasına ulaştığında nasıl uyarı alacağınızı öğreneceksiniz.

> 💁 Bu derslerde bazı bulut kaynakları kullanılacaktır. Eğer bu projedeki tüm dersleri tamamlamazsanız, [Projenizi temizleyin](../clean-up.md) bölümüne göz atmayı unutmayın.

## Konular

1. [Konum takibi](lessons/1-location-tracking/README.md)
1. [Konum verilerini depolama](lessons/2-store-location-data/README.md)
1. [Konum verilerini görselleştirme](lessons/3-visualize-location-data/README.md)
1. [Coğrafi çitler](lessons/4-geofences/README.md)

## Katkıda Bulunanlar

Tüm dersler, [Jen Looper](https://github.com/jlooper) ve [Jim Bennett](https://GitHub.com/JimBobBennett) tarafından ♥️ ile yazılmıştır.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.