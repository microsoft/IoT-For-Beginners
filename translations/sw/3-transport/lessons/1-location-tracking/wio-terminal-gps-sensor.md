<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T21:41:24+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "sw"
}
-->
# Soma Data za GPS - Wio Terminal

Katika sehemu hii ya somo, utaongeza kihisi cha GPS kwenye Wio Terminal yako, na kusoma thamani kutoka kwake.

## Vifaa

Wio Terminal inahitaji kihisi cha GPS.

Kihisi utakachotumia ni [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Kihisi hiki kinaweza kuunganishwa na mifumo mingi ya GPS kwa kupata maelezo haraka na kwa usahihi. Kihisi hiki kina sehemu mbili - vifaa vya msingi vya kihisi, na antena ya nje iliyounganishwa kwa waya mwembamba ili kupokea mawimbi ya redio kutoka kwa setilaiti.

Hiki ni kihisi cha UART, kwa hivyo kinatuma data ya GPS kupitia UART.

### Unganisha kihisi cha GPS

Kihisi cha Grove GPS kinaweza kuunganishwa na Wio Terminal.

#### Kazi - unganisha kihisi cha GPS

Unganisha kihisi cha GPS.

![Kihisi cha Grove GPS](../../../../../translated_images/sw/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya kihisi cha GPS. Itaingia kwa njia moja tu.

1. Ukiwa umeondoa Wio Terminal kutoka kwa kompyuta yako au chanzo kingine cha umeme, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya upande wa kushoto ya Grove kwenye Wio Terminal ukiangalia skrini. Hii ni soketi iliyo karibu zaidi na kitufe cha kuwasha.

    ![Kihisi cha Grove GPS kimeunganishwa kwenye soketi ya upande wa kushoto](../../../../../translated_images/sw/wio-gps-sensor.19fd52b81ce58095.webp)

1. Weka kihisi cha GPS mahali ambapo antena iliyounganishwa inaweza kuona anga - ikiwezekana karibu na dirisha lililo wazi au nje. Ni rahisi kupata ishara wazi bila kitu chochote kuzuia antena.

1. Sasa unaweza kuunganisha Wio Terminal kwenye kompyuta yako.

1. Kihisi cha GPS kina LED mbili - LED ya bluu inayowaka wakati data inapotumwa, na LED ya kijani inayowaka kila sekunde moja wakati wa kupokea data kutoka kwa setilaiti. Hakikisha LED ya bluu inawaka unapowasha Wio Terminal. Baada ya dakika chache, LED ya kijani itawaka - kama haitawaka, huenda ukahitaji kuhamisha antena.

## Programu ya kihisi cha GPS

Sasa Wio Terminal inaweza kupangwa kutumia kihisi cha GPS kilichounganishwa.

### Kazi - panga kihisi cha GPS

Panga kifaa.

1. Tengeneza mradi mpya wa Wio Terminal ukitumia PlatformIO. Uite mradi huu `gps-sensor`. Ongeza msimbo kwenye kazi ya `setup` ili kusanidi bandari ya serial.

1. Ongeza agizo lifuatalo la kujumuisha mwanzoni mwa faili ya `main.cpp`. Hii inajumuisha faili ya kichwa yenye kazi za kusanidi bandari ya Grove ya upande wa kushoto kwa UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Chini ya hii, ongeza mstari ufuatao wa msimbo ili kutangaza muunganisho wa bandari ya serial kwa bandari ya UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Unahitaji kuongeza msimbo fulani ili kuelekeza baadhi ya vishikilia ishara vya ndani kwenye bandari hii ya serial. Ongeza msimbo ufuatao chini ya tangazo la `Serial3`:

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

1. Katika kazi ya `setup` chini ya pale ambapo bandari ya `Serial` imesanidiwa, sanidi bandari ya serial ya UART kwa msimbo ufuatao:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Chini ya msimbo huu katika kazi ya `setup`, ongeza msimbo ufuatao ili kuunganisha pini ya Grove kwenye bandari ya serial:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Ongeza kazi ifuatayo kabla ya kazi ya `loop` ili kutuma data ya GPS kwenye serial monitor:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Katika kazi ya `loop`, ongeza msimbo ufuatao ili kusoma kutoka kwa bandari ya serial ya UART na kuchapisha matokeo kwenye serial monitor:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Msimbo huu unasoma kutoka kwa bandari ya serial ya UART. Kazi ya `readStringUntil` inasoma hadi tabia ya mwisho, katika kesi hii mstari mpya. Hii itasoma sentensi nzima ya NMEA (sentensi za NMEA zinamalizika na tabia ya mstari mpya). Wakati wote data inaweza kusomwa kutoka kwa bandari ya serial ya UART, inasomwa na kutumwa kwenye serial monitor kupitia kazi ya `printGPSData`. Mara data inapokoma kusomwa, `loop` inachelewa kwa sekunde 1 (1,000ms).

1. Jenga na pakia msimbo kwenye Wio Terminal.

1. Mara baada ya kupakiwa, unaweza kufuatilia data ya GPS ukitumia serial monitor.

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

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Programu yako ya kihisi cha GPS imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.