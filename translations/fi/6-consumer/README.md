<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-27T22:12:25+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "fi"
}
-->
# Kuluttaja-IoT - rakenna älykäs ääniavustaja

Ruoka on kasvatettu, kuljetettu jalostuslaitokseen, lajiteltu laadun mukaan, myyty kaupassa ja nyt on aika kokata! Yksi keittiön tärkeimmistä välineistä on ajastin. Aluksi nämä olivat tiimalaseja - ruoka oli valmis, kun kaikki hiekka oli valunut alas alaosaan. Sitten siirryttiin kellokoneistoihin ja lopulta sähköisiin ajastimiin.

Viimeisimmät versiot ovat nyt osa älylaitteitamme. Keittiöissä ympäri maailmaa kuulee kokkien huutavan "Hei Siri - aseta 10 minuutin ajastin" tai "Alexa - peru leipäajastimeni". Enää ei tarvitse kävellä takaisin keittiöön tarkistamaan ajastinta, sen voi tehdä puhelimella tai huutamalla huoneen poikki.

Näissä neljässä oppitunnissa opit rakentamaan älykkään ajastimen, joka käyttää tekoälyä tunnistamaan äänesi, ymmärtämään mitä pyydät ja vastaamaan ajastimeesi liittyvillä tiedoilla. Lisäksi lisäät tuen useille kielille.

> ⚠️ Puhe- ja mikrofonidatan käsittely käyttää paljon muistia, mikä tarkoittaa, että mikro-ohjaimien rajat voivat tulla nopeasti vastaan. Tämä projekti kiertää nämä ongelmat, mutta ole tietoinen siitä, että Wio Terminal -laboratoriot ovat monimutkaisia ja voivat viedä enemmän aikaa kuin muut tämän oppimateriaalin laboratoriot.

> 💁 Näissä oppitunneissa käytetään joitakin pilvipalveluja. Jos et suorita kaikkia projektin oppitunteja, muista [siivota projektisi](../clean-up.md).

## Aiheet

1. [Puheen tunnistaminen IoT-laitteella](./lessons/1-speech-recognition/README.md)
1. [Kielen ymmärtäminen](./lessons/2-language-understanding/README.md)
1. [Ajastimen asettaminen ja puhepalautteen antaminen](./lessons/3-spoken-feedback/README.md)
1. [Useiden kielten tukeminen](./lessons/4-multiple-language-support/README.md)

## Tekijät

Kaikki oppitunnit on kirjoitettu ♥️:lla [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.