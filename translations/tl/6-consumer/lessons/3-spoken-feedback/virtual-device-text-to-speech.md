<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T23:17:59+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "tl"
}
-->
# Text to speech - Virtual IoT device

Sa bahaging ito ng aralin, magsusulat ka ng code upang i-convert ang text sa speech gamit ang speech service.

## I-convert ang text sa speech

Ang speech services SDK na ginamit mo sa nakaraang aralin upang i-convert ang speech sa text ay maaari ring gamitin upang i-convert ang text pabalik sa speech. Kapag humihiling ng speech, kailangan mong tukuyin ang boses na gagamitin dahil maaaring magawa ang speech gamit ang iba't ibang boses.

Ang bawat wika ay may suporta para sa iba't ibang boses, at maaari mong makuha ang listahan ng mga suportadong boses para sa bawat wika mula sa speech services SDK.

### Gawain - i-convert ang text sa speech

1. Buksan ang proyekto na `smart-timer` sa VS Code, at tiyaking naka-load ang virtual environment sa terminal.

1. I-import ang `SpeechSynthesizer` mula sa `azure.cognitiveservices.speech` package sa pamamagitan ng pagdaragdag nito sa kasalukuyang mga import:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Sa itaas ng `say` function, gumawa ng speech configuration na gagamitin sa speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Ginagamit nito ang parehong API key, lokasyon, at wika na ginamit ng recognizer.

1. Sa ibaba nito, idagdag ang sumusunod na code upang makakuha ng boses at itakda ito sa speech config:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Kinukuha nito ang listahan ng lahat ng magagamit na boses, pagkatapos ay hinahanap ang unang boses na tumutugma sa wikang ginagamit.

    > 💁 Maaari mong makuha ang buong listahan ng mga suportadong boses mula sa [Language and voice support documentation sa Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Kung nais mong gumamit ng partikular na boses, maaari mong alisin ang function na ito at i-hard code ang boses gamit ang pangalan ng boses mula sa dokumentasyong ito. Halimbawa:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. I-update ang nilalaman ng `say` function upang makabuo ng SSML para sa tugon:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Sa ibaba nito, itigil ang speech recognition, magsalita ng SSML, pagkatapos ay simulan muli ang recognition:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Ang recognition ay itinitigil habang binibigkas ang text upang maiwasan na ang anunsyo ng pagsisimula ng timer ay ma-detect, maipadala sa LUIS, at posibleng ma-interpret bilang kahilingan upang mag-set ng bagong timer.

    > 💁 Maaari mong subukan ito sa pamamagitan ng pagkomento sa mga linya upang itigil at simulan muli ang recognition. Mag-set ng isang timer, at maaaring mapansin mo na ang anunsyo ay nagse-set ng bagong timer, na nagdudulot ng bagong anunsyo, na nagreresulta sa bagong timer, at tuloy-tuloy na ganito magpakailanman!

1. Patakbuhin ang app, at tiyaking tumatakbo rin ang function app. Mag-set ng ilang timer, at maririnig mo ang isang spoken response na nagsasabing na-set na ang iyong timer, pagkatapos ay isa pang spoken response kapag natapos na ang timer.

> 💁 Maaari mong makita ang code na ito sa [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) folder.

😀 Tagumpay ang iyong timer program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.