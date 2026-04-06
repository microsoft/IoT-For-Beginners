# Detectează proximitatea - Wio Terminal

În această parte a lecției, vei adăuga un senzor de proximitate la Wio Terminal și vei citi distanța de la acesta.

## Hardware

Wio Terminal are nevoie de un senzor de proximitate.

Senzorul pe care îl vei folosi este un [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Acest senzor utilizează un modul de măsurare cu laser pentru a detecta distanța. Senzorul are un interval de măsurare de la 10mm la 2000mm (1cm - 2m) și va raporta valorile din acest interval cu o precizie destul de mare, iar distanțele peste 1000mm vor fi raportate ca 8109mm.

Telemetrul laser se află pe partea din spate a senzorului, opusă conectorului Grove.

Acesta este un socket I²C.

### Conectează senzorul Time of Flight

Senzorul Grove Time of Flight poate fi conectat la Wio Terminal.

#### Sarcină - conectează senzorul Time of Flight

Conectează senzorul Time of Flight.

![Un senzor Grove Time of Flight](../../../../../translated_images/ro/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Introdu un capăt al cablului Grove în conectorul de pe senzorul Time of Flight. Acesta va intra doar într-un singur mod.

1. Cu Wio Terminal deconectat de la computer sau altă sursă de alimentare, conectează celălalt capăt al cablului Grove la conectorul Grove din partea stângă a Wio Terminal, așa cum privești ecranul. Acesta este conectorul cel mai apropiat de butonul de alimentare. Este un socket combinat digital și I²C.

![Senzorul Grove Time of Flight conectat la conectorul din stânga](../../../../../translated_images/ro/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Acum poți conecta Wio Terminal la computerul tău.

## Programează senzorul Time of Flight

Wio Terminal poate fi acum programat pentru a utiliza senzorul Time of Flight atașat.

### Sarcină - programează senzorul Time of Flight

1. Creează un proiect nou pentru Wio Terminal folosind PlatformIO. Denumește acest proiect `distance-sensor`. Adaugă cod în funcția `setup` pentru a configura portul serial.

1. Adaugă o dependență de bibliotecă pentru biblioteca Seeed Grove Time of Flight Distance Sensor în fișierul `platformio.ini` al proiectului:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. În `main.cpp`, adaugă următorul cod sub directivele existente de includere pentru a declara o instanță a clasei `Seeed_vl53l0x` pentru a interacționa cu senzorul Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Adaugă următorul cod la sfârșitul funcției `setup` pentru a inițializa senzorul:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. În funcția `loop`, citește o valoare de la senzor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Acest cod inițializează o structură de date pentru a citi datele, apoi o transmite metodei `PerformSingleRangingMeasurement`, unde va fi populată cu măsurarea distanței.

1. Sub acest cod, scrie măsurarea distanței, apoi adaugă o întârziere de 1 secundă:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Construiește, încarcă și rulează acest cod. Vei putea vedea măsurătorile distanței în monitorul serial. Poziționează obiecte lângă senzor și vei vedea măsurarea distanței:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Telemetrul se află pe partea din spate a senzorului, așa că asigură-te că folosești partea corectă atunci când măsori distanța.

    ![Telemetrul de pe partea din spate a senzorului Time of Flight îndreptat spre o banană](../../../../../translated_images/ro/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Poți găsi acest cod în folderul [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Programul tău pentru senzorul de proximitate a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.