<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T22:23:29+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "fi"
}
-->
# Peruuta ajastin

## Ohjeet

Tähän mennessä tässä oppitunnissa olet kouluttanut mallin ymmärtämään ajastimen asettamisen. Toinen hyödyllinen ominaisuus on ajastimen peruuttaminen – ehkä leipäsi on valmis ja sen voi ottaa uunista ennen kuin ajastin päättyy.

Lisää uusi intentio LUIS-sovellukseesi ajastimen peruuttamista varten. Se ei tarvitse entiteettejä, mutta tarvitsee joitakin esimerkkilauseita. Käsittele tämä serverittömässä koodissasi, jos se on tärkein intentio, kirjaamalla, että intentio tunnistettiin, ja palauttamalla sopiva vastaus.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannettavaa |
| -------- | ----------- | -------- | ------------- |
| Lisää ajastimen peruutusintentio LUIS-sovellukseen | Onnistui lisäämään intention ja kouluttamaan mallin | Onnistui lisäämään intention, mutta ei kouluttamaan mallia | Ei onnistunut lisäämään intention ja kouluttamaan mallia |
| Käsittele intentio serverittömässä sovelluksessa | Onnistui tunnistamaan intention tärkeimpänä intentiona ja kirjaamaan sen | Onnistui tunnistamaan intention tärkeimpänä intentiona | Ei onnistunut tunnistamaan intention tärkeimpänä intentiona |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.