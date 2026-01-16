<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T14:28:15+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "hr"
}
-->
# Pozovite svoj detektor objekata s IoT uređaja - Wio Terminal

Kada je vaš detektor objekata objavljen, može se koristiti s vašeg IoT uređaja.

## Kopirajte projekt klasifikatora slika

Većina vašeg detektora zaliha ista je kao i klasifikator slika koji ste kreirali u prethodnoj lekciji.

### Zadatak - kopirajte projekt klasifikatora slika

1. Spojite svoj ArduCam na Wio Terminal, prateći korake iz [lekcije 2 projekta proizvodnje](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Također biste mogli fiksirati kameru u jednom položaju, na primjer, tako da objesite kabel preko kutije ili limenke, ili pričvrstite kameru na kutiju pomoću obostrane ljepljive trake.

1. Kreirajte potpuno novi projekt za Wio Terminal koristeći PlatformIO. Nazovite ovaj projekt `stock-counter`.

1. Ponovite korake iz [lekcije 2 projekta proizvodnje](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) kako biste snimili slike s kamere.

1. Ponovite korake iz [lekcije 2 projekta proizvodnje](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) kako biste pozvali klasifikator slika. Većina ovog koda će se ponovno koristiti za detekciju objekata.

## Promijenite kod iz klasifikatora u detektor slika

Kod koji ste koristili za klasifikaciju slika vrlo je sličan kodu za detekciju objekata. Glavna razlika je URL koji se poziva, a koji ste dobili iz Custom Vision, te rezultati poziva.

### Zadatak - promijenite kod iz klasifikatora u detektor slika

1. Dodajte sljedeću direktivu za uključivanje na vrh datoteke `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Preimenujte funkciju `classifyImage` u `detectStock`, kako naziv funkcije, tako i poziv u funkciji `buttonPressed`.

1. Iznad funkcije `detectStock`, deklarirajte prag za filtriranje svih detekcija s niskom vjerojatnošću:

    ```cpp
    const float threshold = 0.3f;
    ```

    Za razliku od klasifikatora slika koji vraća samo jedan rezultat po oznaci, detektor objekata će vratiti više rezultata, pa je potrebno filtrirati one s niskom vjerojatnošću.

1. Iznad funkcije `detectStock`, deklarirajte funkciju za obradu predikcija:

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

    Ova funkcija uzima popis predikcija i ispisuje ih na serijski monitor.

1. U funkciji `detectStock`, zamijenite sadržaj `for` petlje koja prolazi kroz predikcije sljedećim:

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

    Ova petlja prolazi kroz predikcije, uspoređujući vjerojatnost s pragom. Sve predikcije koje imaju vjerojatnost veću od praga dodaju se u `list` i prosljeđuju funkciji `processPredictions`.

1. Prenesite i pokrenite svoj kod. Usmjerite kameru prema objektima na polici i pritisnite tipku C. Vidjet ćete izlaz na serijskom monitoru:

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

    > 💁 Možda ćete trebati prilagoditi `threshold` na odgovarajuću vrijednost za vaše slike.

    Moći ćete vidjeti sliku koja je snimljena, kao i ove vrijednosti na kartici **Predictions** u Custom Vision.

    ![4 konzerve paste od rajčice na polici s predikcijama za 4 detekcije od 35.8%, 33.5%, 25.7% i 16.6%](../../../../../translated_images/hr/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Ovaj kod možete pronaći u mapi [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Vaš program za brojanje zaliha bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.