# IoT'ye Giriş

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/tr/lesson-1.2606670fa61ee904.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

Bu ders, [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) tarafından sunulan [Hello IoT serisi](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) kapsamında öğretilmiştir. Ders, 1 saatlik bir ders ve ardından dersin bazı bölümlerine daha derinlemesine dalan ve soruları yanıtlayan 1 saatlik bir ofis saati olmak üzere iki video olarak sunulmuştur.

[![Ders 1: IoT'ye Giriş](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Ders 1: IoT'ye Giriş - Ofis Saatleri](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Videoları izlemek için yukarıdaki görsellere tıklayın

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Giriş

Bu ders, Nesnelerin İnterneti (IoT) ile ilgili bazı giriş konularını ele alır ve donanımınızı kurmaya başlamanızı sağlar.

Bu derste şunları ele alacağız:

* [Nesnelerin İnterneti nedir?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT cihazları](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Cihazınızı kurun](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT'nin uygulamaları](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Çevrenizde bulunabilecek IoT cihazlarına örnekler](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Nesnelerin İnterneti nedir?

'Nesnelerin İnterneti' terimi, 1999 yılında [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) tarafından, sensörler aracılığıyla fiziksel dünyayı internete bağlamayı ifade etmek için ortaya atılmıştır. O zamandan beri, bu terim, sensörlerden veri toplayarak veya aktüatörler (örneğin bir anahtarı açmak veya bir LED'i yakmak gibi bir şey yapan cihazlar) aracılığıyla gerçek dünya etkileşimleri sağlayarak çevresindeki fiziksel dünya ile etkileşime giren herhangi bir cihazı tanımlamak için kullanılmıştır.

> **Sensörler**, hız, sıcaklık veya konum gibi dünyadan bilgi toplar.
>
> **Aktüatörler**, elektrik sinyallerini bir anahtarı tetiklemek, ışıkları açmak, ses çıkarmak veya diğer donanımlara kontrol sinyalleri göndermek gibi gerçek dünya etkileşimlerine dönüştürür.

IoT, yalnızca cihazlardan daha fazlasını içeren bir teknoloji alanıdır - sensör verilerini işleyebilen veya IoT cihazlarına bağlı aktüatörlere istek gönderebilen bulut tabanlı hizmetleri de içerir. Ayrıca, genellikle kenar cihazları olarak adlandırılan, internet bağlantısına sahip olmayan veya buna ihtiyaç duymayan cihazları da içerir. Bu cihazlar, genellikle bulutta eğitilmiş yapay zeka modellerini kullanarak sensör verilerini kendileri işleyebilir ve yanıt verebilir.

IoT, hızla büyüyen bir teknoloji alanıdır. 2020 yılı sonuna kadar 30 milyar IoT cihazının internete bağlı olduğu tahmin edilmektedir. Geleceğe baktığımızda, 2025 yılına kadar IoT cihazlarının neredeyse 80 zettabayt (80 trilyon gigabayt) veri toplayacağı tahmin edilmektedir. Bu, çok büyük bir veri miktarıdır!

![2015'te 5 milyarın altında başlayıp 2025'te 30 milyarın üzerine çıkan bir eğilimle zaman içinde aktif IoT cihazlarını gösteren bir grafik](../../../../../images/connected-iot-devices.svg)

✅ Biraz araştırma yapın: IoT cihazları tarafından üretilen verilerin ne kadarı gerçekten kullanılıyor ve ne kadarı boşa gidiyor? Neden bu kadar çok veri göz ardı ediliyor?

Bu veri, IoT'nin başarısının anahtarıdır. Başarılı bir IoT geliştiricisi olmak için, toplamanız gereken verileri, bu verileri nasıl toplayacağınızı, bu verilere dayanarak nasıl kararlar alacağınızı ve gerekirse bu kararları fiziksel dünyayla nasıl etkileşimde bulunmak için kullanacağınızı anlamanız gerekir.

## IoT cihazları

IoT'deki **T**, çevresindeki fiziksel dünya ile sensörlerden veri toplayarak veya aktüatörler aracılığıyla gerçek dünya etkileşimleri sağlayarak etkileşimde bulunan cihazlar anlamına gelen **Things** (Şeyler) anlamına gelir.

Üretim veya ticari kullanım için tasarlanan cihazlar, örneğin tüketici fitness takipçileri veya endüstriyel makine kontrolörleri, genellikle özel olarak üretilir. Bu cihazlar, belirli bir görevin gereksinimlerini karşılamak için özel devre kartları, hatta belki de özel işlemciler kullanır; örneğin, bir bileğe sığacak kadar küçük veya yüksek sıcaklık, yüksek stres veya yüksek titreşimli bir fabrika ortamında çalışacak kadar dayanıklı olmak gibi.

IoT hakkında öğrenim gören veya bir cihaz prototipi oluşturan bir geliştirici olarak, bir geliştirici kitiyle başlamanız gerekecektir. Bunlar, geliştiricilerin kullanması için tasarlanmış, genellikle üretim cihazlarında bulunmayan özelliklere sahip genel amaçlı IoT cihazlarıdır; örneğin, sensörleri veya aktüatörleri bağlamak için bir dizi harici pin, hata ayıklamayı destekleyen donanım veya büyük bir üretim serisinde gereksiz maliyet ekleyecek ek kaynaklar.

Bu geliştirici kitleri genellikle iki kategoriye ayrılır - mikrodenetleyiciler ve tek kartlı bilgisayarlar. Bunlar burada tanıtılacak ve bir sonraki derste daha ayrıntılı olarak ele alınacaktır.

> 💁 Telefonunuz da sensörler ve aktüatörler ile donatılmış, farklı uygulamaların sensörleri ve aktüatörleri farklı şekillerde ve farklı bulut hizmetleriyle kullandığı genel amaçlı bir IoT cihazı olarak düşünülebilir. Hatta bir telefon uygulamasını IoT cihazı olarak kullanan bazı IoT eğitimleri bile bulabilirsiniz.

### Mikrodenetleyiciler

Bir mikrodenetleyici (kısaca MCU olarak da adlandırılır, mikrodenetleyici biriminin kısaltması), aşağıdakilerden oluşan küçük bir bilgisayardır:

🧠 Bir veya daha fazla merkezi işlem birimi (CPU) - mikrodenetleyicinin programınızı çalıştıran 'beyni'

💾 Bellek (RAM ve program belleği) - programınızın, verilerinizin ve değişkenlerinizin saklandığı yer

🔌 Programlanabilir giriş/çıkış (I/O) bağlantıları - sensörler ve aktüatörler gibi harici çevre birimleriyle iletişim kurmak için

Mikrodenetleyiciler genellikle düşük maliyetli bilgi işlem cihazlarıdır ve özel donanımlarda kullanılanların ortalama fiyatları yaklaşık 0,50 ABD dolarına kadar düşmektedir ve bazı cihazlar 0,03 ABD doları kadar ucuzdur. Geliştirici kitleri 4 ABD dolarından başlayabilir ve daha fazla özellik ekledikçe maliyet artar. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), sensörler, aktüatörler, WiFi ve bir ekrana sahip bir mikrodenetleyici geliştirici kiti, yaklaşık 30 ABD dolarıdır.

![Bir Wio Terminal](../../../../../translated_images/tr/wio-terminal.b8299ee16587db9a.webp)

> 💁 İnternette mikrodenetleyiciler ararken, **MCU** terimini aramaya dikkat edin, çünkü bu, mikrodenetleyiciler yerine Marvel Sinematik Evreni ile ilgili birçok sonuç getirebilir.

Mikrodenetleyiciler, PC'ler veya Mac'ler gibi genel amaçlı bilgisayarlar yerine, çok sınırlı sayıda çok özel görevi yerine getirmek üzere programlanmak üzere tasarlanmıştır. Çok özel senaryolar dışında, bir monitör, klavye ve fare bağlayıp bunları genel amaçlı görevler için kullanamazsınız.

Mikrodenetleyici geliştirici kitleri genellikle yerleşik sensörler ve aktüatörlerle birlikte gelir. Çoğu kartta programlayabileceğiniz bir veya daha fazla LED bulunur ve diğer cihazlar, çeşitli üreticilerin ekosistemlerini kullanarak daha fazla sensör veya aktüatör eklemek için standart fişler veya yerleşik sensörler (genellikle sıcaklık sensörleri gibi en popüler olanlar) içerir. Bazı mikrodenetleyiciler, Bluetooth veya WiFi gibi yerleşik kablosuz bağlantıya sahiptir veya bu bağlantıyı eklemek için kart üzerinde ek mikrodenetleyicilere sahiptir.

> 💁 Mikrodenetleyiciler genellikle C/C++ ile programlanır.

### Tek Kartlı Bilgisayarlar

Tek kartlı bir bilgisayar, tüm bir bilgisayarın unsurlarını tek bir küçük kart üzerinde barındıran küçük bir bilgi işlem cihazıdır. Bunlar, bir masaüstü veya dizüstü bilgisayarın özelliklerine yakın, tam bir işletim sistemi çalıştıran, ancak daha küçük, daha az güç kullanan ve önemli ölçüde daha ucuz olan cihazlardır.

![Bir Raspberry Pi 4](../../../../../translated_images/tr/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi, en popüler tek kartlı bilgisayarlardan biridir.

Bir mikrodenetleyici gibi, tek kartlı bilgisayarlar bir CPU, bellek ve giriş/çıkış pinlerine sahiptir, ancak monitör bağlamanıza olanak tanıyan bir grafik çipi, ses çıkışları ve klavyeler, fareler ve diğer standart USB cihazları gibi cihazları bağlamak için USB bağlantı noktaları gibi ek özelliklere sahiptir. Programlar, kartın içine yerleştirilmiş bir bellek çipi yerine, bir işletim sistemiyle birlikte SD kartlara veya sabit disklere kaydedilir.

> 🎓 Tek kartlı bir bilgisayarı, üzerinde okuduğunuz PC veya Mac'in daha küçük, daha ucuz bir versiyonu olarak düşünebilirsiniz, sensörler ve aktüatörlerle etkileşim kurmak için GPIO (genel amaçlı giriş/çıkış) pinleri eklenmiştir.

Tek kartlı bilgisayarlar tam özellikli bilgisayarlardır, bu nedenle herhangi bir dilde programlanabilirler. IoT cihazları genellikle Python ile programlanır.

### Kalan Dersler İçin Donanım Seçenekleri

Sonraki tüm dersler, fiziksel dünya ile etkileşim kuran ve bulutla iletişim kuran bir IoT cihazı kullanarak ödevler içerir. Her ders, 3 cihaz seçeneğini destekler - Arduino (Seeed Studios Wio Terminal kullanarak) veya bir tek kartlı bilgisayar, fiziksel bir cihaz (Raspberry Pi 4) veya PC veya Mac'inizde çalışan sanal bir tek kartlı bilgisayar.

Tüm ödevleri tamamlamak için gereken donanım hakkında [donanım kılavuzunda](../../../hardware.md) bilgi edinebilirsiniz.

> 💁 Ödevleri tamamlamak için herhangi bir IoT donanımı satın almanıza gerek yoktur, her şeyi sanal bir tek kartlı bilgisayar kullanarak yapabilirsiniz.

Hangi donanımı seçeceğiniz, evde veya okulda mevcut olanlara ve hangi programlama dilini bildiğinize veya öğrenmeyi planladığınıza bağlıdır. Her iki donanım varyantı da aynı sensör ekosistemini kullanacaktır, bu nedenle bir yoldan başlarsanız, kitin çoğunu değiştirmek zorunda kalmadan diğerine geçebilirsiniz. Sanal tek kartlı bilgisayar, bir Raspberry Pi üzerinde öğrenmeye eşdeğer olacak ve kodun çoğu, sonunda bir cihaz ve sensörler alırsanız Pi'ye aktarılabilir.

### Arduino Geliştirici Kiti

Mikrodenetleyici geliştirmeyi öğrenmekle ilgileniyorsanız, ödevleri bir Arduino cihazı kullanarak tamamlayabilirsiniz. Dersler yalnızca Arduino çerçevesi, kullanılan sensörler ve aktüatörler ve bulutla etkileşim kuran kütüphanelerle ilgili kodu öğreteceğinden, C/C++ programlama hakkında temel bir anlayışa sahip olmanız gerekecektir.

Ödevlerde [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) ve mikrodenetleyici geliştirme için [PlatformIO uzantısı](https://platformio.org) kullanılacaktır. Bu araçla deneyiminiz varsa Arduino IDE'yi de kullanabilirsiniz, ancak talimatlar sağlanmayacaktır.

### Tek Kartlı Bilgisayar Geliştirici Kiti

Tek kartlı bilgisayarları kullanarak IoT geliştirmeyi öğrenmekle ilgileniyorsanız, ödevleri bir Raspberry Pi veya PC ya da Mac'inizde çalışan bir sanal cihaz kullanarak tamamlayabilirsiniz.

Dersler yalnızca kullanılan sensörler ve aktüatörler ve bulutla etkileşim kuran kütüphanelerle ilgili kodu öğreteceğinden, Python programlama hakkında temel bir anlayışa sahip olmanız gerekecektir.

> 💁 Python'da kod yazmayı öğrenmek istiyorsanız, aşağıdaki iki video serisine göz atın:
>
> * [Yeni Başlayanlar İçin Python](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Yeni Başlayanlar İçin Daha Fazla Python](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Ödevlerde [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) kullanılacaktır.

Bir Raspberry Pi kullanıyorsanız, Pi'nizi Raspberry Pi OS'nin tam masaüstü sürümünü kullanarak çalıştırabilir ve tüm kodlamayı doğrudan Pi üzerinde [Raspberry Pi OS için VS Code sürümünü](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn) kullanarak yapabilirsiniz veya Pi'nizi başsız bir cihaz olarak çalıştırabilir ve PC veya Mac'inizden [Remote SSH uzantısını](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) kullanarak Pi'ye bağlanabilir ve doğrudan üzerinde kod yazıyormuş gibi düzenleme, hata ayıklama ve kod çalıştırabilirsiniz.

Sanal cihaz seçeneğini kullanırsanız, kodlamayı doğrudan bilgisayarınızda yaparsınız. Sensörlere ve aktüatörlere erişmek yerine, sensör değerlerini tanımlamanıza olanak tanıyan ve aktüatörlerin sonuçlarını ekranda gösteren bir araç kullanarak bu donanımı simüle edersiniz.

## Cihazınızı Kurun

IoT cihazınızı programlamaya başlamadan önce, küçük bir kurulum yapmanız gerekecek. Kullanacağınız cihaza bağlı olarak aşağıdaki ilgili talimatları izleyin.
💁 Henüz bir cihazınız yoksa, hangi cihazı kullanacağınıza ve satın almanız gereken ek donanımlara karar vermenize yardımcı olması için [donanım rehberine](../../../hardware.md) göz atabilirsiniz. Donanım satın almanıza gerek yok, çünkü tüm projeler sanal donanım üzerinde çalıştırılabilir.
Bu talimatlar, kullanacağınız donanım veya araçların üreticilerinden gelen üçüncü taraf web sitelerine bağlantılar içermektedir. Bu, çeşitli araçlar ve donanımlar için her zaman en güncel talimatları kullanmanızı sağlamak içindir.

Cihazınızı kurmak ve bir 'Hello World' projesini tamamlamak için ilgili kılavuzu takip edin. Bu, bu başlangıç bölümündeki 4 ders boyunca bir IoT gece lambası oluşturmanın ilk adımı olacaktır.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device.md)

✅ Hem Arduino hem de tek kartlı bilgisayarlar için VS Code kullanacaksınız. Daha önce bunu kullanmadıysanız, [VS Code sitesi](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) üzerinden daha fazla bilgi edinebilirsiniz.

## IoT'nin Uygulamaları

IoT, birkaç geniş grup içinde çok çeşitli kullanım alanlarını kapsar:

* Tüketici IoT
* Ticari IoT
* Endüstriyel IoT
* Altyapı IoT

✅ Küçük bir araştırma yapın: Aşağıda açıklanan alanların her biri için metinde verilmemiş somut bir örnek bulun.

### Tüketici IoT

Tüketici IoT, tüketicilerin evde satın alıp kullanacağı IoT cihazlarını ifade eder. Bu cihazlardan bazıları oldukça kullanışlıdır, örneğin akıllı hoparlörler, akıllı ısıtma sistemleri ve robotik süpürgeler. Diğerleri ise kullanışlılık açısından tartışmalıdır, örneğin sesle kontrol edilen musluklar, ki bu durumda akan suyun sesi nedeniyle ses kontrolü sizi duyamadığı için musluğu kapatamazsınız.

Tüketici IoT cihazları, özellikle 1 milyar engelli birey için çevrelerinde daha fazlasını başarmalarını sağlıyor. Robotik süpürgeler, hareket kabiliyeti sınırlı olan ve kendileri süpüremeyen kişilere temiz zeminler sağlayabilir, sesle kontrol edilen fırınlar, görme veya motor kontrolü sınırlı olan kişilerin yalnızca sesleriyle fırınlarını ısıtmalarına olanak tanır, sağlık monitörleri ise hastaların kronik durumlarını daha düzenli ve daha ayrıntılı güncellemelerle kendilerinin takip etmelerine olanak tanır. Bu cihazlar o kadar yaygın hale geliyor ki, küçük çocuklar bile bunları günlük yaşamlarının bir parçası olarak kullanıyor, örneğin COVID pandemisi sırasında sanal eğitim alan öğrenciler, okul çalışmalarını takip etmek için akıllı ev cihazlarında zamanlayıcılar ayarlıyor veya yaklaşan ders toplantılarını hatırlatmak için alarmlar kuruyor.

✅ Üzerinizde veya evinizde hangi tüketici IoT cihazları var?

### Ticari IoT

Ticari IoT, IoT'nin iş yerinde kullanımını kapsar. Bir ofis ortamında, aydınlatma ve ısıtmayı yalnızca gerektiğinde açık tutmak için işgal sensörleri ve hareket dedektörleri olabilir, bu da maliyetleri ve karbon emisyonlarını azaltır. Bir fabrikada, IoT cihazları işçilerin sert şapka takmaması veya tehlikeli seviyelere ulaşan gürültü gibi güvenlik tehlikelerini izleyebilir. Perakende sektöründe, IoT cihazları soğuk depoların sıcaklığını ölçebilir, bir buzdolabı veya dondurucu gereken sıcaklık aralığının dışındaysa mağaza sahibini uyarabilir veya raflardaki ürünleri izleyerek çalışanları satılan ürünleri yeniden doldurmaya yönlendirebilir. Ulaşım sektörü, araç konumlarını izlemek, yol kullanıcı ücretlendirmesi için yolda yapılan kilometreleri takip etmek, sürücü saatlerini ve mola uyumluluğunu izlemek veya bir araç bir depoya yaklaşırken personeli yükleme veya boşaltma için hazırlamak gibi konularda IoT'ye giderek daha fazla güveniyor.

✅ Okulunuzda veya iş yerinizde hangi ticari IoT cihazları var?

### Endüstriyel IoT (IIoT)

Endüstriyel IoT veya IIoT, IoT cihazlarının büyük ölçekli makineleri kontrol etmek ve yönetmek için kullanılmasını ifade eder. Bu, fabrikalardan dijital tarıma kadar çok çeşitli kullanım alanlarını kapsar.

Fabrikalar, IoT cihazlarını birçok farklı şekilde kullanır. Makineler, sıcaklık, titreşim ve dönüş hızı gibi şeyleri izlemek için birden fazla sensörle izlenebilir. Bu veriler, makinenin belirli toleransların dışına çıkması durumunda durdurulmasına olanak tanır - örneğin, çok ısınırsa kapatılır. Bu veriler ayrıca zaman içinde toplanabilir ve analiz edilebilir, böylece bir arıza öncesindeki verileri inceleyen ve bunu diğer arızaları önceden tahmin etmek için kullanan AI modelleri ile tahmine dayalı bakım yapılabilir.

Dijital tarım, özellikle [geçimlik tarım](https://wikipedia.org/wiki/Subsistence_agriculture) ile geçinen 500 milyon hanedeki 2 milyar insan için, gezegeni büyüyen nüfusu beslemek için önemlidir. Dijital tarım, birkaç dolarlık sensörlerden büyük ticari kurulumlara kadar değişebilir. Bir çiftçi, sıcaklıkları izleyerek ve [büyüme derecesi günlerini](https://wikipedia.org/wiki/Growing_degree-day) kullanarak bir ürünün ne zaman hasat edileceğini tahmin etmeye başlayabilir. Toprak nemi izlemeyi otomatik sulama sistemlerine bağlayarak bitkilerine ihtiyaç duydukları kadar su verebilir, ancak daha fazlasını vermeyerek ürünlerinin kurumasını önlerken su israfını da önleyebilir. Çiftçiler, dronlar, uydu verileri ve AI kullanarak büyük tarım alanlarında ürün büyümesini, hastalıkları ve toprak kalitesini izleyerek bunu daha da ileriye taşıyor.

✅ Çiftçilere hangi diğer IoT cihazları yardımcı olabilir?

### Altyapı IoT

Altyapı IoT, insanların her gün kullandığı yerel ve küresel altyapıyı izlemek ve kontrol etmekle ilgilidir.

[Akıllı Şehirler](https://wikipedia.org/wiki/Smart_city), şehir hakkında veri toplamak ve bu verileri şehrin nasıl çalıştığını iyileştirmek için kullanan IoT cihazlarını kullanan kentsel alanlardır. Bu şehirler genellikle yerel hükümetler, akademi ve yerel işletmeler arasındaki işbirlikleriyle yönetilir ve ulaşım, park ve kirlilik gibi çeşitli şeyleri izler ve yönetir. Örneğin, Danimarka'nın Kopenhag şehrinde hava kirliliği yerel halk için önemlidir, bu nedenle ölçülür ve veriler en temiz bisiklet ve koşu yolları hakkında bilgi sağlamak için kullanılır.

[Akıllı enerji şebekeleri](https://wikipedia.org/wiki/Smart_grid), bireysel evler düzeyinde kullanım verileri toplayarak enerji talebi hakkında daha iyi analizler sağlar. Bu veriler, ülke düzeyinde yeni enerji santrallerinin nerede inşa edileceği gibi kararları yönlendirebilir ve bireysel düzeyde kullanıcıların ne kadar enerji kullandıkları, ne zaman kullandıkları ve hatta maliyetleri nasıl azaltacakları konusunda öneriler sunabilir, örneğin elektrikli arabaları gece şarj etmek gibi.

✅ Yaşadığınız yerde bir şeyleri ölçmek için IoT cihazları ekleyebilseydiniz, neyi ölçerdiniz?

## Çevrenizde Bulunan IoT Cihazlarına Örnekler

Çevrenizde ne kadar çok IoT cihazı olduğunu öğrenince şaşırabilirsiniz. Bu yazıyı evden yazıyorum ve aşağıdaki cihazlar internet bağlantılı ve uygulama kontrolü, ses kontrolü veya telefonum aracılığıyla bana veri gönderme gibi akıllı özelliklere sahip:

* Birden fazla akıllı hoparlör
* Buzdolabı, bulaşık makinesi, fırın ve mikrodalga
* Güneş panelleri için elektrik monitörü
* Akıllı prizler
* Video kapı zili ve güvenlik kameraları
* Birden fazla akıllı oda sensörüne sahip akıllı termostat
* Garaj kapısı açıcı
* Ev eğlence sistemleri ve sesle kontrol edilen televizyonlar
* Işıklar
* Fitness ve sağlık takip cihazları

Bu tür cihazların hepsi sensörlere ve/veya aktüatörlere sahiptir ve internete bağlanır. Telefonumdan garaj kapımın açık olup olmadığını görebilir ve akıllı hoparlörüme kapatmasını söyleyebilirim. Hatta gece açık kalırsa otomatik olarak kapanacak şekilde bir zamanlayıcı ayarlayabilirim. Kapı zili çaldığında, dünyanın neresinde olursam olayım telefonumdan kimin orada olduğunu görebilir ve kapı ziline yerleştirilmiş bir hoparlör ve mikrofon aracılığıyla onlarla konuşabilirim. Kan şekeri, kalp atış hızı ve uyku düzenimi izleyerek sağlığımı iyileştirmek için verilerdeki kalıpları arayabilirim. Işıklarımı bulut üzerinden kontrol edebilirim ve internet bağlantım kesildiğinde karanlıkta oturabilirim.

---

## 🚀 Zorluk

Evde, okulda veya iş yerinde bulunan IoT cihazlarını olabildiğince listeleyin - düşündüğünüzden daha fazla olabilir!

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Gözden Geçirme ve Kendi Kendine Çalışma

Tüketici IoT projelerinin faydaları ve başarısızlıkları hakkında bilgi edinin. Gizlilik sorunları, donanım problemleri veya bağlantı eksikliğinden kaynaklanan sorunlar gibi konularda yanlış giden durumlarla ilgili haber sitelerinde makaleler arayın.

Bazı örnekler:

* **[Internet of Sh*t](https://twitter.com/internetofshit)** *(küfür uyarısı)* Twitter hesabına göz atarak tüketici IoT ile ilgili başarısızlık örneklerini inceleyin.
* [c|net - Apple Watch hayatımı kurtardı: 5 kişi hikayelerini paylaşıyor](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT teknisyeni yıllarca müşteri kamera görüntülerini izlediği için suçunu kabul etti](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(tetikleyici uyarısı - rızasız gözetim)*

## Ödev

[Bir IoT projesini araştırın](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.