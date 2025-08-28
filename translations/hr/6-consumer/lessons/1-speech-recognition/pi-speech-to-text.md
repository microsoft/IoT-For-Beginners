<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T12:57:48+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "hr"
}
-->
# Pretvaranje govora u tekst - Raspberry Pi

U ovom dijelu lekcije napisat ćete kod za pretvaranje govora iz snimljenog zvuka u tekst koristeći uslugu za govor.

## Slanje zvuka usluzi za govor

Zvuk se može poslati usluzi za govor koristeći REST API. Da biste koristili uslugu za govor, prvo morate zatražiti pristupni token, a zatim koristiti taj token za pristup REST API-ju. Ovi pristupni tokeni istječu nakon 10 minuta, pa vaš kod treba redovito zatražiti nove kako bi uvijek bili ažurirani.

### Zadatak - dobivanje pristupnog tokena

1. Otvorite projekt `smart-timer` na svom Raspberry Pi uređaju.

1. Uklonite funkciju `play_audio`. Više nije potrebna jer ne želite da pametni mjerač vremena ponavlja ono što ste rekli.

1. Dodajte sljedeći uvoz na vrh datoteke `app.py`:

    ```python
    import requests
    ```

1. Dodajte sljedeći kod iznad petlje `while True` kako biste deklarirali neke postavke za uslugu za govor:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Zamijenite `<key>` API ključem za vaš resurs usluge za govor. Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja resursa usluge za govor.

    Zamijenite `<language>` nazivom lokaliteta jezika kojim ćete govoriti, na primjer `en-GB` za engleski ili `zn-HK` za kantonski. Popis podržanih jezika i njihovih naziva lokaliteta možete pronaći u [dokumentaciji o podršci za jezike i glasove na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Ispod ovoga dodajte sljedeću funkciju za dobivanje pristupnog tokena:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ova funkcija poziva endpoint za izdavanje tokena, prosljeđujući API ključ kao zaglavlje. Ovaj poziv vraća pristupni token koji se može koristiti za pozivanje usluga za govor.

1. Ispod ovoga deklarirajte funkciju za pretvaranje govora iz snimljenog zvuka u tekst koristeći REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Unutar ove funkcije postavite URL REST API-ja i zaglavlja:

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

    Ovaj kod gradi URL koristeći lokaciju resursa usluge za govor. Zatim popunjava zaglavlja pristupnim tokenom iz funkcije `get_access_token`, kao i uzorkovanjem koje se koristi za snimanje zvuka. Na kraju definira neke parametre koji se prosljeđuju s URL-om i sadrže jezik u zvuku.

1. Ispod ovoga dodajte sljedeći kod za pozivanje REST API-ja i dobivanje teksta:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Ovaj kod poziva URL i dekodira JSON vrijednost koja dolazi u odgovoru. Vrijednost `RecognitionStatus` u odgovoru pokazuje je li poziv uspješno pretvorio govor u tekst, a ako je `Success`, tekst se vraća iz funkcije, inače se vraća prazan string.

1. Iznad petlje `while True:` definirajte funkciju za obradu teksta koji vraća usluga za pretvaranje govora u tekst. Ova funkcija će za sada samo ispisivati tekst na konzolu.

    ```python
    def process_text(text):
        print(text)
    ```

1. Na kraju zamijenite poziv funkcije `play_audio` u petlji `while True` pozivom funkcije `convert_speech_to_text`, prosljeđujući tekst funkciji `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Pokrenite kod. Pritisnite gumb i govorite u mikrofon. Otpustite gumb kada završite, a zvuk će se pretvoriti u tekst i ispisati na konzolu.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Isprobajte različite vrste rečenica, kao i rečenice u kojima riječi zvuče isto, ali imaju različita značenja. Na primjer, ako govorite na engleskom, recite 'I want to buy two bananas and an apple too' i primijetite kako će koristiti ispravne riječi to, two i too na temelju konteksta, a ne samo zvuka.

> 💁 Ovaj kod možete pronaći u mapi [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Vaš program za pretvaranje govora u tekst bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.