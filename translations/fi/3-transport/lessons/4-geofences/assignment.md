<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T22:48:42+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "fi"
}
-->
# Lähetä ilmoituksia Twilion avulla

## Ohjeet

Tähän asti koodissasi olet vain kirjannut etäisyyden geofencestä. Tässä tehtävässä sinun tulee lisätä ilmoitus, joko tekstiviesti tai sähköposti, kun GPS-koordinaatit ovat geofencen sisällä.

Azure Functions tarjoaa monia vaihtoehtoja sidoksille, mukaan lukien kolmannen osapuolen palvelut, kuten Twilio, viestintäalusta.

* Rekisteröidy ilmaiseksi [Twilio.com](https://www.twilio.com) -sivustolla.
* Lue dokumentaatio Azure Functionsin Twilio SMS -sidoksesta [Microsoftin dokumentaatiosivulta Twilio binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lue dokumentaatio Azure Functionsin Twilio SendGrid -sidoksesta sähköpostien lähettämiseen [Microsoftin dokumentaatiosivulta Azure Functions SendGrid bindings](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lisää sidos Functions-sovellukseesi, jotta saat ilmoituksen GPS-koordinaattien ollessa joko geofencen sisällä tai ulkopuolella - mutta ei molemmissa.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannettavaa |
| -------- | ----------- | -------- | ------------- |
| Konfiguroi funktioiden sidokset ja vastaanota sähköposti tai tekstiviesti | Onnistui konfiguroimaan funktioiden sidokset ja vastaanottamaan sähköpostin tai tekstiviestin, kun koordinaatit olivat geofencen sisällä tai ulkopuolella, mutta ei molemmissa | Onnistui konfiguroimaan sidokset, mutta ei onnistunut lähettämään sähköpostia tai tekstiviestiä, tai onnistui lähettämään vain, kun koordinaatit olivat sekä sisällä että ulkopuolella | Ei onnistunut konfiguroimaan sidoksia eikä lähettämään sähköpostia tai tekstiviestiä |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.