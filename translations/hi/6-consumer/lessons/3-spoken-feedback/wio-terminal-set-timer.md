<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T17:46:26+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "hi"
}
-->
# टाइमर सेट करें - Wio Terminal

इस पाठ के इस भाग में, आप अपने सर्वरलेस कोड को कॉल करेंगे ताकि स्पीच को समझा जा सके और परिणामों के आधार पर अपने Wio Terminal पर एक टाइमर सेट कर सकें।

## टाइमर सेट करें

स्पीच टू टेक्स्ट कॉल से प्राप्त टेक्स्ट को आपके सर्वरलेस कोड में भेजा जाना चाहिए ताकि LUIS द्वारा इसे प्रोसेस किया जा सके और टाइमर के लिए सेकंड की संख्या प्राप्त की जा सके। इस सेकंड की संख्या का उपयोग टाइमर सेट करने के लिए किया जा सकता है।

माइक्रोकंट्रोलर्स में Arduino में मूल रूप से मल्टीपल थ्रेड्स का समर्थन नहीं होता है, इसलिए यहां कोई मानक टाइमर क्लास नहीं होती जैसे कि आप Python या अन्य उच्च-स्तरीय भाषाओं में कोडिंग करते समय पाते हैं। इसके बजाय, आप टाइमर लाइब्रेरीज़ का उपयोग कर सकते हैं जो `loop` फंक्शन में बीते हुए समय को मापकर काम करती हैं और समय समाप्त होने पर फंक्शन को कॉल करती हैं।

### कार्य - टेक्स्ट को सर्वरलेस फंक्शन में भेजें

1. यदि `smart-timer` प्रोजेक्ट पहले से VS Code में खुला नहीं है, तो इसे खोलें।

1. `config.h` हेडर फाइल खोलें और अपनी फंक्शन ऐप के लिए URL जोड़ें:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>` को अपनी फंक्शन ऐप के URL से बदलें, जो आपने पिछले पाठ के अंतिम चरण में प्राप्त किया था, और जो आपके लोकल मशीन के IP एड्रेस की ओर इशारा करता है।

1. `src` फोल्डर में एक नई फाइल बनाएं जिसका नाम `language_understanding.h` हो। इसका उपयोग एक क्लास को परिभाषित करने के लिए किया जाएगा जो पहचानी गई स्पीच को आपकी फंक्शन ऐप में सेकंड में बदलने के लिए भेजेगी।

1. इस फाइल के शीर्ष पर निम्नलिखित जोड़ें:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    इसमें कुछ आवश्यक हेडर फाइलें शामिल हैं।

1. `LanguageUnderstanding` नामक एक क्लास परिभाषित करें और इस क्लास का एक इंस्टेंस घोषित करें:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. अपनी फंक्शन ऐप को कॉल करने के लिए, एक WiFi क्लाइंट घोषित करें। क्लास के `private` सेक्शन में निम्नलिखित जोड़ें:

    ```cpp
    WiFiClient _client;
    ```

1. `public` सेक्शन में, `GetTimerDuration` नामक एक मेथड घोषित करें ताकि फंक्शन ऐप को कॉल किया जा सके:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` मेथड में, फंक्शन ऐप को भेजे जाने वाले JSON को बनाने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    यह `GetTimerDuration` मेथड को पास किए गए टेक्स्ट को निम्नलिखित JSON में बदलता है:

    ```json
    {
        "text" : "<text>"
    }
    ```

    जहां `<text>` वह टेक्स्ट है जो फंक्शन को पास किया गया है।

1. इसके नीचे, फंक्शन ऐप कॉल करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    यह फंक्शन ऐप को एक POST अनुरोध भेजता है, JSON बॉडी पास करता है और प्रतिक्रिया कोड प्राप्त करता है।

1. इसके नीचे निम्नलिखित कोड जोड़ें:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    यह कोड प्रतिक्रिया कोड की जांच करता है। यदि यह 200 (सफलता) है, तो टाइमर के लिए सेकंड की संख्या प्रतिक्रिया बॉडी से प्राप्त की जाती है। अन्यथा, एक त्रुटि सीरियल मॉनिटर पर भेजी जाती है और सेकंड की संख्या 0 पर सेट की जाती है।

1. इस मेथड के अंत में निम्नलिखित कोड जोड़ें ताकि HTTP कनेक्शन बंद हो जाए और सेकंड की संख्या लौटाई जा सके:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` फाइल में इस नए हेडर को शामिल करें:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` फंक्शन के अंत में, `GetTimerDuration` मेथड को कॉल करें ताकि टाइमर की अवधि प्राप्त की जा सके:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    यह `SpeechToText` क्लास से कॉल के टेक्स्ट को टाइमर के सेकंड की संख्या में बदलता है।

