# Läs GPS-data - Raspberry Pi

I den här delen av lektionen kommer du att lägga till en GPS-sensor till din Raspberry Pi och läsa värden från den.

## Hårdvara

Raspberry Pi behöver en GPS-sensor.

Sensorn du kommer att använda är en [Grove GPS Air530-sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Den här sensorn kan ansluta till flera GPS-system för en snabb och exakt positionering. Sensorn består av två delar - kärnelektroniken i sensorn och en extern antenn som är ansluten med en tunn kabel för att ta emot radiosignaler från satelliterna.

Detta är en UART-sensor, så den skickar GPS-data via UART.

## Anslut GPS-sensorn

Grove GPS-sensorn kan anslutas till Raspberry Pi.

### Uppgift - anslut GPS-sensorn

Anslut GPS-sensorn.

![En Grove GPS-sensor](../../../../../translated_images/sv/grove-gps-sensor.247943bf69b03f0d.webp)

1. Sätt i ena änden av en Grove-kabel i uttaget på GPS-sensorn. Den går bara att sätta i på ett sätt.

1. Med Raspberry Pi avstängd, anslut den andra änden av Grove-kabeln till UART-uttaget märkt **UART** på Grove Base-hatten som är ansluten till Pi. Detta uttag finns på den mellersta raden, på sidan närmast SD-kortplatsen, motsatt sida från USB-portarna och ethernet-uttaget.

    ![Grove GPS-sensorn ansluten till UART-uttaget](../../../../../translated_images/sv/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Placera GPS-sensorn så att den anslutna antennen har fri sikt mot himlen - helst nära ett öppet fönster eller utomhus. Det är lättare att få en tydligare signal utan hinder för antennen.

## Programmera GPS-sensorn

Raspberry Pi kan nu programmeras för att använda den anslutna GPS-sensorn.

### Uppgift - programmera GPS-sensorn

Programmera enheten.

1. Starta Pi och vänta tills den har startat upp.

1. GPS-sensorn har två lysdioder - en blå lysdiod som blinkar när data överförs och en grön lysdiod som blinkar varje sekund när den tar emot data från satelliter. Se till att den blå lysdioden blinkar när du startar Pi. Efter några minuter kommer den gröna lysdioden att blinka - om inte, kan du behöva justera antennens position.

1. Starta VS Code, antingen direkt på Pi eller anslut via Remote SSH-tillägget.

    > ⚠️ Du kan hänvisa till [instruktionerna för att ställa in och starta VS Code i lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Med nyare versioner av Raspberry Pi som stöder Bluetooth finns det en konflikt mellan den seriella porten som används för Bluetooth och den som används av Grove UART-porten. För att lösa detta, gör följande:

    1. Från VS Code-terminalen, redigera filen `/boot/config.txt` med hjälp av `nano`, en inbyggd terminaltextredigerare, med följande kommando:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Den här filen kan inte redigeras av VS Code eftersom du behöver redigera den med `sudo`-behörighet, en förhöjd behörighet. VS Code körs inte med denna behörighet.

    1. Använd piltangenterna för att navigera till slutet av filen. Kopiera sedan koden nedan och klistra in den i slutet av filen:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Du kan klistra in med de vanliga tangentbordsgenvägarna för din enhet (`Ctrl+v` på Windows, Linux eller Raspberry Pi OS, `Cmd+v` på macOS).

    1. Spara filen och avsluta nano genom att trycka på `Ctrl+x`. Tryck på `y` när du blir tillfrågad om du vill spara den ändrade bufferten och tryck sedan på `enter` för att bekräfta att du vill skriva över `/boot/config.txt`.

        > Om du gör ett misstag kan du avsluta utan att spara och sedan upprepa dessa steg.

    1. Redigera filen `/boot/cmdline.txt` i nano med följande kommando:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Den här filen innehåller ett antal nyckel/värde-par separerade med mellanslag. Ta bort alla nyckel/värde-par för nyckeln `console`. De ser förmodligen ut så här:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Du kan navigera till dessa poster med piltangenterna och sedan ta bort dem med de vanliga `del`- eller `backspace`-tangenterna.

        Till exempel, om din ursprungliga fil ser ut så här:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Den nya versionen kommer att se ut så här:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Följ stegen ovan för att spara filen och avsluta nano.

    1. Starta om din Pi och anslut sedan igen i VS Code när Pi har startat om.

1. Från terminalen, skapa en ny mapp i hemmakatalogen för användaren `pi` som heter `gps-sensor`. Skapa en fil i den här mappen som heter `app.py`.

1. Öppna den här mappen i VS Code.

1. GPS-modulen skickar UART-data via en seriell port. Installera Pip-paketet `pyserial` för att kommunicera med den seriella porten från din Python-kod:

    ```sh
    pip3 install pyserial
    ```

1. Lägg till följande kod i din `app.py`-fil:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Den här koden importerar modulen `serial` från Pip-paketet `pyserial`. Den ansluter sedan till den seriella porten `/dev/ttyAMA0` - detta är adressen till den seriella port som Grove Pi Base Hat använder för sin UART-port. Den rensar sedan all befintlig data från denna seriella anslutning.

    Därefter definieras en funktion som heter `print_gps_data` som skriver ut raden som skickas till den i konsolen.

    Sedan loopar koden för alltid och läser så många rader text som möjligt från den seriella porten i varje loop. Den anropar funktionen `print_gps_data` för varje rad.

    När all data har lästs sover loopen i 1 sekund och försöker sedan igen.

1. Kör den här koden. Du kommer att se råutdata från GPS-sensorn, något i stil med följande:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Om du får något av följande fel när du stoppar och startar om din kod, lägg till ett `try - except`-block i din while-loop.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Du kan hitta den här koden i mappen [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Ditt GPS-sensorprogram lyckades!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.