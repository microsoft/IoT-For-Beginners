<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T13:51:43+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ne"
}
-->
# टाइमर सेट गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईंले आफ्नो serverless कोडलाई बोलि बुझ्न कल गर्नुहुनेछ, र परिणामको आधारमा Wio Terminal मा टाइमर सेट गर्नुहुनेछ।

## टाइमर सेट गर्नुहोस्

Speech to text कलबाट फर्किएको पाठलाई LUIS द्वारा प्रशोधन गर्न serverless कोडमा पठाउन आवश्यक छ, जसले टाइमरको लागि सेकेन्डको संख्या फिर्ता ल्याउँछ। यो सेकेन्डको संख्या टाइमर सेट गर्न प्रयोग गर्न सकिन्छ।

Arduino मा माइक्रोकन्ट्रोलरहरूले स्वाभाविक रूपमा बहु-थ्रेडहरूको समर्थन गर्दैनन्, त्यसैले Python वा अन्य उच्च-स्तरीय भाषाहरूमा पाइने जस्तै मानक टाइमर कक्षाहरू उपलब्ध हुँदैनन्। यसको सट्टा, तपाईं टाइमर लाइब्रेरीहरू प्रयोग गर्न सक्नुहुन्छ, जसले `loop` फङ्सनमा बितेको समय मापन गरेर काम गर्छ, र समय सकिएपछि फङ्सनहरू कल गर्छ।

### कार्य - पाठलाई serverless फङ्सनमा पठाउनुहोस्

1. यदि `smart-timer` प्रोजेक्ट पहिले नै खुला छैन भने, VS Code मा खोल्नुहोस्।

1. `config.h` हेडर फाइल खोल्नुहोस् र आफ्नो फङ्सन एपको URL थप्नुहोस्:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>` लाई पछिल्लो पाठको अन्तिम चरणमा प्राप्त गरिएको आफ्नो फङ्सन एपको URL सँग प्रतिस्थापन गर्नुहोस्, जसले तपाईंको स्थानीय मेसिनको IP ठेगानामा संकेत गर्दछ, जहाँ फङ्सन एप चलिरहेको छ।

1. `src` फोल्डरमा `language_understanding.h` नामक नयाँ फाइल बनाउनुहोस्। यो फाइल मान्यता प्राप्त बोलिलाई फङ्सन एपमा पठाउन र LUIS प्रयोग गरेर सेकेन्डमा रूपान्तरण गर्न कक्षा परिभाषित गर्न प्रयोग गरिनेछ।

1. यस फाइलको माथि निम्न थप्नुहोस्:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    यसले आवश्यक हेडर फाइलहरू समावेश गर्दछ।

1. `LanguageUnderstanding` नामक कक्षा परिभाषित गर्नुहोस्, र यस कक्षाको एउटा उदाहरण घोषणा गर्नुहोस्:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. आफ्नो फङ्सन एपलाई कल गर्न, WiFi क्लाइन्ट घोषणा गर्नुहोस्। कक्षाको `private` सेक्सनमा निम्न थप्नुहोस्:

    ```cpp
    WiFiClient _client;
    ```

1. `public` सेक्सनमा, `GetTimerDuration` नामक एउटा मेथड घोषणा गर्नुहोस्, जसले फङ्सन एपलाई कल गर्छ:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` मेथडमा, फङ्सन एपमा पठाउन JSON निर्माण गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    यसले `GetTimerDuration` मेथडमा पास गरिएको पाठलाई निम्न JSON मा रूपान्तरण गर्छ:

    ```json
    {
        "text" : "<text>"
    }
    ```

    जहाँ `<text>` भनेको फङ्सनमा पास गरिएको पाठ हो।

1. यसको तल, फङ्सन एप कल गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    यसले फङ्सन एपमा POST अनुरोध गर्छ, JSON बडी पास गर्छ र प्रतिक्रिया कोड प्राप्त गर्छ।

1. यसको तल निम्न कोड थप्नुहोस्:

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

    यो कोडले प्रतिक्रिया कोड जाँच्छ। यदि यो 200 (सफलता) हो भने, टाइमरको लागि सेकेन्डको संख्या प्रतिक्रिया बडीबाट प्राप्त गरिन्छ। अन्यथा, सिरियल मोनिटरमा त्रुटि पठाइन्छ र सेकेन्डको संख्या 0 मा सेट गरिन्छ।

1. यस मेथडको अन्त्यमा निम्न कोड थप्नुहोस्, HTTP कनेक्शन बन्द गर्न र सेकेन्डको संख्या फिर्ता गर्न:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` फाइलमा यो नयाँ हेडर समावेश गर्नुहोस्:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` फङ्सनको अन्त्यमा, `GetTimerDuration` मेथडलाई टाइमरको अवधि प्राप्त गर्न कल गर्नुहोस्:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    यसले `SpeechToText` कक्षाबाट आएको पाठलाई टाइमरको लागि सेकेन्डको संख्यामा रूपान्तरण गर्छ।

