<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-27T23:47:04+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "tl"
}
-->
# Basahin ang GPS Data - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng GPS sensor sa iyong Raspberry Pi at babasahin ang mga halaga mula rito.

## Kagamitan

Kailangan ng Raspberry Pi ng GPS sensor.

Ang sensor na gagamitin mo ay ang [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ang sensor na ito ay maaaring kumonekta sa maraming GPS system para sa mabilis at tumpak na pagkuha ng lokasyon. Binubuo ang sensor ng 2 bahagi - ang pangunahing electronics ng sensor at isang panlabas na antena na nakakabit sa pamamagitan ng manipis na kawad upang makuha ang mga radio wave mula sa mga satellite.

Ito ay isang UART sensor, kaya't nagpapadala ito ng GPS data gamit ang UART.

## Ikonekta ang GPS Sensor

Maaaring ikonekta ang Grove GPS sensor sa Raspberry Pi.

### Gawain - Ikonekta ang GPS Sensor

Ikonekta ang GPS sensor.

![Isang Grove GPS sensor](../../../../../translated_images/tl/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng GPS sensor. Isang paraan lamang ang tamang pagpasok nito.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa UART socket na may markang **UART** sa Grove Base hat na nakakabit sa Pi. Ang socket na ito ay nasa gitnang hilera, sa gilid na pinakamalapit sa SD Card slot, sa kabilang dulo mula sa mga USB port at ethernet socket.

    ![Ang Grove GPS sensor na nakakonekta sa UART socket](../../../../../translated_images/tl/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Ilagay ang GPS sensor sa posisyon kung saan ang nakakabit na antena ay may malinaw na tanaw sa kalangitan - mas mainam kung malapit sa isang bukas na bintana o sa labas. Mas madali itong makakuha ng malinaw na signal kung walang nakaharang sa antena.

## Iprograma ang GPS Sensor

Ngayon ay maaaring i-program ang Raspberry Pi upang magamit ang nakakabit na GPS sensor.

### Gawain - Iprograma ang GPS Sensor

Iprograma ang device.

1. I-on ang Pi at hintaying mag-boot.

1. Ang GPS sensor ay may 2 LED - isang asul na LED na kumikislap kapag nagpapadala ng data, at isang berdeng LED na kumikislap bawat segundo kapag tumatanggap ng data mula sa mga satellite. Siguraduhing kumikislap ang asul na LED kapag in-on mo ang Pi. Pagkalipas ng ilang minuto, ang berdeng LED ay magsisimulang kumislap - kung hindi, maaaring kailanganin mong ilipat ang posisyon ng antena.

1. Ilunsad ang VS Code, alinman direkta sa Pi, o kumonekta gamit ang Remote SSH extension.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa pag-set up at paglulunsad ng VS Code sa aralin 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Sa mga mas bagong bersyon ng Raspberry Pi na may suporta sa Bluetooth, mayroong conflict sa pagitan ng serial port na ginagamit para sa Bluetooth at ng isa na ginagamit ng Grove UART port. Upang ayusin ito, gawin ang mga sumusunod:

    1. Mula sa terminal ng VS Code, i-edit ang file na `/boot/config.txt` gamit ang `nano`, isang built-in na text editor sa terminal, gamit ang sumusunod na command:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Ang file na ito ay hindi maaaring i-edit gamit ang VS Code dahil kailangan itong i-edit gamit ang `sudo` permissions, o mas mataas na antas ng pahintulot. Ang VS Code ay hindi tumatakbo gamit ang ganitong pahintulot.

    1. Gamitin ang mga cursor keys upang pumunta sa dulo ng file, pagkatapos ay kopyahin ang code sa ibaba at i-paste ito sa dulo ng file:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Maaari kang mag-paste gamit ang normal na keyboard shortcuts para sa iyong device (`Ctrl+v` sa Windows, Linux o Raspberry Pi OS, `Cmd+v` sa macOS).

    1. I-save ang file na ito at lumabas sa nano sa pamamagitan ng pagpindot sa `Ctrl+x`. Pindutin ang `y` kapag tinanong kung nais mong i-save ang binagong buffer, pagkatapos ay pindutin ang `enter` upang kumpirmahin na nais mong i-overwrite ang `/boot/config.txt`.

        > Kung nagkamali ka, maaari kang lumabas nang hindi nagse-save, pagkatapos ay ulitin ang mga hakbang na ito.

    1. I-edit ang file na `/boot/cmdline.txt` sa nano gamit ang sumusunod na command:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Ang file na ito ay may maraming key/value pairs na pinaghihiwalay ng mga espasyo. Alisin ang anumang key/value pairs para sa key na `console`. Malamang na ganito ang hitsura:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Maaari kang gumamit ng cursor keys upang pumunta sa mga entry na ito, pagkatapos ay tanggalin gamit ang normal na `del` o `backspace` keys.

        Halimbawa, kung ganito ang orihinal na file:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Ang bagong bersyon ay magiging ganito:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Sundin ang mga hakbang sa itaas upang i-save ang file na ito at lumabas sa nano.

    1. I-reboot ang iyong Pi, pagkatapos ay muling kumonekta sa VS Code kapag ang Pi ay na-reboot na.

1. Mula sa terminal, gumawa ng bagong folder sa home directory ng user na `pi` na tinatawag na `gps-sensor`. Gumawa ng file sa folder na ito na tinatawag na `app.py`.

1. Buksan ang folder na ito sa VS Code.

1. Ang GPS module ay nagpapadala ng UART data sa isang serial port. I-install ang `pyserial` Pip package upang makipag-ugnayan sa serial port mula sa iyong Python code:

    ```sh
    pip3 install pyserial
    ```

1. Idagdag ang sumusunod na code sa iyong `app.py` file:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Ang code na ito ay nag-i-import ng `serial` module mula sa `pyserial` Pip package. Pagkatapos ay kumokonekta ito sa `/dev/ttyAMA0` serial port - ito ang address ng serial port na ginagamit ng Grove Pi Base Hat para sa UART port nito. Nililinis din nito ang anumang umiiral na data mula sa serial connection na ito.

    Susunod, isang function na tinatawag na `print_gps_data` ang tinutukoy na nagpi-print ng linya na ipinasa rito sa console.

    Pagkatapos, ang code ay paulit-ulit na nagbabasa ng maraming linya ng teksto mula sa serial port sa bawat loop. Tinatawag nito ang `print_gps_data` function para sa bawat linya.

    Pagkatapos mabasa ang lahat ng data, ang loop ay natutulog ng 1 segundo, pagkatapos ay muling susubukan.

1. Patakbuhin ang code na ito. Makikita mo ang raw output mula sa GPS sensor, na maaaring ganito:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Kung makakakuha ka ng isa sa mga sumusunod na error kapag pinapatigil at muling pinapatakbo ang iyong code, magdagdag ng `try - except` block sa iyong while loop.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Maaari mong makita ang code na ito sa [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) folder.

😀 Tagumpay ang iyong programa para sa GPS sensor!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.