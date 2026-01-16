<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-27T21:35:40+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "sv"
}
-->
# Lagra platsdata

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Introduktion

I den senaste lektionen lärde du dig hur man använder en GPS-sensor för att fånga platsdata. För att använda dessa data för att visualisera platsen för en lastbil fullastad med mat och dess resa, behöver de skickas till en IoT-tjänst i molnet och sedan lagras någonstans.

I denna lektion kommer du att lära dig om de olika sätten att lagra IoT-data och hur man lagrar data från din IoT-tjänst med serverlös kod.

I denna lektion kommer vi att täcka:

* [Strukturerad och ostrukturerad data](../../../../../3-transport/lessons/2-store-location-data)
* [Skicka GPS-data till en IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Varma, kalla och heta vägar](../../../../../3-transport/lessons/2-store-location-data)
* [Hantera GPS-händelser med serverlös kod](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage-konton](../../../../../3-transport/lessons/2-store-location-data)
* [Anslut din serverlösa kod till lagring](../../../../../3-transport/lessons/2-store-location-data)

## Strukturerad och ostrukturerad data

Datorsystem hanterar data, och dessa data kommer i alla möjliga olika former och storlekar. De kan variera från enkla siffror till stora mängder text, videor och bilder, samt IoT-data. Data kan vanligtvis delas in i en av två kategorier - *strukturerad* data och *ostrukturerad* data.

* **Strukturerad data** är data med en väldefinierad, rigid struktur som inte förändras och som vanligtvis motsvarar tabeller med data och relationer. Ett exempel är en persons uppgifter, inklusive deras namn, födelsedatum och adress.

* **Ostrukturerad data** är data utan en väldefinierad, rigid struktur, inklusive data som kan ändra struktur ofta. Ett exempel är dokument som skrivna texter eller kalkylblad.

✅ Gör lite efterforskning: Kan du komma på några andra exempel på strukturerad och ostrukturerad data?

> 💁 Det finns också semi-strukturerad data som är strukturerad men som inte passar in i fasta datatabeller.

IoT-data anses vanligtvis vara ostrukturerad data.

Föreställ dig att du lägger till IoT-enheter i en fordonsflotta för en stor kommersiell gård. Du kanske vill använda olika enheter för olika typer av fordon. Till exempel:

* För jordbruksfordon som traktorer vill du ha GPS-data för att säkerställa att de arbetar på rätt fält.
* För leveranslastbilar som transporterar mat till lager vill du ha GPS-data samt hastighets- och accelerationsdata för att säkerställa att föraren kör säkert, samt föraridentitet och start/stopp-data för att säkerställa att föraren följer lokala lagar om arbetstider.
* För kylbilar vill du också ha temperaturdata för att säkerställa att maten inte blir för varm eller kall och förstörs under transporten.

Dessa data kan förändras konstant. Till exempel, om IoT-enheten är i en lastbilshytt, kan de data den skickar förändras när släpet byts ut, till exempel genom att endast skicka temperaturdata när ett kylsläp används.

✅ Vilka andra IoT-data kan fångas? Tänk på vilka typer av laster lastbilar kan transportera, samt underhållsdata.

Dessa data varierar från fordon till fordon, men allt skickas till samma IoT-tjänst för bearbetning. IoT-tjänsten måste kunna bearbeta dessa ostrukturerade data och lagra dem på ett sätt som gör det möjligt att söka eller analysera dem, men som fungerar med olika strukturer för dessa data.

### SQL vs NoSQL-lagring

Databaser är tjänster som gör det möjligt att lagra och söka i data. Databaser finns i två typer - SQL och NoSQL.

#### SQL-databaser

