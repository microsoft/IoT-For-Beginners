<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T20:27:19+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "lt"
}
-->
# Pridėti rankinį relės valdymą

## Instrukcijos

Serverless kodas gali būti paleidžiamas įvairiais būdais, įskaitant HTTP užklausas. Naudodami HTTP trigerius, galite pridėti rankinį relės valdymą, leidžiantį kažkam įjungti arba išjungti relę per interneto užklausą.

Šiai užduočiai reikia pridėti du HTTP trigerius prie jūsų Functions App, kad būtų galima įjungti ir išjungti relę, panaudojant tai, ką išmokote šioje pamokoje, norint siųsti komandas į įrenginį.

Keletas užuominų:

* Galite pridėti HTTP trigerį prie esamos Functions App naudodami šią komandą:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Pakeiskite `<trigger name>` į savo HTTP trigerio pavadinimą. Naudokite, pavyzdžiui, `relay_on` ir `relay_off`.

* HTTP trigeriai gali turėti prieigos kontrolę. Pagal numatymą jie reikalauja funkcijai specifinio API rakto, kuris turi būti perduotas kartu su URL, kad funkcija būtų paleista. Šiai užduočiai galite pašalinti šį apribojimą, kad bet kas galėtų paleisti funkciją. Norėdami tai padaryti, atnaujinkite `authLevel` nustatymą `function.json` faile HTTP trigeriams į šį:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Daugiau apie šią prieigos kontrolę galite perskaityti [Funkcijų prieigos raktų dokumentacijoje](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP trigeriai pagal numatymą palaiko GET ir POST užklausas. Tai reiškia, kad juos galite iškviesti naudodami savo interneto naršyklę – interneto naršyklės siunčia GET užklausas.

    Kai paleidžiate savo Functions App lokaliai, pamatysite trigerio URL:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Nukopijuokite URL į savo naršyklę ir paspauskite `Enter`, arba `Ctrl+spustelėkite` (`Cmd+spustelėkite` macOS sistemoje) nuorodą terminalo lange VS Code, kad atidarytumėte ją numatytojoje naršyklėje. Tai paleis trigerį.

    > 💁 Atkreipkite dėmesį, kad URL turi `/api` – HTTP trigeriai pagal numatymą yra `api` subdomeno dalyje.

* Kai įdiegsite Functions App, HTTP trigerio URL bus toks:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Kur `<functions app name>` yra jūsų Functions App pavadinimas, o `<trigger name>` yra jūsų trigerio pavadinimas.

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinimų |
| ---------- | ------- | ---------- | ------------------- |
| Sukurti HTTP trigerius | Sukurti 2 trigeriai relės įjungimui ir išjungimui su tinkamais pavadinimais | Sukurtas vienas trigeris su tinkamu pavadinimu | Nepavyko sukurti trigerių |
| Valdyti relę per HTTP trigerius | Abu trigeriai sėkmingai prijungti prie IoT Hub ir tinkamai valdo relę | Vienas trigeris sėkmingai prijungtas prie IoT Hub ir tinkamai valdo relę | Nepavyko prijungti trigerių prie IoT Hub |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.