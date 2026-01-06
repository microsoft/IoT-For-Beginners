<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T20:43:40+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "sw"
}
-->
# Kugundua Ukaribu - Wio Terminal

Katika sehemu hii ya somo, utaongeza kihisi cha ukaribu kwenye Wio Terminal yako, na kusoma umbali kutoka kwake.

## Vifaa

Wio Terminal inahitaji kihisi cha ukaribu.

Kihisi utakachotumia ni [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Kihisi hiki kinatumia moduli ya laser kupima umbali. Kina uwezo wa kupima umbali wa kati ya 10mm hadi 2000mm (1cm - 2m), na kitaripoti thamani kwa usahihi ndani ya wigo huo, huku umbali zaidi ya 1000mm ukiripotiwa kama 8109mm.

Kipima umbali cha laser kipo nyuma ya kihisi, upande wa pili wa soketi ya Grove.

Hii ni soketi ya I2C.

### Unganisha kihisi cha Time of Flight

Kihisi cha Grove Time of Flight kinaweza kuunganishwa na Wio Terminal.

#### Kazi - unganisha kihisi cha Time of Flight

Unganisha kihisi cha Time of Flight.

![Kihisi cha Grove Time of Flight](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.sw.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya kihisi cha Time of Flight. Itaingia kwa mwelekeo mmoja tu.

1. Ukiwa umeondoa Wio Terminal kutoka kwa kompyuta yako au chanzo kingine cha umeme, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya upande wa kushoto ya Wio Terminal unapoangalia skrini. Hii ni soketi iliyo karibu zaidi na kitufe cha kuwasha. Hii ni soketi ya pamoja ya dijitali na I2C.

![Kihisi cha Grove Time of Flight kimeunganishwa kwenye soketi ya upande wa kushoto](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.sw.png)

1. Sasa unaweza kuunganisha Wio Terminal kwenye kompyuta yako.

## Programu ya kihisi cha Time of Flight

Sasa Wio Terminal inaweza kupangwa kutumia kihisi cha Time of Flight kilichounganishwa.

### Kazi - panga kihisi cha Time of Flight

1. Tengeneza mradi mpya wa Wio Terminal ukitumia PlatformIO. Uite mradi huu `distance-sensor`. Ongeza msimbo kwenye kazi ya `setup` ili kusanidi mlango wa serial.

1. Ongeza tegemezi la maktaba ya Seeed Grove Time of Flight distance sensor kwenye faili ya `platformio.ini` ya mradi:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Katika `main.cpp`, ongeza yafuatayo chini ya maagizo yaliyopo ya kujumuisha ili kutangaza mfano wa darasa la `Seeed_vl53l0x` kwa ajili ya kuingiliana na kihisi cha Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Ongeza yafuatayo chini ya kazi ya `setup` ili kuanzisha kihisi:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Katika kazi ya `loop`, soma thamani kutoka kwa kihisi:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Msimbo huu unaanzisha muundo wa data wa kusomea data, kisha kuipitisha kwenye njia ya `PerformSingleRangingMeasurement` ambapo itajazwa na kipimo cha umbali.

1. Chini ya hii, andika kipimo cha umbali, kisha ucheleweshe kwa sekunde 1:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Jenga, pakia na endesha msimbo huu. Utaweza kuona vipimo vya umbali kwenye mfuatiliaji wa serial. Weka vitu karibu na kihisi na utaona kipimo cha umbali:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Kipima umbali kipo nyuma ya kihisi, kwa hivyo hakikisha unatumia upande sahihi unapopima umbali.

    ![Kipima umbali kilicho nyuma ya kihisi cha Time of Flight kikielekezwa kwenye ndizi](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.sw.png)

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Programu yako ya kihisi cha ukaribu imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, inashauriwa kutumia huduma ya tafsiri ya kibinadamu ya kitaalamu. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.