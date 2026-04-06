# Bir gece lambası yapın - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'nize bir LED ekleyecek ve bunu bir gece lambası oluşturmak için kullanacaksınız.

## Donanım

Gece lambası artık bir aktüatöre ihtiyaç duyuyor.

Aktüatör bir **LED**, bir [ışık yayan diyot](https://wikipedia.org/wiki/Light-emitting_diode) olup, üzerinden akım geçtiğinde ışık yayar. Bu, iki durumu olan dijital bir aktüatördür: açık ve kapalı. 1 değeri gönderildiğinde LED açılır, 0 değeri gönderildiğinde ise kapanır. LED, harici bir Grove aktüatördür ve Raspberry Pi üzerindeki Grove Base hatına bağlanması gerekir.

Gece lambası mantığı, sözde kod olarak:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### LED'i Bağlayın

Grove LED, bir dizi LED içeren bir modül olarak gelir ve size renk seçme imkanı sunar.

#### Görev - LED'i bağlayın

LED'i bağlayın.

![Bir Grove LED](../../../../../translated_images/tr/grove-led.6c853be93f473cf2.webp)

1. En sevdiğiniz LED'i seçin ve ayaklarını LED modülündeki iki deliğe yerleştirin.

    LED'ler ışık yayan diyotlardır ve diyotlar yalnızca bir yönde akım taşıyabilen elektronik cihazlardır. Bu, LED'in doğru şekilde bağlanması gerektiği anlamına gelir, aksi takdirde çalışmaz.

    LED'in ayaklarından biri pozitif pin, diğeri negatif pindir. LED tamamen yuvarlak değildir ve bir tarafı biraz daha düzleşmiştir. Daha düz olan taraf negatif pindir. LED'i modüle bağlarken, yuvarlak tarafın yanındaki pinin modülün dışındaki **+** işaretiyle belirtilen sokete, daha düz olan tarafın ise modülün ortasına daha yakın olan sokete bağlandığından emin olun.

1. LED modülünde parlaklığı kontrol etmenizi sağlayan bir döner düğme bulunur. Küçük bir Phillips başlı tornavida kullanarak bunu saat yönünün tersine sonuna kadar çevirerek başlangıçta tamamen açın.

1. Grove kablosunun bir ucunu LED modülündeki sokete yerleştirin. Kablo yalnızca bir yönde takılabilir.

1. Raspberry Pi kapalıyken, Grove kablosunun diğer ucunu Pi'ye bağlı Grove Base hatındaki **D5** işaretiyle belirtilen dijital sokete bağlayın. Bu soket, GPIO pinlerinin yanındaki soket sırasının soldan ikinci soketidir.

![Grove LED'in D5 soketine bağlanması](../../../../../translated_images/tr/pi-led.97f1d474981dc35d.webp)

## Gece lambasını programlayın

Gece lambası artık Grove ışık sensörü ve Grove LED kullanılarak programlanabilir.

### Görev - gece lambasını programlayın

Gece lambasını programlayın.

1. Pi'yi açın ve başlatılmasını bekleyin.

1. Bu ödevin önceki bölümünde oluşturduğunuz gece lambası projesini VS Code'da açın. Proje, doğrudan Pi üzerinde çalıştırılabilir veya Remote SSH uzantısı kullanılarak bağlanabilir.

1. Gerekli bir kütüphaneyi içe aktarmak için `app.py` dosyasına aşağıdaki kodu ekleyin. Bu kod, diğer `import` satırlarının altına eklenmelidir.

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed` ifadesi, Grove Python kütüphanelerinden `GroveLed`'i içe aktarır. Bu kütüphane, bir Grove LED ile etkileşim kurmak için kod içerir.

1. LED'i yöneten sınıfın bir örneğini oluşturmak için `light_sensor` tanımından sonra aşağıdaki kodu ekleyin:

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` satırı, LED'in bağlı olduğu dijital Grove pini olan **D5** pinine bağlanan `GroveLed` sınıfının bir örneğini oluşturur.

    > 💁 Tüm soketlerin benzersiz pin numaraları vardır. Pinler 0, 2, 4 ve 6 analog pinlerdir; pinler 5, 16, 18, 22, 24 ve 26 dijital pinlerdir.

1. `while` döngüsünün içine ve `time.sleep` satırından önce bir kontrol ekleyerek ışık seviyelerini kontrol edin ve LED'i açıp kapatın:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Bu kod, `light` değerini kontrol eder. Eğer bu değer 300'den küçükse, LED'i açan ve LED'e dijital bir 1 değeri gönderen `GroveLed` sınıfının `on` metodunu çağırır. Eğer ışık değeri 300 veya daha büyükse, LED'i kapatan ve LED'e dijital bir 0 değeri gönderen `off` metodunu çağırır.

    > 💁 Bu kod, `print('Light level:', light)` satırıyla aynı seviyede girintili olmalı ve while döngüsünün içinde yer almalıdır!

    > 💁 Aktüatörlere dijital değerler gönderirken, 0 değeri 0V, 1 değeri ise cihazın maksimum voltajıdır. Raspberry Pi ile Grove sensörleri ve aktüatörleri kullanıldığında, 1 voltajı 3.3V'dir.

1. VS Code Terminalinden aşağıdaki komutu çalıştırarak Python uygulamanızı çalıştırın:

    ```sh
    python3 app.py
    ```

    Işık değerleri konsola yazdırılacaktır.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Işık sensörünü örtün ve açın. Işık seviyesi 300 veya daha az olduğunda LED'in yanıp, ışık seviyesi 300'den büyük olduğunda LED'in söndüğünü fark edin.

    > 💁 LED yanmıyorsa, doğru şekilde bağlandığından ve döner düğmenin tamamen açık olduğundan emin olun.

![Işık seviyesi değiştikçe Pi'ye bağlı LED'in açılıp kapanması](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Bu kodu [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) klasöründe bulabilirsiniz.

😀 Gece lambası programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.