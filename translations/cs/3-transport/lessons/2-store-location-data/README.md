# Ukládání dat o poloze

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-12.ca7f53039712a3ec.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Úvod

V minulé lekci jste se naučili, jak používat GPS senzor k zachycení dat o poloze. Aby bylo možné tato data vizualizovat, například polohu nákladního vozu s potravinami a jeho cestu, je potřeba je odeslat do IoT služby v cloudu a následně někde uložit.

V této lekci se naučíte různé způsoby ukládání IoT dat a jak ukládat data z vaší IoT služby pomocí serverless kódu.

V této lekci se zaměříme na:

* [Strukturovaná a nestrukturovaná data](../../../../../3-transport/lessons/2-store-location-data)
* [Odesílání GPS dat do IoT Hubu](../../../../../3-transport/lessons/2-store-location-data)
* [Horké, teplé a studené cesty](../../../../../3-transport/lessons/2-store-location-data)
* [Zpracování GPS událostí pomocí serverless kódu](../../../../../3-transport/lessons/2-store-location-data)
* [Účty Azure Storage](../../../../../3-transport/lessons/2-store-location-data)
* [Propojení serverless kódu s úložištěm](../../../../../3-transport/lessons/2-store-location-data)

## Strukturovaná a nestrukturovaná data

Počítačové systémy pracují s daty, která mohou mít různé podoby. Mohou to být jednoduchá čísla, velké množství textu, videa, obrázky nebo IoT data. Data lze obvykle rozdělit do dvou kategorií - *strukturovaná* data a *nestrukturovaná* data.

* **Strukturovaná data** jsou data s dobře definovanou, pevnou strukturou, která se nemění, a obvykle odpovídají tabulkám dat s vazbami. Příkladem mohou být údaje o osobě, jako je jméno, datum narození a adresa.

* **Nestrukturovaná data** jsou data bez pevné, dobře definované struktury, která se může často měnit. Příkladem mohou být dokumenty, jako jsou textové dokumenty nebo tabulky.

✅ Udělejte si průzkum: Napadnou vás další příklady strukturovaných a nestrukturovaných dat?

> 💁 Existují také polostrukturovaná data, která mají strukturu, ale neodpovídají pevným tabulkám dat.

IoT data jsou obvykle považována za nestrukturovaná data.

Představte si, že přidáváte IoT zařízení do flotily vozidel velké komerční farmy. Můžete chtít použít různá zařízení pro různé typy vozidel. Například:

* U zemědělských vozidel, jako jsou traktory, chcete GPS data, abyste zajistili, že pracují na správných polích.
* U nákladních vozů přepravujících potraviny do skladů chcete GPS data, ale také údaje o rychlosti a zrychlení, abyste zajistili bezpečnou jízdu, a údaje o identitě řidiče a začátku/konce jízdy, abyste zajistili dodržování místních zákonů o pracovní době.
* U chladírenských vozů chcete také údaje o teplotě, abyste zajistili, že potraviny během přepravy nezteplají nebo nezmrznou.

Tato data se mohou neustále měnit. Například pokud je IoT zařízení v kabině nákladního vozu, může se data, která odesílá, měnit podle připojeného přívěsu, například odesílat údaje o teplotě pouze tehdy, když je připojen chladírenský přívěs.

✅ Jaká další IoT data by mohla být zachycena? Přemýšlejte o typech nákladů, které mohou nákladní vozy přepravovat, a o datech údržby.

Tato data se liší podle vozidla, ale všechna jsou odesílána do stejné IoT služby ke zpracování. IoT služba musí být schopna zpracovat tato nestrukturovaná data, uložit je způsobem, který umožňuje jejich vyhledávání nebo analýzu, a zároveň pracovat s různými strukturami těchto dat.

### SQL vs NoSQL úložiště

Databáze jsou služby, které umožňují ukládat a dotazovat se na data. Databáze se dělí na dva typy - SQL a NoSQL.

#### SQL databáze

První databáze byly relační databázové systémy (RDBMS), známé také jako SQL databáze podle jazyka Structured Query Language (SQL), který se používá k interakci s nimi pro přidávání, odstraňování, aktualizaci nebo dotazování na data. Tyto databáze mají schéma - dobře definovanou sadu tabulek dat, podobnou tabulce v Excelu. Každá tabulka má více pojmenovaných sloupců. Při vkládání dat přidáváte řádek do tabulky a vkládáte hodnoty do jednotlivých sloupců. To udržuje data v pevné struktuře - i když můžete nechat sloupce prázdné, pokud chcete přidat nový sloupec, musíte to udělat v databázi a vyplnit hodnoty pro stávající řádky. Tyto databáze jsou relační - jedna tabulka může mít vztah k jiné.

