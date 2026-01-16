<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-28T03:44:17+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "tr"
}
-->
# Bir gece lambası yapın - Sanal IoT Donanımı

Bu dersin bu bölümünde, sanal IoT cihazınıza bir ışık sensörü ekleyeceksiniz.

## Sanal Donanım

Gece lambası için CounterFit uygulamasında oluşturulan bir sensöre ihtiyaç vardır.

Bu sensör bir **ışık sensörüdür**. Fiziksel bir IoT cihazında, ışığı elektrik sinyaline dönüştüren bir [fotodiyot](https://wikipedia.org/wiki/Photodiode) olurdu. Işık sensörleri, ışığın göreceli miktarını gösteren bir tam sayı değeri gönderen analog sensörlerdir ve bu değer [lüks](https://wikipedia.org/wiki/Lux) gibi standart bir ölçü birimine karşılık gelmez.

### CounterFit'e sensör ekleme

Sanal bir ışık sensörü kullanmak için, bunu CounterFit uygulamasına eklemeniz gerekir.

#### Görev - CounterFit'e sensör ekleme

CounterFit uygulamasına ışık sensörünü ekleyin.

1. Bu ödevin önceki bölümünden CounterFit web uygulamasının çalıştığından emin olun. Çalışmıyorsa, başlatın.

1. Bir ışık sensörü oluşturun:

    1. *Sensors* panelindeki *Create sensor* kutusunda, *Sensor type* açılır kutusunu açın ve *Light* seçeneğini seçin.

    1. *Units* seçeneğini *NoUnits* olarak bırakın.

    1. *Pin* seçeneğinin *0* olarak ayarlandığından emin olun.

    1. Pin 0 üzerinde ışık sensörünü oluşturmak için **Add** düğmesine tıklayın.

    ![Işık sensörü ayarları](../../../../../translated_images/tr/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Işık sensörü oluşturulacak ve sensörler listesinde görünecektir.

    ![Oluşturulan ışık sensörü](../../../../../translated_images/tr/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Işık sensörünü programlama

Cihaz artık yerleşik ışık sensörünü kullanacak şekilde programlanabilir.

### Görev - ışık sensörünü programlama

Cihazı programlayın.

1. Bu ödevin önceki bölümünde oluşturduğunuz gece lambası projesini VS Code'da açın. Gerekirse terminali kapatıp yeniden oluşturun ve sanal ortamı kullanarak çalıştığından emin olun.

1. `app.py` dosyasını açın.

1. Gerekli kütüphaneleri içe aktarmak için `app.py` dosyasının üst kısmına, diğer `import` ifadelerinin yanına aşağıdaki kodu ekleyin:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` ifadesi, bu ödevin ilerleyen bölümlerinde kullanılacak olan Python `time` modülünü içe aktarır.

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` ifadesi, CounterFit Grove shim Python kütüphanelerinden `GroveLightSensor` sınıfını içe aktarır. Bu kütüphane, CounterFit uygulamasında oluşturulan bir ışık sensörüyle etkileşim kurmak için kod içerir.

1. Işık sensörünü yöneten sınıfların örneklerini oluşturmak için dosyanın altına aşağıdaki kodu ekleyin:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` satırı, **0** pinine bağlanan `GroveLightSensor` sınıfının bir örneğini oluşturur - ışık sensörünün bağlı olduğu CounterFit Grove pini.

1. Işık sensörünün değerini sorgulamak ve konsola yazdırmak için yukarıdaki kodun altına sonsuz bir döngü ekleyin:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Bu, `GroveLightSensor` sınıfının `light` özelliğini kullanarak mevcut ışık seviyesini okur. Bu özellik, pinden analog değeri okur. Bu değer daha sonra konsola yazdırılır.

1. `while` döngüsünün sonunda bir saniyelik kısa bir bekleme ekleyin, çünkü ışık seviyelerinin sürekli olarak kontrol edilmesine gerek yoktur. Bekleme, cihazın güç tüketimini azaltır.

    ```python
    time.sleep(1)
    ```

1. VS Code Terminalinden, Python uygulamanızı çalıştırmak için aşağıdaki komutu çalıştırın:

    ```sh
    python3 app.py
    ```

    Işık değerleri konsola yazdırılacaktır. Başlangıçta bu değer 0 olacaktır.

1. CounterFit uygulamasından, uygulama tarafından okunacak ışık sensörünün değerini değiştirin. Bunu iki şekilde yapabilirsiniz:

    * Işık sensörü için *Value* kutusuna bir sayı girin ve ardından **Set** düğmesine tıklayın. Girdiğiniz sayı, sensör tarafından döndürülen değer olacaktır.

    * *Random* kutusunu işaretleyin ve bir *Min* ve *Max* değeri girin, ardından **Set** düğmesine tıklayın. Sensör her değer okuduğunda, *Min* ve *Max* arasında rastgele bir sayı okuyacaktır.

    Ayarladığınız değerler konsola yazdırılacaktır. Değeri değiştirmek için *Value* veya *Random* ayarlarını değiştirin.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Bu kodu [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) klasöründe bulabilirsiniz.

😀 Gece lambası programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.