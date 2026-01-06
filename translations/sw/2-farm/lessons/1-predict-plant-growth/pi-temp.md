<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T23:14:59+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "sw"
}
-->
# Pima joto - Raspberry Pi

Katika sehemu hii ya somo, utaongeza kihisi cha joto kwenye Raspberry Pi yako.

## Vifaa

Kihisi utakachotumia ni [DHT11 humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), kinachochanganya vihisi viwili katika kifurushi kimoja. Hiki ni kifaa maarufu, na kuna vihisi vingi vinavyopatikana kibiashara vinavyounganisha joto, unyevunyevu, na wakati mwingine shinikizo la anga. Sehemu ya kihisi cha joto ni thermistor ya negative temperature coefficient (NTC), thermistor ambapo upinzani hupungua kadri joto linavyoongezeka.

Hiki ni kihisi cha kidijitali, kwa hivyo kina ADC ya ndani inayounda ishara ya kidijitali inayobeba data ya joto na unyevunyevu ambayo microcontroller inaweza kusoma.

### Unganisha kihisi cha joto

Kihisi cha joto cha Grove kinaweza kuunganishwa na Raspberry Pi.

#### Kazi

Unganisha kihisi cha joto

![Kihisi cha joto cha Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.sw.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya kihisi cha unyevunyevu na joto. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya kidijitali iliyoandikwa **D5** kwenye Grove Base hat iliyounganishwa na Pi. Soketi hii ni ya pili kutoka kushoto, kwenye safu ya soketi karibu na pini za GPIO.

![Kihisi cha joto cha Grove kimeunganishwa kwenye soketi A0](../../../../../translated_images/pi-temperature-sensor.3ff82fff672c8e56.sw.png)

## Programu ya kihisi cha joto

Kifaa sasa kinaweza kupangwa kutumia kihisi cha joto kilichounganishwa.

### Kazi

Panga kifaa.

1. Washa Pi na subiri ianze

1. Fungua VS Code, moja kwa moja kwenye Pi, au unganisha kupitia kiendelezi cha Remote SSH.

    > ⚠️ Unaweza kurejelea [maelekezo ya kusanidi na kufungua VS Code katika somo la 1 ikiwa unahitaji](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Kutoka kwenye terminal, unda folda mpya kwenye saraka ya nyumbani ya mtumiaji `pi` inayoitwa `temperature-sensor`. Unda faili katika folda hii inayoitwa `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Fungua folda hii kwenye VS Code

1. Ili kutumia kihisi cha joto na unyevunyevu, pakiti ya ziada ya Pip inahitaji kusanikishwa. Kutoka kwenye Terminal ndani ya VS Code, endesha amri ifuatayo kusanikisha pakiti hii ya Pip kwenye Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Ongeza msimbo ufuatao kwenye faili `app.py` ili kuingiza maktaba zinazohitajika:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Kauli `from seeed_dht import DHT` inaingiza darasa la `DHT` ili kuingiliana na kihisi cha joto cha Grove kutoka kwenye moduli ya `seeed_dht`.

1. Ongeza msimbo ufuatao baada ya msimbo hapo juu ili kuunda mfano wa darasa linalosimamia kihisi cha joto:

    ```python
    sensor = DHT("11", 5)
    ```

    Hii inatangaza mfano wa darasa la `DHT` linalosimamia kihisi cha **D**igital **H**umidity na **T**emperature. Kigezo cha kwanza kinaambia msimbo kuwa kihisi kinachotumika ni kihisi cha *DHT11* - maktaba unayotumia inaunga mkono aina nyingine za kihisi hiki. Kigezo cha pili kinaambia msimbo kuwa kihisi kimeunganishwa kwenye soketi ya kidijitali `D5` kwenye Grove base hat.

    > ✅ Kumbuka, soketi zote zina namba za kipekee za pini. Pini 0, 2, 4, na 6 ni pini za analogi, pini 5, 16, 18, 22, 24, na 26 ni pini za kidijitali.

1. Ongeza kitanzi kisicho na mwisho baada ya msimbo hapo juu ili kuchukua thamani ya kihisi cha joto na kuitoa kwenye koni:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Simu ya `sensor.read()` inarejesha tuple ya unyevunyevu na joto. Unahitaji tu thamani ya joto, kwa hivyo unyevunyevu unapuuzwa. Thamani ya joto kisha inachapishwa kwenye koni.

1. Ongeza muda mfupi wa sekunde kumi mwishoni mwa `loop` kwani viwango vya joto havihitaji kuchunguzwa kila wakati. Muda wa kulala unapunguza matumizi ya nguvu ya kifaa.

    ```python
    time.sleep(10)
    ```

1. Kutoka kwenye Terminal ya VS Code, endesha yafuatayo ili kuendesha programu yako ya Python:

    ```sh
    python3 app.py
    ```

    Unapaswa kuona thamani za joto zikitolewa kwenye koni. Tumia kitu kupasha kihisi moto, kama vile kubonyeza kidole gumba juu yake, au kutumia feni kuona thamani zikibadilika:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Programu yako ya kihisi cha joto imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutokuelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.