<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-28T04:13:52+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "tr"
}
-->
# Sıcaklık Ölçümü - Sanal IoT Donanımı

Bu dersin bu bölümünde, sanal IoT cihazınıza bir sıcaklık sensörü ekleyeceksiniz.

## Sanal Donanım

Sanal IoT cihazı, simüle edilmiş bir Grove Dijital Nem ve Sıcaklık sensörü kullanacaktır. Bu, bu laboratuvarı fiziksel bir Grove DHT11 sensörü ile bir Raspberry Pi kullanmakla aynı hale getirir.

Sensör, bir **sıcaklık sensörü** ile bir **nem sensörünü** birleştirir, ancak bu laboratuvarda yalnızca sıcaklık sensörü bileşeniyle ilgileneceksiniz. Fiziksel bir IoT cihazında, sıcaklık sensörü, sıcaklık değiştikçe dirençteki değişimi algılayarak sıcaklığı ölçen bir [termistör](https://wikipedia.org/wiki/Thermistor) olurdu. Sıcaklık sensörleri genellikle, ölçülen direnci dahili olarak Santigrat derece (veya Kelvin ya da Fahrenheit) cinsinden bir sıcaklığa dönüştüren dijital sensörlerdir.

### Sensörleri CounterFit'e Ekleme

Sanal bir nem ve sıcaklık sensörü kullanmak için, iki sensörü CounterFit uygulamasına eklemeniz gerekir.

#### Görev - Sensörleri CounterFit'e ekleyin

Nem ve sıcaklık sensörlerini CounterFit uygulamasına ekleyin.

1. Bilgisayarınızda `temperature-sensor` adlı bir klasörde `app.py` adlı tek bir dosya içeren yeni bir Python uygulaması oluşturun, bir Python sanal ortamı oluşturun ve CounterFit pip paketlerini ekleyin.

    > ⚠️ Gerekirse [ders 1'de CounterFit Python projesi oluşturma ve ayarlama talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md) başvurabilirsiniz.

1. DHT11 sensörü için bir CounterFit shim yüklemek üzere ek bir Pip paketi yükleyin. Bu işlemi, sanal ortamın etkin olduğu bir terminalden yaptığınızdan emin olun.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. CounterFit web uygulamasının çalıştığından emin olun.

1. Bir nem sensörü oluşturun:

    1. *Sensors* panelindeki *Create sensor* kutusunda, *Sensor type* kutusunu açın ve *Humidity* seçeneğini seçin.

    1. *Units* ayarını *Percentage* olarak bırakın.

    1. *Pin* ayarının *5* olduğundan emin olun.

    1. Pin 5 üzerinde nem sensörünü oluşturmak için **Add** düğmesini seçin.

    ![Nem sensörü ayarları](../../../../../translated_images/tr/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    Nem sensörü oluşturulacak ve sensörler listesinde görünecektir.

    ![Oluşturulan nem sensörü](../../../../../translated_images/tr/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Bir sıcaklık sensörü oluşturun:

    1. *Sensors* panelindeki *Create sensor* kutusunda, *Sensor type* kutusunu açın ve *Temperature* seçeneğini seçin.

    1. *Units* ayarını *Celsius* olarak bırakın.

    1. *Pin* ayarının *6* olduğundan emin olun.

    1. Pin 6 üzerinde sıcaklık sensörünü oluşturmak için **Add** düğmesini seçin.

    ![Sıcaklık sensörü ayarları](../../../../../translated_images/tr/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    Sıcaklık sensörü oluşturulacak ve sensörler listesinde görünecektir.

    ![Oluşturulan sıcaklık sensörü](../../../../../translated_images/tr/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## Sıcaklık Sensörü Uygulamasını Programlama

Artık CounterFit sensörlerini kullanarak sıcaklık sensörü uygulamasını programlayabilirsiniz.

### Görev - Sıcaklık sensörü uygulamasını programlayın

Sıcaklık sensörü uygulamasını programlayın.

1. `temperature-sensor` uygulamasının VS Code'da açık olduğundan emin olun.

1. `app.py` dosyasını açın.

1. Uygulamayı CounterFit'e bağlamak için aşağıdaki kodu `app.py` dosyasının en üstüne ekleyin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Gerekli kütüphaneleri içe aktarmak için aşağıdaki kodu `app.py` dosyasına ekleyin:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT` ifadesi, `counterfit_shims_seeed_python_dht` modülünden bir shim kullanarak sanal bir Grove sıcaklık sensörüyle etkileşim kurmak için `DHT` sensör sınıfını içe aktarır.

1. Yukarıdaki kodun ardından, sanal nem ve sıcaklık sensörünü yöneten sınıfın bir örneğini oluşturmak için aşağıdaki kodu ekleyin:

    ```python
    sensor = DHT("11", 5)
    ```

    Bu, sanal **D**ijital **N**em ve **S**ıcaklık sensörünü yöneten `DHT` sınıfının bir örneğini tanımlar. İlk parametre, kullanılan sensörün sanal bir *DHT11* sensörü olduğunu kodlara bildirir. İkinci parametre, sensörün `5` portuna bağlı olduğunu kodlara bildirir.

    > 💁 CounterFit, bu birleştirilmiş nem ve sıcaklık sensörünü, `DHT` sınıfı oluşturulduğunda verilen pin üzerindeki bir nem sensörüne ve bir sonraki pin üzerinde çalışan bir sıcaklık sensörüne bağlanarak simüle eder. Eğer nem sensörü pin 5 üzerindeyse, shim sıcaklık sensörünün pin 6 üzerinde olmasını bekler.

1. Sıcaklık sensörü değerini sorgulamak ve konsola yazdırmak için yukarıdaki kodun ardından sonsuz bir döngü ekleyin:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()` çağrısı, nem ve sıcaklık değerlerinden oluşan bir tuple döndürür. Sadece sıcaklık değerine ihtiyacınız var, bu yüzden nem değeri göz ardı edilir. Sıcaklık değeri daha sonra konsola yazdırılır.

1. Döngünün sonunda, sıcaklık seviyelerinin sürekli olarak kontrol edilmesine gerek olmadığından, cihazın güç tüketimini azaltmak için on saniyelik bir bekleme süresi ekleyin.

    ```python
    time.sleep(10)
    ```

1. Sanal ortamın etkin olduğu bir VS Code Terminalinden aşağıdaki komutu çalıştırarak Python uygulamanızı çalıştırın:

    ```sh
    python app.py
    ```

1. CounterFit uygulamasından, uygulama tarafından okunacak sıcaklık sensörünün değerini değiştirin. Bunu iki şekilde yapabilirsiniz:

    * Sıcaklık sensörü için *Value* kutusuna bir sayı girin ve ardından **Set** düğmesini seçin. Girdiğiniz sayı, sensör tarafından döndürülen değer olacaktır.

    * *Random* kutusunu işaretleyin ve bir *Min* ve *Max* değeri girin, ardından **Set** düğmesini seçin. Sensör her değer okuduğunda, *Min* ve *Max* arasında rastgele bir sayı okuyacaktır.

    Konsolda ayarladığınız değerlerin göründüğünü görmelisiniz. *Value* veya *Random* ayarlarını değiştirerek değerin değiştiğini gözlemleyin.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Bu kodu [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) klasöründe bulabilirsiniz.

😀 Sıcaklık sensörü programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.