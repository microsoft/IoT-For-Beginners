<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T21:24:36+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "cs"
}
-->
# Převod řeči na text - Raspberry Pi

V této části lekce napíšete kód, který převede řeč z nahraného zvuku na text pomocí služby pro rozpoznávání řeči.

## Odeslání zvuku do služby pro rozpoznávání řeči

Zvuk lze odeslat do služby pro rozpoznávání řeči pomocí REST API. Abyste mohli tuto službu používat, musíte nejprve požádat o přístupový token a poté tento token použít k přístupu k REST API. Tyto přístupové tokeny vyprší po 10 minutách, takže váš kód by měl tokeny pravidelně obnovovat, aby byly vždy aktuální.

### Úkol - získání přístupového tokenu

1. Otevřete projekt `smart-timer` na svém Raspberry Pi.

1. Odstraňte funkci `play_audio`. Tato funkce již není potřeba, protože nechcete, aby chytrý časovač opakoval, co jste řekli.

1. Přidejte následující import na začátek souboru `app.py`:

    ```python
    import requests
    ```

1. Přidejte následující kód nad smyčku `while True`, abyste deklarovali některá nastavení pro službu rozpoznávání řeči:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Nahraďte `<key>` API klíčem pro váš zdroj služby rozpoznávání řeči. Nahraďte `<location>` umístěním, které jste použili při vytvoření zdroje služby rozpoznávání řeči.

    Nahraďte `<language>` názvem místního nastavení jazyka, kterým budete mluvit, například `en-GB` pro angličtinu nebo `zn-HK` pro kantonštinu. Seznam podporovaných jazyků a jejich názvů místních nastavení najdete v [dokumentaci o podpoře jazyků a hlasů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Pod tento kód přidejte následující funkci pro získání přístupového tokenu:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Tato funkce volá koncový bod pro vydávání tokenů a předává API klíč jako hlavičku. Tato volání vrací přístupový token, který lze použít k volání služeb rozpoznávání řeči.

1. Pod tento kód deklarujte funkci pro převod řeči z nahraného zvuku na text pomocí REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Uvnitř této funkce nastavte URL a hlavičky pro REST API:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Tato část kódu sestavuje URL pomocí umístění zdroje služby rozpoznávání řeči. Poté naplní hlavičky přístupovým tokenem z funkce `get_access_token` a vzorkovací frekvencí použitou pro nahrávání zvuku. Nakonec definuje některé parametry, které budou předány s URL a obsahují jazyk zvuku.

1. Pod tento kód přidejte následující část pro volání REST API a získání textu:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Tato část kódu volá URL a dekóduje hodnotu JSON, která je obsažena v odpovědi. Hodnota `RecognitionStatus` v odpovědi indikuje, zda bylo možné úspěšně převést řeč na text. Pokud je tato hodnota `Success`, funkce vrátí text, jinak vrátí prázdný řetězec.

1. Nad smyčku `while True:` definujte funkci pro zpracování textu vráceného službou pro převod řeči na text. Tato funkce zatím pouze vypíše text do konzole.

    ```python
    def process_text(text):
        print(text)
    ```

1. Nakonec nahraďte volání `play_audio` ve smyčce `while True` voláním funkce `convert_speech_to_text` a předejte text funkci `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Spusťte kód. Stiskněte tlačítko a mluvte do mikrofonu. Uvolněte tlačítko, až budete hotovi, a zvuk bude převeden na text a vytištěn do konzole.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Vyzkoušejte různé typy vět, včetně vět, kde slova znějí stejně, ale mají různé významy. Například pokud mluvíte anglicky, řekněte „I want to buy two bananas and an apple too“ a všimněte si, jak správně použije „to“, „two“ a „too“ na základě kontextu slova, nejen jeho zvuku.

> 💁 Tento kód najdete ve složce [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Váš program pro převod řeči na text byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.