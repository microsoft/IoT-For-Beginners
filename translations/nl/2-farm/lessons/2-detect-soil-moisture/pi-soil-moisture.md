<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T21:27:55+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "nl"
}
-->
# Meet bodemvocht - Raspberry Pi

In dit deel van de les voeg je een capacitieve bodemvochtsensor toe aan je Raspberry Pi en lees je waarden ervan uit.

## Hardware

De Raspberry Pi heeft een capacitieve bodemvochtsensor nodig.

De sensor die je gaat gebruiken is een [Capacitieve Bodemvochtsensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), die bodemvocht meet door de capaciteit van de bodem te detecteren, een eigenschap die verandert naarmate het bodemvocht verandert. Naarmate het bodemvocht toeneemt, daalt de spanning.

Dit is een analoge sensor, dus hij gebruikt een analoge pin en de 10-bit ADC in de Grove Base Hat op de Pi om de spanning om te zetten in een digitaal signaal van 1-1.023. Dit wordt vervolgens via I²C verzonden via de GPIO-pinnen op de Pi.

### Verbind de bodemvochtsensor

De Grove bodemvochtsensor kan worden aangesloten op de Raspberry Pi.

#### Taak - verbind de bodemvochtsensor

Verbind de bodemvochtsensor.

![Een grove bodemvochtsensor](../../../../../translated_images/nl/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de bodemvochtsensor. Hij past maar op één manier.

1. Met de Raspberry Pi uitgeschakeld, verbind je het andere uiteinde van de Grove-kabel met de analoge aansluiting gemarkeerd **A0** op de Grove Base Hat die op de Pi is bevestigd. Deze aansluiting is de tweede van rechts, op de rij aansluitingen naast de GPIO-pinnen.

![De grove bodemvochtsensor aangesloten op de A0-aansluiting](../../../../../translated_images/nl/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. Steek de bodemvochtsensor in de grond. Hij heeft een 'hoogste positie lijn' - een witte lijn over de sensor. Steek de sensor tot aan, maar niet voorbij deze lijn.

![De grove bodemvochtsensor in de grond](../../../../../translated_images/nl/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Programmeer de bodemvochtsensor

De Raspberry Pi kan nu worden geprogrammeerd om de aangesloten bodemvochtsensor te gebruiken.

### Taak - programmeer de bodemvochtsensor

Programmeer het apparaat.

1. Zet de Pi aan en wacht tot hij is opgestart.

1. Start VS Code, direct op de Pi of via de Remote SSH-extensie.

    > ⚠️ Je kunt [de instructies voor het instellen en starten van VS Code in nightlight - les 1 indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md) raadplegen.

1. Maak vanuit de terminal een nieuwe map in de home-directory van de `pi`-gebruiker genaamd `soil-moisture-sensor`. Maak een bestand in deze map genaamd `app.py`.

1. Open deze map in VS Code.

1. Voeg de volgende code toe aan het bestand `app.py` om enkele vereiste bibliotheken te importeren:

    ```python
    import time
    from grove.adc import ADC
    ```

    De `import time`-verklaring importeert de `time`-module die later in deze opdracht zal worden gebruikt.

    De `from grove.adc import ADC`-verklaring importeert de `ADC` uit de Grove Python-bibliotheken. Deze bibliotheek bevat code om te communiceren met de analoog-naar-digitaal-converter op de Pi Base Hat en spanningen van analoge sensoren uit te lezen.

1. Voeg de volgende code hieronder toe om een instantie van de `ADC`-klasse te maken:

    ```python
    adc = ADC()
    ```

1. Voeg een oneindige lus toe die leest van deze ADC op de A0-pin en het resultaat naar de console schrijft. Deze lus kan vervolgens 10 seconden pauzeren tussen de metingen.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Voer de Python-app uit. Je zult de bodemvochtmetingen in de console zien verschijnen. Voeg wat water toe aan de grond of verwijder de sensor uit de grond en zie de waarde veranderen.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    In het voorbeeldoutput hierboven kun je zien dat de spanning daalt wanneer er water wordt toegevoegd.

> 💁 Je kunt deze code vinden in de [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) map.

😀 Je programma voor de bodemvochtsensor is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.