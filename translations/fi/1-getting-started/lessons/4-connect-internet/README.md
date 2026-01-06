<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "71b5040e0b3472f1c0949c9b55f224c0",
  "translation_date": "2025-08-27T21:41:15+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/README.md",
  "language_code": "fi"
}
-->
# Yhdistä laitteesi Internetiin

![Tämän oppitunnin sketchnote-yhteenveto](../../../../../translated_images/lesson-4.7344e074ea68fa545fd320b12dce36d72dd62d28c3b4596cb26cf315f434b98f.fi.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä oppitunti oli osa [Hello IoT -sarjaa](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) [Microsoft Reactorilta](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Oppitunti koostui kahdesta videosta: tunnin mittaisesta oppitunnista ja tunnin mittaisesta toimistotunnista, jossa syvennyttiin oppitunnin osiin ja vastattiin kysymyksiin.

[![Oppitunti 4: Yhdistä laitteesi Internetiin](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Oppitunti 4: Yhdistä laitteesi Internetiin - Toimistotunti](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Klikkaa yllä olevia kuvia katsoaksesi videot

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Johdanto

IoT:n **I** tarkoittaa **Internet**iä – pilviyhteyksiä ja palveluita, jotka mahdollistavat monia IoT-laitteiden ominaisuuksia, kuten antureiden keräämien mittausten vastaanottamisen ja viestien lähettämisen toimilaitteiden ohjaamiseksi. IoT-laitteet yhdistyvät tyypillisesti yhteen pilvipalveluun käyttäen standardoitua viestintäprotokollaa, ja tämä palvelu yhdistyy muuhun IoT-sovellukseesi, kuten tekoälypalveluihin, jotka tekevät älykkäitä päätöksiä datan perusteella, tai verkkosovelluksiin ohjausta tai raportointia varten.

> 🎓 Antureiden keräämää ja pilveen lähetettyä dataa kutsutaan telemetriaksi.

IoT-laitteet voivat vastaanottaa viestejä pilvestä. Usein viestit sisältävät komentoja – ohjeita suorittaa toiminto joko sisäisesti (kuten uudelleenkäynnistys tai laiteohjelmiston päivitys) tai toimilaitteen avulla (kuten valon sytyttäminen).

Tässä oppitunnissa esitellään joitakin viestintäprotokollia, joita IoT-laitteet voivat käyttää pilveen yhdistämiseen, sekä datatyyppejä, joita ne voivat lähettää tai vastaanottaa. Pääset myös käytännössä kokeilemaan näitä, lisäten internet-ohjauksen yövaloon ja siirtäen LED-ohjauslogiikan paikallisesti pyörivään "palvelin"-koodiin.

Tässä oppitunnissa käsitellään:

* [Viestintäprotokollat](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetria](../../../../../1-getting-started/lessons/4-connect-internet)
* [Komennot](../../../../../1-getting-started/lessons/4-connect-internet)

## Viestintäprotokollat

IoT-laitteiden ja Internetin väliseen viestintään on useita suosittuja protokollia. Suosituimmat perustuvat julkaisu/tilaus-malliin jonkinlaisen välittäjän kautta. IoT-laitteet yhdistyvät välittäjään ja julkaisevat telemetriaa sekä tilaavat komentoja. Pilvipalvelut yhdistyvät myös välittäjään, tilaavat kaikki telemetriaviestit ja julkaisevat komentoja joko tiettyihin laitteisiin tai laitejoukkoihin.

![IoT-laitteet yhdistyvät välittäjään, julkaisevat telemetriaa ja tilaavat komentoja. Pilvipalvelut yhdistyvät välittäjään, tilaavat kaikki telemetriat ja lähettävät komentoja tiettyihin laitteisiin.](../../../../../translated_images/pub-sub.7c7ed43fe9fd15d4.fi.png)

MQTT on suosituin viestintäprotokolla IoT-laitteille, ja se käsitellään tässä oppitunnissa. Muita protokollia ovat AMQP ja HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) on kevyt, avoin standardi viestintäprotokolla, joka voi lähettää viestejä laitteiden välillä. Se suunniteltiin vuonna 1999 öljyputkien valvontaan, ja IBM julkaisi sen avoimena standardina 15 vuotta myöhemmin.

MQTT:ssä on yksi välittäjä ja useita asiakkaita. Kaikki asiakkaat yhdistyvät välittäjään, ja välittäjä ohjaa viestit oikeille asiakkaille. Viestit ohjataan nimettyjen aiheiden avulla, eikä niitä lähetetä suoraan yksittäiselle asiakkaalle. Asiakas voi julkaista aiheeseen, ja kaikki asiakkaat, jotka tilaavat kyseisen aiheen, saavat viestin.

![IoT-laite julkaisee telemetriaa /telemetry-aiheessa, ja pilvipalvelu tilaa kyseisen aiheen](../../../../../translated_images/mqtt.cbf7f21d9adc3e17548b359444cc11bb4bf2010543e32ece9a47becf54438c23.fi.png)

✅ Tee tutkimusta. Jos sinulla on paljon IoT-laitteita, miten voit varmistaa, että MQTT-välittäjäsi pystyy käsittelemään kaikki viestit?

### Yhdistä IoT-laitteesi MQTT:hen

Ensimmäinen askel yövalon internet-ohjauksen lisäämisessä on sen yhdistäminen MQTT-välittäjään.

#### Tehtävä

Yhdistä laitteesi MQTT-välittäjään.

Tässä oppitunnin osassa yhdistät IoT-yövalosi internetiin, jotta sitä voidaan ohjata etänä. Myöhemmin tässä oppitunnissa IoT-laitteesi lähettää telemetriaviestin MQTT:n kautta julkiseen MQTT-välittäjään, jossa se vastaanotetaan palvelinkoodilla, jonka kirjoitat. Tämä koodi tarkistaa valotason ja lähettää komento-viestin takaisin laitteelle, kehottaen sitä sytyttämään tai sammuttamaan LEDin.

Todellisessa käyttötilanteessa tällainen järjestely voisi kerätä dataa useista valotunnistimista ennen kuin päätetään sytyttää valot paikassa, jossa on paljon valoja, kuten stadionilla. Tämä voisi estää valojen sytyttämisen, jos vain yksi tunnistin on pilvien tai linnun peitossa, mutta muut tunnistimet havaitsevat riittävästi valoa.

✅ Mitkä muut tilanteet vaatisivat datan arviointia useista tunnistimista ennen komentojen lähettämistä?

Sen sijaan, että käsittelisit MQTT-välittäjän asettamisen monimutkaisuuksia osana tätä tehtävää, voit käyttää julkista testipalvelinta, joka käyttää [Eclipse Mosquittoa](https://www.mosquitto.org), avointa MQTT-välittäjää. Tämä testivälittäjä on julkisesti saatavilla osoitteessa [test.mosquitto.org](https://test.mosquitto.org), eikä vaadi tilin luomista, mikä tekee siitä erinomaisen työkalun MQTT-asiakkaiden ja -palvelimien testaamiseen.

> 💁 Tämä testivälittäjä on julkinen ja ei-suojattu. Kuka tahansa voi kuunnella, mitä julkaiset, joten sitä ei pitäisi käyttää yksityistä dataa sisältävien viestien kanssa.

![Tehtävän vuokaavio, jossa valotasoja luetaan ja tarkistetaan, ja LEDiä ohjataan](../../../../../translated_images/assignment-1-internet-flow.3256feab5f052fd273bf4e331157c574c2c3fa42e479836fc9c3586f41db35a5.fi.png)

Seuraa alla olevaa ohjetta yhdistääksesi laitteesi MQTT-välittäjään:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Yksikorttitietokone - Raspberry Pi/virtuaalinen IoT-laite](single-board-computer-mqtt.md)

### Syvällisempi katsaus MQTT:hen

Aiheilla voi olla hierarkia, ja asiakkaat voivat tilata hierarkian eri tasoja käyttämällä jokerimerkkejä. Esimerkiksi voit lähettää lämpötilatelemetriaa `/telemetry/temperature`-aiheeseen ja kosteustelemetriaa `/telemetry/humidity`-aiheeseen, ja pilvisovelluksessasi tilata `/telemetry/*`-aiheen vastaanottaaksesi sekä lämpötila- että kosteustelemetriaviestit.

Viestit voidaan lähettää palvelutason (QoS) kanssa, joka määrittää viestin vastaanottamisen takuun.

* Korkeintaan kerran – viesti lähetetään vain kerran, eikä asiakas ja välittäjä tee lisätoimenpiteitä toimituksen vahvistamiseksi (lähetä ja unohda).
* Vähintään kerran – viestiä yritetään lähettää useita kertoja, kunnes vahvistus vastaanotetaan (vahvistettu toimitus).
* Täsmälleen kerran – lähettäjä ja vastaanottaja suorittavat kaksitasoisen käsittelyn varmistaakseen, että vain yksi kopio viestistä vastaanotetaan (varmistettu toimitus).

✅ Mitkä tilanteet saattaisivat vaatia varmistettua toimitusviestiä verrattuna lähetä ja unohda -viestiin?

Vaikka nimi on Message Queueing (MQTT:n alkukirjaimet), se ei itse asiassa tue viestijonoja. Tämä tarkoittaa, että jos asiakas katkaisee yhteyden ja yhdistää uudelleen, se ei saa viestejä, jotka lähetettiin katkoksen aikana, paitsi ne viestit, jotka se oli jo aloittanut käsittelemään QoS-prosessin avulla. Viesteillä voi olla säilytysmerkki asetettuna. Jos tämä on asetettu, MQTT-välittäjä tallentaa viimeisen viestin, joka on lähetetty aiheeseen tämän merkin kanssa, ja lähettää sen kaikille asiakkaille, jotka myöhemmin tilaavat aiheen. Näin asiakkaat saavat aina viimeisimmän viestin.

MQTT tukee myös keep alive -toimintoa, joka tarkistaa, onko yhteys edelleen aktiivinen pitkien viestivälien aikana.

> 🦟 [Mosquitto Eclipse Foundationilta](https://mosquitto.org) tarjoaa ilmaisen MQTT-välittäjän, jonka voit itse ajaa kokeillaksesi MQTT:tä, sekä julkisen MQTT-välittäjän, jota voit käyttää koodisi testaamiseen, osoitteessa [test.mosquitto.org](https://test.mosquitto.org).

MQTT-yhteydet voivat olla julkisia ja avoimia, tai salattuja ja suojattuja käyttäjätunnusten ja salasanojen tai sertifikaattien avulla.

> 💁 MQTT kommunikoi TCP/IP:n kautta, samaa verkon perusprotokollaa kuin HTTP, mutta eri portissa. Voit myös käyttää MQTT:tä websocketsin kautta kommunikoidaksesi verkkosovellusten kanssa, jotka toimivat selaimessa, tai tilanteissa, joissa palomuurit tai muut verkon säännöt estävät tavalliset MQTT-yhteydet.

## Telemetria

Sana telemetria tulee kreikan juurista, jotka tarkoittavat etämittausta. Telemetria tarkoittaa datan keräämistä antureista ja sen lähettämistä pilveen.

> 💁 Yksi varhaisimmista telemetrialaitteista keksittiin Ranskassa vuonna 1874, ja se lähetti reaaliaikaisia sää- ja lumensyvyystietoja Mont Blancilta Pariisiin. Se käytti fyysisiä johtoja, koska langattomat teknologiat eivät olleet tuolloin saatavilla.

Palataanpa esimerkkiin älytermostaatista oppitunnista 1.

![Internet-yhteydellä varustettu termostaatti, joka käyttää useita huoneantureita](../../../../../translated_images/telemetry.21e5d8b97649d2eb.fi.png)

Termostaatilla on lämpötila-anturit telemetrian keräämiseen. Sillä olisi todennäköisesti yksi sisäänrakennettu lämpötila-anturi, ja se saattaisi yhdistyä useisiin ulkoisiin lämpötila-antureihin langattoman protokollan, kuten [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE), kautta.

Esimerkki telemetriadatasta, jonka se voisi lähettää, voisi olla:

| Nimi | Arvo | Kuvaus |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Termostaatin sisäänrakennetun lämpötila-anturin mittaama lämpötila |
| `livingroom_temperature` | 19°C | Etäanturin mittaama lämpötila, joka on nimetty `livingroom` huoneen tunnistamiseksi |
| `bedroom_temperature` | 21°C | Etäanturin mittaama lämpötila, joka on nimetty `bedroom` huoneen tunnistamiseksi |

Pilvipalvelu voi sitten käyttää tätä telemetriadataa päätösten tekemiseen lämmityksen ohjaamiseen liittyen.

### Lähetä telemetriaa IoT-laitteestasi

Seuraava askel yövalon internet-ohjauksen lisäämisessä on valotason telemetrian lähettäminen MQTT-välittäjään telemetria-aiheessa.

#### Tehtävä - lähetä telemetriaa IoT-laitteestasi

Lähetä valotason telemetriaa MQTT-välittäjään.

Data lähetetään JSON-muodossa – lyhenne sanoista JavaScript Object Notation, standardi datan tekstimuotoiselle koodaukselle avain/arvo-pareina.

✅ Jos et ole aiemmin törmännyt JSON:iin, voit oppia lisää siitä [JSON.org-dokumentaatiosta](https://www.json.org/).

Seuraa alla olevaa ohjetta lähettääksesi telemetriaa laitteestasi MQTT-välittäjään:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Yksikorttitietokone - Raspberry Pi/virtuaalinen IoT-laite](single-board-computer-telemetry.md)

### Vastaanota telemetriaa MQTT-välittäjältä

Telemetrian lähettämisessä ei ole järkeä, jos kukaan ei kuuntele sitä. Valotason telemetria tarvitsee jonkun kuuntelemaan sitä datan käsittelemiseksi. Tämä "palvelin"-koodi on tyyppistä koodia, jonka voit ottaa käyttöön pilvipalvelussa osana laajempaa IoT-sovellusta, mutta tässä aiot ajaa tämän koodin paikallisesti tietokoneellasi (tai Pi:lläsi, jos koodaat suoraan siellä). Palvelinkoodi koostuu Python-sovelluksesta, joka kuuntelee telemetriaviestejä MQTT:n kautta valotasoilla. Myöhemmin tässä oppitunnissa saat sen vastaamaan komento-viestillä, jossa on ohjeet LEDin sytyttämiseen tai sammuttamiseen.

✅ Tee tutkimusta: Mitä tapahtuu MQTT-viesteille, jos kukaan ei kuuntele niitä?

#### Asenna Python ja VS Code

Jos sinulla ei ole Pythonia ja VS Codea asennettuna paikallisesti, sinun täytyy asentaa ne molemmat palvelinkoodin kirjoittamista varten. Jos käytät virtuaalista IoT-laitetta tai työskentelet Raspberry Pi:llä, voit ohittaa tämän vaiheen, sillä ne pitäisi olla jo asennettu ja konfiguroitu.

##### Tehtävä - asenna Python ja VS Code

Asenna Python ja VS Code.

1. Asenna Python. Katso [Pythonin lataussivulta](https://www.python.org/downloads/) ohjeet uusimman Python-version asentamiseen.

1. Asenna Visual Studio Code (VS Code). Tämä on editori, jota käytät virtuaalisen laitteen koodin kirjoittamiseen Pythonilla. Katso [VS Code -dokumentaatiosta](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) ohjeet VS Coden asentamiseen.
💁 Voit vapaasti käyttää mitä tahansa Python IDE:tä tai editoria näiden oppituntien aikana, jos sinulla on suosikkityökalu, mutta oppitunnit antavat ohjeita perustuen VS Codeen.
1. Asenna VS Code Pylance -laajennus. Tämä on VS Code -laajennus, joka tarjoaa Python-kielituen. Katso [Pylance-laajennuksen dokumentaatio](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) saadaksesi ohjeet laajennuksen asentamiseen VS Codeen.

#### Määritä Python-virtuaaliympäristö

Yksi Pythonin tehokkaista ominaisuuksista on mahdollisuus asentaa [pip-paketteja](https://pypi.org) - nämä ovat muiden ihmisten kirjoittamia ja Internetiin julkaistuja koodipaketteja. Voit asentaa pip-paketin tietokoneellesi yhdellä komennolla ja käyttää sitä sitten koodissasi. Käytät pipiä MQTT-yhteyden muodostamiseen tarvittavan paketin asentamiseen.

Oletuksena, kun asennat paketin, se on käytettävissä kaikkialla tietokoneellasi, mikä voi johtaa ongelmiin pakettiversioiden kanssa - esimerkiksi yksi sovellus voi riippua tietystä pakettiversiosta, joka ei toimi, kun asennat uuden version toista sovellusta varten. Tämän ongelman kiertämiseksi voit käyttää [Python-virtuaaliympäristöä](https://docs.python.org/3/library/venv.html), joka on käytännössä Pythonin kopio omassa kansiossaan. Kun asennat pip-paketteja, ne asennetaan vain kyseiseen kansioon.

##### Tehtävä - määritä Python-virtuaaliympäristö

Määritä Python-virtuaaliympäristö ja asenna MQTT-pip-paketit.

1. Avaa terminaali tai komentorivi ja suorita seuraavat komennot haluamassasi sijainnissa uuden hakemiston luomiseksi ja siihen siirtymiseksi:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Suorita seuraava komento virtuaaliympäristön luomiseksi `.venv`-kansioon:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Sinun täytyy kutsua `python3` nimenomaisesti virtuaaliympäristön luomiseksi, jos sinulla on Python 2 asennettuna Python 3:n lisäksi (uusin versio). Jos Python 2 on asennettuna, `python` käyttää Python 2:ta Python 3:n sijaan.

1. Aktivoi virtuaaliympäristö:

    * Windowsissa:
        * Jos käytät Command Promptia tai Windows Terminalin kautta Command Promptia, suorita:

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

    > 💁 Nämä komennot tulee suorittaa samasta sijainnista, jossa loit virtuaaliympäristön. Sinun ei koskaan tarvitse siirtyä `.venv`-kansioon, vaan sinun tulee aina suorittaa aktivointikomento ja kaikki komennot pakettien asentamiseksi tai koodin suorittamiseksi kansiosta, jossa olit virtuaaliympäristön luomisen aikana.

1. Kun virtuaaliympäristö on aktivoitu, oletus `python`-komento suorittaa sen Python-version, jota käytettiin virtuaaliympäristön luomiseen. Suorita seuraava komento version tarkistamiseksi:

    ```sh
    python --version
    ```

    Tuloste näyttää suunnilleen tältä:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Python-versiosi voi olla erilainen - kunhan se on versio 3.6 tai uudempi, olet hyvässä tilanteessa. Jos ei, poista tämä kansio, asenna uudempi Python-versio ja yritä uudelleen.

1. Suorita seuraavat komennot [Paho-MQTT](https://pypi.org/project/paho-mqtt/)-pip-paketin asentamiseksi, joka on suosittu MQTT-kirjasto.

    ```sh
    pip install paho-mqtt
    ```

    Tämä pip-paketti asennetaan vain virtuaaliympäristöön eikä ole käytettävissä sen ulkopuolella.

#### Kirjoita palvelinkoodi

Palvelinkoodi voidaan nyt kirjoittaa Pythonilla.

##### Tehtävä - kirjoita palvelinkoodi

Kirjoita palvelinkoodi.

1. Suorita terminaalissa tai komentorivillä seuraava komento virtuaaliympäristön sisällä Python-tiedoston `app.py` luomiseksi:

    * Windowsissa suorita:

        ```cmd
        type nul > app.py
        ```

    * macOS:ssä tai Linuxissa suorita:

        ```cmd
        touch app.py
        ```

1. Avaa nykyinen kansio VS Codessa:

    ```sh
    code .
    ```

1. Kun VS Code käynnistyy, se aktivoi Python-virtuaaliympäristön. Tämä näkyy alareunan tilapalkissa:

    ![VS Code näyttää valitun virtuaaliympäristön](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.fi.png)

1. Jos VS Code -terminaali on jo käynnissä, kun VS Code käynnistyy, virtuaaliympäristö ei ole aktivoituna siinä. Helpoin tapa korjata tämä on sulkea terminaali käyttämällä **Sulje aktiivinen terminaali**-painiketta:

    ![VS Code Sulje aktiivinen terminaali -painike](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.fi.png)

1. Käynnistä uusi VS Code -terminaali valitsemalla *Terminal -> New Terminal* tai painamalla `` CTRL+` ``. Uusi terminaali lataa virtuaaliympäristön, ja aktivointikutsu näkyy terminaalissa. Virtuaaliympäristön nimi (`.venv`) näkyy myös kehotteessa:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Avaa `app.py`-tiedosto VS Code -tiedostoselaimesta ja lisää seuraava koodi:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Korvaa `<ID>` rivillä 6 ainutlaatuisella tunnuksella, jota käytit luodessasi laitekoodiasi.

    ⚠️ Tämä **täytyy** olla sama tunnus, jota käytit laitteessasi, muuten palvelinkoodi ei tilaa tai julkaise oikeaan aiheeseen.

    Tämä koodi luo MQTT-asiakkaan ainutlaatuisella nimellä ja yhdistää sen *test.mosquitto.org*-välittäjään. Se käynnistää käsittelysilmukan, joka toimii taustasäikeessä kuunnellen viestejä kaikista tilatuista aiheista.

    Asiakas tilaa viestit telemetria-aiheesta ja määrittää funktion, joka kutsutaan, kun viesti vastaanotetaan. Kun telemetriaviesti vastaanotetaan, `handle_telemetry`-funktio kutsutaan, ja vastaanotettu viesti tulostetaan konsoliin.

    Lopuksi ääretön silmukka pitää sovelluksen käynnissä. MQTT-asiakas kuuntelee viestejä taustasäikeessä ja toimii koko ajan, kun pääsovellus on käynnissä.

1. Suorita VS Code -terminaalista seuraava komento Python-sovelluksesi suorittamiseksi:

    ```sh
    python app.py
    ```

    Sovellus alkaa kuunnella IoT-laitteelta tulevia viestejä.

1. Varmista, että laitteesi on käynnissä ja lähettää telemetriaviestejä. Säädä fyysisen tai virtuaalisen laitteen havaitsemia valotasoja. Vastaanotetut viestit tulostetaan terminaaliin.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Nightlight-virtuaaliympäristön `app.py`-tiedoston täytyy olla käynnissä, jotta nightlight-server-virtuaaliympäristön `app.py`-tiedosto voi vastaanottaa lähetetyt viestit.

> 💁 Löydät tämän koodin [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server)-kansiosta.

### Kuinka usein telemetriaa tulisi lähettää?

Yksi tärkeä telemetriaan liittyvä kysymys on, kuinka usein dataa tulisi mitata ja lähettää? Vastaus on - se riippuu. Jos mittaat usein, voit reagoida nopeammin muutoksiin, mutta käytät enemmän virtaa, kaistanleveyttä, tuotat enemmän dataa ja tarvitset enemmän pilviresursseja sen käsittelyyn. Sinun täytyy mitata tarpeeksi usein, mutta ei liian usein.

Termostaatille mittaaminen muutaman minuutin välein on todennäköisesti enemmän kuin tarpeeksi, koska lämpötilat eivät muutu niin usein. Jos mittaat vain kerran päivässä, saatat päätyä lämmittämään taloa yöaikojen lämpötilojen mukaan keskellä aurinkoista päivää, kun taas jos mittaat joka sekunti, saat tuhansia tarpeettomasti toistettuja lämpötilamittauksia, jotka syövät käyttäjän Internet-nopeutta ja kaistanleveyttä (ongelma ihmisille, joilla on rajoitetut kaistanleveyssuunnitelmat), käyttävät enemmän virtaa, mikä voi olla ongelma akkukäyttöisille laitteille, kuten etäantureille, ja lisäävät pilvipalveluntarjoajan laskentaresurssien kustannuksia niiden käsittelyyn ja tallentamiseen.

Jos valvot tehdaskoneen dataa, jonka vikaantuminen voisi aiheuttaa katastrofaalisia vahinkoja ja miljoonien dollarien menetettyjä tuloja, mittaaminen useita kertoja sekunnissa saattaa olla tarpeen. On parempi tuhlata kaistanleveyttä kuin jättää huomaamatta telemetria, joka osoittaa, että kone täytyy pysäyttää ja korjata ennen kuin se rikkoutuu.

> 💁 Tässä tilanteessa kannattaa harkita reunalaitteen käyttöä telemetrian käsittelyyn ensin, jotta riippuvuus Internetistä vähenee.

### Yhteyden katkeaminen

Internet-yhteydet voivat olla epäluotettavia, ja katkoksia esiintyy usein. Mitä IoT-laitteen tulisi tehdä tällaisessa tilanteessa - pitäisikö sen menettää data vai tallentaa se, kunnes yhteys palautuu? Taas kerran, vastaus on se riippuu.

Termostaatille data voidaan todennäköisesti menettää heti, kun uusi lämpötilamittaus on tehty. Lämmitysjärjestelmää ei kiinnosta, että 20 minuuttia sitten lämpötila oli 20,5°C, jos lämpötila on nyt 19°C - nykyinen lämpötila määrittää, pitäisikö lämmitys olla päällä vai ei.

Koneille data kannattaa ehkä säilyttää, erityisesti jos sitä käytetään trendien etsimiseen. On olemassa koneoppimismalleja, jotka voivat havaita poikkeavuuksia datavirroissa tarkastelemalla tietyn ajanjakson (kuten viimeisen tunnin) dataa ja havaitsemalla poikkeavaa dataa. Tätä käytetään usein ennakoivassa huollossa, etsimällä merkkejä siitä, että jokin saattaa rikkoutua pian, jotta voit korjata tai vaihtaa sen ennen kuin se tapahtuu. Saatat haluta, että kaikki koneen telemetria lähetetään, jotta se voidaan käsitellä poikkeavuuksien havaitsemiseksi, joten kun IoT-laite voi muodostaa yhteyden uudelleen, se lähettää kaikki Internet-katkoksen aikana tuotetut telemetriat.

IoT-laitteiden suunnittelijoiden tulisi myös harkita, voiko IoT-laite toimia Internet-katkoksen tai sijainnin aiheuttaman signaalin menetyksen aikana. Älykäs termostaatti pitäisi pystyä tekemään joitakin rajoitettuja päätöksiä lämmityksen ohjaamiseksi, jos se ei voi lähettää telemetriaa pilveen katkoksen vuoksi.

[![Tämä Ferrari meni käyttökelvottomaksi, koska joku yritti päivittää sitä maan alla, missä ei ole matkapuhelinverkkoa](../../../../../translated_images/bricked-car.dc38f8efadc6c59d76211f981a521efb300939283dee468f79503aae3ec67615.fi.png)](https://twitter.com/internetofshit/status/1315736960082808832)

MQTT:n käsitelläkseen yhteyden katkeamista laitteen ja palvelinkoodin täytyy huolehtia viestien toimituksesta, jos se on tarpeen, esimerkiksi vaatimalla, että kaikki lähetetyt viestit saavat vastauksen lisäviesteillä vastausaiheessa, ja jos eivät, ne jonotetaan manuaalisesti toistettavaksi myöhemmin.

## Komennot

Komennot ovat viestejä, jotka pilvi lähettää laitteelle, ohjeistaen sitä tekemään jotain. Useimmiten tämä tarkoittaa jonkinlaista ulostuloa aktuaattorin kautta, mutta se voi olla ohje laitteelle itselleen, kuten uudelleenkäynnistys tai lisätelemetrian kerääminen ja palauttaminen vastauksena komentoon.

![Internet-yhteydessä oleva termostaatti vastaanottaa komennon lämmityksen kytkemiseksi päälle](../../../../../translated_images/commands.d6c06bbbb3a02cce95f2831a1c331daf6dedd4e470c4aa2b0ae54f332016e504.fi.png)

Termostaatti voisi vastaanottaa pilvestä komennon kytkeä lämmitys päälle. Kaikkien antureiden telemetriatietojen perusteella pilvipalvelu on päättänyt, että lämmitys pitäisi olla päällä, joten se lähettää asiaankuuluvan komennon.

### Lähetä komentoja MQTT-välittäjälle

Seuraava askel Internet-ohjatulle yövalolle on, että palvelinkoodi lähettää komennon takaisin IoT-laitteelle ohjatakseen valoa sen havaitsemien valotasojen perusteella.

1. Avaa palvelinkoodi VS Codessa

1. Lisää seuraava rivi `client_telemetry_topic`-määrittelyn jälkeen määrittääksesi, mihin aiheeseen komennot lähetetään:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Lisää seuraava koodi `handle_telemetry`-funktion loppuun:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Tämä lähettää JSON-viestin komentoaiheeseen, jossa `led_on`-arvo asetetaan joko trueksi tai falseksi riippuen siitä, onko valo alle 300 vai ei. Jos valo on alle 300, true lähetetään ohjeistamaan laitetta kytkemään LED päälle.

1. Suorita koodi kuten aiemmin

1. Säädä fyysisen tai virtuaalisen laitteen havaitsemia valotasoja. Vastaanotetut viestit ja lähetetyt komennot kirjoitetaan terminaaliin:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetria ja komennot lähetetään yksittäisellä aiheella. Tämä tarkoittaa, että telemetria useilta laitteilta näkyy samalla telemetria-aiheella, ja komennot useille laitteille näkyvät samalla komentoaiheella. Jos haluaisit lähettää komennon tietylle laitteelle, voisit käyttää useita aiheita, nimettyjä ainutlaatuisella laitetunnuksella, kuten `/commands/device1`, `/commands/device2`. Näin laite voi kuunnella viestejä, jotka on tarkoitettu vain sille yhdelle laitteelle.

> 💁 Löydät tämän koodin [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server)-kansiosta.

### Käsittele komentoja IoT-laitteessa

Nyt kun komentoja lähetetään palvelimelta, voit lisätä koodia IoT-laitteeseen niiden käsittelemiseksi ja LED:n ohjaamiseksi.

Seuraa alla olevaa ohjetta kuunnellaksesi komentoja MQTT-välittäjältä:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Yksikorttitietokone - Raspberry Pi/virtuaalinen IoT-laite](single-board-computer-commands.md)

Kun tämä koodi on kirjoitettu ja käynnissä, kokeile valotasojen muuttamista. Katso palvelimen ja laitteen tulosteet ja katso LED:n toimintaa, kun muutat valotasoja.

### Yhteyden katkeaminen

Mitä pilvipalvelun tulisi tehdä, jos sen täytyy lähettää komento IoT-laitteelle, joka on offline-tilassa? Taas kerran, vastaus on se riippuu.

Jos uusin komento korvaa aiemman, aiemmat voidaan todennäköisesti jättää huomiotta. Jos pilvipalvelu lähettää komennon kytkeä lämmitys päälle ja sitten komennon kytkeä se pois päältä, päälle-komento voidaan jättää huomiotta eikä lähettää uudelleen.

Jos komennot täytyy käsitellä järjestyksessä, kuten robotin käsivarren siirtäminen ylös ja sitten tarttujan sulkeminen, ne täytyy lähettää järjestyksessä, kun yhteys palautuu.

✅ Kuinka laite- tai palvelinkoodi voisi varmistaa, että komennot lähetetään ja käsitellään aina järjestyksessä MQTT:n kautta, jos se on tarpeen?

---

## 🚀 Haaste

Viimeisten kolmen oppitunnin haasteena oli listata mahdollisimman monta IoT-laitetta, jotka ovat kotonasi, koulussasi tai työpaikallasi, ja päättää, onko ne rakennettu mikro-ohjaimien vai yksikorttitietokoneiden ympärille, vai jopa näiden yhdistelmään, ja miettiä, mitä antureita ja aktuaattoreita ne käyttävät.
Mieti näiden laitteiden kohdalla, millaisia viestejä ne saattavat lähettää tai vastaanottaa. Mitä telemetriatietoja ne lähettävät? Millaisia viestejä tai komentoja ne saattavat vastaanottaa? Uskotko, että ne ovat turvallisia?

## Luentojälkeinen kysely

[Luentojälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Kertaus ja itseopiskelu

Lue lisää MQTT:stä [MQTT:n Wikipedia-sivulta](https://wikipedia.org/wiki/MQTT).

Kokeile itse käynnistää MQTT-välityspalvelin käyttämällä [Mosquittoa](https://www.mosquitto.org) ja yhdistä siihen IoT-laitteesi ja palvelinkoodisi avulla.

> 💁 Vinkki - Mosquitto ei oletuksena salli anonyymejä yhteyksiä (eli yhteyksiä ilman käyttäjätunnusta ja salasanaa), eikä salli yhteyksiä tietokoneen ulkopuolelta, jossa se toimii.
> Voit korjata tämän käyttämällä [`mosquitto.conf`-asetustiedostoa](https://www.mosquitto.org/man/mosquitto-conf-5.html), jossa on seuraavat asetukset:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Tehtävä

[Vertaile MQTT:tä muihin viestintäprotokolliin](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.