<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T23:03:02+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "cs"
}
-->
# Přidání manuálního ovládání relé

## Instrukce

Serverless kód může být spuštěn mnoha různými způsoby, včetně HTTP požadavků. Můžete použít HTTP triggery k přidání manuálního ovládání vašeho relé, což umožní někomu zapnout nebo vypnout relé prostřednictvím webového požadavku.

Pro tento úkol musíte přidat dva HTTP triggery do vaší Functions App, abyste mohli zapnout a vypnout relé, a využít to, co jste se naučili v této lekci, k odesílání příkazů zařízení.

Několik tipů:

* Můžete přidat HTTP trigger do vaší stávající Functions App pomocí následujícího příkazu:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Nahraďte `<trigger name>` názvem vašeho HTTP triggeru. Použijte například `relay_on` a `relay_off`.

* HTTP triggery mohou mít řízení přístupu. Ve výchozím nastavení vyžadují, aby byl s URL předán specifický API klíč funkce, aby mohly běžet. Pro tento úkol můžete toto omezení odstranit, aby mohl funkci spustit kdokoli. K tomu aktualizujte nastavení `authLevel` v souboru `function.json` pro HTTP triggery na následující:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Více o tomto řízení přístupu si můžete přečíst v [dokumentaci k přístupovým klíčům funkcí](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP triggery ve výchozím nastavení podporují GET a POST požadavky. To znamená, že je můžete volat pomocí vašeho webového prohlížeče - webové prohlížeče provádějí GET požadavky.

    Když spustíte svou Functions App lokálně, uvidíte URL triggeru:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Vložte URL do svého prohlížeče a stiskněte `Enter`, nebo `Ctrl+klikněte` (`Cmd+klikněte` na macOS) na odkaz v terminálovém okně ve VS Code, abyste jej otevřeli ve výchozím prohlížeči. Tím spustíte trigger.

    > 💁 Všimněte si, že URL obsahuje `/api` - HTTP triggery jsou ve výchozím nastavení v subdoméně `api`.

* Když nasadíte Functions App, URL HTTP triggeru bude:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Kde `<functions app name>` je název vaší Functions App a `<trigger name>` je název vašeho triggeru.

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Potřebuje zlepšení |
| -------- | ---------- | --------- | ------------------ |
| Vytvoření HTTP triggerů | Vytvořeny 2 triggery pro zapnutí a vypnutí relé s vhodnými názvy | Vytvořen jeden trigger s vhodným názvem | Nebyl vytvořen žádný trigger |
| Ovládání relé z HTTP triggerů | Oba triggery byly úspěšně připojeny k IoT Hub a správně ovládaly relé | Jeden trigger byl úspěšně připojen k IoT Hub a správně ovládal relé | Triggery nebyly připojeny k IoT Hub |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.