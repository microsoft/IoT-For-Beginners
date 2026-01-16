<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-27T23:01:14+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "tl"
}
-->
# Isalin ang pagsasalita - Raspberry Pi

Sa bahaging ito ng aralin, magsusulat ka ng code upang isalin ang teksto gamit ang serbisyo ng tagasalin.

## I-convert ang teksto sa pagsasalita gamit ang serbisyo ng tagasalin

Ang REST API ng speech service ay hindi sumusuporta sa direktang pagsasalin. Sa halip, maaari mong gamitin ang Translator service upang isalin ang teksto na nabuo ng speech to text service, pati na rin ang teksto ng sinasalitang tugon. Ang serbisyong ito ay may REST API na magagamit mo upang isalin ang teksto.

### Gawain - gamitin ang translator resource upang isalin ang teksto

1. Ang iyong smart timer ay magkakaroon ng 2 wika na nakatakda - ang wika ng server na ginamit upang sanayin ang LUIS (ang parehong wika ay ginagamit din upang bumuo ng mga mensahe para kausapin ang user), at ang wika na sinasalita ng user. I-update ang `language` variable upang maging wika na sinasalita ng user, at magdagdag ng bagong variable na tinatawag na `server_language` para sa wika na ginamit upang sanayin ang LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Palitan ang `<user language>` ng pangalan ng locale para sa wika na iyong gagamitin, halimbawa `fr-FR` para sa French, o `zn-HK` para sa Cantonese.

    Palitan ang `<server language>` ng pangalan ng locale para sa wika na ginamit upang sanayin ang LUIS.

    Maaari mong makita ang listahan ng mga suportadong wika at ang kanilang mga pangalan ng locale sa [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Kung hindi ka nagsasalita ng maraming wika, maaari mong gamitin ang serbisyo tulad ng [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) upang isalin mula sa iyong gustong wika patungo sa wika ng iyong pinili. Ang mga serbisyong ito ay maaari ring magpatugtog ng audio ng isinaling teksto.
    >
    > Halimbawa, kung sinanay mo ang LUIS sa English, ngunit nais mong gamitin ang French bilang wika ng user, maaari mong isalin ang mga pangungusap tulad ng "set a 2 minute and 27 second timer" mula sa English patungo sa French gamit ang Bing Translate, pagkatapos ay gamitin ang **Listen translation** button upang magsalita ng pagsasalin sa iyong mikropono.
    >
    > ![Ang listen translation button sa Bing translate](../../../../../translated_images/tl/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Idagdag ang translator API key sa ibaba ng `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Palitan ang `<key>` ng API key para sa iyong translator service resource.

1. Sa itaas ng `say` function, tukuyin ang isang `translate_text` function na magsasalin ng teksto mula sa server language patungo sa user language:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Ang mga wika na "from" at "to" ay ipinapasa sa function na ito - kailangang i-convert ng iyong app mula sa user language patungo sa server language kapag kinikilala ang pagsasalita, at mula sa server language patungo sa user language kapag nagbibigay ng sinasalitang feedback.

1. Sa loob ng function na ito, tukuyin ang URL at headers para sa REST API call:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Ang URL para sa API na ito ay hindi location-specific, sa halip ang lokasyon ay ipinapasa bilang header. Ang API key ay direktang ginagamit, kaya hindi tulad ng speech service, walang pangangailangan na kumuha ng access token mula sa token issuer API.

1. Sa ibaba nito, tukuyin ang mga parameters at body para sa tawag:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    Ang `params` ay tumutukoy sa mga parameter na ipapasa sa API call, na ipinapasa ang "from" at "to" na mga wika. Ang tawag na ito ay magsasalin ng teksto mula sa "from" language patungo sa "to" language.

    Ang `body` ay naglalaman ng teksto na isasalin. Ito ay isang array, dahil maraming mga bloke ng teksto ang maaaring isalin sa parehong tawag.

1. Gawin ang tawag sa REST API, at kunin ang tugon:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Ang tugon na bumabalik ay isang JSON array, na may isang item na naglalaman ng mga pagsasalin. Ang item na ito ay may array para sa mga pagsasalin ng lahat ng mga item na ipinasa sa body.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Ibalik ang `text` property mula sa unang pagsasalin mula sa unang item sa array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. I-update ang `while True` loop upang isalin ang teksto mula sa tawag sa `convert_speech_to_text` mula sa user language patungo sa server language:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Ang code na ito ay nagpi-print din ng orihinal at isinaling bersyon ng teksto sa console.

1. I-update ang `say` function upang isalin ang teksto na sasabihin mula sa server language patungo sa user language:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Ang code na ito ay nagpi-print din ng orihinal at isinaling bersyon ng teksto sa console.

1. Patakbuhin ang iyong code. Siguraduhin na ang iyong function app ay tumatakbo, at humiling ng timer sa user language, alinman sa pamamagitan ng pagsasalita ng wika na iyon mismo, o gamit ang translation app.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Dahil sa iba't ibang paraan ng pagsasabi ng isang bagay sa iba't ibang wika, maaaring makakuha ka ng mga pagsasalin na bahagyang naiiba sa mga halimbawa na ibinigay mo sa LUIS. Kung ganito ang kaso, magdagdag ng mas maraming halimbawa sa LUIS, muling sanayin, pagkatapos ay muling i-publish ang modelo.

> 💁 Maaari mong makita ang code na ito sa [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) folder.

😀 Tagumpay ang iyong multilingual timer program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na pinagmulan. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.