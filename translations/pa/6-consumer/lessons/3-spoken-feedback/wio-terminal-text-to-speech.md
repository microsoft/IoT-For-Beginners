<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T13:58:36+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "pa"
}
-->
# ਟੈਕਸਟ ਤੋਂ ਬੋਲਣ ਵਾਲੀ ਆਵਾਜ਼ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਟੈਕਸਟ ਨੂੰ ਬੋਲਣ ਵਾਲੀ ਆਵਾਜ਼ ਵਿੱਚ ਬਦਲ ਕੇ ਬੋਲਣ ਵਾਲਾ ਫੀਡਬੈਕ ਪ੍ਰਦਾਨ ਕਰੋਗੇ।

## ਟੈਕਸਟ ਤੋਂ ਬੋਲਣ ਵਾਲੀ ਆਵਾਜ਼

ਪਿਛਲੇ ਪਾਠ ਵਿੱਚ ਤੁਸੀਂ ਜੋ ਸਪੀਚ ਸਰਵਿਸ SDK ਵਰਤੀ ਸੀ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਲਈ, ਉਸੇ SDK ਨੂੰ ਟੈਕਸਟ ਨੂੰ ਵਾਪਸ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਲਈ ਵੀ ਵਰਤਿਆ ਜਾ ਸਕਦਾ ਹੈ।

## ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰੋ

ਸਪੀਚ ਦੀ ਬੇਨਤੀ ਕਰਦੇ ਸਮੇਂ, ਤੁਹਾਨੂੰ ਵਰਤਣ ਲਈ ਆਵਾਜ਼ ਪ੍ਰਦਾਨ ਕਰਨੀ ਪਵੇਗੀ ਕਿਉਂਕਿ ਸਪੀਚ ਵੱਖ-ਵੱਖ ਆਵਾਜ਼ਾਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਤਿਆਰ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ। ਹਰ ਭਾਸ਼ਾ ਵੱਖ-ਵੱਖ ਆਵਾਜ਼ਾਂ ਦਾ ਸਮਰਥਨ ਕਰਦੀ ਹੈ, ਅਤੇ ਤੁਸੀਂ ਸਪੀਚ ਸਰਵਿਸ SDK ਤੋਂ ਹਰ ਭਾਸ਼ਾ ਲਈ ਸਮਰਥਿਤ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ। ਮਾਈਕਰੋਕੰਟਰੋਲਰ ਦੀਆਂ ਸੀਮਾਵਾਂ ਇੱਥੇ ਆਉਂਦੀਆਂ ਹਨ - ਟੈਕਸਟ ਤੋਂ ਸਪੀਚ ਸਰਵਿਸ ਦੁਆਰਾ ਸਮਰਥਿਤ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਕਾਲ 77KB ਤੋਂ ਵੱਧ ਦੇ JSON ਦਸਤਾਵੇਜ਼ ਦਾ ਰੂਪ ਧਾਰਨ ਕਰਦੀ ਹੈ, ਜੋ Wio Terminal ਦੁਆਰਾ ਪ੍ਰਕਿਰਿਆ ਕਰਨ ਲਈ ਬਹੁਤ ਵੱਡਾ ਹੈ। ਲਿਖਣ ਦੇ ਸਮੇਂ, ਪੂਰੀ ਸੂਚੀ ਵਿੱਚ 215 ਆਵਾਜ਼ਾਂ ਹਨ, ਹਰ ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਦੁਆਰਾ ਪਰਿਭਾਸ਼ਿਤ ਹੈ ਜਿਵੇਂ ਕਿ ਹੇਠਾਂ ਦਿੱਤਾ ਗਿਆ ਹੈ:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

ਇਹ JSON **Aria** ਆਵਾਜ਼ ਲਈ ਹੈ, ਜਿਸ ਵਿੱਚ ਕਈ ਵੱਖ-ਵੱਖ ਆਵਾਜ਼ ਸ਼ੈਲੀਆਂ ਹਨ। ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਸਮੇਂ ਸਿਰਫ਼ shortname, `en-US-AriaNeural`, ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ।

