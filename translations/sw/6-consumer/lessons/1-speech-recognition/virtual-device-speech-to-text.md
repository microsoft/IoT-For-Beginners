<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T21:21:01+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "sw"
}
-->
# Hotuba kwa maandishi - Kifaa cha IoT cha Kijanja

Katika sehemu hii ya somo, utaandika msimbo wa kubadilisha hotuba inayorekodiwa kutoka kwa kipaza sauti chako kuwa maandishi kwa kutumia huduma ya hotuba.

## Badilisha hotuba kuwa maandishi

Kwenye Windows, Linux, na macOS, SDK ya Python ya huduma za hotuba inaweza kutumika kusikiliza kipaza sauti chako na kubadilisha hotuba yoyote inayogunduliwa kuwa maandishi. Itasikiliza mfululizo, ikigundua viwango vya sauti na kutuma hotuba kwa ajili ya kubadilishwa kuwa maandishi wakati kiwango cha sauti kinaposhuka, kama vile mwishoni mwa kipande cha hotuba.

### Kazi - badilisha hotuba kuwa maandishi

1. Unda programu mpya ya Python kwenye kompyuta yako ndani ya folda inayoitwa `smart-timer` yenye faili moja inayoitwa `app.py` na mazingira halisi ya Python.

1. Sakinisha kifurushi cha Pip kwa huduma za hotuba. Hakikisha unafanya usakinishaji huu kutoka kwa terminal yenye mazingira halisi yakiwa yamewashwa.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Ikiwa utapata kosa lifuatalo:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Utahitaji kusasisha Pip. Fanya hivi kwa kutumia amri ifuatayo, kisha jaribu kusakinisha kifurushi tena:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Ongeza uingizaji ufuatao kwenye faili ya `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Hii inaingiza madarasa fulani yanayotumika kutambua hotuba.

1. Ongeza msimbo ufuatao ili kutangaza mipangilio fulani:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Badilisha `<key>` na ufunguo wa API wa huduma yako ya hotuba. Badilisha `<location>` na eneo ulilotumia ulipounda rasilimali ya huduma ya hotuba.

    Badilisha `<language>` na jina la eneo la lugha utakayokuwa ukizungumza, kwa mfano `en-GB` kwa Kiingereza, au `zn-HK` kwa Kantonese. Unaweza kupata orodha ya lugha zinazoungwa mkono na majina yao ya eneo katika [Nyaraka za msaada wa lugha na sauti kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Mipangilio hii kisha hutumika kuunda kitu cha `SpeechConfig` ambacho kitakuwa kinatumika kusanidi huduma za hotuba.

1. Ongeza msimbo ufuatao ili kuunda kitambuzi cha hotuba:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Kitambuzi cha hotuba kinafanya kazi kwenye uzi wa nyuma, kikisikiliza sauti na kubadilisha hotuba yoyote ndani yake kuwa maandishi. Unaweza kupata maandishi kwa kutumia kazi ya callback - kazi unayofafanua na kupitisha kwa kitambuzi. Kila wakati hotuba inapogunduliwa, callback inaitwa. Ongeza msimbo ufuatao ili kufafanua callback, na kupitisha callback hii kwa kitambuzi, pamoja na kufafanua kazi ya kushughulikia maandishi, kuyaandika kwenye console:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Kitambuzi huanza kusikiliza tu unapokianzisha waziwazi. Ongeza msimbo ufuatao ili kuanzisha utambuzi. Hii inafanya kazi kwenye uzi wa nyuma, kwa hivyo programu yako pia itahitaji kitanzi kisicho na mwisho kinacholala ili kuweka programu ikiendelea.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Endesha programu hii. Zungumza kwenye kipaza sauti chako na sauti itakayobadilishwa kuwa maandishi itaonyeshwa kwenye console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Jaribu aina tofauti za sentensi, pamoja na sentensi ambapo maneno yana sauti sawa lakini yana maana tofauti. Kwa mfano, ikiwa unazungumza kwa Kiingereza, sema 'I want to buy two bananas and an apple too', na uone jinsi itakavyotumia to, two, na too kwa usahihi kulingana na muktadha wa neno, siyo tu sauti yake.

> 💁 Unaweza kupata msimbo huu katika folda ya [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Programu yako ya kubadilisha hotuba kuwa maandishi imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.