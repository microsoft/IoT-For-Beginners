<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T03:44:59+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "tr"
}
-->
# Bir Sensör Ekleyin - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal üzerindeki ışık sensörünü kullanacaksınız.

## Donanım

Bu ders için kullanılan sensör, ışığı bir elektrik sinyaline dönüştürmek için bir [fotodiyot](https://wikipedia.org/wiki/Photodiode) kullanan bir **ışık sensörüdür**. Bu, 0 ile 1.023 arasında bir tamsayı değeri gönderen analog bir sensördür ve bu değer, [lüks](https://wikipedia.org/wiki/Lux) gibi standart bir ölçü birimine karşılık gelmez, yalnızca göreceli bir ışık miktarını ifade eder.

Işık sensörü, Wio Terminal'in içine yerleştirilmiştir ve cihazın arkasındaki şeffaf plastik pencere aracılığıyla görülebilir.

![Wio Terminal'in arkasındaki ışık sensörü](../../../../../translated_images/tr/wio-light-sensor.b1f529f3c95f5165.webp)

## Işık Sensörünü Programlayın

Cihaz artık dahili ışık sensörünü kullanacak şekilde programlanabilir.

### Görev

Cihazı programlayın.

1. Bu ödevin önceki bölümünde oluşturduğunuz gece lambası projesini VS Code'da açın.

1. `setup` fonksiyonunun sonuna aşağıdaki satırı ekleyin:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Bu satır, sensör donanımıyla iletişim kurmak için kullanılan pinleri yapılandırır.

    `WIO_LIGHT` pini, dahili ışık sensörüne bağlı GPIO pininin numarasıdır. Bu pin `INPUT` olarak ayarlanmıştır, yani bir sensöre bağlanır ve bu pin üzerinden veri okunur.

1. `loop` fonksiyonunun içeriğini silin.

1. Şimdi boş olan `loop` fonksiyonuna aşağıdaki kodu ekleyin.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Bu kod, `WIO_LIGHT` pininden analog bir değer okur. Bu, dahili ışık sensöründen 0-1.023 arasında bir değer okur. Bu değer daha sonra seri porta gönderilir, böylece bu kod çalışırken Seri Monitör'de okuyabilirsiniz. `Serial.print`, metni yeni bir satır eklemeden yazar, bu nedenle her satır `Light value:` ile başlar ve ardından gerçek ışık değeriyle biter.

1. Döngünün sonunda bir saniyelik (1.000ms) küçük bir gecikme ekleyin, çünkü ışık seviyelerinin sürekli olarak kontrol edilmesi gerekmez. Bir gecikme, cihazın güç tüketimini azaltır.

    ```cpp
    delay(1000);
    ```

1. Wio Terminal'i bilgisayarınıza yeniden bağlayın ve daha önce yaptığınız gibi yeni kodu yükleyin.

1. Seri Monitör'e bağlanın. Işık değerleri terminale yazdırılacaktır. Wio Terminal'in arkasındaki ışık sensörünü kapatıp açın ve değerlerin değiştiğini göreceksiniz.

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

> 💁 Bu kodu [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) klasöründe bulabilirsiniz.

😀 Gece lambası programınıza bir sensör eklemek başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.