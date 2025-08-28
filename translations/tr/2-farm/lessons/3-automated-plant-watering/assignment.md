<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T04:19:13+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "tr"
}
-->
# Daha Verimli Bir Sulama Döngüsü Oluşturun

## Talimatlar

Bu ders, bir röleyi sensör verileriyle nasıl kontrol edeceğinizi ele aldı ve bu röle, bir sulama sistemi için bir pompayı kontrol edebilir. Belirli bir toprak alanı için, pompanın sabit bir süre çalıştırılması, her zaman toprak nemi üzerinde aynı etkiye sahip olmalıdır. Bu, belirli bir toprak nemi düşüşüne karşılık gelen sulama süresini saniye cinsinden tahmin etmenizi sağlar. Bu verileri kullanarak daha kontrollü bir sulama sistemi oluşturabilirsiniz.

Bu ödevde, toprak neminde belirli bir artış için pompanın ne kadar süre çalışması gerektiğini hesaplayacaksınız.

> ⚠️ Sanal IoT donanımı kullanıyorsanız, bu süreci uygulayabilirsiniz, ancak röle açıkken toprak nemi okumasını saniyede sabit bir miktar artırarak sonuçları simüle edin.

1. Kuru toprakla başlayın. Toprak nemini ölçün.

1. Sabit bir miktarda su ekleyin, ya pompayı 1 saniye çalıştırarak ya da sabit bir miktar su dökerek.

    > Pompa her zaman sabit bir hızda çalışmalıdır, bu nedenle pompa her saniye çalıştığında aynı miktarda su sağlamalıdır.

1. Toprak nem seviyesi sabitlenene kadar bekleyin ve bir ölçüm alın.

1. Bu işlemi birkaç kez tekrarlayın ve sonuçların bir tablosunu oluşturun. Aşağıda bu tabloya bir örnek verilmiştir.

    | Toplam Pompa Süresi | Toprak Nemi | Azalma |
    | --- | --: | -: |
    | Kuru | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Toprak neminde, suyun her saniyesinde meydana gelen ortalama artışı hesaplayın. Yukarıdaki örnekte, suyun her saniyesi okuma değerini ortalama 20.3 azaltmaktadır.

1. Bu verileri, sunucu kodunuzun verimliliğini artırmak için kullanın ve pompayı, toprak nemini istenen seviyeye getirmek için gereken süre boyunca çalıştırın.

## Değerlendirme Kriterleri

| Kriter | Mükemmel | Yeterli | Geliştirme Gerekli |
| -------- | --------- | -------- | ----------------- |
| Toprak nemi verilerini toplama | Sabit miktarlarda su ekledikten sonra birden fazla ölçüm alabilir | Sabit miktarlarda su ile bazı ölçümler alabilir | Sadece bir veya iki ölçüm alabilir ya da sabit miktarlarda su kullanamaz |
| Sunucu kodunu kalibre etme | Toprak nemi okumasındaki ortalama azalmayı hesaplayabilir ve sunucu kodunu buna göre güncelleyebilir | Ortalama bir azalma hesaplayabilir, ancak sunucu kodunu güncelleyemez ya da ortalama bir azalmayı doğru şekilde hesaplayamaz, ancak bu değeri kullanarak sunucu kodunu doğru şekilde günceller | Ortalama bir azalmayı hesaplayamaz ya da sunucu kodunu güncelleyemez |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.