ਪੂਰੀ ਸੂਚੀ ਨੂੰ ਆਪਣੇ ਮਾਈਕਰੋਕੰਟਰੋਲਰ 'ਤੇ ਡਾਊਨਲੋਡ ਅਤੇ ਡਿਕੋਡ ਕਰਨ ਦੀ ਬਜਾਏ, ਤੁਹਾਨੂੰ ਕੁਝ ਹੋਰ ਸਰਵਰਲੈਸ ਕੋਡ ਲਿਖਣ ਦੀ ਲੋੜ ਹੋਵੇਗੀ ਤਾਂ ਜੋ ਤੁਸੀਂ ਵਰਤ ਰਹੀ ਭਾਸ਼ਾ ਲਈ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰ ਸਕੋ, ਅਤੇ ਇਸ ਨੂੰ ਆਪਣੇ Wio Terminal ਤੋਂ ਕਾਲ ਕਰੋ। ਤੁਹਾਡਾ ਕੋਡ ਫਿਰ ਸੂਚੀ ਵਿੱਚੋਂ ਇੱਕ ਉਚਿਤ ਆਵਾਜ਼ ਚੁਣ ਸਕਦਾ ਹੈ, ਜਿਵੇਂ ਕਿ ਪਹਿਲੀ ਜੋ ਉਹ ਪਾਉਂਦਾ ਹੈ।

### ਕੰਮ - ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਇੱਕ ਸਰਵਰਲੈਸ ਫੰਕਸ਼ਨ ਬਣਾਓ

1. ਆਪਣੇ `smart-timer-trigger` ਪ੍ਰੋਜੈਕਟ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ, ਅਤੇ ਟਰਮੀਨਲ ਖੋਲ੍ਹੋ ਇਹ ਯਕੀਨੀ ਬਣਾਉਣ ਲਈ ਕਿ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਐਕਟੀਵੇਟ ਹੈ। ਜੇ ਨਹੀਂ, ਟਰਮੀਨਲ ਨੂੰ ਮਾਰੋ ਅਤੇ ਮੁੜ ਬਣਾਓ।

