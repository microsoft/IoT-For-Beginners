<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T03:15:34+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "tr"
}
-->
# GPS Verilerini Çözümleme - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi veya Sanal IoT Cihazı tarafından GPS sensöründen okunan NMEA mesajlarını çözümleyecek ve enlem ile boylam bilgilerini çıkaracaksınız.

## GPS Verilerini Çözümleme

Ham NMEA verileri seri porttan okunduktan sonra, açık kaynaklı bir NMEA kütüphanesi kullanılarak çözümlenebilir.

### Görev - GPS verilerini çözümleme

Cihazı GPS verilerini çözümleyecek şekilde programlayın.

1. `gps-sensor` uygulama projesini henüz açmadıysanız açın.

1. `pynmea2` Pip paketini yükleyin. Bu paket, NMEA mesajlarını çözümlemek için kod içerir.

    ```sh
    pip3 install pynmea2
    ```

1. `app.py` dosyasındaki importlara aşağıdaki kodu ekleyerek `pynmea2` modülünü içe aktarın:

    ```python
    import pynmea2
    ```

1. `print_gps_data` fonksiyonunun içeriğini aşağıdaki kodla değiştirin:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Bu kod, UART seri portundan okunan satırı çözümlemek için `pynmea2` kütüphanesini kullanır.

    Mesajın cümle türü `GGA` ise, bu bir konum sabitleme mesajıdır ve işlenir. Mesajdan enlem ve boylam değerleri okunur ve NMEA `(d)ddmm.mmmm` formatından ondalık dereceye dönüştürülür. `dm_to_sd` fonksiyonu bu dönüşümü gerçekleştirir.

    Daha sonra enlemin yönü kontrol edilir ve eğer enlem güneyde ise, değer negatif bir sayıya dönüştürülür. Aynı şekilde, boylam batıda ise negatif bir sayıya dönüştürülür.

    Son olarak, koordinatlar konsola yazdırılır ve konumu belirlemek için kullanılan uydu sayısı da gösterilir.

1. Kodu çalıştırın. Eğer sanal bir IoT cihazı kullanıyorsanız, CounterFit uygulamasının çalıştığından ve GPS verilerinin gönderildiğinden emin olun.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Bu kodu [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) klasöründe veya [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) klasöründe bulabilirsiniz.

😀 GPS sensör programınız veri çözümleme ile başarıyla tamamlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.