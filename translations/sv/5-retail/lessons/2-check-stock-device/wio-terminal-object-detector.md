# Anropa din objektdetektor från din IoT-enhet - Wio Terminal

När din objektdetektor har publicerats kan den användas från din IoT-enhet.

## Kopiera projektet för bildklassificering

Majoriteten av din lagerdetektor är densamma som bildklassificeraren du skapade i en tidigare lektion.

### Uppgift - kopiera projektet för bildklassificering

1. Anslut din ArduCam till din Wio Terminal, följ stegen från [lektion 2 i tillverkningsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Du kanske också vill fästa kameran i en fast position, till exempel genom att hänga kabeln över en låda eller burk, eller fästa kameran på en låda med dubbelhäftande tejp.

1. Skapa ett helt nytt Wio Terminal-projekt med PlatformIO. Ge detta projekt namnet `stock-counter`.

1. Replikera stegen från [lektion 2 i tillverkningsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) för att ta bilder med kameran.

1. Replikera stegen från [lektion 2 i tillverkningsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) för att anropa bildklassificeraren. Majoriteten av denna kod kommer att återanvändas för att detektera objekt.

## Ändra koden från en klassificerare till en objektdetektor

Koden du använde för att klassificera bilder är mycket lik koden för att detektera objekt. Den största skillnaden är URL:en som anropas, vilken du fick från Custom Vision, och resultaten av anropet.

### Uppgift - ändra koden från en klassificerare till en objektdetektor

1. Lägg till följande include-direktiv högst upp i filen `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Byt namn på funktionen `classifyImage` till `detectStock`, både namnet på funktionen och anropet i funktionen `buttonPressed`.

1. Ovanför funktionen `detectStock`, deklarera en tröskel för att filtrera bort alla detektioner med låg sannolikhet:

    ```cpp
    const float threshold = 0.3f;
    ```

    Till skillnad från en bildklassificerare som bara returnerar ett resultat per tag, kommer objektdetektorn att returnera flera resultat, så de med låg sannolikhet måste filtreras bort.

1. Ovanför funktionen `detectStock`, deklarera en funktion för att bearbeta förutsägelserna:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Denna funktion tar en lista med förutsägelser och skriver ut dem till seriell monitor.

1. I funktionen `detectStock`, ersätt innehållet i `for`-loopen som loopar genom förutsägelserna med följande:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Denna loop går igenom förutsägelserna och jämför sannolikheten med tröskeln. Alla förutsägelser med en sannolikhet högre än tröskeln läggs till i en `list` och skickas till funktionen `processPredictions`.

1. Ladda upp och kör din kod. Rikta kameran mot objekt på en hylla och tryck på C-knappen. Du kommer att se utdata i seriell monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Du kan behöva justera `threshold` till ett lämpligt värde för dina bilder.

    Du kommer att kunna se bilden som togs, och dessa värden i fliken **Predictions** i Custom Vision.

    ![4 burkar tomatpuré på en hylla med förutsägelser för de 4 detektionerna med 35.8%, 33.5%, 25.7% och 16.6%](../../../../../translated_images/sv/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Du kan hitta denna kod i mappen [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Ditt lagerräknarprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.