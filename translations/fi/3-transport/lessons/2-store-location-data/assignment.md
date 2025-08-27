<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T23:04:03+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "fi"
}
-->
# Tutki funktiosidontoja

## Ohjeet

Funktiosidonnat mahdollistavat koodisi tallentaa blobit blob-tallennukseen palauttamalla ne `main`-funktiosta. Azure Storage -tili, kokoelma ja muut yksityiskohdat määritetään `function.json`-tiedostossa.

Kun työskentelet Azuren tai muiden Microsoft-teknologioiden kanssa, paras tietolähde on [Microsoftin dokumentaatio osoitteessa docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Tässä tehtävässä sinun tulee lukea Azure Functions -sidontadokumentaatio selvittääksesi, miten ulostulosidonta asetetaan.

Joistakin sivuista, joilla voit aloittaa, ovat:

* [Azure Functions -triggereiden ja sidontojen peruskäsitteet](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob -tallennuksen sidonnat Azure Functionsille - yleiskatsaus](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob -tallennuksen ulostulosidonta Azure Functionsille](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannusta tarvitaan |
| -------- | ----------- | -------- | -------------------- |
| Blob-tallennuksen ulostulosidonnan konfigurointi | Pystyi konfiguroimaan ulostulosidonnan, palauttamaan blobin ja tallentamaan sen onnistuneesti blob-tallennukseen | Pystyi konfiguroimaan ulostulosidonnan tai palauttamaan blobin, mutta ei onnistunut tallentamaan sitä blob-tallennukseen | Ei pystynyt konfiguroimaan ulostulosidontaa |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.