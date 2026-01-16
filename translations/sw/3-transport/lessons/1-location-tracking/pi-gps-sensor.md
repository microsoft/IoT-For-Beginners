<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-27T21:39:59+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "sw"
}
-->
# Soma data za GPS - Raspberry Pi

Katika sehemu hii ya somo, utaongeza kihisi cha GPS kwenye Raspberry Pi yako, na kusoma maadili kutoka kwake.

## Vifaa

Raspberry Pi inahitaji kihisi cha GPS.

Kihisi utakachotumia ni [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Kihisi hiki kinaweza kuunganishwa na mifumo mbalimbali ya GPS kwa usahihi wa haraka. Kihisi hiki kina sehemu mbili - sehemu ya kielektroniki ya kihisi, na antena ya nje iliyounganishwa kwa waya mwembamba ili kupokea mawimbi ya redio kutoka kwa satelaiti.

Hiki ni kihisi cha UART, kwa hivyo kinatuma data ya GPS kupitia UART.

## Unganisha kihisi cha GPS

Kihisi cha Grove GPS kinaweza kuunganishwa na Raspberry Pi.

### Kazi - unganisha kihisi cha GPS

Unganisha kihisi cha GPS.

![Kihisi cha Grove GPS](../../../../../translated_images/sw/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Ingiza upande mmoja wa kebo ya Grove kwenye soketi ya kihisi cha GPS. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha upande mwingine wa kebo ya Grove kwenye soketi ya UART iliyoandikwa **UART** kwenye Grove Base hat iliyounganishwa na Pi. Soketi hii iko kwenye safu ya katikati, upande ulio karibu na nafasi ya kadi ya SD, upande mwingine kutoka kwa soketi za USB na ethernet.

    ![Kihisi cha Grove GPS kimeunganishwa kwenye soketi ya UART](../../../../../translated_images/sw/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Weka kihisi cha GPS ili antena iliyounganishwa iweze kuona anga - ikiwezekana karibu na dirisha lililo wazi au nje. Ni rahisi kupata ishara safi bila kitu chochote kinachozuia antena.

## Programu ya kihisi cha GPS

Sasa Raspberry Pi inaweza kupangwa kutumia kihisi cha GPS kilichounganishwa.

### Kazi - panga kihisi cha GPS

Panga kifaa.

1. Washa Pi na subiri ianze.

1. Kihisi cha GPS kina LED mbili - LED ya bluu inayowaka wakati data inatumwa, na LED ya kijani inayowaka kila sekunde moja wakati inapokea data kutoka kwa satelaiti. Hakikisha LED ya bluu inawaka unapowasha Pi. Baada ya dakika chache LED ya kijani itawaka - ikiwa haifanyi hivyo, huenda ukahitaji kuweka upya antena.

1. Fungua VS Code, ama moja kwa moja kwenye Pi, au unganisha kupitia kiendelezi cha Remote SSH.

    > ⚠️ Unaweza kurejelea [maelekezo ya kusanidi na kufungua VS Code katika somo la 1 ikiwa unahitaji](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Kwa matoleo mapya ya Raspberry Pi yanayounga mkono Bluetooth, kuna mgongano kati ya bandari ya serial inayotumika kwa Bluetooth, na ile inayotumika na bandari ya Grove UART. Ili kurekebisha hili, fanya yafuatayo:

    1. Kutoka kwa terminal ya VS Code, hariri faili ya `/boot/config.txt` ukitumia `nano`, mhariri wa maandishi wa terminal uliojengwa ndani kwa amri ifuatayo:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Faili hii haiwezi kuhaririwa na VS Code kwa sababu unahitaji kuhariri kwa ruhusa ya `sudo`, ruhusa ya juu. VS Code haifanyi kazi na ruhusa hii.

    1. Tumia funguo za mshale kuhamia mwisho wa faili, kisha nakili msimbo hapa chini na ubandike mwishoni mwa faili:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Unaweza kubandika ukitumia njia za mkato za kibodi za kifaa chako (`Ctrl+v` kwenye Windows, Linux au Raspberry Pi OS, `Cmd+v` kwenye macOS).

    1. Hifadhi faili hii na utoke kwenye nano kwa kubonyeza `Ctrl+x`. Bonyeza `y` unapoulizwa ikiwa unataka kuhifadhi mabadiliko, kisha bonyeza `enter` kuthibitisha unataka kuandika upya `/boot/config.txt`.

        > Ukifanya kosa, unaweza kutoka bila kuhifadhi, kisha kurudia hatua hizi.

    1. Hariri faili ya `/boot/cmdline.txt` kwenye nano kwa amri ifuatayo:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Faili hii ina jozi za funguo/thamani zilizotenganishwa na nafasi. Ondoa jozi zozote za funguo/thamani kwa funguo `console`. Zinaweza kuonekana kama hii:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Unaweza kuhamia kwenye maingizo haya ukitumia funguo za mshale, kisha kufuta ukitumia funguo za kawaida za `del` au `backspace`.

        Kwa mfano, ikiwa faili yako ya awali inaonekana kama hii:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Toleo jipya litakuwa:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Fuata hatua zilizo juu kuhifadhi faili hii na kutoka kwenye nano.

    1. Washa upya Pi yako, kisha unganisha tena kwenye VS Code mara Pi itakapowashwa upya.

1. Kutoka kwa terminal, tengeneza folda mpya kwenye saraka ya nyumbani ya mtumiaji `pi` inayoitwa `gps-sensor`. Tengeneza faili kwenye folda hii inayoitwa `app.py`.

1. Fungua folda hii kwenye VS Code.

1. Moduli ya GPS inatuma data ya UART kupitia bandari ya serial. Sakinisha kifurushi cha Pip `pyserial` ili kuwasiliana na bandari ya serial kutoka kwa msimbo wako wa Python:

    ```sh
    pip3 install pyserial
    ```

1. Ongeza msimbo ufuatao kwenye faili yako ya `app.py`:

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

    Msimbo huu unaingiza moduli ya `serial` kutoka kwa kifurushi cha Pip `pyserial`. Kisha inaunganisha kwenye bandari ya serial `/dev/ttyAMA0` - hii ni anwani ya bandari ya serial ambayo Grove Pi Base Hat hutumia kwa bandari yake ya UART. Kisha inafuta data yoyote iliyopo kutoka kwa muunganisho huu wa serial.

    Kisha, kazi inayoitwa `print_gps_data` inafafanuliwa ambayo inachapisha mstari uliopitishwa kwake kwenye koni.

    Kisha msimbo unazunguka milele, ukisoma mistari mingi ya maandishi kadri inavyoweza kutoka kwa bandari ya serial katika kila mzunguko. Inaita kazi ya `print_gps_data` kwa kila mstari.

    Baada ya data yote kusomwa, mzunguko unalala kwa sekunde 1, kisha unajaribu tena.

1. Endesha msimbo huu. Utaona matokeo ghafi kutoka kwa kihisi cha GPS, kitu kama hiki:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Ikiwa unapata mojawapo ya makosa yafuatayo unapositisha na kuanzisha tena msimbo wako, ongeza kizuizi cha `try - except` kwenye mzunguko wako wa while.

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

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Programu yako ya kihisi cha GPS imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, inashauriwa kutumia huduma ya tafsiri ya kitaalamu ya binadamu. Hatutawajibika kwa maelewano mabaya au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.