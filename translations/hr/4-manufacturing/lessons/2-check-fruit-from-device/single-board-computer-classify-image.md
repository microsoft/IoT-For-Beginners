# Klasificirajte sliku - Virtualni IoT hardver i Raspberry Pi

U ovom dijelu lekcije, poslat ćete sliku snimljenu kamerom usluzi Custom Vision kako biste je klasificirali.

## Slanje slika u Custom Vision

Usluga Custom Vision ima Python SDK koji možete koristiti za klasifikaciju slika.

### Zadatak - slanje slika u Custom Vision

1. Otvorite mapu `fruit-quality-detector` u VS Code. Ako koristite virtualni IoT uređaj, provjerite je li virtualno okruženje pokrenuto u terminalu.

1. Python SDK za slanje slika u Custom Vision dostupan je kao Pip paket. Instalirajte ga sljedećom naredbom:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Dodajte sljedeće naredbe za uvoz na vrh datoteke `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Ovo uključuje neke module iz biblioteka Custom Vision, jedan za autentifikaciju pomoću predikcijskog ključa, i jedan za pružanje klase predikcijskog klijenta koja može pozvati Custom Vision.

1. Dodajte sljedeći kod na kraj datoteke:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Zamijenite `<prediction_url>` s URL-om koji ste kopirali iz dijaloga *Prediction URL* ranije u ovoj lekciji. Zamijenite `<prediction key>` s predikcijskim ključem koji ste kopirali iz istog dijaloga.

1. URL za predikciju koji je pružen u dijalogu *Prediction URL* dizajniran je za korištenje prilikom direktnog pozivanja REST krajnje točke. Python SDK koristi dijelove URL-a na različitim mjestima. Dodajte sljedeći kod kako biste razdvojili ovaj URL na potrebne dijelove:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Ovo razdvaja URL, izvlačeći krajnju točku `https://<location>.api.cognitive.microsoft.com`, ID projekta i naziv objavljene iteracije.

1. Kreirajte objekt prediktora za izvođenje predikcije pomoću sljedećeg koda:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` obuhvaća predikcijski ključ. Oni se zatim koriste za kreiranje objekta predikcijskog klijenta koji pokazuje na krajnju točku.

1. Pošaljite sliku u Custom Vision koristeći sljedeći kod:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Ovo vraća sliku na početak, a zatim je šalje predikcijskom klijentu.

1. Na kraju, prikažite rezultate pomoću sljedećeg koda:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ovo će proći kroz sve predikcije koje su vraćene i prikazati ih u terminalu. Vjerojatnosti koje se vraćaju su decimalni brojevi od 0-1, gdje je 0 šansa od 0% da se podudara s oznakom, a 1 šansa od 100%.

    > 💁 Klasifikatori slika vratit će postotke za sve oznake koje su korištene. Svaka oznaka imat će vjerojatnost da se slika podudara s tom oznakom.

1. Pokrenite svoj kod, s kamerom usmjerenom na neko voće, ili odgovarajući set slika, ili voće vidljivo na vašoj web kameri ako koristite virtualni IoT hardver. Vidjet ćete izlaz u konzoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Moći ćete vidjeti sliku koja je snimljena, i ove vrijednosti u **Predictions** kartici u Custom Vision.

    ![Banana u Custom Visionu predviđena kao zrela s 56.8% i nezrela s 43.1%](../../../../../translated_images/hr/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Ovaj kod možete pronaći u mapi [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) ili [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Vaš program za klasifikaciju kvalitete voća bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.