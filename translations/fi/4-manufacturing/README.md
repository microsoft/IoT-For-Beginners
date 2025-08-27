<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:35:00+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "fi"
}
-->
# Valmistus ja käsittely - IoT:n käyttö ruoan käsittelyn parantamiseksi

Kun ruoka saapuu keskusvarastoon tai käsittelylaitokseen, sitä ei aina vain lähetetä eteenpäin supermarketteihin. Usein ruoka käy läpi useita käsittelyvaiheita, kuten laadun mukaan lajittelua. Tämä oli aiemmin manuaalinen prosessi - se alkoi pellolla, kun poimijat keräsivät vain kypsiä hedelmiä, ja tehtaalla hedelmät kulkivat kuljetushihnalla, jossa työntekijät poistivat käsin kolhiintuneet tai pilaantuneet hedelmät. Itsekin olen kesätyönä kouluaikana poiminut ja lajitellut mansikoita, joten voin todeta, ettei tämä ole hauskaa työtä.

Nykyaikaisemmat järjestelmät käyttävät IoT:tä lajitteluun. Varhaisimmat laitteet, kuten [Weco](https://wecotek.com)-yhtiön lajittelijat, käyttävät optisia sensoreita tuottavuuden laadun havaitsemiseen, esimerkiksi hyläten vihreät tomaatit. Näitä voidaan käyttää sadonkorjuukoneissa suoraan tilalla tai käsittelylaitoksissa.

Kun tekoäly (AI) ja koneoppiminen (ML) kehittyvät, nämä laitteet voivat tulla entistä edistyneemmiksi, käyttämällä ML-malleja, jotka on koulutettu erottamaan hedelmät ja vieraat esineet, kuten kivet, lika tai hyönteiset. Näitä malleja voidaan myös kouluttaa havaitsemaan hedelmien laatu, ei vain kolhiintuneita hedelmiä, vaan myös varhaisia merkkejä sairauksista tai muista viljelyongelmista.

> 🎓 Termi *ML-malli* viittaa koneoppimisen ohjelmiston koulutuksen tulokseen tietojoukolla. Esimerkiksi voit kouluttaa ML-mallin erottamaan kypsät ja raakat tomaatit, ja käyttää mallia uusien kuvien analysointiin nähdäksesi, ovatko tomaatit kypsiä vai eivät.

Näissä neljässä oppitunnissa opit, kuinka kouluttaa kuvapohjaisia AI-malleja hedelmien laadun havaitsemiseen, kuinka käyttää näitä IoT-laitteessa ja kuinka ajaa näitä reunalla - eli IoT-laitteessa pilven sijaan.

> 💁 Näissä oppitunneissa käytetään joitakin pilvipalveluja. Jos et suorita kaikkia projektin oppitunteja, muista [siivota projektisi](../clean-up.md).

## Aiheet

1. [Kouluta hedelmien laadun tunnistin](./lessons/1-train-fruit-detector/README.md)
1. [Tarkista hedelmien laatu IoT-laitteesta](./lessons/2-check-fruit-from-device/README.md)
1. [Aja hedelmien tunnistin reunalla](./lessons/3-run-fruit-detector-edge/README.md)
1. [Käynnistä hedelmien laadun tunnistus sensorista](./lessons/4-trigger-fruit-detector/README.md)

## Tekijät

Kaikki oppitunnit on kirjoitettu ♥️:lla [Jen Fox](https://github.com/jenfoxbot) ja [Jim Bennett](https://GitHub.com/JimBobBennett) toimesta.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.