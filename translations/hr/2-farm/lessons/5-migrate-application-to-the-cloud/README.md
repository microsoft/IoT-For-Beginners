<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-28T14:45:57+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "hr"
}
-->
# Premjestite logiku svoje aplikacije u oblak

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ova lekcija je dio serije [IoT za početnike Projekt 2 - Digitalna poljoprivreda](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Upravljajte svojim IoT uređajem pomoću serverless koda](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Uvod

U prethodnoj lekciji naučili ste kako povezati praćenje vlažnosti tla i upravljanje relejem s IoT uslugom u oblaku. Sljedeći korak je premještanje serverskog koda koji kontrolira vrijeme releja u oblak. U ovoj lekciji naučit ćete kako to učiniti koristeći serverless funkcije.

U ovoj lekciji obradit ćemo:

* [Što je serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Kreiranje serverless aplikacije](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Kreiranje okidača za IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Slanje zahtjeva za direktne metode iz serverless koda](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Implementacija vašeg serverless koda u oblak](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Što je serverless?

Serverless, ili serverless računarstvo, uključuje kreiranje malih blokova koda koji se izvršavaju u oblaku kao odgovor na različite vrste događaja. Kada se dogodi događaj, vaš kod se pokreće i dobiva podatke o tom događaju. Ti događaji mogu dolaziti iz različitih izvora, uključujući web zahtjeve, poruke stavljene u red, promjene podataka u bazi podataka ili poruke koje IoT uređaji šalju IoT usluzi.

![Događaji koji se šalju iz IoT usluge u serverless uslugu, svi se obrađuju istovremeno pomoću više funkcija koje se pokreću](../../../../../translated_images/hr/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 Ako ste prije koristili okidače u bazama podataka, ovo možete zamisliti kao sličan koncept - kod koji se pokreće događajem, poput umetanja retka.

![Kada se više događaja pošalje istovremeno, serverless usluga se skalira kako bi ih sve obradila u isto vrijeme](../../../../../translated_images/hr/serverless-scaling.f8c769adf0413fd1.webp)

Vaš kod se pokreće samo kada se dogodi događaj, a u drugim trenucima nije aktivan. Događaj se dogodi, vaš kod se učita i izvrši. Ovo čini serverless vrlo skalabilnim - ako se mnogo događaja dogodi istovremeno, pružatelj oblaka može pokrenuti vašu funkciju onoliko puta koliko je potrebno, koristeći dostupne resurse. Nedostatak ovog pristupa je što, ako trebate dijeliti informacije između događaja, morate ih pohraniti negdje, poput baze podataka, umjesto da ih držite u memoriji.

Vaš kod je napisan kao funkcija koja prima detalje o događaju kao parametar. Možete koristiti širok raspon programskih jezika za pisanje ovih serverless funkcija.

> 🎓 Serverless se također naziva Functions as a Service (FaaS), jer se svaki okidač događaja implementira kao funkcija u kodu.

Unatoč nazivu, serverless zapravo koristi servere. Naziv dolazi od toga što se kao programer ne morate brinuti o serverima potrebnima za pokretanje vašeg koda, već samo o tome da se vaš kod izvršava kao odgovor na događaj. Pružatelj oblaka ima serverless *runtime* koji upravlja dodjelom servera, mrežom, pohranom, CPU-om, memorijom i svim ostalim potrebnim za pokretanje vašeg koda. Ovaj model znači da ne plaćate po serveru, već za vrijeme kada vaš kod radi i količinu korištene memorije.

> 💰 Serverless je jedan od najjeftinijih načina za pokretanje koda u oblaku. Na primjer, u trenutku pisanja, jedan pružatelj oblaka omogućuje svim vašim serverless funkcijama da se izvrše ukupno 1.000.000 puta mjesečno prije nego što počnu naplaćivati, a nakon toga naplaćuju 0,20 USD za svakih 1.000.000 izvršenja. Kada vaš kod ne radi, ne plaćate.

Kao IoT programer, serverless model je idealan. Možete napisati funkciju koja se poziva kao odgovor na poruke poslane s bilo kojeg IoT uređaja povezanog s vašom IoT uslugom u oblaku. Vaš kod će obraditi sve poslane poruke, ali će raditi samo kada je to potrebno.

✅ Pogledajte kod koji ste napisali kao serverski kod za slušanje poruka putem MQTT-a. Kako bi se ovo moglo pokrenuti u oblaku koristeći serverless? Kako mislite da bi se kod mogao promijeniti kako bi podržao serverless računarstvo?

> 💁 Serverless model se širi i na druge usluge u oblaku, osim pokretanja koda. Na primjer, serverless baze podataka dostupne su u oblaku koristeći serverless model naplate, gdje plaćate po zahtjevu prema bazi podataka, poput upita ili umetanja, obično na temelju količine posla potrebnog za obradu zahtjeva. Na primjer, jednostavan odabir jednog retka prema primarnom ključu koštat će manje od složene operacije koja spaja više tablica i vraća tisuće redaka.

## Kreiranje serverless aplikacije

Microsoftova usluga za serverless računarstvo zove se Azure Functions.

![Logo Azure Functions](../../../../../translated_images/hr/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

Kratki video ispod daje pregled Azure Functions.

[![Pregled Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Kliknite na sliku iznad za gledanje videa.

✅ Odvojite trenutak za istraživanje i pročitajte pregled Azure Functions u [Microsoft Azure Functions dokumentaciji](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Za pisanje Azure Functions, započinjete s aplikacijom Azure Functions na jeziku po vašem izboru. Azure Functions podržava Python, JavaScript, TypeScript, C#, F#, Java i Powershell. U ovoj lekciji naučit ćete kako napisati Azure Functions aplikaciju u Pythonu.

> 💁 Azure Functions također podržava prilagođene rukovatelje, tako da možete pisati funkcije na bilo kojem jeziku koji podržava HTTP zahtjeve, uključujući starije jezike poput COBOL-a.

Aplikacije funkcija sastoje se od jednog ili više *okidača* - funkcija koje reagiraju na događaje. Možete imati više okidača unutar jedne aplikacije funkcija, koje dijele zajedničku konfiguraciju. Na primjer, u konfiguracijskoj datoteci za vašu aplikaciju funkcija možete imati detalje o povezivanju s vašim IoT Hubom, a sve funkcije u aplikaciji mogu koristiti te postavke za povezivanje i slušanje događaja.

### Zadatak - instalacija alata za Azure Functions

> U trenutku pisanja, alati za Azure Functions nisu u potpunosti funkcionalni na Apple Silicon računalima za Python projekte. Trebat ćete koristiti Mac s Intel procesorom, Windows PC ili Linux PC.

Jedna od sjajnih značajki Azure Functions je mogućnost lokalnog pokretanja. Isti runtime koji se koristi u oblaku može se pokrenuti na vašem računalu, omogućujući vam pisanje koda koji reagira na IoT poruke i njegovo lokalno testiranje. Možete čak i otklanjati pogreške dok se događaji obrađuju. Kada ste zadovoljni svojim kodom, možete ga implementirati u oblak.

Alati za Azure Functions dostupni su kao CLI, poznat kao Azure Functions Core Tools.

1. Instalirajte Azure Functions Core Tools slijedeći upute u [Azure Functions Core Tools dokumentaciji](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Instalirajte Azure Functions ekstenziju za VS Code. Ova ekstenzija pruža podršku za kreiranje, otklanjanje pogrešaka i implementaciju Azure funkcija. Pogledajte [dokumentaciju za Azure Functions ekstenziju](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) za upute o instalaciji ove ekstenzije u VS Code.

Kada implementirate svoju Azure Functions aplikaciju u oblak, ona treba koristiti malu količinu pohrane u oblaku za spremanje aplikacijskih datoteka i logova. Kada pokrećete aplikaciju lokalno, i dalje trebate povezivanje s pohranom u oblaku, ali umjesto stvarne pohrane u oblaku, možete koristiti emulator pohrane nazvan [Azurite](https://github.com/Azure/Azurite). Ovo radi lokalno, ali se ponaša kao pohrana u oblaku.

> 🎓 U Azureu, pohrana koju Azure Functions koristi je Azure Storage Account. Ovi računi mogu pohranjivati datoteke, blobove, podatke u tablicama ili podatke u redovima. Jedan račun za pohranu možete dijeliti između više aplikacija, poput aplikacije funkcija i web aplikacije.

1. Azurite je Node.js aplikacija, pa ćete trebati instalirati Node.js. Možete pronaći upute za preuzimanje i instalaciju na [Node.js web stranici](https://nodejs.org/). Ako koristite Mac, možete ga instalirati i putem [Homebrew](https://formulae.brew.sh/formula/node).

1. Instalirajte Azurite koristeći sljedeću naredbu (`npm` je alat koji se instalira zajedno s Node.js):

    ```sh
    npm install -g azurite
    ```

1. Kreirajte mapu nazvanu `azurite` za Azurite kako bi koristio za pohranu podataka:

    ```sh
    mkdir azurite
    ```

1. Pokrenite Azurite, prosljeđujući mu ovu novu mapu:

    ```sh
    azurite --location azurite
    ```

    Emulator pohrane Azurite će se pokrenuti i biti spreman za povezivanje s lokalnim runtimeom funkcija.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Zadatak - kreiranje Azure Functions projekta

CLI za Azure Functions može se koristiti za kreiranje nove aplikacije funkcija.

1. Kreirajte mapu za svoju aplikaciju funkcija i navigirajte u nju. Nazovite je `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Kreirajte Python virtualno okruženje unutar ove mape:

    ```sh
    python3 -m venv .venv
    ```

1. Aktivirajte virtualno okruženje:

    * Na Windowsu:
        * Ako koristite Command Prompt ili Command Prompt kroz Windows Terminal, pokrenite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ako koristite PowerShell, pokrenite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Na macOS-u ili Linuxu, pokrenite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ove naredbe trebaju se pokrenuti iz iste lokacije gdje ste kreirali virtualno okruženje. Nikada ne trebate navigirati u `.venv` mapu, uvijek biste trebali pokretati naredbu za aktivaciju i bilo koje naredbe za instalaciju paketa ili pokretanje koda iz mape u kojoj ste kreirali virtualno okruženje.

1. Pokrenite sljedeću naredbu za kreiranje aplikacije funkcija u ovoj mapi:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Ovo će kreirati tri datoteke unutar trenutne mape:

    * `host.json` - ovaj JSON dokument sadrži postavke za vašu aplikaciju funkcija. Nećete trebati mijenjati ove postavke.
    * `local.settings.json` - ovaj JSON dokument sadrži postavke koje vaša aplikacija koristi prilikom lokalnog pokretanja, poput stringova za povezivanje s vašim IoT Hubom. Ove postavke su samo lokalne i ne bi trebale biti dodane u kontrolu izvornog koda. Kada implementirate aplikaciju u oblak, ove postavke se ne implementiraju, već se učitavaju iz postavki aplikacije. Ovo će biti objašnjeno kasnije u lekciji.
    * `requirements.txt` - ovo je [Pip datoteka zahtjeva](https://pip.pypa.io/en/stable/user_guide/#requirements-files) koja sadrži Pip pakete potrebne za pokretanje vaše aplikacije funkcija.

1. Datoteka `local.settings.json` ima postavku za račun pohrane koji aplikacija funkcija koristi. Ovo je zadano prazno, pa treba postaviti. Za povezivanje s lokalnim emulatorom pohrane Azurite, postavite ovu vrijednost na sljedeće:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Instalirajte potrebne Pip pakete koristeći datoteku zahtjeva:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Potrebni Pip paketi moraju biti u ovoj datoteci, kako bi runtime mogao osigurati instalaciju ispravnih paketa prilikom implementacije aplikacije funkcija u oblak.

1. Da biste testirali radi li sve ispravno, možete pokrenuti runtime funkcija. Pokrenite sljedeću naredbu za to:

    ```sh
    func start
    ```

    Vidjet ćete kako se runtime pokreće i izvještava da nije pronašao nijednu funkciju zadatka (okidač).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Ako primite obavijest o vatrozidu, odobrite pristup jer aplikacija `func` mora imati mogućnost čitanja i pisanja na vašu mrežu.
> ⚠️ Ako koristite macOS, moguće je da će se pojaviti upozorenja u izlazu:
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
> Možete ih zanemariti sve dok se aplikacija Functions ispravno pokreće i prikazuje pokrenute funkcije. Kao što je navedeno u [ovom pitanju na Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), ovo upozorenje se može ignorirati.

1. Zaustavite aplikaciju Functions pritiskom na `ctrl+c`.

1. Otvorite trenutnu mapu u VS Code-u, bilo otvaranjem VS Code-a pa zatim otvaranjem ove mape, ili pokretanjem sljedeće naredbe:

    ```sh
    code .
    ```

    VS Code će prepoznati vaš Functions projekt i prikazati obavijest koja kaže:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Obavijest](../../../../../translated_images/hr/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Odaberite **Yes** u ovoj obavijesti.

1. Provjerite je li Python virtualno okruženje pokrenuto u terminalu VS Code-a. Ako nije, zaustavite ga i ponovno pokrenite.

## Kreiranje okidača za događaje IoT Hub-a

Aplikacija Functions je okvir za vaš serverless kod. Da biste reagirali na događaje IoT Hub-a, možete dodati okidač za IoT Hub u ovu aplikaciju. Ovaj okidač treba se povezati s tokom poruka koje se šalju u IoT Hub i reagirati na njih. Da biste dobili ovaj tok poruka, vaš okidač mora se povezati s *endpoint-om kompatibilnim s Event Hub-om* IoT Hub-a.

IoT Hub se temelji na drugoj Azure usluzi nazvanoj Azure Event Hubs. Event Hubs je usluga koja omogućuje slanje i primanje poruka, dok IoT Hub proširuje ovu funkcionalnost dodavanjem značajki za IoT uređaje. Način na koji se povezujete za čitanje poruka iz IoT Hub-a isti je kao i za Event Hubs.

✅ Istražite: Pročitajte pregled Event Hubs-a u [Azure Event Hubs dokumentaciji](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Kako se osnovne značajke uspoređuju s IoT Hub-om?

Da bi se IoT uređaj povezao s IoT Hub-om, mora koristiti tajni ključ koji osigurava da se samo dopušteni uređaji mogu povezati. Isto vrijedi i za povezivanje radi čitanja poruka – vaš kod će trebati vezu koja sadrži tajni ključ, zajedno s detaljima o IoT Hub-u.

> 💁 Zadani niz za povezivanje koji dobijete ima **iothubowner** dozvole, što omogućuje bilo kojem kodu koji ga koristi potpune dozvole na IoT Hub-u. Idealno bi bilo da se povežete s najnižom razinom potrebnih dozvola. Ovo će biti obrađeno u sljedećoj lekciji.

Kada se vaš okidač poveže, kod unutar funkcije će se pozivati za svaku poruku poslanu u IoT Hub, bez obzira na to koji uređaj ju je poslao. Poruka će se proslijediti okidaču kao parametar.

### Zadatak - dobivanje niza za povezivanje s endpoint-om kompatibilnim s Event Hub-om

1. Iz terminala VS Code-a pokrenite sljedeću naredbu za dobivanje niza za povezivanje s endpoint-om kompatibilnim s Event Hub-om IoT Hub-a:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` imenom koje ste koristili za svoj IoT Hub.

1. U VS Code-u otvorite datoteku `local.settings.json`. Dodajte sljedeću vrijednost unutar odjeljka `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Zamijenite `<connection string>` vrijednošću iz prethodnog koraka. Trebat ćete dodati zarez nakon prethodnog retka kako bi ovo bio valjan JSON.

### Zadatak - kreiranje okidača za događaje

Sada ste spremni za kreiranje okidača za događaje.

1. Iz terminala VS Code-a pokrenite sljedeću naredbu iz mape `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Ovo kreira novu funkciju nazvanu `iot-hub-trigger`. Okidač će se povezati s endpoint-om kompatibilnim s Event Hub-om na IoT Hub-u, tako da možete koristiti okidač za Event Hub. Ne postoji specifičan okidač za IoT Hub.

Ovo će kreirati mapu unutar mape `soil-moisture-trigger` nazvanu `iot-hub-trigger` koja sadrži ovu funkciju. Ova mapa će sadržavati sljedeće datoteke:

* `__init__.py` - ovo je Python datoteka koja sadrži okidač, koristeći standardnu Python konvenciju imenovanja datoteka kako bi se ova mapa pretvorila u Python modul.

    Ova datoteka će sadržavati sljedeći kod:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Jezgra okidača je funkcija `main`. Ova funkcija se poziva s događajima iz IoT Hub-a. Funkcija ima parametar nazvan `event` koji sadrži `EventHubEvent`. Svaki put kada se poruka pošalje u IoT Hub, ova funkcija se poziva prosljeđujući tu poruku kao `event`, zajedno s atributima koji su isti kao i anotacije koje ste vidjeli u prethodnoj lekciji.

    Jezgra ove funkcije bilježi događaj.

* `function.json` - ovo sadrži konfiguraciju za okidač. Glavna konfiguracija je u odjeljku nazvanom `bindings`. Binding je termin za vezu između Azure Functions i drugih Azure usluga. Ova funkcija ima ulazni binding za Event Hub - povezuje se s Event Hub-om i prima podatke.

    > 💁 Također možete imati izlazne bindinge tako da se izlaz funkcije šalje drugoj usluzi. Na primjer, mogli biste dodati izlazni binding za bazu podataka i vratiti događaj IoT Hub-a iz funkcije, a on će automatski biti umetnut u bazu podataka.

    ✅ Istražite: Pročitajte o bindingima u [Azure Functions triggers and bindings concepts dokumentaciji](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Odjeljak `bindings` uključuje konfiguraciju za binding. Vrijednosti od interesa su:

  * `"type": "eventHubTrigger"` - ovo govori funkciji da treba slušati događaje iz Event Hub-a
  * `"name": "events"` - ovo je naziv parametra za događaje Event Hub-a. Ovo odgovara nazivu parametra u funkciji `main` u Python kodu.
  * `"direction": "in"` - ovo je ulazni binding, podaci iz Event Hub-a dolaze u funkciju
  * `"connection": ""` - ovo definira naziv postavke iz koje se čita niz za povezivanje. Kada se pokreće lokalno, ovo će čitati ovu postavku iz datoteke `local.settings.json`.

    > 💁 Niz za povezivanje ne može se pohraniti u datoteku `function.json`, mora se čitati iz postavki. Ovo je kako biste spriječili slučajno izlaganje vašeg niza za povezivanje.

1. Zbog [greške u Azure Functions predlošku](https://github.com/Azure/azure-functions-templates/issues/1250), `function.json` ima netočnu vrijednost za polje `cardinality`. Ažurirajte ovo polje s `many` na `one`:

    ```json
    "cardinality": "one",
    ```

1. Ažurirajte vrijednost `"connection"` u datoteci `function.json` tako da pokazuje na novu vrijednost koju ste dodali u datoteku `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Zapamtite - ovo treba pokazivati na postavku, a ne sadržavati stvarni niz za povezivanje.

1. Niz za povezivanje sadrži vrijednost `eventHubName`, pa vrijednost za ovo u datoteci `function.json` treba biti prazna. Ažurirajte ovu vrijednost na prazan string:

    ```json
    "eventHubName": "",
    ```

### Zadatak - pokretanje okidača za događaje

1. Provjerite da ne pokrećete monitor događaja IoT Hub-a. Ako je ovo pokrenuto istovremeno s aplikacijom Functions, aplikacija Functions neće moći povezati i konzumirati događaje.

    > 💁 Više aplikacija može se povezati s endpoint-ima IoT Hub-a koristeći različite *consumer groups*. Ovo će biti obrađeno u kasnijoj lekciji.

1. Za pokretanje aplikacije Functions, pokrenite sljedeću naredbu iz terminala VS Code-a:

    ```sh
    func start
    ```

    Aplikacija Functions će se pokrenuti i otkriti funkciju `iot-hub-trigger`. Zatim će obraditi sve događaje koji su već poslani u IoT Hub u posljednjih dan.

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

    Svaki poziv funkciji bit će okružen blokovima `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` u izlazu, tako da možete vidjeti koliko je poruka obrađeno u svakom pozivu funkcije.

1. Provjerite radi li vaš IoT uređaj. Vidjet ćete nove poruke o vlažnosti tla koje se pojavljuju u aplikaciji Functions.

1. Zaustavite i ponovno pokrenite aplikaciju Functions. Vidjet ćete da neće ponovno obrađivati prethodne poruke, već samo nove poruke.

> 💁 VS Code također podržava otklanjanje pogrešaka vaših funkcija. Možete postaviti točke prekida klikom na rub pored početka svakog retka koda, ili postavljanjem kursora na redak koda i odabirom *Run -> Toggle breakpoint*, ili pritiskom na `F9`. Možete pokrenuti debugger odabirom *Run -> Start debugging*, pritiskom na `F5`, ili odabirom *Run and debug* okna i odabirom gumba **Start debugging**. Na taj način možete vidjeti detalje događaja koji se obrađuju.

#### Rješavanje problema

* Ako dobijete sljedeću grešku:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Provjerite radi li Azurite i jeste li postavili `AzureWebJobsStorage` u datoteci `local.settings.json` na `UseDevelopmentStorage=true`.

* Ako dobijete sljedeću grešku:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Provjerite jeste li postavili `cardinality` u datoteci `function.json` na `one`.

* Ako dobijete sljedeću grešku:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Provjerite jeste li postavili `eventHubName` u datoteci `function.json` na prazan string.

## Slanje zahtjeva za direktne metode iz serverless koda

Do sada vaša aplikacija Functions sluša poruke iz IoT Hub-a koristeći endpoint kompatibilan s Event Hub-om. Sada trebate poslati naredbe IoT uređaju. Ovo se radi korištenjem drugačije veze s IoT Hub-om putem *Registry Manager-a*. Registry Manager je alat koji vam omogućuje pregled registriranih uređaja na IoT Hub-u i komunikaciju s tim uređajima slanjem poruka iz oblaka uređaju, zahtjeva za direktne metode ili ažuriranjem device twin-a. Također ga možete koristiti za registraciju, ažuriranje ili brisanje IoT uređaja s IoT Hub-a.

Za povezivanje s Registry Manager-om, potreban vam je niz za povezivanje.

### Zadatak - dobivanje niza za povezivanje s Registry Manager-om

1. Za dobivanje niza za povezivanje, pokrenite sljedeću naredbu:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` imenom koje ste koristili za svoj IoT Hub.

    Niz za povezivanje se traži za *ServiceConnect* politiku koristeći parametar `--policy-name service`. Kada tražite niz za povezivanje, možete specificirati koje dozvole taj niz omogućuje. ServiceConnect politika omogućuje vašem kodu povezivanje i slanje poruka IoT uređajima.

    ✅ Istražite: Pročitajte o različitim politikama u [IoT Hub permissions dokumentaciji](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. U VS Code-u otvorite datoteku `local.settings.json`. Dodajte sljedeću vrijednost unutar odjeljka `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Zamijenite `<connection string>` vrijednošću iz prethodnog koraka. Trebat ćete dodati zarez nakon prethodnog retka kako bi ovo bio valjan JSON.

### Zadatak - slanje zahtjeva za direktnu metodu uređaju

1. SDK za Registry Manager dostupan je putem Pip paketa. Dodajte sljedeći redak u datoteku `requirements.txt` kako biste dodali ovisnost o ovom paketu:

    ```sh
    azure-iot-hub
    ```

1. Provjerite je li terminal VS Code-a aktivirao virtualno okruženje i pokrenite sljedeću naredbu za instalaciju Pip paketa:

    ```sh
    pip install -r requirements.txt
    ```

1. Dodajte sljedeće uvoze u datoteku `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Ovo uvozi neke sistemske biblioteke, kao i biblioteke za interakciju s Registry Manager-om i slanje zahtjeva za direktne metode.

1. Uklonite kod iz funkcije `main`, ali zadržite samu funkciju.

1. U funkciji `main`, dodajte sljedeći kod:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Ovaj kod izdvaja tijelo događaja koje sadrži JSON poruku poslanu od IoT uređaja.

    Zatim dobiva ID uređaja iz anotacija proslijeđenih s porukom. Tijelo događaja sadrži poruku poslanu kao telemetriju, dok `iothub_metadata` rječnik sadrži svojstva postavljena od strane IoT Hub-a, poput ID-a uređaja pošiljatelja i vremena slanja poruke.

    Ove informacije se zatim bilježe. Vidjet ćete ovo bilježenje u terminalu kada pokrenete aplikaciju Functions lokalno.

1. Ispod ovoga, dodajte sljedeći kod:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Ovaj kod dobiva vrijednost vlažnosti tla iz poruke. Zatim provjerava vlažnost tla i, ovisno o vrijednosti, kreira pomoćnu klasu za zahtjev za direktnu metodu `relay_on` ili `relay_off`. Zahtjev za metodu ne treba payload, pa se šalje prazan JSON dokument.

1. Ispod ovoga dodajte sljedeći kod:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Ovaj kod učitava `REGISTRY_MANAGER_CONNECTION_STRING` iz datoteke `local.settings.json`. Vrijednosti u ovoj datoteci dostupne su kao varijable okruženja, a mogu se čitati pomoću funkcije `os.environ`, koja vraća rječnik svih varijabli okruženja.

> 💁 Kada se ovaj kod implementira u oblak, vrijednosti iz datoteke `local.settings.json` bit će postavljene kao *Postavke aplikacije*, i mogu se čitati iz varijabli okruženja.

Kod zatim kreira instancu pomoćne klase Registry Manager koristeći string za povezivanje.

1. Ispod ovoga dodajte sljedeći kod:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Ovaj kod govori Registry Manageru da pošalje zahtjev za direktnu metodu uređaju koji je poslao telemetriju.

    > 💁 U verzijama aplikacije koje ste kreirali u ranijim lekcijama koristeći MQTT, naredbe za upravljanje relejem slale su se svim uređajima. Kod je pretpostavljao da imate samo jedan uređaj. Ova verzija koda šalje zahtjev za metodu jednom uređaju, pa bi radila i ako imate više postavki senzora vlage i releja, šaljući odgovarajući zahtjev za direktnu metodu pravom uređaju.

1. Pokrenite aplikaciju Functions i provjerite šalje li vaš IoT uređaj podatke. Vidjet ćete kako se poruke obrađuju i zahtjevi za direktne metode šalju. Pomaknite senzor vlage tla unutar i izvan tla kako biste vidjeli promjene vrijednosti i uključivanje/isključivanje releja.

> 💁 Ovaj kod možete pronaći u mapi [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Implementirajte svoj serverless kod u oblak

Vaš kod sada radi lokalno, pa je sljedeći korak implementacija aplikacije Functions u oblak.

### Zadatak - kreirajte resurse u oblaku

Vaša aplikacija Functions mora biti implementirana u resurs Functions App u Azureu, koji se nalazi unutar Resource Group koju ste kreirali za svoj IoT Hub. Također ćete trebati kreirati Storage Account u Azureu kako biste zamijenili emulirani koji trenutno koristite lokalno.

1. Pokrenite sljedeću naredbu za kreiranje Storage Account-a:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Zamijenite `<storage_name>` nazivom za vaš Storage Account. Ovaj naziv mora biti globalno jedinstven jer čini dio URL-a koji se koristi za pristup Storage Account-u. Možete koristiti samo mala slova i brojeve za ovaj naziv, bez drugih znakova, a ograničen je na 24 znaka. Koristite nešto poput `sms` i dodajte jedinstveni identifikator na kraju, poput nasumičnih riječi ili vašeg imena.

    Opcija `--sku Standard_LRS` odabire razinu cijene, birajući najjeftiniji opći račun. Ne postoji besplatna razina za pohranu, a plaćate za ono što koristite. Troškovi su relativno niski, s najskupljom pohranom koja košta manje od 0,05 USD mjesečno po gigabajtu pohranjenom.

    ✅ Pročitajte više o cijenama na [stranici s cijenama za Azure Storage Account](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn).

1. Pokrenite sljedeću naredbu za kreiranje aplikacije Functions:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja Resource Group u prethodnoj lekciji.

    Zamijenite `<storage_name>` nazivom Storage Account-a koji ste kreirali u prethodnom koraku.

    Zamijenite `<functions_app_name>` jedinstvenim nazivom za vašu aplikaciju Functions. Ovaj naziv mora biti globalno jedinstven jer čini dio URL-a koji se koristi za pristup aplikaciji Functions. Koristite nešto poput `soil-moisture-sensor-` i dodajte jedinstveni identifikator na kraju, poput nasumičnih riječi ili vašeg imena.

    Opcija `--functions-version 3` postavlja verziju Azure Functions koja će se koristiti. Verzija 3 je najnovija verzija.

    Opcija `--os-type Linux` govori runtime-u Functions da koristi Linux kao OS za hostiranje ovih funkcija. Functions se mogu hostirati na Linuxu ili Windowsu, ovisno o programskom jeziku koji se koristi. Python aplikacije podržane su samo na Linuxu.

### Zadatak - učitajte postavke aplikacije

Kada ste razvijali svoju aplikaciju Functions, pohranili ste neke postavke u datoteku `local.settings.json` za stringove za povezivanje s vašim IoT Hub-om. Ove postavke trebaju biti zapisane u Application Settings u vašoj aplikaciji Functions u Azureu kako bi ih vaš kod mogao koristiti.

> 🎓 Datoteka `local.settings.json` namijenjena je samo za lokalne postavke razvoja i ne bi trebala biti uključena u kontrolu izvornog koda, poput GitHuba. Kada se implementira u oblak, koriste se Application Settings. Application Settings su parovi ključ/vrijednost hostirani u oblaku i čitaju se iz varijabli okruženja, bilo u vašem kodu ili od strane runtime-a kada povezuje vaš kod s IoT Hub-om.

1. Pokrenite sljedeću naredbu za postavljanje postavke `IOT_HUB_CONNECTION_STRING` u Application Settings aplikacije Functions:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Zamijenite `<functions_app_name>` nazivom koji ste koristili za vašu aplikaciju Functions.

    Zamijenite `<connection string>` vrijednošću `IOT_HUB_CONNECTION_STRING` iz vaše datoteke `local.settings.json`.

1. Ponovite gornji korak, ali postavite vrijednost `REGISTRY_MANAGER_CONNECTION_STRING` na odgovarajuću vrijednost iz vaše datoteke `local.settings.json`.

Kada pokrenete ove naredbe, one će također ispisati popis svih Application Settings za aplikaciju Functions. Možete koristiti ovo za provjeru jesu li vaše vrijednosti ispravno postavljene.

> 💁 Vidjet ćete vrijednost koja je već postavljena za `AzureWebJobsStorage`. U vašoj datoteci `local.settings.json`, ovo je bilo postavljeno na vrijednost za korištenje lokalnog emulatora pohrane. Kada ste kreirali aplikaciju Functions, proslijedili ste Storage Account kao parametar, i ovo se automatski postavlja u ovu postavku.

### Zadatak - implementirajte svoju aplikaciju Functions u oblak

Sada kada je aplikacija Functions spremna, vaš kod može biti implementiran.

1. Pokrenite sljedeću naredbu iz terminala u VS Code-u za objavljivanje vaše aplikacije Functions:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Zamijenite `<functions_app_name>` nazivom koji ste koristili za vašu aplikaciju Functions.

Kod će biti pakiran i poslan aplikaciji Functions, gdje će biti implementiran i pokrenut. Bit će puno izlaznih podataka u konzoli, završavajući potvrdom implementacije i popisom implementiranih funkcija. U ovom slučaju popis će sadržavati samo okidač.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Provjerite radi li vaš IoT uređaj. Promijenite razine vlage prilagođavanjem vlage tla ili pomicanjem senzora unutar i izvan tla. Vidjet ćete kako se relej uključuje i isključuje dok se vlaga tla mijenja.

---

## 🚀 Izazov

U prethodnoj lekciji upravljali ste vremenom za relej tako što ste se odjavili s MQTT poruka dok je relej bio uključen, i kratko vrijeme nakon što je bio isključen. Ovu metodu ne možete koristiti ovdje - ne možete odjaviti svoj IoT Hub okidač.

Razmislite o različitim načinima na koje biste mogli upravljati ovim u svojoj aplikaciji Functions.

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Pregled i samostalno učenje

* Pročitajte o serverless računarstvu na [stranici o serverless računarstvu na Wikipediji](https://wikipedia.org/wiki/Serverless_computing)
* Pročitajte o korištenju serverless u Azureu, uključujući još primjera, na [blog postu Azure Go serverless for your IoT needs](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Saznajte više o Azure Functions na [YouTube kanalu Azure Functions](https://www.youtube.com/c/AzureFunctions)

## Zadatak

[Dodajte ručnu kontrolu releja](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.