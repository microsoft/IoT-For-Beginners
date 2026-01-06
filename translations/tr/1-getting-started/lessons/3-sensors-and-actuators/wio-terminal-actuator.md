<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-28T03:43:39+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "tr"
}
-->
# Gece Lambası Yapımı - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize bir LED ekleyecek ve bir gece lambası oluşturacaksınız.

## Donanım

Gece lambası artık bir aktüatöre ihtiyaç duyuyor.

Aktüatör, bir **LED**, yani bir [ışık yayan diyot](https://wikipedia.org/wiki/Light-emitting_diode). Akım geçtiğinde ışık yayar. Bu, iki durumu olan dijital bir aktüatördür: açık ve kapalı. 1 değeri gönderildiğinde LED yanar, 0 gönderildiğinde söner. Bu, harici bir Grove aktüatörüdür ve Wio Terminal'e bağlanması gerekir.

Gece lambasının mantığı, sözde kod olarak şu şekildedir:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### LED'i Bağlayın

Grove LED, farklı renklerde LED'ler içeren bir modül olarak gelir, böylece istediğiniz rengi seçebilirsiniz.

#### Görev - LED'i bağlayın

LED'i bağlayın.

![Bir Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.tr.png)

1. En sevdiğiniz LED'i seçin ve bacaklarını LED modülündeki iki deliğe yerleştirin.

    LED'ler ışık yayan diyotlardır ve diyotlar, akımı yalnızca tek bir yönde iletebilen elektronik cihazlardır. Bu, LED'in doğru şekilde bağlanması gerektiği anlamına gelir, aksi takdirde çalışmaz.

    LED'in bacaklarından biri pozitif uç, diğeri negatif uçtur. LED tamamen yuvarlak değildir ve bir tarafı biraz daha düz bir şekildedir. Hafifçe düz olan taraf negatif uçtur. LED'i modüle bağlarken, yuvarlak tarafın yanındaki bacağın modülün dışındaki **+** işaretiyle belirtilen sokete, düz tarafın ise modülün ortasına daha yakın olan sokete bağlandığından emin olun.

1. LED modülünde, parlaklığı kontrol etmenizi sağlayan bir döner düğme bulunur. Küçük bir yıldız tornavida kullanarak bu düğmeyi saat yönünün tersine çevirerek sonuna kadar açın.

1. Grove kablosunun bir ucunu LED modülündeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Wio Terminal'inizi bilgisayarınızdan veya başka bir güç kaynağından ayırarak, Grove kablosunun diğer ucunu Wio Terminal'in ekranına bakarken sağ taraftaki Grove soketine bağlayın. Bu, güç düğmesinden en uzak olan sokettir.

    > 💁 Sağ taraftaki Grove soketi, analog veya dijital sensörler ve aktüatörlerle kullanılabilir. Sol taraftaki soket yalnızca I2C ve dijital sensörler ve aktüatörler içindir. Bu konu daha sonraki bir derste ele alınacaktır.

![Sağ taraftaki sokete bağlanmış Grove LED](../../../../../translated_images/wio-led.265a1897e72d7f21.tr.png)

## Gece Lambasını Programlayın

Gece lambası artık dahili ışık sensörü ve Grove LED kullanılarak programlanabilir.

### Görev - Gece lambasını programlayın

Gece lambasını programlayın.

1. Bu ödevin önceki bölümünde oluşturduğunuz gece lambası projesini VS Code'da açın.

1. `setup` fonksiyonunun sonuna şu satırı ekleyin:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Bu satır, Grove portu üzerinden LED ile iletişim kurmak için kullanılan pini yapılandırır.

    `D0` pini, sağ taraftaki Grove soketi için dijital pindir. Bu pin, bir aktüatöre bağlandığı ve pine veri yazılacağı anlamına gelen `OUTPUT` olarak ayarlanır.

1. Döngü fonksiyonundaki `delay` satırının hemen öncesine şu kodu ekleyin:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Bu kod, `light` değerini kontrol eder. Eğer bu değer 300'den küçükse, `D0` dijital pinine `HIGH` değeri gönderir. Bu `HIGH` değeri 1 anlamına gelir ve LED'i yakar. Eğer ışık değeri 300 veya daha büyükse, pine `LOW` değeri olan 0 gönderilir ve LED söner.

    > 💁 Aktüatörlere dijital değerler gönderirken, LOW değeri 0v, HIGH değeri ise cihaz için maksimum voltajdır. Wio Terminal için HIGH voltajı 3.3V'dir.

1. Wio Terminal'i tekrar bilgisayarınıza bağlayın ve daha önce yaptığınız gibi yeni kodu yükleyin.

1. Seri Monitörü bağlayın. Işık değerleri terminale yazdırılacaktır.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Işık sensörünü kapatıp açın. Işık seviyesi 300 veya daha az olduğunda LED'in yandığını, 300'den büyük olduğunda ise söndüğünü fark edeceksiniz.

![Işık seviyesi değiştikçe WIO'ya bağlı LED'in yanıp sönmesi](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Bu kodu [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) klasöründe bulabilirsiniz.

😀 Gece lambası programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.