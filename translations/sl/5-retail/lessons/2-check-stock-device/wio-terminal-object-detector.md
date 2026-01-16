<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T14:28:30+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "sl"
}
-->
# Pokličite svoj detektor objektov iz IoT naprave - Wio Terminal

Ko je vaš detektor objektov objavljen, ga lahko uporabite iz svoje IoT naprave.

## Kopirajte projekt za razvrščanje slik

Večina vašega detektorja zalog je enaka kot razvrščevalnik slik, ki ste ga ustvarili v prejšnji lekciji.

### Naloga - kopirajte projekt za razvrščanje slik

1. Povežite svojo ArduCam z Wio Terminalom, tako da sledite korakom iz [lekcije 2 proizvodnega projekta](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Morda boste želeli kamero pritrditi v en položaj, na primer tako, da kabel obesite čez škatlo ali pločevinko, ali pa kamero pritrdite na škatlo z dvostranskim lepilnim trakom.

1. Ustvarite povsem nov projekt za Wio Terminal z uporabo PlatformIO. Poimenujte ta projekt `stock-counter`.

1. Ponovite korake iz [lekcije 2 proizvodnega projekta](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) za zajem slik s kamere.

1. Ponovite korake iz [lekcije 2 proizvodnega projekta](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) za klic razvrščevalnika slik. Večina te kode bo ponovno uporabljena za zaznavanje objektov.

## Spremenite kodo iz razvrščevalnika v detektor slik

Koda, ki ste jo uporabili za razvrščanje slik, je zelo podobna kodi za zaznavanje objektov. Glavna razlika je URL, ki ste ga pridobili iz Custom Vision, in rezultati klica.

### Naloga - spremenite kodo iz razvrščevalnika v detektor slik

1. Dodajte naslednjo direktivo `include` na vrh datoteke `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Preimenujte funkcijo `classifyImage` v `detectStock`, tako ime funkcije kot klic v funkciji `buttonPressed`.

1. Nad funkcijo `detectStock` deklarirajte prag za filtriranje vseh zaznavanj z nizko verjetnostjo:

    ```cpp
    const float threshold = 0.3f;
    ```

    Za razliko od razvrščevalnika slik, ki vrne samo en rezultat na oznako, detektor objektov vrne več rezultatov, zato je treba vse z nizko verjetnostjo filtrirati.

1. Nad funkcijo `detectStock` deklarirajte funkcijo za obdelavo napovedi:

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

    Ta funkcija sprejme seznam napovedi in jih natisne na serijski monitor.

1. V funkciji `detectStock` zamenjajte vsebino zanke `for`, ki pregleduje napovedi, z naslednjim:

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

    Ta zanka pregleduje napovedi in primerja verjetnost s pragom. Vse napovedi z verjetnostjo, višjo od praga, se dodajo v `list` in posredujejo funkciji `processPredictions`.

1. Naložite in zaženite svojo kodo. Usmerite kamero na predmete na polici in pritisnite gumb C. Rezultate boste videli na serijskem monitorju:

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

    > 💁 Morda boste morali prilagoditi `threshold` na ustrezno vrednost za vaše slike.

    Videli boste sliko, ki je bila posneta, in te vrednosti v zavihku **Predictions** v Custom Vision.

    ![4 pločevinke paradižnikovega koncentrata na polici z napovedmi za 4 zaznave: 35,8 %, 33,5 %, 25,7 % in 16,6 %](../../../../../translated_images/sl/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 To kodo lahko najdete v mapi [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Vaš program za štetje zalog je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas opozarjamo, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.