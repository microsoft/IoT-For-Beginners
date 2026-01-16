<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T22:27:15+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "sv"
}
-->
# Mäta jordfuktighet - Virtuell IoT-hårdvara

I denna del av lektionen kommer du att lägga till en kapacitiv jordfuktighetssensor till din virtuella IoT-enhet och läsa värden från den.

## Virtuell hårdvara

Den virtuella IoT-enheten kommer att använda en simulerad Grove kapacitiv jordfuktighetssensor. Detta gör att labbet förblir detsamma som att använda en Raspberry Pi med en fysisk Grove kapacitiv jordfuktighetssensor.

I en fysisk IoT-enhet skulle jordfuktighetssensorn vara en kapacitiv sensor som mäter jordfuktighet genom att detektera jordens kapacitans, en egenskap som förändras när jordfuktigheten ändras. När jordfuktigheten ökar, minskar spänningen.

Detta är en analog sensor, så den använder en simulerad 10-bitars ADC för att rapportera ett värde mellan 1-1 023.

### Lägg till jordfuktighetssensorn i CounterFit

För att använda en virtuell jordfuktighetssensor måste du lägga till den i CounterFit-appen.

#### Uppgift - Lägg till jordfuktighetssensorn i CounterFit

Lägg till jordfuktighetssensorn i CounterFit-appen.

1. Skapa en ny Python-app på din dator i en mapp som heter `soil-moisture-sensor` med en enda fil som heter `app.py` och en Python-virtuell miljö, och lägg till CounterFit pip-paketen.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa och ställa in ett CounterFit Python-projekt i lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Se till att CounterFit-webbappen körs.

1. Skapa en jordfuktighetssensor:

    1. I rutan *Create sensor* i panelen *Sensors*, öppna rullgardinsmenyn *Sensor type* och välj *Soil Moisture*.

    1. Låt *Units* vara inställd på *NoUnits*.

    1. Kontrollera att *Pin* är inställd på *0*.

    1. Välj knappen **Add** för att skapa *Soil Moisture*-sensorn på Pin 0.

    ![Inställningar för jordfuktighetssensorn](../../../../../translated_images/sv/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Jordfuktighetssensorn kommer att skapas och visas i sensorlistan.

    ![Den skapade jordfuktighetssensorn](../../../../../translated_images/sv/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programmera appen för jordfuktighetssensorn

Appen för jordfuktighetssensorn kan nu programmeras med hjälp av CounterFit-sensorer.

### Uppgift - Programmera appen för jordfuktighetssensorn

Programmera appen för jordfuktighetssensorn.

1. Se till att appen `soil-moisture-sensor` är öppen i VS Code.

1. Öppna filen `app.py`.

1. Lägg till följande kod högst upp i `app.py` för att ansluta appen till CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lägg till följande kod i filen `app.py` för att importera några nödvändiga bibliotek:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time`-satsen importerar modulen `time` som kommer att användas senare i denna uppgift.

    `from counterfit_shims_grove.adc import ADC`-satsen importerar klassen `ADC` för att interagera med en virtuell analog-till-digital-omvandlare som kan anslutas till en CounterFit-sensor.

1. Lägg till följande kod under detta för att skapa en instans av klassen `ADC`:

    ```python
    adc = ADC()
    ```

1. Lägg till en oändlig loop som läser från denna ADC på pin 0 och skriver resultatet till konsolen. Denna loop kan sedan pausa i 10 sekunder mellan avläsningarna.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Från CounterFit-appen, ändra värdet på jordfuktighetssensorn som kommer att läsas av appen. Du kan göra detta på två sätt:

    * Ange ett nummer i rutan *Value* för jordfuktighetssensorn och välj sedan knappen **Set**. Numret du anger kommer att vara det värde som sensorn returnerar.

    * Markera kryssrutan *Random* och ange ett *Min*- och *Max*-värde, och välj sedan knappen **Set**. Varje gång sensorn läser ett värde kommer den att läsa ett slumpmässigt nummer mellan *Min* och *Max*.

1. Kör Python-appen. Du kommer att se jordfuktighetsmätningarna skrivna till konsolen. Ändra *Value* eller inställningarna för *Random* för att se värdet ändras.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Du kan hitta denna kod i mappen [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Din jordfuktighetssensorprogram var en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.