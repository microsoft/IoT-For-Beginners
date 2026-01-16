<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-28T19:03:10+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "lt"
}
-->
# Aptikite artumą - Wio Terminalas

Šioje pamokos dalyje pridėsite artumo jutiklį prie savo Wio Terminalo ir nuskaitysite atstumą iš jo.

## Aparatinė įranga

Wio Terminalui reikalingas artumo jutiklis.

Jutiklis, kurį naudosite, yra [Grove Time of Flight atstumo jutiklis](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Šis jutiklis naudoja lazerinį nuotolio matavimo modulį atstumui aptikti. Jutiklio diapazonas yra nuo 10 mm iki 2000 mm (1 cm - 2 m), ir jis gana tiksliai praneša reikšmes šiame diapazone, o atstumai virš 1000 mm pranešami kaip 8109 mm.

Lazerinis nuotolio matuoklis yra jutiklio gale, priešingoje pusėje nei Grove jungtis.

Tai yra I²C jutiklis.

### Prijunkite Time of Flight jutiklį

Grove Time of Flight jutiklį galima prijungti prie Wio Terminalo.

#### Užduotis - prijunkite Time of Flight jutiklį

Prijunkite Time of Flight jutiklį.

![Grove Time of Flight jutiklis](../../../../../translated_images/lt/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Įkiškite vieną Grove kabelio galą į Time of Flight jutiklio jungtį. Jis įsistums tik viena kryptimi.

2. Kai Wio Terminalas yra atjungtas nuo kompiuterio ar kito maitinimo šaltinio, prijunkite kitą Grove kabelio galą prie kairiosios Grove jungties Wio Terminale, žiūrint į ekraną. Tai yra jungtis, esanti arčiausiai maitinimo mygtuko. Tai yra kombinuota skaitmeninė ir I²C jungtis.

![Grove Time of Flight jutiklis prijungtas prie kairiosios jungties](../../../../../translated_images/lt/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

3. Dabar galite prijungti Wio Terminalą prie savo kompiuterio.

## Užprogramuokite Time of Flight jutiklį

Dabar Wio Terminalą galima užprogramuoti naudoti prijungtą Time of Flight jutiklį.

### Užduotis - užprogramuokite Time of Flight jutiklį

1. Sukurkite visiškai naują Wio Terminalo projektą naudodami PlatformIO. Pavadinkite šį projektą `distance-sensor`. Pridėkite kodą `setup` funkcijoje, kad sukonfigūruotumėte nuoseklųjį prievadą.

2. Pridėkite bibliotekos priklausomybę Seeed Grove Time of Flight atstumo jutiklio bibliotekai prie projekto `platformio.ini` failo:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

3. `main.cpp` faile, pridėkite šį kodą po esamomis įtraukimo direktyvomis, kad deklaruotumėte `Seeed_vl53l0x` klasės egzempliorių, skirtą sąveikai su Time of Flight jutikliu:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

4. Pridėkite šį kodą į `setup` funkcijos apačią, kad inicializuotumėte jutiklį:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

5. `loop` funkcijoje nuskaitykite reikšmę iš jutiklio:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Šis kodas inicializuoja duomenų struktūrą, į kurią bus įrašomi duomenys, tada perduoda ją į `PerformSingleRangingMeasurement` metodą, kur ji bus užpildyta atstumo matavimu.

6. Po to išveskite atstumo matavimą ir pridėkite 1 sekundės uždelsimą:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

7. Sukurkite, įkelkite ir paleiskite šį kodą. Galėsite matyti atstumo matavimus naudodami nuoseklųjį monitorių. Padėkite objektus šalia jutiklio ir pamatysite atstumo matavimus:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Nuotolio matuoklis yra jutiklio gale, todėl įsitikinkite, kad naudojate tinkamą pusę matuodami atstumą.

    ![Nuotolio matuoklis Time of Flight jutiklio gale, nukreiptas į bananą](../../../../../translated_images/lt/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Šį kodą galite rasti [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) aplanke.

😀 Jūsų artumo jutiklio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.