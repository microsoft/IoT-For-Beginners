<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:47:00+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "fi"
}
-->
# Hallitse yövaloa Internetin kautta - Wio Terminal

IoT-laitteelle täytyy ohjelmoida kyky kommunikoida *test.mosquitto.org*-palvelimen kanssa käyttämällä MQTT-protokollaa. Tämän avulla se voi lähettää telemetriatietoja valosensorin lukemista ja vastaanottaa komentoja LED-valon ohjaamiseen.

Tässä oppitunnin osassa yhdistät Wio Terminalin MQTT-välityspalvelimeen.

## Asenna WiFi- ja MQTT-kirjastot Arduinoa varten

Jotta voit kommunikoida MQTT-välityspalvelimen kanssa, sinun täytyy asentaa joitakin Arduino-kirjastoja, jotka mahdollistavat Wio Terminalin WiFi-sirun käytön ja MQTT-yhteyden. Arduino-laitteille kehittäessäsi voit hyödyntää laajaa valikoimaa avoimen lähdekoodin kirjastoja, jotka tarjoavat monenlaisia toiminnallisuuksia. Seeed julkaisee kirjastoja Wio Terminalille, jotka mahdollistavat WiFi-yhteyden. Lisäksi muut kehittäjät ovat julkaisseet kirjastoja MQTT-välityspalvelimien kanssa kommunikointiin, ja käytät näitä kirjastoja laitteesi kanssa.

Nämä kirjastot toimitetaan lähdekoodina, joka voidaan tuoda automaattisesti PlatformIO:hon ja kääntää laitteellesi. Näin Arduino-kirjastot toimivat kaikilla laitteilla, jotka tukevat Arduino-kehystä, edellyttäen, että laitteessa on kyseisen kirjaston vaatima laitteisto. Jotkin kirjastot, kuten Seeedin WiFi-kirjastot, ovat laitteistokohtaisia.

Kirjastot voidaan asentaa joko globaalisti tai tiettyyn projektiin. Tässä tehtävässä kirjastot asennetaan projektiin.

