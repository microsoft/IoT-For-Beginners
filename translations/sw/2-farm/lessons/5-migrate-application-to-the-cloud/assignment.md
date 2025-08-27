<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T23:02:29+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "sw"
}
-->
# Ongeza Udhibiti wa Relay wa Mwongozo

## Maelekezo

Msimbo wa serverless unaweza kuchochewa na mambo mbalimbali, ikiwa ni pamoja na maombi ya HTTP. Unaweza kutumia vichochezi vya HTTP kuongeza udhibiti wa mwongozo kwa relay yako, kuruhusu mtu kuwasha au kuzima relay kupitia ombi la wavuti.

Kwa kazi hii, unahitaji kuongeza vichochezi viwili vya HTTP kwenye Functions App yako ili kuwasha na kuzima relay, ukitumia kile ulichojifunza katika somo hili kutuma amri kwa kifaa.

Baadhi ya vidokezo:

* Unaweza kuongeza kichochezi cha HTTP kwenye Functions App yako iliyopo kwa kutumia amri ifuatayo:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Badilisha `<trigger name>` na jina la kichochezi chako cha HTTP. Tumia majina kama `relay_on` na `relay_off`.

* Vichochezi vya HTTP vinaweza kuwa na udhibiti wa ufikiaji. Kwa chaguo-msingi, vinahitaji funguo maalum ya API ya kazi kupitishwa pamoja na URL ili kuendesha. Kwa kazi hii, unaweza kuondoa kizuizi hiki ili mtu yeyote aweze kuendesha kazi. Ili kufanya hivyo, sasisha mpangilio wa `authLevel` katika faili ya `function.json` kwa vichochezi vya HTTP kuwa:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Unaweza kusoma zaidi kuhusu udhibiti huu wa ufikiaji katika [nyaraka za funguo za ufikiaji wa Function](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Vichochezi vya HTTP kwa chaguo-msingi vinaunga mkono maombi ya GET na POST. Hii inamaanisha unaweza kuviita ukitumia kivinjari chako cha wavuti - vivinjari vya wavuti hufanya maombi ya GET.

    Unapoendesha Functions App yako ndani ya nchi, utaona URL ya kichochezi:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Bandika URL kwenye kivinjari chako na bonyeza `return`, au `Ctrl+click` (`Cmd+click` kwenye macOS) kiungo kwenye dirisha la terminal katika VS Code kufungua kwenye kivinjari chako cha chaguo-msingi. Hii itaendesha kichochezi.

    > 💁 Kumbuka kwamba URL ina `/api` ndani yake - vichochezi vya HTTP kwa chaguo-msingi viko kwenye subdomain ya `api`.

* Unapoweka Functions App, URL ya kichochezi cha HTTP itakuwa:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Ambapo `<functions app name>` ni jina la Functions App yako, na `<trigger name>` ni jina la kichochezi chako.

## Rubric

| Vigezo | Bora Kabisa | Inaridhisha | Inahitaji Kuboresha |
| -------- | --------- | -------- | ----------------- |
| Unda vichochezi vya HTTP | Viliundwa vichochezi 2 vya kuwasha na kuzima relay, na majina yanayofaa | Kimeundwa kichochezi kimoja na jina linalofaa | Haikuweza kuunda vichochezi vyovyote |
| Dhibiti relay kutoka kwa vichochezi vya HTTP | Iliweza kuunganisha vichochezi vyote viwili na IoT Hub na kudhibiti relay ipasavyo | Iliweza kuunganisha kichochezi kimoja na IoT Hub na kudhibiti relay ipasavyo | Haikuweza kuunganisha vichochezi na IoT Hub |

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.