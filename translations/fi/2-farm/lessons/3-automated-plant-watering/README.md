# Automaattinen kasvien kastelu

![Yleiskatsaus oppitunnista sketchnotena](../../../../../translated_images/fi/lesson-7.30b5f577d3cb8e03.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä oppitunti on osa [IoT for Beginners Project 2 - Digital Agriculture -sarjaa](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx), joka on peräisin [Microsoft Reactorilta](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![IoT-pohjainen automaattinen kasvien kastelu](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Johdanto

Edellisessä oppitunnissa opit seuraamaan maaperän kosteutta. Tässä oppitunnissa opit rakentamaan automaattisen kastelujärjestelmän keskeiset komponentit, jotka reagoivat maaperän kosteuteen. Opit myös ajastuksesta – kuinka anturit voivat reagoida hitaasti muutoksiin ja kuinka toimilaitteet voivat vaikuttaa mitattaviin ominaisuuksiin ajan kuluessa.

Tässä oppitunnissa käsitellään:

* [Ohjaa suuritehoisia laitteita pienitehoisella IoT-laitteella](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Ohjaa relettä](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Ohjaa kasvejasi MQTT:n kautta](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Anturin ja toimilaitteen ajastus](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Lisää ajastus kasvien ohjauspalvelimeen](../../../../../2-farm/lessons/3-automated-plant-watering)

## Ohjaa suuritehoisia laitteita pienitehoisella IoT-laitteella

IoT-laitteet käyttävät matalaa jännitettä. Vaikka tämä riittää antureille ja pienitehoisille toimilaitteille, kuten LED-valoille, se ei riitä suurempien laitteiden, kuten kasteluun käytettävän vesipumpun, ohjaamiseen. Jopa pienet pumput, joita voisit käyttää huonekasveihin, kuluttavat liikaa virtaa IoT-kehitysalustalle ja saattaisivat vahingoittaa sen komponentteja.

> 🎓 Virta, joka mitataan ampeereina (A), kuvaa sähkövirran määrää, joka kulkee piirin läpi. Jännite antaa työntövoiman, kun taas virta kuvaa, kuinka paljon työntöä tapahtuu. Voit lukea lisää virrasta [Wikipedia-sivulta sähkövirta](https://wikipedia.org/wiki/Electric_current).

Ratkaisuna on kytkeä pumppu ulkoiseen virtalähteeseen ja käyttää toimilaitetta pumpun käynnistämiseen, aivan kuten valon kytkemisessä päälle. Sormesi tarvitsee vain pienen määrän energiaa kytkimen kääntämiseen, mikä yhdistää valon kotitaloussähköön, joka toimii 110v/240v jännitteellä.

![Valokytkin kytkee valon päälle](../../../../../translated_images/fi/light-switch.760317ad6ab8bd6d.webp)

> 🎓 [Kotitaloussähkö](https://wikipedia.org/wiki/Mains_electricity) viittaa sähköön, joka toimitetaan koteihin ja yrityksiin kansallisen infrastruktuurin kautta monissa maailman osissa.

✅ IoT-laitteet voivat yleensä tarjota 3.3V tai 5V, alle 1 ampeerin (1A) virralla. Vertaa tätä kotitaloussähköön, joka on useimmiten 230V (120V Pohjois-Amerikassa ja 100V Japanissa) ja voi tarjota virtaa laitteille, jotka kuluttavat jopa 30A.

Toimilaitteita, jotka voivat tehdä tämän, on useita, mukaan lukien mekaaniset laitteet, jotka voidaan kiinnittää olemassa oleviin kytkimiin ja jäljitellä sormen liikettä. Suosituin näistä on rele.

### Releet

Rele on sähkömekaaninen kytkin, joka muuntaa sähköisen signaalin mekaaniseksi liikkeeksi, joka kytkee kytkimen päälle. Releen ydin on sähkömagneetti.

> 🎓 [Sähkömagneetit](https://wikipedia.org/wiki/Electromagnet) ovat magneetteja, jotka syntyvät, kun sähkö kulkee käämin läpi. Kun sähkö kytketään päälle, käämi magnetisoituu. Kun sähkö kytketään pois päältä, käämi menettää magnetisminsa.

![Kun rele on päällä, sähkömagneetti luo magneettikentän, joka kytkee ulostulopiirin päälle](../../../../../translated_images/fi/relay-on.4db16a0fd6b66926.webp)

Releessä ohjauspiiri syöttää sähkömagneetille virtaa. Kun sähkömagneetti on päällä, se vetää vivun, joka liikuttaa kytkintä, sulkee kontaktit ja täydentää ulostulopiirin.

![Kun rele on pois päältä, sähkömagneetti ei luo magneettikenttää, joka kytkisi ulostulopiirin päälle](../../../../../translated_images/fi/relay-off.c34a178a2960fecd.webp)

Kun ohjauspiiri on pois päältä, sähkömagneetti sammuu, vapauttaa vivun ja avaa kontaktit, katkaisten ulostulopiirin. Releet ovat digitaalisia toimilaitteita – korkea signaali kytkee releen päälle, matala signaali kytkee sen pois päältä.

Ulostulopiiriä voidaan käyttää lisälaitteiden, kuten kastelujärjestelmän, virransyöttöön. IoT-laite voi kytkeä releen päälle, täydentää ulostulopiirin, joka syöttää kastelujärjestelmää, ja kasvit saavat vettä. IoT-laite voi sitten kytkeä releen pois päältä, katkaista kastelujärjestelmän virran ja lopettaa veden virtauksen.

![Rele kytkee pumpun päälle, joka lähettää vettä kasville](../../../../../images/strawberry-pump.gif)

Yllä olevassa videossa rele kytketään päälle. Releen LED-valo syttyy osoittamaan, että se on päällä (joissakin relekortteissa on LED-valot, jotka osoittavat releen tilan), ja virta lähetetään pumpulle, joka käynnistyy ja pumppaa vettä kasville.

> 💁 Releitä voidaan käyttää myös vaihtamaan kahden ulostulopiirin välillä sen sijaan, että yksi kytkettäisiin päälle ja pois päältä. Kun vipu liikkuu, se siirtää kytkimen täydentämään yhtä ulostulopiiriä toisen sijasta, yleensä jakamalla yhteisen virtayhteyden tai yhteisen maayhteyden.

✅ Tee tutkimusta: Releitä on useita tyyppejä, joilla on eroja, kuten se, kytkeekö ohjauspiiri releen päälle vai pois päältä, kun virta kytketään, tai onko niissä useita ulostulopiirejä. Ota selvää näistä eri tyypeistä.

Kun vipu liikkuu, voit yleensä kuulla sen osuvan sähkömagneettiin selkeällä napsahduksella.

> 💁 Rele voidaan kytkeä niin, että yhteyden muodostaminen itse asiassa katkaisee releen virran, jolloin rele sammuu, mikä sitten lähettää virtaa releelle kytkien sen takaisin päälle, ja niin edelleen. Tämä tarkoittaa, että rele napsahtaa erittäin nopeasti, mikä aiheuttaa surisevan äänen. Näin jotkut ensimmäiset sähköiset ovikellot toimivat.

### Releen virta

Sähkömagneetti ei tarvitse paljon virtaa aktivoituakseen ja vetääkseen vivun, ja sitä voidaan ohjata IoT-kehitysalustan 3.3V tai 5V ulostulolla. Ulostulopiiri voi kantaa paljon enemmän virtaa, riippuen releestä, mukaan lukien kotitaloussähkö tai jopa korkeammat tehot teollisuuskäyttöön. Näin IoT-kehitysalusta voi ohjata kastelujärjestelmää, pienestä pumpusta yksittäiselle kasville aina massiiviseen teollisuusjärjestelmään koko kaupalliselle tilalle.

![Grove-rele, jossa ohjauspiiri, ulostulopiiri ja rele on merkitty](../../../../../translated_images/fi/grove-relay-labelled.293e068f5c3c2a19.webp)

Yllä olevassa kuvassa näkyy Grove-rele. Ohjauspiiri yhdistetään IoT-laitteeseen ja kytkee releen päälle tai pois päältä 3.3V tai 5V avulla. Ulostulopiirissä on kaksi liitintä, joista kumpi tahansa voi olla virtalähde tai maa. Ulostulopiiri voi käsitellä jopa 250V ja 10A, mikä riittää monille kotitaloussähköllä toimiville laitteille. Saatavilla on myös releitä, jotka kestävät vielä suurempia tehoja.

![Pumppu kytketty releen kautta](../../../../../translated_images/fi/pump-wired-to-relay.66c5cfc0d8918990.webp)

Yllä olevassa kuvassa pumppu saa virtansa releen kautta. Punainen johto yhdistää USB-virtalähteen +5V-liittimen releen ulostulopiirin yhteen liittimeen, ja toinen punainen johto yhdistää ulostulopiirin toisen liittimen pumppuun. Musta johto yhdistää pumpun USB-virtalähteen maahan. Kun rele kytketään päälle, se täydentää piirin, lähettää 5V pumpulle ja käynnistää pumpun.

## Ohjaa relettä

Voit ohjata relettä IoT-kehitysalustaltasi.

### Tehtävä - ohjaa relettä

Käy läpi asiaankuuluva opas releen ohjaamiseksi IoT-laitteellasi:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Yksikorttitietokone - Raspberry Pi](pi-relay.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device-relay.md)

## Ohjaa kasvejasi MQTT:n kautta

Tähän mennessä relettä on ohjattu IoT-laitteelta suoraan yhden maaperän kosteuslukeman perusteella. Kaupallisessa kastelujärjestelmässä ohjauslogiikka on keskitetty, jolloin se voi tehdä kastelupäätöksiä useiden antureiden tietojen perusteella ja mahdollistaa asetusten muuttamisen yhdestä paikasta. Tätä simuloidaksesi voit ohjata relettä MQTT:n kautta.

### Tehtävä - ohjaa relettä MQTT:n kautta

1. Lisää asiaankuuluvat MQTT-kirjastot/pip-paketit ja koodi `soil-moisture-sensor`-projektiisi MQTT-yhteyttä varten. Nimeä asiakas-ID `soilmoisturesensor_client`-muotoon, jonka etuliitteenä on oma ID:si.

    > ⚠️ Voit viitata [ohjeisiin MQTT-yhteyden muodostamisesta projektin 1, oppitunnin 4 kohdassa](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt), jos tarvitset apua.

1. Lisää asiaankuuluva laitekoodi lähettääksesi telemetriatietoja maaperän kosteusasetuksista. Telemetriaviestissä nimeä ominaisuus `soil_moisture`.

    > ⚠️ Voit viitata [ohjeisiin telemetrian lähettämisestä MQTT:hen projektin 1, oppitunnin 4 kohdassa](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device), jos tarvitset apua.

1. Luo paikallinen palvelinkoodi, joka tilaa telemetriatiedot ja lähettää komennon releen ohjaamiseksi kansioon nimeltä `soil-moisture-sensor-server`. Nimeä komento-ominaisuus `relay_on` ja aseta asiakas-ID `soilmoisturesensor_server`-muotoon, jonka etuliitteenä on oma ID:si. Pidä sama rakenne kuin projektin 1, oppitunnin 4 palvelinkoodissa, sillä lisäät tähän koodiin myöhemmin tässä oppitunnissa.

    > ⚠️ Voit viitata [ohjeisiin telemetrian lähettämisestä MQTT:hen](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) ja [komentojen lähettämisestä MQTT:n kautta](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) projektin 1, oppitunnin 4 kohdassa, jos tarvitset apua.

1. Lisää asiaankuuluva laitekoodi releen ohjaamiseksi vastaanotettujen komentojen perusteella, käyttäen viestin `relay_on`-ominaisuutta. Lähetä `true` `relay_on`-ominaisuudelle, jos `soil_moisture` on suurempi kuin 450, muuten lähetä `false`, samalla logiikalla kuin lisäsit IoT-laitteelle aiemmin.

    > ⚠️ Voit viitata [ohjeisiin MQTT-komentojen käsittelystä IoT-laitteella projektin 1, oppitunnin 4 kohdassa](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device), jos tarvitset apua.

> 💁 Löydät tämän koodin [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt)-kansiosta.

Varmista, että koodi toimii laitteellasi ja paikallisella palvelimella, ja testaa sitä muuttamalla maaperän kosteustasoja joko muuttamalla virtuaalianturin lähettämiä arvoja tai lisäämällä vettä maaperään tai poistamalla anturi maaperästä.

## Anturin ja toimilaitteen ajastus

Oppitunnissa 3 rakensit yövalon – LED-valon, joka syttyy heti, kun valotason aleneminen havaitaan valosensorilla. Valosensori havaitsi muutoksen valotasossa välittömästi, ja laite pystyi reagoimaan nopeasti, rajoittuen vain `loop`-funktion tai `while True:`-silmukan viiveeseen. IoT-kehittäjänä et voi aina luottaa näin nopeaan palautesilmukkaan.

### Maaperän kosteuden ajastus

Jos teit edellisen oppitunnin maaperän kosteudesta fyysisellä sensorilla, huomasit, että maaperän kosteuslukeman laskeminen kesti muutaman sekunnin sen jälkeen, kun kastelit kasvia. Tämä ei johdu sensorin hitaudesta, vaan siitä, että veden imeytyminen maaperään vie aikaa.
💁 Jos kastelit liian lähelle anturia, saatat huomata lukeman laskevan nopeasti ja sitten nousevan takaisin – tämä johtuu siitä, että vesi anturin lähellä leviää muualle maaperään, mikä vähentää anturin havaitsemaa maaperän kosteutta.
![Maaperän kosteusmittaus, joka näyttää lukeman 658, ei muutu kastelun aikana. Lukema laskee vasta 320:een, kun vesi on imeytynyt maaperään](../../../../../translated_images/fi/soil-moisture-travel.a0e31af222cf1438.webp)

Yllä olevassa kaaviossa maaperän kosteusmittari näyttää lukeman 658. Kasvia kastellaan, mutta lukema ei muutu heti, koska vesi ei ole vielä saavuttanut anturia. Kastelu voi jopa päättyä ennen kuin vesi saavuttaa anturin ja lukema laskee heijastamaan uutta kosteustasoa.

Jos kirjoittaisit koodia kastelujärjestelmän ohjaamiseen releen avulla maaperän kosteustasojen perusteella, sinun pitäisi ottaa tämä viive huomioon ja rakentaa älykkäämpi ajoitus IoT-laitteeseesi.

✅ Mieti hetki, miten voisit tehdä tämän.

### Ohjaa anturin ja toimilaitteen ajoitusta

Kuvittele, että sinulle on annettu tehtäväksi rakentaa kastelujärjestelmä maatilalle. Maaperän tyypin perusteella ihanteellinen maaperän kosteustaso kasvatettaville kasveille vastaa analogista jännitelukemaa 400-450.

Voisit ohjelmoida laitteen samalla tavalla kuin yövalon - aina kun anturi lukee yli 450, kytke rele päälle ja käynnistä pumppu. Ongelma on, että vesi kestää hetken päästä pumpusta maaperän läpi anturiin. Anturi pysäyttää veden, kun se havaitsee tason 450, mutta veden taso jatkaa laskuaan, kun pumpattu vesi imeytyy maaperään. Lopputuloksena on veden tuhlausta ja juurivaurion riski.

✅ Muista - liiallinen vesi voi olla yhtä haitallista kasveille kuin liian vähäinen, ja se tuhlaa arvokasta resurssia.

Parempi ratkaisu on ymmärtää, että toimilaitteen käynnistämisen ja anturin lukeman muuttumisen välillä on viive. Tämä tarkoittaa, että anturin ei pitäisi vain odottaa hetken ennen kuin se mittaa arvon uudelleen, vaan myös toimilaitteen pitäisi olla pois päältä hetken ennen seuraavaa anturin mittausta.

Kuinka kauan releen pitäisi olla päällä kerrallaan? On parempi olla varovainen ja kytkeä rele päälle vain lyhyeksi ajaksi, odottaa veden imeytymistä ja tarkistaa sitten kosteustasot uudelleen. Loppujen lopuksi voit aina kytkeä sen uudelleen päälle lisätäksesi vettä, mutta et voi poistaa vettä maaperästä.

> 💁 Tällainen ajoituksen hallinta on hyvin spesifistä IoT-laitteelle, jota rakennat, mitattavalle ominaisuudelle sekä käytetyille antureille ja toimilaitteille.

![Mansikkakasvi, joka on yhdistetty veteen pumpun kautta. Pumppu on kytketty releeseen, ja sekä rele että maaperän kosteusanturi ovat kytketty Raspberry Pi:hin](../../../../../translated_images/fi/strawberry-with-pump.b410fc72ac6aabad.webp)

Esimerkiksi minulla on mansikkakasvi, jossa on maaperän kosteusanturi ja pumppu, jota ohjataan releellä. Olen havainnut, että kun lisään vettä, kestää noin 20 sekuntia, ennen kuin maaperän kosteuslukema vakiintuu. Tämä tarkoittaa, että minun täytyy kytkeä rele pois päältä ja odottaa 20 sekuntia ennen kosteustasojen tarkistamista. Mieluummin liian vähän vettä kuin liikaa - voin aina kytkeä pumpun uudelleen päälle, mutta en voi poistaa vettä kasvista.

![Vaihe 1: ota mittaus. Vaihe 2: lisää vettä. Vaihe 3: odota veden imeytymistä maaperään. Vaihe 4: ota uusi mittaus](../../../../../translated_images/fi/soil-moisture-delay.865f3fae206db01d.webp)

Tämä tarkoittaa, että paras prosessi olisi kastelusykli, joka on jotakuinkin seuraava:

* Käynnistä pumppu 5 sekunniksi
* Odota 20 sekuntia
* Tarkista maaperän kosteus
* Jos taso on edelleen liian korkea, toista yllä olevat vaiheet

5 sekuntia voi olla liian pitkä aika pumpulle, erityisesti jos kosteustasot ovat vain hieman yli vaaditun tason. Paras tapa tietää, mitä ajoitusta käyttää, on kokeilla ja säätää, kun sinulla on anturidataa, jatkuvalla palautesilmukalla. Tämä voi jopa johtaa tarkempaan ajoitukseen, kuten pumpun käynnistämiseen 1 sekunniksi jokaista 100 yli vaaditun maaperän kosteustason sijaan, sen sijaan että käytettäisiin kiinteää 5 sekuntia.

✅ Tee tutkimusta: Onko muita ajoitukseen liittyviä huomioita? Voiko kasvia kastella milloin tahansa, kun maaperän kosteus on liian alhainen, vai onko olemassa tiettyjä vuorokaudenaikoja, jotka ovat hyviä tai huonoja kasteluun?

> 💁 Sääennusteet voidaan myös ottaa huomioon ulkokasvien automaattisten kastelujärjestelmien ohjauksessa. Jos sadetta odotetaan, kastelu voidaan keskeyttää, kunnes sade on ohi. Tällöin maaperä voi olla tarpeeksi kostea, ettei kastelua tarvita, mikä on paljon tehokkaampaa kuin veden tuhlaaminen juuri ennen sadetta.

## Lisää ajoitus kasvien ohjauspalvelimeen

Palvelinkoodia voidaan muokata lisäämään ohjausta kastelusyklin ajoituksen ympärille ja odottamaan maaperän kosteustasojen muuttumista. Palvelimen logiikka releen ajoituksen ohjaamiseksi on:

1. Telemetriaviesti vastaanotettu
1. Tarkista maaperän kosteustaso
1. Jos taso on kunnossa, älä tee mitään. Jos lukema on liian korkea (eli maaperän kosteus on liian alhainen), niin:
    1. Lähetä komento releen käynnistämiseksi
    1. Odota 5 sekuntia
    1. Lähetä komento releen sammuttamiseksi
    1. Odota 20 sekuntia, jotta maaperän kosteustasot vakiintuvat

Kastelusykli, prosessi telemetriaviestin vastaanottamisesta siihen, että ollaan valmiita käsittelemään maaperän kosteustasoja uudelleen, kestää noin 25 sekuntia. Lähetämme maaperän kosteustasot joka 10 sekunti, joten on päällekkäisyyttä, jossa viesti vastaanotetaan samalla kun palvelin odottaa maaperän kosteustasojen vakiintumista, mikä voisi käynnistää uuden kastelusyklin.

Tämän kiertämiseksi on kaksi vaihtoehtoa:

* Muuta IoT-laitteen koodia lähettämään telemetriaa vain kerran minuutissa, jolloin kastelusykli ehtii valmistua ennen seuraavan viestin lähettämistä
* Peruuta telemetrian tilaus kastelusyklin aikana

Ensimmäinen vaihtoehto ei aina ole hyvä ratkaisu suurille maatiloille. Viljelijä saattaa haluta tallentaa maaperän kosteustasot kastelun aikana myöhempää analyysiä varten, esimerkiksi ollakseen tietoinen veden virtauksesta eri alueilla tilalla ohjatakseen tarkempaa kastelua. Toinen vaihtoehto on parempi - koodi vain jättää telemetrian huomiotta, kun sitä ei voida käyttää, mutta telemetria on silti olemassa muille palveluille, jotka saattavat tilata sen.

> 💁 IoT-dataa ei lähetetä vain yhdestä laitteesta vain yhdelle palvelulle, vaan monet laitteet voivat lähettää dataa välittäjälle, ja monet palvelut voivat kuunnella dataa välittäjältä. Esimerkiksi yksi palvelu voisi kuunnella maaperän kosteusdataa ja tallentaa sen tietokantaan myöhempää analyysiä varten. Toinen palvelu voi myös kuunnella samaa telemetriaa ohjatakseen kastelujärjestelmää.

### Tehtävä - lisää ajoitus kasvien ohjauspalvelimeen

Päivitä palvelinkoodisi käynnistämään rele 5 sekunniksi ja odottamaan sitten 20 sekuntia.

1. Avaa `soil-moisture-sensor-server`-kansio VS Codessa, jos se ei ole jo auki. Varmista, että virtuaaliympäristö on aktivoitu.

1. Avaa `app.py`-tiedosto

1. Lisää seuraava koodi `app.py`-tiedostoon olemassa olevien tuontien alle:

    ```python
    import threading
    ```

    Tämä lause tuo Python-kirjastoista `threading`-moduulin, joka mahdollistaa Pythonin suorittamaan muuta koodia odotuksen aikana.

1. Lisää seuraava koodi ennen `handle_telemetry`-funktiota, joka käsittelee palvelinkoodin vastaanottamia telemetriaviestejä:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Tämä määrittää, kuinka kauan releen tulisi olla päällä (`water_time`) ja kuinka kauan odottaa sen jälkeen kosteustasojen tarkistamista (`wait_time`).

1. Lisää tämän koodin alle seuraava:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Tämä koodi määrittää funktion nimeltä `send_relay_command`, joka lähettää MQTT-komennon releen ohjaamiseksi. Telemetria luodaan sanakirjana ja muunnetaan JSON-merkkijonoksi. `state`-parametri määrittää, pitäisikö releen olla päällä vai pois päältä.

1. Lisää `send_relay_code`-funktion jälkeen seuraava koodi:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Tämä määrittää funktion releen ohjaamiseksi vaaditun ajoituksen perusteella. Se alkaa peruuttamalla telemetrian tilauksen, jotta maaperän kosteustasoviestejä ei käsitellä kastelun aikana. Seuraavaksi se lähettää komennon releen käynnistämiseksi. Sitten se odottaa `water_time`-ajan ennen kuin lähettää komennon releen sammuttamiseksi. Lopuksi se odottaa maaperän kosteustasojen vakiintumista `wait_time` sekuntia. Lopuksi se tilaa telemetrian uudelleen.

1. Muuta `handle_telemetry`-funktio seuraavaksi:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Tämä koodi tarkistaa maaperän kosteustason. Jos se on yli 450, maaperä tarvitsee kastelua, joten se kutsuu `control_relay`-funktion. Tämä funktio suoritetaan erillisessä säikeessä, joka toimii taustalla.

1. Varmista, että IoT-laitteesi on käynnissä, ja suorita tämä koodi. Muuta maaperän kosteustasoja ja tarkkaile, mitä releelle tapahtuu - sen pitäisi käynnistyä 5 sekunniksi ja pysyä pois päältä vähintään 20 sekuntia, käynnistyen vain, jos maaperän kosteustasot eivät ole riittävät.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Hyvä tapa testata tätä simuloidussa kastelujärjestelmässä on käyttää kuivaa maaperää ja kaataa vettä manuaalisesti releen ollessa päällä, lopettaen kaatamisen, kun rele sammuu.

> 💁 Löydät tämän koodin [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing)-kansiosta.

> 💁 Jos haluat käyttää pumppua rakentaaksesi oikean kastelujärjestelmän, voit käyttää [6V vesipumppua](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) ja [USB-virtalähdettä](https://www.adafruit.com/product/3628). Varmista, että pumpun virta on kytketty releen kautta.

---

## 🚀 Haaste

Voitko keksiä muita IoT- tai sähköisiä laitteita, joissa on samanlainen ongelma, että toimilaitteen vaikutusten saavuttaminen anturiin kestää hetken? Sinulla on todennäköisesti muutama kotona tai koulussa.

* Mitä ominaisuuksia ne mittaavat?
* Kuinka kauan kestää, että ominaisuus muuttuu toimilaitteen käytön jälkeen?
* Onko ok, että ominaisuus muuttuu vaaditun arvon ohi?
* Kuinka se voidaan palauttaa takaisin vaadittuun arvoon, jos tarpeen?

## Luentojälkeinen kysely

[Luentojälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Kertaus ja itseopiskelu

* Lue lisää releistä, mukaan lukien niiden historiallinen käyttö puhelinkeskuksissa, [rele Wikipedia-sivulta](https://wikipedia.org/wiki/Relay).

## Tehtävä

[Rakenna tehokkaampi kastelusykli](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.