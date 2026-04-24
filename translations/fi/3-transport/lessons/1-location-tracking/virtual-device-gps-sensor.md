# Lue GPS-dataa - Virtuaalinen IoT-laitteisto

Tässä oppitunnin osassa lisäät GPS-anturin virtuaaliseen IoT-laitteeseesi ja luet siitä arvoja.

## Virtuaalinen laitteisto

Virtuaalinen IoT-laite käyttää simuloitua GPS-anturia, joka on saatavilla UARTin kautta sarjaportin avulla.

Fyysisessä GPS-anturissa on antenni, joka vastaanottaa GPS-satelliittien radiotaajuuksia ja muuntaa GPS-signaalit GPS-dataksi. Virtuaalinen versio simuloi tätä antamalla sinun joko asettaa leveyspiirin ja pituuspiirin, lähettää raakoja NMEA-lauseita tai ladata GPX-tiedoston, jossa on useita sijainteja, jotka voidaan palauttaa peräkkäin.

> 🎓 NMEA-lauseet käsitellään myöhemmin tässä oppitunnissa

### Lisää anturi CounterFitiin

Virtuaalisen GPS-anturin käyttämiseksi sinun täytyy lisätä sellainen CounterFit-sovellukseen.

#### Tehtävä - lisää anturi CounterFitiin

Lisää GPS-anturi CounterFit-sovellukseen.

1. Luo tietokoneellesi uusi Python-sovellus kansioon nimeltä `gps-sensor`, jossa on yksi tiedosto nimeltä `app.py`, sekä Python-virtuaaliympäristö, ja lisää CounterFitin pip-paketit.

    > ⚠️ Voit tarvittaessa viitata [ohjeisiin CounterFit Python -projektin luomisesta ja asettamisesta oppitunnissa 1](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Asenna lisä-Pip-paketti, joka sisältää CounterFit-shimin, joka voi kommunikoida UART-pohjaisten antureiden kanssa sarjayhteyden kautta. Varmista, että asennat tämän terminaalista, jossa virtuaaliympäristö on aktivoitu.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Varmista, että CounterFit-verkkosovellus on käynnissä.

1. Luo GPS-anturi:

    1. *Create sensor* -laatikossa *Sensors*-paneelissa avaa *Sensor type* -valikko ja valitse *UART GPS*.

    1. Jätä *Port*-asetukseksi */dev/ttyAMA0*.

    1. Valitse **Add**-painike luodaksesi GPS-anturin porttiin `/dev/ttyAMA0`.

    ![GPS-anturin asetukset](../../../../../translated_images/fi/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    GPS-anturi luodaan ja se näkyy anturilistassa.

    ![Luotu GPS-anturi](../../../../../translated_images/fi/counterfit-gps-sensor.3fbb15af0a536756.webp)

## Ohjelmoi GPS-anturi

Virtuaalinen IoT-laite voidaan nyt ohjelmoida käyttämään virtuaalista GPS-anturia.

### Tehtävä - ohjelmoi GPS-anturi

Ohjelmoi GPS-anturisovellus.

1. Varmista, että `gps-sensor`-sovellus on auki VS Codessa.

1. Avaa `app.py`-tiedosto.

1. Lisää seuraava koodi `app.py`-tiedoston alkuun yhdistääksesi sovelluksen CounterFitiin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lisää tämän alle seuraava koodi tuodaksesi tarvittavat kirjastot, mukaan lukien CounterFitin sarjaporttikirjasto:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Tämä koodi tuo `serial`-moduulin `counterfit_shims_serial`-Pip-paketista. Se yhdistää `/dev/ttyAMA0`-sarjaporttiin, joka on virtuaalisen GPS-anturin UART-portin osoite.

1. Lisää tämän alle seuraava koodi lukeaksesi sarjaportista ja tulostaaksesi arvot konsoliin:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Määritellään funktio nimeltä `print_gps_data`, joka tulostaa sille annetun rivin konsoliin.

    Seuraavaksi koodi suorittaa ikuisen silmukan, jossa luetaan niin monta tekstiriviä kuin mahdollista sarjaportista jokaisella silmukan kierroksella. Se kutsuu `print_gps_data`-funktiota jokaiselle riville.

    Kun kaikki data on luettu, silmukka odottaa 1 sekunnin ja yrittää uudelleen.

1. Suorita tämä koodi varmistaen, että käytät eri terminaalia kuin sitä, jossa CounterFit-sovellus on käynnissä, jotta CounterFit-sovellus pysyy käynnissä.

1. Muuta CounterFit-sovelluksessa GPS-anturin arvoja. Voit tehdä tämän jollakin seuraavista tavoista:

    * Aseta **Source** arvoksi `Lat/Lon` ja määritä tarkka leveyspiiri, pituuspiiri ja satelliittien määrä, joita käytetään GPS-paikannukseen. Tämä arvo lähetetään vain kerran, joten valitse **Repeat**-ruutu, jotta data toistuu joka sekunti.

      ![GPS-anturi, jossa lat lon valittuna](../../../../../translated_images/fi/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Aseta **Source** arvoksi `NMEA` ja lisää NMEA-lauseita tekstikenttään. Kaikki nämä arvot lähetetään, ja uuden GGA (paikannus) -lauseen lukemisen välillä on 1 sekunnin viive.

      ![GPS-anturi, jossa NMEA-lauseet asetettu](../../../../../translated_images/fi/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Voit käyttää työkaluja, kuten [nmeagen.org](https://www.nmeagen.org), näiden lauseiden luomiseen piirtämällä kartalle. Nämä arvot lähetetään vain kerran, joten valitse **Repeat**-ruutu, jotta data toistuu sekunnin kuluttua siitä, kun kaikki on lähetetty.

    * Aseta **Source** arvoksi GPX-tiedosto ja lataa GPX-tiedosto, jossa on reittisijainteja. Voit ladata GPX-tiedostoja useilta suosituilla kartta- ja retkeilysivustoilta, kuten [AllTrails](https://www.alltrails.com/). Nämä tiedostot sisältävät useita GPS-sijainteja reittinä, ja GPS-anturi palauttaa jokaisen uuden sijainnin 1 sekunnin välein.

      ![GPS-anturi, jossa GPX-tiedosto asetettu](../../../../../translated_images/fi/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Nämä arvot lähetetään vain kerran, joten valitse **Repeat**-ruutu, jotta data toistuu sekunnin kuluttua siitä, kun kaikki on lähetetty.

    Kun olet määrittänyt GPS-asetukset, valitse **Set**-painike tallentaaksesi nämä arvot anturiin.

1. Näet GPS-anturin raakadatan tulostettuna, esimerkiksi seuraavanlaisen:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Löydät tämän koodin [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device) -kansiosta.

😀 GPS-anturisovelluksesi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.