De första databaserna var relationsdatabashanteringssystem (RDBMS), eller relationsdatabaser. Dessa är också kända som SQL-databaser efter Structured Query Language (SQL) som används för att interagera med dem för att lägga till, ta bort, uppdatera eller söka i data. Dessa databaser består av ett schema - en väldefinierad uppsättning datatabeller, liknande ett kalkylblad. Varje tabell har flera namngivna kolumner. När du lägger till data lägger du till en rad i tabellen och fyller i värden i varje kolumn. Detta håller data i en mycket rigid struktur - även om du kan lämna kolumner tomma, måste du lägga till en ny kolumn i databasen och fylla i värden för de befintliga raderna om du vill lägga till en ny kolumn. Dessa databaser är relationella - en tabell kan ha en relation till en annan.

![En relationsdatabas där ID:t i användartabellen relaterar till användar-ID-kolumnen i köp-tabellen, och ID:t i produkttabellen relaterar till produkt-ID:t i köp-tabellen](../../../../../translated_images/sv/sql-database.be160f12bfccefd3.webp)

Till exempel, om du lagrade en användares personliga uppgifter i en tabell, skulle du ha någon form av internt unikt ID per användare som används i en rad i en tabell som innehåller användarens namn och adress. Om du sedan ville lagra andra detaljer om den användaren, som deras köp, i en annan tabell, skulle du ha en kolumn i den nya tabellen för användarens ID. När du söker upp en användare kan du använda deras ID för att få deras personliga uppgifter från en tabell och deras köp från en annan.

SQL-databaser är idealiska för att lagra strukturerad data och för när du vill säkerställa att data matchar ditt schema.

✅ Om du inte har använt SQL tidigare, ta en stund att läsa om det på [SQL-sidan på Wikipedia](https://wikipedia.org/wiki/SQL).

Några välkända SQL-databaser är Microsoft SQL Server, MySQL och PostgreSQL.

✅ Gör lite efterforskning: Läs om några av dessa SQL-databaser och deras funktioner.

#### NoSQL-databaser

NoSQL-databaser kallas NoSQL eftersom de inte har samma rigida struktur som SQL-databaser. De är också kända som dokumentdatabaser eftersom de kan lagra ostrukturerad data som dokument.

> 💁 Trots sitt namn tillåter vissa NoSQL-databaser att du använder SQL för att söka i data.

![Dokument i mappar i en NoSQL-databas](../../../../../translated_images/sv/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.png)

NoSQL-databaser har inte ett fördefinierat schema som begränsar hur data lagras. Istället kan du lägga till vilken ostrukturerad data som helst, vanligtvis med JSON-dokument. Dessa dokument kan organiseras i mappar, liknande filer på din dator. Varje dokument kan ha olika fält jämfört med andra dokument - till exempel om du lagrade IoT-data från dina jordbruksfordon, kan vissa ha fält för accelerometer- och hastighetsdata, medan andra kan ha fält för temperaturen i släpet. Om du skulle lägga till en ny lastbilstyp, som en med inbyggda vågar för att spåra vikten av transporterat gods, kan din IoT-enhet lägga till detta nya fält och det kan lagras utan några ändringar i databasen.

Några välkända NoSQL-databaser inkluderar Azure CosmosDB, MongoDB och CouchDB.

✅ Gör lite efterforskning: Läs om några av dessa NoSQL-databaser och deras funktioner.

I denna lektion kommer du att använda NoSQL-lagring för att lagra IoT-data.

## Skicka GPS-data till en IoT Hub

I den senaste lektionen fångade du GPS-data från en GPS-sensor ansluten till din IoT-enhet. För att lagra dessa IoT-data i molnet behöver du skicka dem till en IoT-tjänst. Återigen kommer du att använda Azure IoT Hub, samma IoT-molntjänst som du använde i det tidigare projektet.

![Skicka GPS-telemetri från en IoT-enhet till IoT Hub](../../../../../translated_images/sv/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.png)

### Uppgift - skicka GPS-data till en IoT Hub

1. Skapa en ny IoT Hub med gratisnivån.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa en IoT Hub från projekt 2, lektion 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) om det behövs.

    Kom ihåg att skapa en ny resursgrupp. Namnge den nya resursgruppen `gps-sensor` och den nya IoT Hub med ett unikt namn baserat på `gps-sensor`, till exempel `gps-sensor-<ditt namn>`.

    > 💁 Om du fortfarande har din IoT Hub från det tidigare projektet kan du återanvända den. Kom ihåg att använda namnet på denna IoT Hub och resursgruppen den finns i när du skapar andra tjänster.

