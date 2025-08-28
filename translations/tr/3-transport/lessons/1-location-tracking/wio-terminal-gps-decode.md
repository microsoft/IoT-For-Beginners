<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T03:14:44+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "tr"
}
-->
# GPS Verilerini Çözümleme - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal tarafından GPS sensöründen okunan NMEA mesajlarını çözümleyecek ve enlem ile boylam bilgilerini çıkaracaksınız.

## GPS Verilerini Çözümleme

Ham NMEA verileri seri porttan okunduktan sonra, açık kaynaklı bir NMEA kütüphanesi kullanılarak çözümlenebilir.

### Görev - GPS Verilerini Çözümleme

Cihazı GPS verilerini çözümleyecek şekilde programlayın.

1. `gps-sensor` uygulama projesini henüz açmadıysanız açın.

1. Projenin `platformio.ini` dosyasına [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) kütüphanesi için bir kütüphane bağımlılığı ekleyin. Bu kütüphane, NMEA verilerini çözümlemek için kod içerir.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` dosyasına TinyGPSPlus kütüphanesi için bir include yönergesi ekleyin:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` deklarasyonunun altına, NMEA cümlelerini işlemek için bir TinyGPSPlus nesnesi tanımlayın:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` fonksiyonunun içeriğini aşağıdaki gibi değiştirin:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Bu kod, UART seri portundan bir sonraki karakteri `gps` NMEA çözümleyicisine okur. Her karakterden sonra, çözümleyicinin geçerli bir cümle okuyup okumadığını kontrol eder, ardından geçerli bir konum okuyup okumadığını kontrol eder. Konum geçerliyse, seri monitöre gönderir ve bu düzeltmeye katkıda bulunan uydu sayısını da ekler.

1. Kodu Wio Terminal'e derleyin ve yükleyin.

1. Yükleme tamamlandıktan sonra, seri monitör kullanarak GPS konum verilerini izleyebilirsiniz.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Bu kodu [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) klasöründe bulabilirsiniz.

😀 GPS sensör programınız veri çözümleme ile başarıyla tamamlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.