1. `local.settings.json` ਫਾਈਲ ਖੋਲ੍ਹੋ ਅਤੇ ਸਪੀਚ API ਕੁੰਜੀ ਅਤੇ ਸਥਾਨ ਲਈ ਸੈਟਿੰਗਜ਼ ਸ਼ਾਮਲ ਕਰੋ:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` ਨੂੰ ਆਪਣੇ ਸਪੀਚ ਸਰਵਿਸ ਰਿਸੋਰਸ ਲਈ API ਕੁੰਜੀ ਨਾਲ ਬਦਲੋ। `<location>` ਨੂੰ ਉਸ ਸਥਾਨ ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਸੀਂ ਸਪੀਚ ਸਰਵਿਸ ਰਿਸੋਰਸ ਬਣਾਉਣ ਸਮੇਂ ਵਰਤਿਆ ਸੀ।

1. ਇਸ ਐਪ ਵਿੱਚ ਇੱਕ ਨਵਾਂ HTTP ਟ੍ਰਿਗਰ ਸ਼ਾਮਲ ਕਰੋ ਜਿਸਨੂੰ `get-voices` ਕਿਹਾ ਜਾਂਦਾ ਹੈ, VS Code ਟਰਮੀਨਲ ਵਿੱਚ ਫੰਕਸ਼ਨ ਐਪ ਪ੍ਰੋਜੈਕਟ ਦੇ ਰੂਟ ਫੋਲਡਰ ਦੇ ਅੰਦਰ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਦੀ ਵਰਤੋਂ ਕਰਕੇ:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    ਇਹ ਇੱਕ HTTP ਟ੍ਰਿਗਰ ਬਣਾਏਗਾ ਜਿਸਨੂੰ `get-voices` ਕਿਹਾ ਜਾਂਦਾ ਹੈ।

1. `get-voices` ਫੋਲਡਰ ਵਿੱਚ `__init__.py` ਫਾਈਲ ਦੀ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    ਇਹ ਕੋਡ ਸਪੀਚ ਸਰਵਿਸ ਦੇ ਐਂਡਪੌਇੰਟ ਨੂੰ ਕਾਲ ਕਰਦਾ ਹੈ ਤਾਂ ਜੋ ਆਵਾਜ਼ਾਂ ਪ੍ਰਾਪਤ ਕੀਤੀਆਂ ਜਾ ਸਕਣ। ਇਹ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਸਾਰੀਆਂ ਭਾਸ਼ਾਵਾਂ ਲਈ ਆਵਾਜ਼ਾਂ ਨਾਲ ਇੱਕ ਵੱਡਾ JSON ਦਸਤਾਵੇਜ਼ ਹੈ, ਇਸ ਲਈ ਬੇਨਤੀ ਬਾਡੀ ਵਿੱਚ ਦਿੱਤੀ ਭਾਸ਼ਾ ਲਈ ਆਵਾਜ਼ਾਂ ਨੂੰ ਫਿਲਟਰ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਫਿਰ shortname ਨੂੰ ਕੱਢ ਕੇ JSON ਸੂਚੀ ਵਜੋਂ ਵਾਪਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। shortname ਉਹ ਮੁੱਲ ਹੈ ਜੋ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਲਈ ਲੋੜੀਂਦਾ ਹੈ, ਇਸ ਲਈ ਸਿਰਫ਼ ਇਹ ਮੁੱਲ ਵਾਪਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

    > 💁 ਤੁਸੀਂ ਜ਼ਰੂਰਤ ਅਨੁਸਾਰ ਫਿਲਟਰ ਨੂੰ ਬਦਲ ਸਕਦੇ ਹੋ ਤਾਂ ਜੋ ਸਿਰਫ਼ ਉਹ ਆਵਾਜ਼ਾਂ ਚੁਣ ਸਕੋ ਜੋ ਤੁਸੀਂ ਚਾਹੁੰਦੇ ਹੋ।

    ਇਹ ਡਾਟਾ ਦਾ ਆਕਾਰ 77KB (ਲਿਖਣ ਦੇ ਸਮੇਂ) ਤੋਂ ਘਟਾ ਕੇ ਇੱਕ ਬਹੁਤ ਛੋਟੇ JSON ਦਸਤਾਵੇਜ਼ ਵਿੱਚ ਕਰਦਾ ਹੈ। ਉਦਾਹਰਨ ਲਈ, US ਆਵਾਜ਼ਾਂ ਲਈ ਇਹ 408 bytes ਹੈ।

1. ਆਪਣੀ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਸਥਾਨਕ ਤੌਰ 'ਤੇ ਚਲਾਓ। ਤੁਸੀਂ ਇਸ ਨੂੰ curl ਵਰਗੇ ਟੂਲ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਕਾਲ ਕਰ ਸਕਦੇ ਹੋ ਜਿਵੇਂ ਕਿ ਤੁਸੀਂ ਆਪਣੇ `text-to-timer` HTTP ਟ੍ਰਿਗਰ ਦੀ ਜਾਂਚ ਕੀਤੀ ਸੀ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਆਪਣੀ ਭਾਸ਼ਾ ਨੂੰ JSON ਬਾਡੀ ਵਜੋਂ ਪਾਸ ਕਰੋ:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` ਨੂੰ ਆਪਣੀ ਭਾਸ਼ਾ ਨਾਲ ਬਦਲੋ, ਜਿਵੇਂ `en-GB`, ਜਾਂ `zh-CN`।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) ਫੋਲਡਰ ਵਿੱਚ ਪਾ ਸਕਦੇ ਹੋ।

### ਕੰਮ - ਆਪਣੀ Wio Terminal ਤੋਂ ਆਵਾਜ਼ ਪ੍ਰਾਪਤ ਕਰੋ

1. `smart-timer` ਪ੍ਰੋਜੈਕਟ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ ਜੇਕਰ ਇਹ ਪਹਿਲਾਂ ਹੀ ਖੁੱਲ੍ਹਾ ਨਹੀਂ ਹੈ।

1. `config.h` ਹੈਡਰ ਫਾਈਲ ਖੋਲ੍ਹੋ ਅਤੇ ਆਪਣੀ ਫੰਕਸ਼ਨ ਐਪ ਲਈ URL ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ਨੂੰ `get-voices` HTTP ਟ੍ਰਿਗਰ ਲਈ URL ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਹਾਡੀ ਫੰਕਸ਼ਨ ਐਪ 'ਤੇ ਹੈ। ਇਹ `TEXT_TO_TIMER_FUNCTION_URL` ਲਈ ਮੁੱਲ ਦੇ ਸਮਾਨ ਹੋਵੇਗਾ, ਸਿਵਾਏ ਫੰਕਸ਼ਨ ਨਾਮ `get-voices` ਦੇ ਬਦਲੇ `text-to-timer`।

1. `src` ਫੋਲਡਰ ਵਿੱਚ ਇੱਕ ਨਵੀਂ ਫਾਈਲ ਬਣਾਓ ਜਿਸਨੂੰ `text_to_speech.h` ਕਿਹਾ ਜਾਂਦਾ ਹੈ। ਇਹ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਲਈ ਇੱਕ ਕਲਾਸ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾਵੇਗੀ।

