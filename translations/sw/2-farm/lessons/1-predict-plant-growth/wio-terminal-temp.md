<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T23:23:15+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "sw"
}
-->
# Pima joto - Wio Terminal

Katika sehemu hii ya somo, utaongeza kihisi cha joto kwenye Wio Terminal yako, na kusoma thamani za joto kutoka kwake.

## Vifaa

Wio Terminal inahitaji kihisi cha joto.

Kihisi utakachotumia ni [DHT11 humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), kinachochanganya vihisi viwili katika kifurushi kimoja. Hiki ni maarufu sana, na kuna vihisi vingi vinavyopatikana kibiashara vinavyounganisha joto, unyevunyevu, na wakati mwingine shinikizo la anga. Sehemu ya kihisi cha joto ni thermistor ya negative temperature coefficient (NTC), thermistor ambapo upinzani hupungua kadri joto linavyoongezeka.

Hiki ni kihisi cha kidijitali, kwa hivyo kina ADC ya ndani inayounda ishara ya kidijitali inayobeba data ya joto na unyevunyevu ambayo microcontroller inaweza kusoma.

### Unganisha kihisi cha joto

Kihisi cha joto cha Grove kinaweza kuunganishwa kwenye bandari ya kidijitali ya Wio Terminal.

#### Kazi - unganisha kihisi cha joto

Unganisha kihisi cha joto.

![Kihisi cha joto cha Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.sw.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya kihisi cha unyevunyevu na joto. Itaingia kwa njia moja tu.

1. Ukiwa na Wio Terminal imekatwa kutoka kwa kompyuta yako au chanzo kingine cha nguvu, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya kulia ya Grove kwenye Wio Terminal ukiangalia skrini. Hii ni soketi iliyo mbali zaidi na kitufe cha nguvu.

![Kihisi cha joto cha Grove kimeunganishwa kwenye soketi ya kulia](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a.sw.png)

## Programu ya kihisi cha joto

Sasa Wio Terminal inaweza kupangwa kutumia kihisi cha joto kilichounganishwa.

### Kazi - panga kihisi cha joto

Panga kifaa.

1. Unda mradi mpya wa Wio Terminal ukitumia PlatformIO. Uite mradi huu `temperature-sensor`. Ongeza msimbo kwenye kazi ya `setup` ili kusanidi bandari ya serial.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda mradi wa PlatformIO katika mradi wa 1, somo la 1 ikiwa unahitaji](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Ongeza utegemezi wa maktaba ya Seeed Grove Humidity and Temperature sensor kwenye faili ya mradi `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Unaweza kurejelea [maelekezo ya kuongeza maktaba kwenye mradi wa PlatformIO katika mradi wa 1, somo la 4 ikiwa unahitaji](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Ongeza maagizo yafuatayo ya `#include` juu ya faili, chini ya `#include <Arduino.h>` iliyopo:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Hii inaingiza faili zinazohitajika kuingiliana na kihisi. Faili ya kichwa `DHT.h` ina msimbo wa kihisi chenyewe, na kuongeza faili ya kichwa `SPI.h` inahakikisha msimbo unaohitajika kuzungumza na kihisi umeunganishwa wakati programu inakompailiwa.

1. Kabla ya kazi ya `setup`, tangaza kihisi cha DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Hii inatangaza mfano wa darasa la `DHT` linalosimamia kihisi cha **D**igital **H**umidity na **T**emperature. Hii imeunganishwa kwenye bandari `D0`, soketi ya kulia ya Grove kwenye Wio Terminal. Parameta ya pili inaambia msimbo kuwa kihisi kinachotumika ni kihisi cha *DHT11* - maktaba unayotumia inaunga mkono aina nyingine za kihisi hiki.

1. Katika kazi ya `setup`, ongeza msimbo wa kusanidi muunganisho wa serial:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Mwishoni mwa kazi ya `setup`, baada ya `delay` ya mwisho, ongeza mwito wa kuanzisha kihisi cha DHT:

    ```cpp
    dht.begin();
    ```

1. Katika kazi ya `loop`, ongeza msimbo wa kuita kihisi na kuchapisha joto kwenye bandari ya serial:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Msimbo huu unatangaza safu tupu ya floats 2, na kuipitisha kwenye mwito wa `readTempAndHumidity` kwenye mfano wa `DHT`. Mwito huu unajaza safu na thamani 2 - unyevunyevu unaingia kwenye kipengele cha 0 cha safu (kumbuka katika C++ safu ni 0-based, kwa hivyo kipengele cha 0 ni 'cha kwanza' katika safu), na joto linaingia kwenye kipengele cha 1.

    Joto linasomwa kutoka kipengele cha 1 cha safu, na kuchapishwa kwenye bandari ya serial.

    > 🇺🇸 Joto linasomwa kwa Celsius. Kwa Wamarekani, kubadilisha hili kuwa Fahrenheit, gawanya thamani ya Celsius iliyosomwa kwa 5, kisha zidisha kwa 9, kisha ongeza 32. Kwa mfano, usomaji wa joto wa 20°C unakuwa ((20/5)*9) + 32 = 68°F.

1. Jenga na pakia msimbo kwenye Wio Terminal.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda mradi wa PlatformIO katika mradi wa 1, somo la 1 ikiwa unahitaji](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Baada ya kupakiwa, unaweza kufuatilia joto ukitumia serial monitor:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Programu yako ya kihisi cha joto imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, inashauriwa kutumia huduma ya mtafsiri wa kibinadamu mtaalamu. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.