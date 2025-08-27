<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T13:52:09+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "pa"
}
-->
# ਟਾਈਮਰ ਸੈਟ ਕਰੋ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣਾ ਸਰਵਰਲੈਸ ਕੋਡ ਕਾਲ ਕਰੋਗੇ ਤਾਂ ਜੋ ਬੋਲਚਾਲ ਨੂੰ ਸਮਝਿਆ ਜਾ ਸਕੇ ਅਤੇ ਨਤੀਜਿਆਂ ਦੇ ਆਧਾਰ 'ਤੇ ਆਪਣੇ Wio Terminal 'ਤੇ ਟਾਈਮਰ ਸੈਟ ਕੀਤਾ ਜਾ ਸਕੇ।

## ਟਾਈਮਰ ਸੈਟ ਕਰੋ

ਸਪੀਚ-ਟੂ-ਟੈਕਸਟ ਕਾਲ ਤੋਂ ਵਾਪਸ ਆਉਣ ਵਾਲੇ ਟੈਕਸਟ ਨੂੰ ਤੁਹਾਡੇ ਸਰਵਰਲੈਸ ਕੋਡ ਨੂੰ ਭੇਜਣ ਦੀ ਜ਼ਰੂਰਤ ਹੈ ਤਾਂ ਜੋ LUIS ਦੁਆਰਾ ਪ੍ਰੋਸੈਸ ਕੀਤਾ ਜਾ ਸਕੇ, ਅਤੇ ਟਾਈਮਰ ਲਈ ਸਕਿੰਟ ਦੀ ਗਿਣਤੀ ਵਾਪਸ ਪ੍ਰਾਪਤ ਕੀਤੀ ਜਾ ਸਕੇ। ਇਹ ਸਕਿੰਟ ਦੀ ਗਿਣਤੀ ਟਾਈਮਰ ਸੈਟ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾ ਸਕਦੀ ਹੈ।

Arduino ਵਿੱਚ ਮਾਈਕ੍ਰੋਕੰਟਰੋਲਰਜ਼ ਦੇ ਨਾਲ ਮਲਟੀਪਲ ਥ੍ਰੇਡਸ ਲਈ ਮੂਲ ਸਹਾਇਤਾ ਨਹੀਂ ਹੁੰਦੀ, ਇਸ ਲਈ ਕੋਈ ਸਟੈਂਡਰਡ ਟਾਈਮਰ ਕਲਾਸਾਂ ਨਹੀਂ ਹੁੰਦੀਆਂ ਜਿਵੇਂ ਕਿ ਤੁਸੀਂ Python ਜਾਂ ਹੋਰ ਉੱਚ-ਸਤਹ ਦੀਆਂ ਭਾਸ਼ਾਵਾਂ ਵਿੱਚ ਕੋਡਿੰਗ ਕਰਦੇ ਸਮੇਂ ਪਾਉਂਦੇ ਹੋ। ਇਸ ਦੀ ਬਜਾਏ, ਤੁਸੀਂ ਟਾਈਮਰ ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ ਜੋ `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ ਬੀਤੇ ਸਮੇਂ ਨੂੰ ਮਾਪਣ ਦੁਆਰਾ ਕੰਮ ਕਰਦੀਆਂ ਹਨ ਅਤੇ ਸਮਾਂ ਖਤਮ ਹੋਣ 'ਤੇ ਫੰਕਸ਼ਨ ਕਾਲ ਕਰਦੀਆਂ ਹਨ।

### ਕੰਮ - ਟੈਕਸਟ ਨੂੰ ਸਰਵਰਲੈਸ ਫੰਕਸ਼ਨ ਨੂੰ ਭੇਜੋ

1. ਜੇ `smart-timer` ਪ੍ਰੋਜੈਕਟ VS Code ਵਿੱਚ ਖੁੱਲ੍ਹਾ ਨਹੀਂ ਹੈ, ਤਾਂ ਇਸਨੂੰ ਖੋਲ੍ਹੋ।

1. `config.h` ਹੈਡਰ ਫਾਇਲ ਖੋਲ੍ਹੋ ਅਤੇ ਆਪਣੀ ਫੰਕਸ਼ਨ ਐਪ ਲਈ URL ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ਨੂੰ ਪਿਛਲੇ ਪਾਠ ਦੇ ਆਖਰੀ ਕਦਮ ਵਿੱਚ ਪ੍ਰਾਪਤ ਕੀਤੇ URL ਨਾਲ ਬਦਲੋ, ਜੋ ਤੁਹਾਡੇ ਸਥਾਨਕ ਮਸ਼ੀਨ ਦੇ IP ਪਤਾ ਨੂੰ ਦਰਸਾਉਂਦਾ ਹੈ ਜੋ ਫੰਕਸ਼ਨ ਐਪ ਚਲਾ ਰਿਹਾ ਹੈ।

1. `src` ਫੋਲਡਰ ਵਿੱਚ ਇੱਕ ਨਵੀਂ ਫਾਇਲ ਬਣਾਓ ਜਿਸਦਾ ਨਾਮ `language_understanding.h` ਰੱਖੋ। ਇਹ ਫਾਇਲ ਇੱਕ ਕਲਾਸ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾਵੇਗੀ ਜੋ ਪਛਾਣੇ ਗਏ ਬੋਲਚਾਲ ਨੂੰ ਤੁਹਾਡੇ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਸਕਿੰਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਭੇਜੇਗੀ।

1. ਇਸ ਫਾਇਲ ਦੇ ਉੱਪਰ ਹਿੱਸੇ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    ਇਹ ਕੁਝ ਲੋੜੀਂਦੇ ਹੈਡਰ ਫਾਇਲਾਂ ਸ਼ਾਮਲ ਕਰਦਾ ਹੈ।

1. `LanguageUnderstanding` ਨਾਮ ਦੀ ਇੱਕ ਕਲਾਸ ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ ਅਤੇ ਇਸ ਕਲਾਸ ਦਾ ਇੱਕ ਇੰਸਟੈਂਸ ਘੋਸ਼ਿਤ ਕਰੋ:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. ਆਪਣੀ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ, ਤੁਹਾਨੂੰ ਇੱਕ WiFi ਕਲਾਇੰਟ ਘੋਸ਼ਿਤ ਕਰਨ ਦੀ ਜ਼ਰੂਰਤ ਹੈ। ਕਲਾਸ ਦੇ `private` ਸੈਕਸ਼ਨ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    WiFiClient _client;
    ```

