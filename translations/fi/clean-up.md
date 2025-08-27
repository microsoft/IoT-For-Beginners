<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:23:03+00:00",
  "source_file": "clean-up.md",
  "language_code": "fi"
}
-->
# Siivoa projektisi

Kun olet saanut projektin valmiiksi, on hyvä poistaa pilvipalveluresurssit.

Jokaisen projektin oppitunneilla olet saattanut luoda joitakin seuraavista:

* Resurssiryhmä
* IoT Hub
* IoT-laiterekisteröinnit
* Tallennustili
* Functions-sovellus
* Azure Maps -tili
* Custom Vision -projekti
* Azure Container Registry
* Cognitive Services -resurssi

Useimmista näistä resursseista ei aiheudu kustannuksia – ne ovat joko täysin ilmaisia tai käytät ilmaista tasoa. Palveluissa, jotka vaativat maksullisen tason, olet käyttänyt niitä tasolla, joka sisältyy ilmaiseen käyttöön, tai kustannukset ovat vain muutamia senttejä.

Vaikka kustannukset ovat suhteellisen alhaiset, resurssien poistaminen projektin päätyttyä on silti järkevää. Esimerkiksi IoT Hubin ilmainen taso sallii vain yhden IoT Hubin, joten jos haluat luoda toisen, sinun täytyy käyttää maksullista tasoa.

Kaikki palvelusi luotiin Resurssiryhmiin, mikä helpottaa hallintaa. Voit poistaa Resurssiryhmän, jolloin kaikki kyseisen Resurssiryhmän palvelut poistetaan samalla.

Poistaaksesi Resurssiryhmän, suorita seuraava komento terminaalissasi tai komentokehotteessa:

```sh
az group delete --name <resource-group-name>
```

Korvaa `<resource-group-name>` sen Resurssiryhmän nimellä, jonka haluat poistaa.

Näyttöön tulee vahvistus:

```output
Are you sure you want to perform this operation? (y/n): 
```

Syötä `y` vahvistaaksesi ja poistaaksesi Resurssiryhmän.

Kaikkien palveluiden poistaminen vie hetken.

> 💁 Voit lukea lisää Resurssiryhmien poistamisesta [Microsoft Docsin Azure Resource Managerin resurssiryhmien ja resurssien poistamista käsittelevästä dokumentaatiosta](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.