### कार्य - टाइमर सेट करें

सेकंड की संख्या का उपयोग टाइमर सेट करने के लिए किया जा सकता है।

1. `platformio.ini` फाइल में निम्नलिखित लाइब्रेरी डिपेंडेंसी जोड़ें ताकि टाइमर सेट करने के लिए एक लाइब्रेरी जोड़ी जा सके:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. `main.cpp` फाइल में इस लाइब्रेरी के लिए एक इनक्लूड डायरेक्टिव जोड़ें:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` फंक्शन के ऊपर निम्नलिखित कोड जोड़ें:

    ```cpp
    auto timer = timer_create_default();
    ```

    यह कोड `timer` नामक एक टाइमर घोषित करता है।

1. इसके नीचे निम्नलिखित कोड जोड़ें:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    यह `say` फंक्शन अंततः टेक्स्ट को स्पीच में बदल देगा, लेकिन फिलहाल यह पास किए गए टेक्स्ट को केवल सीरियल मॉनिटर पर लिखेगा।

1. `say` फंक्शन के नीचे निम्नलिखित कोड जोड़ें:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    यह एक कॉलबैक फंक्शन है जो तब कॉल किया जाएगा जब टाइमर समाप्त हो जाएगा। इसे एक संदेश पास किया जाता है जिसे टाइमर समाप्त होने पर कहा जाएगा। टाइमर दोहराए जा सकते हैं, और इसे इस कॉलबैक के रिटर्न वैल्यू द्वारा नियंत्रित किया जा सकता है - यह `false` लौटाता है, ताकि टाइमर फिर से न चले।

1. `processAudio` फंक्शन के अंत में निम्नलिखित कोड जोड़ें:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    यह कोड कुल सेकंड की संख्या की जांच करता है, और यदि यह 0 है, तो फंक्शन कॉल से लौट आता है ताकि कोई टाइमर सेट न हो। फिर यह कुल सेकंड की संख्या को मिनट और सेकंड में बदलता है।

1. इस कोड के नीचे, टाइमर शुरू होने पर कहने के लिए एक संदेश बनाने के लिए निम्नलिखित जोड़ें:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. इसके नीचे, टाइमर समाप्त होने पर कहने के लिए एक समान संदेश बनाने के लिए कोड जोड़ें:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. इसके बाद, टाइमर शुरू होने का संदेश कहें:

    ```cpp
    say(begin_message);
    ```

1. इस फंक्शन के अंत में, टाइमर शुरू करें:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    यह टाइमर को ट्रिगर करता है। टाइमर को मिलीसेकंड में सेट किया जाता है, इसलिए कुल सेकंड की संख्या को 1,000 से गुणा किया जाता है ताकि इसे मिलीसेकंड में बदला जा सके। `timerExpired` फंक्शन को कॉलबैक के रूप में पास किया जाता है, और `end_message` को एक आर्ग्युमेंट के रूप में पास किया जाता है ताकि इसे कॉलबैक में पास किया जा सके। यह कॉलबैक केवल `void *` आर्ग्युमेंट लेता है, इसलिए स्ट्रिंग को उपयुक्त रूप से बदला जाता है।

1. अंत में, टाइमर को *टिक* करने की आवश्यकता होती है, और यह `loop` फंक्शन में किया जाता है। `loop` फंक्शन के अंत में निम्नलिखित कोड जोड़ें:

    ```cpp
    timer.tick();
    ```

1. इस कोड को बनाएं, इसे अपने Wio Terminal पर अपलोड करें और इसे सीरियल मॉनिटर के माध्यम से टेस्ट करें। जैसे ही आप सीरियल मॉनिटर में `Ready` देखते हैं, C बटन (बाईं ओर का, जो पावर स्विच के सबसे करीब है) दबाएं और बोलें। 4 सेकंड का ऑडियो कैप्चर किया जाएगा, टेक्स्ट में बदला जाएगा, फिर आपकी फंक्शन ऐप में भेजा जाएगा, और एक टाइमर सेट किया जाएगा। सुनिश्चित करें कि आपकी फंक्शन ऐप लोकल रूप से चल रही है।

    आप देखेंगे कि टाइमर कब शुरू होता है और कब समाप्त होता है।

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 आप इस कोड को [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका टाइमर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।