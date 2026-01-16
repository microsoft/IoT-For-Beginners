<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-28T04:18:42+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "tr"
}
-->
# Röle Kontrolü - Wio Terminal

Bu dersin bu bölümünde, toprak nem sensörüne ek olarak Wio Terminal'inize bir röle ekleyecek ve bunu toprak nem seviyesine göre kontrol edeceksiniz.

## Donanım

Wio Terminal bir röleye ihtiyaç duyar.

Kullanacağınız röle, [Grove rölesi](https://www.seeedstudio.com/Grove-Relay.html) olarak bilinir. Bu, normalde açık bir röledir (yani röleye sinyal gönderilmediğinde çıkış devresi açık veya bağlantısızdır) ve 250V ve 10A'ye kadar çıkış devrelerini destekleyebilir.

Bu bir dijital aktüatördür, bu nedenle Wio Terminal'in dijital pinlerine bağlanır. Analog/dijital birleşik port zaten toprak nem sensörüyle kullanılıyor, bu yüzden röle diğer porta bağlanır; bu port da bir birleşik I2C ve dijital porttur.

### Röleyi Bağlayın

Grove rölesi, Wio Terminal'in dijital portuna bağlanabilir.

#### Görev

Röleyi bağlayın.

![Bir Grove rölesi](../../../../../translated_images/tr/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Grove kablosunun bir ucunu rölenin soketine takın. Kablo yalnızca tek bir yönde takılabilir.

2. Wio Terminal'i bilgisayarınızdan veya başka bir güç kaynağından ayırarak, Grove kablosunun diğer ucunu Wio Terminal'in ekranına bakarken sol taraftaki Grove soketine bağlayın. Toprak nem sensörünü sağ taraftaki sokette bağlı bırakın.

![Grove rölesi sol sokete, toprak nem sensörü sağ sokete bağlı](../../../../../translated_images/tr/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

3. Toprak nem sensörünü toprağa yerleştirin, eğer önceki dersten zaten yerleştirilmişse bu adımı atlayabilirsiniz.

## Röleyi Programlayın

Artık Wio Terminal, bağlı röleyi kullanacak şekilde programlanabilir.

### Görev

Cihazı programlayın.

1. VS Code'da önceki derste oluşturduğunuz `soil-moisture-sensor` projesini açın, eğer zaten açık değilse. Bu projeye ekleme yapacaksınız.

2. Bu aktüatör için bir kütüphane yoktur - bu, yüksek veya düşük bir sinyalle kontrol edilen dijital bir aktüatördür. Röleyi açmak için pine yüksek bir sinyal (3.3V) gönderirsiniz, kapatmak için düşük bir sinyal (0V) gönderirsiniz. Bunu, Arduino'nun yerleşik [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) fonksiyonunu kullanarak yapabilirsiniz. Röleye voltaj göndermek için birleşik I2C/dijital portu bir çıkış pini olarak ayarlamak için aşağıdaki kodu `setup` fonksiyonunun sonuna ekleyin:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL`, birleşik I2C/dijital portun pin numarasıdır.

3. Rölenin çalıştığını test etmek için, aşağıdaki kodu `loop` fonksiyonuna, son `delay` satırının altına ekleyin:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Bu kod, rölenin bağlı olduğu pine yüksek bir sinyal göndererek röleyi açar, 500ms (yarım saniye) bekler, ardından röleyi kapatmak için düşük bir sinyal gönderir.

4. Kodu derleyin ve Wio Terminal'e yükleyin.

5. Kod yüklendikten sonra, röle her 10 saniyede bir açılıp kapanacaktır, açılıp kapanma arasında yarım saniyelik bir gecikme olacaktır. Rölenin açıldığını ve kapandığını belirten bir tıklama sesi duyacaksınız. Grove kartındaki bir LED, röle açıkken yanacak ve röle kapandığında sönecektir.

    ![Rölenin açılıp kapanması](../../../../../images/relay-turn-on-off.gif)

## Röleyi Toprak Nemine Göre Kontrol Etme

Artık röle çalıştığına göre, toprak nemi ölçümlerine yanıt olarak kontrol edilebilir.

### Görev

Röleyi kontrol edin.

1. Röleyi test etmek için eklediğiniz 3 satırlık kodu silin. Yerine aşağıdaki kodu ekleyin:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Bu kod, toprak nem sensöründen gelen toprak nem seviyesini kontrol eder. Eğer seviye 450'nin üzerindeyse röleyi açar, 450'nin altına düştüğünde ise kapatır.

    > 💁 Kapasitif toprak nem sensörünün, toprak nem seviyesi ne kadar düşükse, topraktaki nemin o kadar fazla olduğunu ve tam tersini ölçtüğünü unutmayın.

2. Kodu derleyin ve Wio Terminal'e yükleyin.

3. Cihazı seri monitör üzerinden izleyin. Toprak nem seviyesine bağlı olarak rölenin açılıp kapandığını göreceksiniz. Kuru toprakta deneyin, ardından su ekleyin.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Bu kodu [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal) klasöründe bulabilirsiniz.

😀 Toprak nem sensörünüzle röle kontrol programınız başarıyla tamamlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.