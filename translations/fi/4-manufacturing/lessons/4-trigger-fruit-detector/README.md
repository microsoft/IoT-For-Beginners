<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T20:53:00+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "fi"
}
-->
# Käynnistä hedelmien laadunvalvonta sensorista

![Tämän oppitunnin yleiskuvaus sketchnotena](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.fi.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Johdanto

IoT-sovellus ei ole vain yksittäinen laite, joka kerää dataa ja lähettää sen pilveen. Useimmiten kyseessä on useiden laitteiden kokonaisuus, jotka yhdessä keräävät dataa fyysisestä maailmasta sensoreiden avulla, tekevät päätöksiä tämän datan perusteella ja vuorovaikuttavat takaisin fyysisen maailman kanssa toimilaitteiden tai visualisointien kautta.

Tässä oppitunnissa opit lisää monimutkaisten IoT-sovellusten suunnittelusta, useiden sensoreiden ja pilvipalveluiden integroinnista datan analysointiin ja tallentamiseen sekä vastauksen näyttämisestä toimilaitteen avulla. Opit myös, miten suunnitella hedelmien laadunvalvontajärjestelmän prototyyppi, mukaan lukien läheisyysantureiden käyttö IoT-sovelluksen käynnistämiseen, ja millainen tämän prototyypin arkkitehtuuri olisi.

Tässä oppitunnissa käsitellään:

* [Monimutkaisten IoT-sovellusten suunnittelu](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Hedelmälaadunvalvontajärjestelmän suunnittelu](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Hedelmälaadun tarkistuksen käynnistäminen sensorista](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Hedelmälaadun tarkistimessa käytetty data](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Kehittäjälaitteiden käyttö useiden IoT-laitteiden simulointiin](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Siirtyminen tuotantoon](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Tämä on projektin viimeinen oppitunti, joten tämän oppitunnin ja tehtävän suorittamisen jälkeen muista siivota pilvipalvelusi. Tarvitset palveluita tehtävän suorittamiseen, joten varmista, että suoritat sen ensin.
>
> Katso tarvittaessa [ohjeet projektin siivoamiseen](../../../clean-up.md).

## Monimutkaisten IoT-sovellusten suunnittelu

IoT-sovellukset koostuvat monista komponenteista. Näihin kuuluu erilaisia laitteita ja internet-palveluita.

IoT-sovelluksia voidaan kuvata *asioina* (laitteet), jotka lähettävät dataa, joka tuottaa *oivalluksia*. Nämä *oivallukset* johtavat *toimiin*, jotka parantavat liiketoimintaa tai prosessia. Esimerkkinä moottori (*asia*), joka lähettää lämpötiladataa. Tätä dataa käytetään arvioimaan, toimiiko moottori odotetusti (*oivallus*). Oivalluksen perusteella priorisoidaan moottorin huoltoaikataulu (*toimi*).

* Eri laitteet keräävät erilaisia datan osia.
* IoT-palvelut tuottavat oivalluksia datasta, joskus täydentäen sitä lisälähteistä saadulla datalla.
* Nämä oivallukset johtavat toimiin, kuten toimilaitteiden ohjaamiseen tai datan visualisointiin.

### Viitearkkitehtuuri IoT-sovelluksille

![Viitearkkitehtuuri IoT-sovelluksille](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.fi.png)

Yllä oleva kaavio esittää viitearkkitehtuurin IoT-sovelluksille.

> 🎓 *Viitearkkitehtuuri* on esimerkkiarkkitehtuuri, jota voit käyttää mallina uusien järjestelmien suunnittelussa. Tässä tapauksessa, jos rakennat uutta IoT-järjestelmää, voit seurata viitearkkitehtuuria ja korvata omat laitteesi ja palvelusi sopivilla osilla.

* **Asiat** ovat laitteita, jotka keräävät dataa sensoreista ja mahdollisesti tulkitsevat sitä reunapalveluiden avulla, kuten kuvantunnistimilla. Laitteiden data lähetetään IoT-palveluun.
* **Oivallukset** syntyvät palveluttomista sovelluksista tai analytiikasta, joka suoritetaan tallennetulle datalle.
* **Toimet** voivat olla komentoja, jotka lähetetään laitteille, tai datan visualisointia, joka mahdollistaa päätöksenteon ihmisille.

![Viitearkkitehtuuri Azure IoT:lle](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.fi.png)

Yllä oleva kaavio näyttää joitakin näissä oppitunneissa käsiteltyjä komponentteja ja palveluita sekä niiden yhteydet viitearkkitehtuurissa.

* **Asiat** - olet kirjoittanut laiteohjelmistoa datan keräämiseen sensoreista ja analysoinut kuvia Custom Vision -palvelun avulla sekä pilvessä että reunalaitteella. Tämä data lähetettiin IoT Hubiin.
* **Oivallukset** - olet käyttänyt Azure Functions -toimintoja vastaamaan IoT Hubiin lähetettyihin viesteihin ja tallentanut dataa myöhempää analysointia varten Azure Storageen.
* **Toimet** - olet ohjannut toimilaitteita pilvessä tehtyjen päätösten ja laitteille lähetettyjen komentojen perusteella sekä visualisoinut dataa Azure Mapsin avulla.

✅ Mieti muita käyttämiäsi IoT-laitteita, kuten älykotilaitteita. Mitkä ovat näiden laitteiden asiat, oivallukset ja toimet?

Tätä mallia voidaan laajentaa tarpeen mukaan lisäämällä laitteita ja palveluita.

### Data ja turvallisuus

Kun määrittelet järjestelmäsi arkkitehtuuria, sinun on jatkuvasti otettava huomioon data ja turvallisuus.

* Mitä dataa laitteesi lähettää ja vastaanottaa?
* Miten tämä data tulisi suojata ja turvata?
* Miten laitteen ja pilvipalvelun käyttöä tulisi hallita?

✅ Mieti omistamiesi IoT-laitteiden dataturvallisuutta. Kuinka paljon tästä datasta on henkilökohtaista ja tulisi pitää yksityisenä, sekä siirron aikana että tallennettuna? Mitä dataa ei tulisi tallentaa?

## Hedelmälaadunvalvontajärjestelmän suunnittelu

Sovellamme nyt asioiden, oivallusten ja toimien ideaa hedelmälaadun tarkistimeen ja suunnittelemme laajemman end-to-end-sovelluksen.

Kuvittele, että sinulle on annettu tehtäväksi rakentaa hedelmälaadun tarkistin käytettäväksi käsittelylaitoksessa. Hedelmät kulkevat kuljetinhihnalla, jossa työntekijät tarkistavat hedelmät käsin ja poistavat kypsymättömät hedelmät. Laitoksen omistaja haluaa automatisoida tämän prosessin kustannusten vähentämiseksi.

✅ Yksi IoT:n (ja teknologian yleisesti) nousun trendeistä on, että manuaaliset työt korvataan koneilla. Tee tutkimusta: Kuinka monta työpaikkaa arvioidaan menetettävän IoT:n vuoksi? Kuinka monta uutta työpaikkaa syntyy IoT-laitteiden rakentamisen myötä?

Sinun täytyy rakentaa järjestelmä, jossa hedelmä havaitaan sen saapuessa kuljetinhihnalle, se kuvataan ja tarkistetaan reunalla toimivan tekoälymallin avulla. Tulokset lähetetään pilveen tallennettavaksi, ja jos hedelmä on kypsymätön, annetaan ilmoitus, jotta kypsymätön hedelmä voidaan poistaa.

|   |   |
| - | - |
| **Asiat** | Anturi hedelmien havaitsemiseen kuljetinhihnalla<br>Kamera hedelmien kuvaamiseen ja luokitteluun<br>Reunalaitteella toimiva luokitin<br>Laite kypsymättömien hedelmien ilmoittamiseen |
| **Oivallukset** | Päätös tarkistaa hedelmän kypsyys<br>Kypsyysluokituksen tulosten tallentaminen<br>Tarpeen määrittäminen kypsymättömien hedelmien ilmoittamiseksi |
| **Toimet** | Komennon lähettäminen laitteelle hedelmän kuvaamiseksi ja luokittelemiseksi kuvantunnistimella<br>Komennon lähettäminen laitteelle kypsymättömän hedelmän ilmoittamiseksi |

### Sovelluksen prototyyppi

![Viitearkkitehtuuri hedelmälaadun tarkistukseen](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.fi.png)

Yllä oleva kaavio esittää viitearkkitehtuurin tälle prototyyppisovellukselle.

* IoT-laite, jossa on läheisyysanturi, havaitsee hedelmän saapumisen. Tämä lähettää viestin pilveen ilmoittaen hedelmän havaitsemisesta.
* Pilvessä toimiva palveluton sovellus lähettää komennon toiselle laitteelle hedelmän kuvaamiseksi ja luokittelemiseksi.
* IoT-laite, jossa on kamera, ottaa kuvan ja lähettää sen reunalla toimivalle kuvantunnistimelle. Tulokset lähetetään pilveen.
* Pilvessä toimiva palveluton sovellus tallentaa tämän tiedon analysoitavaksi myöhemmin, jotta voidaan selvittää, kuinka suuri osa hedelmistä on kypsymättömiä. Jos hedelmä on kypsymätön, se lähettää komennon toiselle IoT-laitteelle ilmoittamaan työntekijöille kypsymättömästä hedelmästä LED-valon avulla.

> 💁 Tämä koko IoT-sovellus voitaisiin toteuttaa yhdellä laitteella, jossa kaikki logiikka kuvantunnistuksen käynnistämiseen ja LED-valon ohjaamiseen olisi sisäänrakennettu. IoT Hubia voitaisiin käyttää vain kypsymättömien hedelmien määrän seuraamiseen ja laitteen konfigurointiin. Tässä oppitunnissa sovellusta laajennetaan, jotta voidaan havainnollistaa suurten IoT-sovellusten käsitteitä.

Prototyypissä toteutat kaiken yhdellä laitteella. Jos käytät mikro-ohjainta, käytät erillistä reunalaitetta kuvantunnistimen suorittamiseen. Olet jo oppinut suurimman osan tarvittavista asioista tämän rakentamiseen.

## Hedelmälaadun tarkistuksen käynnistäminen sensorista

IoT-laitteessa tarvitaan jonkinlainen laukaisin, joka ilmoittaa, milloin hedelmä on valmis luokiteltavaksi. Yksi laukaisin voisi olla hedelmän sijainnin mittaaminen kuljetinhihnalla etäisyyden perusteella.

![Läheisyysanturit lähettävät laser- tai infrapunasäteitä kohteisiin, kuten banaaneihin, ja mittaavat ajan, joka kuluu säteen heijastumiseen takaisin](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fe.fi.png)

Läheisyysantureita voidaan käyttää mittaamaan etäisyyttä anturin ja kohteen välillä. Ne lähettävät yleensä sähkömagneettista säteilyä, kuten laser- tai infrapunasäteitä, ja havaitsevat säteilyn heijastumisen kohteesta. Aika, joka kuluu säteen lähettämisestä signaalin heijastumiseen, voidaan käyttää etäisyyden laskemiseen.

> 💁 Olet todennäköisesti käyttänyt läheisyysantureita tietämättäsi. Useimmat älypuhelimet sammuttavat näytön, kun pidät niitä korvalla, estääkseen puhelun päättymisen vahingossa korvalehdelläsi. Tämä toimii läheisyysanturin avulla, joka havaitsee kohteen lähellä näyttöä puhelun aikana ja poistaa kosketustoiminnot käytöstä, kunnes puhelin on tietyn etäisyyden päässä.

### Tehtävä - hedelmälaadun tarkistuksen käynnistäminen etäisyysanturilla

Käy läpi asiaankuuluva opas läheisyysanturin käyttämiseksi IoT-laitteellasi:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Yksikorttitietokone - Raspberry Pi](pi-proximity.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device-proximity.md)

## Hedelmälaadun tarkistimessa käytetty data

Prototyyppinen hedelmälaadun tarkistin sisältää useita toisiinsa kommunikoivia komponentteja.

![Komponentit kommunikoivat keskenään](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.fi.png)

* Läheisyysanturi mittaa etäisyyttä hedelmään ja lähettää tämän IoT Hubiin.
* Kameraa ohjaava komento lähetetään IoT Hubista kameralle.
* Kuvantunnistuksen tulokset lähetetään IoT Hubiin.
* LED-valoa ohjaava komento kypsymättömän hedelmän ilmoittamiseksi lähetetään IoT Hubista LED-laitteelle.

On hyvä määritellä näiden viestien rakenne etukäteen ennen sovelluksen rakentamista.

> 💁 Lähes jokainen kokenut kehittäjä on jossain vaiheessa uraansa käyttänyt tunteja, päiviä tai jopa viikkoja virheiden jäljittämiseen, jotka johtuvat eroista lähetetyn datan ja odotetun datan välillä.

Esimerkiksi - jos lähetät lämpötilatietoja, miten määrittelisit JSON-rakenteen? Voisit käyttää kenttää `temperature` tai yleistä lyhennettä `temp`.

```json
{
    "temperature": 20.7
}
```

verrattuna:

```json
{
    "temp": 20.7
}
```

Sinun on myös otettava huomioon yksiköt - onko lämpötila °C vai °F? Jos mittaat lämpötilaa kuluttajalaitteella ja käyttäjä vaihtaa näyttöyksiköt, sinun on varmistettava, että pilveen lähetetyt yksiköt pysyvät johdonmukaisina.

✅ Tee tutkimusta: Miten yksikköongelmat aiheuttivat 125 miljoonan dollarin Mars Climate Orbiter -luotaimen tuhoutumisen?

Mieti hedelmälaadun tarkistimen lähettämää dataa. Miten määrittelisit jokaisen viestin? Missä analysoisit datan ja tekisit päätökset siitä, mitä dataa lähetetään?

Esimerkiksi - kuvantunnistuksen käynnistäminen läheisyysanturin avulla. IoT-laite mittaa etäisyyden, mutta missä päätös tehdään? Päätetäänkö laitteessa, että hedelmä on tarpeeksi lähellä, ja lähetetäänkö viesti IoT Hubille kuvantunnistuksen käynnistämiseksi? Vai lähetetäänkö läheisyysmittaukset ja annetaan IoT Hubin päättää?

Vastaus tällaisiin kysymyksiin on - se riippuu. Jokainen käyttötapaus on erilainen, minkä vuoksi IoT-kehittäjänä sinun on ymmärrettävä rakentamasi järjestelmä, sen käyttötarkoitus ja havaittu data.

* Jos päätös tehdään IoT Hubissa, sinun on lähetettävä useita etäisyysmittauksia.
* Jos lähetät liian monta viestiä, se lisää IoT Hubin kustannuksia ja IoT-laitteiden tarvitsemaa kaistanleveyttä (erityisesti tehtaassa, jossa on miljoonia laitteita). Se voi myös hidastaa laitettasi.
* Jos päätös tehdään laitteessa, sinun on tarjottava tapa konfiguroida laite hienosäätöä varten.

## Kehittäjälaitteiden käyttö useiden IoT-laitteiden simulointiin

Prototyypin rakentamiseksi tarvitset IoT-kehityspaketin, joka toimii kuin useat laitteet, lähettäen telemetriatietoja ja vastaten komentoihin.

### Useiden IoT-laitteiden simulointi Raspberry Pi:llä tai virtuaalisella IoT-laitteella

Kun käytät yksikorttitietokonetta, kuten Raspberry Pi:tä, voit ajaa useita sovelluksia samanaikaisesti. Tämä tarkoittaa, että voit simuloida useita IoT-laitteita luomalla useita sovelluksia, yksi per 'IoT-laite'. Esimerkiksi voit toteuttaa jokaisen laitteen erillisenä Python-tiedostona ja ajaa niitä eri terminaali-istunnoissa.
> 💁 Huomaa, että jotkin laitteistot eivät toimi, kun niitä käyttää samanaikaisesti useampi sovellus.
### Simuloidaan useita laitteita mikro-ohjaimella

Mikro-ohjaimilla useiden laitteiden simulointi on monimutkaisempaa. Toisin kuin yksikorttitietokoneilla, et voi ajaa useita sovelluksia samanaikaisesti, vaan sinun täytyy sisällyttää kaikkien erillisten IoT-laitteiden logiikka yhteen sovellukseen.

Muutamia ehdotuksia prosessin helpottamiseksi:

* Luo yksi tai useampi luokka per IoT-laite – esimerkiksi luokat nimeltä `DistanceSensor`, `ClassifierCamera`, `LEDController`. Jokaisella voi olla omat `setup`- ja `loop`-metodinsa, joita pääsovelluksen `setup`- ja `loop`-funktiot kutsuvat.
* Käsittele komennot yhdessä paikassa ja ohjaa ne tarvittaessa oikeaan laiteluokkaan.
* Pääsovelluksen `loop`-funktiossa sinun täytyy ottaa huomioon kunkin laitteen ajoitus. Esimerkiksi, jos sinulla on yksi laiteluokka, joka täytyy käsitellä 10 sekunnin välein, ja toinen, joka täytyy käsitellä 1 sekunnin välein, käytä pääsovelluksen `loop`-funktiossa 1 sekunnin viivettä. Jokainen `loop`-kutsu käynnistää koodin sille laitteelle, joka täytyy käsitellä sekunnin välein, ja käytä laskuria laskemaan jokainen silmukka, käsitellen toisen laitteen, kun laskuri saavuttaa 10 (nollaa laskuri sen jälkeen).

## Siirtyminen tuotantoon

Prototyyppi muodostaa perustan lopulliselle tuotantojärjestelmälle. Joitakin eroja tuotantoon siirryttäessä ovat:

* Kestävämmät komponentit – käytetään laitteistoa, joka on suunniteltu kestämään tehtaan melua, lämpöä, tärinää ja rasitusta.
* Sisäiset viestintäyhteydet – jotkut komponentit kommunikoivat suoraan välttäen pilveen siirtymisen, lähettäen dataa pilveen vain tallennusta varten. Tämä toteutetaan tehtaan asetuksista riippuen joko suoralla viestinnällä tai ajamalla osa IoT-palvelusta reunalla käyttämällä yhdyslaitetta.
* Konfigurointivaihtoehdot – jokainen tehdas ja käyttötapaus on erilainen, joten laitteiston täytyy olla konfiguroitavissa. Esimerkiksi läheisyysanturi saattaa joutua tunnistamaan eri hedelmiä eri etäisyyksiltä. Sen sijaan, että etäisyys kovakoodattaisiin luokittelun laukaisemiseksi, haluaisit sen olevan konfiguroitavissa pilven kautta, esimerkiksi käyttämällä laiteparia.
* Automatisoitu hedelmien poisto – sen sijaan, että LED ilmoittaisi hedelmän olevan kypsymätön, automatisoidut laitteet poistaisivat sen.

✅ Tee tutkimusta: Millä muilla tavoilla tuotantolaitteet eroavat kehityssarjoista?

---

## 🚀 Haaste

Tässä oppitunnissa olet oppinut joitakin käsitteitä, jotka sinun täytyy tietää IoT-järjestelmän arkkitehtuurin suunnittelusta. Mieti aiempia projekteja. Miten ne sopivat yllä esitettyyn viitearkkitehtuuriin?

Valitse yksi tähän mennessä tehdyistä projekteista ja mieti monimutkaisemman ratkaisun suunnittelua, joka yhdistää useita ominaisuuksia projektien käsittelemien asioiden ulkopuolelta. Piirrä arkkitehtuuri ja mieti kaikkia tarvittavia laitteita ja palveluita.

Esimerkiksi – ajoneuvon seurantalaite, joka yhdistää GPS:n ja anturit, jotka seuraavat esimerkiksi lämpötiloja jäähdytetyssä kuorma-autossa, moottorin käynnistys- ja sammutusaikoja sekä kuljettajan henkilöllisyyttä. Mitkä laitteet ovat mukana, mitkä palvelut ovat mukana, mitä dataa lähetetään ja mitkä ovat turvallisuus- ja yksityisyysnäkökohdat?

## Oppitunnin jälkeinen kysely

[Oppitunnin jälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Kertaus ja itseopiskelu

* Lue lisää IoT-arkkitehtuurista [Azure IoT -viitearkkitehtuurin dokumentaatiosta Microsoft Docsissa](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Lue lisää laitepareista [IoT Hubin laiteparien käytön ja ymmärtämisen dokumentaatiosta Microsoft Docsissa](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Lue OPC-UA:sta, koneiden välisestä viestintäprotokollasta, jota käytetään teollisuusautomaatiosta [OPC-UA-sivulta Wikipediassa](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Tehtävä

[Rakenna hedelmien laadun tunnistin](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.