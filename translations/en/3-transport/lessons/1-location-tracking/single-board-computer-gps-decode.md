<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T19:38:26+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "en"
}
-->
# Decode GPS data - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will decode the NMEA messages read from the GPS sensor by the Raspberry Pi or Virtual IoT Device, and extract the latitude and longitude.

## Decode GPS data

Once the raw NMEA data has been read from the serial port, it can be decoded using an open-source NMEA library.

### Task - decode GPS data

Program the device to decode the GPS data.

1. Open the `gps-sensor` app project if it's not already open.

1. Install the `pynmea2` Pip package. This package contains code for decoding NMEA messages.

    ```sh
    pip3 install pynmea2
    ```

1. Add the following code to the imports in the `app.py` file to import the `pynmea2` module:

    ```python
    import pynmea2
    ```

1. Replace the contents of the `print_gps_data` function with the following:

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

    This code will use the `pynmea2` library to parse the line read from the UART serial port.

    If the sentence type of the message is `GGA`, then this is a position fix message and is processed. The latitude and longitude values are read from the message and converted to decimal degrees from the NMEA `(d)ddmm.mmmm` format. The `dm_to_sd` function performs this conversion.

    The direction of the latitude is then checked, and if the latitude is south, the value is converted to a negative number. Similarly, if the longitude is west, it is converted to a negative number.

    Finally, the coordinates are printed to the console, along with the number of satellites used to determine the location.

1. Run the code. If you are using a virtual IoT device, ensure the CounterFit app is running and the GPS data is being sent.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 You can find this code in the [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) folder, or the [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) folder.

😀 Your GPS sensor program with data decoding was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.