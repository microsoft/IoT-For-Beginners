# Styr ett relä - Raspberry Pi

I den här delen av lektionen kommer du att lägga till ett relä till din Raspberry Pi, utöver fuktighetssensorn för jord, och styra det baserat på jordens fuktighetsnivå.

## Hårdvara

Raspberry Pi behöver ett relä.

Reläet du kommer att använda är ett [Grove-relä](https://www.seeedstudio.com/Grove-Relay.html), ett normalt öppet relä (vilket betyder att utgångskretsen är öppen eller frånkopplad när ingen signal skickas till reläet) som kan hantera utgångskretsar upp till 250V och 10A.

Detta är en digital aktuator, så det ansluts till en digital pin på Grove Base Hat.

### Anslut reläet

Grove-reläet kan anslutas till Raspberry Pi.

#### Uppgift

Anslut reläet.

![Ett Grove-relä](../../../../../translated_images/sv/grove-relay.d426958ca210fbd0.webp)

1. Sätt ena änden av en Grove-kabel i uttaget på reläet. Den går bara in på ett sätt.

1. Med Raspberry Pi avstängd, anslut den andra änden av Grove-kabeln till det digitala uttaget märkt **D5** på Grove Base Hat som är ansluten till Pi. Detta uttag är det andra från vänster, på raden av uttag bredvid GPIO-pinnarna. Låt fuktighetssensorn för jord vara ansluten till uttaget **A0**.

![Grove-reläet anslutet till D5-uttaget och fuktighetssensorn ansluten till A0-uttaget](../../../../../translated_images/sv/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.webp)

1. Sätt fuktighetssensorn för jord i jorden, om den inte redan är där från föregående lektion.

## Programmera reläet

Raspberry Pi kan nu programmeras för att använda det anslutna reläet.

### Uppgift

Programmera enheten.

1. Starta Pi och vänta tills den har startat.

1. Öppna projektet `soil-moisture-sensor` från förra lektionen i VS Code om det inte redan är öppet. Du kommer att lägga till detta projekt.

1. Lägg till följande kod i filen `app.py` under de befintliga importerna:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Denna kod importerar `GroveRelay` från Grove Python-biblioteken för att interagera med Grove-reläet.

1. Lägg till följande kod under deklarationen av klassen `ADC` för att skapa en instans av `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Detta skapar ett relä som använder pin **D5**, den digitala pinnen du anslöt reläet till.

1. För att testa att reläet fungerar, lägg till följande kod i `while True:`-loopen:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koden slår på reläet, väntar 0,5 sekunder och stänger sedan av reläet.

1. Kör Python-appen. Reläet kommer att slå på och av var tionde sekund, med en halv sekunds fördröjning mellan att slå på och av. Du kommer att höra reläet klicka på och sedan klicka av. En LED på Grove-kortet kommer att lysa när reläet är på och slockna när reläet är av.

    ![Reläet slår på och av](../../../../../images/relay-turn-on-off.gif)

## Styr reläet baserat på jordens fuktighet

Nu när reläet fungerar kan det styras baserat på avläsningar från fuktighetssensorn för jord.

### Uppgift

Styr reläet.

1. Ta bort de 3 rader kod som du lade till för att testa reläet. Ersätt dem med följande kod:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Denna kod kontrollerar fuktighetsnivån i jorden från fuktighetssensorn. Om den är över 450 slår den på reläet, och stänger av det när den går under 450.

    > 💁 Kom ihåg att den kapacitiva fuktighetssensorn för jord läser: ju lägre fuktighetsnivå, desto mer fukt finns det i jorden och vice versa.

1. Kör Python-appen. Du kommer att se reläet slå på eller av beroende på jordens fuktighetsnivå. Testa i torr jord och tillsätt sedan vatten.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du kan hitta denna kod i mappen [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Ditt program för att styra ett relä baserat på jordens fuktighet var en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.