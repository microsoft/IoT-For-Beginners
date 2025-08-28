<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T14:50:40+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "hr"
}
-->
# Dodavanje ručne kontrole releja

## Upute

Serverless kod može se pokrenuti na različite načine, uključujući HTTP zahtjeve. Možete koristiti HTTP okidače kako biste dodali ručno upravljanje relejem, omogućujući nekome da uključi ili isključi relej putem web zahtjeva.

Za ovaj zadatak trebate dodati dva HTTP okidača u svoju Functions App aplikaciju kako biste uključili i isključili relej, koristeći ono što ste naučili u ovoj lekciji za slanje naredbi uređaju.

Neki savjeti:

* Možete dodati HTTP okidač u svoju postojeću Functions App aplikaciju pomoću sljedeće naredbe:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Zamijenite `<trigger name>` imenom za vaš HTTP okidač. Koristite nešto poput `relay_on` i `relay_off`.

* HTTP okidači mogu imati kontrolu pristupa. Prema zadanim postavkama, zahtijevaju API ključ specifičan za funkciju koji se mora proslijediti s URL-om kako bi se pokrenuli. Za ovaj zadatak možete ukloniti ovo ograničenje kako bi svatko mogao pokrenuti funkciju. Da biste to učinili, ažurirajte postavku `authLevel` u datoteci `function.json` za HTTP okidače na sljedeće:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Više o ovoj kontroli pristupa možete pročitati u [dokumentaciji o pristupnim ključevima funkcija](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP okidači prema zadanim postavkama podržavaju GET i POST zahtjeve. To znači da ih možete pozvati pomoću svog web preglednika - web preglednici šalju GET zahtjeve.

    Kada pokrenete svoju Functions App aplikaciju lokalno, vidjet ćete URL okidača:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Zalijepite URL u svoj preglednik i pritisnite `return`, ili `Ctrl+kliknite` (`Cmd+kliknite` na macOS-u) na poveznicu u terminalskom prozoru u VS Code-u kako biste je otvorili u svom zadanom pregledniku. Ovo će pokrenuti okidač.

    > 💁 Primijetite da URL sadrži `/api` - HTTP okidači su prema zadanim postavkama u `api` poddomeni.

* Kada implementirate Functions App aplikaciju, URL HTTP okidača bit će:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Gdje je `<functions app name>` naziv vaše Functions App aplikacije, a `<trigger name>` naziv vašeg okidača.

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | -------- | --------------- | -------------------- |
| Kreiranje HTTP okidača | Kreirana su 2 okidača za uključivanje i isključivanje releja s odgovarajućim imenima | Kreiran je jedan okidač s odgovarajućim imenom | Nije bilo moguće kreirati nijedan okidač |
| Upravljanje relejem putem HTTP okidača | Uspješno povezani oba okidača s IoT Hub-om i pravilno upravljanje relejem | Uspješno povezan jedan okidač s IoT Hub-om i pravilno upravljanje relejem | Nije bilo moguće povezati okidače s IoT Hub-om |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.