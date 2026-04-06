# Tuen lisääminen useille kielille

![Tämän oppitunnin sketchnote-yhteenveto](../../../../../translated_images/fi/lesson-24.4246968ed058510a.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tässä videossa esitellään Azure-puhepalveluita, mukaan lukien aiemmissa oppitunneissa käsitellyt puhe tekstiksi ja teksti puheeksi -toiminnot, sekä tämän oppitunnin aiheena oleva puheen kääntäminen:

[![Puheen tunnistaminen muutamalla Python-rivillä Microsoft Build 2020 -tapahtumassa](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Johdanto

Viimeisten kolmen oppitunnin aikana opit muuntamaan puhetta tekstiksi, ymmärtämään kieltä ja muuntamaan tekstiä puheeksi tekoälyn avulla. Toinen ihmisten viestinnän osa-alue, jossa tekoäly voi auttaa, on kielten kääntäminen – esimerkiksi englannista ranskaksi.

Tässä oppitunnissa opit käyttämään tekoälyä tekstin kääntämiseen, jotta älykäs ajastimesi voi toimia useilla kielillä.

Tässä oppitunnissa käsitellään:

* [Tekstin kääntäminen](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Käännöspalvelut](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Kääntäjäresurssin luominen](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Useiden kielten tukeminen sovelluksissa käännösten avulla](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Tekstin kääntäminen tekoälypalvelun avulla](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Tämä on projektin viimeinen oppitunti, joten tämän oppitunnin ja tehtävän suorittamisen jälkeen muista siivota pilvipalvelusi. Tarvitset palveluita tehtävän suorittamiseen, joten varmista, että suoritat sen ensin.
>
> Katso tarvittaessa ohjeet [projektin siivoamisoppaasta](../../../clean-up.md).

## Tekstin kääntäminen

Tekstin kääntäminen on ollut tietojenkäsittelytieteen ongelma, jota on tutkittu yli 70 vuoden ajan. Vasta tekoälyn ja laskentatehon kehityksen myötä käännösten laatu on lähestynyt ihmiskääntäjien tasoa.

> 💁 Käännösten alkuperä voidaan jäljittää vielä kauemmas, 800-luvulle, jolloin [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), arabialainen kryptografi, kehitti kielten kääntämiseen liittyviä tekniikoita.

### Konekäännökset

Tekstin kääntäminen alkoi teknologiana, jota kutsutaan konekääntämiseksi (Machine Translation, MT). Se voi kääntää eri kieliparien välillä korvaamalla sanoja toisilla ja käyttämällä tekniikoita, jotka valitsevat oikeat tavat kääntää lauseita tai lauseenosia silloin, kun yksinkertainen sanasta sanaan -käännös ei toimi.

> 🎓 Kun kääntäjät tukevat käännöksiä yhden kielen ja toisen välillä, näitä kutsutaan *kielipareiksi*. Eri työkalut tukevat eri kielipareja, eikä tuki välttämättä ole kattava. Esimerkiksi kääntäjä voi tukea englannin ja espanjan välistä käännöstä sekä espanjan ja italian välistä käännöstä, mutta ei englannin ja italian välistä käännöstä.

Esimerkiksi englanninkielisen lauseen "Hello world" kääntäminen ranskaksi voidaan tehdä korvaamalla sanat: "Bonjour" vastaa "Hello" ja "le monde" vastaa "world", jolloin saadaan oikea käännös "Bonjour le monde".

Korvaukset eivät kuitenkaan toimi, kun eri kielissä käytetään erilaisia tapoja ilmaista sama asia. Esimerkiksi englanninkielinen lause "My name is Jim" kääntyy ranskaksi "Je m'appelle Jim", joka tarkoittaa kirjaimellisesti "Minä kutsun itseäni Jimiksi". "Je" tarkoittaa "minä", "moi" tarkoittaa "minua", mutta se yhdistetään verbiin, koska se alkaa vokaalilla, jolloin siitä tulee "m'", "appelle" tarkoittaa kutsua, ja "Jim" ei käänny, koska se on nimi eikä sana, joka voidaan kääntää. Myös sanajärjestys voi aiheuttaa ongelmia – yksinkertainen korvaus "Je m'appelle Jim" muuttuu englanniksi "I myself call Jim", mikä on eri sanajärjestys kuin alkuperäisessä lauseessa.

> 💁 Jotkin sanat eivät koskaan käänny – nimeni on Jim riippumatta siitä, millä kielellä esittelen itseni. Kun käännetään kielille, jotka käyttävät eri aakkostoja tai eri kirjaimia eri äänteille, sanat voidaan *translitteroida*, eli valita kirjaimia tai merkkejä, jotka tuottavat saman äänen kuin alkuperäinen sana.

Myös idiomit ovat haaste kääntämisessä. Idiomit ovat ilmauksia, joiden merkitys on eri kuin sanojen suora tulkinta. Esimerkiksi englanninkielinen idiomi "I've got ants in my pants" ei viittaa kirjaimellisesti muurahaisiin vaatteissa, vaan levottomuuteen. Jos tämän kääntäisi saksaksi, se hämmentäisi kuulijaa, sillä saksaksi vastaava ilmaus on "I have bumble bees in the bottom".

> 💁 Eri alueet tuovat omat monimutkaisuutensa. Esimerkiksi idiomissa "ants in your pants" amerikkalaisessa englannissa "pants" tarkoittaa ulkovaatteita, kun taas brittiläisessä englannissa "pants" tarkoittaa alusvaatteita.

✅ Jos puhut useita kieliä, mieti joitakin ilmauksia, joita ei voi suoraan kääntää.

Konekäännösjärjestelmät perustuvat suuriin sääntötietokantoihin, jotka kuvaavat, miten tiettyjä lauseita ja idiomeja käännetään, sekä tilastollisiin menetelmiin, joilla valitaan sopivimmat käännökset mahdollisista vaihtoehdoista. Näissä tilastollisissa menetelmissä käytetään valtavia tietokantoja, jotka sisältävät ihmisten kääntämiä tekstejä useille kielille, jotta voidaan valita todennäköisin käännös. Tätä tekniikkaa kutsutaan *tilastolliseksi konekääntämiseksi*. Monet näistä järjestelmistä käyttävät välivaiheita, joissa kieli käännetään ensin välivaiheeseen ja sitten siitä toiseen kieleen. Näin uusien kielten lisääminen vaatii vain käännöksiä välivaiheeseen ja siitä pois, eikä kaikkien muiden kielten välillä.

### Neuroverkkoihin perustuvat käännökset

Neuroverkkoihin perustuvat käännökset hyödyntävät tekoälyn voimaa kääntämiseen, yleensä kääntäen kokonaisia lauseita yhdellä mallilla. Nämä mallit koulutetaan valtavilla ihmisten kääntämillä aineistoilla, kuten verkkosivuilla, kirjoilla ja Yhdistyneiden kansakuntien asiakirjoilla.

Neuroverkkoihin perustuvat käännösmallit ovat yleensä pienempiä kuin konekäännösmallit, koska ne eivät tarvitse valtavia tietokantoja lauseista ja idiomeista. Modernit tekoälypalvelut, jotka tarjoavat käännöksiä, yhdistävät usein useita tekniikoita, kuten tilastollista konekääntämistä ja neuroverkkoihin perustuvaa kääntämistä.

Mikään kielipari ei ole täysin 1:1 käännettävissä. Eri käännösmallit tuottavat hieman erilaisia tuloksia riippuen siitä, millä aineistolla malli on koulutettu. Käännökset eivät myöskään aina ole symmetrisiä – jos käännät lauseen yhdeltä kieleltä toiselle ja sitten takaisin alkuperäiselle kielelle, saatat saada hieman erilaisen lauseen tulokseksi.

✅ Kokeile eri verkkokääntäjiä, kuten [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) tai Applen käännössovellusta. Vertaa muutamien lauseiden käännöksiä. Kokeile myös kääntää yhdessä palvelussa ja kääntää takaisin toisessa.

## Käännöspalvelut

On olemassa useita tekoälypalveluita, joita voit käyttää sovelluksissasi puheen ja tekstin kääntämiseen.

### Cognitive Services -puhepalvelu

![Puhepalvelun logo](../../../../../translated_images/fi/azure-speech-logo.a1f08c4befb0159f.webp)

Puhepalvelu, jota olet käyttänyt viimeisissä oppitunneissa, sisältää käännöstoimintoja puheen tunnistamiseen. Kun tunnistat puhetta, voit pyytää puheen tekstiversion paitsi samalla kielellä myös muilla kielillä.

> 💁 Tämä toiminto on saatavilla vain puhe-SDK:sta, ei REST-rajapinnasta.

### Cognitive Services -kääntäjäpalvelu

![Kääntäjäpalvelun logo](../../../../../translated_images/fi/azure-translator-logo.c6ed3a4a433edfd2.webp)

Kääntäjäpalvelu on omistettu käännöspalvelu, joka voi kääntää tekstiä yhdeltä kieleltä yhdelle tai useammalle kohdekielelle. Kääntämisen lisäksi se tukee monia lisäominaisuuksia, kuten kirosanojen peittämistä. Se mahdollistaa myös tietyn käännöksen määrittämisen tietylle sanalle tai lauseelle, jotta voit hallita termejä, joita ei haluta kääntää, tai käyttää tiettyä tunnettua käännöstä.

Esimerkiksi lauseen "I have a Raspberry Pi", joka viittaa yksikorttitietokoneeseen, kääntäminen toiselle kielelle, kuten ranskaksi, halutaan säilyttää "Raspberry Pi" muuttumattomana, jolloin saadaan "J’ai un Raspberry Pi" eikä "J’ai une pi aux framboises".

## Kääntäjäresurssin luominen

Tätä oppituntia varten tarvitset kääntäjäresurssin. Käytät REST-rajapintaa tekstin kääntämiseen.

### Tehtävä – kääntäjäresurssin luominen

1. Suorita seuraava komento terminaalissasi tai komentokehotteessasi luodaksesi kääntäjäresurssin `smart-timer`-resurssiryhmään.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Korvaa `<location>` sijainnilla, jota käytit resurssiryhmää luodessasi.

1. Hanki kääntäjäpalvelun avain:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Ota kopio yhdestä avaimesta.

## Useiden kielten tukeminen sovelluksissa käännösten avulla

Ihannetapauksessa koko sovelluksesi ymmärtäisi mahdollisimman monta eri kieltä, puheen kuuntelusta kielen ymmärtämiseen ja vastauksen antamiseen puheena. Tämä on kuitenkin paljon työtä, joten käännöspalvelut voivat nopeuttaa sovelluksen toimitusaikaa.

![Älykkään ajastimen arkkitehtuuri, joka kääntää japanin englanniksi, käsittelee englanniksi ja kääntää takaisin japaniksi](../../../../../translated_images/fi/translated-smart-timer.08ac20057fdc5c37.webp)

Kuvittele, että rakennat älykästä ajastinta, joka käyttää englantia alusta loppuun: ymmärtää puhuttua englantia ja muuntaa sen tekstiksi, suorittaa kielen ymmärtämisen englanniksi, luo vastaukset englanniksi ja vastaa englanninkielisellä puheella. Jos haluaisit lisätä tuen japanille, voisit aloittaa kääntämällä puhutun japanin englanniksi tekstiksi, pitää sovelluksen ytimen ennallaan ja kääntää vastaustekstin japaniksi ennen kuin vastaat puheella. Tämä mahdollistaisi japanin tuen lisäämisen nopeasti, ja voit myöhemmin laajentaa täyteen japaninkieliseen tukeen.

> 💁 Konekäännösten haittapuoli on, että eri kielet ja kulttuurit ilmaisevat asioita eri tavoin, joten käännös ei välttämättä vastaa odottamaasi ilmaisua.

Konekäännökset avaavat myös mahdollisuuksia sovelluksille ja laitteille, jotka voivat kääntää käyttäjän luomaa sisältöä sen luomisen aikana. Tieteiskirjallisuudessa esiintyy usein "universaaleja kääntäjiä", laitteita, jotka kääntävät vieraita kieliä (yleensä) amerikkalaiselle englannille. Nämä laitteet ovat vähemmän tieteiskirjallisuutta ja enemmän tiedettä, jos jätetään pois vieraat kielet. Jo nyt on olemassa sovelluksia ja laitteita, jotka tarjoavat reaaliaikaista puheen ja kirjoitetun tekstin kääntämistä yhdistämällä puhe- ja käännöspalveluita.

Yksi esimerkki on [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) -mobiilisovellus, jota esitellään tässä videossa:

[![Microsoft Translator -sovelluksen live-toiminto käytössä](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon

Kuvittele, että sinulla olisi tällainen laite käytettävissäsi, erityisesti matkustaessasi tai ollessasi vuorovaikutuksessa ihmisten kanssa, joiden kieltä et osaa. Automaattiset käännöslaitteet lentokentillä tai sairaaloissa parantaisivat merkittävästi saavutettavuutta.

✅ Tee tutkimusta: Onko markkinoilla kaupallisesti saatavilla olevia käännös-IoT-laitteita? Entä käännöstoimintoja, jotka on sisäänrakennettu älylaitteisiin?

> 👽 Vaikka ei ole olemassa todellisia universaaleja kääntäjiä, jotka mahdollistaisivat keskustelun avaruusolioiden kanssa, [Microsoft Translator tukee klingonia](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Tekstin kääntäminen tekoälypalvelun avulla

Voit käyttää tekoälypalvelua lisätäksesi tämän käännöstoiminnon älykkääseen ajastimeesi.

### Tehtävä – tekstin kääntäminen tekoälypalvelun avulla

Käy läpi asiaankuuluva opas tekstin kääntämiseksi IoT-laitteellasi:

* [Arduino – Wio Terminal](wio-terminal-translate-speech.md)
* [Yksikorttitietokone – Raspberry Pi](pi-translate-speech.md)
* [Yksikorttitietokone – Virtuaalilaite](virtual-device-translate-speech.md)

---

## 🚀 Haaste

Miten konekäännökset voivat hyödyttää muita IoT-sovelluksia älylaitteiden lisäksi? Mieti erilaisia tapoja, joilla käännökset voivat auttaa, ei vain puhuttujen sanojen vaan myös tekstin osalta.

## Oppitunnin jälkeinen kysely

[Oppitunnin jälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Kertaus ja itseopiskelu

* Lue lisää konekääntämisestä [Wikipedia-sivulta konekääntäminen](https://wikipedia.org/wiki/Machine_translation)
* Lue lisää neuroverkkoihin perustuvasta kääntämisestä [Wikipedia-sivulta neuroverkkoihin perustuva kääntäminen](https://wikipedia.org/wiki/Neural_machine_translation)
* Tutustu Microsoftin puhepalveluiden tukemiin kieliin [Microsoft Docs -sivuston puhepalvelun kieli- ja äänitukisivulta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Tehtävä

[Rakenna universaali kääntäjä](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.