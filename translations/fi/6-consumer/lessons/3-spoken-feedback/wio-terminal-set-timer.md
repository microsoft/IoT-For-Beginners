<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T22:26:23+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "fi"
}
-->
# Aseta ajastin - Wio Terminal

Tässä oppitunnin osassa kutsut palvelutonta koodiasi puheen ymmärtämiseksi ja asetat ajastimen Wio Terminal -laitteellesi tulosten perusteella.

## Aseta ajastin

Puheesta tekstiksi -kutsusta palautuva teksti täytyy lähettää palveluttomaan koodiisi, jossa LUIS käsittelee sen ja palauttaa ajastimen sekuntimäärän. Tätä sekuntimäärää voidaan käyttää ajastimen asettamiseen.

Mikrokontrollereilla ei ole natiivisti tukea useille säikeille Arduinossa, joten ei ole olemassa standardeja ajastinluokkia, kuten Pythonissa tai muissa korkeamman tason kielissä. Sen sijaan voit käyttää ajastinkirjastoja, jotka toimivat mittaamalla kulunutta aikaa `loop`-funktiossa ja kutsumalla funktioita, kun aika on kulunut.

### Tehtävä - lähetä teksti palveluttomaan funktioon

1. Avaa `smart-timer`-projekti VS Codessa, jos se ei ole jo auki.

1. Avaa `config.h`-otsikkotiedosto ja lisää URL funktiosovelluksellesi:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Korvaa `<URL>` funktiosovelluksesi URL-osoitteella, jonka sait viimeisen oppitunnin viimeisessä vaiheessa, osoittaen paikallisen koneesi IP-osoitteeseen, jossa funktiosovellus toimii.

1. Luo uusi tiedosto `src`-kansioon nimeltä `language_understanding.h`. Tätä käytetään luokan määrittämiseen, joka lähettää tunnistetun puheen funktiosovelluksellesi ja muuntaa sen sekunneiksi LUIS:n avulla.

1. Lisää tämän tiedoston alkuun seuraava:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Tämä sisältää tarvittavat otsikkotiedostot.

1. Määritä luokka nimeltä `LanguageUnderstanding` ja julista tämän luokan instanssi:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Funktiosovelluksen kutsumiseksi sinun täytyy julistaa WiFi-asiakas. Lisää seuraava luokan `private`-osioon:

    ```cpp
    WiFiClient _client;
    ```

1. Julista `public`-osiossa metodi nimeltä `GetTimerDuration`, joka kutsuu funktiosovellusta:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Lisää `GetTimerDuration`-metodiin seuraava koodi JSON:n rakentamiseksi, joka lähetetään funktiosovellukseen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tämä muuntaa `GetTimerDuration`-metodille välitetyn tekstin seuraavaksi JSON:ksi:

    ```json
    {
        "text" : "<text>"
    }
    ```

    missä `<text>` on funktiolle välitetty teksti.

1. Lisää tämän alle seuraava koodi funktiosovelluksen kutsumiseksi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tämä tekee POST-pyynnön funktiosovellukseen, välittää JSON-rungon ja saa vastauskoodin.

1. Lisää tämän alle seuraava koodi:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Tämä koodi tarkistaa vastauskoodin. Jos se on 200 (onnistuminen), ajastimen sekuntimäärä haetaan vastausrungosta. Muussa tapauksessa virhe lähetetään sarjamonitoriin ja sekuntimääräksi asetetaan 0.

1. Lisää tämän metodin loppuun seuraava koodi HTTP-yhteyden sulkemiseksi ja sekuntimäärän palauttamiseksi:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Lisää `main.cpp`-tiedostoon tämän uuden otsikon sisällytys:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Kutsu `processAudio`-funktion lopussa `GetTimerDuration`-metodia ajastimen keston saamiseksi:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Tämä muuntaa `SpeechToText`-luokan kutsusta saadun tekstin ajastimen sekuntimääräksi.

### Tehtävä - aseta ajastin

Sekuntimäärää voidaan käyttää ajastimen asettamiseen.

1. Lisää seuraava kirjastoriippuvuus `platformio.ini`-tiedostoon ajastinkirjaston lisäämiseksi:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Lisää sisällytysohje tälle kirjastolle `main.cpp`-tiedostoon:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Lisää `processAudio`-funktion yläpuolelle seuraava koodi:

    ```cpp
    auto timer = timer_create_default();
    ```

    Tämä koodi julistaa ajastimen nimeltä `timer`.

1. Lisää tämän alle seuraava koodi:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Tämä `say`-funktio muuntaa tekstin puheeksi tulevaisuudessa, mutta toistaiseksi se vain kirjoittaa välitetyn tekstin sarjamonitoriin.

1. Lisää `say`-funktion alle seuraava koodi:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Tämä on palautefunktio, joka kutsutaan, kun ajastin päättyy. Sille välitetään viesti, joka sanotaan ajastimen päättyessä. Ajastimet voivat toistua, ja tämä voidaan hallita palautearvon avulla - tämä palauttaa `false`, mikä kertoo ajastimelle, ettei sitä ajeta uudelleen.

1. Lisää seuraava koodi `processAudio`-funktion loppuun:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Tämä koodi tarkistaa sekuntien kokonaismäärän, ja jos se on 0, se palaa funktiokutsusta, jotta ajastimia ei aseteta. Se muuntaa sekuntien kokonaismäärän minuuteiksi ja sekunneiksi.

1. Lisää tämän koodin alle seuraava koodi viestin luomiseksi, joka sanotaan ajastimen käynnistyessä:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Lisää tämän alle vastaava koodi viestin luomiseksi, joka sanotaan ajastimen päättyessä:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Tämän jälkeen sano ajastimen käynnistysviesti:

    ```cpp
    say(begin_message);
    ```

1. Lisää tämän funktion loppuun ajastimen käynnistys:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Tämä käynnistää ajastimen. Ajastin asetetaan millisekunteina, joten sekuntien kokonaismäärä kerrotaan 1 000:lla millisekunneiksi muuntamiseksi. `timerExpired`-funktio välitetään palautefunktiona, ja `end_message` välitetään argumenttina palautefunktiolle. Tämä palautefunktio hyväksyy vain `void *`-argumentteja, joten merkkijono muunnetaan asianmukaisesti.

1. Lopuksi ajastimen täytyy "tikittää", ja tämä tehdään `loop`-funktiossa. Lisää seuraava koodi `loop`-funktion loppuun:

    ```cpp
    timer.tick();
    ```

1. Rakenna tämä koodi, lataa se Wio Terminal -laitteeseesi ja testaa sitä sarjamonitorin kautta. Kun näet `Ready` sarjamonitorissa, paina C-painiketta (vasemmalla puolella, lähimpänä virtakytkintä) ja puhu. 4 sekuntia ääntä tallennetaan, muunnetaan tekstiksi, lähetetään funktiosovellukseesi ja ajastin asetetaan. Varmista, että funktiosovelluksesi toimii paikallisesti.

    Näet, milloin ajastin käynnistyy ja milloin se päättyy.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Löydät tämän koodin [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) -kansiosta.

😀 Ajastinohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.