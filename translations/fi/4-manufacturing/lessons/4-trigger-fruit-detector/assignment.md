<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T20:55:46+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "fi"
}
-->
# Rakenna hedelmien laadun tunnistin

## Ohjeet

Rakenna hedelmien laadun tunnistin!

Hyödynnä kaikkea oppimaasi ja rakenna prototyyppi hedelmien laadun tunnistimesta. Käynnistä kuvien luokittelu läheisyyden perusteella AI-mallilla, joka toimii reunalaitteella, tallenna luokittelun tulokset säilytykseen ja ohjaa LED-valoa hedelmän kypsyyden mukaan.

Sinun pitäisi pystyä kokoamaan tämä yhteen käyttämällä koodia, jota olet aiemmin kirjoittanut kaikissa tähän asti käydyissä oppitunneissa.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannusta tarvitaan |
| -------- | ----------- | -------- | -------------------- |
| Kaikkien palveluiden konfigurointi | Pystyi määrittämään IoT Hubin, Azure Functions -sovelluksen ja Azure Storage -palvelun | Pystyi määrittämään IoT Hubin, mutta ei Azure Functions -sovellusta tai Azure Storage -palvelua | Ei pystynyt määrittämään mitään IoT-palveluita |
| Läheisyyden seuranta ja datan lähettäminen IoT Hubiin, jos objekti on lähempänä kuin ennalta määritetty etäisyys, ja kameran käynnistäminen komennolla | Pystyi mittaamaan etäisyyden ja lähettämään viestin IoT Hubiin, kun objekti oli tarpeeksi lähellä, sekä lähettämään komennon kameran käynnistämiseksi | Pystyi mittaamaan läheisyyden ja lähettämään datan IoT Hubiin, mutta ei saanut lähetettyä komentoa kameralle | Ei pystynyt mittaamaan etäisyyttä eikä lähettämään viestiä IoT Hubiin tai käynnistämään komentoa |
| Kuvan ottaminen, luokittelu ja tulosten lähettäminen IoT Hubiin | Pystyi ottamaan kuvan, luokittelemaan sen reunalaitteella ja lähettämään tulokset IoT Hubiin | Pystyi luokittelemaan kuvan, mutta ei reunalaitteella, tai ei pystynyt lähettämään tuloksia IoT Hubiin | Ei pystynyt luokittelemaan kuvaa |
| LED-valon sytyttäminen tai sammuttaminen luokittelun tulosten perusteella komennolla, joka lähetetään laitteelle | Pystyi sytyttämään LED-valon komennolla, jos hedelmä oli raaka | Pystyi lähettämään komennon laitteelle, mutta ei ohjaamaan LED-valoa | Ei pystynyt lähettämään komentoa LED-valon ohjaamiseksi |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.