1. `text_to_speech.h` ਫਾਈਲ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤੇ ਸ਼ਾਮਲ ਕਰਨ ਦੇ ਨਿਰਦੇਸ਼ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕੋਡ ਨੂੰ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ `TextToSpeech` ਕਲਾਸ ਦੀ ਘੋਸ਼ਣਾ ਕੀਤੀ ਜਾ ਸਕੇ, ਨਾਲ ਹੀ ਇੱਕ ਇੰਸਟੈਂਸ ਜੋ ਐਪਲੀਕੇਸ਼ਨ ਦੇ ਬਾਕੀ ਹਿੱਸੇ ਵਿੱਚ ਵਰਤਿਆ ਜਾ ਸਕੇ:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. ਆਪਣੀ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ, ਤੁਹਾਨੂੰ ਇੱਕ WiFi ਕਲਾਇੰਟ ਦੀ ਘੋਸ਼ਣਾ ਕਰਨ ਦੀ ਲੋੜ ਹੈ। ਕਲਾਸ ਦੇ `private` ਸੈਕਸ਼ਨ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    WiFiClient _client;
    ```

1. `private` ਸੈਕਸ਼ਨ ਵਿੱਚ, ਚੁਣੀ ਗਈ ਆਵਾਜ਼ ਲਈ ਇੱਕ ਫੀਲਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    String _voice;
    ```

1. `public` ਸੈਕਸ਼ਨ ਵਿੱਚ, ਇੱਕ `init` ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ ਜੋ ਪਹਿਲੀ ਆਵਾਜ਼ ਪ੍ਰਾਪਤ ਕਰੇਗਾ:

    ```cpp
    void init()
    {
    }
    ```

1. ਆਵਾਜ਼ਾਂ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ, ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਨੂੰ ਭਾਸ਼ਾ ਦੇ ਨਾਲ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਭੇਜਣ ਦੀ ਲੋੜ ਹੈ। `init` ਫੰਕਸ਼ਨ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. ਇਸ ਤੋਂ ਬਾਅਦ ਇੱਕ `HTTPClient` ਬਣਾਓ, ਫਿਰ ਇਸਨੂੰ ਆਵਾਜ਼ਾਂ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ ਵਰਤੋ, JSON ਦਸਤਾਵੇਜ਼ ਪੋਸਟ ਕਰਦੇ ਹੋਏ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਜਵਾਬ ਕੋਡ ਦੀ ਜਾਂਚ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ, ਅਤੇ ਜੇਕਰ ਇਹ 200 (ਸਫਲਤਾ) ਹੈ, ਤਾਂ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਕੱਢੋ, ਸੂਚੀ ਵਿੱਚੋਂ ਪਹਿਲੀ ਆਵਾਜ਼ ਪ੍ਰਾਪਤ ਕਰੋ:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. ਇਸ ਤੋਂ ਬਾਅਦ, HTTP ਕਲਾਇੰਟ ਕਨੈਕਸ਼ਨ ਨੂੰ ਬੰਦ ਕਰੋ:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` ਫਾਈਲ ਖੋਲ੍ਹੋ, ਅਤੇ ਇਸ ਨਵੀਂ ਹੈਡਰ ਫਾਈਲ ਨੂੰ ਸ਼ਾਮਲ ਕਰਨ ਲਈ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰਨ ਦਾ ਨਿਰਦੇਸ਼ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ, `speechToText.init();` ਕਾਲ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ `TextToSpeech` ਕਲਾਸ ਨੂੰ ਸ਼ੁਰੂ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    textToSpeech.init();
    ```

1. ਇਸ ਕੋਡ ਨੂੰ ਬਣਾਓ, ਇਸਨੂੰ ਆਪਣੇ Wio Terminal 'ਤੇ ਅਪਲੋਡ ਕਰੋ ਅਤੇ ਇਸਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਦੁਆਰਾ ਜਾਂਚੋ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਹਾਡੀ ਫੰਕਸ਼ਨ ਐਪ ਚੱਲ ਰਹੀ ਹੈ।

    ਤੁਸੀਂ ਫੰਕਸ਼ਨ ਐਪ ਤੋਂ ਵਾਪਸ ਕੀਤੀ ਗਈ ਉਪਲਬਧ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਦੇਖੋਗੇ, ਨਾਲ ਹੀ ਚੁਣੀ ਗਈ ਆਵਾਜ਼।

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲੋ

