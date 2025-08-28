<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T03:18:59+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "tr"
}
-->
# Twilio Kullanarak Bildirim Gönderme

## Talimatlar

Şu ana kadar yazdığınız kodda yalnızca coğrafi çit (geofence) mesafesini logladınız. Bu görevde, GPS koordinatları coğrafi çitin içinde olduğunda bir bildirim eklemeniz gerekecek; bu bildirim bir kısa mesaj (SMS) veya e-posta olabilir.

Azure Functions, Twilio gibi üçüncü taraf hizmetlere bağlanmak da dahil olmak üzere birçok bağlama seçeneği sunar.

* [Twilio.com](https://www.twilio.com) adresinden ücretsiz bir hesap oluşturun.
* Azure Functions'ı Twilio SMS ile bağlama hakkında [Microsoft dokümanlarındaki Twilio binding for Azure Functions sayfasını](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python) okuyun.
* Azure Functions'ı Twilio SendGrid ile bağlayarak e-posta gönderme hakkında [Microsoft dokümanlarındaki Azure Functions SendGrid bindings sayfasını](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python) okuyun.
* GPS koordinatlarının coğrafi çitin içinde veya dışında olduğuna dair bildirim almak için Functions uygulamanıza bağlama ekleyin - ancak her ikisi için değil.

## Değerlendirme Kriterleri

| Kriter | Örnek Niteliğinde | Yeterli | Geliştirme Gerekiyor |
| ------- | ----------------- | ------- | -------------------- |
| Fonksiyon bağlamalarını yapılandırma ve e-posta veya SMS alma | Fonksiyon bağlamalarını yapılandırabildi ve coğrafi çitin içinde veya dışında olduğunda bir e-posta veya SMS almayı başardı, ancak her ikisi için değil | Bağlamaları yapılandırabildi ancak e-posta veya SMS gönderemedi ya da yalnızca koordinatlar hem içinde hem de dışındayken gönderebildi | Bağlamaları yapılandıramadı ve e-posta veya SMS gönderemedi |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.