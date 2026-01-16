<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-28T03:42:05+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "tr"
}
-->
# Bir gece lambası yapın - Sanal IoT Donanımı

Bu dersin bu bölümünde, sanal IoT cihazınıza bir LED ekleyecek ve bunu bir gece lambası oluşturmak için kullanacaksınız.

## Sanal Donanım

Gece lambası, CounterFit uygulamasında oluşturulan bir aktüatöre ihtiyaç duyar.

Aktüatör bir **LED**'dir. Fiziksel bir IoT cihazında, bu, akım geçtiğinde ışık yayan bir [ışık yayan diyot](https://wikipedia.org/wiki/Light-emitting_diode) olurdu. Bu, iki durumu olan dijital bir aktüatördür: açık ve kapalı. 1 değeri göndermek LED'i açar, 0 değeri göndermek ise kapatır.

Gece lambası mantığı şu şekilde bir sözde kod ile ifade edilebilir:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Aktüatörü CounterFit'e ekleyin

Sanal bir LED kullanmak için, bunu CounterFit uygulamasına eklemeniz gerekir.

#### Görev - Aktüatörü CounterFit'e ekleyin

LED'i CounterFit uygulamasına ekleyin.

1. Bu ödevin önceki bölümünden CounterFit web uygulamasının çalıştığından emin olun. Çalışmıyorsa, başlatın ve ışık sensörünü yeniden ekleyin.

1. Bir LED oluşturun:

    1. *Actuator* panelindeki *Create actuator* kutusunda, *Actuator type* açılır menüsünden *LED* seçeneğini seçin.

    1. *Pin* değerini *5* olarak ayarlayın.

    1. **Add** düğmesine tıklayarak Pin 5 üzerinde bir LED oluşturun.

    ![LED ayarları](../../../../../translated_images/tr/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED oluşturulacak ve aktüatörler listesinde görünecektir.

    ![Oluşturulan LED](../../../../../translated_images/tr/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    LED oluşturulduktan sonra, *Color* seçici kullanılarak rengi değiştirebilirsiniz. Rengi seçtikten sonra **Set** düğmesine tıklayarak değişikliği uygulayın.

### Gece lambasını programlayın

Artık CounterFit ışık sensörü ve LED kullanılarak gece lambası programlanabilir.

#### Görev - Gece lambasını programlayın

Gece lambasını programlayın.

1. Bu ödevin önceki bölümünde oluşturduğunuz gece lambası projesini VS Code'da açın. Gerekirse terminali kapatıp yeniden oluşturun ve sanal ortamı kullanarak çalıştığından emin olun.

1. `app.py` dosyasını açın.

1. Gerekli bir kütüphaneyi içe aktarmak için `app.py` dosyasına aşağıdaki kodu ekleyin. Bu kod, diğer `import` satırlarının altına eklenmelidir.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` ifadesi, CounterFit Grove shim Python kütüphanelerinden `GroveLed` sınıfını içe aktarır. Bu kütüphane, CounterFit uygulamasında oluşturulan bir LED ile etkileşim kurmak için kod içerir.

1. LED'i yöneten sınıfın bir örneğini oluşturmak için `light_sensor` tanımından sonra aşağıdaki kodu ekleyin:

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` satırı, LED'in bağlı olduğu CounterFit Grove pini olan **5** pinine bağlanan `GroveLed` sınıfının bir örneğini oluşturur.

1. `while` döngüsü içinde ve `time.sleep` öncesinde ışık seviyelerini kontrol etmek ve LED'i açıp kapatmak için bir kontrol ekleyin:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Bu kod, `light` değerini kontrol eder. Eğer bu değer 300'den küçükse, `GroveLed` sınıfının `on` metodunu çağırır ve LED'e 1 dijital değerini göndererek LED'i açar. Eğer ışık değeri 300 veya daha büyükse, `off` metodunu çağırır ve LED'e 0 dijital değerini göndererek LED'i kapatır.

    > 💁 Bu kod, `print('Light level:', light)` satırıyla aynı seviyede girintilenmelidir, böylece `while` döngüsünün içinde yer alır!

1. VS Code Terminalinden aşağıdaki komutu çalıştırarak Python uygulamanızı çalıştırın:

    ```sh
    python3 app.py
    ```

    Işık değerleri konsola yazdırılacaktır.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Işık seviyesini 300'ün üzerine ve altına değiştirmek için *Value* veya *Random* ayarlarını değiştirin. LED açılıp kapanacaktır.

![Işık seviyesi değiştikçe CounterFit uygulamasındaki LED'in açılıp kapanması](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Bu kodu [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) klasöründe bulabilirsiniz.

😀 Gece lambası programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.