<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T17:53:09+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "hi"
}
-->
# स्पीच टू टेक्स्ट - वर्चुअल IoT डिवाइस

इस पाठ के इस भाग में, आप माइक्रोफोन से प्राप्त स्पीच को टेक्स्ट में बदलने के लिए स्पीच सर्विस का उपयोग करके कोड लिखेंगे।

## स्पीच को टेक्स्ट में बदलें

Windows, Linux, और macOS पर, स्पीच सर्विसेज का Python SDK आपके माइक्रोफोन को सुनने और पहचानी गई स्पीच को टेक्स्ट में बदलने के लिए उपयोग किया जा सकता है। यह लगातार सुनता है, ऑडियो स्तरों का पता लगाता है और जब ऑडियो स्तर गिरता है, जैसे कि स्पीच के एक ब्लॉक के अंत में, तो स्पीच को टेक्स्ट में बदलने के लिए भेजता है।

### कार्य - स्पीच को टेक्स्ट में बदलें

1. अपने कंप्यूटर पर `smart-timer` नामक एक फ़ोल्डर में एक नया Python ऐप बनाएं, जिसमें एक फ़ाइल `app.py` और एक Python वर्चुअल एनवायरनमेंट हो।

1. स्पीच सर्विसेज के लिए Pip पैकेज इंस्टॉल करें। सुनिश्चित करें कि आप इसे वर्चुअल एनवायरनमेंट सक्रिय किए गए टर्मिनल से इंस्टॉल कर रहे हैं।

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ यदि आपको निम्नलिखित त्रुटि मिलती है:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > तो आपको Pip को अपडेट करना होगा। इसे निम्नलिखित कमांड से करें, फिर पैकेज को फिर से इंस्टॉल करने का प्रयास करें:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` फ़ाइल में निम्नलिखित इम्पोर्ट्स जोड़ें:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    यह कुछ क्लासेस को इम्पोर्ट करता है जो स्पीच को पहचानने के लिए उपयोग की जाती हैं।

1. कुछ कॉन्फ़िगरेशन घोषित करने के लिए निम्नलिखित कोड जोड़ें:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` को अपनी स्पीच सर्विस के API key से बदलें। `<location>` को उस स्थान से बदलें जिसे आपने स्पीच सर्विस संसाधन बनाते समय उपयोग किया था।

    `<language>` को उस भाषा के लोकेल नाम से बदलें जिसमें आप बोलने वाले हैं, जैसे कि अंग्रेजी के लिए `en-GB`, या कैंटोनीज़ के लिए `zn-HK`। समर्थित भाषाओं और उनके लोकेल नामों की सूची [Microsoft Docs पर भाषा और आवाज़ समर्थन दस्तावेज़](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) में पाई जा सकती है।

    यह कॉन्फ़िगरेशन एक `SpeechConfig` ऑब्जेक्ट बनाने के लिए उपयोग किया जाता है, जो स्पीच सर्विसेज को कॉन्फ़िगर करेगा।

1. एक स्पीच रिकग्नाइज़र बनाने के लिए निम्नलिखित कोड जोड़ें:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. स्पीच रिकग्नाइज़र एक बैकग्राउंड थ्रेड पर चलता है, ऑडियो को सुनता है और उसमें मौजूद स्पीच को टेक्स्ट में बदलता है। आप टेक्स्ट को एक कॉलबैक फ़ंक्शन का उपयोग करके प्राप्त कर सकते हैं - एक फ़ंक्शन जिसे आप परिभाषित करते हैं और रिकग्नाइज़र को पास करते हैं। हर बार जब स्पीच का पता चलता है, तो कॉलबैक को कॉल किया जाता है। निम्नलिखित कोड जोड़ें ताकि एक कॉलबैक परिभाषित किया जा सके, और इस कॉलबैक को रिकग्नाइज़र को पास किया जा सके, साथ ही टेक्स्ट को प्रोसेस करने के लिए एक फ़ंक्शन परिभाषित करें, जो इसे कंसोल में लिखेगा:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. रिकग्नाइज़र केवल तब सुनना शुरू करता है जब आप इसे स्पष्ट रूप से शुरू करते हैं। रिकग्निशन शुरू करने के लिए निम्नलिखित कोड जोड़ें। यह बैकग्राउंड में चलता है, इसलिए आपके ऐप्लिकेशन को भी एक अनंत लूप की आवश्यकता होगी जो ऐप्लिकेशन को चालू रखने के लिए सोता रहे।

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. इस ऐप को चलाएं। अपने माइक्रोफोन में बोलें और ऑडियो को टेक्स्ट में बदलकर कंसोल में आउटपुट किया जाएगा।

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    विभिन्न प्रकार के वाक्यों का प्रयास करें, साथ ही ऐसे वाक्य जिनमें शब्द समान लगते हैं लेकिन उनके अर्थ अलग होते हैं। उदाहरण के लिए, यदि आप अंग्रेजी में बोल रहे हैं, तो कहें 'I want to buy two bananas and an apple too', और ध्यान दें कि यह सही 'to', 'two' और 'too' का उपयोग करेगा, शब्द के संदर्भ के आधार पर, केवल उसकी ध्वनि पर नहीं।

> 💁 आप इस कोड को [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) फ़ोल्डर में पा सकते हैं।

😀 आपका स्पीच टू टेक्स्ट प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता के लिए प्रयासरत हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।