<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-28T04:04:21+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "tr"
}
-->
# Yeni Bir IoT Cihazı Oluşturma

## Talimatlar

Son 6 derste dijital tarım hakkında bilgi edindiniz ve IoT cihazlarını kullanarak veri toplama, bitki büyümesini tahmin etme ve toprak nemi ölçümlerine dayanarak sulamayı otomatikleştirme konularını öğrendiniz.

Öğrendiklerinizi kullanarak bir sensör ve aktüatör seçerek yeni bir IoT cihazı oluşturun. Telemetriyi bir IoT Hub'a gönderin ve bunu sunucusuz kod aracılığıyla bir aktüatörü kontrol etmek için kullanın. Bu veya önceki projede kullandığınız bir sensör ve aktüatörü kullanabilir ya da başka bir donanımınız varsa yeni bir şey deneyebilirsiniz.

## Değerlendirme Ölçütleri

| Kriter | Örnek Niteliğinde | Yeterli | Geliştirme Gerekiyor |
| ------- | ----------------- | ------- | -------------------- |
| IoT cihazını bir sensör ve aktüatörle kodlama | Sensör ve aktüatörle çalışan bir IoT cihazı kodladı | Sensör veya aktüatörle çalışan bir IoT cihazı kodladı | Sensör veya aktüatörle çalışan bir IoT cihazı kodlayamadı |
| IoT cihazını IoT Hub'a bağlama | IoT Hub'ı kurup telemetri gönderdi ve komutlar aldı | IoT Hub'ı kurup telemetri gönderdi veya komutlar aldı | IoT Hub'ı kurup IoT cihazıyla iletişim kuramadı |
| Aktüatörü sunucusuz kodla kontrol etme | Telemetri olaylarıyla tetiklenen bir Azure Function kurup cihazı kontrol etti | Telemetri olaylarıyla tetiklenen bir Azure Function kurdu ancak aktüatörü kontrol edemedi | Azure Function kuramadı |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.