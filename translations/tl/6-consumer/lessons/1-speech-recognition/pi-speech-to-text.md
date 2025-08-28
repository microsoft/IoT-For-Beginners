<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T23:31:36+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "tl"
}
-->
# Speech to text - Raspberry Pi

Sa bahaging ito ng aralin, magsusulat ka ng code upang i-convert ang pagsasalita sa na-capture na audio patungo sa text gamit ang speech service.

## Ipadala ang audio sa speech service

Ang audio ay maaaring ipadala sa speech service gamit ang REST API. Upang magamit ang speech service, kailangan mo munang humiling ng access token, pagkatapos ay gamitin ang token na iyon upang ma-access ang REST API. Ang mga access token ay nag-e-expire pagkatapos ng 10 minuto, kaya ang iyong code ay dapat regular na humiling ng mga ito upang matiyak na palaging napapanahon.

### Gawain - kumuha ng access token

1. Buksan ang proyekto na `smart-timer` sa iyong Pi.

1. Tanggalin ang function na `play_audio`. Hindi na ito kailangan dahil ayaw mong ulitin ng smart timer ang sinabi mo.

1. Idagdag ang sumusunod na import sa itaas ng file na `app.py`:

    ```python
    import requests
    ```

1. Idagdag ang sumusunod na code sa itaas ng `while True` loop upang ideklara ang ilang mga setting para sa speech service:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Palitan ang `<key>` ng API key para sa iyong speech service resource. Palitan ang `<location>` ng lokasyon na ginamit mo nang nilikha ang speech service resource.

    Palitan ang `<language>` ng pangalan ng locale para sa wika na iyong gagamitin, halimbawa `en-GB` para sa English, o `zn-HK` para sa Cantonese. Makikita mo ang listahan ng mga suportadong wika at kanilang mga pangalan ng locale sa [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Sa ibaba nito, idagdag ang sumusunod na function upang makakuha ng access token:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Tumatawag ito sa token issuing endpoint, na ipinapasa ang API key bilang header. Ang tawag na ito ay nagbabalik ng access token na maaaring gamitin upang tawagan ang speech services.

1. Sa ibaba nito, ideklara ang isang function upang i-convert ang pagsasalita sa na-capture na audio patungo sa text gamit ang REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Sa loob ng function na ito, i-set up ang REST API URL at headers:

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

    Binubuo nito ang URL gamit ang lokasyon ng speech services resource. Pagkatapos ay pinupunan ang headers gamit ang access token mula sa `get_access_token` function, pati na rin ang sample rate na ginamit upang i-capture ang audio. Sa huli, tinutukoy nito ang ilang mga parameter na ipapasa kasama ng URL na naglalaman ng wika sa audio.

1. Sa ibaba nito, idagdag ang sumusunod na code upang tawagan ang REST API at makuha ang text:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Tumatawag ito sa URL at dine-decode ang JSON value na dumating sa response. Ang `RecognitionStatus` value sa response ay nagpapahiwatig kung ang tawag ay matagumpay na nakapag-extract ng pagsasalita patungo sa text, at kung ito ay `Success`, ang text ay ibinabalik mula sa function, kung hindi, isang walang laman na string ang ibinabalik.

1. Sa itaas ng `while True:` loop, magdeklara ng isang function upang iproseso ang text na ibinalik mula sa speech to text service. Ang function na ito ay magpi-print lamang ng text sa console sa ngayon.

    ```python
    def process_text(text):
        print(text)
    ```

1. Sa wakas, palitan ang tawag sa `play_audio` sa loob ng `while True` loop ng tawag sa `convert_speech_to_text` function, na ipinapasa ang text sa `process_text` function:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Patakbuhin ang code. Pindutin ang button at magsalita sa mikropono. Bitawan ang button kapag tapos ka na, at ang audio ay iko-convert sa text at ipi-print sa console.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Subukan ang iba't ibang uri ng mga pangungusap, pati na rin ang mga pangungusap kung saan ang mga salita ay magkatunog ngunit may iba't ibang kahulugan. Halimbawa, kung nagsasalita ka sa English, sabihin ang 'I want to buy two bananas and an apple too', at mapapansin kung paano nito ginagamit ang tamang to, two, at too batay sa konteksto ng salita, hindi lamang sa tunog nito.

> 💁 Makikita mo ang code na ito sa [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) folder.

😀 Tagumpay ang iyong speech to text program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.