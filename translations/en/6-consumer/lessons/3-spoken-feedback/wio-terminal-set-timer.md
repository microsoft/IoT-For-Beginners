<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T19:20:57+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "en"
}
-->
# Set a timer - Wio Terminal

In this part of the lesson, you will call your serverless code to interpret speech and set a timer on your Wio Terminal based on the results.

## Set a timer

The text returned from the speech-to-text call needs to be sent to your serverless code to be processed by LUIS, which will return the number of seconds for the timer. This number can then be used to set a timer.

Microcontrollers don't inherently support multithreading in Arduino, so there are no standard timer classes like those available in Python or other high-level languages. Instead, you can use timer libraries that measure elapsed time in the `loop` function and call functions when the timer expires.

### Task - send the text to the serverless function

1. Open the `smart-timer` project in VS Code if it’s not already open.

1. Open the `config.h` header file and add the URL for your function app:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for your function app that you obtained in the last step of the previous lesson, pointing to the IP address of your local machine running the function app.

1. Create a new file in the `src` folder called `language_understanding.h`. This file will define a class to send the recognized speech to your function app, which will convert it into seconds using LUIS.

1. Add the following to the top of this file:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    This includes the necessary header files.

1. Define a class called `LanguageUnderstanding` and declare an instance of this class:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. To call your function app, you need to declare a WiFi client. Add the following to the `private` section of the class:

    ```cpp
    WiFiClient _client;
    ```

1. In the `public` section, declare a method called `GetTimerDuration` to call the function app:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. In the `GetTimerDuration` method, add the following code to build the JSON to be sent to the function app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    This converts the text passed to the `GetTimerDuration` method into the following JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    where `<text>` is the text passed to the function.

1. Below this, add the following code to make the function app call:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    This sends a POST request to the function app, passing the JSON body and retrieving the response code.

1. Add the following code below this:

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

    This code checks the response code. If it is 200 (success), the number of seconds for the timer is retrieved from the response body. Otherwise, an error is sent to the serial monitor, and the number of seconds is set to 0.

1. Add the following code to the end of this method to close the HTTP connection and return the number of seconds:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. In the `main.cpp` file, include this new header:

    ```cpp
    #include "speech_to_text.h"
    ```

1. At the end of the `processAudio` function, call the `GetTimerDuration` method to get the timer duration:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    This converts the text from the `SpeechToText` class call into the number of seconds for the timer.

### Task - set a timer

The number of seconds can now be used to set a timer.

1. Add the following library dependency to the `platformio.ini` file to include a library for setting a timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Add an include directive for this library to the `main.cpp` file:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Above the `processAudio` function, add the following code:

    ```cpp
    auto timer = timer_create_default();
    ```

    This declares a timer called `timer`.

1. Below this, add the following code:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    The `say` function will eventually convert text to speech, but for now, it will simply write the passed text to the serial monitor.

1. Below the `say` function, add the following code:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    This is a callback function that will be triggered when a timer expires. It receives a message to display when the timer ends. Timers can repeat, and this is controlled by the return value of the callback—this returns `false` to indicate the timer should not run again.

1. Add the following code to the end of the `processAudio` function:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    This checks the total number of seconds, and if it is 0, exits the function without setting any timers. It then converts the total number of seconds into minutes and seconds.

1. Below this code, add the following to create a message to display when the timer starts:

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

1. Below this, add similar code to create a message to display when the timer expires:

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

1. After this, display the timer start message:

    ```cpp
    say(begin_message);
    ```

1. At the end of this function, start the timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    This activates the timer. The timer is set using milliseconds, so the total number of seconds is multiplied by 1,000 to convert to milliseconds. The `timerExpired` function is passed as the callback, and the `end_message` is passed as an argument to the callback. Since the callback only accepts `void *` arguments, the string is converted accordingly.

1. Finally, the timer needs to "tick," which is done in the `loop` function. Add the following code at the end of the `loop` function:

    ```cpp
    timer.tick();
    ```

1. Build the code, upload it to your Wio Terminal, and test it through the serial monitor. Once you see `Ready` in the serial monitor, press the C button (the one on the left-hand side, closest to the power switch), and speak. Four seconds of audio will be captured, converted to text, sent to your function app, and a timer will be set. Ensure your function app is running locally.

    You will see messages indicating when the timer starts and when it ends.

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

> 💁 You can find this code in the [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) folder.

😀 Your timer program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.