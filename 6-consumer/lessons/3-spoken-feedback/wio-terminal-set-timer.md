# Set a timer - Wio Terminal

In this part of the lesson, you will call your serverless code to understand the speech, and set a timer on your Wio Terminal based off the results.

## Set a timer

The text that comes back from the speech to text call needs to be sent to your serverless code to be processed by LUIS, getting back the number of seconds for the timer. This number of seconds can be used to set a timer.

Microcontrollers don't natively have support for multiple threads in Arduino, so there are no standard timer classes like you might find when coding in Python or other higher-level languages. Instead you can use timer libraries that work by measuring elapsed time in the `loop` function, and calling functions when the time is up.

### Task - send the text to the serverless function

1. Open the `smart-timer` project in VS Code if it is not already open.

1. Open the `config.h` header file and add the URL for your function app:

    ```cpp
    const char *FUNCTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for your function app that you obtained in the last step of the last lesson, either pointing to the IP address of your local machine that is running the function app, or the function app deployed to the cloud.

1. If you have deployed your functions app to the cloud, add the following certificate for `azurewebsites.net` to the `config.h` file.

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    > 💁 If you are accessing your functions app locally, you don't need to do this.

1. Create a new file in the `src` folder called `language_understanding.h`. This will be used to define a class to send the recognized speech to your function app to be converted to seconds using LUIS.

1. Add the following to the top of this file:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    ```

    This includes some needed header files.

1. Define a class called `LanguageUnderstanding`, and declare an instance of this class:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. To call your functions app, you need to declare a WiFi client. The type you need depends on whether you are accessing the function app locally or deployed to the cloud.

    * If you are running the function app locally, add the following to the `private` section of the class:

        ```cpp
        WiFiClient _client;
        ```

    * If you are running the function app in the cloud, add the following to the `private` section of the class:

        ```cpp
        WiFiClientSecure _client;
        ```

      You will also need to set the certificate on this class, so add the following constructor to the `public` section:

        ```cpp
        LanguageUnderstanding()
        {
            _client.setCACert(FUNCTIONS_CERTIFICATE);
        }
        ```

1. In the `public` section, declare a method called `GetTimerDuration` to call the functions app:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. In the `GetTimerDuration` method, add the following code to build the JSON to be sent to the functions app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    JsonObject obj = doc.as<JsonObject>();
    serializeJson(obj, body);
    ```

    This coverts the text passed to the `GetTimerDuration` method into the following JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    where `<text>` is the text passed to the function.

1. Below this, add the following code to make the functions app call:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, FUNCTION_URL);

    int httpResponseCode = httpClient.sendRequest("POST", body);
    ```

    This makes a POST request to the functions app, passing the JSON body and getting the response code.

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

    This code checks the response code. If it is 200 (success), then the number of seconds for the time is retrieved from the response body. Otherwise an error is sent to the serial monitor and the number of seconds is set to 0.

1. Add the following code to the end of this method to close the HTTP connection and return the number of seconds:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. In the `main.cpp` file, include this new header:

    ```cpp
    #include "speech_to_text.h"
    ```

1. On the end of the `processAudio` function, call the `GetTimerDuration` method to get the timer duration:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    This converts the text from the call to the `SpeechToText` class into the number of seconds for the timer.

### Task - set a timer

The number of seconds can be used to set a timer.

1. Add the following library dependency to the `platformio.ini` file to add a library to set a timer:

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

    This code declares a timer called `timer`.

1. Below this, add the following code:

    ```cpp
    void say(String text)
    {
        Serial.println(text);
    }
    ```

    This `say` function will eventually convert text to speech, but for now it will just write the passed in text to the serial monitor.

1. Below the `say` function, add the following code:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    This is a callback function that will be called when a timer expires. It is passed a message to say when the timer expires. Timers can repeat, and this can be controlled by the return value of this callback - this returns `false`, to tell the timer to not run again.

1. Add the following code to the end of the `processAudio` function:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    This code checks the total number of seconds, and if it is 0, returns from teh function call so no timers are set. It then converts the total number of seconds into minutes and seconds.

1. Below this code, add the following to create a message to say when the timer is started:

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

1. Below this, add similar code to create a message to say when the timer has expired:

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

1. After this, say the timer started message:

    ```cpp
    say(begin_message);
    ```

1. At the end of this function,  start the timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    This triggers the timer. The timer is set using milliseconds, so the total number of seconds is multiplied by 1,000 to convert to milliseconds. The `timerExpired` function is passed as the callback, and the `end_message` is passed as an argument to pass to the callback. This callback only takes `void *` arguments, so the string is converted appropriately.

1. Finally, the timer needs to *tick*, and this is done in the `loop` function. Add the following code at the end of the `loop` function:

    ```cpp
    timer.tick();
    ```

1. Build this code, upload it to your Wio Terminal and test it out through the serial monitor. Press the C button (the one on the left-hand side, closest to the power switch), and speak. 4 seconds of audio will be captured, converted to text, then sent to your function app, and a timer will be set. If you are running the functions app locally, make sure it is running.

    You will see when the timer starts, and when it ends.

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

> 💁 You can find this code in the [code-timer/wio-terminal](code-timer/wio-terminal) folder.

😀 Your timer program was a success!
