<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T02:41:50+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "tr"
}
-->
# Meyve Kalitesi Dedektörü Oluşturma

## Talimatlar

Meyve kalitesi dedektörünü oluşturun!

Şimdiye kadar öğrendiğiniz her şeyi kullanarak prototip bir meyve kalitesi dedektörü oluşturun. Yakınlık temelinde görüntü sınıflandırmayı tetiklemek için kenarda çalışan bir AI modeli kullanın, sınıflandırma sonuçlarını depolamada saklayın ve meyvenin olgunluğuna göre bir LED'i kontrol edin.

Şimdiye kadar tüm derslerde yazdığınız kodları kullanarak bunu bir araya getirebilmelisiniz.

## Değerlendirme Ölçütleri

| Kriter | Örnek Düzey | Yeterli | Geliştirme Gerekiyor |
| ------- | ----------- | ------- | -------------------- |
| Tüm hizmetleri yapılandırma | IoT Hub, Azure işlevleri uygulaması ve Azure depolamasını kurmayı başardı | IoT Hub'ı kurmayı başardı, ancak Azure işlevleri uygulamasını veya Azure depolamasını kuramadı | Hiçbir internet IoT hizmetini kurmayı başaramadı |
| Yakınlığı izleme ve bir nesne önceden tanımlanmış bir mesafeden daha yakın olduğunda IoT Hub'a veri gönderme ve bir komutla kamerayı tetikleme | Mesafeyi ölçmeyi, nesne yeterince yakın olduğunda IoT Hub'a bir mesaj göndermeyi ve kamerayı tetiklemek için bir komut göndermeyi başardı | Yakınlığı ölçmeyi ve IoT Hub'a veri göndermeyi başardı, ancak kameraya bir komut gönderemedi | Mesafeyi ölçmeyi ve IoT Hub'a mesaj göndermeyi veya bir komut tetiklemeyi başaramadı |
| Bir görüntü yakalama, sınıflandırma ve sonuçları IoT Hub'a gönderme | Bir görüntü yakalamayı, kenar cihazı kullanarak sınıflandırmayı ve sonuçları IoT Hub'a göndermeyi başardı | Görüntüyü sınıflandırmayı başardı ancak kenar cihazı kullanmadı veya sonuçları IoT Hub'a gönderemedi | Bir görüntüyü sınıflandıramadı |
| Sınıflandırma sonuçlarına bağlı olarak bir cihaza gönderilen bir komutla LED'i açma veya kapatma | Meyve olgunlaşmamışsa bir komutla LED'i açmayı başardı | Cihaza komut göndermeyi başardı ancak LED'i kontrol edemedi | LED'i kontrol etmek için bir komut göndermeyi başaramadı |

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Orijinal belgenin kendi dilindeki hali, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.