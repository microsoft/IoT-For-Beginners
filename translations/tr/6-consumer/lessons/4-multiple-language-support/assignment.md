<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T03:11:33+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "tr"
}
-->
# Evrensel Bir Çevirici Oluşturma

## Talimatlar

Evrensel bir çevirici, birden fazla dil arasında çeviri yapabilen ve farklı diller konuşan kişilerin iletişim kurmasını sağlayan bir cihazdır. Son birkaç derste öğrendiklerinizi kullanarak 2 IoT cihazı ile bir evrensel çevirici oluşturun.

> Eğer 2 cihazınız yoksa, önceki birkaç derste anlatılan adımları takip ederek bir sanal IoT cihazını IoT cihazlarından biri olarak ayarlayın.

Bir cihazı bir dil için, diğerini başka bir dil için yapılandırmalısınız. Her cihaz konuşmayı kabul etmeli, metne dönüştürmeli, IoT Hub ve Functions uygulaması aracılığıyla diğer cihaza göndermeli, ardından çeviriyi yapıp çevrilen konuşmayı oynatmalıdır.

> 💁 İpucu: Bir cihazdan diğerine konuşma gönderirken, konuşmanın hangi dilde olduğunu da gönderin, böylece çeviri yapmak daha kolay olur. Hatta her cihazın önce IoT Hub ve Functions uygulaması kullanarak kaydolmasını sağlayabilir, destekledikleri dili Azure Storage'da saklamak üzere iletebilirsiniz. Daha sonra çevirileri yapmak için bir Functions uygulaması kullanabilir ve çevrilen metni IoT cihazına gönderebilirsiniz.

## Değerlendirme Ölçütleri

| Kriter | Örnek Niteliğinde | Yeterli | Geliştirme Gerekiyor |
| ------- | ----------------- | ------- | -------------------- |
| Evrensel bir çevirici oluşturma | Bir cihaz tarafından algılanan konuşmayı başka bir cihazda farklı bir dilde oynatılan konuşmaya dönüştüren bir evrensel çevirici oluşturmayı başardı | Bazı bileşenleri çalıştırmayı başardı, örneğin konuşmayı yakalama veya çeviri yapma, ancak uçtan uca çözümü oluşturamadı | Çalışan bir evrensel çeviricinin herhangi bir parçasını oluşturmayı başaramadı |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlama veya yanlış yorumlamalardan sorumlu değiliz.