# Johdanto IoT:hen

![Tämän oppitunnin sketchnote-yhteenveto](../../../../../translated_images/fi/lesson-1.2606670fa61ee904.webp)

> Sketchnoten on tehnyt [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä oppitunti oli osa [Hello IoT -sarjaa](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) [Microsoft Reactorilta](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Oppitunti koostui kahdesta videosta: tunnin mittaisesta oppitunnista ja tunnin mittaisesta toimistotunnista, jossa syvennyttiin oppitunnin osiin ja vastattiin kysymyksiin.

[![Oppitunti 1: Johdanto IoT:hen](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Oppitunti 1: Johdanto IoT:hen - Toimistotunti](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klikkaa yllä olevia kuvia katsoaksesi videot

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Johdanto

Tässä oppitunnissa käsitellään joitakin Internet of Thingsin (IoT) perusaiheita ja opastetaan laitteiston käyttöönotossa.

Tässä oppitunnissa käsitellään:

* [Mikä on 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT-laitteet](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Laitteen käyttöönotto](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT:n sovellukset](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Esimerkkejä IoT-laitteista ympärilläsi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Mikä on 'Internet of Things'?

Termi 'Internet of Things' (IoT) lanseerattiin vuonna 1999 [Kevin Ashtonin](https://wikipedia.org/wiki/Kevin_Ashton) toimesta, ja sillä viitattiin Internetin yhdistämiseen fyysiseen maailmaan sensoreiden avulla. Sittemmin termiä on käytetty kuvaamaan mitä tahansa laitetta, joka on vuorovaikutuksessa ympäröivän fyysisen maailman kanssa joko keräämällä tietoa sensoreilla tai tarjoamalla reaalimaailman toimintoja aktuaattoreilla (laitteilla, jotka tekevät jotain, kuten kytkevät kytkimen päälle tai sytyttävät LEDin), yleensä yhteydessä muihin laitteisiin tai Internetiin.

> **Sensorit** keräävät tietoa maailmasta, kuten mittaavat nopeutta, lämpötilaa tai sijaintia.
>
> **Aktuaattorit** muuntavat sähköiset signaalit reaalimaailman toiminnoiksi, kuten kytkimen laukaisemiseksi, valojen sytyttämiseksi, äänten tuottamiseksi tai ohjaussignaalien lähettämiseksi muille laitteille, esimerkiksi pistorasian kytkemiseksi päälle.

IoT on enemmän kuin vain laitteita - siihen kuuluu pilvipohjaisia palveluita, jotka voivat käsitellä sensoritietoja tai lähettää pyyntöjä IoT-laitteisiin kytketyille aktuaattoreille. Se sisältää myös laitteita, joilla ei ole tai jotka eivät tarvitse Internet-yhteyttä, ja joita kutsutaan usein reunalaitteiksi. Nämä laitteet voivat käsitellä ja vastata sensoritietoihin itsenäisesti, yleensä pilvessä koulutettujen tekoälymallien avulla.

IoT on nopeasti kasvava teknologia-alue. Arvioiden mukaan vuoden 2020 loppuun mennessä oli otettu käyttöön ja yhdistetty Internetiin 30 miljardia IoT-laitetta. Tulevaisuudessa arvioidaan, että vuoteen 2025 mennessä IoT-laitteet keräävät lähes 80 zettatavua dataa eli 80 biljoonaa gigatavua. Se on valtava määrä dataa!

![Kaavio, joka näyttää aktiivisten IoT-laitteiden määrän kasvun ajan myötä, alle 5 miljardista vuonna 2015 yli 30 miljardiin vuonna 2025](../../../../../images/connected-iot-devices.svg)

✅ Tee hieman tutkimusta: Kuinka suuri osa IoT-laitteiden tuottamasta datasta todella käytetään, ja kuinka paljon menee hukkaan? Miksi niin paljon dataa jätetään huomiotta?

Tämä data on avain IoT:n menestykseen. Jotta voisit olla menestyksekäs IoT-kehittäjä, sinun täytyy ymmärtää, mitä dataa sinun täytyy kerätä, miten kerätä sitä, miten tehdä päätöksiä sen perusteella ja miten käyttää näitä päätöksiä vuorovaikutuksessa fyysisen maailman kanssa tarvittaessa.

## IoT-laitteet

IoT:n **T** tarkoittaa **Things** eli laitteita, jotka ovat vuorovaikutuksessa ympäröivän fyysisen maailman kanssa joko keräämällä tietoa sensoreilla tai tarjoamalla reaalimaailman toimintoja aktuaattoreilla.

Tuotanto- tai kaupalliseen käyttöön tarkoitetut laitteet, kuten kuluttajien kuntoseurantalaitteet tai teollisuuden koneiden ohjaimet, ovat yleensä räätälöityjä. Ne käyttävät räätälöityjä piirilevyjä, mahdollisesti jopa räätälöityjä prosessoreita, jotka on suunniteltu vastaamaan tietyn tehtävän tarpeita, olipa kyseessä sitten riittävän pieni koko ranteeseen sopimiseksi tai kestävyys korkeassa lämpötilassa, kovassa rasituksessa tai tärinässä tehtaassa.

Kehittäjänä, joka joko opettelee IoT:ta tai luo laitteen prototyyppiä, sinun täytyy aloittaa kehityspaketilla. Nämä ovat yleiskäyttöisiä IoT-laitteita, jotka on suunniteltu kehittäjien käyttöön, ja niissä on usein ominaisuuksia, joita tuotantolaitteessa ei olisi, kuten ulkoisia liittimiä sensoreiden tai aktuaattoreiden kytkemiseksi, laitteistoa virheenkorjaukseen tai lisäresursseja, jotka lisäisivät tarpeettomia kustannuksia suurissa valmistuserissä.

Nämä kehityspaketit jakautuvat yleensä kahteen kategoriaan - mikrokontrollereihin ja yhden piirilevyn tietokoneisiin. Näitä esitellään tässä, ja seuraavassa oppitunnissa mennään yksityiskohtaisemmin.

> 💁 Puhelintasi voidaan myös pitää yleiskäyttöisenä IoT-laitteena, jossa on sisäänrakennettuja sensoreita ja aktuaattoreita. Eri sovellukset käyttävät näitä sensoreita ja aktuaattoreita eri tavoin eri pilvipalveluiden kanssa. Löydät jopa IoT-opetusohjelmia, joissa käytetään puhelinsovellusta IoT-laitteena.

### Mikrokontrollerit

Mikrokontrolleri (tunnetaan myös nimellä MCU, lyhenne sanoista microcontroller unit) on pieni tietokone, joka koostuu:

🧠 Yhdestä tai useammasta keskusyksiköstä (CPU) - mikrokontrollerin "aivot", jotka suorittavat ohjelmasi

💾 Muistista (RAM ja ohjelmamuisti) - paikka, jossa ohjelmasi, datasi ja muuttujasi säilytetään

🔌 Ohjelmoitavista tulo-/lähtöliitännöistä (I/O) - ulkoisten oheislaitteiden (kuten sensoreiden ja aktuaattoreiden) kanssa kommunikointiin

Mikrokontrollerit ovat tyypillisesti edullisia laskentalaitteita, joiden keskimääräiset hinnat mukautetussa laitteistossa ovat noin 0,50 USD, ja jotkut laitteet maksavat vain 0,03 USD. Kehityspaketit voivat maksaa alkaen 4 USD, ja hinnat nousevat ominaisuuksien lisääntyessä. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), mikrokontrollerikehityspaketti [Seeed Studiosilta](https://www.seeedstudio.com), jossa on sensoreita, aktuaattoreita, WiFi ja näyttö, maksaa noin 30 USD.

![Wio Terminal](../../../../../translated_images/fi/wio-terminal.b8299ee16587db9a.webp)

> 💁 Kun etsit mikrokontrollereita Internetistä, ole varovainen hakusanalla **MCU**, sillä se tuo paljon tuloksia Marvelin elokuvauniversumista, ei mikrokontrollereista.

Mikrokontrollerit on suunniteltu ohjelmoitaviksi suorittamaan rajallinen määrä hyvin spesifisiä tehtäviä, eikä niitä ole tarkoitettu yleiskäyttöisiksi tietokoneiksi kuten PC:t tai Macit. Paitsi hyvin erityisissä tilanteissa, et voi liittää niihin näyttöä, näppäimistöä ja hiirtä ja käyttää niitä yleiskäyttöisiin tehtäviin.

Mikrokontrollerikehityspaketeissa on yleensä mukana lisäsensoreita ja aktuaattoreita. Useimmissa korteissa on yksi tai useampi ohjelmoitava LED sekä muita laitteita, kuten standardiliittimiä lisäsensoreiden tai aktuaattoreiden liittämiseen eri valmistajien ekosysteemeihin tai sisäänrakennettuja sensoreita (yleensä suosituimpia, kuten lämpötila-antureita). Joissakin mikrokontrollereissa on sisäänrakennettu langaton yhteys, kuten Bluetooth tai WiFi, tai lisämikrokontrollereita, jotka lisäävät tämän yhteyden.

> 💁 Mikrokontrollereita ohjelmoidaan yleensä C/C++-kielellä.

### Yhden piirilevyn tietokoneet

Yhden piirilevyn tietokone on pieni laskentalaite, joka sisältää kaikki täysimittaisen tietokoneen osat yhdellä pienellä piirilevyllä. Nämä laitteet ovat ominaisuuksiltaan lähellä pöytätietokonetta tai kannettavaa, käyttävät täysimittaista käyttöjärjestelmää, mutta ovat pienempiä, kuluttavat vähemmän virtaa ja ovat huomattavasti halvempia.

![Raspberry Pi 4](../../../../../translated_images/fi/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi on yksi suosituimmista yhden piirilevyn tietokoneista.

Kuten mikrokontrollerit, yhden piirilevyn tietokoneissa on CPU, muisti ja tulo-/lähtöliitännät, mutta niissä on myös lisäominaisuuksia, kuten grafiikkapiiri näyttöjen liittämiseen, äänilähdöt ja USB-portit näppäimistöjen, hiirien ja muiden standardien USB-laitteiden, kuten verkkokameroiden tai ulkoisten tallennuslaitteiden, liittämiseen. Ohjelmat tallennetaan SD-korteille tai kiintolevyille käyttöjärjestelmän kanssa, eikä piirilevyyn sisäänrakennettuun muistiin.

> 🎓 Voit ajatella yhden piirilevyn tietokonetta pienempänä, halvempana versiona PC:stä tai Macista, jolla luet tätä, ja jolla on lisäksi GPIO (yleiskäyttöiset tulo-/lähtöliitännät) sensoreiden ja aktuaattoreiden kanssa vuorovaikutukseen.

Yhden piirilevyn tietokoneet ovat täysimittaisia tietokoneita, joten niitä voidaan ohjelmoida millä tahansa kielellä. IoT-laitteita ohjelmoidaan tyypillisesti Pythonilla.

### Laitteistovalinnat loppuoppitunneille

Kaikki seuraavat oppitunnit sisältävät tehtäviä, joissa käytetään IoT-laitetta vuorovaikutukseen fyysisen maailman kanssa ja kommunikointiin pilven kanssa. Jokainen oppitunti tukee kolmea laitevalintaa - Arduino (käyttäen Seeed Studiosin Wio Terminalia) tai yhden piirilevyn tietokonetta, joko fyysistä laitetta (Raspberry Pi 4) tai virtuaalista yhden piirilevyn tietokonetta, joka toimii PC:llä tai Macilla.

Voit lukea tarvittavasta laitteistosta kaikkien tehtävien suorittamiseksi [laitteisto-oppaasta](../../../hardware.md).

> 💁 Sinun ei tarvitse ostaa mitään IoT-laitteistoa tehtävien suorittamiseksi, voit tehdä kaiken virtuaalisella yhden piirilevyn tietokoneella.

Minkä laitteiston valitset, riippuu siitä, mitä sinulla on saatavilla kotona tai koulussa, ja mitä ohjelmointikieltä osaat tai haluat oppia. Molemmat laitevaihtoehdot käyttävät samaa sensoriekosysteemiä, joten jos aloitat yhdellä polulla, voit vaihtaa toiseen ilman, että suurin osa laitteistosta täytyy korvata. Virtuaalinen yhden piirilevyn tietokone vastaa oppimista Raspberry Pi:llä, ja suurin osa koodista on siirrettävissä Pi:lle, jos hankit laitteen ja sensorit myöhemmin.

### Arduino-kehityspaketti

Jos olet kiinnostunut oppimaan mikrokontrollerikehitystä, voit suorittaa tehtävät Arduino-laitteella. Sinun täytyy ymmärtää perusteet C/C++-ohjelmoinnista, sillä oppitunnit opettavat vain koodia, joka liittyy Arduino-kehykseen, käytettäviin sensoreihin ja aktuaattoreihin sekä pilven kanssa vuorovaikuttaviin kirjastoihin.

Tehtävissä käytetään [Visual Studio Codea](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) ja [PlatformIO-laajennusta mikrokontrollerikehitykseen](https://platformio.org). Voit myös käyttää Arduino IDE:tä, jos olet kokenut tämän työkalun käyttäjä, sillä ohjeita ei anneta.

### Yhden piirilevyn tietokoneen kehityspaketti

Jos olet kiinnostunut oppimaan IoT-kehitystä yhden piirilevyn tietokoneilla, voit suorittaa tehtävät Raspberry Pi:llä tai virtuaalisella laitteella, joka toimii PC:llä tai Macilla.

Sinun täytyy ymmärtää Python-ohjelmoinnin perusteet, sillä oppitunnit opettavat vain koodia, joka liittyy käytettäviin sensoreihin ja aktuaattoreihin sekä pilven kanssa vuorovaikuttaviin kirjastoihin.

> 💁 Jos haluat oppia Python-ohjelmointia, tutustu seuraaviin kahteen videosarjaan:
>
> * [Python aloittelijoille](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Lisää Pythonia aloittelijoille](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Tehtävissä käytetään [Visual Studio Codea](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Jos käytät Raspberry Pi:tä, voit joko käyttää Pi:täsi täysimittaisella Raspberry Pi OS -työpöytäversiolla ja tehdä kaiken koodauksen suoraan Pi:llä käyttäen [Raspberry Pi OS -versiota VS Codesta](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), tai käyttää Pi:täsi päätelaitteena ja koodata PC:ltäsi tai Maciltasi käyttäen VS Codea ja [Remote SSH -laajennusta](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), joka mahdollistaa yhteyden Pi:hin ja koodin muokkaamisen, virheenkorjauksen ja suorittamisen aivan kuin koodaisit suoraan sillä.

Jos käytät virtuaalilaitetta, koodaat suoraan tietokoneellasi. Sensoreiden ja aktuaattoreiden sijaan käytät työkalua, joka simuloi tätä laitteistoa tarjoamalla sensoriarvoja, jotka voit määrittää, ja näyttämällä aktuaattoreiden tulokset näytöllä.

## Laitteen käyttöönotto

Ennen kuin voit aloittaa IoT-laitteesi ohjelmoinnin, sinun täytyy tehdä pieni määrä asetuksia. Seuraa alla olevia ohjeita riippuen siitä, mitä laitetta käytät.
💁 Jos sinulla ei vielä ole laitetta, tutustu [laitteisto-oppaaseen](../../../hardware.md) auttaaksesi päättämään, mitä laitetta aiot käyttää ja mitä lisälaitteita sinun täytyy hankkia. Sinun ei tarvitse ostaa laitteistoa, sillä kaikki projektit voidaan suorittaa virtuaalisella laitteistolla.
Nämä ohjeet sisältävät linkkejä kolmansien osapuolien verkkosivustoille, jotka ovat laitteiden tai työkalujen valmistajien luomia. Tämä varmistaa, että käytät aina ajantasaisimpia ohjeita eri työkaluille ja laitteille.

Käy läpi asiaankuuluva opas asentaaksesi laitteesi ja suorittaaksesi "Hello World" -projektin. Tämä on ensimmäinen askel IoT-yövalon luomisessa neljän oppitunnin aikana tässä aloitusosiossa.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Yksikorttitietokone - Raspberry Pi](pi.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device.md)

✅ Käytät VS Codea sekä Arduinolle että yksikorttitietokoneille. Jos et ole käyttänyt sitä aiemmin, lue lisää [VS Code -sivustolta](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## IoT:n sovellukset

IoT kattaa valtavan määrän käyttötapauksia, jotka jakautuvat muutamaan laajaan ryhmään:

* Kuluttaja-IoT
* Kaupallinen IoT
* Teollinen IoT
* Infrastruktuuri-IoT

✅ Tee hieman tutkimusta: Etsi jokaiselle alla kuvatulle alueelle yksi konkreettinen esimerkki, jota ei ole mainittu tekstissä.

### Kuluttaja-IoT

Kuluttaja-IoT viittaa IoT-laitteisiin, joita kuluttajat ostavat ja käyttävät kotonaan. Jotkut näistä laitteista ovat erittäin hyödyllisiä, kuten älykaiuttimet, älylämmitysjärjestelmät ja robottipölynimurit. Toiset taas ovat kyseenalaisia hyödyllisyydessään, kuten ääniohjatut hanat, joita ei voi sulkea, koska ääniohjaus ei kuule sinua juoksevan veden äänen yli.

Kuluttaja-IoT-laitteet antavat ihmisille mahdollisuuden saavuttaa enemmän ympäristössään, erityisesti miljardille ihmiselle, joilla on jokin vamma. Robottipölynimurit voivat tarjota puhtaat lattiat liikuntarajoitteisille, jotka eivät voi imuroida itse, ääniohjatut uunit mahdollistavat näkö- tai motoriikkarajoitteisille uunin lämmittämisen pelkällä äänellä, ja terveydenseurantalaitteet antavat potilaille mahdollisuuden seurata kroonisia sairauksiaan säännöllisemmin ja yksityiskohtaisemmin. Nämä laitteet ovat niin yleisiä, että jopa pienet lapset käyttävät niitä osana päivittäistä elämäänsä, esimerkiksi virtuaalikoulutusta käyvät oppilaat COVID-pandemian aikana asettavat ajastimia älykotilaitteilla seuratakseen koulutehtäviään tai muistutuksia tulevista oppitunneista.

✅ Mitä kuluttaja-IoT-laitteita sinulla on kotonasi tai mukanasi?

### Kaupallinen IoT

Kaupallinen IoT kattaa IoT:n käytön työpaikoilla. Toimistoympäristössä voi olla tilan käyttöä mittaavia sensoreita ja liiketunnistimia, jotka hallitsevat valaistusta ja lämmitystä niin, että valot ja lämpö ovat päällä vain tarvittaessa, mikä vähentää kustannuksia ja hiilidioksidipäästöjä. Tehtaassa IoT-laitteet voivat valvoa turvallisuusriskejä, kuten työntekijöitä, jotka eivät käytä kypärää, tai melua, joka on saavuttanut vaarallisen tason. Kaupan alalla IoT-laitteet voivat mitata kylmäsäilytyksen lämpötilaa ja ilmoittaa kaupan omistajalle, jos jääkaappi tai pakastin on vaaditun lämpötila-alueen ulkopuolella, tai ne voivat seurata hyllyjen tuotteita ohjaten työntekijöitä täyttämään myytyjä tuotteita. Kuljetusalalla IoT:ta käytetään yhä enemmän ajoneuvojen sijainnin seuraamiseen, tienkäyttömaksujen kilometriseurantaan, kuljettajien työaikojen ja taukojen noudattamisen valvontaan tai henkilökunnan ilmoittamiseen, kun ajoneuvo lähestyy terminaalia lastausta tai purkua varten.

✅ Mitä kaupallisia IoT-laitteita sinulla on koulussasi tai työpaikallasi?

### Teollinen IoT (IIoT)

Teollinen IoT, eli IIoT, tarkoittaa IoT-laitteiden käyttöä koneiden hallintaan ja ohjaukseen suuressa mittakaavassa. Tämä kattaa laajan valikoiman käyttötapauksia, tehtaista digitaaliseen maatalouteen.

Tehtaissa IoT-laitteita käytetään monin eri tavoin. Koneita voidaan valvoa useilla sensoreilla, jotka seuraavat esimerkiksi lämpötilaa, värähtelyä ja pyörimisnopeutta. Näitä tietoja voidaan valvoa, jotta kone voidaan pysäyttää, jos se ylittää tietyt toleranssit - esimerkiksi jos se käy liian kuumana, se voidaan sammuttaa. Näitä tietoja voidaan myös kerätä ja analysoida ajan mittaan ennakoivaa huoltoa varten, jossa tekoälymallit tarkastelevat tietoja, jotka johtavat vikaantumiseen, ja käyttävät niitä ennustamaan muita vikoja ennen niiden tapahtumista.

Digitaalinen maatalous on tärkeää, jotta planeetta pystyy ruokkimaan kasvavan väestön, erityisesti 2 miljardia ihmistä 500 miljoonassa kotitaloudessa, jotka elävät [omavaraisviljelyllä](https://wikipedia.org/wiki/Subsistence_agriculture). Digitaalinen maatalous voi vaihdella muutaman dollarin sensoreista massiivisiin kaupallisiin järjestelmiin. Viljelijä voi aloittaa seuraamalla lämpötiloja ja käyttämällä [kasvupäiväasteita](https://wikipedia.org/wiki/Growing_degree-day) ennustaakseen, milloin sato on valmis korjattavaksi. He voivat yhdistää maaperän kosteuden seurannan automatisoituihin kastelujärjestelmiin antaakseen kasveilleen juuri tarvittavan määrän vettä, mutta ei enempää, jotta heidän satonsa eivät kuivu ilman veden tuhlausta. Viljelijät menevät jopa pidemmälle ja käyttävät droneja, satelliittidataa ja tekoälyä valvoakseen sadon kasvua, sairauksia ja maaperän laatua valtavilla viljelyalueilla.

✅ Mitä muita IoT-laitteita voisi auttaa viljelijöitä?

### Infrastruktuuri-IoT

Infrastruktuuri-IoT tarkoittaa paikallisen ja globaalin infrastruktuurin valvontaa ja hallintaa, jota ihmiset käyttävät päivittäin.

[Älykaupungit](https://wikipedia.org/wiki/Smart_city) ovat kaupunkialueita, jotka käyttävät IoT-laitteita kerätäkseen tietoa kaupungista ja käyttävät sitä kaupungin toiminnan parantamiseen. Näitä kaupunkeja hallinnoidaan yleensä paikallishallinnon, akateemisten tahojen ja paikallisten yritysten yhteistyönä, ja niissä seurataan ja hallitaan asioita, kuten liikennettä, pysäköintiä ja saastumista. Esimerkiksi Kööpenhaminassa, Tanskassa, ilman saastuminen on tärkeää paikallisille asukkaille, joten sitä mitataan ja tietoja käytetään tarjoamaan tietoa puhtaimmista pyöräily- ja lenkkeilyreiteistä.

[Älykkäät sähköverkot](https://wikipedia.org/wiki/Smart_grid) mahdollistavat paremman analytiikan sähkönkulutuksesta keräämällä käyttödataa yksittäisten kotien tasolla. Näitä tietoja voidaan käyttää päätöksentekoon maanlaajuisesti, kuten uusien voimalaitosten rakentamispaikkojen valintaan, ja henkilökohtaisella tasolla antamalla käyttäjille tietoa siitä, kuinka paljon sähköä he käyttävät, milloin he käyttävät sitä, ja jopa ehdotuksia kustannusten vähentämiseksi, kuten sähköautojen lataaminen yöllä.

✅ Jos voisit lisätä IoT-laitteita mittaamaan mitä tahansa asuinalueellasi, mitä se olisi?

## Esimerkkejä IoT-laitteista, joita sinulla saattaa olla ympärilläsi

Olisit yllättynyt siitä, kuinka monta IoT-laitetta sinulla on ympärilläsi. Kirjoitan tätä kotona, ja minulla on seuraavat laitteet yhdistettynä Internetiin älyominaisuuksilla, kuten sovellusten ohjaus, ääniohjaus tai kyky lähettää tietoja puhelimeeni:

* Useita älykaiuttimia
* Jääkaappi, astianpesukone, uuni ja mikroaaltouuni
* Sähkömittari aurinkopaneeleille
* Älypistorasiat
* Videokello ja turvakamerat
* Älytermostaatti, jossa on useita älyhuonesensoreita
* Autotallin oven avaaja
* Kodin viihdejärjestelmät ja ääniohjatut televisiot
* Valot
* Kunto- ja terveydenseurantalaitteet

Kaikilla näillä laitteilla on sensoreita ja/tai toimilaitteita, ja ne kommunikoivat Internetin kautta. Voin tarkistaa puhelimestani, onko autotallin ovi auki, ja pyytää älykaiutinta sulkemaan sen puolestani. Voin jopa asettaa sen ajastimelle, jotta jos se on vielä auki yöllä, se sulkeutuu automaattisesti. Kun ovikello soi, voin nähdä puhelimestani, kuka siellä on, missä tahansa olenkin maailmassa, ja puhua heille ovikelloon sisäänrakennetun kaiuttimen ja mikrofonin kautta. Voin seurata verensokeriani, sydämen sykettäni ja uneni laatua, etsiä datasta kaavoja parantaakseni terveyttäni. Voin ohjata valojani pilven kautta ja istua pimeässä, kun Internet-yhteys katkeaa.

---

## 🚀 Haaste

Listaa niin monta IoT-laitetta kuin voit, jotka ovat kotonasi, koulussasi tai työpaikallasi - niitä saattaa olla enemmän kuin luulet!

## Luentojälkeinen kysely

[Luentojälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Kertaus ja itseopiskelu

Lue kuluttaja-IoT-projektien hyödyistä ja epäonnistumisista. Tarkista uutissivustoilta artikkeleita siitä, milloin ne ovat menneet pieleen, kuten yksityisyysongelmat, laitteisto-ongelmat tai ongelmat, jotka johtuvat yhteyden puutteesta.

Joistakin esimerkkejä:

* Katso Twitter-tili **[Internet of Sh*t](https://twitter.com/internetofshit)** *(varoitus: kielenkäyttö)*, jossa on hyviä esimerkkejä kuluttaja-IoT:n epäonnistumisista.
* [c|net - Apple Watch pelasti henkeni: 5 ihmistä jakaa tarinansa](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT-teknikko myöntää syyllisyytensä asiakkaiden kamerasyötteiden vakoiluun vuosien ajan](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(varoitus: ei-toivottu voyeurismi)*

## Tehtävä

[Tutki IoT-projektia](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.