<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T12:58:08+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "sl"
}
-->
# Pretvorba govora v besedilo - Raspberry Pi

V tem delu lekcije boste napisali kodo za pretvorbo govora iz zajetega zvoka v besedilo z uporabo storitve za prepoznavanje govora.

## Pošlji zvok storitvi za prepoznavanje govora

Zvok lahko pošljete storitvi za prepoznavanje govora prek REST API-ja. Za uporabo storitve morate najprej pridobiti dostopni žeton, nato pa s tem žetonom dostopati do REST API-ja. Ti dostopni žetoni potečejo po 10 minutah, zato mora vaša koda redno pridobivati nove žetone, da zagotovi, da so vedno posodobljeni.

### Naloga - pridobite dostopni žeton

1. Odprite projekt `smart-timer` na svojem Raspberry Pi.

1. Odstranite funkcijo `play_audio`. Ta ni več potrebna, saj ne želite, da pametni časovnik ponavlja, kar ste rekli.

1. Dodajte naslednji uvoz na vrh datoteke `app.py`:

    ```python
    import requests
    ```

1. Dodajte naslednjo kodo nad zanko `while True`, da nastavite nekaj parametrov za storitev za prepoznavanje govora:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Zamenjajte `<key>` z API ključem za vašo storitev za prepoznavanje govora. Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju vira storitve za prepoznavanje govora.

    Zamenjajte `<language>` z oznako jezika, v katerem boste govorili, na primer `en-GB` za angleščino ali `zn-HK` za kantonščino. Seznam podprtih jezikov in njihovih oznak najdete v [dokumentaciji o podpori za jezike in glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Pod to kodo dodajte naslednjo funkcijo za pridobitev dostopnega žetona:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ta funkcija pokliče končno točko za izdajo žetonov, pri čemer API ključ pošlje kot glavo. Klic vrne dostopni žeton, ki ga lahko uporabite za klic storitev za prepoznavanje govora.

1. Pod to funkcijo deklarirajte funkcijo za pretvorbo govora iz zajetega zvoka v besedilo z uporabo REST API-ja:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Znotraj te funkcije nastavite URL REST API-ja in glave:

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

    Ta koda ustvari URL z uporabo lokacije vira storitve za prepoznavanje govora. Nato napolni glave z dostopnim žetonom iz funkcije `get_access_token`, kot tudi s frekvenco vzorčenja, ki je bila uporabljena za zajem zvoka. Na koncu definira nekaj parametrov, ki jih je treba poslati z URL-jem, vključno z jezikom v zvoku.

1. Pod to kodo dodajte naslednjo kodo za klic REST API-ja in pridobitev besedila:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Ta koda pokliče URL in dekodira JSON vrednost, ki jo prejme v odgovoru. Vrednost `RecognitionStatus` v odgovoru označuje, ali je klic uspešno pretvoril govor v besedilo. Če je ta vrednost `Success`, funkcija vrne besedilo, sicer pa vrne prazno niz.

1. Nad zanko `while True:` definirajte funkcijo za obdelavo besedila, ki ga vrne storitev za prepoznavanje govora. Ta funkcija bo za zdaj samo izpisala besedilo v konzolo.

    ```python
    def process_text(text):
        print(text)
    ```

1. Na koncu zamenjajte klic funkcije `play_audio` v zanki `while True` s klicem funkcije `convert_speech_to_text`, pri čemer besedilo posredujete funkciji `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Zaženite kodo. Pritisnite gumb in govorite v mikrofon. Ko končate, sprostite gumb, zvok pa bo pretvorjen v besedilo in izpisan v konzolo.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Preizkusite različne vrste stavkov, vključno s stavki, kjer besede zvenijo enako, a imajo različne pomene. Na primer, če govorite v angleščini, recite 'I want to buy two bananas and an apple too' in opazite, kako bo uporabil pravilne oblike 'to', 'two' in 'too' glede na kontekst besede, ne le njen zvok.

> 💁 To kodo najdete v mapi [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Vaš program za pretvorbo govora v besedilo je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.