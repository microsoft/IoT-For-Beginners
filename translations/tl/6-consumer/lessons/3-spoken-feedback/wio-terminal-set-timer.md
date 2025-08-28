<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T23:12:54+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "tl"
}
-->
# Mag-set ng Timer - Wio Terminal

Sa bahaging ito ng aralin, tatawagin mo ang iyong serverless code upang maunawaan ang boses, at mag-set ng timer sa iyong Wio Terminal base sa mga resulta.

## Mag-set ng Timer

Ang text na bumabalik mula sa speech-to-text na tawag ay kailangang ipadala sa iyong serverless code upang maiproseso ng LUIS, at makuha ang bilang ng segundo para sa timer. Ang bilang ng segundo na ito ay maaaring gamitin upang mag-set ng timer.

Ang mga microcontroller ay walang native na suporta para sa multiple threads sa Arduino, kaya walang mga standard na timer classes tulad ng makikita mo kapag nagko-code sa Python o iba pang mas mataas na antas ng wika. Sa halip, maaari kang gumamit ng mga timer library na gumagana sa pamamagitan ng pagsukat ng lumipas na oras sa `loop` function, at pagtawag ng mga function kapag natapos na ang oras.

### Gawain - ipadala ang text sa serverless function

1. Buksan ang proyekto na `smart-timer` sa VS Code kung hindi pa ito nakabukas.

1. Buksan ang `config.h` header file at idagdag ang URL para sa iyong function app:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Palitan ang `<URL>` ng URL para sa iyong function app na nakuha mo sa huling hakbang ng nakaraang aralin, na tumuturo sa IP address ng iyong lokal na makina na nagpapatakbo ng function app.

1. Gumawa ng bagong file sa folder na `src` na tinatawag na `language_understanding.h`. Ito ay gagamitin upang magdeklara ng isang klase na magpapadala ng na-recognize na boses sa iyong function app upang ma-convert sa segundo gamit ang LUIS.

1. Idagdag ang sumusunod sa itaas ng file na ito:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Kasama dito ang ilang kinakailangang header files.

1. Magdeklara ng isang klase na tinatawag na `LanguageUnderstanding`, at magdeklara ng isang instance ng klase na ito:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Upang tawagin ang iyong function app, kailangan mong magdeklara ng WiFi client. Idagdag ang sumusunod sa `private` na seksyon ng klase:

    ```cpp
    WiFiClient _client;
    ```

1. Sa `public` na seksyon, magdeklara ng isang method na tinatawag na `GetTimerDuration` upang tawagin ang function app:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Sa `GetTimerDuration` method, idagdag ang sumusunod na code upang buuin ang JSON na ipapadala sa function app:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Kinoconvert nito ang text na ipinasa sa `GetTimerDuration` method sa sumusunod na JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    kung saan ang `<text>` ay ang text na ipinasa sa function.

1. Sa ibaba nito, idagdag ang sumusunod na code upang gawin ang tawag sa function app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Gumagawa ito ng POST request sa function app, ipinapasa ang JSON body at kinukuha ang response code.

1. Idagdag ang sumusunod na code sa ibaba nito:

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

    Sinusuri ng code na ito ang response code. Kung ito ay 200 (tagumpay), ang bilang ng segundo para sa timer ay kinukuha mula sa response body. Kung hindi, isang error ang ipinapadala sa serial monitor at ang bilang ng segundo ay itinatakda sa 0.

1. Idagdag ang sumusunod na code sa dulo ng method na ito upang isara ang HTTP connection at ibalik ang bilang ng segundo:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Sa `main.cpp` file, isama ang bagong header na ito:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Sa dulo ng `processAudio` function, tawagin ang `GetTimerDuration` method upang makuha ang tagal ng timer:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Kinoconvert nito ang text mula sa tawag sa `SpeechToText` class sa bilang ng segundo para sa timer.

### Gawain - mag-set ng timer

Ang bilang ng segundo ay maaaring gamitin upang mag-set ng timer.

1. Idagdag ang sumusunod na library dependency sa `platformio.ini` file upang magdagdag ng library para sa pag-set ng timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Magdagdag ng include directive para sa library na ito sa `main.cpp` file:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Sa itaas ng `processAudio` function, idagdag ang sumusunod na code:

    ```cpp
    auto timer = timer_create_default();
    ```

    Ang code na ito ay nagdeklara ng isang timer na tinatawag na `timer`.

1. Sa ibaba nito, idagdag ang sumusunod na code:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Ang `say` function na ito ay sa huli ay magko-convert ng text sa boses, ngunit sa ngayon ay isusulat lamang nito ang ipinasa na text sa serial monitor.

1. Sa ibaba ng `say` function, idagdag ang sumusunod na code:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Ito ay isang callback function na tatawagin kapag nag-expire ang timer. Ipinapasa dito ang mensahe na sasabihin kapag nag-expire ang timer. Ang mga timer ay maaaring maulit, at ito ay makokontrol ng return value ng callback na ito - nagbabalik ito ng `false`, upang sabihin sa timer na huwag nang tumakbo muli.

1. Idagdag ang sumusunod na code sa dulo ng `processAudio` function:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Sinusuri ng code na ito ang kabuuang bilang ng segundo, at kung ito ay 0, babalik mula sa function call upang walang timer na ma-set. Kinoconvert nito ang kabuuang bilang ng segundo sa minuto at segundo.

1. Sa ibaba ng code na ito, idagdag ang sumusunod upang lumikha ng mensahe na sasabihin kapag nagsimula ang timer:

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

1. Sa ibaba nito, idagdag ang katulad na code upang lumikha ng mensahe na sasabihin kapag nag-expire ang timer:

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

1. Pagkatapos nito, sabihin ang mensahe ng pagsisimula ng timer:

    ```cpp
    say(begin_message);
    ```

1. Sa dulo ng function na ito, simulan ang timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Ina-activate nito ang timer. Ang timer ay na-set gamit ang milliseconds, kaya ang kabuuang bilang ng segundo ay minumultiply ng 1,000 upang ma-convert sa milliseconds. Ang `timerExpired` function ay ipinapasa bilang callback, at ang `end_message` ay ipinapasa bilang argumento sa callback. Ang callback na ito ay tumatanggap lamang ng `void *` na mga argumento, kaya ang string ay naaangkop na kino-convert.

1. Sa wakas, kailangang mag-*tick* ang timer, at ito ay ginagawa sa `loop` function. Idagdag ang sumusunod na code sa dulo ng `loop` function:

    ```cpp
    timer.tick();
    ```

1. I-build ang code na ito, i-upload ito sa iyong Wio Terminal at subukan ito sa pamamagitan ng serial monitor. Kapag nakita mo ang `Ready` sa serial monitor, pindutin ang C button (ang nasa kaliwang bahagi, pinakamalapit sa power switch), at magsalita. 4 na segundo ng audio ang makukuha, iko-convert sa text, pagkatapos ay ipapadala sa iyong function app, at isang timer ang ma-set. Siguraduhing tumatakbo ang iyong function app nang lokal.

    Makikita mo kung kailan nagsimula ang timer, at kung kailan ito natapos.

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

> 💁 Makikita mo ang code na ito sa [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) folder.

😀 Tagumpay ang iyong timer program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.