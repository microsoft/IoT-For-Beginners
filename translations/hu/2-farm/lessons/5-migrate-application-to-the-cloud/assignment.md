<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T23:02:47+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "hu"
}
-->
# Manuális relévezérlés hozzáadása

## Útmutató

A szerver nélküli kódot számos dolog kiválthatja, például HTTP-kérések. HTTP-triggereket használhatsz arra, hogy manuális felülbírálást adj a relévezérléshez, lehetővé téve, hogy valaki egy webes kérésen keresztül be- vagy kikapcsolja a relét.

Ebben a feladatban két HTTP-triggert kell hozzáadnod a Functions App-odhoz, hogy a relét be- és kikapcsolhasd, újrahasznosítva azokat az ismereteket, amelyeket ebben a leckében tanultál az eszköznek küldött parancsokkal kapcsolatban.

Néhány tipp:

* Egy HTTP-triggert az alábbi paranccsal adhatsz hozzá a meglévő Functions App-odhoz:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Cseréld le a `<trigger name>` helyére a HTTP-trigger nevét. Használj például olyan neveket, mint `relay_on` és `relay_off`.

* A HTTP-triggereknél hozzáférés-szabályozás is beállítható. Alapértelmezés szerint egy funkcióspecifikus API-kulcsot kell megadni az URL-lel együtt a futtatáshoz. Ehhez a feladathoz eltávolíthatod ezt a korlátozást, hogy bárki futtathassa a funkciót. Ehhez frissítsd az `authLevel` beállítást a HTTP-triggereknél a `function.json` fájlban az alábbiak szerint:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 További információt a hozzáférés-szabályozásról a [Function access keys dokumentációban](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys) olvashatsz.

* A HTTP-triggereknél alapértelmezés szerint GET és POST kérések támogatottak. Ez azt jelenti, hogy böngészőből is meghívhatod őket - a böngészők GET kéréseket küldenek.

    Amikor helyben futtatod a Functions App-ot, látni fogod a trigger URL-jét:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Illeszd be az URL-t a böngésződbe, és nyomj `return`-t, vagy `Ctrl+click`-elj (`Cmd+click` macOS-en) a terminálablakban a VS Code-ban a linkre, hogy megnyisd az alapértelmezett böngésződben. Ez futtatni fogja a triggert.

    > 💁 Vedd észre, hogy az URL-ben szerepel az `/api` - a HTTP-triggereket alapértelmezés szerint az `api` aldomainben helyezik el.

* Amikor telepíted a Functions App-ot, a HTTP-trigger URL-je a következő lesz:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Ahol `<functions app name>` a Functions App neve, és `<trigger name>` a trigger neve.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| HTTP-triggereket hoz létre | 2 triggert hozott létre a relé be- és kikapcsolására, megfelelő nevekkel | Egy triggert hozott létre megfelelő névvel | Nem tudott triggert létrehozni |
| A relé vezérlése a HTTP-triggerekkel | Mindkét triggert sikeresen csatlakoztatta az IoT Hub-hoz, és megfelelően vezérelte a relét | Egy triggert sikeresen csatlakoztatott az IoT Hub-hoz, és megfelelően vezérelte a relét | Nem tudta csatlakoztatni a triggereket az IoT Hub-hoz |

---

**Felelősség kizárása**:  
Ez a dokumentum az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítási szolgáltatás segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.