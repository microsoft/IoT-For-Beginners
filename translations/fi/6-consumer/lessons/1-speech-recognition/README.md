# Tunnista puhe IoT-laitteella

![Tämän oppitunnin yleiskuvaus sketchnotena](../../../../../translated_images/fi/lesson-21.e34de51354d6606f.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tässä videossa esitellään Azure Speech Service -palvelua, joka on tämän oppitunnin aiheena:

[![Kuinka aloittaa Cognitive Services Speech -resurssin käyttö Microsoft Azuren YouTube-kanavalta](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Johdanto

'Alexa, aseta 12 minuutin ajastin'

'Alexa, mikä on ajastimen tila?'

'Alexa, aseta 8 minuutin ajastin nimeltä höyrytä parsakaali'

Älylaitteet ovat yhä yleisempiä. Ne eivät ole pelkästään älykaiuttimia, kuten HomePodit, Echot ja Google Homest, vaan niitä on myös puhelimissamme, kelloissamme ja jopa valaisimissamme ja termostaateissamme.

> 💁 Minulla on kotonani ainakin 19 laitetta, joissa on puheavustaja, ja nämä ovat vain ne, joista tiedän!

Puheohjaus lisää saavutettavuutta, sillä se mahdollistaa laitteiden käytön myös niille, joilla on rajoittunut liikuntakyky. Olipa kyseessä pysyvä vamma, kuten synnynnäinen käsien puuttuminen, väliaikainen vamma, kuten murtunut käsi, tai tilanne, jossa kädet ovat täynnä ostoksia tai pieniä lapsia, kodin hallinta äänellä käsien sijaan avaa uusia mahdollisuuksia. Esimerkiksi huutamalla 'Hei Siri, sulje autotallin ovi' samalla kun käsittelet vaipanvaihtoa ja villiä taaperoa, voi olla pieni mutta merkittävä elämänlaadun parannus.

Yksi suosituimmista puheavustajien käyttötavoista on ajastimien asettaminen, erityisesti keittiössä. Useiden ajastimien asettaminen pelkällä äänellä on suuri apu keittiössä – ei tarvitse keskeyttää taikinan vaivaamista, keiton sekoittamista tai pestä käsiä fyysisen ajastimen käyttämiseksi.

Tässä oppitunnissa opit, kuinka lisätä puheentunnistus IoT-laitteisiin. Opit mikrofoneista sensoreina, kuinka tallentaa ääntä IoT-laitteeseen liitetystä mikrofonista ja kuinka käyttää tekoälyä kuullun muuntamiseen tekstiksi. Projektin aikana rakennat älykkään keittiöajastimen, joka osaa asettaa ajastimia äänikomennoilla useilla kielillä.

Tässä oppitunnissa käsitellään:

* [Mikrofonit](../../../../../6-consumer/lessons/1-speech-recognition)
* [Äänen tallentaminen IoT-laitteesta](../../../../../6-consumer/lessons/1-speech-recognition)
* [Puhe tekstiksi](../../../../../6-consumer/lessons/1-speech-recognition)
* [Puheen muuntaminen tekstiksi](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofonit

Mikrofonit ovat analogisia sensoreita, jotka muuttavat ääniaallot sähköisiksi signaaleiksi. Ilman värähtelyt saavat mikrofonin komponentit liikkumaan hyvin pieniä määriä, mikä aiheuttaa pieniä muutoksia sähköisissä signaaleissa. Nämä muutokset vahvistetaan sähköiseksi ulostuloksi.

### Mikrofonityypit

Mikrofoneja on monenlaisia:

* Dynaamiset - Dynaamisissa mikrofoneissa on magneetti, joka on kiinnitetty liikkuvaan kalvoon. Kalvo liikkuu käämissä, mikä luo sähkövirran. Tämä on päinvastainen prosessi kuin useimmissa kaiuttimissa, joissa sähkövirta liikuttaa magneettia käämissä ja saa kalvon tuottamaan ääntä. Tämä tarkoittaa, että kaiuttimia voidaan käyttää dynaamisina mikrofoneina ja dynaamisia mikrofoneja kaiuttimina. Esimerkiksi sisäpuhelimissa, joissa käyttäjä joko kuuntelee tai puhuu, mutta ei molempia yhtä aikaa, yksi laite voi toimia sekä kaiuttimena että mikrofonina.

    Dynaamiset mikrofonit eivät tarvitse virtaa toimiakseen, sillä sähköinen signaali syntyy täysin mikrofonin toiminnasta.

    ![Patti Smith laulamassa Shure SM58 (dynaaminen kardioidimikrofoni) -mikrofoniin](../../../../../translated_images/fi/dynamic-mic.8babac890a2d80df.webp)

* Nauhamikrofonit - Nauhamikrofonit ovat samankaltaisia kuin dynaamiset mikrofonit, mutta niissä on metallinauha kalvon sijasta. Tämä nauha liikkuu magneettikentässä ja tuottaa sähkövirran. Kuten dynaamiset mikrofonit, nauhamikrofonit eivät tarvitse virtaa toimiakseen.

    ![Edmund Lowe, amerikkalainen näyttelijä, seisoo radiomikrofonin (merkitty (NBC) Blue Network) edessä, käsikirjoitus kädessään, 1942](../../../../../translated_images/fi/ribbon-mic.eacc8e092c7441ca.webp)

* Kondensaattorimikrofonit - Kondensaattorimikrofoneissa on ohut metallikalvo ja kiinteä metallinen takalevy. Molempiin johdetaan sähköä, ja kun kalvo värähtelee, staattinen varaus levyjen välillä muuttuu ja tuottaa signaalin. Kondensaattorimikrofonit tarvitsevat virtaa toimiakseen – tätä kutsutaan *phantom-virraksi*.

    ![C451B pienikalvoinen kondensaattorimikrofoni AKG Acousticsilta](../../../../../translated_images/fi/condenser-mic.6f6ed5b76ca19e0e.webp)

* MEMS - Mikroelektromekaaniset järjestelmät (MEMS) ovat sirulle rakennettuja mikrofoneja. Niissä on paineherkkä kalvo, joka on kaiverrettu piisiruun, ja ne toimivat samankaltaisesti kuin kondensaattorimikrofonit. Nämä mikrofonit voivat olla erittäin pieniä ja integroitavissa piireihin.

    ![MEMS-mikrofoni piirilevyllä](../../../../../translated_images/fi/mems-microphone.80574019e1f5e4d9.webp)

    Yllä olevassa kuvassa siru, jossa lukee **LEFT**, on MEMS-mikrofoni, jossa on alle millimetrin levyinen kalvo.

✅ Tee tutkimusta: Mitä mikrofoneja sinulla on ympärilläsi – joko tietokoneessasi, puhelimessasi, kuulokkeissasi tai muissa laitteissa? Minkä tyyppisiä mikrofoneja ne ovat?

### Digitaalinen ääni

Ääni on analoginen signaali, joka sisältää erittäin hienojakoista tietoa. Tämän signaalin muuntamiseksi digitaaliseksi ääni on näytettävä tuhansia kertoja sekunnissa.

> 🎓 Näytteenotto tarkoittaa äänen signaalin muuntamista digitaaliseksi arvoksi, joka edustaa signaalia tietyllä ajanhetkellä.

![Viivakaavio, joka näyttää signaalin ja kiintein välein otetut pisteet](../../../../../translated_images/fi/sampling.6f4fadb3f2d9dfe7.webp)

Digitaalinen ääni näytteistetään käyttämällä pulssikoodimodulaatiota (Pulse Code Modulation, PCM). PCM:ssä signaalin jännite luetaan ja valitaan lähin diskreetti arvo tälle jännitteelle määritellyn koon perusteella.

> 💁 Voit ajatella PCM:ää sensoriversiona pulssinleveysmodulaatiosta (PWM). (PWM käsiteltiin [aloitusprojektin oppitunnissa 3](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM muuntaa analogisen signaalin digitaaliseksi, kun taas PWM muuntaa digitaalisen signaalin analogiseksi.

Esimerkiksi useimmat suoratoistomusiikkipalvelut tarjoavat 16-bittistä tai 24-bittistä ääntä. Tämä tarkoittaa, että ne muuntavat jännitteen arvoksi, joka mahtuu 16-bittiseen tai 24-bittiseen kokonaislukuun. 16-bittinen ääni mahtuu arvoon, joka vaihtelee välillä -32 768 ja 32 767, kun taas 24-bittinen ääni vaihtelee välillä −8 388 608 ja 8 388 607. Mitä enemmän bittejä, sitä lähempänä näyte on sitä, mitä korvamme todella kuulevat.

> 💁 Olet ehkä kuullut 8-bittisestä äänestä, jota kutsutaan usein LoFi-ääneksi. Tämä on ääntä, joka on näytteistetty vain 8-bittisenä, eli välillä -128 ja 127. Ensimmäiset tietokoneäänet rajoittuivat 8-bittisiksi laitteistorajoitusten vuoksi, joten tämä on yleistä retropeleissä.

Näytteet otetaan tuhansia kertoja sekunnissa, käyttäen hyvin määriteltyjä näytteenottotaajuuksia, jotka mitataan kilohertseinä (tuhansia näytteitä sekunnissa). Suoratoistomusiikkipalvelut käyttävät useimmiten 48 kHz:n näytteenottotaajuutta, mutta jotkut 'häviöttömät' äänet käyttävät jopa 96 kHz tai 192 kHz. Mitä korkeampi näytteenottotaajuus, sitä lähempänä alkuperäistä ääntä ollaan – tiettyyn pisteeseen asti. On kiistanalaista, voivatko ihmiset erottaa äänenlaadun eroja yli 48 kHz:n taajuuksilla.

✅ Tee tutkimusta: Jos käytät suoratoistomusiikkipalvelua, mikä on sen käyttämä näytteenottotaajuus ja bittisyvyys? Jos käytät CD-levyjä, mikä on CD-äänen näytteenottotaajuus ja bittisyvyys?

Äänidataa on saatavilla useissa eri formaateissa. Olet luultavasti kuullut mp3-tiedostoista – äänidatasta, joka on pakattu pienemmäksi ilman laadun heikkenemistä. Pakkamatonta ääntä tallennetaan usein WAV-tiedostoina – nämä tiedostot sisältävät 44 tavua otsikkotietoa ja sen jälkeen raakaa äänidataa. Otsikko sisältää tietoja, kuten näytteenottotaajuuden (esimerkiksi 16000 16 kHz:lle), bittisyvyyden (esimerkiksi 16 16-bittiselle) ja kanavien määrän. Otsikon jälkeen WAV-tiedosto sisältää raakaa äänidataa.

> 🎓 Kanavat viittaavat siihen, kuinka monta erillistä äänivirtaa muodostaa äänen. Esimerkiksi stereossa, jossa on vasen ja oikea kanava, kanavia olisi 2. Kotiteatterijärjestelmän 7.1-tilaäänessä kanavia olisi 8.

### Äänidatan koko

Äänidata on suhteellisen suurta. Esimerkiksi tallennettaessa pakkaamatonta 16-bittistä ääntä 16 kHz:n taajuudella (riittävä puheentunnistusmallille), dataa kertyy 32 kt sekunnissa:

* 16-bittinen tarkoittaa 2 tavua näytettä kohden (1 tavu on 8 bittiä).
* 16 kHz tarkoittaa 16 000 näytettä sekunnissa.
* 16 000 x 2 tavua = 32 000 tavua sekunnissa.

Tämä saattaa kuulostaa pieneltä määrältä dataa, mutta jos käytät mikro-ohjainta, jossa on rajallinen määrä muistia, tämä voi olla paljon. Esimerkiksi Wio Terminal -laitteessa on 192 kt muistia, ja sen on tallennettava ohjelmakoodi ja muuttujat. Vaikka ohjelmakoodi olisi pieni, et voisi tallentaa yli 5 sekuntia ääntä.

Mikro-ohjaimet voivat käyttää lisätallennustilaa, kuten SD-kortteja tai flash-muistia. Kun rakennat IoT-laitetta, joka tallentaa ääntä, sinun on varmistettava, että sinulla on lisätallennustilaa ja että koodisi kirjoittaa mikrofonista tallennetun äänen suoraan tallennustilaan. Kun lähetät ääntä pilveen, sinun tulee suoratoistaa tallennustilasta verkkopyyntöön. Näin voit välttää muistin loppumisen yrittämällä pitää koko äänidatablokin muistissa kerralla.

## Äänen tallentaminen IoT-laitteesta

IoT-laitteesi voidaan liittää mikrofoniin äänen tallentamista varten, jotta se voidaan muuntaa tekstiksi. Se voidaan myös liittää kaiuttimiin äänen toistamista varten. Myöhemmissä oppitunneissa tätä käytetään äänen palautteen antamiseen, mutta kaiuttimien asettaminen on hyödyllistä jo nyt mikrofonin testaamiseksi.

### Tehtävä – mikrofonin ja kaiuttimien konfigurointi

Seuraa sopivaa ohjetta mikrofonin ja kaiuttimien konfiguroimiseksi IoT-laitteellesi:

* [Arduino – Wio Terminal](wio-terminal-microphone.md)
* [Yksikorttitietokone – Raspberry Pi](pi-microphone.md)
* [Yksikorttitietokone – Virtuaalilaite](virtual-device-microphone.md)

### Tehtävä – äänen tallentaminen

Seuraa sopivaa ohjetta äänen tallentamiseksi IoT-laitteellasi:

* [Arduino – Wio Terminal](wio-terminal-audio.md)
* [Yksikorttitietokone – Raspberry Pi](pi-audio.md)
* [Yksikorttitietokone – Virtuaalilaite](virtual-device-audio.md)

## Puhe tekstiksi

Puhe tekstiksi, eli puheentunnistus, tarkoittaa tekoälyn käyttöä äänessä olevien sanojen muuntamiseksi tekstiksi.

### Puheentunnistusmallit

Puheen muuntamiseksi tekstiksi äänisignaalin näytteet ryhmitellään ja syötetään koneoppimismalliin, joka perustuu toistuvaan neuroverkkoon (Recurrent Neural Network, RNN). Tämä on koneoppimismalli, joka voi käyttää aiempia tietoja päätöksenteossa uusien tietojen suhteen. Esimerkiksi RNN voisi tunnistaa yhden ääninäytteen 'Hel'-äänteeksi ja seuraavan 'lo'-äänteeksi, yhdistää nämä ja päätellä, että 'Hello' on kelvollinen sana.

Koneoppimismallit käsittelevät aina saman kokoista dataa. Kuvantunnistusmalli, jonka rakensit aiemmassa oppitunnissa, muuttaa kuvat kiinteään kokoon ennen niiden käsittelyä. Sama pätee puhemalleihin – niiden on käsiteltävä kiinteän kokoisia äänipaloja. Puhemallien on pystyttävä yhdistämään useiden ennusteiden tulokset saadakseen vastauksen, jotta ne voivat erottaa esimerkiksi sanat 'Hi' ja 'Highway' tai 'flock' ja 'floccinaucinihilipilification'.

Puhemallit ovat myös riittävän kehittyneitä ymmärtämään kontekstia ja voivat korjata havaitsemiaan sanoja, kun lisää ääntä käsitellään. Esimerkiksi lauseessa "I went to the shops to get two bananas and an apple too" käytät kolmea sanaa, jotka kuulostavat samalta mutta kirjoitetaan eri tavoin – to, two ja too. Puhemallit pystyvät ymmärtämään kontekstin ja valitsemaan sanalle oikean kirjoitusasun.
💁 Jotkut puhepalvelut mahdollistavat mukauttamisen, jotta ne toimisivat paremmin meluisissa ympäristöissä, kuten tehtaissa, tai alakohtaisilla sanoilla, kuten kemiallisilla nimillä. Nämä mukautukset koulutetaan tarjoamalla esimerkkiaudiota ja transkriptio, ja ne toimivat siirto-oppimisen avulla, samalla tavalla kuin miten koulutit kuvantunnistimen käyttämällä vain muutamia kuvia aiemmassa oppitunnissa.
### Yksityisyys

Kun käytät puheentunnistusta kuluttajan IoT-laitteessa, yksityisyys on äärimmäisen tärkeää. Nämä laitteet kuuntelevat ääntä jatkuvasti, joten kuluttajana et halua, että kaikki sanomasi lähetetään pilveen ja muutetaan tekstiksi. Tämä ei ainoastaan kuluta paljon internet-kaistaa, vaan sillä on myös merkittäviä yksityisyyteen liittyviä vaikutuksia, erityisesti kun jotkut älylaitteiden valmistajat valitsevat satunnaisesti ääntä [ihmisten validoitavaksi tekstin kanssa mallinsa parantamiseksi](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Haluat, että älylaitteesi lähettää ääntä pilveen käsiteltäväksi vain silloin, kun käytät sitä, ei silloin, kun se kuulee ääntä kotonasi, ääntä, joka voi sisältää yksityisiä kokouksia tai intiimejä vuorovaikutuksia. Useimmat älylaitteet toimivat *herätyssanan* avulla, avainlauseen, kuten "Alexa", "Hey Siri" tai "OK Google", joka saa laitteen 'heräämään' ja kuuntelemaan, mitä sanot, kunnes se havaitsee puheessasi tauon, mikä osoittaa, että olet lopettanut puhumisen laitteelle.

> 🎓 Herätyssanan tunnistusta kutsutaan myös *avainsanan tunnistukseksi* tai *avainsanan havaitsemiseksi*.

Nämä herätyssanat tunnistetaan laitteessa, ei pilvessä. Älylaitteissa on pieniä tekoälymalleja, jotka toimivat laitteessa ja kuuntelevat herätyssanaa, ja kun se havaitaan, ne alkavat lähettää ääntä pilveen tunnistettavaksi. Nämä mallit ovat hyvin erikoistuneita ja kuuntelevat vain herätyssanaa.

> 💁 Jotkut teknologiayritykset lisäävät laitteisiinsa enemmän yksityisyyttä ja tekevät osan puheentunnistuksesta laitteessa. Apple on ilmoittanut, että osana vuoden 2021 iOS- ja macOS-päivityksiään ne tukevat puheentunnistusta laitteessa ja pystyvät käsittelemään monia pyyntöjä ilman pilven käyttöä. Tämä on mahdollista, koska heidän laitteissaan on tehokkaita prosessoreita, jotka voivat ajaa koneoppimismalleja.

✅ Mitkä mielestäsi ovat yksityisyyteen ja etiikkaan liittyvät vaikutukset, kun ääntä tallennetaan pilveen? Pitäisikö tämä ääni tallentaa, ja jos kyllä, miten? Onko mielestäsi tallenteiden käyttö lainvalvonnassa hyvä kompromissi yksityisyyden menetykselle?

Herätyssanan tunnistus käyttää yleensä tekniikkaa nimeltä TinyML, joka muuntaa koneoppimismalleja toimimaan mikro-ohjaimilla. Nämä mallit ovat kooltaan pieniä ja kuluttavat hyvin vähän energiaa.

Välttääkseen herätyssanamallin kouluttamisen ja käytön monimutkaisuuden, tässä oppitunnissa rakennettava älykäs ajastin käyttää painiketta puheentunnistuksen aktivoimiseen.

> 💁 Jos haluat kokeilla herätyssanamallin luomista, joka toimii Wio Terminalilla tai Raspberry Pi:llä, tutustu tähän [Edge Impulsen vastaaminen ääneesi -oppaaseen](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Jos haluat käyttää tietokonettasi tähän, voit kokeilla [Microsoft-dokumenttien Custom Keyword -pikaopasta](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Muunna puhe tekstiksi

![Puhepalveluiden logo](../../../../../translated_images/fi/azure-speech-logo.a1f08c4befb0159f.webp)

Aivan kuten kuvien luokittelussa aiemmassa projektissa, on olemassa valmiita tekoälypalveluita, jotka voivat ottaa puheen äänitiedostona ja muuntaa sen tekstiksi. Yksi tällainen palvelu on Puhepalvelu, joka on osa Cognitive Services -palveluita, valmiita tekoälypalveluita, joita voit käyttää sovelluksissasi.

### Tehtävä - konfiguroi puhetekoälyresurssi

1. Luo tämän projektin resurssiryhmä nimeltä `smart-timer`.

1. Käytä seuraavaa komentoa luodaksesi ilmaisen puhepalveluresurssin:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Korvaa `<location>` sijainnilla, jota käytit luodessasi resurssiryhmän.

1. Tarvitset API-avaimen päästäksesi puhepalveluresurssiin koodistasi. Suorita seuraava komento saadaksesi avaimen:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopioi yksi avaimista.

### Tehtävä - muunna puhe tekstiksi

Käy läpi asiaankuuluva opas muuntaaksesi puheen tekstiksi IoT-laitteellasi:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Yksikorttitietokone - Raspberry Pi](pi-speech-to-text.md)
* [Yksikorttitietokone - Virtuaalilaite](virtual-device-speech-to-text.md)

---

## 🚀 Haaste

Puheentunnistus on ollut olemassa pitkään ja kehittyy jatkuvasti. Tutki nykyisiä ominaisuuksia ja vertaa, miten ne ovat kehittyneet ajan myötä, mukaan lukien kuinka tarkkoja koneelliset transkriptiot ovat verrattuna ihmisiin.

Mitä mieltä olet, mitä tulevaisuus tuo puheentunnistukselle?

## Luentojälkeinen kysely

[Luentojälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Kertaus & Itseopiskelu

* Lue eri mikrofonityypeistä ja niiden toiminnasta [Musician's HQ:n artikkelista dynaamisten ja kondensaattorimikrofonien eroista](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Lue lisää Cognitive Services -puhepalvelusta [Microsoft Docsin puhepalvelun dokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Lue avainsanan tunnistuksesta [Microsoft Docsin avainsanan tunnistuksen dokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Tehtävä

[](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.