✅ Voit oppia lisää kirjastojen hallinnasta ja niiden löytämisestä ja asentamisesta [PlatformIO:n kirjasto-dokumentaatiosta](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Tehtävä - WiFi- ja MQTT-kirjastojen asentaminen

Asenna Arduino-kirjastot.

1. Avaa yövaloprojekti VS Codessa.

1. Lisää seuraava `platformio.ini`-tiedoston loppuun:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Tämä tuo Seeedin WiFi-kirjastot. `@ <numero>`-syntaksi viittaa tiettyyn kirjaston versioon.

    > 💁 Voit poistaa `@ <numero>`-osan käyttääksesi aina kirjastojen uusinta versiota, mutta ei ole takeita, että uudemmat versiot toimivat alla olevan koodin kanssa. Tämä koodi on testattu näiden kirjastoversioiden kanssa.

    Tämä riittää kirjastojen lisäämiseen. Seuraavan kerran, kun PlatformIO rakentaa projektin, se lataa näiden kirjastojen lähdekoodin ja kääntää sen osaksi projektiasi.

1. Lisää seuraava `lib_deps`-osioon:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Tämä tuo [PubSubClient](https://github.com/knolleary/pubsubclient)-kirjaston, joka on Arduino MQTT -asiakas.

## Yhdistä WiFi-verkkoon

Nyt Wio Terminal voidaan yhdistää WiFi-verkkoon.

### Tehtävä - yhdistä WiFi-verkkoon

Yhdistä Wio Terminal WiFi-verkkoon.

1. Luo uusi tiedosto `src`-kansioon nimeltä `config.h`. Voit tehdä tämän valitsemalla `src`-kansion tai sen sisällä olevan `main.cpp`-tiedoston ja napsauttamalla **Uusi tiedosto** -painiketta resurssienhallinnassa. Tämä painike näkyy vain, kun hiiren osoitin on resurssienhallinnan päällä.

    ![Uuden tiedoston painike](../../../../../translated_images/fi/vscode-new-file-button.182702340fe6723c.webp)

1. Lisää tähän tiedostoon seuraava koodi määrittääksesi WiFi-tunnistetietojen vakioarvot:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Korvaa `<SSID>` WiFi-verkkosi SSID:llä. Korvaa `<PASSWORD>` WiFi-verkkosi salasanalla.

1. Avaa `main.cpp`-tiedosto.

1. Lisää seuraavat `#include`-direktiivit tiedoston alkuun:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Tämä tuo mukaan aiemmin lisäämiesi kirjastojen otsikkotiedostot sekä config-otsikkotiedoston. Nämä otsikkotiedostot ovat tarpeen, jotta PlatformIO tuo kirjastojen koodin mukaan. Ilman näiden otsikkotiedostojen eksplisiittistä sisällyttämistä osa koodista ei käänny, ja saat kääntäjävirheitä.

1. Lisää seuraava koodi `setup`-funktion yläpuolelle:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Tämä koodi yrittää yhdistää laitetta WiFi-verkkoon, kunnes yhteys on muodostettu, käyttäen config-otsikkotiedostosta saatuja SSID- ja salasana-arvoja.

1. Lisää kutsu tähän funktioon `setup`-funktion loppuun, kun pinnit on konfiguroitu.

    ```cpp
    connectWiFi();
    ```

1. Lataa tämä koodi laitteellesi tarkistaaksesi, että WiFi-yhteys toimii. Näet tämän sarjamonitorissa.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Yhdistä MQTT:hen

Kun Wio Terminal on yhdistetty WiFi-verkkoon, se voi yhdistyä MQTT-välityspalvelimeen.

### Tehtävä - yhdistä MQTT:hen

Yhdistä MQTT-välityspalvelimeen.

1. Lisää seuraava koodi `config.h`-tiedoston loppuun määrittääksesi MQTT-välityspalvelimen yhteystiedot:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Korvaa `<ID>` ainutlaatuisella tunnisteella, jota käytetään tämän laitteen asiakasnimenä ja myöhemmin aiheissa, joihin tämä laite julkaisee ja tilaa. *test.mosquitto.org*-välityspalvelin on julkinen ja monien ihmisten, mukaan lukien muiden tämän tehtävän parissa työskentelevien opiskelijoiden, käytössä. Ainutlaatuisen MQTT-asiakasnimen ja aiheiden avulla varmistat, ettei koodisi mene sekaisin muiden kanssa. Tarvitset myös tämän tunnisteen, kun luot palvelinkoodia myöhemmin tässä tehtävässä.

    > 💁 Voit käyttää verkkosivustoa, kuten [GUIDGen](https://www.guidgen.com), luodaksesi ainutlaatuisen tunnisteen.

    `BROKER` on MQTT-välityspalvelimen URL-osoite.

    `CLIENT_NAME` on tämän MQTT-asiakkaan ainutlaatuinen nimi välityspalvelimessa.

1. Avaa `main.cpp`-tiedosto ja lisää seuraava koodi `connectWiFi`-funktion alapuolelle ja `setup`-funktion yläpuolelle:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Tämä koodi luo WiFi-asiakkaan Wio Terminalin WiFi-kirjastoja käyttäen ja käyttää sitä MQTT-asiakkaan luomiseen.

1. Lisää tämän koodin alapuolelle seuraava:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Tämä funktio testaa yhteyden MQTT-välityspalvelimeen ja yhdistää uudelleen, jos yhteyttä ei ole. Se yrittää yhdistää uudelleen 5 sekunnin välein, jos yhteys epäonnistuu.

1. Lisää seuraava koodi `reconnectMQTTClient`-funktion alapuolelle:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Tämä koodi määrittää MQTT-välityspalvelimen asiakkaalle sekä asettaa takaisinsoiton, kun viesti vastaanotetaan. Se yrittää myös yhdistää välityspalvelimeen.

1. Kutsu `createMQTTClient`-funktiota `setup`-funktiossa sen jälkeen, kun WiFi-yhteys on muodostettu.

1. Korvaa koko `loop`-funktio seuraavalla:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Tämä koodi aloittaa tarkistamalla ja tarvittaessa yhdistämällä uudelleen MQTT-välityspalvelimeen. Nämä yhteydet voivat katketa helposti, joten on hyvä tarkistaa ja yhdistää säännöllisesti. Sen jälkeen se kutsuu MQTT-asiakkaan `loop`-metodia käsitelläkseen mahdolliset saapuvat viestit tilatuista aiheista. Tämä sovellus on yksisäikeinen, joten viestejä ei voida vastaanottaa taustasäikeessä, ja pääsäikeellä täytyy varata aikaa odottavien viestien käsittelyyn.

    Lopuksi 2 sekunnin viive varmistaa, että valotasotietoja ei lähetetä liian usein, mikä vähentää laitteen virrankulutusta.

1. Lataa koodi Wio Terminalillesi ja käytä sarjamonitoria nähdäksesi laitteen yhdistyvän WiFi-verkkoon ja MQTT:hen.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Löydät tämän koodin [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal)-kansiosta.

😀 Olet onnistuneesti yhdistänyt laitteesi MQTT-välityspalvelimeen.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.