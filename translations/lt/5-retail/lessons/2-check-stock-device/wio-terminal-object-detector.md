# Paleiskite savo objektų detektorių iš IoT įrenginio - Wio Terminal

Kai jūsų objektų detektorius bus paskelbtas, jį galėsite naudoti iš savo IoT įrenginio.

## Nukopijuokite vaizdų klasifikatoriaus projektą

Dauguma jūsų atsargų detektoriaus kodo yra tokia pati kaip vaizdų klasifikatoriaus, kurį sukūrėte ankstesnėje pamokoje.

### Užduotis - nukopijuokite vaizdų klasifikatoriaus projektą

1. Prijunkite savo ArduCam prie Wio Terminal, vadovaudamiesi [2-osios gamybos projekto pamokos](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) žingsniais.

   Taip pat galite pritvirtinti kamerą vienoje pozicijoje, pavyzdžiui, pakabindami kabelį virš dėžutės ar skardinės arba pritvirtindami kamerą prie dėžutės su dvipuse lipnia juosta.

1. Sukurkite visiškai naują Wio Terminal projektą naudodami PlatformIO. Pavadinkite šį projektą `stock-counter`.

1. Pakartokite žingsnius iš [2-osios gamybos projekto pamokos](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), kad užfiksuotumėte vaizdus iš kameros.

1. Pakartokite žingsnius iš [2-osios gamybos projekto pamokos](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), kad iškviestumėte vaizdų klasifikatorių. Dauguma šio kodo bus panaudota objektų aptikimui.

## Pakeiskite kodą iš klasifikatoriaus į vaizdų detektorių

Kodas, kurį naudojote vaizdams klasifikuoti, yra labai panašus į kodą, skirtą objektams aptikti. Pagrindinis skirtumas yra URL, kurį gavote iš Custom Vision, ir skambučio rezultatai.

### Užduotis - pakeiskite kodą iš klasifikatoriaus į vaizdų detektorių

1. Pridėkite šią `include` direktyvą failo `main.cpp` viršuje:

    ```cpp
    #include <vector>
    ```

1. Pervardykite funkciją `classifyImage` į `detectStock`, tiek funkcijos pavadinimą, tiek jos iškvietimą funkcijoje `buttonPressed`.

1. Virš funkcijos `detectStock` deklaruokite slenkstį, kad atmestumėte aptikimus su maža tikimybe:

    ```cpp
    const float threshold = 0.3f;
    ```

    Skirtingai nuo vaizdų klasifikatoriaus, kuris grąžina tik vieną rezultatą kiekvienai žymai, objektų detektorius grąžina kelis rezultatus, todėl tie, kurių tikimybė maža, turi būti atmesti.

1. Virš funkcijos `detectStock` deklaruokite funkciją, skirtą apdoroti prognozes:

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

    Ši funkcija priima prognozių sąrašą ir išveda jas į serijinį monitorių.

1. Funkcijoje `detectStock` pakeiskite `for` ciklo, kuris iteruoja per prognozes, turinį šiuo:

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

    Šis ciklas iteruoja per prognozes, lygindamas tikimybę su slenksčiu. Visos prognozės, kurių tikimybė didesnė už slenkstį, pridedamos į `list` ir perduodamos funkcijai `processPredictions`.

1. Įkelkite ir paleiskite savo kodą. Nukreipkite kamerą į objektus lentynoje ir paspauskite C mygtuką. Rezultatus pamatysite serijiniame monitoriuje:

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

    > 💁 Gali tekti pritaikyti `threshold` reikšmę, kad ji atitiktų jūsų vaizdus.

    Galėsite pamatyti užfiksuotą vaizdą ir šias reikšmes **Predictions** skirtuke Custom Vision.

    ![4 pomidorų pastos skardinės lentynoje su prognozėmis: 35.8%, 33.5%, 25.7% ir 16.6%](../../../../../translated_images/lt/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Šį kodą galite rasti [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) aplanke.

😀 Jūsų atsargų skaičiavimo programa buvo sėkminga!

---

**Atsakomybės atsisakymas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.