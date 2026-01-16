<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-28T12:13:29+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "sl"
}
-->
# Zaznavanje bližine - Wio Terminal

V tem delu lekcije boste dodali senzor bližine na vaš Wio Terminal in odčitavali razdaljo z njega.

## Strojna oprema

Wio Terminal potrebuje senzor bližine.

Senzor, ki ga boste uporabili, je [Grove Time of Flight senzor razdalje](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ta senzor uporablja laserski modul za merjenje razdalje. Senzor ima razpon od 10 mm do 2000 mm (1 cm - 2 m) in bo poročal vrednosti v tem razponu precej natančno, pri čemer bodo razdalje nad 1000 mm poročane kot 8109 mm.

Laserski merilnik razdalje se nahaja na zadnji strani senzorja, na nasprotni strani od Grove priključka.

To je I²C senzor.

### Povežite senzor Time of Flight

Grove senzor Time of Flight je mogoče povezati z Wio Terminalom.

#### Naloga - povežite senzor Time of Flight

Povežite senzor Time of Flight.

![Grove senzor Time of Flight](../../../../../translated_images/sl/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Vstavite en konec Grove kabla v priključek na senzorju Time of Flight. Kabel bo šel noter le na en način.

1. Ko je Wio Terminal odklopljen od računalnika ali drugega napajalnika, povežite drugi konec Grove kabla z levim Grove priključkom na Wio Terminalu, ko gledate zaslon. To je priključek, ki je najbližje gumbu za vklop. To je kombiniran digitalni in I²C priključek.

![Grove senzor Time of Flight povezan z levim priključkom](../../../../../translated_images/sl/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Zdaj lahko povežete Wio Terminal z računalnikom.

## Programiranje senzorja Time of Flight

Wio Terminal je zdaj mogoče programirati za uporabo priključenega senzorja Time of Flight.

### Naloga - programirajte senzor Time of Flight

1. Ustvarite povsem nov projekt za Wio Terminal z uporabo PlatformIO. Projekt poimenujte `distance-sensor`. Dodajte kodo v funkcijo `setup`, da konfigurirate serijski port.

1. Dodajte odvisnost knjižnice za Seeed Grove senzor razdalje Time of Flight v datoteko `platformio.ini` projekta:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. V datoteki `main.cpp` dodajte naslednje pod obstoječe direktive `include`, da deklarirate instanco razreda `Seeed_vl53l0x` za interakcijo s senzorjem Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Na dno funkcije `setup` dodajte naslednje, da inicializirate senzor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. V funkciji `loop` preberite vrednost s senzorja:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Ta koda inicializira podatkovno strukturo za branje podatkov, nato pa jo posreduje metodi `PerformSingleRangingMeasurement`, kjer bo napolnjena z meritvijo razdalje.

1. Pod tem napišite izpis meritve razdalje, nato pa dodajte zamik za 1 sekundo:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Sestavite, naložite in zaženite to kodo. Meritve razdalje boste lahko videli v serijskem monitorju. Postavite predmete blizu senzorja in videli boste meritve razdalje:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Merilnik razdalje je na zadnji strani senzorja, zato poskrbite, da boste uporabili pravilno stran pri merjenju razdalje.

    ![Merilnik razdalje na zadnji strani senzorja Time of Flight, usmerjen proti banani](../../../../../translated_images/sl/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 To kodo lahko najdete v mapi [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Vaš program za senzor bližine je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.