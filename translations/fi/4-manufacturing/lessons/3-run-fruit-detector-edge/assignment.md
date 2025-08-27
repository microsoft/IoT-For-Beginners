<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:50:43+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "fi"
}
-->
# Aja muita palveluita reunalla

## Ohjeet

Reunalla ei voida ajaa vain kuvien luokittelijoita, vaan mitä tahansa, mikä voidaan paketoida konttiin, voidaan ottaa käyttöön IoT Edge -laitteessa. Palvelimettomat koodit, jotka toimivat Azure Functions -toimintoina, kuten aiemmissa oppitunneissa luomasi laukaisijat, voidaan ajaa konteissa ja siten myös IoT Edgessä.

Valitse jokin aiemmista oppitunneista ja yritä ajaa Azure Functions -sovellusta IoT Edge -kontissa. Löydät oppaan, joka näyttää, miten tämä tehdään eri Functions-sovellusprojektilla, [Opas: Azure Functions -toimintojen käyttöönotto IoT Edge -moduuleina Microsoftin dokumentaatiossa](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannettavaa |
| -------- | ----------- | -------- | ------------- |
| Azure Functions -sovelluksen käyttöönotto IoT Edgessä | Onnistui ottamaan Azure Functions -sovelluksen käyttöön IoT Edgessä ja käyttämään sitä IoT-laitteen kanssa laukaisemaan triggerin IoT-datasta | Onnistui ottamaan Functions-sovelluksen käyttöön IoT Edgessä, mutta ei saanut triggeriä toimimaan | Ei onnistunut ottamaan Functions-sovellusta käyttöön IoT Edgessä |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.