1. `public` ਸੈਕਸ਼ਨ ਵਿੱਚ, `GetTimerDuration` ਨਾਮਕ ਇੱਕ ਮੈਥਡ ਘੋਸ਼ਿਤ ਕਰੋ ਜੋ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਕਾਲ ਕਰੇ:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` ਮੈਥਡ ਵਿੱਚ, ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਭੇਜਣ ਲਈ JSON ਬਣਾਉਣ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    ਇਹ `GetTimerDuration` ਮੈਥਡ ਨੂੰ ਪਾਸ ਕੀਤੇ ਟੈਕਸਟ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ JSON ਵਿੱਚ ਬਦਲਦਾ ਹੈ:

    ```json
    {
        "text" : "<text>"
    }
    ```

    ਜਿੱਥੇ `<text>` ਉਹ ਟੈਕਸਟ ਹੈ ਜੋ ਫੰਕਸ਼ਨ ਨੂੰ ਪਾਸ ਕੀਤਾ ਗਿਆ ਹੈ।

1. ਇਸ ਦੇ ਹੇਠਾਂ, ਫੰਕਸ਼ਨ ਐਪ ਕਾਲ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    ਇਹ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ POST ਰਿਕਵੈਸਟ ਭੇਜਦਾ ਹੈ, JSON ਬਾਡੀ ਪਾਸ ਕਰਦਾ ਹੈ ਅਤੇ ਰਿਸਪਾਂਸ ਕੋਡ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ।

1. ਇਸ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਰਿਸਪਾਂਸ ਕੋਡ ਦੀ ਜਾਂਚ ਕਰਦਾ ਹੈ। ਜੇਕਰ ਇਹ 200 (ਸਫਲਤਾ) ਹੈ, ਤਾਂ ਟਾਈਮਰ ਲਈ ਸਕਿੰਟ ਦੀ ਗਿਣਤੀ ਰਿਸਪਾਂਸ ਬਾਡੀ ਤੋਂ ਪ੍ਰਾਪਤ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਨਹੀਂ ਤਾਂ ਇੱਕ ਗਲਤੀ ਸੀਰੀਅਲ ਮਾਨੀਟਰ 'ਤੇ ਭੇਜੀ ਜਾਂਦੀ ਹੈ ਅਤੇ ਸਕਿੰਟ ਦੀ ਗਿਣਤੀ 0 'ਤੇ ਸੈਟ ਕੀਤੀ ਜਾਂਦੀ ਹੈ।

1. ਇਸ ਮੈਥਡ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਜੋ HTTP ਕਨੈਕਸ਼ਨ ਨੂੰ ਬੰਦ ਕਰਦਾ ਹੈ ਅਤੇ ਸਕਿੰਟ ਦੀ ਗਿਣਤੀ ਵਾਪਸ ਕਰਦਾ ਹੈ:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` ਫਾਇਲ ਵਿੱਚ, ਇਸ ਨਵੀਂ ਹੈਡਰ ਨੂੰ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ, `GetTimerDuration` ਮੈਥਡ ਨੂੰ ਕਾਲ ਕਰੋ ਤਾਂ ਜੋ ਟਾਈਮਰ ਦੀ ਮਿਆਦ ਪ੍ਰਾਪਤ ਕੀਤੀ ਜਾ ਸਕੇ:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    ਇਹ `SpeechToText` ਕਲਾਸ ਤੋਂ ਟੈਕਸਟ ਨੂੰ ਟਾਈਮਰ ਲਈ ਸਕਿੰਟ ਦੀ ਗਿਣਤੀ ਵਿੱਚ ਬਦਲਦਾ ਹੈ।

