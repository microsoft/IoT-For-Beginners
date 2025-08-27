<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T22:16:22+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "fi"
}
-->
# Rakenna universaali kääntäjä

## Ohjeet

Universaali kääntäjä on laite, joka voi kääntää useiden kielten välillä, mahdollistaen eri kieliä puhuvien ihmisten kommunikoinnin. Käytä oppimiasi asioita viimeisten oppituntien aikana rakentaaksesi universaalin kääntäjän kahden IoT-laitteen avulla.

> Jos sinulla ei ole kahta laitetta, seuraa edellisten oppituntien ohjeita virtuaalisen IoT-laitteen luomiseksi yhdeksi IoT-laitteista.

Sinun tulisi määrittää yksi laite yhdelle kielelle ja toinen toiselle. Jokaisen laitteen tulisi vastaanottaa puhetta, muuntaa se tekstiksi, lähettää se toiselle laitteelle IoT Hubin ja Functions-sovelluksen kautta, kääntää se ja toistaa käännetty puhe.

> 💁 Vinkki: Kun lähetät puhetta laitteesta toiseen, lähetä myös tieto siitä, millä kielellä puhe on, jotta kääntäminen olisi helpompaa. Voisit jopa rekisteröidä jokaisen laitteen IoT Hubin ja Functions-sovelluksen avulla ensin, välittäen tuetun kielen Azure Storageen tallennettavaksi. Voisit sitten käyttää Functions-sovellusta käännösten tekemiseen ja lähettää käännetyn tekstin IoT-laitteelle.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannusta tarvitaan |
| -------- | ----------- | -------- | -------------------- |
| Universaalin kääntäjän luominen | Pystyi rakentamaan universaalin kääntäjän, joka muuntaa yhden laitteen havaitseman puheen toisen laitteen toistamaksi puheeksi eri kielellä | Pystyi saamaan joitakin osia toimimaan, kuten puheen tallentamisen tai kääntämisen, mutta ei pystynyt rakentamaan kokonaisratkaisua | Ei pystynyt rakentamaan mitään osia toimivasta universaalista kääntäjästä |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.