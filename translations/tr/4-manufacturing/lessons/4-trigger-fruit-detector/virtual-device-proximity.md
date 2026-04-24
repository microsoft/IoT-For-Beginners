# Yakınlık Algılama - Sanal IoT Donanımı

Bu dersin bu bölümünde, sanal IoT cihazınıza bir yakınlık sensörü ekleyecek ve mesafeyi okuyacaksınız.

## Donanım

Sanal IoT cihazı, simüle edilmiş bir mesafe sensörü kullanacak.

Fiziksel bir IoT cihazında, mesafeyi algılamak için lazer ölçüm modülüne sahip bir sensör kullanılır.

### Mesafe sensörünü CounterFit'e ekleyin

Sanal bir mesafe sensörü kullanmak için CounterFit uygulamasına bir sensör eklemeniz gerekiyor.

#### Görev - Mesafe sensörünü CounterFit'e ekleyin

Mesafe sensörünü CounterFit uygulamasına ekleyin.

1. VS Code'da `fruit-quality-detector` kodunu açın ve sanal ortamın etkin olduğundan emin olun.

1. Mesafe sensörleriyle konuşabilen bir CounterFit shim'i yüklemek için ek bir Pip paketi yükleyin. Bu shim, [rpi-vl53l0x Pip paketi](https://pypi.org/project/rpi-vl53l0x/) adlı bir Python paketi ile [VL53L0X uçuş süresi mesafe sensörü](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) simülasyonu yapar. Sanal ortamın etkin olduğu bir terminalden yüklediğinizden emin olun.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. CounterFit web uygulamasının çalıştığından emin olun.

1. Bir mesafe sensörü oluşturun:

    1. *Sensors* panelindeki *Create sensor* kutusunda, *Sensor type* açılır kutusundan *Distance* seçeneğini seçin.

    1. *Units* kısmını `Millimeter` olarak bırakın.

    1. Bu sensör bir I²C sensörüdür, bu yüzden adresi `0x29` olarak ayarlayın. Fiziksel bir VL53L0X sensörü kullansaydınız, bu adres sabit kodlanmış olurdu.

    1. Mesafe sensörünü oluşturmak için **Add** düğmesini seçin.

    ![Mesafe sensörü ayarları](../../../../../translated_images/tr/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Mesafe sensörü oluşturulacak ve sensörler listesinde görünecek.

    ![Oluşturulan mesafe sensörü](../../../../../translated_images/tr/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Mesafe sensörünü programlayın

Sanal IoT cihazı artık simüle edilmiş mesafe sensörünü kullanacak şekilde programlanabilir.

### Görev - Uçuş süresi sensörünü programlayın

1. `fruit-quality-detector` projesinde `distance-sensor.py` adlı yeni bir dosya oluşturun.

    > 💁 Birden fazla IoT cihazını simüle etmenin kolay bir yolu, her birini farklı bir Python dosyasında yapmak ve ardından aynı anda çalıştırmaktır.

1. CounterFit ile bir bağlantı başlatmak için aşağıdaki kodu ekleyin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Bunun altına aşağıdaki kodu ekleyin:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Bu, VL53L0X uçuş süresi sensörü için sensör kütüphanesi shim'ini içe aktarır.

1. Bunun altına sensöre erişmek için aşağıdaki kodu ekleyin:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Bu kod bir mesafe sensörü tanımlar ve ardından sensörü başlatır.

1. Son olarak, mesafeleri okumak için sonsuz bir döngü ekleyin:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Bu kod, sensörden bir değer okumaya hazır olana kadar bekler ve ardından konsola yazdırır.

1. Bu kodu çalıştırın.

    > 💁 Bu dosyanın adı `distance-sensor.py`! Python ile çalıştırdığınızdan emin olun, `app.py` ile değil.

1. Konsolda mesafe ölçümleri görünecek. CounterFit'teki değeri değiştirin veya rastgele değerler kullanın.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Bu kodu [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Yakınlık sensörü programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.