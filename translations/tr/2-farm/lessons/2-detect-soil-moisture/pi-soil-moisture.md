# Toprak Nemini Ölç - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'ye kapasitif bir toprak nem sensörü ekleyecek ve ondan değerler okuyacaksınız.

## Donanım

Raspberry Pi, kapasitif bir toprak nem sensörüne ihtiyaç duyar.

Kullanacağınız sensör, toprağın kapasitansını algılayarak toprak nemini ölçen bir [Kapasitif Toprak Nem Sensörü](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html). Toprağın nemi değiştikçe bu özellik de değişir. Toprak nemi arttıkça, voltaj azalır.

Bu bir analog sensördür, bu nedenle bir analog pin kullanır ve Pi üzerindeki Grove Base Hat'teki 10-bit ADC, voltajı 1-1.023 arasında bir dijital sinyale dönüştürür. Bu sinyal daha sonra Pi üzerindeki GPIO pinleri üzerinden I²C ile gönderilir.

### Toprak nem sensörünü bağlayın

Grove toprak nem sensörü Raspberry Pi'ye bağlanabilir.

#### Görev - Toprak nem sensörünü bağlayın

Toprak nem sensörünü bağlayın.

![Bir Grove toprak nem sensörü](../../../../../translated_images/tr/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Grove kablosunun bir ucunu toprak nem sensöründeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Raspberry Pi kapalıyken, Grove kablosunun diğer ucunu Pi'ye bağlı Grove Base Hat üzerindeki **A0** olarak işaretlenmiş analog sokete bağlayın. Bu soket, GPIO pinlerinin yanındaki soket sırasının sağdan ikinci soketidir.

![Grove toprak nem sensörü A0 soketine bağlı](../../../../../translated_images/tr/pi-soil-moisture-sensor.fdd7eb2393792cf6.webp)

1. Toprak nem sensörünü toprağa yerleştirin. Sensör üzerinde bir 'en yüksek pozisyon çizgisi' - beyaz bir çizgi bulunur. Sensörü bu çizgiye kadar, ancak çizgiyi geçmeyecek şekilde yerleştirin.

![Toprakta Grove toprak nem sensörü](../../../../../translated_images/tr/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Toprak nem sensörünü programlayın

Raspberry Pi artık bağlı toprak nem sensörünü kullanacak şekilde programlanabilir.

### Görev - Toprak nem sensörünü programlayın

Cihazı programlayın.

1. Pi'yi açın ve başlatılmasını bekleyin.

1. VS Code'u doğrudan Pi üzerinde veya Remote SSH uzantısı aracılığıyla bağlanarak başlatın.

    > ⚠️ Gerekirse [nightlight - ders 1'de VS Code'u kurma ve başlatma talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md) başvurabilirsiniz.

1. Terminalden, `pi` kullanıcısının ana dizininde `soil-moisture-sensor` adında yeni bir klasör oluşturun. Bu klasörde `app.py` adında bir dosya oluşturun.

1. Bu klasörü VS Code'da açın.

1. Gerekli kütüphaneleri içe aktarmak için `app.py` dosyasına aşağıdaki kodu ekleyin:

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time` ifadesi, bu görevde daha sonra kullanılacak olan `time` modülünü içe aktarır.

    `from grove.adc import ADC` ifadesi, Grove Python kütüphanelerinden `ADC`'yi içe aktarır. Bu kütüphane, Pi base hat üzerindeki analog-dijital dönüştürücü ile etkileşim kurmak ve analog sensörlerden voltaj okumak için kod içerir.

1. `ADC` sınıfının bir örneğini oluşturmak için aşağıdaki kodu ekleyin:

    ```python
    adc = ADC()
    ```

1. A0 pinindeki bu ADC'den okuma yapan ve sonucu konsola yazan sonsuz bir döngü ekleyin. Bu döngü, okumalar arasında 10 saniye bekleyebilir.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Python uygulamasını çalıştırın. Toprak nem ölçümlerinin konsola yazıldığını göreceksiniz. Toprağa biraz su ekleyin veya sensörü topraktan çıkarın ve değerin değiştiğini gözlemleyin.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Yukarıdaki örnek çıktıda, su eklendikçe voltajın düştüğünü görebilirsiniz.

> 💁 Bu kodu [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) klasöründe bulabilirsiniz.

😀 Toprak nem sensörü programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.