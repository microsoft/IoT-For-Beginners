<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:40:35+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "fi"
}
-->
# Vastaa luokittelutuloksiin

## Ohjeet

Laitteesi on luokitellut kuvia ja saanut ennusteiden arvot. Laitteesi voi käyttää näitä tietoja jollain tavalla - se voi lähettää ne IoT Hubiin muiden järjestelmien käsiteltäväksi tai ohjata toimilaitetta, kuten sytyttää LED-valon, kun hedelmä ei ole kypsä.

Lisää laitteeseesi koodi, joka reagoi valitsemallasi tavalla - joko lähettämällä tiedot IoT Hubiin, ohjaamalla toimilaitetta tai yhdistämällä molemmat. Voit esimerkiksi lähettää tiedot IoT Hubiin ja käyttää palvelutonta koodia, joka määrittää, onko hedelmä kypsä vai ei, ja lähettää takaisin komennon toimilaitteen ohjaamiseksi.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannettavaa |
| -------- | ----------- | -------- | ------------- |
| Reagointi ennusteisiin | Pystyi toteuttamaan reaktion ennusteisiin, joka toimii johdonmukaisesti samanarvoisten ennusteiden kanssa. | Pystyi toteuttamaan reaktion, joka ei riipu ennusteista, kuten vain raakadatan lähettäminen IoT Hubiin. | Ei pystynyt ohjelmoimaan laitetta reagoimaan ennusteisiin. |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.