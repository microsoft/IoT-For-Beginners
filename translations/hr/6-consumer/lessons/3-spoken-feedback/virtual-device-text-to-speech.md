<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T12:39:44+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "hr"
}
-->
# Pretvaranje teksta u govor - Virtualni IoT uređaj

U ovom dijelu lekcije napisat ćete kod za pretvaranje teksta u govor koristeći uslugu za govor.

## Pretvaranje teksta u govor

SDK za usluge govora koji ste koristili u prethodnoj lekciji za pretvaranje govora u tekst može se koristiti i za pretvaranje teksta natrag u govor. Prilikom zahtjeva za govorom, potrebno je odabrati glas koji će se koristiti, jer govor može biti generiran koristeći razne glasove.

Svaki jezik podržava niz različitih glasova, a popis podržanih glasova za svaki jezik možete dobiti putem SDK-a za usluge govora.

### Zadatak - pretvaranje teksta u govor

1. Otvorite projekt `smart-timer` u VS Code-u i provjerite je li virtualno okruženje učitano u terminalu.

1. Uvezite `SpeechSynthesizer` iz paketa `azure.cognitiveservices.speech` dodajući ga postojećim uvozima:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Iznad funkcije `say`, kreirajte konfiguraciju za govor koja će se koristiti s govorom sintetizatora:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Ovo koristi isti API ključ, lokaciju i jezik koji je koristio prepoznavač.

1. Ispod toga dodajte sljedeći kod za dohvaćanje glasa i postavljanje na konfiguraciju za govor:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Ovaj kod dohvaća popis svih dostupnih glasova, a zatim pronalazi prvi glas koji odgovara jeziku koji se koristi.

    > 💁 Cijeli popis podržanih glasova možete pronaći u [dokumentaciji o podršci za jezike i glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ako želite koristiti određeni glas, možete ukloniti ovu funkciju i ručno unijeti ime glasa iz te dokumentacije. Na primjer:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Ažurirajte sadržaj funkcije `say` kako biste generirali SSML za odgovor:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Ispod toga zaustavite prepoznavanje govora, izgovorite SSML, a zatim ponovno pokrenite prepoznavanje:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Prepoznavanje se zaustavlja dok se tekst izgovara kako bi se izbjeglo da najava pokretanja timera bude prepoznata, poslana LUIS-u i potencijalno interpretirana kao zahtjev za postavljanje novog timera.

    > 💁 Ovo možete testirati tako da komentirate linije za zaustavljanje i ponovno pokretanje prepoznavanja. Postavite jedan timer i možda ćete primijetiti da najava postavlja novi timer, što uzrokuje novu najavu, koja postavlja novi timer, i tako dalje u beskonačnost!

1. Pokrenite aplikaciju i provjerite je li funkcijska aplikacija također pokrenuta. Postavite nekoliko timera i čut ćete glasovni odgovor koji kaže da je vaš timer postavljen, a zatim još jedan glasovni odgovor kada timer završi.

> 💁 Ovaj kod možete pronaći u mapi [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Vaš program za timere bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.