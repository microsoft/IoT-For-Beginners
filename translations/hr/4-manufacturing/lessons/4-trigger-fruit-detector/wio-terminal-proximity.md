<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-28T12:13:14+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "hr"
}
-->
# Otkrivanje blizine - Wio Terminal

U ovom dijelu lekcije dodat ćete senzor blizine na svoj Wio Terminal i očitavati udaljenost s njega.

## Hardver

Wio Terminal treba senzor blizine.

Senzor koji ćete koristiti je [Grove Time of Flight senzor udaljenosti](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ovaj senzor koristi laserski modul za mjerenje udaljenosti. Ima raspon od 10 mm do 2000 mm (1 cm - 2 m) i prilično točno prijavljuje vrijednosti unutar tog raspona, dok će udaljenosti iznad 1000 mm biti prijavljene kao 8109 mm.

Laserski mjerač udaljenosti nalazi se na stražnjoj strani senzora, na suprotnoj strani od Grove priključka.

Ovo je I²C senzor.

### Povezivanje senzora Time of Flight

Grove senzor Time of Flight može se povezati s Wio Terminalom.

#### Zadatak - povezivanje senzora Time of Flight

Povežite senzor Time of Flight.

![Grove senzor Time of Flight](../../../../../translated_images/hr/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Umetnite jedan kraj Grove kabela u priključak na senzoru Time of Flight. Kabel će ući samo na jedan način.

1. Dok je Wio Terminal isključen s vašeg računala ili drugog izvora napajanja, spojite drugi kraj Grove kabela na lijevi Grove priključak na Wio Terminalu dok gledate u ekran. To je priključak najbliži gumbu za uključivanje. Ovo je kombinirani digitalni i I²C priključak.

![Grove senzor Time of Flight povezan s lijevim priključkom](../../../../../translated_images/hr/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Sada možete spojiti Wio Terminal na svoje računalo.

## Programiranje senzora Time of Flight

Wio Terminal sada se može programirati za korištenje povezanog senzora Time of Flight.

### Zadatak - programiranje senzora Time of Flight

1. Napravite potpuno novi projekt za Wio Terminal koristeći PlatformIO. Nazovite ovaj projekt `distance-sensor`. Dodajte kod u funkciju `setup` za konfiguraciju serijskog porta.

1. Dodajte ovisnost o biblioteci za Seeed Grove senzor udaljenosti Time of Flight u datoteku `platformio.ini` projekta:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. U datoteci `main.cpp`, dodajte sljedeće ispod postojećih direktiva za uključivanje kako biste deklarirali instancu klase `Seeed_vl53l0x` za interakciju sa senzorom Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Dodajte sljedeće na dno funkcije `setup` za inicijalizaciju senzora:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. U funkciji `loop`, očitajte vrijednost sa senzora:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Ovaj kod inicijalizira strukturu podataka za očitavanje podataka, a zatim je prosljeđuje metodi `PerformSingleRangingMeasurement`, gdje će biti popunjena mjerenjem udaljenosti.

1. Ispod toga, ispišite mjerenje udaljenosti, a zatim odgodite za 1 sekundu:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Sastavite, prenesite i pokrenite ovaj kod. Moći ćete vidjeti mjerenja udaljenosti pomoću serijskog monitora. Postavite objekte blizu senzora i vidjet ćete mjerenje udaljenosti:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Mjerač udaljenosti nalazi se na stražnjoj strani senzora, stoga pazite da koristite ispravnu stranu prilikom mjerenja udaljenosti.

    ![Mjerač udaljenosti na stražnjoj strani senzora Time of Flight usmjeren prema banani](../../../../../translated_images/hr/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Ovaj kod možete pronaći u mapi [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Vaš program za senzor blizine bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.