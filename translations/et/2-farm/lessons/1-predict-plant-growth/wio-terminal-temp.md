<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-10-11T12:34:56+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "et"
}
-->
# Mõõda temperatuuri - Wio Terminal

Selles õppetunni osas lisad oma Wio Terminalile temperatuurianduri ja loed sellelt temperatuuri väärtusi.

## Riistvara

Wio Terminal vajab temperatuuriandurit.

Andur, mida kasutad, on [DHT11 niiskuse ja temperatuuri andur](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), mis ühendab kaks andurit ühes pakendis. See on üsna populaarne, kuna paljud kaubanduslikult saadaval olevad andurid ühendavad temperatuuri, niiskuse ja mõnikord ka õhurõhu mõõtmise. Temperatuurianduri komponent on negatiivse temperatuurikoefitsiendiga (NTC) termistor, termistor, mille takistus väheneb temperatuuri tõustes.

See on digitaalne andur, millel on sisseehitatud ADC, mis loob digitaalse signaali, mis sisaldab temperatuuri ja niiskuse andmeid, mida mikrokontroller saab lugeda.

### Ühenda temperatuuriandur

Grove temperatuurianduri saab ühendada Wio Terminali digitaalsesse porti.

#### Ülesanne - ühenda temperatuuriandur

Ühenda temperatuuriandur.

![Grove temperatuuriandur](../../../../../translated_images/et/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Sisesta Grove-kaabli üks ots niiskuse ja temperatuuri anduri pistikusse. Kaabel läheb sisse ainult ühes suunas.

1. Kui Wio Terminal on lahti ühendatud arvutist või muust toiteallikast, ühenda Grove-kaabli teine ots Wio Terminali parempoolse Grove-pistikuga, vaadates ekraani. See on pistik, mis asub kõige kaugemal toitenupust.

![Grove temperatuuriandur ühendatud parempoolse pistikuga](../../../../../translated_images/et/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programmeeri temperatuuriandur

Nüüd saab Wio Terminali programmeerida kasutama ühendatud temperatuuriandurit.

### Ülesanne - programmeeri temperatuuriandur

Programmeeeri seade.

1. Loo täiesti uus Wio Terminali projekt, kasutades PlatformIO-d. Nimeta see projekt `temperature-sensor`. Lisa kood `setup` funktsiooni, et seadistada serial port.

    > ⚠️ Vajadusel võid viidata [juhistele PlatformIO projekti loomiseks projektis 1, õppetund 1](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Lisa projekti `platformio.ini` faili sõltuvus Seeed Grove niiskuse ja temperatuuri anduri teegist:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Vajadusel võid viidata [juhistele teekide lisamiseks PlatformIO projekti projektis 1, õppetund 4](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Lisa järgmised `#include` direktiivid faili ülaossa, olemasoleva `#include <Arduino.h>` alla:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    See impordib failid, mis on vajalikud anduriga suhtlemiseks. `DHT.h` päisefail sisaldab koodi anduri jaoks, ja `SPI.h` päisefaili lisamine tagab, et anduriga suhtlemiseks vajalik kood lingitakse rakenduse kompileerimisel.

1. Deklareeri DHT andur enne `setup` funktsiooni:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    See deklareerib `DHT` klassi instantsi, mis haldab **D**igitaalse **H**umidity ja **T**emperature andurit. See on ühendatud porti `D0`, mis on Wio Terminali parempoolne Grove-pistik. Teine parameeter ütleb koodile, et kasutatav andur on *DHT11* - teek, mida kasutad, toetab selle anduri teisi variante.

1. Lisa `setup` funktsiooni kood, et seadistada serial ühendus:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Lisa `setup` funktsiooni lõppu, pärast viimast `delay`, käsk DHT anduri käivitamiseks:

    ```cpp
    dht.begin();
    ```

1. Lisa `loop` funktsiooni kood, et kutsuda andurit ja printida temperatuur serial porti:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    See kood deklareerib tühja 2 float-tüüpi elemendiga massiivi ja edastab selle `readTempAndHumidity` meetodile `DHT` instantsil. See meetod täidab massiivi kahe väärtusega - niiskus läheb massiivi 0. elemendisse (pidage meeles, et C++ massiivid on 0-põhised, seega 0. element on massiivi "esimene" element) ja temperatuur läheb 1. elemendisse.

    Temperatuur loetakse massiivi 1. elemendist ja prinditakse serial porti.

    > 🇺🇸 Temperatuur loetakse Celsiuse kraadides. Ameeriklaste jaoks, et teisendada see Fahrenheiti kraadideks, jagage loetud Celsiuse väärtus 5-ga, korrutage 9-ga ja lisage 32. Näiteks temperatuurinäit 20°C muutub ((20/5)*9) + 32 = 68°F.

1. Kompileeri ja laadi kood Wio Terminali.

    > ⚠️ Vajadusel võid viidata [juhistele PlatformIO projekti loomiseks projektis 1, õppetund 1](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Kui kood on üles laaditud, saad temperatuuri jälgida serial monitori abil:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Selle koodi leiad [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) kaustast.

😀 Sinu temperatuurianduri programm õnnestus!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.