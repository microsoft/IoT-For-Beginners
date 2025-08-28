<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T23:52:42+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "tl"
}
-->
# I-decode ang GPS data - Virtual IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, ide-decode mo ang mga NMEA message na nabasa mula sa GPS sensor gamit ang Raspberry Pi o Virtual IoT Device, at kukunin ang latitude at longitude.

## I-decode ang GPS data

Kapag nabasa na ang raw NMEA data mula sa serial port, maaari itong i-decode gamit ang isang open source na NMEA library.

### Gawain - i-decode ang GPS data

I-program ang device upang i-decode ang GPS data.

1. Buksan ang proyekto ng `gps-sensor` app kung hindi pa ito bukas.

1. I-install ang `pynmea2` Pip package. Ang package na ito ay may code para sa pag-decode ng mga NMEA message.

    ```sh
    pip3 install pynmea2
    ```

1. Idagdag ang sumusunod na code sa mga imports sa file na `app.py` upang i-import ang `pynmea2` module:

    ```python
    import pynmea2
    ```

1. Palitan ang nilalaman ng function na `print_gps_data` ng sumusunod:

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

    Ang code na ito ay gagamit ng `pynmea2` library upang i-parse ang linya na nabasa mula sa UART serial port.

    Kung ang uri ng sentence ng message ay `GGA`, ito ay isang position fix message at ipoproseso. Ang latitude at longitude na mga halaga ay babasahin mula sa message at iko-convert sa decimal degrees mula sa NMEA `(d)ddmm.mmmm` format. Ang function na `dm_to_sd` ang gumagawa ng conversion na ito.

    Susuriin din ang direksyon ng latitude, at kung ang latitude ay nasa timog, iko-convert ang halaga sa negatibong numero. Ganoon din sa longitude, kung ito ay nasa kanluran, iko-convert ito sa negatibong numero.

    Sa huli, ipi-print ang mga coordinate sa console, kasama ang bilang ng mga satellite na ginamit upang makuha ang lokasyon.

1. Patakbuhin ang code. Kung gumagamit ka ng virtual IoT device, siguraduhing tumatakbo ang CounterFit app at ipinapadala ang GPS data.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Maaari mong mahanap ang code na ito sa [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) folder, o sa [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) folder.

😀 Tagumpay ang iyong GPS sensor program na may data decoding!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.