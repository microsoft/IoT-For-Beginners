# Yakınlık Algılama - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'ye bir yakınlık sensörü ekleyecek ve ondan mesafe okuyacaksınız.

## Donanım

Raspberry Pi'nin bir yakınlık sensörüne ihtiyacı var.

Kullanacağınız sensör, bir [Grove Time of Flight mesafe sensörü](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Bu sensör, mesafeyi algılamak için bir lazer ölçüm modülü kullanır. Sensör, 10mm ile 2000mm (1cm - 2m) arasında bir aralığa sahiptir ve bu aralıktaki değerleri oldukça doğru bir şekilde raporlar. 1000mm'nin üzerindeki mesafeler 8109mm olarak rapor edilir.

Lazer mesafe ölçer, sensörün arka tarafında, Grove soketinin karşı tarafında yer alır.

Bu bir I²C sensörüdür.

### Time of Flight Sensörünü Bağlama

Grove time of flight sensörü Raspberry Pi'ye bağlanabilir.

#### Görev - Time of Flight Sensörünü Bağlayın

Time of flight sensörünü bağlayın.

![Bir Grove time of flight sensörü](../../../../../translated_images/tr/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Grove kablosunun bir ucunu time of flight sensöründeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Raspberry Pi kapalıyken, Grove kablosunun diğer ucunu, Pi'ye bağlı Grove Base şapkasındaki **I²C** olarak işaretlenmiş soketlerden birine bağlayın. Bu soketler, GPIO pinlerinin karşı ucunda, alt sırada ve kamera kablosu yuvasının yanındadır.

![Grove time of flight sensörünün I²C soketine bağlı hali](../../../../../translated_images/tr/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Time of Flight Sensörünü Programlama

Artık Raspberry Pi, bağlı time of flight sensörünü kullanacak şekilde programlanabilir.

### Görev - Time of Flight Sensörünü Programlayın

Cihazı programlayın.

1. Pi'yi açın ve başlatılmasını bekleyin.

1. `fruit-quality-detector` kodunu VS Code'da açın. Bunu doğrudan Pi üzerinde yapabilir veya Remote SSH uzantısı aracılığıyla bağlanabilirsiniz.

1. VL53L0X time-of-flight mesafe sensörüyle etkileşim kuran bir Python paketi olan rpi-vl53l0x Pip paketini yükleyin. Aşağıdaki pip komutunu kullanarak yükleyin:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Bu projede `distance-sensor.py` adında yeni bir dosya oluşturun.

    > 💁 Birden fazla IoT cihazını simüle etmenin kolay bir yolu, her birini farklı bir Python dosyasında yapmak ve ardından aynı anda çalıştırmaktır.

1. Bu dosyaya aşağıdaki kodu ekleyin:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Bu kod, Grove I²C bus kütüphanesini ve Grove time of flight sensöründe yerleşik olan temel sensör donanımı için bir sensör kütüphanesini içe aktarır.

1. Bunun altına, sensöre erişmek için aşağıdaki kodu ekleyin:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Bu kod, Grove I²C bus kullanarak bir mesafe sensörü tanımlar ve ardından sensörü başlatır.

1. Son olarak, mesafeleri okumak için sonsuz bir döngü ekleyin:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Bu kod, sensörden bir değer okumaya hazır olmasını bekler ve ardından konsola yazdırır.

1. Bu kodu çalıştırın.

    > 💁 Bu dosyanın adı `distance-sensor.py`! `app.py` yerine Python ile çalıştırmayı unutmayın.

1. Konsolda mesafe ölçümleri görünecektir. Sensöre yakın nesneler yerleştirin ve mesafe ölçümünü göreceksiniz:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Mesafe ölçer, sensörün arka tarafındadır, bu yüzden mesafeyi ölçerken doğru tarafı kullandığınızdan emin olun.

    ![Time of flight sensörünün arka tarafındaki mesafe ölçer bir muza doğrultulmuş](../../../../../translated_images/tr/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Bu kodu [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) klasöründe bulabilirsiniz.

😀 Yakınlık sensörü programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.