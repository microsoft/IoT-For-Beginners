<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T08:37:03+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "sk"
}
-->
# Klasifikácia obrázku pomocou IoT Edge zariadenia na klasifikáciu obrázkov - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie budete používať klasifikátor obrázkov bežiaci na IoT Edge zariadení.

## Použitie klasifikátora IoT Edge

IoT zariadenie môže byť presmerované na použitie klasifikátora obrázkov IoT Edge. URL pre klasifikátor obrázkov je `http://<IP adresa alebo názov>/image`, kde `<IP adresa alebo názov>` nahradíte IP adresou alebo názvom hostiteľa počítača, na ktorom beží IoT Edge.

Python knižnica pre Custom Vision funguje iba s modelmi hostovanými v cloude, nie s modelmi hostovanými na IoT Edge. To znamená, že budete musieť použiť REST API na volanie klasifikátora.

### Úloha - použitie klasifikátora IoT Edge

1. Otvorte projekt `fruit-quality-detector` vo VS Code, ak ešte nie je otvorený. Ak používate virtuálne IoT zariadenie, uistite sa, že virtuálne prostredie je aktivované.

1. Otvorte súbor `app.py` a odstráňte importy z `azure.cognitiveservices.vision.customvision.prediction` a `msrest.authentication`.

1. Pridajte nasledujúci import na začiatok súboru:

    ```python
    import requests
    ```

1. Odstráňte všetok kód po tom, ako je obrázok uložený do súboru, od `image_file.write(image.read())` až po koniec súboru.

1. Pridajte nasledujúci kód na koniec súboru:

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

    Nahraďte `<URL>` URL adresou vášho klasifikátora.

    Tento kód vykonáva REST POST požiadavku na klasifikátor, pričom obrázok posiela ako telo požiadavky. Výsledky sa vrátia vo formáte JSON, ktorý je dekódovaný na výpis pravdepodobností.

1. Spustite svoj kód, pričom kamera bude namierená na nejaké ovocie, alebo na vhodnú sadu obrázkov, alebo ovocie viditeľné na vašej webkamere, ak používate virtuálny IoT hardvér. Výstup uvidíte v konzole:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Tento kód nájdete v priečinku [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) alebo [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Váš program na klasifikáciu kvality ovocia bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.