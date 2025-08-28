<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T11:12:15+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "sk"
}
-->
# Pridanie manuálneho ovládania relé

## Pokyny

Serverless kód môže byť spustený rôznymi spôsobmi, vrátane HTTP požiadaviek. Môžete použiť HTTP spúšťače na pridanie manuálneho ovládania relé, čo umožní niekomu zapnúť alebo vypnúť relé prostredníctvom webovej požiadavky.

Pre túto úlohu musíte pridať dva HTTP spúšťače do svojej aplikácie Functions App na zapnutie a vypnutie relé, pričom využijete to, čo ste sa naučili v tejto lekcii na odosielanie príkazov zariadeniu.

Niekoľko tipov:

* HTTP spúšťač môžete pridať do existujúcej aplikácie Functions App pomocou nasledujúceho príkazu:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Nahraďte `<trigger name>` názvom pre váš HTTP spúšťač. Použite niečo ako `relay_on` a `relay_off`.

* HTTP spúšťače môžu mať kontrolu prístupu. Predvolene vyžadujú funkčne špecifický API kľúč, ktorý musí byť odoslaný s URL na spustenie. Pre túto úlohu môžete túto obmedzenie odstrániť, aby mohol funkciu spustiť ktokoľvek. Na to aktualizujte nastavenie `authLevel` v súbore `function.json` pre HTTP spúšťače na nasledujúce:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Viac o tejto kontrole prístupu si môžete prečítať v [dokumentácii k prístupovým kľúčom funkcií](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP spúšťače predvolene podporujú GET a POST požiadavky. To znamená, že ich môžete spustiť pomocou vášho webového prehliadača - webové prehliadače vykonávajú GET požiadavky.

    Keď spustíte svoju aplikáciu Functions App lokálne, uvidíte URL spúšťača:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Vložte URL do svojho prehliadača a stlačte `return`, alebo `Ctrl+klik` (`Cmd+klik` na macOS) na odkaz v terminálovom okne vo VS Code, aby ste ho otvorili vo svojom predvolenom prehliadači. Týmto spustíte spúšťač.

    > 💁 Všimnite si, že URL obsahuje `/api` - HTTP spúšťače sú predvolene v subdoméne `api`.

* Keď nasadíte aplikáciu Functions App, URL HTTP spúšťača bude:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Kde `<functions app name>` je názov vašej aplikácie Functions App a `<trigger name>` je názov vášho spúšťača.

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Vyžaduje zlepšenie |
| --------- | ---------- | ---------- | ------------------ |
| Vytvorenie HTTP spúšťačov | Vytvorené 2 spúšťače na zapnutie a vypnutie relé s vhodnými názvami | Vytvorený jeden spúšťač s vhodným názvom | Neboli vytvorené žiadne spúšťače |
| Ovládanie relé z HTTP spúšťačov | Oba spúšťače boli pripojené k IoT Hub a správne ovládali relé | Jeden spúšťač bol pripojený k IoT Hub a správne ovládal relé | Spúšťače neboli pripojené k IoT Hub |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.