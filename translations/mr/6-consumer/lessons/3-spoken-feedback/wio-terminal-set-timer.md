<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T13:51:17+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "mr"
}
-->
# टाइमर सेट करा - Wio Terminal

या धड्याच्या भागात, तुम्ही तुमचा सर्व्हरलेस कोड कॉल कराल जे भाषण समजून घेईल आणि परिणामांवर आधारित तुमच्या Wio Terminal वर टाइमर सेट करेल.

## टाइमर सेट करा

भाषण ते मजकूर कॉलमधून परत आलेला मजकूर तुमच्या सर्व्हरलेस कोडकडे पाठवणे आवश्यक आहे, जे LUIS द्वारे प्रक्रिया केली जाईल आणि टाइमरसाठी सेकंदांची संख्या परत मिळेल. ही सेकंदांची संख्या टाइमर सेट करण्यासाठी वापरली जाऊ शकते.

मायक्रोकंट्रोलर्समध्ये Arduino मध्ये अनेक थ्रेड्ससाठी मूळ समर्थन नसते, त्यामुळे Python किंवा इतर उच्च-स्तरीय भाषांमध्ये कोडिंग करताना तुम्हाला सापडणाऱ्या मानक टाइमर क्लासेस उपलब्ध नसतात. त्याऐवजी तुम्ही टाइमर लायब्ररी वापरू शकता ज्या `loop` फंक्शनमध्ये कालावधी मोजून काम करतात आणि वेळ संपल्यावर फंक्शन्स कॉल करतात.

### कार्य - मजकूर सर्व्हरलेस फंक्शनकडे पाठवा

1. जर `smart-timer` प्रकल्प VS Code मध्ये उघडलेला नसेल तर तो उघडा.

1. `config.h` हेडर फाइल उघडा आणि तुमच्या फंक्शन अॅपसाठी URL जोडा:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ला तुमच्या फंक्शन अॅपसाठी URL ने बदला, जो तुम्ही मागील धड्याच्या शेवटच्या टप्प्यात प्राप्त केला होता, तुमच्या स्थानिक मशीनच्या IP पत्त्याकडे निर्देश करत आहे जे फंक्शन अॅप चालवत आहे.

1. `src` फोल्डरमध्ये एक नवीन फाइल तयार करा ज्याचे नाव `language_understanding.h` असे ठेवा. ही फाइल ओळखलेले भाषण फंक्शन अॅपकडे सेकंदांमध्ये रूपांतरित करण्यासाठी पाठवण्यासाठी एक क्लास परिभाषित करण्यासाठी वापरली जाईल.

1. या फाइलच्या शीर्षस्थानी खालील कोड जोडा:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    यात आवश्यक हेडर फाइल्स समाविष्ट आहेत.

1. `LanguageUnderstanding` नावाचा एक क्लास परिभाषित करा आणि या क्लासचे एक उदाहरण घोषित करा:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. तुमच्या फंक्शन अॅपला कॉल करण्यासाठी, तुम्हाला WiFi क्लायंट घोषित करणे आवश्यक आहे. क्लासच्या `private` विभागात खालील कोड जोडा:

    ```cpp
    WiFiClient _client;
    ```

1. `public` विभागात, `GetTimerDuration` नावाचा एक मेथड घोषित करा जो फंक्शन अॅपला कॉल करेल:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` मेथडमध्ये, फंक्शन अॅपकडे पाठवण्यासाठी JSON तयार करण्यासाठी खालील कोड जोडा:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    हे `GetTimerDuration` मेथडला पास केलेल्या मजकूराला खालील JSON मध्ये रूपांतरित करते:

    ```json
    {
        "text" : "<text>"
    }
    ```

    जिथे `<text>` हा फंक्शनला पास केलेला मजकूर आहे.

1. याखाली, फंक्शन अॅप कॉल करण्यासाठी खालील कोड जोडा:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    हे JSON बॉडी पास करत POST विनंती करते आणि प्रतिसाद कोड प्राप्त करते.

1. याखालील कोड जोडा:

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

    हा कोड प्रतिसाद कोड तपासतो. जर तो 200 (यशस्वी) असेल, तर टाइमरसाठी सेकंदांची संख्या प्रतिसाद बॉडीमधून मिळवली जाते. अन्यथा, एक त्रुटी सीरियल मॉनिटरवर पाठवली जाते आणि सेकंदांची संख्या 0 सेट केली जाते.

1. या मेथडच्या शेवटी खालील कोड जोडा जे HTTP कनेक्शन बंद करते आणि सेकंदांची संख्या परत करते:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` फाइलमध्ये, ही नवीन हेडर समाविष्ट करा:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` फंक्शनच्या शेवटी, टाइमरची कालावधी मिळवण्यासाठी `GetTimerDuration` मेथड कॉल करा:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    हे `SpeechToText` क्लासमधून कॉल केलेल्या मजकूराला टाइमरसाठी सेकंदांमध्ये रूपांतरित करते.

### कार्य - टाइमर सेट करा

सेकंदांची संख्या टाइमर सेट करण्यासाठी वापरली जाऊ शकते.

1. `platformio.ini` फाइलमध्ये खालील लायब्ररी डिपेंडन्सी जोडा जे टाइमर सेट करण्यासाठी लायब्ररी जोडते:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. `main.cpp` फाइलमध्ये या लायब्ररीसाठी एक `include` निर्देश जोडा:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` फंक्शनच्या वर खालील कोड जोडा:

    ```cpp
    auto timer = timer_create_default();
    ```

    हा कोड `timer` नावाचा टाइमर घोषित करतो.

