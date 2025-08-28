<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T14:51:00+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "sl"
}
-->
# Dodaj ročno upravljanje releja

## Navodila

Strežniška koda brez strežnika se lahko sproži na različne načine, vključno z HTTP zahtevami. Z uporabo HTTP sprožilcev lahko dodate ročno preglasitev za upravljanje releja, kar omogoča, da nekdo vklopi ali izklopi rele prek spletne zahteve.

Za to nalogo morate dodati dva HTTP sprožilca v svojo aplikacijo Functions App, da vklopite in izklopite rele, pri čemer ponovno uporabite, kar ste se naučili v tej lekciji, za pošiljanje ukazov napravi.

Nekaj namigov:

* HTTP sprožilec lahko dodate v obstoječo aplikacijo Functions App z naslednjim ukazom:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Zamenjajte `<trigger name>` z imenom za vaš HTTP sprožilec. Uporabite nekaj, kot sta `relay_on` in `relay_off`.

* HTTP sprožilci lahko imajo nadzor dostopa. Privzeto zahtevajo funkcijsko specifičen API ključ, ki ga je treba posredovati z URL-jem za zagon. Za to nalogo lahko odstranite to omejitev, da lahko funkcijo zažene kdorkoli. To storite tako, da posodobite nastavitev `authLevel` v datoteki `function.json` za HTTP sprožilce na naslednje:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Več o tem nadzoru dostopa lahko preberete v [dokumentaciji o funkcijskih dostopnih ključih](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP sprožilci privzeto podpirajo GET in POST zahteve. To pomeni, da jih lahko pokličete z uporabo vašega spletnega brskalnika - spletni brskalniki izvajajo GET zahteve.

    Ko lokalno zaženete svojo aplikacijo Functions App, boste videli URL sprožilca:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Prilepite URL v svoj brskalnik in pritisnite `return`, ali pa `Ctrl+kliknite` (`Cmd+kliknite` na macOS) povezavo v terminalskem oknu v VS Code, da jo odprete v privzetem brskalniku. To bo sprožilo sprožilec.

    > 💁 Opazite, da URL vsebuje `/api` - HTTP sprožilci so privzeto v poddomeni `api`.

* Ko aplikacijo Functions App namestite, bo URL HTTP sprožilca:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Kjer `<functions app name>` predstavlja ime vaše aplikacije Functions App, in `<trigger name>` predstavlja ime vašega sprožilca.

## Merila ocenjevanja

| Merila | Odlično | Zadostno | Potrebno izboljšanje |
| ------- | -------- | -------- | -------------------- |
| Ustvarjanje HTTP sprožilcev | Ustvarjena 2 sprožilca za vklop in izklop releja z ustreznimi imeni | Ustvarjen en sprožilec z ustreznim imenom | Ni bilo mogoče ustvariti nobenega sprožilca |
| Upravljanje releja prek HTTP sprožilcev | Uspešno povezana oba sprožilca z IoT Hub in ustrezno upravljanje releja | Uspešno povezan en sprožilec z IoT Hub in ustrezno upravljanje releja | Ni bilo mogoče povezati sprožilcev z IoT Hub |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.