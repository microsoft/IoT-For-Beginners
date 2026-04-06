# Konum Takibi

![Bu dersin genel bir sketchnote görünümü](../../../../../translated_images/tr/lesson-11.9fddbac4b664c6d5.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

## Ders Öncesi Testi

[Ders öncesi testi](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Giriş

Bir çiftçiden tüketiciye yiyecek ulaştırmanın ana süreci, ürün kutularını kamyonlara, gemilere, uçaklara veya diğer ticari taşıma araçlarına yüklemek ve yiyecekleri bir yere teslim etmeyi içerir - ya doğrudan bir müşteriye ya da işleme için bir merkezi hub veya depoya. Çiftlikten tüketiciye kadar olan bu uçtan uca süreç, *tedarik zinciri* olarak adlandırılır. Arizona State Üniversitesi'nin W. P. Carey İşletme Fakültesi'nden aşağıdaki video, tedarik zinciri fikrini ve nasıl yönetildiğini daha ayrıntılı bir şekilde ele alıyor.

[![Tedarik Zinciri Yönetimi Nedir? Arizona State Üniversitesi'nin W. P. Carey İşletme Fakültesi'nden bir video](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Videoyu izlemek için yukarıdaki görsele tıklayın

IoT cihazları eklemek, tedarik zincirinizi büyük ölçüde iyileştirebilir, öğelerin nerede olduğunu yönetmenize, taşıma ve malzeme işleme planlamanızı daha iyi yapmanıza ve sorunlara daha hızlı yanıt vermenize olanak tanır.

Bir kamyon filosu gibi araçları yönetirken, her bir aracın belirli bir zamanda nerede olduğunu bilmek faydalıdır. Araçlara GPS sensörleri takılarak konumlarının IoT sistemlerine gönderilmesi sağlanabilir, bu da sahiplerinin araçların konumunu belirlemesine, izledikleri rotayı görmesine ve varış noktalarına ne zaman ulaşacaklarını bilmesine olanak tanır. Çoğu araç WiFi kapsama alanı dışında çalıştığı için bu tür verileri göndermek için hücresel ağlar kullanır. Bazen GPS sensörü, elektronik seyir defterleri gibi daha karmaşık IoT cihazlarına entegre edilir. Bu cihazlar, sürücülerin çalışma saatleriyle ilgili yerel yasalara uyduğundan emin olmak için bir kamyonun ne kadar süredir yolda olduğunu takip eder.

Bu derste, bir Global Konumlandırma Sistemi (GPS) sensörü kullanarak bir aracın konumunu nasıl takip edeceğinizi öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Bağlı araçlar](../../../../../3-transport/lessons/1-location-tracking)
* [Coğrafi koordinatlar](../../../../../3-transport/lessons/1-location-tracking)
* [Global Konumlandırma Sistemleri (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [GPS sensör verilerini okuma](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS verileri](../../../../../3-transport/lessons/1-location-tracking)
* [GPS sensör verilerini çözme](../../../../../3-transport/lessons/1-location-tracking)

## Bağlı Araçlar

IoT, *bağlı araçlar* filoları oluşturarak mal taşımacılığını dönüştürüyor. Bu araçlar, konumları ve diğer sensör verileri hakkında bilgi raporlayan merkezi BT sistemlerine bağlıdır. Bağlı araçlardan oluşan bir filoya sahip olmanın birçok avantajı vardır:

* Konum takibi - bir aracın herhangi bir zamanda nerede olduğunu belirleyebilir, böylece:

  * Bir araç bir varış noktasına yaklaşırken uyarılar alarak boşaltma ekibini hazırlayabilirsiniz.
  * Çalınan araçları bulabilirsiniz.
  * Konum ve rota verilerini trafik sorunlarıyla birleştirerek araçları yolculuk sırasında yeniden yönlendirebilirsiniz.
  * Vergi uyumluluğu sağlayabilirsiniz. Bazı ülkeler, kamu yollarında kat edilen mesafeye göre araçlardan vergi alır (örneğin [Yeni Zelanda'nın RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), bu nedenle bir aracın kamu yollarında mı yoksa özel yollarında mı olduğunu bilmek, ödenecek vergiyi hesaplamayı kolaylaştırır.
  * Arıza durumunda bakım ekiplerini nereye göndereceğinizi bilirsiniz.

* Sürücü telemetrisi - sürücülerin hız sınırlarına uyduğundan, uygun hızlarda viraj aldığından, erken ve verimli fren yaptığından ve güvenli bir şekilde sürdüğünden emin olabilirsiniz. Bağlı araçlar ayrıca olayları kaydetmek için kameralarla donatılabilir. Bu, sigorta ile bağlantılı olabilir ve iyi sürücüler için indirimli oranlar sunabilir.

* Sürücü saatleri uyumluluğu - sürücülerin motoru açma ve kapama zamanlarına göre yasal olarak izin verilen saatlerde sürüş yaptığından emin olabilirsiniz.

Bu avantajlar birleştirilebilir - örneğin, sürücü saatleri uyumluluğunu konum takibi ile birleştirerek sürücüleri yasal sürüş saatleri içinde varış noktalarına ulaşamayacaklarsa yeniden yönlendirebilirsiniz. Bunlar ayrıca sıcaklık kontrollü kamyonlardan sıcaklık verileri gibi araçlara özgü diğer telemetri ile birleştirilebilir, böylece malların sıcaklıkta tutulamayacağı bir rota mevcutsa araçlar yeniden yönlendirilebilir.

> 🎓 Lojistik, malları bir yerden başka bir yere taşımak sürecidir, örneğin bir çiftlikten bir süpermarkete bir veya daha fazla depo aracılığıyla. Bir çiftçi, bir kamyona yüklenen domates kutularını paketler, merkezi bir depoya teslim edilir ve ardından farklı türde ürünler içerebilecek ikinci bir kamyona yüklenir ve süpermarkete teslim edilir.

Araç takibinin temel bileşeni, konumlarını Dünya üzerinde herhangi bir yerde belirleyebilen GPS sensörleridir. Bu derste bir GPS sensörü kullanmayı öğreneceksiniz, önce Dünya üzerinde bir konumu nasıl tanımlayacağınızı öğrenerek başlayacağız.

## Coğrafi Koordinatlar

Coğrafi koordinatlar, Dünya yüzeyindeki noktaları tanımlamak için kullanılır, tıpkı bir bilgisayar ekranında bir piksel çizmek veya çapraz dikişte dikişleri konumlandırmak için koordinatların kullanılması gibi. Tek bir nokta için bir çift koordinatınız vardır. Örneğin, Microsoft Kampüsü, Redmond, Washington, ABD'de 47.6423109, -122.1390293 konumunda bulunur.

### Enlem ve Boylam

Dünya bir küredir - üç boyutlu bir daire. Bu nedenle, noktalar, dairelerin geometrisiyle aynı şekilde 360 dereceye bölünerek tanımlanır. Enlem, kuzeyden güneye olan derece sayısını ölçer, boylam ise doğudan batıya olan derece sayısını ölçer.

> 💁 Kimse dairelerin neden 360 dereceye bölündüğünün orijinal nedenini tam olarak bilmiyor. [Wikipedia'daki derece (açı) sayfası](https://wikipedia.org/wiki/Degree_(angle)) bazı olası nedenleri ele alıyor.

![Kuzey Kutbu'nda 90°, Kuzey Kutbu ile ekvator arasında yarı yolda 45°, ekvatorda 0°, ekvator ile Güney Kutbu arasında yarı yolda -45° ve Güney Kutbu'nda -90° enlem çizgileri](../../../../../translated_images/tr/latitude-lines.11d8d91dfb2014a5.webp)

Enlem, Dünya'yı çevreleyen ve ekvatora paralel olarak uzanan çizgiler kullanılarak ölçülür, Kuzey ve Güney Yarımküreleri her biri 90° olacak şekilde böler. Ekvator 0°'dedir, Kuzey Kutbu 90°'dedir, ayrıca 90° Kuzey olarak da bilinir ve Güney Kutbu -90°'dedir veya 90° Güney olarak bilinir.

Boylam, doğu ve batı yönünde ölçülen derece sayısı olarak ölçülür. Boylamın 0° başlangıcı *Baş Meridyen* olarak adlandırılır ve 1884 yılında [İngiltere'deki Greenwich Kraliyet Gözlemevi](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich) üzerinden geçen Kuzey Kutbu'ndan Güney Kutbu'na uzanan bir çizgi olarak tanımlanmıştır.

![Baş Meridyen'in batısında -180°'den, Baş Meridyen'de 0°'ye, Baş Meridyen'in doğusunda 180°'ye kadar uzanan boylam meridyenleri](../../../../../translated_images/tr/longitude-meridians.ab4ef1c91c064586.webp)

> 🎓 Meridyen, Kuzey Kutbu'ndan Güney Kutbu'na uzanan ve bir yarım daire oluşturan hayali bir düz çizgidir.

Bir noktanın boylamını ölçmek için, Baş Meridyen'den o noktadan geçen bir meridyene kadar ekvator boyunca ölçülen derece sayısını ölçersiniz. Boylam -180°'den, yani 180° Batı'dan, Baş Meridyen'de 0°'ye, 180°'ye veya 180° Doğu'ya kadar uzanır. 180° ve -180° aynı noktayı ifade eder, antimeridyen veya 180. meridyen. Bu, Baş Meridyen'in tam karşısındaki Dünya üzerindeki bir meridyendir.

> 💁 Antimeridyen, yaklaşık olarak aynı konumda olan ancak düz bir çizgi olmayan ve jeopolitik sınırların etrafında değişen Uluslararası Tarih Çizgisi ile karıştırılmamalıdır.

✅ Araştırma yapın: Şu anki konumunuzun enlem ve boylamını bulmaya çalışın.

### Derece, Dakika ve Saniye vs Ondalık Dereceler

Geleneksel olarak, enlem ve boylam derecelerinin ölçümleri, ilk zaman ve mesafe ölçümlerini ve kayıtlarını yapan Antik Babilliler tarafından kullanılan bir numaralandırma sistemi olan seksagesimal numaralandırma veya taban-60 kullanılarak yapılırdı. Muhtemelen farkında bile olmadan her gün seksagesimal kullanıyorsunuz - saatleri 60 dakikaya ve dakikaları 60 saniyeye bölerek.

Boylam ve enlem, derece, dakika ve saniye cinsinden ölçülür, bir dakika bir derecenin 1/60'ı ve bir saniye bir dakikanın 1/60'ıdır.

Örneğin, ekvatorda:

* 1° enlem **111.3 kilometre**dir.
* 1 dakika enlem 111.3/60 = **1.855 kilometre**dir.
* 1 saniye enlem 1.855/60 = **0.031 kilometre**dir.

Bir dakika için sembol tek bir tırnak işareti, bir saniye için ise çift tırnak işaretidir. Örneğin, 2 derece, 17 dakika ve 43 saniye, 2°17'43" olarak yazılır. Saniyenin kesirleri ondalık olarak verilir, örneğin yarım saniye 0°0'0.5" olarak yazılır.

Bilgisayarlar taban-60 ile çalışmaz, bu nedenle bu koordinatlar çoğu bilgisayar sisteminde GPS verileri kullanılırken ondalık dereceler olarak verilir. Örneğin, 2°17'43", 2.295277 olarak ifade edilir. Derece sembolü genellikle çıkarılır.

Bir noktanın koordinatları her zaman `enlem, boylam` olarak verilir, bu nedenle daha önceki Microsoft Kampüsü örneği olan 47.6423109,-122.117198 şu değerlere sahiptir:

* Enlem: 47.6423109 (ekvatordan 47.6423109 derece kuzey)
* Boylam: -122.1390293 (Baş Meridyen'den 122.1390293 derece batı).

![Microsoft Kampüsü, 47.6423109,-122.117198](../../../../../translated_images/tr/microsoft-gps-location-world.a321d481b010f6ad.webp)

## Global Konumlandırma Sistemleri (GPS)

GPS sistemleri, Dünya'nın etrafında dönen birden fazla uydu kullanarak konumunuzu bulur. Muhtemelen farkında bile olmadan GPS sistemlerini kullandınız - telefonunuzdaki Apple Haritalar veya Google Haritalar gibi bir harita uygulamasında konumunuzu bulmak için, bir yolculuk uygulamasında (Uber veya Lyft gibi) aracınızın nerede olduğunu görmek için veya aracınızdaki uydu navigasyonunu (sat-nav) kullanırken.

> 🎓 'Uydu navigasyonu'ndaki uydular GPS uydularıdır!

GPS sistemleri, her bir uydunun mevcut konumunu ve doğru bir zaman damgasını içeren bir sinyal göndererek çalışır. Bu sinyaller radyo dalgaları üzerinden gönderilir ve GPS sensöründeki bir anten tarafından algılanır. Bir GPS sensörü bu sinyalleri algılar ve mevcut zamanı kullanarak sinyalin uydu ile sensör arasındaki mesafeyi ölçer. Radyo dalgalarının hızı sabit olduğu için, GPS sensörü gönderilen zaman damgasını kullanarak sensörün uyduya olan uzaklığını hesaplayabilir. En az 3 uydudan gelen verileri ve gönderilen konumları birleştirerek, GPS sensörü Dünya üzerindeki konumunu belirleyebilir.

> 💁 GPS sensörlerinin radyo dalgalarını algılamak için antenlere ihtiyacı vardır. Yerleşik GPS'e sahip kamyonlar ve arabalarda antenler genellikle ön camda veya çatıda iyi bir sinyal almak için konumlandırılır. Ayrı bir GPS sistemi kullanıyorsanız, örneğin bir akıllı telefon veya bir IoT cihazı, GPS sistemine veya telefona entegre edilmiş antenin gökyüzünü net bir şekilde görebildiğinden emin olmanız gerekir, örneğin ön camınıza monte edilerek.

![Sensörün birden fazla uyduya olan mesafesini bilerek konum hesaplanabilir](../../../../../translated_images/tr/gps-satellites.04acf1148fe25fbf.webp)

GPS uyduları Dünya'nın etrafında döner, sensörün üzerinde sabit bir noktada değildir, bu nedenle konum verileri enlem ve boylamın yanı sıra deniz seviyesinden yükseklik içerir.

GPS, ABD ordusu tarafından uygulanan doğruluk sınırlamalarına sahipti ve doğruluğu yaklaşık 5 metre ile sınırlıyordu. Bu sınırlama 2000 yılında kaldırıldı ve 30 santimetre doğruluğa izin verildi. Ancak, bu doğruluğu elde etmek her zaman mümkün değildir çünkü sinyallerdeki parazitler doğruluğu etkileyebilir.

✅ Eğer bir akıllı telefonunuz varsa, harita uygulamasını açın ve konumunuzun ne kadar doğru olduğunu görün. Telefonunuzun daha doğru bir konum elde etmek için birden fazla uydu algılaması biraz zaman alabilir.
💁 Uydular, son derece hassas atom saatleri içerir, ancak Einstein'ın özel ve genel görelilik teorilerinin öngördüğü gibi hız arttıkça zamanın yavaşlaması nedeniyle Dünya'daki atom saatlerine kıyasla günde 38 mikrosaniye (0.0000038 saniye) sapma gösterir - uydular Dünya'nın dönüşünden daha hızlı hareket eder. Bu sapma, özel ve genel görelilik teorilerinin öngörülerini kanıtlamak için kullanılmıştır ve GPS sistemlerinin tasarımında buna göre ayarlama yapılması gerekir. Kelimenin tam anlamıyla, bir GPS uydusunda zaman daha yavaş akar.
GPS sistemleri, ABD, Rusya, Japonya, Hindistan, AB ve Çin gibi birçok ülke ve siyasi birlik tarafından geliştirilmiş ve kullanıma sunulmuştur. Modern GPS sensörleri, daha hızlı ve daha doğru konum belirlemek için bu sistemlerin çoğuna bağlanabilir.

> 🎓 Her bir sistemdeki uydu gruplarına "takımyıldızlar" denir.

## GPS sensör verilerini okuma

Çoğu GPS sensörü, GPS verilerini UART üzerinden gönderir.

> ⚠️ UART, [proje 2, ders 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart) kapsamında ele alınmıştır. Gerekirse bu derse geri dönün.

IoT cihazınızda bir GPS sensörü kullanarak GPS verilerini alabilirsiniz.

### Görev - GPS sensörünü bağlayın ve GPS verilerini okuyun

IoT cihazınızı kullanarak GPS verilerini okumak için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-gps-sensor.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-gps-sensor.md)

## NMEA GPS verileri

Kodunuzu çalıştırdığınızda, çıktıda anlamsız gibi görünen bir şeyler görmüş olabilirsiniz. Aslında bu, standart GPS verileridir ve hepsinin bir anlamı vardır.

GPS sensörleri, NMEA mesajlarını kullanarak veri gönderir ve bu mesajlar NMEA 0183 standardına dayanır. NMEA, ABD merkezli bir ticaret organizasyonu olan [National Marine Electronics Association](https://www.nmea.org) (Ulusal Deniz Elektroniği Derneği) için kullanılan bir kısaltmadır ve deniz elektroniği arasındaki iletişim için standartlar belirler.

> 💁 Bu standart tescillidir ve en az 2.000 ABD doları karşılığında satılmaktadır, ancak standart hakkında yeterli bilgi kamuya açık olduğundan, çoğu kısmı tersine mühendislik ile çözülmüş ve açık kaynaklı veya ticari olmayan kodlarda kullanılabilir hale gelmiştir.

Bu mesajlar metin tabanlıdır. Her mesaj, `$` karakteriyle başlayan bir *cümle*den oluşur, ardından mesajın kaynağını belirten 2 karakter (örneğin, ABD GPS sistemi için GP, Rus GPS sistemi GLONASS için GN) ve mesaj türünü belirten 3 karakter gelir. Mesajın geri kalanı, virgülle ayrılmış alanlardan oluşur ve bir yeni satır karakteriyle biter.

Alınabilecek mesaj türlerinden bazıları şunlardır:

| Tür  | Açıklama |
| ---- | -------- |
| GGA  | GPS Konum Verileri, GPS sensörünün enlem, boylam ve rakımı ile bu konumu hesaplamak için görülebilen uydu sayısını içerir. |
| ZDA  | Mevcut tarih ve saat, yerel saat dilimi dahil |
| GSV  | Görülebilen uyduların detayları - GPS sensörünün sinyal algılayabildiği uydular olarak tanımlanır |

> 💁 GPS verileri zaman damgalarını içerir, bu nedenle IoT cihazınız bir GPS sensöründen zaman alabilir ve bir NTP sunucusuna veya dahili gerçek zamanlı saate bağımlı kalmaz.

GGA mesajı, `(dd)dmm.mmmm` formatında mevcut konumu ve yönü belirten tek bir karakter içerir. Formatta `d` dereceyi, `m` dakikayı ve saniyeler dakikanın ondalık kısmı olarak gösterir. Örneğin, 2°17'43" 217.716666667 olarak ifade edilir - 2 derece, 17.716666667 dakika.

Yön karakteri, kuzey veya güneyi belirtmek için enlemde `N` veya `S`, doğu veya batıyı belirtmek için boylamda `E` veya `W` olabilir. Örneğin, 2°17'43" enlemi için yön karakteri `N`, -2°17'43" için ise `S` olur.

Örnek - NMEA cümlesi `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Enlem kısmı `4738.538654,N`, bu da ondalık derece olarak 47.6423109'a dönüşür. `4738.538654` 47.6423109'dur ve yön `N` (kuzey) olduğu için pozitif bir enlemdir.

* Boylam kısmı `12208.341758,W`, bu da ondalık derece olarak -122.1390293'e dönüşür. `12208.341758` 122.1390293°'dir ve yön `W` (batı) olduğu için negatif bir boylamdır.

## GPS sensör verilerini çözümleme

Ham NMEA verilerini kullanmak yerine, bunları daha kullanışlı bir formata dönüştürmek daha iyidir. Ham NMEA mesajlarından faydalı veriler çıkarmak için kullanabileceğiniz birçok açık kaynaklı kütüphane bulunmaktadır.

### Görev - GPS sensör verilerini çözümleme

IoT cihazınızı kullanarak GPS sensör verilerini çözümlemek için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer-gps-decode.md)

---

## 🚀 Meydan Okuma

Kendi NMEA çözümleyicinizi yazın! NMEA cümlelerini çözümlemek için üçüncü taraf kütüphanelere güvenmek yerine, NMEA cümlelerinden enlem ve boylamı çıkarmak için kendi çözümleyicinizi yazabilir misiniz?

## Ders sonrası test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Gözden Geçirme ve Kendi Kendine Çalışma

* Wikipedia'daki [Coğrafi koordinat sistemi sayfasında](https://wikipedia.org/wiki/Geographic_coordinate_system) Coğrafi Koordinatlar hakkında daha fazla bilgi edinin.
* Wikipedia'daki [Baş Meridyen sayfasında](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies) Dünya dışındaki diğer gök cisimlerindeki Baş Meridyenler hakkında bilgi edinin.
* AB, Japonya, Rusya, Hindistan ve ABD gibi çeşitli dünya hükümetleri ve siyasi birlikler tarafından geliştirilen farklı GPS sistemlerini araştırın.

## Ödev

[Diğer GPS verilerini araştırın](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.