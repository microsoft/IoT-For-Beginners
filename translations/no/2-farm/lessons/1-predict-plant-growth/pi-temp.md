<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T22:46:37+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "no"
}
-->
# Mål temperatur - Raspberry Pi

I denne delen av leksjonen skal du legge til en temperatursensor på din Raspberry Pi.

## Maskinvare

Sensoren du skal bruke er en [DHT11 fuktighets- og temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), som kombinerer to sensorer i én pakke. Denne sensoren er ganske populær, og det finnes flere kommersielt tilgjengelige sensorer som kombinerer temperatur, fuktighet og noen ganger atmosfærisk trykk. Temperaturkomponenten er en negativ temperaturkoeffisient (NTC) termistor, en type termistor der motstanden reduseres når temperaturen øker.

Dette er en digital sensor, så den har en innebygd ADC som lager et digitalt signal med temperatur- og fuktighetsdata som mikrokontrolleren kan lese.

### Koble til temperatursensoren

Grove-temperatursensoren kan kobles til Raspberry Pi.

#### Oppgave

Koble til temperatursensoren

![En Grove-temperatursensor](../../../../../translated_images/no/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på fuktighets- og temperatursensoren. Den vil kun passe én vei.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til den digitale kontakten merket **D5** på Grove Base-hatten som er festet til Pi. Denne kontakten er den andre fra venstre, på raden med kontakter ved siden av GPIO-pinnene.

![Grove-temperatursensoren koblet til kontakt A0](../../../../../translated_images/no/pi-temperature-sensor.3ff82fff672c8e56.webp)

## Programmer temperatursensoren

Enheten kan nå programmeres for å bruke den tilkoblede temperatursensoren.

### Oppgave

Programmer enheten.

1. Slå på Pi og vent til den starter opp.

1. Start VS Code, enten direkte på Pi eller ved å koble til via Remote SSH-utvidelsen.

    > ⚠️ Du kan referere til [instruksjonene for oppsett og oppstart av VS Code i leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Fra terminalen, opprett en ny mappe i hjemmekatalogen til brukeren `pi` kalt `temperature-sensor`. Opprett en fil i denne mappen kalt `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Åpne denne mappen i VS Code.

1. For å bruke fuktighets- og temperatursensoren må en ekstra Pip-pakke installeres. Fra terminalen i VS Code, kjør følgende kommando for å installere denne Pip-pakken på Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Legg til følgende kode i `app.py`-filen for å importere de nødvendige bibliotekene:

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT`-setningen importerer `DHT`-sensor-klassen for å interagere med en Grove-temperatursensor fra `seeed_dht`-modulen.

1. Legg til følgende kode etter koden ovenfor for å opprette en instans av klassen som håndterer temperatursensoren:

    ```python
    sensor = DHT("11", 5)
    ```

    Dette erklærer en instans av `DHT`-klassen som håndterer den **D**igitale **H**umidity og **T**emperature-sensoren. Den første parameteren forteller koden at sensoren som brukes er *DHT11*-sensoren - biblioteket du bruker støtter andre varianter av denne sensoren. Den andre parameteren forteller koden at sensoren er koblet til den digitale porten `D5` på Grove Base-hatten.

    > ✅ Husk, alle kontaktene har unike pin-nummer. Pins 0, 2, 4 og 6 er analoge pins, pins 5, 16, 18, 22, 24 og 26 er digitale pins.

1. Legg til en uendelig løkke etter koden ovenfor for å hente verdien fra temperatursensoren og skrive den ut til konsollen:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Kallet til `sensor.read()` returnerer en tuple med fuktighet og temperatur. Du trenger kun temperaturverdien, så fuktigheten ignoreres. Temperaturverdien skrives deretter ut til konsollen.

1. Legg til en liten pause på ti sekunder på slutten av `loop`, siden temperaturverdiene ikke trenger å sjekkes kontinuerlig. En pause reduserer strømforbruket til enheten.

    ```python
    time.sleep(10)
    ```

1. Fra terminalen i VS Code, kjør følgende kommando for å kjøre Python-appen din:

    ```sh
    python3 app.py
    ```

    Du bør se temperaturverdier som skrives ut til konsollen. Bruk noe for å varme opp sensoren, som å trykke tommelen på den eller bruke en vifte for å se verdiene endre seg:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Du finner denne koden i [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi)-mappen.

😀 Programmet for temperatursensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vennligst vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.