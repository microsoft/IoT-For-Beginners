# Conectează dispozitivul tău la Internet

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-4.7344e074ea68fa54.webp)

> Schiță realizată de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

Această lecție a fost predată ca parte a [seriei Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) de la [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lecția a fost predată în 2 videoclipuri - o lecție de o oră și o sesiune de o oră pentru aprofundarea unor părți ale lecției și răspunsuri la întrebări.

[![Lecția 4: Conectează dispozitivul tău la Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lecția 4: Conectează dispozitivul tău la Internet - Sesiune de întrebări](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Click pe imaginile de mai sus pentru a viziona videoclipurile

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introducere

Litera **I** din IoT reprezintă **Internet** - conectivitatea cloud și serviciile care permit multe dintre funcțiile dispozitivelor IoT, de la colectarea măsurătorilor de la senzorii conectați la dispozitiv, până la trimiterea de mesaje pentru a controla actuatoarele. Dispozitivele IoT se conectează de obicei la un singur serviciu cloud IoT folosind un protocol de comunicare standard, iar acel serviciu este conectat la restul aplicației IoT, de la servicii AI pentru a lua decizii inteligente pe baza datelor, până la aplicații web pentru control sau raportare.

> 🎓 Datele colectate de la senzori și trimise către cloud se numesc telemetrie.

Dispozitivele IoT pot primi mesaje de la cloud. Adesea, aceste mesaje conțin comenzi - adică instrucțiuni pentru a efectua o acțiune fie intern (cum ar fi repornirea sau actualizarea firmware-ului), fie folosind un actuator (cum ar fi aprinderea unei lumini).

Această lecție introduce câteva dintre protocoalele de comunicare pe care dispozitivele IoT le pot folosi pentru a se conecta la cloud și tipurile de date pe care le-ar putea trimite sau primi. Vei avea, de asemenea, ocazia să experimentezi cu acestea, adăugând control prin internet la lampa ta de noapte, mutând logica de control al LED-ului în codul 'server' care rulează local.

În această lecție vom acoperi:

* [Protocoale de comunicare](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetrie](../../../../../1-getting-started/lessons/4-connect-internet)
* [Comenzi](../../../../../1-getting-started/lessons/4-connect-internet)

## Protocoale de comunicare

Există o serie de protocoale de comunicare populare utilizate de dispozitivele IoT pentru a comunica cu Internetul. Cele mai populare sunt bazate pe mesageria de tip publicare/abonare prin intermediul unui broker. Dispozitivele IoT se conectează la broker și publică telemetrie și se abonează la comenzi. Serviciile cloud se conectează, de asemenea, la broker și se abonează la toate mesajele de telemetrie și publică comenzi fie către dispozitive specifice, fie către grupuri de dispozitive.

![Dispozitivele IoT se conectează la un broker și publică telemetrie și se abonează la comenzi. Serviciile cloud se conectează la broker și se abonează la toată telemetria și trimit comenzi către dispozitive specifice.](../../../../../translated_images/ro/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT este cel mai popular protocol de comunicare pentru dispozitivele IoT și este acoperit în această lecție. Alte protocoale includ AMQP și HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) este un protocol de mesagerie ușor, standard deschis, care poate trimite mesaje între dispozitive. A fost conceput în 1999 pentru monitorizarea conductelor de petrol, înainte de a fi lansat ca standard deschis 15 ani mai târziu de IBM.

MQTT are un singur broker și mai mulți clienți. Toți clienții se conectează la broker, iar brokerul direcționează mesajele către clienții relevanți. Mesajele sunt direcționate folosind subiecte denumite, mai degrabă decât să fie trimise direct unui client individual. Un client poate publica pe un subiect, iar orice client care se abonează la acel subiect va primi mesajul.

![Dispozitiv IoT care publică telemetrie pe subiectul /telemetry, iar serviciul cloud se abonează la acel subiect](../../../../../translated_images/ro/mqtt.cbf7f21d9adc3e17.webp)

✅ Fă niște cercetări. Dacă ai multe dispozitive IoT, cum poți asigura că brokerul MQTT poate gestiona toate mesajele?

### Conectează dispozitivul IoT la MQTT

Prima parte a adăugării controlului prin Internet la lampa ta de noapte este conectarea acesteia la un broker MQTT.

#### Sarcină

Conectează dispozitivul tău la un broker MQTT.

În această parte a lecției, vei conecta lampa ta de noapte IoT la Internet pentru a permite controlul de la distanță. Mai târziu în această lecție, dispozitivul tău IoT va trimite un mesaj de telemetrie prin MQTT către un broker MQTT public cu nivelul de lumină, unde va fi preluat de un cod server pe care îl vei scrie. Acest cod va verifica nivelul de lumină și va trimite un mesaj de comandă înapoi către dispozitiv, spunându-i să aprindă sau să stingă LED-ul.

Un caz de utilizare real pentru o astfel de configurație ar putea fi colectarea datelor de la mai mulți senzori de lumină înainte de a decide să aprinzi luminile, într-o locație care are multe lumini, cum ar fi un stadion. Acest lucru ar putea împiedica aprinderea luminilor dacă doar un senzor este acoperit de nori sau de un pasăre, dar ceilalți senzori detectează suficientă lumină.

✅ Ce alte situații ar necesita evaluarea datelor de la mai mulți senzori înainte de a trimite comenzi?

În loc să te ocupi de complexitățile configurării unui broker MQTT ca parte a acestui exercițiu, poți folosi un server de test public care rulează [Eclipse Mosquitto](https://www.mosquitto.org), un broker MQTT open-source. Acest broker de test este disponibil public la [test.mosquitto.org](https://test.mosquitto.org) și nu necesită configurarea unui cont, ceea ce îl face un instrument excelent pentru testarea clienților și serverelor MQTT.

> 💁 Acest broker de test este public și nesecurizat. Oricine ar putea asculta ceea ce publici, așa că nu ar trebui utilizat cu date care trebuie păstrate private.

![Un diagramă de flux a exercițiului care arată nivelurile de lumină fiind citite și verificate, și LED-ul fiind controlat](../../../../../translated_images/ro/assignment-1-internet-flow.3256feab5f052fd2.webp)

Urmează pasul relevant de mai jos pentru a conecta dispozitivul tău la brokerul MQTT:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Computer cu o singură placă - Raspberry Pi/Dispozitiv IoT virtual](single-board-computer-mqtt.md)

### O privire mai profundă asupra MQTT

Subiectele pot avea o ierarhie, iar clienții se pot abona la diferite niveluri ale ierarhiei folosind caractere wildcard. De exemplu, poți trimite mesaje de telemetrie pentru temperatură pe subiectul `/telemetry/temperature` și mesaje de umiditate pe subiectul `/telemetry/humidity`, apoi în aplicația ta cloud te poți abona la subiectul `/telemetry/*` pentru a primi atât mesajele de telemetrie pentru temperatură, cât și cele pentru umiditate.

Mesajele pot fi trimise cu o calitate a serviciului (QoS), care determină garanția primirii mesajului.

* Cel mult o dată - mesajul este trimis doar o dată, iar clientul și brokerul nu iau măsuri suplimentare pentru a confirma livrarea (trimite și uită).
* Cel puțin o dată - mesajul este retrimis de către expeditor de mai multe ori până când se primește confirmarea (livrare confirmată).
* Exact o dată - expeditorul și receptorul se angajează într-un proces de confirmare în două etape pentru a se asigura că doar o copie a mesajului este primită (livrare garantată).

✅ Ce situații ar necesita un mesaj cu livrare garantată în loc de un mesaj de tip trimite și uită?

Deși numele este Message Queueing (inițialele din MQTT), protocolul nu suportă de fapt cozi de mesaje. Acest lucru înseamnă că, dacă un client se deconectează, apoi se reconectează, nu va primi mesajele trimise în timpul deconectării, cu excepția celor pe care le-a început deja să le proceseze folosind procesul QoS. Mesajele pot avea un flag de retenție setat pe ele. Dacă acest flag este setat, brokerul MQTT va stoca ultimul mesaj trimis pe un subiect cu acest flag și îl va trimite oricărui client care se abonează ulterior la subiect. În acest fel, clienții vor primi întotdeauna cel mai recent mesaj.

MQTT suportă, de asemenea, o funcție de menținere a conexiunii care verifică dacă conexiunea este încă activă în timpul pauzelor lungi între mesaje.

> 🦟 [Mosquitto de la Eclipse Foundation](https://mosquitto.org) are un broker MQTT gratuit pe care îl poți rula singur pentru a experimenta cu MQTT, împreună cu un broker MQTT public pe care îl poți folosi pentru a testa codul tău, găzduit la [test.mosquitto.org](https://test.mosquitto.org).

Conexiunile MQTT pot fi publice și deschise sau criptate și securizate folosind nume de utilizator și parole sau certificate.

> 💁 MQTT comunică prin TCP/IP, același protocol de rețea de bază ca HTTP, dar pe un port diferit. Poți folosi MQTT și prin websockets pentru a comunica cu aplicații web care rulează într-un browser sau în situații în care firewall-urile sau alte reguli de rețea blochează conexiunile MQTT standard.

## Telemetrie

Cuvântul telemetrie provine din rădăcini grecești care înseamnă a măsura de la distanță. Telemetria este actul de a colecta date de la senzori și de a le trimite către cloud.

> 💁 Unul dintre cele mai vechi dispozitive de telemetrie a fost inventat în Franța în 1874 și trimitea în timp real date despre vreme și adâncimea zăpezii de pe Mont Blanc către Paris. Folosea fire fizice, deoarece tehnologiile wireless nu erau disponibile la acea vreme.

Să ne uităm înapoi la exemplul termostatului inteligent din Lecția 1.

![Un termostat conectat la Internet folosind senzori multipli de cameră](../../../../../translated_images/ro/telemetry.21e5d8b97649d2eb.webp)

Termostatul are senzori de temperatură pentru a colecta telemetrie. Cel mai probabil ar avea un senzor de temperatură încorporat și s-ar putea conecta la mai mulți senzori de temperatură externi printr-un protocol wireless, cum ar fi [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Un exemplu de date de telemetrie pe care le-ar trimite ar putea fi:

| Nume | Valoare | Descriere |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Temperatura măsurată de senzorul de temperatură încorporat al termostatului |
| `livingroom_temperature` | 19°C | Temperatura măsurată de un senzor de temperatură extern care a fost denumit `livingroom` pentru a identifica camera în care se află |
| `bedroom_temperature` | 21°C | Temperatura măsurată de un senzor de temperatură extern care a fost denumit `bedroom` pentru a identifica camera în care se află |

Serviciul cloud poate apoi folosi aceste date de telemetrie pentru a lua decizii cu privire la ce comenzi să trimită pentru a controla încălzirea.

### Trimite telemetrie de la dispozitivul tău IoT

Următorul pas în adăugarea controlului prin Internet la lampa ta de noapte este trimiterea telemetriei nivelului de lumină către brokerul MQTT pe un subiect de telemetrie.

#### Sarcină - trimite telemetrie de la dispozitivul tău IoT

Trimite telemetrie a nivelului de lumină către brokerul MQTT.

Datele sunt trimise codificate ca JSON - prescurtare pentru JavaScript Object Notation, un standard pentru codificarea datelor în text folosind perechi cheie/valoare.

✅ Dacă nu ai întâlnit JSON până acum, poți afla mai multe despre el în [documentația JSON.org](https://www.json.org/).

Urmează pasul relevant de mai jos pentru a trimite telemetrie de la dispozitivul tău către brokerul MQTT:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Computer cu o singură placă - Raspberry Pi/Dispozitiv IoT virtual](single-board-computer-telemetry.md)

### Primește telemetrie de la brokerul MQTT

Nu are rost să trimiți telemetrie dacă nu există nimic la celălalt capăt care să o asculte. Telemetria nivelului de lumină are nevoie de ceva care să o asculte pentru a procesa datele. Acest cod 'server' este genul de cod pe care îl vei implementa într-un serviciu cloud ca parte a unei aplicații IoT mai mari, dar aici vei rula acest cod local pe computerul tău (sau pe Pi-ul tău dacă lucrezi direct pe acesta). Codul server constă într-o aplicație Python care ascultă mesajele de telemetrie prin MQTT cu niveluri de lumină. Mai târziu în această lecție, vei face ca aceasta să răspundă cu un mesaj de comandă cu instrucțiuni pentru a aprinde sau stinge LED-ul.

✅ Fă niște cercetări: Ce se întâmplă cu mesajele MQTT dacă nu există niciun ascultător?

#### Instalează Python și VS Code

Dacă nu ai Python și VS Code instalate local, va trebui să le instalezi pe ambele pentru a scrie codul server. Dacă folosești un dispozitiv IoT virtual sau lucrezi pe Raspberry Pi-ul tău, poți sări peste acest pas, deoarece ar trebui să fie deja instalate și configurate.

##### Sarcină - instalează Python și VS Code

Instalează Python și VS Code.

1. Instalează Python. Consultă [pagina de descărcări Python](https://www.python.org/downloads/) pentru instrucțiuni despre instalarea celei mai recente versiuni de Python.

1. Instalează Visual Studio Code (VS Code). Acesta este editorul pe care îl vei folosi pentru a scrie codul dispozitivului virtual în Python. Consultă [documentația VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pentru instrucțiuni despre instalarea VS Code.
💁 Ești liber să folosești orice IDE sau editor Python preferi pentru aceste lecții, dar instrucțiunile din lecții vor fi bazate pe utilizarea VS Code.
1. Instalează extensia Pylance pentru VS Code. Aceasta este o extensie pentru VS Code care oferă suport pentru limbajul Python. Consultă [documentația extensiei Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pentru instrucțiuni despre cum să instalezi această extensie în VS Code.

#### Configurează un mediu virtual Python

Unul dintre avantajele puternice ale Python este abilitatea de a instala [pachete pip](https://pypi.org) - acestea sunt pachete de cod scrise de alte persoane și publicate pe Internet. Poți instala un pachet pip pe computerul tău cu o singură comandă, apoi să folosești acel pachet în codul tău. Vei folosi pip pentru a instala un pachet care permite comunicarea prin MQTT.

În mod implicit, când instalezi un pachet, acesta este disponibil peste tot pe computerul tău, ceea ce poate duce la probleme cu versiunile pachetelor - de exemplu, o aplicație depinde de o versiune a unui pachet care se poate strica atunci când instalezi o versiune nouă pentru o altă aplicație. Pentru a evita această problemă, poți folosi un [mediu virtual Python](https://docs.python.org/3/library/venv.html), practic o copie a Python într-un folder dedicat, iar când instalezi pachete pip, acestea sunt instalate doar în acel folder.

##### Sarcină - configurează un mediu virtual Python

Configurează un mediu virtual Python și instalează pachetele pip pentru MQTT.

1. Din terminalul sau linia ta de comandă, rulează următoarele comenzi într-o locație la alegerea ta pentru a crea și naviga într-un nou director:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Acum rulează următoarea comandă pentru a crea un mediu virtual în folderul `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Trebuie să apelezi explicit `python3` pentru a crea mediul virtual, în cazul în care ai instalat și Python 2 pe lângă Python 3 (cea mai recentă versiune). Dacă ai instalat Python 2, atunci apelarea `python` va folosi Python 2 în loc de Python 3.

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

    > 💁 Aceste comenzi ar trebui să fie rulate din aceeași locație în care ai rulat comanda pentru a crea mediul virtual. Nu va trebui niciodată să navighezi în folderul `.venv`, ar trebui întotdeauna să rulezi comanda de activare și orice alte comenzi pentru a instala pachete sau a rula cod din folderul în care te aflai când ai creat mediul virtual.

1. Odată ce mediul virtual a fost activat, comanda implicită `python` va rula versiunea de Python care a fost folosită pentru a crea mediul virtual. Rulează următoarea comandă pentru a obține versiunea:

    ```sh
    python --version
    ```

    Rezultatul va fi similar cu următorul:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Versiunea ta de Python poate fi diferită - atâta timp cât este versiunea 3.6 sau mai mare, este în regulă. Dacă nu, șterge acest folder, instalează o versiune mai nouă de Python și încearcă din nou.

1. Rulează următoarele comenzi pentru a instala pachetul pip pentru [Paho-MQTT](https://pypi.org/project/paho-mqtt/), o bibliotecă populară pentru MQTT.

    ```sh
    pip install paho-mqtt
    ```

    Acest pachet pip va fi instalat doar în mediul virtual și nu va fi disponibil în afara acestuia.

#### Scrie codul serverului

Codul serverului poate fi acum scris în Python.

##### Sarcină - scrie codul serverului

Scrie codul serverului.

1. Din terminalul sau linia ta de comandă, rulează următoarele comenzi în interiorul mediului virtual pentru a crea un fișier Python numit `app.py`:

    * Pe Windows rulează:

        ```cmd
        type nul > app.py
        ```

    * Pe macOS sau Linux, rulează:

        ```cmd
        touch app.py
        ```

1. Deschide folderul curent în VS Code:

    ```sh
    code .
    ```

1. Când VS Code pornește, acesta va activa mediul virtual Python. Acest lucru va fi raportat în bara de stare de jos:

    ![VS Code arătând mediul virtual selectat](../../../../../translated_images/ro/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Dacă terminalul VS Code este deja pornit când VS Code se deschide, mediul virtual nu va fi activat în acesta. Cel mai simplu lucru de făcut este să închizi terminalul folosind butonul **Kill the active terminal instance**:

    ![Butonul VS Code Kill the active terminal instance](../../../../../translated_images/ro/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Lansează un nou terminal VS Code selectând *Terminal -> New Terminal*, sau apăsând `` CTRL+` ``. Noul terminal va încărca mediul virtual, cu apelul de activare apărând în terminal. Numele mediului virtual (`.venv`) va apărea și în prompt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Deschide fișierul `app.py` din exploratorul VS Code și adaugă următorul cod:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Înlocuiește `<ID>` de pe linia 6 cu ID-ul unic pe care l-ai folosit când ai creat codul dispozitivului.

    ⚠️ Acesta **trebuie** să fie același ID pe care l-ai folosit pe dispozitivul tău, altfel codul serverului nu se va abona sau publica pe topicul corect.

    Acest cod creează un client MQTT cu un nume unic și se conectează la brokerul *test.mosquitto.org*. Apoi pornește un ciclu de procesare care rulează pe un fir de execuție în fundal, ascultând mesajele de pe orice topicuri la care este abonat.

    Clientul se abonează apoi la mesajele de pe topicul de telemetrie și definește o funcție care este apelată când un mesaj este primit. Când un mesaj de telemetrie este primit, funcția `handle_telemetry` este apelată, afișând mesajul primit în consolă.

    În final, un ciclu infinit menține aplicația în funcțiune. Clientul MQTT ascultă mesajele pe un fir de execuție în fundal și rulează tot timpul cât aplicația principală este activă.

1. Din terminalul VS Code, rulează următoarea comandă pentru a rula aplicația Python:

    ```sh
    python app.py
    ```

    Aplicația va începe să asculte mesajele de la dispozitivul IoT.

1. Asigură-te că dispozitivul tău funcționează și trimite mesaje de telemetrie. Ajustează nivelurile de lumină detectate de dispozitivul tău fizic sau virtual. Mesajele primite vor fi afișate în terminal.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Fișierul `app.py` din mediul virtual nightlight trebuie să fie în execuție pentru ca fișierul `app.py` din mediul virtual nightlight-server să primească mesajele trimise.

> 💁 Poți găsi acest cod în folderul [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Cât de des ar trebui trimisă telemetria?

O considerație importantă pentru telemetrie este cât de des să măsori și să trimiți datele? Răspunsul este - depinde. Dacă măsori des, poți răspunde mai rapid la schimbări, dar folosești mai multă energie, mai multă lățime de bandă, generezi mai multe date și ai nevoie de mai multe resurse cloud pentru procesare. Trebuie să măsori suficient de des, dar nu prea des.

Pentru un termostat, măsurarea la câteva minute este probabil suficientă, deoarece temperaturile nu se schimbă atât de des. Dacă măsori doar o dată pe zi, ai putea ajunge să încălzești casa pentru temperaturile de noapte în mijlocul unei zile însorite, în timp ce dacă măsori în fiecare secundă vei avea mii de măsurători duplicate inutil care vor consuma viteza și lățimea de bandă a utilizatorilor (o problemă pentru cei cu planuri de lățime de bandă limitată), vor folosi mai multă energie, ceea ce poate fi o problemă pentru dispozitivele alimentate cu baterii, și vor crește costurile resurselor cloud pentru procesare și stocare.

Dacă monitorizezi datele unei mașinării dintr-o fabrică care, dacă se defectează, ar putea cauza daune catastrofale și pierderi de milioane de dolari, atunci măsurarea de mai multe ori pe secundă ar putea fi necesară. Este mai bine să consumi lățime de bandă decât să ratezi telemetria care indică faptul că o mașinărie trebuie oprită și reparată înainte să se strice.

> 💁 În această situație, ai putea lua în considerare utilizarea unui dispozitiv edge pentru a procesa mai întâi telemetria, reducând astfel dependența de Internet.

### Pierderea conectivității

Conexiunile la Internet pot fi nesigure, cu întreruperi frecvente. Ce ar trebui să facă un dispozitiv IoT în aceste circumstanțe - să piardă datele sau să le stocheze până când conectivitatea este restabilită? Din nou, răspunsul este că depinde.

Pentru un termostat, datele pot fi probabil pierdute imediat ce o nouă măsurătoare de temperatură a fost luată. Sistemul de încălzire nu este interesat că acum 20 de minute temperatura era de 20.5°C dacă acum este de 19°C, temperatura actuală determină dacă încălzirea ar trebui să fie pornită sau oprită.

Pentru mașinării, s-ar putea să vrei să păstrezi datele, mai ales dacă sunt folosite pentru a căuta tendințe. Există modele de învățare automată care pot detecta anomalii în fluxurile de date analizând datele dintr-o perioadă definită de timp (cum ar fi ultima oră) și identificând datele anormale. Acest lucru este adesea folosit pentru întreținerea predictivă, căutând indicii că ceva s-ar putea strica în curând, astfel încât să poți repara sau înlocui înainte să se întâmple. Ai putea dori ca fiecare bit de telemetrie pentru o mașinărie să fie trimis pentru a fi procesat pentru detectarea anomaliilor, astfel încât, odată ce dispozitivul IoT se poate reconecta, să trimită toată telemetria generată în timpul întreruperii Internetului.

Designerii dispozitivelor IoT ar trebui să ia în considerare, de asemenea, dacă dispozitivul IoT poate fi utilizat în timpul unei întreruperi a Internetului sau a pierderii semnalului cauzate de locație. Un termostat inteligent ar trebui să poată lua unele decizii limitate pentru a controla încălzirea dacă nu poate trimite telemetrie în cloud din cauza unei întreruperi.

[![Această mașină Ferrari a fost blocată pentru că cineva a încercat să o actualizeze sub pământ, unde nu există semnal](../../../../../translated_images/ro/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Pentru ca MQTT să gestioneze o pierdere de conectivitate, codul dispozitivului și al serverului va trebui să fie responsabil pentru asigurarea livrării mesajelor, dacă este necesar, de exemplu prin cerința ca toate mesajele trimise să fie răspunse prin mesaje suplimentare pe un topic de răspuns, iar dacă nu, acestea să fie puse în coadă manual pentru a fi retrimise mai târziu.

## Comenzi

Comenzile sunt mesaje trimise de cloud către un dispozitiv, instruindu-l să facă ceva. De cele mai multe ori, acest lucru implică oferirea unui fel de ieșire printr-un actuator, dar poate fi și o instrucțiune pentru dispozitivul în sine, cum ar fi să se repornească sau să colecteze telemetrie suplimentară și să o returneze ca răspuns la comandă.

![Un termostat conectat la Internet care primește o comandă pentru a porni încălzirea](../../../../../translated_images/ro/commands.d6c06bbbb3a02cce.webp)

Un termostat ar putea primi o comandă din cloud pentru a porni încălzirea. Pe baza datelor de telemetrie de la toți senzorii, dacă serviciul cloud a decis că încălzirea ar trebui să fie pornită, trimite comanda relevantă.

### Trimite comenzi către brokerul MQTT

Următorul pas pentru lampa noastră de noapte controlată prin Internet este ca codul serverului să trimită o comandă înapoi către dispozitivul IoT pentru a controla lumina pe baza nivelurilor de lumină detectate.

1. Deschide codul serverului în VS Code.

1. Adaugă următoarea linie după declarația `client_telemetry_topic` pentru a defini pe ce topic să trimiți comenzi:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Adaugă următorul cod la sfârșitul funcției `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Acesta trimite un mesaj JSON pe topicul de comandă cu valoarea `led_on` setată la true sau false, în funcție de dacă lumina este mai mică de 300 sau nu. Dacă lumina este mai mică de 300, se trimite true pentru a instrui dispozitivul să aprindă LED-ul.

1. Rulează codul ca înainte.

1. Ajustează nivelurile de lumină detectate de dispozitivul tău fizic sau virtual. Mesajele primite și comenzile trimise vor fi afișate în terminal:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetria și comenzile sunt trimise pe un singur topic fiecare. Aceasta înseamnă că telemetria de la mai multe dispozitive va apărea pe același topic de telemetrie, iar comenzile către mai multe dispozitive vor apărea pe același topic de comenzi. Dacă dorești să trimiți o comandă către un dispozitiv specific, ai putea folosi mai multe topicuri, denumite cu un ID unic al dispozitivului, cum ar fi `/commands/device1`, `/commands/device2`. În acest fel, un dispozitiv poate asculta doar mesajele destinate acelui dispozitiv.

> 💁 Poți găsi acest cod în folderul [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Gestionează comenzile pe dispozitivul IoT

Acum că comenzile sunt trimise de la server, poți adăuga cod pe dispozitivul IoT pentru a le gestiona și a controla LED-ul.

Urmează pasul relevant de mai jos pentru a asculta comenzile de la brokerul MQTT:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Single-board computer - Raspberry Pi/Dispozitiv IoT virtual](single-board-computer-commands.md)

Odată ce acest cod este scris și în execuție, experimentează schimbând nivelurile de lumină. Urmărește ieșirea de la server și dispozitiv și observă LED-ul pe măsură ce schimbi nivelurile de lumină.

### Pierderea conectivității

Ce ar trebui să facă un serviciu cloud dacă trebuie să trimită o comandă către un dispozitiv IoT care este offline? Din nou, răspunsul este că depinde.

Dacă cea mai recentă comandă suprascrie una anterioară, atunci cele anterioare pot fi probabil ignorate. Dacă un serviciu cloud trimite o comandă pentru a porni încălzirea, apoi trimite o comandă pentru a o opri, atunci comanda de pornire poate fi ignorată și nu trebuie retrimisă.

Dacă comenzile trebuie procesate în secvență, cum ar fi mișcarea unui braț robotic în sus, apoi închiderea unui dispozitiv de prindere, atunci acestea trebuie trimise în ordine odată ce conectivitatea este restabilită.

✅ Cum ar putea codul dispozitivului sau al serverului să asigure că comenzile sunt întotdeauna trimise și gestionate în ordine prin MQTT, dacă este necesar?

---

## 🚀 Provocare

Provocarea din ultimele trei lecții a fost să enumeri cât mai multe dispozitive IoT pe care le ai acasă, la școală sau la locul de muncă și să decizi dacă sunt construite în jurul microcontrolerelor sau al calculatoarelor pe o singură placă, sau chiar o combinație a acestora, și să te gândești la ce senzori și actuatori folosesc.
Pentru aceste dispozitive, gândește-te la ce mesaje ar putea trimite sau primi. Ce telemetrie trimit? Ce mesaje sau comenzi ar putea primi? Crezi că sunt securizate?

## Chestionar de după curs

[Chestionar de după curs](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Recapitulare și Studiu Individual

Citește mai multe despre MQTT pe [pagina Wikipedia MQTT](https://wikipedia.org/wiki/MQTT).

Încearcă să rulezi un broker MQTT pe cont propriu folosind [Mosquitto](https://www.mosquitto.org) și conectează-te la acesta de pe dispozitivul tău IoT și din codul serverului.

> 💁 Sfat - implicit, Mosquitto nu permite conexiuni anonime (adică fără un nume de utilizator și o parolă) și nu permite conexiuni din afara calculatorului pe care rulează.
> Poți rezolva acest lucru cu un [fișier de configurare `mosquitto.conf`](https://www.mosquitto.org/man/mosquitto-conf-5.html) care conține următoarele:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Temă

[Compară și contrastează MQTT cu alte protocoale de comunicare](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.