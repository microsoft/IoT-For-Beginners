<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T15:13:00+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "sl"
}
-->
# Objavi temperaturo - Wio Terminal

V tem delu lekcije boste objavili vrednosti temperature, ki jih zazna Wio Terminal, prek MQTT, da jih boste lahko kasneje uporabili za izračun GDD.

## Objavi temperaturo

Ko je temperatura prebrana, jo lahko objavite prek MQTT na neko 'strežniško' kodo, ki bo prebrala vrednosti in jih shranila za kasnejši izračun GDD. Mikrokontrolerji ne berejo časa iz interneta in ne sledijo času z realnočasovno uro privzeto, napravo je treba programirati, da to omogoči, če ima ustrezno strojno opremo.

Da poenostavimo stvari za to lekcijo, čas ne bo poslan skupaj s podatki senzorja, ampak ga lahko strežniška koda doda kasneje, ko prejme sporočila.

### Naloga

Programirajte napravo, da objavi podatke o temperaturi.

1. Odprite projekt `temperature-sensor` za Wio Terminal.

1. Ponovite korake, ki ste jih izvedli v lekciji 4, da se povežete z MQTT in pošljete telemetrijo. Uporabili boste isti javni Mosquitto strežnik.

    Koraki za to so:

    - Dodajte knjižnice Seeed WiFi in MQTT v datoteko `.ini`.
    - Dodajte konfiguracijsko datoteko in kodo za povezavo z WiFi.
    - Dodajte kodo za povezavo z MQTT strežnikom.
    - Dodajte kodo za objavo telemetrije.

    > ⚠️ Oglejte si [navodila za povezavo z MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) in [navodila za pošiljanje telemetrije](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) iz lekcije 4, če je potrebno.

1. Prepričajte se, da `CLIENT_NAME` v glavni datoteki `config.h` odraža ta projekt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Za telemetrijo namesto pošiljanja vrednosti svetlobe pošljite vrednost temperature, prebrano s senzorja DHT, v lastnosti JSON dokumenta, imenovani `temperature`, tako da spremenite funkcijo `loop` v datoteki `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Vrednosti temperature ni treba brati zelo pogosto - v kratkem času se ne bo veliko spremenila, zato nastavite `delay` v funkciji `loop` na 10 minut:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funkcija `delay` sprejme čas v milisekundah, zato je za lažje branje vrednost podana kot rezultat izračuna. 1.000 ms v sekundi, 60 s v minuti, torej 10 x (60 s v minuti) x (1.000 ms v sekundi) daje zamik 10 minut.

1. Naložite to na vaš Wio Terminal in uporabite serijski monitor, da vidite, kako se temperatura pošilja na MQTT strežnik.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 To kodo lahko najdete v mapi [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Uspešno ste objavili temperaturo kot telemetrijo iz vaše naprave.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne odgovarjamo za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.