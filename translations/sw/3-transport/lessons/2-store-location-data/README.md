<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-27T21:52:51+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "sw"
}
-->
# Hifadhi data ya eneo

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa.

## Maswali ya awali ya somo

[Maswali ya awali ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Utangulizi

Katika somo lililopita, ulijifunza jinsi ya kutumia sensa ya GPS kukamata data ya eneo. Ili kutumia data hii kuonyesha eneo la lori lililobeba chakula na safari yake, data hiyo inahitaji kutumwa kwa huduma ya IoT kwenye wingu, kisha kuhifadhiwa mahali fulani.

Katika somo hili utajifunza njia tofauti za kuhifadhi data ya IoT, na jinsi ya kuhifadhi data kutoka kwa huduma yako ya IoT kwa kutumia msimbo usiohitaji seva.

Katika somo hili tutashughulikia:

* [Data iliyopangiliwa na isiyopangiliwa](../../../../../3-transport/lessons/2-store-location-data)
* [Tuma data ya GPS kwa IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Njia za moto, joto, na baridi](../../../../../3-transport/lessons/2-store-location-data)
* [Shughulikia matukio ya GPS kwa kutumia msimbo usiohitaji seva](../../../../../3-transport/lessons/2-store-location-data)
* [Akaunti za Hifadhi za Azure](../../../../../3-transport/lessons/2-store-location-data)
* [Unganisha msimbo wako usiohitaji seva na hifadhi](../../../../../3-transport/lessons/2-store-location-data)

## Data iliyopangiliwa na isiyopangiliwa

Mifumo ya kompyuta hushughulikia data, na data hii huja katika maumbo na ukubwa tofauti. Inaweza kuwa namba moja, maandishi mengi, video na picha, au data ya IoT. Data mara nyingi hugawanywa katika makundi mawili - *data iliyopangiliwa* na *data isiyopangiliwa*.

* **Data iliyopangiliwa** ni data yenye muundo ulioelezwa vizuri, thabiti ambao hauwezi kubadilika na mara nyingi huakisi meza za data zenye uhusiano. Mfano mmoja ni maelezo ya mtu ikiwa ni pamoja na jina lake, tarehe ya kuzaliwa, na anwani.

* **Data isiyopangiliwa** ni data bila muundo ulioelezwa vizuri, thabiti, ikiwa ni pamoja na data inayoweza kubadilika mara kwa mara. Mfano mmoja ni nyaraka kama maandishi au lahajedwali.

✅ Fanya utafiti: Je, unaweza kufikiria mifano mingine ya data iliyopangiliwa na isiyopangiliwa?

> 💁 Kuna pia data ya nusu-pangiliwa ambayo ina muundo lakini haifai katika meza za data zilizowekwa.

Data ya IoT mara nyingi huchukuliwa kuwa data isiyopangiliwa.

Fikiria ungekuwa unaongeza vifaa vya IoT kwenye magari ya kampuni kubwa ya kilimo. Unaweza kutaka kutumia vifaa tofauti kwa aina tofauti za magari. Kwa mfano:

* Kwa magari ya shamba kama matrekta unataka data ya GPS kuhakikisha yanatumika kwenye mashamba sahihi.
* Kwa malori ya kusafirisha chakula kwenda maghala unataka data ya GPS pamoja na data ya kasi na kasi ya kuharakisha kuhakikisha dereva anaendesha kwa usalama, na data ya utambulisho wa dereva na kuanza/kusimama kuhakikisha kufuata sheria za kazi za saa za eneo.
* Kwa malori yenye friji unataka pia data ya joto kuhakikisha chakula hakipati joto au baridi kupita kiasi na kuharibika wakati wa usafiri.

Data hii inaweza kubadilika mara kwa mara. Kwa mfano, ikiwa kifaa cha IoT kiko kwenye kabati la lori, basi data inayotumwa inaweza kubadilika kulingana na mabadiliko ya trela, kwa mfano kutuma data ya joto tu wakati trela yenye friji inatumiwa.

✅ Je, data nyingine ya IoT inaweza kukamatwa? Fikiria aina za mizigo ambayo malori yanaweza kubeba, pamoja na data ya matengenezo.

Data hii inatofautiana kutoka gari moja hadi jingine, lakini yote inatumwa kwa huduma moja ya IoT kwa ajili ya usindikaji. Huduma ya IoT inahitaji kuwa na uwezo wa kusindika data hii isiyopangiliwa, kuihifadhi kwa njia inayoruhusu kutafutwa au kuchambuliwa, lakini inafanya kazi na miundo tofauti ya data hii.

### Hifadhi ya SQL vs NoSQL

Hifadhidata ni huduma zinazokuruhusu kuhifadhi na kuuliza data. Hifadhidata huja katika aina mbili - SQL na NoSQL.

#### Hifadhidata za SQL

Hifadhidata za kwanza zilikuwa Mfumo wa Usimamizi wa Hifadhidata za Uhusiano (RDBMS), au hifadhidata za uhusiano. Hizi pia zinajulikana kama hifadhidata za SQL kutokana na Lugha ya Uulizaji Iliyopangiliwa (SQL) inayotumika kuingiliana nazo ili kuongeza, kuondoa, kusasisha au kuuliza data. Hifadhidata hizi zina muundo - seti iliyoelezwa vizuri ya meza za data, sawa na lahajedwali. Kila meza ina safu nyingi zilizopewa majina. Unapoweka data, unaongeza safu kwenye meza, ukiweka thamani kwenye kila safu. Hii huweka data katika muundo thabiti - ingawa unaweza kuacha safu tupu, ikiwa unataka kuongeza safu mpya lazima ufanye hivyo kwenye hifadhidata, ukijaza thamani kwa safu zilizopo. Hifadhidata hizi zina uhusiano - kwamba meza moja inaweza kuwa na uhusiano na nyingine.

![Hifadhidata ya uhusiano na ID ya meza ya Mtumiaji inayohusiana na safu ya ID ya mtumiaji ya meza ya manunuzi, na ID ya meza ya bidhaa inayohusiana na ID ya bidhaa ya meza ya manunuzi](../../../../../translated_images/sw/sql-database.be160f12bfccefd3.webp)

Kwa mfano, ikiwa ungehifadhi maelezo ya kibinafsi ya mtumiaji kwenye meza, ungekuwa na aina fulani ya ID ya kipekee ya ndani kwa kila mtumiaji inayotumika kwenye safu kwenye meza inayojumuisha jina na anwani ya mtumiaji. Ikiwa ungependa kuhifadhi maelezo mengine kuhusu mtumiaji huyo, kama manunuzi yake, kwenye meza nyingine, ungekuwa na safu moja kwenye meza mpya kwa ID ya mtumiaji huyo. Unapomtafuta mtumiaji, unaweza kutumia ID yake kupata maelezo yake ya kibinafsi kutoka meza moja, na manunuzi yake kutoka nyingine.

Hifadhidata za SQL ni bora kwa kuhifadhi data iliyopangiliwa, na kwa wakati unapotaka kuhakikisha data inalingana na muundo wako.

✅ Ikiwa hujawahi kutumia SQL hapo awali, chukua muda kusoma kuhusu SQL kwenye [ukurasa wa SQL kwenye Wikipedia](https://wikipedia.org/wiki/SQL).

Baadhi ya hifadhidata za SQL zinazojulikana ni Microsoft SQL Server, MySQL, na PostgreSQL.

✅ Fanya utafiti: Soma kuhusu baadhi ya hifadhidata hizi za SQL na uwezo wake.

#### Hifadhidata za NoSQL

Hifadhidata za NoSQL zinaitwa NoSQL kwa sababu hazina muundo thabiti kama hifadhidata za SQL. Pia zinajulikana kama hifadhidata za nyaraka kwa sababu zinaweza kuhifadhi data isiyopangiliwa kama nyaraka.

> 💁 Licha ya jina lao, baadhi ya hifadhidata za NoSQL hukuruhusu kutumia SQL kuuliza data.

![Nyaraka kwenye folda kwenye hifadhidata ya NoSQL](../../../../../translated_images/sw/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.png)

Hifadhidata za NoSQL hazina muundo uliowekwa awali unaozuia jinsi data inavyohifadhiwa, badala yake unaweza kuingiza data yoyote isiyopangiliwa, mara nyingi kwa kutumia nyaraka za JSON. Nyaraka hizi zinaweza kupangwa kwenye folda, sawa na faili kwenye kompyuta yako. Kila nyaraka inaweza kuwa na sehemu tofauti na nyaraka nyingine - kwa mfano ikiwa ungehifadhi data ya IoT kutoka kwa magari ya shamba, baadhi yanaweza kuwa na sehemu za data ya kasi na kasi ya kuharakisha, mengine yanaweza kuwa na sehemu za joto kwenye trela. Ikiwa ungeongeza aina mpya ya lori, kama moja lenye mizani ya ndani kufuatilia uzito wa mazao yanayobebwa, basi kifaa chako cha IoT kinaweza kuongeza sehemu hii mpya na inaweza kuhifadhiwa bila mabadiliko yoyote kwenye hifadhidata.

Baadhi ya hifadhidata za NoSQL zinazojulikana ni Azure CosmosDB, MongoDB, na CouchDB.

✅ Fanya utafiti: Soma kuhusu baadhi ya hifadhidata hizi za NoSQL na uwezo wake.

Katika somo hili, utatumia hifadhi ya NoSQL kuhifadhi data ya IoT.

## Tuma data ya GPS kwa IoT Hub

Katika somo lililopita ulikamata data ya GPS kutoka kwa sensa ya GPS iliyounganishwa na kifaa chako cha IoT. Ili kuhifadhi data hii ya IoT kwenye wingu, unahitaji kuituma kwa huduma ya IoT. Mara nyingine tena, utatumia Azure IoT Hub, huduma ya wingu ya IoT uliyotumia katika mradi uliopita.

![Kutuma telemetry ya GPS kutoka kwa kifaa cha IoT kwenda IoT Hub](../../../../../translated_images/sw/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.png)

### Kazi - tuma data ya GPS kwa IoT Hub

1. Unda IoT Hub mpya kwa kutumia kiwango cha bure.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda IoT Hub kutoka mradi wa 2, somo la 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) ikiwa inahitajika.

    Kumbuka kuunda Kikundi cha Rasilimali kipya. Pea Kikundi cha Rasilimali kipya jina `gps-sensor`, na IoT Hub mpya jina la kipekee kulingana na `gps-sensor`, kama `gps-sensor-<jina lako>`.

    > 💁 Ikiwa bado una IoT Hub yako kutoka mradi uliopita, unaweza kuitumia tena. Kumbuka kutumia jina la IoT Hub hii na Kikundi cha Rasilimali kilichomo wakati wa kuunda huduma nyingine.

1. Ongeza kifaa kipya kwenye IoT Hub. Pea kifaa hiki jina `gps-sensor`. Chukua mnyororo wa muunganisho wa kifaa.

1. Sasisha msimbo wa kifaa chako kutuma data ya GPS kwa IoT Hub mpya kwa kutumia mnyororo wa muunganisho wa kifaa kutoka hatua ya awali.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunganisha kifaa chako na IoT kutoka mradi wa 2, somo la 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) ikiwa inahitajika.

