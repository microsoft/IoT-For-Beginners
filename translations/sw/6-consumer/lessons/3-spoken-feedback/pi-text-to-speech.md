<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T21:12:49+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "sw"
}
-->
# Maandishi hadi Sauti - Raspberry Pi

Katika sehemu hii ya somo, utaandika msimbo wa kubadilisha maandishi kuwa sauti kwa kutumia huduma ya sauti.

## Badilisha maandishi kuwa sauti kwa kutumia huduma ya sauti

Maandishi yanaweza kutumwa kwa huduma ya sauti kupitia REST API ili kupata sauti kama faili ya sauti ambayo inaweza kuchezwa kwenye kifaa chako cha IoT. Unapoomba sauti, unahitaji kutoa sauti ya kutumia kwani sauti inaweza kuzalishwa kwa kutumia sauti mbalimbali.

Kila lugha inaunga mkono sauti mbalimbali, na unaweza kufanya ombi la REST dhidi ya huduma ya sauti ili kupata orodha ya sauti zinazoungwa mkono kwa kila lugha.

### Kazi - pata sauti

1. Fungua mradi wa `smart-timer` kwenye VS Code.

1. Ongeza msimbo ufuatao juu ya kazi ya `say` ili kuomba orodha ya sauti kwa lugha:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Msimbo huu hufafanua kazi inayoitwa `get_voice` inayotumia huduma ya sauti kupata orodha ya sauti. Kisha inatafuta sauti ya kwanza inayolingana na lugha inayotumika.

    Kazi hii inaitwa ili kuhifadhi sauti ya kwanza, na jina la sauti linaonyeshwa kwenye console. Sauti hii inaweza kuombwa mara moja na thamani hiyo kutumika kwa kila ombi la kubadilisha maandishi kuwa sauti.

    > 💁 Unaweza kupata orodha kamili ya sauti zinazoungwa mkono kutoka kwa [Nyaraka za msaada wa lugha na sauti kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ikiwa unataka kutumia sauti maalum, basi unaweza kuondoa kazi hii na kuweka jina la sauti moja kwa moja kutoka kwenye nyaraka hizi. Kwa mfano:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Kazi - badilisha maandishi kuwa sauti

1. Chini ya hii, fafanua thamani ya kudumu kwa muundo wa sauti utakaopatikana kutoka kwa huduma za sauti. Unapoomba sauti, unaweza kuifanya katika miundo mbalimbali.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Muundo unaoweza kutumia unategemea vifaa vyako. Ikiwa unapata makosa ya `Invalid sample rate` unapoendesha sauti, badilisha hii kwa thamani nyingine. Unaweza kupata orodha ya thamani zinazoungwa mkono kwenye [Nyaraka za REST API za maandishi hadi sauti kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Utahitaji kutumia sauti ya muundo wa `riff`, na thamani za kujaribu ni `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` na `riff-48khz-16bit-mono-pcm`.

1. Chini ya hii, tangaza kazi inayoitwa `get_speech` ambayo itabadilisha maandishi kuwa sauti kwa kutumia REST API ya huduma ya sauti:

    ```python
    def get_speech(text):
    ```

1. Katika kazi ya `get_speech`, fafanua URL ya kupiga simu na vichwa vya habari vya kupitisha:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Hii inaweka vichwa vya habari kutumia tokeni ya ufikiaji iliyotengenezwa, kuweka maudhui kuwa SSML na kufafanua muundo wa sauti unaohitajika.

1. Chini ya hii, fafanua SSML ya kutuma kwa REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    SSML hii inaweka lugha na sauti ya kutumia, pamoja na maandishi ya kubadilisha.

1. Hatimaye, ongeza msimbo katika kazi hii kufanya ombi la REST na kurudisha data ya sauti ya binary:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Kazi - cheza sauti

1. Chini ya kazi ya `get_speech`, fafanua kazi mpya ya kucheza sauti iliyorejeshwa na simu ya REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech` inayopitishwa kwa kazi hii itakuwa data ya sauti ya binary iliyorejeshwa kutoka kwa REST API. Tumia msimbo ufuatao kufungua hii kama faili ya mawimbi na kuipitisha kwa PyAudio ili kucheza sauti:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Msimbo huu hutumia mkondo wa PyAudio, sawa na kunasa sauti. Tofauti hapa ni kwamba mkondo umewekwa kama mkondo wa pato, na data inasomwa kutoka kwa data ya sauti na kusukumwa kwa mkondo.

    Badala ya kuweka maelezo ya mkondo kama kiwango cha sampuli, inasomwa kutoka kwa data ya sauti.

1. Badilisha yaliyomo ya kazi ya `say` na yafuatayo:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Msimbo huu hubadilisha maandishi kuwa sauti kama data ya sauti ya binary, na kucheza sauti.

1. Endesha programu, na hakikisha programu ya kazi pia inaendesha. Weka baadhi ya vipima muda, na utasikia majibu ya sauti yakisema kwamba kipima muda chako kimewekwa, kisha jibu lingine la sauti linapokamilika.

    Ikiwa unapata makosa ya `Invalid sample rate`, badilisha `playback_format` kama ilivyoelezwa hapo juu.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Programu yako ya kipima muda imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.