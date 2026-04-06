# Yakınlık Algılama - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize bir yakınlık sensörü ekleyecek ve mesafeyi okuyacaksınız.

## Donanım

Wio Terminal bir yakınlık sensörüne ihtiyaç duyar.

Kullanacağınız sensör, bir [Grove Time of Flight mesafe sensörü](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Bu sensör, mesafeyi algılamak için bir lazer ölçüm modülü kullanır. Sensör, 10mm ile 2000mm (1cm - 2m) arasında bir aralığa sahiptir ve bu aralıktaki değerleri oldukça doğru bir şekilde raporlar. 1000mm'nin üzerindeki mesafeler 8109mm olarak rapor edilir.

Lazer mesafe ölçer, sensörün arka tarafında, Grove soketinin karşı tarafında yer alır.

Bu bir I²C sensörüdür.

### Time of Flight Sensörünü Bağlama

Grove Time of Flight sensörü, Wio Terminal'e bağlanabilir.

#### Görev - Time of Flight Sensörünü Bağlayın

Time of Flight sensörünü bağlayın.

![Bir Grove Time of Flight sensörü](../../../../../translated_images/tr/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Grove kablosunun bir ucunu Time of Flight sensöründeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

2. Wio Terminal'inizi bilgisayarınızdan veya başka bir güç kaynağından ayırarak, Grove kablosunun diğer ucunu Wio Terminal'in ekranına bakarken sol taraftaki Grove soketine bağlayın. Bu soket, güç düğmesine en yakın olan sokettir. Bu soket, dijital ve I²C kombinasyonlu bir sokettir.

![Time of Flight sensörünün sol sokete bağlı hali](../../../../../translated_images/tr/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

3. Artık Wio Terminal'i bilgisayarınıza bağlayabilirsiniz.

## Time of Flight Sensörünü Programlama

Wio Terminal artık bağlı Time of Flight sensörünü kullanacak şekilde programlanabilir.

### Görev - Time of Flight Sensörünü Programlayın

1. PlatformIO kullanarak yeni bir Wio Terminal projesi oluşturun. Bu projeye `distance-sensor` adını verin. `setup` fonksiyonunda seri portu yapılandırmak için kod ekleyin.

2. Projenin `platformio.ini` dosyasına Seeed Grove Time of Flight mesafe sensörü kütüphanesi için bir bağımlılık ekleyin:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

3. `main.cpp` dosyasında, mevcut include yönergelerinin altına, Time of Flight sensörüyle etkileşim kurmak için `Seeed_vl53l0x` sınıfının bir örneğini tanımlayın:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

4. Sensörü başlatmak için `setup` fonksiyonunun sonuna şu kodu ekleyin:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

5. `loop` fonksiyonunda, sensörden bir değer okuyun:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Bu kod, verileri okumak için bir veri yapısı başlatır ve ardından bu yapıyı `PerformSingleRangingMeasurement` metoduna geçirir. Bu metod, mesafe ölçümünü veri yapısına doldurur.

6. Bunun altına, mesafe ölçümünü yazdırın ve ardından 1 saniye bekleyin:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

7. Bu kodu derleyin, yükleyin ve çalıştırın. Seri monitör ile mesafe ölçümlerini görebileceksiniz. Sensöre yakın nesneler yerleştirin ve mesafe ölçümünü gözlemleyin:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Mesafe ölçer, sensörün arka tarafında yer alır, bu yüzden mesafeyi ölçerken doğru tarafı kullandığınızdan emin olun.

    ![Time of Flight sensörünün arka tarafındaki mesafe ölçer bir muza doğrultulmuş](../../../../../translated_images/tr/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Bu kodu [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) klasöründe bulabilirsiniz.

😀 Yakınlık sensörü programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.