1. Unapotuma data ya GPS, fanya hivyo kama JSON katika muundo ufuatao:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Tuma data ya GPS kila dakika ili usitumie idadi ya ujumbe wa kila siku uliotengwa.

Ikiwa unatumia Wio Terminal, kumbuka kuongeza maktaba zote muhimu, na kuweka muda kwa kutumia seva ya NTP. Msimbo wako pia unahitaji kuhakikisha kuwa umesoma data yote kutoka kwa bandari ya serial kabla ya kutuma eneo la GPS, kwa kutumia msimbo uliopo kutoka somo lililopita. Tumia msimbo ufuatao kuunda nyaraka ya JSON:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Ikiwa unatumia kifaa cha IoT cha Virtual, kumbuka kusakinisha maktaba zote zinazohitajika kwa kutumia mazingira ya virtual.

Kwa Raspberry Pi na kifaa cha IoT cha Virtual, tumia msimbo uliopo kutoka somo lililopita kupata thamani za latitude na longitude, kisha uzitumie katika muundo sahihi wa JSON kwa msimbo ufuatao:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) au [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Endesha msimbo wa kifaa chako na hakikisha ujumbe unafika kwenye IoT Hub kwa kutumia amri ya CLI `az iot hub monitor-events`.

## Njia za moto, joto, na baridi

Data inayotoka kwa kifaa cha IoT kwenda wingu haishughulikiwi kila mara kwa wakati halisi. Data nyingine inahitaji usindikaji wa wakati halisi, data nyingine inaweza kusindika muda mfupi baadaye, na data nyingine inaweza kusindika baadaye sana. Mwelekeo wa data kwenda huduma tofauti zinazoshughulikia data kwa nyakati tofauti hujulikana kama njia za moto, joto, na baridi.

### Njia ya moto

Njia ya moto inahusu data inayohitaji kusindika kwa wakati halisi au karibu na wakati halisi. Ungetumia data ya njia ya moto kwa tahadhari, kama kupata tahadhari kwamba gari linakaribia kituo, au kwamba joto kwenye lori lenye friji ni juu sana.

Ili kutumia data ya njia ya moto, msimbo wako ungetikia matukio mara tu yanapopokelewa na huduma zako za wingu.

### Njia ya joto

Njia ya joto inahusu data inayoweza kusindika muda mfupi baada ya kupokelewa, kwa mfano kwa ripoti au uchambuzi wa muda mfupi. Ungetumia data ya njia ya joto kwa ripoti za kila siku za mileage ya gari, kwa kutumia data iliyokusanywa siku iliyopita.

Data ya njia ya joto huhifadhiwa mara tu inapopokelewa na huduma ya wingu ndani ya aina fulani ya hifadhi inayoweza kufikiwa haraka.

### Njia ya baridi

Njia ya baridi inahusu data ya kihistoria, kuhifadhi data kwa muda mrefu ili kusindika wakati wowote inapohitajika. Kwa mfano, unaweza kutumia njia ya baridi kupata ripoti za mileage ya kila mwaka kwa magari, au kufanya uchambuzi wa njia ili kupata njia bora zaidi kupunguza gharama za mafuta.

Data ya njia ya baridi huhifadhiwa kwenye maghala ya data - hifadhidata zilizoundwa kwa kuhifadhi kiasi kikubwa cha data ambacho hakitabadilika na kinaweza kuulizwa haraka na kwa urahisi. Kwa kawaida ungekuwa na kazi ya kawaida katika programu yako ya wingu ambayo ingefanya kazi kwa wakati wa kawaida kila siku, wiki, au mwezi kuhamisha data kutoka hifadhi ya njia ya joto kwenda kwenye ghala la data.

✅ Fikiria kuhusu data uliyokusanya hadi sasa katika masomo haya. Je, ni data ya njia ya moto, joto, au baridi?

## Shughulikia matukio ya GPS kwa kutumia msimbo usiohitaji seva

Mara data inapokuwa inatiririka kwenye IoT Hub yako, unaweza kuandika msimbo usiohitaji seva kusikiliza matukio yanayochapishwa kwenye endpoint inayolingana na Event-Hub. Hii ni njia ya joto - data hii itahifadhiwa na kutumika katika somo linalofuata kwa ripoti ya safari.

![Kutuma telemetry ya GPS kutoka kwa kifaa cha IoT kwenda IoT Hub, kisha kwa Azure Functions kupitia trigger ya event hub](../../../../../translated_images/sw/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.png)

### Kazi - shughulikia matukio ya GPS kwa kutumia msimbo usiohitaji seva

1. Unda programu ya Azure Functions kwa kutumia CLI ya Azure Functions. Tumia runtime ya Python, na uiunde kwenye folda inayoitwa `gps-trigger`, na tumia jina hilo hilo kwa jina la mradi wa programu ya Functions. Hakikisha unaunda mazingira ya virtual ya kutumia kwa hili.
> ⚠️ Unaweza kurejelea [maelekezo ya kuunda Mradi wa Azure Functions kutoka mradi wa 2, somo la 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) ikiwa inahitajika.
1. Ongeza kichocheo cha tukio la IoT Hub kinachotumia endpoint inayolingana na Event Hub ya IoT Hub.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda kichocheo cha tukio la IoT Hub kutoka mradi wa 2, somo la 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) ikiwa inahitajika.

