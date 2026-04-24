# Bygg en nattlampa - Virtuell IoT-hårdvara

I den här delen av lektionen kommer du att lägga till en LED till din virtuella IoT-enhet och använda den för att skapa en nattlampa.

## Virtuell hårdvara

Nattlampan behöver en ställdon, skapad i CounterFit-appen.

Ställdonet är en **LED**. I en fysisk IoT-enhet skulle det vara en [ljusemitterande diod](https://wikipedia.org/wiki/Light-emitting_diode) som avger ljus när ström flyter genom den. Detta är ett digitalt ställdon som har två tillstånd, på och av. Att skicka ett värde på 1 tänder LED-lampan, och 0 släcker den.

Nattlampans logik i pseudokod är:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Lägg till ställdonet i CounterFit

För att använda en virtuell LED måste du lägga till den i CounterFit-appen.

#### Uppgift - lägg till ställdonet i CounterFit

Lägg till LED-lampan i CounterFit-appen.

1. Se till att CounterFit-webbappen körs från den tidigare delen av denna uppgift. Om inte, starta den och lägg till ljussensorn igen.

1. Skapa en LED:

    1. I rutan *Create actuator* i panelen *Actuator*, öppna rullgardinsmenyn *Actuator type* och välj *LED*.

    1. Ställ in *Pin* till *5*.

    1. Välj knappen **Add** för att skapa LED-lampan på Pin 5.

    ![LED-inställningarna](../../../../../translated_images/sv/counterfit-create-led.ba9db1c9b8c622a6.webp)

    LED-lampan kommer att skapas och visas i listan över ställdon.

    ![Den skapade LED-lampan](../../../../../translated_images/sv/counterfit-led.c0ab02de6d256ad8.webp)

    När LED-lampan har skapats kan du ändra färgen med hjälp av färgväljaren *Color*. Välj knappen **Set** för att ändra färgen efter att du har valt den.

### Programmera nattlampan

Nattlampan kan nu programmeras med hjälp av CounterFits ljussensor och LED.

#### Uppgift - programmera nattlampan

Programmera nattlampan.

1. Öppna nattlampa-projektet i VS Code som du skapade i den tidigare delen av denna uppgift. Avsluta och återskapa terminalen för att säkerställa att den körs med den virtuella miljön om det behövs.

1. Öppna filen `app.py`.

1. Lägg till följande kod i filen `app.py` för att importera ett nödvändigt bibliotek. Detta ska läggas till högst upp, under de andra `import`-raderna.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Raden `from counterfit_shims_grove.grove_led import GroveLed` importerar `GroveLed` från CounterFit Grove shim Python-biblioteken. Detta bibliotek innehåller kod för att interagera med en LED som skapats i CounterFit-appen.

1. Lägg till följande kod efter deklarationen av `light_sensor` för att skapa en instans av klassen som hanterar LED-lampan:

    ```python
    led = GroveLed(5)
    ```

    Raden `led = GroveLed(5)` skapar en instans av klassen `GroveLed` som ansluter till pin **5** - CounterFit Grove-pinnen som LED-lampan är ansluten till.

1. Lägg till en kontroll inuti `while`-loopen, och före `time.sleep`, för att kontrollera ljusnivåerna och tända eller släcka LED-lampan:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Denna kod kontrollerar värdet `light`. Om detta är mindre än 300 anropar den metoden `on` i klassen `GroveLed`, vilket skickar ett digitalt värde på 1 till LED-lampan och tänder den. Om ljusvärdet är större än eller lika med 300 anropar den metoden `off`, vilket skickar ett digitalt värde på 0 till LED-lampan och släcker den.

    > 💁 Denna kod ska vara indragen på samma nivå som raden `print('Light level:', light)` för att vara inuti while-loopen!

1. Från VS Code-terminalen, kör följande för att köra din Python-app:

    ```sh
    python3 app.py
    ```

    Ljusvärden kommer att skrivas ut i konsolen.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Ändra inställningarna för *Value* eller *Random* för att variera ljusnivån över och under 300. LED-lampan kommer att tändas och släckas.

![LED-lampan i CounterFit-appen tänds och släcks när ljusnivån ändras](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Du kan hitta denna kod i mappen [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Ditt nattlampa-program blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.