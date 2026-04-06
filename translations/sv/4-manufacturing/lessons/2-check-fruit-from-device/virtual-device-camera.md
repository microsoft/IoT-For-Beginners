# Ta en bild - Virtuell IoT-hårdvara

I den här delen av lektionen kommer du att lägga till en kamerasensor till din virtuella IoT-enhet och läsa bilder från den.

## Hårdvara

Den virtuella IoT-enheten kommer att använda en simulerad kamera som skickar bilder antingen från filer eller från din webbkamera.

### Lägg till kameran i CounterFit

För att använda en virtuell kamera behöver du lägga till en i CounterFit-appen.

#### Uppgift - lägg till kameran i CounterFit

Lägg till kameran i CounterFit-appen.

1. Skapa en ny Python-app på din dator i en mapp som heter `fruit-quality-detector` med en enda fil som heter `app.py` och en Python-virtuell miljö, och lägg till CounterFit pip-paket.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa och ställa in ett CounterFit Python-projekt i lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installera ett extra Pip-paket för att installera en CounterFit-shim som kan kommunicera med kamerasensorer genom att simulera vissa delar av [Picamera Pip-paketet](https://pypi.org/project/picamera/). Se till att du installerar detta från en terminal med den virtuella miljön aktiverad.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Se till att CounterFit-webbappen körs.

1. Skapa en kamera:

    1. I *Create sensor*-rutan i *Sensors*-panelen, öppna rullgardinsmenyn *Sensor type* och välj *Camera*.

    1. Ställ in *Name* till `Picamera`.

    1. Välj knappen **Add** för att skapa kameran.

    ![Kamerainställningarna](../../../../../translated_images/sv/counterfit-create-camera.a5de97f59c0bd3cb.webp)

    Kameran kommer att skapas och visas i sensorlistan.

    ![Kameran skapad](../../../../../translated_images/sv/counterfit-camera.001ec52194c8ee5d.webp)

## Programmera kameran

Den virtuella IoT-enheten kan nu programmeras för att använda den virtuella kameran.

### Uppgift - programmera kameran

Programmera enheten.

1. Se till att appen `fruit-quality-detector` är öppen i VS Code.

1. Öppna filen `app.py`.

1. Lägg till följande kod högst upp i `app.py` för att ansluta appen till CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lägg till följande kod i din `app.py`-fil:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Den här koden importerar några bibliotek som behövs, inklusive klassen `PiCamera` från biblioteket counterfit_shims_picamera.

1. Lägg till följande kod under detta för att initiera kameran:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Den här koden skapar ett PiCamera-objekt och ställer in upplösningen till 640x480. Även om högre upplösningar stöds, fungerar bildklassificeraren på mycket mindre bilder (227x227), så det finns ingen anledning att ta och skicka större bilder.

    Raden `camera.rotation = 0` ställer in bildens rotation i grader. Om du behöver rotera bilden från webbkameran eller filen, ställ in detta som lämpligt. Till exempel, om du vill ändra bilden av en banan på en webbkamera i liggande läge till stående, ställ in `camera.rotation = 90`.

1. Lägg till följande kod under detta för att ta bilden som binär data:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Den här koden skapar ett `BytesIO`-objekt för att lagra binär data. Bilden läses från kameran som en JPEG-fil och lagras i detta objekt. Detta objekt har en positionsindikator för att veta var det befinner sig i datan så att mer data kan skrivas till slutet om det behövs, så raden `image.seek(0)` flyttar denna position tillbaka till början så att all data kan läsas senare.

1. Lägg till följande kod under detta för att spara bilden till en fil:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Den här koden öppnar en fil som heter `image.jpg` för skrivning, läser sedan all data från `BytesIO`-objektet och skriver det till filen.

    > 💁 Du kan ta bilden direkt till en fil istället för ett `BytesIO`-objekt genom att skicka filnamnet till `camera.capture`-anropet. Anledningen till att använda `BytesIO`-objektet är att du senare i denna lektion kan skicka bilden till din bildklassificerare.

1. Konfigurera bilden som kameran i CounterFit kommer att ta. Du kan antingen ställa in *Source* till *File*, sedan ladda upp en bildfil, eller ställa in *Source* till *WebCam*, och bilder kommer att tas från din webbkamera. Se till att du väljer knappen **Set** efter att ha valt en bild eller din webbkamera.

    ![CounterFit med en fil inställd som bildkälla och en webbkamera som visar en person som håller en banan i en förhandsvisning av webbkameran](../../../../../translated_images/sv/counterfit-camera-options.eb3bd5150a8e7dff.webp)

1. En bild kommer att tas och sparas som `image.jpg` i den aktuella mappen. Du kommer att se denna fil i VS Code explorer. Välj filen för att visa bilden. Om den behöver roteras, uppdatera raden `camera.rotation = 0` som nödvändigt och ta en ny bild.

> 💁 Du kan hitta denna kod i mappen [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Ditt kameraprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.