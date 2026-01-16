<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-28T03:57:27+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "tr"
}
-->
# Toprak Nemini Ölç - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize kapasitif bir toprak nem sensörü ekleyecek ve ondan değerler okuyacaksınız.

## Donanım

Wio Terminal için bir kapasitif toprak nem sensörüne ihtiyacınız var.

Kullanacağınız sensör, toprağın nemini, toprağın kapasitansını algılayarak ölçen bir [Kapasitif Toprak Nem Sensörü](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html). Toprağın nemi değiştikçe bu özellik de değişir. Toprak nemi arttıkça, voltaj azalır.

Bu bir analog sensördür, bu nedenle Wio Terminal üzerindeki analog pinlere bağlanır ve 0-1.023 arasında bir değer oluşturmak için dahili bir ADC kullanır.

### Toprak nem sensörünü bağlayın

Grove toprak nem sensörü, Wio Terminal'in analog/dijital olarak yapılandırılabilir portuna bağlanabilir.

#### Görev - toprak nem sensörünü bağlayın

Toprak nem sensörünü bağlayın.

![Bir Grove toprak nem sensörü](../../../../../translated_images/tr/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Grove kablosunun bir ucunu toprak nem sensöründeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Wio Terminal'inizi bilgisayarınızdan veya başka bir güç kaynağından ayırarak, Grove kablosunun diğer ucunu ekranı size dönük şekilde sağ taraftaki Grove soketine bağlayın. Bu, güç düğmesinden en uzak olan sokettir.

![Grove toprak nem sensörü sağ sokete bağlı](../../../../../translated_images/tr/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Toprak nem sensörünü toprağa yerleştirin. Sensör üzerinde bir 'en yüksek pozisyon çizgisi' vardır - sensör boyunca uzanan beyaz bir çizgi. Sensörü bu çizgiye kadar, ancak çizgiyi geçmeyecek şekilde yerleştirin.

![Topraktaki Grove toprak nem sensörü](../../../../../translated_images/tr/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Artık Wio Terminal'inizi bilgisayarınıza bağlayabilirsiniz.

## Toprak nem sensörünü programlayın

Wio Terminal artık bağlı toprak nem sensörünü kullanacak şekilde programlanabilir.

### Görev - toprak nem sensörünü programlayın

Cihazı programlayın.

1. PlatformIO kullanarak yepyeni bir Wio Terminal projesi oluşturun. Bu projeye `soil-moisture-sensor` adını verin. `setup` fonksiyonuna seri portu yapılandırmak için kod ekleyin.

    > ⚠️ Gerekirse [1. proje, 1. dersteki PlatformIO projesi oluşturma talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project) başvurabilirsiniz.

1. Bu sensör için bir kütüphane yoktur, bunun yerine analog pinden okumak için yerleşik Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) fonksiyonunu kullanabilirsiniz. Başlangıç olarak, `setup` fonksiyonuna aşağıdaki kodu ekleyerek analog pini giriş olarak yapılandırın, böylece bu pinden değerler okunabilir.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Bu, `A0` pinini, voltajın okunabileceği bir giriş pini olarak ayarlar.

1. `loop` fonksiyonuna bu pinden voltaj okumak için aşağıdaki kodu ekleyin:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Bu kodun altına, değeri seri porta yazdırmak için aşağıdaki kodu ekleyin:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Son olarak, 10 saniyelik bir gecikme ekleyin:

    ```cpp
    delay(10000);
    ```

1. Kodu derleyin ve Wio Terminal'e yükleyin.

    > ⚠️ Gerekirse [1. proje, 1. dersteki PlatformIO projesi oluşturma talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app) başvurabilirsiniz.

1. Kod yüklendikten sonra, seri monitörü kullanarak toprak nemini izleyebilirsiniz. Toprağa biraz su ekleyin veya sensörü topraktan çıkarın ve değerin nasıl değiştiğini görün.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Yukarıdaki örnek çıktıda, su eklendikçe voltajın düştüğünü görebilirsiniz.

> 💁 Bu kodu [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) klasöründe bulabilirsiniz.

😀 Toprak nem sensörü programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.