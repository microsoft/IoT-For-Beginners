<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:10:49+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "sv"
}
-->
# Lägg till en sensor - Wio Terminal

I den här delen av lektionen kommer du att använda ljussensorn på din Wio Terminal.

## Hårdvara

Sensorn för den här lektionen är en **ljussensor** som använder en [fotodiod](https://wikipedia.org/wiki/Photodiode) för att omvandla ljus till en elektrisk signal. Det är en analog sensor som skickar ett heltalsvärde från 0 till 1 023, vilket indikerar en relativ mängd ljus som inte motsvarar någon standardenhet som till exempel [lux](https://wikipedia.org/wiki/Lux).

Ljussensorn är inbyggd i Wio Terminal och syns genom det genomskinliga plastfönstret på baksidan.

![Ljussensorn på baksidan av Wio Terminal](../../../../../translated_images/sv/wio-light-sensor.b1f529f3c95f5165.webp)

## Programmera ljussensorn

Enheten kan nu programmeras för att använda den inbyggda ljussensorn.

### Uppgift

Programmera enheten.

1. Öppna nattljusprojektet i VS Code som du skapade i den tidigare delen av uppgiften.

1. Lägg till följande rad längst ner i `setup`-funktionen:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Den här raden konfigurerar de pinnar som används för att kommunicera med sensorhårdvaran.

    `WIO_LIGHT`-pinnen är numret på GPIO-pinnen som är ansluten till den inbyggda ljussensorn. Den här pinnen är inställd på `INPUT`, vilket innebär att den är ansluten till en sensor och data kommer att läsas från pinnen.

1. Ta bort innehållet i `loop`-funktionen.

1. Lägg till följande kod i den nu tomma `loop`-funktionen.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Den här koden läser ett analogt värde från `WIO_LIGHT`-pinnen. Detta läser ett värde från 0–1 023 från den inbyggda ljussensorn. Värdet skickas sedan till seriella porten så att du kan läsa det i Serial Monitor när koden körs. `Serial.print` skriver texten utan en ny rad i slutet, så varje rad börjar med `Light value:` och slutar med det faktiska ljusvärdet.

1. Lägg till en kort fördröjning på en sekund (1 000 ms) i slutet av `loop`, eftersom ljusnivåerna inte behöver kontrolleras kontinuerligt. En fördröjning minskar enhetens strömförbrukning.

    ```cpp
    delay(1000);
    ```

1. Anslut Wio Terminal till din dator igen och ladda upp den nya koden som du gjorde tidigare.

1. Anslut Serial Monitor. Ljusstyrkevärden kommer att visas i terminalen. Täck över och avtäcka ljussensorn på baksidan av Wio Terminal, och värdena kommer att ändras.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Du hittar den här koden i mappen [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Att lägga till en sensor i ditt nattljusprogram var en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.