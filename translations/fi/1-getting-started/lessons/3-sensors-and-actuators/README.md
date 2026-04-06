# Vuorovaikutus fyysisen maailman kanssa antureiden ja toimilaitteiden avulla

![Tämän oppitunnin sketchnote-yhteenveto](../../../../../translated_images/fi/lesson-3.cc3b7b4cd646de59.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä oppitunti oli osa [Hello IoT -sarjaa](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) [Microsoft Reactorilta](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Oppitunti koostui kahdesta videosta: tunnin mittaisesta oppitunnista ja tunnin mittaisesta toimistotunnista, jossa syvennyttiin oppitunnin osiin ja vastattiin kysymyksiin.

[![Oppitunti 3: Vuorovaikutus fyysisen maailman kanssa antureiden ja toimilaitteiden avulla](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Oppitunti 3: Vuorovaikutus fyysisen maailman kanssa antureiden ja toimilaitteiden avulla - Toimistotunti](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Klikkaa yllä olevia kuvia katsoaksesi videot

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Johdanto

Tässä oppitunnissa tutustutaan kahteen tärkeään IoT-laitteen käsitteeseen: antureihin ja toimilaitteisiin. Pääset myös käytännössä kokeilemaan molempia lisäämällä valosensorin IoT-projektiisi ja sen jälkeen LED-valon, joka reagoi valon määrään, käytännössä luoden yövalon.

Tässä oppitunnissa käsitellään:

* [Mitä anturit ovat?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Anturin käyttö](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Anturityypit](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Mitä toimilaitteet ovat?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Toimilaitteen käyttö](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Toimilaitetyypit](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Mitä anturit ovat?

Anturit ovat laitteita, jotka havaitsevat fyysisen maailman - ne mittaavat yhtä tai useampaa ominaisuutta ympäristöstään ja lähettävät tiedot IoT-laitteelle. Antureita on valtava määrä, koska mitattavia asioita on niin paljon, kuten luonnollisia ominaisuuksia, kuten ilman lämpötila, tai fyysisiä vuorovaikutuksia, kuten liike.

Joidenkin yleisten antureiden esimerkkejä:

* Lämpötila-anturit - mittaavat ilman lämpötilaa tai sen kohteen lämpötilaa, johon ne on upotettu. Harrastelijoille ja kehittäjille nämä yhdistetään usein ilmanpaine- ja kosteusantureihin yhdeksi sensoriksi.
* Painikkeet - havaitsevat, kun niitä painetaan.
* Valoanturit - mittaavat valon määrää ja voivat olla erikoistuneita tiettyihin väreihin, UV-valoon, IR-valoon tai yleiseen näkyvään valoon.
* Kamerat - havaitsevat visuaalisen esityksen maailmasta ottamalla valokuvan tai suoratoistamalla videota.
* Kiihtyvyysanturit - mittaavat liikettä useissa suunnissa.
* Mikrofonit - havaitsevat ääntä, joko yleistä äänenvoimakkuutta tai suunnattua ääntä.

✅ Tee tutkimusta. Mitä antureita puhelimessasi on?

Kaikilla antureilla on yksi yhteinen piirre - ne muuntavat havaitsemansa asian sähköiseksi signaaliksi, jonka IoT-laite voi tulkita. Sähköisen signaalin tulkinta riippuu anturista sekä viestintäprotokollasta, jota käytetään IoT-laitteen kanssa kommunikointiin.

## Anturin käyttö

Seuraa alla olevia ohjeita lisätäksesi anturin IoT-laitteeseesi:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Yksikorttitietokone - Raspberry Pi](pi-sensor.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device-sensor.md)

## Anturityypit

Anturit ovat joko analogisia tai digitaalisia.

### Analogiset anturit

Yksinkertaisimmat anturit ovat analogisia antureita. Nämä anturit vastaanottavat jännitteen IoT-laitteelta, anturikomponentit säätävät tätä jännitettä, ja anturista palaava jännite mitataan anturiarvon saamiseksi.

> 🎓 Jännite mittaa, kuinka paljon voimaa on sähkövirran siirtämiseksi paikasta toiseen, kuten pariston positiivisesta navasta negatiiviseen napaan. Esimerkiksi tavallinen AA-paristo on 1,5V (V on volttien symboli) ja voi siirtää sähköä 1,5V voimalla positiivisesta navasta negatiiviseen napaan. Eri sähkökomponentit vaativat eri jännitteitä toimiakseen, esimerkiksi LED-valo voi syttyä 2-3V:lla, mutta 100W hehkulamppu tarvitsee 240V. Voit lukea lisää jännitteestä [Wikipedia-sivulta](https://wikipedia.org/wiki/Voltage).

Yksi esimerkki on potentiometri. Tämä on säädin, jota voi kiertää kahden asennon välillä, ja anturi mittaa kiertokulman.

![Potentiometri asetettuna keskiasentoon, vastaanottaa 5 volttia ja palauttaa 3,8 volttia](../../../../../translated_images/fi/potentiometer.35a348b9ce22f6ec.webp)

IoT-laite lähettää sähköisen signaalin potentiometrille tietyllä jännitteellä, kuten 5 volttia (5V). Kun potentiometriä säädetään, se muuttaa ulostulevaa jännitettä. Kuvittele, että sinulla on potentiometri, joka on merkitty asteikolla 0–[11](https://wikipedia.org/wiki/Up_to_eleven), kuten vahvistimen äänenvoimakkuuden säädin. Kun potentiometri on täysin pois päältä (0), ulos tulee 0V (0 volttia). Kun se on täysin päällä (11), ulos tulee 5V (5 volttia).

> 🎓 Tämä on yksinkertaistus, ja voit lukea lisää potentiometreistä ja muuttuvista vastuksista [Wikipedia-sivulta](https://wikipedia.org/wiki/Potentiometer).

Anturista tuleva jännite luetaan IoT-laitteella, ja laite voi reagoida siihen. Riippuen anturista, tämä jännite voi olla mielivaltainen arvo tai se voi vastata standardiyksikköä. Esimerkiksi analoginen lämpötila-anturi, joka perustuu [termistoriin](https://wikipedia.org/wiki/Thermistor), muuttaa vastustaan lämpötilan mukaan. Ulostulojännite voidaan sitten muuntaa lämpötilaksi Kelvinissä ja vastaavasti °C tai °F yksiköiksi laskemalla koodissa.

✅ Mitä luulet tapahtuvan, jos anturi palauttaa korkeamman jännitteen kuin mitä sille lähetettiin (esimerkiksi ulkoisesta virtalähteestä)? ⛔️ ÄLÄ testaa tätä.

#### Analogisen signaalin muuntaminen digitaaliseksi

IoT-laitteet ovat digitaalisia - ne eivät voi käsitellä analogisia arvoja, vaan toimivat vain 0:lla ja 1:llä. Tämä tarkoittaa, että analogiset anturiarvot täytyy muuntaa digitaaliseksi signaaliksi ennen niiden käsittelyä. Monilla IoT-laitteilla on analogi-digitaalimuuntimia (ADC), jotka muuntavat analogiset syötteet niiden digitaalisiksi vastineiksi. Anturit voivat myös toimia ADC:n kanssa liitäntälevyn kautta. Esimerkiksi Seeed Grove -ekosysteemissä Raspberry Pi:n kanssa analogiset anturit liitetään tiettyihin portteihin "hatissa", joka istuu Pi:n GPIO-pinnien päällä, ja tämä hattu sisältää ADC:n, joka muuntaa jännitteen digitaaliseksi signaaliksi, joka voidaan lähettää Pi:n GPIO-pinnien kautta.

Kuvittele, että sinulla on analoginen valoanturi, joka on kytketty IoT-laitteeseen, joka käyttää 3,3V ja palauttaa arvon 1V. Tämä 1V ei tarkoita mitään digitaalisessa maailmassa, joten se täytyy muuntaa. Jännite muunnetaan analogiseksi arvoksi asteikolla, joka riippuu laitteesta ja anturista. Yksi esimerkki on Seeed Grove -valoanturi, joka tuottaa arvoja välillä 0–1 023. Tälle anturille, joka toimii 3,3V:lla, 1V ulostulo olisi arvo 300. IoT-laite ei voi käsitellä 300:aa analogisena arvona, joten arvo muunnettaisiin `0000000100101100`:ksi, joka on 300:n binääriesitys Grove-hatilla. Tämä käsiteltäisiin sitten IoT-laitteella.

✅ Jos et tunne binäärijärjestelmää, tee pieni tutkimus oppiaksesi, miten numerot esitetään 0:lla ja 1:llä. [BBC Bitesize -binäärijärjestelmän johdanto](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) on hyvä paikka aloittaa.

Koodauksen näkökulmasta kaikki tämä hoidetaan yleensä antureiden mukana tulevilla kirjastoilla, joten sinun ei tarvitse huolehtia tästä muunnoksesta itse. Grove-valoanturin tapauksessa käyttäisit Python-kirjastoa ja kutsuisit `light`-ominaisuutta tai Arduino-kirjastoa ja kutsuisit `analogRead`-funktiota saadaksesi arvon 300.

### Digitaaliset anturit

Digitaaliset anturit, kuten analogiset anturit, havaitsevat ympäröivän maailman sähköisen jännitteen muutosten avulla. Erona on, että ne tuottavat digitaalisen signaalin joko mittaamalla vain kaksi tilaa tai käyttämällä sisäänrakennettua ADC:tä. Digitaaliset anturit ovat yhä yleisempiä, jotta ADC:tä ei tarvitse käyttää liitäntälevyssä tai IoT-laitteessa.

Yksinkertaisin digitaalinen anturi on painike tai kytkin. Tämä on anturi, jolla on kaksi tilaa: päällä tai pois päältä.

![Painike vastaanottaa 5 volttia. Kun sitä ei paineta, se palauttaa 0 volttia, kun sitä painetaan, se palauttaa 5 volttia](../../../../../translated_images/fi/button.eadb560b77ac45e5.webp)

IoT-laitteiden pinnit, kuten GPIO-pinnit, voivat mitata tämän signaalin suoraan 0:na tai 1:nä. Jos lähetetty jännite on sama kuin palautettu jännite, luettu arvo on 1, muuten luettu arvo on 0. Signaalia ei tarvitse muuntaa, sillä se voi olla vain 1 tai 0.

> 💁 Jännitteet eivät koskaan ole täysin tarkkoja, erityisesti koska anturin komponentit aiheuttavat jonkin verran vastusta, joten yleensä on olemassa toleranssi. Esimerkiksi Raspberry Pi:n GPIO-pinnit toimivat 3,3V:lla ja lukevat palautussignaalin yli 1,8V:na 1:ksi, alle 1,8V:na 0:ksi.

* 3,3V menee painikkeeseen. Painike on pois päältä, joten ulos tulee 0V, mikä antaa arvon 0.
* 3,3V menee painikkeeseen. Painike on päällä, joten ulos tulee 3,3V, mikä antaa arvon 1.

Kehittyneemmät digitaaliset anturit lukevat analogisia arvoja ja muuntavat ne sisäänrakennetuilla ADC:illä digitaalisiksi signaaleiksi. Esimerkiksi digitaalinen lämpötila-anturi käyttää edelleen termoelementtiä samalla tavalla kuin analoginen anturi ja mittaa edelleen jännitteen muutosta, joka johtuu termoelementin vastuksesta nykyisessä lämpötilassa. Sen sijaan, että se palauttaisi analogisen arvon ja luottaisi laitteen tai liitäntälevyn muuntavan sen digitaaliseksi signaaliksi, anturiin sisäänrakennettu ADC muuntaa arvon ja lähettää sen sarjana 0:ia ja 1:iä IoT-laitteelle. Nämä 0:t ja 1:t lähetetään samalla tavalla kuin painikkeen digitaalinen signaali, jossa 1 on täysi jännite ja 0 on 0V.

![Digitaalinen lämpötila-anturi muuntaa analogisen lukeman binääridataksi, jossa 0 on 0 volttia ja 1 on 5 volttia ennen sen lähettämistä IoT-laitteelle](../../../../../translated_images/fi/temperature-as-digital.85004491b977bae1.webp)

Digitaalisen datan lähettäminen mahdollistaa antureiden monimutkaistumisen ja yksityiskohtaisemman datan lähettämisen, jopa salatun datan turvallisille antureille. Yksi esimerkki on kamera. Tämä on anturi, joka tallentaa kuvan ja lähettää sen digitaalisena datana, joka sisältää kuvan, yleensä pakatussa muodossa, kuten JPEG, IoT-laitteen luettavaksi. Se voi jopa suoratoistaa videota tallentamalla kuvia ja lähettämällä joko täydellisen kuvan kehys kerrallaan tai pakatun videovirran.

## Mitä toimilaitteet ovat?

Toimilaitteet ovat antureiden vastakohta - ne muuntavat IoT-laitteelta tulevan sähköisen signaalin vuorovaikutukseksi fyysisen maailman kanssa, kuten valon tai äänen tuottamiseksi tai moottorin liikuttamiseksi.

Joidenkin yleisten toimilaitteiden esimerkkejä:

* LED - tuottaa valoa, kun se kytketään päälle.
* Kaiutin - tuottaa ääntä lähetetyn signaalin perusteella, yksinkertaisesta summerista musiikkia soittavaan kaiuttimeen.
* Askelmoottori - muuntaa signaalin määritettyyn määrään kiertoa, kuten säätimen kääntämiseen 90°.
* Rele - kytkimiä, jotka voidaan kytkeä päälle tai pois päältä sähköisellä signaalilla. Ne mahdollistavat IoT-laitteen pienen jännitteen kytkemisen suurempiin jännitteisiin.
* Näytöt - monimutkaisempia toimilaitteita, jotka näyttävät tietoa monisegmenttinäytöllä. Näytöt vaihtelevat yksinkertaisista LED-näytöistä korkearesoluutioisiin videomonitoriin.

✅ Tee tutkimusta. Mitä toimilaitteita puhelimessasi on?

## Toimilaitteen käyttö

Seuraa alla olevia ohjeita lisätäksesi toimilaitteen IoT-laitteeseesi, jota ohjataan anturilla, rakentaaksesi IoT-yövalon. Se kerää valon määrän valoanturista ja käyttää toimilaitetta, kuten LED-valoa, tuottamaan valoa, kun havaittu valon määrä on liian alhainen.

![Tehtävän vuokaavio, joka näyttää valon määrän lukemisen ja tarkistamisen sekä LED-valon ohjaamisen](../../../../../translated_images/fi/assignment-1-flow.7552a51acb1a5ec8.webp)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Yksikorttitietokone - Raspberry Pi](pi-actuator.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device-actuator.md)

## Toimilaitetyypit

Kuten anturit, toimilaitteet ovat joko analogisia tai digitaalisia.

### Analogiset toimilaitteet

Analogiset toimilaitteet ottavat analogisen signaalin ja muuntavat sen jonkinlaiseksi vuorovaikutukseksi, jossa vuorovaikutus muuttuu syötetyn jännitteen mukaan.

Yksi esimerkki on himmennettävä valo, kuten ne, joita saatat käyttää kotonasi. Valon kirkkaus määräytyy syötetyn jännitteen mukaan.
![Valo himmennetty matalalla jännitteellä ja kirkkaampi korkeammalla jännitteellä](../../../../../translated_images/fi/dimmable-light.9ceffeb195dec1a8.webp)

Kuten antureiden kanssa, varsinainen IoT-laite toimii digitaalisilla signaaleilla, ei analogisilla. Tämä tarkoittaa, että analogisen signaalin lähettämiseksi IoT-laitteessa täytyy olla digitaalista analogiseksi muuntava laite (DAC), joko suoraan IoT-laitteessa tai liitäntälevyssä. Tämä muuntaa IoT-laitteen 0:t ja 1:t analogiseksi jännitteeksi, jota toimilaite voi käyttää.

✅ Mitä luulet tapahtuvan, jos IoT-laite lähettää suuremman jännitteen kuin toimilaite pystyy käsittelemään?  
⛔️ ÄLÄ kokeile tätä.

#### Pulssinleveysmodulaatio

Toinen vaihtoehto IoT-laitteen digitaalisten signaalien muuntamiseksi analogiseksi signaaliksi on pulssinleveysmodulaatio (PWM). Tämä tarkoittaa, että lähetetään paljon lyhyitä digitaalisia pulsseja, jotka toimivat ikään kuin ne olisivat analogisia signaaleja.

Esimerkiksi PWM:ää voidaan käyttää moottorin nopeuden säätämiseen.

Kuvittele, että ohjaat moottoria 5V:n virtalähteellä. Lähetät lyhyen pulssin moottorillesi, jolloin jännite nousee korkeaksi (5V) kahden sadasosan sekunnin ajaksi (0,02s). Tänä aikana moottori voi pyöriä yhden kymmenesosan kierroksesta eli 36°. Signaali sitten taukoaa kahden sadasosan sekunnin ajaksi (0,02s), jolloin lähetetään matala signaali (0V). Jokainen sykli, jossa jännite on ensin päällä ja sitten pois, kestää 0,04s. Sykli toistuu.

![Pulssinleveysmodulaatio moottorin pyörimisessä 150 RPM](../../../../../translated_images/fi/pwm-motor-150rpm.83347ac04ca38482.webp)

Tämä tarkoittaa, että yhdessä sekunnissa lähetetään 25 5V:n pulssia, jotka kestävät 0,02s ja pyörittävät moottoria, ja jokaisen pulssin jälkeen on 0,02s tauko, jolloin moottori ei pyöri. Jokainen pulssi pyörittää moottoria yhden kymmenesosan kierroksesta, mikä tarkoittaa, että moottori tekee 2,5 kierrosta sekunnissa. Olet käyttänyt digitaalista signaalia pyörittämään moottoria 2,5 kierrosta sekunnissa eli 150 [kierrosta minuutissa](https://wikipedia.org/wiki/Revolutions_per_minute) (RPM, epästandardi pyörimisnopeuden mitta).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Kun PWM-signaali on päällä puolet ajasta ja pois päältä puolet ajasta, sitä kutsutaan [50% työsykliksi](https://wikipedia.org/wiki/Duty_cycle). Työsyklit mitataan prosenttiosuutena ajasta, jolloin signaali on päällä verrattuna aikaan, jolloin se on pois päältä.

![Pulssinleveysmodulaatio moottorin pyörimisessä 75 RPM](../../../../../translated_images/fi/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Voit muuttaa moottorin nopeutta muuttamalla pulssien kokoa. Esimerkiksi saman moottorin kanssa voit pitää syklin ajan samana, 0,04s, mutta puolittaa päällä olevan pulssin ajan 0,01s:iin ja lisätä pois päältä olevan pulssin ajan 0,03s:iin. Pulssien määrä sekunnissa pysyy samana (25), mutta jokainen päällä oleva pulssi on puolet lyhyempi. Puolikas pulssi pyörittää moottoria vain yhden kahdeskymmenesosan kierroksesta, ja 25 pulssilla sekunnissa moottori tekee 1,25 kierrosta sekunnissa eli 75 RPM. Muuttamalla digitaalisen signaalin pulssin nopeutta olet puolittanut analogisen moottorin nopeuden.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Miten pitäisit moottorin pyörimisen tasaisena, erityisesti alhaisilla nopeuksilla? Käyttäisitkö pientä määrää pitkiä pulsseja ja pitkiä taukoja vai paljon hyvin lyhyitä pulsseja ja hyvin lyhyitä taukoja?

> 💁 Jotkut anturit käyttävät myös PWM:ää muuntaakseen analogiset signaalit digitaalisiksi.

> 🎓 Voit lukea lisää pulssinleveysmodulaatiosta [Wikipedia-sivulta pulssinleveysmodulaatio](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digitaaliset toimilaitteet

Digitaaliset toimilaitteet, kuten digitaaliset anturit, ovat joko kahdessa tilassa, joita ohjataan korkealla tai matalalla jännitteellä, tai niissä on sisäänrakennettu DAC, joka voi muuntaa digitaalisen signaalin analogiseksi.

Yksi yksinkertainen digitaalinen toimilaite on LED. Kun laite lähettää digitaalisen signaalin 1, lähetetään korkea jännite, joka sytyttää LEDin. Kun lähetetään digitaalinen signaali 0, jännite laskee 0V:iin ja LED sammuu.

![LED on pois päältä 0 voltilla ja päällä 5V:lla](../../../../../translated_images/fi/led.ec6d94f66676a174.webp)

✅ Mitä muita yksinkertaisia kaksitilaisia toimilaitteita keksit? Yksi esimerkki on solenoidi, joka on sähkömagneetti, jota voidaan aktivoida tekemään asioita, kuten siirtämään oven salpaa lukitsemalla/avaamalla oven.

Kehittyneemmät digitaaliset toimilaitteet, kuten näytöt, vaativat digitaalisen datan lähettämistä tietyissä formaateissa. Niissä on yleensä mukana kirjastoja, jotka helpottavat oikean datan lähettämistä niiden ohjaamiseksi.

---

## 🚀 Haaste

Viimeisten kahden oppitunnin haasteena oli listata niin monta IoT-laitetta kuin mahdollista, jotka ovat kotonasi, koulussasi tai työpaikallasi, ja päättää, onko ne rakennettu mikro-ohjaimien vai yksikorttitietokoneiden ympärille, vai jopa näiden yhdistelmään.

Jokaisen listaamasi laitteen kohdalla, mihin antureihin ja toimilaitteisiin ne ovat kytketty? Mikä on kunkin anturin ja toimilaitteen tarkoitus näissä laitteissa?

## Oppitunnin jälkeinen kysely

[Oppitunnin jälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Kertaus ja itseopiskelu

* Lue sähköstä ja virtapiireistä [ThingLearn-sivustolla](http://thinglearn.jenlooper.com/curriculum/).  
* Lue eri tyyppisistä lämpötila-antureista [Seeed Studiosin lämpötila-antureiden oppaassa](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)  
* Lue LED-valoista [Wikipedia LED-sivulla](https://wikipedia.org/wiki/Light-emitting_diode)  

## Tehtävä

[Tutki antureita ja toimilaitteita](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.