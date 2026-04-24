# Tarkista varasto IoT-laitteella

![Tämän oppitunnin yleiskuvaus sketchnotena](../../../../../translated_images/fi/lesson-20.0211df9551a8abb3.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Johdanto

Edellisessä oppitunnissa opit objektintunnistuksen eri käyttötarkoituksista vähittäiskaupassa. Opit myös kouluttamaan objektintunnistimen tunnistamaan varastoa. Tässä oppitunnissa opit käyttämään objektintunnistinta IoT-laitteeltasi varaston laskemiseen.

Tässä oppitunnissa käsitellään:

* [Varaston laskeminen](../../../../../5-retail/lessons/2-check-stock-device)
* [Kutsu objektintunnistinta IoT-laitteeltasi](../../../../../5-retail/lessons/2-check-stock-device)
* [Rajauslaatikot](../../../../../5-retail/lessons/2-check-stock-device)
* [Mallin uudelleenkoulutus](../../../../../5-retail/lessons/2-check-stock-device)
* [Laske varasto](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Tämä on projektin viimeinen oppitunti, joten kun olet suorittanut tämän oppitunnin ja tehtävän, muista siivota pilvipalvelusi. Tarvitset palveluita tehtävän suorittamiseen, joten varmista, että teet sen ensin.
>
> Katso tarvittaessa [projektin siivousopas](../../../clean-up.md) saadaksesi ohjeita.

## Varaston laskeminen

Objektintunnistimia voidaan käyttää varaston tarkistamiseen, joko laskemalla varastoa tai varmistamalla, että varasto on oikeassa paikassa. IoT-laitteita, joissa on kamerat, voidaan sijoittaa ympäri kauppaa varaston valvontaan, alkaen tärkeistä paikoista, joissa tuotteiden täydennys on kriittistä, kuten alueista, joissa on pieni määrä arvokkaita tuotteita.

Esimerkiksi, jos kamera osoittaa hyllyyn, joka voi pitää 8 tomaattipyreen purkkia, ja objektintunnistin havaitsee vain 7 purkkia, yksi puuttuu ja se täytyy täydentää.

![7 tomaattipyreen purkkia hyllyllä, 4 ylhäällä ja 3 alhaalla](../../../../../translated_images/fi/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

Yllä olevassa kuvassa objektintunnistin on havainnut 7 tomaattipyreen purkkia hyllyllä, joka voi pitää 8 purkkia. IoT-laite ei ainoastaan voi lähettää ilmoitusta täydennystarpeesta, vaan se voi myös antaa tiedon puuttuvan tuotteen sijainnista, mikä on tärkeää, jos käytät robotteja hyllyjen täydennykseen.

> 💁 Riippuen kaupasta ja tuotteen suosiosta, täydennystä ei todennäköisesti tehtäisi, jos vain yksi purkki puuttuu. Sinun täytyy rakentaa algoritmi, joka määrittää täydennystarpeen tuotteesi, asiakkaidesi ja muiden kriteerien perusteella.

✅ Missä muissa tilanteissa voisit yhdistää objektintunnistuksen ja robotit?

Joskus hyllyillä voi olla väärää varastoa. Tämä voi johtua inhimillisestä virheestä täydennyksen aikana tai asiakkaista, jotka muuttavat mielensä ostoksesta ja laittavat tuotteen takaisin ensimmäiseen vapaaseen paikkaan. Kun kyseessä on ei-pilaantuva tuote, kuten säilykkeet, tämä on ärsyttävää. Jos kyseessä on pilaantuva tuote, kuten pakasteet tai kylmätuotteet, tämä voi tarkoittaa, että tuotetta ei voi enää myydä, koska voi olla mahdotonta tietää, kuinka kauan tuote oli pois pakastimesta.

Objektintunnistusta voidaan käyttää havaitsemaan odottamattomia tuotteita, ja taas IoT-laite voi ilmoittaa ihmiselle tai robotille tuotteen palauttamisesta heti, kun se havaitaan.

![Väärä maissipurkki tomaattipyreen hyllyllä](../../../../../translated_images/fi/stock-rogue-corn.be1f3ada8c457854.webp)

Yllä olevassa kuvassa maissipurkki on laitettu hyllylle tomaattipyreen viereen. Objektintunnistin on havainnut tämän, jolloin IoT-laite voi ilmoittaa ihmiselle tai robotille purkin palauttamisesta oikeaan paikkaan.

## Kutsu objektintunnistinta IoT-laitteeltasi

Edellisessä oppitunnissa kouluttamaasi objektintunnistinta voidaan kutsua IoT-laitteeltasi.

### Tehtävä - julkaise objektintunnistimen iterointi

Iteroinnit julkaistaan Custom Vision -portaalista.

1. Avaa Custom Vision -portaali osoitteessa [CustomVision.ai](https://customvision.ai) ja kirjaudu sisään, jos et ole jo tehnyt niin. Avaa sitten `stock-detector`-projektisi.

1. Valitse **Performance**-välilehti ylävalikosta.

1. Valitse uusin iterointi *Iterations*-listasta sivupalkista.

1. Valitse iteroinnin **Publish**-painike.

    ![Julkaisupainike](../../../../../translated_images/fi/custom-vision-object-detector-publish-button.34ee379fc650ccb9.webp)

1. *Publish Model* -valintaikkunassa aseta *Prediction resource* viime oppitunnissa luomaasi `stock-detector-prediction`-resurssiin. Jätä nimi `Iteration2`:ksi ja valitse **Publish**-painike.

1. Kun iterointi on julkaistu, valitse **Prediction URL** -painike. Tämä näyttää ennustuksen API:n tiedot, joita tarvitset mallin kutsumiseen IoT-laitteeltasi. Alempi osio on merkitty *If you have an image file*, ja nämä ovat tarvitsemasi tiedot. Kopioi näytetty URL, joka näyttää suunnilleen tältä:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Missä `<location>` on sijainti, jonka käytit luodessasi Custom Vision -resurssin, ja `<id>` on pitkä ID, joka koostuu kirjaimista ja numeroista.

    Kopioi myös *Prediction-Key*-arvo. Tämä on turvallinen avain, joka täytyy välittää mallia kutsuttaessa. Vain sovellukset, jotka välittävät tämän avaimen, voivat käyttää mallia, muut sovellukset hylätään.

    ![Ennustuksen API-valintaikkuna, joka näyttää URL:n ja avaimen](../../../../../translated_images/fi/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Kun uusi iterointi julkaistaan, sillä on eri nimi. Miten luulet, että IoT-laitteen käyttämä iterointi vaihdetaan?

### Tehtävä - kutsu objektintunnistinta IoT-laitteeltasi

Seuraa alla olevia ohjeita käyttääksesi objektintunnistinta IoT-laitteeltasi:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Yksikorttitietokone - Raspberry Pi/virtuaalilaite](single-board-computer-object-detector.md)

## Rajauslaatikot

Kun käytät objektintunnistinta, saat takaisin paitsi havaitut objektit niiden tunnisteiden ja todennäköisyyksien kanssa, myös objektien rajauslaatikot. Nämä määrittävät alueen, jossa objektintunnistin havaitsi objektin annetulla todennäköisyydellä.

> 💁 Rajauslaatikko on laatikko, joka määrittää alueen, joka sisältää havaitun objektin, laatikko, joka määrittää objektin rajat.

Ennustuksen tulokset **Predictions**-välilehdellä Custom Visionissa sisältävät rajauslaatikot, jotka on piirretty kuvan päälle, joka lähetettiin ennustettavaksi.

![4 tomaattipyreen purkkia hyllyllä, ennustukset 35.8%, 33.5%, 25.7% ja 16.6%](../../../../../translated_images/fi/custom-vision-stock-prediction.942266ab1bcca341.webp)

Yllä olevassa kuvassa havaittiin 4 tomaattipyreen purkkia. Tuloksissa punainen neliö on lisätty jokaisen havaitun objektin päälle, mikä osoittaa kuvan rajauslaatikon.

✅ Avaa ennustukset Custom Visionissa ja tarkista rajauslaatikot.

Rajauslaatikot määritetään neljällä arvolla - yläreuna, vasen reuna, korkeus ja leveys. Nämä arvot ovat asteikolla 0-1, mikä edustaa sijainteja prosentteina kuvan koosta. Alkuperä (0,0-sijainti) on kuvan vasen yläkulma, joten yläreunan arvo on etäisyys yläreunasta, ja rajauslaatikon alareuna on yläreuna plus korkeus.

![Rajauslaatikko tomaattipyreen purkin ympärillä](../../../../../translated_images/fi/bounding-box.1420a7ea0d3d15f7.webp)

Yllä oleva kuva on 600 pikseliä leveä ja 800 pikseliä korkea. Rajauslaatikko alkaa 320 pikseliä alaspäin, mikä antaa yläreunan arvoksi 0.4 (800 x 0.4 = 320). Vasemmalta raja alkaa 240 pikseliä sivulle, mikä antaa vasemman reunan arvoksi 0.4 (600 x 0.4 = 240). Rajauslaatikon korkeus on 240 pikseliä, mikä antaa korkeuden arvoksi 0.3 (800 x 0.3 = 240). Rajauslaatikon leveys on 120 pikseliä, mikä antaa leveyden arvoksi 0.2 (600 x 0.2 = 120).

| Koordinaatti | Arvo |
| ------------ | ----: |
| Yläreuna     | 0.4   |
| Vasen reuna  | 0.4   |
| Korkeus      | 0.3   |
| Leveys       | 0.2   |

Prosenttiarvojen käyttö asteikolla 0-1 tarkoittaa, että riippumatta kuvan koosta, rajauslaatikko alkaa 0.4 matkan päästä ylhäältä ja vasemmalta, ja sen korkeus on 0.3 ja leveys 0.2.

Voit käyttää rajauslaatikoita yhdessä todennäköisyyksien kanssa arvioidaksesi, kuinka tarkka havainto on. Esimerkiksi objektintunnistin voi havaita useita objekteja, jotka menevät päällekkäin, esimerkiksi havaitsemalla yhden purkin toisen sisällä. Koodisi voisi tarkistaa rajauslaatikot, ymmärtää, että tämä on mahdotonta, ja jättää huomiotta kaikki objektit, joilla on merkittävä päällekkäisyys muiden objektien kanssa.

![Kaksi rajauslaatikkoa päällekkäin tomaattipyreen purkin ympärillä](../../../../../translated_images/fi/overlap-object-detection.d431e03cae75072a.webp)

Yllä olevassa esimerkissä yksi rajauslaatikko osoittaa ennustetun tomaattipyreen purkin 78.3% todennäköisyydellä. Toinen rajauslaatikko on hieman pienempi ja sisällä ensimmäisessä laatikossa 64.3% todennäköisyydellä. Koodisi voi tarkistaa rajauslaatikot, nähdä niiden olevan täysin päällekkäisiä, ja jättää huomiotta alemman todennäköisyyden, koska ei ole mahdollista, että yksi purkki olisi toisen sisällä.

✅ Voitko keksiä tilanteen, jossa on validia havaita yksi objekti toisen sisällä?

## Mallin uudelleenkoulutus

Kuten kuvien luokittelijan kanssa, voit kouluttaa mallisi uudelleen käyttämällä IoT-laitteesi keräämiä tietoja. Näiden todellisten tietojen käyttö varmistaa, että mallisi toimii hyvin, kun sitä käytetään IoT-laitteelta.

Toisin kuin kuvien luokittelijan kanssa, et voi vain merkitä kuvaa. Sen sijaan sinun täytyy tarkistaa jokainen mallin havaitsema rajauslaatikko. Jos laatikko on väärän asian ympärillä, se täytyy poistaa, ja jos se on väärässä paikassa, se täytyy säätää.

### Tehtävä - kouluta malli uudelleen

1. Varmista, että olet kerännyt joukon kuvia IoT-laitteeltasi.

1. Valitse **Predictions**-välilehdeltä kuva. Näet punaisia laatikoita, jotka osoittavat havaittujen objektien rajauslaatikot.

1. Käy läpi jokainen rajauslaatikko. Valitse se ensin, ja näet ponnahdusikkunan, joka näyttää tunnisteen. Käytä laatikon kulmien kahvoja säätääksesi kokoa tarvittaessa. Jos tunniste on väärä, poista se **X**-painikkeella ja lisää oikea tunniste. Jos rajauslaatikko ei sisällä objektia, poista se roskakori-painikkeella.

1. Sulje editori, kun olet valmis, ja kuva siirtyy **Predictions**-välilehdeltä **Training Images**-välilehdelle. Toista prosessi kaikille ennustuksille.

1. Käytä **Train**-painiketta kouluttaaksesi mallisi uudelleen. Kun se on koulutettu, julkaise iterointi ja päivitä IoT-laitteesi käyttämään uuden iteroinnin URL-osoitetta.

1. Ota koodi käyttöön uudelleen ja testaa IoT-laitteesi.

## Laske varasto

Käyttämällä havaittujen objektien määrää ja rajauslaatikoita yhdessä voit laskea hyllyllä olevan varaston.

### Tehtävä - laske varasto

Seuraa alla olevia ohjeita laskeaksesi varaston IoT-laitteesi objektintunnistimen tulosten avulla:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Yksikorttitietokone - Raspberry Pi/virtuaalilaite](single-board-computer-count-stock.md)

---

## 🚀 Haaste

Voitko havaita väärän varaston? Kouluta mallisi useilla objekteilla ja päivitä sovelluksesi ilmoittamaan, jos väärä varasto havaitaan.

Ehkä voit viedä tämän pidemmälle ja havaita vierekkäiset varastot samalla hyllyllä ja nähdä, onko jotain laitettu väärään paikkaan määrittelemällä rajoituksia rajauslaatikoille.

## Jälkikysely

[Jälkikysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Kertaus ja itseopiskelu

* Lue lisää siitä, miten rakentaa kokonaisvaltainen varastontunnistusjärjestelmä [Out of stock detection at the edge pattern guide on Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Tutustu muihin tapoihin rakentaa kokonaisvaltaisia vähittäiskaupan ratkaisuja yhdistämällä erilaisia IoT- ja pilvipalveluita katsomalla tämä [Behind the scenes of a retail solution - Hands On! video on YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Tehtävä

[Käytä objektintunnistinta reunalla](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa tämän käännöksen käytöstä johtuvista väärinkäsityksistä tai virhetulkinnoista.