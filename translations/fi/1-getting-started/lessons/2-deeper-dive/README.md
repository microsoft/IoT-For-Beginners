<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-27T22:07:34+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "fi"
}
-->
# Syvällisempi katsaus IoT:hen

![Tämän oppitunnin sketchnote](../../../../../translated_images/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.fi.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä oppitunti oli osa [Hello IoT -sarjaa](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) [Microsoft Reactorilta](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Oppitunti koostui kahdesta videosta: tunnin mittaisesta oppitunnista ja tunnin mittaisesta toimistotunnista, jossa syvennyttiin oppitunnin osiin ja vastattiin kysymyksiin.

[![Oppitunti 2: Syvällisempi katsaus IoT:hen](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Oppitunti 2: Syvällisempi katsaus IoT:hen - Toimistotunti](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klikkaa yllä olevia kuvia katsoaksesi videot

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Johdanto

Tässä oppitunnissa syvennytään joihinkin edellisen oppitunnin käsitteisiin.

Tässä oppitunnissa käsitellään:

* [IoT-sovelluksen komponentit](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Syvällisempi katsaus mikrokontrollereihin](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Syvällisempi katsaus yksikorttitietokoneisiin](../../../../../1-getting-started/lessons/2-deeper-dive)

## IoT-sovelluksen komponentit

IoT-sovelluksen kaksi pääkomponenttia ovat *Internet* ja *laite*. Tarkastellaan näitä kahta komponenttia tarkemmin.

### Laite

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.fi.jpg)

IoT:n **laite**-osa viittaa laitteeseen, joka voi olla vuorovaikutuksessa fyysisen maailman kanssa. Nämä laitteet ovat yleensä pieniä, edullisia tietokoneita, jotka toimivat alhaisilla nopeuksilla ja kuluttavat vähän virtaa – esimerkiksi yksinkertaisia mikrokontrollereita, joissa on vain kilotavuja RAM-muistia (verrattuna PC:n gigatavuihin) ja jotka toimivat vain muutamilla sadoilla megahertseillä (verrattuna PC:n gigahertseihin). Ne voivat kuluttaa niin vähän virtaa, että ne voivat toimia viikkoja, kuukausia tai jopa vuosia paristoilla.

Nämä laitteet ovat vuorovaikutuksessa fyysisen maailman kanssa joko käyttämällä antureita ympäristönsä tietojen keräämiseen tai ohjaamalla ulostuloja tai toimilaitteita fyysisten muutosten tekemiseksi. Tyypillinen esimerkki on älykäs termostaatti – laite, jossa on lämpötila-anturi, tapa asettaa haluttu lämpötila, kuten säädin tai kosketusnäyttö, ja yhteys lämmitys- tai jäähdytysjärjestelmään, joka voidaan kytkeä päälle, kun havaittu lämpötila on halutun alueen ulkopuolella. Lämpötila-anturi havaitsee, että huone on liian kylmä, ja toimilaite kytkee lämmityksen päälle.

![Kaavio, jossa lämpötila ja säädin ovat IoT-laitteen syötteitä, ja lämmittimen ohjaus on ulostulo](../../../../../translated_images/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.fi.png)

IoT-laitteina voi toimia valtava määrä erilaisia laitteita, yksinkertaisista antureista yleiskäyttöisiin laitteisiin, jopa älypuhelimeesi! Älypuhelin voi käyttää antureita ympäristönsä havaitsemiseen ja toimilaitteita vuorovaikutukseen maailman kanssa – esimerkiksi GPS-anturia sijaintisi havaitsemiseen ja kaiutinta navigointiohjeiden antamiseen määränpäähän.

✅ Mieti muita järjestelmiä, joita sinulla on ympärilläsi ja jotka lukevat tietoja anturista ja käyttävät niitä päätöksentekoon. Yksi esimerkki voisi olla uunin termostaatti. Löydätkö lisää?

### Internet

IoT-sovelluksen **Internet**-osa koostuu sovelluksista, joihin IoT-laite voi yhdistää lähettääkseen ja vastaanottaakseen tietoja, sekä muista sovelluksista, jotka voivat käsitellä IoT-laitteen tietoja ja auttaa tekemään päätöksiä siitä, mitä pyyntöjä lähettää IoT-laitteen toimilaitteille.

Tyypillinen kokoonpano voisi olla jonkinlainen pilvipalvelu, johon IoT-laite yhdistää. Tämä pilvipalvelu hoitaa esimerkiksi tietoturvan, vastaanottaa viestejä IoT-laitteelta ja lähettää viestejä takaisin laitteelle. Tämä pilvipalvelu yhdistyy sitten muihin sovelluksiin, jotka voivat käsitellä tai tallentaa anturitietoja tai käyttää anturitietoja muiden järjestelmien tietojen kanssa päätöksenteossa.

Laitteet eivät myöskään aina yhdistä suoraan Internetiin WiFi- tai langallisten yhteyksien kautta. Jotkut laitteet käyttävät mesh-verkkoja keskustellakseen keskenään Bluetoothin kaltaisten teknologioiden avulla, yhdistyen keskittimen kautta, jolla on Internet-yhteys.

Esimerkkinä älykkäästä termostaatista, termostaatti yhdistyy kodin WiFi-verkon kautta pilvipalveluun. Se lähettää lämpötilatiedot tähän pilvipalveluun, josta ne tallennetaan jonkinlaiseen tietokantaan, jolloin kodinomistaja voi tarkistaa nykyiset ja aiemmat lämpötilat puhelinsovelluksella. Toinen pilvipalvelu tietää, mikä lämpötila kodinomistajaa miellyttää, ja lähettää viestejä IoT-laitteelle pilvipalvelun kautta kertoakseen lämmitysjärjestelmälle, milloin se kytketään päälle tai pois päältä.

![Kaavio, jossa lämpötila ja säädin ovat IoT-laitteen syötteitä, IoT-laite on kaksisuuntaisessa yhteydessä pilveen, joka puolestaan on kaksisuuntaisessa yhteydessä puhelimeen, ja lämmittimen ohjaus on ulostulo IoT-laitteesta](../../../../../translated_images/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.fi.png)

Älykkäämpi versio voisi käyttää pilvessä olevaa tekoälyä ja tietoja muista IoT-laitteisiin liitetyistä antureista, kuten tilan käyttöä havaitsevista antureista, sekä tietoja, kuten säätietoja ja jopa kalenteriasi, tehdäkseen päätöksiä lämpötilan asettamisesta älykkäästi. Esimerkiksi se voisi kytkeä lämmityksen pois päältä, jos kalenterisi mukaan olet lomalla, tai säätää lämmitystä huonekohtaisesti sen mukaan, mitä huoneita käytät, oppien datasta ajan myötä tarkemmaksi.

![Kaavio, jossa useita lämpötila-antureita ja säädin ovat IoT-laitteen syötteitä, IoT-laite on kaksisuuntaisessa yhteydessä pilveen, joka puolestaan on kaksisuuntaisessa yhteydessä puhelimeen, kalenteriin ja säätietopalveluun, ja lämmittimen ohjaus on ulostulo IoT-laitteesta](../../../../../translated_images/smarter-thermostat.a75855f15d2d9e63.fi.png)

✅ Mitä muita tietoja voisi käyttää tekemään Internet-yhdistetyistä termostaateista älykkäämpiä?

### IoT reunalla

Vaikka IoT:n I tarkoittaa Internetiä, näiden laitteiden ei tarvitse yhdistyä Internetiin. Joissain tapauksissa laitteet voivat yhdistyä 'reuna'-laitteisiin – yhdyskäytävä-laitteisiin, jotka toimivat paikallisessa verkossasi, jolloin voit käsitellä tietoja ilman Internet-yhteyttä. Tämä voi olla nopeampaa, kun dataa on paljon tai Internet-yhteys on hidas, mahdollistaa offline-tilan, kun Internet-yhteys ei ole mahdollinen, kuten laivalla tai humanitaarisen kriisin aikana, ja mahdollistaa tietojen yksityisyyden säilyttämisen. Jotkut laitteet sisältävät pilvityökaluilla luotua käsittelykoodia ja suorittavat sen paikallisesti kerätäkseen ja vastatakseen tietoihin ilman Internet-yhteyttä.

Yksi esimerkki tästä on älykotilaite, kuten Apple HomePod, Amazon Alexa tai Google Home, joka kuuntelee ääntäsi pilvessä koulutettujen tekoälymallien avulla, mutta suorittaa ne paikallisesti laitteessa. Nämä laitteet 'heräävät', kun tietty sana tai lause sanotaan, ja lähettävät puheesi Internetiin vain silloin. Laite lopettaa puheen lähettämisen sopivassa kohdassa, kuten kun se havaitsee tauon puheessasi. Kaikki, mitä sanot ennen laitteen herättämistä herätyssanalla, ja kaikki, mitä sanot sen jälkeen, kun laite on lopettanut kuuntelun, ei lähetetä Internetiin laitteen tarjoajalle ja pysyy näin ollen yksityisenä.

✅ Mieti muita tilanteita, joissa yksityisyys on tärkeää, joten datan käsittely olisi parempi tehdä reunalla kuin pilvessä. Vihjeenä – ajattele IoT-laitteita, joissa on kameroita tai muita kuvantamislaitteita.

### IoT-tietoturva

Kaikissa Internet-yhteyksissä tietoturva on tärkeä huomioitava asia. On vanha vitsi, että 'IoT:n S tarkoittaa tietoturvaa' – IoT:ssa ei ole S-kirjainta, mikä viittaa siihen, että se ei ole turvallinen.

IoT-laitteet yhdistyvät pilvipalveluun ja ovat näin ollen vain yhtä turvallisia kuin kyseinen pilvipalvelu – jos pilvipalvelu sallii minkä tahansa laitteen yhdistämisen, haitallisia tietoja voidaan lähettää tai virushyökkäyksiä voi tapahtua. Tällä voi olla hyvin todellisia seurauksia, koska IoT-laitteet ovat vuorovaikutuksessa ja ohjaavat muita laitteita. Esimerkiksi [Stuxnet-mato](https://wikipedia.org/wiki/Stuxnet) manipuloi sentrifugien venttiilejä vahingoittaakseen niitä. Hakkerit ovat myös hyödyntäneet [heikkoa tietoturvaa päästäkseen käsiksi vauvamonitoreihin](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) ja muihin kodin valvontalaitteisiin.

> 💁 Joskus IoT-laitteet ja reunalaitteet toimivat verkossa, joka on täysin eristetty Internetistä, jotta tiedot pysyvät yksityisinä ja turvallisina. Tätä kutsutaan [ilmarakoksi](https://wikipedia.org/wiki/Air_gap_(networking)).

## Syvällisempi katsaus mikrokontrollereihin

Edellisessä oppitunnissa esiteltiin mikrokontrollerit. Tarkastellaan niitä nyt tarkemmin.

### Suoritin (CPU)

Suoritin on mikrokontrollerin 'aivot'. Se on prosessori, joka suorittaa koodiasi ja voi lähettää ja vastaanottaa tietoja liitetyistä laitteista. Suorittimissa voi olla yksi tai useampi ydin – käytännössä yksi tai useampi prosessori, jotka voivat työskennellä yhdessä suorittaakseen koodiasi.

Suorittimet toimivat kellon avulla, joka tikittää miljoonia tai miljardeja kertoja sekunnissa. Jokainen tikki, tai sykli, synkronoi toiminnot, joita suoritin voi suorittaa. Jokaisella tikillä suoritin voi suorittaa ohjelman käskyn, kuten hakea tietoja ulkoisesta laitteesta tai suorittaa matemaattisen laskelman. Tämä säännöllinen sykli mahdollistaa kaikkien toimintojen suorittamisen ennen seuraavan käskyn käsittelyä.

Mitä nopeampi kellosykli, sitä enemmän käskyjä voidaan käsitellä sekunnissa ja sitä nopeampi suoritin on. Suorittimen nopeudet mitataan [hertseinä (Hz)](https://wikipedia.org/wiki/Hertz), joka on standardiyksikkö, jossa 1 Hz tarkoittaa yhtä sykliä tai kellotikkiä sekunnissa.

> 🎓 Suorittimen nopeudet ilmoitetaan usein MHz- tai GHz-yksiköissä. 1 MHz on 1 miljoona Hz, 1 GHz on 1 miljardi Hz.

> 💁 Suorittimet suorittavat ohjelmia käyttäen [fetch-decode-execute-sykliä](https://wikipedia.org/wiki/Instruction_cycle). Jokaisella kellotikillä suoritin hakee seuraavan käskyn muistista, dekoodaa sen ja suorittaa sen, esimerkiksi käyttämällä aritmeettis-loogista yksikköä (ALU) kahden luvun yhteenlaskuun. Jotkut suoritukset vievät useita tikkejä, joten seuraava sykli alkaa seuraavalla tikillä, kun käsky on suoritettu.

![Fetch-decode-execute-syklit, joissa fetch hakee käskyn ohjelmasta RAM-muistista, dekoodaa ja suorittaa sen suorittimessa](../../../../../translated_images/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.fi.png)

Mikrokontrollereiden kellonopeudet ovat paljon alhaisempia kuin pöytätietokoneiden, kannettavien tietokoneiden tai useimpien älypuhelimien. Esimerkiksi Wio Terminalin suoritin toimii 120 MHz:n nopeudella eli 120 000 000 sykliä sekunnissa.

✅ Keskimääräisessä PC:ssä tai Macissa on useita ytimiä sisältävä suoritin, joka toimii useilla gigahertseillä, mikä tarkoittaa, että kellot tikittävät miljardeja kertoja sekunnissa. Tutki tietokoneesi kellonopeutta ja vertaa, kuinka monta kertaa nopeampi se on kuin Wio Terminal.

Jokainen kellosykli kuluttaa virtaa ja tuottaa lämpöä. Mitä nopeammin tikit, sitä enemmän virtaa kuluu ja lämpöä syntyy. PC:issä on jäähdytyselementtejä ja tuulettimia lämmön poistamiseksi, ilman niitä ne ylikuumenisivat ja sammuisivat sekunneissa. Mikrokontrollereissa ei usein ole kumpaakaan, koska ne toimivat paljon viileämmin ja siten paljon hitaammin. PC:t toimivat verkkovirralla tai suurilla akuilla muutaman tunnin ajan, kun taas mikrokontrollerit voivat toimia päiviä, kuukausia tai jopa vuosia pienillä akuilla. Mikrokontrollereissa voi myös olla ytimiä, jotka toimivat eri nopeuksilla, ja ne voivat vaihtaa hitaampiin vähävirtaisiin ytimiin, kun suorittimen kuormitus on alhainen, vähentääkseen virrankulutusta.

> 💁 Jotkut PC:t ja Macit ottavat käyttöön samanlaisen yhdistelmän nopeita tehokkaita ytimiä ja hitaampia vähävirtaisia ytimiä, vaihtaen akun säästämiseksi. Esimerkiksi uusimpien Apple-läppäreiden M1-siru voi vaihtaa 4 suorituskykyytimen ja 4 tehokkuusytimen välillä optimoidakseen akun keston tai nopeuden riippuen suoritettavasta tehtävästä.

✅ Tee hieman tutkimusta: Lue suorittimista [Wikipedia-artikkelista suorittimista](https://wikipedia.org/wiki/Central_processing_unit).

#### Tehtävä

Tutki Wio Terminalia.

Jos käytät Wio Terminalia näissä oppitunneissa, yritä löytää suoritin. Etsi *Hardware Overview* -osio [Wio Terminalin tuotesivulta](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) nähdäksesi kuvan laitteen sisäosista ja yritä löytää suoritin laitteen takana olevan läpinäkyvän muovi-ikkunan kautta.

### Muisti

Mikrokontrollereissa on yleensä kahta tyyppistä muistia – ohjelmamuistia ja satunnaiskäyttöistä muistia (RAM).

Ohjelmamuisti on ei-haihtuvaa, mikä tarkoittaa, että siihen tallennettu sisältö säilyy, vaikka laitteessa ei olisi virtaa. Tämä muisti tallentaa ohjelmakoodisi.

RAM on muisti, jota ohjelma käyttää suorittaessaan, sisältäen ohjelman varaamat muuttujat ja oheislaitteista kerätyt tiedot. RAM on haihtuvaa, ja kun virta katkeaa, sen sisältö menetetään, mikä käytännössä nollaa ohjelmasi.
🎓 Ohjelmamuisti tallentaa koodisi ja säilyy, vaikka virtaa ei olisi.
🎓 RAMia käytetään ohjelman suorittamiseen, ja se nollautuu, kun virta katkeaa

Kuten CPU:ssa, mikro-ohjaimen muisti on moninkertaisesti pienempi kuin PC:ssä tai Macissa. Tyypillisessä PC:ssä voi olla 8 gigatavua (GB) RAM-muistia, eli 8 000 000 000 tavua, joista jokainen tavu tarjoaa tilaa yhden kirjaimen tai numeron (0–255) tallentamiseen. Mikro-ohjaimessa RAM-muistia on vain kilotavuja (KB), ja kilotavu vastaa 1 000 tavua. Yllä mainitussa Wio Terminalissa on 192KB RAM-muistia, eli 192 000 tavua – yli 40 000 kertaa vähemmän kuin keskimääräisessä PC:ssä!

Alla oleva kaavio näyttää suhteellisen kokoeron 192KB:n ja 8GB:n välillä – pieni piste keskellä edustaa 192KB:tä.

![Vertailu 192KB:n ja 8GB:n välillä – yli 40 000 kertaa suurempi](../../../../../translated_images/ram-comparison.6beb73541b42ac6f.fi.png)

Ohjelman tallennustila on myös pienempi kuin PC:ssä. Tyypillisessä PC:ssä voi olla 500GB:n kiintolevy ohjelmien tallennusta varten, kun taas mikro-ohjaimessa tallennustilaa on vain kilotavuja tai ehkä muutama megatavu (MB) (1MB on 1 000KB, eli 1 000 000 tavua). Wio Terminalissa on 4MB ohjelman tallennustilaa.

✅ Tee hieman tutkimusta: Kuinka paljon RAM-muistia ja tallennustilaa tietokoneessasi on, jolla luet tätä? Kuinka tämä vertautuu mikro-ohjaimeen?

### Syöttö ja lähtö

Mikro-ohjaimet tarvitsevat syöttö- ja lähtöliitäntöjä (I/O) lukemaan dataa sensoreista ja lähettämään ohjaussignaaleja toimilaitteille. Niissä on yleensä useita yleiskäyttöisiä syöttö-/lähtöliitäntöjä (GPIO-pinnit). Näitä pinnejä voidaan ohjelmallisesti määrittää syötöksi (eli ne vastaanottavat signaalin) tai lähdöksi (ne lähettävät signaalin).

🧠⬅️ Syöttöpinnejä käytetään sensorien arvojen lukemiseen

🧠➡️ Lähtöpinnejä käytetään ohjeiden lähettämiseen toimilaitteille

✅ Opit tästä lisää seuraavassa oppitunnissa.

#### Tehtävä

Tutki Wio Terminalia.

Jos käytät Wio Terminalia näissä oppitunneissa, etsi GPIO-pinnit. Löydä *Pinout diagram* -osio [Wio Terminal -tuotesivulta](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) ja opi, mitkä pinnit ovat mitä. Wio Terminalissa on mukana tarra, jonka voit kiinnittää laitteen taakse pin-numeroiden kanssa, joten lisää tämä nyt, jos et ole jo tehnyt niin.

### Fyysinen koko

Mikro-ohjaimet ovat tyypillisesti pieniä kooltaan, ja pienin, [Freescale Kinetis KL03 MCU, mahtuu golfpallon kuoppaan](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Pelkkä PC:n CPU voi olla kooltaan 40mm x 40mm, eikä tämä sisällä jäähdytyselementtejä ja tuulettimia, jotka tarvitaan varmistamaan, että CPU voi toimia muutamaa sekuntia pidempään ylikuumenematta – huomattavasti suurempi kuin kokonainen mikro-ohjain. Wio Terminal -kehityspaketti, jossa on mikro-ohjain, kotelo, näyttö ja joukko liitäntöjä ja komponentteja, ei ole paljon suurempi kuin paljas Intel i9 CPU, ja huomattavasti pienempi kuin CPU jäähdytyselementin ja tuulettimen kanssa!

| Laite                          | Koko                  |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio Terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, jäähdytyselementti ja tuuletin | 136mm x 145mm x 103mm |

### Kehykset ja käyttöjärjestelmät

Hitaan nopeuden ja pienen muistin vuoksi mikro-ohjaimet eivät käytä käyttöjärjestelmää (OS) siinä mielessä kuin työpöytäkoneet. Käyttöjärjestelmä, joka saa tietokoneesi toimimaan (Windows, Linux tai macOS), tarvitsee paljon muistia ja prosessointitehoa suorittaakseen tehtäviä, jotka ovat täysin tarpeettomia mikro-ohjaimelle. Muista, että mikro-ohjaimet ohjelmoidaan yleensä suorittamaan yksi tai useampi hyvin spesifinen tehtävä, toisin kuin yleiskäyttöinen tietokone, kuten PC tai Mac, joka tarvitsee tukea käyttöliittymälle, musiikin tai elokuvien toistolle, työkaluille dokumenttien tai koodin kirjoittamiseen, pelien pelaamiseen tai Internetin selaamiseen.

Mikro-ohjaimen ohjelmointiin ilman käyttöjärjestelmää tarvitaan työkaluja, jotka mahdollistavat koodin rakentamisen tavalla, jonka mikro-ohjain voi suorittaa, käyttäen API:ita, jotka voivat kommunikoida oheislaitteiden kanssa. Jokainen mikro-ohjain on erilainen, joten valmistajat tukevat yleensä standardikehyksiä, jotka mahdollistavat standardin 'reseptin' seuraamisen koodin rakentamiseksi ja sen suorittamiseksi millä tahansa mikro-ohjaimella, joka tukee kyseistä kehystä.

Mikro-ohjaimia voi ohjelmoida käyttöjärjestelmällä – usein viitataan reaaliaikaisena käyttöjärjestelmänä (RTOS), koska ne on suunniteltu käsittelemään datan lähettämistä ja vastaanottamista oheislaitteista reaaliajassa. Nämä käyttöjärjestelmät ovat erittäin kevyitä ja tarjoavat ominaisuuksia, kuten:

* Monisäikeisyys, joka mahdollistaa useamman koodilohkon suorittamisen samanaikaisesti, joko useilla ytimillä tai vuorotellen yhdellä ytimellä
* Verkkoyhteydet, jotka mahdollistavat turvallisen kommunikoinnin Internetin kautta
* Graafiset käyttöliittymäkomponentit (GUI) käyttöliittymien (UI) rakentamiseen laitteille, joissa on näyttö.

✅ Lue lisää eri RTOS-järjestelmistä: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Arduino-logo](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) on luultavasti suosituin mikro-ohjainkehys, erityisesti opiskelijoiden, harrastajien ja valmistajien keskuudessa. Arduino on avoimen lähdekoodin elektroniikka-alusta, joka yhdistää ohjelmiston ja laitteiston. Voit ostaa Arduino-yhteensopivia kortteja Arduinolta itseltään tai muilta valmistajilta ja koodata sitten Arduino-kehyksen avulla.

Arduino-kortit ohjelmoidaan C- tai C++-kielellä. C/C++:n käyttö mahdollistaa koodin kompiloimisen erittäin pieneksi ja sen nopean suorittamisen, mikä on tarpeen rajoitetussa laitteessa, kuten mikro-ohjaimessa. Arduino-sovelluksen ydin tunnetaan nimellä sketch, ja se on C/C++-koodia, jossa on kaksi funktiota – `setup` ja `loop`. Kun kortti käynnistyy, Arduino-kehyskoodi suorittaa `setup`-funktion kerran, ja sitten se suorittaa `loop`-funktion uudelleen ja uudelleen, jatkuvasti, kunnes virta katkaistaan.

Kirjoittaisit alustuslogiikkasi `setup`-funktioon, kuten WiFi-yhteyden muodostamisen ja pilvipalveluihin yhdistämisen tai pinnejä syötölle ja lähdölle alustettaessa. `loop`-funktioon sisältyisi prosessointikoodi, kuten sensorin lukeminen ja arvon lähettäminen pilveen. Lisäisit yleensä viiveen jokaiseen silmukkaan, esimerkiksi jos haluat sensoridatan lähetettävän vain 10 sekunnin välein, lisäisit 10 sekunnin viiveen silmukan loppuun, jotta mikro-ohjain voi nukkua, säästää virtaa ja suorittaa silmukan uudelleen tarvittaessa 10 sekunnin kuluttua.

![Arduino-sketch, joka suorittaa ensin setupin ja sitten loopin toistuvasti](../../../../../translated_images/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.fi.png)

✅ Tämä ohjelma-arkkitehtuuri tunnetaan nimellä *tapahtumasilmukka* tai *viestisilmukka*. Monet sovellukset käyttävät tätä taustalla, ja se on standardi useimmille työpöytäsovelluksille, jotka toimivat käyttöjärjestelmissä kuten Windows, macOS tai Linux. `loop` kuuntelee viestejä käyttöliittymäkomponenteilta, kuten painikkeilta, tai laitteilta, kuten näppäimistöltä, ja reagoi niihin. Voit lukea lisää tästä [artikkelista tapahtumasilmukasta](https://wikipedia.org/wiki/Event_loop).

Arduino tarjoaa standardikirjastoja mikro-ohjainten ja I/O-pinnien kanssa vuorovaikutukseen, joissa on erilaisia toteutuksia taustalla eri mikro-ohjaimilla toimimiseen. Esimerkiksi [`delay`-funktio](https://www.arduino.cc/reference/en/language/functions/time/delay/) pysäyttää ohjelman tietyn ajan, [`digitalRead`-funktio](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) lukee arvon `HIGH` tai `LOW` annetusta pinnistä riippumatta siitä, millä kortilla koodi suoritetaan. Nämä standardikirjastot tarkoittavat, että yhdelle kortille kirjoitettu Arduino-koodi voidaan kääntää uudelleen mille tahansa muulle Arduino-kortille ja se toimii, olettaen että pinnit ovat samat ja kortit tukevat samoja ominaisuuksia.

Arduino-ekosysteemissä on suuri määrä kolmannen osapuolen kirjastoja, jotka mahdollistavat lisäominaisuuksien lisäämisen Arduino-projekteihin, kuten sensorien ja toimilaitteiden käytön tai pilvi-IoT-palveluihin yhdistämisen.

##### Tehtävä

Tutki Wio Terminalia.

Jos käytät Wio Terminalia näissä oppitunneissa, lue uudelleen koodi, jonka kirjoitit edellisessä oppitunnissa. Etsi `setup`- ja `loop`-funktiot. Tarkkaile sarjaportin tulostusta, kun `loop`-funktio kutsutaan toistuvasti. Kokeile lisätä koodia `setup`-funktioon kirjoittaaksesi sarjaporttiin ja huomaa, että tämä koodi kutsutaan vain kerran joka kerta, kun laite käynnistetään uudelleen. Kokeile käynnistää laite uudelleen sivussa olevalla virtakytkimellä ja näytä, että tämä koodi kutsutaan joka kerta, kun laite käynnistetään uudelleen.

## Syvällisempi katsaus yhden piirilevyn tietokoneisiin

Edellisessä oppitunnissa esiteltiin yhden piirilevyn tietokoneet. Tarkastellaan nyt niitä syvällisemmin.

### Raspberry Pi

![Raspberry Pi -logo](../../../../../translated_images/raspberry-pi-logo.4efaa16605cee054.fi.png)

[Raspberry Pi Foundation](https://www.raspberrypi.org) on brittiläinen hyväntekeväisyysjärjestö, joka perustettiin vuonna 2009 edistämään tietojenkäsittelytieteen opiskelua erityisesti kouluissa. Osana tätä tehtävää he kehittivät yhden piirilevyn tietokoneen, nimeltään Raspberry Pi. Raspberry Pi:t ovat tällä hetkellä saatavilla kolmessa versiossa – täysikokoinen versio, pienempi Pi Zero ja laskentamoduuli, joka voidaan rakentaa lopulliseen IoT-laitteeseen.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.fi.jpg)

Viimeisin täysikokoisen Raspberry Pi:n versio on Raspberry Pi 4B. Siinä on neliytiminen (4 ydintä) CPU, joka toimii 1.5GHz:n nopeudella, 2, 4 tai 8GB RAM-muistia, gigabitin ethernet, WiFi, 2 HDMI-porttia, jotka tukevat 4k-näyttöjä, ääni- ja komposiittivideolähtöportti, USB-portit (2 USB 2.0, 2 USB 3.0), 40 GPIO-pinniä, kameraliitin Raspberry Pi -kameramoduulille ja SD-korttipaikka. Kaikki tämä piirilevyllä, joka on kooltaan 88mm x 58mm x 19.5mm ja saa virtansa 3A USB-C-virtalähteestä. Näiden hinta alkaa 35 Yhdysvaltain dollarista, mikä on paljon halvempi kuin PC tai Mac.

> 💁 Saatavilla on myös Pi400, joka on all-in-one-tietokone, jossa Pi4 on rakennettu näppäimistöön.

![Raspberry Pi Zero](../../../../../translated_images/raspberry-pi-zero.f7a4133e1e7d54bb.fi.jpg)

Pi Zero on paljon pienempi ja vähävirtaisempi. Siinä on yksiytiminen 1GHz CPU, 512MB RAM-muistia, WiFi (Zero W -mallissa), yksi HDMI-portti, yksi micro-USB-portti, 40 GPIO-pinniä, kameraliitin Raspberry Pi -kameramoduulille ja SD-korttipaikka. Sen mitat ovat 65mm x 30mm x 5mm, ja se kuluttaa hyvin vähän virtaa. Zero maksaa 5 Yhdysvaltain dollaria, ja W-versio, jossa on WiFi, maksaa 10 dollaria.

> 🎓 Molempien CPU:t ovat ARM-prosessoreita, toisin kuin Intel/AMD x86- tai x64-prosessorit, joita löytyy useimmista PC:istä ja Mac-tietokoneista. Nämä ovat samanlaisia kuin prosessorit, joita löytyy joistakin mikro-ohjaimista, sekä lähes kaikista matkapuhelimista, Microsoft Surface X:stä ja uusista Apple Silicon -pohjaisista Apple Mac -tietokoneista.

Kaikki Raspberry Pi -versiot käyttävät Debian Linux -versiota nimeltä Raspberry Pi OS. Tämä on saatavilla kevyenä versiona ilman työpöytää, mikä on täydellinen 'päättömiin' projekteihin, joissa näyttöä ei tarvita, tai täysversiona, jossa on täysi työpöytäympäristö, verkkoselain, toimisto-ohjelmat, koodausvälineet ja pelejä. Koska käyttöjärjestelmä on Debian Linux -versio, voit asentaa minkä tahansa sovelluksen tai työkalun, joka toimii Debianissa ja on rakennettu Pi:n sisällä olevalle ARM-prosessorille.

#### Tehtävä

Tutki Raspberry Pi:tä.

Jos käytät Raspberry Pi:tä näissä oppitunneissa, lue lisää piirilevyn eri laitteistokomponenteista.

* Löydät tietoja käytetyistä prosessoreista [Raspberry Pi -laitteistodokumentaatiosta](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Lue prosessorista, jota Pi:ssäsi käytetään.
* Etsi GPIO-pinnit. Lue lisää niistä [Raspberry Pi GPIO -dokumentaatiosta](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Käytä [GPIO Pin Usage -opasta](https://www.raspberrypi.org/documentation/usage/gpio/README.md) tunnistaaksesi Pi:si eri pinnit.

### Yhden piirilevyn tietokoneiden ohjelmointi

Yhden piirilevyn tietokoneet ovat täysiä tietokoneita, joissa on täysi käyttöjärjestelmä. Tämä tarkoittaa, että niiden ohjelmointiin on käytettävissä laaja valikoima ohjelmointikieliä, kehyksiä ja työkaluja, toisin kuin mikro-ohjaimet, jotka ovat riippuvaisia kortin tuesta kehyksissä, kuten Arduino. Useimmat ohjelmointikielet sisältävät kirjastoja, jotka voivat käyttää GPIO-pinnejä sensorien ja toimilaitteiden datan lähettämiseen ja vastaanottamiseen.

✅ Mitä ohjelmointikieliä osaat? Tukevatko ne Linuxia?

Yleisin ohjelmointikieli IoT-sovellusten rakentamiseen Raspberry Pi:llä on Python. Pi:lle suunniteltu laitteistoekosysteemi on valtava, ja lähes kaikki näistä sisältävät tarvittavan koodin niiden käyttämiseksi Python-kirjastoina. Jotkut näistä ekosysteemeistä perustuvat 'hattuihin' – niin kutsuttuihin, koska ne istuvat Pi:n päällä kuin hattu ja yhdistyvät suurella liittimellä 40 GPIO-pinniin. Nämä hatut tarjoavat lisäominaisuuksia, kuten näyttöjä, sensoreita, kauko-ohjattavia autoja tai sovittimia, jotka mahdollistavat sensorien liittämisen standardoiduilla kaapeleilla.
### Yksikorttitietokoneiden käyttö ammattimaisissa IoT-sovelluksissa

Yksikorttitietokoneita käytetään ammattimaisissa IoT-sovelluksissa, ei pelkästään kehitysalustoina. Ne tarjoavat tehokkaan tavan ohjata laitteistoa ja suorittaa monimutkaisia tehtäviä, kuten koneoppimismallien ajamista. Esimerkiksi [Raspberry Pi 4 compute module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) tarjoaa kaiken Raspberry Pi 4:n tehon, mutta kompaktimmassa ja edullisemmassa muodossa ilman useimpia portteja, ja se on suunniteltu asennettavaksi räätälöityyn laitteistoon.

---

## 🚀 Haaste

Viime oppitunnin haasteena oli listata niin monta IoT-laitetta kuin mahdollista, jotka löytyvät kodistasi, koulustasi tai työpaikastasi. Jokaisen laitteen kohdalla mieti, onko se rakennettu mikro-ohjaimien, yksikorttitietokoneiden vai näiden yhdistelmän ympärille.

## Oppitunnin jälkeinen kysely

[Oppitunnin jälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Kertaus ja itseopiskelu

* Lue [Arduino-aloitusopas](https://www.arduino.cc/en/Guide/Introduction) ymmärtääksesi enemmän Arduino-alustasta.
* Lue [esittely Raspberry Pi 4:stä](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) oppiaksesi lisää Raspberry Pi -laitteista.
* Tutustu joihinkin käsitteisiin ja lyhenteisiin [What the FAQ are CPUs, MPUs, MCUs, and GPUs -artikkelissa Electrical Engineering Journalissa](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Käytä näitä oppaita sekä kustannustietoja, jotka löytyvät seuraamalla linkkejä [laitteisto-oppaassa](../../../hardware.md), päättääksesi, mitä laitteistoalustaa haluat käyttää, tai haluatko mieluummin käyttää virtuaalista laitetta.

## Tehtävä

[Vertaa ja vertaile mikro-ohjaimia ja yksikorttitietokoneita](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.