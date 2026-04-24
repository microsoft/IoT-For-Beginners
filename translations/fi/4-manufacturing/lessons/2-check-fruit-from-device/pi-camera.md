# Tallenna kuva - Raspberry Pi

Tässä osassa oppituntia lisäät kameran sensorin Raspberry Pi:hin ja luet kuvia siitä.

## Laitteisto

Raspberry Pi tarvitsee kameran.

Kamera, jota käytät, on [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Tämä kamera on suunniteltu toimimaan Raspberry Pi:n kanssa ja se liitetään Pi:n omaan liitäntään.

> 💁 Tämä kamera käyttää [Camera Serial Interface -protokollaa, joka on Mobile Industry Processor Interface Alliancen kehittämä](https://wikipedia.org/wiki/Camera_Serial_Interface), tunnettu nimellä MIPI-CSI. Tämä on erityinen protokolla kuvien lähettämiseen.

## Liitä kamera

Kamera voidaan liittää Raspberry Pi:hin nauhakaapelilla.

### Tehtävä - liitä kamera

![Raspberry Pi -kamera](../../../../../translated_images/fi/pi-camera-module.4278753c31bd6e75.webp)

1. Sammuta Pi.

1. Liitä kameran mukana tuleva nauhakaapeli kameraan. Vedä varovasti pidikkeen mustaa muoviklipsiä ulospäin, jotta se irtoaa hieman, ja liu'uta kaapeli liittimeen siten, että sininen puoli on poispäin linssistä ja metalliset pinnit kohti linssiä. Kun kaapeli on kokonaan sisällä, työnnä musta muoviklipsi takaisin paikalleen.

    Voit katsoa animaation, joka näyttää, miten klipsi avataan ja kaapeli asetetaan, [Raspberry Pi:n Getting Started with the Camera module -dokumentaatiosta](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Nauhakaapeli liitetty kameramoduuliin](../../../../../translated_images/fi/pi-camera-ribbon-cable.0bf82acd251611c2.webp)

1. Poista Grove Base Hat Pi:stä.

1. Vie nauhakaapeli Grove Base Hatin kameran aukon läpi. Varmista, että kaapelin sininen puoli on kohti analogisia portteja, jotka on merkitty **A0**, **A1** jne.

    ![Nauhakaapeli kulkee Grove Base Hatin läpi](../../../../../translated_images/fi/grove-base-hat-ribbon-cable.501fed202fcf73b1.webp)

1. Aseta nauhakaapeli Pi:n kameraliitäntään. Vedä jälleen mustaa muoviklipsiä ylös, aseta kaapeli ja työnnä klipsi takaisin paikalleen. Kaapelin sininen puoli tulisi olla kohti USB- ja Ethernet-portteja.

    ![Nauhakaapeli liitetty Pi:n kameraliitäntään](../../../../../translated_images/fi/pi-camera-socket-ribbon-cable.a18309920b118009.webp)

1. Kiinnitä Grove Base Hat takaisin paikalleen.

## Ohjelmoi kamera

Raspberry Pi voidaan nyt ohjelmoida käyttämään kameraa [PiCamera](https://pypi.org/project/picamera/) Python-kirjaston avulla.

### Tehtävä - ota käyttöön vanha kameratila

Valitettavasti Raspberry Pi OS Bullseye -version julkaisun myötä kameran ohjelmisto muuttui, ja oletuksena PiCamera ei enää toimi. Työn alla on korvaava ohjelmisto, nimeltään PiCamera2, mutta se ei ole vielä valmis käytettäväksi.

Toistaiseksi voit asettaa Pi:n vanhaan kameratilaan, jotta PiCamera toimii. Kameraliitäntä on myös oletuksena pois käytöstä, mutta vanhan kameran ohjelmiston käyttöönotto aktivoi liitännän automaattisesti.

1. Käynnistä Pi ja odota, että se käynnistyy.

1. Käynnistä VS Code joko suoraan Pi:ssä tai yhdistä Remote SSH -laajennuksen kautta.

1. Suorita seuraavat komennot terminaalista:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Tämä ottaa käyttöön asetuksen, joka aktivoi vanhan kameran ohjelmiston, ja käynnistää Pi:n uudelleen, jotta asetus tulee voimaan.

1. Odota, että Pi käynnistyy uudelleen, ja käynnistä VS Code uudelleen.

### Tehtävä - ohjelmoi kamera

Ohjelmoi laite.

1. Luo terminaalista uusi kansio `pi`-käyttäjän kotihakemistoon nimeltä `fruit-quality-detector`. Luo tiedosto tässä kansiossa nimeltä `app.py`.

1. Avaa tämä kansio VS Codessa.

1. Kameran kanssa vuorovaikuttamiseksi voit käyttää PiCamera Python-kirjastoa. Asenna Pip-paketti seuraavalla komennolla:

    ```sh
    pip3 install picamera
    ```

1. Lisää seuraava koodi `app.py`-tiedostoon:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Tämä koodi tuo tarvittavat kirjastot, mukaan lukien `PiCamera`-kirjaston.

1. Lisää tämän alle seuraava koodi kameran alustamiseksi:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Tämä koodi luo PiCamera-objektin ja asettaa resoluution 640x480. Vaikka suurempia resoluutioita tuetaan (jopa 3280x2464), kuvantunnistin toimii paljon pienemmillä kuvilla (227x227), joten ei ole tarpeen tallentaa ja lähettää suurempia kuvia.

    Rivi `camera.rotation = 0` asettaa kuvan kierron. Nauhakaapeli tulee kameran alapuolelta, mutta jos kamera on käännetty helpottamaan kohteen suuntaamista, voit muuttaa tätä riviä kierron asteiden mukaan.

    ![Kamera roikkuu juomatölkin yläpuolella](../../../../../translated_images/fi/pi-camera-upside-down.5376961ba3145988.webp)

    Esimerkiksi, jos ripustat nauhakaapelin kameran yläpuolelle, aseta kierto 180 asteeseen:

    ```python
    camera.rotation = 180
    ```

    Kameran käynnistyminen kestää muutaman sekunnin, joten `time.sleep(2)`-rivi on tarpeen.

1. Lisää tämän alle seuraava koodi kuvan tallentamiseksi binäärimuodossa:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Tämä koodi luo `BytesIO`-objektin binääridatan tallentamista varten. Kuva luetaan kamerasta JPEG-tiedostona ja tallennetaan tähän objektiin. Objekti sisältää sijainti-indikaattorin, joka kertoo, missä kohtaa dataa ollaan, joten rivi `image.seek(0)` siirtää sijainnin takaisin alkuun, jotta kaikki data voidaan lukea myöhemmin.

1. Lisää tämän alle seuraava koodi kuvan tallentamiseksi tiedostoon:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Tämä koodi avaa tiedoston nimeltä `image.jpg` kirjoittamista varten, lukee kaiken datan `BytesIO`-objektista ja kirjoittaa sen tiedostoon.

    > 💁 Voit tallentaa kuvan suoraan tiedostoon ilman `BytesIO`-objektia antamalla tiedostonimen `camera.capture`-kutsulle. Syynä `BytesIO`-objektin käyttöön on se, että myöhemmin tässä oppitunnissa voit lähettää kuvan kuvantunnistimelle.

1. Suuntaa kamera johonkin kohteeseen ja suorita tämä koodi.

1. Kuva tallennetaan ja nimetään `image.jpg` nykyiseen kansioon. Näet tämän tiedoston VS Code -tiedostoselaimessa. Valitse tiedosto nähdäksesi kuvan. Jos se tarvitsee kiertoa, päivitä rivi `camera.rotation = 0` tarpeen mukaan ja ota uusi kuva.

> 💁 Löydät tämän koodin [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) -kansiosta.

😀 Kameran ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.