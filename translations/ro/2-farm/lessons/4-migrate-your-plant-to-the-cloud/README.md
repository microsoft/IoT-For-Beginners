<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-28T11:20:53+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "ro"
}
-->
# Migrarea plantei tale în cloud

![O prezentare grafică a lecției](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.ro.jpg)

> Prezentare grafică realizată de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

Această lecție a fost predată ca parte a [Proiectului IoT pentru Începători 2 - Seria Agricultură Digitală](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) de la [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Conectează dispozitivul tău la cloud cu Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introducere

În lecția anterioară, ai învățat cum să conectezi planta ta la un broker MQTT și să controlezi un releu folosind cod server care rulează local. Acesta reprezintă nucleul unui sistem automatizat de irigare conectat la internet, utilizat atât pentru plante individuale acasă, cât și pentru ferme comerciale.

Dispozitivul IoT a comunicat cu un broker MQTT public pentru a demonstra principiile, dar aceasta nu este cea mai fiabilă sau sigură metodă. În această lecție vei învăța despre cloud și capacitățile IoT oferite de serviciile publice de cloud. De asemenea, vei învăța cum să migrezi planta ta către unul dintre aceste servicii cloud de la brokerul MQTT public.

În această lecție vom acoperi:

* [Ce este cloud-ul?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Crearea unui abonament cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Servicii IoT în cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Crearea unui serviciu IoT în cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Comunicarea cu IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Conectarea dispozitivului tău la serviciul IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Ce este cloud-ul?

Înainte de apariția cloud-ului, atunci când o companie dorea să ofere servicii angajaților săi (cum ar fi baze de date sau stocare de fișiere) sau publicului (cum ar fi site-uri web), trebuia să construiască și să gestioneze un centru de date. Acesta putea varia de la o cameră cu un număr mic de computere până la o clădire cu multe computere. Compania era responsabilă de tot, inclusiv:

* Achiziționarea de computere
* Întreținerea hardware-ului
* Alimentare și răcire
* Rețelistică
* Securitate, inclusiv securizarea clădirii și a software-ului de pe computere
* Instalarea și actualizarea software-ului

Acest lucru putea fi foarte costisitor, necesita o gamă largă de angajați calificați și era foarte lent de schimbat atunci când era necesar. De exemplu, dacă un magazin online trebuia să se pregătească pentru un sezon de sărbători aglomerat, trebuia să planifice cu luni înainte pentru a achiziționa mai mult hardware, să-l configureze, să instaleze software-ul necesar pentru procesul de vânzare. După ce sezonul de sărbători se încheia și vânzările scădeau, rămâneau cu computerele achiziționate care stăteau neutilizate până la următorul sezon aglomerat.

✅ Crezi că acest lucru ar permite companiilor să se miște rapid? Dacă un retailer de haine online devenea brusc popular datorită unui celebru care purta hainele lor, ar putea să își mărească rapid puterea de calcul pentru a susține influxul brusc de comenzi?

### Computerul altcuiva

Cloud-ul este adesea numit în glumă „computerul altcuiva”. Ideea inițială era simplă - în loc să cumperi computere, închiriezi computerele altcuiva. Altcineva, un furnizor de servicii cloud, ar gestiona centre de date uriașe. Ei ar fi responsabili de achiziționarea și instalarea hardware-ului, gestionarea alimentării și răcirii, rețelistică, securitatea clădirii, actualizările hardware și software, totul. Ca client, ai închiria computerele de care ai nevoie, închiriind mai multe pe măsură ce cererea crește, apoi reducând numărul închiriat dacă cererea scade. Aceste centre de date cloud sunt răspândite în întreaga lume.

![Un centru de date cloud Microsoft](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.ro.png)
![O extindere planificată a unui centru de date cloud Microsoft](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.ro.png)

Aceste centre de date pot avea dimensiuni de câțiva kilometri pătrați. Imaginile de mai sus au fost realizate acum câțiva ani la un centru de date cloud Microsoft și arată dimensiunea inițială, împreună cu o extindere planificată. Zona curățată pentru extindere are peste 5 kilometri pătrați.

> 💁 Aceste centre de date necesită cantități foarte mari de energie, astfel încât unele au propriile stații de alimentare. Datorită dimensiunii lor și nivelului de investiție din partea furnizorilor de cloud, ele sunt de obicei foarte prietenoase cu mediul. Sunt mai eficiente decât un număr mare de centre de date mici, funcționează în mare parte pe energie regenerabilă, iar furnizorii de cloud depun eforturi pentru a reduce deșeurile, a diminua consumul de apă și a replanta păduri pentru a compensa cele tăiate pentru a face loc centrelor de date. Poți citi mai multe despre cum un furnizor de cloud lucrează la sustenabilitate pe [site-ul de sustenabilitate Azure](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Fă niște cercetări: Citește despre principalele servicii cloud, cum ar fi [Azure de la Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) sau [GCP de la Google](https://cloud.google.com). Câte centre de date au și unde sunt localizate în lume?

Utilizarea cloud-ului reduce costurile pentru companii și le permite să se concentreze pe ceea ce fac cel mai bine, lăsând expertiza în calcul cloud în mâinile furnizorului. Companiile nu mai trebuie să închirieze sau să cumpere spațiu pentru centre de date, să plătească diferiți furnizori pentru conectivitate și energie sau să angajeze experți. În schimb, pot plăti o singură factură lunară furnizorului de cloud pentru ca totul să fie gestionat.

Furnizorul de cloud poate apoi să folosească economiile de scară pentru a reduce costurile, achiziționând computere în cantități mari la costuri mai mici, investind în instrumente pentru a reduce volumul de muncă pentru întreținere, chiar proiectând și construind propriul hardware pentru a îmbunătăți oferta cloud.

### Microsoft Azure

Azure este cloud-ul pentru dezvoltatori de la Microsoft, și acesta este cloud-ul pe care îl vei folosi în aceste lecții. Videoclipul de mai jos oferă o scurtă prezentare a Azure:

[![Videoclip de prezentare Azure](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.ro.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Crearea unui abonament cloud

Pentru a utiliza servicii în cloud, va trebui să te înscrii pentru un abonament la un furnizor de cloud. Pentru această lecție, te vei înscrie pentru un abonament Microsoft Azure. Dacă ai deja un abonament Azure, poți sări peste această sarcină. Detaliile abonamentului descrise aici sunt corecte la momentul redactării, dar pot fi modificate.

> 💁 Dacă accesezi aceste lecții prin intermediul școlii tale, este posibil să ai deja un abonament Azure disponibil. Verifică cu profesorul tău.

Există două tipuri diferite de abonamente gratuite Azure la care te poți înscrie:

* **Azure pentru Studenți** - Acesta este un abonament conceput pentru studenți de 18+. Nu ai nevoie de un card de credit pentru a te înscrie și folosești adresa de e-mail a școlii pentru a valida că ești student. Când te înscrii, primești 100 USD pentru a cheltui pe resurse cloud, împreună cu servicii gratuite, inclusiv o versiune gratuită a unui serviciu IoT. Acesta durează 12 luni și poate fi reînnoit în fiecare an cât timp rămâi student.

* **Abonament gratuit Azure** - Acesta este un abonament pentru oricine nu este student. Va trebui să folosești un card de credit pentru a te înscrie, dar cardul nu va fi taxat, acesta este utilizat doar pentru a verifica că ești o persoană reală, nu un bot. Primești 200 USD credit pentru a utiliza în primele 30 de zile pe orice serviciu, împreună cu niveluri gratuite ale serviciilor Azure. După ce creditul tău a fost utilizat, cardul nu va fi taxat decât dacă convertești la un abonament cu plată pe măsură ce folosești.

> 💁 Microsoft oferă un abonament Azure pentru Studenți Starter pentru studenți sub 18 ani, dar la momentul redactării acestuia nu suportă servicii IoT.

### Sarcină - înscrierea pentru un abonament cloud gratuit

Dacă ești student cu vârsta de 18+, atunci te poți înscrie pentru un abonament Azure pentru Studenți. Va trebui să validezi cu o adresă de e-mail a școlii. Poți face acest lucru în două moduri:

* Înscrie-te pentru un pachet de dezvoltator GitHub pentru studenți la [education.github.com/pack](https://education.github.com/pack). Acesta îți oferă acces la o gamă de instrumente și oferte, inclusiv GitHub și Microsoft Azure. După ce te înscrii pentru pachetul de dezvoltator, poți activa oferta Azure pentru Studenți.

* Înscrie-te direct pentru un cont Azure pentru Studenți la [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Dacă adresa de e-mail a școlii tale nu este recunoscută, deschide o [problemă în acest repo](https://github.com/Microsoft/IoT-For-Beginners/issues) și vom vedea dacă poate fi adăugată la lista de permisiuni Azure pentru Studenți.

Dacă nu ești student sau nu ai o adresă de e-mail validă a școlii, atunci te poți înscrie pentru un abonament gratuit Azure.

* Înscrie-te pentru un abonament gratuit Azure la [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Servicii IoT în cloud

Brokerul MQTT public pe care l-ai utilizat este un instrument excelent pentru învățare, dar are o serie de dezavantaje ca instrument utilizat într-un mediu comercial:

* Fiabilitate - este un serviciu gratuit fără garanții și poate fi oprit în orice moment
* Securitate - este public, astfel încât oricine ar putea asculta telemetria sau trimite comenzi pentru a controla hardware-ul tău
* Performanță - este conceput pentru doar câteva mesaje de test, astfel încât nu ar face față unui volum mare de mesaje trimise
* Descoperire - nu există nicio modalitate de a ști ce dispozitive sunt conectate

Serviciile IoT în cloud rezolvă aceste probleme. Ele sunt întreținute de furnizori mari de cloud care investesc masiv în fiabilitate și sunt disponibili pentru a rezolva orice probleme care ar putea apărea. Au securitate integrată pentru a împiedica hackerii să citească datele tale sau să trimită comenzi neautorizate. De asemenea, sunt foarte performante, fiind capabile să gestioneze milioane de mesaje în fiecare zi, profitând de cloud pentru a se scala după necesități.

> 💁 Deși plătești pentru aceste avantaje cu o taxă lunară, majoritatea furnizorilor de cloud oferă o versiune gratuită a serviciului lor IoT cu un număr limitat de mesaje pe zi sau dispozitive care pot fi conectate. Această versiune gratuită este de obicei mai mult decât suficientă pentru ca un dezvoltator să învețe despre serviciu. În această lecție vei folosi o versiune gratuită.

Dispozitivele IoT se conectează la un serviciu cloud fie utilizând un SDK pentru dispozitive (o bibliotecă care oferă cod pentru a lucra cu funcțiile serviciului), fie direct printr-un protocol de comunicare precum MQTT sau HTTP. SDK-ul pentru dispozitive este de obicei cea mai ușoară cale, deoarece gestionează totul pentru tine, cum ar fi cunoașterea subiectelor de publicare sau abonare și modul de gestionare a securității.

![Dispozitivele se conectează la un serviciu folosind un SDK pentru dispozitive. Codul serverului se conectează de asemenea la serviciu printr-un SDK](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.ro.png)

Dispozitivul tău comunică apoi cu alte părți ale aplicației tale prin acest serviciu - similar cu modul în care ai trimis telemetria și ai primit comenzi prin MQTT. Acest lucru se face de obicei folosind un SDK pentru serviciu sau o bibliotecă similară. Mesajele vin de la dispozitivul tău către serviciu, unde alte componente ale aplicației tale le pot citi, iar mesajele pot fi trimise înapoi către dispozitivul tău.

![Dispozitivele fără o cheie secretă validă nu se pot conecta la serviciul IoT](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.ro.png)

Aceste servicii implementează securitatea prin cunoașterea tuturor dispozitivelor care pot fi conectate și pot trimite date, fie prin înregistrarea prealabilă a dispozitivelor în serviciu, fie prin oferirea dispozitivelor de chei secrete sau certificate pe care le pot folosi pentru a se înregistra singure în serviciu prima dată când se conectează. Dispozitivele necunoscute nu pot să se conecteze; dacă încearcă, serviciul respinge conexiunea și ignoră mesajele trimise de acestea.

✅ Fă niște cercetări: Care este dezavantajul unui serviciu IoT deschis, unde orice dispozitiv sau cod poate să se conecteze? Poți găsi exemple specifice de hackeri care au profitat de acest lucru?

Alte componente ale aplicației tale pot să se conecteze la serviciul IoT și să afle despre toate dispozitivele conectate sau înregistrate, comunicând cu ele direct, fie în masă, fie individual.
💁 Serviciile IoT implementează, de asemenea, capabilități suplimentare, iar furnizorii de cloud oferă servicii și aplicații adiționale care pot fi conectate la serviciu. De exemplu, dacă dorești să stochezi toate mesajele de telemetrie trimise de toate dispozitivele într-o bază de date, de obicei este nevoie doar de câteva clicuri în instrumentul de configurare al furnizorului de cloud pentru a conecta serviciul la o bază de date și a transmite datele.
## Creează un serviciu IoT în cloud

Acum că ai un abonament Azure, te poți înscrie pentru un serviciu IoT. Serviciul IoT de la Microsoft se numește Azure IoT Hub.

![Logo-ul Azure IoT Hub](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.ro.png)

Videoclipul de mai jos oferă o scurtă prezentare generală a Azure IoT Hub:

[![Videoclip de prezentare a Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Fă clic pe imaginea de mai sus pentru a urmări videoclipul

✅ Alocă-ți un moment pentru a face cercetări și a citi prezentarea generală a IoT Hub în [documentația Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Serviciile cloud disponibile în Azure pot fi configurate printr-un portal web sau printr-o interfață de linie de comandă (CLI). Pentru această sarcină, vei folosi CLI.

### Sarcină - instalează Azure CLI

Pentru a utiliza Azure CLI, trebuie mai întâi să fie instalat pe PC-ul sau Mac-ul tău.

1. Urmează instrucțiunile din [documentația Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) pentru a instala CLI.

1. Azure CLI acceptă o serie de extensii care adaugă capabilități pentru a gestiona o gamă largă de servicii Azure. Instalează extensia IoT rulând următoarea comandă din linia ta de comandă sau terminal:

    ```sh
    az extension add --name azure-iot
    ```

1. Din linia ta de comandă sau terminal, rulează următoarea comandă pentru a te conecta la abonamentul tău Azure din Azure CLI.

    ```sh
    az login
    ```

    Se va deschide o pagină web în browserul tău implicit. Conectează-te folosind contul pe care l-ai utilizat pentru a te înscrie la abonamentul Azure. După ce te-ai conectat, poți închide fila browserului.

1. Dacă ai mai multe abonamente Azure, cum ar fi unul oferit de școală și unul propriu pentru Azure for Students, va trebui să selectezi pe cel pe care dorești să-l utilizezi. Rulează următoarea comandă pentru a lista toate abonamentele la care ai acces:

    ```sh
    az account list --output table
    ```

    În rezultatul afișat, vei vedea numele fiecărui abonament împreună cu `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Pentru a selecta abonamentul pe care dorești să-l utilizezi, folosește următoarea comandă:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Înlocuiește `<SubscriptionId>` cu ID-ul abonamentului pe care dorești să-l utilizezi. După ce rulezi această comandă, rulează din nou comanda pentru a lista conturile tale. Vei vedea că coloana `IsDefault` va fi marcată ca `True` pentru abonamentul pe care tocmai l-ai setat.

### Sarcină - creează un grup de resurse

Serviciile Azure, cum ar fi instanțele IoT Hub, mașinile virtuale, bazele de date sau serviciile AI, sunt denumite **resurse**. Fiecare resursă trebuie să existe într-un **grup de resurse**, o grupare logică a uneia sau mai multor resurse.

> 💁 Utilizarea grupurilor de resurse îți permite să gestionezi mai multe servicii simultan. De exemplu, odată ce ai terminat toate lecțiile pentru acest proiect, poți șterge grupul de resurse, iar toate resursele din el vor fi șterse automat.

1. Există mai multe centre de date Azure în întreaga lume, împărțite pe regiuni. Când creezi o resursă sau un grup de resurse Azure, trebuie să specifici unde dorești să fie creat. Rulează următoarea comandă pentru a obține lista locațiilor:

    ```sh
    az account list-locations --output table
    ```

    Vei vedea o listă de locații. Această listă va fi lungă.

    > 💁 La momentul redactării, există 65 de locații în care poți implementa resurse.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Notează valoarea din coloana `Name` a regiunii celei mai apropiate de tine. Poți găsi regiunile pe o hartă pe [pagina Azure geographies](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Rulează următoarea comandă pentru a crea un grup de resurse numit `soil-moisture-sensor`. Numele grupurilor de resurse trebuie să fie unice în abonamentul tău.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Înlocuiește `<location>` cu locația pe care ai selectat-o în pasul anterior.

### Sarcină - creează un IoT Hub

Acum poți crea o resursă IoT Hub în grupul tău de resurse.

1. Folosește următoarea comandă pentru a crea resursa IoT Hub:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu un nume pentru hub-ul tău. Acest nume trebuie să fie unic la nivel global - adică niciun alt IoT Hub creat de altcineva nu poate avea același nume. Acest nume este utilizat într-un URL care indică hub-ul, așa că trebuie să fie unic. Folosește ceva de genul `soil-moisture-sensor-` și adaugă un identificator unic la final, cum ar fi câteva cuvinte aleatorii sau numele tău.

    Opțiunea `--sku F1` indică utilizarea unui nivel gratuit. Nivelul gratuit acceptă 8.000 de mesaje pe zi, împreună cu majoritatea funcțiilor nivelurilor cu preț complet.

    > 🎓 Diferitele niveluri de preț ale serviciilor Azure sunt denumite niveluri. Fiecare nivel are un cost diferit și oferă funcții sau volume de date diferite.

    > 💁 Dacă dorești să afli mai multe despre prețuri, poți consulta [ghidul de prețuri pentru Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Opțiunea `--partition-count 2` definește câte fluxuri de date acceptă IoT Hub, mai multe partiții reduc blocajele de date atunci când mai multe dispozitive citesc și scriu în IoT Hub. Partițiile sunt în afara scopului acestor lecții, dar această valoare trebuie setată pentru a crea un IoT Hub de nivel gratuit.

    > 💁 Poți avea doar un singur IoT Hub de nivel gratuit per abonament.

IoT Hub va fi creat. Acest proces poate dura un minut sau două pentru a se finaliza.

## Comunică cu IoT Hub

În lecția anterioară, ai utilizat MQTT și ai trimis mesaje înainte și înapoi pe diferite subiecte, fiecare subiect având scopuri diferite. În loc să trimiți mesaje pe subiecte diferite, IoT Hub are mai multe moduri definite prin care dispozitivul poate comunica cu Hub-ul sau Hub-ul cu dispozitivul.

> 💁 În culise, această comunicare între IoT Hub și dispozitivul tău poate utiliza MQTT, HTTPS sau AMQP.

* Mesaje de la dispozitiv la cloud (D2C) - acestea sunt mesaje trimise de un dispozitiv către IoT Hub, cum ar fi telemetria. Acestea pot fi apoi citite din IoT Hub de codul aplicației tale.

    > 🎓 În culise, IoT Hub utilizează un serviciu Azure numit [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Când scrii cod pentru a citi mesajele trimise către hub, acestea sunt adesea numite evenimente.

* Mesaje de la cloud la dispozitiv (C2D) - acestea sunt mesaje trimise de codul aplicației, printr-un IoT Hub, către un dispozitiv IoT.

* Cereri de metode directe - acestea sunt mesaje trimise de codul aplicației printr-un IoT Hub către un dispozitiv IoT pentru a solicita ca dispozitivul să facă ceva, cum ar fi controlul unui actuator. Aceste mesaje necesită un răspuns, astfel încât codul aplicației tale să poată verifica dacă au fost procesate cu succes.

* Device twins - acestea sunt documente JSON păstrate sincronizate între dispozitiv și IoT Hub și sunt utilizate pentru a stoca setări sau alte proprietăți raportate de dispozitiv sau care ar trebui setate pe dispozitiv (cunoscute ca dorite) de IoT Hub.

IoT Hub poate stoca mesaje și cereri de metode directe pentru o perioadă configurabilă de timp (implicit o zi), astfel încât dacă un dispozitiv sau codul aplicației pierde conexiunea, poate totuși să recupereze mesajele trimise în timp ce era offline după ce se reconectează. Device twins sunt păstrate permanent în IoT Hub, astfel încât în orice moment un dispozitiv se poate reconecta și obține cel mai recent device twin.

✅ Fă cercetări: Citește mai multe despre aceste tipuri de mesaje în [Ghidul de comunicare de la dispozitiv la cloud](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) și [Ghidul de comunicare de la cloud la dispozitiv](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) din documentația IoT Hub.

## Conectează dispozitivul tău la serviciul IoT

Odată ce hub-ul este creat, dispozitivul tău IoT se poate conecta la acesta. Doar dispozitivele înregistrate pot să se conecteze la un serviciu, așa că va trebui să îți înregistrezi dispozitivul mai întâi. Când te înregistrezi, vei primi un connection string pe care dispozitivul îl poate utiliza pentru a se conecta. Acest connection string este specific dispozitivului și conține informații despre IoT Hub, dispozitiv și o cheie secretă care va permite acestui dispozitiv să se conecteze.

> 🎓 Un connection string este un termen generic pentru un text care conține detalii de conexiune. Acestea sunt utilizate pentru conectarea la IoT Hub, baze de date și multe alte servicii. De obicei, constau într-un identificator pentru serviciu, cum ar fi un URL, și informații de securitate, cum ar fi o cheie secretă. Acestea sunt transmise SDK-urilor pentru a se conecta la serviciu.

> ⚠️ Connection strings trebuie păstrate în siguranță! Securitatea va fi acoperită în detaliu într-o lecție viitoare.

### Sarcină - înregistrează dispozitivul IoT

Dispozitivul IoT poate fi înregistrat cu IoT Hub utilizând Azure CLI.

1. Rulează următoarea comandă pentru a înregistra un dispozitiv:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu numele pe care l-ai utilizat pentru IoT Hub.

    Aceasta va crea un dispozitiv cu un ID de `soil-moisture-sensor`.

1. Când dispozitivul tău IoT se conectează la IoT Hub utilizând SDK-ul, trebuie să utilizeze un connection string care oferă URL-ul hub-ului, împreună cu o cheie secretă. Rulează următoarea comandă pentru a obține connection string-ul:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu numele pe care l-ai utilizat pentru IoT Hub.

1. Stochează connection string-ul afișat în output, deoarece vei avea nevoie de el mai târziu.

### Sarcină - conectează dispozitivul IoT la cloud

Parcurge ghidul relevant pentru a conecta dispozitivul IoT la cloud:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-connect-hub.md)

### Sarcină - monitorizează evenimentele

Deocamdată, nu vei actualiza codul serverului. În schimb, poți utiliza Azure CLI pentru a monitoriza evenimentele de la dispozitivul IoT.

1. Asigură-te că dispozitivul IoT funcționează și trimite valori de telemetrie pentru umiditatea solului.

1. Rulează următoarea comandă în promptul de comandă sau terminal pentru a monitoriza mesajele trimise către IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu numele pe care l-ai utilizat pentru IoT Hub.

    Vei vedea mesaje apărând în output-ul consolei pe măsură ce sunt trimise de dispozitivul IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Conținutul `payload` va corespunde mesajului trimis de dispozitivul IoT.

    > La momentul redactării, extensia `az iot` nu funcționează complet pe dispozitivele Apple Silicon. Dacă utilizezi un dispozitiv Apple Silicon, va trebui să monitorizezi mesajele într-un alt mod, cum ar fi utilizând [Azure IoT Tools pentru Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Aceste mesaje au mai multe proprietăți atașate automat, cum ar fi timestamp-ul la care au fost trimise. Acestea sunt cunoscute sub numele de *anotări*. Pentru a vizualiza toate anotările mesajelor, utilizează următoarea comandă:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu numele pe care l-ai utilizat pentru IoT Hub.

    Vei vedea mesaje apărând în output-ul consolei pe măsură ce sunt trimise de dispozitivul IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Valorile de timp din anotări sunt în [timp UNIX](https://wikipedia.org/wiki/Unix_time), reprezentând numărul de secunde de la miezul nopții din 1<sup>ianuarie</sup> 1970.

    Ieși din monitorul de evenimente când ai terminat.

### Sarcină - controlează dispozitivul IoT

De asemenea, poți utiliza Azure CLI pentru a apela metode directe pe dispozitivul IoT.

1. Rulează următoarea comandă în promptul de comandă sau terminal pentru a invoca metoda `relay_on` pe dispozitivul IoT:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Înlocuiește `
<hub_name>
` cu numele pe care l-ai folosit pentru IoT Hub.

    Aceasta trimite o cerere de metodă directă pentru metoda specificată prin `method-name`. Metodele directe pot primi o sarcină utilă care conține date pentru metodă, iar aceasta poate fi specificată în parametrul `method-payload` sub formă de JSON.

    Vei vedea releul pornind și ieșirea corespunzătoare de la dispozitivul tău IoT:

    ```output
    Direct method received -  relay_on
    ```

1. Repetă pasul de mai sus, dar setează `--method-name` la `relay_off`. Vei vedea releul oprindu-se și ieșirea corespunzătoare de la dispozitivul IoT.

---

## 🚀 Provocare

Nivelul gratuit al IoT Hub permite 8.000 de mesaje pe zi. Codul pe care l-ai scris trimite mesaje de telemetrie la fiecare 10 secunde. Câte mesaje pe zi înseamnă un mesaj la fiecare 10 secunde?

Gândește-te cât de des ar trebui trimise măsurătorile de umiditate a solului. Cum poți modifica codul pentru a rămâne în limita nivelului gratuit și pentru a verifica cât de des este necesar, dar nu prea des? Ce s-ar întâmpla dacă ai dori să adaugi un al doilea dispozitiv?

## Chestionar post-lectură

[Chestionar post-lectură](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Recapitulare și studiu individual

SDK-ul IoT Hub este open source atât pentru Arduino, cât și pentru Python. În depozitele de cod de pe GitHub există o serie de exemple care arată cum să lucrezi cu diferite funcții ale IoT Hub.

* Dacă folosești un Wio Terminal, verifică [exemplele Arduino pe GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Dacă folosești un Raspberry Pi sau un dispozitiv virtual, verifică [exemplele Python pe GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Temă

[Află despre serviciile cloud](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.