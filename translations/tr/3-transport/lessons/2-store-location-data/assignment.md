<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T03:24:12+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "tr"
}
-->
# Fonksiyon Bağlantılarını İnceleyin

## Talimatlar

Fonksiyon bağlantıları, `main` fonksiyonundan döndürülerek kodunuzun blobları blob depolamaya kaydetmesine olanak tanır. Azure Depolama hesabı, koleksiyon ve diğer ayrıntılar `function.json` dosyasında yapılandırılır.

Azure veya diğer Microsoft teknolojileriyle çalışırken, en iyi bilgi kaynağı [docs.com'daki Microsoft belgeleridir](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Bu görevde, çıktı bağlantısını nasıl ayarlayacağınızı öğrenmek için Azure Functions bağlantı belgelerini okumanız gerekecek.

Başlamak için bakabileceğiniz bazı sayfalar şunlardır:

* [Azure Functions tetikleyicileri ve bağlantı kavramları](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions için Azure Blob depolama bağlantılarına genel bakış](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions için Azure Blob depolama çıktı bağlantısı](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Değerlendirme Kriterleri

| Kriter | Örnek Niteliğinde | Yeterli | Geliştirmeye İhtiyaç Var |
| ------- | ----------------- | ------- | ----------------------- |
| Blob depolama çıktı bağlantısını yapılandırma | Çıktı bağlantısını yapılandırabildi, blobu döndürdü ve blob depolamaya başarıyla kaydedebildi | Çıktı bağlantısını yapılandırabildi veya blobu döndürdü ancak blob depolamaya başarıyla kaydedemedi | Çıktı bağlantısını yapılandıramadı |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.