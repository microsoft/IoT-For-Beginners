# Bygg en nattlampa - Virtuell IoT-hårdvara

I den här delen av lektionen kommer du att lägga till en ljussensor till din virtuella IoT-enhet.

## Virtuell hårdvara

Nattlampan behöver en sensor, skapad i CounterFit-appen.

Sensorn är en **ljussensor**. På en fysisk IoT-enhet skulle det vara en [fotodiod](https://wikipedia.org/wiki/Photodiode) som omvandlar ljus till en elektrisk signal. Ljussensorer är analoga sensorer som skickar ett heltalsvärde som indikerar en relativ mängd ljus, vilket inte motsvarar någon standardenhet som [lux](https://wikipedia.org/wiki/Lux).

### Lägg till sensorer i CounterFit

För att använda en virtuell ljussensor måste du lägga till den i CounterFit-appen.

#### Uppgift - lägg till sensorer i CounterFit

Lägg till ljussensorn i CounterFit-appen.

1. Se till att CounterFit-webbappen körs från den tidigare delen av denna uppgift. Om inte, starta den.

1. Skapa en ljussensor:

    1. I rutan *Create sensor* i panelen *Sensors*, öppna rullgardinsmenyn *Sensor type* och välj *Light*.

    1. Låt *Units* vara inställd på *NoUnits*.

    1. Kontrollera att *Pin* är inställd på *0*.

    1. Välj knappen **Add** för att skapa ljussensorn på Pin 0.

    ![Inställningar för ljussensorn](../../../../../translated_images/sv/counterfit-create-light-sensor.9f36a5e0d4458d8d.webp)

    Ljussensorn kommer att skapas och visas i sensorlistan.

    ![Ljussensorn skapad](../../../../../translated_images/sv/counterfit-light-sensor.5d0f5584df56b90f.webp)

## Programmera ljussensorn

Enheten kan nu programmeras för att använda den inbyggda ljussensorn.

### Uppgift - programmera ljussensorn

Programmera enheten.

1. Öppna nattlampa-projektet i VS Code som du skapade i den tidigare delen av denna uppgift. Döda och återskapa terminalen för att säkerställa att den körs med den virtuella miljön om det behövs.

1. Öppna filen `app.py`.

1. Lägg till följande kod högst upp i filen `app.py` tillsammans med de andra `import`-satserna för att importera några nödvändiga bibliotek:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time`-satsen importerar Pythons `time`-modul som kommer att användas senare i denna uppgift.

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor`-satsen importerar `GroveLightSensor` från CounterFit Grove shim Python-bibliotek. Detta bibliotek innehåller kod för att interagera med en ljussensor skapad i CounterFit-appen.

1. Lägg till följande kod längst ner i filen för att skapa instanser av klasser som hanterar ljussensorn:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Raden `light_sensor = GroveLightSensor(0)` skapar en instans av klassen `GroveLightSensor` som ansluter till pin **0** - CounterFit Grove-pinnen som ljussensorn är ansluten till.

1. Lägg till en oändlig loop efter koden ovan för att hämta ljussensorns värde och skriva ut det till konsolen:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Detta kommer att läsa av den aktuella ljusnivån med egenskapen `light` från klassen `GroveLightSensor`. Denna egenskap läser det analoga värdet från pinnen. Värdet skrivs sedan ut till konsolen.

1. Lägg till en kort paus på en sekund i slutet av `while`-loopen eftersom ljusnivåerna inte behöver kontrolleras kontinuerligt. En paus minskar enhetens strömförbrukning.

    ```python
    time.sleep(1)
    ```

1. Kör följande kommando från VS Code-terminalen för att köra din Python-app:

    ```sh
    python3 app.py
    ```

    Ljusstyrkevärden kommer att skrivas ut till konsolen. Initialt kommer detta värde att vara 0.

1. Ändra värdet på ljussensorn som kommer att läsas av appen från CounterFit-appen. Du kan göra detta på två sätt:

    * Ange ett nummer i rutan *Value* för ljussensorn och välj sedan knappen **Set**. Numret du anger kommer att vara det värde som sensorn returnerar.

    * Markera kryssrutan *Random* och ange ett *Min*- och *Max*-värde, välj sedan knappen **Set**. Varje gång sensorn läser ett värde kommer den att läsa ett slumpmässigt nummer mellan *Min* och *Max*.

    De värden du ställer in kommer att skrivas ut till konsolen. Ändra *Value* eller inställningarna för *Random* för att få värdet att ändras.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Du hittar denna kod i mappen [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Ditt nattlampa-program blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.