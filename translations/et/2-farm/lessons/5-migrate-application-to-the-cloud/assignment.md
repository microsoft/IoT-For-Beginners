<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-10-11T12:41:02+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "et"
}
-->
# Lisa manuaalne relee juhtimine

## Juhised

Serverivaba kood võib käivituda mitmesuguste sündmuste, sealhulgas HTTP-päringute kaudu. HTTP-käivitajaid saab kasutada, et lisada manuaalne juhtimisvõimalus relee juhtimiseks, võimaldades kellelgi veebipäringu kaudu relee sisse või välja lülitada.

Selle ülesande jaoks pead lisama oma Functions App-i kaks HTTP-käivitajat, et lülitada relee sisse ja välja, kasutades õpitut seadmele käskude saatmiseks.

Mõned vihjed:

* Sa saad lisada HTTP-käivitaja oma olemasolevasse Functions App-i järgmise käsuga:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Asenda `<trigger name>` oma HTTP-käivitaja nimega. Kasuta midagi sellist nagu `relay_on` ja `relay_off`.

* HTTP-käivitajatel võib olla juurdepääsukontroll. Vaikimisi nõuavad need funktsioonispetsiifilist API-võtit, mis tuleb URL-iga kaasa anda, et funktsioon käivituks. Selle ülesande jaoks võid selle piirangu eemaldada, et igaüks saaks funktsiooni käivitada. Selleks uuenda HTTP-käivitajate `function.json` faili `authLevel` seadistust järgmiselt:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Sa saad lugeda rohkem selle juurdepääsukontrolli kohta [Function access keys dokumentatsioonist](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP-käivitajad toetavad vaikimisi GET ja POST päringuid. See tähendab, et neid saab kutsuda veebibrauseri abil - veebibrauserid teevad GET-päringuid.

    Kui käivitad oma Functions App-i lokaalselt, näed käivitaja URL-i:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Kleebi URL oma brauserisse ja vajuta `return`, või `Ctrl+klõps` (`Cmd+klõps` macOS-is) lingil terminaliaknas VS Code-is, et avada see oma vaikimisi brauseris. See käivitab käivitaja.

    > 💁 Pane tähele, et URL-is on `/api` - HTTP-käivitajad on vaikimisi `api` alamdomeenis.

* Kui sa juurutad Functions App-i, on HTTP-käivitaja URL järgmine:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Kus `<functions app name>` on sinu Functions App-i nimi ja `<trigger name>` on sinu käivitaja nimi.

## Hindamiskriteeriumid

| Kriteerium | Suurepärane | Piisav | Vajab parandamist |
| ---------- | ----------- | ------ | ----------------- |
| HTTP-käivitajate loomine | Loodud 2 käivitajat relee sisse ja välja lülitamiseks, sobivate nimedega | Loodud üks käivitaja sobiva nimega | Ei suutnud luua ühtegi käivitajat |
| Relee juhtimine HTTP-käivitajate kaudu | Suutis ühendada mõlemad käivitajad IoT Hub-iga ja juhtida releed korrektselt | Suutis ühendada ühe käivitaja IoT Hub-iga ja juhtida releed korrektselt | Ei suutnud käivitajaid IoT Hub-iga ühendada |

---

**Lahtiütlus**:  
See dokument on tõlgitud, kasutades AI tõlketeenust [Co-op Translator](https://github.com/Azure/co-op-translator). Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks lugeda autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valede tõlgenduste eest.