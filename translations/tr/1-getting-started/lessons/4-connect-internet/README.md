# Cihazınızı İnternete Bağlayın

![Bu dersin bir sketchnote özeti](../../../../../translated_images/tr/lesson-4.7344e074ea68fa54.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

Bu ders, [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) tarafından sunulan [Hello IoT serisinin](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) bir parçası olarak öğretildi. Ders, 1 saatlik bir ders ve dersin bazı bölümlerine daha derinlemesine dalarak soruları yanıtlayan 1 saatlik bir ofis saati olmak üzere iki video olarak sunuldu.

[![Ders 4: Cihazınızı İnternete Bağlayın](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Ders 4: Cihazınızı İnternete Bağlayın - Ofis Saatleri](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Videoları izlemek için yukarıdaki görsellere tıklayın

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Giriş

IoT'deki **I**, **Internet** anlamına gelir - IoT cihazlarının özelliklerini mümkün kılan bulut bağlantısı ve hizmetler. Bu özellikler, cihazlara bağlı sensörlerden ölçümler toplamaktan, aktüatörleri kontrol etmek için mesajlar göndermeye kadar uzanır. IoT cihazları genellikle standart bir iletişim protokolü kullanarak tek bir bulut IoT hizmetine bağlanır ve bu hizmet, IoT uygulamanızın geri kalanına bağlanır. Bu, verilerinizle akıllı kararlar almak için yapay zeka hizmetlerinden, kontrol veya raporlama için web uygulamalarına kadar her şeyi içerir.

> 🎓 Sensörlerden toplanan ve buluta gönderilen verilere telemetri denir.

IoT cihazları buluttan mesajlar alabilir. Bu mesajlar genellikle komutlar içerir - yani, cihaz içinde (örneğin yeniden başlatma veya yazılım güncelleme) veya bir aktüatör kullanarak (örneğin bir ışığı açma) bir eylem gerçekleştirme talimatlarıdır.

Bu ders, IoT cihazlarının buluta bağlanmak için kullanabileceği bazı iletişim protokollerini ve gönderebilecekleri veya alabilecekleri veri türlerini tanıtır. Ayrıca, hem bunlarla pratik yapacak hem de gece lambanıza internet kontrolü ekleyerek LED kontrol mantığını yerel olarak çalışan 'sunucu' koduna taşıyacaksınız.

Bu derste şunları ele alacağız:

* [İletişim protokolleri](../../../../../1-getting-started/lessons/4-connect-internet)
* [Mesaj Kuyruğu Telemetri Taşıma (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetri](../../../../../1-getting-started/lessons/4-connect-internet)
* [Komutlar](../../../../../1-getting-started/lessons/4-connect-internet)

## İletişim Protokolleri

IoT cihazlarının İnternet ile iletişim kurmak için kullandığı birçok popüler iletişim protokolü vardır. En popüler olanlar, bir tür aracı üzerinden yayınla/abone ol mesajlaşmasına dayanır. IoT cihazları aracıya bağlanır, telemetri yayınlar ve komutlara abone olur. Bulut hizmetleri de aracıya bağlanır, tüm telemetri mesajlarına abone olur ve belirli cihazlara veya cihaz gruplarına komutlar yayınlar.

![IoT cihazları bir aracıya bağlanır, telemetri yayınlar ve komutlara abone olur. Bulut hizmetleri aracıya bağlanır, tüm telemetri mesajlarına abone olur ve belirli cihazlara komut gönderir.](../../../../../translated_images/tr/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT, IoT cihazları için en popüler iletişim protokolüdür ve bu derste ele alınacaktır. Diğer protokoller arasında AMQP ve HTTP/HTTPS bulunur.

## Mesaj Kuyruğu Telemetri Taşıma (MQTT)

[MQTT](http://mqtt.org), cihazlar arasında mesaj gönderebilen hafif, açık standart bir mesajlaşma protokolüdür. 1999 yılında petrol boru hatlarını izlemek için tasarlanmış ve 15 yıl sonra IBM tarafından açık bir standart olarak yayınlanmıştır.

MQTT, tek bir aracı ve birden fazla istemciye sahiptir. Tüm istemciler aracıya bağlanır ve aracı, mesajları ilgili istemcilere yönlendirir. Mesajlar, bireysel bir istemciye doğrudan gönderilmek yerine adlandırılmış konular kullanılarak yönlendirilir. Bir istemci bir konuya yayın yapabilir ve o konuya abone olan tüm istemciler mesajı alır.

![IoT cihazı, /telemetry konusunda telemetri yayınlıyor ve bulut hizmeti bu konuya abone oluyor](../../../../../translated_images/tr/mqtt.cbf7f21d9adc3e17.webp)

✅ Araştırma yapın. Çok sayıda IoT cihazınız varsa, MQTT aracınızın tüm mesajları işleyebilmesini nasıl sağlayabilirsiniz?

### IoT Cihazınızı MQTT'ye Bağlayın

Gece lambanıza internet kontrolü eklemenin ilk adımı, onu bir MQTT aracısına bağlamaktır.

#### Görev

Cihazınızı bir MQTT aracısına bağlayın.

Bu dersin bu bölümünde, IoT gece lambanızı internete bağlayarak uzaktan kontrol edilmesini sağlayacaksınız. Dersin ilerleyen bölümlerinde, IoT cihazınız bir MQTT aracısına ışık seviyesiyle ilgili bir telemetri mesajı gönderecek ve bu mesaj, yazacağınız bir sunucu kodu tarafından alınacaktır. Bu kod, ışık seviyesini kontrol edecek ve LED'i açıp kapatmasını söyleyen bir komut mesajı gönderecektir.

Böyle bir kurulumun gerçek dünya kullanım durumu, bir stadyum gibi çok sayıda ışığın bulunduğu bir yerde, ışıkları açmadan önce birden fazla ışık sensöründen veri toplamaktır. Bu, yalnızca bir sensör bulutlar veya bir kuş tarafından kapatılmış olsa bile diğer sensörlerin yeterli ışık algıladığı durumlarda ışıkların açılmasını engelleyebilir.

✅ Hangi durumlar, komut göndermeden önce birden fazla sensörden veri değerlendirilmesini gerektirir?

Bu ödevin bir parçası olarak bir MQTT aracı kurmanın karmaşıklıklarıyla uğraşmak yerine, [Eclipse Mosquitto](https://www.mosquitto.org) adlı açık kaynaklı bir MQTT aracısını çalıştıran bir genel test sunucusunu kullanabilirsiniz. Bu test aracı, [test.mosquitto.org](https://test.mosquitto.org) adresinde herkese açık olarak mevcuttur ve bir hesap oluşturulmasını gerektirmez, bu da MQTT istemcileri ve sunucularını test etmek için harika bir araçtır.

> 💁 Bu test aracı herkese açıktır ve güvenli değildir. Yayınladığınız şeyleri başkaları dinleyebilir, bu nedenle özel tutulması gereken verilerle kullanılmamalıdır.

![Görev akış şeması: ışık seviyeleri okunur ve kontrol edilir, LED kontrol edilir](../../../../../translated_images/tr/assignment-1-internet-flow.3256feab5f052fd2.webp)

Cihazınızı MQTT aracısına bağlamak için aşağıdaki ilgili adımı izleyin:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer-mqtt.md)

### MQTT'ye Daha Derin Bir Bakış

Konular bir hiyerarşiye sahip olabilir ve istemciler, joker karakterler kullanarak hiyerarşinin farklı seviyelerine abone olabilir. Örneğin, sıcaklık telemetri mesajlarını `/telemetry/temperature` konusuna ve nem mesajlarını `/telemetry/humidity` konusuna gönderebilir, ardından bulut uygulamanızda hem sıcaklık hem de nem telemetri mesajlarını almak için `/telemetry/*` konusuna abone olabilirsiniz.

Mesajlar, alınma garantisini belirleyen bir hizmet kalitesi (QoS) ile gönderilebilir.

* En fazla bir kez - mesaj yalnızca bir kez gönderilir ve istemci ile aracı, teslimatı onaylamak için ek adımlar atmaz (gönder ve unut).
* En az bir kez - mesaj, onay alınana kadar gönderici tarafından birden çok kez yeniden gönderilir (onaylı teslimat).
* Tam olarak bir kez - gönderici ve alıcı, mesajın yalnızca bir kopyasının alınmasını sağlamak için iki seviyeli bir el sıkışma sürecine girer (garantili teslimat).

✅ Hangi durumlar, gönder ve unut mesajı yerine garantili bir teslimat mesajı gerektirir?

MQTT'nin adı Mesaj Kuyruğu (MQ) olsa da, aslında mesaj kuyruklarını desteklemez. Bu, bir istemci bağlantısı kesilip yeniden bağlanırsa, bağlantı kesilmesi sırasında gönderilen mesajları almayacağı anlamına gelir. Ancak, QoS sürecini kullanarak işlemeye başladığı mesajlar hariç. Mesajlar, bir retained (saklanan) bayrağı ile gönderilebilir. Bu bayrak ayarlandığında, MQTT aracı, bu bayrakla gönderilen bir konudaki son mesajı saklar ve daha sonra o konuya abone olan istemcilere gönderir. Bu şekilde, istemciler her zaman en son mesajı alır.

MQTT ayrıca, mesajlar arasındaki uzun boşluklar sırasında bağlantının hala canlı olup olmadığını kontrol eden bir keep alive (canlı tutma) işlevini destekler.

> 🦟 [Eclipse Foundation'dan Mosquitto](https://mosquitto.org), MQTT ile denemeler yapmak için kendiniz çalıştırabileceğiniz ücretsiz bir MQTT aracı sunar. Ayrıca, kodunuzu test etmek için kullanabileceğiniz bir genel MQTT aracı [test.mosquitto.org](https://test.mosquitto.org) adresinde barındırılmaktadır.

MQTT bağlantıları herkese açık ve açık olabilir veya kullanıcı adları ve şifreler ya da sertifikalar kullanılarak şifrelenip güvenli hale getirilebilir.

> 💁 MQTT, HTTP ile aynı temel ağ protokolü olan TCP/IP üzerinden iletişim kurar, ancak farklı bir port üzerinden. Ayrıca, web tarayıcısında çalışan web uygulamalarıyla iletişim kurmak veya güvenlik duvarları ya da diğer ağ kuralları standart MQTT bağlantılarını engellediğinde MQTT'yi websockets üzerinden kullanabilirsiniz.

## Telemetri

Telemetri kelimesi, uzaktan ölçüm anlamına gelen Yunanca köklerden türetilmiştir. Telemetri, sensörlerden veri toplama ve bu verileri buluta gönderme işlemidir.

> 💁 İlk telemetri cihazlarından biri, 1874 yılında Fransa'da icat edilmiştir ve Mont Blanc'dan Paris'e gerçek zamanlı hava durumu ve kar derinliklerini göndermiştir. O dönemde kablosuz teknolojiler mevcut olmadığından fiziksel kablolar kullanılmıştır.

1. Dersteki akıllı termostat örneğine geri dönelim.

![Birden fazla oda sensörü kullanan internet bağlantılı bir termostat](../../../../../translated_images/tr/telemetry.21e5d8b97649d2eb.webp)

Termostat, telemetri toplamak için sıcaklık sensörlerine sahiptir. Muhtemelen bir sıcaklık sensörü yerleşik olarak bulunur ve birden fazla harici sıcaklık sensörüne [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE) gibi bir kablosuz protokol üzerinden bağlanabilir.

Gönderebileceği telemetri verilerine bir örnek:

| Ad | Değer | Açıklama |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Termostatın yerleşik sıcaklık sensörü tarafından ölçülen sıcaklık |
| `livingroom_temperature` | 19°C | `livingroom` olarak adlandırılmış bir uzaktan sıcaklık sensörü tarafından ölçülen sıcaklık |
| `bedroom_temperature` | 21°C | `bedroom` olarak adlandırılmış bir uzaktan sıcaklık sensörü tarafından ölçülen sıcaklık |

Bulut hizmeti, bu telemetri verilerini kullanarak ısıtmayı kontrol etmek için hangi komutların gönderileceği konusunda kararlar alabilir.

### IoT Cihazınızdan Telemetri Gönderin

Gece lambanıza internet kontrolü eklemenin bir sonraki adımı, ışık seviyesi telemetrisini bir telemetri konusu üzerinden MQTT aracısına göndermektir.

#### Görev - IoT cihazınızdan telemetri gönderin

Işık seviyesi telemetrisini MQTT aracısına gönderin.

Veriler, anahtar/değer çiftlerini kullanarak metin halinde veri kodlamak için bir standart olan JSON (JavaScript Object Notation) olarak kodlanmış şekilde gönderilir.

✅ JSON hakkında daha önce bilgi sahibi değilseniz, [JSON.org dokümantasyonu](https://www.json.org/) üzerinden daha fazla bilgi edinebilirsiniz.

Cihazınızdan MQTT aracısına telemetri göndermek için aşağıdaki ilgili adımı izleyin:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer-telemetry.md)

### MQTT Aracısından Telemetri Alın

Telemetri gönderiyorsanız, diğer uçta bunu dinleyen bir şeyin olması gerekir. Işık seviyesi telemetrisinin, verileri işlemek için bir şey tarafından dinlenmesi gerekir. Bu 'sunucu' kodu, daha büyük bir IoT uygulamasının bir parçası olarak bir bulut hizmetine dağıtacağınız türden bir koddur, ancak burada bu kodu bilgisayarınızda (veya doğrudan Raspberry Pi'nizde çalışıyorsanız Pi'nizde) çalıştıracaksınız. Sunucu kodu, MQTT üzerinden ışık seviyeleriyle ilgili telemetri mesajlarını dinleyen bir Python uygulamasından oluşur. Dersin ilerleyen bölümlerinde, LED'i açıp kapatma talimatları içeren bir komut mesajıyla yanıt vermesini sağlayacaksınız.

✅ Araştırma yapın: Eğer bir dinleyici yoksa MQTT mesajlarına ne olur?

#### Python ve VS Code'u Yükleyin

Eğer bilgisayarınızda Python ve VS Code yüklü değilse, sunucu kodunu yazmak için her ikisini de yüklemeniz gerekecek. Eğer sanal bir IoT cihazı kullanıyorsanız veya Raspberry Pi'nizde çalışıyorsanız, bu adımı atlayabilirsiniz çünkü bunlar zaten yüklü ve yapılandırılmış olmalıdır.

##### Görev - Python ve VS Code'u yükleyin

Python ve VS Code'u yükleyin.

1. Python'u yükleyin. En son Python sürümünü yüklemek için [Python indirme sayfasına](https://www.python.org/downloads/) başvurun.

2. Visual Studio Code (VS Code) yükleyin. Bu, Python'da sanal cihaz kodunuzu yazmak için kullanacağınız editördür. VS Code'u yüklemek için [VS Code dokümantasyonuna](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) başvurun.
💁 Bu dersler için tercih ettiğiniz bir Python IDE veya editörünü kullanmakta özgürsünüz, ancak dersler VS Code kullanımı temel alınarak talimatlar verecektir.
1. VS Code Pylance uzantısını yükleyin. Bu, VS Code için Python dil desteği sağlayan bir uzantıdır. Bu uzantıyı VS Code'a nasıl yükleyeceğinizle ilgili talimatlar için [Pylance uzantısı dokümantasyonuna](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) bakın.

#### Bir Python sanal ortamı yapılandırın

Python'un güçlü özelliklerinden biri, [pip paketlerini](https://pypi.org) yükleyebilme yeteneğidir - bunlar, başkaları tarafından yazılmış ve internete yüklenmiş kod paketleridir. Bir pip paketini bilgisayarınıza tek bir komutla yükleyebilir ve ardından bu paketi kodunuzda kullanabilirsiniz. MQTT üzerinden iletişim kurmak için bir paket yüklemek için pip kullanacaksınız.

Varsayılan olarak bir paket yüklediğinizde, bu paket bilgisayarınızın her yerinde kullanılabilir hale gelir ve bu durum paket sürümleriyle ilgili sorunlara yol açabilir - örneğin, bir uygulama bir paketin bir sürümüne bağlıyken, başka bir uygulama için yeni bir sürüm yüklediğinizde bu sürüm bozulabilir. Bu sorunu aşmak için, [Python sanal ortamı](https://docs.python.org/3/library/venv.html) kullanabilirsiniz; bu, Python'un özel bir klasördeki bir kopyasıdır ve pip paketlerini yüklediğinizde yalnızca o klasöre yüklenir.

##### Görev - Bir Python sanal ortamı yapılandırın

Bir Python sanal ortamı yapılandırın ve MQTT pip paketlerini yükleyin.

1. Terminalinizden veya komut satırınızdan, yeni bir dizin oluşturmak ve bu dizine gitmek için aşağıdaki komutları çalıştırın:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Şimdi `.venv` klasöründe bir sanal ortam oluşturmak için aşağıdaki komutu çalıştırın:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Sanal ortamı oluşturmak için `python3`'ü açıkça çağırmanız gerekir, çünkü Python 2'nin yanı sıra Python 3'ü de yüklemiş olabilirsiniz (en son sürüm). Python 2 yüklüyse, `python` komutunu çağırmak Python 2'yi kullanacaktır.

1. Sanal ortamı etkinleştirin:

    * Windows'ta:
        * Komut İstemi veya Windows Terminal üzerinden Komut İstemi kullanıyorsanız, şu komutu çalıştırın:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell kullanıyorsanız, şu komutu çalıştırın:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS veya Linux'ta şu komutu çalıştırın:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Bu komutlar, sanal ortamı oluşturmak için komutu çalıştırdığınız aynı konumdan çalıştırılmalıdır. `.venv` klasörüne asla gitmeniz gerekmez; her zaman etkinleştirme komutunu ve paketleri yüklemek veya kod çalıştırmak için komutları sanal ortamı oluşturduğunuz klasörden çalıştırmalısınız.

1. Sanal ortam etkinleştirildikten sonra, varsayılan `python` komutu, sanal ortamı oluşturmak için kullanılan Python sürümünü çalıştırır. Sürümü almak için aşağıdaki komutu çalıştırın:

    ```sh
    python --version
    ```

    Çıktı aşağıdakine benzer olacaktır:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Python sürümünüz farklı olabilir - sürüm 3.6 veya daha yüksek olduğu sürece sorun yok. Değilse, bu klasörü silin, daha yeni bir Python sürümü yükleyin ve tekrar deneyin.

1. [Paho-MQTT](https://pypi.org/project/paho-mqtt/) için pip paketini yüklemek için aşağıdaki komutları çalıştırın. Bu, popüler bir MQTT kütüphanesidir.

    ```sh
    pip install paho-mqtt
    ```

    Bu pip paketi yalnızca sanal ortamda yüklenecek ve bunun dışında kullanılamayacaktır.

#### Sunucu kodunu yazın

Artık sunucu kodu Python'da yazılabilir.

##### Görev - Sunucu kodunu yazın

Sunucu kodunu yazın.

1. Sanal ortamın içinde, terminalinizden veya komut satırınızdan aşağıdaki komutları çalıştırarak `app.py` adlı bir Python dosyası oluşturun:

    * Windows'ta şu komutu çalıştırın:

        ```cmd
        type nul > app.py
        ```

    * macOS veya Linux'ta şu komutu çalıştırın:

        ```cmd
        touch app.py
        ```

1. Mevcut klasörü VS Code'da açın:

    ```sh
    code .
    ```

1. VS Code başlatıldığında, Python sanal ortamını etkinleştirecektir. Bu, alt durum çubuğunda rapor edilecektir:

    ![VS Code seçilen sanal ortamı gösteriyor](../../../../../translated_images/tr/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. VS Code Terminali, VS Code başlatıldığında zaten çalışıyorsa, sanal ortam terminalde etkinleştirilmez. En kolay çözüm, **Aktif terminal örneğini sonlandır** düğmesini kullanarak terminali kapatmaktır:

    ![VS Code Aktif terminal örneğini sonlandır düğmesi](../../../../../translated_images/tr/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. *Terminal -> Yeni Terminal* seçeneğini seçerek veya `` CTRL+` `` tuşlarına basarak yeni bir VS Code Terminali başlatın. Yeni terminal sanal ortamı yükleyecek ve bu, terminalde görünecektir. Sanal ortamın adı (`.venv`) istemde de görünecektir:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. VS Code gezgininden `app.py` dosyasını açın ve aşağıdaki kodu ekleyin:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    6. satırdaki `<ID>`'yi cihaz kodunuzu oluştururken kullandığınız benzersiz kimlikle değiştirin.

    ⚠️ Bu **mutlaka** cihazınızda kullandığınız kimlikle aynı olmalıdır, aksi takdirde sunucu kodu doğru konuya abone olmaz veya yayın yapmaz.

    Bu kod, benzersiz bir adla bir MQTT istemcisi oluşturur ve *test.mosquitto.org* broker'ına bağlanır. Daha sonra, herhangi bir abone olunan konuda mesajları dinleyen bir arka plan iş parçacığında çalışan bir işlem döngüsü başlatır.

    İstemci, telemetri konusundaki mesajlara abone olur ve bir mesaj alındığında çağrılan bir işlev tanımlar. Bir telemetri mesajı alındığında, `handle_telemetry` işlevi çağrılır ve alınan mesaj konsola yazdırılır.

    Son olarak, sonsuz bir döngü uygulamanın çalışmasını sürdürür. MQTT istemcisi, bir arka plan iş parçacığında mesajları dinler ve ana uygulama çalıştığı sürece çalışır.

1. Python uygulamanızı çalıştırmak için VS Code terminalinden aşağıdaki komutu çalıştırın:

    ```sh
    python app.py
    ```

    Uygulama, IoT cihazından gelen mesajları dinlemeye başlayacaktır.

1. Cihazınızın çalıştığından ve telemetri mesajları gönderdiğinden emin olun. Fiziksel veya sanal cihazınızdaki ışık seviyelerini ayarlayın. Alınan mesajlar terminale yazdırılacaktır.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Nightlight sanal ortamındaki app.py dosyasının, nightlight-server sanal ortamındaki app.py dosyasının gönderilen mesajları alabilmesi için çalışıyor olması gerekir.

> 💁 Bu kodu [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server) klasöründe bulabilirsiniz.

### Telemetri ne sıklıkla gönderilmeli?

Telemetri ile ilgili önemli bir husus, verilerin ne sıklıkla ölçülüp gönderileceğidir. Cevap - duruma bağlıdır. Sık ölçüm yaparsanız değişikliklere daha hızlı yanıt verebilirsiniz, ancak daha fazla güç, daha fazla bant genişliği kullanır, daha fazla veri üretir ve işlemek için daha fazla bulut kaynağına ihtiyaç duyarsınız. Yeterince sık ölçüm yapmanız gerekir, ancak çok sık olmamalıdır.

Bir termostat için, birkaç dakikada bir ölçüm yapmak muhtemelen yeterlidir çünkü sıcaklıklar bu kadar sık değişmez. Günde yalnızca bir kez ölçüm yaparsanız, güneşli bir günün ortasında gece sıcaklıkları için evinizi ısıtabilirsiniz, ancak her saniye ölçüm yaparsanız, gereksiz yere binlerce sıcaklık ölçümü yaparsınız ve bu, kullanıcıların internet hızını ve bant genişliğini tüketir (sınırlı bant genişliği planları olan kişiler için bir sorun), daha fazla güç kullanır (uzaktan sensörler gibi pil ile çalışan cihazlar için bir sorun olabilir) ve sağlayıcıların bulut bilişim kaynaklarının maliyetini artırır.

Bir fabrikadaki bir makine parçasını izliyorsanız ve bu parça arızalanırsa felaketle sonuçlanabilecek hasarlara ve milyonlarca dolarlık gelir kaybına neden olabilecekse, saniyede birden fazla ölçüm yapmak gerekebilir. Bant genişliğini boşa harcamaktansa, bir makinenin durdurulması ve kırılmadan önce tamir edilmesi gerektiğini gösteren telemetriyi kaçırmamak daha iyidir.

> 💁 Bu durumda, internet bağımlılığını azaltmak için telemetriyi önce işlemek için bir uç cihaz kullanmayı düşünebilirsiniz.

### Bağlantı kaybı

İnternet bağlantıları güvenilir olmayabilir ve kesintiler yaygındır. Bu durumda bir IoT cihazı ne yapmalıdır - verileri kaybetmeli mi yoksa bağlantı yeniden sağlanana kadar saklamalı mı? Yine, cevap duruma bağlıdır.

Bir termostat için, yeni bir sıcaklık ölçümü alındığında veriler muhtemelen kaybedilebilir. Isıtma sistemi, 20 dakika önce sıcaklığın 20.5°C olduğunu umursamaz; şu anki sıcaklık 19°C ise, ısıtmanın açık mı kapalı mı olması gerektiğini belirleyen budur.

Bir makine için verileri saklamak isteyebilirsiniz, özellikle de eğilimleri izlemek için kullanılıyorsa. Bazı makine öğrenimi modelleri, belirli bir zaman dilimindeki (örneğin son bir saat) verileri inceleyerek ve anormal verileri tespit ederek veri akışlarındaki anormallikleri algılayabilir. Bu genellikle kestirimci bakım için kullanılır; bir şeyin yakında kırılabileceğini gösteren işaretleri arar, böylece bu gerçekleşmeden önce tamir edebilir veya değiştirebilirsiniz. Bir makine için her bir telemetri verisinin gönderilmesini isteyebilirsiniz, böylece internet kesintisi sırasında üretilen tüm telemetri, IoT cihazı yeniden bağlanabildiğinde gönderilir.

IoT cihaz tasarımcıları ayrıca, IoT cihazının bir internet kesintisi veya konum nedeniyle sinyal kaybı sırasında kullanılabilir olup olmadığını da düşünmelidir. Akıllı bir termostat, bir kesinti nedeniyle telemetriyi buluta gönderemiyorsa, ısıtmayı kontrol etmek için bazı sınırlı kararlar alabilmelidir.

[![Bu Ferrari, yeraltında hücresel sinyal olmadığı bir yerde güncellenmeye çalışıldığı için kullanılamaz hale geldi](../../../../../translated_images/tr/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

MQTT'nin bağlantı kaybını ele alabilmesi için, cihaz ve sunucu kodu, mesaj tesliminin gerektiğinde sağlanmasından sorumlu olmalıdır. Örneğin, gönderilen tüm mesajların bir yanıt konusu üzerinde ek mesajlarla yanıtlanmasını gerektirerek ve yanıtlanmazsa, bunları manuel olarak sıraya alarak daha sonra yeniden oynatılmasını sağlayabilir.

## Komutlar

Komutlar, buluttan bir cihaza gönderilen ve bir şey yapmasını talep eden mesajlardır. Çoğu zaman bu, bir aktüatör aracılığıyla bir tür çıktı vermeyi içerir, ancak cihazın kendisi için bir talimat da olabilir, örneğin yeniden başlatmak veya ek telemetri toplamak ve bunu komuta yanıt olarak geri göndermek.

![Bir internet bağlantılı termostatın ısıtmayı açma komutunu alması](../../../../../translated_images/tr/commands.d6c06bbbb3a02cce.webp)

Bir termostat, buluttan ısıtmayı açma komutunu alabilir. Tüm sensörlerden gelen telemetri verilerine dayanarak, bulut hizmeti ısıtmanın açık olması gerektiğine karar verdiyse, ilgili komutu gönderir.

### MQTT broker'a komut gönderin

İnternet kontrollü gece lambamız için bir sonraki adım, sunucu kodunun algıladığı ışık seviyelerine göre ışığı kontrol etmek için IoT cihazına bir komut göndermesidir.

1. VS Code'da sunucu kodunu açın.

1. Komutları hangi konuya göndereceğinizi tanımlamak için `client_telemetry_topic` tanımından sonra aşağıdaki satırı ekleyin:

    ```python
    server_command_topic = id + '/commands'
    ```

1. `handle_telemetry` işlevinin sonuna aşağıdaki kodu ekleyin:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Bu, ışığın 300'den az olup olmamasına bağlı olarak `led_on` değerini true veya false olarak ayarlayan bir JSON mesajını komut konusuna gönderir. Işık 300'den azsa, LED'i açmasını talep etmek için true gönderilir.

1. Daha önce olduğu gibi kodu çalıştırın.

1. Fiziksel veya sanal cihazınızdaki ışık seviyelerini ayarlayın. Alınan mesajlar ve gönderilen komutlar terminale yazılacaktır:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetri ve komutlar tek bir konu üzerinde gönderiliyor. Bu, birden fazla cihazdan gelen telemetri verilerinin aynı telemetri konusunda görüneceği ve birden fazla cihaza gönderilen komutların aynı komut konusunda görüneceği anlamına gelir. Belirli bir cihaza komut göndermek istiyorsanız, `/commands/device1`, `/commands/device2` gibi benzersiz cihaz kimlikleriyle adlandırılmış birden fazla konu kullanabilirsiniz. Bu şekilde bir cihaz, yalnızca o cihaza yönelik mesajları dinleyebilir.

> 💁 Bu kodu [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server) klasöründe bulabilirsiniz.

### IoT cihazında komutları işleyin

Artık sunucudan komutlar gönderildiğine göre, MQTT broker'dan komutları dinlemek ve LED'i kontrol etmek için IoT cihazına kod ekleyebilirsiniz.

MQTT broker'dan komutları dinlemek için aşağıdaki ilgili adımı izleyin:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer-commands.md)

Bu kod yazılıp çalıştırıldıktan sonra ışık seviyelerini değiştirmeyi deneyin. Sunucu ve cihazdan gelen çıktıyı izleyin ve ışık seviyelerini değiştirdiğinizde LED'i gözlemleyin.

### Bağlantı kaybı

Bir IoT cihazı çevrimdışıysa, bir bulut hizmeti bu cihaza bir komut göndermesi gerektiğinde ne yapmalıdır? Yine, cevap duruma bağlıdır.

Eğer en son komut bir önceki komutu geçersiz kılıyorsa, önceki komutlar muhtemelen göz ardı edilebilir. Eğer bir bulut hizmeti ısıtmayı açma komutu gönderir, ardından kapatma komutu gönderirse, açma komutu göz ardı edilebilir ve yeniden gönderilmez.

Eğer komutların sırayla işlenmesi gerekiyorsa, örneğin bir robot kolunu yukarı hareket ettirip ardından bir tutucuyu kapatmak gibi, bu komutlar bağlantı yeniden sağlandığında sırayla gönderilmelidir.

✅ Cihaz veya sunucu kodu, MQTT üzerinden komutların her zaman sırayla gönderilmesini ve işlenmesini nasıl sağlayabilir?

---

## 🚀 Meydan Okuma

Son üç dersteki meydan okuma, evinizde, okulunuzda veya iş yerinizde bulunan IoT cihazlarını listelemek, bunların mikrodenetleyiciler mi yoksa tek kartlı bilgisayarlar mı (veya her ikisinin bir karışımı mı) olduğunu belirlemek ve hangi sensörler ve aktüatörler kullandıklarını düşünmekti.
Bu cihazlar için, gönderdikleri veya aldıkları mesajlar hakkında düşünün. Hangi telemetri verilerini gönderiyorlar? Hangi mesajları veya komutları alabilirler? Sizce güvenli mi?

## Ders Sonrası Test

[Ders sonrası testi](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Gözden Geçirme ve Kendi Kendine Çalışma

MQTT hakkında daha fazla bilgi edinmek için [MQTT Wikipedia sayfasını](https://wikipedia.org/wiki/MQTT) okuyun.

Kendi başınıza bir MQTT broker çalıştırmayı deneyin. [Mosquitto](https://www.mosquitto.org) kullanarak bir broker çalıştırabilir ve IoT cihazınız ile sunucu kodunuzdan bağlantı kurabilirsiniz.

> 💁 İpucu - Varsayılan olarak Mosquitto anonim bağlantılara (yani kullanıcı adı ve şifre olmadan bağlantı kurmaya) izin vermez ve çalıştığı bilgisayarın dışından bağlantılara izin vermez.  
> Bunu, aşağıdaki gibi bir [`mosquitto.conf` yapılandırma dosyası](https://www.mosquitto.org/man/mosquitto-conf-5.html) ile düzeltebilirsiniz:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Ödev

[MQTT'yi diğer iletişim protokolleriyle karşılaştırın ve farklılıklarını inceleyin](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.