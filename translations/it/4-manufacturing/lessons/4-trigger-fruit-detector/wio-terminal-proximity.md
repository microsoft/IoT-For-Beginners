<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-25T16:41:59+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "it"
}
-->
# Rileva la prossimità - Wio Terminal

In questa parte della lezione, aggiungerai un sensore di prossimità al tuo Wio Terminal e leggerai la distanza rilevata.

## Hardware

Il Wio Terminal necessita di un sensore di prossimità.

Il sensore che utilizzerai è un [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Questo sensore utilizza un modulo di misurazione laser per rilevare la distanza. Ha un intervallo di rilevamento che va da 10mm a 2000mm (1cm - 2m) e riporta valori in questo intervallo con buona precisione. Per distanze superiori a 1000mm, il valore riportato sarà 8109mm.

Il telemetro laser si trova sul retro del sensore, sul lato opposto rispetto alla presa Grove.

Questo è un socket I²C.

### Collega il sensore Time of Flight

Il sensore Grove Time of Flight può essere collegato al Wio Terminal.

#### Attività - collega il sensore Time of Flight

Collega il sensore Time of Flight.

![Un sensore Grove Time of Flight](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.it.png)

1. Inserisci un'estremità di un cavo Grove nella presa del sensore Time of Flight. Il cavo può essere inserito solo in un verso.

1. Con il Wio Terminal scollegato dal computer o da altre fonti di alimentazione, collega l'altra estremità del cavo Grove alla presa Grove sul lato sinistro del Wio Terminal, guardando lo schermo. Questa è la presa più vicina al pulsante di accensione. Si tratta di una presa combinata digitale e I²C.

![Il sensore Grove Time of Flight collegato alla presa sinistra](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.it.png)

1. Ora puoi collegare il Wio Terminal al tuo computer.

## Programma il sensore Time of Flight

Ora il Wio Terminal può essere programmato per utilizzare il sensore Time of Flight collegato.

### Attività - programma il sensore Time of Flight

1. Crea un nuovo progetto per il Wio Terminal utilizzando PlatformIO. Chiama questo progetto `distance-sensor`. Aggiungi il codice nella funzione `setup` per configurare la porta seriale.

1. Aggiungi una dipendenza per la libreria Seeed Grove Time of Flight Distance Sensor al file `platformio.ini` del progetto:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. In `main.cpp`, aggiungi il seguente codice sotto le direttive di inclusione esistenti per dichiarare un'istanza della classe `Seeed_vl53l0x` per interagire con il sensore Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Aggiungi il seguente codice alla fine della funzione `setup` per inizializzare il sensore:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Nella funzione `loop`, leggi un valore dal sensore:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Questo codice inizializza una struttura dati in cui leggere i dati, quindi la passa al metodo `PerformSingleRangingMeasurement`, che la popolerà con la misurazione della distanza.

1. Sotto questo, scrivi il valore della misurazione della distanza, quindi aggiungi un ritardo di 1 secondo:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Compila, carica ed esegui questo codice. Sarai in grado di vedere le misurazioni della distanza nel monitor seriale. Posiziona oggetti vicino al sensore e vedrai la misurazione della distanza:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Il telemetro si trova sul retro del sensore, quindi assicurati di utilizzare il lato corretto quando misuri la distanza.

    ![Il telemetro sul retro del sensore Time of Flight puntato verso una banana](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.it.png)

> 💁 Puoi trovare questo codice nella cartella [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Il tuo programma per il sensore di prossimità è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.