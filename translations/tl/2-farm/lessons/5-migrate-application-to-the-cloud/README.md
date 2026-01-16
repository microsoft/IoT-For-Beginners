<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T21:44:38+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "tl"
}
-->
# Ilipat ang iyong application logic sa cloud

![Isang sketchnote na buod ng araling ito](../../../../../translated_images/tl/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

Ang araling ito ay itinuro bilang bahagi ng [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) mula sa [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Kontrolin ang iyong IoT device gamit ang serverless code](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Panimula

Sa nakaraang aralin, natutunan mo kung paano ikonekta ang iyong plant soil moisture monitoring at relay control sa isang cloud-based na IoT service. Ang susunod na hakbang ay ilipat ang server code na kumokontrol sa timing ng relay sa cloud. Sa araling ito, matutunan mo kung paano ito gawin gamit ang serverless functions.

Sa araling ito, tatalakayin natin ang:

* [Ano ang serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Gumawa ng serverless application](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Gumawa ng IoT Hub event trigger](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Magpadala ng direct method requests mula sa serverless code](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [I-deploy ang iyong serverless code sa cloud](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Ano ang serverless?

Ang serverless, o serverless computing, ay tumutukoy sa paggawa ng maliliit na piraso ng code na tumatakbo sa cloud bilang tugon sa iba't ibang uri ng mga event. Kapag nangyari ang event, tatakbo ang iyong code at bibigyan ito ng data tungkol sa event. Ang mga event na ito ay maaaring magmula sa iba't ibang bagay, kabilang ang web requests, mga mensahe sa queue, pagbabago sa data sa database, o mga mensaheng ipinadala sa isang IoT service ng mga IoT device.

![Mga event na ipinapadala mula sa isang IoT service patungo sa isang serverless service, lahat ay pinoproseso nang sabay-sabay ng maraming function](../../../../../translated_images/tl/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 Kung gumamit ka na ng database triggers dati, maaari mong isipin ito bilang katulad nito, kung saan ang code ay na-trigger ng isang event tulad ng pag-insert ng row.

![Kapag maraming event ang ipinadala nang sabay-sabay, ang serverless service ay nag-e-scale up upang patakbuhin ang lahat ng ito nang sabay-sabay](../../../../../translated_images/tl/serverless-scaling.f8c769adf0413fd1.webp)

Ang iyong code ay tatakbo lamang kapag nangyari ang event, at hindi ito aktibo sa ibang oras. Kapag nangyari ang event, ang iyong code ay ilulunsad at tatakbo. Ginagawa nitong napaka-scalable ng serverless - kung maraming event ang nangyari nang sabay-sabay, maaaring patakbuhin ng cloud provider ang iyong function nang maraming beses nang sabay-sabay sa iba't ibang server na mayroon sila. Ang downside nito ay kung kailangan mong magbahagi ng impormasyon sa pagitan ng mga event, kailangan mong i-save ito sa isang lugar tulad ng database sa halip na i-store ito sa memory.

Ang iyong code ay isinusulat bilang isang function na tumatanggap ng mga detalye tungkol sa event bilang parameter. Maaari kang gumamit ng iba't ibang programming languages upang isulat ang mga serverless function na ito.

> 🎓 Ang serverless ay tinatawag ding Functions as a Service (FaaS) dahil ang bawat event trigger ay ipinatutupad bilang isang function sa code.

Sa kabila ng pangalan, ang serverless ay gumagamit pa rin ng mga server. Ang pangalan ay dahil hindi mo kailangang alalahanin ang mga server na kailangan upang patakbuhin ang iyong code, ang mahalaga lamang sa iyo ay ang iyong code ay tumatakbo bilang tugon sa isang event. Ang cloud provider ay may serverless *runtime* na namamahala sa pag-aallocate ng mga server, networking, storage, CPU, memory, at iba pang kinakailangan upang patakbuhin ang iyong code. Sa modelong ito, hindi ka nagbabayad per server para sa serbisyo, dahil walang server na direktang ginagamit. Sa halip, nagbabayad ka para sa oras na tumatakbo ang iyong code, at sa dami ng memory na nagamit.

> 💰 Ang serverless ay isa sa pinakamurang paraan upang patakbuhin ang code sa cloud. Halimbawa, sa kasalukuyang panahon ng pagsulat, ang isang cloud provider ay nagpapahintulot sa lahat ng iyong serverless functions na tumakbo nang pinagsama-sama ng 1,000,000 beses bawat buwan bago ka nila singilin, at pagkatapos nito ay sinisingil ka ng US$0.20 para sa bawat 1,000,000 executions. Kapag hindi tumatakbo ang iyong code, wala kang babayaran.

Bilang isang IoT developer, ang serverless model ay perpekto. Maaari kang magsulat ng function na tinatawag bilang tugon sa mga mensaheng ipinadala mula sa anumang IoT device na nakakonekta sa iyong cloud-hosted IoT service. Ang iyong code ay hahawak sa lahat ng mensaheng ipinadala, ngunit tatakbo lamang kapag kinakailangan.

✅ Balikan ang code na isinulat mo bilang server code na nakikinig sa mga mensahe gamit ang MQTT. Paano kaya ito tatakbo sa cloud gamit ang serverless? Sa tingin mo, paano maaaring baguhin ang code upang suportahan ang serverless computing?

> 💁 Ang serverless model ay lumalawak na rin sa iba pang cloud services bukod sa pagpapatakbo ng code. Halimbawa, may mga serverless databases na available sa cloud gamit ang serverless pricing model kung saan nagbabayad ka per request na ginawa laban sa database, tulad ng query o insert, karaniwang batay sa dami ng trabaho na ginawa upang maibigay ang request. Halimbawa, ang isang simpleng select ng isang row gamit ang primary key ay mas mura kaysa sa isang komplikadong operasyon na nagjo-join ng maraming table at nagbabalik ng libu-libong row.

## Gumawa ng serverless application

Ang serverless computing service mula sa Microsoft ay tinatawag na Azure Functions.

![Ang logo ng Azure Functions](../../../../../translated_images/tl/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

Ang maikling video sa ibaba ay nagbibigay ng overview ng Azure Functions:

[![Azure Functions overview video](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 I-click ang imahe sa itaas upang panoorin ang video

✅ Maglaan ng oras upang magsaliksik at basahin ang overview ng Azure Functions sa [Microsoft Azure Functions documentation](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Upang magsulat ng Azure Functions, magsisimula ka sa isang Azure Functions app gamit ang wika ng iyong pinili. Ang Azure Functions ay sumusuporta sa Python, JavaScript, TypeScript, C#, F#, Java, at Powershell. Sa araling ito, matututo kang magsulat ng Azure Functions app gamit ang Python.

> 💁 Ang Azure Functions ay sumusuporta rin sa custom handlers kaya maaari kang magsulat ng iyong functions gamit ang anumang wika na sumusuporta sa HTTP requests, kabilang ang mga mas lumang wika tulad ng COBOL.

Ang Functions apps ay binubuo ng isa o higit pang *triggers* - mga function na tumutugon sa mga event. Maaari kang magkaroon ng maraming triggers sa loob ng isang function app, lahat ay nagbabahagi ng karaniwang configuration. Halimbawa, sa configuration file ng iyong Functions app, maaari mong ilagay ang connection details ng iyong IoT Hub, at lahat ng function sa app ay maaaring gumamit nito upang kumonekta at makinig sa mga event.

### Gawain - i-install ang Azure Functions tooling

> Sa kasalukuyang panahon ng pagsulat, ang Azure Functions code tools ay hindi pa ganap na gumagana sa Apple Silicon para sa mga Python project. Kakailanganin mong gumamit ng Intel-based Mac, Windows PC, o Linux PC.

Isa sa mga magagandang tampok ng Azure Functions ay maaari mo itong patakbuhin nang lokal. Ang parehong runtime na ginagamit sa cloud ay maaaring patakbuhin sa iyong computer, na nagpapahintulot sa iyong magsulat ng code na tumutugon sa mga IoT message at patakbuhin ito nang lokal. Maaari mo ring i-debug ang iyong code habang hinahawakan ang mga event. Kapag nasiyahan ka na sa iyong code, maaari mo itong i-deploy sa cloud.

Ang Azure Functions tooling ay available bilang isang CLI, na kilala bilang Azure Functions Core Tools.

1. I-install ang Azure Functions core tools sa pamamagitan ng pagsunod sa mga tagubilin sa [Azure Functions Core Tools documentation](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. I-install ang Azure Functions extension para sa VS Code. Ang extension na ito ay nagbibigay ng suporta para sa paggawa, pag-debug, at pag-deploy ng Azure functions. Tingnan ang [Azure Functions extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) para sa mga tagubilin sa pag-install ng extension na ito sa VS Code.

Kapag dineploy mo ang iyong Azure Functions app sa cloud, kakailanganin nito ng kaunting cloud storage upang mag-imbak ng mga application file at log file. Kapag pinatakbo mo ang iyong Functions app nang lokal, kailangan mo pa ring kumonekta sa cloud storage, ngunit sa halip na gumamit ng aktwal na cloud storage, maaari kang gumamit ng storage emulator na tinatawag na [Azurite](https://github.com/Azure/Azurite). Ito ay tumatakbo nang lokal ngunit kumikilos tulad ng cloud storage.

> 🎓 Sa Azure, ang storage na ginagamit ng Azure Functions ay isang Azure Storage Account. Ang mga account na ito ay maaaring mag-imbak ng mga file, blobs, data sa tables, o data sa queues. Maaari mong ibahagi ang isang storage account sa maraming apps, tulad ng isang Functions app at isang web app.

1. Ang Azurite ay isang Node.js app, kaya kakailanganin mong i-install ang Node.js. Maaari mong makita ang download at installation instructions sa [Node.js website](https://nodejs.org/). Kung gumagamit ka ng Mac, maaari mo rin itong i-install mula sa [Homebrew](https://formulae.brew.sh/formula/node).

1. I-install ang Azurite gamit ang sumusunod na command (`npm` ay isang tool na naka-install kapag in-install mo ang Node.js):

    ```sh
    npm install -g azurite
    ```

1. Gumawa ng folder na tinatawag na `azurite` para magamit ng Azurite sa pag-iimbak ng data:

    ```sh
    mkdir azurite
    ```

1. Patakbuhin ang Azurite, gamit ang bagong folder na ito:

    ```sh
    azurite --location azurite
    ```

    Ang Azurite storage emulator ay maglulunsad at magiging handa para sa lokal na Functions runtime na kumonekta.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Gawain - gumawa ng Azure Functions project

Ang Azure Functions CLI ay maaaring gamitin upang gumawa ng bagong Functions app.

1. Gumawa ng folder para sa iyong Functions app at mag-navigate dito. Tawagin itong `soil-moisture-trigger`:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Gumawa ng Python virtual environment sa loob ng folder na ito:

    ```sh
    python3 -m venv .venv
    ```

1. I-activate ang virtual environment:

    * Sa Windows:
        * Kung gumagamit ka ng Command Prompt, o Command Prompt sa pamamagitan ng Windows Terminal, patakbuhin:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Kung gumagamit ka ng PowerShell, patakbuhin:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Sa macOS o Linux, patakbuhin:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ang mga command na ito ay dapat patakbuhin mula sa parehong lokasyon kung saan mo pinatakbo ang command upang gumawa ng virtual environment. Hindi mo kailangang mag-navigate sa `.venv` folder, dapat mong palaging patakbuhin ang activate command at anumang command upang mag-install ng mga package o magpatakbo ng code mula sa folder kung saan mo ginawa ang virtual environment.

1. Patakbuhin ang sumusunod na command upang gumawa ng Functions app sa folder na ito:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Ito ay lilikha ng tatlong file sa loob ng kasalukuyang folder:

    * `host.json` - ang JSON document na ito ay naglalaman ng mga setting para sa iyong Functions app. Hindi mo kailangang baguhin ang mga setting na ito.
    * `local.settings.json` - ang JSON document na ito ay naglalaman ng mga setting na gagamitin ng iyong app kapag tumatakbo nang lokal, tulad ng connection strings para sa iyong IoT Hub. Ang mga setting na ito ay lokal lamang at hindi dapat idagdag sa source code control. Kapag dineploy ang app sa cloud, ang mga setting na ito ay hindi kasama, sa halip ang iyong mga setting ay ikakarga mula sa application settings. Tatalakayin ito mamaya sa araling ito.
    * `requirements.txt` - ito ay isang [Pip requirements file](https://pip.pypa.io/en/stable/user_guide/#requirements-files) na naglalaman ng mga Pip package na kinakailangan upang patakbuhin ang iyong Functions app.

1. Ang `local.settings.json` file ay may setting para sa storage account na gagamitin ng Functions app. Ang default nito ay walang laman, kaya kailangang itakda. Upang kumonekta sa Azurite local storage emulator, itakda ang value nito sa sumusunod:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. I-install ang mga kinakailangang Pip package gamit ang requirements file:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Ang mga kinakailangang Pip package ay kailangang nasa file na ito, upang kapag dineploy ang Functions app sa cloud, masisiguro ng runtime na mai-install ang tamang mga package.

1. Upang masigurado na gumagana nang tama ang lahat, maaari mong simulan ang Functions runtime. Patakbuhin ang sumusunod na command upang gawin ito:

    ```sh
    func start
    ```

    Makikita mo ang runtime na nagsisimula at nag-uulat na wala itong nahanap na job functions (triggers).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Kung makakatanggap ka ng notification mula sa firewall, payagan ang access dahil kailangang magbasa at magsulat ng `func` application sa iyong network.
> ⚠️ Kung gumagamit ka ng macOS, maaaring may mga babala sa output:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Maaari mong balewalain ang mga ito basta't maayos na magsimula ang Functions app at maipakita ang mga tumatakbong function. Tulad ng nabanggit sa [tanong na ito sa Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), maaari itong balewalain.

1. Itigil ang Functions app sa pamamagitan ng pagpindot sa `ctrl+c`.

1. Buksan ang kasalukuyang folder sa VS Code, alinman sa pamamagitan ng pagbukas ng VS Code at pagbukas ng folder na ito, o sa pamamagitan ng pagtakbo ng sumusunod na command:

    ```sh
    code .
    ```

    Awtomatikong madedetect ng VS Code ang iyong Functions project at magpapakita ng notification na nagsasabing:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Ang notification](../../../../../translated_images/tl/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Piliin ang **Yes** mula sa notification na ito.

1. Siguraduhing tumatakbo ang Python virtual environment sa terminal ng VS Code. Itigil ito at i-restart kung kinakailangan.

## Gumawa ng IoT Hub event trigger

Ang Functions app ang shell ng iyong serverless code. Para tumugon sa mga event ng IoT Hub, maaari kang magdagdag ng IoT Hub trigger sa app na ito. Ang trigger na ito ay kailangang kumonekta sa stream ng mga mensahe na ipinapadala sa IoT Hub at tumugon sa mga ito. Para makuha ang stream ng mga mensahe, kailangang kumonekta ang iyong trigger sa *event hub compatible endpoint* ng IoT Hub.

Ang IoT Hub ay nakabase sa isa pang Azure service na tinatawag na Azure Event Hubs. Ang Event Hubs ay isang serbisyo na nagbibigay-daan sa pagpapadala at pagtanggap ng mga mensahe, at ang IoT Hub ay nagdadagdag ng mga feature para sa mga IoT device. Ang paraan ng pagkonekta para basahin ang mga mensahe mula sa IoT Hub ay pareho sa kung paano mo ito gagawin gamit ang Event Hubs.

✅ Mag-research: Basahin ang overview ng Event Hubs sa [Azure Event Hubs documentation](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Paano ikinukumpara ang mga pangunahing feature nito sa IoT Hub?

Para makakonekta ang isang IoT device sa IoT Hub, kailangan nitong gumamit ng secret key na nagsisiguro na ang mga pinapayagang device lamang ang makakakonekta. Ganito rin ang proseso kapag kumokonekta para basahin ang mga mensahe; ang iyong code ay mangangailangan ng connection string na naglalaman ng secret key, kasama ang mga detalye ng IoT Hub.

> 💁 Ang default na connection string na makukuha mo ay may **iothubowner** permissions, na nagbibigay ng buong access sa IoT Hub sa anumang code na gumagamit nito. Mas mainam na kumonekta gamit ang pinakamababang antas ng permissions na kinakailangan. Ito ay tatalakayin sa susunod na leksyon.

Kapag nakakonekta na ang iyong trigger, tatawagin ang code sa loob ng function para sa bawat mensahe na ipinadala sa IoT Hub, anuman ang device na nagpadala nito. Ang trigger ay ipapasa ang mensahe bilang parameter.

### Gawain - kunin ang Event Hub compatible endpoint connection string

1. Mula sa terminal ng VS Code, patakbuhin ang sumusunod na command para makuha ang connection string para sa Event Hub compatible endpoint ng IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan na ginamit mo para sa iyong IoT Hub.

1. Sa VS Code, buksan ang file na `local.settings.json`. Magdagdag ng sumusunod na karagdagang halaga sa loob ng seksyong `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Palitan ang `<connection string>` ng halaga mula sa nakaraang hakbang. Kailangan mong magdagdag ng kuwit pagkatapos ng linya sa itaas para maging valid ang JSON.

### Gawain - gumawa ng event trigger

Handa ka nang gumawa ng event trigger.

1. Mula sa terminal ng VS Code, patakbuhin ang sumusunod na command mula sa loob ng folder na `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Ito ay lilikha ng bagong Function na tinatawag na `iot-hub-trigger`. Ang trigger ay kokonekta sa Event Hub compatible endpoint sa IoT Hub, kaya maaari kang gumamit ng event hub trigger. Walang partikular na IoT Hub trigger.

Ito ay lilikha ng folder sa loob ng `soil-moisture-trigger` na tinatawag na `iot-hub-trigger` na naglalaman ng function na ito. Ang folder na ito ay magkakaroon ng mga sumusunod na file sa loob nito:

* `__init__.py` - ito ang Python code file na naglalaman ng trigger, gamit ang standard na Python file name convention para gawing Python module ang folder na ito.

    Ang file na ito ay maglalaman ng sumusunod na code:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Ang core ng trigger ay ang `main` function. Ang function na ito ang tatawagin gamit ang mga event mula sa IoT Hub. Ang function na ito ay may parameter na tinatawag na `event` na naglalaman ng `EventHubEvent`. Sa tuwing may mensahe na ipinadala sa IoT Hub, tatawagin ang function na ito at ipapasa ang mensahe bilang `event`, kasama ang mga properties na kapareho ng mga annotations na nakita mo sa nakaraang leksyon.

    Ang core ng function na ito ay naglo-log ng event.

* `function.json` - naglalaman ito ng configuration para sa trigger. Ang pangunahing configuration ay nasa seksyong tinatawag na `bindings`. Ang binding ay ang tawag sa koneksyon sa pagitan ng Azure Functions at iba pang Azure services. Ang function na ito ay may input binding sa isang event hub - kumokonekta ito sa event hub at tumatanggap ng data.

    > 💁 Maaari ka ring magkaroon ng output bindings para ang output ng isang function ay maipadala sa ibang serbisyo. Halimbawa, maaari kang magdagdag ng output binding sa isang database at ibalik ang IoT Hub event mula sa function, at ito ay awtomatikong maipasok sa database.

    ✅ Mag-research: Basahin ang tungkol sa bindings sa [Azure Functions triggers and bindings concepts documentation](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Ang seksyong `bindings` ay naglalaman ng configuration para sa binding. Ang mga mahalagang halaga ay:

  * `"type": "eventHubTrigger"` - sinasabi nito sa function na kailangan nitong makinig sa mga event mula sa Event Hub
  * `"name": "events"` - ito ang pangalan ng parameter na gagamitin para sa Event Hub events. Tumutugma ito sa pangalan ng parameter sa `main` function sa Python code.
  * `"direction": "in"` - ito ay isang input binding, ang data mula sa event hub ay pumapasok sa function
  * `"connection": ""` - tinutukoy nito ang pangalan ng setting para basahin ang connection string. Kapag tumatakbo nang lokal, babasahin nito ang setting mula sa `local.settings.json` file.

    > 💁 Ang connection string ay hindi maaaring itago sa `function.json` file, kailangan itong basahin mula sa settings. Ito ay para maiwasan ang aksidenteng paglalantad ng iyong connection string.

1. Dahil sa [isang bug sa Azure Functions template](https://github.com/Azure/azure-functions-templates/issues/1250), ang `function.json` ay may maling halaga para sa field na `cardinality`. I-update ang field na ito mula `many` sa `one`:

    ```json
    "cardinality": "one",
    ```

1. I-update ang halaga ng `"connection"` sa `function.json` file para ituro sa bagong halaga na idinagdag mo sa `local.settings.json` file:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Tandaan - kailangan itong ituro sa setting, hindi dapat maglaman ng aktwal na connection string.

1. Ang connection string ay naglalaman ng `eventHubName` value, kaya ang halaga para dito sa `function.json` file ay kailangang i-clear. I-update ang halaga nito sa isang empty string:

    ```json
    "eventHubName": "",
    ```

### Gawain - patakbuhin ang event trigger

1. Siguraduhing hindi tumatakbo ang IoT Hub event monitor. Kapag tumatakbo ito kasabay ng functions app, hindi makakakonekta ang functions app at hindi makakakonsumo ng mga event.

    > 💁 Maraming apps ang maaaring kumonekta sa IoT Hub endpoints gamit ang iba't ibang *consumer groups*. Ito ay tatalakayin sa susunod na leksyon.

1. Para patakbuhin ang Functions app, patakbuhin ang sumusunod na command mula sa terminal ng VS Code:

    ```sh
    func start
    ```

    Magsisimula ang Functions app, at madidiskubre ang `iot-hub-trigger` function. Pagkatapos, ipoproseso nito ang anumang mga event na naipadala na sa IoT Hub sa nakaraang araw.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Ang bawat tawag sa function ay napapalibutan ng `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` block sa output, kaya makikita mo kung ilang mensahe ang naproseso sa bawat tawag sa function.

1. Siguraduhing tumatakbo ang iyong IoT device. Makikita mo ang mga bagong soil moisture messages na lumalabas sa Functions app.

1. Itigil at i-restart ang Functions app. Makikita mo na hindi nito ipoproseso ang mga nakaraang mensahe muli, ipoproseso lamang nito ang mga bagong mensahe.

> 💁 Sinusuportahan din ng VS Code ang pag-debug ng iyong Functions. Maaari kang mag-set ng break points sa pamamagitan ng pag-click sa border sa simula ng bawat linya ng code, o paglalagay ng cursor sa isang linya ng code at pagpili sa *Run -> Toggle breakpoint*, o pagpindot sa `F9`. Maaari mong ilunsad ang debugger sa pamamagitan ng pagpili sa *Run -> Start debugging*, pagpindot sa `F5`, o pagpili sa *Run and debug* pane at pagpili sa **Start debugging** button. Sa paggawa nito, makikita mo ang mga detalye ng mga event na napoproseso.

#### Pag-troubleshoot

* Kung makakakuha ka ng sumusunod na error:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Siguraduhing tumatakbo ang Azurite at na-set mo ang `AzureWebJobsStorage` sa `local.settings.json` file sa `UseDevelopmentStorage=true`.

* Kung makakakuha ka ng sumusunod na error:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Siguraduhing na-set mo ang `cardinality` sa `function.json` file sa `one`.

* Kung makakakuha ka ng sumusunod na error:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Siguraduhing na-set mo ang `eventHubName` sa `function.json` file sa isang empty string.

## Magpadala ng direct method requests mula sa serverless code

Sa ngayon, ang iyong Functions app ay nakikinig sa mga mensahe mula sa IoT Hub gamit ang Event Hub compatible endpoint. Ngayon, kailangan mong magpadala ng mga command sa IoT device. Ginagawa ito sa pamamagitan ng paggamit ng ibang koneksyon sa IoT Hub gamit ang *Registry Manager*. Ang Registry Manager ay isang tool na nagbibigay-daan sa iyo na makita kung aling mga device ang nakarehistro sa IoT Hub, at makipag-ugnayan sa mga device na iyon sa pamamagitan ng pagpapadala ng cloud-to-device messages, direct method requests, o pag-update ng device twin. Maaari mo rin itong gamitin para magrehistro, mag-update, o mag-delete ng mga IoT device mula sa IoT Hub.

Para kumonekta sa Registry Manager, kailangan mo ng connection string.

### Gawain - kunin ang Registry Manager connection string

1. Para makuha ang connection string, patakbuhin ang sumusunod na command:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan na ginamit mo para sa iyong IoT Hub.

    Ang connection string ay hiniling para sa *ServiceConnect* policy gamit ang `--policy-name service` parameter. Kapag humiling ka ng connection string, maaari mong tukuyin kung anong mga permissions ang papayagan ng connection string na iyon. Ang ServiceConnect policy ay nagbibigay-daan sa iyong code na kumonekta at magpadala ng mga mensahe sa IoT devices.

    ✅ Mag-research: Basahin ang tungkol sa iba't ibang policies sa [IoT Hub permissions documentation](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Sa VS Code, buksan ang file na `local.settings.json`. Magdagdag ng sumusunod na karagdagang halaga sa loob ng seksyong `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Palitan ang `<connection string>` ng halaga mula sa nakaraang hakbang. Kailangan mong magdagdag ng kuwit pagkatapos ng linya sa itaas para maging valid ang JSON.

### Gawain - magpadala ng direct method request sa isang device

1. Ang SDK para sa Registry Manager ay available sa pamamagitan ng Pip package. Magdagdag ng sumusunod na linya sa `requirements.txt` file para idagdag ang dependency sa package na ito:

    ```sh
    azure-iot-hub
    ```

1. Siguraduhing naka-activate ang virtual environment sa terminal ng VS Code, at patakbuhin ang sumusunod na command para i-install ang Pip packages:

    ```sh
    pip install -r requirements.txt
    ```

1. Magdagdag ng sumusunod na imports sa `__init__.py` file:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Ini-import nito ang ilang system libraries, pati na rin ang mga libraries para makipag-ugnayan sa Registry Manager at magpadala ng direct method requests.

1. Alisin ang code mula sa loob ng `main` method, ngunit panatilihin ang method mismo.

1. Sa `main` method, magdagdag ng sumusunod na code:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Ang code na ito ay kumukuha ng body ng event na naglalaman ng JSON message na ipinadala ng IoT device.

    Pagkatapos, kinukuha nito ang device ID mula sa annotations na ipinasa kasama ng mensahe. Ang body ng event ay naglalaman ng mensahe na ipinadala bilang telemetry, ang `iothub_metadata` dictionary ay naglalaman ng mga properties na itinakda ng IoT Hub tulad ng device ID ng sender, at ang oras na ipinadala ang mensahe.

    Ang impormasyong ito ay pagkatapos ay nilo-log. Makikita mo ang logging na ito sa terminal kapag pinatakbo mo ang Function app nang lokal.

1. Sa ibaba nito, magdagdag ng sumusunod na code:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Ang code na ito ay kumukuha ng soil moisture mula sa mensahe. Pagkatapos, sinusuri nito ang soil moisture, at depende sa halaga, gumagawa ng helper class para sa direct method request para sa `relay_on` o `relay_off` direct method. Ang method request ay hindi nangangailangan ng payload, kaya isang empty JSON document ang ipinapadala.

1. Sa ibaba nito, magdagdag ng sumusunod na code:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Ang code na ito ay naglo-load ng `REGISTRY_MANAGER_CONNECTION_STRING` mula sa file na `local.settings.json`. Ang mga halaga sa file na ito ay ginagawang available bilang mga environment variable, at maaaring basahin gamit ang function na `os.environ`, isang function na nagbabalik ng dictionary ng lahat ng environment variables.

> 💁 Kapag ang code na ito ay na-deploy sa cloud, ang mga halaga sa file na `local.settings.json` ay itatakda bilang *Application Settings*, at maaaring basahin mula sa environment variables.

Pagkatapos, ang code ay lumilikha ng isang instance ng Registry Manager helper class gamit ang connection string.

1. Idagdag ang sumusunod na code sa ibaba nito:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Ang code na ito ay nagsasabi sa registry manager na magpadala ng direct method request sa device na nagpadala ng telemetry.

    > 💁 Sa mga bersyon ng app na ginawa mo sa mga naunang aralin gamit ang MQTT, ang mga relay control command ay ipinapadala sa lahat ng devices. Ang code ay inaasahan na mayroon ka lamang isang device. Ang bersyon ng code na ito ay nagpapadala ng method request sa isang partikular na device, kaya't ito ay gagana kung mayroon kang maraming setup ng moisture sensors at relays, na nagpapadala ng tamang direct method request sa tamang device.

1. Patakbuhin ang Functions app, at tiyaking ang iyong IoT device ay nagpapadala ng data. Makikita mo ang mga mensaheng pinoproseso at ang mga direct method request na ipinapadala. Ilipat ang soil moisture sensor sa loob at labas ng lupa upang makita ang pagbabago ng mga halaga at ang pag-on at pag-off ng relay.

> 💁 Makikita mo ang code na ito sa [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) folder.

## I-deploy ang iyong serverless code sa cloud

Ang iyong code ay gumagana na nang lokal, kaya ang susunod na hakbang ay i-deploy ang Functions App sa cloud.

### Gawain - lumikha ng cloud resources

Ang iyong Functions app ay kailangang i-deploy sa isang Functions App resource sa Azure, na nasa loob ng Resource Group na ginawa mo para sa iyong IoT Hub. Kakailanganin mo rin ng isang Storage Account na nilikha sa Azure upang palitan ang emulated na ginagamit mo nang lokal.

1. Patakbuhin ang sumusunod na command upang lumikha ng storage account:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Palitan ang `<storage_name>` ng pangalan para sa iyong storage account. Kailangang ito ay globally unique dahil ito ay bahagi ng URL na ginagamit upang ma-access ang storage account. Maaari ka lamang gumamit ng maliliit na letra at numero para sa pangalang ito, walang ibang karakter, at limitado ito sa 24 na karakter. Gumamit ng tulad ng `sms` at magdagdag ng natatanging identifier sa dulo, tulad ng ilang random na salita o ang iyong pangalan.

    Ang `--sku Standard_LRS` ay pumipili ng pricing tier, na pinipili ang pinakamurang general-purpose account. Walang libreng tier ng storage, at magbabayad ka para sa iyong ginagamit. Ang mga gastos ay medyo mababa, na ang pinakamahal na storage ay mas mababa sa US$0.05 bawat buwan bawat gigabyte na nakaimbak.

    ✅ Basahin ang tungkol sa pagpepresyo sa [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Patakbuhin ang sumusunod na command upang lumikha ng Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Palitan ang `<location>` ng lokasyon na ginamit mo noong nilikha ang Resource Group sa nakaraang aralin.

    Palitan ang `<storage_name>` ng pangalan ng storage account na nilikha mo sa nakaraang hakbang.

    Palitan ang `<functions_app_name>` ng natatanging pangalan para sa iyong Functions App. Kailangang ito ay globally unique dahil ito ay bahagi ng URL na maaaring gamitin upang ma-access ang Functions App. Gumamit ng tulad ng `soil-moisture-sensor-` at magdagdag ng natatanging identifier sa dulo, tulad ng ilang random na salita o ang iyong pangalan.

    Ang `--functions-version 3` na opsyon ay nagtatakda ng bersyon ng Azure Functions na gagamitin. Ang bersyon 3 ang pinakabagong bersyon.

    Ang `--os-type Linux` ay nagsasabi sa Functions runtime na gamitin ang Linux bilang OS upang i-host ang mga functions na ito. Ang mga functions ay maaaring i-host sa Linux o Windows, depende sa programming language na ginamit. Ang mga Python apps ay sinusuportahan lamang sa Linux.

### Gawain - i-upload ang iyong application settings

Kapag dinevelop mo ang iyong Functions App, nag-imbak ka ng ilang settings sa file na `local.settings.json` para sa connection strings ng iyong IoT Hub. Ang mga ito ay kailangang isulat sa Application Settings sa iyong Function App sa Azure upang magamit ng iyong code.

> 🎓 Ang file na `local.settings.json` ay para lamang sa lokal na development settings, at hindi dapat i-check in sa source code control, tulad ng GitHub. Kapag na-deploy sa cloud, ang Application Settings ang ginagamit. Ang Application Settings ay key/value pairs na naka-host sa cloud at binabasa mula sa environment variables alinman sa iyong code o ng runtime kapag ikinokonekta ang iyong code sa IoT Hub.

1. Patakbuhin ang sumusunod na command upang itakda ang `IOT_HUB_CONNECTION_STRING` setting sa Functions App Application Settings:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Palitan ang `<functions_app_name>` ng pangalan na ginamit mo para sa iyong Functions App.

    Palitan ang `<connection string>` ng halaga ng `IOT_HUB_CONNECTION_STRING` mula sa iyong `local.settings.json` file.

1. Ulitin ang hakbang sa itaas, ngunit itakda ang halaga ng `REGISTRY_MANAGER_CONNECTION_STRING` sa kaukulang halaga mula sa iyong `local.settings.json` file.

Kapag pinatakbo mo ang mga command na ito, maglalabas din ito ng listahan ng lahat ng Application Settings para sa function app. Maaari mong gamitin ito upang suriin kung tama ang iyong mga halaga.

> 💁 Makikita mo ang isang halaga na nakatakda na para sa `AzureWebJobsStorage`. Sa iyong `local.settings.json` file, ito ay nakatakda sa isang halaga upang gamitin ang lokal na storage emulator. Kapag nilikha mo ang Functions App, ipinapasa mo ang storage account bilang isang parameter, at ito ay awtomatikong itinatakda sa setting na ito.

### Gawain - i-deploy ang iyong Functions App sa cloud

Ngayon na ang Functions App ay handa na, ang iyong code ay maaaring i-deploy.

1. Patakbuhin ang sumusunod na command mula sa VS Code terminal upang i-publish ang iyong Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Palitan ang `<functions_app_name>` ng pangalan na ginamit mo para sa iyong Functions App.

Ang code ay ipapakete at ipapadala sa Functions App, kung saan ito ay ide-deploy at sisimulan. Magkakaroon ng maraming console output, na magtatapos sa kumpirmasyon ng deployment at isang listahan ng mga na-deploy na functions. Sa kasong ito, ang listahan ay maglalaman lamang ng trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Tiyaking tumatakbo ang iyong IoT device. Baguhin ang moisture levels sa pamamagitan ng pag-adjust sa soil moisture, o paglipat ng sensor sa loob at labas ng lupa. Makikita mo ang relay na nag-o-on at nag-o-off habang nagbabago ang soil moisture.

---

## 🚀 Hamon

Sa nakaraang aralin, pinamahalaan mo ang timing para sa relay sa pamamagitan ng pag-unsubscribe mula sa MQTT messages habang naka-on ang relay, at sa maikling panahon pagkatapos itong ma-off. Hindi mo magagamit ang pamamaraang ito dito - hindi mo maaaring i-unsubscribe ang iyong IoT Hub trigger.

Mag-isip ng iba't ibang paraan kung paano mo ito mahahawakan sa iyong Functions App.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Review at Pag-aaral sa Sarili

* Basahin ang tungkol sa serverless computing sa [Serverless Computing page sa Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Basahin ang tungkol sa paggamit ng serverless sa Azure kabilang ang ilang higit pang mga halimbawa sa [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Alamin ang higit pa tungkol sa Azure Functions sa [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions)

## Takdang Aralin

[Magdagdag ng manual relay control](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na pinagmulan. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.