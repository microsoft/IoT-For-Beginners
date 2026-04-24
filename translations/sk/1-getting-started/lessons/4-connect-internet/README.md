# Pripojte svoje zariadenie k internetu

![Prehľad lekcie v sketchnote](../../../../../translated_images/sk/lesson-4.7344e074ea68fa54.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

Táto lekcia bola súčasťou série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) z [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcia bola prezentovaná vo forme dvoch videí - hodinovej lekcie a hodinového office hour, kde sa podrobnejšie rozoberali časti lekcie a odpovedali na otázky.

[![Lekcia 4: Pripojte svoje zariadenie k internetu](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lekcia 4: Pripojte svoje zariadenie k internetu - Office hours](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Kliknite na obrázky vyššie, aby ste si pozreli videá

## Kvíz pred lekciou

[Kvíz pred lekciou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Úvod

**I** v IoT znamená **Internet** - cloudová konektivita a služby, ktoré umožňujú mnohé funkcie IoT zariadení, od zhromažďovania meraní zo senzorov pripojených k zariadeniu až po odosielanie správ na ovládanie akčných členov. IoT zariadenia sa zvyčajne pripájajú k jednej cloudovej IoT službe pomocou štandardného komunikačného protokolu, a táto služba je prepojená so zvyškom vašej IoT aplikácie, od AI služieb na inteligentné rozhodovanie na základe vašich údajov až po webové aplikácie na ovládanie alebo reportovanie.

> 🎓 Údaje zhromaždené zo senzorov a odoslané do cloudu sa nazývajú telemetria.

IoT zariadenia môžu prijímať správy z cloudu. Často tieto správy obsahujú príkazy - inštrukcie na vykonanie akcie buď interne (napríklad reštart alebo aktualizácia firmvéru), alebo pomocou akčného člena (napríklad zapnutie svetla).

Táto lekcia predstavuje niektoré komunikačné protokoly, ktoré IoT zariadenia môžu používať na pripojenie k cloudu, a typy údajov, ktoré môžu odosielať alebo prijímať. Získate tiež praktické skúsenosti s oboma, pridáte internetové ovládanie k svojmu nočnému svetlu a presuniete logiku ovládania LED do 'serverového' kódu, ktorý bude bežať lokálne.

V tejto lekcii sa budeme venovať:

* [Komunikačné protokoly](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetria](../../../../../1-getting-started/lessons/4-connect-internet)
* [Príkazy](../../../../../1-getting-started/lessons/4-connect-internet)

## Komunikačné protokoly

Existuje množstvo populárnych komunikačných protokolov, ktoré IoT zariadenia používajú na komunikáciu s internetom. Najpopulárnejšie sú založené na publikovaní/odoberaní správ prostredníctvom nejakého sprostredkovateľa. IoT zariadenia sa pripájajú k sprostredkovateľovi, publikujú telemetriu a odoberajú príkazy. Cloudové služby sa tiež pripájajú k sprostredkovateľovi, odoberajú všetky telemetrické správy a publikujú príkazy buď konkrétnym zariadeniam, alebo skupinám zariadení.

![IoT zariadenia sa pripájajú k sprostredkovateľovi, publikujú telemetriu a odoberajú príkazy. Cloudové služby sa pripájajú k sprostredkovateľovi, odoberajú všetku telemetriu a posielajú príkazy konkrétnym zariadeniam.](../../../../../translated_images/sk/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT je najpopulárnejší komunikačný protokol pre IoT zariadenia a je pokrytý v tejto lekcii. Medzi ďalšie protokoly patrí AMQP a HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) je ľahký, otvorený štandard pre zasielanie správ medzi zariadeniami. Bol navrhnutý v roku 1999 na monitorovanie ropovodov, a o 15 rokov neskôr bol uvoľnený ako otvorený štandard spoločnosťou IBM.

MQTT má jedného sprostredkovateľa a viacero klientov. Všetci klienti sa pripájajú k sprostredkovateľovi, a ten smeruje správy relevantným klientom. Správy sú smerované pomocou pomenovaných tém, namiesto priameho zasielania konkrétnemu klientovi. Klient môže publikovať do témy, a všetci klienti, ktorí odoberajú túto tému, dostanú správu.

![IoT zariadenie publikujúce telemetriu na tému /telemetry, a cloudová služba odoberajúca túto tému](../../../../../translated_images/sk/mqtt.cbf7f21d9adc3e17.webp)

✅ Urobte si prieskum. Ak máte veľa IoT zariadení, ako môžete zabezpečiť, že váš MQTT sprostredkovateľ zvládne všetky správy?

### Pripojte svoje IoT zariadenie k MQTT

Prvým krokom pri pridávaní internetového ovládania k vášmu nočnému svetlu je pripojenie k MQTT sprostredkovateľovi.

#### Úloha

Pripojte svoje zariadenie k MQTT sprostredkovateľovi.

V tejto časti lekcie pripojíte svoje IoT nočné svetlo k internetu, aby mohlo byť ovládané na diaľku. Neskôr v tejto lekcii vaše IoT zariadenie odošle telemetrickú správu cez MQTT na verejný MQTT sprostredkovateľ s úrovňou svetla, kde ju zachytí serverový kód, ktorý napíšete. Tento kód skontroluje úroveň svetla a odošle príkazovú správu späť zariadeniu, ktorá mu povie, aby zaplo alebo vyplo LED.

Reálny prípad použitia takéhoto nastavenia by mohol byť zhromažďovanie údajov z viacerých svetelných senzorov pred rozhodnutím o zapnutí svetiel na mieste, kde je veľa svetiel, napríklad na štadióne. To by mohlo zabrániť zapnutiu svetiel, ak by iba jeden senzor bol zakrytý oblakmi alebo vtákom, ale ostatné senzory by detekovali dostatok svetla.

✅ Aké iné situácie by vyžadovali vyhodnotenie údajov z viacerých senzorov pred odoslaním príkazov?

Namiesto riešenia zložitostí nastavenia MQTT sprostredkovateľa ako súčasť tejto úlohy môžete použiť verejný testovací server, ktorý beží na [Eclipse Mosquitto](https://www.mosquitto.org), open-source MQTT sprostredkovateľ. Tento testovací sprostredkovateľ je verejne dostupný na [test.mosquitto.org](https://test.mosquitto.org) a nevyžaduje nastavenie účtu, čo z neho robí skvelý nástroj na testovanie MQTT klientov a serverov.

> 💁 Tento testovací sprostredkovateľ je verejný a nie je zabezpečený. Ktokoľvek môže počúvať, čo publikujete, takže by sa nemal používať na žiadne údaje, ktoré musia zostať súkromné.

![Diagram úlohy zobrazujúci čítanie a kontrolu úrovní svetla a ovládanie LED](../../../../../translated_images/sk/assignment-1-internet-flow.3256feab5f052fd2.webp)

Postupujte podľa relevantného kroku nižšie, aby ste pripojili svoje zariadenie k MQTT sprostredkovateľovi:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Jednodoskový počítač - Raspberry Pi/virtuálne IoT zariadenie](single-board-computer-mqtt.md)

### Hlbší pohľad na MQTT

Témy môžu mať hierarchiu a klienti môžu odoberať rôzne úrovne hierarchie pomocou zástupných znakov. Napríklad môžete posielať telemetrické správy o teplote na tému `/telemetry/temperature` a správy o vlhkosti na tému `/telemetry/humidity`, a potom vo svojej cloudovej aplikácii odoberať tému `/telemetry/*`, aby ste dostali správy o teplote aj vlhkosti.

Správy môžu byť odosielané s kvalitou služby (QoS), ktorá určuje záruku prijatia správy.

* Najviac raz - správa je odoslaná iba raz a klient a sprostredkovateľ nepodnikajú žiadne ďalšie kroky na potvrdenie doručenia (odoslať a zabudnúť).
* Aspoň raz - správa je opakovane odosielaná odosielateľom, kým nie je prijaté potvrdenie (potvrdené doručenie).
* Presne raz - odosielateľ a prijímateľ sa zapoja do dvojúrovňového handshake procesu, aby zabezpečili, že bude prijatá iba jedna kópia správy (zaručené doručenie).

✅ Aké situácie by vyžadovali zaručené doručenie správy namiesto odoslania a zabudnutia?

Hoci názov je Message Queueing (MQTT), v skutočnosti nepodporuje fronty správ. To znamená, že ak sa klient odpojí a potom znova pripojí, nedostane správy odoslané počas odpojenia, okrem tých, ktoré už začal spracovávať pomocou QoS procesu. Správy môžu mať nastavenú vlajku "retained". Ak je táto vlajka nastavená, MQTT sprostredkovateľ uloží poslednú správu odoslanú na tému s touto vlajkou a pošle ju každému klientovi, ktorý sa neskôr prihlási na odber tejto témy. Týmto spôsobom klienti vždy dostanú najnovšiu správu.

MQTT tiež podporuje funkciu "keep alive", ktorá kontroluje, či je pripojenie stále aktívne počas dlhých medzier medzi správami.

> 🦟 [Mosquitto od Eclipse Foundation](https://mosquitto.org) má bezplatný MQTT sprostredkovateľ, ktorý si môžete sami spustiť na experimentovanie s MQTT, spolu s verejným MQTT sprostredkovateľom, ktorý môžete použiť na testovanie svojho kódu, hostovaným na [test.mosquitto.org](https://test.mosquitto.org).

MQTT pripojenia môžu byť verejné a otvorené, alebo šifrované a zabezpečené pomocou používateľských mien a hesiel, alebo certifikátov.

> 💁 MQTT komunikuje cez TCP/IP, rovnaký základný sieťový protokol ako HTTP, ale na inom porte. Môžete tiež používať MQTT cez websockets na komunikáciu s webovými aplikáciami bežiacimi v prehliadači, alebo v situáciách, kde firewally alebo iné sieťové pravidlá blokujú štandardné MQTT pripojenia.

## Telemetria

Slovo telemetria pochádza z gréckych koreňov a znamená merať na diaľku. Telemetria je akt zhromažďovania údajov zo senzorov a ich odosielania do cloudu.

> 💁 Jedno z prvých telemetrických zariadení bolo vynájdené vo Francúzsku v roku 1874 a posielalo aktuálne údaje o počasí a hĺbke snehu z Mont Blancu do Paríža. Používalo fyzické drôty, pretože bezdrôtové technológie v tom čase neboli dostupné.

Pozrime sa späť na príklad inteligentného termostatu z Lekcie 1.

![Internetový termostat používajúci viaceré senzory v miestnostiach](../../../../../translated_images/sk/telemetry.21e5d8b97649d2eb.webp)

Termostat má teplotné senzory na zhromažďovanie telemetrie. Pravdepodobne by mal jeden teplotný senzor zabudovaný, a mohol by sa pripojiť k viacerým externým teplotným senzorom cez bezdrôtový protokol, ako je [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Príklad telemetrických údajov, ktoré by mohol odosielať, by mohol byť:

| Názov | Hodnota | Popis |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Teplota nameraná zabudovaným teplotným senzorom termostatu |
| `livingroom_temperature` | 19°C | Teplota nameraná vzdialeným teplotným senzorom, ktorý bol pomenovaný `livingroom`, aby identifikoval miestnosť, v ktorej sa nachádza |
| `bedroom_temperature` | 21°C | Teplota nameraná vzdialeným teplotným senzorom, ktorý bol pomenovaný `bedroom`, aby identifikoval miestnosť, v ktorej sa nachádza |

Cloudová služba potom môže použiť tieto telemetrické údaje na rozhodovanie o tom, aké príkazy poslať na ovládanie kúrenia.

### Odosielanie telemetrie z vášho IoT zariadenia

Ďalším krokom pri pridávaní internetového ovládania k vášmu nočnému svetlu je odosielanie telemetrie úrovne svetla na MQTT sprostredkovateľa na telemetrickú tému.

#### Úloha - odosielanie telemetrie z vášho IoT zariadenia

Odošlite telemetriu úrovne svetla na MQTT sprostredkovateľa.

Údaje sú odosielané zakódované ako JSON - skratka pre JavaScript Object Notation, štandard na kódovanie údajov v texte pomocou párov kľúč/hodnota.

✅ Ak ste sa ešte nestretli s JSON, môžete sa o ňom dozvedieť viac v [dokumentácii JSON.org](https://www.json.org/).

Postupujte podľa relevantného kroku nižšie, aby ste odoslali telemetriu zo svojho zariadenia na MQTT sprostredkovateľa:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Jednodoskový počítač - Raspberry Pi/virtuálne IoT zariadenie](single-board-computer-telemetry.md)

### Prijímanie telemetrie od MQTT sprostredkovateľa

Nemá zmysel odosielať telemetriu, ak na druhej strane nie je nič, čo by ju počúvalo. Telemetria úrovne svetla potrebuje niečo, čo ju bude počúvať a spracovávať údaje. Tento 'serverový' kód je typ kódu, ktorý nasadíte na cloudovú službu ako súčasť väčšej IoT aplikácie, ale tu budete tento kód spúšťať lokálne na svojom počítači (alebo na svojom Pi, ak na ňom priamo kódujete). Serverový kód pozostáva z Python aplikácie, ktorá počúva telemetrické správy cez MQTT s úrovňami svetla. Neskôr v tejto lekcii ho nastavíte tak, aby odpovedal príkazovou správou s inštrukciami na zapnutie alebo vypnutie LED.

✅ Urobte si prieskum: Čo sa stane s MQTT správami, ak nie je žiadny poslucháč?

#### Inštalácia Pythonu a VS Code

Ak nemáte Python a VS Code nainštalované lokálne, budete ich musieť nainštalovať, aby ste mohli kódovať server. Ak používate virtuálne IoT zariadenie alebo pracujete na svojom Raspberry Pi, môžete tento krok preskočiť, pretože by ste to už mali mať nainštalované a nakonfigurované.

##### Úloha - inštalácia Pythonu a VS Code

Nainštalujte Python a VS Code.

1. Nainštalujte Python. Pozrite si [stránku na stiahnutie Pythonu](https://www.python.org/downloads/) pre inštrukcie na inštaláciu najnovšej verzie Pythonu.

1. Nainštalujte Visual Studio Code (VS Code). Toto je editor, ktorý budete používať na písanie kódu virtuálneho zariadenia v Pythone. Pozrite si [dokumentáciu VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pre inštrukcie na inštaláciu VS Code.
💁 Môžete použiť akékoľvek IDE alebo editor pre Python, ak máte preferovaný nástroj, ale lekcie budú obsahovať pokyny založené na používaní VS Code.
1. Nainštalujte rozšírenie Pylance pre VS Code. Toto je rozšírenie pre VS Code, ktoré poskytuje podporu pre jazyk Python. Pokyny na inštaláciu tohto rozšírenia vo VS Code nájdete v [dokumentácii k rozšíreniu Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

#### Nastavenie virtuálneho prostredia pre Python

Jednou z výhod Pythonu je možnosť inštalovať [pip balíčky](https://pypi.org) - ide o balíčky kódu napísané inými ľuďmi a zverejnené na internete. Pip balíček môžete nainštalovať na svoj počítač jediným príkazom a následne ho použiť vo svojom kóde. Pip budete používať na inštaláciu balíčka na komunikáciu cez MQTT.

Štandardne, keď nainštalujete balíček, je dostupný kdekoľvek na vašom počítači, čo môže viesť k problémom s verziami balíčkov - napríklad jedna aplikácia závisí od jednej verzie balíčka, ktorá prestane fungovať, keď nainštalujete novú verziu pre inú aplikáciu. Na vyriešenie tohto problému môžete použiť [virtuálne prostredie pre Python](https://docs.python.org/3/library/venv.html), čo je v podstate kópia Pythonu v špeciálnom priečinku. Keď nainštalujete pip balíčky, budú dostupné iba v tomto priečinku.

##### Úloha - nastavenie virtuálneho prostredia pre Python

Nastavte virtuálne prostredie pre Python a nainštalujte pip balíčky pre MQTT.

1. V termináli alebo príkazovom riadku spustite nasledujúce príkazy na vytvorenie a prechod do nového priečinka:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Teraz spustite nasledujúci príkaz na vytvorenie virtuálneho prostredia v priečinku `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Je potrebné explicitne zavolať `python3` na vytvorenie virtuálneho prostredia, ak máte nainštalovaný aj Python 2. Ak zavoláte `python`, použije sa Python 2 namiesto Pythonu 3.

1. Aktivujte virtuálne prostredie:

    * Na Windows:
        * Ak používate príkazový riadok alebo príkazový riadok cez Windows Terminal, spustite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ak používate PowerShell, spustite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Na macOS alebo Linux spustite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Tieto príkazy by sa mali spustiť z rovnakého miesta, kde ste vytvorili virtuálne prostredie. Nikdy nebudete musieť prechádzať do priečinka `.venv`, vždy by ste mali spustiť príkaz na aktiváciu a akékoľvek príkazy na inštaláciu balíčkov alebo spustenie kódu z priečinka, kde ste vytvorili virtuálne prostredie.

1. Po aktivácii virtuálneho prostredia bude predvolený príkaz `python` spúšťať verziu Pythonu, ktorá bola použitá na vytvorenie virtuálneho prostredia. Spustite nasledujúci príkaz na zistenie verzie:

    ```sh
    python --version
    ```

    Výstup bude podobný nasledujúcemu:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Vaša verzia Pythonu môže byť iná - pokiaľ je to verzia 3.6 alebo vyššia, je to v poriadku. Ak nie, odstráňte tento priečinok, nainštalujte novšiu verziu Pythonu a skúste to znova.

1. Spustite nasledujúce príkazy na inštaláciu pip balíčka [Paho-MQTT](https://pypi.org/project/paho-mqtt/), populárnej knižnice pre MQTT.

    ```sh
    pip install paho-mqtt
    ```

    Tento pip balíček bude nainštalovaný iba vo virtuálnom prostredí a nebude dostupný mimo neho.

#### Napíšte kód pre server

Teraz môžete napísať kód pre server v Pythone.

##### Úloha - napíšte kód pre server

Napíšte kód pre server.

1. V termináli alebo príkazovom riadku spustite nasledujúci príkaz vo virtuálnom prostredí na vytvorenie Python súboru s názvom `app.py`:

    * Na Windows spustite:

        ```cmd
        type nul > app.py
        ```

    * Na macOS alebo Linux spustite:

        ```cmd
        touch app.py
        ```

1. Otvorte aktuálny priečinok vo VS Code:

    ```sh
    code .
    ```

1. Keď sa VS Code spustí, aktivuje virtuálne prostredie pre Python. Toto bude zobrazené v dolnom stavovom riadku:

    ![VS Code zobrazujúci vybrané virtuálne prostredie](../../../../../translated_images/sk/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Ak je terminál vo VS Code už spustený pri štarte VS Code, virtuálne prostredie v ňom nebude aktivované. Najjednoduchšie je ukončiť terminál pomocou tlačidla **Kill the active terminal instance**:

    ![VS Code tlačidlo na ukončenie aktívneho terminálu](../../../../../translated_images/sk/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Spustite nový terminál vo VS Code výberom *Terminal -> New Terminal* alebo stlačením `` CTRL+` ``. Nový terminál načíta virtuálne prostredie, pričom príkaz na jeho aktiváciu sa zobrazí v termináli. Názov virtuálneho prostredia (`.venv`) sa zobrazí aj v príkazovom riadku:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Otvorte súbor `app.py` v prieskumníkovi VS Code a pridajte nasledujúci kód:

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

    Nahraďte `<ID>` na riadku 6 unikátnym ID, ktoré ste použili pri vytváraní kódu pre zariadenie.

    ⚠️ Toto **musí** byť rovnaké ID, aké ste použili na zariadení, inak sa kód servera neprihlási na odber alebo nepublikuje na správnu tému.

    Tento kód vytvára MQTT klienta s unikátnym názvom a pripája sa k brokerovi *test.mosquitto.org*. Následne spustí spracovateľskú slučku, ktorá beží na pozadí a počúva správy na všetkých prihlásených témach.

    Klient sa potom prihlási na odber správ na telemetrickej téme a definuje funkciu, ktorá sa zavolá, keď sa prijme správa. Keď sa prijme telemetrická správa, zavolá sa funkcia `handle_telemetry`, ktorá vypíše prijatú správu do konzoly.

    Nakoniec nekonečná slučka udržiava aplikáciu v chode. MQTT klient počúva správy na pozadí a beží po celý čas, kým hlavná aplikácia beží.

1. V termináli VS Code spustite nasledujúci príkaz na spustenie Python aplikácie:

    ```sh
    python app.py
    ```

    Aplikácia začne počúvať správy zo zariadenia IoT.

1. Uistite sa, že vaše zariadenie beží a odosiela telemetrické správy. Upravte úrovne svetla detekované vaším fyzickým alebo virtuálnym zariadením. Prijaté správy sa budú vypisovať do terminálu.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Súbor `app.py` vo virtuálnom prostredí nightlight musí byť spustený, aby súbor `app.py` vo virtuálnom prostredí nightlight-server mohol prijímať odosielané správy.

> 💁 Tento kód nájdete v priečinku [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Ako často by sa mala telemetria odosielať?

Jednou z dôležitých otázok pri telemetrii je, ako často merať a odosielať údaje? Odpoveď je - záleží na situácii. Ak meriate často, môžete rýchlejšie reagovať na zmeny, ale spotrebujete viac energie, šírky pásma, generujete viac údajov a potrebujete viac cloudových zdrojov na ich spracovanie. Musíte merať dostatočne často, ale nie príliš často.

Pre termostat je meranie každých pár minút pravdepodobne viac než dosť, pretože teploty sa nemenia tak často. Ak by ste merali len raz denne, mohli by ste vykurovať dom pre nočné teploty uprostred slnečného dňa, zatiaľ čo ak by ste merali každú sekundu, mali by ste tisíce zbytočne duplikovaných meraní teploty, ktoré by spomalili internet používateľa a spotrebovali viac energie, čo môže byť problém pre zariadenia napájané batériami, ako sú vzdialené senzory, a zvýšili by náklady na cloudové zdroje poskytovateľa na ich spracovanie a ukladanie.

Ak monitorujete údaje o stroji vo fabrike, ktorého zlyhanie by mohlo spôsobiť katastrofálne škody a milióny dolárov strát, meranie viackrát za sekundu môže byť nevyhnutné. Je lepšie plytvať šírkou pásma, než prehliadnuť telemetriu, ktorá naznačuje, že stroj treba zastaviť a opraviť skôr, než sa pokazí.

> 💁 V takejto situácii by ste mohli zvážiť použitie edge zariadenia na spracovanie telemetrie, aby ste znížili závislosť od internetu.

### Strata pripojenia

Internetové pripojenia môžu byť nespoľahlivé a výpadky sú bežné. Čo by malo zariadenie IoT robiť v takýchto prípadoch - malo by stratiť údaje, alebo ich uložiť, kým sa pripojenie neobnoví? Odpoveď opäť závisí od situácie.

Pre termostat môžu byť údaje stratené, akonáhle sa získa nové meranie teploty. Kúrenie nezaujíma, že pred 20 minútami bolo 20,5 °C, ak je teraz 19 °C - aktuálna teplota určuje, či má byť kúrenie zapnuté alebo vypnuté.

Pre stroje by ste možno chceli údaje uchovať, najmä ak sa používajú na sledovanie trendov. Existujú modely strojového učenia, ktoré dokážu detegovať anomálie v prúdoch údajov tým, že analyzujú údaje za definované časové obdobie (napríklad poslednú hodinu) a hľadajú anomálne údaje. To sa často používa na prediktívnu údržbu, ktorá hľadá náznaky, že niečo môže čoskoro zlyhať, aby ste to mohli opraviť alebo vymeniť skôr, než sa to stane. V takom prípade by ste mohli chcieť, aby zariadenie IoT odoslalo všetku telemetriu, ktorá bola generovaná počas výpadku internetu, hneď ako sa pripojenie obnoví.

Dizajnéri zariadení IoT by tiež mali zvážiť, či zariadenie môže byť použité počas výpadku internetu alebo straty signálu spôsobenej lokalitou. Inteligentný termostat by mal byť schopný robiť obmedzené rozhodnutia na ovládanie kúrenia, ak nemôže odosielať telemetriu do cloudu kvôli výpadku.

[![Toto Ferrari sa stalo nepoužiteľným, pretože niekto sa ho pokúsil aktualizovať pod zemou, kde nie je mobilný signál](../../../../../translated_images/sk/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Aby MQTT zvládlo stratu pripojenia, zariadenie a kód servera budú musieť byť zodpovedné za zabezpečenie doručenia správ, ak je to potrebné, napríklad vyžadovaním, aby všetky odoslané správy boli potvrdené ďalšími správami na odpovednej téme. Ak nie sú potvrdené, musia byť manuálne zaradené do frontu na opätovné odoslanie neskôr.

## Príkazy

Príkazy sú správy odoslané z cloudu do zariadenia, ktoré ho inštruujú, aby niečo vykonalo. Väčšinou ide o poskytnutie nejakého výstupu cez akčný člen, ale môže to byť aj inštrukcia pre samotné zariadenie, napríklad na reštartovanie alebo zhromaždenie ďalšej telemetrie a jej vrátenie ako odpoveď na príkaz.

![Internetom pripojený termostat prijímajúci príkaz na zapnutie kúrenia](../../../../../translated_images/sk/commands.d6c06bbbb3a02cce.webp)

Termostat by mohol prijať príkaz z cloudu na zapnutie kúrenia. Na základe telemetrických údajov zo všetkých senzorov cloudová služba rozhodla, že kúrenie by malo byť zapnuté, a preto posiela príslušný príkaz.

### Odosielanie príkazov na MQTT broker

Ďalším krokom pre náš internetom ovládaný nočný svetelný zdroj je, aby kód servera odoslal príkaz späť do zariadenia IoT na ovládanie svetla na základe úrovní svetla, ktoré deteguje.

1. Otvorte kód servera vo VS Code.

1. Pridajte nasledujúci riadok po deklarácii `client_telemetry_topic`, aby ste definovali, na ktorú tému sa majú odosielať príkazy:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Pridajte nasledujúci kód na koniec funkcie `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Tento kód odosiela JSON správu na tému príkazov s hodnotou `led_on` nastavenou na true alebo false v závislosti od toho, či je svetlo menšie ako 300 alebo nie. Ak je svetlo menšie ako 300, odošle sa true, aby zariadenie zaplo LED.

1. Spustite kód ako predtým.

1. Upravte úrovne svetla detekované vaším fyzickým alebo virtuálnym zariadením. Prijaté správy a odoslané príkazy sa budú vypisovať do terminálu:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetria a príkazy sa odosielajú na jednu tému. To znamená, že telemetria z viacerých zariadení sa objaví na rovnakej telemetrickej téme a príkazy pre viaceré zariadenia sa objavia na rovnakej téme príkazov. Ak by ste chceli odoslať príkaz konkrétnemu zariadeniu, mohli by ste použiť viacero tém, pomenovaných unikátnym ID zariadenia, ako napríklad `/commands/device1`, `/commands/device2`. Takto by zariadenie mohlo počúvať iba správy určené pre konkrétne zariadenie.

> 💁 Tento kód nájdete v priečinku [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Spracovanie príkazov na zariadení IoT

Teraz, keď sa príkazy odosielajú zo servera, môžete pridať kód do zariadenia IoT na ich spracovanie a ovládanie LED.

Postupujte podľa príslušného kroku nižšie na počúvanie príkazov z MQTT brokera:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Jednodoskový počítač - Raspberry Pi/virtuálne IoT zariadenie](single-board-computer-commands.md)

Keď bude tento kód napísaný a spustený, experimentujte so zmenou úrovní svetla. Sledujte výstup zo servera a zariadenia a sledujte LED, keď meníte úrovne svetla.

### Strata pripojenia

Čo by mala cloudová služba robiť, ak potrebuje odoslať príkaz zariadeniu IoT, ktoré je offline? Odpoveď opäť závisí od situácie.

Ak najnovší príkaz prepíše predchádzajúci, potom môžu byť predchádzajúce ignorované. Ak cloudová služba odošle príkaz na zapnutie kúrenia a potom príkaz na jeho vypnutie, príkaz na zapnutie môže byť ignorovaný a nemusí byť odoslaný znova.

Ak je potrebné príkazy spracovať v poradí, napríklad pohybovať robotickým ramenom hore a potom zatvoriť uchopovač, musia byť odoslané v poradí, keď sa pripojenie obnoví.

✅ Ako by mohli zariadenie alebo kód servera zabezpečiť, že príkazy bud
Premýšľajte o týchto zariadeniach, aké správy môžu posielať alebo prijímať. Aké telemetrické údaje posielajú? Aké správy alebo príkazy môžu prijímať? Myslíte si, že sú bezpečné?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Prehľad a samostatné štúdium

Prečítajte si viac o MQTT na [stránke Wikipédie o MQTT](https://wikipedia.org/wiki/MQTT).

Vyskúšajte si spustiť vlastný MQTT broker pomocou [Mosquitto](https://www.mosquitto.org) a pripojte sa k nemu zo svojho IoT zariadenia a serverového kódu.

> 💁 Tip - predvolene Mosquitto neumožňuje anonymné pripojenia (teda pripojenia bez používateľského mena a hesla) a neumožňuje pripojenia mimo počítača, na ktorom beží.
> Toto môžete vyriešiť pomocou [`mosquitto.conf` konfiguračného súboru](https://www.mosquitto.org/man/mosquitto-conf-5.html) s nasledujúcim obsahom:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Zadanie

[Porovnajte a porovnajte MQTT s inými komunikačnými protokolmi](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.