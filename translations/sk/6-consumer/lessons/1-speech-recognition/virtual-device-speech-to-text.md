<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T09:13:05+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "sk"
}
-->
# Prevod reči na text - Virtuálne IoT zariadenie

V tejto časti lekcie napíšete kód na prevod reči zachytenej z vášho mikrofónu na text pomocou služby na spracovanie reči.

## Prevod reči na text

Na Windows, Linuxe a macOS môžete použiť Python SDK pre služby na spracovanie reči, ktoré umožňuje počúvať váš mikrofón a prevádzať detekovanú reč na text. SDK bude nepretržite počúvať, detekovať úrovne zvuku a odosielať reč na prevod na text, keď úroveň zvuku klesne, napríklad na konci bloku reči.

### Úloha - prevod reči na text

1. Vytvorte novú Python aplikáciu na vašom počítači v priečinku s názvom `smart-timer` s jediným súborom nazvaným `app.py` a s virtuálnym prostredím Python.

1. Nainštalujte balík Pip pre služby na spracovanie reči. Uistite sa, že inštaláciu vykonávate z terminálu s aktivovaným virtuálnym prostredím.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Ak dostanete nasledujúcu chybu:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Budete musieť aktualizovať Pip. Urobte to pomocou nasledujúceho príkazu a potom skúste balík nainštalovať znova:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Pridajte nasledujúce importy do súboru `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Tieto importy zahŕňajú triedy používané na rozpoznávanie reči.

1. Pridajte nasledujúci kód na deklarovanie konfigurácie:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Nahraďte `<key>` API kľúčom pre vašu službu na spracovanie reči. Nahraďte `<location>` lokalitou, ktorú ste použili pri vytváraní zdroja služby na spracovanie reči.

    Nahraďte `<language>` názvom lokalizácie jazyka, v ktorom budete hovoriť, napríklad `en-GB` pre angličtinu alebo `zn-HK` pre kantončinu. Zoznam podporovaných jazykov a ich názvy lokalizácií nájdete v [dokumentácii o podpore jazykov a hlasov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Táto konfigurácia sa potom použije na vytvorenie objektu `SpeechConfig`, ktorý bude slúžiť na konfiguráciu služieb na spracovanie reči.

1. Pridajte nasledujúci kód na vytvorenie rozpoznávača reči:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Rozpoznávač reči beží na pozadí, počúva zvuk a prevádza akúkoľvek reč na text. Text môžete získať pomocou spätnej volacej funkcie - funkcie, ktorú definujete a odovzdáte rozpoznávaču. Pri každom detekovaní reči sa zavolá spätná funkcia. Pridajte nasledujúci kód na definovanie spätnej funkcie a odovzdajte ju rozpoznávaču, ako aj definovanie funkcie na spracovanie textu, ktorý sa vypíše do konzoly:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Rozpoznávač začne počúvať iba vtedy, keď ho explicitne spustíte. Pridajte nasledujúci kód na spustenie rozpoznávania. Toto beží na pozadí, takže vaša aplikácia bude potrebovať aj nekonečnú slučku, ktorá bude spať, aby aplikácia zostala spustená.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Spustite túto aplikáciu. Hovorte do mikrofónu a zvuk prevedený na text sa zobrazí v konzole.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Vyskúšajte rôzne typy viet, ako aj vety, kde slová znejú rovnako, ale majú rôzne významy. Napríklad, ak hovoríte po anglicky, povedzte „I want to buy two bananas and an apple too“ a všimnite si, ako správne použije „to“, „two“ a „too“ na základe kontextu slova, nielen jeho zvuku.

> 💁 Tento kód nájdete v priečinku [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Váš program na prevod reči na text bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Za autoritatívny zdroj by sa mal považovať pôvodný dokument v jeho pôvodnom jazyku. Pre dôležité informácie odporúčame profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.