# Birden Fazla Dili Destekleme

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/tr/lesson-24.4246968ed058510a.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

Bu video, Azure konuşma hizmetlerinin genel bir özetini sunar. Daha önceki derslerde ele alınan konuşmadan metne ve metinden konuşmaya konularını kapsar. Ayrıca bu derste ele alınan konuşma çevirisini de içerir:

[![Microsoft Build 2020'den birkaç satır Python ile konuşmayı tanıma](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Videoyu izlemek için yukarıdaki görsele tıklayın

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Giriş

Son 3 derste, konuşmayı metne dönüştürme, dil anlama ve metni konuşmaya dönüştürme konularını öğrendiniz. Tüm bu işlemler yapay zeka tarafından desteklenmektedir. Yapay zekanın insan iletişiminde yardımcı olabileceği bir diğer alan ise dil çevirisidir - bir dili başka bir dile dönüştürmek, örneğin İngilizceden Fransızcaya.

Bu derste, yapay zekayı kullanarak metin çevirisi yapmayı öğreneceksiniz. Böylece akıllı zamanlayıcınızın birden fazla dilde kullanıcılarla etkileşim kurmasını sağlayabilirsiniz.

Bu derste şunları ele alacağız:

* [Metin çevir](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Çeviri hizmetleri](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Bir çeviri kaynağı oluştur](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Uygulamalarda çevirilerle birden fazla dili destekleme](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Bir yapay zeka hizmeti kullanarak metin çevir](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Bu proje içindeki son derstir. Bu dersi ve ödevi tamamladıktan sonra bulut hizmetlerinizi temizlemeyi unutmayın. Ödevi tamamlamak için bu hizmetlere ihtiyacınız olacak, bu yüzden önce ödevi tamamladığınızdan emin olun.
>
> Gerekirse [projenizi temizleme rehberine](../../../clean-up.md) başvurabilirsiniz.

## Metin Çevir

Metin çevirisi, bilgisayar bilimlerinde 70 yılı aşkın süredir araştırılan bir problemdir. Ancak yapay zeka ve bilgisayar gücündeki ilerlemeler sayesinde, insan çevirmenler kadar iyi bir seviyeye ulaşmaya oldukça yaklaştı.

> 💁 Kökenleri daha da geriye, 9. yüzyılda dil çevirisi teknikleri geliştiren Arap kriptograf [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi)'ye kadar izlenebilir.

### Makine Çevirileri

Metin çevirisi, farklı dil çiftleri arasında çeviri yapabilen Makine Çevirisi (MT) olarak bilinen bir teknolojiyle başladı. MT, bir dildeki kelimeleri başka bir dildeki kelimelerle değiştirme ve basit kelime kelime çevirinin anlamlı olmadığı durumlarda ifadeleri veya cümle parçalarını doğru şekilde çevirmek için teknikler ekleme prensibiyle çalışır.

> 🎓 Çevirmenler bir dilden diğerine çeviri yapmayı desteklediğinde, bunlara *dil çiftleri* denir. Farklı araçlar farklı dil çiftlerini destekler ve bu destek tam olmayabilir. Örneğin, bir çevirmen İngilizceden İspanyolcaya ve İspanyolcadan İtalyancaya çeviri yapabilir, ancak İngilizceden İtalyancaya çeviri yapamayabilir.

Örneğin, İngilizce "Hello world" ifadesini Fransızcaya çevirmek, "Hello" için "Bonjour" ve "world" için "le monde" kelimelerini değiştirerek doğru çeviri olan "Bonjour le monde" sonucunu verir.

Ancak, farklı diller aynı şeyi ifade etmek için farklı yollar kullandığında bu tür değişiklikler işe yaramaz. Örneğin, İngilizce "My name is Jim" cümlesi Fransızcaya "Je m'appelle Jim" olarak çevrilir - kelimenin tam anlamıyla "Ben kendime Jim diyorum". "Je" Fransızca "Ben" anlamına gelir, "moi" "ben"dir, ancak bir ünlüyle başladığı için fiille birleştirilir ve "m'" olur, "appelle" "aramak" anlamına gelir ve "Jim" bir isim olduğu için çevrilmez. Kelime sıralaması da bir sorun haline gelir - "Je m'appelle Jim" ifadesinin basit bir çevirisi "I myself call Jim" olur ve İngilizceye göre farklı bir kelime sıralaması içerir.

> 💁 Bazı kelimeler asla çevrilmez - adım Jim'dir ve hangi dilde tanıtım yaparsam yapayım bu değişmez. Farklı alfabeler kullanan veya farklı sesler için farklı harfler kullanan dillere çeviri yaparken, kelimeler *transliterasyon* ile çevrilebilir, yani verilen kelimeyle aynı sesi vermek için uygun harfler veya karakterler seçilir.

Deyimler de çeviri için bir sorundur. Bunlar, kelimelerin doğrudan yorumlanmasından farklı bir anlamı olan ifadelerdir. Örneğin, İngilizce "I've got ants in my pants" deyimi, kıyafetinizde karınca olduğu anlamına gelmez, huzursuz olduğunuzu ifade eder. Bu deyimi Almancaya çevirirseniz, dinleyiciyi şaşırtırsınız çünkü Almanca versiyonu "I have bumble bees in the bottom" şeklindedir.

> 💁 Farklı bölgeler farklı karmaşıklıklar ekler. "Ants in your pants" deyiminde, Amerikan İngilizcesinde "pants" dış giyim anlamına gelirken, İngiliz İngilizcesinde "pants" iç çamaşırı anlamına gelir.

✅ Birden fazla dil biliyorsanız, doğrudan çevrilemeyen bazı ifadeler düşünün.

Makine çeviri sistemleri, belirli ifadelerin ve deyimlerin nasıl çevrileceğini tanımlayan büyük kural veritabanlarına dayanır. Ayrıca, olası seçeneklerden uygun çevirileri seçmek için istatistiksel yöntemler kullanır. Bu istatistiksel yöntemler, birden fazla dile insanlar tarafından çevrilmiş büyük veri tabanlarını kullanarak en olası çeviriyi seçer. Bu tekniğe *istatistiksel makine çevirisi* denir. Bazıları, bir dili ara bir temsile çevirip, ardından bu ara temsilden başka bir dile çevirerek çalışan ara temsiller kullanır. Bu şekilde, daha fazla dil eklemek, tüm diğer dillere çeviriler yerine ara temsile ve ara temsilden çeviriler içerir.

### Sinirsel Çeviriler

Sinirsel çeviriler, genellikle tüm cümleleri tek bir model kullanarak çevirmek için yapay zekanın gücünden yararlanır. Bu modeller, web sayfaları, kitaplar ve Birleşmiş Milletler belgeleri gibi insanlar tarafından çevrilmiş büyük veri setleri üzerinde eğitilir.

Sinirsel çeviri modelleri, deyim ve ifadeler için büyük veri tabanlarına ihtiyaç duymadıkları için genellikle makine çeviri modellerinden daha küçüktür. Modern yapay zeka hizmetleri, çeviriler sağlarken genellikle birden fazla tekniği birleştirir, istatistiksel makine çevirisi ve sinirsel çeviriyi karıştırır.

Hiçbir dil çifti için birebir çeviri yoktur. Farklı çeviri modelleri, modelin eğitildiği verilere bağlı olarak biraz farklı sonuçlar üretebilir. Çeviriler her zaman simetrik değildir - bir cümleyi bir dilden diğerine çevirip, ardından tekrar ilk dile çevirdiğinizde, biraz farklı bir cümle elde edebilirsiniz.

✅ [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) veya Apple çeviri uygulaması gibi farklı çevrimiçi çevirmenleri deneyin. Birkaç cümlenin çevirilerini karşılaştırın. Ayrıca birinde çevirip, diğerinde geri çevirerek deneyin.

## Çeviri Hizmetleri

Uygulamalarınızdan konuşma ve metin çevirisi yapmak için kullanabileceğiniz bir dizi yapay zeka hizmeti vardır.

### Bilişsel Hizmetler Konuşma Hizmeti

![Konuşma hizmeti logosu](../../../../../translated_images/tr/azure-speech-logo.a1f08c4befb0159f.webp)

Son birkaç derste kullandığınız konuşma hizmeti, konuşma tanıma için çeviri yeteneklerine sahiptir. Konuşmayı tanıdığınızda, yalnızca aynı dildeki konuşmanın metnini değil, aynı zamanda diğer dillerdeki metni de talep edebilirsiniz.

> 💁 Bu yalnızca konuşma SDK'sında mevcuttur, REST API'de yerleşik çeviriler yoktur.

### Bilişsel Hizmetler Çevirmen Hizmeti

![Çevirmen hizmeti logosu](../../../../../translated_images/tr/azure-translator-logo.c6ed3a4a433edfd2.webp)

Çevirmen hizmeti, bir dilden bir veya daha fazla hedef dile metin çevirebilen özel bir çeviri hizmetidir. Çeviri yapmanın yanı sıra, küfürleri maskeleme gibi çok çeşitli ek özellikleri destekler. Ayrıca, belirli bir kelime veya cümle için belirli bir çeviri sağlamanıza, çevrilmesini istemediğiniz terimlerle çalışmanıza veya belirli bir iyi bilinen çeviriyi kullanmanıza olanak tanır.

Örneğin, tek kartlı bilgisayar olan "Raspberry Pi" ifadesini Fransızca gibi başka bir dile çevirirken, "Raspberry Pi" adını olduğu gibi bırakmak ve çevirmemek istersiniz. Bu durumda "J’ai un Raspberry Pi" yerine "J’ai une pi aux framboises" gibi bir çeviri elde edersiniz.

## Bir Çeviri Kaynağı Oluştur

Bu ders için bir Çevirmen kaynağına ihtiyacınız olacak. Metin çevirisi yapmak için REST API'yi kullanacaksınız.

### Görev - bir çeviri kaynağı oluştur

1. Terminalinizden veya komut isteminizden, `smart-timer` kaynak grubunuzda bir çeviri kaynağı oluşturmak için aşağıdaki komutu çalıştırın.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    `<location>` kısmını Kaynak Grubu oluştururken kullandığınız konumla değiştirin.

1. Çevirmen hizmeti için anahtarı alın:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Anahtarlardan birinin bir kopyasını alın.

## Uygulamalarda Çevirilerle Birden Fazla Dili Destekleme

İdeal bir dünyada, tüm uygulamanız mümkün olduğunca çok dili anlamalıdır; konuşmayı dinlemekten, dili anlamaya ve konuşma ile yanıt vermeye kadar. Bu oldukça fazla iş gerektirir, bu nedenle çeviri hizmetleri uygulamanızın teslim süresini hızlandırabilir.

![Japoncayı İngilizceye çeviren, İngilizce işleyen ve ardından Japoncaya çeviren bir akıllı zamanlayıcı mimarisi](../../../../../translated_images/tr/translated-smart-timer.08ac20057fdc5c37.webp)

Diyelim ki, baştan sona İngilizce kullanan bir akıllı zamanlayıcı oluşturuyorsunuz. İngilizce konuşmayı anlayıp metne dönüştürerek, dili İngilizce anlayarak, İngilizce yanıtlar oluşturup İngilizce konuşma ile yanıt vererek çalışıyor. Japonca desteği eklemek istiyorsanız, Japonca konuşmayı İngilizce metne çevirerek başlayabilir, ardından uygulamanın çekirdeğini aynı tutabilir ve yanıt metnini Japoncaya çevirerek yanıtı konuşabilirsiniz. Bu, Japonca desteğini hızlı bir şekilde eklemenizi sağlar ve daha sonra tam uçtan uca Japonca desteği sağlamaya genişleyebilirsiniz.

> 💁 Makine çevirisine güvenmenin dezavantajı, farklı dillerin ve kültürlerin aynı şeyleri ifade etmek için farklı yollarının olmasıdır. Bu nedenle çeviri, beklediğiniz ifadeyle eşleşmeyebilir.

Makine çevirileri, kullanıcı tarafından oluşturulan içeriği oluşturuldukça çevirebilen uygulamalar ve cihazlar için de olanaklar sunar. Bilim kurgu, düzenli olarak yabancı dilleri (genellikle Amerikan İngilizcesine) çevirebilen 'evrensel çevirmenler' cihazlarını içerir. Bu cihazlar, uzaylı kısmını görmezden gelirseniz, bilim kurgudan çok bilim gerçeğidir. Konuşma ve çeviri hizmetlerinin kombinasyonlarını kullanarak gerçek zamanlı konuşma ve yazılı metin çevirisi sağlayan uygulamalar ve cihazlar zaten mevcuttur.

Bir örnek, bu videoda gösterilen [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) mobil telefon uygulamasıdır:

[![Microsoft Translator canlı özelliği eylemde](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Videoyu izlemek için yukarıdaki görsele tıklayın

Özellikle seyahat ederken veya dilini bilmediğiniz insanlarla etkileşim kurarken böyle bir cihazın yanınızda olduğunu hayal edin. Havalimanlarında veya hastanelerde otomatik çeviri cihazlarının bulunması, çok ihtiyaç duyulan erişilebilirlik iyileştirmeleri sağlayacaktır.

✅ Araştırma yapın: Ticari olarak mevcut çeviri IoT cihazları var mı? Akıllı cihazlara entegre edilmiş çeviri yetenekleri hakkında ne düşünüyorsunuz?

> 👽 Gerçek anlamda uzaylılarla konuşmamızı sağlayan evrensel çevirmenler olmasa da, [Microsoft Translator Klingon dilini destekliyor](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Bir Yapay Zeka Hizmeti Kullanarak Metin Çevir

Bu çeviri yeteneğini akıllı zamanlayıcınıza eklemek için bir yapay zeka hizmeti kullanabilirsiniz.

### Görev - bir yapay zeka hizmeti kullanarak metin çevir

IoT cihazınızda metin çevirisi yapmak için ilgili rehberi takip edin:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-translate-speech.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-translate-speech.md)

---

## 🚀 Zorluk

Makine çevirileri, akıllı cihazların ötesinde diğer IoT uygulamalarına nasıl fayda sağlayabilir? Çevirilerin yalnızca konuşulan kelimelerle değil, metinle de nasıl yardımcı olabileceğini düşünün.

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Gözden Geçirme ve Kendi Kendine Çalışma

* Makine çevirisi hakkında daha fazla bilgi için [Wikipedia'daki makine çevirisi sayfasını](https://wikipedia.org/wiki/Machine_translation) okuyun.
* Sinirsel makine çevirisi hakkında daha fazla bilgi için [Wikipedia'daki sinirsel makine çevirisi sayfasını](https://wikipedia.org/wiki/Neural_machine_translation) okuyun.
* Microsoft konuşma hizmetleri için desteklenen dillerin listesini [Microsoft Docs'taki konuşma hizmeti dil ve ses desteği belgelerinde](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn) inceleyin.

## Ödev

[Evrensel bir çevirmen oluşturun](assignment.md)

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlama veya yanlış yorumlamalardan sorumlu değiliz.