ਜਦੋਂ ਤੁਹਾਡੇ ਕੋਲ ਵਰਤਣ ਲਈ ਇੱਕ ਆਵਾਜ਼ ਹੁੰਦੀ ਹੈ, ਇਸਨੂੰ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਲਈ ਵਰਤਿਆ ਜਾ ਸਕਦਾ ਹੈ। ਆਵਾਜ਼ਾਂ ਦੇ ਨਾਲ ਉਹੀ ਮੈਮਰੀ ਸੀਮਾਵਾਂ ਸਪੀਚ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਸਮੇਂ ਵੀ ਲਾਗੂ ਹੁੰਦੀਆਂ ਹਨ, ਇਸ ਲਈ ਤੁਹਾਨੂੰ ਸਪੀਚ ਨੂੰ SD ਕਾਰਡ 'ਤੇ ਲਿਖਣ ਦੀ ਲੋੜ ਹੋਵੇਗੀ ਤਾਂ ਜੋ ਇਸਨੂੰ ReSpeaker 'ਤੇ ਚਲਾਇਆ ਜਾ ਸਕੇ।

> 💁 ਇਸ ਪ੍ਰੋਜੈਕਟ ਦੇ ਪਹਿਲੇ ਪਾਠਾਂ ਵਿੱਚ ਤੁਸੀਂ ਮਾਈਕਰੋਫੋਨ ਤੋਂ ਕੈਪਚਰ ਕੀਤੀ ਗਈ ਸਪੀਚ ਨੂੰ ਸਟੋਰ ਕਰਨ ਲਈ ਫਲੈਸ਼ ਮੈਮਰੀ ਦੀ ਵਰਤੋਂ ਕੀਤੀ ਸੀ। ਇਹ ਪਾਠ SD ਕਾਰਡ ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ ਕਿਉਂਕਿ Seeed ਆਡੀਓ ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇਸ ਤੋਂ ਆਡੀਓ ਚਲਾਉਣਾ ਆਸਾਨ ਹੈ।

ਇਸ ਤੋਂ ਇਲਾਵਾ ਇੱਕ ਹੋਰ ਸੀਮਾ ਨੂੰ ਧਿਆਨ ਵਿੱਚ ਰੱਖਣ ਦੀ ਲੋੜ ਹੈ, ਸਪੀਚ ਸਰਵਿਸ ਤੋਂ ਉਪਲਬਧ ਆਡੀਓ ਡਾਟਾ, ਅਤੇ Wio Terminal ਦੁਆਰਾ ਸਮਰਥਿਤ ਫਾਰਮੈਟ। ਪੂਰੇ ਕੰਪਿਊਟਰਾਂ ਦੇ ਵਿਰੁੱਧ, ਮਾਈਕਰੋਕੰਟਰੋਲਰ ਲਈ ਆਡੀਓ ਲਾਇਬ੍ਰੇਰੀਆਂ ਆਡੀਓ ਫਾਰਮੈਟਾਂ ਵਿੱਚ ਬਹੁਤ ਸੀਮਿਤ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਉਦਾਹਰਨ ਲਈ, Seeed Arduino Audio ਲਾਇਬ੍ਰੇਰੀ ਜੋ ReSpeaker 'ਤੇ ਆਵਾਜ਼ ਚਲਾ ਸਕਦੀ ਹੈ ਸਿਰਫ਼ 44.1KHz ਸੈਂਪਲ ਰੇਟ 'ਤੇ ਆਡੀਓ ਦਾ ਸਮਰਥਨ ਕਰਦੀ ਹੈ। Azure ਸਪੀਚ ਸਰਵਿਸਾਂ ਕਈ ਫਾਰਮੈਟਾਂ ਵਿੱਚ ਆਡੀਓ ਪ੍ਰਦਾਨ ਕਰ ਸਕਦੀਆਂ ਹਨ, ਪਰ ਉਹਨਾਂ ਵਿੱਚੋਂ ਕੋਈ ਵੀ ਇਹ ਸੈਂਪਲ ਰੇਟ ਵਰਤਦਾ ਨਹੀਂ ਹੈ, ਉਹ ਸਿਰਫ਼ 8KHz, 16KHz, 24KHz ਅਤੇ 48KHz ਪ੍ਰਦਾਨ ਕਰਦੇ ਹਨ। ਇਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਆਡੀਓ ਨੂੰ 44.1KHz ਵਿੱਚ ਮੁੜ-ਸੈਂਪਲ ਕਰਨ ਦੀ ਲੋੜ ਹੈ, ਜੋ Wio Terminal ਦੇ ਕੋਲ ਹੋਰ ਵਸਾਏ ਦੀ ਲੋੜ ਹੋਵੇਗੀ, ਖਾਸ ਤੌਰ 'ਤੇ ਮੈਮਰੀ।

