<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-27T21:21:16+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "fi"
}
-->
C, lausuttuna *I-squared-C*, on moniohjaaja-moniperiferia-protokolla, jossa mikä tahansa liitetty laite voi toimia ohjaajana tai perifeerisenä laitteena kommunikoiden I²C-väylän kautta (tietoliikennejärjestelmä, joka siirtää dataa). Data lähetetään osoitteellisina paketteina, joissa jokainen paketti sisältää osoitteen sille laitteelle, jolle se on tarkoitettu.

> 💁 Tätä mallia kutsuttiin aiemmin master/slave-malliksi, mutta terminologiaa ollaan hylkäämässä sen yhteyden vuoksi orjuuteen. [Open Source Hardware Association on ottanut käyttöön ohjaaja/perifeerinen](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), mutta vanhaan terminologiaan voi edelleen törmätä.

Laitteilla on osoite, jota käytetään niiden liittäessä I²C-väylään, ja se on yleensä kovakoodattu laitteeseen. Esimerkiksi jokaisella Seeedin Grove-sensorityypillä on sama osoite, joten kaikilla valosensoreilla on sama osoite, kaikilla painikkeilla on sama osoite, joka eroaa valosensorin osoitteesta. Joillakin laitteilla on mahdollisuus muuttaa osoitetta, esimerkiksi muuttamalla hyppykytkimen asetuksia tai juottamalla pinnejä yhteen.

I²C-väylä koostuu kahdesta pääjohtimesta sekä kahdesta virtajohdosta:

| Johto | Nimi | Kuvaus |
| ---- | --------- | ----------- |
| SDA | Sarjadata | Tämä johto lähettää dataa laitteiden välillä. |
| SCL | Sarjakello | Tämä johto lähettää kellosignaalin ohjaajan määrittämällä nopeudella. |
| VCC | Jännite yhteiskerääjä | Laitteiden virtalähde. Tämä on kytketty SDA- ja SCL-johtimiin, jotka saavat virtansa vetovastuksen kautta, joka kytkee signaalin pois päältä, kun mikään laite ei ole ohjaaja. |
| GND | Maa | Tarjoaa yhteisen maadoituksen sähköpiirille. |

![I2C-väylä, jossa 3 laitetta on kytketty SDA- ja SCL-johtimiin, jakamassa yhteisen maadoitusjohdon](../../../../../translated_images/fi/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.png)

Datan lähettämiseksi yksi laite antaa aloitusehdon osoittaakseen, että se on valmis lähettämään dataa. Se toimii sitten ohjaajana. Ohjaaja lähettää sen laitteen osoitteen, jonka kanssa se haluaa kommunikoida, sekä tiedon siitä, haluaako se lukea vai kirjoittaa dataa. Kun data on lähetetty, ohjaaja lähettää lopetusehdon osoittaakseen, että se on valmis. Tämän jälkeen toinen laite voi ryhtyä ohjaajaksi ja lähettää tai vastaanottaa dataa.

2</sup>C:llä on nopeusrajoituksia, ja siinä on kolme eri tilaa, jotka toimivat kiinteillä nopeuksilla. Nopein on High Speed -tila, jonka maksiminopeus on 3,4 Mbps (megabittiä sekunnissa), mutta vain harvat laitteet tukevat tätä nopeutta. Esimerkiksi Raspberry Pi on rajoitettu Fast-tilaan, jonka nopeus on 400 Kbps (kilobittiä sekunnissa). Standard-tila toimii nopeudella 100 Kbps.

> 💁 Jos käytät Raspberry Pi:tä, jossa on Grove Base -hattu IoT-laitteena, näet piirilevyllä useita I<sup>2</sup>C-liitäntöjä, joita voit käyttää kommunikoidaksesi I<sup>2</sup>C-antureiden kanssa. Analogiset Grove-anturit käyttävät myös I<sup>2</sup>C:tä ADC:n avulla lähettääkseen analogisia arvoja digitaalisena datana, joten käyttämäsi valoanturi simuloi analogista pinniä, ja arvo lähetetään I<sup>2</sup>C:n kautta, koska Raspberry Pi tukee vain digitaalisia pinnejä.

### Universal asynchronous receiver-transmitter (UART)

UART sisältää fyysisen piirin, joka mahdollistaa kahden laitteen välisen kommunikoinnin. Jokaisella laitteella on kaksi viestintäpinniä - lähetys (Tx) ja vastaanotto (Rx). Ensimmäisen laitteen Tx-pinni on kytketty toisen laitteen Rx-pinniin, ja toisen laitteen Tx-pinni on kytketty ensimmäisen laitteen Rx-pinniin. Tämä mahdollistaa datan lähettämisen molempiin suuntiin.

