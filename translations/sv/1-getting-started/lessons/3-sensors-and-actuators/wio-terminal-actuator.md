# Bygg en nattlampa - Wio Terminal

I den här delen av lektionen kommer du att lägga till en LED till din Wio Terminal och använda den för att skapa en nattlampa.

## Hårdvara

Nattlampan behöver nu en aktuator.

Aktuatoren är en **LED**, en [ljusemitterande diod](https://wikipedia.org/wiki/Light-emitting_diode) som avger ljus när ström flyter genom den. Detta är en digital aktuator som har två lägen: på och av. Att skicka ett värde på 1 tänder LED-lampan, och 0 släcker den. Detta är en extern Grove-aktuator som måste anslutas till Wio Terminal.

Logiken för nattlampan i pseudokod är:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Anslut LED-lampan

Grove LED kommer som en modul med ett urval av LED-lampor, vilket gör att du kan välja färg.

#### Uppgift - anslut LED-lampan

Anslut LED-lampan.

![En Grove LED](../../../../../translated_images/sv/grove-led.6c853be93f473cf2.webp)

1. Välj din favorit-LED och sätt in benen i de två hålen på LED-modulen.

    LED-lampor är ljusemitterande dioder, och dioder är elektroniska komponenter som bara kan leda ström i en riktning. Detta innebär att LED-lampan måste anslutas åt rätt håll, annars fungerar den inte.

    Ett av benen på LED-lampan är den positiva pinnen, det andra är den negativa pinnen. LED-lampan är inte helt rund och är något plattare på ena sidan. Den något plattare sidan är den negativa pinnen. När du ansluter LED-lampan till modulen, se till att pinnen vid den rundade sidan är ansluten till sockeln märkt **+** på utsidan av modulen, och den plattare sidan är ansluten till sockeln närmare mitten av modulen.

1. LED-modulen har en vridknapp som gör att du kan justera ljusstyrkan. Vrid denna helt uppåt till att börja med genom att rotera den moturs så långt det går med en liten stjärnskruvmejsel.

1. Sätt in ena änden av en Grove-kabel i sockeln på LED-modulen. Den går bara in på ett sätt.

1. Med Wio Terminal frånkopplad från din dator eller annan strömkälla, anslut den andra änden av Grove-kabeln till den högra Grove-sockeln på Wio Terminal när du tittar på skärmen. Detta är sockeln längst bort från strömknappen.

    > 💁 Den högra Grove-sockeln kan användas med analoga eller digitala sensorer och aktuatorer. Den vänstra sockeln är för I2C och digitala sensorer och aktuatorer endast. C kommer att behandlas i en senare lektion.

![Grove LED ansluten till den högra sockeln](../../../../../translated_images/sv/wio-led.265a1897e72d7f21.webp)

## Programmera nattlampan

Nattlampan kan nu programmeras med hjälp av den inbyggda ljussensorn och Grove LED.

### Uppgift - programmera nattlampan

Programmera nattlampan.

1. Öppna nattlampsprojektet i VS Code som du skapade i den föregående delen av denna uppgift.

1. Lägg till följande rad längst ner i `setup`-funktionen:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Denna rad konfigurerar pinnen som används för att kommunicera med LED-lampan via Grove-porten.

    `D0`-pinnen är den digitala pinnen för den högra Grove-sockeln. Denna pinne är inställd på `OUTPUT`, vilket innebär att den är ansluten till en aktuator och data kommer att skrivas till pinnen.

1. Lägg till följande kod omedelbart före `delay` i loop-funktionen:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Denna kod kontrollerar `light`-värdet. Om detta är mindre än 300 skickas ett `HIGH`-värde till den digitala pinnen `D0`. Detta `HIGH` är ett värde på 1, vilket tänder LED-lampan. Om ljuset är större än eller lika med 300 skickas ett `LOW`-värde på 0 till pinnen, vilket släcker LED-lampan.

    > 💁 När digitala värden skickas till aktuatorer är ett LOW-värde 0V, och ett HIGH-värde är den maximala spänningen för enheten. För Wio Terminal är den höga spänningen 3,3V.

1. Anslut Wio Terminal till din dator igen och ladda upp den nya koden som du gjorde tidigare.

1. Anslut Serial Monitor. Ljusstyrkevärden kommer att visas i terminalen.

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

1. Täck över och avtäcka ljussensorn. Notera hur LED-lampan tänds om ljusnivån är 300 eller mindre, och släcks när ljusnivån är större än 300.

![LED-lampan ansluten till Wio tänds och släcks när ljusnivån ändras](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Du kan hitta denna kod i [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal)-mappen.

😀 Ditt nattlampsprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, vänligen notera att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.