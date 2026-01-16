<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:03:31+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "fi"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) on yhden piirilevyn tietokone. Voit lisätä antureita ja toimilaitteita käyttämällä laajaa valikoimaa laitteita ja ekosysteemejä. Näissä oppitunneissa käytetään laitteistoekosysteemiä nimeltä [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Koodaat Pi:täsi ja käytät Grove-antureita Pythonin avulla.

![Raspberry Pi 4](../../../../../translated_images/fi/raspberry-pi-4.fd4590d308c3d456.jpg)

## Asennus

Jos käytät Raspberry Pi:tä IoT-laitteistonasi, sinulla on kaksi vaihtoehtoa - voit käydä läpi kaikki nämä oppitunnit ja koodata suoraan Pi:llä, tai voit yhdistää etänä "päätelaitteettomaan" Pi:hin ja koodata tietokoneeltasi.

Ennen kuin aloitat, sinun täytyy myös liittää Grove Base Hat Pi:hen.

### Tehtävä - asennus

Asenna Grove Base Hat Pi:hen ja konfiguroi Pi.

1. Liitä Grove Base Hat Pi:hen. Hatin liitin sopii kaikkiin Pi:n GPIO-pinneihin, ja se liukuu alas pinnejä pitkin istuen tiukasti pohjalle. Se peittää Pi:n kokonaan.

    ![Grove Hatin kiinnitys](../../../../../images/pi-grove-hat-fitting.gif)

1. Päätä, miten haluat ohjelmoida Pi:täsi, ja siirry alla olevaan asiaankuuluvaan osioon:

    * [Työskentele suoraan Pi:llä](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Etäyhteys Pi:n koodaamiseen](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Työskentele suoraan Pi:llä

Jos haluat työskennellä suoraan Pi:llä, voit käyttää Raspberry Pi OS:n työpöytäversiota ja asentaa kaikki tarvittavat työkalut.

#### Tehtävä - työskentele suoraan Pi:llä

Valmistele Pi kehitystyötä varten.

1. Seuraa ohjeita [Raspberry Pi:n asennusoppaassa](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) asentaaksesi Pi:n, yhdistääksesi sen näppäimistöön/hiireen/näyttöön, yhdistääksesi sen WiFi- tai ethernet-verkkoon ja päivittääksesi ohjelmiston.

Pi:n ohjelmoimiseksi Grove-antureiden ja toimilaitteiden avulla sinun täytyy asentaa editori, jolla voit kirjoittaa laiteohjelmointikoodia, sekä erilaisia kirjastoja ja työkaluja, jotka toimivat Grove-laitteiston kanssa.

1. Kun Pi on käynnistynyt uudelleen, avaa Terminal napsauttamalla **Terminal**-kuvaketta ylävalikkopalkissa tai valitse *Menu -> Accessories -> Terminal*

1. Suorita seuraava komento varmistaaksesi, että käyttöjärjestelmä ja asennettu ohjelmisto ovat ajan tasalla:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Suorita seuraavat komennot asentaaksesi kaikki tarvittavat kirjastot Grove-laitteistolle:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Tämä aloittaa Gitin ja Pipin asentamisen Python-pakettien asentamista varten.

    Yksi Pythonin tehokkaista ominaisuuksista on kyky asentaa [Pip-paketteja](https://pypi.org) - nämä ovat muiden ihmisten kirjoittamia ja Internetiin julkaistuja koodipaketteja. Voit asentaa Pip-paketin tietokoneellesi yhdellä komennolla ja käyttää sitä koodissasi.

    Seeed Grove Python -paketit täytyy asentaa lähdekoodista. Nämä komennot kloonaavat repo:n, joka sisältää tämän paketin lähdekoodin, ja asentavat sen paikallisesti.

    > 💁 Oletuksena, kun asennat paketin, se on käytettävissä kaikkialla tietokoneellasi, mikä voi aiheuttaa ongelmia pakettiversioiden kanssa - esimerkiksi yksi sovellus voi riippua yhdestä pakettiversiosta, joka rikkoutuu, kun asennat uuden version toista sovellusta varten. Tämän ongelman välttämiseksi voit käyttää [Python-virtuaaliympäristöä](https://docs.python.org/3/library/venv.html), joka on käytännössä Pythonin kopio omassa kansiossaan, ja kun asennat Pip-paketteja, ne asennetaan vain siihen kansioon. Pi:tä käyttäessäsi et kuitenkaan käytä virtuaaliympäristöjä. Grove-asennusskripti asentaa Grove Python -paketit globaalisti, joten jos haluat käyttää virtuaaliympäristöä, sinun täytyy luoda virtuaaliympäristö ja asentaa Grove-paketit manuaalisesti uudelleen siihen ympäristöön. On helpompaa käyttää globaaleja paketteja, erityisesti koska monet Pi-kehittäjät flashaavat puhtaan SD-kortin jokaista projektia varten.

    Lopuksi tämä ottaa käyttöön I<sup>2</sup>C-liitännän.

1. Käynnistä Pi uudelleen joko valikon kautta tai suorittamalla seuraava komento Terminalissa:

    ```sh
    sudo reboot
    ```

1. Kun Pi on käynnistynyt uudelleen, avaa Terminal uudelleen ja suorita seuraava komento asentaaksesi [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - tämä on editori, jota käytät laiteohjelmointikoodin kirjoittamiseen Pythonilla.

    ```sh
    sudo apt install code
    ```

    Kun tämä on asennettu, VS Code on käytettävissä ylävalikosta.

    > 💁 Voit vapaasti käyttää mitä tahansa Python IDE:tä tai editoria näissä oppitunneissa, jos sinulla on suosikkityökalu, mutta oppitunnit antavat ohjeita perustuen VS Codeen.

1. Asenna Pylance. Tämä on VS Code -laajennus, joka tarjoaa Python-kielen tukea. Katso [Pylance-laajennuksen dokumentaatio](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) ohjeita tämän laajennuksen asentamiseen VS Codeen.

### Etäyhteys Pi:n koodaamiseen

Sen sijaan, että koodaisit suoraan Pi:llä, se voi toimia "päätelaitteettomana", eli ei ole kytkettynä näppäimistöön/hiireen/näyttöön, ja voit konfiguroida ja koodata sitä tietokoneeltasi Visual Studio Coden avulla.

#### Asenna Pi OS

Etäkoodausta varten Pi OS täytyy asentaa SD-kortille.

##### Tehtävä - asenna Pi OS

Asenna päätelaitteeton Pi OS.

1. Lataa **Raspberry Pi Imager** [Raspberry Pi OS -ohjelmistosivulta](https://www.raspberrypi.org/software/) ja asenna se

1. Aseta SD-kortti tietokoneeseesi, tarvittaessa adapterin avulla

1. Käynnistä Raspberry Pi Imager

1. Raspberry Pi Imagerissa valitse **CHOOSE OS** -painike ja valitse *Raspberry Pi OS (Other)*, jonka jälkeen *Raspberry Pi OS Lite (32-bit)*

    ![Raspberry Pi Imager, jossa Raspberry Pi OS Lite valittuna](../../../../../translated_images/fi/raspberry-pi-imager.24aedeab9e233d84.png)

    > 💁 Raspberry Pi OS Lite on Raspberry Pi OS:n versio, jossa ei ole työpöytäkäyttöliittymää tai käyttöliittymäpohjaisia työkaluja. Näitä ei tarvita päätelaitteettomalle Pi:lle, ja tämä tekee asennuksesta pienemmän ja käynnistysajasta nopeamman.

1. Valitse **CHOOSE STORAGE** -painike ja valitse SD-korttisi

1. Käynnistä **Advanced Options** painamalla `Ctrl+Shift+X`. Nämä asetukset mahdollistavat Raspberry Pi OS:n esikonfiguroinnin ennen sen kirjoittamista SD-kortille.

    1. Valitse **Enable SSH** -valintaruutu ja aseta salasana `pi`-käyttäjälle. Tämä on salasana, jota käytät kirjautuaksesi Pi:lle myöhemmin.

    1. Jos aiot yhdistää Pi:n WiFi:n kautta, valitse **Configure WiFi** -valintaruutu ja syötä WiFi SSID ja salasana sekä valitse WiFi-maa. Tätä ei tarvitse tehdä, jos käytät ethernet-kaapelia. Varmista, että verkko, johon yhdistät, on sama kuin tietokoneesi.

    1. Valitse **Set locale settings** -valintaruutu ja aseta maa ja aikavyöhyke

    1. Valitse **SAVE**-painike

1. Valitse **WRITE**-painike kirjoittaaksesi käyttöjärjestelmän SD-kortille. Jos käytät macOS:ia, sinua pyydetään syöttämään salasanasi, koska taustalla oleva työkalu, joka kirjoittaa levykuvia, tarvitsee oikeudet.

Käyttöjärjestelmä kirjoitetaan SD-kortille, ja kun se on valmis, kortti poistetaan käyttöjärjestelmän toimesta, ja sinulle ilmoitetaan. Poista SD-kortti tietokoneestasi, aseta se Pi:hen, käynnistä Pi ja odota noin 2 minuuttia, että se käynnistyy kunnolla.

#### Yhdistä Pi:hin

Seuraava vaihe on Pi:n etäkäyttö. Voit tehdä tämän käyttämällä `ssh`:ta, joka on saatavilla macOS:issa, Linuxissa ja Windowsin uusimmissa versioissa.

##### Tehtävä - yhdistä Pi:hin

Yhdistä Pi:hin etänä.

1. Käynnistä Terminal tai Command Prompt ja syötä seuraava komento yhdistääksesi Pi:hin:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Jos käytät Windowsia vanhemmalla versiolla, jossa ei ole `ssh`:ta asennettuna, voit käyttää OpenSSH:ta. Löydät asennusohjeet [OpenSSH:n asennusdokumentaatiosta](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Tämä yhdistää Pi:hin ja pyytää salasanaa.

    Kyky löytää tietokoneita verkostasi käyttämällä `<hostname>.local` on melko uusi lisäys Linuxiin ja Windowsiin. Jos käytät Linuxia tai Windowsia ja saat virheitä, joissa Hostnamea ei löydy, sinun täytyy asentaa lisäohjelmisto ZeroConf-verkkoyhteyden mahdollistamiseksi (Apple kutsuu tätä Bonjouriksi):

    1. Jos käytät Linuxia, asenna Avahi seuraavalla komennolla:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Jos käytät Windowsia, helpoin tapa ottaa ZeroConf käyttöön on asentaa [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Voit myös asentaa [iTunes for Windows](https://www.apple.com/itunes/download/) saadaksesi uudemman version apuohjelmasta (joka ei ole saatavilla erillisenä).

    > 💁 Jos et voi yhdistää käyttämällä `raspberrypi.local`, voit käyttää Pi:n IP-osoitetta. Katso [Raspberry Pi IP-osoite dokumentaatio](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) ohjeita useista tavoista saada IP-osoite.

1. Syötä salasana, jonka asetit Raspberry Pi Imager Advanced Options -asetuksissa.

#### Konfiguroi ohjelmisto Pi:llä

Kun olet yhdistänyt Pi:hin, sinun täytyy varmistaa, että käyttöjärjestelmä on ajan tasalla, ja asentaa erilaisia kirjastoja ja työkaluja, jotka toimivat Grove-laitteiston kanssa.

##### Tehtävä - konfiguroi ohjelmisto Pi:llä

Konfiguroi asennettu Pi-ohjelmisto ja asenna Grove-kirjastot.

1. `ssh`-istunnostasi suorita seuraava komento päivittääksesi ja käynnistääksesi Pi uudelleen:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi päivitetään ja käynnistetään uudelleen. `ssh`-istunto päättyy, kun Pi käynnistetään uudelleen, joten odota noin 30 sekuntia ja yhdistä uudelleen.

1. Uudelleen yhdistetystä `ssh`-istunnosta suorita seuraavat komennot asentaaksesi kaikki tarvittavat kirjastot Grove-laitteistolle:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Tämä aloittaa Gitin ja Pipin asentamisen Python-pakettien asentamista varten.

    Yksi Pythonin tehokkaista ominaisuuksista on kyky asentaa [Pip-paketteja](https://pypi.org) - nämä ovat muiden ihmisten kirjoittamia ja Internetiin julkaistuja koodipaketteja. Voit asentaa Pip-paketin tietokoneellesi yhdellä komennolla ja käyttää sitä koodissasi.

    Seeed Grove Python -paketit täytyy asentaa lähdekoodista. Nämä komennot kloonaavat repo:n, joka sisältää tämän paketin lähdekoodin, ja asentavat sen paikallisesti.

    > 💁 Oletuksena, kun asennat paketin, se on käytettävissä kaikkialla tietokoneellasi, mikä voi aiheuttaa ongelmia pakettiversioiden kanssa - esimerkiksi yksi sovellus voi riippua yhdestä pakettiversiosta, joka rikkoutuu, kun asennat uuden version toista sovellusta varten. Tämän ongelman välttämiseksi voit käyttää [Python-virtuaaliympäristöä](https://docs.python.org/3/library/venv.html), joka on käytännössä Pythonin kopio omassa kansiossaan, ja kun asennat Pip-paketteja, ne asennetaan vain siihen kansioon. Pi:tä käyttäessäsi et kuitenkaan käytä virtuaaliympäristöjä. Grove-asennusskripti asentaa Grove Python -paketit globaalisti, joten jos haluat käyttää virtuaaliympäristöä, sinun täytyy luoda virtuaaliympäristö ja asentaa Grove-paketit manuaalisesti uudelleen siihen ympäristöön. On helpompaa käyttää globaaleja paketteja, erityisesti koska monet Pi-kehittäjät flashaavat puhtaan SD-kortin jokaista projektia varten.

    Lopuksi tämä ottaa käyttöön I<sup>2</sup>C-liitännän.

1. Käynnistä Pi uudelleen suorittamalla seuraava komento:

    ```sh
    sudo reboot
    ```

    `ssh`-istunto päättyy, kun Pi käynnistetään uudelleen. Uudelleen yhdistäminen ei ole tarpeen.

#### Konfiguroi VS Code etäkäyttöä varten

Kun Pi on konfiguroitu, voit yhdistää siihen Visual Studio Coden (VS Code) avulla tietokoneeltasi - tämä on ilmainen kehittäjien tekstieditori, jota käytät laiteohjelmointikoodin kirjoittamiseen Pythonilla.

##### Tehtävä - konfiguroi VS Code etäkäyttöä varten

Asenna tarvittava ohjelmisto ja yhdistä etänä Pi:hin.

1. Asenna VS Code tietokoneellesi seuraamalla [VS Code -dokumentaatiota](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

1. Seuraa ohjeita [VS Code Remote Development using SSH -dokumentaatiossa](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) asentaaksesi tarvittavat komponentit

1. Seuraa samoja ohjeita yhdistääksesi VS Code Pi:hin

1. Kun olet yhdistänyt, seuraa [laajennusten hallinta](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) -ohjeita asentaaksesi [Pylance-laajennuksen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) etänä Pi:lle

## Hello world
On perinteistä, että uuden ohjelmointikielen tai teknologian parissa aloitetaan luomalla 'Hello World' -sovellus – pieni sovellus, joka tulostaa esimerkiksi tekstin `"Hello World"` osoittaakseen, että kaikki työkalut on asennettu oikein.

Pi:n Hello World -sovellus varmistaa, että Python ja Visual Studio Code on asennettu oikein.

Tämä sovellus sijaitsee kansiossa nimeltä `nightlight`, ja sitä käytetään myöhemmin eri koodilla osana tätä tehtävää yövalosovelluksen rakentamiseksi.

### Tehtävä - hello world

Luo Hello World -sovellus.

1. Käynnistä VS Code joko suoraan Pi:llä tai tietokoneellasi ja yhdistä Pi:hin Remote SSH -laajennuksen avulla.

1. Avaa VS Code -pääte valitsemalla *Terminal -> New Terminal* tai painamalla `` CTRL+` ``. Pääte avautuu `pi`-käyttäjän kotihakemistoon.

1. Suorita seuraavat komennot luodaksesi hakemiston koodillesi ja Python-tiedoston nimeltä `app.py` kyseiseen hakemistoon:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Avaa tämä kansio VS Codessa valitsemalla *File -> Open...* ja valitsemalla *nightlight*-kansio, sitten valitse **OK**.

    ![VS Code -avausdialogi, jossa näkyy nightlight-kansio](../../../../../translated_images/fi/vscode-open-nightlight-remote.d3d2a4011e30d535.png)

1. Avaa `app.py`-tiedosto VS Code -tiedostoselaimesta ja lisää seuraava koodi:

    ```python
    print('Hello World!')
    ```

    `print`-funktio tulostaa konsoliin sen, mitä sille annetaan.

1. Suorita Python-sovelluksesi VS Code -päätteestä seuraavalla komennolla:

    ```sh
    python app.py
    ```

    > 💁 Saatat joutua kutsumaan nimenomaisesti `python3` suorittaaksesi tämän koodin, jos sinulla on asennettuna Python 2 Python 3:n lisäksi (uusin versio). Jos sinulla on Python 2 asennettuna, `python` käyttää Python 2:ta Python 3:n sijaan. Oletuksena uusimmissa Raspberry Pi OS -versioissa on vain Python 3 asennettuna.

    Seuraava tulostus ilmestyy päätteeseen:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Löydät tämän koodin [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) -kansiosta.

😀 'Hello World' -ohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.