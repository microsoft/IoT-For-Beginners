<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T21:21:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "cs"
}
-->
# Převod řeči na text - Virtuální IoT zařízení

V této části lekce napíšete kód pro převod řeči zachycené z vašeho mikrofonu na text pomocí služby pro rozpoznávání řeči.

## Převod řeči na text

Na Windows, Linuxu a macOS můžete použít Python SDK pro služby rozpoznávání řeči, které poslouchá váš mikrofon a převádí detekovanou řeč na text. SDK poslouchá nepřetržitě, detekuje úrovně zvuku a odesílá řeč k převodu na text, když úroveň zvuku klesne, například na konci bloku řeči.

### Úkol - převod řeči na text

1. Vytvořte novou Python aplikaci na svém počítači ve složce nazvané `smart-timer` s jediným souborem nazvaným `app.py` a Python virtuálním prostředím.

1. Nainstalujte balíček Pip pro služby rozpoznávání řeči. Ujistěte se, že instalaci provádíte z terminálu s aktivovaným virtuálním prostředím.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Pokud obdržíte následující chybu:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Budete muset aktualizovat Pip. Udělejte to pomocí následujícího příkazu a poté zkuste balíček znovu nainstalovat:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Přidejte následující importy do souboru `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Tyto importy zahrnují některé třídy používané k rozpoznávání řeči.

1. Přidejte následující kód pro deklaraci konfigurace:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Nahraďte `<key>` API klíčem pro vaši službu rozpoznávání řeči. Nahraďte `<location>` místem, které jste použili při vytvoření zdroje služby rozpoznávání řeči.

    Nahraďte `<language>` názvem místního nastavení jazyka, ve kterém budete mluvit, například `en-GB` pro angličtinu nebo `zn-HK` pro kantonštinu. Seznam podporovaných jazyků a jejich názvů místních nastavení najdete v [dokumentaci o podpoře jazyků a hlasů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Tato konfigurace se poté použije k vytvoření objektu `SpeechConfig`, který bude použit k nastavení služeb rozpoznávání řeči.

1. Přidejte následující kód pro vytvoření rozpoznávače řeči:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Rozpoznávač řeči běží na pozadí, poslouchá zvuk a převádí jakoukoli řeč v něm na text. Text můžete získat pomocí funkce zpětného volání - funkce, kterou definujete a předáte rozpoznávači. Pokaždé, když je detekována řeč, je volána zpětná funkce. Přidejte následující kód pro definici zpětné funkce a předání této funkce rozpoznávači, stejně jako definici funkce pro zpracování textu, která jej zapíše do konzole:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Rozpoznávač začne poslouchat pouze tehdy, když jej explicitně spustíte. Přidejte následující kód pro spuštění rozpoznávání. To běží na pozadí, takže vaše aplikace bude také potřebovat nekonečnou smyčku, která bude spát, aby aplikace zůstala spuštěná.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Spusťte tuto aplikaci. Mluvte do mikrofonu a zvuk převedený na text bude vypsán do konzole.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Vyzkoušejte různé typy vět, spolu s větami, kde slova znějí stejně, ale mají různé významy. Například pokud mluvíte anglicky, řekněte 'I want to buy two bananas and an apple too' a všimněte si, jak bude použito správné to, two a too na základě kontextu slova, nejen jeho zvuku.

> 💁 Tento kód najdete ve složce [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Váš program pro převod řeči na text byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.