### कार्य - टाइमर सेट गर्नुहोस्

टाइमर सेट गर्न सेकेन्डको संख्या प्रयोग गर्न सकिन्छ।

1. `platformio.ini` फाइलमा निम्न लाइब्रेरी निर्भरता थप्नुहोस्, टाइमर सेट गर्न लाइब्रेरी थप्न:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. `main.cpp` फाइलमा यो लाइब्रेरीको लागि समावेश निर्देशन थप्नुहोस्:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` फङ्सनको माथि निम्न कोड थप्नुहोस्:

    ```cpp
    auto timer = timer_create_default();
    ```

    यसले `timer` नामक टाइमर घोषणा गर्छ।

1. यसको तल निम्न कोड थप्नुहोस्:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    यो `say` फङ्सनले अन्ततः पाठलाई बोलिमा रूपान्तरण गर्नेछ, तर अहिलेको लागि यसले सिरियल मोनिटरमा पास गरिएको पाठ लेख्नेछ।

1. `say` फङ्सनको तल निम्न कोड थप्नुहोस्:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    यो एउटा क्यालब्याक फङ्सन हो, जुन टाइमर समाप्त हुँदा कल गरिन्छ। यसलाई टाइमर समाप्त हुँदा भन्नुपर्ने सन्देश पास गरिन्छ। टाइमरहरू दोहोरिन सक्छन्, र यो क्यालब्याकको रिटर्न मानले नियन्त्रण गर्न सकिन्छ - यसले `false` फिर्ता गर्छ, टाइमरलाई फेरि नचलाउन भन्न।

1. `processAudio` फङ्सनको अन्त्यमा निम्न कोड थप्नुहोस्:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    यो कोडले कुल सेकेन्ड जाँच्छ, र यदि यो 0 हो भने, फङ्सन कलबाट फर्किन्छ ताकि कुनै टाइमर सेट नगरियोस्। त्यसपछि यो कुल सेकेन्डलाई मिनेट र सेकेन्डमा रूपान्तरण गर्छ।

1. यस कोडको तल, टाइमर सुरु हुँदा भन्नुपर्ने सन्देश बनाउन निम्न थप्नुहोस्:

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

1. यसको तल, टाइमर समाप्त हुँदा भन्नुपर्ने सन्देश बनाउन यस्तै कोड थप्नुहोस्:

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

1. यसपछि, टाइमर सुरु भएको सन्देश भन्नुहोस्:

    ```cpp
    say(begin_message);
    ```

1. यस फङ्सनको अन्त्यमा, टाइमर सुरु गर्नुहोस्:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    यसले टाइमर ट्रिगर गर्छ। टाइमर मिलिसेकेन्ड प्रयोग गरेर सेट गरिन्छ, त्यसैले कुल सेकेन्डलाई मिलिसेकेन्डमा रूपान्तरण गर्न 1,000 ले गुणा गरिन्छ। `timerExpired` फङ्सन क्यालब्याकको रूपमा पास गरिन्छ, र `end_message` क्यालब्याकमा पास गर्नको लागि आर्गुमेन्टको रूपमा पास गरिन्छ। यो क्यालब्याकले केवल `void *` आर्गुमेन्टहरू लिन्छ, त्यसैले स्ट्रिङलाई उपयुक्त रूपमा रूपान्तरण गरिन्छ।

1. अन्ततः, टाइमरलाई *tick* गर्न आवश्यक छ, र यो `loop` फङ्सनमा गरिन्छ। `loop` फङ्सनको अन्त्यमा निम्न कोड थप्नुहोस्:

    ```cpp
    timer.tick();
    ```

1. यो कोड बनाउनुहोस्, Wio Terminal मा अपलोड गर्नुहोस् र सिरियल मोनिटर मार्फत परीक्षण गर्नुहोस्। जब तपाईं सिरियल मोनिटरमा `Ready` देख्नुहुन्छ, C बटन थिच्नुहोस् (बायाँपट्टि, पावर स्विचको नजिक), र बोल्नुहोस्। 4 सेकेन्डको अडियो क्याप्चर गरिनेछ, पाठमा रूपान्तरण गरिनेछ, त्यसपछि तपाईंको फङ्सन एपमा पठाइनेछ, र टाइमर सेट गरिनेछ। सुनिश्चित गर्नुहोस् कि तपाईंको फङ्सन एप स्थानीय रूपमा चलिरहेको छ।

    तपाईंले टाइमर सुरु हुँदा र समाप्त हुँदा देख्नुहुनेछ।

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

> 💁 तपाईंले यो कोड [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको टाइमर प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरी अनुवाद गरिएको हो। हामी यथासम्भव सटीकता सुनिश्चित गर्न प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषामा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्त्वपूर्ण जानकारीका लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याका लागि हामी जिम्मेवार हुने छैनौं।  