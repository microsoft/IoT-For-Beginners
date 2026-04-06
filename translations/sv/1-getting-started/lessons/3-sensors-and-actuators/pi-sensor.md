# Bygg en nattlampa - Raspberry Pi

I den här delen av lektionen kommer du att lägga till en ljussensor till din Raspberry Pi.

## Hårdvara

Sensorn för den här lektionen är en **ljussensor** som använder en [fotodiod](https://wikipedia.org/wiki/Fotodiod) för att omvandla ljus till en elektrisk signal. Detta är en analog sensor som skickar ett heltalsvärde mellan 0 och 1 000, vilket indikerar en relativ mängd ljus som inte motsvarar någon standardenhet som [lux](https://wikipedia.org/wiki/Lux).

Ljussensorn är en extern Grove-sensor och måste anslutas till Grove Base-hatten på Raspberry Pi.

### Anslut ljussensorn

Grove-ljussensorn som används för att upptäcka ljusnivåer måste anslutas till Raspberry Pi.

#### Uppgift - anslut ljussensorn

Anslut ljussensorn.

![En Grove-ljussensor](../../../../../translated_images/sv/grove-light-sensor.b8127b7c434e632d.webp)

1. Sätt in ena änden av en Grove-kabel i uttaget på ljussensormodulen. Den går bara in på ett sätt.

1. Med Raspberry Pi avstängd, anslut den andra änden av Grove-kabeln till det analoga uttaget märkt **A0** på Grove Base-hatten som är ansluten till Pi. Detta uttag är det andra från höger, på raden av uttag bredvid GPIO-stiften.

![Grove-ljussensorn ansluten till uttag A0](../../../../../translated_images/sv/pi-light-sensor.66cc1e31fa48cd7d.webp)

## Programmera ljussensorn

Enheten kan nu programmeras med hjälp av Grove-ljussensorn.

### Uppgift - programmera ljussensorn

Programmera enheten.

1. Starta Pi och vänta tills den har startat upp.

1. Öppna nattlampa-projektet i VS Code som du skapade i den föregående delen av denna uppgift, antingen direkt på Pi eller via Remote SSH-tillägget.

1. Öppna filen `app.py` och ta bort all kod från den.

1. Lägg till följande kod i filen `app.py` för att importera några nödvändiga bibliotek:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time`-satsen importerar `time`-modulen som kommer att användas senare i denna uppgift.

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor`-satsen importerar `GroveLightSensor` från Grove Python-biblioteken. Detta bibliotek innehåller kod för att interagera med en Grove-ljussensor och installerades globalt under Pi-inställningen.

1. Lägg till följande kod efter koden ovan för att skapa en instans av klassen som hanterar ljussensorn:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Raden `light_sensor = GroveLightSensor(0)` skapar en instans av klassen `GroveLightSensor` som ansluter till pin **A0** - den analoga Grove-pinnen som ljussensorn är ansluten till.

1. Lägg till en oändlig loop efter koden ovan för att läsa av ljussensorns värde och skriva ut det till konsolen:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Detta kommer att läsa av den aktuella ljusnivån på en skala från 0-1 023 med hjälp av egenskapen `light` i klassen `GroveLightSensor`. Denna egenskap läser det analoga värdet från pinnen. Detta värde skrivs sedan ut till konsolen.

1. Lägg till en kort paus på en sekund i slutet av loopen eftersom ljusnivåerna inte behöver kontrolleras kontinuerligt. En paus minskar enhetens strömförbrukning.

    ```python
    time.sleep(1)
    ```

1. Från VS Code-terminalen, kör följande för att köra din Python-app:

    ```sh
    python3 app.py
    ```

    Ljusstyrkevärden kommer att skrivas ut till konsolen. Täck över och avtäcka ljussensorn, och värdena kommer att ändras:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Du kan hitta denna kod i mappen [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Att lägga till en sensor till ditt nattlampa-program var en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.