# Lue GPS-data - Raspberry Pi

Tässä osassa oppituntia lisäät GPS-anturin Raspberry Pi:hin ja luet sen antamia arvoja.

## Laitteisto

Raspberry Pi tarvitsee GPS-anturin.

Käytettävä anturi on [Grove GPS Air530 -anturi](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Tämä anturi voi yhdistyä useisiin GPS-järjestelmiin nopean ja tarkan sijainnin määrittämiseksi. Anturi koostuu kahdesta osasta - anturin ydinelektroniikasta ja ulkoisesta antennista, joka on yhdistetty ohuella johdolla satelliittien radiotaajuuksien vastaanottamiseksi.

Tämä on UART-anturi, joten se lähettää GPS-dataa UARTin kautta.

## Yhdistä GPS-anturi

Grove GPS -anturi voidaan yhdistää Raspberry Pi:hin.

### Tehtävä - yhdistä GPS-anturi

Yhdistä GPS-anturi.

![Grove GPS -anturi](../../../../../translated_images/fi/grove-gps-sensor.247943bf69b03f0d.webp)

1. Työnnä Grove-kaapelin toinen pää GPS-anturin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Raspberry Pi on sammutettu, yhdistä Grove-kaapelin toinen pää UART-liittimeen, joka on merkitty **UART** Grove Base -hatissa, joka on kiinnitetty Pi:hin. Tämä liitin sijaitsee keskimmäisellä rivillä, SD-korttipaikan puolella, USB-porttien ja Ethernet-liittimen vastakkaisella puolella.

    ![Grove GPS -anturi yhdistetty UART-liittimeen](../../../../../translated_images/fi/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Aseta GPS-anturi niin, että siihen kiinnitetty antenni on näkyvissä taivaalle - mieluiten avoimen ikkunan vieressä tai ulkona. On helpompi saada selkeämpi signaali, kun antennin edessä ei ole esteitä.

## Ohjelmoi GPS-anturi

Raspberry Pi voidaan nyt ohjelmoida käyttämään liitettyä GPS-anturia.

### Tehtävä - ohjelmoi GPS-anturi

Ohjelmoi laite.

1. Käynnistä Pi ja odota, että se käynnistyy.

1. GPS-anturissa on kaksi LED-valoa - sininen LED, joka vilkkuu, kun dataa lähetetään, ja vihreä LED, joka vilkkuu sekunnin välein, kun satelliiteista vastaanotetaan dataa. Varmista, että sininen LED vilkkuu, kun käynnistät Pi:n. Muutaman minuutin kuluttua vihreä LED alkaa vilkkua - jos ei, sinun täytyy ehkä siirtää antennia.

1. Käynnistä VS Code joko suoraan Pi:ssä tai yhdistä Remote SSH -laajennuksen kautta.

    > ⚠️ Voit viitata [ohjeisiin VS Coden asennuksesta ja käynnistämisestä oppitunnilla 1 tarvittaessa](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Uudemmissa Raspberry Pi -malleissa, jotka tukevat Bluetoothia, on ristiriita Bluetoothin käyttämän sarjaportin ja Grove UART -portin käyttämän sarjaportin välillä. Korjaa tämä seuraavasti:

    1. VS Code -terminaalista muokkaa `/boot/config.txt` -tiedostoa käyttämällä `nano`-editoria seuraavalla komennolla:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Tätä tiedostoa ei voi muokata VS Codessa, koska sinun täytyy käyttää `sudo`-oikeuksia, eli korotettuja käyttöoikeuksia. VS Code ei toimi näillä oikeuksilla.

    1. Käytä nuolinäppäimiä siirtyäksesi tiedoston loppuun ja kopioi alla oleva koodi tiedoston loppuun:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Voit liittää koodin käyttämällä laitteen normaaleja näppäinyhdistelmiä (`Ctrl+v` Windowsissa, Linuxissa tai Raspberry Pi OS:ssa, `Cmd+v` macOS:ssa).

    1. Tallenna tiedosto ja poistu nanosta painamalla `Ctrl+x`. Paina `y`, kun sinulta kysytään, haluatko tallentaa muutetun puskurin, ja paina sitten `enter` vahvistaaksesi, että haluat korvata `/boot/config.txt`.

        > Jos teet virheen, voit poistua tallentamatta ja toistaa nämä vaiheet.

    1. Muokkaa `/boot/cmdline.txt` -tiedostoa nanossa seuraavalla komennolla:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Tämä tiedosto sisältää useita avain/arvo-pareja, jotka on erotettu välilyönneillä. Poista kaikki avain/arvo-parit, joiden avain on `console`. Ne näyttävät todennäköisesti tältä:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Voit siirtyä näihin merkintöihin nuolinäppäimillä ja poistaa ne käyttämällä normaaleja `del`- tai `backspace`-näppäimiä.

        Esimerkiksi, jos alkuperäinen tiedosto näyttää tältä:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Uusi versio näyttää tältä:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Noudata yllä olevia ohjeita tallentaaksesi tiedoston ja poistuaksesi nanosta.

    1. Käynnistä Pi uudelleen ja yhdistä VS Codeen, kun Pi on käynnistynyt.

1. Luo terminaalista uusi kansio `pi`-käyttäjän kotihakemistoon nimeltä `gps-sensor`. Luo tiedosto tässä kansiossa nimeltä `app.py`.

1. Avaa tämä kansio VS Codessa.

1. GPS-moduuli lähettää UART-dataa sarjaportin kautta. Asenna `pyserial` Pip-paketti, jotta voit kommunikoida sarjaportin kanssa Python-koodistasi:

    ```sh
    pip3 install pyserial
    ```

1. Lisää seuraava koodi `app.py`-tiedostoosi:

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

    Tämä koodi tuo `serial`-moduulin `pyserial` Pip-paketista. Se yhdistää `/dev/ttyAMA0`-sarjaporttiin - tämä on Grove Pi Base Hatin UART-portin osoite. Se tyhjentää kaikki olemassa olevat tiedot tästä sarjayhteydestä.

    Seuraavaksi määritellään funktio nimeltä `print_gps_data`, joka tulostaa sille välitetyn rivin konsoliin.

    Sitten koodi suorittaa ikuisen silmukan, jossa se lukee niin monta tekstiriviä kuin mahdollista sarjaportista jokaisessa silmukan kierrossa. Se kutsuu `print_gps_data`-funktiota jokaiselle riville.

    Kun kaikki data on luettu, silmukka odottaa 1 sekunnin ja yrittää uudelleen.

1. Suorita tämä koodi. Näet GPS-anturin raakadataa, joka näyttää suunnilleen tältä:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Jos saat seuraavat virheet, kun pysäytät ja käynnistät koodin uudelleen, lisää `try - except`-lohko while-silmukkaasi.

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

> 💁 Löydät tämän koodin [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) -kansiosta.

😀 GPS-anturin ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.