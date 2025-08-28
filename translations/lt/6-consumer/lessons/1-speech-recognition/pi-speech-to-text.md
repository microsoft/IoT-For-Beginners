<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T19:27:31+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "lt"
}
-->
# Kalbos pavertimas tekstu - Raspberry Pi

Šioje pamokos dalyje rašysite kodą, kuris pavers užfiksuotą garsą tekstu, naudodamas kalbos paslaugą.

## Siųskite garsą į kalbos paslaugą

Garsą galima siųsti į kalbos paslaugą naudojant REST API. Norėdami naudotis kalbos paslauga, pirmiausia turite gauti prieigos raktą, o tada naudoti tą raktą REST API pasiekti. Šie prieigos raktai galioja tik 10 minučių, todėl jūsų kodas turėtų reguliariai juos atnaujinti, kad jie visada būtų galiojantys.

### Užduotis - gauti prieigos raktą

1. Atidarykite `smart-timer` projektą savo Pi.

1. Pašalinkite `play_audio` funkciją. Jos nebereikia, nes nenorite, kad išmanusis laikmatis pakartotų tai, ką pasakėte.

1. Pridėkite šį importą failo `app.py` viršuje:

    ```python
    import requests
    ```

1. Pridėkite šį kodą virš `while True` ciklo, kad nustatytumėte kai kuriuos kalbos paslaugos nustatymus:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Pakeiskite `<key>` savo kalbos paslaugos API raktu. Pakeiskite `<location>` vieta, kurią naudojote kurdami kalbos paslaugos išteklių.

    Pakeiskite `<language>` kalbos, kuria kalbėsite, lokalės pavadinimu, pavyzdžiui, `en-GB` anglų kalbai arba `zn-HK` kantoniečių kalbai. Palaikomų kalbų ir jų lokalės pavadinimų sąrašą galite rasti [Microsoft dokumentacijoje apie kalbų ir balsų palaikymą](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Po šiuo kodu pridėkite šią funkciją, kad gautumėte prieigos raktą:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ši funkcija kviečia raktų išdavimo galinį tašką, perduodama API raktą kaip antraštę. Šis kvietimas grąžina prieigos raktą, kurį galima naudoti kalbos paslaugoms kviesti.

1. Po šiuo kodu apibrėžkite funkciją, kuri pavers užfiksuotą garsą tekstu naudodama REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Šios funkcijos viduje nustatykite REST API URL ir antraštes:

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

    Šis kodas sukuria URL, naudodamas kalbos paslaugos ištekliaus vietą. Tada jis užpildo antraštes prieigos raktu iš `get_access_token` funkcijos, taip pat mėginių ėmimo dažniu, naudotu garsui užfiksuoti. Galiausiai jis apibrėžia kai kuriuos parametrus, kurie bus perduoti kartu su URL, nurodant kalbą garse.

1. Po šiuo kodu pridėkite šį kodą, kad iškviestumėte REST API ir gautumėte tekstą:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Šis kodas kviečia URL ir dekoduoja JSON reikšmę, kuri grįžta atsakyme. Atsakyme esanti `RecognitionStatus` reikšmė nurodo, ar kvietimas sėkmingai pavertė kalbą tekstu. Jei reikšmė yra `Success`, tekstas grąžinamas iš funkcijos, kitu atveju grąžinamas tuščias tekstas.

1. Virš `while True:` ciklo apibrėžkite funkciją, kuri apdoros tekstą, grąžintą iš kalbos į tekstą paslaugos. Šiuo metu ši funkcija tiesiog atspausdins tekstą konsolėje.

    ```python
    def process_text(text):
        print(text)
    ```

1. Galiausiai, `while True` cikle pakeiskite `play_audio` kvietimą į `convert_speech_to_text` funkcijos kvietimą, perduodant tekstą į `process_text` funkciją:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Paleiskite kodą. Paspauskite mygtuką ir kalbėkite į mikrofoną. Atleiskite mygtuką, kai baigsite, ir garsas bus paverstas tekstu bei atspausdintas konsolėje.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Išbandykite skirtingus sakinius, taip pat sakinius, kuriuose žodžiai skamba vienodai, bet turi skirtingas reikšmes. Pavyzdžiui, jei kalbate angliškai, pasakykite „I want to buy two bananas and an apple too“ ir pastebėkite, kaip sistema teisingai parenka „to“, „two“ ir „too“ pagal žodžio kontekstą, o ne tik pagal jo garsą.

> 💁 Šį kodą galite rasti [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) aplanke.

😀 Jūsų kalbos pavertimo tekstu programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.