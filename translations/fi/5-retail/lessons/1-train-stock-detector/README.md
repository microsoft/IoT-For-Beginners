# Kouluta varastontunnistin

![Tämän oppitunnin yleiskatsaus sketchnotena](../../../../../translated_images/fi/lesson-19.cf6973cecadf080c.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

Tämä video antaa yleiskatsauksen Azure Custom Vision -palvelun objektintunnistuksesta, joka käsitellään tässä oppitunnissa.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Klikkaa yllä olevaa kuvaa katsoaksesi videon

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Johdanto

Edellisessä projektissa käytit tekoälyä kouluttaaksesi kuvien luokittelijan - mallin, joka osaa kertoa, sisältääkö kuva jotain, kuten kypsää tai raakaa hedelmää. Toinen kuvien kanssa käytettävä tekoälymalli on objektintunnistus. Nämä mallit eivät luokittele kuvaa tunnisteiden perusteella, vaan ne koulutetaan tunnistamaan esineitä ja löytämään ne kuvista. Ne eivät vain havaitse, että kuva sisältää esineen, vaan myös sen, missä kohtaa kuvaa esine sijaitsee. Tämä mahdollistaa esineiden laskemisen kuvista.

Tässä oppitunnissa opit objektintunnistuksesta ja sen käytöstä vähittäiskaupassa. Opit myös kouluttamaan objektintunnistimen pilvessä.

Tässä oppitunnissa käsitellään:

* [Objektintunnistus](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektintunnistuksen käyttö vähittäiskaupassa](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektintunnistimen kouluttaminen](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektintunnistimen testaaminen](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektintunnistimen uudelleenkoulutus](../../../../../5-retail/lessons/1-train-stock-detector)

## Objektintunnistus

Objektintunnistus tarkoittaa esineiden havaitsemista kuvista tekoälyn avulla. Toisin kuin edellisessä projektissa kouluttamasi kuvien luokittelija, objektintunnistus ei keskity ennustamaan parasta tunnistetta koko kuvalle, vaan löytämään yhden tai useamman esineen kuvasta.

### Objektintunnistus vs kuvien luokittelu

Kuvien luokittelu keskittyy koko kuvan luokitteluun - mitkä ovat todennäköisyydet, että koko kuva vastaa kutakin tunnistetta. Saat takaisin todennäköisyydet kaikille mallin koulutuksessa käytetyille tunnisteille.

![Kuvien luokittelu cashewpähkinöistä ja tomaattipyreestä](../../../../../translated_images/fi/image-classifier-cashews-tomato.bc2e16ab8f05cf9a.webp)

Yllä olevassa esimerkissä kaksi kuvaa luokitellaan mallilla, joka on koulutettu luokittelemaan cashewpähkinöiden purkkeja tai tomaattipyreen tölkkejä. Ensimmäinen kuva on cashewpähkinöiden purkki, ja kuvien luokittelija antaa seuraavat tulokset:

| Tunniste        | Todennäköisyys |
| --------------- | -------------: |
| `cashewpähkinät` | 98.4%         |
| `tomaattipyree`  | 1.6%          |

Toinen kuva on tomaattipyreen tölkki, ja tulokset ovat:

| Tunniste        | Todennäköisyys |
| --------------- | -------------: |
| `cashewpähkinät` | 0.7%          |
| `tomaattipyree`  | 99.3%         |

Voit käyttää näitä arvoja ja kynnysprosenttia ennustaaksesi, mitä kuvassa on. Mutta entä jos kuvassa olisi useita tomaattipyreen tölkkejä tai sekä cashewpähkinöitä että tomaattipyrettä? Tulokset eivät todennäköisesti antaisi haluamaasi tietoa. Tässä kohtaa objektintunnistus tulee avuksi.

Objektintunnistus tarkoittaa mallin kouluttamista tunnistamaan esineitä. Sen sijaan, että annat mallille kuvia, joissa on esine, ja kerrot, että jokainen kuva vastaa yhtä tunnistetta, korostat kuvan osan, joka sisältää tietyn esineen, ja annat sille tunnisteen. Voit merkitä yhden esineen kuvaan tai useita. Näin malli oppii, miltä esine itsessään näyttää, ei vain miltä kuvat, joissa esine esiintyy, näyttävät.

Kun käytät mallia ennustamiseen, et saa takaisin tunnisteiden ja prosenttien listaa, vaan listan havaituista esineistä, niiden rajauslaatikoista ja todennäköisyydestä, että rajauslaatikko sisältää annetun tunnisteen mukaisen esineen.

> 🎓 *Rajauslaatikot* ovat laatikoita esineen ympärillä.

![Objektintunnistus cashewpähkinöistä ja tomaattipyreestä](../../../../../translated_images/fi/object-detector-cashews-tomato.1af7c26686b4db0e.webp)

Yllä olevassa kuvassa on sekä cashewpähkinöiden purkki että kolme tomaattipyreen tölkkiä. Objektintunnistin havaitsi cashewpähkinät ja palautti rajauslaatikon, joka sisältää cashewpähkinät, sekä todennäköisyyden, että rajauslaatikko sisältää esineen, tässä tapauksessa 97.6%. Objektintunnistin havaitsi myös kolme tomaattipyreen tölkkiä ja antoi kolme erillistä rajauslaatikkoa, yhden jokaiselle havaitulle tölkille, ja jokaiselle prosentuaalisen todennäköisyyden, että rajauslaatikko sisältää tomaattipyreen tölkin.

✅ Mieti erilaisia skenaarioita, joissa voisit käyttää kuvapohjaisia tekoälymalleja. Mitkä niistä tarvitsisivat luokittelua ja mitkä objektintunnistusta?

### Miten objektintunnistus toimii

Objektintunnistus käyttää monimutkaisia koneoppimismalleja. Nämä mallit toimivat jakamalla kuvan useisiin soluihin ja tarkistamalla, vastaako rajauslaatikon keskipiste kuvaa, joka vastaa yhtä mallin koulutuksessa käytetyistä kuvista. Voit ajatella tätä ikään kuin suorittaisit kuvien luokittelua eri osissa kuvaa etsiäksesi osumia.

> 💁 Tämä on suuri yksinkertaistus. Objektintunnistukseen on olemassa monia tekniikoita, ja voit lukea niistä lisää [Wikipedian objektintunnistussivulta](https://wikipedia.org/wiki/Object_detection).

On olemassa useita erilaisia malleja, jotka voivat suorittaa objektintunnistusta. Yksi erityisen tunnettu malli on [YOLO (You Only Look Once)](https://pjreddie.com/darknet/yolo/), joka on erittäin nopea ja voi tunnistaa 20 erilaista esineluokkaa, kuten ihmisiä, koiria, pulloja ja autoja.

✅ Lue lisää YOLO-mallista osoitteessa [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Objektintunnistusmalleja voidaan kouluttaa uudelleen käyttämällä siirto-oppimista tunnistamaan mukautettuja esineitä.

## Objektintunnistuksen käyttö vähittäiskaupassa

Objektintunnistuksella on monia käyttötarkoituksia vähittäiskaupassa. Näitä ovat esimerkiksi:

* **Varaston tarkistus ja laskenta** - tunnistaa, kun hyllyillä oleva varasto on vähissä. Jos varasto on liian vähissä, voidaan lähettää ilmoituksia henkilökunnalle tai roboteille hyllyjen täyttämiseksi.
* **Maskin tunnistus** - kaupoissa, joissa on maskipolitiikka julkisten terveyshaasteiden aikana, objektintunnistus voi tunnistaa maskia käyttävät ja maskittomat henkilöt.
* **Automaattinen laskutus** - tunnistaa hyllyiltä otetut tuotteet automaattisissa kaupoissa ja laskuttaa asiakkaita oikein.
* **Vaarojen tunnistus** - tunnistaa lattialla olevat rikkoutuneet esineet tai läikkyneet nesteet ja hälyttää siivoushenkilökunnan.

✅ Tee tutkimusta: Mitä muita käyttötapauksia objektintunnistukselle voisi olla vähittäiskaupassa?

## Objektintunnistimen kouluttaminen

Voit kouluttaa objektintunnistimen Custom Vision -palvelussa samalla tavalla kuin koulutit kuvien luokittelijan.

### Tehtävä - luo objektintunnistin

1. Luo tämän projektin resurssiryhmä nimeltä `stock-detector`.

1. Luo ilmainen Custom Vision -koulutusresurssi ja ilmainen Custom Vision -ennustamisresurssi `stock-detector`-resurssiryhmään. Nimeä ne `stock-detector-training` ja `stock-detector-prediction`.

    > 💁 Voit luoda vain yhden ilmaisen koulutus- ja ennustamisresurssin, joten varmista, että olet poistanut aiempien oppituntien projektit.

    > ⚠️ Voit viitata [ohjeisiin koulutus- ja ennustamisresurssien luomisesta projektin 4, oppitunnin 1 kohdasta tarvittaessa](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Avaa Custom Vision -portaali osoitteessa [CustomVision.ai](https://customvision.ai) ja kirjaudu sisään Microsoft-tililläsi, jota käytit Azure-tilisi kanssa.

1. Seuraa [Microsoft-dokumentaation objektintunnistimen luomisen pikaohjeen Luo uusi projekti -osaa](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) luodaksesi uuden Custom Vision -projektin. Käyttöliittymä voi muuttua, ja nämä dokumentit ovat aina ajantasaisin viite.

    Nimeä projektisi `stock-detector`.

    Kun luot projektisi, varmista, että käytät aiemmin luomaasi `stock-detector-training`-resurssia. Valitse *Object Detection* -projektityyppi ja *Products on Shelves* -toimialue.

    ![Custom Vision -projektin asetukset, joissa nimi on asetettu "fruit-quality-detector", ei kuvausta, resurssi on "fruit-quality-detector-training", projektityyppi on "classification", luokittelutyypit ovat "multi class" ja toimialue on "food"](../../../../../translated_images/fi/custom-vision-create-object-detector-project.32d4fb9aa8e7e737.webp)

    ✅ *Products on Shelves* -toimialue on erityisesti suunniteltu hyllyillä olevien tuotteiden tunnistamiseen. Lue lisää eri toimialueista [Microsoft-dokumentaation toimialueen valinta -osiosta](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection).

✅ Käytä hetki aikaa tutustuaksesi Custom Vision -käyttöliittymään objektintunnistimellesi.

### Tehtävä - kouluta objektintunnistin

Kouluttaaksesi mallisi tarvitset joukon kuvia, jotka sisältävät tunnistettavia esineitä.

1. Kerää kuvia, jotka sisältävät tunnistettavan esineen. Tarvitset vähintään 15 kuvaa, joissa on jokainen tunnistettava esine eri kulmista ja valaistusolosuhteista, mutta mitä enemmän, sen parempi. Tämä objektintunnistin käyttää *Products on Shelves* -toimialuetta, joten yritä asetella esineet ikään kuin ne olisivat kaupan hyllyllä. Tarvitset myös muutamia kuvia mallin testaamista varten. Jos tunnistat useampaa kuin yhtä esinettä, haluat joitakin testikuvia, jotka sisältävät kaikki esineet.

    > 💁 Kuvat, joissa on useita eri esineitä, lasketaan mukaan 15 kuvan vähimmäismäärään kaikkien kuvassa olevien esineiden osalta.

    Kuviesi tulisi olla png- tai jpeg-muodossa, kooltaan alle 6 MB. Jos luot ne esimerkiksi iPhonella, ne voivat olla korkearesoluutioisia HEIC-kuvia, joten ne täytyy muuntaa ja mahdollisesti pienentää. Mitä enemmän kuvia, sen parempi, ja sinulla tulisi olla saman verran kypsiä ja raakoja esineitä.

    Malli on suunniteltu hyllyillä oleville tuotteille, joten yritä ottaa kuvat esineistä hyllyillä.

    Löydät esimerkkikuvia, joita voit käyttää, [images](../../../../../5-retail/lessons/1-train-stock-detector/images)-kansiosta, jossa on kuvia cashewpähkinöistä ja tomaattipyreestä.

1. Seuraa [Microsoft-dokumentaation objektintunnistimen luomisen pikaohjeen Lataa ja merkitse kuvat -osaa](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) ladataksesi koulutuskuvasi. Luo asiaankuuluvat tunnisteet esineiden tyypin mukaan, joita haluat tunnistaa.

    ![Latausikkunat, joissa ladataan kypsien ja raakojen banaanien kuvia](../../../../../translated_images/fi/image-upload-object-detector.77c7892c3093cb59.webp)

    Kun piirrät rajauslaatikoita esineille, pidä ne tiukasti esineen ympärillä. Kuvien merkitseminen voi viedä aikaa, mutta työkalu tunnistaa, mitä se uskoo olevan rajauslaatikot, mikä nopeuttaa prosessia.

    ![Tomaattipyreen merkitseminen](../../../../../translated_images/fi/object-detector-tag-tomato-paste.f47c362fb0f0eb58.webp)

    > 💁 Jos sinulla on yli 15 kuvaa kutakin esinettä varten, voit kouluttaa mallin 15 kuvan jälkeen ja käyttää **Ehdotetut tunnisteet** -ominaisuutta. Tämä käyttää koulutettua mallia tunnistamaan esineet merkitsemättömistä kuvista. Voit sitten vahvistaa havaitut esineet tai hylätä ja piirtää rajauslaatikot uudelleen. Tämä voi säästää *paljon* aikaa.

1. Seuraa [Microsoft-dokumentaation objektintunnistimen luomisen pikaohjeen Kouluta tunnistin -osaa](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) kouluttaaksesi objektintunnistimen merkittyjen kuviesi avulla.

    Sinulle annetaan valinta koulutustyypistä. Valitse **Pikakoulutus**.

Objektintunnistin alkaa kouluttautua. Koulutus kestää muutaman minuutin.

## Testaa objektintunnistin

Kun objektintunnistin on koulutettu, voit testata sitä antamalla sille uusia kuvia, joista se tunnistaa esineitä.

### Tehtävä - testaa objektintunnistin

1. Käytä **Pikatesti**-painiketta ladataksesi testikuvia ja varmistaaksesi, että esineet tunnistetaan. Käytä aiemmin luomiasi testikuvia, älä mitään koulutuksessa käytettyjä kuvia.

    ![3 tomaattipyreen tölkkiä havaittu todennäköisyyksillä 38%, 35.5% ja 34.6%](../../../../../translated_images/fi/object-detector-detected-tomato-paste.52656fe87af4c37b.webp)

1. Kokeile kaikkia käytettävissäsi olevia testikuvia ja tarkkaile todennäköisyyksiä.

## Kouluta objektintunnistin uudelleen

Kun testaat objektintunnistinta, se ei välttämättä anna odottamiasi tuloksia, kuten kuvien luokittelijoiden kanssa edellisessä projektissa. Voit parantaa objektintunnistinta kouluttamalla sen uudelleen kuvilla, joissa se tekee virheitä.

Joka kerta, kun teet ennusteen pikatestivaihtoehdolla, kuva ja tulokset tallennetaan. Voit käyttää näitä kuvia mallin uudelleenkoulutukseen.

1. Käytä **Ennusteet**-välilehteä löytääksesi testauksessa käyttämäsi kuvat.

1. Vahvista kaikki tarkat havainnot, poista virheelliset ja lisää puuttuvat esineet.

1. Kouluta ja testaa malli uudelleen.

---

## 🚀 Haaste

Mitä tapahtuisi, jos käyttäisit objektintunnistinta samannäköisillä esineillä, kuten saman merkin tomaattipyreen ja tomaattimurskan tölkeillä?

Jos sinulla on samannäköisiä esineitä, testaa lisäämällä niiden kuvia objektintunnistimeesi.

## Jälkikysely
[Luennon jälkeinen kysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Kertaus ja itseopiskelu

* Kun koulutit objektintunnistinta, näit arvoja kuten *Precision*, *Recall* ja *mAP*, jotka arvioivat luotua mallia. Lue lisää näistä arvoista käyttämällä [Microsoft-dokumentaation objektintunnistimen arviointiosuutta Build an object detector -pikaoppaassa](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Lue lisää objektintunnistuksesta [Wikipedian objektintunnistussivulta](https://wikipedia.org/wiki/Object_detection)

## Tehtävä

[Vertaa toimialueita](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.