<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T12:54:47+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "hr"
}
-->
# Pretvaranje govora u tekst - Virtualni IoT uređaj

U ovom dijelu lekcije napisat ćete kod za pretvaranje govora snimljenog putem vašeg mikrofona u tekst koristeći uslugu za govor.

## Pretvaranje govora u tekst

Na Windowsu, Linuxu i macOS-u, Python SDK za usluge govora može se koristiti za slušanje vašeg mikrofona i pretvaranje govora koji se detektira u tekst. SDK kontinuirano sluša, detektira razine zvuka i šalje govor na pretvaranje u tekst kada razina zvuka opadne, primjerice na kraju bloka govora.

### Zadatak - pretvaranje govora u tekst

1. Kreirajte novu Python aplikaciju na svom računalu u mapi nazvanoj `smart-timer` s jednim datotekama nazvanim `app.py` i Python virtualnim okruženjem.

1. Instalirajte Pip paket za usluge govora. Pobrinite se da ovo instalirate iz terminala s aktiviranim virtualnim okruženjem.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Ako dobijete sljedeću grešku:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Morat ćete ažurirati Pip. Učinite to sljedećom naredbom, a zatim pokušajte ponovno instalirati paket.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Dodajte sljedeće uvoze u datoteku `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Ovo uvozi neke klase koje se koriste za prepoznavanje govora.

1. Dodajte sljedeći kod za deklariranje konfiguracije:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Zamijenite `<key>` API ključem za vašu uslugu govora. Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja resursa za uslugu govora.

    Zamijenite `<language>` nazivom lokaliteta jezika kojim ćete govoriti, na primjer `en-GB` za engleski ili `zn-HK` za kantonski. Popis podržanih jezika i njihovih naziva lokaliteta možete pronaći u [dokumentaciji o podršci za jezike i glasove na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ova konfiguracija se zatim koristi za kreiranje objekta `SpeechConfig` koji će se koristiti za konfiguriranje usluga govora.

1. Dodajte sljedeći kod za kreiranje prepoznavača govora:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Prepoznavač govora radi na pozadinskoj niti, sluša zvuk i pretvara svaki govor u tekst. Tekst možete dobiti pomoću funkcije povratnog poziva - funkcije koju definirate i prosljeđujete prepoznavaču. Svaki put kad se detektira govor, poziva se povratni poziv. Dodajte sljedeći kod za definiranje povratnog poziva i proslijedite ovaj povratni poziv prepoznavaču, kao i definiranje funkcije za obradu teksta, koja ga ispisuje na konzolu:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Prepoznavač počinje slušati samo kada ga eksplicitno pokrenete. Dodajte sljedeći kod za pokretanje prepoznavanja. Ovo se izvodi u pozadini, pa vaša aplikacija također treba beskonačnu petlju koja spava kako bi aplikacija ostala aktivna.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Pokrenite ovu aplikaciju. Govorite u mikrofon, a audio pretvoren u tekst bit će ispisan na konzolu.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Isprobajte različite vrste rečenica, zajedno s rečenicama u kojima riječi zvuče isto, ali imaju različita značenja. Na primjer, ako govorite na engleskom, recite 'I want to buy two bananas and an apple too' i primijetite kako će koristiti ispravne to, two i too na temelju konteksta riječi, a ne samo njenog zvuka.

> 💁 Ovaj kod možete pronaći u mapi [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Vaš program za pretvaranje govora u tekst bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.