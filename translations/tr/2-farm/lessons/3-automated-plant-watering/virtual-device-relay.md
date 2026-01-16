<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-28T04:17:33+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "tr"
}
-->
# Röle Kontrolü - Sanal IoT Donanımı

Bu dersin bu bölümünde, sanal IoT cihazınıza toprak nem sensörüne ek olarak bir röle ekleyecek ve toprak nem seviyesine göre kontrol edeceksiniz.

## Sanal Donanım

Sanal IoT cihazı, simüle edilmiş bir Grove rölesi kullanacaktır. Bu, bu laboratuvarı fiziksel bir Grove rölesi ile bir Raspberry Pi kullanmaya benzer hale getirir.

Fiziksel bir IoT cihazında, röle genellikle normalde açık bir röle olur (yani, röleye sinyal gönderilmediğinde çıkış devresi açık veya bağlantısızdır). Bu tür bir röle, 250V ve 10A'ya kadar çıkış devrelerini kontrol edebilir.

### Röleyi CounterFit'e Ekleme

Sanal bir röle kullanmak için, bunu CounterFit uygulamasına eklemeniz gerekir.

#### Görev

Röleyi CounterFit uygulamasına ekleyin.

1. VS Code'da önceki dersten `soil-moisture-sensor` projesini açın (henüz açık değilse). Bu projeye ekleme yapacaksınız.

1. CounterFit web uygulamasının çalıştığından emin olun.

1. Bir röle oluşturun:

    1. *Actuators* panelindeki *Create actuator* kutusunda, *Actuator type* açılır menüsünden *Relay* seçeneğini seçin.

    1. *Pin* değerini *5* olarak ayarlayın.

    1. Röleyi Pin 5 üzerinde oluşturmak için **Add** düğmesini seçin.

    ![Röle ayarları](../../../../../translated_images/tr/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Röle oluşturulacak ve aktüatörler listesinde görünecektir.

    ![Oluşturulan röle](../../../../../translated_images/tr/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Röleyi Programlama

Toprak nem sensörü uygulaması artık sanal röleyi kullanacak şekilde programlanabilir.

### Görev

Sanal cihazı programlayın.

1. VS Code'da önceki dersten `soil-moisture-sensor` projesini açın (henüz açık değilse). Bu projeye ekleme yapacaksınız.

1. Aşağıdaki kodu mevcut import ifadelerinin altına, `app.py` dosyasına ekleyin:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Bu ifade, sanal Grove rölesiyle etkileşim kurmak için Grove Python shim kütüphanelerinden `GroveRelay` sınıfını içe aktarır.

1. `ADC` sınıfının tanımının altına aşağıdaki kodu ekleyerek bir `GroveRelay` örneği oluşturun:

    ```python
    relay = GroveRelay(5)
    ```

    Bu, röleyi bağladığınız pin olan **5** numaralı pini kullanarak bir röle oluşturur.

1. Rölenin çalıştığını test etmek için, `while True:` döngüsüne aşağıdaki kodu ekleyin:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod, röleyi açar, 0.5 saniye bekler ve ardından röleyi kapatır.

1. Python uygulamasını çalıştırın. Röle her 10 saniyede bir açılıp kapanacak ve açılıp kapanma arasında yarım saniyelik bir gecikme olacaktır. CounterFit uygulamasında sanal rölenin açılıp kapandığını göreceksiniz.

    ![Sanal rölenin açılıp kapanması](../../../../../images/virtual-relay-turn-on-off.gif)

## Röleyi Toprak Nemine Göre Kontrol Etme

Artık röle çalıştığına göre, toprak nemi okumalarına göre kontrol edilebilir.

### Görev

Röleyi kontrol edin.

1. Röleyi test etmek için eklediğiniz 3 satırlık kodu silin. Yerine aşağıdaki kodu ekleyin:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Bu kod, toprak nem sensöründen gelen nem seviyesini kontrol eder. Eğer değer 450'nin üzerindeyse röleyi açar, 450'nin altına düştüğünde ise kapatır.

    > 💁 Kapasitif toprak nem sensörünün, toprak nem seviyesi düştükçe topraktaki nemin arttığını ve tam tersini okuduğunu unutmayın.

1. Python uygulamasını çalıştırın. Toprak nem seviyelerine bağlı olarak rölenin açılıp kapandığını göreceksiniz. Toprak nem sensörü için *Value* veya *Random* ayarlarını değiştirerek değerin değiştiğini gözlemleyin.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Bu kodu [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) klasöründe bulabilirsiniz.

😀 Sanal toprak nem sensörünüzle röle kontrol programınız başarıyla tamamlandı!

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlama veya yanlış yorumlamalardan sorumlu değiliz.