![Relační databáze s ID tabulky uživatelů, které se vztahuje k ID uživatele ve sloupci tabulky nákupů, a ID tabulky produktů, které se vztahuje k ID produktu v tabulce nákupů](../../../../../translated_images/cs/sql-database.be160f12bfccefd3.webp)

Například pokud byste ukládali osobní údaje uživatelů do tabulky, měli byste pro každého uživatele nějaké interní jedinečné ID, které se používá v řádku tabulky obsahující jméno a adresu uživatele. Pokud byste pak chtěli uložit další údaje o tomto uživateli, například jeho nákupy, do jiné tabulky, měli byste v nové tabulce jeden sloupec pro ID tohoto uživatele. Při vyhledávání uživatele můžete použít jeho ID k získání osobních údajů z jedné tabulky a jeho nákupů z jiné.

SQL databáze jsou ideální pro ukládání strukturovaných dat a pro situace, kdy chcete zajistit, že data odpovídají vašemu schématu.

✅ Pokud jste SQL ještě nepoužívali, věnujte chvíli přečtení [stránky o SQL na Wikipedii](https://wikipedia.org/wiki/SQL).

Mezi známé SQL databáze patří Microsoft SQL Server, MySQL a PostgreSQL.

✅ Udělejte si průzkum: Přečtěte si o některých z těchto SQL databází a jejich schopnostech.

#### NoSQL databáze

NoSQL databáze se nazývají NoSQL, protože nemají stejnou pevnou strukturu jako SQL databáze. Jsou také známé jako dokumentové databáze, protože mohou ukládat nestrukturovaná data, jako jsou dokumenty.

> 💁 Navzdory svému názvu některé NoSQL databáze umožňují používat SQL k dotazování na data.

![Dokumenty ve složkách v NoSQL databázi](../../../../../translated_images/cs/noqsl-database.62d24ccf5b73f60d.webp)

NoSQL databáze nemají předem definované schéma, které by omezovalo způsob ukládání dat. Můžete do nich vkládat jakákoli nestrukturovaná data, obvykle ve formátu JSON. Tyto dokumenty mohou být organizovány do složek, podobně jako soubory na vašem počítači. Každý dokument může mít jiné pole než ostatní dokumenty - například pokud byste ukládali IoT data z vašich zemědělských vozidel, některá mohou mít pole pro data z akcelerometru a rychlosti, jiná mohou mít pole pro teplotu v přívěsu. Pokud byste přidali nový typ nákladního vozu, například s vestavěnými váhami pro sledování hmotnosti přepravovaného zboží, vaše IoT zařízení by mohlo přidat toto nové pole a mohlo by být uloženo bez jakýchkoli změn v databázi.

Mezi známé NoSQL databáze patří Azure CosmosDB, MongoDB a CouchDB.

✅ Udělejte si průzkum: Přečtěte si o některých z těchto NoSQL databází a jejich schopnostech.

V této lekci budete používat NoSQL úložiště pro ukládání IoT dat.

## Odesílání GPS dat do IoT Hubu

V minulé lekci jste zachytili GPS data z GPS senzoru připojeného k vašemu IoT zařízení. Aby bylo možné tato IoT data uložit v cloudu, je potřeba je odeslat do IoT služby. Opět budete používat Azure IoT Hub, stejnou IoT cloudovou službu, kterou jste použili v předchozím projektu.

![Odesílání GPS telemetrie z IoT zařízení do IoT Hubu](../../../../../translated_images/cs/gps-telemetry-iot-hub.8115335d51cd2c12.webp)

### Úkol - odesílání GPS dat do IoT Hubu

1. Vytvořte nový IoT Hub pomocí bezplatné verze.

    > ⚠️ Můžete se odkazovat na [pokyny pro vytvoření IoT Hubu z projektu 2, lekce 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud), pokud je to potřeba.

    Nezapomeňte vytvořit novou Resource Group. Pojmenujte novou Resource Group `gps-sensor` a nový IoT Hub unikátním názvem založeným na `gps-sensor`, například `gps-sensor-<vaše jméno>`.

    > 💁 Pokud stále máte svůj IoT Hub z předchozího projektu, můžete jej znovu použít. Nezapomeňte použít název tohoto IoT Hubu a Resource Group, ve které se nachází, při vytváření dalších služeb.

1. Přidejte nové zařízení do IoT Hubu. Pojmenujte toto zařízení `gps-sensor`. Získejte připojovací řetězec pro zařízení.

1. Aktualizujte kód svého zařízení tak, aby odesílal GPS data do nového IoT Hubu pomocí připojovacího řetězce zařízení z předchozího kroku.

    > ⚠️ Můžete se odkazovat na [pokyny pro připojení vašeho zařízení k IoT z projektu 2, lekce 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service), pokud je to potřeba.

1. Při odesílání GPS dat je odesílejte ve formátu JSON následujícím způsobem:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Odesílejte GPS data každou minutu, abyste nevyčerpali svůj denní limit zpráv.

Pokud používáte Wio Terminal, nezapomeňte přidat všechny potřebné knihovny a nastavit čas pomocí NTP serveru. Váš kód také musí zajistit, že přečte všechna data ze sériového portu před odesláním GPS polohy, pomocí stávajícího kódu z minulé lekce. Použijte následující kód pro vytvoření JSON dokumentu:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Pokud používáte virtuální IoT zařízení, nezapomeňte nainstalovat všechny potřebné knihovny pomocí virtuálního prostředí.

Pro Raspberry Pi i virtuální IoT zařízení použijte stávající kód z minulé lekce k získání hodnot zeměpisné šířky a délky a poté je odešlete ve správném formátu JSON pomocí následujícího kódu:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Tento kód najdete ve složce [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) nebo [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Spusťte kód svého zařízení a ujistěte se, že zprávy proudí do IoT Hubu pomocí příkazu CLI `az iot hub monitor-events`.

## Horké, teplé a studené cesty

Data, která proudí z IoT zařízení do cloudu, nejsou vždy zpracovávána v reálném čase. Některá data je potřeba zpracovat okamžitě, jiná mohou být zpracována o něco později a další mohou být zpracována až mnohem později. Tok dat do různých služeb, které data zpracovávají v různých časech, se označuje jako horké, teplé a studené cesty.

### Horká cesta

Horká cesta se týká dat, která je potřeba zpracovat v reálném čase nebo téměř v reálném čase. Horká data byste použili například pro upozornění, že se vozidlo blíží k depu, nebo že teplota v chladírenském voze je příliš vysoká.

Pro použití horkých dat by váš kód reagoval na události ihned po jejich přijetí cloudovými službami.

### Teplá cesta

Teplá cesta se týká dat, která mohou být zpracována krátce po přijetí, například pro reporty nebo krátkodobé analýzy. Teplá data byste použili například pro denní reporty o ujetých kilometrech vozidel, využívající data z předchozího dne.

Teplá data jsou uložena ihned po přijetí cloudovou službou v nějakém typu úložiště, které lze rychle přistupovat.

### Studená cesta

Studená cesta se týká historických dat, která jsou ukládána dlouhodobě a mohou být zpracována kdykoli. Například byste mohli použít studená data pro roční reporty o ujetých kilometrech vozidel nebo pro analýzu tras za účelem nalezení nejoptimálnější trasy pro snížení nákladů na palivo.

Studená data jsou ukládána v datových skladech - databázích navržených pro ukládání velkého množství dat, která se nikdy nemění a lze je rychle a snadno dotazovat. Obvykle byste měli pravidelnou úlohu ve své cloudové aplikaci, která by běžela v pravidelných intervalech (denně, týdně nebo měsíčně) a přesouvala data z teplého úložiště do datového skladu.

✅ Přemýšlejte o datech, která jste dosud v těchto lekcích zachytili. Jsou to horká, teplá nebo studená data?

## Zpracování GPS událostí pomocí serverless kódu

Jakmile data proudí do vašeho IoT Hubu, můžete napsat serverless kód, který bude naslouchat událostem publikovaným na Event-Hub kompatibilním endpointu. Toto je teplá cesta - tato data budou uložena a použita v další lekci pro reportování cesty.

![Odesílání GPS telemetrie z IoT zařízení do IoT Hubu a poté do Azure Functions pomocí triggeru Event Hub](../../../../../translated_images/cs/gps-telemetry-iot-hub-functions.24d3fa5592455e9f.webp)

### Úkol - zpracování GPS událostí pomocí serverless kódu

1. Vytvořte aplikaci Azure Functions pomocí Azure Functions CLI. Použijte runtime Python a vytvořte ji ve složce `gps-trigger`, přičemž použijte stejný název pro projekt aplikace Functions. Ujistěte se, že vytvoříte virtuální prostředí pro použití.
> ⚠️ Můžete se odkazovat na [instrukce pro vytvoření projektu Azure Functions z projektu 2, lekce 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application), pokud to bude potřeba.
1. Přidejte trigger události IoT Hub, který využívá kompatibilní endpoint Event Hubu IoT Hubu.

    > ⚠️ Pokud potřebujete, můžete se podívat na [instrukce pro vytvoření triggeru události IoT Hub z projektu 2, lekce 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Nastavte připojovací řetězec kompatibilního endpointu Event Hubu v souboru `local.settings.json` a použijte klíč pro tento záznam v souboru `function.json`.

1. Použijte aplikaci Azurite jako lokální emulátor úložiště.

1. Spusťte aplikaci funkcí, abyste ověřili, že přijímá události z vašeho GPS zařízení. Ujistěte se, že vaše IoT zařízení také běží a odesílá GPS data.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Účty Azure Storage

![Logo Azure Storage](../../../../../translated_images/cs/azure-storage-logo.605c0f602c640d48.webp)

Účty Azure Storage jsou univerzální službou úložiště, která umožňuje ukládat data různými způsoby. Data můžete ukládat jako blob, do front, do tabulek nebo jako soubory, a to vše současně.

### Blob úložiště

Slovo *Blob* znamená binární velké objekty, ale stalo se termínem pro jakákoli nestrukturovaná data. V blob úložišti můžete ukládat jakákoli data, od JSON dokumentů obsahujících IoT data až po obrazové a filmové soubory. Blob úložiště má koncept *kontejnerů*, pojmenovaných "bucketů", do kterých můžete ukládat data, podobně jako tabulky v relační databázi. Tyto kontejnery mohou obsahovat jednu nebo více složek pro ukládání blobů, a každá složka může obsahovat další složky, podobně jako jsou soubory ukládány na pevný disk vašeho počítače.

V této lekci budete používat blob úložiště k ukládání IoT dat.

✅ Udělejte si průzkum: Přečtěte si o [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Tabulkové úložiště

Tabulkové úložiště umožňuje ukládat polostrukturovaná data. Tabulkové úložiště je ve skutečnosti NoSQL databáze, takže nevyžaduje předem definovanou sadu tabulek, ale je navrženo pro ukládání dat do jedné nebo více tabulek s unikátními klíči pro definování každého řádku.

✅ Udělejte si průzkum: Přečtěte si o [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Frontové úložiště

Frontové úložiště umožňuje ukládat zprávy o velikosti až 64 KB do fronty. Zprávy můžete přidávat na konec fronty a číst je z jejího začátku. Fronty ukládají zprávy neomezeně dlouho, pokud je stále k dispozici úložný prostor, což umožňuje dlouhodobé ukládání zpráv, které lze číst, když je to potřeba. Například pokud chcete spustit měsíční úlohu na zpracování GPS dat, můžete je každý den přidávat do fronty a na konci měsíce zpracovat všechny zprávy z fronty.

✅ Udělejte si průzkum: Přečtěte si o [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Souborové úložiště

Souborové úložiště umožňuje ukládání souborů v cloudu, ke kterým se mohou připojit aplikace nebo zařízení pomocí standardních průmyslových protokolů. Soubory můžete zapisovat do souborového úložiště a poté je připojit jako disk na vašem PC nebo Macu.

✅ Udělejte si průzkum: Přečtěte si o [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Připojení serverless kódu k úložišti

Vaše aplikace funkcí nyní potřebuje připojit blob úložiště, aby mohla ukládat zprávy z IoT Hubu. Existují dva způsoby, jak to udělat:

* Uvnitř kódu funkce připojte blob úložiště pomocí Python SDK pro blob úložiště a zapisujte data jako blob.
* Použijte výstupní vazbu funkce k propojení návratové hodnoty funkce s blob úložištěm a automaticky uložit blob.

V této lekci použijete Python SDK, abyste viděli, jak pracovat s blob úložištěm.

![Odesílání GPS telemetrie z IoT zařízení do IoT Hubu, poté do Azure Functions přes trigger Event Hubu, a následné ukládání do blob úložiště](../../../../../translated_images/cs/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Data budou uložena jako JSON blob s následujícím formátem:

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

### Úkol - připojení serverless kódu k úložišti

1. Vytvořte účet Azure Storage. Pojmenujte ho například `gps<vaše jméno>`.

    > ⚠️ Pokud potřebujete, můžete se podívat na [instrukce pro vytvoření účtu úložiště z projektu 2, lekce 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

    Pokud máte účet úložiště z předchozího projektu, můžete ho znovu použít.

    > 💁 Budete moci použít stejný účet úložiště k nasazení vaší aplikace Azure Functions později v této lekci.

1. Spusťte následující příkaz pro získání připojovacího řetězce pro účet úložiště:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Nahraďte `<storage_name>` názvem účtu úložiště, který jste vytvořili v předchozím kroku.

1. Přidejte nový záznam do souboru `local.settings.json` pro připojovací řetězec vašeho účtu úložiště, pomocí hodnoty z předchozího kroku. Pojmenujte ho `STORAGE_CONNECTION_STRING`.

1. Přidejte následující do souboru `requirements.txt`, abyste nainstalovali balíčky Azure storage Pip:

    ```sh
    azure-storage-blob
    ```

    Nainstalujte balíčky z tohoto souboru ve vašem virtuálním prostředí.

    > Pokud narazíte na chybu, aktualizujte verzi Pip ve vašem virtuálním prostředí na nejnovější verzi pomocí následujícího příkazu a zkuste to znovu:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. V souboru `__init__.py` pro `iot-hub-trigger` přidejte následující importovací příkazy:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Modul `json` bude použit pro čtení a zápis JSON, modul `os` bude použit pro čtení připojovacího řetězce, modul `uuid` bude použit pro generování unikátního ID pro GPS záznam.

    Balíček `azure.storage.blob` obsahuje Python SDK pro práci s blob úložištěm.

1. Před metodou `main` přidejte následující pomocnou funkci:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python blob SDK nemá pomocnou metodu pro vytvoření kontejneru, pokud neexistuje. Tento kód načte připojovací řetězec ze souboru `local.settings.json` (nebo z Application Settings po nasazení do cloudu), poté vytvoří třídu `BlobServiceClient` pro interakci s účtem blob úložiště. Následně prochází všechny kontejnery účtu blob úložiště, hledá jeden s poskytnutým názvem - pokud ho najde, vrátí třídu `ContainerClient`, která může interagovat s kontejnerem pro vytvoření blobů. Pokud ho nenajde, kontejner je vytvořen a klient pro nový kontejner je vrácen.

    Když je nový kontejner vytvořen, je mu udělen veřejný přístup pro dotazování blobů v kontejneru. To bude použito v další lekci pro vizualizaci GPS dat na mapě.

1. Na rozdíl od vlhkosti půdy chceme s tímto kódem uložit každou událost, takže přidejte následující kód uvnitř smyčky `for event in events:` v metodě `main`, pod příkazem `logging`:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Tento kód získá ID zařízení z metadat události a poté ho použije k vytvoření názvu blobu. Bloby mohou být ukládány do složek, a ID zařízení bude použito jako název složky, takže každé zařízení bude mít všechny své GPS události v jedné složce. Název blobu je tato složka, následovaná názvem dokumentu, oddělená lomítky, podobně jako cesty v Linuxu a macOS (podobně i ve Windows, ale Windows používá zpětná lomítka). Název dokumentu je unikátní ID generované pomocí modulu Python `uuid`, s typem souboru `json`.

    Například pro ID zařízení `gps-sensor` může být název blobu `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Přidejte následující kód pod tento:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Tento kód získá klienta kontejneru pomocí pomocné třídy `get_or_create_container` a poté získá objekt klienta blobu pomocí názvu blobu. Tito klienti blobů mohou odkazovat na existující bloby, nebo jako v tomto případě, na nové bloby.

1. Přidejte následující kód po tomto:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Tento kód vytvoří tělo blobu, které bude zapsáno do blob úložiště. Jedná se o JSON dokument obsahující ID zařízení, čas, kdy byla telemetrie odeslána do IoT Hubu, a GPS souřadnice z telemetrie.

    > 💁 Je důležité použít čas zařazení zprávy místo aktuálního času, abyste získali čas, kdy byla zpráva odeslána. Může být na hubu nějakou dobu, než bude vyzvednuta, pokud aplikace funkcí neběží.

1. Přidejte následující pod tento kód:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Tento kód zaznamená, že blob bude zapsán s jeho detaily, poté nahraje tělo blobu jako obsah nového blobu.

1. Spusťte aplikaci funkcí. Uvidíte, že bloby jsou zapisovány pro všechny GPS události ve výstupu:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Ujistěte se, že současně neběží monitor událostí IoT Hubu.

> 💁 Tento kód najdete ve složce [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Úkol - ověření nahraných blobů

1. Pro zobrazení vytvořených blobů můžete použít buď [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), bezplatný nástroj, který umožňuje zobrazit a spravovat vaše účty úložiště, nebo CLI.

    1. Pro použití CLI budete nejprve potřebovat klíč účtu. Spusťte následující příkaz pro získání tohoto klíče:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Nahraďte `<storage_name>` názvem účtu úložiště.

        Zkopírujte hodnotu `key1`.

    1. Spusťte následující příkaz pro vypsání blobů v kontejneru:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Nahraďte `<storage_name>` názvem účtu úložiště a `<key1>` hodnotou `key1`, kterou jste zkopírovali v předchozím kroku.

        Tento příkaz vypíše všechny bloby v kontejneru:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Stáhněte jeden z blobů pomocí následujícího příkazu:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Nahraďte `<storage_name>` názvem účtu úložiště a `<key1>` hodnotou `key1`, kterou jste zkopírovali v předchozím kroku.

        Nahraďte `<blob_name>` plným názvem ze sloupce `Name` výstupu z předchozího kroku, včetně názvu složky. Nahraďte `<file_name>` názvem lokálního souboru, do kterého chcete blob uložit.

    Po stažení můžete otevřít JSON soubor ve VS Code a uvidíte blob obsahující detaily GPS polohy:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Úkol - nasazení vaší aplikace funkcí do cloudu

Nyní, když vaše aplikace funkcí funguje, ji můžete nasadit do cloudu.

1. Vytvořte novou aplikaci Azure Functions, pomocí účtu úložiště, který jste vytvořili dříve. Pojmenujte ji například `gps-sensor-` a přidejte unikátní identifikátor na konec, například nějaká náhodná slova nebo vaše jméno.

    > ⚠️ Pokud potřebujete, můžete se podívat na [instrukce pro vytvoření aplikace funkcí z projektu 2, lekce 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources).

1. Nahrajte hodnoty `IOT_HUB_CONNECTION_STRING` a `STORAGE_CONNECTION_STRING` do Application Settings.

    > ⚠️ Pokud potřebujete, můžete se podívat na [instrukce pro nahrání Application Settings z projektu 2, lekce 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

1. Nasazte vaši lokální aplikaci funkcí do cloudu.
> ⚠️ Můžete se odkazovat na [instrukce pro nasazení vaší aplikace Functions z projektu 2, lekce 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud), pokud to bude potřeba.
---

## 🚀 Výzva

GPS data nejsou dokonale přesná a detekované polohy mohou být posunuté o několik metrů, nebo i více, zejména v tunelech a oblastech s vysokými budovami.

Přemýšlejte o tom, jak by satelitní navigace mohla tento problém překonat. Jaké údaje má váš satelitní navigační systém, které by mu umožnily lépe předpovědět vaši polohu?

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Přehled & Samostudium

* Přečtěte si o strukturovaných datech na [stránce o datovém modelu na Wikipedii](https://wikipedia.org/wiki/Data_model)
* Přečtěte si o polostrukturovaných datech na [stránce o polostrukturovaných datech na Wikipedii](https://wikipedia.org/wiki/Semi-structured_data)
* Přečtěte si o nestrukturovaných datech na [stránce o nestrukturovaných datech na Wikipedii](https://wikipedia.org/wiki/Unstructured_data)
* Přečtěte si více o Azure Storage a různých typech úložišť v [dokumentaci Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Úkol

[Prozkoumejte vazby funkcí](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.