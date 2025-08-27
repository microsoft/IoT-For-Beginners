<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:51:50+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "cs"
}
-->
# Klasifikace obrázku pomocí klasifikátoru obrázků na bázi IoT Edge - Virtuální IoT hardware a Raspberry Pi

V této části lekce použijete klasifikátor obrázků běžící na zařízení IoT Edge.

## Použití klasifikátoru IoT Edge

Zařízení IoT může být přesměrováno k použití klasifikátoru obrázků IoT Edge. URL pro klasifikátor obrázků je `http://<IP adresa nebo název>/image`, kde `<IP adresa nebo název>` nahradíte IP adresou nebo názvem hostitele počítače, na kterém běží IoT Edge.

Knihovna Pythonu pro Custom Vision funguje pouze s modely hostovanými v cloudu, nikoli s modely hostovanými na IoT Edge. To znamená, že budete muset použít REST API k volání klasifikátoru.

### Úkol - použití klasifikátoru IoT Edge

1. Otevřete projekt `fruit-quality-detector` v aplikaci VS Code, pokud již není otevřen. Pokud používáte virtuální IoT zařízení, ujistěte se, že je aktivováno virtuální prostředí.

1. Otevřete soubor `app.py` a odstraňte příkazy importu z `azure.cognitiveservices.vision.customvision.prediction` a `msrest.authentication`.

1. Přidejte následující import na začátek souboru:

    ```python
    import requests
    ```

1. Odstraňte veškerý kód po uložení obrázku do souboru, od `image_file.write(image.read())` až do konce souboru.

1. Přidejte následující kód na konec souboru:

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

    Nahraďte `<URL>` URL adresou vašeho klasifikátoru.

    Tento kód provádí REST POST požadavek na klasifikátor, přičemž obrázek je odeslán jako tělo požadavku. Výsledky se vrátí ve formátu JSON, který je dekódován a zobrazí pravděpodobnosti.

1. Spusťte svůj kód, přičemž kameru namiřte na nějaké ovoce, vhodnou sadu obrázků nebo ovoce viditelné na vaší webkameře, pokud používáte virtuální IoT hardware. Výstup uvidíte v konzoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Tento kód najdete ve složce [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) nebo [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Váš program pro klasifikaci kvality ovoce byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.