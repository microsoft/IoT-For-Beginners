# Styr ett relä - Virtuell IoT-hårdvara

I den här delen av lektionen kommer du att lägga till ett relä till din virtuella IoT-enhet, utöver fuktighetssensorn för jord, och styra det baserat på jordens fuktighetsnivå.

## Virtuell hårdvara

Den virtuella IoT-enheten kommer att använda ett simulerat Grove-relä. Detta gör att labbet liknar användningen av en Raspberry Pi med ett fysiskt Grove-relä.

På en fysisk IoT-enhet skulle reläet vara ett normalt öppet relä (vilket innebär att utgångskretsen är öppen eller frånkopplad när ingen signal skickas till reläet). Ett sådant relä kan hantera utgångskretsar upp till 250V och 10A.

### Lägg till reläet i CounterFit

För att använda ett virtuellt relä behöver du lägga till det i CounterFit-appen.

#### Uppgift

Lägg till reläet i CounterFit-appen.

1. Öppna projektet `soil-moisture-sensor` från förra lektionen i VS Code om det inte redan är öppet. Du kommer att lägga till detta projekt.

1. Se till att CounterFit-webbappen körs.

1. Skapa ett relä:

    1. I rutan *Create actuator* i panelen *Actuators*, öppna rullgardinsmenyn *Actuator type* och välj *Relay*.

    1. Ställ in *Pin* till *5*.

    1. Välj knappen **Add** för att skapa reläet på Pin 5.

    ![Reläinställningarna](../../../../../translated_images/sv/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    Reläet kommer att skapas och visas i listan över aktuatorer.

    ![Reläet skapat](../../../../../translated_images/sv/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Programmera reläet

Appen för jordfuktighetssensorn kan nu programmeras för att använda det virtuella reläet.

### Uppgift

Programmera den virtuella enheten.

1. Öppna projektet `soil-moisture-sensor` från förra lektionen i VS Code om det inte redan är öppet. Du kommer att lägga till detta projekt.

1. Lägg till följande kod i filen `app.py` under de befintliga importerna:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Denna rad importerar `GroveRelay` från Grove Python-shim-biblioteken för att interagera med det virtuella Grove-reläet.

1. Lägg till följande kod under deklarationen av klassen `ADC` för att skapa en instans av `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Detta skapar ett relä som använder pin **5**, den pin du anslöt reläet till.

1. För att testa att reläet fungerar, lägg till följande kod i loopen `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koden slår på reläet, väntar 0,5 sekunder och stänger sedan av reläet.

1. Kör Python-appen. Reläet kommer att slå på och av var 10:e sekund, med en halv sekunds fördröjning mellan att slå på och av. Du kommer att se det virtuella reläet i CounterFit-appen stängas och öppnas när reläet slås på och av.

    ![Det virtuella reläet slås på och av](../../../../../images/virtual-relay-turn-on-off.gif)

## Styr reläet med jordfuktighet

Nu när reläet fungerar kan det styras baserat på avläsningar från jordfuktighetssensorn.

### Uppgift

Styr reläet.

1. Ta bort de 3 raderna kod som du lade till för att testa reläet. Ersätt dem med följande kod på samma plats:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Denna kod kontrollerar jordfuktighetsnivån från jordfuktighetssensorn. Om den är över 450 slår den på reläet, och stänger av det om den går under 450.

    > 💁 Kom ihåg att den kapacitiva jordfuktighetssensorn läser av: ju lägre jordfuktighetsnivå, desto mer fukt finns det i jorden och vice versa.

1. Kör Python-appen. Du kommer att se reläet slå på eller av beroende på jordfuktighetsnivåerna. Ändra inställningarna *Value* eller *Random* för jordfuktighetssensorn för att se värdet ändras.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du kan hitta denna kod i mappen [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Ditt program för att styra ett relä med en virtuell jordfuktighetssensor blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.