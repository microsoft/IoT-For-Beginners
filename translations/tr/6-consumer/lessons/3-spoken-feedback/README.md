# Bir zamanlayıcı ayarlayın ve sesli geri bildirim sağlayın

![Bu dersin bir sketchnote özeti](../../../../../translated_images/tr/lesson-23.f38483e1d4df4828.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için resme tıklayın.

## Ders öncesi test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Giriş

Akıllı asistanlar tek yönlü iletişim cihazları değildir. Onlara konuşursunuz ve size yanıt verirler:

"Alexa, 3 dakikalık bir zamanlayıcı ayarla"

"Tamam, zamanlayıcınız 3 dakika için ayarlandı"

Son iki derste konuşmayı metne dönüştürmeyi ve ardından bu metinden bir zamanlayıcı ayarlama isteğini çıkarmayı öğrendiniz. Bu derste, IoT cihazında zamanlayıcıyı nasıl ayarlayacağınızı, kullanıcıya zamanlayıcılarını onaylayan sesli bir yanıtla nasıl geri bildirim vereceğinizi ve zamanlayıcıları bittiğinde onları nasıl uyaracağınızı öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Metinden konuşmaya](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Zamanlayıcıyı ayarla](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Metni konuşmaya dönüştür](../../../../../6-consumer/lessons/3-spoken-feedback)

## Metinden konuşmaya

Adından da anlaşılacağı gibi, metinden konuşmaya işlemi, metni sesli kelimeler olarak içeren sese dönüştürme sürecidir. Temel prensip, metindeki kelimeleri bileşen seslerine (fonemler olarak bilinir) ayırmak ve bu sesler için sesleri birleştirmek, ya önceden kaydedilmiş sesleri kullanarak ya da yapay zeka modelleri tarafından üretilen sesleri kullanarak gerçekleştirilir.

![Tipik metinden konuşmaya sistemlerinin üç aşaması](../../../../../translated_images/tr/tts-overview.193843cf3f5ee09f.webp)

Metinden konuşmaya sistemleri genellikle 3 aşamadan oluşur:

* Metin analizi
* Dilbilimsel analiz
* Dalga formu oluşturma

### Metin analizi

Metin analizi, sağlanan metni alıp konuşma üretmek için kullanılabilecek kelimelere dönüştürmeyi içerir. Örneğin, "Merhaba dünya"yı dönüştürmek istiyorsanız, metin analizi gerekmez, iki kelime konuşmaya dönüştürülebilir. Ancak "1234" varsa, bu bağlama bağlı olarak "Bin iki yüz otuz dört" veya "Bir, iki, üç, dört" olarak dönüştürülmesi gerekebilir. "1234 elmam var" için "Bin iki yüz otuz dört" olurken, "Çocuk 1234'ü saydı" için "Bir, iki, üç, dört" olur.

Oluşturulan kelimeler yalnızca dil için değil, aynı zamanda o dilin yerel varyasyonu için de değişir. Örneğin, Amerikan İngilizcesinde 120 "Yüz yirmi" olarak ifade edilirken, İngiliz İngilizcesinde "Yüz ve yirmi" olarak ifade edilir, yüzlerden sonra "ve" kullanılır.

✅ Metin analizi gerektiren diğer örnekler arasında "in" kelimesinin inç kısaltması olarak kullanılması ve "st" kelimesinin aziz veya sokak kısaltması olarak kullanılması yer alır. Dilinizde bağlam olmadan belirsiz olan başka kelimeler düşünebilir misiniz?

Kelime tanımlandıktan sonra dilbilimsel analize gönderilir.

### Dilbilimsel analiz

Dilbilimsel analiz, kelimeleri fonemlere ayırır. Fonemler yalnızca kullanılan harflere değil, kelimedeki diğer harflere de dayanır. Örneğin, İngilizcede 'car' ve 'care' kelimelerindeki 'a' sesi farklıdır. İngilizce dilinde alfabedeki 26 harf için 44 farklı fonem vardır, bazıları farklı harfler tarafından paylaşılır, örneğin 'circle' ve 'serpent' kelimelerinin başlangıcında aynı fonem kullanılır.

✅ Araştırma yapın: Dilinizdeki fonemler nelerdir?

Kelime fonemlere dönüştürüldükten sonra, bu fonemler bağlama bağlı olarak tonlama, ton veya süreyi ayarlamak için ek verilere ihtiyaç duyar. Bir örnek, İngilizcede bir cümleyi soruya dönüştürmek için ton yükseltmelerinin kullanılabilmesidir; son kelime için yükseltilmiş bir tonlama bir soruyu ima eder.

Örneğin - "Bir elman var" cümlesi, bir elmanız olduğunu belirten bir ifadedir. Sonunda tonlama yükselirse, elma kelimesi için artarak "Bir elman var mı?" sorusuna dönüşür, elmanız olup olmadığını sorar. Dilbilimsel analiz, tonlamayı artırmaya karar vermek için sonundaki soru işaretini kullanmalıdır.

Fonemler oluşturulduktan sonra, ses çıkışı üretmek için dalga formu oluşturma işlemine gönderilir.

### Dalga formu oluşturma