1. याखाली, खालील कोड जोडा:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    ही `say` फंक्शन मजकूर भाषणात रूपांतरित करेल, परंतु सध्या ती फक्त पास केलेला मजकूर सीरियल मॉनिटरवर लिहील.

1. `say` फंक्शनच्या खाली, खालील कोड जोडा:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    ही एक कॉलबॅक फंक्शन आहे जी टाइमर संपल्यावर कॉल केली जाईल. टाइमर संपल्यावर सांगण्यासाठी एक संदेश पास केला जातो. टाइमर पुन्हा चालू होऊ शकतो, आणि हे कॉलबॅकच्या परत मूल्याद्वारे नियंत्रित केले जाते - हे `false` परत करते, टाइमर पुन्हा चालू न करण्यासाठी.

1. `processAudio` फंक्शनच्या शेवटी खालील कोड जोडा:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    हा कोड एकूण सेकंदांची संख्या तपासतो, आणि जर ती 0 असेल, तर फंक्शन कॉलमधून परत येतो जेणेकरून कोणतेही टाइमर सेट केले जात नाहीत. नंतर एकूण सेकंदांना मिनिटे आणि सेकंदांमध्ये रूपांतरित करते.

1. या कोडखाली, टाइमर सुरू झाल्यावर सांगण्यासाठी एक संदेश तयार करण्यासाठी खालील कोड जोडा:

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

1. याखाली, टाइमर संपल्यावर सांगण्यासाठी समान कोड जोडा:

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

1. यानंतर, टाइमर सुरू झाल्याचा संदेश सांगा:

    ```cpp
    say(begin_message);
    ```

1. या फंक्शनच्या शेवटी, टाइमर सुरू करा:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    हे टाइमर ट्रिगर करते. टाइमर मिलिसेकंदांमध्ये सेट केला जातो, त्यामुळे एकूण सेकंदांची संख्या 1,000 ने गुणाकार केली जाते जेणेकरून ती मिलिसेकंदांमध्ये रूपांतरित होईल. `timerExpired` फंक्शन कॉलबॅक म्हणून पास केले जाते, आणि `end_message` कॉलबॅकला पास करण्यासाठी एक आर्ग्युमेंट म्हणून पास केले जाते. हा कॉलबॅक फक्त `void *` आर्ग्युमेंट घेतो, त्यामुळे स्ट्रिंग योग्य प्रकारे रूपांतरित केली जाते.

1. शेवटी, टाइमरला *tick* करणे आवश्यक आहे, आणि हे `loop` फंक्शनच्या शेवटी खालील कोड जोडून केले जाते:

    ```cpp
    timer.tick();
    ```

1. हा कोड तयार करा, Wio Terminal वर अपलोड करा आणि सीरियल मॉनिटरद्वारे तपासा. एकदा तुम्हाला सीरियल मॉनिटरमध्ये `Ready` दिसले की, C बटण (डाव्या बाजूला, पॉवर स्विचजवळ) दाबा आणि बोला. 4 सेकंदांचे ऑडिओ कॅप्चर केले जाईल, मजकूरात रूपांतरित केले जाईल, नंतर तुमच्या फंक्शन अॅपकडे पाठवले जाईल, आणि टाइमर सेट केला जाईल. तुमचे फंक्शन अॅप स्थानिक पातळीवर चालू असल्याची खात्री करा.

    तुम्हाला टाइमर सुरू झाल्याचे आणि संपल्याचे दिसेल.

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

> 💁 तुम्ही हा कोड [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा टाइमर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.