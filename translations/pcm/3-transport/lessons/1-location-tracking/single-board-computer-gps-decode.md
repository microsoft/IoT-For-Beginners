<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-11-18T19:08:11+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "pcm"
}
-->
# Decode GPS data - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go decode di NMEA messages wey di GPS sensor read from di Raspberry Pi or Virtual IoT Device, and you go comot di latitude and longitude.

## Decode GPS data

Once you don read di raw NMEA data from di serial port, you fit decode am using one open source NMEA library.

### Task - decode GPS data

Program di device make e decode di GPS data.

1. Open di `gps-sensor` app project if e never open before.

1. Install di `pynmea2` Pip package. Dis package get code wey fit decode NMEA messages.

    ```sh
    pip3 install pynmea2
    ```

1. Add dis code to di imports for di `app.py` file to import di `pynmea2` module:

    ```python
    import pynmea2
    ```

1. Change wetin dey inside di `print_gps_data` function to dis one:

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

    Dis code go use di `pynmea2` library to parse di line wey e read from di UART serial port.

    If di sentence type for di message na `GGA`, e mean say na position fix message, and e go process am. Di latitude and longitude values go dey read from di message and e go convert am to decimal degrees from di NMEA `(d)ddmm.mmmm` format. Di `dm_to_sd` function na im dey do dis conversion.

    Di direction for di latitude go dey check, and if di latitude dey south, di value go change to negative number. Same thing for longitude, if e dey west, e go change to negative number.

    At di end, di coordinates go show for di console, plus di number of satellites wey dem use to get di location.

1. Run di code. If you dey use virtual IoT device, make sure say di CounterFit app dey run and di GPS data dey send.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 You fit find dis code for di [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) folder, or di [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) folder.

😀 Your GPS sensor program wey decode data don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) do di translation. Even as we dey try make am accurate, abeg sabi say machine translation fit get mistake or no dey correct well. Di original dokyument wey dey for im native language na di one wey you go take as di correct source. For important mata, e good make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->