İlk elektronik metinden konuşmaya sistemleri, her fonem için tek bir ses kaydı kullanıyordu, bu da çok monoton, robotik seslere yol açıyordu. Dilbilimsel analiz fonemler üretir, bunlar bir ses veritabanından yüklenir ve ses oluşturmak için birleştirilirdi.

✅ Araştırma yapın: Erken konuşma sentezleme sistemlerinden bazı ses kayıtlarını bulun. Bunu modern konuşma sentezleme ile karşılaştırın, örneğin akıllı asistanlarda kullanılan sistemlerle.

Daha modern dalga formu oluşturma, insanlardan ayırt edilemeyen daha doğal sesler üretmek için derin öğrenme (beyindeki nöronlara benzer şekilde çalışan çok büyük sinir ağları) kullanılarak oluşturulan ML modellerini kullanır.

> 💁 Bu ML modellerinden bazıları, gerçek insanlar gibi ses çıkarmak için transfer öğrenimi kullanılarak yeniden eğitilebilir. Bu, sesin bir güvenlik sistemi olarak kullanılması anlamına gelir, bankaların giderek daha fazla denediği bir şeydir, ancak sesinizin birkaç dakikalık bir kaydına sahip olan herkes sizi taklit edebilir.

Bu büyük ML modelleri, üç adımı birleştirerek uçtan uca konuşma sentezleyiciler oluşturmak için eğitiliyor.

## Zamanlayıcıyı ayarla

Zamanlayıcıyı ayarlamak için IoT cihazınızın, sunucusuz kod kullanarak oluşturduğunuz REST uç noktasını çağırması ve ardından döndürülen saniye sayısını kullanarak bir zamanlayıcı ayarlaması gerekir.

### Görev - sunucusuz işlevi çağırarak zamanlayıcı süresini alın

IoT cihazınızdan REST uç noktasını çağırmak ve gerekli süre için bir zamanlayıcı ayarlamak için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer-set-timer.md)

## Metni konuşmaya dönüştür

Konuşmayı metne dönüştürmek için kullandığınız aynı konuşma hizmeti, metni tekrar konuşmaya dönüştürmek için kullanılabilir ve bu, IoT cihazınızdaki bir hoparlör aracılığıyla çalınabilir. Dönüştürülecek metin, konuşma hizmetine gönderilir, ses türü (örneğin örnekleme oranı) ile birlikte ve ses içeren ikili veri döndürülür.

Bu isteği gönderdiğinizde, *Konuşma Sentezleme İşaretleme Dili* (SSML) kullanarak gönderirsiniz, konuşma sentezleme uygulamaları için XML tabanlı bir işaretleme dili. Bu, yalnızca dönüştürülecek metni değil, metnin dilini, kullanılacak sesi tanımlar ve hatta bazı veya tüm kelimeler için hız, ses seviyesi ve tonlama tanımlamak için kullanılabilir.

Örneğin, bu SSML, "3 dakika 5 saniyelik zamanlayıcınız ayarlandı" metnini `en-GB-MiaNeural` adlı bir İngiliz İngilizcesi sesi kullanarak konuşmaya dönüştürme isteğini tanımlar.

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Çoğu metinden konuşmaya sistemi, farklı diller için ilgili aksanlarla birden fazla ses içerir, örneğin İngiliz aksanlı bir İngiliz İngilizcesi sesi ve Yeni Zelanda aksanlı bir Yeni Zelanda İngilizcesi sesi.

### Görev - metni konuşmaya dönüştür

IoT cihazınızı kullanarak metni konuşmaya dönüştürmek için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-text-to-speech.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-text-to-speech.md)

---

## 🚀 Zorluk

SSML, kelimelerin nasıl konuşulduğunu değiştirmek için yollar sunar, örneğin belirli kelimelere vurgu eklemek, duraklamalar eklemek veya tonlamayı değiştirmek. IoT cihazınızdan farklı SSML göndererek ve çıktıyı karşılaştırarak bunları deneyin. SSML hakkında daha fazla bilgi edinebilir, kelimelerin nasıl konuşulduğunu değiştirme yollarını öğrenebilirsiniz: [World Wide Web konsorsiyumunun Speech Synthesis Markup Language (SSML) Version 1.1 spesifikasyonu](https://www.w3.org/TR/speech-synthesis11/).

## Ders sonrası test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Gözden Geçirme ve Kendi Kendine Çalışma

* Konuşma sentezleme hakkında daha fazla bilgi edinin: [Wikipedia'daki konuşma sentezleme sayfası](https://wikipedia.org/wiki/Speech_synthesis)
* Suçluların konuşma sentezlemeyi nakit çalmak için nasıl kullandığını öğrenin: [BBC haberindeki 'sahte sesler siber suçluların nakit çalmasına yardımcı oluyor' hikayesi](https://www.bbc.com/news/technology-48908736)
* Seslendirme sanatçılarının seslerinin sentezlenmiş versiyonlarından kaynaklanan riskler hakkında daha fazla bilgi edinin: [Vice'daki 'Bu TikTok davası, yapay zekanın seslendirme sanatçılarını nasıl zor durumda bıraktığını gösteriyor' makalesi](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Ödev

[Zamanlayıcıyı iptal et](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.