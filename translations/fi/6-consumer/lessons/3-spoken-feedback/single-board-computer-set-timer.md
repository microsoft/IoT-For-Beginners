<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T22:23:52+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "fi"
}
-->
# Aseta ajastin - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä oppitunnin osassa kutsut serverittömän koodisi ymmärtämään puhetta ja asetat ajastimen virtuaalisessa IoT-laitteessasi tai Raspberry Pi:ssä tulosten perusteella.

## Aseta ajastin

Puheesta tekstiksi -kutsusta palautuva teksti täytyy lähettää serverittömään koodiisi, jotta LUIS voi käsitellä sen ja palauttaa ajastimen sekuntimäärän. Tätä sekuntimäärää voidaan käyttää ajastimen asettamiseen.

Ajastimia voidaan asettaa Pythonin `threading.Timer`-luokan avulla. Tämä luokka ottaa viiveajan ja funktion, ja viiveajan jälkeen funktio suoritetaan.

### Tehtävä - lähetä teksti serverittömään funktioon

1. Avaa `smart-timer`-projekti VS Code -editorissa ja varmista, että virtuaalinen ympäristö on ladattu terminaaliin, jos käytät virtuaalista IoT-laitetta.

1. Julista `process_text`-funktion yläpuolelle funktio nimeltä `get_timer_time`, joka kutsuu luomaasi REST-päätepistettä:

    ```python
    def get_timer_time(text):
    ```

1. Lisää tähän funktioon seuraava koodi määrittääksesi kutsuttavan URL-osoitteen:

    ```python
    url = '<URL>'
    ```

    Korvaa `<URL>` REST-päätepisteesi URL-osoitteella, jonka loit edellisessä oppitunnissa, joko tietokoneellasi tai pilvessä.

1. Lisää seuraava koodi asettaaksesi tekstin JSON-ominaisuudeksi kutsua varten:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Tämän alapuolelle hae `seconds` vastausdatasta ja palauta 0, jos kutsu epäonnistui:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Onnistuneet HTTP-kutsut palauttavat tilakoodin 200-alueella, ja serveritön koodisi palauttaa 200, jos teksti käsiteltiin ja tunnistettiin ajastimen asettamiseksi.

### Tehtävä - aseta ajastin taustasäikeessä

1. Lisää tiedoston alkuun seuraava tuontilauseke tuodaksesi Pythonin threading-kirjaston:

    ```python
    import threading
    ```

1. Lisää `process_text`-funktion yläpuolelle funktio, joka puhuu vastauksen. Toistaiseksi tämä vain kirjoittaa tekstin konsoliin, mutta myöhemmin tässä oppitunnissa se puhuu tekstin.

    ```python
    def say(text):
        print(text)
    ```

1. Lisää tämän alapuolelle funktio, jota ajastin kutsuu ilmoittaakseen, että ajastin on päättynyt:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Tämä funktio ottaa ajastimen minuutti- ja sekuntimäärän ja rakentaa lauseen, joka ilmoittaa ajastimen päättyneen. Se tarkistaa minuutti- ja sekuntimäärät ja sisällyttää viestiin vain ne yksiköt, joilla on arvo. Esimerkiksi, jos minuuttien määrä on 0, viesti sisältää vain sekunnit. Tämä lause lähetetään sitten `say`-funktiolle.

1. Lisää tämän alapuolelle seuraava `create_timer`-funktio ajastimen luomiseksi:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Tämä funktio ottaa ajastimen kokonaissekuntimäärän, joka lähetetään komennossa, ja muuntaa sen minuuteiksi ja sekunneiksi. Se luo ja käynnistää ajastin-olion käyttäen kokonaissekuntimäärää, välittäen `announce_timer`-funktion ja listan, joka sisältää minuutit ja sekunnit. Kun ajastin päättyy, se kutsuu `announce_timer`-funktion ja välittää tämän listan sisällön parametreina - joten listan ensimmäinen kohde välitetään `minutes`-parametrina ja toinen kohde `seconds`-parametrina.

1. Lisää `create_timer`-funktion loppuun koodi, joka rakentaa käyttäjälle puhuttavan viestin ilmoittaakseen, että ajastin käynnistyy:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Tämä sisältää jälleen vain ne aikayksiköt, joilla on arvo. Tämä lause lähetetään sitten `say`-funktiolle.

1. Lisää seuraava `process_text`-funktion loppuun saadaksesi ajastimen ajan tekstistä ja luodaksesi ajastimen:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Ajastin luodaan vain, jos sekuntien määrä on suurempi kuin 0.

1. Suorita sovellus ja varmista, että funktiosovellus on myös käynnissä. Aseta joitakin ajastimia, ja tuloste näyttää ajastimen asettamisen ja ilmoittaa, kun se päättyy:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Löydät tämän koodin [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) tai [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) -kansiosta.

😀 Ajastinohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.