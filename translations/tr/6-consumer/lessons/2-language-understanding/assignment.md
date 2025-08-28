<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-28T02:55:12+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "tr"
}
-->
# Zamanlayıcıyı İptal Et

## Talimatlar

Bu derste şu ana kadar bir zamanlayıcı ayarlamayı anlayan bir model eğittiniz. Bir başka faydalı özellik ise zamanlayıcıyı iptal etmektir - belki ekmeğiniz hazırdır ve zamanlayıcı süresi dolmadan fırından çıkarılabilir.

LUIS uygulamanıza zamanlayıcıyı iptal etmek için yeni bir niyet ekleyin. Bu niyet için herhangi bir varlık gerekmez, ancak bazı örnek cümlelere ihtiyaç duyacaktır. Eğer bu niyet en üst niyet olarak algılanırsa, bunu sunucusuz kodunuzda ele alın, niyetin tanındığını kaydedin ve uygun bir yanıt döndürün.

## Değerlendirme Kriterleri

| Kriter | Örnek Niteliğinde | Yeterli | Geliştirmeye Açık |
| ------- | ----------------- | ------- | ----------------- |
| Zamanlayıcıyı iptal etme niyetini LUIS uygulamasına ekleme | Niyeti ekleyip modeli eğitebildi | Niyeti ekleyebildi ancak modeli eğitemedi | Niyeti ekleyip modeli eğitemedi |
| Niyeti sunucusuz uygulamada ele alma | Niyeti en üst niyet olarak algılayıp kaydedebildi | Niyeti en üst niyet olarak algılayabildi | Niyeti en üst niyet olarak algılayamadı |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.