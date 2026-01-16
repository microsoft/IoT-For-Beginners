<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T22:52:57+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "no"
}
-->
# Mål temperatur - Wio Terminal

I denne delen av leksjonen skal du legge til en temperatursensor på din Wio Terminal og lese temperaturverdier fra den.

## Maskinvare

Wio Terminal trenger en temperatursensor.

Sensoren du skal bruke er en [DHT11 fuktighets- og temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), som kombinerer to sensorer i én pakke. Denne sensoren er ganske populær, og det finnes flere kommersielt tilgjengelige sensorer som kombinerer temperatur, fuktighet og noen ganger også atmosfærisk trykk. Temperaturkomponenten er en negativ temperaturkoeffisient (NTC) termistor, en type termistor hvor motstanden reduseres når temperaturen øker.

Dette er en digital sensor, så den har en innebygd ADC som lager et digitalt signal med temperatur- og fuktighetsdata som mikrokontrolleren kan lese.

### Koble til temperatursensoren

Grove-temperatursensoren kan kobles til Wio Terminals digitale port.

#### Oppgave - koble til temperatursensoren

Koble til temperatursensoren.

![En Grove-temperatursensor](../../../../../translated_images/no/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på fuktighets- og temperatursensoren. Den kan bare settes inn på én måte.

1. Med Wio Terminal frakoblet fra datamaskinen eller annen strømkilde, koble den andre enden av Grove-kabelen til den høyre Grove-kontakten på Wio Terminal når du ser på skjermen. Dette er kontakten som er lengst unna strømknappen.

![Grove-temperatursensoren koblet til den høyre kontakten](../../../../../translated_images/no/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programmer temperatursensoren

Wio Terminal kan nå programmeres til å bruke den tilkoblede temperatursensoren.

### Oppgave - programmer temperatursensoren

Programmer enheten.

1. Opprett et helt nytt Wio Terminal-prosjekt ved hjelp av PlatformIO. Kall dette prosjektet `temperature-sensor`. Legg til kode i `setup`-funksjonen for å konfigurere seriellporten.

    > ⚠️ Du kan se [instruksjonene for å opprette et PlatformIO-prosjekt i prosjekt 1, leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Legg til et bibliotekavhengighet for Seeed Grove Humidity and Temperature-sensorbiblioteket i prosjektets `platformio.ini`-fil:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Du kan se [instruksjonene for å legge til biblioteker i et PlatformIO-prosjekt i prosjekt 1, leksjon 4 hvis nødvendig](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Legg til følgende `#include`-direktiver øverst i filen, under den eksisterende `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Dette importerer filene som trengs for å samhandle med sensoren. `DHT.h`-headerfilen inneholder koden for selve sensoren, og ved å legge til `SPI.h`-headeren sikrer du at koden som trengs for å kommunisere med sensoren blir inkludert når appen kompileres.

1. Før `setup`-funksjonen, deklarer DHT-sensoren:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Dette deklarerer en instans av `DHT`-klassen som håndterer den **D**igitale **H**umidity og **T**emperature-sensoren. Denne er koblet til port `D0`, den høyre Grove-kontakten på Wio Terminal. Den andre parameteren forteller koden at sensoren som brukes er *DHT11*-sensoren - biblioteket du bruker støtter andre varianter av denne sensoren.

1. I `setup`-funksjonen, legg til kode for å sette opp den serielle forbindelsen:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. På slutten av `setup`-funksjonen, etter den siste `delay`, legg til et kall for å starte DHT-sensoren:

    ```cpp
    dht.begin();
    ```

1. I `loop`-funksjonen, legg til kode for å kalle sensoren og skrive ut temperaturen til seriellporten:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Denne koden deklarerer et tomt array med 2 floats og sender dette til kallet til `readTempAndHumidity` på `DHT`-instansen. Dette kallet fyller arrayet med 2 verdier - fuktigheten går inn i det første elementet i arrayet (0-indeksert), og temperaturen går inn i det andre elementet.

    Temperaturen leses fra det andre elementet i arrayet og skrives ut til seriellporten.

    > 🇺🇸 Temperaturen leses i Celsius. For amerikanere, for å konvertere dette til Fahrenheit, del Celsius-verdien på 5, multipliser med 9, og legg til 32. For eksempel, en temperaturavlesning på 20°C blir ((20/5)*9) + 32 = 68°F.

1. Bygg og last opp koden til Wio Terminal.

    > ⚠️ Du kan se [instruksjonene for å opprette et PlatformIO-prosjekt i prosjekt 1, leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Når koden er lastet opp, kan du overvåke temperaturen ved hjelp av seriellmonitoren:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Du finner denne koden i [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal)-mappen.

😀 Programmet for temperatursensoren var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.