1. Weka connection string ya endpoint inayolingana na Event Hub kwenye faili `local.settings.json`, na tumia ufunguo wa ingizo hilo kwenye faili `function.json`.

1. Tumia programu ya Azurite kama emulator ya hifadhi ya ndani.

1. Endesha programu yako ya functions ili kuhakikisha inapokea matukio kutoka kwa kifaa chako cha GPS. Hakikisha kifaa chako cha IoT pia kinafanya kazi na kinatuma data ya GPS.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Akaunti za Hifadhi ya Azure

![Nembo ya Azure Storage](../../../../../translated_images/sw/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.png)

Akaunti za Hifadhi ya Azure ni huduma ya hifadhi ya matumizi ya jumla inayoweza kuhifadhi data kwa njia mbalimbali. Unaweza kuhifadhi data kama blobs, kwenye foleni, kwenye meza, au kama faili, na yote kwa wakati mmoja.

### Hifadhi ya Blob

Neno *Blob* linamaanisha binary large objects, lakini limekuwa neno la jumla kwa data isiyo na muundo maalum. Unaweza kuhifadhi data yoyote kwenye hifadhi ya blob, kuanzia hati za JSON zenye data ya IoT, hadi faili za picha na video. Hifadhi ya blob ina dhana ya *containers*, ndoo zilizopewa majina ambapo unaweza kuhifadhi data, sawa na meza kwenye hifadhidata ya uhusiano. Containers hizi zinaweza kuwa na folda moja au zaidi za kuhifadhi blobs, na kila folda inaweza kuwa na folda nyingine, sawa na jinsi faili zinavyohifadhiwa kwenye diski kuu ya kompyuta yako.

