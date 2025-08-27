<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-27T22:44:13+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "fi"
}
-->
# Kuljetus tilalta tehtaalle - IoT:n käyttö ruoan toimitusten seuraamiseen

Monet viljelijät kasvattavat ruokaa myyntiin – joko he ovat kaupallisia viljelijöitä, jotka myyvät kaiken kasvattamansa, tai omavaraisviljelijöitä, jotka myyvät ylimääräisen sadon hankkiakseen välttämättömyyksiä. Jollain tavalla ruoka on saatava tilalta kuluttajalle, ja tämä tapahtuu yleensä massakuljetuksilla tiloilta keskuksiin tai jalostuslaitoksiin ja sieltä kauppoihin. Esimerkiksi tomaattiviljelijä korjaa tomaatit, pakkaa ne laatikoihin, lastaa laatikot kuorma-autoon ja toimittaa ne jalostuslaitokseen. Tomaatit lajitellaan, ja sen jälkeen ne toimitetaan kuluttajille jalostettuna ruokana, vähittäismyynnin kautta tai ravintoloissa nautittavaksi.

IoT voi auttaa tässä toimitusketjussa seuraamalla ruoan kuljetusta – varmistamalla, että kuljettajat ovat oikeilla reiteillä, seuraamalla ajoneuvojen sijainteja ja lähettämällä ilmoituksia, kun ajoneuvot saapuvat, jotta ruoka voidaan purkaa ja valmistella jalostettavaksi mahdollisimman nopeasti.

> 🎓 *Toimitusketju* tarkoittaa toimintojen sarjaa, jolla jokin tuote valmistetaan ja toimitetaan. Esimerkiksi tomaattiviljelyssä se kattaa siementen, maan, lannoitteiden ja veden hankinnan, tomaattien kasvattamisen, niiden toimittamisen keskuskeskukseen, kuljettamisen supermarketin paikalliseen keskukseen, kuljettamisen yksittäiseen supermarkettiin, esillepanon, myynnin kuluttajalle ja kotiin viemisen syötäväksi. Jokainen vaihe on kuin lenkki ketjussa.

> 🎓 Toimitusketjun kuljetusosuutta kutsutaan *logistiikaksi*.

Näissä neljässä oppitunnissa opit, kuinka voit hyödyntää esineiden internetiä (IoT) parantaaksesi toimitusketjua seuraamalla ruokaa, kun se lastataan (virtuaaliseen) kuorma-autoon, jota seurataan sen matkalla määränpäähänsä. Opit GPS-seurannasta, GPS-datan tallentamisesta ja visualisoinnista sekä siitä, kuinka saat ilmoituksen, kun kuorma-auto saapuu määränpäähänsä.

> 💁 Näissä oppitunneissa käytetään joitakin pilvipalveluresursseja. Jos et suorita kaikkia tämän projektin oppitunteja, muista [siivota projektisi](../clean-up.md).

## Aiheet

1. [Sijainnin seuranta](lessons/1-location-tracking/README.md)
1. [Sijaintidatan tallentaminen](lessons/2-store-location-data/README.md)
1. [Sijaintidatan visualisointi](lessons/3-visualize-location-data/README.md)
1. [Geoaidat](lessons/4-geofences/README.md)

## Tekijät

Kaikki oppitunnit on kirjoitettu ♥️:lla [Jen Looperin](https://github.com/jlooper) ja [Jim Bennettin](https://GitHub.com/JimBobBennett) toimesta.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.