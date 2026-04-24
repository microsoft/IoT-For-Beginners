# Otomatik Bitki Sulama

![Bu dersin genel görünümünü gösteren bir sketchnote](../../../../../translated_images/tr/lesson-7.30b5f577d3cb8e03.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

Bu ders, [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) tarafından sunulan [IoT for Beginners Proje 2 - Dijital Tarım serisi](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) kapsamında öğretilmiştir.

[![IoT destekli otomatik bitki sulama](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Ders Öncesi Testi

[Ders öncesi testi](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Giriş

Son derste, toprak nemini nasıl izleyeceğinizi öğrendiniz. Bu derste, toprak nemine yanıt veren otomatik bir sulama sisteminin temel bileşenlerini nasıl oluşturacağınızı öğreneceksiniz. Ayrıca zamanlama hakkında bilgi edineceksiniz - sensörlerin değişikliklere yanıt vermesinin zaman alabileceği ve aktüatörlerin sensörler tarafından ölçülen özellikleri değiştirmesinin zaman alabileceği.

Bu derste şunları ele alacağız:

* [Düşük güçlü bir IoT cihazından yüksek güçlü cihazları kontrol etme](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Bir röleyi kontrol etme](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Bitkinizi MQTT üzerinden kontrol etme](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Sensör ve aktüatör zamanlaması](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Bitki kontrol sunucunuza zamanlama ekleme](../../../../../2-farm/lessons/3-automated-plant-watering)

## Düşük Güçlü Bir IoT Cihazından Yüksek Güçlü Cihazları Kontrol Etme

IoT cihazları düşük voltaj kullanır. Bu, sensörler ve LED gibi düşük güçlü aktüatörler için yeterlidir, ancak sulama için kullanılan bir su pompası gibi daha büyük donanımları kontrol etmek için yetersizdir. Ev bitkileri için kullanabileceğiniz küçük pompalar bile bir IoT geliştirme kitine fazla akım çeker ve kartı yakabilir.

> 🎓 Akım, Amper (A) cinsinden ölçülür ve bir devreden geçen elektrik miktarını ifade eder. Voltaj itme gücünü sağlar, akım ise ne kadar itildiğini gösterir. Akım hakkında daha fazla bilgi için [Wikipedia'daki elektrik akımı sayfasını](https://wikipedia.org/wiki/Electric_current) okuyabilirsiniz.

Bu sorunun çözümü, bir pompayı harici bir güç kaynağına bağlamak ve pompayı açmak için bir aktüatör kullanmaktır. Bu, bir ışığı açmak için bir anahtarı çevirmeye benzer. Parmağınızın bir anahtarı çevirmesi için gereken enerji miktarı küçüktür, ancak bu, ışığı 110v/240v ana elektrik şebekesine bağlar.

![Bir ışık anahtarı, bir ışığa güç sağlar](../../../../../translated_images/tr/light-switch.760317ad6ab8bd6d.webp)

> 🎓 [Ana elektrik şebekesi](https://wikipedia.org/wiki/Mains_electricity), dünyanın birçok yerinde evlere ve iş yerlerine ulusal altyapı aracılığıyla sağlanan elektriği ifade eder.

✅ IoT cihazları genellikle 3.3V veya 5V sağlayabilir ve 1 amperden (1A) daha az akım çekebilir. Bunu, genellikle 230V (Kuzey Amerika'da 120V ve Japonya'da 100V) olan ve 30A çeken cihazlara güç sağlayabilen ana elektrik şebekesiyle karşılaştırın.

Bu işi yapabilecek birçok aktüatör vardır, bunlar arasında mevcut anahtarlara bağlanarak bir parmağın onları açmasını taklit eden mekanik cihazlar da bulunur. En popüler olanı röledir.

### Röleler

Bir röle, bir elektrik sinyalini mekanik bir harekete dönüştüren ve bir anahtarı açan elektromekanik bir anahtardır. Rölenin çekirdeği bir elektromıknatıstır.

> 🎓 [Elektromıknatıslar](https://wikipedia.org/wiki/Electromagnet), bir tel bobininden elektrik geçirilerek oluşturulan mıknatıslardır. Elektrik açıldığında, bobin manyetize olur. Elektrik kapatıldığında, bobin manyetizmasını kaybeder.

![Açık olduğunda, elektromıknatıs bir manyetik alan oluşturur ve çıkış devresinin anahtarını açar](../../../../../translated_images/tr/relay-on.4db16a0fd6b66926.webp)

Bir rölede, bir kontrol devresi elektromıknatısı besler. Elektromıknatıs açık olduğunda, bir kolu çeker ve bir anahtarı hareket ettirir, bir çift kontağı kapatır ve bir çıkış devresini tamamlar.

![Kapalı olduğunda, elektromıknatıs bir manyetik alan oluşturmaz ve çıkış devresinin anahtarını kapatır](../../../../../translated_images/tr/relay-off.c34a178a2960fecd.webp)

Kontrol devresi kapalı olduğunda, elektromıknatıs kapanır, kolu serbest bırakır ve kontakları açar, çıkış devresini kapatır. Röleler dijital aktüatörlerdir - röleye yüksek bir sinyal gönderildiğinde açılır, düşük bir sinyal gönderildiğinde kapanır.

Çıkış devresi, bir sulama sistemi gibi ek donanımları çalıştırmak için kullanılabilir. IoT cihazı röleyi açabilir, sulama sistemine güç sağlayan çıkış devresini tamamlayabilir ve bitkiler sulanır. IoT cihazı daha sonra röleyi kapatabilir, sulama sistemine giden gücü kesebilir ve suyu kapatabilir.

![Bir röle açıldığında, bir pompa açılır ve bir bitkiye su gönderir](../../../../../images/strawberry-pump.gif)

Yukarıdaki videoda, bir röle açılıyor. Röledeki bir LED, rölenin açık olduğunu göstermek için yanıyor (bazı röle kartlarında rölenin açık veya kapalı olduğunu göstermek için LED'ler bulunur) ve pompaya güç gönderilir, pompa açılır ve bir bitkiye su pompalanır.

> 💁 Röleler, bir çıkış devresini açıp kapatmak yerine iki çıkış devresi arasında geçiş yapmak için de kullanılabilir. Kol hareket ettikçe, bir çıkış devresini tamamlamaktan başka bir çıkış devresini tamamlamaya geçer, genellikle ortak bir güç bağlantısını veya ortak bir toprak bağlantısını paylaşır.

✅ Araştırma yapın: Rölelerin, kontrol devresinin güç uygulandığında röleyi açıp kapatması veya birden fazla çıkış devresi gibi farklılıkları olan birçok türü vardır. Bu farklı türler hakkında bilgi edinin.

Kol hareket ettiğinde, genellikle elektromıknatısla temas ettiğinde belirgin bir tıklama sesi duyabilirsiniz.

> 💁 Bir röle, bağlantıyı yapmanın aslında röleye giden gücü kesmesi, röleyi kapatması ve ardından röleye tekrar güç göndermesi için kablolanabilir. Bu, rölenin inanılmaz hızlı bir şekilde tıklayarak bir vızıltı sesi çıkarmasına neden olur. Bu, ilk elektrikli kapı zillerinde kullanılan bazı vızıltıların nasıl çalıştığıdır.

### Röle Gücü

Elektromıknatısın kolu çekmek için çok fazla güce ihtiyacı yoktur, 3.3V veya 5V çıkış kullanılarak bir IoT geliştirme kiti ile kontrol edilebilir. Çıkış devresi, röleye bağlı olarak, ana voltaj veya endüstriyel kullanım için daha yüksek güç seviyeleri dahil olmak üzere çok daha fazla güç taşıyabilir. Bu şekilde bir IoT geliştirme kiti, tek bir bitki için küçük bir pompadan, ticari bir çiftlik için devasa bir endüstriyel sisteme kadar bir sulama sistemini kontrol edebilir.

![Kontrol devresi, çıkış devresi ve röle etiketlenmiş bir Grove rölesi](../../../../../translated_images/tr/grove-relay-labelled.293e068f5c3c2a19.webp)

Yukarıdaki görselde bir Grove rölesi gösterilmektedir. Kontrol devresi, bir IoT cihazına bağlanır ve röleyi 3.3V veya 5V kullanarak açar veya kapatır. Çıkış devresinin iki terminali vardır, herhangi biri güç veya toprak olabilir. Çıkış devresi, 250V'da 10A'ya kadar dayanabilir, bu da bir dizi ana elektrikle çalışan cihaz için yeterlidir. Daha yüksek güç seviyelerine dayanabilen röleler de mevcuttur.

![Bir röle üzerinden bağlanmış bir pompa](../../../../../translated_images/tr/pump-wired-to-relay.66c5cfc0d8918990.webp)

Yukarıdaki görselde, bir röle üzerinden bir pompaya güç sağlanmaktadır. Bir kırmızı kablo, bir USB güç kaynağının +5V terminalini rölenin çıkış devresinin bir terminaline bağlar ve başka bir kırmızı kablo, çıkış devresinin diğer terminalini pompaya bağlar. Siyah bir kablo, pompayı USB güç kaynağının toprak terminaline bağlar. Röle açıldığında, devre tamamlanır, pompaya 5V gönderilir ve pompa çalışır.

## Bir Röleyi Kontrol Etme

Bir IoT geliştirme kitinden bir röleyi kontrol edebilirsiniz.

### Görev - Bir Röleyi Kontrol Etme

IoT cihazınızı kullanarak bir röleyi kontrol etmek için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Tek kartlı bilgisayar - Raspberry Pi](pi-relay.md)
* [Tek kartlı bilgisayar - Sanal cihaz](virtual-device-relay.md)

## Bitkinizi MQTT Üzerinden Kontrol Etme

Şu ana kadar röleniz, tek bir toprak nemi ölçümüne dayalı olarak doğrudan IoT cihazı tarafından kontrol ediliyordu. Ticari bir sulama sisteminde, kontrol mantığı merkezi hale getirilir, böylece birden fazla sensörden gelen verileri kullanarak sulama kararları alabilir ve herhangi bir yapılandırmayı tek bir yerden değiştirebilir. Bunu simüle etmek için röleyi MQTT üzerinden kontrol edebilirsiniz.

### Görev - Röleyi MQTT Üzerinden Kontrol Etme

1. `soil-moisture-sensor` projenize MQTT'ye bağlanmak için gerekli MQTT kütüphanelerini/pip paketlerini ve kodunu ekleyin. İstemci kimliğini, kimliğinizin önüne `soilmoisturesensor_client` ekleyerek adlandırın.

    > ⚠️ Gerekirse [Proje 1, Ders 4'teki MQTT'ye bağlanma talimatlarına](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt) başvurabilirsiniz.

1. Toprak nemi ayarlarıyla telemetri göndermek için ilgili cihaz kodunu ekleyin. Telemetri mesajı için özelliği `soil_moisture` olarak adlandırın.

    > ⚠️ Gerekirse [Proje 1, Ders 4'teki MQTT'ye telemetri gönderme talimatlarına](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device) başvurabilirsiniz.

1. Telemetriye abone olmak ve bir komut göndererek röleyi kontrol etmek için `soil-moisture-sensor-server` adlı bir klasörde yerel sunucu kodu oluşturun. Komut mesajındaki özelliği `relay_on` olarak adlandırın ve istemci kimliğini kimliğinizin önüne `soilmoisturesensor_server` ekleyerek adlandırın. Bu derste bu koda ekleme yapacağınız için, Proje 1, Ders 4'te yazdığınız sunucu koduyla aynı yapıyı koruyun.

    > ⚠️ Gerekirse [MQTT'ye telemetri gönderme talimatlarına](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) ve [MQTT üzerinden komut gönderme talimatlarına](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) başvurabilirsiniz.

1. Gelen komutlardan röleyi kontrol etmek için ilgili cihaz kodunu ekleyin ve mesajdaki `relay_on` özelliğini kullanın. `soil_moisture` 450'den büyükse `relay_on` için true gönderin, aksi takdirde false gönderin. Bu, daha önce IoT cihazı için eklediğiniz mantıkla aynıdır.

    > ⚠️ Gerekirse [MQTT'den gelen komutlara yanıt verme talimatlarına](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device) başvurabilirsiniz.

> 💁 Bu kodu [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt) klasöründe bulabilirsiniz.

Cihazınızda ve yerel sunucunuzda kodun çalıştığından emin olun ve sanal sensör tarafından gönderilen değerleri değiştirerek veya toprağa su ekleyerek ya da sensörü topraktan çıkararak toprak nem seviyelerini değiştirerek test edin.

## Sensör ve Aktüatör Zamanlaması

Ders 3'te bir gece lambası yapmıştınız - bir ışık sensörü tarafından düşük ışık seviyesi algılandığında hemen açılan bir LED. Işık sensörü, ışık seviyelerindeki değişikliği anında algıladı ve cihaz hızlı bir şekilde yanıt verebildi, yalnızca `loop` fonksiyonundaki veya `while True:` döngüsündeki gecikme süresiyle sınırlıydı. Bir IoT geliştiricisi olarak, her zaman bu kadar hızlı bir geri bildirim döngüsüne güvenemezsiniz.

### Toprak Nemi İçin Zamanlama

Eğer önceki derste fiziksel bir sensör kullanarak toprak nemini ölçtüyseniz, bitkinizi suladıktan sonra toprak nemi ölçümünün düşmesinin birkaç saniye sürdüğünü fark etmiş olabilirsiniz. Bu, sensörün yavaş olmasından değil, suyun toprağa nüfuz etmesinin zaman almasından kaynaklanır.
💁 Sensöre çok yakın bir şekilde sulama yaptıysanız, ölçümün hızla düştüğünü ve ardından tekrar yükseldiğini görmüş olabilirsiniz - bu, sensörün yakınındaki suyun toprağın geri kalanına yayılması ve sensörün bulunduğu bölgedeki toprak nemini azaltmasından kaynaklanır.
![Sulama sırasında 658 olan bir toprak nem ölçümü değişmez, su toprağa nüfuz ettiğinde sulamadan sonra yalnızca 320'ye düşer](../../../../../translated_images/tr/soil-moisture-travel.a0e31af222cf1438.webp)

Yukarıdaki diyagramda, bir toprak nem ölçümü 658 değerini gösteriyor. Bitki sulanıyor, ancak bu ölçüm hemen değişmiyor çünkü su henüz sensöre ulaşmamış. Su sensöre ulaşmadan sulama işlemi tamamlanabilir ve değer, yeni nem seviyesini yansıtacak şekilde düşer.

Toprak nem seviyelerine göre bir röle aracılığıyla bir sulama sistemini kontrol etmek için kod yazıyor olsaydınız, bu gecikmeyi dikkate almanız ve IoT cihazınıza daha akıllı zamanlama eklemeniz gerekirdi.

✅ Bir an durup bunu nasıl yapabileceğinizi düşünün.

### Sensör ve aktüatör zamanlamasını kontrol etme

Bir çiftlik için bir sulama sistemi kurmakla görevlendirildiğinizi hayal edin. Toprak türüne bağlı olarak, yetiştirilen bitkiler için ideal toprak nem seviyesi, 400-450 analog voltaj okumasına karşılık gelmektedir.

Cihazı gece lambası gibi programlayabilirsiniz - sensör 450'nin üzerinde okuma yaptığı sürece bir röleyi açarak pompayı çalıştırabilirsiniz. Ancak sorun şu ki, suyun pompadan toprağa ve sensöre ulaşması biraz zaman alır. Sensör, 450 seviyesini algıladığında suyu durdurur, ancak pompalanan su toprağa nüfuz etmeye devam ettikçe su seviyesi düşmeye devam eder. Sonuç olarak su israfı ve kök hasarı riski oluşur.

✅ Unutmayın - çok fazla su, çok az su kadar kötü olabilir ve değerli bir kaynağı boşa harcar.

Daha iyi çözüm, aktüatörün açılması ile sensörün okuduğu özelliğin değişmesi arasında bir gecikme olduğunu anlamaktır. Bu, sensörün değeri tekrar ölçmeden önce bir süre beklemesi gerektiği gibi, aktüatörün de bir sonraki sensör ölçümü alınmadan önce bir süre kapalı kalması gerektiği anlamına gelir.

Röle her seferinde ne kadar süre açık kalmalı? Daha temkinli olmak ve röleyi kısa bir süre açıp suyun toprağa nüfuz etmesini beklemek, ardından nem seviyelerini tekrar kontrol etmek daha iyidir. Sonuçta, her zaman daha fazla su eklemek için pompayı tekrar açabilirsiniz, ancak topraktan suyu çıkaramazsınız.

> 💁 Bu tür zamanlama kontrolü, oluşturduğunuz IoT cihazına, ölçülen özelliğe ve kullanılan sensörler ve aktüatörlere çok özeldir.

![Bir çilek bitkisi, bir pompa aracılığıyla suya bağlı, pompa bir röleye bağlı. Röle ve bitkideki bir toprak nem sensörü, bir Raspberry Pi'ye bağlı](../../../../../translated_images/tr/strawberry-with-pump.b410fc72ac6aabad.webp)

Örneğin, bir toprak nem sensörü ve bir röle tarafından kontrol edilen bir pompa ile bir çilek bitkim var. Su eklediğimde, toprak nem okumasının stabilize olması yaklaşık 20 saniye sürüyor. Bu, röleyi kapatmam ve nem seviyelerini kontrol etmeden önce 20 saniye beklemem gerektiği anlamına geliyor. Çok az su olmasını çok fazla suya tercih ederim - pompayı her zaman tekrar açabilirim, ancak bitkiden suyu çıkaramam.

![Adım 1, ölçüm al. Adım 2, su ekle. Adım 3, suyun toprağa nüfuz etmesini bekle. Adım 4, ölçümü tekrar al](../../../../../translated_images/tr/soil-moisture-delay.865f3fae206db01d.webp)

Bu, en iyi sürecin şu şekilde bir sulama döngüsü olacağı anlamına gelir:

* Pompayı 5 saniye aç
* 20 saniye bekle
* Toprak nemini kontrol et
* Seviye hala ihtiyaç duyduğum seviyenin üzerindeyse, yukarıdaki adımları tekrarla

Pompa için 5 saniye çok uzun olabilir, özellikle nem seviyeleri yalnızca gereken seviyenin biraz üzerindeyse. Hangi zamanlamayı kullanacağınızı bilmenin en iyi yolu, denemek ve ardından sensör verileriyle ayarlamalar yapmaktır; sürekli bir geri bildirim döngüsü ile. Bu, sabit bir 5 saniye yerine, gereken toprak neminin her 100 fazlası için pompayı 1 saniye açmak gibi daha ayrıntılı bir zamanlamaya bile yol açabilir.

✅ Araştırma yapın: Başka zamanlama hususları var mı? Toprak nemi çok düşük olduğunda bitki herhangi bir zamanda sulanabilir mi, yoksa bitkileri sulamak için iyi ve kötü zamanlar olan belirli saatler var mı?

> 💁 Dış mekan yetiştiriciliği için otomatik sulama sistemlerini kontrol ederken hava tahminleri de dikkate alınabilir. Yağmur bekleniyorsa, sulama yağmur bitene kadar bekletilebilir. Bu noktada toprak yeterince nemli olabilir ve sulamaya gerek kalmaz, yağmurdan hemen önce sulama yaparak suyu boşa harcamaktan çok daha verimlidir.

## Bitki kontrol sunucunuza zamanlama ekleyin

Sunucu kodu, sulama döngüsünün zamanlaması ve toprak nem seviyelerinin değişmesini bekleme kontrolü eklemek için değiştirilebilir. Röle zamanlamasını kontrol eden sunucu mantığı şu şekildedir:

1. Telemetri mesajı alındı
1. Toprak nem seviyesini kontrol et
1. Eğer seviyeler uygunsa, hiçbir şey yapma. Eğer okuma çok yüksekse (toprak nemi çok düşük anlamına gelir):
    1. Röleyi açmak için bir komut gönder
    1. 5 saniye bekle
    1. Röleyi kapatmak için bir komut gönder
    1. Toprak nem seviyelerinin stabilize olması için 20 saniye bekle

Sulama döngüsü, telemetri mesajını almaktan toprak nem seviyelerini tekrar işlemeye hazır olmaya kadar geçen süreç, yaklaşık 25 saniye sürer. Toprak nem seviyelerini her 10 saniyede bir gönderiyoruz, bu nedenle bir mesaj alınırken sunucu toprak nem seviyelerinin stabilize olmasını bekliyor olabilir ve bu başka bir sulama döngüsünü başlatabilir.

Bu durumu aşmak için iki seçenek vardır:

* IoT cihaz kodunu yalnızca her dakika telemetri gönderecek şekilde değiştirin, böylece sulama döngüsü bir sonraki mesaj gönderilmeden önce tamamlanır
* Sulama döngüsü sırasında telemetri aboneliğini iptal et

Birinci seçenek büyük çiftlikler için her zaman iyi bir çözüm değildir. Çiftçi, sulama sırasında toprak nem seviyelerini daha sonra analiz etmek için yakalamak isteyebilir, örneğin çiftlikteki farklı alanlardaki su akışını bilmek ve daha hedefli sulama yapmak için. İkinci seçenek daha iyidir - kod, telemetriyi kullanamayacağı zaman görmezden geliyor, ancak telemetri diğer hizmetler için hala mevcut.

> 💁 IoT verileri yalnızca bir cihazdan bir hizmete gönderilmez, bunun yerine birçok cihaz bir aracıya veri gönderebilir ve birçok hizmet aracının verilerini dinleyebilir. Örneğin, bir hizmet toprak nem verilerini dinleyebilir ve daha sonra analiz için bir veritabanında depolayabilir. Başka bir hizmet aynı telemetriyi dinleyerek bir sulama sistemini kontrol edebilir.

### Görev - bitki kontrol sunucunuza zamanlama ekleyin

Sunucu kodunuzu röleyi 5 saniye çalıştıracak, ardından 20 saniye bekleyecek şekilde güncelleyin.

1. `soil-moisture-sensor-server` klasörünü VS Code'da açın (henüz açık değilse). Sanal ortamın etkin olduğundan emin olun.

1. `app.py` dosyasını açın.

1. Mevcut ithalatların altına aşağıdaki kodu ekleyin:

    ```python
    import threading
    ```

    Bu ifade, Python kütüphanelerinden `threading`'i içe aktarır. Threading, Python'un beklerken başka kodları çalıştırmasına olanak tanır.

1. Sunucu kodu tarafından alınan telemetri mesajlarını işleyen `handle_telemetry` işlevinden önce aşağıdaki kodu ekleyin:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Bu, röleyi ne kadar süre çalıştıracağını (`water_time`) ve ardından toprak nemini kontrol etmek için ne kadar süre bekleyeceğini (`wait_time`) tanımlar.

1. Bu kodun altına aşağıdaki kodu ekleyin:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Bu kod, röleyi kontrol etmek için MQTT üzerinden bir komut gönderen `send_relay_command` adlı bir işlev tanımlar. Telemetri bir sözlük olarak oluşturulur, ardından bir JSON dizesine dönüştürülür. `state` içine geçirilen değer, rölenin açık mı kapalı mı olması gerektiğini belirler.

1. `send_relay_code` işlevinden sonra aşağıdaki kodu ekleyin:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Bu, gerekli zamanlamaya göre röleyi kontrol eden bir işlev tanımlar. Telemetriyi sulama işlemi sırasında işlenmemesi için abonelikten çıkarak başlar. Ardından röleyi açmak için bir komut gönderir. Daha sonra `water_time` kadar bekler ve röleyi kapatmak için bir komut gönderir. Son olarak, toprak nem seviyelerinin stabilize olması için `wait_time` saniye bekler. Ardından telemetriye yeniden abone olur.

1. `handle_telemetry` işlevini aşağıdaki şekilde değiştirin:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Bu kod, toprak nem seviyesini kontrol eder. Eğer 450'den büyükse, toprak sulama gerektirir, bu nedenle `control_relay` işlevini çağırır. Bu işlev, arka planda çalışan ayrı bir thread üzerinde çalıştırılır.

1. IoT cihazınızın çalıştığından emin olun, ardından bu kodu çalıştırın. Toprak nem seviyelerini değiştirin ve rölede neler olduğunu gözlemleyin - röle 5 saniye açık kalmalı, ardından en az 20 saniye kapalı kalmalı ve yalnızca toprak nem seviyeleri yeterli değilse tekrar açılmalıdır.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Simüle edilmiş bir sulama sisteminde bunu test etmenin iyi bir yolu, kuru toprak kullanmak ve röle açıkken manuel olarak su dökmek, röle kapandığında dökmeyi durdurmaktır.

> 💁 Bu kodu [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing) klasöründe bulabilirsiniz.

> 💁 Gerçek bir sulama sistemi oluşturmak için bir pompa kullanmak istiyorsanız, bir [6V su pompası](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) ve bir [USB terminal güç kaynağı](https://www.adafruit.com/product/3628) kullanabilirsiniz. Pompa için güç bağlantısının röle üzerinden yapıldığından emin olun.

---

## 🚀 Zorluk

Sensörün aktüatörün sonuçlarını algılaması biraz zaman aldığı benzer bir sorun yaşayan başka IoT veya elektrikli cihazlar düşünebilir misiniz? Muhtemelen evinizde veya okulunuzda birkaç tane vardır.

* Hangi özellikleri ölçüyorlar?
* Özelliğin aktüatör kullanıldıktan sonra değişmesi ne kadar sürüyor?
* Özelliğin gereken değerin ötesine geçmesi kabul edilebilir mi?
* Gerekirse nasıl tekrar gereken değere döndürülebilir?

## Ders sonrası test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## İnceleme ve Kendi Kendine Çalışma

* Röleler hakkında daha fazla bilgi edinin, telefon santrallerindeki tarihsel kullanımları dahil, [röle Wikipedia sayfasında](https://wikipedia.org/wiki/Relay).

## Ödev

[Daha verimli bir sulama döngüsü oluşturun](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.