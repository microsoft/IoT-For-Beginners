# Razvrsti sliko - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste poslali sliko, ki jo je zajela kamera, storitvi Custom Vision za razvrščanje.

## Pošlji slike v Custom Vision

Storitev Custom Vision ima Python SDK, ki ga lahko uporabite za razvrščanje slik.

### Naloga - pošlji slike v Custom Vision

1. Odprite mapo `fruit-quality-detector` v VS Code. Če uporabljate virtualno IoT napravo, poskrbite, da je virtualno okolje zagnano v terminalu.

1. Python SDK za pošiljanje slik v Custom Vision je na voljo kot Pip paket. Namestite ga z naslednjim ukazom:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Dodajte naslednje uvozne izjave na vrh datoteke `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    To vključuje nekaj modulov iz knjižnic Custom Vision, enega za avtentikacijo s ključem za napovedovanje in enega za zagotavljanje razreda klienta za napovedovanje, ki lahko kliče Custom Vision.

1. Na konec datoteke dodajte naslednjo kodo:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Zamenjajte `<prediction_url>` z URL-jem, ki ste ga prej kopirali iz pogovornega okna *Prediction URL*. Zamenjajte `<prediction key>` s ključem za napovedovanje, ki ste ga kopirali iz istega pogovornega okna.

1. URL za napovedovanje, ki ga je zagotovilo pogovorno okno *Prediction URL*, je zasnovan za neposredno klicanje REST končne točke. Python SDK uporablja dele URL-ja na različnih mestih. Dodajte naslednjo kodo za razdelitev tega URL-ja na potrebne dele:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    To razdeli URL, pri čemer izvleče končno točko `https://<location>.api.cognitive.microsoft.com`, ID projekta in ime objavljene iteracije.

1. Ustvarite objekt za napovedovanje, da izvedete napoved z naslednjo kodo:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` ovijejo ključ za napovedovanje. Ti se nato uporabijo za ustvarjanje objekta klienta za napovedovanje, ki kaže na končno točko.

1. Pošljite sliko v Custom Vision z naslednjo kodo:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    To premakne sliko nazaj na začetek, nato pa jo pošlje klientu za napovedovanje.

1. Na koncu prikažite rezultate z naslednjo kodo:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    To bo zagnalo zanko skozi vse napovedi, ki so bile vrnjene, in jih prikazalo v terminalu. Verjetnosti, ki so vrnjene, so števila s plavajočo vejico od 0 do 1, pri čemer je 0 0% verjetnost ujemanja z oznako, 1 pa 100% verjetnost.

    > 💁 Razvrščevalniki slik bodo vrnili odstotke za vse oznake, ki so bile uporabljene. Vsaka oznaka bo imela verjetnost, da se slika ujema s to oznako.

1. Zaženite svojo kodo, pri čemer naj bo vaša kamera usmerjena na nekaj sadja, ali na ustrezen nabor slik, ali na sadje, vidno na vaši spletni kameri, če uporabljate virtualno IoT strojno opremo. Izpis boste videli v konzoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Videli boste sliko, ki je bila posneta, in te vrednosti v zavihku **Predictions** v Custom Vision.

    ![Banana v Custom Vision, napovedana kot zrela s 56,8% in nezrela s 43,1%](../../../../../translated_images/sl/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 To kodo lahko najdete v mapi [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) ali [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Vaš program za razvrščanje kakovosti sadja je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.