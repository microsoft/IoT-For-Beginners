# Suorita hedelmätunnistin reunalaitteella

![Tämän oppitunnin yleiskuvaus sketchnotena](../../../../../translated_images/fi/lesson-17.bc333c3c35ba8e42.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä video tarjoaa yleiskatsauksen kuvantunnistimien suorittamisesta IoT-laitteilla, aiheesta, jota käsitellään tässä oppitunnissa.

[![Custom Vision AI Azure IoT Edgessä](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Johdanto

Edellisessä oppitunnissa käytit kuvantunnistinta kypsien ja raakojen hedelmien luokitteluun, lähettäen IoT-laitteesi kameralla otetun kuvan internetin kautta pilvipalveluun. Nämä kutsut vievät aikaa, maksavat rahaa ja voivat kuvadatan tyypistä riippuen aiheuttaa yksityisyysongelmia.

Tässä oppitunnissa opit, kuinka koneoppimismalleja (ML) voidaan suorittaa reunalaitteilla – IoT-laitteilla, jotka toimivat omassa verkossasi pilven sijaan. Opit reunalaskennan ja pilvilaskennan hyödyt ja haitat, kuinka AI-malli otetaan käyttöön reunalaitteella ja kuinka siihen pääsee käsiksi IoT-laitteelta.

Tässä oppitunnissa käsitellään:

* [Reunalaskenta](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge -laitteen rekisteröinti](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge -laitteen asennus](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Mallin vienti](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Kontin valmistelu käyttöönottoa varten](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Kontin käyttöönotto](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge -laitteen käyttö](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Reunalaskenta

Reunalaskenta tarkoittaa IoT-datan käsittelyä mahdollisimman lähellä sen syntypaikkaa. Sen sijaan, että käsittely tapahtuisi pilvessä, se siirretään pilven reunalle – sisäiseen verkkoosi.

![Arkkitehtuurikaavio, jossa internetpalvelut pilvessä ja IoT-laitteet paikallisessa verkossa](../../../../../translated_images/fi/cloud-without-edge.b4da641f6022c95e.webp)

Tähän mennessä oppitunneilla laitteet ovat keränneet dataa ja lähettäneet sen pilveen analysoitavaksi, suorittaen pilvessä serverittömiä toimintoja tai AI-malleja.

![Arkkitehtuurikaavio, jossa IoT-laitteet paikallisessa verkossa yhdistyvät reunalaitteisiin, ja nämä reunalaitteet yhdistyvät pilveen](../../../../../translated_images/fi/cloud-with-edge.1e26462c62c126fe.webp)

Reunalaskenta siirtää osan pilvipalveluista pois pilvestä ja tietokoneille, jotka toimivat samalla verkolla kuin IoT-laitteet, kommunikoiden pilven kanssa vain tarvittaessa. Esimerkiksi AI-malleja voidaan suorittaa reunalaitteilla hedelmien kypsyyden analysoimiseksi, ja pilveen lähetetään vain analytiikkaa, kuten kypsien ja raakojen hedelmien lukumäärä.

✅ Mieti IoT-sovelluksia, joita olet tähän mennessä rakentanut. Mitkä osat niistä voitaisiin siirtää reunalle?

### Hyödyt

Reunalaskennan hyödyt ovat:

1. **Nopeus** – reunalaskenta sopii hyvin ajallisesti kriittiseen dataan, sillä toiminnot tapahtuvat samalla verkolla kuin laite, sen sijaan että tehtäisiin kutsuja internetin kautta. Tämä mahdollistaa suuremmat nopeudet, sillä sisäiset verkot voivat toimia huomattavasti nopeammin kuin internet-yhteydet, ja data kulkee paljon lyhyemmän matkan.

    > 💁 Vaikka internet-yhteyksissä käytetään optisia kaapeleita, jotka mahdollistavat datan kulkemisen valon nopeudella, datan kulkeminen ympäri maailmaa pilvipalveluntarjoajille vie aikaa. Esimerkiksi, jos lähetät dataa Euroopasta pilvipalveluihin Yhdysvalloissa, datan kulkeminen Atlantin yli optisessa kaapelissa vie vähintään 28 ms, ja tämä ei sisällä aikaa, joka kuluu datan saamiseen transatlanttiselle kaapelille, sähköisten signaalien muuntamiseen valosignaaleiksi ja takaisin toisella puolella, sekä pilvipalveluntarjoajalle pääsyyn.

    Reunalaskenta vaatii myös vähemmän verkkoliikennettä, mikä vähentää riskiä datan hidastumisesta internet-yhteyden rajallisen kaistanleveyden ruuhkautumisen vuoksi.

1. **Etäkäyttö** – reunalaskenta toimii, kun yhteys on rajallinen tai puuttuu kokonaan, tai yhteyden käyttö on liian kallista jatkuvaan käyttöön. Esimerkiksi humanitaarisissa katastrofialueilla, joissa infrastruktuuri on rajallinen, tai kehittyvissä maissa.

1. **Alhaisemmat kustannukset** – datan kerääminen, tallentaminen, analysointi ja toimintojen käynnistäminen reunalaitteella vähentää pilvipalveluiden käyttöä, mikä voi pienentää IoT-sovelluksen kokonaiskustannuksia. Viime aikoina on tullut markkinoille laitteita, jotka on suunniteltu reunalaskentaan, kuten AI-kiihdytyskortit, kuten [Jetson Nano NVIDIA:lta](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), jotka voivat suorittaa AI-tehtäviä GPU-pohjaisella laitteistolla alle 100 dollarin hintaan.

1. **Yksityisyys ja turvallisuus** – reunalaskennan avulla data pysyy verkossasi eikä sitä ladata pilveen. Tämä on usein suositeltavaa arkaluontoisen ja henkilökohtaisesti tunnistettavan tiedon kohdalla, erityisesti koska dataa ei tarvitse tallentaa analysoinnin jälkeen, mikä vähentää merkittävästi tietovuotojen riskiä. Esimerkkejä ovat lääketieteellinen data ja valvontakameran kuvamateriaali.

1. **Turvattomien laitteiden käsittely** – jos sinulla on laitteita, joissa on tunnettuja turvallisuuspuutteita, joita et halua yhdistää suoraan verkkoosi tai internetiin, voit yhdistää ne erilliseen verkkoon, jossa on yhdyskäytävä IoT Edge -laite. Tämä reunalaite voi sitten olla yhteydessä laajempaan verkkoosi tai internetiin ja hallita datavirtoja edestakaisin.

1. **Yhteensopimattomien laitteiden tuki** – jos sinulla on laitteita, jotka eivät voi yhdistyä IoT Hubiin, esimerkiksi laitteita, jotka voivat yhdistyä vain HTTP-yhteyksillä tai laitteita, joilla on vain Bluetooth-yhteys, voit käyttää IoT Edge -laitetta yhdyskäytävälaitteena, joka välittää viestit IoT Hubiin.

✅ Tee tutkimusta: Mitä muita hyötyjä reunalaskennalla voisi olla?

### Haitat

Reunalaskennalla on haittoja, joissa pilvi voi olla parempi vaihtoehto:

1. **Skaalautuvuus ja joustavuus** – pilvilaskenta voi mukautua verkon ja datan tarpeisiin reaaliajassa lisäämällä tai vähentämällä palvelimia ja muita resursseja. Lisää reunalaitteita vaatii manuaalista laitteiden lisäämistä.

1. **Luotettavuus ja kestävyys** – pilvilaskenta tarjoaa useita palvelimia usein useissa sijainneissa redundanssia ja katastrofien palautusta varten. Sama taso redundanssia reunalla vaatii suuria investointeja ja paljon konfigurointityötä.

1. **Ylläpito** – pilvipalveluntarjoajat tarjoavat järjestelmän ylläpidon ja päivitykset.

✅ Tee tutkimusta: Mitä muita haittoja reunalaskennalla voisi olla?

Haitat ovat oikeastaan pilvilaskennan hyötyjen vastakohtia – sinun täytyy rakentaa ja hallita näitä laitteita itse sen sijaan, että luottaisit pilvipalveluntarjoajien asiantuntemukseen ja skaalautuvuuteen.

Joissakin tapauksissa riskit lievennetään reunalaskennan luonteen vuoksi. Esimerkiksi, jos sinulla on reunalaite, joka toimii tehtaassa keräten dataa koneista, sinun ei tarvitse miettiä joitakin katastrofipalautusskenaarioita. Jos tehtaan sähköt katkeavat, sinun ei tarvitse varalaitetta, koska koneet, jotka tuottavat dataa reunalaitteen käsiteltäväksi, ovat myös ilman sähköä.

IoT-järjestelmissä haluat usein yhdistää pilvi- ja reunalaskennan, hyödyntäen kumpaakin palvelua järjestelmän, sen asiakkaiden ja ylläpitäjien tarpeiden mukaan.

## Azure IoT Edge

![Azure IoT Edge -logo](../../../../../translated_images/fi/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge on palvelu, joka voi auttaa siirtämään työkuormia pois pilvestä reunalle. Voit määrittää laitteen reunalaitteeksi ja pilvestä käsin ottaa käyttöön koodia kyseiselle reunalaitteelle. Tämä mahdollistaa pilven ja reunan kyvykkyyksien yhdistämisen.

> 🎓 *Työkuormat* tarkoittavat mitä tahansa palvelua, joka tekee jonkinlaista työtä, kuten AI-malleja, sovelluksia tai serverittömiä toimintoja.

Esimerkiksi voit kouluttaa kuvantunnistimen pilvessä ja ottaa sen käyttöön reunalaitteella pilvestä käsin. IoT-laitteesi lähettää sitten kuvia reunalaitteelle luokittelua varten sen sijaan, että lähettäisi kuvat internetin kautta. Jos tarvitset uuden mallin version, voit kouluttaa sen pilvessä ja käyttää IoT Edgeä päivittääksesi mallin reunalaitteella uuteen versioon.

> 🎓 IoT Edgeen otettu käyttöön ohjelmisto tunnetaan nimellä *moduulit*. Oletuksena IoT Edge suorittaa moduuleja, jotka kommunikoivat IoT Hubin kanssa, kuten `edgeAgent` ja `edgeHub` -moduulit. Kun otat kuvantunnistimen käyttöön, se otetaan käyttöön lisämoduulina.

IoT Edge on sisäänrakennettu IoT Hubiin, joten voit hallita reunalaitteita samalla palvelulla, jota käyttäisit IoT-laitteiden hallintaan, samalla turvallisuustasolla.

IoT Edge suorittaa koodia *konteista* – itsenäisistä sovelluksista, jotka toimivat erillään muista tietokoneesi sovelluksista. Kun suoritat kontin, se toimii kuin erillinen tietokone tietokoneesi sisällä, omilla ohjelmistoillaan, palveluillaan ja sovelluksillaan. Useimmiten kontit eivät pääse käsiksi mihinkään tietokoneellasi, ellei valitse jakaa esimerkiksi kansiota kontin kanssa. Kontti sitten tarjoaa palveluita avoimen portin kautta, johon voit yhdistää tai altistaa verkollesi.

![Verkkopyyntö ohjataan konttiin](../../../../../translated_images/fi/container-web-browser.4ee81dd4f0d8838c.webp)

Esimerkiksi voit olla kontti, jossa verkkosivusto toimii portissa 80, oletus HTTP-portissa, ja voit sitten altistaa sen tietokoneeltasi myös portissa 80.

✅ Tee tutkimusta: Lue kontteja ja palveluita, kuten Docker tai Moby.

Voit käyttää Custom Visionia ladataksesi kuvantunnistimia ja ottaa ne käyttöön kontteina, joko suoraan laitteelle tai IoT Edgen kautta. Kun ne toimivat kontissa, niihin pääsee käsiksi samalla REST-rajapinnalla kuin pilviversioon, mutta päätepiste osoittaa reunalaitteelle, joka suorittaa konttia.

## IoT Edge -laitteen rekisteröinti

IoT Edge -laitteen käyttöä varten se täytyy rekisteröidä IoT Hubissa.

### Tehtävä – IoT Edge -laitteen rekisteröinti

1. Luo IoT Hub `fruit-quality-detector` -resurssiryhmään. Anna sille yksilöllinen nimi, joka perustuu `fruit-quality-detector`iin.

1. Rekisteröi IoT Edge -laite nimeltä `fruit-quality-detector-edge` IoT Hubissasi. Komento tämän tekemiseen on samanlainen kuin ei-reunalaitteen rekisteröintiin käytetty komento, paitsi että lisäät `--edge-enabled` -lipun.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Korvaa `<hub_name>` IoT Hubisi nimellä.

1. Hanki laitteen yhteysmerkkijono seuraavalla komennolla:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Korvaa `<hub_name>` IoT Hubisi nimellä.

    Ota kopio yhteysmerkkijonosta, joka näkyy tulosteessa.

## IoT Edge -laitteen asennus

Kun olet luonut reunalaitteen rekisteröinnin IoT Hubissa, voit asentaa reunalaitteen.

### Tehtävä – IoT Edge -ajonaikaisen ympäristön asennus ja käynnistys

**IoT Edge -ajonaikainen ympäristö tukee vain Linux-kontteja.** Se voidaan suorittaa Linuxissa tai Windowsissa Linux-virtuaalikoneiden avulla.

* Jos käytät Raspberry Pi:tä IoT-laitteena, se käyttää tuettua Linux-versiota ja voi isännöidä IoT Edge -ajonaikaista ympäristöä. Seuraa [Azure IoT Edge -asennusohjetta Linuxille Microsoftin dokumentaatiossa](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) asentaaksesi IoT Edgen ja asettaaksesi yhteysmerkkijonon.

    > 💁 Muista, että Raspberry Pi OS on Debian Linuxin muunnelma.

* Jos et käytä Raspberry Pi:tä, mutta sinulla on Linux-tietokone, voit suorittaa IoT Edge -ajonaikaisen ympäristön. Seuraa [Azure IoT Edge -asennusohjetta Linuxille Microsoftin dokumentaatiossa](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) asentaaksesi IoT Edgen ja asettaaksesi yhteysmerkkijonon.

* Jos käytät Windowsia, voit asentaa IoT Edge -ajonaikaisen ympäristön Linux-virtuaalikoneeseen seuraamalla [IoT Edge -moduulin käyttöönotto Windows-laitteelle -pikaohjetta Microsoftin dokumentaatiossa](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Voit lopettaa, kun saavut *Moduulin käyttöönotto* -osioon.

* Jos käytät macOS:ia, voit luoda virtuaalikoneen (VM) pilvessä IoT Edge -laitteeksi. Nämä ovat tietokoneita, joita voit luoda pilvessä ja käyttää internetin kautta. Voit luoda Linux-VM:n, jossa on IoT Edge asennettuna. Seuraa [virtuaalikoneen luominen IoT Edgen kanssa -ohjetta](vm-iotedge.md) saadaksesi ohjeet tämän tekemiseen.

## Mallin vienti

Jotta tunnistin voidaan suorittaa reunalla, se täytyy viedä Custom Visionista. Custom Vision voi luoda kahdenlaisia malleja – standardimalleja ja kompaktimalleja. Kompaktimallit käyttävät erilaisia tekniikoita pienentääkseen mallin kokoa, tehden siitä tarpeeksi pienen ladattavaksi ja otettavaksi käyttöön IoT-laitteilla.

Kun loit kuvantunnistimen, käytit *Ruoka*-toimialaa, malliversiota, joka on optimoitu ruokakuvien kouluttamiseen. Custom Visionissa voit vaihtaa projektisi toimialaa, käyttäen koulutusdataasi uuden mallin kouluttamiseen uudella toimialalla. Kaikki Custom Visionin tukemat toimialat ovat saatavilla sekä standardina että kompaktina.

### Tehtävä – kouluta mallisi Ruoka (kompakti) -toimialalla
1. Avaa Custom Vision -portaali osoitteessa [CustomVision.ai](https://customvision.ai) ja kirjaudu sisään, jos et ole jo tehnyt niin. Avaa sitten `fruit-quality-detector`-projektisi.

1. Valitse **Asetukset**-painike (⚙-kuvake).

1. Valitse *Toimialueet*-listasta *Ruoka (kompakti)*.

1. Varmista, että *Perusalustat (Tensorflow, CoreML, ONNX, ...)* on valittuna kohdassa *Vientiominaisuudet*.

1. Valitse **Tallenna muutokset** Asetukset-sivun alareunasta.

1. Kouluta malli uudelleen **Kouluta**-painikkeella valitsemalla *Nopea koulutus*.

### Tehtävä - vie mallisi

Kun malli on koulutettu, se täytyy viedä konttina.

1. Valitse **Suorituskyky**-välilehti ja etsi uusin iteraatio, joka on koulutettu kompaktilla toimialueella.

1. Valitse **Vie**-painike ylhäältä.

1. Valitse **DockerFile** ja valitse versio, joka vastaa reunalaitettasi:

    * Jos käytät IoT Edgeä Linux-tietokoneella, Windows-tietokoneella tai virtuaalikoneella, valitse *Linux*-versio.
    * Jos käytät IoT Edgeä Raspberry Pi:llä, valitse *ARM (Raspberry Pi 3)* -versio.

> 🎓 Docker on yksi suosituimmista työkaluista konttien hallintaan, ja DockerFile sisältää ohjeet konttien asennukseen.

1. Valitse **Vie**, jotta Custom Vision luo tarvittavat tiedostot, ja sitten **Lataa**, jotta voit ladata ne zip-tiedostona.

1. Tallenna tiedostot tietokoneellesi ja pura kansio.

## Valmistele kontti käyttöönottoa varten

![Kontit rakennetaan, työnnetään konttirekisteriin ja otetaan käyttöön reunalaitteella IoT Edgen avulla](../../../../../translated_images/fi/container-edge-flow.c246050dd60ceefd.webp)

Kun olet ladannut mallisi, se täytyy rakentaa kontiksi ja työntää konttirekisteriin - verkossa olevaan sijaintiin, jossa voit säilyttää kontteja. IoT Edge voi sitten ladata kontin rekisteristä ja siirtää sen laitteellesi.

![Azure Container Registry -logo](../../../../../translated_images/fi/azure-container-registry-logo.09494206991d4b29.webp)

Tässä oppitunnissa käytettävä konttirekisteri on Azure Container Registry. Tämä ei ole ilmainen palvelu, joten säästääksesi rahaa varmista, että [siivoat projektisi](../../../clean-up.md) kun olet valmis.

> 💁 Voit tarkistaa Azure Container Registry -palvelun kustannukset [Azure Container Registry -hinnoittelusivulta](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Tehtävä - asenna Docker

Jotta voit rakentaa ja ottaa käyttöön luokittelijan, sinun täytyy mahdollisesti asentaa [Docker](https://www.docker.com/).

Tämä on tarpeen vain, jos aiot rakentaa kontin eri laitteella kuin se, johon IoT Edge on asennettu - IoT Edgen asennuksen yhteydessä Docker asennetaan automaattisesti.

1. Jos rakennat Docker-kontin eri laitteella kuin IoT Edge -laitteesi, seuraa Dockerin asennusohjeita [Dockerin asennussivulla](https://www.docker.com/products/docker-desktop) asentaaksesi Docker Desktopin tai Docker-moottorin. Varmista, että se on käynnissä asennuksen jälkeen.

### Tehtävä - luo konttirekisteriresurssi

1. Suorita seuraava komento terminaalista tai komentokehotteesta luodaksesi Azure Container Registry -resurssin:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Korvaa `<Container registry name>` ainutlaatuisella nimellä konttirekisterillesi, käyttäen vain kirjaimia ja numeroita. Perusta nimi `fruitqualitydetector`-malliin. Tämä nimi tulee osaksi URL-osoitetta, jolla konttirekisteriin pääsee, joten sen täytyy olla globaalisti ainutlaatuinen.

1. Kirjaudu Azure Container Registryyn seuraavalla komennolla:

    ```sh
    az acr login --name <Container registry name>
    ```

    Korvaa `<Container registry name>` konttirekisterisi nimellä.

1. Aseta konttirekisteri hallintatilaan, jotta voit luoda salasanan seuraavalla komennolla:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Korvaa `<Container registry name>` konttirekisterisi nimellä.

1. Luo salasanat konttirekisterillesi seuraavalla komennolla:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Korvaa `<Container registry name>` konttirekisterisi nimellä.

    Kopioi `PASSWORD`-arvo, sillä tarvitset sitä myöhemmin.

### Tehtävä - rakenna konttisi

Custom Visionista ladattu tiedosto oli DockerFile, joka sisältää ohjeet kontin rakentamiseen, sekä sovelluskoodin, joka suoritetaan kontin sisällä isännöimään mukautettua visiomalliasi ja REST API:n kutsumista varten. Voit käyttää Dockeria rakentaaksesi ja merkitäksesi kontin DockerFile-tiedostosta ja työntääksesi sen konttirekisteriin.

> 🎓 Konteille annetaan tunniste, joka määrittää niiden nimen ja version. Kun sinun täytyy päivittää kontti, voit rakentaa sen samalla tunnisteella mutta uudella versiolla.

1. Avaa terminaali tai komentokehote ja siirry ladatun mallin purkukansioon.

1. Suorita seuraava komento rakentaaksesi ja merkitäksesi kuvan:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Korvaa `<platform>` alustalla, jolla kontti suoritetaan. Jos käytät IoT Edgeä Raspberry Pi:llä, aseta tämä `linux/armhf`:ksi, muuten aseta tämä `linux/amd64`:ksi.

    > 💁 Jos suoritat tämän komennon laitteelta, jossa IoT Edge toimii, kuten Raspberry Pi:ltä, voit jättää pois `--platform <platform>`-osan, sillä se oletetaan nykyiseksi alustaksi.

    Korvaa `<Container registry name>` konttirekisterisi nimellä.

    > 💁 Jos käytät Linuxia tai Raspberry Pi OS:ää, saatat joutua käyttämään `sudo`-komentoa tämän suorittamiseen.

    Docker rakentaa kuvan ja konfiguroi tarvittavan ohjelmiston. Kuva merkitään nimellä `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Tehtävä - työnnä konttisi konttirekisteriin

1. Käytä seuraavaa komentoa työntääksesi konttisi konttirekisteriin:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Korvaa `<Container registry name>` konttirekisterisi nimellä.

    > 💁 Jos käytät Linuxia, saatat joutua käyttämään `sudo`-komentoa tämän suorittamiseen.

    Kontti työnnetään konttirekisteriin.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Vahvista työntö listaamalla kontit rekisterissä seuraavalla komennolla:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Korvaa `<Container registry name>` konttirekisterisi nimellä.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Näet luokittelijasi listattuna tulosteessa.

## Ota konttisi käyttöön

Konttisi voidaan nyt ottaa käyttöön IoT Edge -laitteellasi. Käyttöönottoa varten sinun täytyy määrittää käyttöönottoilmoitus - JSON-dokumentti, joka listaa moduulit, jotka otetaan käyttöön reunalaitteella.

### Tehtävä - luo käyttöönottoilmoitus

1. Luo uusi tiedosto nimeltä `deployment.json` jonnekin tietokoneellesi.

1. Lisää tiedostoon seuraava:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Löydät tämän tiedoston [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment)-kansiosta.

    Korvaa kolme `<Container registry name>`-esiintymää konttirekisterisi nimellä. Yksi on `ImageClassifier`-moduuliosiossa, kaksi muuta ovat `registryCredentials`-osiossa.

    Korvaa `<Container registry password>` `registryCredentials`-osiossa konttirekisterisi salasanalla.

1. Suorita seuraava komento kansiosta, jossa käyttöönottoilmoitus sijaitsee:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Korvaa `<hub_name>` IoT Hubisi nimellä.

    Kuvan luokittelijamoduuli otetaan käyttöön reunalaitteellasi.

### Tehtävä - varmista, että luokittelija toimii

1. Yhdistä IoT Edge -laitteeseen:

    * Jos käytät Raspberry Pi:tä IoT Edgen suorittamiseen, yhdistä ssh:n avulla joko terminaalista tai etä-SSH-istunnon kautta VS Codessa.
    * Jos suoritat IoT Edgeä Linux-kontissa Windowsissa, seuraa [onnistuneen konfiguraation vahvistusopasta](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) yhdistääksesi IoT Edge -laitteeseen.
    * Jos suoritat IoT Edgeä virtuaalikoneessa, voit SSH-yhteyden avulla yhdistää koneeseen käyttämällä `adminUsername`- ja `password`-tunnuksia, jotka määritit virtuaalikoneen luomisen yhteydessä, ja käyttämällä joko IP-osoitetta tai DNS-nimeä:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Tai:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Syötä salasanasi, kun sitä pyydetään.

1. Kun olet yhdistänyt, suorita seuraava komento saadaksesi IoT Edge -moduulien lista:

    ```sh
    iotedge list
    ```

    > 💁 Saatat joutua suorittamaan tämän komennon `sudo`-komennolla.

    Näet käynnissä olevat moduulit:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Tarkista kuvien luokittelijamoduulin lokit seuraavalla komennolla:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Saatat joutua suorittamaan tämän komennon `sudo`-komennolla.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Tehtävä - testaa kuvien luokittelija

1. Voit käyttää CURL:ia testataksesi kuvien luokittelijaa käyttämällä IoT Edge -agenttia suorittavan tietokoneen IP-osoitetta tai isäntänimeä. Etsi IP-osoite:

    * Jos olet samalla koneella, jossa IoT Edge toimii, voit käyttää `localhost`-isäntänimeä.
    * Jos käytät virtuaalikonetta, voit käyttää joko virtuaalikoneen IP-osoitetta tai DNS-nimeä.
    * Muussa tapauksessa voit hankkia IoT Edgeä suorittavan koneen IP-osoitteen:
      * Windows 10:ssä seuraa [IP-osoitteen löytämisopasta](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * macOS:ssä seuraa [IP-osoitteen löytämisopasta Macilla](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Linuxissa seuraa osaa yksityisen IP-osoitteen löytämisestä [IP-osoitteen löytämisoppaassa Linuxissa](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Voit testata konttia paikallisella tiedostolla suorittamalla seuraavan curl-komennon:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Korvaa `<IP address or name>` IoT Edgeä suorittavan tietokoneen IP-osoitteella tai isäntänimellä. Korvaa `<file_Name>` testattavan tiedoston nimellä.

    Näet ennustetulokset tulosteessa:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Täällä ei tarvitse antaa ennusteavainta, koska tämä ei käytä Azure-resurssia. Sen sijaan turvallisuus konfiguroidaan sisäverkossa sisäisten turvallisuustarpeiden perusteella, eikä julkisen päätepisteen ja API-avaimen avulla.

## Käytä IoT Edge -laitettasi

Nyt kun kuvien luokittelija on otettu käyttöön IoT Edge -laitteella, voit käyttää sitä IoT-laitteestasi.

### Tehtävä - käytä IoT Edge -laitettasi

Käy läpi asiaankuuluva opas kuvien luokittelemiseksi IoT Edge -luokittelijan avulla:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Yksikorttitietokone - Raspberry Pi/virtuaalinen IoT-laite](single-board-computer.md)

### Mallin uudelleenkoulutus

Yksi haittapuoli kuvien luokittelijoiden suorittamisessa IoT Edgessä on, että ne eivät ole yhteydessä Custom Vision -projektiisi. Jos tarkastelet **Ennusteet**-välilehteä Custom Visionissa, et näe kuvia, jotka on luokiteltu Edge-pohjaisella luokittelijalla.

Tämä on odotettu toiminta - kuvia ei lähetetä pilveen luokittelua varten, joten ne eivät ole saatavilla pilvessä. Yksi IoT Edgen käytön eduista on yksityisyys, joka varmistaa, että kuvat eivät poistu verkostasi, toinen on offline-työskentely, jolloin ei tarvitse luottaa kuvien lataamiseen, kun laitteella ei ole internetyhteyttä. Haittapuoli on mallin parantaminen - sinun täytyisi toteuttaa toinen tapa tallentaa kuvia, jotka voidaan manuaalisesti luokitella uudelleen mallin parantamiseksi ja uudelleenkouluttamiseksi.

✅ Mieti tapoja ladata kuvia luokittelijan uudelleenkouluttamista varten.

---

## 🚀 Haaste

AI-mallien suorittaminen reunalaitteilla voi olla nopeampaa kuin pilvessä - verkkoyhteys on lyhyempi. Se voi myös olla hitaampaa, koska mallia suorittava laitteisto ei välttämättä ole yhtä tehokas kuin pilvi.

Tee ajoituksia ja vertaa, onko kutsu reunalaitteellesi nopeampi vai hitaampi kuin kutsu pilveen? Mieti syitä, jotka selittävät eron tai sen puuttumisen. Tutki tapoja suorittaa AI-malleja nopeammin reunalla käyttämällä erikoistunutta laitteistoa.

## Luentojälkeinen kysely

[Luentojälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Kertaus ja itseopiskelu

* Lue lisää konteista [OS-tason virtualisoinnin Wikipedia-sivulta](https://wikipedia.org/wiki/OS-level_virtualization).
* Lue lisää reunalaskennasta, erityisesti siitä, miten 5G voi auttaa laajentamaan reunalaskentaa [NetworkWorldin artikkelissa "Mitä reunalaskenta on ja miksi sillä on merkitystä?"](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Opi lisää tekoälypalvelujen käytöstä IoT Edgessä katsomalla [Microsoft Channel9:n Learn Live -jakso "Opi käyttämään Azure IoT Edgeä valmiiksi rakennetulla tekoälypalvelulla reunalla kielen tunnistamiseen"](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Tehtävä

[Suorita muita palveluja reunalla](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.