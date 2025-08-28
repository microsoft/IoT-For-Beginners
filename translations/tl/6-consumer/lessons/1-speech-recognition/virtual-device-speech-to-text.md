<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T23:24:02+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "tl"
}
-->
# Speech to text - Virtual IoT device

Sa bahaging ito ng aralin, magsusulat ka ng code upang i-convert ang boses na nakuha mula sa iyong mikropono patungo sa text gamit ang speech service.

## I-convert ang boses sa text

Sa Windows, Linux, at macOS, maaaring gamitin ang Python SDK ng speech services upang makinig sa iyong mikropono at i-convert ang anumang boses na madedetect sa text. Patuloy itong makikinig, idedetect ang mga antas ng audio, at ipapadala ang boses para sa conversion sa text kapag bumaba ang antas ng audio, tulad ng sa pagtatapos ng isang bloke ng pagsasalita.

### Gawain - i-convert ang boses sa text

1. Gumawa ng bagong Python app sa iyong computer sa isang folder na tinatawag na `smart-timer` na may isang file na tinatawag na `app.py` at isang Python virtual environment.

1. I-install ang Pip package para sa speech services. Siguraduhing ini-install mo ito mula sa terminal na may naka-activate na virtual environment.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Kung makakakuha ka ng sumusunod na error:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Kailangan mong i-update ang Pip. Gawin ito gamit ang sumusunod na command, pagkatapos ay subukang i-install muli ang package:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Idagdag ang sumusunod na imports sa file na `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Ini-import nito ang ilang klase na ginagamit upang makilala ang boses.

1. Idagdag ang sumusunod na code upang magdeklara ng ilang configuration:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Palitan ang `<key>` ng API key para sa iyong speech service. Palitan ang `<location>` ng lokasyon na ginamit mo nang likhain mo ang speech service resource.

    Palitan ang `<language>` ng pangalan ng locale para sa wika na iyong gagamitin, halimbawa `en-GB` para sa Ingles, o `zn-HK` para sa Cantonese. Maaari mong makita ang listahan ng mga suportadong wika at kanilang mga pangalan ng locale sa [Language and voice support documentation sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ang configuration na ito ay gagamitin upang lumikha ng isang `SpeechConfig` object na gagamitin upang i-configure ang speech services.

1. Idagdag ang sumusunod na code upang lumikha ng isang speech recognizer:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Ang speech recognizer ay tumatakbo sa isang background thread, nakikinig para sa audio at kino-convert ang anumang boses dito sa text. Maaari mong makuha ang text gamit ang isang callback function - isang function na ide-define mo at ipapasa sa recognizer. Tuwing may madedetect na boses, tatawagin ang callback. Idagdag ang sumusunod na code upang magdeklara ng callback, at ipasa ang callback na ito sa recognizer, pati na rin ang pagde-define ng isang function upang iproseso ang text, isinusulat ito sa console:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Ang recognizer ay magsisimulang makinig lamang kapag sinimulan mo ito nang tahasan. Idagdag ang sumusunod na code upang simulan ang recognition. Ito ay tumatakbo sa background, kaya ang iyong application ay kakailanganin din ng isang infinite loop na natutulog upang panatilihing tumatakbo ang application.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Patakbuhin ang app na ito. Magsalita sa iyong mikropono at ang audio na na-convert sa text ay ipapakita sa console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Subukan ang iba't ibang uri ng mga pangungusap, kasama ang mga pangungusap kung saan ang mga salita ay magkatunog ngunit may iba't ibang kahulugan. Halimbawa, kung nagsasalita ka sa Ingles, sabihin ang 'I want to buy two bananas and an apple too', at mapapansin kung paano nito gagamitin ang tamang to, two, at too batay sa konteksto ng salita, hindi lamang sa tunog nito.

> 💁 Maaari mong makita ang code na ito sa [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) na folder.

😀 Tagumpay ang iyong speech to text program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.