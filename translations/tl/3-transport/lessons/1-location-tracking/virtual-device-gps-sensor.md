<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-27T23:53:39+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "tl"
}
-->
# Basahin ang GPS Data - Virtual IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng GPS sensor sa iyong virtual na IoT device, at babasahin ang mga halaga mula rito.

## Virtual Hardware

Ang virtual na IoT device ay gagamit ng isang simulated na GPS sensor na maaring ma-access sa pamamagitan ng UART gamit ang serial port.

Ang isang pisikal na GPS sensor ay may antena upang makakuha ng radio waves mula sa mga GPS satellite, at i-convert ang mga GPS signal sa GPS data. Ang virtual na bersyon ay ginagaya ito sa pamamagitan ng pagpapahintulot sa iyo na magtakda ng latitude at longitude, magpadala ng raw na NMEA sentences, o mag-upload ng GPX file na may maraming lokasyon na maaaring ibalik nang sunud-sunod.

> 🎓 Ang NMEA sentences ay tatalakayin sa susunod na bahagi ng aralin

### Idagdag ang Sensor sa CounterFit

Upang magamit ang isang virtual na GPS sensor, kailangan mong magdagdag ng isa sa CounterFit app.

#### Gawain - idagdag ang sensor sa CounterFit

Idagdag ang GPS sensor sa CounterFit app.

1. Gumawa ng bagong Python app sa iyong computer sa isang folder na tinatawag na `gps-sensor` na may isang file na tinatawag na `app.py` at isang Python virtual environment, at idagdag ang CounterFit pip packages.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa paggawa at pag-set up ng CounterFit Python project sa aralin 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Mag-install ng karagdagang Pip package upang mag-install ng CounterFit shim na maaaring makipag-usap sa mga UART-based sensors sa pamamagitan ng serial connection. Siguraduhing ini-install mo ito mula sa terminal na may naka-activate na virtual environment.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Siguraduhing tumatakbo ang CounterFit web app.

1. Gumawa ng GPS sensor:

    1. Sa *Create sensor* box sa *Sensors* pane, i-drop down ang *Sensor type* box at piliin ang *UART GPS*.

    1. Iwanang nakatakda ang *Port* sa */dev/ttyAMA0*.

    1. Piliin ang **Add** button upang lumikha ng GPS sensor sa port `/dev/ttyAMA0`.

    ![Ang mga setting ng GPS sensor](../../../../../translated_images/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.tl.png)

    Ang GPS sensor ay malilikha at lilitaw sa listahan ng mga sensor.

    ![Ang nalikhang GPS sensor](../../../../../translated_images/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.tl.png)

## Iprograma ang GPS Sensor

Ang Virtual IoT device ay maaari nang i-program upang magamit ang virtual na GPS sensor.

### Gawain - iprograma ang GPS sensor

Iprograma ang GPS sensor app.

1. Siguraduhing bukas ang `gps-sensor` app sa VS Code.

1. Buksan ang `app.py` file.

1. Idagdag ang sumusunod na code sa itaas ng `app.py` upang ikonekta ang app sa CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Idagdag ang sumusunod na code sa ibaba nito upang mag-import ng ilang kinakailangang libraries, kabilang ang library para sa CounterFit serial port:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Ang code na ito ay nag-i-import ng `serial` module mula sa `counterfit_shims_serial` Pip package. Pagkatapos ay kumokonekta ito sa `/dev/ttyAMA0` serial port - ito ang address ng serial port na ginagamit ng virtual GPS sensor para sa UART port nito.

1. Idagdag ang sumusunod na code sa ibaba nito upang basahin mula sa serial port at i-print ang mga halaga sa console:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Ang isang function na tinatawag na `print_gps_data` ay tinukoy na nagpi-print ng linya na ipinasa rito sa console.

    Pagkatapos, ang code ay paulit-ulit na nagbabasa ng maraming linya ng teksto mula sa serial port sa bawat loop. Tinatawag nito ang `print_gps_data` function para sa bawat linya.

    Matapos mabasa ang lahat ng data, ang loop ay natutulog ng 1 segundo, pagkatapos ay susubukang muli.

1. Patakbuhin ang code na ito, siguraduhing gumagamit ka ng ibang terminal mula sa terminal kung saan tumatakbo ang CounterFit app, upang manatiling tumatakbo ang CounterFit app.

1. Mula sa CounterFit app, baguhin ang halaga ng GPS sensor. Maaari mo itong gawin sa isa sa mga sumusunod na paraan:

    * Itakda ang **Source** sa `Lat/Lon`, at magtakda ng tiyak na latitude, longitude, at bilang ng mga satellite na ginamit upang makuha ang GPS fix. Ang halagang ito ay ipapadala nang isang beses lamang, kaya i-check ang **Repeat** box upang maulit ang data bawat segundo.

      ![Ang GPS sensor na may lat lon na napili](../../../../../translated_images/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.tl.png)

    * Itakda ang **Source** sa `NMEA` at magdagdag ng ilang NMEA sentences sa text box. Ang lahat ng mga halagang ito ay ipapadala, na may delay na 1 segundo bago mabasa ang bawat bagong GGA (position fix) sentence.

      ![Ang GPS sensor na may NMEA sentences na nakatakda](../../../../../translated_images/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.tl.png)

      Maaari kang gumamit ng tool tulad ng [nmeagen.org](https://www.nmeagen.org) upang bumuo ng mga sentences na ito sa pamamagitan ng pagguhit sa mapa. Ang mga halagang ito ay ipapadala nang isang beses lamang, kaya i-check ang **Repeat** box upang maulit ang data isang segundo pagkatapos maipadala ang lahat.

    * Itakda ang **Source** sa GPX file, at mag-upload ng GPX file na may mga lokasyon ng track. Maaari kang mag-download ng GPX files mula sa iba't ibang sikat na mapping at hiking sites, tulad ng [AllTrails](https://www.alltrails.com/). Ang mga file na ito ay naglalaman ng maraming GPS lokasyon bilang isang trail, at ang GPS sensor ay magbabalik ng bawat bagong lokasyon sa 1 segundo na pagitan.

      ![Ang GPS sensor na may GPX file na nakatakda](../../../../../translated_images/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.tl.png)

      Ang mga halagang ito ay ipapadala nang isang beses lamang, kaya i-check ang **Repeat** box upang maulit ang data isang segundo pagkatapos maipadala ang lahat.

    Kapag na-configure mo na ang mga setting ng GPS, piliin ang **Set** button upang i-commit ang mga halagang ito sa sensor.

1. Makikita mo ang raw output mula sa GPS sensor, na maaaring ganito:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Maaari mong makita ang code na ito sa [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device) folder.

😀 Tagumpay ang iyong GPS sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.