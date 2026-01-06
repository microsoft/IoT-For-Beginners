<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-28T09:51:17+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "sk"
}
-->
# Umiestnenie údajov o polohe

![Prehľad tejto lekcie v sketchnote](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.sk.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Úvod

V predchádzajúcej lekcii ste sa naučili, ako používať GPS senzor na zachytávanie údajov o polohe. Aby ste mohli tieto údaje použiť na vizualizáciu polohy nákladného auta s potravinami a jeho cesty, je potrebné ich odoslať do IoT služby v cloude a následne niekde uložiť.

V tejto lekcii sa naučíte rôzne spôsoby ukladania IoT údajov a ako ukladať údaje z vašej IoT služby pomocou serverless kódu.

V tejto lekcii sa budeme venovať:

* [Štruktúrované a neštruktúrované údaje](../../../../../3-transport/lessons/2-store-location-data)
* [Odoslanie GPS údajov do IoT Hubu](../../../../../3-transport/lessons/2-store-location-data)
* [Horúce, teplé a studené cesty](../../../../../3-transport/lessons/2-store-location-data)
* [Spracovanie GPS udalostí pomocou serverless kódu](../../../../../3-transport/lessons/2-store-location-data)
* [Účty Azure Storage](../../../../../3-transport/lessons/2-store-location-data)
* [Prepojenie serverless kódu s úložiskom](../../../../../3-transport/lessons/2-store-location-data)

## Štruktúrované a neštruktúrované údaje

Počítačové systémy pracujú s údajmi, ktoré môžu mať rôzne tvary a veľkosti. Môžu sa líšiť od jednotlivých čísel, cez veľké množstvo textu, až po videá, obrázky a IoT údaje. Údaje sa zvyčajne delia do dvoch kategórií - *štruktúrované* údaje a *neštruktúrované* údaje.

* **Štruktúrované údaje** sú údaje s dobre definovanou, pevnou štruktúrou, ktorá sa nemení a zvyčajne sa mapujú na tabuľky údajov s vzťahmi. Príkladom sú osobné údaje osoby, ako meno, dátum narodenia a adresa.

* **Neštruktúrované údaje** sú údaje bez dobre definovanej, pevnej štruktúry, vrátane údajov, ktoré môžu často meniť svoju štruktúru. Príkladom sú dokumenty, ako písomné dokumenty alebo tabuľky.

✅ Urobte si prieskum: Dokážete vymyslieť ďalšie príklady štruktúrovaných a neštruktúrovaných údajov?

> 💁 Existujú aj pološtruktúrované údaje, ktoré sú štruktúrované, ale nezapadajú do pevných tabuliek údajov.

IoT údaje sa zvyčajne považujú za neštruktúrované údaje.

Predstavte si, že pridávate IoT zariadenia do flotily vozidiel veľkej komerčnej farmy. Môžete chcieť používať rôzne zariadenia pre rôzne typy vozidiel. Napríklad:

* Pre farmárske vozidlá, ako traktory, chcete GPS údaje na zabezpečenie práce na správnych poliach.
* Pre nákladné autá, ktoré prepravujú potraviny do skladov, chcete GPS údaje, ako aj údaje o rýchlosti a zrýchlení na zabezpečenie bezpečnej jazdy, identitu vodiča a údaje o začiatku/konci jazdy na zabezpečenie dodržiavania miestnych zákonov o pracovných hodinách.
* Pre chladiarenské nákladné autá chcete aj údaje o teplote, aby ste zabezpečili, že potraviny nebudú príliš teplé alebo studené a nezkazia sa počas prepravy.

Tieto údaje sa môžu neustále meniť. Napríklad, ak je IoT zariadenie v kabíne nákladného auta, údaje, ktoré odosiela, sa môžu meniť podľa toho, ako sa mení príves, napríklad odosielanie údajov o teplote iba pri použití chladiarenského prívesu.

✅ Aké ďalšie IoT údaje by mohli byť zachytené? Premýšľajte o druhoch nákladu, ktoré môžu nákladné autá prepravovať, ako aj o údajoch o údržbe.

Tieto údaje sa líšia od vozidla k vozidlu, ale všetky sa odosielajú do tej istej IoT služby na spracovanie. IoT služba musí byť schopná spracovať tieto neštruktúrované údaje, ukladať ich spôsobom, ktorý umožňuje ich vyhľadávanie alebo analýzu, ale zároveň pracovať s rôznymi štruktúrami týchto údajov.

### SQL vs NoSQL úložisko

Databázy sú služby, ktoré umožňujú ukladať a vyhľadávať údaje. Databázy sa delia na dva typy - SQL a NoSQL.

#### SQL databázy

Prvé databázy boli relačné databázové systémy (RDBMS), alebo relačné databázy. Tieto sú tiež známe ako SQL databázy podľa jazyka Structured Query Language (SQL), ktorý sa používa na interakciu s nimi na pridávanie, odstraňovanie, aktualizáciu alebo vyhľadávanie údajov. Tieto databázy pozostávajú zo schémy - dobre definovanej sady tabuliek údajov, podobnej tabuľke. Každá tabuľka má viacero pomenovaných stĺpcov. Keď vkladáte údaje, pridávate riadok do tabuľky, pričom vkladáte hodnoty do každého stĺpca. To udržuje údaje v veľmi pevnej štruktúre - aj keď môžete nechať stĺpce prázdne, ak chcete pridať nový stĺpec, musíte to urobiť v databáze, pričom vyplníte hodnoty pre existujúce riadky. Tieto databázy sú relačné - jeden stôl môže mať vzťah k inému.

![Relačná databáza s ID tabuľky používateľov, ktoré sa vzťahuje na stĺpec ID používateľa tabuľky nákupov, a ID tabuľky produktov, ktoré sa vzťahuje na stĺpec ID produktu tabuľky nákupov](../../../../../translated_images/sql-database.be160f12bfccefd3.sk.png)

Napríklad, ak by ste ukladali osobné údaje používateľov do tabuľky, mali by ste nejaké interné jedinečné ID pre každého používateľa, ktoré sa používa v riadku tabuľky obsahujúcej meno a adresu používateľa. Ak by ste potom chceli uložiť ďalšie údaje o tomto používateľovi, ako jeho nákupy, do inej tabuľky, mali by ste jeden stĺpec v novej tabuľke pre ID tohto používateľa. Keď vyhľadávate používateľa, môžete použiť jeho ID na získanie jeho osobných údajov z jednej tabuľky a jeho nákupov z inej.

SQL databázy sú ideálne na ukladanie štruktúrovaných údajov a na zabezpečenie, že údaje zodpovedajú vašej schéme.

✅ Ak ste ešte nepoužívali SQL, chvíľu si prečítajte o ňom na [stránke SQL na Wikipédii](https://wikipedia.org/wiki/SQL).

Niektoré známe SQL databázy sú Microsoft SQL Server, MySQL a PostgreSQL.

✅ Urobte si prieskum: Prečítajte si o niektorých z týchto SQL databáz a ich schopnostiach.

#### NoSQL databázy

NoSQL databázy sa nazývajú NoSQL, pretože nemajú rovnakú pevnú štruktúru ako SQL databázy. Sú tiež známe ako dokumentové databázy, pretože môžu ukladať neštruktúrované údaje, ako dokumenty.

> 💁 Napriek svojmu názvu niektoré NoSQL databázy umožňujú používať SQL na vyhľadávanie údajov.

![Dokumenty v priečinkoch v NoSQL databáze](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.sk.png)

NoSQL databázy nemajú preddefinovanú schému, ktorá obmedzuje spôsob ukladania údajov, namiesto toho môžete vložiť akékoľvek neštruktúrované údaje, zvyčajne pomocou JSON dokumentov. Tieto dokumenty môžu byť organizované do priečinkov, podobne ako súbory vo vašom počítači. Každý dokument môže mať rôzne polia od iných dokumentov - napríklad, ak by ste ukladali IoT údaje z farmárskych vozidiel, niektoré môžu mať polia pre údaje z akcelerometra a rýchlosti, iné môžu mať polia pre teplotu v prívesu. Ak by ste pridali nový typ nákladného auta, napríklad s integrovanými váhami na sledovanie hmotnosti prepravovaného tovaru, vaše IoT zariadenie by mohlo pridať toto nové pole a mohlo by byť uložené bez akýchkoľvek zmien v databáze.

Niektoré známe NoSQL databázy zahŕňajú Azure CosmosDB, MongoDB a CouchDB.

✅ Urobte si prieskum: Prečítajte si o niektorých z týchto NoSQL databáz a ich schopnostiach.

V tejto lekcii budete používať NoSQL úložisko na ukladanie IoT údajov.

## Odoslanie GPS údajov do IoT Hubu

V predchádzajúcej lekcii ste zachytili GPS údaje zo senzora pripojeného k vášmu IoT zariadeniu. Aby ste mohli tieto IoT údaje uložiť v cloude, musíte ich odoslať do IoT služby. Opäť budete používať Azure IoT Hub, tú istú IoT cloudovú službu, ktorú ste použili v predchádzajúcom projekte.

![Odosielanie GPS telemetrie z IoT zariadenia do IoT Hubu](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.sk.png)

### Úloha - odoslanie GPS údajov do IoT Hubu

1. Vytvorte nový IoT Hub pomocou bezplatného plánu.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie IoT Hubu z projektu 2, lekcia 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud), ak je to potrebné.

    Nezabudnite vytvoriť novú Resource Group. Nazvite novú Resource Group `gps-sensor` a nový IoT Hub jedinečným názvom založeným na `gps-sensor`, napríklad `gps-sensor-<vaše meno>`.

    > 💁 Ak stále máte svoj IoT Hub z predchádzajúceho projektu, môžete ho znovu použiť. Nezabudnite použiť názov tohto IoT Hubu a Resource Group, v ktorej sa nachádza, pri vytváraní ďalších služieb.

1. Pridajte nové zariadenie do IoT Hubu. Nazvite toto zariadenie `gps-sensor`. Získajte pripojovací reťazec pre zariadenie.

1. Aktualizujte kód vášho zariadenia na odosielanie GPS údajov do nového IoT Hubu pomocou pripojovacieho reťazca zariadenia z predchádzajúceho kroku.

    > ⚠️ Môžete sa odvolať na [pokyny na pripojenie vášho zariadenia k IoT službe z projektu 2, lekcia 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service), ak je to potrebné.

1. Pri odosielaní GPS údajov to robte vo formáte JSON nasledovne:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Odosielajte GPS údaje každú minútu, aby ste nevyčerpali denný limit správ.

Ak používate Wio Terminal, nezabudnite pridať všetky potrebné knižnice a nastaviť čas pomocou NTP servera. Váš kód bude tiež musieť zabezpečiť, že prečítal všetky údaje zo sériového portu pred odoslaním GPS polohy, pomocou existujúceho kódu z predchádzajúcej lekcie. Použite nasledujúci kód na zostavenie JSON dokumentu:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Ak používate virtuálne IoT zariadenie, nezabudnite nainštalovať všetky potrebné knižnice pomocou virtuálneho prostredia.

Pre Raspberry Pi aj virtuálne IoT zariadenie použite existujúci kód z predchádzajúcej lekcie na získanie hodnôt zemepisnej šírky a dĺžky, potom ich odošlite v správnom formáte JSON pomocou nasledujúceho kódu:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Tento kód nájdete v priečinkoch [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) alebo [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Spustite kód vášho zariadenia a uistite sa, že správy prichádzajú do IoT Hubu pomocou príkazu CLI `az iot hub monitor-events`.

## Horúce, teplé a studené cesty

Údaje, ktoré prúdia z IoT zariadenia do cloudu, sa nie vždy spracovávajú v reálnom čase. Niektoré údaje potrebujú spracovanie v reálnom čase, iné môžu byť spracované o chvíľu neskôr a ďalšie môžu byť spracované oveľa neskôr. Tok údajov do rôznych služieb, ktoré spracovávajú údaje v rôznych časoch, sa označuje ako horúce, teplé a studené cesty.

### Horúca cesta

Horúca cesta sa týka údajov, ktoré je potrebné spracovať v reálnom čase alebo takmer v reálnom čase. Horúce údaje by ste použili na upozornenia, napríklad na upozornenie, že vozidlo sa blíži k depu, alebo že teplota v chladiarenskom nákladnom aute je príliš vysoká.

Na použitie horúcich údajov by váš kód reagoval na udalosti hneď, ako ich prijmú vaše cloudové služby.

### Teplá cesta

Teplá cesta sa týka údajov, ktoré môžu byť spracované krátko po ich prijatí, napríklad na vytváranie správ alebo krátkodobé analýzy. Teplé údaje by ste použili na denné správy o prejdených kilometroch vozidiel, pomocou údajov zhromaždených predchádzajúci deň.

Teplé údaje sa ukladajú hneď po ich prijatí cloudovou službou do nejakého typu úložiska, ktoré je rýchlo prístupné.

### Studená cesta

Studená cesta sa týka historických údajov, ktoré sa ukladajú dlhodobo na spracovanie kedykoľvek je to potrebné. Napríklad by ste mohli použiť studenú cestu na získanie ročných správ o prejdených kilometroch vozidiel alebo na analýzu trás na nájdenie najoptimálnejšej trasy na zníženie nákladov na palivo.

Studené údaje sa ukladajú do dátových skladov - databáz navrhnutých na ukladanie veľkého množstva údajov, ktoré sa nikdy nezmenia a môžu byť rýchlo a jednoducho vyhľadávané. Zvyčajne by ste mali pravidelnú úlohu vo vašej cloudovej aplikácii, ktorá by sa spúšťala v pravidelných intervaloch každý deň, týždeň alebo mesiac na presun údajov z teplého úložiska do dátového skladu.

✅ Premýšľajte o údajoch, ktoré ste doteraz zachytili v týchto lekciách. Sú to horúce, teplé alebo studené údaje?

## Spracovanie GPS udalostí pomocou serverless kódu

Keď údaje prúdia do vášho IoT Hubu, môžete napísať serverless kód na počúvanie udalostí publikovaných na Event-Hub kompatibilnom koncovom bode. Toto je teplá cesta - tieto údaje budú uložené a použité v ďalšej lekcii na vytváranie správ o ceste.

![Odosielanie GPS telemetrie z IoT zariadenia do IoT Hubu, potom do Azure Functions cez trigger Event Hubu](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.sk.png)

### Úloha - spracovanie GPS udalostí pomocou serverless kódu

1. Vytvorte aplikáciu Azure Functions pomocou Azure Functions CLI. Použite runtime Python a vytvorte ju v priečinku `gps-trigger`, pričom použ
> ⚠️ Môžete sa odvolať na [pokyny na vytvorenie projektu Azure Functions z projektu 2, lekcia 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application), ak to bude potrebné.
1. Pridajte spúšťač udalostí IoT Hub, ktorý používa kompatibilný koncový bod Event Hub IoT Hubu.

    > ⚠️ Ak potrebujete, môžete si pozrieť [pokyny na vytvorenie spúšťača udalostí IoT Hub z projektu 2, lekcia 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Nastavte reťazec pripojenia kompatibilného koncového bodu Event Hub v súbore `local.settings.json` a použite kľúč pre tento záznam v súbore `function.json`.

1. Použite aplikáciu Azurite ako lokálny emulátor úložiska.

1. Spustite aplikáciu funkcií, aby ste sa uistili, že prijíma udalosti z vášho GPS zariadenia. Uistite sa, že vaše IoT zariadenie tiež beží a odosiela GPS údaje.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage Accounts

![Logo Azure Storage](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.sk.png)

Azure Storage Accounts je univerzálna služba úložiska, ktorá dokáže ukladať údaje rôznymi spôsobmi. Údaje môžete ukladať ako blob, do frontov, do tabuliek alebo ako súbory, a to všetko naraz.

### Blob úložisko

Slovo *Blob* znamená veľké binárne objekty, ale stalo sa termínom pre akékoľvek nestruktúrované údaje. V blob úložisku môžete ukladať akékoľvek údaje, od JSON dokumentov obsahujúcich IoT údaje až po obrazové a filmové súbory. Blob úložisko má koncept *kontajnerov*, pomenovaných "bucketov", do ktorých môžete ukladať údaje, podobne ako tabuľky v relačnej databáze. Tieto kontajnery môžu obsahovať jeden alebo viac priečinkov na ukladanie blobov, pričom každý priečinok môže obsahovať ďalšie priečinky, podobne ako súbory uložené na pevnom disku vášho počítača.

V tejto lekcii budete používať blob úložisko na ukladanie IoT údajov.

✅ Urobte si prieskum: Prečítajte si o [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Tabuľkové úložisko

Tabuľkové úložisko umožňuje ukladať pološtruktúrované údaje. Tabuľkové úložisko je vlastne NoSQL databáza, takže nevyžaduje vopred definovanú sadu tabuliek, ale je navrhnuté na ukladanie údajov do jednej alebo viacerých tabuliek s jedinečnými kľúčmi na definovanie každého riadku.

✅ Urobte si prieskum: Prečítajte si o [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Frontové úložisko

Frontové úložisko umožňuje ukladať správy do veľkosti 64 KB vo fronte. Správy môžete pridávať na koniec frontu a čítať ich z jeho začiatku. Fronty ukladajú správy neobmedzene dlho, pokiaľ je k dispozícii úložný priestor, čo umožňuje dlhodobé ukladanie správ, ktoré sa potom čítajú podľa potreby. Napríklad, ak chcete spustiť mesačnú úlohu na spracovanie GPS údajov, môžete ich pridávať do frontu každý deň počas mesiaca a na konci mesiaca spracovať všetky správy z frontu.

✅ Urobte si prieskum: Prečítajte si o [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Súborové úložisko

Súborové úložisko je úložisko súborov v cloude, ku ktorému sa môžu pripojiť aplikácie alebo zariadenia pomocou štandardných protokolov. Súbory môžete zapisovať do súborového úložiska a potom ho pripojiť ako disk na vašom PC alebo Macu.

✅ Urobte si prieskum: Prečítajte si o [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Pripojte svoj serverless kód k úložisku

Vaša aplikácia funkcií teraz potrebuje pripojiť sa k blob úložisku, aby mohla ukladať správy z IoT Hubu. Existujú 2 spôsoby, ako to urobiť:

* V rámci kódu funkcie sa pripojte k blob úložisku pomocou Python SDK pre blob úložisko a zapisujte údaje ako blob.
* Použite výstupné väzby funkcie na pripojenie návratovej hodnoty funkcie k blob úložisku, aby sa blob automaticky uložil.

V tejto lekcii použijete Python SDK, aby ste videli, ako pracovať s blob úložiskom.

![Odosielanie GPS telemetrie z IoT zariadenia do IoT Hubu, potom do Azure Functions cez spúšťač udalostí Event Hub, a následne ukladanie do blob úložiska](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.sk.png)

Údaje budú uložené ako JSON blob s nasledujúcim formátom:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Úloha - pripojte svoj serverless kód k úložisku

1. Vytvorte Azure Storage účet. Pomenujte ho napríklad `gps<vaše meno>`.

    > ⚠️ Ak potrebujete, môžete si pozrieť [pokyny na vytvorenie úložného účtu z projektu 2, lekcia 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

    Ak máte úložný účet z predchádzajúceho projektu, môžete ho znovu použiť.

    > 💁 Rovnaký úložný účet budete môcť použiť na nasadenie vašej aplikácie Azure Functions neskôr v tejto lekcii.

1. Spustite nasledujúci príkaz na získanie reťazca pripojenia pre úložný účet:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Nahraďte `<storage_name>` názvom úložného účtu, ktorý ste vytvorili v predchádzajúcom kroku.

1. Pridajte nový záznam do súboru `local.settings.json` pre reťazec pripojenia úložného účtu, pomocou hodnoty z predchádzajúceho kroku. Pomenujte ho `STORAGE_CONNECTION_STRING`.

1. Pridajte nasledujúce do súboru `requirements.txt`, aby ste nainštalovali Azure storage Pip balíčky:

    ```sh
    azure-storage-blob
    ```

    Nainštalujte balíčky z tohto súboru vo vašom virtuálnom prostredí.

    > Ak dostanete chybu, aktualizujte verziu Pip vo vašom virtuálnom prostredí na najnovšiu verziu pomocou nasledujúceho príkazu a skúste to znova:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. V súbore `__init__.py` pre `iot-hub-trigger` pridajte nasledujúce importy:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Modul `json` bude použitý na čítanie a zápis JSON, modul `os` bude použitý na čítanie reťazca pripojenia, modul `uuid` bude použitý na generovanie jedinečného ID pre GPS údaje.

    Balíček `azure.storage.blob` obsahuje Python SDK na prácu s blob úložiskom.

1. Pred metódou `main` pridajte nasledujúcu pomocnú funkciu:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python blob SDK nemá pomocnú metódu na vytvorenie kontajnera, ak neexistuje. Tento kód načíta reťazec pripojenia zo súboru `local.settings.json` (alebo z Application Settings po nasadení do cloudu), potom vytvorí triedu `BlobServiceClient` na interakciu s blob úložiskom. Následne prechádza všetky kontajnery blob úložiska, hľadá jeden s poskytnutým názvom - ak ho nájde, vráti triedu `ContainerClient`, ktorá môže interagovať s kontajnerom na vytváranie blobov. Ak ho nenájde, kontajner sa vytvorí a klient pre nový kontajner sa vráti.

    Keď sa nový kontajner vytvorí, je mu udelený verejný prístup na dotazovanie blobov v kontajneri. Toto bude použité v nasledujúcej lekcii na vizualizáciu GPS údajov na mape.

1. Na rozdiel od vlhkosti pôdy, v tomto kóde chceme uložiť každú udalosť, takže pridajte nasledujúci kód do slučky `for event in events:` v `main` funkcii, pod `logging` príkaz:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Tento kód získa ID zariadenia z metadát udalosti a použije ho na vytvorenie názvu blobu. Bloby môžu byť uložené v priečinkoch a ID zariadenia bude použité ako názov priečinka, takže každé zariadenie bude mať všetky svoje GPS udalosti v jednom priečinku. Názov blobu je tento priečinok, nasledovaný názvom dokumentu, oddelený lomkami, podobne ako cesty v Linuxe a macOS (podobne aj vo Windows, ale Windows používa spätné lomky). Názov dokumentu je jedinečné ID generované pomocou Python modulu `uuid`, s typom súboru `json`.

    Napríklad, pre ID zariadenia `gps-sensor` môže byť názov blobu `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Pridajte nasledujúci kód pod tento:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Tento kód získa klienta kontajnera pomocou pomocnej triedy `get_or_create_container` a potom získa objekt klienta blobu pomocou názvu blobu. Títo klienti blobov môžu odkazovať na existujúce bloby alebo, ako v tomto prípade, na nové bloby.

1. Pridajte nasledujúci kód po tomto:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Tento kód vytvorí telo blobu, ktoré bude zapísané do blob úložiska. Je to JSON dokument obsahujúci ID zariadenia, čas, kedy bola telemetria odoslaná do IoT Hubu, a GPS súradnice z telemetrie.

    > 💁 Je dôležité použiť čas zaradenia správy namiesto aktuálneho času, aby ste získali čas, kedy bola správa odoslaná. Môže byť na hubu chvíľu, kým ju aplikácia funkcií nevyzdvihne, ak nebeží.

1. Pridajte nasledujúci kód pod tento:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Tento kód zaznamenáva, že blob sa chystá byť zapísaný s jeho detailmi, potom nahrá telo blobu ako obsah nového blobu.

1. Spustite aplikáciu funkcií. Uvidíte, že bloby sa zapisujú pre všetky GPS udalosti vo výstupe:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Uistite sa, že nespúšťate monitor udalostí IoT Hubu súčasne.

> 💁 Tento kód nájdete v priečinku [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Úloha - overte nahrané bloby

1. Na zobrazenie vytvorených blobov môžete použiť buď [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), bezplatný nástroj, ktorý umožňuje zobraziť a spravovať vaše úložné účty, alebo CLI.

    1. Na použitie CLI najprv budete potrebovať kľúč účtu. Spustite nasledujúci príkaz na získanie tohto kľúča:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Nahraďte `<storage_name>` názvom úložného účtu.

        Skopírujte hodnotu `key1`.

    1. Spustite nasledujúci príkaz na zoznam blobov v kontajneri:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Nahraďte `<storage_name>` názvom úložného účtu a `<key1>` hodnotou `key1`, ktorú ste skopírovali v predchádzajúcom kroku.

        Toto vypíše všetky bloby v kontajneri:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Stiahnite jeden z blobov pomocou nasledujúceho príkazu:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Nahraďte `<storage_name>` názvom úložného účtu a `<key1>` hodnotou `key1`, ktorú ste skopírovali v predchádzajúcom kroku.

        Nahraďte `<blob_name>` úplným názvom z stĺpca `Name` výstupu z predchádzajúceho kroku, vrátane názvu priečinka. Nahraďte `<file_name>` názvom lokálneho súboru, do ktorého chcete blob uložiť.

    Po stiahnutí môžete otvoriť JSON súbor vo VS Code a uvidíte blob obsahujúci detaily GPS polohy:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Úloha - nasadenie vašej aplikácie funkcií do cloudu

Teraz, keď vaša aplikácia funkcií funguje, môžete ju nasadiť do cloudu.

1. Vytvorte novú aplikáciu Azure Functions, pomocou úložného účtu, ktorý ste vytvorili skôr. Pomenujte ju napríklad `gps-sensor-` a pridajte jedinečný identifikátor na koniec, ako náhodné slová alebo vaše meno.

    > ⚠️ Ak potrebujete, môžete si pozrieť [pokyny na vytvorenie aplikácie funkcií z projektu 2, lekcia 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

1. Nahrajte hodnoty `IOT_HUB_CONNECTION_STRING` a `STORAGE_CONNECTION_STRING` do Application Settings.

    > ⚠️ Ak potrebujete, môžete si pozrieť [pokyny na nahrávanie Application Settings z projektu 2, lekcia 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

1. Nasadenie vašej lokálnej aplikácie funkcií do cloudu.
> ⚠️ Môžete sa odvolať na [pokyny na nasadenie vašej aplikácie Functions z projektu 2, lekcie 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud), ak to bude potrebné.
## 🚀 Výzva

GPS údaje nie sú úplne presné a zistené polohy môžu byť posunuté o niekoľko metrov, ak nie viac, najmä v tuneloch a oblastiach s vysokými budovami.

Premýšľajte o tom, ako by satelitná navigácia mohla tento problém prekonať. Aké údaje má váš satelitný navigačný systém, ktoré by mu umožnili lepšie predpovedať vašu polohu?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Prehľad a samostatné štúdium

* Prečítajte si o štruktúrovaných údajoch na [stránke o dátových modeloch na Wikipédii](https://wikipedia.org/wiki/Data_model)
* Prečítajte si o pološtruktúrovaných údajoch na [stránke o pološtruktúrovaných údajoch na Wikipédii](https://wikipedia.org/wiki/Semi-structured_data)
* Prečítajte si o neštruktúrovaných údajoch na [stránke o neštruktúrovaných údajoch na Wikipédii](https://wikipedia.org/wiki/Unstructured_data)
* Prečítajte si viac o Azure Storage a rôznych typoch úložísk v [dokumentácii k Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Zadanie

[Preskúmajte väzby funkcií](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za záväzný zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.