# Tarkista hedelmien laatu IoT-laitteella

![Tämän oppitunnin luonnoskuva](../../../../../translated_images/fi/lesson-16.215daf18b00631fb.webp)

> Luonnoskuva: [Nitya Narasimhan](https://github.com/nitya). Klikkaa kuvaa nähdäksesi suuremman version.

## Ennakkokysely

[Ennakkokysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Johdanto

Edellisessä oppitunnissa opit kuvien luokittelijoista ja niiden kouluttamisesta tunnistamaan hyviä ja huonoja hedelmiä. Jotta voit käyttää tätä kuvien luokittelijaa IoT-sovelluksessa, sinun täytyy pystyä ottamaan kuva jollakin kameralla ja lähettämään se pilveen luokiteltavaksi.

Tässä oppitunnissa opit kameran sensoreista ja niiden käytöstä IoT-laitteella kuvan ottamiseksi. Opit myös, kuinka kutsua kuvien luokittelijaa IoT-laitteeltasi.

Tässä oppitunnissa käsitellään:

* [Kameran sensorit](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kuvan ottaminen IoT-laitteella](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kuvien luokittelijan julkaiseminen](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kuvien luokittelu IoT-laitteelta](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Mallin parantaminen](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kameran sensorit

Kameran sensorit, kuten nimi kertoo, ovat kameroita, jotka voit liittää IoT-laitteeseesi. Ne voivat ottaa still-kuvia tai tallentaa videota. Jotkut sensorit palauttavat raakakuvaa, kun taas toiset pakkaavat kuvan esimerkiksi JPEG- tai PNG-tiedostoksi. Yleensä IoT-laitteiden kanssa käytettävät kamerat ovat paljon pienempiä ja matalamman resoluution kuin mihin olet tottunut, mutta saatavilla on myös korkearesoluutioisia kameroita, jotka kilpailevat huippupuhelimien kanssa. Voit hankkia vaihdettavia linssejä, usean kameran kokoonpanoja, infrapunalämpökameroita tai UV-kameroita.

![Valo kulkee linssin läpi ja tarkentuu CMOS-sensorille](../../../../../translated_images/fi/cmos-sensor.75f9cd74decb1371.webp)

Useimmat kameran sensorit käyttävät kuvakennoja, joissa jokainen pikseli on valodiodi. Linssi tarkentaa kuvan kuvakennolle, ja tuhannet tai miljoonat valodiodit havaitsevat niihin osuvan valon ja tallentavat sen pikselidatana.

> 💁 Linssit kääntävät kuvat ylösalaisin, ja kameran sensori kääntää kuvan takaisin oikein päin. Sama tapahtuu silmissäsi – näkemäsi kuva havaitaan ylösalaisin silmän takaosassa, ja aivosi korjaavat sen.

> 🎓 Kuvakenno tunnetaan nimellä aktiivipikselikenno (APS), ja suosituin APS-tyyppi on komplementaarinen metallioksidipuolijohdesensori eli CMOS. Olet ehkä kuullut termin CMOS-sensori käytettävän kameran sensoreista.

Kameran sensorit ovat digitaalisia sensoreita, jotka lähettävät kuvadataa digitaalisena, yleensä kirjaston avulla, joka hoitaa kommunikoinnin. Kamerat käyttävät esimerkiksi SPI-protokollaa suurten datamäärien, kuten kuvien, lähettämiseen – kuvat ovat huomattavasti suurempia kuin esimerkiksi lämpötila-anturin yksittäiset numerot.

✅ Mitä rajoituksia IoT-laitteilla on kuvakoon suhteen? Mieti erityisesti mikro-ohjaimen laitteiston rajoitteita.

## Kuvan ottaminen IoT-laitteella

Voit käyttää IoT-laitettasi kuvan ottamiseen ja sen luokitteluun.

### Tehtävä – kuvan ottaminen IoT-laitteella

Seuraa sopivaa ohjetta ottaaksesi kuvan IoT-laitteellasi:

* [Arduino – Wio Terminal](wio-terminal-camera.md)
* [Yksikorttitietokone – Raspberry Pi](pi-camera.md)
* [Yksikorttitietokone – Virtuaalilaite](virtual-device-camera.md)

## Kuvien luokittelijan julkaiseminen

Koulutit kuvien luokittelijan edellisessä oppitunnissa. Ennen kuin voit käyttää sitä IoT-laitteeltasi, sinun täytyy julkaista malli.

### Mallin iteroinnit

Kun mallisi koulutettiin edellisessä oppitunnissa, huomasit ehkä, että **Suorituskyky**-välilehdellä näkyy iterointeja sivussa. Kun koulutit mallin ensimmäistä kertaa, näit *Iteraatio 1* -merkinnän koulutuksessa. Kun paransit mallia ennustekuvilla, näit *Iteraatio 2* -merkinnän koulutuksessa.

Joka kerta, kun koulutat mallin, saat uuden iteroinnin. Tämä on tapa seurata mallisi eri versioita, jotka on koulutettu eri tietojoukoilla. Kun teet **Pikakokeen**, voit valita iteroinnin pudotusvalikosta ja vertailla tuloksia eri iterointien välillä.

Kun olet tyytyväinen iterointiin, voit julkaista sen, jotta sitä voidaan käyttää ulkoisista sovelluksista. Näin voit pitää julkaistun version, jota laitteesi käyttävät, ja työstää uutta versiota useiden iterointien kautta, kunnes olet tyytyväinen siihen ja julkaiset sen.

### Tehtävä – iteroinnin julkaiseminen

Iteroinnit julkaistaan Custom Vision -portaalista.

1. Avaa Custom Vision -portaali osoitteessa [CustomVision.ai](https://customvision.ai) ja kirjaudu sisään, jos et ole jo tehnyt niin. Avaa sitten `fruit-quality-detector`-projektisi.

1. Valitse ylävalikosta **Suorituskyky**-välilehti.

1. Valitse uusin iterointi *Iteraatiot*-listasta sivussa.

1. Valitse **Julkaise**-painike kyseiselle iteroinnille.

    ![Julkaise-painike](../../../../../translated_images/fi/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. *Julkaise malli* -valintaikkunassa aseta *Ennusteresurssi* `fruit-quality-detector-prediction`-resurssiksi, jonka loit edellisessä oppitunnissa. Jätä nimi `Iteration2`:ksi ja valitse **Julkaise**-painike.

1. Kun julkaisu on valmis, valitse **Ennuste-URL**-painike. Tämä näyttää ennuste-API:n tiedot, joita tarvitset kutsuaksesi mallia IoT-laitteeltasi. Alempi osio on merkitty *Jos sinulla on kuvatiedosto*, ja nämä ovat tarvitsemasi tiedot. Kopioi näytetty URL, joka on jotain seuraavanlaista:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Missä `<location>` on sijainti, jonka valitsit luodessasi Custom Vision -resurssin, ja `<id>` on pitkä kirjain- ja numerosarja.

    Kopioi myös *Ennusteavain*-arvo. Tämä on turvallinen avain, joka täytyy välittää, kun kutsut mallia. Vain sovellukset, jotka välittävät tämän avaimen, voivat käyttää mallia, muut sovellukset hylätään.

    ![Ennuste-API-valintaikkuna, joka näyttää URL:n ja avaimen](../../../../../translated_images/fi/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Kun uusi iterointi julkaistaan, sillä on eri nimi. Miten luulet, että IoT-laitteessa vaihdetaan käytettävä iterointi?

## Kuvien luokittelu IoT-laitteelta

Voit nyt käyttää näitä yhteystietoja kutsuaksesi kuvien luokittelijaa IoT-laitteeltasi.

### Tehtävä – kuvien luokittelu IoT-laitteelta

Seuraa sopivaa ohjetta luokitellaksesi kuvia IoT-laitteellasi:

* [Arduino – Wio Terminal](wio-terminal-classify-image.md)
* [Yksikorttitietokone – Raspberry Pi/Virtuaalinen IoT-laite](single-board-computer-classify-image.md)

## Mallin parantaminen

Saatat huomata, että kameran avulla IoT-laitteella otettujen kuvien tulokset eivät vastaa odotuksiasi. Ennusteet eivät aina ole yhtä tarkkoja kuin tietokoneeltasi ladatuilla kuvilla. Tämä johtuu siitä, että malli koulutettiin eri datalla kuin mitä käytetään ennusteisiin.

Parhaiden tulosten saavuttamiseksi kuvien luokittelijassa haluat kouluttaa mallin kuvilla, jotka ovat mahdollisimman samanlaisia kuin ennusteisiin käytetyt kuvat. Jos esimerkiksi käytit puhelimen kameraa koulutuskuvien ottamiseen, kuvan laatu, terävyys ja värit eroavat IoT-laitteeseen liitetyn kameran kuvista.

![2 banaanikuvaa, toinen matalaresoluutioinen ja huonosti valaistu IoT-laitteelta, toinen korkearesoluutioinen ja hyvin valaistu puhelimesta](../../../../../translated_images/fi/banana-picture-compare.174df164dc326a42.webp)

Yllä olevassa kuvassa vasemmanpuoleinen banaanikuva otettiin Raspberry Pi -kameralla, oikeanpuoleinen kuva otettiin samasta banaanista samassa paikassa iPhonella. Kuvien laadussa on selkeä ero – iPhonen kuva on terävämpi, värikkäämpi ja kontrastikkaampi.

✅ Mitkä muut tekijät voivat aiheuttaa sen, että IoT-laitteesi ottamat kuvat antavat virheellisiä ennusteita? Mieti ympäristöä, jossa IoT-laitetta käytetään, ja mitä tekijöitä voi vaikuttaa otettuun kuvaan.

Mallin parantamiseksi voit kouluttaa sen uudelleen IoT-laitteella otetuilla kuvilla.

### Tehtävä – mallin parantaminen

1. Luokittele useita kypsien ja raakojen hedelmien kuvia IoT-laitteellasi.

1. Custom Vision -portaalissa kouluta malli uudelleen *Ennusteet*-välilehdellä olevilla kuvilla.

    > ⚠️ Voit tarvittaessa viitata [ohjeisiin luokittelijan uudelleenkouluttamisesta oppitunnissa 1](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Jos kuvasi eroavat huomattavasti alkuperäisistä koulutukseen käytetyistä kuvista, voit poistaa kaikki alkuperäiset kuvat valitsemalla ne *Koulutuskuvat*-välilehdellä ja valitsemalla **Poista**-painikkeen. Valitaksesi kuvan vie hiiri sen päälle, jolloin näkyviin tulee valintamerkki, jota klikkaamalla voit valita tai poistaa valinnan.

1. Kouluta mallista uusi iterointi ja julkaise se yllä olevien ohjeiden mukaisesti.

1. Päivitä koodissasi käytettävä päätepisteen URL ja suorita sovellus uudelleen.

1. Toista nämä vaiheet, kunnes olet tyytyväinen ennusteiden tuloksiin.

---

## 🚀 Haaste

Kuinka paljon kuvan resoluutio tai valaistus vaikuttaa ennusteeseen?

Kokeile muuttaa laitteesi koodissa kuvien resoluutiota ja katso, vaikuttaako se kuvien laatuun. Kokeile myös muuttaa valaistusta.

Jos loisit tuotantolaitteen, jota myytäisiin maatiloille tai tehtaisiin, kuinka varmistaisit, että se antaa johdonmukaisia tuloksia koko ajan?

## Jälkikysely

[Jälkikysely](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Kertaus ja itseopiskelu

Koulutit Custom Vision -mallisi portaalin avulla. Tämä edellyttää, että kuvat ovat saatavilla – ja tosielämässä et välttämättä saa koulutusdataa, joka vastaa laitteen kameran ottamia kuvia. Voit kiertää tämän kouluttamalla suoraan laitteeltasi käyttämällä koulutus-API:a, jolloin voit kouluttaa mallin IoT-laitteella otetuilla kuvilla.

* Lue lisää koulutus-API:sta [Custom Vision SDK:n pikaoppaasta](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python).

## Tehtävä

[Reagoi luokittelutuloksiin](assignment.md)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.