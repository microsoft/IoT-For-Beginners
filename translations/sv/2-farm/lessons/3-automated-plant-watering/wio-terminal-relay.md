<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-27T22:57:58+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "sv"
}
-->
# Styr ett relä - Wio Terminal

I denna del av lektionen kommer du att lägga till ett relä till din Wio Terminal, utöver fuktighetssensorn för jord, och styra det baserat på jordens fuktighetsnivå.

## Hårdvara

Wio Terminal behöver ett relä.

Reläet du kommer att använda är ett [Grove-relä](https://www.seeedstudio.com/Grove-Relay.html), ett normalt öppet relä (vilket betyder att utgångskretsen är öppen eller frånkopplad när ingen signal skickas till reläet) som kan hantera utgångskretsar upp till 250V och 10A.

Detta är en digital aktuator, så den ansluts till digitala stift på Wio Terminal. Den kombinerade analog/digital-porten används redan av fuktighetssensorn för jord, så detta ansluts till den andra porten, som är en kombinerad I2C och digital port.

### Anslut reläet

Grove-reläet kan anslutas till Wio Terminals digitala port.

#### Uppgift

Anslut reläet.

![Ett Grove-relä](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.sv.png)

1. Sätt ena änden av en Grove-kabel i uttaget på reläet. Den går bara in på ett sätt.

1. Med Wio Terminal frånkopplad från din dator eller annan strömkälla, anslut den andra änden av Grove-kabeln till den vänstra Grove-porten på Wio Terminal när du tittar på skärmen. Låt fuktighetssensorn för jord vara ansluten till den högra porten.

![Grove-reläet anslutet till den vänstra porten, och fuktighetssensorn för jord ansluten till den högra porten](../../../../../translated_images/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.sv.png)

1. Sätt fuktighetssensorn för jord i jorden, om den inte redan är det från föregående lektion.

## Programmera reläet

Wio Terminal kan nu programmeras för att använda det anslutna reläet.

### Uppgift

Programmera enheten.

1. Öppna projektet `soil-moisture-sensor` från förra lektionen i VS Code om det inte redan är öppet. Du kommer att lägga till detta projekt.

2. Det finns inget bibliotek för denna aktuator - det är en digital aktuator som styrs av en hög eller låg signal. För att slå på den skickar du en hög signal till stiftet (3.3V), för att stänga av den skickar du en låg signal (0V). Du kan göra detta med den inbyggda Arduino-funktionen [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Börja med att lägga till följande längst ner i funktionen `setup` för att konfigurera den kombinerade I2C/digital-porten som en utgångsstift för att skicka en spänning till reläet:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` är portnumret för den kombinerade I2C/digital-porten.

1. För att testa att reläet fungerar, lägg till följande i funktionen `loop`, under den sista `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Koden skickar en hög signal till stiftet som reläet är anslutet till för att slå på det, väntar 500ms (en halv sekund), och skickar sedan en låg signal för att stänga av reläet.

1. Bygg och ladda upp koden till Wio Terminal.

1. När koden har laddats upp kommer reläet att slå på och av var 10:e sekund, med en halv sekunds fördröjning mellan att slå på och av. Du kommer att höra reläet klicka på och sedan klicka av. En LED på Grove-kortet kommer att lysa när reläet är på och slockna när reläet är av.

    ![Reläet slår på och av](../../../../../images/relay-turn-on-off.gif)

## Styr reläet baserat på jordens fuktighet

Nu när reläet fungerar kan det styras som svar på avläsningar från fuktighetssensorn för jord.

### Uppgift

Styr reläet.

1. Ta bort de 3 rader kod som du lade till för att testa reläet. Ersätt dem med följande kod:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Denna kod kontrollerar fuktighetsnivån i jorden från fuktighetssensorn. Om den är över 450 slår den på reläet, och stänger av det när den går under 450.

    > 💁 Kom ihåg att den kapacitiva fuktighetssensorn för jord läser: ju lägre fuktighetsnivå, desto mer fukt finns det i jorden och vice versa.

1. Bygg och ladda upp koden till Wio Terminal.

1. Övervaka enheten via seriell monitor. Du kommer att se reläet slå på eller av beroende på fuktighetsnivån i jorden. Testa i torr jord och tillsätt sedan vatten.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du kan hitta denna kod i mappen [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Ditt program för att styra ett relä baserat på fuktighetssensorn för jord var en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.