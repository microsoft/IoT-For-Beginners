# Rakenna uusi IoT-laite

## Ohjeet

Viimeisten kuuden oppitunnin aikana olet oppinut digitaalisen maatalouden perusteita ja kuinka käyttää IoT-laitteita datan keräämiseen kasvien kasvun ennustamiseksi sekä kastelun automatisoimiseksi maaperän kosteuden mittausten perusteella.

Hyödynnä oppimaasi rakentaaksesi uuden IoT-laitteen, joka käyttää valitsemaasi sensoria ja toimilaitetta. Lähetä telemetriatiedot IoT Hubiin ja käytä niitä toimilaitteen ohjaamiseen palvelimettoman koodin avulla. Voit käyttää sensoria ja toimilaitetta, joita olet jo käyttänyt tässä tai edellisessä projektissa, tai jos sinulla on muuta laitteistoa, kokeile jotain uutta.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannusta tarvitaan |
| -------- | ----------- | -------- | -------------------- |
| IoT-laitteen koodaus sensorin ja toimilaitteen käyttöön | Koodattu IoT-laite, joka toimii sensorin ja toimilaitteen kanssa | Koodattu IoT-laite, joka toimii sensorin tai toimilaitteen kanssa | Ei onnistunut koodaamaan IoT-laitetta sensorin tai toimilaitteen käyttöön |
| IoT-laitteen yhdistäminen IoT Hubiin | Onnistui ottamaan käyttöön IoT Hubin, lähettämään telemetriatiedot siihen ja vastaanottamaan komentoja siitä | Onnistui ottamaan käyttöön IoT Hubin ja joko lähettämään telemetriatiedot tai vastaanottamaan komentoja | Ei onnistunut ottamaan käyttöön IoT Hubia eikä kommunikoimaan sen kanssa IoT-laitteesta |
| Toimilaitteen ohjaaminen palvelimettoman koodin avulla | Onnistui ottamaan käyttöön Azure Functionin, joka ohjaa laitetta telemetriatapahtumien perusteella | Onnistui ottamaan käyttöön Azure Functionin, joka aktivoituu telemetriatapahtumista, mutta ei onnistunut ohjaamaan toimilaitetta | Ei onnistunut ottamaan käyttöön Azure Functionia |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.