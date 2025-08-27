<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T21:14:57+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "sw"
}
-->
# Weka Kipima Muda - Vifaa vya IoT vya Kijumla na Raspberry Pi

Katika sehemu hii ya somo, utaita msimbo wako usio na seva ili kuelewa hotuba, na kuweka kipima muda kwenye kifaa chako cha IoT cha kijumla au Raspberry Pi kulingana na matokeo.

## Weka Kipima Muda

Maandishi yanayorudi kutoka kwa mwito wa hotuba hadi maandishi yanahitaji kutumwa kwa msimbo wako usio na seva ili kuchakatwa na LUIS, na kurudisha idadi ya sekunde za kipima muda. Idadi hii ya sekunde inaweza kutumika kuweka kipima muda.

Vipima muda vinaweza kuwekwa kwa kutumia darasa la Python `threading.Timer`. Darasa hili linachukua muda wa kuchelewa na kazi, na baada ya muda wa kuchelewa, kazi hiyo inatekelezwa.

### Kazi - tuma maandishi kwa kazi ya seva isiyo na seva

1. Fungua mradi wa `smart-timer` katika VS Code, na hakikisha mazingira ya kijumla yamewashwa kwenye terminal ikiwa unatumia kifaa cha IoT cha kijumla.

1. Juu ya kazi ya `process_text`, tangaza kazi inayoitwa `get_timer_time` ili kuita mwisho wa REST uliounda:

    ```python
    def get_timer_time(text):
    ```

1. Ongeza msimbo ufuatao kwenye kazi hii ili kufafanua URL ya kuita:

    ```python
    url = '<URL>'
    ```

    Badilisha `<URL>` na URL ya mwisho wa REST uliyojenga katika somo la mwisho, iwe kwenye kompyuta yako au kwenye wingu.

1. Ongeza msimbo ufuatao ili kuweka maandishi kama mali inayopitishwa kama JSON kwa mwito:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Chini ya hii, pata `seconds` kutoka kwa mzigo wa majibu, ukirudisha 0 ikiwa mwito ulishindwa:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Mwito wa HTTP uliofanikiwa unarudisha msimbo wa hali katika safu ya 200, na msimbo wako usio na seva unarudisha 200 ikiwa maandishi yalichakatwa na kutambuliwa kama nia ya kuweka kipima muda.

### Kazi - weka kipima muda kwenye thread ya usuli

1. Ongeza tamko la kuingiza ifuatayo juu ya faili ili kuingiza maktaba ya threading ya Python:

    ```python
    import threading
    ```

1. Juu ya kazi ya `process_text`, ongeza kazi ya kusema jibu. Kwa sasa hii itaandika tu kwenye console, lakini baadaye katika somo hili itasema maandishi.

    ```python
    def say(text):
        print(text)
    ```

1. Chini ya hii ongeza kazi ambayo itaitwa na kipima muda kutangaza kwamba kipima muda kimekamilika:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Kazi hii inachukua idadi ya dakika na sekunde za kipima muda, na kujenga sentensi ya kusema kwamba kipima muda kimekamilika. Itakagua idadi ya dakika na sekunde, na kujumuisha tu kila kipimo cha muda ikiwa kina namba. Kwa mfano, ikiwa idadi ya dakika ni 0 basi sekunde pekee zinajumuishwa katika ujumbe. Sentensi hii kisha inatumwa kwa kazi ya `say`.

1. Chini ya hii, ongeza kazi ya `create_timer` ifuatayo ili kuunda kipima muda:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Kazi hii inachukua idadi ya jumla ya sekunde za kipima muda ambazo zitatumwa kwenye amri, na kuzibadilisha kuwa dakika na sekunde. Kisha inaunda na kuanza kipima muda kwa kutumia idadi ya jumla ya sekunde, ikipitisha kazi ya `announce_timer` na orodha inayojumuisha dakika na sekunde. Wakati kipima muda kinapomalizika, kitaita kazi ya `announce_timer`, na kupitisha yaliyomo kwenye orodha hii kama vigezo - kwa hivyo kipengee cha kwanza kwenye orodha kinapita kama kigezo cha `minutes`, na cha pili kama kigezo cha `seconds`.

1. Mwisho wa kazi ya `create_timer`, ongeza msimbo wa kujenga ujumbe wa kuzungumza na mtumiaji kutangaza kwamba kipima muda kinaanza:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Tena, hii inajumuisha tu kipimo cha muda ambacho kina thamani. Sentensi hii kisha inatumwa kwa kazi ya `say`.

1. Ongeza yafuatayo mwishoni mwa kazi ya `process_text` ili kupata muda wa kipima muda kutoka kwa maandishi, kisha unda kipima muda:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Kipima muda kinaundwa tu ikiwa idadi ya sekunde ni zaidi ya 0.

1. Endesha programu, na hakikisha programu ya kazi pia inaendesha. Weka vipima muda kadhaa, na matokeo yataonyesha kipima muda kikianzishwa, na kisha yataonyesha wakati kinapomalizika:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) au [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Programu yako ya kipima muda imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asilia katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.