<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T10:49:40+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "ro"
}
-->
# Apelarea detectorului de obiecte de pe dispozitivul IoT - Wio Terminal

După ce detectorul de obiecte a fost publicat, acesta poate fi utilizat de pe dispozitivul tău IoT.

## Copiază proiectul de clasificare a imaginilor

Majoritatea codului pentru detectorul de stocuri este similar cu cel al clasificatorului de imagini pe care l-ai creat într-o lecție anterioară.

### Sarcină - copiază proiectul de clasificare a imaginilor

1. Conectează camera ArduCam la Wio Terminal, urmând pașii din [lecția 2 a proiectului de producție](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    De asemenea, ai putea fixa camera într-o poziție stabilă, de exemplu, prin agățarea cablului peste o cutie sau o conservă, sau prin lipirea camerei de o cutie cu bandă dublu adezivă.

1. Creează un proiect nou pentru Wio Terminal folosind PlatformIO. Denumește acest proiect `stock-counter`.

1. Repetă pașii din [lecția 2 a proiectului de producție](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) pentru a captura imagini de la cameră.

1. Repetă pașii din [lecția 2 a proiectului de producție](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) pentru a apela clasificatorul de imagini. Majoritatea acestui cod va fi reutilizat pentru detectarea obiectelor.

## Modifică codul de la clasificator la detector de imagini

Codul utilizat pentru clasificarea imaginilor este foarte asemănător cu cel pentru detectarea obiectelor. Principala diferență constă în URL-ul apelat, pe care l-ai obținut din Custom Vision, și rezultatele apelului.

### Sarcină - modifică codul de la clasificator la detector de imagini

1. Adaugă următoarea directivă `include` în partea de sus a fișierului `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Redenumește funcția `classifyImage` în `detectStock`, atât numele funcției, cât și apelul din funcția `buttonPressed`.

1. Deasupra funcției `detectStock`, declară un prag pentru a filtra orice detecții cu o probabilitate scăzută:

    ```cpp
    const float threshold = 0.3f;
    ```

    Spre deosebire de un clasificator de imagini care returnează un singur rezultat pentru fiecare etichetă, detectorul de obiecte va returna mai multe rezultate, astfel încât cele cu o probabilitate scăzută trebuie filtrate.

1. Deasupra funcției `detectStock`, declară o funcție pentru procesarea predicțiilor:

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

    Aceasta primește o listă de predicții și le afișează în monitorul serial.

1. În funcția `detectStock`, înlocuiește conținutul buclei `for` care parcurge predicțiile cu următorul cod:

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

    Aceasta parcurge predicțiile, comparând probabilitatea cu pragul. Toate predicțiile care au o probabilitate mai mare decât pragul sunt adăugate într-o `list` și transmise funcției `processPredictions`.

1. Încarcă și rulează codul. Îndreaptă camera spre obiecte de pe un raft și apasă butonul C. Vei vedea rezultatele în monitorul serial:

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

    > 💁 Este posibil să fie nevoie să ajustezi valoarea `threshold` pentru a se potrivi imaginilor tale.

    Vei putea vedea imaginea capturată și aceste valori în fila **Predictions** din Custom Vision.

    ![4 conserve de pastă de roșii pe un raft cu predicții pentru cele 4 detecții de 35.8%, 33.5%, 25.7% și 16.6%](../../../../../translated_images/ro/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Poți găsi acest cod în folderul [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Programul tău de numărare a stocurilor a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.