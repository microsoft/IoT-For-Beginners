<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T21:25:02+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "fi"
}
-->
# Mittaa maaperän kosteutta - Wio Terminal

Tässä osassa oppituntia lisäät kapasiivisen maaperän kosteusanturin Wio Terminaliin ja luet sen antamia arvoja.

## Laitteisto

Wio Terminal tarvitsee kapasiivisen maaperän kosteusanturin.

Anturi, jota käytät, on [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), joka mittaa maaperän kosteutta havaitsemalla maaperän kapasitanssin. Tämä ominaisuus muuttuu maaperän kosteuden muuttuessa. Kun maaperän kosteus kasvaa, jännite laskee.

Kyseessä on analoginen anturi, joka liitetään Wio Terminalin analogisiin pinneihin. Anturi käyttää sisäänrakennettua ADC:tä (analoginen-digitaalimuunnin) luodakseen arvon välillä 0–1 023.

### Liitä maaperän kosteusanturi

Grove-maaperän kosteusanturi voidaan liittää Wio Terminalin konfiguroitavaan analoginen/digitaalinen-porttiin.

#### Tehtävä - liitä maaperän kosteusanturi

Liitä maaperän kosteusanturi.

![Grove-maaperän kosteusanturi](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.fi.png)

1. Työnnä Grove-kaapelin toinen pää maaperän kosteusanturin liittimeen. Kaapeli menee sisään vain yhdellä tavalla.

1. Kun Wio Terminal ei ole kytketty tietokoneeseen tai muuhun virtalähteeseen, liitä Grove-kaapelin toinen pää Wio Terminalin oikeanpuoleiseen Grove-liittimeen, kun katsot näyttöä. Tämä liitin on kauimpana virtapainikkeesta.

![Grove-maaperän kosteusanturi liitetty oikeanpuoleiseen liittimeen](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.fi.png)

1. Työnnä maaperän kosteusanturi maaperään. Anturissa on "korkein asennuslinja" - valkoinen viiva anturin poikki. Työnnä anturi maaperään tähän viivaan asti, mutta älä sen yli.

![Grove-maaperän kosteusanturi maaperässä](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.fi.png)

1. Voit nyt liittää Wio Terminalin tietokoneeseesi.

## Ohjelmoi maaperän kosteusanturi

Wio Terminal voidaan nyt ohjelmoida käyttämään liitettyä maaperän kosteusanturia.

### Tehtävä - ohjelmoi maaperän kosteusanturi

Ohjelmoi laite.

1. Luo täysin uusi Wio Terminal -projekti PlatformIO:lla. Nimeä projekti `soil-moisture-sensor`. Lisää koodi `setup`-funktioon sarjaportin konfiguroimiseksi.

    > ⚠️ Voit tarvittaessa viitata [ohjeisiin PlatformIO-projektin luomisesta projektissa 1, oppitunnilla 1](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Tälle anturille ei ole kirjastoa, mutta voit lukea analogisesta pinnistä sisäänrakennetulla Arduinon [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) -funktiolla. Aloita konfiguroimalla analoginen pinni sisääntuloksi, jotta siitä voidaan lukea arvoja, lisäämällä seuraava `setup`-funktioon.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Tämä asettaa `A0`-pinnin, yhdistetyn analoginen/digitaalinen-pinnin, sisääntulopinniksi, josta voidaan lukea jännite.

1. Lisää seuraava koodi `loop`-funktioon lukemaan jännite tästä pinnistä:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Lisää tämän koodin alle seuraava koodi tulostamaan arvo sarjaporttiin:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Lisää lopuksi 10 sekunnin viive loppuun:

    ```cpp
    delay(10000);
    ```

1. Rakenna ja lataa koodi Wio Terminaliin.

    > ⚠️ Voit tarvittaessa viitata [ohjeisiin PlatformIO-projektin luomisesta projektissa 1, oppitunnilla 1](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Kun koodi on ladattu, voit seurata maaperän kosteutta sarjamonitorilla. Lisää vettä maaperään tai poista anturi maaperästä ja katso, miten arvo muuttuu.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Esimerkkituloksessa näet, kuinka jännite laskee veden lisäämisen myötä.

> 💁 Löydät tämän koodin [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) -kansiosta.

😀 Maaperän kosteusanturin ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.