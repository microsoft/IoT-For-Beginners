<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T01:24:36+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "tl"
}
-->
# Magdagdag ng Manual na Kontrol sa Relay

## Mga Instruksyon

Ang serverless na code ay maaaring ma-trigger ng iba't ibang bagay, kabilang ang mga HTTP request. Maaari mong gamitin ang HTTP triggers upang magdagdag ng manual na override sa iyong relay control, na nagbibigay-daan sa sinuman na i-on o i-off ang relay gamit ang isang web request.

Para sa gawaing ito, kailangan mong magdagdag ng dalawang HTTP triggers sa iyong Functions App upang i-on at i-off ang relay, gamit ang mga natutunan mo mula sa araling ito upang magpadala ng mga utos sa device.

Ilang mga pahiwatig:

* Maaari kang magdagdag ng HTTP trigger sa iyong umiiral na Functions App gamit ang sumusunod na command:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Palitan ang `<trigger name>` ng pangalan para sa iyong HTTP trigger. Gumamit ng mga pangalan tulad ng `relay_on` at `relay_off`.

* Ang mga HTTP trigger ay maaaring magkaroon ng access control. Sa default, nangangailangan sila ng function-specific na API key na kailangang ipasa kasama ng URL upang tumakbo. Para sa gawaing ito, maaari mong alisin ang restriksyong ito upang kahit sino ay maaaring magpatakbo ng function. Upang gawin ito, i-update ang setting na `authLevel` sa file na `function.json` para sa mga HTTP trigger sa sumusunod:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Maaari mong basahin ang higit pa tungkol sa access control na ito sa [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Ang mga HTTP trigger ay default na sumusuporta sa GET at POST requests. Nangangahulugan ito na maaari mo silang tawagin gamit ang iyong web browser - ang mga web browser ay gumagawa ng GET requests.

    Kapag pinatakbo mo ang iyong Functions App nang lokal, makikita mo ang URL ng trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    I-paste ang URL sa iyong browser at pindutin ang `return`, o `Ctrl+click` (`Cmd+click` sa macOS) ang link sa terminal window sa VS Code upang buksan ito sa iyong default na browser. Ito ay magpapatakbo ng trigger.

    > 💁 Pansinin na ang URL ay may `/api` dito - ang mga HTTP trigger ay default na nasa `api` subdomain.

* Kapag dineploy mo ang Functions App, ang HTTP trigger URL ay magiging:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Kung saan ang `<functions app name>` ay ang pangalan ng iyong Functions App, at ang `<trigger name>` ay ang pangalan ng iyong trigger.

## Rubric

| Pamantayan | Natatangi | Katanggap-tanggap | Kailangan ng Pagpapabuti |
| ---------- | --------- | ----------------- | ------------------------ |
| Gumawa ng HTTP triggers | Nakagawa ng 2 triggers upang i-on at i-off ang relay, na may angkop na mga pangalan | Nakagawa ng isang trigger na may angkop na pangalan | Hindi nakagawa ng anumang trigger |
| Kontrolin ang relay mula sa HTTP triggers | Nakakonekta ang parehong triggers sa IoT Hub at nakontrol ang relay nang maayos | Nakakonekta ang isang trigger sa IoT Hub at nakontrol ang relay nang maayos | Hindi nakakonekta ang mga triggers sa IoT Hub |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.