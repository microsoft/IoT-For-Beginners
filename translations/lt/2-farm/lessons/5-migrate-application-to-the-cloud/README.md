# Perkelkite savo programos logiką į debesį

![Pamokos apžvalga piešinyje](../../../../../translated_images/lt/lesson-9.dfe99c8e891f48e1.webp)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Ši pamoka buvo dėstoma kaip [IoT pradedantiesiems 2 projektas - Skaitmeninė žemdirbystė](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) serijos dalis iš [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Valdykite savo IoT įrenginį naudodami serverless kodą](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Klausimynas prieš pamoką

[Klausimynas prieš pamoką](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Įvadas

Praeitoje pamokoje išmokote, kaip prijungti savo augalų dirvožemio drėgmės stebėjimo ir relės valdymo sistemą prie debesyje veikiančios IoT paslaugos. Kitas žingsnis – perkelti serverio kodą, kuris valdo relės laiką, į debesį. Šioje pamokoje sužinosite, kaip tai padaryti naudojant serverless funkcijas.

Šioje pamokoje aptarsime:

* [Kas yra serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Sukurkite serverless programą](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Sukurkite IoT Hub įvykio paleidiklį](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Siųskite tiesioginius metodų užklausas iš serverless kodo](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Įdiekite savo serverless kodą į debesį](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Kas yra serverless?

Serverless, arba serverless kompiuterija, apima mažų kodo blokų kūrimą, kurie vykdomi debesyje reaguojant į įvairius įvykius. Kai įvykis įvyksta, jūsų kodas vykdomas ir jam perduodami duomenys apie įvykį. Šie įvykiai gali būti įvairūs, įskaitant interneto užklausas, pranešimus eilėje, duomenų pokyčius duomenų bazėje ar pranešimus, kuriuos IoT įrenginiai siunčia IoT paslaugai.

![Įvykiai siunčiami iš IoT paslaugos į serverless paslaugą, visi apdorojami vienu metu kelių funkcijų](../../../../../translated_images/lt/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Jei anksčiau naudojote duomenų bazės paleidiklius, galite tai laikyti panašiu dalyku – kodas paleidžiamas įvykus įvykiui, pvz., įterpiant eilutę.

![Kai daug įvykių siunčiama vienu metu, serverless paslauga plečiasi, kad visus juos apdorotų vienu metu](../../../../../translated_images/lt/serverless-scaling.f8c769adf0413fd1.webp)

Jūsų kodas vykdomas tik tada, kai įvyksta įvykis, kitu metu jis nėra aktyvus. Įvykis įvyksta, jūsų kodas įkeliamas ir vykdomas. Tai daro serverless labai masteliniu – jei daug įvykių įvyksta vienu metu, debesų paslaugų teikėjas gali vykdyti jūsų funkciją tiek kartų, kiek reikia, vienu metu, naudodamas turimus serverius. Trūkumas yra tas, kad jei reikia dalintis informacija tarp įvykių, ją reikia išsaugoti kažkur, pvz., duomenų bazėje, o ne laikyti atmintyje.

Jūsų kodas rašomas kaip funkcija, kuri priima informaciją apie įvykį kaip parametrą. Serverless funkcijas galima rašyti naudojant įvairias programavimo kalbas.

> 🎓 Serverless taip pat vadinamas funkcijomis kaip paslauga (FaaS), nes kiekvienas įvykio paleidiklis įgyvendinamas kaip funkcija kode.

Nepaisant pavadinimo, serverless iš tikrųjų naudoja serverius. Pavadinimas reiškia, kad kaip kūrėjas jūs nesirūpinate serveriais, reikalingais jūsų kodui vykdyti, jums rūpi tik tai, kad jūsų kodas būtų vykdomas reaguojant į įvykį. Debesų paslaugų teikėjas turi serverless *vykdymo aplinką*, kuri valdo serverių, tinklų, saugyklų, procesorių, atminties ir visko, kas reikalinga jūsų kodui vykdyti, paskirstymą. Šis modelis reiškia, kad negalite mokėti už paslaugą pagal serverį, nes nėra serverio. Vietoj to mokate už laiką, kurį jūsų kodas vykdomas, ir už naudojamą atmintį.

> 💰 Serverless yra vienas pigiausių būdų vykdyti kodą debesyje. Pavyzdžiui, rašymo metu vienas debesų paslaugų teikėjas leidžia visoms jūsų serverless funkcijoms vykdyti bendrą 1,000,000 kartų per mėnesį prieš pradedant taikyti mokestį, o po to jie ima 0,20 USD už kiekvieną 1,000,000 vykdymų. Kai jūsų kodas nevykdomas, jūs nemokate.

Kaip IoT kūrėjas, serverless modelis yra idealus. Galite parašyti funkciją, kuri bus iškviesta reaguojant į pranešimus, siunčiamus iš bet kurio IoT įrenginio, prijungto prie jūsų debesyje talpinamos IoT paslaugos. Jūsų kodas apdoros visus siunčiamus pranešimus, tačiau bus vykdomas tik tada, kai to reikia.

✅ Peržiūrėkite kodą, kurį rašėte kaip serverio kodą, klausantį pranešimų per MQTT. Kaip tai galėtų veikti debesyje naudojant serverless? Kaip, jūsų manymu, kodas galėtų būti pakeistas, kad palaikytų serverless kompiuteriją?

> 💁 Serverless modelis plečiasi ir į kitas debesų paslaugas, be kodo vykdymo. Pavyzdžiui, serverless duomenų bazės yra prieinamos debesyje, naudojant serverless kainodaros modelį, kai mokate už kiekvieną užklausą, pateiktą duomenų bazei, pvz., užklausą ar įterpimą, paprastai remiantis tuo, kiek darbo reikia užklausai aptarnauti. Pavyzdžiui, vienos eilutės pasirinkimas pagal pirminį raktą kainuos mažiau nei sudėtinga operacija, jungianti daug lentelių ir grąžinanti tūkstančius eilučių.

## Sukurkite serverless programą

Microsoft serverless kompiuterijos paslauga vadinama Azure Functions.

![Azure Functions logotipas](../../../../../translated_images/lt/azure-functions-logo.1cfc8e3204c9c44a.webp)

Trumpas vaizdo įrašas žemiau pateikia Azure Functions apžvalgą.

[![Azure Functions apžvalgos vaizdo įrašas](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Spustelėkite paveikslėlį aukščiau, kad peržiūrėtumėte vaizdo įrašą.

✅ Skirkite akimirką atlikti tyrimą ir perskaityti Azure Functions apžvalgą [Microsoft Azure Functions dokumentacijoje](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Norėdami rašyti Azure Functions, pradedate nuo Azure Functions programos pasirinkta kalba. Azure Functions palaiko Python, JavaScript, TypeScript, C#, F#, Java ir Powershell. Šioje pamokoje išmoksite, kaip rašyti Azure Functions programą naudojant Python.

> 💁 Azure Functions taip pat palaiko pasirinktinius tvarkytuvus, todėl galite rašyti funkcijas bet kuria kalba, palaikančia HTTP užklausas, įskaitant senesnes kalbas, tokias kaip COBOL.

Functions programos susideda iš vieno ar daugiau *paleidiklių* – funkcijų, kurios reaguoja į įvykius. Vienoje Functions programoje galite turėti kelis paleidiklius, kurie dalijasi bendru konfigūracija. Pavyzdžiui, jūsų Functions programos konfigūracijos faile galite turėti IoT Hub prisijungimo duomenis, ir visos programos funkcijos gali naudoti šiuos duomenis prisijungti ir klausytis įvykių.

### Užduotis – įdiekite Azure Functions įrankius

> Rašymo metu Azure Functions kodo įrankiai nėra visiškai suderinami su Apple Silicon naudojant Python projektus. Jums reikės naudoti Intel pagrindu veikiančią Mac, Windows PC arba Linux PC.

Vienas puikus Azure Functions bruožas yra tai, kad galite juos vykdyti lokaliai. Ta pati vykdymo aplinka, kuri naudojama debesyje, gali būti vykdoma jūsų kompiuteryje, leidžiant jums rašyti kodą, kuris reaguoja į IoT pranešimus, ir vykdyti jį lokaliai. Jūs netgi galite derinti savo kodą, kai įvykiai apdorojami. Kai būsite patenkinti savo kodu, jį galima įdiegti debesyje.

Azure Functions įrankiai yra prieinami kaip CLI, žinomas kaip Azure Functions Core Tools.

1. Įdiekite Azure Functions Core Tools, vadovaudamiesi instrukcijomis [Azure Functions Core Tools dokumentacijoje](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Įdiekite Azure Functions plėtinį VS Code. Šis plėtinys suteikia palaikymą kuriant, derinant ir diegiant Azure Functions. Žr. [Azure Functions plėtinio dokumentaciją](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions), kad sužinotumėte, kaip įdiegti šį plėtinį VS Code.

Kai įdiegiate savo Azure Functions programą debesyje, jai reikia nedidelės debesų saugyklos, kad būtų saugomi tokie dalykai kaip programos failai ir žurnalo failai. Kai vykdote savo Functions programą lokaliai, vis tiek reikia prisijungti prie debesų saugyklos, tačiau vietoj tikros debesų saugyklos galite naudoti saugyklos emuliatorių, vadinamą [Azurite](https://github.com/Azure/Azurite). Jis veikia lokaliai, bet elgiasi kaip debesų saugykla.

> 🎓 Azure saugykloje, kurią naudoja Azure Functions, yra Azure Storage Account. Šios paskyros gali saugoti failus, blobus, duomenis lentelėse arba duomenis eilėse. Vieną saugyklos paskyrą galite dalintis tarp daugelio programų, pvz., Functions programos ir interneto programos.

1. Azurite yra Node.js programa, todėl jums reikės įdiegti Node.js. Atsisiuntimo ir diegimo instrukcijas rasite [Node.js svetainėje](https://nodejs.org/). Jei naudojate Mac, taip pat galite ją įdiegti iš [Homebrew](https://formulae.brew.sh/formula/node).

1. Įdiekite Azurite naudodami šią komandą (`npm` yra įrankis, kuris įdiegtas kartu su Node.js):

    ```sh
    npm install -g azurite
    ```

1. Sukurkite aplanką, pavadintą `azurite`, kurį Azurite naudos duomenims saugoti:

    ```sh
    mkdir azurite
    ```

1. Paleiskite Azurite, perduodami jam šį naują aplanką:

    ```sh
    azurite --location azurite
    ```

    Azurite saugyklos emuliatorius bus paleistas ir pasiruošęs prisijungti prie vietinės Functions vykdymo aplinkos.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Užduotis – sukurkite Azure Functions projektą

Azure Functions CLI gali būti naudojamas naujai Functions programai sukurti.

1. Sukurkite aplanką savo Functions programai ir pereikite į jį. Pavadinkite jį `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Sukurkite Python virtualią aplinką šiame aplanke:

    ```sh
    python3 -m venv .venv
    ```

1. Aktyvuokite virtualią aplinką:

    * Windows:
        * Jei naudojate Command Prompt arba Command Prompt per Windows Terminal, vykdykite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jei naudojate PowerShell, vykdykite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS arba Linux, vykdykite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Šias komandas reikia vykdyti iš tos pačios vietos, kurioje vykdėte komandą virtualiai aplinkai sukurti. Jums niekada nereikės pereiti į `.venv` aplanką, visada turėtumėte vykdyti aktyvavimo komandą ir bet kokias komandas paketams įdiegti ar kodui vykdyti iš aplanko, kuriame buvote, kai sukūrėte virtualią aplinką.

1. Vykdykite šią komandą, kad sukurtumėte Functions programą šiame aplanke:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Tai sukurs tris failus dabartiniame aplanke:

    * `host.json` – šis JSON dokumentas turi nustatymus jūsų Functions programai. Jums nereikės keisti šių nustatymų.
    * `local.settings.json` – šis JSON dokumentas turi nustatymus, kuriuos jūsų programa naudos vykdant lokaliai, pvz., prisijungimo eilutes jūsų IoT Hub. Šie nustatymai yra tik vietiniai ir neturėtų būti įtraukti į šaltinio kodo kontrolę. Kai programa bus įdiegta debesyje, šie nustatymai nebus įdiegti, vietoj to jūsų nustatymai bus įkelti iš programos nustatymų. Tai bus aptarta vėliau šioje pamokoje.
    * `requirements.txt` – tai [Pip reikalavimų failas](https://pip.pypa.io/en/stable/user_guide/#requirements-files), kuriame yra Pip paketai, reikalingi jūsų Functions programai vykdyti.

1. `local.settings.json` faile yra nustatymas saugyklos paskyrai, kurią naudos Functions programa. Šis nustatymas pagal numatymą yra tuščias, todėl jį reikia nustatyti. Norėdami prisijungti prie Azurite vietinės saugyklos emuliatoriaus, nustatykite šią reikšmę:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Įdiekite reikalingus Pip paketus naudodami reikalavimų failą:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Reikalingi Pip paketai turi būti šiame faile, kad kai Functions programa bus įdiegta debesyje, vykdymo aplinka galėtų užtikrinti, kad įdiegs teisingus paketus.

1. Norėdami patikrinti, ar viskas veikia tinkamai, galite paleisti Functions vykdymo aplinką. Vykdykite šią komandą:

    ```sh
    func start
    ```

    Pamatysite, kaip vykdymo aplinka paleidžiama ir praneša, kad nerado jokių funkcijų (paleidiklių).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Jei gaunate ugniasienės pranešimą, suteikite prieigą, nes `func` programa turi turėti galimybę skaityti ir rašyti jūsų tinklą.
> ⚠️ Jei naudojate macOS, išvestyje gali būti įspėjimų:
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
> Juos galite ignoruoti, jei Functions programa paleidžiama teisingai ir rodo veikiančias funkcijas. Kaip nurodyta [Microsoft Docs Q&A klausime](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), tai galima ignoruoti.

1. Sustabdykite Functions programą paspausdami `ctrl+c`.

1. Atidarykite dabartinį aplanką VS Code programoje, arba atidarydami VS Code ir tada šį aplanką, arba vykdydami šią komandą:

    ```sh
    code .
    ```

    VS Code aptiks jūsų Functions projektą ir parodys pranešimą:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Pranešimas](../../../../../translated_images/lt/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Pasirinkite **Yes** iš šio pranešimo.

1. Įsitikinkite, kad Python virtuali aplinka veikia VS Code terminale. Jei reikia, nutraukite ir paleiskite ją iš naujo.

## Sukurkite IoT Hub įvykio trigerį

Functions programa yra jūsų serverless kodo apvalkalas. Norėdami reaguoti į IoT Hub įvykius, galite pridėti IoT Hub trigerį prie šios programos. Šis trigeris turi prisijungti prie pranešimų srauto, kuris siunčiamas į IoT Hub, ir į juos reaguoti. Norėdami gauti šį pranešimų srautą, jūsų trigeris turi prisijungti prie IoT Hub *event hub compatible endpoint*.

IoT Hub yra pagrįstas kita Azure paslauga, vadinama Azure Event Hubs. Event Hubs leidžia siųsti ir gauti pranešimus, o IoT Hub prideda funkcijas, skirtas IoT įrenginiams. Prijungimo būdas, norint skaityti pranešimus iš IoT Hub, yra toks pat, kaip naudojant Event Hubs.

✅ Atlikite tyrimą: Perskaitykite Event Hubs apžvalgą [Azure Event Hubs dokumentacijoje](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Kaip pagrindinės funkcijos lyginamos su IoT Hub?

Kad IoT įrenginys galėtų prisijungti prie IoT Hub, jis turi naudoti slaptą raktą, kuris užtikrina, kad prisijungti gali tik leidžiami įrenginiai. Tas pats taikoma ir prisijungimui skaityti pranešimus – jūsų kodui reikės prisijungimo eilutės, kurioje yra slaptas raktas ir IoT Hub detalės.

> 💁 Numatytoji prisijungimo eilutė turi **iothubowner** leidimus, kurie suteikia bet kokiam kodui, naudojančiam ją, pilnus leidimus IoT Hub. Idealiu atveju turėtumėte prisijungti su mažiausiu reikalingu leidimų lygiu. Tai bus aptarta kitoje pamokoje.

Kai jūsų trigeris prisijungia, funkcijos viduje esantis kodas bus iškviečiamas kiekvienam pranešimui, siunčiamam į IoT Hub, nepriklausomai nuo to, kuris įrenginys jį išsiuntė. Trigeris perduos pranešimą kaip parametrą.

### Užduotis - gauti Event Hub suderinamo endpoint prisijungimo eilutę

1. VS Code terminale vykdykite šią komandą, kad gautumėte prisijungimo eilutę IoT Hub Event Hub suderinamam endpoint:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` į jūsų IoT Hub pavadinimą.

1. VS Code programoje atidarykite `local.settings.json` failą. Pridėkite šią papildomą reikšmę `Values` sekcijoje:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Pakeiskite `<connection string>` į reikšmę iš ankstesnio žingsnio. Jums reikės pridėti kablelį po ankstesnės eilutės, kad JSON būtų galiojantis.

### Užduotis - sukurti įvykio trigerį

Dabar galite sukurti įvykio trigerį.

1. VS Code terminale vykdykite šią komandą iš `soil-moisture-trigger` aplanko:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Tai sukurs naują funkciją, pavadintą `iot-hub-trigger`. Trigeris prisijungs prie Event Hub suderinamo endpoint IoT Hub, todėl galite naudoti Event Hub trigerį. Specifinio IoT Hub trigerio nėra.

Tai sukurs aplanką `soil-moisture-trigger` aplanke, pavadintą `iot-hub-trigger`, kuriame bus ši funkcija. Šiame aplanke bus šie failai:

* `__init__.py` - tai Python kodo failas, kuriame yra trigeris, naudojant standartinį Python failų pavadinimų konvenciją, kad šis aplankas taptų Python moduliu.

    Šiame faile bus toks kodas:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Trigerio pagrindas yra `main` funkcija. Ši funkcija yra iškviečiama su įvykiais iš IoT Hub. Funkcija turi parametrą, vadinamą `event`, kuris yra `EventHubEvent`. Kiekvieną kartą, kai pranešimas siunčiamas į IoT Hub, ši funkcija yra iškviečiama, perduodant pranešimą kaip `event`, kartu su savybėmis, kurios yra tokios pačios kaip anotacijos, kurias matėte ankstesnėje pamokoje.

    Funkcijos pagrindas yra įvykio registravimas.

* `function.json` - tai trigerio konfigūracija. Pagrindinė konfigūracija yra sekcijoje, vadinamoje `bindings`. Binding yra terminas, apibūdinantis ryšį tarp Azure Functions ir kitų Azure paslaugų. Ši funkcija turi įvesties binding į Event Hub - ji prisijungia prie Event Hub ir gauna duomenis.

    > 💁 Taip pat galite turėti išvesties binding, kad funkcijos išvestis būtų siunčiama į kitą paslaugą. Pavyzdžiui, galite pridėti išvesties binding į duomenų bazę ir grąžinti IoT Hub įvykį iš funkcijos, ir jis automatiškai bus įterptas į duomenų bazę.

    ✅ Atlikite tyrimą: Perskaitykite apie binding [Azure Functions triggers and bindings concepts dokumentacijoje](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    `bindings` sekcija apima binding konfigūraciją. Svarbios reikšmės yra:

  * `"type": "eventHubTrigger"` - tai nurodo funkcijai, kad ji turi klausytis įvykių iš Event Hub
  * `"name": "events"` - tai parametro pavadinimas, naudojamas Event Hub įvykiams. Tai atitinka parametro pavadinimą `main` funkcijoje Python kode.
  * `"direction": "in"` - tai įvesties binding, duomenys iš Event Hub ateina į funkciją
  * `"connection": ""` - tai apibrėžia nustatymo pavadinimą, iš kurio skaitoma prisijungimo eilutė. Vietiniu būdu vykdant, tai bus skaitoma iš `local.settings.json` failo.

    > 💁 Prisijungimo eilutė negali būti saugoma `function.json` faile, ji turi būti skaitoma iš nustatymų. Tai daroma, kad netyčia neatskleistumėte prisijungimo eilutės.

1. Dėl [klaidos Azure Functions šablone](https://github.com/Azure/azure-functions-templates/issues/1250), `function.json` turi neteisingą reikšmę `cardinality` laukui. Atnaujinkite šį lauką iš `many` į `one`:

    ```json
    "cardinality": "one",
    ```

1. Atnaujinkite `"connection"` reikšmę `function.json` faile, kad ji nurodytų naują reikšmę, kurią pridėjote `local.settings.json` faile:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Atminkite - tai turi nurodyti nustatymą, o ne turėti faktinę prisijungimo eilutę.

1. Prisijungimo eilutė turi `eventHubName` reikšmę, todėl šios reikšmės `function.json` faile reikia išvalyti. Atnaujinkite šią reikšmę į tuščią eilutę:

    ```json
    "eventHubName": "",
    ```

### Užduotis - paleisti įvykio trigerį

1. Įsitikinkite, kad IoT Hub įvykių monitorius neveikia. Jei jis veikia tuo pačiu metu kaip Functions programa, Functions programa negalės prisijungti ir vartoti įvykių.

    > 💁 Kelios programos gali prisijungti prie IoT Hub endpoint naudojant skirtingas *consumer groups*. Tai bus aptarta vėlesnėje pamokoje.

1. Norėdami paleisti Functions programą, vykdykite šią komandą iš VS Code terminalo:

    ```sh
    func start
    ```

    Functions programa paleis, aptiks `iot-hub-trigger` funkciją ir apdoros visus įvykius, kurie jau buvo išsiųsti į IoT Hub per pastarąją dieną.

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

    Kiekvienas funkcijos iškvietimas bus apsuptas `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` bloku išvestyje, todėl matysite, kiek pranešimų buvo apdorota kiekviename funkcijos iškvietime.

1. Įsitikinkite, kad jūsų IoT įrenginys veikia. Matysite naujus dirvožemio drėgmės pranešimus, atsirandančius Functions programoje.

1. Sustabdykite ir paleiskite Functions programą iš naujo. Matysite, kad ji neapdoros ankstesnių pranešimų, o tik naujus pranešimus.

> 💁 VS Code taip pat palaiko jūsų Functions derinimą. Galite nustatyti pertraukos taškus spustelėdami ant linijos pradžios krašto arba pasirinkdami *Run -> Toggle breakpoint*, arba paspausdami `F9`. Galite paleisti derinimo įrankį pasirinkdami *Run -> Start debugging*, paspausdami `F5`, arba pasirinkdami *Run and debug* skydelį ir spustelėdami **Start debugging** mygtuką. Taip galite matyti apdorojamų įvykių detales.

#### Trikčių šalinimas

* Jei gaunate šią klaidą:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Patikrinkite, ar veikia Azurite ir ar nustatėte `AzureWebJobsStorage` `local.settings.json` faile į `UseDevelopmentStorage=true`.

* Jei gaunate šią klaidą:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Patikrinkite, ar nustatėte `cardinality` `function.json` faile į `one`.

* Jei gaunate šią klaidą:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Patikrinkite, ar nustatėte `eventHubName` `function.json` faile į tuščią eilutę.

## Siųsti tiesioginius metodų užklausas iš serverless kodo

Iki šiol jūsų Functions programa klausosi pranešimų iš IoT Hub naudodama Event Hub suderinamą endpoint. Dabar reikia siųsti komandas IoT įrenginiui. Tai daroma naudojant kitą prisijungimą prie IoT Hub per *Registry Manager*. Registry Manager yra įrankis, leidžiantis matyti, kurie įrenginiai yra registruoti IoT Hub, ir bendrauti su tais įrenginiais, siunčiant pranešimus iš debesies į įrenginį, tiesiogines metodų užklausas arba atnaujinant įrenginio dvynį. Taip pat galite jį naudoti registruoti, atnaujinti arba ištrinti IoT įrenginius iš IoT Hub.

Norėdami prisijungti prie Registry Manager, jums reikia prisijungimo eilutės.

### Užduotis - gauti Registry Manager prisijungimo eilutę

1. Norėdami gauti prisijungimo eilutę, vykdykite šią komandą:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` į jūsų IoT Hub pavadinimą.

    Prisijungimo eilutė prašoma *ServiceConnect* politikai naudojant `--policy-name service` parametrą. Kai prašote prisijungimo eilutės, galite nurodyti, kokius leidimus ta prisijungimo eilutė leis. ServiceConnect politika leidžia jūsų kodui prisijungti ir siųsti pranešimus IoT įrenginiams.

    ✅ Atlikite tyrimą: Perskaitykite apie skirtingas politikas [IoT Hub leidimų dokumentacijoje](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. VS Code programoje atidarykite `local.settings.json` failą. Pridėkite šią papildomą reikšmę `Values` sekcijoje:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Pakeiskite `<connection string>` į reikšmę iš ankstesnio žingsnio. Jums reikės pridėti kablelį po ankstesnės eilutės, kad JSON būtų galiojantis.

### Užduotis - siųsti tiesioginę metodų užklausą į įrenginį

1. Registry Manager SDK yra pasiekiamas per Pip paketą. Pridėkite šią eilutę į `requirements.txt` failą, kad pridėtumėte priklausomybę nuo šio paketo:

    ```sh
    azure-iot-hub
    ```

1. Įsitikinkite, kad VS Code terminale aktyvuota virtuali aplinka, ir vykdykite šią komandą, kad įdiegtumėte Pip paketus:

    ```sh
    pip install -r requirements.txt
    ```

1. Pridėkite šiuos importus į `__init__.py` failą:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Tai importuoja kai kurias sistemos bibliotekas, taip pat bibliotekas, skirtas Registry Manager sąveikai ir tiesioginių metodų užklausų siuntimui.

1. Pašalinkite kodą iš `main` metodo, bet palikite patį metodą.

1. `main` metode pridėkite šį kodą:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Šis kodas ištraukia įvykio turinį, kuriame yra JSON pranešimas, siunčiamas IoT įrenginio.

    Tada jis gauna įrenginio ID iš anotacijų, perduotų su pranešimu. Įvykio turinys apima pranešimą, siunčiamą kaip telemetriją, o `iothub_metadata` žodynas apima savybes, nustatytas IoT Hub, tokias kaip siuntėjo įrenginio ID ir pranešimo siuntimo laiką.

    Ši informacija yra registruojama. Matysite šį registravimą terminale, kai vykdysite Functions programą vietiniu būdu.

1. Po to pridėkite šį kodą:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Šis kodas gauna dirvožemio drėgmę iš pranešimo. Tada jis patikrina dirvožemio drėgmę ir, priklausomai nuo reikšmės, sukuria pagalbinę klasę tiesioginės metodų užklausos `relay_on` arba `relay_off` tiesioginiam metodui. Metodų užklausa nereikalauja turinio, todėl siunčiamas tuščias JSON dokumentas.

1. Po to pridėkite šį kodą:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Šis kodas įkelia `REGISTRY_MANAGER_CONNECTION_STRING` iš `local.settings.json` failo. Šio failo reikšmės tampa aplinkos kintamaisiais, kuriuos galima nuskaityti naudojant `os.environ` funkciją, grąžinančią visų aplinkos kintamųjų žodyną.

> 💁 Kai šis kodas yra įdiegtas debesyje, `local.settings.json` failo reikšmės bus nustatytos kaip *Application Settings*, ir jas galima nuskaityti iš aplinkos kintamųjų.

Tada kodas sukuria Registry Manager pagalbinės klasės egzempliorių, naudodamas prisijungimo eilutę.

1. Po to pridėkite šį kodą:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Šis kodas nurodo Registry Manager išsiųsti tiesioginio metodo užklausą įrenginiui, kuris siuntė telemetriją.

    > 💁 Ankstesnėse pamokose, kuriose naudojote MQTT, relės valdymo komandos buvo siunčiamos visiems įrenginiams. Kodas darė prielaidą, kad turėsite tik vieną įrenginį. Ši kodo versija siunčia metodo užklausą vienam įrenginiui, todėl ji veiks, jei turėsite kelis drėgmės jutiklių ir relių rinkinius, siunčiant tinkamą tiesioginio metodo užklausą tinkamam įrenginiui.

1. Paleiskite Functions programą ir įsitikinkite, kad jūsų IoT įrenginys siunčia duomenis. Pamatysite, kaip pranešimai yra apdorojami ir tiesioginio metodo užklausos siunčiamos. Perkelkite dirvožemio drėgmės jutiklį į dirvožemį ir iš jo, kad pamatytumėte, kaip keičiasi reikšmės ir relė įsijungia bei išsijungia.

> 💁 Šį kodą galite rasti [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) aplanke.

## Įdiekite savo serverless kodą į debesį

Jūsų kodas dabar veikia lokaliai, todėl kitas žingsnis yra įdiegti Functions App į debesį.

### Užduotis - sukurkite debesies resursus

Jūsų Functions programa turi būti įdiegta į Functions App resursą Azure platformoje, esančią Resource Group, kurią sukūrėte savo IoT Hub. Taip pat reikės sukurti Storage Account Azure platformoje, kuris pakeis lokaliai emuliuojamą saugyklą.

1. Paleiskite šią komandą, kad sukurtumėte saugyklos paskyrą:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Pakeiskite `<storage_name>` į saugyklos paskyros pavadinimą. Jis turi būti globaliai unikalus, nes sudaro dalį URL, naudojamo pasiekti saugyklos paskyrą. Šiame pavadinime galite naudoti tik mažąsias raides ir skaičius, jokių kitų simbolių, ir jis yra ribotas iki 24 simbolių. Naudokite kažką panašaus į `sms` ir pridėkite unikalų identifikatorių, pvz., atsitiktinius žodžius ar savo vardą.

    `--sku Standard_LRS` parenka kainų lygį, pasirinkdamas mažiausios kainos bendros paskirties paskyrą. Nemokamo saugojimo lygio nėra, ir mokate už tai, ką naudojate. Kainos yra gana žemos, brangiausias saugojimas kainuoja mažiau nei 0,05 USD per mėnesį už gigabaitą.

    ✅ Skaitykite apie kainas [Azure Storage Account kainų puslapyje](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Paleiskite šią komandą, kad sukurtumėte Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Pakeiskite `<location>` į vietą, kurią naudojote kurdami Resource Group ankstesnėje pamokoje.

    Pakeiskite `<storage_name>` į saugyklos paskyros pavadinimą, kurį sukūrėte ankstesniame žingsnyje.

    Pakeiskite `<functions_app_name>` į unikalų Functions App pavadinimą. Jis turi būti globaliai unikalus, nes sudaro dalį URL, naudojamo pasiekti Functions App. Naudokite kažką panašaus į `soil-moisture-sensor-` ir pridėkite unikalų identifikatorių, pvz., atsitiktinius žodžius ar savo vardą.

    `--functions-version 3` nustato Azure Functions versiją. Versija 3 yra naujausia versija.

    `--os-type Linux` nurodo Functions runtime naudoti Linux kaip OS, kurioje bus talpinamos šios funkcijos. Funkcijos gali būti talpinamos Linux arba Windows, priklausomai nuo naudojamos programavimo kalbos. Python programos palaikomos tik Linux.

### Užduotis - įkelkite savo programos nustatymus

Kurdami savo Functions App, saugojote kai kuriuos nustatymus `local.settings.json` faile, skirtame prisijungimo eilutėms prie IoT Hub. Šie nustatymai turi būti įrašyti į Application Settings jūsų Function App Azure platformoje, kad juos galėtų naudoti jūsų kodas.

> 🎓 `local.settings.json` failas skirtas tik lokaliems kūrimo nustatymams, ir jo nereikėtų įtraukti į šaltinio kodo kontrolę, pvz., GitHub. Kai įdiegiama į debesį, naudojami Application Settings. Application Settings yra raktų/reikšmių poros, talpinamos debesyje, ir jos yra skaitomos iš aplinkos kintamųjų arba jūsų kode, arba runtime, kai jūsų kodas jungiasi prie IoT Hub.

1. Paleiskite šią komandą, kad nustatytumėte `IOT_HUB_CONNECTION_STRING` nustatymą Functions App Application Settings:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Pakeiskite `<functions_app_name>` į pavadinimą, kurį naudojote savo Functions App.

    Pakeiskite `<connection string>` į `IOT_HUB_CONNECTION_STRING` reikšmę iš jūsų `local.settings.json` failo.

1. Pakartokite aukščiau esantį žingsnį, bet nustatykite `REGISTRY_MANAGER_CONNECTION_STRING` reikšmę, atitinkančią reikšmę iš jūsų `local.settings.json` failo.

Kai paleisite šias komandas, jos taip pat išves visų funkcijų programos Application Settings sąrašą. Galite naudoti tai, kad patikrintumėte, ar jūsų reikšmės nustatytos teisingai.

> 💁 Jūs pamatysite jau nustatytą reikšmę `AzureWebJobsStorage`. Jūsų `local.settings.json` faile ši reikšmė buvo nustatyta naudoti lokalią saugyklos emuliatorių. Kai sukūrėte Functions App, saugyklos paskyra buvo perduota kaip parametras, ir tai automatiškai nustatoma šioje reikšmėje.

### Užduotis - įdiekite savo Functions App į debesį

Dabar, kai Functions App yra paruošta, jūsų kodas gali būti įdiegtas.

1. Paleiskite šią komandą iš VS Code terminalo, kad publikuotumėte savo Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Pakeiskite `<functions_app_name>` į pavadinimą, kurį naudojote savo Functions App.

Kodas bus supakuotas ir išsiųstas į Functions App, kur jis bus įdiegtas ir paleistas. Bus daug konsolės išvesties, baigiantis patvirtinimu apie įdiegimą ir funkcijų sąrašu. Šiuo atveju sąraše bus tik trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Įsitikinkite, kad jūsų IoT įrenginys veikia. Keiskite drėgmės lygį, reguliuodami dirvožemio drėgmę arba perkeldami jutiklį į dirvožemį ir iš jo. Pamatysite, kaip relė įsijungia ir išsijungia, kai keičiasi dirvožemio drėgmė.

---

## 🚀 Iššūkis

Ankstesnėje pamokoje jūs valdėte relės laiką, atsisakydami MQTT pranešimų, kol relė buvo įjungta, ir trumpą laiką po to, kai ji buvo išjungta. Čia negalite naudoti šio metodo - negalite atsisakyti savo IoT Hub trigger.

Pagalvokite apie skirtingus būdus, kaip galėtumėte tai valdyti savo Functions App.

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Apžvalga ir savarankiškas mokymasis

* Skaitykite apie serverless kompiuteriją [Serverless Computing puslapyje Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Skaitykite apie serverless naudojimą Azure, įskaitant daugiau pavyzdžių [Go serverless for your IoT needs Azure tinklaraščio įraše](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Sužinokite daugiau apie Azure Functions [Azure Functions YouTube kanale](https://www.youtube.com/c/AzureFunctions)

## Užduotis

[Pridėkite rankinį relės valdymą](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.