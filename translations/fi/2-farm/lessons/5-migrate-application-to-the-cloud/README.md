# Siirrä sovelluslogiikkasi pilveen

![Tämän oppitunnin luonnoskuva](../../../../../translated_images/fi/lesson-9.dfe99c8e891f48e1.webp)

> Luonnoskuva: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä oppitunti oli osa [IoT for Beginners Project 2 - Digital Agriculture -sarjaa](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx), joka on tuotettu [Microsoft Reactorin](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) toimesta.

[![Ohjaa IoT-laitettasi serverittömällä koodilla](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Johdanto

Edellisessä oppitunnissa opit yhdistämään kasvien maaperän kosteuden seurannan ja releen ohjauksen pilvipohjaiseen IoT-palveluun. Seuraava askel on siirtää releen ajoitusta ohjaava palvelinkoodi pilveen. Tässä oppitunnissa opit tekemään tämän serverittömien funktioiden avulla.

Tässä oppitunnissa käsitellään:

* [Mitä serveritön tarkoittaa?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Luo serveritön sovellus](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Luo IoT Hub -tapahtumakäynnistin](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Lähetä suoria metodipyyntöjä serverittömästä koodista](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Ota serveritön koodi käyttöön pilvessä](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Mitä serveritön tarkoittaa?

Serveritön, tai serveritön laskenta, tarkoittaa pienten koodilohkojen luomista, jotka suoritetaan pilvessä vastauksena erilaisiin tapahtumiin. Kun tapahtuma tapahtuu, koodisi suoritetaan ja sille välitetään tietoja tapahtumasta. Näitä tapahtumia voi tulla monista eri lähteistä, kuten verkkopyynnöistä, jonoon lisätyistä viesteistä, tietokannan muutoksista tai IoT-laitteiden lähettämistä viesteistä IoT-palveluun.

![Tapahtumia lähetetään IoT-palvelusta serverittömään palveluun, ja niitä käsitellään samanaikaisesti useilla funktioilla](../../../../../translated_images/fi/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Jos olet käyttänyt tietokantatriggereitä aiemmin, voit ajatella tätä samalla tavalla: koodi käynnistyy tapahtumasta, kuten rivin lisäämisestä.

![Kun useita tapahtumia lähetetään samanaikaisesti, serveritön palvelu skaalautuu suorittamaan ne kaikki yhtä aikaa](../../../../../translated_images/fi/serverless-scaling.f8c769adf0413fd1.webp)

Koodisi suoritetaan vain, kun tapahtuma tapahtuu, eikä sitä pidetä aktiivisena muina aikoina. Tapahtuma tapahtuu, koodisi ladataan ja suoritetaan. Tämä tekee serverittömästä mallista erittäin skaalautuvan – jos useita tapahtumia tapahtuu samanaikaisesti, pilvipalveluntarjoaja voi suorittaa funktiosi niin monta kertaa kuin tarvitaan samanaikaisesti käytettävissä olevilla palvelimilla. Haittapuolena on, että jos sinun täytyy jakaa tietoa tapahtumien välillä, sinun täytyy tallentaa se esimerkiksi tietokantaan sen sijaan, että säilyttäisit sen muistissa.

Koodisi kirjoitetaan funktiona, joka ottaa tapahtuman tiedot parametrina. Näitä serverittömiä funktioita voi kirjoittaa monilla eri ohjelmointikielillä.

> 🎓 Serveritöntä kutsutaan myös nimellä Functions as a Service (FaaS), koska jokainen tapahtumakäynnistin toteutetaan koodissa funktiona.

Nimestään huolimatta serveritön käyttää palvelimia. Nimi viittaa siihen, että kehittäjänä sinun ei tarvitse huolehtia palvelimista, jotka suorittavat koodisi – sinun tarvitsee vain tietää, että koodisi suoritetaan tapahtuman tapahtuessa. Pilvipalveluntarjoajalla on serveritön *ajoympäristö*, joka hallitsee palvelimien, verkon, tallennustilan, suorittimen, muistin ja muiden resurssien allokointia koodisi suorittamiseksi. Tämän mallin vuoksi et maksa palvelimista, vaan koodisi suoritusajasta ja käytetystä muistista.

> 💰 Serveritön on yksi edullisimmista tavoista suorittaa koodia pilvessä. Esimerkiksi tätä kirjoitettaessa eräs pilvipalveluntarjoaja sallii kaikkien serverittömien funktioidesi suorittaa yhteensä 1 000 000 kertaa kuukaudessa ennen kuin sinulta veloitetaan mitään, ja sen jälkeen veloitus on 0,20 USD per 1 000 000 suoritusta. Kun koodisi ei ole käynnissä, et maksa mitään.

IoT-kehittäjänä serveritön malli on ihanteellinen. Voit kirjoittaa funktion, joka kutsutaan vastauksena viesteihin, jotka lähetetään mistä tahansa pilvipalveluun yhdistetystä IoT-laitteesta. Koodisi käsittelee kaikki lähetetyt viestit, mutta on käynnissä vain tarvittaessa.

✅ Katso takaisin koodia, jonka kirjoitit palvelinkoodiksi kuuntelemaan viestejä MQTT:n kautta. Miten tämä voisi toimia pilvessä serverittömänä? Miten koodia pitäisi muuttaa tukemaan serveritöntä laskentaa?

> 💁 Serveritön malli laajenee myös muihin pilvipalveluihin koodin suorittamisen lisäksi. Esimerkiksi serverittömiä tietokantoja on saatavilla pilvessä serverittömällä hinnoittelumallilla, jossa maksat per pyyntö, kuten kysely tai lisäys. Hinnoittelu perustuu yleensä siihen, kuinka paljon työtä pyynnön käsittely vaatii. Esimerkiksi yhden rivin valinta pääavaimen perusteella maksaa vähemmän kuin monimutkainen operaatio, joka yhdistää useita tauluja ja palauttaa tuhansia rivejä.

## Luo serveritön sovellus

Microsoftin serveritön laskentapalvelu tunnetaan nimellä Azure Functions.

![Azure Functions -logo](../../../../../translated_images/fi/azure-functions-logo.1cfc8e3204c9c44a.webp)

Alla oleva lyhyt video tarjoaa yleiskatsauksen Azure Functionsista.

[![Azure Functions -yleiskatsausvideo](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon.

✅ Käytä hetki aikaa tutkiaksesi ja lue Azure Functionsin yleiskatsaus [Microsoft Azure Functions -dokumentaatiosta](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Azure Functions -sovellusten kirjoittaminen alkaa valitsemallasi ohjelmointikielellä. Azure Functions tukee oletuksena Pythonia, JavaScriptiä, TypeScriptiä, C#:tä, F#:tä, Javaa ja Powershelliä. Tässä oppitunnissa opit kirjoittamaan Azure Functions -sovelluksen Pythonilla.

> 💁 Azure Functions tukee myös mukautettuja käsittelijöitä, joten voit kirjoittaa funktioita millä tahansa kielellä, joka tukee HTTP-pyyntöjä, mukaan lukien vanhemmat kielet, kuten COBOL.

Functions-sovellukset koostuvat yhdestä tai useammasta *käynnistimestä* – funktioista, jotka reagoivat tapahtumiin. Yhdessä Functions-sovelluksessa voi olla useita käynnistimiä, jotka jakavat yhteiset asetukset. Esimerkiksi Functions-sovelluksen asetustiedostossa voi olla IoT Hubin yhteystiedot, ja kaikki sovelluksen funktiot voivat käyttää näitä tietoja yhdistääkseen ja kuunnellakseen tapahtumia.

### Tehtävä – asenna Azure Functions -työkalut

> Tämän kirjoitushetkellä Azure Functions -koodityökalut eivät toimi täysin Apple Silicon -laitteilla Python-projekteissa. Tarvitset Intel-pohjaisen Macin, Windows-tietokoneen tai Linux-tietokoneen.

Yksi Azure Functionsin hienoista ominaisuuksista on, että voit suorittaa niitä paikallisesti. Sama ajoympäristö, jota käytetään pilvessä, voidaan suorittaa tietokoneellasi, jolloin voit kirjoittaa koodia, joka reagoi IoT-viesteihin, ja suorittaa sen paikallisesti. Voit jopa debugata koodiasi tapahtumien käsittelyn aikana. Kun olet tyytyväinen koodiisi, voit ottaa sen käyttöön pilvessä.

Azure Functions -työkalut ovat saatavilla CLI:nä, joka tunnetaan nimellä Azure Functions Core Tools.

1. Asenna Azure Functions Core Tools noudattamalla ohjeita [Azure Functions Core Tools -dokumentaatiosta](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Asenna Azure Functions -laajennus VS Codeen. Tämä laajennus tarjoaa tuen Azure Functions -sovellusten luomiseen, debuggaamiseen ja käyttöönottoon. Katso ohjeet [Azure Functions -laajennuksen dokumentaatiosta](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions).

Kun otat Azure Functions -sovelluksen käyttöön pilvessä, se tarvitsee pienen määrän pilvitallennustilaa sovellustiedostojen ja lokitiedostojen tallentamiseen. Kun suoritat Functions-sovellusta paikallisesti, sinun täytyy silti yhdistää pilvitallennukseen, mutta sen sijaan, että käyttäisit oikeaa pilvitallennusta, voit käyttää tallennusemulaattoria nimeltä [Azurite](https://github.com/Azure/Azurite). Tämä toimii paikallisesti mutta käyttäytyy kuin pilvitallennus.

> 🎓 Azuren tallennustila, jota Azure Functions käyttää, on Azure Storage Account. Näihin tileihin voi tallentaa tiedostoja, objekteja, tietoja tauluihin tai tietoja jonoihin. Yksi tallennustili voidaan jakaa useiden sovellusten, kuten Functions-sovelluksen ja verkkosovelluksen, kesken.

1. Azurite on Node.js-sovellus, joten sinun täytyy asentaa Node.js. Löydät lataus- ja asennusohjeet [Node.js-verkkosivustolta](https://nodejs.org/). Jos käytät Macia, voit asentaa sen myös [Homebrew'n](https://formulae.brew.sh/formula/node) kautta.

1. Asenna Azurite seuraavalla komennolla (`npm` on työkalu, joka asennetaan Node.js:n mukana):

    ```sh
    npm install -g azurite
    ```

1. Luo kansio nimeltä `azurite`, jota Azurite käyttää tietojen tallentamiseen:

    ```sh
    mkdir azurite
    ```

1. Suorita Azurite ja anna sille tämä uusi kansio:

    ```sh
    azurite --location azurite
    ```

    Azurite-tallennusemulaattori käynnistyy ja on valmis paikallisen Functions-ajoympäristön yhdistettäväksi.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Tehtävä – luo Azure Functions -projekti

Azure Functions CLI:llä voidaan luoda uusi Functions-sovellus.

1. Luo kansio Functions-sovelluksellesi ja siirry siihen. Nimeä se `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Luo Python-virtuaaliympäristö tämän kansion sisälle:

    ```sh
    python3 -m venv .venv
    ```

1. Aktivoi virtuaaliympäristö:

    * Windowsissa:
        * Jos käytät komentokehotetta tai Windows Terminalin komentokehotetta, suorita:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jos käytät PowerShelliä, suorita:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS:ssä tai Linuxissa suorita:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Nämä komennot tulisi suorittaa samasta sijainnista, jossa loit virtuaaliympäristön. Sinun ei koskaan tarvitse siirtyä `.venv`-kansioon, vaan sinun tulisi aina suorittaa aktivointikomento ja kaikki paketinasennus- tai koodinajokomennot kansiosta, jossa olit virtuaaliympäristöä luodessasi.

1. Suorita seuraava komento luodaksesi Functions-sovellus tähän kansioon:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Tämä luo kolme tiedostoa nykyisen kansion sisälle:

    * `host.json` – tämä JSON-dokumentti sisältää asetukset Functions-sovelluksellesi. Näitä asetuksia ei tarvitse muokata.
    * `local.settings.json` – tämä JSON-dokumentti sisältää asetukset, joita sovelluksesi käyttää paikallisesti suoritettaessa, kuten IoT Hubin yhteysmerkkijonot. Nämä asetukset ovat vain paikallisia, eikä niitä tulisi lisätä versionhallintaan. Kun otat sovelluksen käyttöön pilvessä, näitä asetuksia ei oteta käyttöön, vaan asetukset ladataan sovellusasetuksista. Tämä käsitellään myöhemmin tässä oppitunnissa.
    * `requirements.txt` – tämä on [Pip-vaatimustiedosto](https://pip.pypa.io/en/stable/user_guide/#requirements-files), joka sisältää Functions-sovelluksen suorittamiseen tarvittavat Pip-paketit.

1. `local.settings.json` -tiedostossa on asetus tallennustilille, jota Functions-sovellus käyttää. Tämä on oletuksena tyhjä, joten se täytyy asettaa. Yhdistääksesi Azurite-paikalliseen tallennusemulaattoriin, aseta tämä arvo seuraavasti:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Asenna tarvittavat Pip-paketit käyttämällä vaatimustiedostoa:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Tarvittavat Pip-paketit täytyy olla tässä tiedostossa, jotta kun Functions-sovellus otetaan käyttöön pilvessä, ajoympäristö voi varmistaa oikeiden pakettien asennuksen.

1. Testataksesi, että kaikki toimii oikein, voit käynnistää Functions-ajoympäristön. Suorita seuraava komento tehdäksesi tämän:

    ```sh
    func start
    ```

    Näet, että ajoympäristö käynnistyy ja raportoi, ettei se löytänyt mitään tehtäväfunktioita (käynnistimiä).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Jos saat palomuurin ilmoituksen, anna lupa, sillä `func`-sovelluksen täytyy pystyä lukemaan ja kirjoittamaan verkkoosi.
> ⚠️ Jos käytät macOS:ia, tulosteessa saattaa näkyä varoituksia:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Voit ohittaa nämä, kunhan Functions-sovellus käynnistyy oikein ja listaa käynnissä olevat funktiot. Kuten [tässä Microsoft Docs Q&A -kysymyksessä](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) mainitaan, nämä varoitukset voi jättää huomiotta.

1. Lopeta Functions-sovellus painamalla `ctrl+c`.

1. Avaa nykyinen kansio VS Code:ssa joko avaamalla VS Code ja sitten tämä kansio, tai suorittamalla seuraava komento:

    ```sh
    code .
    ```

    VS Code tunnistaa Functions-projektisi ja näyttää ilmoituksen:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Ilmoitus](../../../../../translated_images/fi/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Valitse **Yes** tästä ilmoituksesta.

1. Varmista, että Python-virtuaaliympäristö on käynnissä VS Code -terminaalissa. Lopeta ja käynnistä se uudelleen tarvittaessa.

## Luo IoT Hub -tapahtumatriggeri

Functions-sovellus toimii palvelimettoman koodisi alustana. Vastataksesi IoT Hub -tapahtumiin voit lisätä IoT Hub -triggerin tähän sovellukseen. Tämä triggeri tarvitsee yhteyden viestivirtaan, joka lähetetään IoT Hubiin, ja sen tulee reagoida näihin viesteihin. Viestivirran saamiseksi triggerin täytyy yhdistää IoT Hubin *Event Hub -yhteensopivaan päätepisteeseen*.

IoT Hub perustuu toiseen Azure-palveluun nimeltä Azure Event Hubs. Event Hubs on palvelu, joka mahdollistaa viestien lähettämisen ja vastaanottamisen, ja IoT Hub laajentaa tätä lisäämällä ominaisuuksia IoT-laitteille. Viestien lukeminen IoT Hubista tapahtuu samalla tavalla kuin Event Hubsia käytettäessä.

✅ Tee tutkimusta: Lue Event Hubsin yleiskatsaus [Azure Event Hubs -dokumentaatiosta](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Miten perusominaisuudet vertautuvat IoT Hubiin?

IoT-laitteen täytyy käyttää salaisuutta sisältävää avainta yhdistääkseen IoT Hubiin, mikä varmistaa, että vain sallitut laitteet voivat yhdistää. Sama pätee viestien lukemiseen: koodisi tarvitsee yhteysmerkkijonon, joka sisältää salaisen avaimen sekä IoT Hubin tiedot.

> 💁 Oletusyhteysmerkkijonolla on **iothubowner**-oikeudet, mikä antaa täydet oikeudet IoT Hubiin kaikelle koodille, joka käyttää sitä. Ihanteellisesti sinun tulisi yhdistää vain tarvittavilla vähimmäisoikeuksilla. Tämä käsitellään seuraavassa oppitunnissa.

Kun triggeri on yhdistetty, funktion sisällä oleva koodi kutsutaan jokaiselle IoT Hubiin lähetetylle viestille riippumatta siitä, mikä laite sen lähetti. Triggeri välittää viestin parametrina.

### Tehtävä - hanki Event Hub -yhteensopivan päätepisteen yhteysmerkkijono

1. Suorita VS Code -terminaalissa seuraava komento saadaksesi IoT Hubin Event Hub -yhteensopivan päätepisteen yhteysmerkkijonon:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Korvaa `<hub_name>` IoT Hubille antamallasi nimellä.

1. Avaa VS Code:ssa `local.settings.json` -tiedosto. Lisää seuraava arvo `Values`-osioon:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Korvaa `<connection string>` edellisen vaiheen arvolla. Lisää pilkku edellisen rivin jälkeen, jotta JSON on kelvollinen.

### Tehtävä - luo tapahtumatriggeri

Nyt voit luoda tapahtumatriggerin.

1. Suorita VS Code -terminaalissa seuraava komento `soil-moisture-trigger`-kansion sisällä:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Tämä luo uuden funktion nimeltä `iot-hub-trigger`. Triggeri yhdistää IoT Hubin Event Hub -yhteensopivaan päätepisteeseen, joten voit käyttää Event Hub -triggeriä. Erillistä IoT Hub -triggeriä ei ole.

Tämä luo kansion `soil-moisture-trigger`-kansion sisälle nimeltä `iot-hub-trigger`, joka sisältää tämän funktion. Tämä kansio sisältää seuraavat tiedostot:

* `__init__.py` - Python-kooditiedosto, joka sisältää triggerin. Tiedoston nimi noudattaa Python-moduulin nimeämiskäytäntöä.

    Tämä tiedosto sisältää seuraavan koodin:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Triggerin ydin on `main`-funktio. Tämä funktio kutsutaan IoT Hubin tapahtumien kanssa. Funktiolla on parametri nimeltä `event`, joka sisältää `EventHubEvent`-objektin. Joka kerta kun viesti lähetetään IoT Hubiin, tämä funktio kutsutaan ja viesti välitetään `event`-parametrina, yhdessä ominaisuuksien kanssa, jotka ovat samoja kuin edellisessä oppitunnissa nähtyjen annotaatioiden kanssa.

    Funktion ydin kirjaa tapahtuman.

* `function.json` - sisältää triggerin konfiguraation. Pääkonfiguraatio on osiossa nimeltä `bindings`. Binding tarkoittaa yhteyttä Azure Functionsin ja muiden Azure-palveluiden välillä. Tämä funktio sisältää syöttöbindingin Event Hubiin - se yhdistää Event Hubiin ja vastaanottaa dataa.

    > 💁 Voit myös lisätä ulostulobindingeja, jolloin funktion ulostulo lähetetään toiseen palveluun. Esimerkiksi voit lisätä ulostulobindingin tietokantaan ja palauttaa IoT Hubin tapahtuman funktiosta, jolloin se lisätään automaattisesti tietokantaan.

    ✅ Tee tutkimusta: Lue bindingeista [Azure Functions triggers and bindings concepts -dokumentaatiosta](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    `bindings`-osio sisältää bindingin konfiguraation. Kiinnostavat arvot ovat:

  * `"type": "eventHubTrigger"` - kertoo funktiolle, että sen tulee kuunnella tapahtumia Event Hubista
  * `"name": "events"` - Event Hub -tapahtumien parametrin nimi. Tämä vastaa Python-koodin `main`-funktion parametrin nimeä.
  * `"direction": "in"` - syöttöbinding, data Event Hubista tulee funktioon
  * `"connection": ""` - määrittää asetuksen nimen, josta yhteysmerkkijono luetaan. Paikallisesti ajettaessa tämä lukee asetuksen `local.settings.json`-tiedostosta.

    > 💁 Yhteysmerkkijonoa ei voi tallentaa `function.json`-tiedostoon, vaan se täytyy lukea asetuksista. Tämä estää yhteysmerkkijonon paljastamisen vahingossa.

1. Päivitä `function.json`-tiedoston `cardinality`-kentän arvo `many` -> `one` [Azure Functions -mallin bugin](https://github.com/Azure/azure-functions-templates/issues/1250) vuoksi:

    ```json
    "cardinality": "one",
    ```

1. Päivitä `"connection"`-arvo `function.json`-tiedostossa osoittamaan uuteen arvoon, jonka lisäsit `local.settings.json`-tiedostoon:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Muista - tämän täytyy osoittaa asetukseen, ei sisältää varsinaista yhteysmerkkijonoa.

1. Yhteysmerkkijono sisältää `eventHubName`-arvon, joten tämän arvon `function.json`-tiedostossa täytyy olla tyhjä. Päivitä tämä arvo tyhjäksi:

    ```json
    "eventHubName": "",
    ```

### Tehtävä - aja tapahtumatriggeri

1. Varmista, että IoT Hub -tapahtumamonitori ei ole käynnissä. Jos tämä on käynnissä samaan aikaan kuin Functions-sovellus, Functions-sovellus ei voi yhdistää ja kuluttaa tapahtumia.

    > 💁 Useat sovellukset voivat yhdistää IoT Hubin päätepisteisiin eri *kuluttajaryhmien* avulla. Nämä käsitellään myöhemmässä oppitunnissa.

1. Aja Functions-sovellus suorittamalla seuraava komento VS Code -terminaalissa:

    ```sh
    func start
    ```

    Functions-sovellus käynnistyy ja löytää `iot-hub-trigger`-funktion. Se käsittelee kaikki tapahtumat, jotka on jo lähetetty IoT Hubiin viimeisen päivän aikana.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Jokainen funktion kutsu ympäröidään `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'`-lohkoilla tulosteessa, joten näet kuinka monta viestiä käsiteltiin kussakin funktion kutsussa.

1. Varmista, että IoT-laitteesi on käynnissä. Näet uusia maaperän kosteutta koskevia viestejä ilmestyvän Functions-sovellukseen.

1. Lopeta ja käynnistä Functions-sovellus uudelleen. Näet, että se ei käsittele aiempia viestejä uudelleen, vaan käsittelee vain uusia viestejä.

> 💁 VS Code tukee myös Functions-sovellusten debuggausta. Voit asettaa breakpointin klikkaamalla koodirivin alussa olevaa reunaa, siirtämällä kursorin riville ja valitsemalla *Run -> Toggle breakpoint*, tai painamalla `F9`. Voit käynnistää debuggerin valitsemalla *Run -> Start debugging*, painamalla `F5`, tai valitsemalla *Run and debug* -paneelin ja klikkaamalla **Start debugging**-painiketta. Näin voit tarkastella käsiteltävien tapahtumien yksityiskohtia.

#### Vianetsintä

* Jos saat seuraavan virheen:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Tarkista, että Azurite on käynnissä ja että olet asettanut `AzureWebJobsStorage`-arvon `local.settings.json`-tiedostossa `UseDevelopmentStorage=true`.

* Jos saat seuraavan virheen:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Tarkista, että olet asettanut `cardinality`-arvon `function.json`-tiedostossa `one`.

* Jos saat seuraavan virheen:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Tarkista, että olet asettanut `eventHubName`-arvon `function.json`-tiedostossa tyhjäksi.

## Lähetä suoria metodipyyntöjä palvelimettomasta koodista

Tähän mennessä Functions-sovelluksesi on kuunnellut viestejä IoT Hubista Event Hub -yhteensopivan päätepisteen kautta. Nyt sinun täytyy lähettää komentoja IoT-laitteelle. Tämä tehdään käyttämällä eri yhteyttä IoT Hubiin *Registry Managerin* kautta. Registry Manager on työkalu, joka mahdollistaa IoT Hubiin rekisteröityjen laitteiden tarkastelun ja niiden kanssa kommunikoinnin lähettämällä pilvestä laitteelle viestejä, suoria metodipyyntöjä tai päivittämällä laitteen twinin. Voit myös käyttää sitä IoT-laitteiden rekisteröintiin, päivittämiseen tai poistamiseen IoT Hubista.

Yhdistääksesi Registry Manageriin tarvitset yhteysmerkkijonon.

### Tehtävä - hanki Registry Manager -yhteysmerkkijono

1. Hankkiaksesi yhteysmerkkijonon, suorita seuraava komento:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Korvaa `<hub_name>` IoT Hubille antamallasi nimellä.

    Yhteysmerkkijono pyydetään *ServiceConnect*-käytännölle käyttämällä `--policy-name service`-parametria. Kun pyydät yhteysmerkkijonoa, voit määrittää, mitä oikeuksia yhteysmerkkijono sallii. ServiceConnect-käytäntö sallii koodisi yhdistää ja lähettää viestejä IoT-laitteille.

    ✅ Tee tutkimusta: Lue eri käytännöistä [IoT Hub -oikeuksien dokumentaatiosta](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Avaa VS Code:ssa `local.settings.json` -tiedosto. Lisää seuraava arvo `Values`-osioon:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Korvaa `<connection string>` edellisen vaiheen arvolla. Lisää pilkku edellisen rivin jälkeen, jotta JSON on kelvollinen.

### Tehtävä - lähetä suora metodipyyntö laitteelle

1. Registry Managerin SDK on saatavilla Pip-paketin kautta. Lisää seuraava rivi `requirements.txt`-tiedostoon lisätäksesi riippuvuuden tähän pakettiin:

    ```sh
    azure-iot-hub
    ```

1. Varmista, että VS Code -terminaaliin on aktivoitu virtuaaliympäristö, ja suorita seuraava komento asentaaksesi Pip-paketit:

    ```sh
    pip install -r requirements.txt
    ```

1. Lisää seuraavat tuonnit `__init__.py`-tiedostoon:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Tämä tuo joitakin järjestelmäkirjastoja sekä kirjastot Registry Managerin kanssa kommunikointiin ja suorien metodipyyntöjen lähettämiseen.

1. Poista koodi `main`-metodin sisältä, mutta säilytä itse metodi.

1. Lisää `main`-metodiin seuraava koodi:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Tämä koodi poimii tapahtuman rungon, joka sisältää IoT-laitteen lähettämän JSON-viestin.

    Se hakee laitteen tunnuksen viestin mukana lähetetyistä annotaatioista. Tapahtuman runko sisältää telemetriana lähetetyn viestin, ja `iothub_metadata`-sanakirja sisältää IoT Hubin asettamat ominaisuudet, kuten lähettäjän laitteen tunnuksen ja ajan, jolloin viesti lähetettiin.

    Tämä tieto kirjataan. Näet tämän kirjauksen terminaalissa, kun ajat Functions-sovelluksen paikallisesti.

1. Lisää tämän alle seuraava koodi:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Tämä koodi hakee maaperän kosteuden viestistä. Se tarkistaa kosteuden ja luo sen perusteella apuluokan suoralle metodipyynnölle joko `relay_on`- tai `relay_off`-metodille. Metodipyyntö ei tarvitse sisältöä, joten tyhjä JSON-dokumentti lähetetään.

1. Lisää tämän alle seuraava koodi:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Tämä koodi lataa `REGISTRY_MANAGER_CONNECTION_STRING`-arvon tiedostosta `local.settings.json`. Tämän tiedoston arvot ovat käytettävissä ympäristömuuttujina, ja niitä voidaan lukea `os.environ`-funktiolla, joka palauttaa sanakirjan kaikista ympäristömuuttujista.

> 💁 Kun tämä koodi otetaan käyttöön pilvessä, `local.settings.json`-tiedoston arvot asetetaan *Sovellusasetuksiksi* (Application Settings), ja niitä voidaan lukea ympäristömuuttujista.

Koodi luo sitten instanssin Registry Manager -apuohjelmaluokasta käyttäen yhteysmerkkijonoa.

1. Lisää tämän alle seuraava koodi:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Tämä koodi käskee rekisterinhallintaa lähettämään suoran metodipyynnön laitteelle, joka lähetti telemetriatiedot.

    > 💁 Aiemmissa oppitunneissa luomissasi sovellusversioissa, jotka käyttivät MQTT:tä, releen ohjauskomennot lähetettiin kaikille laitteille. Koodi oletti, että käytössä olisi vain yksi laite. Tämä koodiversio lähettää metodipyynnön yhdelle laitteelle, joten se toimii, vaikka sinulla olisi useita kosteusantureiden ja releiden kokoonpanoja, lähettäen oikean metodipyynnön oikealle laitteelle.

1. Käynnistä Functions-sovellus ja varmista, että IoT-laitteesi lähettää dataa. Näet viestien käsittelyn ja suorien metodipyyntöjen lähettämisen. Siirrä maaperän kosteusanturia maahan ja pois maasta nähdäksesi arvojen muuttuvan ja releen kytkeytyvän päälle ja pois.

> 💁 Löydät tämän koodin [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) -kansiosta.

## Ota palvelimeton koodi käyttöön pilvessä

Koodisi toimii nyt paikallisesti, joten seuraava askel on ottaa Functions-sovellus käyttöön pilvessä.

### Tehtävä - luo pilviresurssit

Functions-sovelluksesi täytyy ottaa käyttöön Azureen Functions App -resurssina, joka sijaitsee IoT Hubille luomassasi resurssiryhmässä. Tarvitset myös Azureen luodun tallennustilin korvaamaan paikallisesti käytössä olevan emulaattorin.

1. Suorita seuraava komento luodaksesi tallennustili:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Korvaa `<storage_name>` tallennustilisi nimellä. Nimen täytyy olla globaalisti uniikki, koska se muodostaa osan URL-osoitteesta, jota käytetään tallennustilin käyttämiseen. Voit käyttää vain pieniä kirjaimia ja numeroita, ei muita merkkejä, ja nimi on rajoitettu 24 merkkiin. Käytä esimerkiksi `sms` ja lisää loppuun uniikki tunniste, kuten satunnaisia sanoja tai nimesi.

    `--sku Standard_LRS` valitsee hinnoittelutason, valiten edullisimman yleiskäyttöisen tilin. Tallennustilille ei ole ilmaista tasoa, ja maksat käytön mukaan. Kustannukset ovat suhteellisen alhaiset, kalleimman tallennustilan ollessa alle 0,05 USD kuukaudessa per gigatavu.

    ✅ Lue lisää hinnoittelusta [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn) -sivulta.

1. Suorita seuraava komento luodaksesi Functions App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Korvaa `<location>` sijainnilla, jota käytit luodessasi resurssiryhmän edellisessä oppitunnissa.

    Korvaa `<storage_name>` tallennustilisi nimellä, jonka loit edellisessä vaiheessa.

    Korvaa `<functions_app_name>` uniikilla nimellä Functions-sovelluksellesi. Nimen täytyy olla globaalisti uniikki, koska se muodostaa osan URL-osoitteesta, jota voidaan käyttää Functions-sovelluksen käyttämiseen. Käytä esimerkiksi `soil-moisture-sensor-` ja lisää loppuun uniikki tunniste, kuten satunnaisia sanoja tai nimesi.

    `--functions-version 3` -vaihtoehto asettaa käytettävän Azure Functions -version. Versio 3 on uusin versio.

    `--os-type Linux` kertoo Functions-ajoympäristölle, että näitä funktioita isännöidään Linuxissa. Funktioita voidaan isännöidä Linuxissa tai Windowsissa käytetystä ohjelmointikielestä riippuen. Python-sovellukset tukevat vain Linuxia.

### Tehtävä - lataa sovellusasetuksesi

Kun kehitit Functions-sovellustasi, tallensit joitakin asetuksia `local.settings.json`-tiedostoon IoT Hubin yhteysmerkkijonoja varten. Nämä täytyy kirjoittaa Azure Functions Appin sovellusasetuksiin, jotta koodisi voi käyttää niitä.

> 🎓 `local.settings.json`-tiedosto on tarkoitettu vain paikalliseen kehitykseen, eikä sitä pitäisi tallentaa versionhallintaan, kuten GitHubiin. Pilveen otettaessa käyttöön käytetään sovellusasetuksia. Sovellusasetukset ovat pilvessä isännöityjä avain/arvo-pareja, joita luetaan ympäristömuuttujista joko koodissasi tai ajonaikaisesti, kun koodisi yhdistetään IoT Hubiin.

1. Suorita seuraava komento asettaaksesi `IOT_HUB_CONNECTION_STRING`-asetuksen Functions-sovelluksen sovellusasetuksiin:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Korvaa `<functions_app_name>` Functions-sovelluksesi nimellä.

    Korvaa `<connection string>` `local.settings.json`-tiedostosi `IOT_HUB_CONNECTION_STRING`-arvolla.

1. Toista edellinen vaihe, mutta aseta `REGISTRY_MANAGER_CONNECTION_STRING` vastaavalla arvolla `local.settings.json`-tiedostostasi.

Kun suoritat nämä komennot, ne tulostavat myös listan kaikista sovellusasetuksista Functions-sovellukselle. Voit käyttää tätä tarkistaaksesi, että arvosi on asetettu oikein.

> 💁 Näet arvon, joka on jo asetettu `AzureWebJobsStorage`-asetukselle. `local.settings.json`-tiedostossasi tämä oli asetettu käyttämään paikallista tallennusemulaattoria. Kun loit Functions-sovelluksen, annoit tallennustilin parametrina, ja tämä asetus määritettiin automaattisesti.

### Tehtävä - ota Functions-sovellus käyttöön pilvessä

Nyt kun Functions-sovellus on valmis, koodisi voidaan ottaa käyttöön.

1. Suorita seuraava komento VS Code -terminaalista julkaistaksesi Functions-sovelluksesi:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Korvaa `<functions_app_name>` Functions-sovelluksesi nimellä.

Koodi pakataan ja lähetetään Functions-sovellukseen, jossa se otetaan käyttöön ja käynnistetään. Konsoliin tulostuu paljon tietoa, ja lopuksi saat vahvistuksen käyttöönotosta sekä listan käyttöön otetuista funktioista. Tässä tapauksessa lista sisältää vain liipaisimen.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Varmista, että IoT-laitteesi on käynnissä. Muuta kosteustasoja säätämällä maaperän kosteutta tai siirtämällä anturia maahan ja pois maasta. Näet releen kytkeytyvän päälle ja pois maaperän kosteuden muuttuessa.

---

## 🚀 Haaste

Edellisessä oppitunnissa hallitsit releen ajoitusta peruuttamalla MQTT-viestien tilauksen, kun rele oli päällä, ja hetken sen sammuttamisen jälkeen. Tätä menetelmää ei voi käyttää tässä - et voi peruuttaa IoT Hub -liipaisintasi.

Mieti erilaisia tapoja, joilla voisit käsitellä tätä Functions-sovelluksessasi.

## Oppitunnin jälkeinen kysely

[Oppitunnin jälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Kertaus ja itseopiskelu

* Lue lisää palvelimettomasta laskennasta [Serverless Computing -sivulta Wikipediassa](https://wikipedia.org/wiki/Serverless_computing)
* Lue palvelimettoman käytöstä Azuren kanssa, mukaan lukien lisää esimerkkejä, [Go serverless for your IoT needs Azure -blogikirjoituksesta](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Opi lisää Azure Functionsista [Azure Functions YouTube -kanavalla](https://www.youtube.com/c/AzureFunctions)

## Tehtävä

[Lisää manuaalinen releen ohjaus](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.