Utatumia hifadhi ya blob katika somo hili kuhifadhi data ya IoT.

✅ Fanya utafiti: Soma kuhusu [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Hifadhi ya Meza

Hifadhi ya meza inakuwezesha kuhifadhi data yenye muundo wa nusu. Hifadhi ya meza kimsingi ni hifadhidata ya NoSQL, kwa hivyo haihitaji seti iliyofafanuliwa ya meza mapema, lakini imeundwa kuhifadhi data kwenye meza moja au zaidi, na funguo za kipekee za kufafanua kila safu.

✅ Fanya utafiti: Soma kuhusu [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Hifadhi ya Foleni

Hifadhi ya foleni inakuwezesha kuhifadhi ujumbe wa hadi ukubwa wa 64KB kwenye foleni. Unaweza kuongeza ujumbe mwishoni mwa foleni, na kuusoma mwanzoni. Foleni huhifadhi ujumbe kwa muda mrefu mradi bado kuna nafasi ya hifadhi, hivyo inaruhusu ujumbe kuhifadhiwa kwa muda mrefu na kusomwa inapohitajika. Kwa mfano, ikiwa ungependa kuendesha kazi ya kila mwezi ya kuchakata data ya GPS, ungeweza kuongeza kwenye foleni kila siku kwa mwezi, kisha mwishoni mwa mwezi kuchakata ujumbe wote kutoka kwenye foleni.

✅ Fanya utafiti: Soma kuhusu [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Hifadhi ya Faili

Hifadhi ya faili ni hifadhi ya faili kwenye wingu, na programu au vifaa vyovyote vinaweza kuunganishwa kwa kutumia itifaki za viwango vya tasnia. Unaweza kuandika faili kwenye hifadhi ya faili, kisha kuipachika kama diski kwenye PC au Mac yako.

✅ Fanya utafiti: Soma kuhusu [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Unganisha msimbo wako wa serverless na hifadhi

Sasa programu yako ya functions inahitaji kuunganishwa na hifadhi ya blob ili kuhifadhi ujumbe kutoka kwa IoT Hub. Kuna njia 2 za kufanya hivi:

* Ndani ya msimbo wa function, unganisha na hifadhi ya blob kwa kutumia blob storage Python SDK na uandike data kama blobs.
* Tumia output function binding kuunganisha thamani ya kurudi ya function na hifadhi ya blob na kuwa na blob ihifadhiwe moja kwa moja.

Katika somo hili, utatumia Python SDK kuona jinsi ya kuingiliana na hifadhi ya blob.

![Kutuma telemetry ya GPS kutoka kifaa cha IoT kwenda IoT Hub, kisha Azure Functions kupitia kichocheo cha event hub, kisha kuihifadhi kwenye hifadhi ya blob](../../../../../translated_images/sw/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Data itahifadhiwa kama blob ya JSON yenye muundo ufuatao:

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

### Kazi - unganisha msimbo wako wa serverless na hifadhi

1. Unda akaunti ya Hifadhi ya Azure. Ipe jina kama `gps<jinalako>`.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda akaunti ya hifadhi kutoka mradi wa 2, somo la 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) ikiwa inahitajika.

    Ikiwa bado una akaunti ya hifadhi kutoka mradi uliopita, unaweza kuitumia tena.

    > 💁 Utaweza kutumia akaunti hiyo hiyo ya hifadhi kupeleka programu yako ya Azure Functions baadaye katika somo hili.

1. Endesha amri ifuatayo kupata connection string ya akaunti ya hifadhi:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Badilisha `<storage_name>` na jina la akaunti ya hifadhi uliyoijenga katika hatua ya awali.

1. Ongeza ingizo jipya kwenye faili `local.settings.json` kwa ajili ya connection string ya akaunti yako ya hifadhi, ukitumia thamani kutoka hatua ya awali. Ipe jina `STORAGE_CONNECTION_STRING`.

1. Ongeza yafuatayo kwenye faili `requirements.txt` ili kusakinisha vifurushi vya Pip vya hifadhi ya Azure:

    ```sh
    azure-storage-blob
    ```

    Sakinisha vifurushi kutoka faili hii kwenye mazingira yako ya virtual.

    > Ikiwa utapata hitilafu, basi boresha toleo la Pip kwenye mazingira yako ya virtual hadi toleo la hivi karibuni kwa amri ifuatayo, kisha jaribu tena:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Katika faili `__init__.py` kwa `iot-hub-trigger`, ongeza kauli za uingizaji zifuatazo:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Moduli ya mfumo `json` itatumika kusoma na kuandika JSON, moduli ya mfumo `os` itatumika kusoma connection string, na moduli ya mfumo `uuid` itatumika kuzalisha kitambulisho cha kipekee kwa usomaji wa GPS.

    Kifurushi cha `azure.storage.blob` kina Python SDK ya kufanya kazi na hifadhi ya blob.

1. Kabla ya njia ya `main`, ongeza kazi ya msaidizi ifuatayo:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    SDK ya blob ya Python haina njia ya msaidizi ya kuunda container ikiwa haipo. Msimbo huu utapakia connection string kutoka faili `local.settings.json` (au Application Settings mara baada ya kupelekwa kwenye wingu), kisha kuunda darasa la `BlobServiceClient` kutoka kwa hii ili kuingiliana na akaunti ya hifadhi ya blob. Kisha inazunguka kupitia containers zote za akaunti ya hifadhi ya blob, ikitafuta moja yenye jina lililotolewa - ikiwa itapata moja itarudisha darasa la `ContainerClient` linaloweza kuingiliana na container ili kuunda blobs. Ikiwa haipatikani, basi container inaundwa na mteja wa container mpya unarudishwa.

    Wakati container mpya inaundwa, ufikiaji wa umma unaruhusiwa kuuliza blobs kwenye container. Hii itatumika katika somo lijalo kuona data ya GPS kwenye ramani.

1. Tofauti na unyevu wa udongo, na msimbo huu tunataka kuhifadhi kila tukio, kwa hivyo ongeza msimbo ufuatao ndani ya kitanzi `for event in events:` kwenye kazi ya `main`, chini ya kauli ya `logging`:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Msimbo huu unapata kitambulisho cha kifaa kutoka metadata ya tukio, kisha unakitumia kuunda jina la blob. Blobs zinaweza kuhifadhiwa kwenye folda, na kitambulisho cha kifaa kitatumika kama jina la folda, kwa hivyo kila kifaa kitakuwa na matukio yake yote ya GPS kwenye folda moja. Jina la blob ni folda hii, ikifuatiwa na jina la hati, likitenganishwa na slashes za mbele, sawa na njia za Linux na macOS (sawa na Windows pia, lakini Windows hutumia backslashes). Jina la hati ni kitambulisho cha kipekee kilichozalishwa kwa kutumia moduli ya Python `uuid`, na aina ya faili ya `json`.

    Kwa mfano, kwa kitambulisho cha kifaa `gps-sensor`, jina la blob linaweza kuwa `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Ongeza msimbo ufuatao chini ya hii:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Msimbo huu unapata mteja wa container kwa kutumia darasa la msaidizi `get_or_create_container`, kisha unapata kitu cha mteja wa blob kwa kutumia jina la blob. Wateja hawa wa blob wanaweza kurejelea blobs zilizopo, au kama katika kesi hii, kwa blob mpya.

1. Ongeza msimbo ufuatao baada ya hii:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Hii inajenga mwili wa blob ambao utaandikwa kwenye hifadhi ya blob. Ni hati ya JSON inayojumuisha kitambulisho cha kifaa, wakati telemetry ilipotumwa kwa IoT Hub, na kuratibu za GPS kutoka telemetry.

    > 💁 Ni muhimu kutumia wakati wa ujumbe ulioingia badala ya wakati wa sasa kupata wakati ambao ujumbe ulitumwa. Inaweza kuwa imekaa kwenye hub kwa muda kabla ya kuchukuliwa ikiwa Functions App haifanyi kazi.

1. Ongeza yafuatayo chini ya msimbo huu:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Msimbo huu unarekodi kuwa blob inakaribia kuandikwa na maelezo yake, kisha unapakia mwili wa blob kama maudhui ya blob mpya.

1. Endesha programu ya Functions. Utaona blobs zikiandikwa kwa matukio yote ya GPS kwenye matokeo:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Hakikisha huendeshi mfuatiliaji wa matukio wa IoT Hub kwa wakati mmoja.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Kazi - thibitisha blobs zilizopakiwa

1. Ili kuona blobs zilizoundwa, unaweza kutumia [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), zana ya bure inayokuwezesha kuona na kudhibiti akaunti zako za hifadhi, au kutoka CLI.

    1. Ili kutumia CLI, kwanza utahitaji ufunguo wa akaunti. Endesha amri ifuatayo kupata ufunguo huu:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Badilisha `<storage_name>` na jina la akaunti ya hifadhi.

        Nakili thamani ya `key1`.

    1. Endesha amri ifuatayo kuorodhesha blobs kwenye container:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Badilisha `<storage_name>` na jina la akaunti ya hifadhi, na `<key1>` na thamani ya `key1` uliyonakili katika hatua ya mwisho.

        Hii itaorodhesha blobs zote kwenye container:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Pakua moja ya blobs kwa kutumia amri ifuatayo:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Badilisha `<storage_name>` na jina la akaunti ya hifadhi, na `<key1>` na thamani ya `key1` uliyonakili katika hatua ya awali.

        Badilisha `<blob_name>` na jina kamili kutoka safu ya `Name` ya matokeo ya hatua ya mwisho, ikijumuisha jina la folda. Badilisha `<file_name>` na jina la faili ya ndani ya kuhifadhi blob.

    Mara baada ya kupakuliwa, unaweza kufungua faili ya JSON kwenye VS Code, na utaona blob yenye maelezo ya eneo la GPS:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Kazi - peleka programu yako ya Functions kwenye wingu

Sasa kwa kuwa programu yako ya Function inafanya kazi, unaweza kupeleka kwenye wingu.

1. Unda programu mpya ya Azure Functions, ukitumia akaunti ya hifadhi uliyoijenga awali. Ipe jina kama `gps-sensor-` na ongeza kitambulisho cha kipekee mwishoni, kama maneno ya nasibu au jina lako.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda programu ya Functions kutoka mradi wa 2, somo la 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) ikiwa inahitajika.

1. Pakia thamani za `IOT_HUB_CONNECTION_STRING` na `STORAGE_CONNECTION_STRING` kwenye Application Settings.

    > ⚠️ Unaweza kurejelea [maelekezo ya kupakia Application Settings kutoka mradi wa 2, somo la 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) ikiwa inahitajika.

1. Peleka programu yako ya Functions ya ndani kwenye wingu.
> ⚠️ Unaweza kurejelea [maelekezo ya kupeleka programu yako ya Functions kutoka mradi wa 2, somo la 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) ikiwa inahitajika.
## 🚀 Changamoto

Takwimu za GPS si sahihi kabisa, na maeneo yanayogunduliwa yanaweza kuwa na tofauti ya mita chache, au zaidi hasa katika vichuguu na maeneo yenye majengo marefu.

Fikiria jinsi urambazaji wa satelaiti unaweza kushinda changamoto hii? Ni data gani ambayo sat-nav yako inayo ambayo inaweza kuisaidia kufanya makadirio bora ya eneo lako?

## Jaribio la Baada ya Somo

[Jaribio la Baada ya Somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Mapitio na Kujisomea

* Soma kuhusu data iliyopangiliwa kwenye [ukurasa wa Data model kwenye Wikipedia](https://wikipedia.org/wiki/Data_model)
* Soma kuhusu data isiyo na mpangilio kamili kwenye [ukurasa wa Semi-structured data kwenye Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Soma kuhusu data isiyo na mpangilio kwenye [ukurasa wa Unstructured data kwenye Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Soma zaidi kuhusu Azure Storage na aina tofauti za hifadhi kwenye [nyaraka za Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Kazi

[Chunguza viunganishi vya kazi](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.