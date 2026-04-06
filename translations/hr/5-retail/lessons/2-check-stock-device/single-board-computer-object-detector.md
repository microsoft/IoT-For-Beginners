# Pozovite svoj detektor objekata s IoT uređaja - Virtualni IoT hardver i Raspberry Pi

Kada je vaš detektor objekata objavljen, može se koristiti s vašeg IoT uređaja.

## Kopirajte projekt klasifikatora slika

Većina vašeg detektora zaliha ista je kao i klasifikator slika koji ste kreirali u prethodnoj lekciji.

### Zadatak - kopirajte projekt klasifikatora slika

1. Napravite mapu pod nazivom `stock-counter` na svom računalu ako koristite virtualni IoT uređaj, ili na svom Raspberry Pi uređaju. Ako koristite virtualni IoT uređaj, pobrinite se da postavite virtualno okruženje.

1. Postavite hardver kamere.

    * Ako koristite Raspberry Pi, trebat ćete postaviti PiCamera. Također biste mogli fiksirati kameru u jednom položaju, na primjer, tako da objesite kabel preko kutije ili limenke, ili pričvrstite kameru na kutiju pomoću obostrane ljepljive trake.
    * Ako koristite virtualni IoT uređaj, trebat ćete instalirati CounterFit i CounterFit PyCamera shim. Ako ćete koristiti statične slike, snimite nekoliko slika koje vaš detektor objekata još nije vidio. Ako ćete koristiti web kameru, pobrinite se da je postavljena tako da može vidjeti zalihe koje detektirate.

1. Ponovite korake iz [lekcije 2 projekta proizvodnje](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) za snimanje slika pomoću kamere.

1. Ponovite korake iz [lekcije 2 projekta proizvodnje](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) za pozivanje klasifikatora slika. Većina ovog koda će se ponovno koristiti za detekciju objekata.

## Promijenite kod iz klasifikatora u detektor slika

Kod koji ste koristili za klasifikaciju slika vrlo je sličan kodu za detekciju objekata. Glavna razlika je metoda koja se poziva na Custom Vision SDK-u i rezultati poziva.

### Zadatak - promijenite kod iz klasifikatora u detektor slika

1. Obrišite tri linije koda koje klasificiraju sliku i obrađuju predikcije:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Uklonite ove tri linije.

1. Dodajte sljedeći kod za detekciju objekata na slici:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ovaj kod poziva metodu `detect_image` na prediktoru kako bi pokrenuo detektor objekata. Zatim prikuplja sve predikcije s vjerojatnošću iznad praga i ispisuje ih na konzolu.

    Za razliku od klasifikatora slika koji vraća samo jedan rezultat po oznaci, detektor objekata vraća više rezultata, pa je potrebno filtrirati one s niskom vjerojatnošću.

1. Pokrenite ovaj kod i on će snimiti sliku, poslati je detektoru objekata i ispisati detektirane objekte. Ako koristite virtualni IoT uređaj, osigurajte da imate odgovarajuću sliku postavljenu u CounterFit-u ili da je vaša web kamera odabrana. Ako koristite Raspberry Pi, pobrinite se da vaša kamera pokazuje na objekte na polici.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Možda ćete trebati prilagoditi `threshold` na odgovarajuću vrijednost za vaše slike.

    Moći ćete vidjeti sliku koja je snimljena i ove vrijednosti u kartici **Predictions** u Custom Vision.

    ![4 limenke paste od rajčice na polici s predikcijama za 4 detekcije od 35.8%, 33.5%, 25.7% i 16.6%](../../../../../translated_images/hr/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Ovaj kod možete pronaći u mapi [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) ili [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Vaš program za brojanje zaliha bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.