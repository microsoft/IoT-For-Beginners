<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-28T03:16:01+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "tr"
}
-->
# GPS Verilerini Okuma - Sanal IoT Donanımı

Bu dersin bu bölümünde, sanal IoT cihazınıza bir GPS sensörü ekleyecek ve ondan değerler okuyacaksınız.

## Sanal Donanım

Sanal IoT cihazı, bir seri port üzerinden UART ile erişilebilen simüle edilmiş bir GPS sensörü kullanacaktır.

Fiziksel bir GPS sensörü, GPS uydularından gelen radyo dalgalarını almak için bir antene sahip olacak ve GPS sinyallerini GPS verilerine dönüştürecektir. Sanal versiyon, bir enlem ve boylam ayarlamanıza, ham NMEA cümleleri göndermenize veya sırasıyla döndürülebilecek birden fazla konum içeren bir GPX dosyası yüklemenize olanak tanıyarak bunu simüle eder.

> 🎓 NMEA cümleleri bu dersin ilerleyen bölümlerinde ele alınacaktır.

### Sensörü CounterFit'e Ekleme

Sanal bir GPS sensörü kullanmak için, CounterFit uygulamasına bir tane eklemeniz gerekir.

#### Görev - Sensörü CounterFit'e ekleyin

GPS sensörünü CounterFit uygulamasına ekleyin.

1. Bilgisayarınızda `gps-sensor` adlı bir klasörde tek bir dosya olan `app.py` ile yeni bir Python uygulaması oluşturun, bir Python sanal ortamı oluşturun ve CounterFit pip paketlerini ekleyin.

    > ⚠️ Gerekirse [ders 1'de CounterFit Python projesi oluşturma ve ayarlama talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md) başvurabilirsiniz.

1. Seri bağlantı üzerinden UART tabanlı sensörlerle iletişim kurabilen bir CounterFit shim yüklemek için ek bir Pip paketi yükleyin. Bu işlemi, sanal ortamın etkin olduğu bir terminalden yaptığınızdan emin olun.

    ```sh
    pip install counterfit-shims-serial
    ```

1. CounterFit web uygulamasının çalıştığından emin olun.

1. Bir GPS sensörü oluşturun:

    1. *Sensors* panelindeki *Create sensor* kutusunda, *Sensor type* açılır kutusunu açın ve *UART GPS* seçeneğini seçin.

    1. *Port* ayarını */dev/ttyAMA0* olarak bırakın.

    1. **Add** düğmesini seçerek `/dev/ttyAMA0` portunda GPS sensörünü oluşturun.

    ![GPS sensör ayarları](../../../../../translated_images/tr/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    GPS sensörü oluşturulacak ve sensörler listesinde görünecektir.

    ![Oluşturulan GPS sensörü](../../../../../translated_images/tr/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## GPS Sensörünü Programlama

Sanal IoT cihazı artık sanal GPS sensörünü kullanacak şekilde programlanabilir.

### Görev - GPS sensörünü programlayın

GPS sensörü uygulamasını programlayın.

1. `gps-sensor` uygulamasının VS Code'da açık olduğundan emin olun.

1. `app.py` dosyasını açın.

1. Uygulamayı CounterFit'e bağlamak için `app.py` dosyasının en üstüne aşağıdaki kodu ekleyin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Bunun altına, CounterFit seri port kütüphanesi dahil olmak üzere bazı gerekli kütüphaneleri içe aktarmak için aşağıdaki kodu ekleyin:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Bu kod, `counterfit_shims_serial` Pip paketinden `serial` modülünü içe aktarır. Daha sonra sanal GPS sensörünün UART portu için kullandığı `/dev/ttyAMA0` seri portuna bağlanır.

1. Bunun altına, seri porttan veri okumak ve değerleri konsola yazdırmak için aşağıdaki kodu ekleyin:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    `print_gps_data` adlı bir fonksiyon tanımlanır ve kendisine iletilen satırı konsola yazdırır.

    Daha sonra kod, her döngüde seri porttan mümkün olduğunca çok metin satırı okuyarak sonsuza kadar döner. Her satır için `print_gps_data` fonksiyonunu çağırır.

    Tüm veriler okunduktan sonra döngü 1 saniye uyur ve tekrar denemeye başlar.

1. Bu kodu çalıştırın, CounterFit uygulamasının çalışmaya devam etmesi için CounterFit uygulamasını çalıştırdığınız terminalden farklı bir terminal kullandığınızdan emin olun.

1. CounterFit uygulamasından GPS sensörünün değerini değiştirin. Bunu şu yöntemlerden biriyle yapabilirsiniz:

    * **Source**'u `Lat/Lon` olarak ayarlayın ve GPS sabitlemesi için kullanılan açık bir enlem, boylam ve uydu sayısı ayarlayın. Bu değer yalnızca bir kez gönderilecektir, bu nedenle verilerin her saniye tekrarlanması için **Repeat** kutusunu işaretleyin.

      ![Lat/Lon seçili GPS sensörü](../../../../../translated_images/tr/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * **Source**'u `NMEA` olarak ayarlayın ve metin kutusuna bazı NMEA cümleleri ekleyin. Tüm bu değerler gönderilecek ve her yeni GGA (konum sabitleme) cümlesi okunmadan önce 1 saniyelik bir gecikme olacaktır.

      ![NMEA cümleleri ayarlanmış GPS sensörü](../../../../../translated_images/tr/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Bu cümleleri oluşturmak için [nmeagen.org](https://www.nmeagen.org) gibi bir araç kullanabilirsiniz. Bu değerler yalnızca bir kez gönderilecektir, bu nedenle tümü gönderildikten bir saniye sonra verilerin tekrarlanması için **Repeat** kutusunu işaretleyin.

    * **Source**'u GPX dosyası olarak ayarlayın ve bir GPX dosyası yükleyin. Bu dosyaları [AllTrails](https://www.alltrails.com/) gibi popüler haritalama ve yürüyüş sitelerinden indirebilirsiniz. Bu dosyalar bir iz olarak birden fazla GPS konumu içerir ve GPS sensörü her yeni konumu 1 saniyelik aralıklarla döndürecektir.

      ![GPX dosyası ayarlanmış GPS sensörü](../../../../../translated_images/tr/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Bu değerler yalnızca bir kez gönderilecektir, bu nedenle tümü gönderildikten bir saniye sonra verilerin tekrarlanması için **Repeat** kutusunu işaretleyin.

    GPS ayarlarını yapılandırdıktan sonra, bu değerleri sensöre uygulamak için **Set** düğmesini seçin.

1. GPS sensöründen gelen ham çıktıyı göreceksiniz, örneğin:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Bu kodu [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device) klasöründe bulabilirsiniz.

😀 GPS sensörü programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.