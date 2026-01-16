<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-28T03:43:11+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "tr"
}
-->
# Bir gece lambası yap - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'ye bir ışık sensörü ekleyeceksiniz.

## Donanım

Bu ders için kullanılan sensör, ışığı elektrik sinyaline dönüştürmek için bir [fotodiyot](https://wikipedia.org/wiki/Photodiode) kullanan bir **ışık sensörüdür**. Bu, ışık miktarını 0 ile 1.000 arasında bir tam sayı değeri olarak gönderen analog bir sensördür. Bu değer, [lüks](https://wikipedia.org/wiki/Lux) gibi standart bir ölçü birimine karşılık gelmez.

Işık sensörü, harici bir Grove sensörüdür ve Raspberry Pi üzerindeki Grove Base şapkasına bağlanması gerekir.

### Işık sensörünü bağlayın

Işık seviyelerini algılamak için kullanılan Grove ışık sensörünün Raspberry Pi'ye bağlanması gerekir.

#### Görev - ışık sensörünü bağlayın

Işık sensörünü bağlayın.

![Bir Grove ışık sensörü](../../../../../translated_images/tr/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Grove kablosunun bir ucunu ışık sensörü modülündeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Raspberry Pi kapalıyken, Grove kablosunun diğer ucunu, Pi'ye bağlı Grove Base şapkasındaki **A0** olarak işaretlenmiş analog sokete bağlayın. Bu soket, GPIO pinlerinin yanındaki soket sırasının sağdan ikinci soketidir.

![A0 soketine bağlı Grove ışık sensörü](../../../../../translated_images/tr/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Işık sensörünü programlayın

Cihaz artık Grove ışık sensörü kullanılarak programlanabilir.

### Görev - ışık sensörünü programlayın

Cihazı programlayın.

1. Pi'yi açın ve başlatılmasını bekleyin.

1. Bu ödevin önceki bölümünde oluşturduğunuz gece lambası projesini, doğrudan Pi üzerinde çalıştırarak veya Remote SSH uzantısını kullanarak VS Code'da açın.

1. `app.py` dosyasını açın ve içindeki tüm kodları silin.

1. `app.py` dosyasına aşağıdaki kodu ekleyerek gerekli kütüphaneleri içe aktarın:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` ifadesi, bu ödevin ilerleyen bölümlerinde kullanılacak olan `time` modülünü içe aktarır.

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor` ifadesi, Grove Python kütüphanelerinden `GroveLightSensor` sınıfını içe aktarır. Bu kütüphane, bir Grove ışık sensörüyle etkileşim kurmak için kod içerir ve Pi kurulumu sırasında global olarak yüklenmiştir.

1. Yukarıdaki kodun altına, ışık sensörünü yöneten sınıfın bir örneğini oluşturmak için aşağıdaki kodu ekleyin:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)` satırı, ışık sensörünün bağlı olduğu analog Grove pini olan **A0** pinine bağlanarak `GroveLightSensor` sınıfının bir örneğini oluşturur.

1. Yukarıdaki kodun altına, ışık sensörü değerini sürekli olarak sorgulamak ve konsola yazdırmak için sonsuz bir döngü ekleyin:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Bu, `GroveLightSensor` sınıfının `light` özelliğini kullanarak 0-1.023 ölçeğinde mevcut ışık seviyesini okur. Bu özellik, pinden analog değeri okur. Bu değer daha sonra konsola yazdırılır.

1. Döngünün sonuna bir saniyelik kısa bir bekleme ekleyin, çünkü ışık seviyelerinin sürekli olarak kontrol edilmesi gerekmez. Bekleme, cihazın güç tüketimini azaltır.

    ```python
    time.sleep(1)
    ```

1. VS Code Terminalinden aşağıdaki komutu çalıştırarak Python uygulamanızı çalıştırın:

    ```sh
    python3 app.py
    ```

    Işık değerleri konsola yazdırılacaktır. Işık sensörünü kapatıp açın ve değerlerin değiştiğini göreceksiniz:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Bu kodu [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) klasöründe bulabilirsiniz.

😀 Gece lambası programınıza bir sensör eklemek başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.