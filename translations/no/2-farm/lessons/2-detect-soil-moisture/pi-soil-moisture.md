<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T22:22:26+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "no"
}
-->
# Mål jordfuktighet - Raspberry Pi

I denne delen av leksjonen skal du legge til en kapasitiv jordfuktighetssensor til din Raspberry Pi og lese verdier fra den.

## Maskinvare

Raspberry Pi trenger en kapasitansbasert jordfuktighetssensor.

Sensoren du skal bruke er en [Kapasitiv Jordfuktighetssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), som måler jordfuktighet ved å oppdage jordens kapasitans, en egenskap som endrer seg med fuktighetsnivået. Når jordfuktigheten øker, synker spenningen.

Dette er en analog sensor, så den bruker en analog pinne og 10-bits ADC i Grove Base Hat på Pi for å konvertere spenningen til et digitalt signal fra 1-1 023. Dette sendes deretter over I²C via GPIO-pinnene på Pi.

### Koble til jordfuktighetssensoren

Grove jordfuktighetssensoren kan kobles til Raspberry Pi.

#### Oppgave - koble til jordfuktighetssensoren

Koble til jordfuktighetssensoren.

![En Grove jordfuktighetssensor](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.no.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på jordfuktighetssensoren. Den kan kun settes inn på én måte.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til den analoge kontakten merket **A0** på Grove Base Hat som er festet til Pi. Denne kontakten er den andre fra høyre, på raden av kontakter ved siden av GPIO-pinnene.

![Grove jordfuktighetssensor koblet til A0-kontakten](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.no.png)

1. Sett jordfuktighetssensoren inn i jorden. Den har en 'høyeste posisjonslinje' - en hvit linje på tvers av sensoren. Sett sensoren inn opp til, men ikke forbi, denne linjen.

![Grove jordfuktighetssensor i jord](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.no.png)

## Programmer jordfuktighetssensoren

Raspberry Pi kan nå programmeres til å bruke den tilkoblede jordfuktighetssensoren.

### Oppgave - programmer jordfuktighetssensoren

Programmer enheten.

1. Slå på Pi og vent til den starter opp.

1. Start VS Code, enten direkte på Pi eller ved å koble til via Remote SSH-utvidelsen.

    > ⚠️ Du kan referere til [instruksjonene for å sette opp og starte VS Code i nightlight - leksjon 1 om nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Fra terminalen, opprett en ny mappe i hjemmekatalogen til brukeren `pi` kalt `soil-moisture-sensor`. Opprett en fil i denne mappen kalt `app.py`.

1. Åpne denne mappen i VS Code.

1. Legg til følgende kode i `app.py`-filen for å importere noen nødvendige biblioteker:

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time`-setningen importerer `time`-modulen som vil bli brukt senere i denne oppgaven.

    `from grove.adc import ADC`-setningen importerer `ADC` fra Grove Python-bibliotekene. Dette biblioteket inneholder kode for å samhandle med analog-til-digital-omformeren på Pi Base Hat og lese spenninger fra analoge sensorer.

1. Legg til følgende kode under dette for å opprette en instans av `ADC`-klassen:

    ```python
    adc = ADC()
    ```

1. Legg til en uendelig løkke som leser fra denne ADC-en på A0-pinnen og skriver resultatet til konsollen. Denne løkken kan deretter sove i 10 sekunder mellom hver avlesning.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Kjør Python-appen. Du vil se jordfuktighetsmålingene skrevet til konsollen. Tilsett litt vann i jorden, eller fjern sensoren fra jorden, og se verdien endre seg.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    I eksempelet over kan du se spenningen synke når vann tilsettes.

> 💁 Du finner denne koden i [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi)-mappen.

😀 Programmet for jordfuktighetssensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.