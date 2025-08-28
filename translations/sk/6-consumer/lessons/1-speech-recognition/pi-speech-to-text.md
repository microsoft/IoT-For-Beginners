<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T09:16:53+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "sk"
}
-->
# Prevod reči na text - Raspberry Pi

V tejto časti lekcie napíšete kód na prevod reči zo zaznamenaného zvuku na text pomocou služby na rozpoznávanie reči.

## Odoslanie zvuku do služby na rozpoznávanie reči

Zvuk je možné odoslať do služby na rozpoznávanie reči pomocou REST API. Na použitie tejto služby je najprv potrebné požiadať o prístupový token, ktorý následne použijete na prístup k REST API. Tieto prístupové tokeny vypršia po 10 minútach, takže váš kód by ich mal pravidelne obnovovať, aby boli vždy aktuálne.

### Úloha - získanie prístupového tokenu

1. Otvorte projekt `smart-timer` na vašom Raspberry Pi.

1. Odstráňte funkciu `play_audio`. Tá už nie je potrebná, pretože nechcete, aby inteligentný časovač opakoval to, čo ste povedali.

1. Pridajte nasledujúci import na začiatok súboru `app.py`:

    ```python
    import requests
    ```

1. Pridajte nasledujúci kód nad cyklus `while True`, aby ste deklarovali niektoré nastavenia pre službu na rozpoznávanie reči:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Nahraďte `<key>` API kľúčom pre váš zdroj služby na rozpoznávanie reči. Nahraďte `<location>` lokalitou, ktorú ste použili pri vytváraní zdroja služby na rozpoznávanie reči.

    Nahraďte `<language>` názvom lokality pre jazyk, ktorým budete hovoriť, napríklad `en-GB` pre angličtinu alebo `zn-HK` pre kantončinu. Zoznam podporovaných jazykov a ich názvov lokalít nájdete v [dokumentácii o podpore jazykov a hlasov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Pod týmto kódom pridajte nasledujúcu funkciu na získanie prístupového tokenu:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Táto funkcia volá koncový bod na vydávanie tokenov, pričom API kľúč odosiela ako hlavičku. Táto výzva vráti prístupový token, ktorý je možné použiť na volanie služieb na rozpoznávanie reči.

1. Pod týmto kódom deklarujte funkciu na prevod reči zo zaznamenaného zvuku na text pomocou REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Vo vnútri tejto funkcie nastavte URL REST API a hlavičky:

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

    Tento kód vytvára URL pomocou lokality zdroja služby na rozpoznávanie reči. Následne naplní hlavičky prístupovým tokenom z funkcie `get_access_token`, ako aj vzorkovacou frekvenciou použitou na zaznamenanie zvuku. Nakoniec definuje niektoré parametre, ktoré sa odovzdajú spolu s URL a obsahujú jazyk v zvuku.

1. Pod týmto kódom pridajte nasledujúci kód na volanie REST API a získanie textu:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Tento kód volá URL a dekóduje hodnotu JSON, ktorá prichádza v odpovedi. Hodnota `RecognitionStatus` v odpovedi indikuje, či sa podarilo úspešne previesť reč na text. Ak je táto hodnota `Success`, text sa vráti z funkcie, inak sa vráti prázdny reťazec.

1. Nad cyklus `while True:` definujte funkciu na spracovanie textu vráteného zo služby na prevod reči na text. Táto funkcia zatiaľ iba vypíše text do konzoly.

    ```python
    def process_text(text):
        print(text)
    ```

1. Nakoniec nahraďte volanie `play_audio` v cykle `while True` volaním funkcie `convert_speech_to_text`, pričom text odovzdajte funkcii `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Spustite kód. Stlačte tlačidlo a hovorte do mikrofónu. Uvoľnite tlačidlo, keď skončíte, a zvuk sa prevedie na text a vypíše do konzoly.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Vyskúšajte rôzne typy viet, ako aj vety, kde slová znejú rovnako, ale majú rôzne významy. Napríklad, ak hovoríte po anglicky, povedzte „I want to buy two bananas and an apple too“ a všimnite si, ako správne použije „to“, „two“ a „too“ na základe kontextu slova, nielen jeho zvuku.

> 💁 Tento kód nájdete v priečinku [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Váš program na prevod reči na text bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie odporúčame profesionálny preklad vykonaný človekom. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.