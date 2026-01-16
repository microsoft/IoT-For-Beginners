<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-27T22:51:01+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "fi"
}
-->
# Sijainnin seuranta

![Tämän oppitunnin luonnoskuva](../../../../../translated_images/fi/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Luonnoskuva: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Johdanto

Ruokatuotteiden kuljetus viljelijältä kuluttajalle sisältää prosessin, jossa laatikot lastataan kuorma-autoihin, laivoihin, lentokoneisiin tai muihin kaupallisiin kuljetusvälineisiin ja toimitetaan ruokaa jonnekin – joko suoraan asiakkaalle tai keskitettyyn varastoon tai käsittelykeskukseen. Koko prosessi viljelijältä kuluttajalle on osa *toimitusketjua*. Alla oleva video Arizonan osavaltion yliopiston W. P. Carey School of Business -koulusta käsittelee toimitusketjun ideaa ja sen hallintaa tarkemmin.

[![Mitä on toimitusketjun hallinta? Video Arizonan osavaltion yliopiston W. P. Carey School of Business -koulusta](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon

IoT-laitteiden lisääminen voi merkittävästi parantaa toimitusketjua, jolloin voit hallita, missä tuotteet ovat, suunnitella kuljetusta ja tavaroiden käsittelyä paremmin sekä reagoida nopeammin ongelmiin.

Kun hallitset ajoneuvokalustoa, kuten kuorma-autoja, on hyödyllistä tietää, missä kukin ajoneuvo on milloin tahansa. Ajoneuvoihin voidaan asentaa GPS-antureita, jotka lähettävät sijaintinsa IoT-järjestelmiin, jolloin omistajat voivat paikantaa ajoneuvon, nähdä sen kulkeman reitin ja tietää, milloin se saapuu määränpäähänsä. Useimmat ajoneuvot toimivat WiFi-yhteyden ulkopuolella, joten ne käyttävät matkapuhelinverkkoja tämän tyyppisen datan lähettämiseen. Joskus GPS-anturi on osa monimutkaisempia IoT-laitteita, kuten elektronisia lokikirjoja. Nämä laitteet seuraavat, kuinka kauan kuorma-auto on ollut matkalla, jotta kuljettajat noudattavat paikallisia työaikalakeja.

Tässä oppitunnissa opit seuraamaan ajoneuvon sijaintia käyttämällä Global Positioning System (GPS) -anturia.

Tässä oppitunnissa käsitellään:

* [Yhdistetyt ajoneuvot](../../../../../3-transport/lessons/1-location-tracking)
* [Paikkatiedon koordinaatit](../../../../../3-transport/lessons/1-location-tracking)
* [Global Positioning Systems (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [GPS-anturidatan lukeminen](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS-data](../../../../../3-transport/lessons/1-location-tracking)
* [GPS-anturidatan dekoodaus](../../../../../3-transport/lessons/1-location-tracking)

## Yhdistetyt ajoneuvot

IoT muuttaa tavaroiden kuljetusta luomalla *yhdistettyjen ajoneuvojen* kalustoja. Nämä ajoneuvot ovat yhteydessä keskitettyihin IT-järjestelmiin ja raportoivat sijaintinsa sekä muita anturidatoja. Yhdistettyjen ajoneuvojen kalustolla on monia etuja:

* Sijainnin seuranta – voit paikantaa ajoneuvon sijainnin milloin tahansa, jolloin voit:

  * Saada ilmoituksia, kun ajoneuvo on saapumassa määränpäähänsä, jotta purkutiimi voi valmistautua
  * Paikantaa varastetut ajoneuvot
  * Yhdistää sijainti- ja reittidatan liikenneongelmiin, jolloin voit muuttaa ajoneuvon reittiä kesken matkan
  * Noudattaa verolakeja. Joissakin maissa ajoneuvoilta peritään vero julkisilla teillä ajetun kilometrimäärän perusteella (kuten [Uuden-Seelannin RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), joten tieto siitä, milloin ajoneuvo on julkisilla teillä vs yksityisillä teillä, helpottaa verojen laskemista.
  * Tietää, minne lähettää huoltotiimi ajoneuvon rikkoutuessa

* Kuljettajan telemetria – varmistaa, että kuljettajat noudattavat nopeusrajoituksia, ajavat mutkissa sopivalla nopeudella, jarruttavat ajoissa ja tehokkaasti sekä ajavat turvallisesti. Yhdistetyissä ajoneuvoissa voi myös olla kameroita, jotka tallentavat tapahtumia. Tämä voidaan yhdistää vakuutuksiin, jolloin hyvät kuljettajat saavat alennettuja hintoja.

* Kuljettajan työaikojen noudattaminen – varmistaa, että kuljettajat ajavat vain laillisesti sallittujen tuntien ajan moottorin käynnistys- ja sammutusaikojen perusteella.

Näitä etuja voidaan yhdistää – esimerkiksi yhdistämällä kuljettajan työaikojen noudattaminen sijainnin seurantaan, jolloin kuljettajat voidaan ohjata uudelleen, jos he eivät voi saavuttaa määränpäätään sallittujen ajoaikojen puitteissa. Näitä voidaan myös yhdistää muihin ajoneuvokohtaisiin telemetriatietoihin, kuten lämpötilatietoihin lämpötilasäädellyistä kuorma-autoista, jolloin ajoneuvot voidaan ohjata uudelleen, jos nykyinen reitti estäisi tavaroiden säilyttämisen oikeassa lämpötilassa.

> 🎓 Logistiikka on prosessi, jossa tavaroita kuljetetaan paikasta toiseen, esimerkiksi viljelijältä supermarkettiin yhden tai useamman varaston kautta. Viljelijä pakkaa tomaattilaatikoita, jotka lastataan kuorma-autoon, toimitetaan keskitettyyn varastoon ja siirretään toiseen kuorma-autoon, joka voi sisältää sekoituksen eri tyyppisiä tuotteita, jotka sitten toimitetaan supermarkettiin.

Ajoneuvojen seurannan ydinosa on GPS – anturit, jotka voivat paikantaa sijaintinsa missä tahansa maapallolla. Tässä oppitunnissa opit käyttämään GPS-anturia, alkaen siitä, miten sijainti määritellään maapallolla.

## Paikkatiedon koordinaatit

Paikkatiedon koordinaatteja käytetään määrittämään pisteitä maapallon pinnalla, samalla tavalla kuin koordinaatteja voidaan käyttää piirtämään pikseli tietokoneen näytölle tai sijoittamaan pistoja ristipistotyöhön. Yksittäiselle pisteelle on parikoordinaatit. Esimerkiksi Microsoftin kampus Redmondissa, Washingtonissa, Yhdysvalloissa sijaitsee koordinaateissa 47.6423109, -122.1390293.

### Leveys- ja pituusasteet

Maapallo on pallo – kolmiulotteinen ympyrä. Tämän vuoksi pisteet määritellään jakamalla se 360 asteeseen, sama kuin ympyrän geometria. Leveysaste mittaa astemäärän pohjoisesta etelään, pituusaste mittaa astemäärän idästä länteen.

> 💁 Kukaan ei oikeastaan tiedä alkuperäistä syytä siihen, miksi ympyrät jaetaan 360 asteeseen. [Wikipedia-sivu asteista (kulma)](https://wikipedia.org/wiki/Degree_(angle)) käsittelee joitakin mahdollisia syitä.

![Leveysasteiden linjat: 90° pohjoisnavalla, 45° puolivälissä pohjoisnavan ja päiväntasaajan välillä, 0° päiväntasaajalla, -45° puolivälissä päiväntasaajan ja etelänavan välillä ja -90° etelänavalla](../../../../../translated_images/fi/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

Leveysaste mitataan linjoilla, jotka kiertävät maapallon ja kulkevat rinnakkain päiväntasaajan kanssa, jakaen pohjoisen ja eteläisen pallonpuoliskon 90° kumpaankin. Päiväntasaaja on 0°, pohjoisnapa on 90°, joka tunnetaan myös nimellä 90° pohjoista, ja etelänapa on -90°, eli 90° etelää.

Pituusaste mitataan astemääränä itään ja länteen. Pituusasteen 0° alkuperä, *päämeridiaani*, määriteltiin vuonna 1884 linjaksi, joka kulkee pohjoisnavalta etelänavalle ja kulkee [Britannian kuninkaallisen observatorion Greenwichissä, Englannissa](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Pituusasteiden linjat: -180° päämeridiaanin länsipuolella, 0° päämeridiaanilla, 180° päämeridiaanin itäpuolella](../../../../../translated_images/fi/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 Meridiaani on kuvitteellinen suora linja, joka kulkee pohjoisnavalta etelänavalle muodostaen puolikaaren.

Pituusasteen mittaamiseksi pisteelle mitataan astemäärä päiväntasaajalla päämeridiaanista meridiaaniin, joka kulkee kyseisen pisteen läpi. Pituusaste vaihtelee -180°:sta, eli 180° länteen, 0°:een päämeridiaanilla, 180°:een, eli 180° itään. 180° ja -180° viittaavat samaan pisteeseen, antimeridiaaniin tai 180. meridiaaniin. Tämä on meridiaani maapallon vastakkaisella puolella päämeridiaanista.

> 💁 Antimeridiaania ei pidä sekoittaa kansainväliseen päivämäärärajaan, joka sijaitsee suunnilleen samassa kohdassa, mutta ei ole suora linja ja vaihtelee geopoliittisten rajojen mukaan.

✅ Tee tutkimusta: Yritä löytää nykyisen sijaintisi leveys- ja pituusasteet.

### Asteet, minuutit ja sekunnit vs desimaaliasteet

Perinteisesti leveys- ja pituusasteiden mittaukset tehtiin seksagesimaalilukujärjestelmällä, eli 60-kantaisella järjestelmällä, jota muinaiset babylonialaiset käyttivät ensimmäisissä ajan ja etäisyyden mittauksissa ja tallennuksissa. Käytät seksagesimaalijärjestelmää todennäköisesti päivittäin huomaamatta sitä – jakamalla tunnit 60 minuuttiin ja minuutit 60 sekuntiin.

Pituus- ja leveysasteet mitataan asteina, minuutteina ja sekunteina, jolloin yksi minuutti on 1/60 astetta ja yksi sekunti on 1/60 minuuttia.

Esimerkiksi päiväntasaajalla:

* 1° leveysastetta on **111,3 kilometriä**
* 1 minuutti leveysastetta on 111,3/60 = **1,855 kilometriä**
* 1 sekunti leveysastetta on 1,855/60 = **0,031 kilometriä**

Minuutin symboli on yksittäinen heittomerkki, sekunnin symboli on kaksoisheittomerkki. Esimerkiksi 2 astetta, 17 minuuttia ja 43 sekuntia kirjoitettaisiin 2°17'43". Sekunnin osat annetaan desimaaleina, esimerkiksi puoli sekuntia on 0°0'0.5".

Tietokoneet eivät toimi 60-kantaisella järjestelmällä, joten nämä koordinaatit annetaan desimaaliasteina, kun GPS-dataa käytetään useimmissa tietokonejärjestelmissä. Esimerkiksi 2°17'43" on 2.295277. Asteen symboli jätetään yleensä pois.

Pisteen koordinaatit annetaan aina muodossa `leveysaste, pituusaste`, joten aiemmin mainittu esimerkki Microsoftin kampuksesta 47.6423109,-122.117198 sisältää:

* Leveysasteen 47.6423109 (47.6423109 astetta pohjoiseen päiväntasaajasta)
* Pituusasteen -122.1390293 (122.1390293 astetta länteen päämeridiaanista).

![Microsoftin kampus koordinaateissa 47.6423109,-122.117198](../../../../../translated_images/fi/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Global Positioning Systems (GPS)

GPS-järjestelmät käyttävät useita satelliitteja, jotka kiertävät maapalloa, paikantaakseen sijaintisi. Olet todennäköisesti käyttänyt GPS-järjestelmiä huomaamattasi – löytääksesi sijaintisi puhelimen karttasovelluksessa, kuten Apple Maps tai Google Maps, tai nähdäksesi, missä kyytisi on kyytipalvelusovelluksessa, kuten Uber tai Lyft, tai käyttäessäsi satelliittinavigointia (sat-nav) autossasi.

> 🎓 'Satelliittinavigoinnin' satelliitit ovat GPS-satelliitteja!

GPS-järjestelmät toimivat siten, että useat satelliitit lähettävät signaalin, joka sisältää kunkin satelliitin nykyisen sijainnin ja tarkan aikaleiman. Nämä signaalit lähetetään radiotaajuuksilla ja havaitaan GPS-anturin antennilla. GPS-anturi havaitsee nämä signaalit ja käyttää nykyistä aikaa mitatakseen, kuinka kauan signaalin saapuminen satelliitista anturiin kesti. Koska radiotaajuuksien nopeus on vakio, GPS-anturi voi käyttää lähetettyä aikaleimaa määrittääkseen, kuinka kaukana anturi on satelliitista. Yhdistämällä vähintään 3 satelliitin tiedot lähetettyjen sijaintien kanssa GPS-anturi pystyy paikantamaan sijaintinsa maapallolla.

> 💁 GPS-anturit tarvitsevat antenneja havaitakseen radiotaajuuksia. Kuorma-autoihin ja autoihin sisäänrakennettujen GPS-järjestelmien antennit on sijoitettu hyvän signaalin saamiseksi, yleensä tuulilasiin tai katolle. Jos käytät erillistä GPS-järjestelmää, kuten älypuhelinta tai IoT-laitetta, sinun on varmistettava, että GPS-järjestelmään tai puhelimeen sisäänrakennettu antenni on selkeästi näkyvissä taivaalle, esimerkiksi tuulilasilla.

![Kun anturin etäisyys useista satelliiteista tiedetään, sijainti voidaan laskea](../../../../../translated_images/fi/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

GPS-satelliitit kiertävät maapalloa, eivät ole kiinteässä pisteessä anturin yläpuolella, joten sijaintitieto sisältää korkeuden merenpinnan yläpuolella sekä leveys- ja pituusasteen.

GPS:llä oli aiemmin Yhdysvaltain armeijan asettamia tarkkuusrajoituksia, jotka rajoittivat tarkkuuden noin 5 metriin. Tämä rajoitus poistettiin vuonna 2000, jolloin tarkkuus parani 30 senttimetriin. Tämän tarkkuuden saavuttaminen ei kuitenkaan aina ole mahdollista signaalien häiriöiden vuoksi.

✅ Jos sinulla on älypuhelin, avaa karttasovellus ja katso, kuinka tarkka sijaintisi on. Puhelimellasi voi kestää hetki havaita useita satelliitteja saadakseen tarkemman sijainnin.
💁 Satelliitit sisältävät atomikelloja, jotka ovat äärimmäisen tarkkoja, mutta ne poikkeavat 38 mikrosekuntia (0,0000038 sekuntia) päivässä verrattuna Maan atomikelloihin, koska aika hidastuu nopeuden kasvaessa, kuten Einsteinin erityis- ja yleisen suhteellisuusteorian ennustukset osoittavat - satelliitit liikkuvat nopeammin kuin Maan pyörimisliike. Tämä poikkeama on käytetty erityis- ja yleisen suhteellisuusteorian ennustusten todistamiseen, ja se täytyy ottaa huomioon GPS-järjestelmien suunnittelussa. Kirjaimellisesti aika kulkee hitaammin GPS-satelliitissa.
GPS-järjestelmiä on kehittänyt ja ottanut käyttöön useat maat ja poliittiset liitot, kuten Yhdysvallat, Venäjä, Japani, Intia, EU ja Kiina. Modernit GPS-anturit voivat yhdistyä useimpiin näistä järjestelmistä saadakseen nopeampia ja tarkempia paikannuksia.

> 🎓 Kunkin järjestelmän satelliittiryhmiä kutsutaan tähdistöiksi.

## Lue GPS-anturin dataa

Useimmat GPS-anturit lähettävät GPS-dataa UARTin kautta.

> ⚠️ UART käsiteltiin [projektissa 2, oppitunnilla 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Palaa tarvittaessa takaisin kyseiseen oppituntiin.

Voit käyttää GPS-anturia IoT-laitteessasi GPS-datan lukemiseen.

### Tehtävä - yhdistä GPS-anturi ja lue GPS-dataa

Käy läpi sopiva opas GPS-datan lukemiseksi IoT-laitteellasi:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Yksikorttitietokone - Raspberry Pi](pi-gps-sensor.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device-gps-sensor.md)

## NMEA GPS-data

Kun suoritat koodisi, saatat nähdä tulosteessa jotain, mikä näyttää sekavalta. Tämä on itse asiassa standardoitua GPS-dataa, jolla on oma merkityksensä.

GPS-anturit tuottavat dataa NMEA-viestien muodossa käyttäen NMEA 0183 -standardia. NMEA on lyhenne sanoista [National Marine Electronics Association](https://www.nmea.org), yhdysvaltalainen kauppajärjestö, joka asettaa standardeja merielektroniikan väliselle viestinnälle.

> 💁 Tämä standardi on maksullinen ja sen hinta on vähintään 2 000 Yhdysvaltain dollaria, mutta julkisessa käytössä on riittävästi tietoa, jotta suurin osa standardista on voitu purkaa ja sitä voidaan käyttää avoimen lähdekoodin ja muussa ei-kaupallisessa koodissa.

Nämä viestit ovat tekstipohjaisia. Jokainen viesti koostuu *lauseesta*, joka alkaa `$`-merkillä, jota seuraa kaksi merkkiä viestin lähteen osoittamiseksi (esim. GP Yhdysvaltain GPS-järjestelmälle, GN GLONASSille, Venäjän GPS-järjestelmälle) ja kolme merkkiä viestityypin osoittamiseksi. Viestin loppuosa koostuu pilkuilla erotetuista kentistä, jotka päättyvät rivinvaihtomerkkiin.

Joidenkin vastaanotettavien viestityyppien kuvaukset:

| Tyyppi | Kuvaus |
| ------ | ------- |
| GGA | GPS-paikannustiedot, mukaan lukien GPS-anturin leveysaste, pituusaste ja korkeus sekä näkyvien satelliittien määrä paikannuksen laskemiseksi. |
| ZDA | Nykyinen päivämäärä ja kellonaika, mukaan lukien paikallinen aikavyöhyke |
| GSV | Näkyvien satelliittien tiedot - määriteltynä satelliiteiksi, joista GPS-anturi voi vastaanottaa signaaleja |

> 💁 GPS-data sisältää aikaleimat, joten IoT-laitteesi voi tarvittaessa saada ajan GPS-anturilta sen sijaan, että se luottaisi NTP-palvelimeen tai sisäiseen reaaliaikakelloon.

GGA-viesti sisältää nykyisen sijainnin muodossa `(dd)dmm.mmmm`, sekä yhden merkin osoittamaan suuntaa. `d` muodossa tarkoittaa asteita, `m` minuutteja ja sekunnit ovat minuutin desimaaleina. Esimerkiksi 2°17'43" olisi 217.716666667 - 2 astetta, 17.716666667 minuuttia.

Suuntaa osoittava merkki voi olla `N` tai `S` leveysasteelle osoittamaan pohjoista tai etelää, ja `E` tai `W` pituusasteelle osoittamaan itää tai länttä. Esimerkiksi leveysaste 2°17'43" olisi `N`, kun taas -2°17'43" olisi `S`.

Esimerkki - NMEA-lause `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Leveysasteosa on `4738.538654,N`, joka muunnetaan desimaaliasteiksi 47.6423109. `4738.538654` on 47.6423109, ja suunta on `N` (pohjoinen), joten se on positiivinen leveysaste.

* Pituusasteosa on `12208.341758,W`, joka muunnetaan desimaaliasteiksi -122.1390293. `12208.341758` on 122.1390293°, ja suunta on `W` (länsi), joten se on negatiivinen pituusaste.

## Dekoodaa GPS-anturin dataa

Sen sijaan, että käyttäisit raakaa NMEA-dataa, on parempi dekoodata se hyödyllisempään muotoon. On olemassa useita avoimen lähdekoodin kirjastoja, jotka auttavat hyödyllisen datan poimimisessa raaoista NMEA-viesteistä.

### Tehtävä - dekoodaa GPS-anturin dataa

Käy läpi sopiva opas GPS-anturidatan dekoodaamiseksi IoT-laitteellasi:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Yksikorttitietokone - Raspberry Pi/Virtuaalinen IoT-laite](single-board-computer-gps-decode.md)

---

## 🚀 Haaste

Kirjoita oma NMEA-dekooderisi! Voitko kolmannen osapuolen kirjastojen sijaan kirjoittaa oman dekooderisi, joka poimii leveys- ja pituusasteet NMEA-lauseista?

## Oppitunnin jälkeinen testi

[Oppitunnin jälkeinen testi](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Kertaus ja itseopiskelu

* Lue lisää maantieteellisistä koordinaateista [Wikipedia-sivulta maantieteellinen koordinaattijärjestelmä](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Tutustu muiden taivaankappaleiden nollameridiaaneihin [Wikipedia-sivulla nollameridiaani](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Tutki eri GPS-järjestelmiä, joita eri maailman hallitukset ja poliittiset liitot, kuten EU, Japani, Venäjä, Intia ja Yhdysvallat, ovat kehittäneet.

## Tehtävä

[Tutki muuta GPS-dataa](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.