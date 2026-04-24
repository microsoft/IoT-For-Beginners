# Pokličite svoj detektor objektov iz svoje IoT naprave - Virtualna IoT strojna oprema in Raspberry Pi

Ko je vaš detektor objektov objavljen, ga lahko uporabite iz svoje IoT naprave.

## Kopirajte projekt za razvrščanje slik

Večina vašega detektorja zalog je enaka razvrščevalniku slik, ki ste ga ustvarili v prejšnji lekciji.

### Naloga - kopirajte projekt za razvrščanje slik

1. Ustvarite mapo z imenom `stock-counter` na svojem računalniku, če uporabljate virtualno IoT napravo, ali na svojem Raspberry Pi. Če uporabljate virtualno IoT napravo, poskrbite, da nastavite virtualno okolje.

1. Nastavite strojno opremo kamere.

    * Če uporabljate Raspberry Pi, boste morali namestiti PiCamera. Morda boste želeli kamero pritrditi v en položaj, na primer tako, da kabel obesite čez škatlo ali pločevinko, ali pa kamero pritrdite na škatlo z obojestranskim lepilnim trakom.
    * Če uporabljate virtualno IoT napravo, boste morali namestiti CounterFit in CounterFit PyCamera shim. Če boste uporabljali statične slike, zajemite nekaj slik, ki jih vaš detektor objektov še ni videl. Če boste uporabljali spletno kamero, poskrbite, da bo postavljena tako, da bo videla zalogo, ki jo zaznavate.

1. Ponovite korake iz [lekcije 2 projekta za proizvodnjo](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) za zajemanje slik s kamere.

1. Ponovite korake iz [lekcije 2 projekta za proizvodnjo](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) za klic razvrščevalnika slik. Večina te kode bo ponovno uporabljena za zaznavanje objektov.

## Spremenite kodo iz razvrščevalnika v detektor slik

Koda, ki ste jo uporabili za razvrščanje slik, je zelo podobna kodi za zaznavanje objektov. Glavna razlika je metoda, ki jo pokličete v Custom Vision SDK, in rezultati klica.

### Naloga - spremenite kodo iz razvrščevalnika v detektor slik

1. Izbrišite tri vrstice kode, ki razvrščajo sliko in obdelujejo napovedi:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Odstranite te tri vrstice.

1. Dodajte naslednjo kodo za zaznavanje objektov na sliki:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ta koda pokliče metodo `detect_image` na prediktorju, da zažene detektor objektov. Nato zbere vse napovedi z verjetnostjo nad pragom in jih izpiše v konzolo.

    Za razliko od razvrščevalnika slik, ki vrne le en rezultat na oznako, detektor objektov vrne več rezultatov, zato je treba vse z nizko verjetnostjo filtrirati.

1. Zaženite to kodo, ki bo zajela sliko, jo poslala detektorju objektov in izpisala zaznane objekte. Če uporabljate virtualno IoT napravo, poskrbite, da imate ustrezno sliko nastavljeno v CounterFit, ali da je izbrana vaša spletna kamera. Če uporabljate Raspberry Pi, poskrbite, da je vaša kamera usmerjena proti objektom na polici.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Morda boste morali prilagoditi `threshold` na ustrezno vrednost za vaše slike.

    Videli boste lahko sliko, ki je bila posneta, in te vrednosti v zavihku **Predictions** v Custom Vision.

    ![4 pločevinke paradižnikove paste na polici z napovedmi za 4 zaznave: 35,8 %, 33,5 %, 25,7 % in 16,6 %](../../../../../translated_images/sl/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 To kodo lahko najdete v mapi [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) ali [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Vaš program za štetje zalog je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.