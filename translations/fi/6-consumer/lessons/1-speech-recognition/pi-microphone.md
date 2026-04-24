# Määritä mikrofoni ja kaiuttimet - Raspberry Pi

Tässä osassa oppituntia lisäät mikrofonin ja kaiuttimet Raspberry Pi:hin.

## Laitteisto

Raspberry Pi tarvitsee mikrofonin.

Pi:ssä ei ole sisäänrakennettua mikrofonia, joten sinun täytyy lisätä ulkoinen mikrofoni. Tämä voidaan tehdä useilla tavoilla:

* USB-mikrofoni
* USB-kuulokemikrofoni
* USB-kaiutinpuhelin
* USB-äänisovitin ja mikrofoni, jossa on 3,5 mm liitin
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Kaikkia Bluetooth-mikrofoneja ei tueta Raspberry Pi:ssä, joten jos sinulla on Bluetooth-mikrofoni tai -kuulokkeet, niiden yhdistämisessä tai äänen tallentamisessa voi ilmetä ongelmia.

Raspberry Pi:ssä on 3,5 mm kuulokeliitäntä. Voit käyttää sitä kuulokkeiden, kuulokemikrofonin tai kaiuttimen liittämiseen. Voit myös lisätä kaiuttimia seuraavilla tavoilla:

* HDMI-ääni näytön tai television kautta
* USB-kaiuttimet
* USB-kuulokemikrofoni
* USB-kaiutinpuhelin
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html), johon on liitetty kaiutin joko 3,5 mm liittimen tai JST-portin kautta

## Liitä ja määritä mikrofoni ja kaiuttimet

Mikrofoni ja kaiuttimet täytyy liittää ja määrittää.

### Tehtävä - liitä ja määritä mikrofoni

1. Liitä mikrofoni sopivalla tavalla. Esimerkiksi liitä se yhteen USB-porteista.

1. Jos käytät ReSpeaker 2-Mics Pi HAT:ia, voit poistaa Grove-pohjahatun ja asentaa ReSpeaker-hatun sen tilalle.

    ![Raspberry Pi, jossa on ReSpeaker-hattu](../../../../../translated_images/fi/pi-respeaker-hat.f00fabe7dd039a93.webp)

    Tarvitset Grove-painikkeen myöhemmin tässä oppitunnissa, mutta sellainen on sisäänrakennettuna tässä hatussa, joten Grove-pohjahattua ei tarvita.

    Kun hattu on asennettu, sinun täytyy asentaa ajurit. Katso [Seeedin aloitusohjeet](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) ajureiden asennusohjeita varten.

    > ⚠️ Ohjeissa käytetään `git`-komentoa arkiston kloonaamiseen. Jos `git` ei ole asennettuna Pi:ssäsi, voit asentaa sen suorittamalla seuraavan komennon:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Suorita seuraava komento Terminalissa joko Pi:ssä tai yhdistettynä VS Coden ja etä-SSH-istunnon kautta nähdäksesi tietoja liitetystä mikrofonista:

    ```sh
    arecord -l
    ```

    Näet luettelon liitetyistä mikrofoneista. Se näyttää suunnilleen tältä:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Jos sinulla on vain yksi mikrofoni, näet vain yhden merkinnän. Mikrofonien määrittäminen voi olla haastavaa Linuxissa, joten on helpointa käyttää vain yhtä mikrofonia ja irrottaa mahdolliset muut.

    Kirjoita kortin numero muistiin, sillä tarvitset sitä myöhemmin. Yllä olevassa esimerkissä kortin numero on 1.

### Tehtävä - liitä ja määritä kaiutin

1. Liitä kaiuttimet sopivalla tavalla.

1. Suorita seuraava komento Terminalissa joko Pi:ssä tai yhdistettynä VS Coden ja etä-SSH-istunnon kautta nähdäksesi tietoja liitetyistä kaiuttimista:

    ```sh
    aplay -l
    ```

    Näet luettelon liitetyistä kaiuttimista. Se näyttää suunnilleen tältä:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Näet aina `card 0: Headphones`, joka on sisäänrakennettu kuulokeliitäntä. Jos olet lisännyt muita kaiuttimia, kuten USB-kaiuttimen, näet sen myös luettelossa.

1. Jos käytät lisäkaiutinta etkä sisäänrakennettuun kuulokeliitäntään liitettyä kaiutinta tai kuulokkeita, sinun täytyy määrittää se oletuskaiuttimeksi. Tee tämä suorittamalla seuraava komento:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Tämä avaa konfiguraatiotiedoston `nano`-tekstieditorissa, joka toimii terminaalissa. Vieritä alaspäin nuolinäppäimillä, kunnes löydät seuraavan rivin:

    ```output
    defaults.pcm.card 0
    ```

    Vaihda arvo `0`:sta siihen kortin numeroon, jonka haluat käyttää, perustuen `aplay -l`-komennon palauttamaan luetteloon. Esimerkiksi yllä olevassa esimerkissä on toinen äänikortti nimeltä `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, joka käyttää korttia 1. Käyttääksesi tätä päivittäisin rivin seuraavasti:

    ```output
    defaults.pcm.card 1
    ```

    Aseta tämä arvo oikeaan kortin numeroon. Voit siirtyä numeroon nuolinäppäimillä ja poistaa sekä kirjoittaa uuden numeron normaalisti tekstieditoria käyttäessäsi.

1. Tallenna muutokset ja sulje tiedosto painamalla `Ctrl+x`. Paina `y` tallentaaksesi tiedoston ja `return` valitaksesi tiedostonimen.

### Tehtävä - testaa mikrofoni ja kaiutin

1. Suorita seuraava komento tallentaaksesi 5 sekuntia ääntä mikrofonin kautta:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Kun tämä komento on käynnissä, tuota ääntä mikrofoniin, esimerkiksi puhumalla, laulamalla, beatboxaamalla, soittamalla instrumenttia tai mitä ikinä haluatkaan.

1. Viiden sekunnin jälkeen tallennus pysähtyy. Suorita seuraava komento toistaaksesi äänen:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Kuulemasi ääni toistetaan kaiuttimien kautta. Säädä kaiuttimen äänenvoimakkuutta tarvittaessa.

1. Jos sinun täytyy säätää sisäänrakennetun mikrofoniliitännän äänenvoimakkuutta tai mikrofonin vahvistusta, voit käyttää `alsamixer`-työkalua. Voit lukea lisää tästä työkalusta [Linux alsamixer -manuaalisivulta](https://linux.die.net/man/1/alsamixer).

1. Jos äänen toistossa ilmenee virheitä, tarkista `alsa.conf`-tiedostossa asetettu `defaults.pcm.card`-arvo.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Pyrimme tarkkuuteen, mutta huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulee pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskääntämistä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.