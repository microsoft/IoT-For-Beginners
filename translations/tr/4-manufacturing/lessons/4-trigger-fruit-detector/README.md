<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-28T02:39:35+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "tr"
}
-->
# Sensörden Meyve Kalitesi Tespiti Tetikleme

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.tr.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Giriş

Bir IoT uygulaması, yalnızca tek bir cihazın veri toplayıp buluta göndermesinden ibaret değildir. Çoğu zaman, sensörler aracılığıyla fiziksel dünyadan veri toplayan, bu verilere dayanarak kararlar alan ve aktüatörler veya görselleştirmeler aracılığıyla fiziksel dünyayla etkileşimde bulunan birden fazla cihazın birlikte çalıştığı bir sistemdir.

Bu derste, birden fazla sensör ve bulut hizmetini entegre ederek karmaşık IoT uygulamalarını nasıl tasarlayacağınızı, verileri analiz edip depolayacağınızı ve bir aktüatör aracılığıyla yanıt göstereceğinizi öğreneceksiniz. Ayrıca, bir meyve kalite kontrol sistemi prototipini nasıl tasarlayacağınızı, IoT uygulamasını tetiklemek için yakınlık sensörlerini nasıl kullanacağınızı ve bu prototipin mimarisinin nasıl olacağını öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Karmaşık IoT uygulamaları tasarlama](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Bir meyve kalite kontrol sistemi tasarlama](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Sensörden meyve kalitesi kontrolü tetikleme](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Meyve kalite dedektörü için kullanılan veriler](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Birden fazla IoT cihazını simüle etmek için geliştirici cihazları kullanma](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Üretime geçiş](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Bu proje kapsamındaki son derstir, bu nedenle bu dersi ve ödevi tamamladıktan sonra bulut hizmetlerinizi temizlemeyi unutmayın. Ödevi tamamlamak için bu hizmetlere ihtiyacınız olacak, bu yüzden önce ödevi tamamladığınızdan emin olun.
>
> Gerekirse [projenizi temizleme rehberine](../../../clean-up.md) başvurabilirsiniz.

## Karmaşık IoT Uygulamaları Tasarlama

IoT uygulamaları birçok bileşenden oluşur. Bu bileşenler, çeşitli cihazlar ve internet hizmetlerini içerir.

IoT uygulamaları, *nesnelerin* (cihazların) veri gönderdiği, bu verilerin *içgörüler* oluşturduğu ve bu *içgörülerin* bir iş veya süreci iyileştirmek için *eylemler* oluşturduğu sistemler olarak tanımlanabilir. Örneğin, bir motor (nesne) sıcaklık verisi gönderir. Bu veri, motorun beklendiği gibi çalışıp çalışmadığını değerlendirmek için kullanılır (içgörü). Bu içgörü, motorun bakım programını önceliklendirmek için kullanılır (eylem).

* Farklı nesneler farklı veri parçalarını toplar.
* IoT hizmetleri, bu veriler üzerinde içgörüler sağlar ve bazen ek kaynaklardan gelen verilerle bu içgörüleri zenginleştirir.
* Bu içgörüler, cihazlardaki aktüatörleri kontrol etmek veya verileri görselleştirerek insanların karar vermesini sağlamak gibi eylemleri yönlendirir.

### Referans IoT Mimarisi

![Bir referans IoT mimarisi](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.tr.png)

Yukarıdaki diyagram, bir referans IoT mimarisini göstermektedir.

> 🎓 *Referans mimari*, yeni sistemler tasarlarken kullanabileceğiniz bir örnek mimaridir. Bu durumda, yeni bir IoT sistemi oluşturuyorsanız, referans mimariyi takip edebilir ve uygun yerlerde kendi cihazlarınızı ve hizmetlerinizi yerine koyabilirsiniz.

* **Nesneler**, sensörlerden veri toplayan cihazlardır ve bu verileri yorumlamak için kenar hizmetleriyle etkileşime girebilirler, örneğin görüntü verilerini yorumlamak için görüntü sınıflandırıcılar. Cihazlardan gelen veriler bir IoT hizmetine gönderilir.
* **İçgörüler**, sunucusuz uygulamalardan veya depolanan veriler üzerinde yapılan analizlerden gelir.
* **Eylemler**, cihazlara gönderilen komutlar veya insanların karar vermesini sağlayan veri görselleştirmeleri olabilir.

![Azure'da bir referans IoT mimarisi](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.tr.png)

Yukarıdaki diyagram, bu derslerde ele alınan bazı bileşenleri ve hizmetleri ve bunların bir referans IoT mimarisinde nasıl bir araya geldiğini göstermektedir.

* **Nesneler** - Sensörlerden veri toplamak için cihaz kodu yazdınız ve hem bulutta hem de bir kenar cihazında çalışan Custom Vision kullanarak görüntüleri analiz ettiniz. Bu veriler IoT Hub'a gönderildi.
* **İçgörüler** - IoT Hub'a gönderilen mesajlara yanıt vermek için Azure Functions kullandınız ve verileri daha sonra analiz etmek için Azure Storage'da depoladınız.
* **Eylemler** - Bulutta alınan kararlara ve cihazlara gönderilen komutlara dayalı olarak aktüatörleri kontrol ettiniz ve Azure Maps kullanarak verileri görselleştirdiniz.

✅ Daha önce kullandığınız diğer IoT cihazlarını düşünün, örneğin akıllı ev cihazları. Bu cihaz ve yazılımında yer alan nesneler, içgörüler ve eylemler nelerdir?

Bu model, ihtiyacınıza göre daha büyük veya daha küçük ölçeklerde uygulanabilir, daha fazla cihaz ve hizmet eklenebilir.

### Veri ve Güvenlik

Sisteminizi tasarlarken, sürekli olarak veri ve güvenliği göz önünde bulundurmanız gerekir.

* Cihazınız hangi verileri gönderiyor ve alıyor?
* Bu veriler nasıl güvence altına alınmalı ve korunmalı?
* Cihaza ve bulut hizmetine erişim nasıl kontrol edilmeli?

✅ Sahip olduğunuz IoT cihazlarının veri güvenliğini düşünün. Bu verilerin ne kadarı kişisel ve hem aktarım sırasında hem de depolandığında gizli tutulmalı? Hangi veriler depolanmamalı?

## Bir Meyve Kalite Kontrol Sistemi Tasarlama

Şimdi, nesneler, içgörüler ve eylemler fikrini alıp, bunu meyve kalite dedektörümüze uygulayarak uçtan uca bir uygulama tasarlayalım.

Bir işleme tesisinde kullanılmak üzere bir meyve kalite dedektörü oluşturma görevi verildiğinizi hayal edin. Meyveler, şu anda çalışanların elle kontrol edip olgunlaşmamış meyveleri ayırdığı bir konveyör bant sistemi üzerinde taşınıyor. Maliyetleri azaltmak için tesis sahibi otomatik bir sistem istiyor.

✅ IoT'nin (ve genel olarak teknolojinin) yükselişiyle birlikte manuel işlerin makinelerle değiştirildiği bir trend var. Araştırma yapın: IoT nedeniyle kaç işin kaybedileceği tahmin ediliyor? IoT cihazları oluşturmak için kaç yeni iş yaratılacak?

Bir sistem oluşturmanız gerekiyor: Meyve konveyör bandına geldiğinde algılanacak, fotoğraflanacak ve kenarda çalışan bir yapay zeka modeliyle kontrol edilecek. Sonuçlar buluta gönderilecek ve eğer meyve olgunlaşmamışsa bir bildirim verilerek olgunlaşmamış meyvenin çıkarılması sağlanacak.

|   |   |
| - | - |
| **Nesneler** | Konveyör bandına gelen meyveyi algılayan dedektör<br>Meyveyi fotoğraflayıp sınıflandıran kamera<br>Sınıflandırıcıyı çalıştıran kenar cihaz<br>Olgunlaşmamış meyveyi bildiren cihaz |
| **İçgörüler** | Meyvenin olgunluğunu kontrol etme kararı<br>Olgunluk sınıflandırmasının sonuçlarını depolama<br>Olgunlaşmamış meyve için uyarı gerekip gerekmediğini belirleme |
| **Eylemler** | Meyveyi fotoğraflayıp bir görüntü sınıflandırıcıyla kontrol etmek için bir cihaza komut gönderme<br>Olgunlaşmamış meyve olduğunu bildirmek için bir cihaza komut gönderme |

### Uygulamanızı Prototipleme

![Meyve kalite kontrolü için bir referans IoT mimarisi](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.tr.png)

Yukarıdaki diyagram, bu prototip uygulama için bir referans mimariyi göstermektedir.

* Bir IoT cihazı, bir yakınlık sensörü ile meyvenin gelişini algılar. Bu, buluta bir mesaj göndererek meyvenin algılandığını bildirir.
* Buluttaki bir sunucusuz uygulama, başka bir cihaza fotoğraf çekmesi ve görüntüyü sınıflandırması için bir komut gönderir.
* Kameralı bir IoT cihazı, bir fotoğraf çeker ve bunu kenarda çalışan bir görüntü sınıflandırıcıya gönderir. Sonuçlar daha sonra buluta gönderilir.
* Buluttaki bir sunucusuz uygulama, bu bilgiyi daha sonra analiz edilmek üzere depolar ve meyve olgunlaşmamışsa, bir IoT cihazına bir LED aracılığıyla fabrika çalışanlarını uyarması için bir komut gönderir.

> 💁 Bu IoT uygulamasının tamamı, tüm mantığın görüntü sınıflandırmasını başlatmak ve LED'i kontrol etmek için yerleşik olduğu tek bir cihaz olarak uygulanabilir. IoT Hub, yalnızca tespit edilen olgunlaşmamış meyve sayısını izlemek ve cihazı yapılandırmak için kullanılabilir. Bu derste, büyük ölçekli IoT uygulamaları için kavramları göstermek amacıyla genişletilmiştir.

Prototip için, tüm bunları tek bir cihazda uygulayacaksınız. Bir mikrodenetleyici kullanıyorsanız, görüntü sınıflandırıcıyı çalıştırmak için ayrı bir kenar cihazı kullanacaksınız. Bunun için gerekenlerin çoğunu zaten öğrendiniz.

## Sensörden Meyve Kalitesi Kontrolü Tetikleme

IoT cihazının, meyvenin sınıflandırılmaya hazır olduğunu belirten bir tür tetikleyiciye ihtiyacı vardır. Bunun bir yolu, bir sensörle mesafeyi ölçerek meyvenin konveyör bandında doğru konumda olup olmadığını belirlemektir.

![Yakınlık sensörleri, muz gibi nesnelere lazer ışınları gönderir ve ışının geri yansıma süresini ölçer](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fe.tr.png)

Yakınlık sensörleri, sensör ile bir nesne arasındaki mesafeyi ölçmek için kullanılabilir. Genellikle bir lazer ışını veya kızılötesi ışık gibi bir elektromanyetik radyasyon ışını gönderir ve ardından bir nesneden yansıyan radyasyonu algılarlar. Lazer ışınının gönderilmesi ile sinyalin geri yansıması arasındaki süre, sensöre olan mesafeyi hesaplamak için kullanılabilir.

> 💁 Yakınlık sensörlerini farkında olmadan kullanmış olabilirsiniz. Çoğu akıllı telefon, bir arama sırasında ekranı kulağınıza tuttuğunuzda ekranı kapatır ve bu, bir yakınlık sensörü kullanılarak yapılır. Sensör, bir arama sırasında ekrana yakın bir nesne algılar ve telefon belirli bir mesafeye ulaşana kadar dokunmatik özellikleri devre dışı bırakır.

### Görev - Bir Mesafe Sensörü ile Meyve Kalitesi Tespitini Tetikleme

IoT cihazınızı kullanarak bir nesneyi algılamak için bir yakınlık sensörü kullanma rehberini inceleyin:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-proximity.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-proximity.md)

## Meyve Kalite Dedektörü için Kullanılan Veriler

Prototip meyve dedektörü, birbiriyle iletişim kuran birden fazla bileşene sahiptir.

![Birbiriyle iletişim kuran bileşenler](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.tr.png)

* Bir meyveye olan mesafeyi ölçen ve bunu IoT Hub'a gönderen bir yakınlık sensörü
* Kamerayı kontrol etmek için IoT Hub'dan kamera cihazına gelen komut
* Görüntü sınıflandırma sonuçlarının IoT Hub'a gönderilmesi
* Meyvenin olgunlaşmamış olduğunu bildirmek için IoT Hub'dan LED'li cihaza gönderilen komut

Bu mesajların yapısını, uygulamayı oluşturmadan önce tanımlamak iyi bir fikirdir.

> 💁 Deneyimli hemen hemen her geliştirici, kariyerinde bir noktada, gönderilen veriler ile beklenen veriler arasındaki farklılıkların neden olduğu hataları günlerce veya haftalarca takip etmek zorunda kalmıştır.

Örneğin - sıcaklık bilgisi gönderiyorsanız, JSON'u nasıl tanımlarsınız? `temperature` adlı bir alanınız olabilir veya yaygın bir kısaltma olan `temp` kullanabilirsiniz.

```json
{
    "temperature": 20.7
}
```

ile karşılaştırıldığında:

```json
{
    "temp": 20.7
}
```

Ayrıca birimleri de göz önünde bulundurmanız gerekir - sıcaklık °C mi yoksa °F cinsinden mi? Bir tüketici cihazı kullanarak sıcaklığı ölçüyorsanız ve kullanıcı ekran birimlerini değiştirirse, buluta gönderilen birimlerin tutarlı kalmasını sağlamanız gerekir.

✅ Araştırma yapın: Birim sorunları, 125 milyon dolarlık Mars Climate Orbiter'ın çarpmasına nasıl neden oldu?

Meyve kalite dedektörü için gönderilen verileri düşünün. Her mesajı nasıl tanımlarsınız? Verileri nerede analiz eder ve hangi verilerin gönderileceğine karar verirsiniz?

Örneğin - yakınlık sensörü kullanarak görüntü sınıflandırmayı tetikleme. IoT cihazı mesafeyi ölçer, ancak karar nerede alınır? Cihaz, meyvenin yeterince yakın olduğuna karar verip IoT Hub'a sınıflandırmayı tetiklemesini söyleyen bir mesaj mı gönderir? Yoksa yakınlık ölçümlerini gönderip IoT Hub'ın karar vermesini mi sağlar?

Bu tür soruların cevabı - duruma bağlıdır. Her kullanım durumu farklıdır, bu yüzden bir IoT geliştiricisi olarak, oluşturduğunuz sistemi, nasıl kullanıldığını ve algılanan verileri anlamanız gerekir.

* Karar IoT Hub tarafından alınırsa, birden fazla mesafe ölçümü göndermeniz gerekir.
* Çok fazla mesaj gönderirseniz, IoT Hub'ın maliyetini ve IoT cihazlarınızın (özellikle milyonlarca cihazın bulunduğu bir fabrikada) ihtiyaç duyduğu bant genişliğini artırır. Ayrıca cihazınızı yavaşlatabilir.
* Kararı cihazda alırsanız, cihazı ince ayar yapmak için bir yapılandırma yöntemi sağlamanız gerekir.

## Birden Fazla IoT Cihazını Simüle Etmek için Geliştirici Cihazları Kullanma

Prototipinizi oluşturmak için, IoT geliştirme kitinizin birden fazla cihaz gibi davranmasını, telemetri göndermesini ve komutlara yanıt vermesini sağlamanız gerekecek.

### Raspberry Pi veya Sanal IoT Donanımında Birden Fazla IoT Cihazını Simüle Etme

Bir Raspberry Pi gibi tek kartlı bir bilgisayar kullanırken, aynı anda birden fazla uygulama çalıştırabilirsiniz. Bu, her 'IoT cihazı' için bir uygulama oluşturarak birden fazla IoT cihazını simüle edebileceğiniz anlamına gelir. Örneğin, her cihazı ayrı bir Python dosyası olarak uygulayabilir ve bunları farklı terminal oturumlarında çalıştırabilirsiniz.
> 💁 Bazı donanımlar, aynı anda çalışan birden fazla uygulama tarafından erişildiğinde çalışmayabilir.
### Mikrodenetleyicide birden fazla cihazı simüle etme

Mikrodenetleyicilerde birden fazla cihazı simüle etmek daha karmaşıktır. Tek kartlı bilgisayarların aksine, aynı anda birden fazla uygulama çalıştıramazsınız; tüm ayrı IoT cihazlarının mantığını tek bir uygulamaya dahil etmeniz gerekir.

Bu süreci kolaylaştırmak için bazı öneriler:

* IoT cihazı başına bir veya daha fazla sınıf oluşturun - örneğin, `DistanceSensor`, `ClassifierCamera`, `LEDController` adında sınıflar. Her birinin, ana `setup` ve `loop` fonksiyonları tarafından çağrılan kendi `setup` ve `loop` yöntemleri olabilir.
* Komutları tek bir yerde yönetin ve gerektiğinde ilgili cihaz sınıfına yönlendirin.
* Ana `loop` fonksiyonunda, her bir cihaz için zamanlamayı dikkate almanız gerekecek. Örneğin, bir cihaz sınıfının her 10 saniyede bir işlem yapması gerekiyorsa ve başka bir cihazın her 1 saniyede bir işlem yapması gerekiyorsa, ana `loop` fonksiyonunda 1 saniyelik bir gecikme kullanın. Her `loop` çağrısı, her saniyede işlem yapması gereken cihaz için ilgili kodu tetikler ve bir sayaç kullanarak her döngüyü sayar, sayaç 10'a ulaştığında diğer cihazı işler (ardından sayacı sıfırlar).

## Üretime geçiş

Prototip, nihai üretim sisteminin temelini oluşturacaktır. Üretime geçtiğinizde bazı farklılıklar şunlar olabilir:

* Dayanıklı bileşenler - fabrikadaki gürültü, ısı, titreşim ve strese dayanacak şekilde tasarlanmış donanımların kullanılması.
* Dahili iletişimlerin kullanılması - bazı bileşenler, buluta veri göndermek yerine doğrudan iletişim kurar. Bu, fabrikanın kurulumuna bağlı olarak ya doğrudan iletişimle ya da bir ağ geçidi cihazı kullanarak IoT hizmetinin bir kısmını uçta çalıştırarak yapılır.
* Yapılandırma seçenekleri - her fabrika ve kullanım durumu farklıdır, bu nedenle donanım yapılandırılabilir olmalıdır. Örneğin, yakınlık sensörü farklı mesafelerde farklı meyveleri algılamalı olabilir. Sınıflandırmayı tetiklemek için mesafeyi sabit kodlamak yerine, bunun bulut üzerinden yapılandırılabilir olmasını istersiniz; örneğin bir cihaz ikizi kullanarak.
* Otomatik meyve çıkarma - olgunlaşmamış meyveyi belirtmek için bir LED yerine, otomatik cihazlar meyveyi çıkarır.

✅ Araştırma yapın: Üretim cihazları, geliştirici kitlerinden başka hangi yönlerden farklıdır?

---

## 🚀 Zorluk

Bu derste, bir IoT sistemini nasıl tasarlayacağınızla ilgili bilmeniz gereken bazı kavramları öğrendiniz. Önceki projeleri düşünün. Bu projeler yukarıda gösterilen referans mimariye nasıl uyuyor?

Şimdiye kadar yapılan projelerden birini seçin ve projelerde ele alınanların ötesinde birden fazla yeteneği bir araya getiren daha karmaşık bir çözüm tasarımını düşünün. Mimarinin bir çizimini yapın ve ihtiyaç duyacağınız tüm cihazları ve hizmetleri düşünün.

Örneğin - GPS ile birleştirilmiş bir araç takip cihazı, soğutmalı bir kamyondaki sıcaklıkları, motorun açılıp kapanma sürelerini ve sürücünün kimliğini izlemek için sensörler içerir. Hangi cihazlar, hangi hizmetler, hangi veriler iletiliyor ve güvenlik ile gizlilikle ilgili hangi hususlar dikkate alınıyor?

## Ders sonrası sınav

[Ders sonrası sınav](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Gözden Geçirme ve Kendi Kendine Çalışma

* IoT mimarisi hakkında daha fazla bilgi edinmek için [Microsoft dokümanlarındaki Azure IoT referans mimarisi dokümantasyonunu](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn) okuyun.
* IoT Hub dokümantasyonundaki [cihaz ikizlerini anlama ve kullanma](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn) hakkında daha fazla bilgi edinin.
* Endüstriyel otomasyonda kullanılan bir makineden makineye iletişim protokolü olan OPC-UA hakkında [Wikipedia'daki OPC-UA sayfasını](https://wikipedia.org/wiki/OPC_Unified_Architecture) okuyun.

## Ödev

[Meyve kalitesi dedektörü oluşturun](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.