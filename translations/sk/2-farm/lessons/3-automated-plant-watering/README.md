<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-28T11:36:20+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "sk"
}
-->
# Automatické zavlažovanie rastlín

![Prehľad tejto lekcie vo forme sketchnote](../../../../../translated_images/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.sk.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre jeho zväčšenú verziu.

Táto lekcia bola súčasťou [IoT pre začiatočníkov Projekt 2 - Digitálne poľnohospodárstvo](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) zo série [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Automatické zavlažovanie rastlín pomocou IoT](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Kvíz pred lekciou

[Kvíz pred lekciou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Úvod

V predchádzajúcej lekcii ste sa naučili, ako monitorovať vlhkosť pôdy. V tejto lekcii sa naučíte, ako zostaviť základné komponenty automatického zavlažovacieho systému, ktorý reaguje na vlhkosť pôdy. Tiež sa dozviete o načasovaní – ako senzory môžu potrebovať určitý čas na reakciu na zmeny a ako aktuátory môžu potrebovať čas na zmenu vlastností, ktoré senzory merajú.

V tejto lekcii sa budeme venovať:

* [Ovládanie zariadení s vysokým výkonom pomocou IoT zariadenia s nízkym výkonom](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Ovládanie relé](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Ovládanie vašej rastliny cez MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Načasovanie senzorov a aktuátorov](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Pridanie načasovania do vášho servera na ovládanie rastlín](../../../../../2-farm/lessons/3-automated-plant-watering)

## Ovládanie zariadení s vysokým výkonom pomocou IoT zariadenia s nízkym výkonom

IoT zariadenia používajú nízke napätie. Hoci to stačí pre senzory a nízkovýkonné aktuátory, ako sú LED diódy, je to príliš málo na ovládanie väčšieho hardvéru, ako je vodné čerpadlo používané na zavlažovanie. Dokonca aj malé čerpadlá, ktoré by ste mohli použiť pre izbové rastliny, odoberajú príliš veľa prúdu pre IoT vývojovú dosku a mohli by ju poškodiť.

> 🎓 Prúd, meraný v ampéroch (A), je množstvo elektriny pretekajúce obvodom. Napätie poskytuje tlak, prúd je to, koľko sa tlačí. Viac o prúde si môžete prečítať na [stránke o elektrickom prúde na Wikipédii](https://wikipedia.org/wiki/Electric_current).

Riešením je pripojiť čerpadlo k externému zdroju napájania a použiť aktuátor na zapnutie čerpadla, podobne ako by ste zapli svetlo. Na preklopenie vypínača prstom stačí malé množstvo energie (vo forme energie vášho tela), a to spojí svetlo s elektrickou sieťou bežiacou na 110V/240V.

![Vypínač zapína svetlo](../../../../../translated_images/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.sk.png)

> 🎓 [Elektrická sieť](https://wikipedia.org/wiki/Mains_electricity) označuje elektrinu dodávanú do domácností a podnikov prostredníctvom národnej infraštruktúry v mnohých častiach sveta.

✅ IoT zariadenia zvyčajne poskytujú 3,3V alebo 5V, pri prúde menej ako 1 ampér (1A). Porovnajte to s elektrickou sieťou, ktorá je najčastejšie na úrovni 230V (120V v Severnej Amerike a 100V v Japonsku) a dokáže napájať zariadenia, ktoré odoberajú 30A.

Existuje množstvo aktuátorov, ktoré to dokážu, vrátane mechanických zariadení, ktoré môžete pripojiť k existujúcim vypínačom a ktoré napodobňujú prst zapínajúci ich. Najpopulárnejším je relé.

### Relé

Relé je elektromechanický spínač, ktorý premieňa elektrický signál na mechanický pohyb, ktorý zapína spínač. Jadro relé tvorí elektromagnet.

> 🎓 [Elektromagnety](https://wikipedia.org/wiki/Electromagnet) sú magnety, ktoré vznikajú prechodom elektriny cez cievku drôtu. Keď je elektrina zapnutá, cievka sa zmagnetizuje. Keď je elektrina vypnutá, cievka stratí svoju magnetickú schopnosť.

![Keď je zapnuté, elektromagnet vytvára magnetické pole, ktoré zapína spínač pre výstupný obvod](../../../../../translated_images/relay-on.4db16a0fd6b66926.sk.png)

V relé napája ovládací obvod elektromagnet. Keď je elektromagnet zapnutý, pritiahne páku, ktorá pohne spínačom, uzavrie pár kontaktov a dokončí výstupný obvod.

![Keď je vypnuté, elektromagnet nevytvára magnetické pole, ktoré by zapínalo spínač pre výstupný obvod](../../../../../translated_images/relay-off.c34a178a2960fecd.sk.png)

Keď je ovládací obvod vypnutý, elektromagnet sa vypne, uvoľní páku a otvorí kontakty, čím vypne výstupný obvod. Relé sú digitálne aktuátory – vysoký signál do relé ho zapne, nízky signál ho vypne.

Výstupný obvod môže byť použitý na napájanie ďalšieho hardvéru, ako je zavlažovací systém. IoT zariadenie môže zapnúť relé, čím dokončí výstupný obvod, ktorý napája zavlažovací systém, a rastliny sa zavlažia. IoT zariadenie potom môže relé vypnúť, čím preruší napájanie zavlažovacieho systému a zastaví vodu.

![Relé zapína čerpadlo, ktoré posiela vodu do rastliny](../../../../../images/strawberry-pump.gif)

Vo videu vyššie sa zapne relé. LED dióda na relé sa rozsvieti, aby signalizovala, že je zapnuté (niektoré relé majú LED diódy na indikáciu zapnutia alebo vypnutia), a napájanie sa odošle do čerpadla, ktoré sa zapne a pumpuje vodu do rastliny.

> 💁 Relé môžu byť tiež použité na prepínanie medzi dvoma výstupnými obvodmi namiesto zapínania a vypínania jedného. Keď sa páka pohybuje, presúva spínač z dokončenia jedného výstupného obvodu na dokončenie iného výstupného obvodu, zvyčajne zdieľajúceho spoločné napájanie alebo spoločné uzemnenie.

✅ Urobte si výskum: Existuje viacero typov relé s rozdielmi, ako napríklad či ovládací obvod zapína alebo vypína relé, keď je napájanie pripojené, alebo s viacerými výstupnými obvodmi. Zistite viac o týchto rôznych typoch.

Keď sa páka pohybuje, zvyčajne počujete, ako sa dotkne elektromagnetu s dobre definovaným kliknutím.

> 💁 Relé môže byť zapojené tak, že vytvorenie spojenia vlastne preruší napájanie relé, čím sa relé vypne, čo potom pošle napájanie späť do relé, čím sa opäť zapne, a tak ďalej. To znamená, že relé bude klikať neuveriteľne rýchlo a vytvárať bzučivý zvuk. Takto fungovali niektoré z prvých bzučiakov používaných v elektrických zvončekoch.

### Napájanie relé

Elektromagnet nepotrebuje veľa energie na aktiváciu a pritiahne páku, môže byť ovládaný pomocou 3,3V alebo 5V výstupu z IoT vývojovej dosky. Výstupný obvod môže niesť oveľa viac energie, v závislosti od relé, vrátane napätia zo siete alebo dokonca vyšších úrovní výkonu pre priemyselné použitie. Týmto spôsobom môže IoT vývojová doska ovládať zavlažovací systém, od malého čerpadla pre jednu rastlinu až po masívny priemyselný systém pre celú komerčnú farmu.

![Relé Grove s označenými ovládacím obvodom, výstupným obvodom a relé](../../../../../translated_images/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.sk.png)

Na obrázku vyššie je relé Grove. Ovládací obvod sa pripája k IoT zariadeniu a zapína alebo vypína relé pomocou 3,3V alebo 5V. Výstupný obvod má dva terminály, buď jeden môže byť napájanie alebo uzemnenie. Výstupný obvod zvládne až 250V pri 10A, čo je dosť pre rad zariadení napájaných zo siete. Môžete získať relé, ktoré zvládnu ešte vyššie úrovne výkonu.

![Čerpadlo zapojené cez relé](../../../../../translated_images/pump-wired-to-relay.66c5cfc0d8918990.sk.png)

Na obrázku vyššie je čerpadlo napájané cez relé. Červený vodič spája +5V terminál USB napájacieho zdroja s jedným terminálom výstupného obvodu relé a ďalší červený vodič spája druhý terminál výstupného obvodu s čerpadlom. Čierny vodič spája čerpadlo s uzemnením USB napájacieho zdroja. Keď sa relé zapne, dokončí obvod, pošle 5V do čerpadla a zapne ho.

## Ovládanie relé

Relé môžete ovládať zo svojej IoT vývojovej dosky.

### Úloha - ovládanie relé

Prejdite si príslušný návod na ovládanie relé pomocou vášho IoT zariadenia:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Jednodoskový počítač - Raspberry Pi](pi-relay.md)
* [Jednodoskový počítač - Virtuálne zariadenie](virtual-device-relay.md)

## Ovládanie vašej rastliny cez MQTT

Doteraz bolo vaše relé ovládané IoT zariadením priamo na základe jedného merania vlhkosti pôdy. V komerčnom zavlažovacom systéme bude riadiaca logika centralizovaná, čo umožní rozhodovanie o zavlažovaní na základe údajov z viacerých senzorov a umožní zmenu konfigurácie na jednom mieste. Na simuláciu tohto procesu môžete ovládať relé cez MQTT.

### Úloha - ovládanie relé cez MQTT

1. Pridajte príslušné knižnice/pip balíčky MQTT a kód do vášho projektu `soil-moisture-sensor`, aby ste sa pripojili k MQTT. Pomenujte ID klienta ako `soilmoisturesensor_client` s predponou vášho ID.

    > ⚠️ Môžete sa odvolať na [pokyny na pripojenie k MQTT v projekte 1, lekcia 4, ak je to potrebné](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Pridajte príslušný kód zariadenia na odosielanie telemetrie s nastaveniami vlhkosti pôdy. Pre správu telemetrie pomenujte vlastnosť `soil_moisture`.

    > ⚠️ Môžete sa odvolať na [pokyny na odosielanie telemetrie do MQTT v projekte 1, lekcia 4, ak je to potrebné](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Vytvorte lokálny serverový kód na odber telemetrie a odoslanie príkazu na ovládanie relé v priečinku `soil-moisture-sensor-server`. Pomenujte vlastnosť v správe príkazu `relay_on` a nastavte ID klienta ako `soilmoisturesensor_server` s predponou vášho ID. Zachovajte rovnakú štruktúru ako serverový kód, ktorý ste napísali pre projekt 1, lekcia 4, pretože tento kód budete neskôr v tejto lekcii rozširovať.

    > ⚠️ Môžete sa odvolať na [pokyny na odosielanie telemetrie do MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) a [odosielanie príkazov cez MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) v projekte 1, lekcia 4, ak je to potrebné.

1. Pridajte príslušný kód zariadenia na ovládanie relé z prijatých príkazov, pomocou vlastnosti `relay_on` zo správy. Pošlite hodnotu true pre `relay_on`, ak je `soil_moisture` väčšia ako 450, inak pošlite hodnotu false, rovnako ako logiku, ktorú ste pridali pre IoT zariadenie skôr.

    > ⚠️ Môžete sa odvolať na [pokyny na reagovanie na príkazy z MQTT v projekte 1, lekcia 4, ak je to potrebné](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Tento kód nájdete v priečinku [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt).

Uistite sa, že kód beží na vašom zariadení a lokálnom serveri, a otestujte ho zmenou úrovní vlhkosti pôdy, buď zmenou hodnôt odosielaných virtuálnym senzorom, alebo zmenou úrovní vlhkosti pôdy pridaním vody alebo odstránením senzora z pôdy.

## Načasovanie senzorov a aktuátorov

V lekcii 3 ste vytvorili nočné svetlo – LED diódu, ktorá sa zapne hneď, ako svetelný senzor zistí nízku úroveň svetla. Svetelný senzor zistil zmenu úrovne svetla okamžite a zariadenie mohlo reagovať rýchlo, obmedzené iba dĺžkou oneskorenia v slučke `loop` alebo `while True:`. Ako vývojár IoT sa však nemôžete vždy spoliehať na takúto rýchlu spätnú väzbu.

### Načasovanie pre vlhkosť pôdy

Ak ste robili predchádzajúcu lekciu o vlhkosti pôdy pomocou fyzického senzora, mohli ste si všimnúť, že trvalo niekoľko sekúnd, kým hodnota vlhkosti pôdy klesla po tom, čo ste zaliali rastlinu. To nie je preto, že by bol senzor pomalý, ale preto, že vode trvá určitý čas, kým sa vsiakne do pôdy.
💁 Ak ste polievali príliš blízko senzora, mohli ste si všimnúť, že hodnota rýchlo klesla a potom sa opäť zvýšila – je to spôsobené tým, že voda v blízkosti senzora sa rozšírila do zvyšku pôdy, čím sa znížila vlhkosť pôdy v okolí senzora.
![Meranie vlhkosti pôdy na úrovni 658 sa nemení počas zalievania, klesne na 320 až po tom, ako voda presiakne pôdou](../../../../../translated_images/soil-moisture-travel.a0e31af222cf1438.sk.png)

Na diagrame vyššie je zobrazené meranie vlhkosti pôdy na úrovni 658. Rastlina je zaliata, ale táto hodnota sa okamžite nezmení, pretože voda ešte nedosiahla senzor. Zalievanie môže dokonca skončiť skôr, než voda dosiahne senzor, a hodnota klesne, aby odrážala novú úroveň vlhkosti.

Ak by ste písali kód na ovládanie zavlažovacieho systému pomocou relé na základe úrovní vlhkosti pôdy, museli by ste zohľadniť toto oneskorenie a implementovať inteligentnejšie načasovanie do vášho IoT zariadenia.

✅ Zamyslite sa nad tým, ako by ste to mohli urobiť.

### Ovládanie načasovania senzora a aktuátora

Predstavte si, že máte za úlohu vybudovať zavlažovací systém pre farmu. Na základe typu pôdy sa zistilo, že ideálna úroveň vlhkosti pôdy pre pestované rastliny zodpovedá analógovému napätiu v rozmedzí 400-450.

Mohli by ste naprogramovať zariadenie podobne ako nočné svetlo – vždy, keď senzor nameria hodnotu nad 450, zapne relé na spustenie čerpadla. Problém je, že voda potrebuje určitý čas, aby sa dostala z čerpadla cez pôdu k senzoru. Senzor zastaví prívod vody, keď zistí úroveň 450, ale úroveň vlhkosti bude naďalej klesať, pretože čerpaná voda stále presakuje pôdou. Výsledkom je plytvanie vodou a riziko poškodenia koreňov.

✅ Pamätajte – príliš veľa vody môže byť pre rastliny rovnako škodlivé ako jej nedostatok a zároveň plytvá vzácnym zdrojom.

Lepším riešením je pochopiť, že medzi zapnutím aktuátora a zmenou vlastnosti, ktorú senzor meria, existuje oneskorenie. To znamená, že senzor by mal nielen chvíľu počkať pred opätovným meraním hodnoty, ale aktuátor by sa mal vypnúť na určitý čas pred ďalším meraním senzora.

Ako dlho by malo byť relé zapnuté pri každom cykle? Je lepšie byť opatrný a zapnúť relé len na krátky čas, potom počkať, kým voda presiakne, a následne znovu skontrolovať úroveň vlhkosti. Nakoniec, vždy môžete relé znovu zapnúť, aby ste pridali viac vody, ale nemôžete vodu z pôdy odstrániť.

> 💁 Tento typ načasovania je veľmi špecifický pre IoT zariadenie, ktoré budujete, vlastnosť, ktorú meriate, a použité senzory a aktuátory.

![Rastlina jahody pripojená k čerpadlu cez relé. Relé a senzor vlhkosti pôdy sú pripojené k Raspberry Pi](../../../../../translated_images/strawberry-with-pump.b410fc72ac6aabad.sk.png)

Napríklad mám rastlinu jahody so senzorom vlhkosti pôdy a čerpadlom ovládaným relé. Zistil som, že keď pridám vodu, trvá približne 20 sekúnd, kým sa hodnota vlhkosti pôdy stabilizuje. To znamená, že musím relé vypnúť a počkať 20 sekúnd pred kontrolou úrovne vlhkosti. Radšej pridám menej vody než príliš veľa – čerpadlo môžem vždy znovu zapnúť, ale nemôžem vodu z rastliny odstrániť.

![Krok 1: vykonajte meranie. Krok 2: pridajte vodu. Krok 3: počkajte, kým voda presiakne pôdou. Krok 4: vykonajte opätovné meranie](../../../../../translated_images/soil-moisture-delay.865f3fae206db01d.sk.png)

To znamená, že najlepší proces zavlažovania by mohol vyzerať takto:

* Zapnite čerpadlo na 5 sekúnd
* Počkajte 20 sekúnd
* Skontrolujte vlhkosť pôdy
* Ak je úroveň stále nad požadovanou hodnotou, zopakujte vyššie uvedené kroky

5 sekúnd môže byť pre čerpadlo príliš dlhý čas, najmä ak sú úrovne vlhkosti len mierne nad požadovanou hodnotou. Najlepší spôsob, ako zistiť správne načasovanie, je vyskúšať to, potom upraviť na základe údajov zo senzora, s neustálym spätným cyklom. To môže viesť k jemnejšiemu načasovaniu, napríklad zapnutiu čerpadla na 1 sekundu za každých 100 nad požadovanou úrovňou vlhkosti, namiesto pevne stanovených 5 sekúnd.

✅ Urobte si prieskum: Existujú ďalšie faktory načasovania? Môže byť rastlina zalievaná kedykoľvek, keď je vlhkosť pôdy príliš nízka, alebo existujú konkrétne časy dňa, ktoré sú vhodné alebo nevhodné na zalievanie rastlín?

> 💁 Predpovede počasia môžu byť tiež zohľadnené pri ovládaní automatizovaných zavlažovacích systémov pre vonkajšie pestovanie. Ak sa očakáva dážď, zavlažovanie môže byť odložené až po skončení dažďa. V tom momente môže byť pôda dostatočne vlhká, takže už nebude potrebné zalievať, čo je oveľa efektívnejšie než plytvanie vodou tesne pred dažďom.

## Pridajte načasovanie do vášho servera na ovládanie rastlín

Kód servera môže byť upravený tak, aby pridával kontrolu nad načasovaním zavlažovacieho cyklu a čakaním na zmenu úrovne vlhkosti pôdy. Logika servera na ovládanie načasovania relé je:

1. Prijatie telemetrickej správy
1. Kontrola úrovne vlhkosti pôdy
1. Ak je úroveň v poriadku, nerobte nič. Ak je hodnota príliš vysoká (čo znamená, že vlhkosť pôdy je príliš nízka), potom:
    1. Pošlite príkaz na zapnutie relé
    1. Počkajte 5 sekúnd
    1. Pošlite príkaz na vypnutie relé
    1. Počkajte 20 sekúnd, kým sa úrovne vlhkosti pôdy stabilizujú

Zavlažovací cyklus, proces od prijatia telemetrickej správy po pripravenosť na spracovanie úrovní vlhkosti pôdy, trvá približne 25 sekúnd. Posielame úrovne vlhkosti pôdy každých 10 sekúnd, takže existuje prekrytie, kde je správa prijatá, zatiaľ čo server čaká na stabilizáciu úrovní vlhkosti pôdy, čo by mohlo spustiť ďalší zavlažovací cyklus.

Existujú dve možnosti, ako tento problém vyriešiť:

* Zmeniť kód IoT zariadenia tak, aby posielalo telemetriu každú minútu, čím sa zabezpečí, že zavlažovací cyklus bude dokončený pred odoslaním ďalšej správy
* Odhlásiť sa z telemetrie počas zavlažovacieho cyklu

Prvá možnosť nie je vždy dobrým riešením pre veľké farmy. Farmár môže chcieť zachytiť úrovne vlhkosti pôdy počas zavlažovania na neskoršiu analýzu, napríklad aby si uvedomil tok vody v rôznych oblastiach farmy na lepšie cielené zavlažovanie. Druhá možnosť je lepšia – kód jednoducho ignoruje telemetriu, keď ju nemôže použiť, ale telemetria je stále dostupná pre iné služby, ktoré by ju mohli odoberať.

> 💁 IoT údaje nie sú posielané len z jedného zariadenia do jednej služby, ale mnoho zariadení môže posielať údaje do brokeru a mnoho služieb môže počúvať údaje z brokeru. Napríklad jedna služba môže počúvať údaje o vlhkosti pôdy a ukladať ich do databázy na neskoršiu analýzu. Iná služba môže počúvať tú istú telemetriu na ovládanie zavlažovacieho systému.

### Úloha – pridajte načasovanie do vášho servera na ovládanie rastlín

Aktualizujte kód servera tak, aby relé bežalo 5 sekúnd, potom čakalo 20 sekúnd.

1. Otvorte priečinok `soil-moisture-sensor-server` vo VS Code, ak už nie je otvorený. Uistite sa, že virtuálne prostredie je aktivované.

1. Otvorte súbor `app.py`

1. Pridajte nasledujúci kód do súboru `app.py` pod existujúce importy:

    ```python
    import threading
    ```

    Tento príkaz importuje `threading` z knižníc Pythonu, čo umožňuje Pythonu vykonávať iný kód počas čakania.

1. Pridajte nasledujúci kód pred funkciu `handle_telemetry`, ktorá spracováva telemetrické správy prijaté kódom servera:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Toto definuje, ako dlho má relé bežať (`water_time`) a ako dlho má čakať pred kontrolou vlhkosti pôdy (`wait_time`).

1. Pod tento kód pridajte nasledujúci:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Tento kód definuje funkciu nazvanú `send_relay_command`, ktorá posiela príkaz cez MQTT na ovládanie relé. Telemetria je vytvorená ako slovník, potom konvertovaná na JSON reťazec. Hodnota odovzdaná do `state` určuje, či má byť relé zapnuté alebo vypnuté.

1. Po funkcii `send_relay_code` pridajte nasledujúci kód:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Toto definuje funkciu na ovládanie relé na základe požadovaného načasovania. Začína odhlásením z telemetrie, aby sa správy o vlhkosti pôdy nespracovávali počas zavlažovania. Potom pošle príkaz na zapnutie relé. Následne čaká `water_time`, než pošle príkaz na vypnutie relé. Nakoniec čaká na stabilizáciu úrovní vlhkosti pôdy po dobu `wait_time`. Potom sa znovu prihlási na telemetriu.

1. Zmeňte funkciu `handle_telemetry` na nasledujúcu:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Tento kód kontroluje úroveň vlhkosti pôdy. Ak je vyššia ako 450, pôda potrebuje zavlažovanie, takže zavolá funkciu `control_relay`. Táto funkcia beží na samostatnom vlákne, ktoré beží na pozadí.

1. Uistite sa, že vaše IoT zariadenie beží, potom spustite tento kód. Zmeňte úrovne vlhkosti pôdy a pozorujte, čo sa stane s relé – malo by byť zapnuté na 5 sekúnd a potom zostať vypnuté aspoň 20 sekúnd, pričom sa zapne iba v prípade, že úrovne vlhkosti nie sú dostatočné.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Dobrým spôsobom, ako to otestovať v simulovanom zavlažovacom systéme, je použiť suchú pôdu, potom manuálne nalievať vodu, zatiaľ čo relé je zapnuté, a zastaviť nalievanie, keď sa relé vypne.

> 💁 Tento kód nájdete v priečinku [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).

> 💁 Ak chcete použiť čerpadlo na vybudovanie skutočného zavlažovacieho systému, môžete použiť [6V vodné čerpadlo](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) s [USB napájacím terminálom](https://www.adafruit.com/product/3628). Uistite sa, že napájanie do alebo z čerpadla je pripojené cez relé.

---

## 🚀 Výzva

Dokážete si predstaviť iné IoT alebo elektrické zariadenia, ktoré majú podobný problém, kde trvá určitý čas, kým výsledky aktuátora dosiahnu senzor? Pravdepodobne máte niekoľko takýchto zariadení vo vašom dome alebo škole.

* Aké vlastnosti merajú?
* Ako dlho trvá, kým sa vlastnosť zmení po použití aktuátora?
* Je v poriadku, ak sa vlastnosť zmení nad požadovanú hodnotu?
* Ako ju možno vrátiť späť na požadovanú hodnotu, ak je to potrebné?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Prehľad a samostatné štúdium

* Prečítajte si viac o relé vrátane ich historického použitia v telefónnych ústredniach na [stránke Wikipedia o relé](https://wikipedia.org/wiki/Relay).

## Zadanie

[Vybudujte efektívnejší zavlažovací cyklus](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.