ਜਦੋਂ ਡਾਟਾ ਨੂੰ ਇਸ ਤਰ੍ਹਾਂ ਮੈਨਿਪੁਲੇਟ ਕਰਨ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ, ਤਾਂ ਇਹ ਅਕਸਰ ਵਧੀਆ ਹੁੰਦਾ ਹੈ ਕਿ ਸਰਵਰਲੈਸ ਕੋਡ ਦੀ ਵਰਤੋਂ ਕੀਤੀ ਜਾਵੇ, ਖਾਸ ਤੌਰ 'ਤੇ ਜੇਕਰ ਡਾਟਾ ਵੈੱਬ ਕਾਲ ਦੁਆਰਾ ਪ੍ਰਾਪਤ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। Wio Terminal ਇੱਕ ਸਰਵਰਲੈਸ ਫੰਕਸ਼ਨ ਨੂੰ ਕਾਲ ਕਰ ਸਕਦਾ ਹੈ, ਟੈਕਸਟ ਨੂੰ ਬਦਲਣ ਲਈ ਪਾਸ ਕਰਦਾ ਹੈ, ਅਤੇ ਸਰਵਰਲੈਸ ਫੰਕਸ਼ਨ ਸਪੀਚ ਸਰਵਿਸ ਨੂੰ ਕਾਲ ਕਰ ਸਕਦਾ ਹੈ ਤਾਂ ਜੋ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਿਆ ਜਾ ਸਕੇ, ਨਾਲ ਹੀ ਆਡੀਓ ਨੂੰ ਲੋੜੀਂਦੇ ਸੈਂਪਲ ਰੇਟ ਵਿੱਚ ਮੁੜ-ਸੈਂਪਲ ਕਰ ਸਕਦਾ ਹੈ। ਇਹ ਫਿਰ ਆਡੀਓ ਨੂੰ Wio Terminal ਦੀ ਲੋੜ ਅਨੁਸਾਰ ਰੂਪ ਵਿੱਚ ਵਾਪਸ ਕਰ ਸਕਦਾ ਹੈ ਜੋ SD ਕਾਰਡ 'ਤੇ ਸਟੋਰ ਕੀਤਾ ਜਾ ਸਕੇ ਅਤੇ ReSpeaker 'ਤੇ ਚਲਾਇਆ ਜਾ ਸਕੇ।

### ਕੰਮ - ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਲਈ ਇੱਕ ਸਰਵਰਲੈਸ ਫੰਕਸ਼ਨ ਬਣਾਓ

1. ਆਪਣੇ `smart-timer-trigger` ਪ੍ਰੋਜੈਕਟ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ, ਅਤੇ ਟਰਮੀਨਲ ਖੋਲ੍ਹੋ ਇਹ ਯਕੀਨੀ ਬਣਾਉਣ ਲਈ ਕਿ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਐਕਟੀਵੇਟ ਹੈ। ਜੇ ਨਹੀਂ, ਟਰਮੀਨਲ ਨੂੰ ਮਾਰੋ ਅਤੇ ਮੁੜ ਬਣਾਓ।

1. ਇਸ ਐਪ ਵਿੱਚ ਇੱਕ ਨਵਾਂ HTTP ਟ੍ਰਿਗਰ ਸ਼ਾਮਲ ਕਰੋ ਜਿਸਨੂੰ `text-to-speech` ਕਿਹਾ ਜਾਂਦਾ ਹੈ, VS Code ਟਰਮੀਨਲ ਵਿੱਚ ਫੰਕਸ਼ਨ ਐਪ ਪ੍ਰੋਜੈਕਟ ਦੇ ਰੂਟ ਫੋਲਡਰ ਦੇ ਅੰਦਰ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਦੀ ਵਰਤੋਂ ਕਰਕੇ:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    ਇਹ ਇੱਕ HTTP ਟ੍ਰਿਗਰ ਬਣਾਏਗਾ ਜਿਸਨੂੰ `text-to-speech` ਕਿਹਾ ਜਾਂਦਾ ਹੈ।

