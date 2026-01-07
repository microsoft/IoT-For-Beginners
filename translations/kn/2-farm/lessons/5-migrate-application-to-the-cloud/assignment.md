<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2026-01-07T05:20:13+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "kn"
}
-->
#manuelige relay niyantrana seerike

## Nirdeshagalu

Serverless koDige bahu vividha samayadallAdare audyogika tAhuvala sUTi mADabahudu, HTTP nivedanagaLoo sahitavAgide. Nimma relay niyantrana mele mAnavige siddha niyantrana seerike mADalu HTTP tAhuvala kaTa bardu, halavu vyakti relay na tAhuvala nirdEsada mUlaka relay na ON athavA OFF mADabahudu.

ee Karyakarikege, relay na on mADuvudu mattu off mADuvudu nirdisalu nimma Functions App ge eraDu HTTP tAhuvali seerikey annu seerisuva beku, ee paatha nirdiSha mattu kalitava sahita mADi device ge aadeshagala kaLanisuva vidhanavanunu punarUpayogisi.

kelavu tipugaLu:

* nivu nimma iruva Functions App ge HTTP tAhuvali seerike iMdu ide command nu seerisuva mAdhayamavide:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    `<trigger name>` na stala nAku HTTP tAhuvali hesarannu baradu. UdAharanege `relay_on` mattu `relay_off` hOgirtave.

* HTTP tAhuvalige parigraha niyantranavide. niyamagatavAgi function visheSha API key http URL togalike opapadutade. ee Karyakarikeya galu nivu ee badukana vilAku mADabahudu hAgU yAra kUDA eshtuvege nivu hELutitde nu mupayogamADabahudu. adakagi, HTTP tAhuvali gagi `function.json` fAyil nalli `authLevel` sEtTingannu hiMde ide vidha nalli mADabahudu:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 ee parigraha niyantranada visheShadeVVana tilidukollalu [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys) parishiLisu.

* HTTP tAhuvali samanya vidhAnadalli GET mattu POST requestgalannu samarthisuvavu. Adarinda nimma web brauzarinda call mADabahudu - web brauzarugaLu GET requestgalannu maduve.

    nimma Functions App na sthalIya mADuvAga, tAhuvali URL nu noVDabahudu:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    URL nunu nimma brauzaralli hAkisi `return` nu aLisi, athava `Ctrl+click` (`Cmd+click` macOS nalli) terminal window nalli link mendirisi toDiyuvade nimma default brauzar alli mADabahudu. Idu tAhuvali na naDeyisuvudu.

    > 💁 URL alli `/api` iruvude, HTTP tAhuvali samanya vidhAnadalli `api` subdomain nalli iruttade.

* nimma Functions App na sudha mudidAga, HTTP tAhuvali URL eMdu iruttade:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    `functions app name` nimma functions app na hesaru, `trigger name` nimma tAhuvali hesaru.

## Rubric

| MulyavanishthA | UtkrisTa | YathAvaStateya | SudhAraNeya Aavashyakate |
| -------- | --------- | -------- | ----------------- |
| HTTP tAhuvalannu srushtisu | Relay on athava off mADuvAga eraDu tAhuvali srushtisiddu, sariyAda hesarinda | sariyAda hesarinda ondu tAhuvali srushtisiddu | yAva tAhuvali kUDa srushtisalu sAdhyavAgilalvayite |
| HTTP tAhuvali mUlaka relay niyantrana | eraDu tAhuvali kUDa IoT Hub ge seerisiddu relay na sariyAgi niyantrisuva kshamata | ondu tAhuvali kUDa IoT Hub ge seerisiddu relay na sariyAgi niyantrisuva kshamata | tAhuvali gaLu IoT Hub ge seerisuvalilalvayite |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ವಿಮರ್ಶಾ ಸೂಚನೆ**:  
ಈ ದಸ್ತಾವೇಜನ್ನು AI ಭಾಷಾಂತರ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಭಾಷಾಂತರಿಸಲಾಗಿದೆ. ನಾವು ನಿಖರತೆಯ ಕಡೆ ಗಮನಹರಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಭಾಷಾಂತರಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸತ್ವತೆಯಿರಬಹುದಾಗಿದೆ ಎಂಬುದನ್ನು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ದಸ್ತಾವೇಜಿನ ಸ್ಥಳೀಯ ಭಾಷೆಯ ಪ್ರತಿಯನ್ನು ಅಧಿಕೃತ ಮೂಲವಾಗಿ ಪರಿಗಣಿಸಬೇಕು. ಮಹತ್ವದ ಮಾಹಿತಿಗಾಗಿ ನಿಪುಣ ಮಾನವ ಭಾಷಾಂತರಿಯನ್ನು ಸಲಹೆ ಮಾಡಲಾಗಿದೆ. ಈ ಭಾಷಾಂತರದಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ಅವಗಾಹನೆಗಳು ಅಥವಾ ತಾತ್ಪರ್ಯ ತಪ್ಪುಗಳಿಗಾಗಿ ನಾವು ಜವಾಬ್ದಾರಿಯಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->