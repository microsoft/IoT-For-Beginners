<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T21:19:47+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "fi"
}
-->
# Lisää manuaalinen releen ohjaus

## Ohjeet

Palvelimettoman koodin suoritus voi käynnistyä monin eri tavoin, kuten HTTP-pyynnöillä. Voit käyttää HTTP-käynnistimiä lisätäksesi manuaalisen ohituksen releen ohjaukseen, jolloin joku voi kytkeä releen päälle tai pois päältä verkkopyynnön avulla.

Tässä tehtävässä sinun tulee lisätä kaksi HTTP-käynnistintä Functions App -sovellukseesi releen päälle ja pois päältä kytkemiseksi, hyödyntäen oppitunnilla opittuja asioita laitteelle komentoja lähettämiseen.

Muutamia vinkkejä:

* Voit lisätä HTTP-käynnistimen olemassa olevaan Functions App -sovellukseesi seuraavalla komennolla:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Korvaa `<trigger name>` HTTP-käynnistimen nimellä. Käytä esimerkiksi `relay_on` ja `relay_off`.

* HTTP-käynnistimillä voi olla käyttöoikeuksien hallinta. Oletuksena ne vaativat toiminnolle spesifisen API-avaimen, joka välitetään URL-osoitteen mukana. Tässä tehtävässä voit poistaa tämän rajoituksen, jotta kuka tahansa voi suorittaa toiminnon. Tee tämä päivittämällä `authLevel`-asetus HTTP-käynnistimien `function.json`-tiedostossa seuraavasti:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Voit lukea lisää käyttöoikeuksien hallinnasta [Function access keys -dokumentaatiosta](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP-käynnistimet tukevat oletuksena GET- ja POST-pyyntöjä. Tämä tarkoittaa, että voit kutsua niitä verkkoselaimella - verkkoselaimet tekevät GET-pyyntöjä.

    Kun suoritat Functions App -sovellusta paikallisesti, näet käynnistimen URL-osoitteen:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Liitä URL-osoite selaimeesi ja paina `return`, tai `Ctrl+klikkaa` (`Cmd+klikkaa` macOS:ssä) linkkiä VS Code -terminaali-ikkunassa avataksesi sen oletusselaimessasi. Tämä suorittaa käynnistimen.

    > 💁 Huomaa, että URL-osoitteessa on `/api` - HTTP-käynnistimet ovat oletuksena `api`-aliverkkotunnuksessa.

* Kun julkaiset Functions App -sovelluksen, HTTP-käynnistimen URL-osoite on:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Missä `<functions app name>` on Functions App -sovelluksesi nimi ja `<trigger name>` on käynnistimesi nimi.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannettavaa |
| -------- | ----------- | -------- | ------------- |
| Luo HTTP-käynnistimet | Luotu 2 käynnistintä releen päälle ja pois päältä kytkemiseksi, sopivilla nimillä | Luotu yksi käynnistin sopivalla nimellä | Ei onnistuttu luomaan käynnistimiä |
| Ohjaa relettä HTTP-käynnistimistä | Molemmat käynnistimet yhdistetty IoT Hubiin ja relettä ohjattu oikein | Yksi käynnistin yhdistetty IoT Hubiin ja relettä ohjattu oikein | Käynnistimiä ei onnistuttu yhdistämään IoT Hubiin |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.