# Läs GPS-data - Virtuell IoT-hårdvara

I den här delen av lektionen kommer du att lägga till en GPS-sensor till din virtuella IoT-enhet och läsa värden från den.

## Virtuell hårdvara

Den virtuella IoT-enheten kommer att använda en simulerad GPS-sensor som är tillgänglig via UART genom en seriell port.

En fysisk GPS-sensor har en antenn för att ta emot radiovågor från GPS-satelliter och omvandla GPS-signaler till GPS-data. Den virtuella versionen simulerar detta genom att låta dig antingen ställa in en latitud och longitud, skicka råa NMEA-meningar eller ladda upp en GPX-fil med flera platser som kan returneras sekventiellt.

> 🎓 NMEA-meningar kommer att behandlas senare i denna lektion

### Lägg till sensorn i CounterFit

För att använda en virtuell GPS-sensor behöver du lägga till en i CounterFit-appen.

#### Uppgift - lägg till sensorn i CounterFit

Lägg till GPS-sensorn i CounterFit-appen.

1. Skapa en ny Python-app på din dator i en mapp som heter `gps-sensor` med en enda fil som heter `app.py` och en virtuell Python-miljö, och lägg till CounterFit pip-paketen.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa och ställa in ett CounterFit Python-projekt i lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installera ett ytterligare Pip-paket för att installera en CounterFit-shim som kan kommunicera med UART-baserade sensorer via en seriell anslutning. Se till att du installerar detta från en terminal med den virtuella miljön aktiverad.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Se till att CounterFit-webbappen körs.

1. Skapa en GPS-sensor:

    1. I rutan *Create sensor* i panelen *Sensors*, öppna rullgardinsmenyn *Sensor type* och välj *UART GPS*.

    1. Lämna *Port* inställd på */dev/ttyAMA0*.

    1. Välj knappen **Add** för att skapa GPS-sensorn på porten `/dev/ttyAMA0`.

    ![Inställningar för GPS-sensorn](../../../../../translated_images/sv/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    GPS-sensorn kommer att skapas och visas i sensorlistan.

    ![Den skapade GPS-sensorn](../../../../../translated_images/sv/counterfit-gps-sensor.3fbb15af0a536756.webp)

## Programmera GPS-sensorn

Den virtuella IoT-enheten kan nu programmeras för att använda den virtuella GPS-sensorn.

### Uppgift - programmera GPS-sensorn

Programmera GPS-sensorappen.

1. Se till att appen `gps-sensor` är öppen i VS Code.

1. Öppna filen `app.py`.

1. Lägg till följande kod högst upp i `app.py` för att ansluta appen till CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lägg till följande kod under detta för att importera några nödvändiga bibliotek, inklusive biblioteket för CounterFit-serieporten:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Denna kod importerar modulen `serial` från Pip-paketet `counterfit_shims_serial`. Den ansluter sedan till seriella porten `/dev/ttyAMA0` - detta är adressen till den seriella port som den virtuella GPS-sensorn använder för sin UART-port.

1. Lägg till följande kod under detta för att läsa från den seriella porten och skriva ut värdena till konsolen:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    En funktion som heter `print_gps_data` definieras, som skriver ut raden som skickas till den till konsolen.

    Därefter loopar koden för alltid och läser så många rader text som möjligt från den seriella porten i varje loop. Den anropar funktionen `print_gps_data` för varje rad.

    När all data har lästs, sover loopen i 1 sekund och försöker sedan igen.

1. Kör denna kod och se till att du använder en annan terminal än den där CounterFit-appen körs, så att CounterFit-appen förblir igång.

1. Ändra värdet på GPS-sensorn från CounterFit-appen. Du kan göra detta på ett av följande sätt:

    * Ställ in **Source** till `Lat/Lon` och ange en specifik latitud, longitud och antal satelliter som används för att få GPS-fix. Detta värde skickas endast en gång, så markera rutan **Repeat** för att få data att upprepas varje sekund.

      ![GPS-sensorn med lat lon vald](../../../../../translated_images/sv/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Ställ in **Source** till `NMEA` och lägg till några NMEA-meningar i textrutan. Alla dessa värden kommer att skickas, med en fördröjning på 1 sekund innan varje ny GGA (positionsfixerings-)mening kan läsas.

      ![GPS-sensorn med NMEA-meningar inställda](../../../../../translated_images/sv/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Du kan använda ett verktyg som [nmeagen.org](https://www.nmeagen.org) för att generera dessa meningar genom att rita på en karta. Dessa värden skickas endast en gång, så markera rutan **Repeat** för att få data att upprepas en sekund efter att allt har skickats.

    * Ställ in **Source** till GPX-fil och ladda upp en GPX-fil med spårplatser. Du kan ladda ner GPX-filer från ett antal populära kart- och vandringssajter, som [AllTrails](https://www.alltrails.com/). Dessa filer innehåller flera GPS-platser som en rutt, och GPS-sensorn kommer att returnera varje ny plats med 1 sekunds intervall.

      ![GPS-sensorn med en GPX-fil inställd](../../../../../translated_images/sv/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Dessa värden skickas endast en gång, så markera rutan **Repeat** för att få data att upprepas en sekund efter att allt har skickats.

    När du har konfigurerat GPS-inställningarna, välj knappen **Set** för att tillämpa dessa värden på sensorn.

1. Du kommer att se råutdata från GPS-sensorn, något i stil med följande:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Du kan hitta denna kod i mappen [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Din GPS-sensorprogrammering lyckades!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.