1. Lägg till en ny enhet i IoT Hub. Kalla denna enhet `gps-sensor`. Hämta anslutningssträngen för enheten.

1. Uppdatera din enhetskod för att skicka GPS-data till den nya IoT Hub med hjälp av anslutningssträngen från föregående steg.

    > ⚠️ Du kan hänvisa till [instruktionerna för att ansluta din enhet till en IoT från projekt 2, lektion 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) om det behövs.

1. När du skickar GPS-data, gör det som JSON i följande format:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Skicka GPS-data varje minut så att du inte överskrider din dagliga meddelandeallokering.

Om du använder Wio Terminal, kom ihåg att lägga till alla nödvändiga bibliotek och ställa in tiden med en NTP-server. Din kod måste också säkerställa att den har läst all data från seriella porten innan den skickar GPS-positionen, med hjälp av den befintliga koden från den senaste lektionen. Använd följande kod för att skapa JSON-dokumentet:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Om du använder en virtuell IoT-enhet, kom ihåg att installera alla nödvändiga bibliotek med en virtuell miljö.

För både Raspberry Pi och virtuell IoT-enhet, använd den befintliga koden från den senaste lektionen för att få latitud- och longitudvärden, och skicka dem sedan i rätt JSON-format med följande kod:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Du kan hitta denna kod i mappen [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) eller [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Kör din enhetskod och säkerställ att meddelanden flödar in i IoT Hub med hjälp av kommandot `az iot hub monitor-events` i CLI.

## Varma, kalla och heta vägar

Data som flödar från en IoT-enhet till molnet bearbetas inte alltid i realtid. Vissa data behöver bearbetas i realtid, andra data kan bearbetas en kort stund senare, och andra data kan bearbetas mycket senare. Flödet av data till olika tjänster som bearbetar data vid olika tidpunkter kallas heta, varma och kalla vägar.

### Het väg

Den heta vägen avser data som behöver bearbetas i realtid eller nära realtid. Du skulle använda het väg-data för varningar, till exempel att få varningar om att ett fordon närmar sig en depå eller att temperaturen i en kylbil är för hög.

För att använda het väg-data skulle din kod svara på händelser så snart de tas emot av dina molntjänster.

### Varm väg

Den varma vägen avser data som kan bearbetas en kort stund efter att de tagits emot, till exempel för rapportering eller kortsiktig analys. Du skulle använda varm väg-data för dagliga rapporter om fordonsmätarställning, med data som samlats in föregående dag.

Varm väg-data lagras när de tas emot av molntjänsten i någon form av lagring som kan nås snabbt.

### Kall väg

Den kalla vägen avser historiska data, som lagras på lång sikt för att bearbetas vid behov. Till exempel kan du använda den kalla vägen för att få årliga rapporter om fordonsmätarställning eller köra analyser på rutter för att hitta den mest optimala rutten för att minska bränslekostnader.

Kall väg-data lagras i datalager - databaser designade för att lagra stora mängder data som aldrig förändras och som kan sökas snabbt och enkelt. Du skulle normalt ha ett regelbundet jobb i din molnapplikation som körs vid en regelbunden tid varje dag, vecka eller månad för att flytta data från varm väg-lagring till datalagret.

✅ Tänk på de data du har fångat hittills i dessa lektioner. Är det het, varm eller kall väg-data?

## Hantera GPS-händelser med serverlös kod

När data flödar in i din IoT Hub kan du skriva serverlös kod för att lyssna på händelser som publiceras till den Event-Hub-kompatibla slutpunkten. Detta är den varma vägen - dessa data kommer att lagras och användas i nästa lektion för att rapportera om resan.

![Skicka GPS-telemetri från en IoT-enhet till IoT Hub, sedan till Azure Functions via en event hub-trigger](../../../../../translated_images/sv/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.png)

### Uppgift - hantera GPS-händelser med serverlös kod

1. Skapa en Azure Functions-app med hjälp av Azure Functions CLI. Använd Python-runtime och skapa den i en mapp som heter `gps-trigger`, och använd samma namn för Functions App-projektet. Se till att skapa en virtuell miljö att använda för detta.
> ⚠️ Du kan hänvisa till [instruktionerna för att skapa ett Azure Functions-projekt från projekt 2, lektion 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) om det behövs.
1. Lägg till en IoT Hub-händelseutlösare som använder IoT Hubs Event Hub-kompatibla slutpunkt.

   > ⚠️ Du kan hänvisa till [instruktionerna för att skapa en IoT Hub-händelseutlösare från projekt 2, lektion 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) om det behövs.

1. Ställ in anslutningssträngen för Event Hub-kompatibla slutpunkten i filen `local.settings.json` och använd nyckeln för den posten i filen `function.json`.

1. Använd Azurite-appen som en lokal lagringsemulator.

1. Kör din Functions-app för att säkerställa att den tar emot händelser från din GPS-enhet. Se till att din IoT-enhet också körs och skickar GPS-data.

   ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage-konton

![Azure Storage-logotypen](../../../../../translated_images/sv/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.png)

Azure Storage-konton är en allmän lagringstjänst som kan lagra data på olika sätt. Du kan lagra data som blobbar, i köer, i tabeller eller som filer, och allt detta samtidigt.

### Blob-lagring

Ordet *Blob* betyder binära stora objekt, men har blivit termen för ostrukturerad data. Du kan lagra vilken data som helst i blob-lagring, från JSON-dokument som innehåller IoT-data till bild- och filmfiler. Blob-lagring har konceptet *containers*, namngivna behållare där du kan lagra data, liknande tabeller i en relationsdatabas. Dessa behållare kan ha en eller flera mappar för att lagra blobbar, och varje mapp kan innehålla andra mappar, liknande hur filer lagras på din dators hårddisk.

Du kommer att använda blob-lagring i denna lektion för att lagra IoT-data.

✅ Gör lite efterforskning: Läs om [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Tabell-lagring

Tabell-lagring låter dig lagra semi-strukturerad data. Tabell-lagring är faktiskt en NoSQL-databas, så det krävs inte en fördefinierad uppsättning tabeller, men den är designad för att lagra data i en eller flera tabeller, med unika nycklar för att definiera varje rad.

✅ Gör lite efterforskning: Läs om [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Kö-lagring

Kö-lagring låter dig lagra meddelanden på upp till 64 KB i storlek i en kö. Du kan lägga till meddelanden längst bak i kön och läsa dem från framsidan. Köer lagrar meddelanden på obestämd tid så länge det finns lagringsutrymme, vilket gör att meddelanden kan lagras långsiktigt och läsas när det behövs. Till exempel, om du vill köra ett månatligt jobb för att bearbeta GPS-data kan du lägga till det i en kö varje dag under en månad och sedan bearbeta alla meddelanden i slutet av månaden.

✅ Gör lite efterforskning: Läs om [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Fil-lagring

Fil-lagring är lagring av filer i molnet, och alla appar eller enheter kan ansluta med hjälp av standardprotokoll. Du kan skriva filer till fil-lagring och sedan montera det som en enhet på din PC eller Mac.

✅ Gör lite efterforskning: Läs om [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Anslut din serverlösa kod till lagring

Din Functions-app behöver nu ansluta till blob-lagring för att lagra meddelanden från IoT Hub. Det finns två sätt att göra detta:

* Inuti funktionskoden, anslut till blob-lagring med hjälp av blob-lagringens Python SDK och skriv data som blobbar.
* Använd en utdata-funktionsbindning för att binda returvärdet från funktionen till blob-lagring och låta blobben sparas automatiskt.

I denna lektion kommer du att använda Python SDK för att se hur man interagerar med blob-lagring.

![Skicka GPS-telemetri från en IoT-enhet till IoT Hub, sedan till Azure Functions via en Event Hub-utlösare, och sedan spara det till blob-lagring](../../../../../translated_images/sv/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Data kommer att sparas som en JSON-blob med följande format:

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

### Uppgift - anslut din serverlösa kod till lagring

1. Skapa ett Azure Storage-konto. Namnge det något i stil med `gps<ditt namn>`.

   > ⚠️ Du kan hänvisa till [instruktionerna för att skapa ett lagringskonto från projekt 2, lektion 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) om det behövs.

   Om du fortfarande har ett lagringskonto från det tidigare projektet kan du återanvända detta.

   > 💁 Du kommer att kunna använda samma lagringskonto för att distribuera din Azure Functions-app senare i denna lektion.

1. Kör följande kommando för att få anslutningssträngen för lagringskontot:

   ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

   Ersätt `<storage_name>` med namnet på lagringskontot du skapade i föregående steg.

1. Lägg till en ny post i filen `local.settings.json` för anslutningssträngen till ditt lagringskonto, med värdet från föregående steg. Namnge det `STORAGE_CONNECTION_STRING`.

1. Lägg till följande i filen `requirements.txt` för att installera Azure Storage Pip-paketen:

   ```sh
    azure-storage-blob
    ```

   Installera paketen från denna fil i din virtuella miljö.

   > Om du får ett fel, uppgradera din Pip-version i din virtuella miljö till den senaste versionen med följande kommando och försök igen:
   >
   > ```sh
    > pip install --upgrade pip
    > ```

1. I filen `__init__.py` för `iot-hub-trigger`, lägg till följande importsatser:

   ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

   Modulen `json` kommer att användas för att läsa och skriva JSON, modulen `os` kommer att användas för att läsa anslutningssträngen, och modulen `uuid` kommer att användas för att generera ett unikt ID för GPS-avläsningen.

   Paketet `azure.storage.blob` innehåller Python SDK för att arbeta med blob-lagring.

1. Före metoden `main`, lägg till följande hjälpfunktion:

   ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

   Python blob SDK har ingen hjälpfunktion för att skapa en container om den inte redan finns. Denna kod laddar anslutningssträngen från filen `local.settings.json` (eller applikationsinställningarna när den distribueras till molnet), skapar sedan en `BlobServiceClient`-klass från detta för att interagera med blob-lagringskontot. Den loopar sedan igenom alla containrar för blob-lagringskontot och letar efter en med det angivna namnet - om den hittar en returnerar den en `ContainerClient`-klass som kan interagera med containern för att skapa blobbar. Om den inte hittar någon skapas containern och klienten för den nya containern returneras.

   När den nya containern skapas ges offentlig åtkomst för att fråga blobbarna i containern. Detta kommer att användas i nästa lektion för att visualisera GPS-data på en karta.

1. Till skillnad från jordfuktighet vill vi med denna kod lagra varje händelse, så lägg till följande kod inuti loopen `for event in events:` i funktionen `main`, under `logging`-satsen:

   ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

   Denna kod hämtar enhets-ID från händelsemetadata och använder det för att skapa ett blob-namn. Blobbar kan lagras i mappar, och enhets-ID kommer att användas som mappnamn, så varje enhet kommer att ha alla sina GPS-händelser i en mapp. Blob-namnet är denna mapp följt av ett dokumentnamn, separerat med snedstreck, liknande Linux- och macOS-sökvägar (liknande Windows också, men Windows använder bakåtsnedstreck). Dokumentnamnet är ett unikt ID som genereras med Python-modulen `uuid`, med filtypen `json`.

   Till exempel, för enhets-ID `gps-sensor`, kan blob-namnet vara `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Lägg till följande kod under detta:

   ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

   Denna kod hämtar container-klienten med hjälp av hjälpfunktionen `get_or_create_container` och hämtar sedan ett blob-klientobjekt med hjälp av blob-namnet. Dessa blob-klienter kan hänvisa till befintliga blobbar eller, som i detta fall, till nya blobbar.

1. Lägg till följande kod efter detta:

   ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

   Detta bygger blobbens innehåll som kommer att skrivas till blob-lagring. Det är ett JSON-dokument som innehåller enhets-ID, tiden då telemetrin skickades till IoT Hub och GPS-koordinaterna från telemetrin.

   > 💁 Det är viktigt att använda meddelandets kötid istället för aktuell tid för att få tiden då meddelandet skickades. Det kan ha legat på hubben ett tag innan det plockas upp om Functions-appen inte körs.

1. Lägg till följande kod under detta:

   ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

   Denna kod loggar att en blob är på väg att skrivas med dess detaljer och laddar sedan upp blobbens innehåll som innehållet i den nya blobben.

1. Kör Functions-appen. Du kommer att se blobbar skapas för alla GPS-händelser i utdata:

   ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

   > 💁 Se till att du inte kör IoT Hub-händelseövervakaren samtidigt.

> 💁 Du kan hitta denna kod i mappen [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Uppgift - verifiera de uppladdade blobbarna

1. För att visa de skapade blobbarna kan du antingen använda [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), ett gratisverktyg som låter dig visa och hantera dina lagringskonton, eller från CLI.

   1. För att använda CLI behöver du först en kontonyckel. Kör följande kommando för att få denna nyckel:

      ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

      Ersätt `<storage_name>` med namnet på lagringskontot.

      Kopiera värdet av `key1`.

   1. Kör följande kommando för att lista blobbarna i containern:

      ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

      Ersätt `<storage_name>` med namnet på lagringskontot och `<key1>` med värdet av `key1` som du kopierade i föregående steg.

      Detta kommer att lista alla blobbar i containern:

      ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

   1. Ladda ner en av blobbarna med följande kommando:

      ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

      Ersätt `<storage_name>` med namnet på lagringskontot och `<key1>` med värdet av `key1` som du kopierade i föregående steg.

      Ersätt `<blob_name>` med det fullständiga namnet från kolumnen `Name` i utdata från föregående steg, inklusive mappnamnet. Ersätt `<file_name>` med namnet på en lokal fil för att spara blobben till.

      När den har laddats ner kan du öppna JSON-filen i VS Code, och du kommer att se blobben som innehåller GPS-platsdetaljer:

      ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Uppgift - distribuera din Functions-app till molnet

Nu när din Functions-app fungerar kan du distribuera den till molnet.

1. Skapa en ny Azure Functions-app med hjälp av lagringskontot du skapade tidigare. Namnge detta något i stil med `gps-sensor-` och lägg till en unik identifierare i slutet, som några slumpmässiga ord eller ditt namn.

   > ⚠️ Du kan hänvisa till [instruktionerna för att skapa en Functions-app från projekt 2, lektion 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) om det behövs.

1. Ladda upp värdena för `IOT_HUB_CONNECTION_STRING` och `STORAGE_CONNECTION_STRING` till applikationsinställningarna.

   > ⚠️ Du kan hänvisa till [instruktionerna för att ladda upp applikationsinställningar från projekt 2, lektion 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) om det behövs.

1. Distribuera din lokala Functions-app till molnet.
> ⚠️ Du kan hänvisa till [instruktionerna för att distribuera din Functions-app från projekt 2, lektion 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) om det behövs.
## 🚀 Utmaning

GPS-data är inte helt exakt, och de platser som detekteras kan vara fel med några meter, eller mer, särskilt i tunnlar och områden med höga byggnader.

Fundera på hur satellitnavigering kan hantera detta? Vilken data har din satellitnavigering som kan hjälpa den att göra bättre förutsägelser om din position?

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Granskning & Självstudier

* Läs om strukturerad data på [Data model-sidan på Wikipedia](https://wikipedia.org/wiki/Data_model)
* Läs om semistrukturerad data på [Semistrukturerad data-sidan på Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Läs om ostrukturerad data på [Ostrukturerad data-sidan på Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Läs mer om Azure Storage och de olika lagringstyperna i [Azure Storage-dokumentationen](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Uppgift

[Undersök funktionsbindningar](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.