<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-27T21:12:58+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "fi"
}
-->
# Ohjaa relettä - Wio Terminal

Tässä osassa oppituntia lisäät releen Wio Terminal -laitteeseesi maankosteusanturin lisäksi ja ohjaat sitä maankosteustason perusteella.

## Laitteisto

Wio Terminal tarvitsee releen.

Käytettävä rele on [Grove-rele](https://www.seeedstudio.com/Grove-Relay.html), normaalisti avoin rele (eli lähtöpiiri on avoin tai irrotettu, kun releelle ei lähetetä signaalia), joka pystyy käsittelemään lähtöpiirejä jopa 250V ja 10A.

Tämä on digitaalinen toimilaite, joten se liitetään Wio Terminalin digitaalisiin pinneihin. Yhdistetty analoginen/digitaalinen portti on jo käytössä maankosteusanturin kanssa, joten tämä liitetään toiseen porttiin, joka on yhdistetty I

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.