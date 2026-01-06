<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-27T23:55:43+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "tl"
}
-->
# Lokasyon ng Tindahan ng Data

![Isang sketchnote overview ng araling ito](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture Quiz

[Pre-lecture Quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Panimula

Sa nakaraang aralin, natutunan mo kung paano gamitin ang GPS sensor upang makuha ang data ng lokasyon. Upang magamit ang data na ito para maipakita ang lokasyon ng isang trak na may kargang pagkain, at ang paglalakbay nito, kailangang ipadala ito sa isang IoT service sa cloud, at pagkatapos ay itago sa isang lugar.

Sa araling ito, matutunan mo ang iba't ibang paraan ng pag-iimbak ng IoT data, at kung paano mag-imbak ng data mula sa iyong IoT service gamit ang serverless code.

Sa araling ito, tatalakayin natin ang:

* [Structured at unstructured na data](../../../../../3-transport/lessons/2-store-location-data)
* [Magpadala ng GPS data sa isang IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Hot, warm, at cold paths](../../../../../3-transport/lessons/2-store-location-data)
* [I-handle ang GPS events gamit ang serverless code](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage Accounts](../../../../../3-transport/lessons/2-store-location-data)
* [Ikonekta ang iyong serverless code sa storage](../../../../../3-transport/lessons/2-store-location-data)

## Structured at Unstructured na Data

Ang mga computer system ay humahawak ng data, at ang data na ito ay may iba't ibang anyo at laki. Maaaring mag-iba ito mula sa simpleng numero, sa malalaking dami ng teksto, sa mga video at imahe, at sa IoT data. Ang data ay karaniwang nahahati sa dalawang kategorya - *structured* na data at *unstructured* na data.

* **Structured na data** ay data na may malinaw na tinukoy, matibay na istruktura na hindi nagbabago at karaniwang tumutugma sa mga talahanayan ng data na may mga relasyon. Isang halimbawa nito ay ang mga detalye ng isang tao kabilang ang kanilang pangalan, petsa ng kapanganakan, at address.

* **Unstructured na data** ay data na walang malinaw na tinukoy, matibay na istruktura, kabilang ang data na maaaring magbago ng istruktura nang madalas. Isang halimbawa nito ay mga dokumento tulad ng mga nakasulat na dokumento o spreadsheet.

✅ Mag-research: Makakaisip ka ba ng iba pang halimbawa ng structured at unstructured na data?

> 💁 Mayroon ding semi-structured na data na structured ngunit hindi akma sa mga fixed na talahanayan ng data.

Ang IoT data ay karaniwang itinuturing na unstructured na data.

Isipin na nagdadagdag ka ng mga IoT device sa isang fleet ng mga sasakyan para sa isang malaking komersyal na sakahan. Maaaring gusto mong gumamit ng iba't ibang device para sa iba't ibang uri ng sasakyan. Halimbawa:

* Para sa mga sasakyang pang-sakahan tulad ng mga traktora, gusto mo ng GPS data upang matiyak na nagtatrabaho sila sa tamang mga bukid.
* Para sa mga delivery truck na nagdadala ng pagkain sa mga warehouse, gusto mo ng GPS data pati na rin ang bilis at acceleration data upang matiyak na ligtas ang pagmamaneho ng driver, at drive identity at start/stop data upang matiyak ang pagsunod ng driver sa mga lokal na batas sa oras ng trabaho.
* Para sa mga refrigerated truck, gusto mo rin ng temperature data upang matiyak na ang pagkain ay hindi masyadong mainit o malamig at masira sa biyahe.

Ang data na ito ay maaaring magbago nang patuloy. Halimbawa, kung ang IoT device ay nasa cab ng trak, maaaring magbago ang data na ipinapadala nito habang nagbabago ang trailer, halimbawa ay magpadala lamang ng temperature data kapag ginagamit ang isang refrigerated trailer.

✅ Anong iba pang IoT data ang maaaring makuha? Isipin ang mga uri ng kargamento na maaaring dalhin ng mga trak, pati na rin ang data ng maintenance.

Ang data na ito ay nag-iiba mula sa sasakyan patungo sa sasakyan, ngunit lahat ito ay ipinapadala sa parehong IoT service para sa pagproseso. Ang IoT service ay kailangang magproseso ng unstructured na data na ito, iniimbak ito sa isang paraan na maaaring hanapin o suriin, ngunit gumagana sa iba't ibang istruktura ng data na ito.

### SQL vs NoSQL Storage

Ang mga database ay mga serbisyo na nagbibigay-daan sa iyo upang mag-imbak at mag-query ng data. Ang mga database ay may dalawang uri - SQL at NoSQL.

#### SQL Databases

Ang mga unang database ay Relational Database Management Systems (RDBMS), o relational database. Kilala rin ang mga ito bilang SQL databases dahil sa Structured Query Language (SQL) na ginagamit upang makipag-ugnayan sa mga ito upang magdagdag, mag-alis, mag-update, o mag-query ng data. Ang mga database na ito ay binubuo ng isang schema - isang malinaw na tinukoy na hanay ng mga talahanayan ng data, katulad ng isang spreadsheet. Ang bawat talahanayan ay may maraming pinangalanang mga column. Kapag nagpasok ka ng data, nagdaragdag ka ng isang row sa talahanayan, inilalagay ang mga halaga sa bawat column. Pinapanatili nito ang data sa isang napakatibay na istruktura - bagaman maaari mong iwanang walang laman ang mga column, kung nais mong magdagdag ng bagong column, kailangan mong gawin ito sa database, pinupunan ang mga halaga para sa mga umiiral na row. Ang mga database na ito ay relational - kung saan ang isang talahanayan ay maaaring magkaroon ng relasyon sa isa pa.

![Isang relational database kung saan ang ID ng User table ay nauugnay sa user ID column ng purchases table, at ang ID ng products table ay nauugnay sa product ID ng purchases table](../../../../../translated_images/sql-database.be160f12bfccefd3.tl.png)

Halimbawa, kung iniimbak mo ang mga personal na detalye ng isang user sa isang talahanayan, magkakaroon ka ng isang uri ng internal unique ID bawat user na ginagamit sa isang row sa isang talahanayan na naglalaman ng pangalan at address ng user. Kung nais mong mag-imbak ng iba pang detalye tungkol sa user na iyon, tulad ng kanilang mga binili, sa isa pang talahanayan, magkakaroon ka ng isang column sa bagong talahanayan para sa ID ng user na iyon. Kapag hinanap mo ang isang user, maaari mong gamitin ang kanilang ID upang makuha ang kanilang personal na detalye mula sa isang talahanayan, at ang kanilang mga binili mula sa isa pa.

Ang SQL databases ay perpekto para sa pag-iimbak ng structured na data, at para sa kapag nais mong tiyakin na ang data ay tumutugma sa iyong schema.

✅ Kung hindi mo pa nagagamit ang SQL dati, maglaan ng oras upang basahin ito sa [SQL page sa Wikipedia](https://wikipedia.org/wiki/SQL).

Ang ilang kilalang SQL databases ay Microsoft SQL Server, MySQL, at PostgreSQL.

✅ Mag-research: Basahin ang tungkol sa ilan sa mga SQL databases na ito at ang kanilang mga kakayahan.

#### NoSQL Databases

Ang NoSQL databases ay tinatawag na NoSQL dahil wala silang parehong matibay na istruktura ng SQL databases. Kilala rin ang mga ito bilang document databases dahil maaari silang mag-imbak ng unstructured na data tulad ng mga dokumento.

> 💁 Sa kabila ng kanilang pangalan, ang ilang NoSQL databases ay nagbibigay-daan sa iyo na gumamit ng SQL upang mag-query ng data.

![Mga dokumento sa mga folder sa isang NoSQL database](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.tl.png)

Ang NoSQL databases ay walang pre-defined na schema na naglilimita kung paano iniimbak ang data, sa halip maaari kang magpasok ng anumang unstructured na data, karaniwang gamit ang JSON documents. Ang mga dokumentong ito ay maaaring ayusin sa mga folder, katulad ng mga file sa iyong computer. Ang bawat dokumento ay maaaring magkaroon ng iba't ibang mga field mula sa ibang mga dokumento - halimbawa kung iniimbak mo ang IoT data mula sa iyong mga sasakyang pang-sakahan, ang ilan ay maaaring magkaroon ng mga field para sa accelerometer at speed data, ang iba ay maaaring magkaroon ng mga field para sa temperatura sa trailer. Kung magdadagdag ka ng bagong uri ng trak, tulad ng isa na may built-in na timbangan upang subaybayan ang timbang ng kargamento, ang iyong IoT device ay maaaring magdagdag ng bagong field na ito at maaari itong maimbak nang walang anumang pagbabago sa database.

Ang ilang kilalang NoSQL databases ay Azure CosmosDB, MongoDB, at CouchDB.

✅ Mag-research: Basahin ang tungkol sa ilan sa mga NoSQL databases na ito at ang kanilang mga kakayahan.

Sa araling ito, gagamit ka ng NoSQL storage upang mag-imbak ng IoT data.

## Magpadala ng GPS Data sa isang IoT Hub

Sa nakaraang aralin, nakakuha ka ng GPS data mula sa isang GPS sensor na nakakonekta sa iyong IoT device. Upang maimbak ang IoT data na ito sa cloud, kailangan mo itong ipadala sa isang IoT service. Muli, gagamitin mo ang Azure IoT Hub, ang parehong IoT cloud service na ginamit mo sa nakaraang proyekto.

![Pagpapadala ng GPS telemetry mula sa isang IoT device patungo sa IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.tl.png)

### Gawain - Magpadala ng GPS Data sa isang IoT Hub

1. Gumawa ng bagong IoT Hub gamit ang free tier.

    > ⚠️ Maaari mong tingnan ang [mga tagubilin para sa paggawa ng IoT Hub mula sa proyekto 2, aralin 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) kung kinakailangan.

    Tandaan na gumawa ng bagong Resource Group. Pangalanan ang bagong Resource Group na `gps-sensor`, at ang bagong IoT Hub ng isang natatanging pangalan batay sa `gps-sensor`, tulad ng `gps-sensor-<iyong pangalan>`.

    > 💁 Kung mayroon ka pa ring IoT Hub mula sa nakaraang proyekto, maaari mo itong muling gamitin. Tandaan na gamitin ang pangalan ng IoT Hub na ito at ang Resource Group kung saan ito naroroon kapag gumagawa ng iba pang mga serbisyo.

1. Magdagdag ng bagong device sa IoT Hub. Tawagin ang device na ito na `gps-sensor`. Kunin ang connection string para sa device.

1. I-update ang iyong device code upang ipadala ang GPS data sa bagong IoT Hub gamit ang device connection string mula sa nakaraang hakbang.

    > ⚠️ Maaari mong tingnan ang [mga tagubilin para sa pagkonekta ng iyong device sa IoT mula sa proyekto 2, aralin 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) kung kinakailangan.

1. Kapag nagpapadala ng GPS data, gawin ito bilang JSON sa sumusunod na format:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Magpadala ng GPS data bawat minuto upang hindi maubos ang iyong daily message allocation.

Kung gumagamit ka ng Wio Terminal, tandaan na idagdag ang lahat ng kinakailangang libraries, at itakda ang oras gamit ang isang NTP server. Ang iyong code ay kailangan ding tiyakin na nabasa nito ang lahat ng data mula sa serial port bago ipadala ang GPS location, gamit ang umiiral na code mula sa nakaraang aralin. Gamitin ang sumusunod na code upang buuin ang JSON document:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Kung gumagamit ka ng Virtual IoT device, tandaan na i-install ang lahat ng kinakailangang libraries gamit ang virtual environment.

Para sa parehong Raspberry Pi at Virtual IoT device, gamitin ang umiiral na code mula sa nakaraang aralin upang makuha ang latitude at longitude values, pagkatapos ay ipadala ang mga ito sa tamang JSON format gamit ang sumusunod na code:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Maaari mong makita ang code na ito sa [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) o [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device) folder.

Patakbuhin ang iyong device code at tiyakin na ang mga mensahe ay dumadaloy sa IoT Hub gamit ang `az iot hub monitor-events` CLI command.

## Hot, Warm, at Cold Paths

Ang data na dumadaloy mula sa isang IoT device patungo sa cloud ay hindi palaging napoproseso nang real time. Ang ilang data ay kailangang iproseso nang real time, ang iba ay maaaring iproseso nang kaunti pagkatapos, at ang iba ay maaaring iproseso nang mas matagal pa. Ang daloy ng data sa iba't ibang serbisyo na nagpoproseso ng data sa iba't ibang oras ay tinutukoy bilang hot, warm, at cold paths.

### Hot Path

Ang hot path ay tumutukoy sa data na kailangang iproseso nang real time o malapit sa real time. Gagamitin mo ang hot path data para sa mga alerto, tulad ng pagkuha ng alerto na ang isang sasakyan ay papalapit sa depot, o na ang temperatura sa isang refrigerated truck ay masyadong mataas.

Upang magamit ang hot path data, ang iyong code ay tutugon sa mga event sa sandaling matanggap ang mga ito ng iyong cloud services.

### Warm Path

Ang warm path ay tumutukoy sa data na maaaring iproseso nang kaunti pagkatapos matanggap, halimbawa para sa pag-uulat o short-term analytics. Gagamitin mo ang warm path data para sa mga daily report sa mileage ng sasakyan, gamit ang data na nakolekta noong nakaraang araw.

Ang warm path data ay iniimbak sa sandaling matanggap ito ng cloud service sa loob ng isang uri ng storage na maaaring mabilis na ma-access.

### Cold Path

Ang cold path ay tumutukoy sa historical data, iniimbak ang data para sa pangmatagalang paggamit upang iproseso kung kailan kinakailangan. Halimbawa, maaari mong gamitin ang cold path upang makakuha ng taunang mileage reports para sa mga sasakyan, o magsagawa ng analytics sa mga ruta upang mahanap ang pinaka-optimal na ruta upang mabawasan ang gastos sa gasolina.

Ang cold path data ay iniimbak sa mga data warehouses - mga database na idinisenyo para sa pag-iimbak ng malaking dami ng data na hindi magbabago at maaaring ma-query nang mabilis at madali. Karaniwan kang magkakaroon ng regular na trabaho sa iyong cloud application na tatakbo sa regular na oras bawat araw, linggo, o buwan upang ilipat ang data mula sa warm path storage patungo sa data warehouse.

✅ Isipin ang data na nakolekta mo sa mga araling ito. Ito ba ay hot, warm, o cold path data?

## I-handle ang GPS Events Gamit ang Serverless Code

Kapag ang data ay dumadaloy na sa iyong IoT Hub, maaari kang magsulat ng serverless code upang makinig sa mga event na inilathala sa Event-Hub compatible endpoint. Ito ang warm path - ang data na ito ay maiimbak at gagamitin sa susunod na aralin para sa pag-uulat sa paglalakbay.

![Pagpapadala ng GPS telemetry mula sa isang IoT device patungo sa IoT Hub, pagkatapos sa Azure Functions sa pamamagitan ng event hub trigger](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.tl.png)

### Gawain - I-handle ang GPS Events Gamit ang Serverless Code

1. Gumawa ng Azure Functions app gamit ang Azure Functions CLI. Gamitin ang Python runtime, at gawin ito sa isang folder na tinatawag na `gps-trigger`, at gamitin ang parehong pangalan para sa Functions App project name. Siguraduhing gumawa ng virtual environment para dito.
> ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa paglikha ng isang Azure Functions Project mula sa proyekto 2, aralin 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) kung kinakailangan.
1. Magdagdag ng IoT Hub event trigger na gumagamit ng Event Hub compatible endpoint ng IoT Hub.

   > ⚠️ Maaari mong tingnan ang [mga tagubilin para sa paglikha ng IoT Hub event trigger mula sa proyekto 2, aralin 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) kung kinakailangan.

1. Itakda ang Event Hub compatible endpoint connection string sa `local.settings.json` file, at gamitin ang key para sa entry na iyon sa `function.json` file.

1. Gamitin ang Azurite app bilang isang local storage emulator.

1. Patakbuhin ang iyong functions app upang tiyakin na ito ay tumatanggap ng mga event mula sa iyong GPS device. Siguraduhin na ang iyong IoT device ay tumatakbo rin at nagpapadala ng GPS data.

   ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage Accounts

![Ang logo ng Azure Storage](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.tl.png)

Ang Azure Storage Accounts ay isang pangkalahatang serbisyo sa imbakan na maaaring mag-imbak ng data sa iba't ibang paraan. Maaari kang mag-imbak ng data bilang blobs, sa queues, sa tables, o bilang mga files, at lahat ng ito ay sabay-sabay.

### Blob storage

Ang salitang *Blob* ay nangangahulugang binary large objects, ngunit naging termino na ito para sa anumang unstructured data. Maaari kang mag-imbak ng anumang data sa blob storage, mula sa mga JSON document na naglalaman ng IoT data, hanggang sa mga larawan at video files. Ang Blob storage ay may konsepto ng *containers*, mga pinangalanang bucket kung saan maaari kang mag-imbak ng data, na katulad ng mga table sa relational database. Ang mga container na ito ay maaaring magkaroon ng isa o higit pang mga folder upang mag-imbak ng blobs, at bawat folder ay maaaring maglaman ng iba pang mga folder, katulad ng kung paano naka-imbak ang mga file sa iyong computer hard disk.

Gagamitin mo ang blob storage sa araling ito upang mag-imbak ng IoT data.

✅ Mag-research: Basahin ang tungkol sa [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Table storage

Ang Table storage ay nagbibigay-daan sa iyo na mag-imbak ng semi-structured data. Ang Table storage ay isang NoSQL database, kaya hindi nito kinakailangan ang isang pre-defined na set ng mga table, ngunit ito ay idinisenyo upang mag-imbak ng data sa isa o higit pang mga table, na may mga unique key upang tukuyin ang bawat row.

✅ Mag-research: Basahin ang tungkol sa [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Queue storage

Ang Queue storage ay nagbibigay-daan sa iyo na mag-imbak ng mga mensahe na hanggang 64KB ang laki sa isang queue. Maaari kang magdagdag ng mga mensahe sa likod ng queue, at basahin ang mga ito mula sa harapan. Ang mga queue ay nag-iimbak ng mga mensahe nang walang hangganan hangga't may natitirang espasyo sa imbakan, kaya't pinapayagan nitong maimbak ang mga mensahe nang pangmatagalan at mabasa kapag kinakailangan. Halimbawa, kung nais mong magpatakbo ng buwanang trabaho upang iproseso ang GPS data, maaari kang magdagdag nito sa isang queue araw-araw sa loob ng isang buwan, at pagkatapos ay iproseso ang lahat ng mga mensahe mula sa queue sa katapusan ng buwan.

✅ Mag-research: Basahin ang tungkol sa [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### File storage

Ang File storage ay imbakan ng mga file sa cloud, at anumang apps o device ay maaaring kumonekta gamit ang mga industry standard protocols. Maaari kang magsulat ng mga file sa file storage, pagkatapos ay i-mount ito bilang isang drive sa iyong PC o Mac.

✅ Mag-research: Basahin ang tungkol sa [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Ikonekta ang iyong serverless code sa storage

Ang iyong function app ay kailangang kumonekta sa blob storage upang mag-imbak ng mga mensahe mula sa IoT Hub. Mayroong dalawang paraan upang gawin ito:

* Sa loob ng function code, kumonekta sa blob storage gamit ang blob storage Python SDK at isulat ang data bilang blobs.
* Gumamit ng output function binding upang i-bind ang return value ng function sa blob storage at awtomatikong mai-save ang blob.

Sa araling ito, gagamitin mo ang Python SDK upang makita kung paano makipag-ugnayan sa blob storage.

![Pagpapadala ng GPS telemetry mula sa isang IoT device papunta sa IoT Hub, pagkatapos sa Azure Functions sa pamamagitan ng isang event hub trigger, pagkatapos ay sine-save ito sa blob storage](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.tl.png)

Ang data ay mase-save bilang isang JSON blob na may sumusunod na format:

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

### Gawain - ikonekta ang iyong serverless code sa storage

1. Gumawa ng isang Azure Storage account. Pangalanan ito ng tulad ng `gps<iyong pangalan>`.

   > ⚠️ Maaari mong tingnan ang [mga tagubilin para sa paglikha ng storage account mula sa proyekto 2, aralin 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) kung kinakailangan.

   Kung mayroon ka pang storage account mula sa nakaraang proyekto, maaari mo itong muling gamitin.

   > 💁 Magagamit mo ang parehong storage account upang i-deploy ang iyong Azure Functions app mamaya sa araling ito.

1. Patakbuhin ang sumusunod na command upang makuha ang connection string para sa storage account:

   ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

   Palitan ang `<storage_name>` ng pangalan ng storage account na ginawa mo sa nakaraang hakbang.

1. Magdagdag ng bagong entry sa `local.settings.json` file para sa iyong storage account connection string, gamit ang value mula sa nakaraang hakbang. Pangalanan ito bilang `STORAGE_CONNECTION_STRING`.

1. Idagdag ang sumusunod sa `requirements.txt` file upang i-install ang Azure storage Pip packages:

   ```sh
    azure-storage-blob
    ```

   I-install ang mga package mula sa file na ito sa iyong virtual environment.

   > Kung makakakuha ka ng error, i-upgrade ang iyong Pip version sa iyong virtual environment sa pinakabagong bersyon gamit ang sumusunod na command, pagkatapos ay subukang muli:
   >
   > ```sh
    > pip install --upgrade pip
    > ```

1. Sa `__init__.py` file para sa `iot-hub-trigger`, idagdag ang sumusunod na import statements:

   ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

   Ang `json` system module ay gagamitin upang magbasa at magsulat ng JSON, ang `os` system module ay gagamitin upang basahin ang connection string, ang `uuid` system module ay gagamitin upang bumuo ng unique ID para sa GPS reading.

   Ang `azure.storage.blob` package ay naglalaman ng Python SDK upang makipag-ugnayan sa blob storage.

1. Bago ang `main` method, idagdag ang sumusunod na helper function:

   ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

   Ang Python blob SDK ay walang helper method upang lumikha ng container kung wala ito. Ang code na ito ay maglo-load ng connection string mula sa `local.settings.json` file (o mula sa Application Settings kapag na-deploy na sa cloud), pagkatapos ay lilikha ng isang `BlobServiceClient` class mula rito upang makipag-ugnayan sa blob storage account. Pagkatapos ay iikot nito ang lahat ng mga container para sa blob storage account, hinahanap ang isa na may ibinigay na pangalan - kung makakahanap ito, ibabalik nito ang isang `ContainerClient` class na maaaring makipag-ugnayan sa container upang lumikha ng blobs. Kung wala itong makita, lilikha ito ng bagong container at ibabalik ang client para sa bagong container.

   Kapag ang bagong container ay nilikha, bibigyan ito ng public access upang ma-query ang mga blobs sa container. Gagamitin ito sa susunod na aralin upang ma-visualize ang GPS data sa isang mapa.

1. Hindi tulad ng sa soil moisture, sa code na ito nais nating i-save ang bawat event, kaya idagdag ang sumusunod na code sa loob ng `for event in events:` loop sa `main` function, sa ibaba ng `logging` statement:

   ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

   Ang code na ito ay kinukuha ang device ID mula sa event metadata, pagkatapos ay ginagamit ito upang lumikha ng blob name. Ang mga blob ay maaaring maimbak sa mga folder, at ang device ID ay gagamitin bilang pangalan ng folder, kaya ang bawat device ay magkakaroon ng lahat ng GPS events nito sa isang folder. Ang blob name ay ang folder na ito, kasunod ng pangalan ng dokumento, na pinaghihiwalay ng forward slashes, katulad ng Linux at macOS paths (katulad din ng Windows, ngunit ang Windows ay gumagamit ng back slashes). Ang pangalan ng dokumento ay isang unique ID na nabuo gamit ang Python `uuid` module, na may file type na `json`.

   Halimbawa, para sa `gps-sensor` device ID, ang blob name ay maaaring `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Idagdag ang sumusunod na code sa ibaba nito:

   ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

   Ang code na ito ay kumukuha ng container client gamit ang `get_or_create_container` helper class, at pagkatapos ay kumukuha ng blob client object gamit ang blob name. Ang mga blob client ay maaaring tumukoy sa mga umiiral na blob, o tulad ng sa kasong ito, sa bagong blob.

1. Idagdag ang sumusunod na code pagkatapos nito:

   ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

   Ito ay bumubuo ng katawan ng blob na isusulat sa blob storage. Ito ay isang JSON document na naglalaman ng device ID, ang oras na ang telemetry ay ipinadala sa IoT Hub, at ang GPS coordinates mula sa telemetry.

   > 💁 Mahalagang gamitin ang enqueued time ng mensahe sa halip na ang kasalukuyang oras upang makuha ang oras na ang mensahe ay ipinadala. Maaaring ito ay nasa hub nang matagal bago makuha kung ang Functions App ay hindi tumatakbo.

1. Idagdag ang sumusunod sa ibaba ng code na ito:

   ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

   Ang code na ito ay naglo-log na ang isang blob ay isusulat kasama ang mga detalye nito, pagkatapos ay ina-upload ang blob body bilang nilalaman ng bagong blob.

1. Patakbuhin ang Functions app. Makikita mo ang mga blob na isinusulat para sa lahat ng GPS events sa output:

   ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

   > 💁 Siguraduhin na hindi mo pinapatakbo ang IoT Hub event monitor nang sabay.

> 💁 Maaari mong mahanap ang code na ito sa [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions) folder.

### Gawain - i-verify ang mga na-upload na blob

1. Upang makita ang mga blob na nilikha, maaari mong gamitin ang [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), isang libreng tool na nagbibigay-daan sa iyo upang tingnan at pamahalaan ang iyong mga storage account, o mula sa CLI.

   1. Upang gamitin ang CLI, una mong kakailanganin ang account key. Patakbuhin ang sumusunod na command upang makuha ang key na ito:

      ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

      Palitan ang `<storage_name>` ng pangalan ng storage account.

      Kopyahin ang value ng `key1`.

   1. Patakbuhin ang sumusunod na command upang ilista ang mga blob sa container:

      ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

      Palitan ang `<storage_name>` ng pangalan ng storage account, at `<key1>` ng value ng `key1` na kinopya mo sa nakaraang hakbang.

      Ipapakita nito ang lahat ng blob sa container:

      ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

   1. I-download ang isa sa mga blob gamit ang sumusunod na command:

      ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

      Palitan ang `<storage_name>` ng pangalan ng storage account, at `<key1>` ng value ng `key1` na kinopya mo sa naunang hakbang.

      Palitan ang `<blob_name>` ng buong pangalan mula sa `Name` column ng output ng huling hakbang, kabilang ang pangalan ng folder. Palitan ang `<file_name>` ng pangalan ng isang lokal na file upang i-save ang blob.

   Kapag na-download, maaari mong buksan ang JSON file sa VS Code, at makikita mo ang blob na naglalaman ng mga detalye ng GPS location:

   ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Gawain - i-deploy ang iyong Functions App sa cloud

Ngayon na gumagana na ang iyong Function app, maaari mo na itong i-deploy sa cloud.

1. Gumawa ng bagong Azure Functions app, gamit ang storage account na ginawa mo kanina. Pangalanan ito ng tulad ng `gps-sensor-` at magdagdag ng unique identifier sa dulo, tulad ng ilang random na salita o ang iyong pangalan.

   > ⚠️ Maaari mong tingnan ang [mga tagubilin para sa paglikha ng Functions app mula sa proyekto 2, aralin 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) kung kinakailangan.

1. I-upload ang `IOT_HUB_CONNECTION_STRING` at `STORAGE_CONNECTION_STRING` values sa Application Settings.

   > ⚠️ Maaari mong tingnan ang [mga tagubilin para sa pag-upload ng Application Settings mula sa proyekto 2, aralin 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) kung kinakailangan.

1. I-deploy ang iyong lokal na Functions app sa cloud.
> ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa pag-deploy ng iyong Functions app mula sa proyekto 2, aralin 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) kung kinakailangan.
## 🚀 Hamon

Ang GPS data ay hindi palaging eksaktong tama, at ang mga lokasyong natutukoy nito ay maaaring may pagkakaiba ng ilang metro, lalo na sa mga lagusan at lugar na may matataas na gusali.

Pag-isipan kung paano maaaring malampasan ng satellite navigation ang problemang ito? Anong mga datos ang mayroon ang iyong sat-nav na makakatulong upang makagawa ng mas mahusay na prediksyon sa iyong lokasyon?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Review at Pag-aaral sa Sarili

* Magbasa tungkol sa structured data sa [Data model page sa Wikipedia](https://wikipedia.org/wiki/Data_model)
* Magbasa tungkol sa semi-structured data sa [Semi-structured data page sa Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Magbasa tungkol sa unstructured data sa [Unstructured data page sa Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Magbasa pa tungkol sa Azure Storage at ang iba't ibang uri ng storage sa [Azure Storage documentation](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Gawain

[Imbestigahan ang function bindings](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.