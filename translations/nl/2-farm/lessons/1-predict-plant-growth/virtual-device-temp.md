<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-27T21:06:56+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "nl"
}
-->
# Meet temperatuur - Virtuele IoT-hardware

In dit deel van de les voeg je een temperatuursensor toe aan je virtuele IoT-apparaat.

## Virtuele hardware

Het virtuele IoT-apparaat maakt gebruik van een gesimuleerde Grove Digital Humidity and Temperature sensor. Dit zorgt ervoor dat deze oefening hetzelfde blijft als het gebruik van een Raspberry Pi met een fysieke Grove DHT11-sensor.

De sensor combineert een **temperatuursensor** met een **vochtigheidssensor**, maar in deze oefening ben je alleen geïnteresseerd in de temperatuursensorcomponent. In een fysiek IoT-apparaat zou de temperatuursensor een [thermistor](https://wikipedia.org/wiki/Thermistor) zijn die de temperatuur meet door een verandering in weerstand te detecteren naarmate de temperatuur verandert. Temperatuursensoren zijn meestal digitale sensoren die intern de gemeten weerstand omzetten in een temperatuur in graden Celsius (of Kelvin, of Fahrenheit).

### Voeg de sensoren toe aan CounterFit

Om een virtuele vochtigheids- en temperatuursensor te gebruiken, moet je de twee sensoren toevoegen aan de CounterFit-app.

#### Taak - voeg de sensoren toe aan CounterFit

Voeg de vochtigheids- en temperatuursensoren toe aan de CounterFit-app.

1. Maak een nieuwe Python-app op je computer in een map genaamd `temperature-sensor` met een enkel bestand genaamd `app.py` en een Python-virtuele omgeving, en voeg de CounterFit pip-pakketten toe.

    > ⚠️ Je kunt [de instructies voor het maken en instellen van een CounterFit Python-project in les 1 raadplegen indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installeer een extra Pip-pakket om een CounterFit shim voor de DHT11-sensor te installeren. Zorg ervoor dat je dit installeert vanuit een terminal met de virtuele omgeving geactiveerd.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Zorg ervoor dat de CounterFit-webapp actief is.

1. Maak een vochtigheidssensor aan:

    1. In het vak *Create sensor* in het *Sensors*-paneel, open het dropdownmenu *Sensor type* en selecteer *Humidity*.

    1. Laat de *Units* ingesteld op *Percentage*.

    1. Zorg ervoor dat de *Pin* is ingesteld op *5*.

    1. Selecteer de knop **Add** om de vochtigheidssensor op Pin 5 aan te maken.

    ![De instellingen van de vochtigheidssensor](../../../../../translated_images/nl/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    De vochtigheidssensor wordt aangemaakt en verschijnt in de sensorenlijst.

    ![De aangemaakte vochtigheidssensor](../../../../../translated_images/nl/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Maak een temperatuursensor aan:

    1. In het vak *Create sensor* in het *Sensors*-paneel, open het dropdownmenu *Sensor type* en selecteer *Temperature*.

    1. Laat de *Units* ingesteld op *Celsius*.

    1. Zorg ervoor dat de *Pin* is ingesteld op *6*.

    1. Selecteer de knop **Add** om de temperatuursensor op Pin 6 aan te maken.

    ![De instellingen van de temperatuursensor](../../../../../translated_images/nl/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    De temperatuursensor wordt aangemaakt en verschijnt in de sensorenlijst.

    ![De aangemaakte temperatuursensor](../../../../../translated_images/nl/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## Programmeer de temperatuursensor-app

De temperatuursensor-app kan nu worden geprogrammeerd met behulp van de CounterFit-sensoren.

### Taak - programmeer de temperatuursensor-app

Programmeerde temperatuursensor-app.

1. Zorg ervoor dat de `temperature-sensor`-app geopend is in VS Code.

1. Open het bestand `app.py`.

1. Voeg de volgende code toe aan de bovenkant van `app.py` om de app te verbinden met CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Voeg de volgende code toe aan het bestand `app.py` om de benodigde bibliotheken te importeren:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    De instructie `from seeed_dht import DHT` importeert de `DHT`-sensorclass om te communiceren met een virtuele Grove-temperatuursensor met behulp van een shim uit de module `counterfit_shims_seeed_python_dht`.

1. Voeg de volgende code toe na de bovenstaande code om een instantie te maken van de class die de virtuele vochtigheids- en temperatuursensor beheert:

    ```python
    sensor = DHT("11", 5)
    ```

    Dit declareert een instantie van de `DHT`-class die de virtuele **D**igitale **H**umidity en **T**emperature sensor beheert. De eerste parameter geeft aan dat de gebruikte sensor een virtuele *DHT11*-sensor is. De tweede parameter geeft aan dat de sensor is aangesloten op poort `5`.

    > 💁 CounterFit simuleert deze gecombineerde vochtigheids- en temperatuursensor door verbinding te maken met 2 sensoren: een vochtigheidssensor op de pin die wordt opgegeven bij het maken van de `DHT`-class, en een temperatuursensor die draait op de volgende pin. Als de vochtigheidssensor op pin 5 zit, verwacht de shim dat de temperatuursensor op pin 6 zit.

1. Voeg een oneindige lus toe na de bovenstaande code om de waarde van de temperatuursensor op te vragen en deze naar de console te printen:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    De aanroep van `sensor.read()` retourneert een tuple van vochtigheid en temperatuur. Je hebt alleen de temperatuurwaarde nodig, dus de vochtigheid wordt genegeerd. De temperatuurwaarde wordt vervolgens naar de console geprint.

1. Voeg een korte pauze van tien seconden toe aan het einde van de `loop`, omdat de temperatuurwaarden niet continu hoeven te worden gecontroleerd. Een pauze vermindert het stroomverbruik van het apparaat.

    ```python
    time.sleep(10)
    ```

1. Voer vanuit de VS Code-terminal met een geactiveerde virtuele omgeving het volgende uit om je Python-app te starten:

    ```sh
    python app.py
    ```

1. Verander vanuit de CounterFit-app de waarde van de temperatuursensor die door de app wordt gelezen. Je kunt dit op twee manieren doen:

    * Voer een getal in het vak *Value* in voor de temperatuursensor en selecteer vervolgens de knop **Set**. Het getal dat je invoert, wordt de waarde die door de sensor wordt geretourneerd.

    * Vink het vakje *Random* aan en voer een *Min*- en *Max*-waarde in, selecteer vervolgens de knop **Set**. Elke keer dat de sensor een waarde leest, leest deze een willekeurig getal tussen *Min* en *Max*.

    Je zou de waarden die je hebt ingesteld in de console moeten zien verschijnen. Verander de *Value* of de *Random*-instellingen om de waarde te zien veranderen.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Je kunt deze code vinden in de map [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Je temperatuursensorprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen om nauwkeurigheid te garanderen, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.