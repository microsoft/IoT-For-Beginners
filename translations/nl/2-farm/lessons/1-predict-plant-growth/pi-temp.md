<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T21:08:07+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "nl"
}
-->
# Meet temperatuur - Raspberry Pi

In dit deel van de les voeg je een temperatuursensor toe aan je Raspberry Pi.

## Hardware

De sensor die je gaat gebruiken is een [DHT11 vochtigheids- en temperatuursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), die twee sensoren in één pakket combineert. Deze sensor is vrij populair en er zijn veel commercieel verkrijgbare sensoren die temperatuur, vochtigheid en soms ook luchtdruk combineren. Het temperatuuronderdeel van de sensor is een negatieve temperatuurcoëfficiënt (NTC) thermistor, een thermistor waarbij de weerstand afneemt naarmate de temperatuur stijgt.

Dit is een digitale sensor en heeft een ingebouwde ADC om een digitaal signaal te genereren met de temperatuur- en vochtigheidsgegevens die de microcontroller kan uitlezen.

### Verbind de temperatuursensor

De Grove-temperatuursensor kan worden aangesloten op de Raspberry Pi.

#### Taak

Verbind de temperatuursensor

![Een Grove-temperatuursensor](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.nl.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de vochtigheids- en temperatuursensor. De kabel past maar op één manier.

1. Schakel de Raspberry Pi uit en verbind het andere uiteinde van de Grove-kabel met de digitale aansluiting gemarkeerd als **D5** op de Grove Base Hat die op de Pi is aangesloten. Deze aansluiting is de tweede van links, in de rij aansluitingen naast de GPIO-pinnen.

![De Grove-temperatuursensor aangesloten op aansluiting A0](../../../../../translated_images/pi-temperature-sensor.3ff82fff672c8e56.nl.png)

## Programmeer de temperatuursensor

Het apparaat kan nu worden geprogrammeerd om de aangesloten temperatuursensor te gebruiken.

### Taak

Programmeur het apparaat.

1. Zet de Pi aan en wacht tot deze is opgestart.

1. Start VS Code, direct op de Pi of via de Remote SSH-extensie.

    > ⚠️ Je kunt [de instructies voor het instellen en starten van VS Code in les 1 raadplegen indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Maak vanuit de terminal een nieuwe map in de home-directory van de gebruiker `pi` genaamd `temperature-sensor`. Maak in deze map een bestand aan genaamd `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Open deze map in VS Code.

1. Om de temperatuur- en vochtigheidssensor te gebruiken, moet een extra Pip-pakket worden geïnstalleerd. Voer vanuit de terminal in VS Code het volgende commando uit om dit Pip-pakket op de Pi te installeren:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Voeg de volgende code toe aan het bestand `app.py` om de benodigde bibliotheken te importeren:

    ```python
    import time
    from seeed_dht import DHT
    ```

    De instructie `from seeed_dht import DHT` importeert de `DHT`-sensorclass om te communiceren met een Grove-temperatuursensor uit de module `seeed_dht`.

1. Voeg de volgende code toe na de bovenstaande code om een instantie te maken van de class die de temperatuursensor beheert:

    ```python
    sensor = DHT("11", 5)
    ```

    Dit declareert een instantie van de `DHT`-class die de **D**igitale **H**umidity en **T**emperature-sensor beheert. De eerste parameter geeft aan dat de gebruikte sensor de *DHT11*-sensor is - de bibliotheek die je gebruikt ondersteunt andere varianten van deze sensor. De tweede parameter geeft aan dat de sensor is aangesloten op digitale poort `D5` op de Grove Base Hat.

    > ✅ Onthoud dat alle aansluitingen unieke pinnummers hebben. Pinnen 0, 2, 4 en 6 zijn analoge pinnen, pinnen 5, 16, 18, 22, 24 en 26 zijn digitale pinnen.

1. Voeg een oneindige lus toe na de bovenstaande code om de waarde van de temperatuursensor op te vragen en deze naar de console te printen:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    De aanroep van `sensor.read()` retourneert een tuple met vochtigheid en temperatuur. Je hebt alleen de temperatuurwaarde nodig, dus de vochtigheid wordt genegeerd. De temperatuurwaarde wordt vervolgens naar de console geprint.

1. Voeg een korte pauze van tien seconden toe aan het einde van de `loop`, omdat de temperatuurwaarden niet continu hoeven te worden gecontroleerd. Een pauze vermindert het stroomverbruik van het apparaat.

    ```python
    time.sleep(10)
    ```

1. Voer vanuit de VS Code-terminal het volgende uit om je Python-app te starten:

    ```sh
    python3 app.py
    ```

    Je zou temperatuurwaarden in de console moeten zien verschijnen. Gebruik iets om de sensor op te warmen, zoals je duim erop drukken of een ventilator gebruiken, om te zien hoe de waarden veranderen:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Je kunt deze code vinden in de map [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Je programma voor de temperatuursensor is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen om nauwkeurigheid te garanderen, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.