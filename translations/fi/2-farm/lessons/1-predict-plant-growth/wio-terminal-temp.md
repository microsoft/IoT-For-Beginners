# Mittaa lämpötila - Wio Terminal

Tässä osassa oppituntia lisäät lämpötila-anturin Wio Terminal -laitteeseesi ja luet siitä lämpötilan arvot.

## Laitteisto

Wio Terminal tarvitsee lämpötila-anturin.

Anturi, jota käytät, on [DHT11 kosteus- ja lämpötila-anturi](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), joka yhdistää kaksi anturia yhteen pakettiin. Tämä on melko suosittu, ja markkinoilla on useita antureita, jotka yhdistävät lämpötilan, kosteuden ja joskus myös ilmanpaineen mittauksen. Lämpötila-anturikomponentti on negatiivisen lämpötilakertoimen (NTC) termistori, eli termistori, jonka vastus pienenee lämpötilan noustessa.

Kyseessä on digitaalinen anturi, joten siinä on sisäänrakennettu ADC, joka luo digitaalisen signaalin sisältäen lämpötila- ja kosteustiedot, joita mikrokontrolleri voi lukea.

### Yhdistä lämpötila-anturi

Grove-lämpötila-anturi voidaan liittää Wio Terminalin digitaaliseen porttiin.

#### Tehtävä - yhdistä lämpötila-anturi

Yhdistä lämpötila-anturi.

![Grove-lämpötila-anturi](../../../../../translated_images/fi/grove-dht11.07f8eafceee17004.webp)

1. Työnnä Grove-kaapelin toinen pää kosteus- ja lämpötila-anturin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Wio Terminal ei ole kytketty tietokoneeseen tai muuhun virtalähteeseen, yhdistä Grove-kaapelin toinen pää Wio Terminalin oikeanpuoleiseen Grove-liittimeen, kun katsot näyttöä. Tämä on liitin, joka on kauimpana virtapainikkeesta.

![Grove-lämpötila-anturi yhdistetty oikeanpuoleiseen liittimeen](../../../../../translated_images/fi/wio-temperature-sensor.2934928f38c7f79a.webp)

## Ohjelmoi lämpötila-anturi

Wio Terminal voidaan nyt ohjelmoida käyttämään liitettyä lämpötila-anturia.

### Tehtävä - ohjelmoi lämpötila-anturi

Ohjelmoi laite.

1. Luo täysin uusi Wio Terminal -projekti käyttämällä PlatformIO:ta. Nimeä tämä projekti `temperature-sensor`. Lisää koodi `setup`-funktioon sarjaportin konfiguroimiseksi.

    > ⚠️ Voit viitata [ohjeisiin PlatformIO-projektin luomisesta projektissa 1, oppitunnilla 1 tarvittaessa](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Lisää kirjastoriippuvuus Seeed Grove -kosteus- ja lämpötila-anturin kirjastolle projektin `platformio.ini`-tiedostoon:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Voit viitata [ohjeisiin kirjastojen lisäämisestä PlatformIO-projektiin projektissa 1, oppitunnilla 4 tarvittaessa](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Lisää seuraavat `#include`-direktiivit tiedoston alkuun, olemassa olevan `#include <Arduino.h>`-direktiivin alle:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Tämä tuo tiedostot, joita tarvitaan anturin kanssa toimimiseen. `DHT.h`-otsikkotiedosto sisältää koodin itse anturille, ja lisäämällä `SPI.h`-otsikkotiedoston varmistetaan, että anturin kanssa kommunikointiin tarvittava koodi linkitetään sovelluksen kääntämisen yhteydessä.

1. Ennen `setup`-funktiota, määritä DHT-anturi:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Tämä määrittää `DHT`-luokan instanssin, joka hallitsee **D**igitaalista **K**osteus- ja **L**ämpötila-anturia. Tämä on liitetty porttiin `D0`, oikeanpuoleiseen Grove-liittimeen Wio Terminalissa. Toinen parametri kertoo koodille, että käytettävä anturi on *DHT11* -anturi - käyttämäsi kirjasto tukee myös muita tämän anturin variantteja.

1. Lisää `setup`-funktioon koodi sarjayhteyden asettamiseksi:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Lisää `setup`-funktion loppuun, viimeisen `delay`-kutsun jälkeen, kutsu DHT-anturin käynnistämiseksi:

    ```cpp
    dht.begin();
    ```

1. Lisää `loop`-funktioon koodi, joka kutsuu anturia ja tulostaa lämpötilan sarjaporttiin:

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

    Tämä koodi määrittää tyhjän 2 desimaaliluvun taulukon ja välittää sen `readTempAndHumidity`-kutsuun `DHT`-instanssissa. Tämä kutsu täyttää taulukon kahdella arvolla - kosteus menee taulukon 0. kohtaan (muista, että C++-taulukot ovat 0-pohjaisia, joten 0. kohta on taulukon 'ensimmäinen' kohta), ja lämpötila menee 1. kohtaan.

    Lämpötila luetaan taulukon 1. kohdasta ja tulostetaan sarjaporttiin.

    > 🇺🇸 Lämpötila luetaan Celsius-asteina. Amerikkalaisille, Celsius-arvon muuntamiseksi Fahrenheit-asteiksi jaa Celsius-arvo viidellä, kerro yhdeksällä ja lisää 32. Esimerkiksi lämpötilalukema 20°C muuttuu ((20/5)*9) + 32 = 68°F.

1. Käännä ja lataa koodi Wio Terminaliin.

    > ⚠️ Voit viitata [ohjeisiin PlatformIO-projektin luomisesta projektissa 1, oppitunnilla 1 tarvittaessa](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Kun koodi on ladattu, voit seurata lämpötilaa sarjavalvonnan avulla:

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

> 💁 Löydät tämän koodin [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) -kansiosta.

😀 Lämpötila-anturin ohjelma onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.