<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-28T04:18:05+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "tr"
}
-->
# Röle Kontrolü - Raspberry Pi

Bu dersin bu bölümünde, toprak nem sensörüne ek olarak Raspberry Pi'ye bir röle ekleyecek ve toprak nem seviyesine göre kontrol edeceksiniz.

## Donanım

Raspberry Pi bir röleye ihtiyaç duyar.

Kullanacağınız röle, [Grove rölesi](https://www.seeedstudio.com/Grove-Relay.html) olarak bilinir. Bu, normalde açık bir röledir (yani röleye sinyal gönderilmediğinde çıkış devresi açık veya bağlantısızdır) ve 250V ve 10A'ya kadar çıkış devrelerini destekleyebilir.

Bu bir dijital aktüatördür, bu nedenle Grove Base Hat üzerindeki bir dijital pine bağlanır.

### Röleyi Bağlayın

Grove rölesi Raspberry Pi'ye bağlanabilir.

#### Görev

Röleyi bağlayın.

![Bir Grove rölesi](../../../../../translated_images/tr/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Grove kablosunun bir ucunu rölenin üzerindeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Raspberry Pi kapalıyken, Grove kablosunun diğer ucunu Pi'ye bağlı olan Grove Base Hat üzerindeki **D5** olarak işaretlenmiş dijital sokete bağlayın. Bu soket, GPIO pinlerinin yanındaki soket sırasının soldan ikinci soketidir. Toprak nem sensörünü **A0** soketine bağlı bırakın.

![Grove rölesi D5 soketine ve toprak nem sensörü A0 soketine bağlı](../../../../../translated_images/tr/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Toprak nem sensörünü toprağa yerleştirin, eğer önceki dersten itibaren zaten yerleştirilmemişse.

## Röleyi Programlayın

Raspberry Pi artık bağlı röleyi kullanacak şekilde programlanabilir.

### Görev

Cihazı programlayın.

1. Pi'yi açın ve başlatılmasını bekleyin.

1. VS Code'da önceki dersten kalan `soil-moisture-sensor` projesini açın, eğer zaten açık değilse. Bu projeye ekleme yapacaksınız.

1. Aşağıdaki kodu mevcut importların altına `app.py` dosyasına ekleyin:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Bu ifade, Grove Python kütüphanelerinden `GroveRelay`'i içe aktarır ve Grove rölesiyle etkileşim kurar.

1. `ADC` sınıfının tanımının altına aşağıdaki kodu ekleyerek bir `GroveRelay` örneği oluşturun:

    ```python
    relay = GroveRelay(5)
    ```

    Bu, röleyi **D5** pinini kullanarak oluşturur; bu, röleyi bağladığınız dijital pindir.

1. Rölenin çalıştığını test etmek için, aşağıdaki kodu `while True:` döngüsüne ekleyin:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod, röleyi açar, 0.5 saniye bekler ve ardından röleyi kapatır.

1. Python uygulamasını çalıştırın. Röle her 10 saniyede bir açılıp kapanacaktır ve açılıp kapanma arasında yarım saniyelik bir gecikme olacaktır. Rölenin açıldığını ve kapandığını duyacaksınız. Röle açıkken Grove kartındaki bir LED yanacak ve kapandığında sönecektir.

    ![Rölenin açılıp kapanması](../../../../../images/relay-turn-on-off.gif)

## Röleyi Toprak Nemine Göre Kontrol Edin

Artık röle çalıştığına göre, toprak nemi ölçümlerine yanıt olarak kontrol edilebilir.

### Görev

Röleyi kontrol edin.

1. Röleyi test etmek için eklediğiniz 3 satır kodu silin. Bunların yerine aşağıdaki kodu ekleyin:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Bu kod, toprak nem sensöründen gelen toprak nem seviyesini kontrol eder. Eğer seviye 450'nin üzerindeyse röleyi açar, 450'nin altına düştüğünde ise kapatır.

    > 💁 Kapasitif toprak nem sensörünün, toprak nem seviyesi ne kadar düşükse, topraktaki nemin o kadar fazla olduğunu ve bunun tersinin de geçerli olduğunu ölçtüğünü unutmayın.

1. Python uygulamasını çalıştırın. Rölenin toprak nem seviyesine bağlı olarak açılıp kapandığını göreceksiniz. Kuru toprakta deneyin, ardından su ekleyin.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Bu kodu [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) klasöründe bulabilirsiniz.

😀 Toprak nem sensörünüzle röle kontrolü programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.