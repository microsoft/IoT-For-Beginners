<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-11-18T19:15:58+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "pcm"
}
-->
# Set timer - Wio Terminal

For dis part of di lesson, you go call your serverless code to sabi di speech, and set timer for your Wio Terminal based on di result.

## Set timer

Di text wey go come back from di speech to text call need to go your serverless code make e process am with LUIS, wey go return di number of seconds for di timer. Dis number of seconds fit dey use set timer.

Microcontrollers no dey support multiple threads for Arduino normally, so e no get standard timer classes like di one wey you fit see when you dey code for Python or other high-level languages. Instead, you fit use timer libraries wey dey work by measuring di time wey don pass for di `loop` function, and e go call functions when di time don finish.

### Task - send di text go di serverless function

1. Open di `smart-timer` project for VS Code if e never dey open.

1. Open di `config.h` header file and add di URL for your function app:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Change `<URL>` to di URL for your function app wey you get for di last step of di last lesson, wey dey point to di IP address of your local machine wey dey run di function app.

1. Create new file for di `src` folder wey you go call `language_understanding.h`. Dis one go dey use define class wey go send di speech wey dem recognize go your function app to convert am to seconds using LUIS.

1. Add dis one for di top of dis file:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Dis one include some header files wey you need.

1. Define class wey you go call `LanguageUnderstanding`, and declare one instance of dis class:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. To call your functions app, you need declare WiFi client. Add dis one for di `private` section of di class:

    ```cpp
    WiFiClient _client;
    ```

1. For di `public` section, declare method wey you go call `GetTimerDuration` to call di functions app:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. For di `GetTimerDuration` method, add dis code to build di JSON wey you go send go di functions app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dis one dey convert di text wey dem pass to di `GetTimerDuration` method into dis JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    wey `<text>` na di text wey dem pass to di function.

1. Under dis one, add dis code to make di functions app call:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dis one dey make POST request go di functions app, dey pass di JSON body and dey get di response code.

1. Add dis code under dis one:

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

    Dis code dey check di response code. If e be 200 (success), di number of seconds for di timer go dey retrieve from di response body. If e no be 200, error go dey send go di serial monitor and di number of seconds go dey set to 0.

1. Add dis code for di end of dis method to close di HTTP connection and return di number of seconds:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. For di `main.cpp` file, include dis new header:

    ```cpp
    #include "speech_to_text.h"
    ```

1. For di end of di `processAudio` function, call di `GetTimerDuration` method to get di timer duration:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Dis one dey convert di text from di call to di `SpeechToText` class into di number of seconds for di timer.

### Task - set timer

Di number of seconds fit dey use set timer.

1. Add dis library dependency to di `platformio.ini` file to add library wey go set timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Add include directive for dis library to di `main.cpp` file:

    ```cpp
    #include <arduino-timer.h>
    ```

1. For di top of di `processAudio` function, add dis code:

    ```cpp
    auto timer = timer_create_default();
    ```

    Dis code dey declare timer wey dem call `timer`.

1. Under dis one, add dis code:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Dis `say` function go later convert text to speech, but for now e go just write di text wey dem pass to di serial monitor.

1. Under di `say` function, add dis code:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Dis na callback function wey dem go call when timer don finish. E dey pass message wey e go talk when timer don finish. Timers fit repeat, and dis one fit dey control by di return value of dis callback - dis one dey return `false`, to tell di timer make e no run again.

1. Add dis code for di end of di `processAudio` function:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Dis code dey check di total number of seconds, and if e be 0, e go return from di function call so no timer go dey set. E go then convert di total number of seconds into minutes and seconds.

1. Under dis code, add dis one to create message wey e go talk when timer don start:

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

1. Under dis one, add similar code to create message wey e go talk when timer don finish:

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

1. After dis one, talk di timer start message:

    ```cpp
    say(begin_message);
    ```

1. For di end of dis function, start di timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Dis one dey trigger di timer. Di timer dey set using milliseconds, so di total number of seconds dey multiply by 1,000 to convert to milliseconds. Di `timerExpired` function dey pass as di callback, and di `end_message` dey pass as argument wey dem go pass to di callback. Dis callback only dey take `void *` arguments, so dem go convert di string well.

1. Finally, di timer need to *tick*, and dis one dey happen for di `loop` function. Add dis code for di end of di `loop` function:

    ```cpp
    timer.tick();
    ```

1. Build dis code, upload am to your Wio Terminal and test am through di serial monitor. Once you see `Ready` for di serial monitor, press di C button (di one wey dey left-hand side, close to di power switch), and talk. 4 seconds of audio go dey capture, convert to text, then send go your function app, and timer go dey set. Make sure say your functions app dey run locally.

    You go see when di timer start, and when e finish.

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

> 💁 You fit find dis code for di [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) folder.

😀 Your timer program work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis docu wey you dey see don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) take translate am. Even though we dey try make sure say e correct, abeg no forget say machine translation fit get mistake or no too accurate. Di original docu for di language wey dem first write am na di main correct one. If na important matter, e go better make you use professional human translation. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->