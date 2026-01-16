<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T23:39:59+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "tl"
}
-->
# Basahin ang GPS Data - Wio Terminal

Sa bahaging ito ng aralin, magdadagdag ka ng GPS sensor sa iyong Wio Terminal at babasahin ang mga halaga mula rito.

## Kagamitan

Kailangan ng Wio Terminal ng GPS sensor.

Ang sensor na gagamitin mo ay ang [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ang sensor na ito ay maaaring kumonekta sa maraming GPS system para sa mabilis at tumpak na pagkuha ng lokasyon. Binubuo ang sensor ng 2 bahagi - ang pangunahing electronics ng sensor at isang panlabas na antena na nakakabit sa pamamagitan ng manipis na kawad upang makuha ang mga radio wave mula sa mga satellite.

Ito ay isang UART sensor, kaya't ipinapadala nito ang GPS data sa pamamagitan ng UART.

### Ikonekta ang GPS Sensor

Maaaring ikonekta ang Grove GPS sensor sa Wio Terminal.

#### Gawain - ikonekta ang GPS sensor

Ikonekta ang GPS sensor.

![Isang Grove GPS sensor](../../../../../translated_images/tl/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng GPS sensor. Isang direksyon lamang ang tamang paraan ng pagpasok nito.

1. Habang ang Wio Terminal ay hindi nakakonekta sa iyong computer o iba pang power supply, ikonekta ang kabilang dulo ng Grove cable sa kaliwang Grove socket ng Wio Terminal habang nakaharap ka sa screen. Ito ang socket na pinakamalapit sa power button.

    ![Ang Grove GPS sensor na nakakonekta sa kaliwang socket](../../../../../translated_images/tl/wio-gps-sensor.19fd52b81ce58095.webp)

1. Iposisyon ang GPS sensor upang ang nakakabit na antena ay may malinaw na tanaw sa kalangitan - mas mainam kung malapit sa isang bukas na bintana o sa labas. Mas madali itong makakuha ng malinaw na signal kung walang nakaharang sa antena.

1. Maaari mo nang ikonekta ang Wio Terminal sa iyong computer.

1. Ang GPS sensor ay may 2 LED - isang asul na LED na kumikislap kapag may ipinapadalang data, at isang berdeng LED na kumikislap bawat segundo kapag tumatanggap ng data mula sa mga satellite. Siguraduhing kumikislap ang asul na LED kapag binuksan mo ang Wio Terminal. Pagkalipas ng ilang minuto, ang berdeng LED ay magsisimulang kumislap - kung hindi, maaaring kailangan mong ilipat ang posisyon ng antena.

## Iprograma ang GPS Sensor

Ngayon ay maaari nang iprograma ang Wio Terminal upang magamit ang nakakabit na GPS sensor.

### Gawain - iprograma ang GPS sensor

Iprograma ang device.

1. Gumawa ng bagong Wio Terminal project gamit ang PlatformIO. Tawagin ang proyektong ito na `gps-sensor`. Magdagdag ng code sa `setup` function upang i-configure ang serial port.

1. Idagdag ang sumusunod na include directive sa itaas ng `main.cpp` file. Kasama rito ang header file na may mga function para i-configure ang kaliwang Grove port para sa UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Sa ibaba nito, idagdag ang sumusunod na linya ng code upang ideklara ang isang serial port connection sa UART port:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Kailangan mong magdagdag ng ilang code upang i-redirect ang ilang internal signal handlers sa serial port na ito. Idagdag ang sumusunod na code sa ibaba ng deklarasyon ng `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. Sa `setup` function sa ibaba ng kung saan naka-configure ang `Serial` port, i-configure ang UART serial port gamit ang sumusunod na code:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Sa ibaba ng code na ito sa `setup` function, idagdag ang sumusunod na code upang ikonekta ang Grove pin sa serial port:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Idagdag ang sumusunod na function bago ang `loop` function upang ipadala ang GPS data sa serial monitor:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Sa `loop` function, idagdag ang sumusunod na code upang basahin mula sa UART serial port at i-print ang output sa serial monitor:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Binabasa ng code na ito ang data mula sa UART serial port. Ang `readStringUntil` function ay nagbabasa hanggang sa isang terminator character, sa kasong ito ay isang bagong linya. Babasahin nito ang isang buong NMEA sentence (ang mga NMEA sentence ay nagtatapos sa isang bagong linya na character). Habang may data na mababasa mula sa UART serial port, ito ay babasahin at ipapadala sa serial monitor gamit ang `printGPSData` function. Kapag wala nang mababasang data, ang `loop` ay maghihintay ng 1 segundo (1,000ms).

1. I-build at i-upload ang code sa Wio Terminal.

1. Kapag na-upload na, maaari mong i-monitor ang GPS data gamit ang serial monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Makikita mo ang code na ito sa [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) folder.

😀 Tagumpay ang iyong GPS sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.