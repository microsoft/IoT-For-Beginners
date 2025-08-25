<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T17:57:59+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "hi"
}
-->
# स्पीच टू टेक्स्ट - रास्पबेरी पाई

इस पाठ के इस भाग में, आप ऐसा कोड लिखेंगे जो कैप्चर किए गए ऑडियो में स्पीच को टेक्स्ट में बदल देगा, इसके लिए स्पीच सर्विस का उपयोग किया जाएगा।

## ऑडियो को स्पीच सर्विस पर भेजें

ऑडियो को REST API का उपयोग करके स्पीच सर्विस पर भेजा जा सकता है। स्पीच सर्विस का उपयोग करने के लिए, पहले आपको एक एक्सेस टोकन प्राप्त करना होगा, फिर उस टोकन का उपयोग REST API तक पहुंचने के लिए करना होगा। ये एक्सेस टोकन 10 मिनट के बाद समाप्त हो जाते हैं, इसलिए आपके कोड को नियमित रूप से इन्हें प्राप्त करना चाहिए ताकि वे हमेशा अपडेट रहें।

### कार्य - एक्सेस टोकन प्राप्त करें

1. अपने पाई पर `smart-timer` प्रोजेक्ट खोलें।

1. `play_audio` फंक्शन को हटा दें। अब इसकी आवश्यकता नहीं है क्योंकि आप नहीं चाहते कि स्मार्ट टाइमर आपके कहे गए शब्दों को दोहराए।

1. `app.py` फाइल के शीर्ष पर निम्नलिखित इंपोर्ट जोड़ें:

    ```python
    import requests
    ```

1. `while True` लूप के ऊपर निम्नलिखित कोड जोड़ें ताकि स्पीच सर्विस के लिए कुछ सेटिंग्स डिक्लेयर की जा सकें:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` को अपनी स्पीच सर्विस रिसोर्स के API की के साथ बदलें। `<location>` को उस स्थान के साथ बदलें जिसे आपने स्पीच सर्विस रिसोर्स बनाते समय चुना था।

    `<language>` को उस भाषा के लोकल नाम के साथ बदलें जिसमें आप बोलेंगे, जैसे अंग्रेजी के लिए `en-GB`, या कैंटोनीज़ के लिए `zn-HK`। समर्थित भाषाओं और उनके लोकल नामों की सूची [Microsoft Docs पर भाषा और आवाज़ समर्थन दस्तावेज़](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) में पाई जा सकती है।

1. इसके नीचे, एक्सेस टोकन प्राप्त करने के लिए निम्नलिखित फंक्शन जोड़ें:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    यह एक टोकन जारी करने वाले एंडपॉइंट को कॉल करता है, API की को एक हेडर के रूप में पास करता है। यह कॉल एक एक्सेस टोकन लौटाता है जिसका उपयोग स्पीच सर्विस को कॉल करने के लिए किया जा सकता है।

1. इसके नीचे, एक फंक्शन डिक्लेयर करें जो कैप्चर किए गए ऑडियो में स्पीच को REST API का उपयोग करके टेक्स्ट में बदल देगा:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. इस फंक्शन के अंदर, REST API URL और हेडर्स सेट करें:

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

    यह स्पीच सर्विस रिसोर्स के स्थान का उपयोग करके एक URL बनाता है। फिर यह `get_access_token` फंक्शन से प्राप्त एक्सेस टोकन के साथ हेडर्स को पॉप्युलेट करता है, साथ ही ऑडियो कैप्चर करने के लिए उपयोग किए गए सैंपल रेट को भी। अंत में, यह URL के साथ पास किए जाने वाले कुछ पैरामीटर को परिभाषित करता है, जिसमें ऑडियो की भाषा शामिल है।

1. इसके नीचे, REST API को कॉल करने और टेक्स्ट प्राप्त करने के लिए निम्नलिखित कोड जोड़ें:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    यह URL को कॉल करता है और प्रतिक्रिया में आने वाले JSON मान को डिकोड करता है। प्रतिक्रिया में `RecognitionStatus` मान यह इंगित करता है कि क्या कॉल ने सफलतापूर्वक स्पीच को टेक्स्ट में बदला है, और यदि यह `Success` है, तो टेक्स्ट फंक्शन से लौटाया जाता है, अन्यथा एक खाली स्ट्रिंग लौटाई जाती है।

1. `while True:` लूप के ऊपर, स्पीच टू टेक्स्ट सर्विस से लौटाए गए टेक्स्ट को प्रोसेस करने के लिए एक फंक्शन डिफाइन करें। यह फंक्शन फिलहाल केवल टेक्स्ट को कंसोल में प्रिंट करेगा।

    ```python
    def process_text(text):
        print(text)
    ```

1. अंत में, `while True` लूप में `play_audio` को कॉल करने की जगह `convert_speech_to_text` फंक्शन को कॉल करें, और टेक्स्ट को `process_text` फंक्शन में पास करें:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. कोड चलाएं। बटन दबाएं और माइक्रोफोन में बोलें। जब आप बोलना समाप्त कर लें, तो बटन छोड़ दें, और ऑडियो को टेक्स्ट में बदलकर कंसोल में प्रिंट किया जाएगा।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    विभिन्न प्रकार के वाक्यों को आज़माएं, साथ ही ऐसे वाक्य जिनमें शब्दों की ध्वनि समान हो लेकिन उनके अर्थ अलग हों। उदाहरण के लिए, यदि आप अंग्रेजी में बोल रहे हैं, तो कहें 'I want to buy two bananas and an apple too', और ध्यान दें कि यह संदर्भ के आधार पर सही 'to', 'two' और 'too' का उपयोग करेगा, न कि केवल उनकी ध्वनि के आधार पर।

> 💁 आप इस कोड को [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) फोल्डर में पा सकते हैं।

😀 आपका स्पीच टू टेक्स्ट प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।