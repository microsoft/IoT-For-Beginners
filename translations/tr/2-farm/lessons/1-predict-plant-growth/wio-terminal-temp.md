<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-28T04:14:33+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "tr"
}
-->
# Sıcaklık Ölçümü - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize bir sıcaklık sensörü ekleyecek ve sıcaklık değerlerini okuyacaksınız.

## Donanım

Wio Terminal bir sıcaklık sensörüne ihtiyaç duyar.

Kullanacağınız sensör, [DHT11 nem ve sıcaklık sensörü](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)'dür. Bu sensör, tek bir pakette iki sensörü birleştirir. Oldukça popülerdir ve ticari olarak temin edilebilen birçok sensör, sıcaklık, nem ve bazen atmosferik basıncı birleştirir. Sıcaklık sensörü bileşeni, negatif sıcaklık katsayısına (NTC) sahip bir termistördür; bu, sıcaklık arttıkça direncin azaldığı bir termistördür.

Bu bir dijital sensördür, bu nedenle mikrodenetleyicinin okuyabileceği sıcaklık ve nem verilerini içeren bir dijital sinyal oluşturmak için bir dahili ADC'ye sahiptir.

### Sıcaklık sensörünü bağlayın

Grove sıcaklık sensörü, Wio Terminal'in dijital portuna bağlanabilir.

#### Görev - sıcaklık sensörünü bağlayın

Sıcaklık sensörünü bağlayın.

![Bir Grove sıcaklık sensörü](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.tr.png)

1. Grove kablosunun bir ucunu nem ve sıcaklık sensöründeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Wio Terminal'inizi bilgisayarınızdan veya başka bir güç kaynağından ayırarak, Grove kablosunun diğer ucunu Wio Terminal'in ekranına bakarken sağ taraftaki Grove soketine bağlayın. Bu, güç düğmesinden en uzak olan sokettir.

![Sağ sokete bağlı Grove sıcaklık sensörü](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a.tr.png)

## Sıcaklık sensörünü programlayın

Artık Wio Terminal, bağlı sıcaklık sensörünü kullanacak şekilde programlanabilir.

### Görev - sıcaklık sensörünü programlayın

Cihazı programlayın.

1. PlatformIO kullanarak yeni bir Wio Terminal projesi oluşturun. Bu projeye `temperature-sensor` adını verin. `setup` fonksiyonuna seri portu yapılandırmak için kod ekleyin.

    > ⚠️ Gerekirse [proje 1, ders 1'de PlatformIO projesi oluşturma talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project) başvurabilirsiniz.

1. Seeed Grove Nem ve Sıcaklık sensörü kütüphanesi için bir kütüphane bağımlılığı ekleyin ve bunu projenin `platformio.ini` dosyasına ekleyin:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Gerekirse [proje 1, ders 4'te PlatformIO projesine kütüphane ekleme talimatlarına](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries) başvurabilirsiniz.

1. Dosyanın en üstüne, mevcut `#include <Arduino.h>` satırının altına şu `#include` yönergelerini ekleyin:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Bu, sensörle etkileşim kurmak için gereken dosyaları içe aktarır. `DHT.h` başlık dosyası sensörün kendisi için gereken kodu içerir ve `SPI.h` başlığını eklemek, uygulama derlenirken sensörle iletişim kurmak için gereken kodun bağlantılandırılmasını sağlar.

1. `setup` fonksiyonundan önce, DHT sensörünü tanımlayın:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Bu, **D**ijital **N**em ve **S**ıcaklık sensörünü yöneten `DHT` sınıfının bir örneğini tanımlar. Bu, Wio Terminal'in sağ tarafındaki Grove soketine, yani `D0` portuna bağlanmıştır. İkinci parametre, kullanılan sensörün *DHT11* sensörü olduğunu koda bildirir - kullandığınız kütüphane bu sensörün diğer varyantlarını da destekler.

1. `setup` fonksiyonunda, seri bağlantıyı ayarlamak için kod ekleyin:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. `setup` fonksiyonunun sonunda, son `delay` satırından sonra, DHT sensörünü başlatmak için bir çağrı ekleyin:

    ```cpp
    dht.begin();
    ```

1. `loop` fonksiyonunda, sensörü çağırmak ve sıcaklığı seri porta yazdırmak için kod ekleyin:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Bu kod, 2 adet float değerini tutacak boş bir dizi tanımlar ve bu diziyi `DHT` örneğindeki `readTempAndHumidity` fonksiyonuna geçirir. Bu çağrı, diziyi 2 değerle doldurur - nem, dizinin 0. elemanına (C++ dizilerinin 0 tabanlı olduğunu unutmayın, bu nedenle 0. eleman dizinin 'ilk' elemanıdır), sıcaklık ise 1. elemanına yerleştirilir.

    Sıcaklık, dizinin 1. elemanından okunur ve seri porta yazdırılır.

    > 🇺🇸 Sıcaklık Celsius cinsinden okunur. Amerikalılar için, bunu Fahrenheit'e dönüştürmek için okunan Celsius değerini 5'e bölün, ardından 9 ile çarpın ve 32 ekleyin. Örneğin, 20°C'lik bir sıcaklık okuması şu şekilde dönüştürülür: ((20/5)*9) + 32 = 68°F.

1. Kodu derleyin ve Wio Terminal'e yükleyin.

    > ⚠️ Gerekirse [proje 1, ders 1'de PlatformIO projesi oluşturma talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app) başvurabilirsiniz.

1. Kod yüklendikten sonra, sıcaklığı seri monitör kullanarak izleyebilirsiniz:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Bu kodu [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) klasöründe bulabilirsiniz.

😀 Sıcaklık sensörü programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.