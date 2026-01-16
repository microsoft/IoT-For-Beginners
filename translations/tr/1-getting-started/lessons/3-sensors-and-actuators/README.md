<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-28T03:40:44+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "tr"
}
-->
# Sensörler ve Aktüatörlerle Fiziksel Dünya ile Etkileşim

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/tr/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

Bu ders, [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) tarafından sunulan [Hello IoT serisinin](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) bir parçası olarak öğretildi. Ders, 1 saatlik bir ders ve ardından dersin bazı bölümlerine daha derinlemesine dalan ve soruları yanıtlayan 1 saatlik bir ofis saati olmak üzere iki video olarak sunuldu.

[![Ders 3: Sensörler ve Aktüatörlerle Fiziksel Dünya ile Etkileşim](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Ders 3: Sensörler ve Aktüatörlerle Fiziksel Dünya ile Etkileşim - Ofis Saati](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Videoları izlemek için yukarıdaki görsellere tıklayın

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Giriş

Bu ders, IoT cihazınız için önemli iki kavramı tanıtıyor: sensörler ve aktüatörler. Ayrıca, her ikisiyle de pratik yaparak bir ışık sensörünü IoT projenize ekleyecek ve ardından ışık seviyeleriyle kontrol edilen bir LED ekleyerek etkili bir şekilde bir gece lambası oluşturacaksınız.

Bu derste şunları ele alacağız:

* [Sensörler nedir?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Bir sensör kullanın](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Sensör türleri](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Aktüatörler nedir?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Bir aktüatör kullanın](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Aktüatör türleri](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Sensörler nedir?

Sensörler, fiziksel dünyayı algılayan donanım cihazlarıdır - yani çevrelerindeki bir veya daha fazla özelliği ölçer ve bilgiyi bir IoT cihazına gönderirler. Ölçülebilecek çok fazla şey olduğu için sensörler geniş bir cihaz yelpazesini kapsar; doğal özelliklerden (örneğin hava sıcaklığı) fiziksel etkileşimlere (örneğin hareket) kadar.

Bazı yaygın sensörler şunlardır:

* Sıcaklık sensörleri - hava sıcaklığını veya daldırıldıkları nesnenin sıcaklığını algılarlar. Hobi amaçlı ve geliştiriciler için, genellikle hava basıncı ve nem ile birleştirilirler.
* Düğmeler - basıldıklarında algılarlar.
* Işık sensörleri - ışık seviyelerini algılar ve belirli renkler, UV ışığı, IR ışığı veya genel görünür ışık için olabilirler.
* Kameralar - bir fotoğraf çekerek veya video akışı yaparak dünyanın görsel bir temsilini algılarlar.
* İvmeölçerler - birden fazla yöndeki hareketi algılarlar.
* Mikrofonlar - genel ses seviyelerini veya yönlü sesi algılarlar.

✅ Araştırma yapın. Telefonunuzda hangi sensörler var?

Tüm sensörlerin ortak bir noktası vardır - algıladıkları şeyi bir IoT cihazı tarafından yorumlanabilecek bir elektrik sinyaline dönüştürürler. Bu elektrik sinyalinin nasıl yorumlandığı, sensöre ve IoT cihazıyla iletişim kurmak için kullanılan iletişim protokolüne bağlıdır.

## Bir sensör kullanın

IoT cihazınıza bir sensör eklemek için aşağıdaki ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-sensor.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-sensor.md)

## Sensör türleri

Sensörler analog veya dijital olabilir.

### Analog sensörler

En temel sensörlerden bazıları analog sensörlerdir. Bu sensörler, IoT cihazından bir voltaj alır, sensör bileşenleri bu voltajı ayarlar ve sensörden dönen voltaj ölçülerek sensör değeri elde edilir.

> 🎓 Voltaj, elektriğin bir yerden başka bir yere hareket etmesi için ne kadar itme gücü olduğunu ölçer, örneğin bir pilin pozitif terminalinden negatif terminaline. Örneğin, standart bir AA pili 1.5V'dir (V, voltun sembolüdür) ve elektriği pozitif terminalinden negatif terminaline 1.5V'luk bir kuvvetle itebilir. Farklı elektrikli donanımların çalışması için farklı voltajlara ihtiyacı vardır; örneğin, bir LED 2-3V arasında bir voltajla yanabilir, ancak 100W'lık bir akkor ampul 240V gerektirir. Voltaj hakkında daha fazla bilgiyi [Wikipedia'daki Voltaj sayfasında](https://wikipedia.org/wiki/Voltage) okuyabilirsiniz.

Bunun bir örneği bir potansiyometredir. Bu, iki pozisyon arasında döndürebileceğiniz bir kadrandır ve sensör dönüşü ölçer.

![5 volt gönderilen ve 3.8 volt dönen orta noktaya ayarlanmış bir potansiyometre](../../../../../translated_images/tr/potentiometer.35a348b9ce22f6ec.webp)

IoT cihazı, potansiyometreye bir voltajda (örneğin 5 volt) bir elektrik sinyali gönderir. Potansiyometre ayarlandıkça, diğer taraftan çıkan voltaj değişir. Örneğin, bir amplifikatör üzerindeki bir ses düğmesi gibi, 0'dan [11'e](https://wikipedia.org/wiki/Up_to_eleven) kadar bir kadran olarak etiketlenmiş bir potansiyometreniz olduğunu hayal edin. Potansiyometre tamamen kapalı konumda (0) olduğunda, 0V (0 volt) çıkacaktır. Tamamen açık konumda (11) olduğunda, 5V (5 volt) çıkacaktır.

> 🎓 Bu bir basitleştirmedir ve potansiyometreler ve değişken dirençler hakkında daha fazla bilgiyi [Wikipedia'daki potansiyometre sayfasında](https://wikipedia.org/wiki/Potentiometer) okuyabilirsiniz.

Sensörden çıkan voltaj daha sonra IoT cihazı tarafından okunur ve cihaz buna yanıt verebilir. Sensöre bağlı olarak, bu voltaj rastgele bir değer olabilir veya standart bir birime eşlenebilir. Örneğin, bir [termistör](https://wikipedia.org/wiki/Thermistor) tabanlı analog sıcaklık sensörü, sıcaklığa bağlı olarak direncini değiştirir. Çıkış voltajı daha sonra kodda yapılan hesaplamalarla Kelvin cinsinden bir sıcaklığa ve buna karşılık °C veya °F'ye dönüştürülebilir.

✅ Sensör gönderilen voltajdan daha yüksek bir voltaj döndürürse (örneğin harici bir güç kaynağından geliyorsa) ne olacağını düşünüyorsunuz? ⛔️ Bunu test ETMEYİN.

#### Analogdan dijitale dönüşüm

IoT cihazları dijitaldir - analog değerlerle çalışamazlar, yalnızca 0 ve 1'lerle çalışırlar. Bu, analog sensör değerlerinin işlenmeden önce dijital bir sinyale dönüştürülmesi gerektiği anlamına gelir. Birçok IoT cihazında, analog girişleri dijital temsillere dönüştürmek için analogdan dijitale dönüştürücüler (ADC'ler) bulunur. Sensörler ayrıca bir bağlantı kartı aracılığıyla ADC'lerle çalışabilir. Örneğin, Raspberry Pi ile Seeed Grove ekosisteminde, analog sensörler Pi'nin GPIO pinlerine bağlı bir 'hat' üzerindeki belirli portlara bağlanır ve bu hat, voltajı dijital bir sinyale dönüştürmek için bir ADC'ye sahiptir.

3.3V kullanan bir IoT cihazına bağlı bir analog ışık sensörünüz olduğunu ve 1V'luk bir değer döndürdüğünü hayal edin. Bu 1V dijital dünyada bir anlam ifade etmez, bu yüzden dönüştürülmesi gerekir. Voltaj, cihaz ve sensöre bağlı bir ölçek kullanılarak analog bir değere dönüştürülür. Örneğin, Seeed Grove ışık sensörü 0 ile 1.023 arasında değerler döndürür. Bu sensör 3.3V'da çalışırken, 1V'luk bir çıkış 300 değerine karşılık gelir. Bir IoT cihazı 300'ü analog bir değer olarak işleyemez, bu yüzden Grove hat tarafından 300'ün ikili temsili olan `0000000100101100` değerine dönüştürülür. Bu daha sonra IoT cihazı tarafından işlenir.

✅ İkili sistemi bilmiyorsanız, 0 ve 1'lerle sayıların nasıl temsil edildiğini öğrenmek için biraz araştırma yapın. [BBC Bitesize'ın ikili sistem giriş dersi](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) başlamak için harika bir yerdir.

Kodlama açısından, tüm bunlar genellikle sensörlerle birlikte gelen kütüphaneler tarafından halledilir, bu yüzden bu dönüşümle kendiniz ilgilenmeniz gerekmez. Grove ışık sensörü için Python kütüphanesini kullanarak `light` özelliğini çağırabilir veya Arduino kütüphanesini kullanarak `analogRead` fonksiyonunu çağırarak 300 değerini alabilirsiniz.

### Dijital sensörler

Dijital sensörler, analog sensörler gibi, çevrelerindeki dünyayı elektrik voltajındaki değişiklikleri kullanarak algılar. Fark, dijital bir sinyal üretmeleridir; ya yalnızca iki durumu ölçerek ya da yerleşik bir ADC kullanarak. Dijital sensörler, bir bağlantı kartında veya IoT cihazında bir ADC kullanma gereksinimini ortadan kaldırmak için giderek daha yaygın hale geliyor.

En basit dijital sensör bir düğme veya anahtardır. Bu, iki durumu olan bir sensördür: açık veya kapalı.

![Bir düğmeye 5 volt gönderilir. Basılmadığında 0 volt döner, basıldığında 5 volt döner](../../../../../translated_images/tr/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.png)

IoT cihazlarındaki GPIO pinleri gibi pinler, bu sinyali doğrudan 0 veya 1 olarak ölçebilir. Gönderilen voltaj dönen voltajla aynıysa, okunan değer 1'dir; aksi takdirde okunan değer 0'dır. Sinyali dönüştürmeye gerek yoktur, yalnızca 1 veya 0 olabilir.

> 💁 Voltajlar asla tam olarak doğru değildir, özellikle bir sensördeki bileşenlerin bir miktar direnci olacağından. Bu nedenle genellikle bir tolerans vardır. Örneğin, Raspberry Pi'nin GPIO pinleri 3.3V ile çalışır ve 1.8V'un üzerindeki bir dönüş sinyalini 1, 1.8V'un altındaki bir dönüş sinyalini 0 olarak okur.

* 3.3V düğmeye gider. Düğme kapalıdır, bu yüzden 0V çıkar ve 0 değeri elde edilir.
* 3.3V düğmeye gider. Düğme açıktır, bu yüzden 3.3V çıkar ve 1 değeri elde edilir.

Daha gelişmiş dijital sensörler analog değerleri okur ve ardından yerleşik ADC'ler kullanarak bunları dijital sinyallere dönüştürür. Örneğin, dijital bir sıcaklık sensörü, analog bir sensörle aynı şekilde bir termokupl kullanır ve mevcut sıcaklıkta termokuplun direncinden kaynaklanan voltaj değişimini ölçer. Analog bir değer döndürmek ve cihazın veya bağlantı kartının dijital bir sinyale dönüştürmesine güvenmek yerine, sensöre yerleşik bir ADC değeri dönüştürür ve IoT cihazına 0 ve 1'lerden oluşan bir dizi olarak gönderir. Bu 0 ve 1'ler, bir düğme için dijital sinyalde olduğu gibi, 1 tam voltaj ve 0 0V olarak gönderilir.

![Bir dijital sıcaklık sensörü, analog bir okumayı 0 volt için 0 ve 5 volt için 1 ile ikili verilere dönüştürerek IoT cihazına gönderiyor](../../../../../translated_images/tr/temperature-as-digital.85004491b977bae1.webp)

Dijital veri gönderimi, sensörlerin daha karmaşık hale gelmesine ve daha ayrıntılı veri, hatta güvenli sensörler için şifrelenmiş veri göndermesine olanak tanır. Bir örnek bir kameradır. Bu, bir görüntüyü yakalayan ve genellikle JPEG gibi sıkıştırılmış bir formatta IoT cihazı tarafından okunacak şekilde dijital veri olarak gönderen bir sensördür. Hatta görüntüleri yakalayıp ya kare kare tam görüntü ya da sıkıştırılmış bir video akışı göndererek video akışı yapabilir.

## Aktüatörler nedir?

Aktüatörler, sensörlerin tersidir - IoT cihazınızdan gelen bir elektrik sinyalini ışık veya ses yayma ya da bir motoru hareket ettirme gibi fiziksel dünyayla bir etkileşime dönüştürürler.

Bazı yaygın aktüatörler şunlardır:

* LED - açıldığında ışık yayar
* Hoparlör - gönderilen sinyale bağlı olarak ses yayar, basit bir buzzer'dan müzik çalabilen bir ses hoparlörüne kadar
* Adım motoru - bir sinyali belirli bir miktarda dönüşe dönüştürür, örneğin bir kadranı 90° döndürmek
* Röle - bir elektrik sinyaliyle açılıp kapatılabilen anahtarlardır. IoT cihazından gelen küçük bir voltajın daha büyük voltajları açmasına izin verirler.
* Ekranlar - daha karmaşık aktüatörlerdir ve çok segmentli bir ekranda bilgi gösterirler. Ekranlar basit LED ekranlardan yüksek çözünürlüklü video monitörlerine kadar değişir.

✅ Araştırma yapın. Telefonunuzda hangi aktüatörler var?

## Bir aktüatör kullanın

IoT cihazınıza bir aktüatör eklemek için aşağıdaki ilgili kılavuzu takip edin. Bu aktüatör, sensör tarafından kontrol edilerek bir IoT gece lambası oluşturacaktır. Işık seviyelerini ışık sensöründen toplayacak ve algılanan ışık seviyesi çok düşük olduğunda ışık yaymak için bir LED formunda bir aktüatör kullanacaktır.

![Görev akış diyagramı, ışık seviyelerinin okunmasını ve kontrol edilmesini, ardından LED'in kontrol edilmesini gösteriyor](../../../../../translated_images/tr/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-actuator.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-actuator.md)

## Aktüatör türleri

Sensörler gibi, aktüatörler de analog veya dijital olabilir.

### Analog aktüatörler

Analog aktüatörler, bir analog sinyali alır ve bunu bir tür etkileşime dönüştürür, bu etkileşim sağlanan voltaja bağlı olarak değişir.

Bir örnek, evinizdeki gibi kısılabilir bir ışıktır. Işığa sağlanan voltaj miktarı, ışığın ne kadar parlak olduğunu belirler.
![Düşük voltajda kısık, yüksek voltajda parlak bir ışık](../../../../../translated_images/tr/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.png)

Sensörlerde olduğu gibi, gerçek IoT cihazları analog değil, dijital sinyallerle çalışır. Bu, bir analog sinyal göndermek için IoT cihazının bir dijitalden analoğa dönüştürücüye (DAC) ihtiyaç duyduğu anlamına gelir. Bu dönüştürücü ya doğrudan IoT cihazında bulunur ya da bir bağlantı kartında yer alır. Bu, IoT cihazından gelen 0 ve 1'leri aktüatörün kullanabileceği bir analog voltaja dönüştürür.

✅ IoT cihazı, aktüatörün kaldırabileceğinden daha yüksek bir voltaj gönderirse ne olacağını düşünüyorsunuz?  
⛔️ Bunu test ETMEYİN.

#### Darbe Genişlik Modülasyonu

IoT cihazından gelen dijital sinyalleri analog bir sinyale dönüştürmenin bir başka seçeneği de darbe genişlik modülasyonudur (PWM). Bu yöntem, analog bir sinyal gibi davranan birçok kısa dijital darbe göndermeyi içerir.

Örneğin, bir motorun hızını kontrol etmek için PWM kullanabilirsiniz.

Bir motoru 5V'luk bir güç kaynağıyla kontrol ettiğinizi hayal edin. Motorunuza kısa bir darbe göndererek voltajı iki saliselik (0.02s) bir süre için yüksek (5V) yaparsınız. Bu süre zarfında motorunuz bir dönüşün onda biri kadar, yani 36° dönebilir. Sinyal daha sonra iki saliselik (0.02s) bir süre için duraklar ve düşük bir sinyal (0V) gönderir. Açık ve kapalı her döngü 0.04s sürer. Döngü bu şekilde tekrar eder.

![150 RPM'de bir motorun darbe genişlik modülasyonu ile dönüşü](../../../../../translated_images/tr/pwm-motor-150rpm.83347ac04ca38482.webp)

Bu, bir saniyede motoru döndüren 0.02s'lik 25 adet 5V darbesi ve ardından motoru döndürmeyen 0.02s'lik 0V duraklaması olduğu anlamına gelir. Her darbe motoru bir dönüşün onda biri kadar döndürür, bu da motorun saniyede 2.5 dönüş yapması anlamına gelir. Dijital bir sinyal kullanarak motoru saniyede 2.5 dönüş veya 150 [dakikada devir](https://wikipedia.org/wiki/Revolutions_per_minute) (RPM) hızında döndürmüş olursunuz.

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Bir PWM sinyali yarı zaman açık, yarı zaman kapalı olduğunda buna [50% görev döngüsü](https://wikipedia.org/wiki/Duty_cycle) denir. Görev döngüleri, sinyalin açık durumda olduğu sürenin kapalı duruma göre yüzdesi olarak ölçülür.

![75 RPM'de bir motorun darbe genişlik modülasyonu ile dönüşü](../../../../../translated_images/tr/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Darbelerin boyutunu değiştirerek motor hızını değiştirebilirsiniz. Örneğin, aynı motorla 0.04s'lik aynı döngü süresini koruyabilir, açık darbe süresini yarıya indirerek 0.01s yapabilir ve kapalı darbe süresini 0.03s'ye çıkarabilirsiniz. Saniyede aynı sayıda darbe (25) olmasına rağmen, her açık darbe yarı uzunluktadır. Yarı uzunlukta bir darbe motoru yalnızca bir dönüşün yirmide biri kadar döndürür ve saniyede 25 darbe ile 1.25 dönüş veya 75 RPM tamamlar. Dijital bir sinyalin darbe hızını değiştirerek analog bir motorun hızını yarıya indirmiş olursunuz.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Motorun dönüşünü özellikle düşük hızlarda nasıl düzgün tutarsınız? Uzun duraklamalarla az sayıda uzun darbe mi yoksa çok kısa duraklamalarla birçok kısa darbe mi kullanırsınız?

> 💁 Bazı sensörler de analog sinyalleri dijital sinyallere dönüştürmek için PWM kullanır.

> 🎓 Darbe genişlik modülasyonu hakkında daha fazla bilgi için [Wikipedia'daki darbe genişlik modülasyonu sayfasını](https://wikipedia.org/wiki/Pulse-width_modulation) okuyabilirsiniz.

### Dijital Aktüatörler

Dijital aktüatörler, dijital sensörler gibi, ya yüksek veya düşük voltajla kontrol edilen iki duruma sahiptir ya da bir DAC içerir ve böylece dijital bir sinyali analog bir sinyale dönüştürebilir.

Basit bir dijital aktüatör bir LED'dir. Bir cihaz 1 dijital sinyali gönderdiğinde, LED'i aydınlatan yüksek bir voltaj gönderilir. 0 dijital sinyali gönderildiğinde, voltaj 0V'a düşer ve LED söner.

![0 voltta kapalı ve 5V'da açık bir LED](../../../../../translated_images/tr/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.png)

✅ Başka hangi basit 2 durumlu aktüatörleri düşünebilirsiniz? Bir örnek, bir kapı sürgüsünü hareket ettirerek bir kapıyı kilitleyip açmak gibi şeyler yapabilen bir elektromıknatıs olan solenoiddir.

Daha gelişmiş dijital aktüatörler, örneğin ekranlar, dijital verilerin belirli formatlarda gönderilmesini gerektirir. Genellikle, doğru verileri göndermeyi kolaylaştıran kütüphanelerle birlikte gelirler.

---

## 🚀 Zorluk

Son iki dersteki zorluk, evinizde, okulunuzda veya iş yerinizde bulunan olabildiğince çok IoT cihazını listelemek ve bunların mikrodenetleyiciler, tek kartlı bilgisayarlar veya her ikisinin bir karışımı etrafında mı inşa edildiğine karar vermekti.

Listelediğiniz her cihaz için, hangi sensörlere ve aktüatörlere bağlı olduklarını belirleyin. Bu cihazlara bağlı her bir sensör ve aktüatörün amacı nedir?

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## İnceleme ve Kendi Kendine Çalışma

* [ThingLearn](http://thinglearn.jenlooper.com/curriculum/) üzerinde elektrik ve devreler hakkında okuyun.  
* [Seeed Studios Sıcaklık Sensörleri rehberi](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/) üzerinde farklı sıcaklık sensörleri hakkında bilgi edinin.  
* [Wikipedia LED sayfası](https://wikipedia.org/wiki/Light-emitting_diode) üzerinde LED'ler hakkında bilgi edinin.  

## Ödev

[Sensörler ve aktüatörler üzerine araştırma yapın](assignment.md)  

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.