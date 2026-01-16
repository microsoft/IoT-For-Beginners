<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T22:46:06+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "sv"
}
-->
# Mäta temperatur - Raspberry Pi

I den här delen av lektionen kommer du att lägga till en temperatursensor till din Raspberry Pi.

## Hårdvara

Sensorn du kommer att använda är en [DHT11 fukt- och temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), som kombinerar två sensorer i en enhet. Denna sensor är ganska populär och finns i flera kommersiellt tillgängliga varianter som kombinerar temperatur, luftfuktighet och ibland även lufttryck. Komponentdelen för temperatur är en negativ temperaturkoefficient (NTC) termistor, en typ av termistor där resistansen minskar när temperaturen ökar.

Detta är en digital sensor och har därför en inbyggd ADC som skapar en digital signal med temperatur- och fuktdata som mikrokontrollern kan läsa.

### Anslut temperatursensorn

Grove-temperatursensorn kan anslutas till Raspberry Pi.

#### Uppgift

Anslut temperatursensorn

![En Grove-temperatursensor](../../../../../translated_images/sv/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Sätt in ena änden av en Grove-kabel i uttaget på fukt- och temperatursensorn. Den går bara att sätta i på ett sätt.

1. Med Raspberry Pi avstängd, anslut den andra änden av Grove-kabeln till det digitala uttaget märkt **D5** på Grove Base-hatten som är ansluten till Pi. Detta uttag är det andra från vänster, på raden av uttag bredvid GPIO-stiften.

![Grove-temperatursensorn ansluten till uttag A0](../../../../../translated_images/sv/pi-temperature-sensor.3ff82fff672c8e56.webp)

## Programmera temperatursensorn

Enheten kan nu programmeras för att använda den anslutna temperatursensorn.

### Uppgift

Programmera enheten.

1. Starta Pi och vänta tills den har startat upp.

1. Öppna VS Code, antingen direkt på Pi eller anslut via Remote SSH-tillägget.

    > ⚠️ Du kan hänvisa till [instruktionerna för att ställa in och starta VS Code i lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Skapa en ny mapp i hemmakatalogen för användaren `pi` via terminalen och kalla den `temperature-sensor`. Skapa en fil i denna mapp som heter `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Öppna denna mapp i VS Code.

1. För att använda fukt- och temperatursensorn behöver du installera ett extra Pip-paket. Kör följande kommando från terminalen i VS Code för att installera detta Pip-paket på Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Lägg till följande kod i filen `app.py` för att importera de nödvändiga biblioteken:

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` importerar klassen `DHT` för att interagera med en Grove-temperatursensor från modulen `seeed_dht`.

1. Lägg till följande kod efter ovanstående kod för att skapa en instans av klassen som hanterar temperatursensorn:

    ```python
    sensor = DHT("11", 5)
    ```

    Detta deklarerar en instans av klassen `DHT` som hanterar den **D**igitala **H**umidity och **T**emperature-sensorn. Den första parametern anger att sensorn som används är *DHT11*-sensorn – biblioteket du använder stöder andra varianter av denna sensor. Den andra parametern anger att sensorn är ansluten till den digitala porten `D5` på Grove Base-hatten.

    > ✅ Kom ihåg att alla uttag har unika pinnummer. Pinnarna 0, 2, 4 och 6 är analoga pinnar, medan pinnarna 5, 16, 18, 22, 24 och 26 är digitala pinnar.

1. Lägg till en oändlig loop efter ovanstående kod för att läsa av temperatursensorns värde och skriva ut det i konsolen:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Anropet till `sensor.read()` returnerar en tuple med luftfuktighet och temperatur. Du behöver bara temperaturvärdet, så luftfuktigheten ignoreras. Temperaturvärdet skrivs sedan ut i konsolen.

1. Lägg till en kort paus på tio sekunder i slutet av loopen eftersom temperaturvärdena inte behöver kontrolleras kontinuerligt. En paus minskar enhetens strömförbrukning.

    ```python
    time.sleep(10)
    ```

1. Kör följande kommando från VS Code-terminalen för att köra ditt Python-program:

    ```sh
    python3 app.py
    ```

    Du bör se temperaturvärden som skrivs ut i konsolen. Använd något för att värma sensorn, till exempel genom att trycka med tummen på den eller använda en fläkt, för att se värdena ändras:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Du kan hitta denna kod i mappen [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Ditt program för temperatursensorn lyckades!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.