### ਕੰਮ - ਟਾਈਮਰ ਸੈਟ ਕਰੋ

ਸਕਿੰਟ ਦੀ ਗਿਣਤੀ ਟਾਈਮਰ ਸੈਟ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾ ਸਕਦੀ ਹੈ।

1. `platformio.ini` ਫਾਇਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੀ ਲਾਇਬ੍ਰੇਰੀ ਡਿਪੈਂਡੈਂਸੀ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ ਟਾਈਮਰ ਸੈਟ ਕਰਨ ਲਈ ਲਾਇਬ੍ਰੇਰੀ ਸ਼ਾਮਲ ਕੀਤੀ ਜਾ ਸਕੇ:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. `main.cpp` ਫਾਇਲ ਵਿੱਚ ਇਸ ਲਾਇਬ੍ਰੇਰੀ ਲਈ ਇੱਕ include ਡਾਇਰੈਕਟਿਵ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    auto timer = timer_create_default();
    ```

    ਇਹ ਕੋਡ `timer` ਨਾਮਕ ਇੱਕ ਟਾਈਮਰ ਘੋਸ਼ਿਤ ਕਰਦਾ ਹੈ।

1. ਇਸ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    ਇਹ `say` ਫੰਕਸ਼ਨ ਆਖਿਰਕਾਰ ਟੈਕਸਟ ਨੂੰ ਬੋਲਚਾਲ ਵਿੱਚ ਬਦਲੇਗਾ, ਪਰ ਇਸ ਸਮੇਂ ਇਹ ਸਿਰਫ਼ ਪਾਸ ਕੀਤੇ ਟੈਕਸਟ ਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ 'ਤੇ ਲਿਖੇਗਾ।

1. `say` ਫੰਕਸ਼ਨ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    ਇਹ ਇੱਕ ਕਾਲਬੈਕ ਫੰਕਸ਼ਨ ਹੈ ਜੋ ਟਾਈਮਰ ਖਤਮ ਹੋਣ 'ਤੇ ਕਾਲ ਕੀਤਾ ਜਾਵੇਗਾ। ਇਸਨੂੰ ਇੱਕ ਸੁਨੇਹਾ ਪਾਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ ਜੋ ਟਾਈਮਰ ਖਤਮ ਹੋਣ 'ਤੇ ਕਿਹਾ ਜਾਵੇਗਾ। ਟਾਈਮਰ ਦੁਹਰਾਏ ਜਾ ਸਕਦੇ ਹਨ, ਅਤੇ ਇਹ ਇਸ ਕਾਲਬੈਕ ਦੇ ਰਿਟਰਨ ਵੈਲਿਊ ਦੁਆਰਾ ਨਿਯੰਤਰਿਤ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ - ਇਹ `false` ਵਾਪਸ ਕਰਦਾ ਹੈ, ਟਾਈਮਰ ਨੂੰ ਮੁੜ ਨਾ ਚਲਾਉਣ ਲਈ।

1. `processAudio` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    ਇਹ ਕੋਡ ਕੁੱਲ ਸਕਿੰਟ ਦੀ ਜਾਂਚ ਕਰਦਾ ਹੈ, ਅਤੇ ਜੇਕਰ ਇਹ 0 ਹੈ, ਤਾਂ ਫੰਕਸ਼ਨ ਕਾਲ ਤੋਂ ਵਾਪਸ ਆ ਜਾਂਦਾ ਹੈ ਤਾਂ ਜੋ ਕੋਈ ਟਾਈਮਰ ਸੈਟ ਨਾ ਹੋਵੇ। ਇਹ ਕੁੱਲ ਸਕਿੰਟ ਨੂੰ ਮਿੰਟ ਅਤੇ ਸਕਿੰਟ ਵਿੱਚ ਬਦਲਦਾ ਹੈ।

1. ਇਸ ਕੋਡ ਦੇ ਹੇਠਾਂ, ਟਾਈਮਰ ਸ਼ੁਰੂ ਹੋਣ 'ਤੇ ਕਹਿਣ ਲਈ ਇੱਕ ਸੁਨੇਹਾ ਬਣਾਉਣ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

1. ਇਸ ਦੇ ਹੇਠਾਂ, ਟਾਈਮਰ ਖਤਮ ਹੋਣ 'ਤੇ ਕਹਿਣ ਲਈ ਇੱਕ ਸੁਨੇਹਾ ਬਣਾਉਣ ਲਈ ਸਮਾਨ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

1. ਇਸ ਤੋਂ ਬਾਅਦ, ਟਾਈਮਰ ਸ਼ੁਰੂ ਹੋਣ ਵਾਲਾ ਸੁਨੇਹਾ ਕਹੋ:

    ```cpp
    say(begin_message);
    ```

1. ਇਸ ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ, ਟਾਈਮਰ ਸ਼ੁਰੂ ਕਰੋ:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    ਇਹ ਟਾਈਮਰ ਨੂੰ ਟ੍ਰਿਗਰ ਕਰਦਾ ਹੈ। ਟਾਈਮਰ ਮਿਲੀਸਕਿੰਟ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਸੈਟ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਇਸ ਲਈ ਕੁੱਲ ਸਕਿੰਟ ਨੂੰ ਮਿਲੀਸਕਿੰਟ ਵਿੱਚ ਬਦਲਣ ਲਈ 1,000 ਨਾਲ ਗੁਣਾ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। `timerExpired` ਫੰਕਸ਼ਨ ਨੂੰ ਕਾਲਬੈਕ ਵਜੋਂ ਪਾਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਅਤੇ `end_message` ਨੂੰ ਕਾਲਬੈਕ ਨੂੰ ਪਾਸ ਕਰਨ ਲਈ ਆਰਗੂਮੈਂਟ ਵਜੋਂ ਪਾਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। ਇਹ ਕਾਲਬੈਕ ਸਿਰਫ਼ `void *` ਆਰਗੂਮੈਂਟ ਲੈਂਦਾ ਹੈ, ਇਸ ਲਈ ਸਟ੍ਰਿੰਗ ਨੂੰ ਢੰਗ ਨਾਲ ਬਦਲਿਆ ਜਾਂਦਾ ਹੈ।

1. ਆਖਿਰਕਾਰ, ਟਾਈਮਰ ਨੂੰ *ਟਿਕ* ਕਰਨ ਦੀ ਜ਼ਰੂਰਤ ਹੈ, ਅਤੇ ਇਹ `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। `loop` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    timer.tick();
    ```

1. ਇਸ ਕੋਡ ਨੂੰ ਬਣਾਓ, ਇਸਨੂੰ ਆਪਣੇ Wio Terminal 'ਤੇ ਅਪਲੋਡ ਕਰੋ ਅਤੇ ਇਸਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਦੁਆਰਾ ਟੈਸਟ ਕਰੋ। ਜਦੋਂ ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵਿੱਚ `Ready` ਦੇਖਦੇ ਹੋ, ਤਾਂ C ਬਟਨ (ਜੋ ਖੱਬੇ ਪਾਸੇ, ਪਾਵਰ ਸਵਿੱਚ ਦੇ ਸਭ ਤੋਂ ਨੇੜੇ ਹੈ) ਦਬਾਓ ਅਤੇ ਬੋਲੋ। 4 ਸਕਿੰਟ ਦਾ ਆਡੀਓ ਕੈਪਚਰ ਕੀਤਾ ਜਾਵੇਗਾ, ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਿਆ ਜਾਵੇਗਾ, ਫਿਰ ਤੁਹਾਡੇ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਭੇਜਿਆ ਜਾਵੇਗਾ, ਅਤੇ ਇੱਕ ਟਾਈਮਰ ਸੈਟ ਕੀਤਾ ਜਾਵੇਗਾ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਹਾਡਾ ਫੰਕਸ਼ਨ ਐਪ ਸਥਾਨਕ ਤੌਰ 'ਤੇ ਚੱਲ ਰਿਹਾ ਹੈ।

    ਤੁਸੀਂ ਦੇਖੋਗੇ ਕਿ ਟਾਈਮਰ ਕਦੋਂ ਸ਼ੁਰੂ ਹੁੰਦਾ ਹੈ ਅਤੇ ਕਦੋਂ ਖਤਮ ਹੁੰਦਾ ਹੈ।

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

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਪਾ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਟਾਈਮਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੱਜੇਪਣ ਹੋ ਸਕਦੇ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।