* Laite 1 lähettää dataa Tx-pinnistään, jonka laite 2 vastaanottaa Rx-pinnillään.
* Laite 1 vastaanottaa dataa Rx-pinnillään, jonka laite 2 lähettää Tx-pinnistään.

![UART, jossa yhden sirun Tx-pinni on kytketty toisen sirun Rx-pinniin ja päinvastoin](../../../../../translated_images/fi/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Data lähetetään yksi bitti kerrallaan, ja tätä kutsutaan *sarjakommunikaatioksi*. Useimmissa käyttöjärjestelmissä ja mikrokontrollereissa on *sarjaportteja*, eli yhteyksiä, jotka voivat lähettää ja vastaanottaa sarjadataa ja jotka ovat käytettävissä koodissasi.

UART-laitteilla on [baud rate](https://wikipedia.org/wiki/Symbol_rate) (tunnetaan myös nimellä symbolinopeus), joka määrittää, kuinka nopeasti data lähetetään ja vastaanotetaan bitteinä sekunnissa. Yleinen baud rate on 9 600, mikä tarkoittaa, että 9 600 bittiä (0:ia ja 1:siä) dataa lähetetään sekunnissa.

UART käyttää aloitus- ja lopetusbittejä - eli se lähettää aloitusbitin ilmoittaakseen, että se on lähettämässä tavua (8 bittiä) dataa, ja lopetusbitin sen jälkeen, kun 8 bittiä on lähetetty.

UART-nopeus riippuu laitteistosta, mutta jopa nopeimmat toteutukset eivät ylitä 6,5 Mbps (megabittiä sekunnissa, eli miljoonia bittejä, 0 tai 1, lähetetty sekunnissa).

Voit käyttää UART:ia GPIO-pinnien kautta - voit määrittää yhden pinnin Tx:ksi ja toisen Rx:ksi ja kytkeä nämä toiseen laitteeseen.

> 💁 Jos käytät Raspberry Pi:tä, jossa on Grove Base -hattu IoT-laitteena, näet piirilevyllä UART-liitännän, jota voit käyttää kommunikoidaksesi antureiden kanssa, jotka käyttävät UART-protokollaa.

### Serial Peripheral Interface (SPI)

SPI on suunniteltu lyhyen matkan viestintään, kuten mikrokontrollerin ja tallennuslaitteen, kuten flash-muistin, välillä. Se perustuu ohjain/periferia-malliin, jossa yksi ohjain (yleensä IoT-laitteen prosessori) kommunikoi useiden periferioiden kanssa. Ohjain hallitsee kaikkea valitsemalla periferian ja lähettämällä tai pyytämällä dataa.

> 💁 Kuten I<sup>2</sup>C:ssä, termit ohjain ja periferia ovat uusia muutoksia, joten saatat nähdä edelleen vanhempia termejä käytössä.

SPI-ohjaimet käyttävät 3 johtoa sekä yhtä ylimääräistä johtoa per periferia. Periferioilla on 4 johtoa. Nämä johdot ovat:

| Johto | Nimi | Kuvaus |
| ---- | --------- | ----------- |
| COPI | Ohjaimen ulostulo, periferian sisääntulo | Tämä johto lähettää dataa ohjaimelta periferiaan. |
| CIPO | Ohjaimen sisääntulo, periferian ulostulo | Tämä johto lähettää dataa periferialta ohjaimelle. |
| SCLK | Sarjakello | Tämä johto lähettää kellosignaalin ohjaimen määrittämällä nopeudella. |
| CS   | Piirin valinta | Ohjaimella on useita johtoja, yksi per periferia, ja jokainen johto on kytketty vastaavan periferian CS-johtoon. |

![SPI, jossa yksi ohjain ja kaksi periferiaa](../../../../../translated_images/fi/spi.297431d6f98b386b.webp)

CS-johtoa käytetään aktivoimaan yksi periferia kerrallaan, kommunikoimalla COPI- ja CIPO-johtojen kautta. Kun ohjaimen täytyy vaihtaa periferiaa, se deaktivoi CS-johdon, joka on kytketty aktiiviseen periferiaan, ja aktivoi johdon, joka on kytketty seuraavaan periferiaan, jonka kanssa se haluaa kommunikoida.

SPI on *täysdupleksi*, mikä tarkoittaa, että ohjain voi lähettää ja vastaanottaa dataa samanaikaisesti samalta periferialta COPI- ja CIPO-johtojen kautta. SPI käyttää kellosignaalia SCLK-johdossa pitääkseen laitteet synkronoituna, joten toisin kuin UART:in kautta lähettäessä, se ei tarvitse aloitus- ja lopetusbittejä.

SPI:lle ei ole määritelty nopeusrajoituksia, ja toteutukset voivat usein lähettää useita megatavuja dataa sekunnissa.

IoT-kehityspaketit tukevat usein SPI:tä joidenkin GPIO-pinnien kautta. Esimerkiksi Raspberry Pi:ssä voit käyttää GPIO-pinnejä 19, 21, 23, 24 ja 26 SPI:lle.

### Langaton viestintä

Jotkut anturit voivat kommunikoida standardien langattomien protokollien, kuten Bluetoothin (pääasiassa Bluetooth Low Energy eli BLE), LoRaWAN:n (**Lo**ng **Ra**nge vähävirtaisen verkon protokolla) tai WiFi:n kautta. Näiden avulla etäanturit, jotka eivät ole fyysisesti kytkettynä IoT-laitteeseen, voivat kommunikoida.

Yksi esimerkki tästä on kaupalliset maaperän kosteusanturit. Nämä mittaavat maaperän kosteuden pellolla ja lähettävät datan LoRaWAN:n kautta keskuslaitteelle, joka käsittelee datan tai lähettää sen Internetiin. Tämä mahdollistaa anturin sijoittamisen kauas IoT-laitteesta, joka hallinnoi dataa, vähentäen virrankulutusta ja tarvetta suurille WiFi-verkoille tai pitkille kaapeleille.

BLE on suosittu edistyneille antureille, kuten ranteessa toimiville kuntoseurantalaitteille. Nämä yhdistävät useita antureita ja lähettävät anturidatan IoT-laitteelle, kuten puhelimellesi, BLE:n kautta.

✅ Onko sinulla Bluetooth-antureita mukanasi, kotonasi tai koulussasi? Näihin voi kuulua lämpötila-anturit, läsnäoloanturit, laitteiden seurantajärjestelmät ja kuntolaitteet.

Yksi suosittu tapa kaupallisten laitteiden yhdistämiseen on Zigbee. Zigbee käyttää WiFiä muodostaakseen mesh-verkkoja laitteiden välillä, joissa jokainen laite yhdistyy mahdollisimman moneen lähellä olevaan laitteeseen, muodostaen suuren määrän yhteyksiä kuin hämähäkin verkko. Kun yksi laite haluaa lähettää viestin Internetiin, se voi lähettää sen lähimmille laitteille, jotka sitten välittävät sen eteenpäin muille lähellä oleville laitteille ja niin edelleen, kunnes se saavuttaa koordinaattorin ja voidaan lähettää Internetiin.

> 🐝 Nimi Zigbee viittaa hunajamehiläisten tanssiin niiden palattua pesään.

## Mittaa maaperän kosteustaso

Voit mitata maaperän kosteustason käyttämällä maaperän kosteusanturia, IoT-laitetta ja huonekasvia tai läheistä maaperäaluetta.

### Tehtävä - mittaa maaperän kosteus

Käy läpi asiaankuuluva opas mitataksesi maaperän kosteuden IoT-laitteellasi:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Yksikorttitietokone - Raspberry Pi](pi-soil-moisture.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device-soil-moisture.md)

## Anturin kalibrointi

Anturit perustuvat sähköisten ominaisuuksien, kuten resistanssin tai kapasitanssin, mittaamiseen.

> 🎓 Resistanssi, mitattuna ohmeina (Ω), kertoo kuinka paljon vastustusta sähkövirta kohtaa kulkiessaan jonkin läpi. Kun jännite kohdistetaan materiaaliin, sen läpi kulkevan virran määrä riippuu materiaalin resistanssista. Voit lukea lisää [resistanssin Wikipedia-sivulta](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Kapasitanssi, mitattuna faradeina (F), on komponentin tai piirin kyky kerätä ja varastoida sähköenergiaa. Voit lukea lisää kapasitanssista [kapasitanssin Wikipedia-sivulta](https://wikipedia.org/wiki/Capacitance).

Nämä mittaukset eivät aina ole hyödyllisiä - kuvittele lämpötila-anturi, joka antaisi mittauksen 22,5 kΩ! Sen sijaan mitattu arvo täytyy muuntaa hyödylliseksi yksiköksi kalibroimalla - eli yhdistämällä mitatut arvot mitattuun suureeseen, jotta uudet mittaukset voidaan muuntaa oikeaan yksikköön.

Jotkut anturit ovat valmiiksi kalibroituja. Esimerkiksi viime tunnilla käyttämäsi lämpötila-anturi oli jo kalibroitu niin, että se voi palauttaa lämpötilamittauksen °C-yksikössä. Tehtaalla ensimmäinen anturi altistettaisiin tunnetuille lämpötiloille ja resistanssi mitattaisiin. Tätä käytettäisiin sitten laskelman luomiseen, joka voi muuntaa mitatun arvon Ω-yksiköstä (resistanssin yksikkö) °C-yksikköön.

> 💁 Kaava, jolla lasketaan resistanssi lämpötilasta, on nimeltään [Steinhart–Hart-yhtälö](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Maaperän kosteusanturin kalibrointi

Maaperän kosteus mitataan gravimetrisellä tai volymetrisellä vesipitoisuudella.

* Gravimetrinen tarkoittaa veden painoa maaperän yksikköpainossa, mitattuna kilogrammoina vettä per kilogramma kuivaa maaperää.
* Volymetrinen tarkoittaa veden tilavuutta maaperän yksikkötilavuudessa, mitattuna kuutiometreinä vettä per kuutiometri kuivaa maaperää.

> 🇺🇸 Amerikkalaisille, yksiköiden johdonmukaisuuden vuoksi nämä voidaan mitata paunoina kilogrammojen sijaan tai kuutiojalkoina kuutiometrien sijaan.

Maaperän kosteusanturit mittaavat sähköistä resistanssia tai kapasitanssia - tämä ei ainoastaan vaihtele maaperän kosteuden mukaan, vaan myös maaperän tyypin mukaan, sillä maaperän komponentit voivat muuttaa sen sähköisiä ominaisuuksia. Ihanteellisesti anturit tulisi kalibroida - eli ottaa anturin lukemia ja verrata niitä tieteellisemmällä menetelmällä saatuihin mittauksiin. Esimerkiksi laboratorio voi laskea gravimetrisen maaperän kosteuden tietyn pellon näytteistä muutaman kerran vuodessa, ja näitä lukuja voidaan käyttää anturin kalibrointiin, yhdistäen anturin lukemat gravimetriseen maaperän kosteuteen.

![Graafi jännitteestä vs maaperän kosteuspitoisuus](../../../../../translated_images/fi/soil-moisture-to-voltage.df86d80cda158700.webp)

Yllä oleva graafi näyttää, kuinka anturi kalibroidaan. Jännite mitataan maaperänäytteestä, joka sitten analysoidaan laboratoriossa vertaamalla kosteaa painoa kuivaan painoon (mittaamalla paino kosteana, sitten kuivaamalla uunissa ja mittaamalla kuivana). Kun muutama lukema on otettu, ne voidaan piirtää graafiin ja sovittaa viiva pisteisiin. Tätä viivaa voidaan sitten käyttää muuntamaan IoT-laitteen ottamat maaperän kosteusanturin lukemat todellisiksi maaperän kosteuden mittauksiksi.

💁 Resistiivisillä maaperän kosteusantureilla jännite kasvaa maaperän kosteuden kasvaessa. Kapasitiivisilla maaperän kosteusantureilla jännite laskee maaperän kosteuden kasvaessa, joten näiden graafit kallistuisivat alaspäin, eivät ylöspäin.

![Maaperän kosteuslukema interpoloituna graafista](../../../../../translated_images/fi/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

Yllä oleva graafi näyttää maaperän kosteusanturin jännitelukeman, ja seuraamalla sitä graafin viivaan voidaan laskea todellinen maaperän kosteus.

Tämä lähestymistapa tarkoittaa, että viljelijän tarvitsee saada vain muutama laboratoriomittaus pellosta, ja sitten he voivat käyttää IoT-laitteita mittaamaan maaperän kosteutta - mikä nopeuttaa mittausten ottamista huomattavasti.

---

## 🚀 Haaste

Resistiivisillä ja kapasitiivisilla maaperän kosteusantureilla on useita eroja. Mitkä ovat nämä erot, ja mikä tyyppi (jos mikään) on paras viljelijälle? Muuttuuko vastaus kehittyvien ja kehittyneiden maiden välillä?

## Luentojälkeinen kysely

[Luentojälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Kertaus ja itseopiskelu

Lue lisää antureiden ja toimilaitteiden käyttämistä laitteistoista ja protokollista:

* [GPIO Wikipedia-sivu](https://wikipedia.org/wiki/General-purpose_input/output)
* [UART Wikipedia-sivu](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [SPI Wikipedia-sivu](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [I<sup>2</sup>C Wikipedia-sivu](https://wikipedia.org/wiki/I²C)
* [Zigbee Wikipedia-sivu](https://wikipedia.org/wiki/Zigbee)

## Tehtävä

[Kalibroi anturisi](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.