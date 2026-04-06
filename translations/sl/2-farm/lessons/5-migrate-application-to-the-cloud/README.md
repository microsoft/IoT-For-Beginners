# Migrirajte logiko svoje aplikacije v oblak

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-9.dfe99c8e891f48e1.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta lekcija je bila del [IoT za začetnike Projekt 2 - serija Digitalno kmetijstvo](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Nadzorujte svojo IoT napravo s strežniško kodo](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Predhodni kviz

[Predhodni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Uvod

V prejšnji lekciji ste se naučili, kako povezati spremljanje vlažnosti tal vaše rastline in nadzor releja z oblačno IoT storitvijo. Naslednji korak je premik strežniške kode, ki nadzoruje časovno razporeditev releja, v oblak. V tej lekciji se boste naučili, kako to storiti z uporabo strežniških funkcij.

V tej lekciji bomo obravnavali:

* [Kaj je strežniško?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Ustvarite strežniško aplikacijo](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Ustvarite sprožilec dogodkov IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Pošiljanje zahtev za neposredne metode iz strežniške kode](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Namestite svojo strežniško kodo v oblak](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Kaj je strežniško?

Strežniško, ali strežniško računalništvo, vključuje ustvarjanje majhnih blokov kode, ki se izvajajo v oblaku kot odziv na različne vrste dogodkov. Ko se dogodek zgodi, se vaša koda zažene in prejme podatke o dogodku. Ti dogodki lahko izhajajo iz različnih virov, vključno s spletnimi zahtevami, sporočili v vrsti, spremembami podatkov v bazi podatkov ali sporočili, ki jih IoT naprave pošljejo IoT storitvi.

![Dogodki, ki se pošiljajo iz IoT storitve v strežniško storitev, vsi obdelani hkrati z več funkcijami](../../../../../translated_images/sl/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Če ste že uporabljali sprožilce v bazi podatkov, si to lahko predstavljate kot nekaj podobnega - koda, ki se sproži ob dogodku, kot je vstavljanje vrstice.

![Ko se hkrati pošlje veliko dogodkov, se strežniška storitev razširi, da jih vse obdeluje hkrati](../../../../../translated_images/sl/serverless-scaling.f8c769adf0413fd1.webp)

Vaša koda se zažene le, ko se dogodek zgodi, sicer ni aktivna. Dogodek se zgodi, vaša koda se naloži in zažene. To naredi strežniško zelo prilagodljivo - če se hkrati zgodi veliko dogodkov, lahko ponudnik oblaka zažene vašo funkcijo tolikokrat, kot je potrebno, hkrati na vseh razpoložljivih strežnikih. Slabost tega je, da če morate deliti informacije med dogodki, jih morate shraniti nekje, na primer v bazi podatkov, namesto da jih hranite v pomnilniku.

Vaša koda je napisana kot funkcija, ki sprejema podrobnosti o dogodku kot parameter. Za pisanje teh strežniških funkcij lahko uporabite širok spekter programskih jezikov.

> 🎓 Strežniško se pogosto imenuje tudi Funkcije kot storitev (FaaS), saj je vsak sprožilec dogodka implementiran kot funkcija v kodi.

Kljub imenu strežniško dejansko uporablja strežnike. Ime izhaja iz dejstva, da kot razvijalec ne skrbite za strežnike, potrebne za izvajanje vaše kode, vse kar vas zanima je, da se vaša koda zažene kot odziv na dogodek. Ponudnik oblaka ima strežniško *runtime*, ki upravlja dodeljevanje strežnikov, omrežja, shranjevanje, CPU, pomnilnik in vse ostalo, kar je potrebno za izvajanje vaše kode. Zaradi tega modela ne plačujete na strežnik, ampak za čas izvajanja vaše kode in količino uporabljenega pomnilnika.

> 💰 Strežniško je eden najcenejših načinov za izvajanje kode v oblaku. Na primer, ob času pisanja, en ponudnik oblaka omogoča, da se vse vaše strežniške funkcije skupaj izvedejo 1.000.000-krat na mesec, preden začnejo zaračunavati, nato pa zaračunajo 0,20 USD za vsakih 1.000.000 izvedb. Ko vaša koda ni aktivna, ne plačujete.

Kot IoT razvijalec je strežniški model idealen. Lahko napišete funkcijo, ki se pokliče kot odziv na sporočila, poslana iz katere koli IoT naprave, povezane z vašo oblačno IoT storitvijo. Vaša koda bo obdelala vsa poslana sporočila, vendar bo aktivna le, ko bo to potrebno.

✅ Poglejte nazaj na kodo, ki ste jo napisali kot strežniško kodo za poslušanje sporočil prek MQTT. Kako bi se to izvajalo v oblaku z uporabo strežniškega modela? Kako mislite, da bi bilo treba kodo spremeniti, da bi podpirala strežniško računalništvo?

> 💁 Strežniški model se širi tudi na druge oblačne storitve poleg izvajanja kode. Na primer, strežniške baze podatkov so na voljo v oblaku z modelom cenjenja, kjer plačujete na zahtevo, kot je poizvedba ali vstavljanje, običajno na podlagi količine dela, potrebnega za obdelavo zahteve. Na primer, enostavna poizvedba ene vrstice na primarni ključ bo stala manj kot zapletena operacija, ki združuje več tabel in vrača tisoče vrstic.

## Ustvarite strežniško aplikacijo

Strežniška računalniška storitev Microsofta se imenuje Azure Functions.

![Logotip Azure Functions](../../../../../translated_images/sl/azure-functions-logo.1cfc8e3204c9c44a.webp)

Kratek video spodaj ponuja pregled Azure Functions.

[![Pregled videa Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Kliknite na sliko zgoraj za ogled videa.

✅ Vzemite si trenutek za raziskovanje in preberite pregled Azure Functions v [dokumentaciji Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Za pisanje Azure Functions začnete z aplikacijo Azure Functions v jeziku po vaši izbiri. Azure Functions privzeto podpira Python, JavaScript, TypeScript, C#, F#, Java in Powershell. V tej lekciji se boste naučili, kako napisati aplikacijo Azure Functions v Pythonu.

> 💁 Azure Functions podpira tudi prilagojene obdelovalce, tako da lahko svoje funkcije napišete v katerem koli jeziku, ki podpira HTTP zahteve, vključno s starejšimi jeziki, kot je COBOL.

Aplikacije funkcij sestavljajo ena ali več *sprožilcev* - funkcij, ki se odzivajo na dogodke. V eni aplikaciji funkcij lahko imate več sprožilcev, ki si delijo skupne nastavitve. Na primer, v konfiguracijski datoteki vaše aplikacije funkcij lahko imate podrobnosti o povezavi z vašim IoT Hubom, in vse funkcije v aplikaciji lahko to uporabijo za povezavo in poslušanje dogodkov.

### Naloga - namestite orodja za Azure Functions

> Ob času pisanja orodja za Azure Functions niso popolnoma združljiva z Apple Silicon za Python projekte. Namesto tega boste morali uporabiti Mac z Intel procesorjem, Windows PC ali Linux PC.

Ena odlična funkcija Azure Functions je, da jih lahko izvajate lokalno. Enak runtime, ki se uporablja v oblaku, lahko zaženete na svojem računalniku, kar vam omogoča pisanje kode, ki se odziva na IoT sporočila, in njeno lokalno izvajanje. Lahko celo odpravljate napake v svoji kodi med obdelavo dogodkov. Ko ste zadovoljni s svojo kodo, jo lahko namestite v oblak.

Orodje za Azure Functions je na voljo kot CLI, znano kot Azure Functions Core Tools.

1. Namestite Azure Functions Core Tools tako, da sledite navodilom v [dokumentaciji Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Namestite razširitev Azure Functions za VS Code. Ta razširitev omogoča podporo za ustvarjanje, odpravljanje napak in nameščanje Azure funkcij. Oglejte si [dokumentacijo razširitve Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) za navodila o namestitvi te razširitve v VS Code.

Ko namestite svojo aplikacijo Azure Functions v oblak, potrebuje majhno količino oblačnega prostora za shranjevanje stvari, kot so datoteke aplikacije in dnevniške datoteke. Ko svojo aplikacijo funkcij izvajate lokalno, se morate še vedno povezati z oblačnim prostorom za shranjevanje, vendar namesto dejanskega oblačnega prostora za shranjevanje lahko uporabite emulator za shranjevanje, imenovan [Azurite](https://github.com/Azure/Azurite). Ta se izvaja lokalno, vendar deluje kot oblačno shranjevanje.

> 🎓 V Azure je prostor za shranjevanje, ki ga Azure Functions uporablja, Azure Storage Account. Ti računi lahko shranjujejo datoteke, bloke, podatke v tabelah ali podatke v vrstah. En račun za shranjevanje lahko delite med več aplikacijami, kot so aplikacija funkcij in spletna aplikacija.

1. Azurite je aplikacija Node.js, zato boste morali namestiti Node.js. Prenos in navodila za namestitev najdete na [spletni strani Node.js](https://nodejs.org/). Če uporabljate Mac, ga lahko namestite tudi prek [Homebrew](https://formulae.brew.sh/formula/node).

1. Namestite Azurite z naslednjim ukazom (`npm` je orodje, ki se namesti ob namestitvi Node.js):

    ```sh
    npm install -g azurite
    ```

1. Ustvarite mapo z imenom `azurite` za uporabo Azurite za shranjevanje podatkov:

    ```sh
    mkdir azurite
    ```

1. Zaženite Azurite in mu posredujte to novo mapo:

    ```sh
    azurite --location azurite
    ```

    Emulator za shranjevanje Azurite se bo zagnal in bo pripravljen za povezavo z lokalnim runtime-om funkcij.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Naloga - ustvarite projekt Azure Functions

CLI za Azure Functions se lahko uporablja za ustvarjanje nove aplikacije funkcij.

1. Ustvarite mapo za svojo aplikacijo funkcij in se premaknite vanjo. Poimenujte jo `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Ustvarite virtualno okolje Python znotraj te mape:

    ```sh
    python3 -m venv .venv
    ```

1. Aktivirajte virtualno okolje:

    * Na Windows:
        * Če uporabljate Command Prompt ali Command Prompt prek Windows Terminal, zaženite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Če uporabljate PowerShell, zaženite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Na macOS ali Linux, zaženite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Te ukaze je treba zagnati iz iste lokacije, kjer ste zagnali ukaz za ustvarjanje virtualnega okolja. Nikoli vam ne bo treba navigirati v mapo `.venv`, vedno morate zagnati ukaz za aktivacijo in vse ukaze za namestitev paketov ali izvajanje kode iz mape, kjer ste ustvarili virtualno okolje.

1. Zaženite naslednji ukaz za ustvarjanje aplikacije funkcij v tej mapi:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    To bo ustvarilo tri datoteke znotraj trenutne mape:

    * `host.json` - ta JSON dokument vsebuje nastavitve za vašo aplikacijo funkcij. Teh nastavitev ne boste potrebovali spreminjati.
    * `local.settings.json` - ta JSON dokument vsebuje nastavitve, ki jih vaša aplikacija uporablja pri lokalnem izvajanju, kot so povezovalni nizi za vaš IoT Hub. Te nastavitve so samo lokalne in jih ne bi smeli dodati v nadzor izvorne kode. Ko aplikacijo namestite v oblak, te nastavitve niso nameščene, namesto tega se vaše nastavitve naložijo iz nastavitev aplikacije. To bo obravnavano kasneje v tej lekciji.
    * `requirements.txt` - to je [Pip datoteka zahtev](https://pip.pypa.io/en/stable/user_guide/#requirements-files), ki vsebuje Pip pakete, potrebne za izvajanje vaše aplikacije funkcij.

1. Datoteka `local.settings.json` ima nastavitev za račun za shranjevanje, ki ga aplikacija funkcij uporablja. Privzeto je ta nastavitev prazna, zato jo je treba nastaviti. Za povezavo z lokalnim emulatorjem za shranjevanje Azurite nastavite to vrednost na naslednje:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Namestite potrebne Pip pakete z uporabo datoteke zahtev:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Potrebni Pip paketi morajo biti v tej datoteki, tako da lahko runtime aplikacije funkcij ob namestitvi v oblak zagotovi, da namesti pravilne pakete.

1. Za testiranje, ali vse deluje pravilno, lahko zaženete runtime funkcij. Zaženite naslednji ukaz za to:

    ```sh
    func start
    ```

    Videli boste, da se runtime zažene in poroča, da ni našel nobenih funkcij (sprožilcev).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Če prejmete obvestilo požarnega zidu, odobrite dostop, saj mora aplikacija `func` imeti možnost branja in pisanja v vašem omrežju.
> ⚠️ Če uporabljate macOS, se lahko v izhodu pojavijo opozorila:
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
> Ta opozorila lahko prezrete, dokler se aplikacija Functions pravilno zažene in prikaže delujoče funkcije. Kot je omenjeno v [tem vprašanju na Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), jih lahko ignorirate.

1. Ustavite aplikacijo Functions s pritiskom na `ctrl+c`.

1. Odprite trenutno mapo v VS Code, bodisi tako, da odprete VS Code in nato to mapo, bodisi z zagonom naslednjega ukaza:

    ```sh
    code .
    ```

    VS Code bo zaznal vaš projekt Functions in prikazal obvestilo:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Obvestilo](../../../../../translated_images/sl/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Izberite **Yes** v tem obvestilu.

1. Prepričajte se, da je Python virtualno okolje zagnano v terminalu VS Code. Po potrebi ga ustavite in ponovno zaženite.

## Ustvarite sprožilec dogodkov za IoT Hub

Aplikacija Functions je osnova za vašo strežniško kodo. Za odzivanje na dogodke IoT Hub lahko tej aplikaciji dodate sprožilec IoT Hub. Ta sprožilec se mora povezati s tokom sporočil, ki so poslana v IoT Hub, in se nanje odzvati. Da bi pridobili ta tok sporočil, se mora vaš sprožilec povezati z *dogodkovno združljivim končnim točkam* IoT Hub.

IoT Hub temelji na drugi Azure storitvi, imenovani Azure Event Hubs. Event Hubs omogoča pošiljanje in prejemanje sporočil, IoT Hub pa to razširja z dodatnimi funkcijami za IoT naprave. Način povezovanja za branje sporočil iz IoT Hub je enak kot pri uporabi Event Hubs.

✅ Raziskujte: Preberite pregled Event Hubs v [dokumentaciji Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Kako se osnovne funkcije primerjajo z IoT Hub?

Da se IoT naprava poveže z IoT Hub, mora uporabiti skrivni ključ, ki zagotavlja, da se lahko povežejo samo dovoljene naprave. Enako velja za povezovanje za branje sporočil – vaša koda bo potrebovala povezovalni niz, ki vsebuje skrivni ključ in podrobnosti o IoT Hub.

> 💁 Privzeti povezovalni niz, ki ga dobite, ima dovoljenja **iothubowner**, kar omogoča polna dovoljenja za IoT Hub katerikoli kodi, ki ga uporablja. Idealno bi bilo, da se povežete z najnižjo stopnjo potrebnih dovoljenj. To bo obravnavano v naslednji lekciji.

Ko se vaš sprožilec poveže, se bo koda znotraj funkcije klicala za vsako sporočilo, poslano v IoT Hub, ne glede na to, katera naprava ga je poslala. Sprožilec bo sporočilo prejel kot parameter.

### Naloga - pridobite povezovalni niz dogodkovno združljivega končnega točke

1. V terminalu VS Code zaženite naslednji ukaz za pridobitev povezovalnega niza za dogodkovno združljivi končni točki IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Zamenjajte `<hub_name>` z imenom, ki ste ga uporabili za vaš IoT Hub.

1. V VS Code odprite datoteko `local.settings.json`. Dodajte naslednjo vrednost v razdelek `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Zamenjajte `<connection string>` z vrednostjo iz prejšnjega koraka. Za veljaven JSON boste morali dodati vejico za prejšnjo vrstico.

### Naloga - ustvarite sprožilec dogodka

Zdaj ste pripravljeni ustvariti sprožilec dogodka.

1. V terminalu VS Code zaženite naslednji ukaz znotraj mape `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    To ustvari novo funkcijo z imenom `iot-hub-trigger`. Sprožilec se bo povezal z dogodkovno združljivim končnim točkom na IoT Hub, zato lahko uporabite sprožilec dogodkovnega vozlišča. Specifičnega sprožilca za IoT Hub ni.

To bo ustvarilo mapo znotraj mape `soil-moisture-trigger`, imenovano `iot-hub-trigger`, ki vsebuje to funkcijo. Ta mapa bo vsebovala naslednje datoteke:

* `__init__.py` - to je Python datoteka s kodo, ki vsebuje sprožilec, z uporabo standardne Python konvencije za imena datotek, da se mapa spremeni v Python modul.

    Ta datoteka bo vsebovala naslednjo kodo:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Jedro sprožilca je funkcija `main`. Ta funkcija se kliče z dogodki iz IoT Hub. Funkcija ima parameter `event`, ki vsebuje `EventHubEvent`. Vsakič, ko je sporočilo poslano v IoT Hub, se ta funkcija pokliče in prejme to sporočilo kot `event`, skupaj z lastnostmi, ki so enake opombam, ki ste jih videli v prejšnji lekciji.

    Jedro te funkcije beleži dogodek.

* `function.json` - ta datoteka vsebuje konfiguracijo za sprožilec. Glavna konfiguracija je v razdelku `bindings`. Binding je izraz za povezavo med Azure Functions in drugimi Azure storitvami. Ta funkcija ima vhodni binding za dogodkovno vozlišče – povezuje se z dogodkovnim vozliščem in prejema podatke.

    > 💁 Lahko imate tudi izhodne bindinge, tako da se izhod funkcije pošlje drugi storitvi. Na primer, lahko dodate izhodni binding za bazo podatkov in vrnete dogodek IoT Hub iz funkcije, ki se bo samodejno vstavil v bazo podatkov.

    ✅ Raziskujte: Preberite več o bindingih v [dokumentaciji o sprožilcih in bindingih Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Razdelek `bindings` vključuje konfiguracijo za binding. Zanimive vrednosti so:

  * `"type": "eventHubTrigger"` - to pove funkciji, da mora poslušati dogodke iz dogodkovnega vozlišča
  * `"name": "events"` - to je ime parametra za dogodke iz dogodkovnega vozlišča. To se ujema z imenom parametra v funkciji `main` v Python kodi.
  * `"direction": "in"` - to je vhodni binding, podatki iz dogodkovnega vozlišča prihajajo v funkcijo
  * `"connection": ""` - to določa ime nastavitve, iz katere se prebere povezovalni niz. Pri lokalnem zagonu se ta nastavitev prebere iz datoteke `local.settings.json`.

    > 💁 Povezovalni niz ne more biti shranjen v datoteki `function.json`, ampak mora biti prebran iz nastavitev. To preprečuje nenamerno razkritje vašega povezovalnega niza.

1. Zaradi [napake v predlogi Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250) ima `function.json` napačno vrednost za polje `cardinality`. Posodobite to polje iz `many` v `one`:

    ```json
    "cardinality": "one",
    ```

1. Posodobite vrednost `"connection"` v datoteki `function.json`, da kaže na novo vrednost, ki ste jo dodali v datoteko `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Ne pozabite – to mora kazati na nastavitev, ne vsebovati dejanskega povezovalnega niza.

1. Povezovalni niz vsebuje vrednost `eventHubName`, zato mora biti vrednost za to v datoteki `function.json` izpraznjena. Posodobite to vrednost na prazen niz:

    ```json
    "eventHubName": "",
    ```

### Naloga - zaženite sprožilec dogodka

1. Prepričajte se, da ne izvajate monitorja dogodkov IoT Hub. Če ta deluje hkrati z aplikacijo Functions, se aplikacija Functions ne bo mogla povezati in porabiti dogodkov.

    > 💁 Več aplikacij se lahko poveže z IoT Hub končnimi točkami z uporabo različnih *potrošniških skupin*. Te bodo obravnavane v kasnejši lekciji.

1. Za zagon aplikacije Functions zaženite naslednji ukaz iz terminala VS Code:

    ```sh
    func start
    ```

    Aplikacija Functions se bo zagnala in odkrila funkcijo `iot-hub-trigger`. Nato bo obdelala vse dogodke, ki so bili poslani v IoT Hub v zadnjem dnevu.

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

    Vsak klic funkcije bo obdan z blokom `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` v izhodu, tako da lahko vidite, koliko sporočil je bilo obdelanih v vsakem klicu funkcije.

1. Prepričajte se, da vaša IoT naprava deluje. Videli boste nova sporočila o vlažnosti tal, ki se pojavljajo v aplikaciji Functions.

1. Ustavite in ponovno zaženite aplikacijo Functions. Videli boste, da ne bo ponovno obdelala prejšnjih sporočil, ampak le nova sporočila.

> 💁 VS Code podpira tudi odpravljanje napak v vaših funkcijah. Prelomne točke lahko nastavite s klikom na rob na začetku vsake vrstice kode, ali tako, da postavite kazalec na vrstico kode in izberete *Run -> Toggle breakpoint*, ali pritisnete `F9`. Debugger lahko zaženete z izbiro *Run -> Start debugging*, pritiskom na `F5`, ali z izbiro zavihka *Run and debug* in klikom na gumb **Start debugging**. Tako lahko vidite podrobnosti o dogodkih, ki se obdelujejo.

#### Odpravljanje težav

* Če prejmete naslednjo napako:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Preverite, ali Azurite deluje in ali ste nastavili `AzureWebJobsStorage` v datoteki `local.settings.json` na `UseDevelopmentStorage=true`.

* Če prejmete naslednjo napako:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Preverite, ali ste nastavili `cardinality` v datoteki `function.json` na `one`.

* Če prejmete naslednjo napako:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Preverite, ali ste nastavili `eventHubName` v datoteki `function.json` na prazen niz.

## Pošiljanje zahtev za neposredne metode iz strežniške kode

Do zdaj vaša aplikacija Functions posluša sporočila iz IoT Hub z uporabo dogodkovno združljivega končnega točke. Zdaj morate poslati ukaze IoT napravi. To se izvede z uporabo drugačne povezave z IoT Hub prek *Registry Manager*. Registry Manager je orodje, ki vam omogoča ogled registriranih naprav v IoT Hub in komunikacijo z njimi s pošiljanjem sporočil iz oblaka v napravo, zahtev za neposredne metode ali posodabljanjem dvojčkov naprav. Prav tako ga lahko uporabite za registracijo, posodabljanje ali brisanje IoT naprav iz IoT Hub.

Za povezavo z Registry Manager potrebujete povezovalni niz.

### Naloga - pridobite povezovalni niz za Registry Manager

1. Za pridobitev povezovalnega niza zaženite naslednji ukaz:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Zamenjajte `<hub_name>` z imenom, ki ste ga uporabili za vaš IoT Hub.

    Povezovalni niz je zahtevan za politiko *ServiceConnect* z uporabo parametra `--policy-name service`. Ko zahtevate povezovalni niz, lahko določite, katera dovoljenja bo ta povezovalni niz omogočal. Politika ServiceConnect omogoča vaši kodi povezovanje in pošiljanje sporočil IoT napravam.

    ✅ Raziskujte: Preberite več o različnih politikah v [dokumentaciji o dovoljenjih IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. V VS Code odprite datoteko `local.settings.json`. Dodajte naslednjo vrednost v razdelek `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Zamenjajte `<connection string>` z vrednostjo iz prejšnjega koraka. Za veljaven JSON boste morali dodati vejico za prejšnjo vrstico.

### Naloga - pošljite zahtevo za neposredno metodo napravi

1. SDK za Registry Manager je na voljo prek Pip paketa. Dodajte naslednjo vrstico v datoteko `requirements.txt`, da dodate odvisnost od tega paketa:

    ```sh
    azure-iot-hub
    ```

1. Prepričajte se, da je terminal VS Code aktiviral virtualno okolje, in zaženite naslednji ukaz za namestitev Pip paketov:

    ```sh
    pip install -r requirements.txt
    ```

1. Dodajte naslednje uvoze v datoteko `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    To uvozi nekaj sistemskih knjižnic, kot tudi knjižnice za interakcijo z Registry Manager in pošiljanje zahtev za neposredne metode.

1. Odstranite kodo iz funkcije `main`, vendar obdržite samo funkcijo.

1. V funkciji `main` dodajte naslednjo kodo:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Ta koda izvleče telo dogodka, ki vsebuje JSON sporočilo, poslano z IoT naprave.

    Nato pridobi ID naprave iz opomb, poslanih s sporočilom. Telo dogodka vsebuje sporočilo, poslano kot telemetrija, slovar `iothub_metadata` pa vsebuje lastnosti, ki jih nastavi IoT Hub, kot so ID naprave pošiljatelja in čas, ko je bilo sporočilo poslano.

    Te informacije se nato zabeležijo. To beleženje boste videli v terminalu, ko lokalno zaženete aplikacijo Functions.

1. Pod to kodo dodajte naslednjo kodo:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Ta koda pridobi vlažnost tal iz sporočila. Nato preveri vlažnost tal in glede na vrednost ustvari pomožni razred za zahtevo neposredne metode za `relay_on` ali `relay_off`. Zahteva za metodo ne potrebuje vsebine, zato se pošlje prazen JSON dokument.

1. Pod to kodo dodajte naslednjo kodo:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Ta koda naloži `REGISTRY_MANAGER_CONNECTION_STRING` iz datoteke `local.settings.json`. Vrednosti v tej datoteki so na voljo kot okoljske spremenljivke, ki jih lahko preberete z uporabo funkcije `os.environ`, funkcije, ki vrne slovar vseh okoljskih spremenljivk.

> 💁 Ko je ta koda nameščena v oblaku, bodo vrednosti v datoteki `local.settings.json` nastavljene kot *Application Settings*, ki jih je mogoče prebrati iz okoljskih spremenljivk.

Koda nato ustvari instanco pomožnega razreda Registry Manager z uporabo povezovalnega niza.

1. Pod to dodajte naslednjo kodo:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Ta koda Registry Managerju pove, naj pošlje zahtevo za neposredno metodo napravi, ki je poslala telemetrijo.

    > 💁 V različicah aplikacije, ki ste jih ustvarili v prejšnjih lekcijah z uporabo MQTT, so bili ukazi za nadzor releja poslani vsem napravam. Koda je predvidevala, da imate samo eno napravo. Ta različica kode pošlje zahtevo za metodo eni napravi, zato bi delovala, če bi imeli več nastavitev senzorjev vlage in relejev, pri čemer bi poslala pravo zahtevo za neposredno metodo pravi napravi.

1. Zaženite aplikacijo Functions in se prepričajte, da vaša IoT naprava pošilja podatke. Videli boste, kako se sporočila obdelujejo in zahteve za neposredne metode pošiljajo. Premikajte senzor vlage v in iz zemlje, da vidite, kako se vrednosti spreminjajo in rele vklaplja ter izklaplja.

> 💁 To kodo lahko najdete v mapi [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Namestite svojo strežniško kodo v oblak

Vaša koda zdaj deluje lokalno, naslednji korak pa je namestitev aplikacije Functions v oblak.

### Naloga - ustvarite oblačne vire

Vaša aplikacija Functions mora biti nameščena v viru Functions App v Azure, ki se nahaja znotraj Resource Group, ki ste jo ustvarili za vaš IoT Hub. Prav tako boste morali ustvariti Storage Account v Azure, da zamenjate emulirani račun, ki ga imate lokalno.

1. Zaženite naslednji ukaz za ustvarjanje Storage Account:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Zamenjajte `<storage_name>` z imenom za vaš Storage Account. To ime mora biti globalno unikatno, saj je del URL-ja, ki se uporablja za dostop do Storage Account. Uporabite lahko samo male črke in številke, brez drugih znakov, omejeno na 24 znakov. Uporabite nekaj, kot je `sms`, in dodajte unikatni identifikator na koncu, na primer naključne besede ali vaše ime.

    Možnost `--sku Standard_LRS` izbere cenovni razred, ki izbere najcenejši splošni račun. Brezplačnega razreda za shranjevanje ni, plačate pa za to, kar uporabljate. Stroški so relativno nizki, najdražje shranjevanje pa stane manj kot 0,05 USD na mesec na gigabajt shranjenega podatka.

    ✅ Preberite več o cenah na [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Zaženite naslednji ukaz za ustvarjanje Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju Resource Group v prejšnji lekciji.

    Zamenjajte `<storage_name>` z imenom Storage Account, ki ste ga ustvarili v prejšnjem koraku.

    Zamenjajte `<functions_app_name>` z unikatnim imenom za vaš Functions App. To ime mora biti globalno unikatno, saj je del URL-ja, ki se uporablja za dostop do Functions App. Uporabite nekaj, kot je `soil-moisture-sensor-`, in dodajte unikatni identifikator na koncu, na primer naključne besede ali vaše ime.

    Možnost `--functions-version 3` nastavi različico Azure Functions, ki jo želite uporabiti. Različica 3 je najnovejša različica.

    Možnost `--os-type Linux` pove funkcijskemu okolju, naj za gostovanje teh funkcij uporabi Linux kot operacijski sistem. Funkcije lahko gostujejo na Linuxu ali Windowsu, odvisno od uporabljenega programskega jezika. Python aplikacije so podprte samo na Linuxu.

### Naloga - naložite nastavitve aplikacije

Ko ste razvijali svojo aplikacijo Functions, ste shranili nekaj nastavitev v datoteko `local.settings.json` za povezovalne nize za vaš IoT Hub. Te je treba zapisati v Application Settings v vašem Function App v Azure, da jih lahko uporablja vaša koda.

> 🎓 Datoteka `local.settings.json` je namenjena samo lokalnim nastavitvam razvoja in je ne bi smeli vključiti v nadzor izvorne kode, kot je GitHub. Ko je nameščena v oblaku, se uporabljajo Application Settings. Application Settings so pari ključ/vrednost, gostovani v oblaku, ki se berejo iz okoljskih spremenljivk bodisi v vaši kodi bodisi s strani okolja ob povezovanju vaše kode z IoT Hub.

1. Zaženite naslednji ukaz za nastavitev nastavitve `IOT_HUB_CONNECTION_STRING` v Application Settings za Functions App:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Zamenjajte `<functions_app_name>` z imenom, ki ste ga uporabili za vaš Functions App.

    Zamenjajte `<connection string>` z vrednostjo `IOT_HUB_CONNECTION_STRING` iz vaše datoteke `local.settings.json`.

1. Ponovite zgornji korak, vendar nastavite vrednost `REGISTRY_MANAGER_CONNECTION_STRING` na ustrezno vrednost iz vaše datoteke `local.settings.json`.

Ko zaženete te ukaze, bodo prav tako prikazali seznam vseh Application Settings za funkcijsko aplikacijo. To lahko uporabite za preverjanje, ali so vaše vrednosti pravilno nastavljene.

> 💁 Videli boste vrednost, ki je že nastavljena za `AzureWebJobsStorage`. V vaši datoteki `local.settings.json` je bila ta nastavljena na vrednost za uporabo lokalnega emuliranega shranjevanja. Ko ste ustvarili Functions App, ste kot parameter podali Storage Account, in ta se samodejno nastavi v tej nastavitvi.

### Naloga - namestite svojo aplikacijo Functions v oblak

Zdaj, ko je Functions App pripravljena, lahko vašo kodo namestite.

1. Zaženite naslednji ukaz iz terminala v VS Code za objavo vaše aplikacije Functions:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Zamenjajte `<functions_app_name>` z imenom, ki ste ga uporabili za vaš Functions App.

Koda bo zapakirana in poslana v Functions App, kjer bo nameščena in zagnana. Prikazalo se bo veliko izhodnih podatkov v konzoli, ki se končajo s potrditvijo namestitve in seznamom nameščenih funkcij. V tem primeru bo seznam vseboval samo sprožilec.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Prepričajte se, da vaša IoT naprava deluje. Spreminjajte nivoje vlage z nastavljanjem vlage v zemlji ali premikanjem senzorja v in iz zemlje. Videli boste, kako se rele vklaplja in izklaplja, ko se vlaga spreminja.

---

## 🚀 Izziv

V prejšnji lekciji ste upravljali čas releja z odjavo od MQTT sporočil, medtem ko je bil rele vklopljen, in za kratek čas po tem, ko je bil izklopljen. Tega načina tukaj ne morete uporabiti - ne morete odjaviti svojega IoT Hub sprožilca.

Razmislite o različnih načinih, kako bi to lahko obravnavali v svoji aplikaciji Functions.

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Pregled in samostojno učenje

* Preberite več o strežniškem računalništvu na [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Preberite o uporabi strežniškega računalništva v Azure, vključno z nekaterimi dodatnimi primeri, na [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Naučite se več o Azure Functions na [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions)

## Naloga

[Dodajte ročni nadzor releja](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.