1. [librosa](https://librosa.org) Pip ਪੈਕੇਜ ਵਿੱਚ ਆਡੀਓ ਨੂੰ ਮੁੜ-ਸੈਂਪਲ ਕਰਨ ਦੇ ਫੰਕਸ਼ਨ ਹਨ, ਇਸ ਲਈ ਇਸਨੂੰ `requirements.txt` ਫਾਈਲ ਵਿੱਚ ਸ਼ਾਮਲ ਕਰੋ:

    ```sh
    librosa
    ```

    ਜਦੋਂ ਇਹ ਸ਼ਾਮਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, Pip ਪੈਕੇਜ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਦੀ ਵਰਤੋਂ ਕਰਕੇ VS Code ਟਰਮੀਨਲ ਤੋਂ ਇੰਸਟਾਲ ਕਰੋ:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ ਜੇਕਰ ਤੁਸੀਂ Linux ਵਰਤ ਰਹੇ ਹੋ, ਜਿਸ ਵਿੱਚ Raspberry Pi OS ਸ਼ਾਮਲ ਹੈ, ਤਾਂ ਤੁਹਾਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ `libsndfile` ਇੰਸਟਾਲ ਕਰਨ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਬਦਲਣ ਲਈ, ਤੁਸੀਂ ਸਿੱਧੇ ਸਪੀਚ API ਕੁੰਜੀ ਦੀ ਵਰਤੋਂ ਨਹੀਂ ਕਰ ਸਕਦੇ, ਇਸਦੀ ਬਜਾਏ ਤੁਹਾਨੂੰ ਇੱਕ ਐਕਸੈਸ ਟੋਕਨ ਦੀ ਬੇਨਤੀ ਕਰਨ ਦੀ ਲੋੜ ਹੈ, ਸਪੀਚ ਸਰਵਿਸ ਲਈ ਐਕਸੈਸ ਟੋਕਨ ਬੇਨਤੀ ਨੂੰ ਪ੍ਰਮਾਣਿਤ ਕਰਨ ਲਈ API ਕੁੰਜੀ ਦੀ ਵਰਤੋਂ ਕਰਦੇ ਹੋਏ। `text-to-speech` ਫੋਲਡਰ ਤੋਂ `__init__.py` ਫਾਈਲ ਖੋਲ੍ਹੋ ਅਤੇ ਇਸ ਵਿੱਚ ਸਾਰੀ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    ਇਹ ਸੈਟਿੰਗਜ਼ ਤੋਂ ਪੜ੍ਹੇ ਜਾਣ ਵਾਲੇ ਸਥਾਨ ਅਤੇ ਸਪੀਚ ਕੁੰਜੀ ਲਈ ਕਾਂਸਟੈਂਟਸ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ। ਫਿਰ ਇਹ `get_access_token` ਫੰਕਸ਼ਨ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ ਸਪੀਚ ਸਰਵਿਸ ਲਈ ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰੇਗਾ।

1. ਇਸ ਕੋਡ ਦੇ ਹੇ
### ਟਾਸਕ - ਆਪਣੇ Wio Terminal ਤੋਂ ਆਡੀਓ ਚਲਾਓ

**ਜਲਦੀ ਆ ਰਿਹਾ ਹੈ**

## ਆਪਣੀ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਕਲਾਉਡ ਵਿੱਚ ਡਿਪਲੌਇ ਕਰਨਾ

ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ ਲੋਕਲ ਰਨ ਕਰਨ ਦਾ ਕਾਰਨ ਇਹ ਹੈ ਕਿ `librosa` ਪਿਪ ਪੈਕੇਜ, ਜੋ ਲਿਨਕਸ 'ਤੇ ਵਰਤਿਆ ਜਾਂਦਾ ਹੈ, ਇੱਕ ਲਾਇਬ੍ਰੇਰੀ 'ਤੇ ਨਿਰਭਰ ਹੈ ਜੋ ਡਿਫਾਲਟ ਰੂਪ ਵਿੱਚ ਇੰਸਟਾਲ ਨਹੀਂ ਹੁੰਦੀ। ਇਸ ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਇੰਸਟਾਲ ਕਰਨਾ ਪਵੇਗਾ ਤਾਂ ਜੋ ਫੰਕਸ਼ਨ ਐਪ ਚੱਲ ਸਕੇ। ਫੰਕਸ਼ਨ ਐਪ ਸਰਵਰਲੈਸ ਹੁੰਦੇ ਹਨ - ਇੱਥੇ ਕੋਈ ਸਰਵਰ ਨਹੀਂ ਹੁੰਦੇ ਜੋ ਤੁਸੀਂ ਖੁਦ ਮੈਨੇਜ ਕਰ ਸਕੋ, ਇਸ ਲਈ ਪਹਿਲਾਂ ਤੋਂ ਇਹ ਲਾਇਬ੍ਰੇਰੀ ਇੰਸਟਾਲ ਕਰਨ ਦਾ ਕੋਈ ਤਰੀਕਾ ਨਹੀਂ ਹੈ।

ਇਸ ਨੂੰ ਕਰਨ ਦਾ ਤਰੀਕਾ ਇਹ ਹੈ ਕਿ ਆਪਣੀ ਫੰਕਸ਼ਨ ਐਪ ਨੂੰ Docker ਕੰਟੇਨਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਡਿਪਲੌਇ ਕਰੋ। ਇਹ ਕੰਟੇਨਰ ਕਲਾਉਡ ਦੁਆਰਾ ਤਬ ਡਿਪਲੌਇ ਕੀਤਾ ਜਾਂਦਾ ਹੈ ਜਦੋਂ ਵੀ ਇਹ ਨਵੀਂ ਇੰਸਟੈਂਸ ਨੂੰ ਚਲਾਉਣ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ (ਜਿਵੇਂ ਕਿ ਜਦੋਂ ਮੰਗ ਉਪਲਬਧ ਸਰੋਤਾਂ ਤੋਂ ਵੱਧ ਹੁੰਦੀ ਹੈ, ਜਾਂ ਜੇ ਫੰਕਸ਼ਨ ਐਪ ਕੁਝ ਸਮੇਂ ਲਈ ਵਰਤਿਆ ਨਹੀਂ ਗਿਆ ਅਤੇ ਬੰਦ ਹੋ ਗਿਆ ਹੈ)।

ਤੁਸੀਂ ਫੰਕਸ਼ਨ ਐਪ ਸੈਟਅਪ ਕਰਨ ਅਤੇ Docker ਰਾਹੀਂ ਡਿਪਲੌਇ ਕਰਨ ਦੇ ਨਿਰਦੇਸ਼ [Microsoft Docs 'ਤੇ Linux 'ਤੇ ਕਸਟਮ ਕੰਟੇਨਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਫੰਕਸ਼ਨ ਬਣਾਉਣ ਦੀ ਡਾਕੂਮੈਂਟੇਸ਼ਨ](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) ਵਿੱਚ ਪਾ ਸਕਦੇ ਹੋ।

ਇਸਨੂੰ ਡਿਪਲੌਇ ਕਰਨ ਤੋਂ ਬਾਅਦ, ਤੁਸੀਂ ਆਪਣਾ Wio Terminal ਕੋਡ ਇਸ ਫੰਕਸ਼ਨ ਤੱਕ ਪਹੁੰਚ ਕਰਨ ਲਈ ਪੋਰਟ ਕਰ ਸਕਦੇ ਹੋ:

1. Azure Functions ਸਰਟੀਫਿਕੇਟ ਨੂੰ `config.h` ਵਿੱਚ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. ਸਾਰੇ `<WiFiClient.h>` ਸ਼ਾਮਲ ਕਰਨ ਨੂੰ `<WiFiClientSecure.h>` ਵਿੱਚ ਬਦਲੋ।

1. ਸਾਰੇ `WiFiClient` ਫੀਲਡ ਨੂੰ `WiFiClientSecure` ਵਿੱਚ ਬਦਲੋ।

1. ਹਰ ਕਲਾਸ ਵਿੱਚ ਜਿਸ ਵਿੱਚ `WiFiClientSecure` ਫੀਲਡ ਹੈ, ਇੱਕ ਕਨਸਟ੍ਰਕਟਰ ਸ਼ਾਮਲ ਕਰੋ ਅਤੇ ਉਸ ਕਨਸਟ੍ਰਕਟਰ ਵਿੱਚ ਸਰਟੀਫਿਕੇਟ ਸੈਟ ਕਰੋ:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**ਅਸਵੀਕਰਤਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਪੂਰੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁੱਤੀਆਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।