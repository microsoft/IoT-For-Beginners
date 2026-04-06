# Migrarea logicii aplicației tale în cloud

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-9.dfe99c8e891f48e1.webp)

> Schiță realizată de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

Această lecție a fost predată ca parte a [Proiectului IoT pentru Începători 2 - Seria Agricultură Digitală](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) de la [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Controlează dispozitivul IoT cu cod serverless](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Introducere

În lecția anterioară, ai învățat cum să conectezi monitorizarea umidității solului plantei și controlul releului la un serviciu IoT bazat pe cloud. Următorul pas este să muți codul serverului care controlează sincronizarea releului în cloud. În această lecție vei învăța cum să faci acest lucru folosind funcții serverless.

În această lecție vom acoperi:

* [Ce este serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Crearea unei aplicații serverless](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Crearea unui declanșator de evenimente pentru IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Trimiterea cererilor de metodă directă din cod serverless](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Deploiarea codului serverless în cloud](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Ce este serverless?

Serverless, sau calculul fără server, implică crearea unor blocuri mici de cod care sunt rulate în cloud ca răspuns la diferite tipuri de evenimente. Când evenimentul are loc, codul tău este rulat și primește date despre eveniment. Aceste evenimente pot proveni din diverse surse, inclusiv cereri web, mesaje puse într-o coadă, modificări ale datelor dintr-o bază de date sau mesaje trimise către un serviciu IoT de către dispozitive IoT.

![Evenimente trimise de la un serviciu IoT către un serviciu serverless, toate procesate simultan de funcții multiple](../../../../../translated_images/ro/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Dacă ai folosit declanșatoare de baze de date înainte, poți considera acest lucru similar: codul este declanșat de un eveniment, cum ar fi inserarea unui rând.

![Când multe evenimente sunt trimise simultan, serviciul serverless se scalează pentru a le procesa pe toate în același timp](../../../../../translated_images/ro/serverless-scaling.f8c769adf0413fd1.webp)

Codul tău este rulat doar atunci când evenimentul are loc, nu există nimic care să mențină codul activ în alte momente. Evenimentul are loc, codul tău este încărcat și rulat. Acest lucru face ca serverless să fie foarte scalabil - dacă multe evenimente au loc simultan, furnizorul de cloud poate rula funcția ta de câte ori este nevoie, simultan, pe serverele disponibile. Dezavantajul este că, dacă trebuie să partajezi informații între evenimente, trebuie să le salvezi undeva, cum ar fi într-o bază de date, în loc să le stochezi în memorie.

Codul tău este scris ca o funcție care primește detalii despre eveniment ca parametru. Poți folosi o gamă largă de limbaje de programare pentru a scrie aceste funcții serverless.

> 🎓 Serverless este denumit și Funcții ca Serviciu (FaaS), deoarece fiecare declanșator de eveniment este implementat ca o funcție în cod.

Deși numele sugerează altceva, serverless folosește de fapt servere. Denumirea vine din faptul că, ca dezvoltator, nu te preocupi de serverele necesare pentru a rula codul tău, ci doar de faptul că codul tău este rulat ca răspuns la un eveniment. Furnizorul de cloud are un *runtime* serverless care gestionează alocarea serverelor, rețelele, stocarea, CPU-ul, memoria și tot ce este necesar pentru a rula codul tău. Acest model înseamnă că nu plătești per server pentru serviciu, deoarece nu există un server dedicat. În schimb, plătești pentru timpul în care codul tău este rulat și pentru cantitatea de memorie utilizată.

> 💰 Serverless este una dintre cele mai ieftine modalități de a rula cod în cloud. De exemplu, la momentul redactării, un furnizor de cloud permite ca toate funcțiile serverless să fie executate de 1.000.000 de ori pe lună înainte de a începe să te taxeze, iar după aceea percepe 0,20 USD pentru fiecare 1.000.000 de execuții. Când codul tău nu rulează, nu plătești.

Ca dezvoltator IoT, modelul serverless este ideal. Poți scrie o funcție care este apelată ca răspuns la mesajele trimise de orice dispozitiv IoT conectat la serviciul IoT găzduit în cloud. Codul tău va gestiona toate mesajele trimise, dar va fi activ doar atunci când este necesar.

✅ Revizuiește codul pe care l-ai scris ca server care ascultă mesaje prin MQTT. Cum ar putea acesta să funcționeze în cloud folosind serverless? Cum crezi că ar trebui modificat codul pentru a susține calculul serverless?

> 💁 Modelul serverless se extinde și la alte servicii cloud, pe lângă rularea codului. De exemplu, bazele de date serverless sunt disponibile în cloud folosind un model de tarifare serverless, unde plătești per cerere făcută împotriva bazei de date, cum ar fi o interogare sau o inserare, de obicei pe baza volumului de muncă necesar pentru a răspunde cererii. De exemplu, o singură selecție a unui rând pe baza unei chei primare va costa mai puțin decât o operațiune complexă care unește multe tabele și returnează mii de rânduri.

## Crearea unei aplicații serverless

Serviciul de calcul serverless de la Microsoft se numește Azure Functions.

![Logo-ul Azure Functions](../../../../../translated_images/ro/azure-functions-logo.1cfc8e3204c9c44a.webp)

Videoclipul scurt de mai jos oferă o prezentare generală a Azure Functions.

[![Videoclip de prezentare Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Click pe imaginea de mai sus pentru a viziona videoclipul.

✅ Ia un moment pentru a face cercetări și citește prezentarea generală a Azure Functions în [documentația Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Pentru a scrie Azure Functions, începi cu o aplicație Azure Functions în limbajul de programare ales. Azure Functions suportă Python, JavaScript, TypeScript, C#, F#, Java și Powershell. În această lecție vei învăța cum să scrii o aplicație Azure Functions în Python.

> 💁 Azure Functions suportă și handleri personalizați, astfel încât să poți scrie funcțiile tale în orice limbaj care suportă cereri HTTP, inclusiv limbaje mai vechi precum COBOL.

Aplicațiile de funcții constau din unul sau mai multe *declanșatoare* - funcții care răspund la evenimente. Poți avea mai multe declanșatoare într-o singură aplicație de funcții, toate împărtășind o configurație comună. De exemplu, în fișierul de configurare al aplicației tale de funcții poți avea detaliile de conectare ale IoT Hub-ului tău, iar toate funcțiile din aplicație pot folosi aceste detalii pentru a se conecta și a asculta evenimente.

### Sarcină - instalarea instrumentelor Azure Functions

> La momentul redactării, instrumentele de cod Azure Functions nu funcționează complet pe Apple Silicon pentru proiectele Python. Va trebui să folosești un Mac bazat pe Intel, un PC Windows sau un PC Linux.

Un mare avantaj al Azure Functions este că le poți rula local. Același runtime utilizat în cloud poate fi rulat pe computerul tău, permițându-ți să scrii cod care răspunde la mesaje IoT și să-l rulezi local. Poți chiar să depanezi codul pe măsură ce evenimentele sunt gestionate. Odată ce ești mulțumit de codul tău, acesta poate fi deploiat în cloud.

Instrumentele Azure Functions sunt disponibile ca CLI, cunoscut sub numele de Azure Functions Core Tools.

1. Instalează instrumentele Azure Functions Core Tools urmând instrucțiunile din [documentația Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Instalează extensia Azure Functions pentru VS Code. Această extensie oferă suport pentru crearea, depanarea și deploierea funcțiilor Azure. Consultă [documentația extensiei Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) pentru instrucțiuni despre instalarea acestei extensii în VS Code.

Când deploi aplicația Azure Functions în cloud, aceasta trebuie să folosească o mică cantitate de stocare cloud pentru a stoca fișierele aplicației și fișierele jurnal. Când rulezi aplicația de funcții local, trebuie să te conectezi la stocarea cloud, dar în loc să folosești stocarea reală, poți folosi un emulator de stocare numit [Azurite](https://github.com/Azure/Azurite). Acesta rulează local, dar se comportă ca stocarea cloud.

> 🎓 În Azure, stocarea utilizată de Azure Functions este un cont de stocare Azure. Aceste conturi pot stoca fișiere, blob-uri, date în tabele sau date în cozi. Poți partaja un cont de stocare între mai multe aplicații, cum ar fi o aplicație de funcții și o aplicație web.

1. Azurite este o aplicație Node.js, așa că va trebui să instalezi Node.js. Poți găsi instrucțiunile de descărcare și instalare pe [site-ul Node.js](https://nodejs.org/). Dacă folosești un Mac, îl poți instala și din [Homebrew](https://formulae.brew.sh/formula/node).

1. Instalează Azurite folosind următoarea comandă (`npm` este un instrument instalat odată cu Node.js):

    ```sh
    npm install -g azurite
    ```

1. Creează un folder numit `azurite` pentru ca Azurite să-l folosească pentru stocarea datelor:

    ```sh
    mkdir azurite
    ```

1. Rulează Azurite, trecându-i acest nou folder:

    ```sh
    azurite --location azurite
    ```

    Emulatorul de stocare Azurite va fi lansat și va fi gata pentru ca runtime-ul local de funcții să se conecteze.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Sarcină - crearea unui proiect Azure Functions

CLI-ul Azure Functions poate fi folosit pentru a crea o nouă aplicație de funcții.

1. Creează un folder pentru aplicația ta de funcții și navighează în el. Numeste-l `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Creează un mediu virtual Python în acest folder:

    ```sh
    python3 -m venv .venv
    ```

1. Activează mediul virtual:

    * Pe Windows:
        * Dacă folosești Command Prompt sau Command Prompt prin Windows Terminal, rulează:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Dacă folosești PowerShell, rulează:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Pe macOS sau Linux, rulează:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Aceste comenzi ar trebui să fie rulate din aceeași locație în care ai rulat comanda pentru a crea mediul virtual. Nu va trebui niciodată să navighezi în folderul `.venv`, ar trebui să rulezi întotdeauna comanda de activare și orice comenzi pentru instalarea pachetelor sau rularea codului din folderul în care te aflai când ai creat mediul virtual.

1. Rulează următoarea comandă pentru a crea o aplicație de funcții în acest folder:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Aceasta va crea trei fișiere în folderul curent:

    * `host.json` - acest document JSON conține setările pentru aplicația ta de funcții. Nu va trebui să modifici aceste setări.
    * `local.settings.json` - acest document JSON conține setările pe care aplicația ta le-ar folosi atunci când rulează local, cum ar fi șirurile de conexiune pentru IoT Hub. Aceste setări sunt doar locale și nu ar trebui să fie adăugate în controlul sursei. Când deploi aplicația în cloud, aceste setări nu sunt deploiate, în schimb setările tale sunt încărcate din setările aplicației. Acest lucru va fi acoperit mai târziu în lecție.
    * `requirements.txt` - acesta este un [fișier de cerințe Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files) care conține pachetele Pip necesare pentru a rula aplicația ta de funcții.

1. Fișierul `local.settings.json` are o setare pentru contul de stocare pe care aplicația de funcții îl va folosi. Acesta are implicit o setare goală, așa că trebuie să fie setat. Pentru a te conecta la emulatorul de stocare local Azurite, setează această valoare la următoarea:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Instalează pachetele Pip necesare folosind fișierul de cerințe:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Pachetele Pip necesare trebuie să fie în acest fișier, astfel încât atunci când aplicația de funcții este deploiată în cloud, runtime-ul să poată asigura instalarea pachetelor corecte.

1. Pentru a testa dacă totul funcționează corect, poți porni runtime-ul de funcții. Rulează următoarea comandă pentru a face acest lucru:

    ```sh
    func start
    ```

    Vei vedea cum runtime-ul pornește și raportează că nu a găsit funcții de lucru (declanșatoare).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Dacă primești o notificare de firewall, acordă acces deoarece aplicația `func` trebuie să poată citi și scrie pe rețeaua ta.
> ⚠️ Dacă utilizați macOS, este posibil să apară avertismente în ieșire:
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
> Puteți ignora aceste avertismente atâta timp cât aplicația Functions pornește corect și listează funcțiile care rulează. După cum este menționat în [această întrebare pe Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), acestea pot fi ignorate.

1. Opriți aplicația Functions apăsând `ctrl+c`.

1. Deschideți folderul curent în VS Code, fie deschizând VS Code și apoi acest folder, fie rulând următoarea comandă:

    ```sh
    code .
    ```

    VS Code va detecta proiectul Functions și va afișa o notificare care spune:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Notificarea](../../../../../translated_images/ro/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Selectați **Yes** din această notificare.

1. Asigurați-vă că mediul virtual Python rulează în terminalul VS Code. Opriți-l și reporniți-l dacă este necesar.

## Creați un trigger pentru evenimentele IoT Hub

Aplicația Functions este scheletul codului dvs. serverless. Pentru a răspunde evenimentelor IoT Hub, puteți adăuga un trigger IoT Hub la această aplicație. Acest trigger trebuie să se conecteze la fluxul de mesaje trimise către IoT Hub și să răspundă la acestea. Pentru a obține acest flux de mesaje, trigger-ul dvs. trebuie să se conecteze la *endpoint-ul compatibil cu Event Hub* al IoT Hub.

IoT Hub se bazează pe un alt serviciu Azure numit Azure Event Hubs. Event Hubs este un serviciu care permite trimiterea și primirea de mesaje, iar IoT Hub extinde acest lucru pentru a adăuga funcționalități pentru dispozitive IoT. Modul în care vă conectați pentru a citi mesajele din IoT Hub este același ca și cum ați utiliza Event Hubs.

✅ Faceți cercetări: Citiți prezentarea generală a Event Hubs în [documentația Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Cum se compară funcțiile de bază cu cele ale IoT Hub?

Pentru ca un dispozitiv IoT să se conecteze la IoT Hub, trebuie să utilizeze o cheie secretă care asigură că doar dispozitivele autorizate se pot conecta. Același lucru se aplică și atunci când vă conectați pentru a citi mesajele; codul dvs. va avea nevoie de un connection string care conține o cheie secretă, împreună cu detalii despre IoT Hub.

> 💁 Connection string-ul implicit pe care îl obțineți are permisiuni **iothubowner**, ceea ce oferă oricărui cod care îl utilizează permisiuni complete asupra IoT Hub. Ideal ar fi să vă conectați cu cel mai scăzut nivel de permisiuni necesar. Acest lucru va fi acoperit în lecția următoare.

Odată ce trigger-ul s-a conectat, codul din funcție va fi apelat pentru fiecare mesaj trimis către IoT Hub, indiferent de dispozitivul care l-a trimis. Trigger-ul va primi mesajul ca parametru.

### Sarcină - obțineți connection string-ul endpoint-ului compatibil cu Event Hub

1. Din terminalul VS Code, rulați următoarea comandă pentru a obține connection string-ul pentru endpoint-ul compatibil cu Event Hub al IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Înlocuiți `<hub_name>` cu numele pe care l-ați utilizat pentru IoT Hub.

1. În VS Code, deschideți fișierul `local.settings.json`. Adăugați următoarea valoare suplimentară în secțiunea `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Înlocuiți `<connection string>` cu valoarea din pasul anterior. Va trebui să adăugați o virgulă după linia de mai sus pentru a face acest JSON valid.

### Sarcină - creați un trigger pentru evenimente

Acum sunteți gata să creați trigger-ul pentru evenimente.

1. Din terminalul VS Code, rulați următoarea comandă din folderul `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Aceasta creează o nouă funcție numită `iot-hub-trigger`. Trigger-ul se va conecta la endpoint-ul compatibil cu Event Hub al IoT Hub, astfel încât să puteți utiliza un trigger pentru Event Hub. Nu există un trigger specific pentru IoT Hub.

Aceasta va crea un folder în interiorul folderului `soil-moisture-trigger` numit `iot-hub-trigger`, care conține această funcție. Acest folder va avea următoarele fișiere în interior:

* `__init__.py` - acesta este fișierul de cod Python care conține trigger-ul, utilizând convenția standard de denumire a fișierelor Python pentru a transforma acest folder într-un modul Python.

    Acest fișier va conține următorul cod:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Nucleul trigger-ului este funcția `main`. Aceasta este funcția care este apelată cu evenimentele de la IoT Hub. Această funcție are un parametru numit `event` care conține un `EventHubEvent`. De fiecare dată când un mesaj este trimis către IoT Hub, această funcție este apelată, transmițând acel mesaj ca `event`, împreună cu proprietăți care sunt aceleași cu adnotările pe care le-ați văzut în lecția anterioară.

    Nucleul acestei funcții înregistrează evenimentul.

* `function.json` - acesta conține configurația pentru trigger. Configurația principală este într-o secțiune numită `bindings`. Un binding este termenul pentru o conexiune între Azure Functions și alte servicii Azure. Această funcție are un binding de intrare către un Event Hub - se conectează la un Event Hub și primește date.

    > 💁 Puteți avea și binding-uri de ieșire, astfel încât ieșirea unei funcții să fie trimisă către un alt serviciu. De exemplu, ați putea adăuga un binding de ieșire către o bază de date și să returnați evenimentul IoT Hub din funcție, iar acesta va fi inserat automat în baza de date.

    ✅ Faceți cercetări: Citiți despre binding-uri în [documentația despre conceptele de triggers și bindings din Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Secțiunea `bindings` include configurația pentru binding. Valorile de interes sunt:

  * `"type": "eventHubTrigger"` - aceasta indică funcției că trebuie să asculte evenimentele de la un Event Hub
  * `"name": "events"` - acesta este numele parametrului utilizat pentru evenimentele Event Hub. Acesta corespunde cu numele parametrului din funcția `main` din codul Python.
  * `"direction": "in"` - acesta este un binding de intrare, datele din Event Hub intră în funcție
  * `"connection": ""` - aceasta definește numele setării din care se citește connection string-ul. Când rulați local, aceasta va citi această setare din fișierul `local.settings.json`.

    > 💁 Connection string-ul nu poate fi stocat în fișierul `function.json`, trebuie să fie citit din setări. Acest lucru este pentru a preveni expunerea accidentală a connection string-ului.

1. Datorită [unei erori în șablonul Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250), fișierul `function.json` are o valoare incorectă pentru câmpul `cardinality`. Actualizați acest câmp de la `many` la `one`:

    ```json
    "cardinality": "one",
    ```

1. Actualizați valoarea `"connection"` din fișierul `function.json` pentru a indica noua valoare pe care ați adăugat-o în fișierul `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Rețineți - aceasta trebuie să indice setarea, nu să conțină efectiv connection string-ul.

1. Connection string-ul conține valoarea `eventHubName`, astfel încât valoarea pentru aceasta din fișierul `function.json` trebuie să fie golită. Actualizați această valoare la un șir gol:

    ```json
    "eventHubName": "",
    ```

### Sarcină - rulați trigger-ul pentru evenimente

1. Asigurați-vă că nu rulați monitorul de evenimente IoT Hub. Dacă acesta rulează în același timp cu aplicația Functions, aplicația Functions nu va putea să se conecteze și să consume evenimente.

    > 💁 Mai multe aplicații se pot conecta la endpoint-urile IoT Hub utilizând diferite *grupuri de consumatori*. Acestea vor fi acoperite într-o lecție ulterioară.

1. Pentru a rula aplicația Functions, rulați următoarea comandă din terminalul VS Code:

    ```sh
    func start
    ```

    Aplicația Functions va porni și va descoperi funcția `iot-hub-trigger`. Aceasta va procesa apoi orice evenimente care au fost deja trimise către IoT Hub în ultima zi.

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

    Fiecare apel al funcției va fi înconjurat de un bloc `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` în ieșire, astfel încât să puteți vedea câte mesaje au fost procesate în fiecare apel al funcției.

1. Asigurați-vă că dispozitivul dvs. IoT rulează. Veți vedea noi mesaje despre umiditatea solului apărând în aplicația Functions.

1. Opriți și reporniți aplicația Functions. Veți observa că nu va procesa din nou mesajele anterioare, ci doar mesajele noi.

> 💁 VS Code suportă, de asemenea, depanarea funcțiilor dvs. Puteți seta puncte de întrerupere făcând clic pe marginea de la începutul fiecărei linii de cod, sau plasând cursorul pe o linie de cod și selectând *Run -> Toggle breakpoint*, sau apăsând `F9`. Puteți lansa depanatorul selectând *Run -> Start debugging*, apăsând `F5`, sau selectând panoul *Run and debug* și apăsând butonul **Start debugging**. Procedând astfel, puteți vedea detaliile evenimentelor procesate.

#### Depanare

* Dacă primiți următoarea eroare:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Verificați dacă Azurite rulează și dacă ați setat `AzureWebJobsStorage` în fișierul `local.settings.json` la `UseDevelopmentStorage=true`.

* Dacă primiți următoarea eroare:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Verificați dacă ați setat `cardinality` în fișierul `function.json` la `one`.

* Dacă primiți următoarea eroare:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Verificați dacă ați setat `eventHubName` în fișierul `function.json` la un șir gol.

## Trimiteți cereri de metodă directă din cod serverless

Până acum, aplicația Functions ascultă mesajele de la IoT Hub utilizând endpoint-ul compatibil cu Event Hub. Acum trebuie să trimiteți comenzi către dispozitivul IoT. Acest lucru se face utilizând o conexiune diferită la IoT Hub prin *Registry Manager*. Registry Manager este un instrument care vă permite să vedeți ce dispozitive sunt înregistrate în IoT Hub și să comunicați cu acele dispozitive trimițând mesaje cloud-to-device, cereri de metodă directă sau actualizând device twin-ul. De asemenea, îl puteți utiliza pentru a înregistra, actualiza sau șterge dispozitive IoT din IoT Hub.

Pentru a vă conecta la Registry Manager, aveți nevoie de un connection string.

### Sarcină - obțineți connection string-ul pentru Registry Manager

1. Pentru a obține connection string-ul, rulați următoarea comandă:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Înlocuiți `<hub_name>` cu numele pe care l-ați utilizat pentru IoT Hub.

    Connection string-ul este solicitat pentru politica *ServiceConnect* utilizând parametrul `--policy-name service`. Când solicitați un connection string, puteți specifica ce permisiuni va permite acel connection string. Politica ServiceConnect permite codului dvs. să se conecteze și să trimită mesaje către dispozitive IoT.

    ✅ Faceți cercetări: Citiți despre diferitele politici în [documentația despre permisiunile IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. În VS Code, deschideți fișierul `local.settings.json`. Adăugați următoarea valoare suplimentară în secțiunea `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Înlocuiți `<connection string>` cu valoarea din pasul anterior. Va trebui să adăugați o virgulă după linia de mai sus pentru a face acest JSON valid.

### Sarcină - trimiteți o cerere de metodă directă către un dispozitiv

1. SDK-ul pentru Registry Manager este disponibil printr-un pachet Pip. Adăugați următoarea linie în fișierul `requirements.txt` pentru a adăuga dependența de acest pachet:

    ```sh
    azure-iot-hub
    ```

1. Asigurați-vă că terminalul VS Code are activat mediul virtual și rulați următoarea comandă pentru a instala pachetele Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. Adăugați următoarele importuri în fișierul `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Acestea importă câteva biblioteci de sistem, precum și bibliotecile pentru a interacționa cu Registry Manager și a trimite cereri de metodă directă.

1. Eliminați codul din interiorul metodei `main`, dar păstrați metoda în sine.

1. În metoda `main`, adăugați următorul cod:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Acest cod extrage corpul evenimentului care conține mesajul JSON trimis de dispozitivul IoT.

    Apoi obține ID-ul dispozitivului din adnotările transmise cu mesajul. Corpul evenimentului conține mesajul trimis ca telemetrie, iar dicționarul `iothub_metadata` conține proprietăți setate de IoT Hub, cum ar fi ID-ul dispozitivului expeditor și timpul la care a fost trimis mesajul.

    Aceste informații sunt apoi înregistrate. Veți vedea acest jurnal în terminal atunci când rulați aplicația Function local.

1. Sub acest cod, adăugați următorul cod:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Acest cod obține valoarea umidității solului din mesaj. Apoi verifică umiditatea solului și, în funcție de valoare, creează o clasă ajutătoare pentru cererea de metodă directă pentru metoda `relay_on` sau `relay_off`. Cererea metodei nu necesită un payload, astfel încât se trimite un document JSON gol.

1. Sub acest cod, adăugați următorul cod:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Acest cod încarcă `REGISTRY_MANAGER_CONNECTION_STRING` din fișierul `local.settings.json`. Valorile din acest fișier sunt disponibile ca variabile de mediu și pot fi citite folosind funcția `os.environ`, o funcție care returnează un dicționar cu toate variabilele de mediu.

> 💁 Când acest cod este implementat în cloud, valorile din fișierul `local.settings.json` vor fi setate ca *Application Settings* și pot fi citite din variabilele de mediu.

Codul creează apoi o instanță a clasei helper Registry Manager folosind connection string-ul.

1. Adaugă următorul cod mai jos:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Acest cod indică managerului de registru să trimită cererea de metodă directă dispozitivului care a trimis telemetria.

    > 💁 În versiunile aplicației create în lecțiile anterioare folosind MQTT, comenzile de control al releului erau trimise către toate dispozitivele. Codul presupunea că vei avea un singur dispozitiv. Această versiune a codului trimite cererea de metodă către un singur dispozitiv, astfel încât să funcționeze dacă ai mai multe seturi de senzori de umiditate și relee, trimițând cererea de metodă directă dispozitivului corect.

1. Rulează aplicația Functions și asigură-te că dispozitivul tău IoT trimite date. Vei vedea mesajele procesate și cererile de metodă directă trimise. Mută senzorul de umiditate a solului în și din sol pentru a vedea cum valorile se schimbă și releul se aprinde și se stinge.

> 💁 Poți găsi acest cod în folderul [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Implementează codul serverless în cloud

Codul tău funcționează acum local, așa că următorul pas este să implementezi aplicația Functions în cloud.

### Sarcină - creează resursele în cloud

Aplicația ta Functions trebuie implementată într-o resursă Functions App din Azure, care se află în cadrul Resource Group creat pentru IoT Hub-ul tău. De asemenea, vei avea nevoie de un Storage Account creat în Azure pentru a înlocui cel emulat pe care îl rulezi local.

1. Rulează următoarea comandă pentru a crea un cont de stocare:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Înlocuiește `<storage_name>` cu un nume pentru contul tău de stocare. Acesta trebuie să fie unic la nivel global, deoarece face parte din URL-ul folosit pentru a accesa contul de stocare. Poți folosi doar litere mici și cifre pentru acest nume, fără alte caractere, și este limitat la 24 de caractere. Folosește ceva precum `sms` și adaugă un identificator unic la final, cum ar fi câteva cuvinte aleatorii sau numele tău.

    Opțiunea `--sku Standard_LRS` selectează nivelul de preț, alegând cel mai ieftin cont general. Nu există un nivel gratuit de stocare, iar costurile sunt calculate în funcție de utilizare. Costurile sunt relativ mici, cel mai scump stocaj fiind mai puțin de 0,05 USD pe lună per gigabyte stocat.

    ✅ Citește despre prețuri pe [pagina de prețuri Azure Storage Account](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Rulează următoarea comandă pentru a crea o aplicație Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Înlocuiește `<location>` cu locația pe care ai folosit-o când ai creat Resource Group-ul în lecția anterioară.

    Înlocuiește `<storage_name>` cu numele contului de stocare creat în pasul anterior.

    Înlocuiește `<functions_app_name>` cu un nume unic pentru aplicația ta Functions App. Acesta trebuie să fie unic la nivel global, deoarece face parte dintr-un URL care poate fi folosit pentru a accesa aplicația Functions. Folosește ceva precum `soil-moisture-sensor-` și adaugă un identificator unic la final, cum ar fi câteva cuvinte aleatorii sau numele tău.

    Opțiunea `--functions-version 3` setează versiunea Azure Functions de utilizat. Versiunea 3 este cea mai recentă versiune.

    Opțiunea `--os-type Linux` indică runtime-ului Functions să folosească Linux ca sistem de operare pentru găzduirea acestor funcții. Funcțiile pot fi găzduite pe Linux sau Windows, în funcție de limbajul de programare utilizat. Aplicațiile Python sunt acceptate doar pe Linux.

### Sarcină - încarcă setările aplicației tale

Când ai dezvoltat aplicația Functions, ai stocat câteva setări în fișierul `local.settings.json` pentru connection strings ale IoT Hub-ului tău. Acestea trebuie scrise în Application Settings în Function App-ul tău din Azure, astfel încât să poată fi utilizate de codul tău.

> 🎓 Fișierul `local.settings.json` este destinat doar setărilor de dezvoltare locală și nu ar trebui să fie inclus în controlul sursei, cum ar fi GitHub. Când este implementat în cloud, sunt utilizate Application Settings. Application Settings sunt perechi cheie/valoare găzduite în cloud și sunt citite din variabilele de mediu fie în codul tău, fie de runtime atunci când conectează codul tău la IoT Hub.

1. Rulează următoarea comandă pentru a seta setarea `IOT_HUB_CONNECTION_STRING` în Application Settings ale aplicației Functions:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Înlocuiește `<functions_app_name>` cu numele pe care l-ai folosit pentru aplicația Functions.

    Înlocuiește `<connection string>` cu valoarea `IOT_HUB_CONNECTION_STRING` din fișierul tău `local.settings.json`.

1. Repetă pasul de mai sus, dar setează valoarea `REGISTRY_MANAGER_CONNECTION_STRING` la valoarea corespunzătoare din fișierul tău `local.settings.json`.

Când rulezi aceste comenzi, ele vor afișa și o listă cu toate Application Settings pentru aplicația ta Functions. Poți folosi această listă pentru a verifica dacă valorile sunt setate corect.

> 💁 Vei vedea o valoare deja setată pentru `AzureWebJobsStorage`. În fișierul tău `local.settings.json`, aceasta a fost setată la o valoare pentru a utiliza emulatorul de stocare locală. Când ai creat aplicația Functions, ai trecut contul de stocare ca parametru, iar acesta este setat automat în această setare.

### Sarcină - implementează aplicația Functions în cloud

Acum că aplicația Functions este pregătită, codul tău poate fi implementat.

1. Rulează următoarea comandă din terminalul VS Code pentru a publica aplicația Functions:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Înlocuiește `<functions_app_name>` cu numele pe care l-ai folosit pentru aplicația Functions.

Codul va fi împachetat și trimis către aplicația Functions, unde va fi implementat și pornit. Va exista o mulțime de ieșiri în consolă, care se vor încheia cu confirmarea implementării și o listă a funcțiilor implementate. În acest caz, lista va conține doar trigger-ul.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Asigură-te că dispozitivul tău IoT este pornit. Modifică nivelurile de umiditate ajustând umiditatea solului sau mutând senzorul în și din sol. Vei vedea releul aprinzându-se și stingându-se pe măsură ce umiditatea solului se schimbă.

---

## 🚀 Provocare

În lecția anterioară, ai gestionat temporizarea releului dezabonându-te de la mesajele MQTT în timp ce releul era pornit și pentru o scurtă perioadă după ce a fost oprit. Nu poți folosi această metodă aici - nu te poți dezabona de la trigger-ul IoT Hub.

Gândește-te la diferite moduri în care ai putea gestiona acest lucru în aplicația Functions.

## Chestionar post-lectură

[Chestionar post-lectură](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Recapitulare și studiu individual

* Citește despre computing-ul serverless pe [pagina Serverless Computing de pe Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Citește despre utilizarea serverless în Azure, inclusiv câteva exemple suplimentare, în [postarea de blog Azure despre serverless pentru nevoile tale IoT](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Află mai multe despre Azure Functions pe [canalul YouTube Azure Functions](https://www.youtube.com/c/AzureFunctions)

## Temă

[Adaugă control manual al releului](assignment.md)

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.