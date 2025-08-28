<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T12:22:30+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "sl"
}
-->
# Razvrščanje slike z uporabo IoT Edge naprave za prepoznavanje slik - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste uporabili prepoznavalnik slik, ki deluje na napravi IoT Edge.

## Uporaba prepoznavalnika IoT Edge

IoT napravo je mogoče preusmeriti, da uporablja prepoznavalnik slik na IoT Edge. URL za prepoznavalnik slik je `http://<IP naslov ali ime>/image`, kjer `<IP naslov ali ime>` zamenjate z IP naslovom ali imenom računalnika, na katerem deluje IoT Edge.

Python knjižnica za Custom Vision deluje samo z modeli, ki so gostovani v oblaku, ne pa z modeli, ki so gostovani na IoT Edge. To pomeni, da boste morali uporabiti REST API za klic prepoznavalnika.

### Naloga - uporaba prepoznavalnika IoT Edge

1. Odprite projekt `fruit-quality-detector` v VS Code, če še ni odprt. Če uporabljate virtualno IoT napravo, se prepričajte, da je virtualno okolje aktivirano.

1. Odprite datoteko `app.py` in odstranite uvozne izjave iz `azure.cognitiveservices.vision.customvision.prediction` in `msrest.authentication`.

1. Na vrh datoteke dodajte naslednji uvoz:

    ```python
    import requests
    ```

1. Izbrišite vso kodo po tem, ko je slika shranjena v datoteko, od `image_file.write(image.read())` do konca datoteke.

1. Na konec datoteke dodajte naslednjo kodo:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Zamenjajte `<URL>` z URL-jem vašega prepoznavalnika.

    Ta koda pošlje REST POST zahtevo prepoznavalniku, pri čemer sliko pošlje kot telo zahteve. Rezultati se vrnejo v obliki JSON, ki se nato dekodira za izpis verjetnosti.

1. Zaženite svojo kodo, pri čemer usmerite kamero na nekaj sadja, ustrezen nabor slik ali sadje, ki je vidno na vaši spletni kameri, če uporabljate virtualno IoT strojno opremo. Izhod boste videli v konzoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 To kodo lahko najdete v mapi [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ali [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Vaš program za prepoznavanje kakovosti sadja je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve AI za prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.